#include <string.h>
#include "common.h"
#include "proc_util.h"
#include "qmux_util.h"
#include "ts_handler.h"
#include "ts.h"

extern bool g_exiting;

static QmiService s_TsService;
static uint8_t tsVer = 0; // Initialize to unknown. 1: v1, 2: v2
static uint32_t tsNumSensors = 0;
static ts_sensorId* pTsSensors = NULL;

void TsIndicationCallback(uint8_t* qmiPacket, uint16_t qmiPacketSize, void* pIndicationCallbackContext);

void reg_ts_notif(bool reg)
{
	if (pTsSensors == NULL)
		return;

	for (uint8_t i = 0; i < tsNumSensors; i++)
	{
		float highThres = 50.0;
		float lowThres = 10.0;
		pack_ts_SLQSTsRegNotTempRpt_t sRegNotif;
		memcpy(&sRegNotif.sensor, &pTsSensors[i], sizeof(ts_sensorId));
		sRegNotif.curTempReport = 1;
		sRegNotif.pHighThresTemp = reg ? &highThres : NULL;
		sRegNotif.pLowThresTemp = reg ? &lowThres : NULL;
		sRegNotif.pSeqNum = NULL;

		int rtn = tsVer < 2 ?
			SENDRECEIVE(&s_TsService, pack_ts_SLQSTsRegNotTempRpt, &sRegNotif, unpack_ts_SLQSTsRegNotTempRpt, NULL) :
			SENDRECEIVE(&s_TsService, pack_ts_SLQSTsRegNotTempRptV2, &sRegNotif, unpack_ts_SLQSTsRegNotTempRptV2, NULL);

		if (rtn == 0)
			dlog(eLOG_INFO, "  Thermal sensor \"%s\" notification %s\n",
				sRegNotif.sensor.sensorId, reg ? "registered" : "deregistered");
		else
			dlog(eLOG_ERROR, "  Thermal sensor \"%s\" notification %s error %d\n",
				sRegNotif.sensor.sensorId, reg ? "registeration" : "deregisteration", rtn);
	}
}

void register_ts_ind(CtlService* pCtlSvc)
{
	if (pCtlSvc == NULL)
		return;

	dlog(eLOG_INFO, "\nRegistering thermal sensor notification(s)\n");

	int rtn = CtlService_InitializeRegularService(pCtlSvc, &s_TsService, eTS, TsIndicationCallback, NULL);
	if (rtn != 0)
	{
		dlog(eLOG_ERROR, "InitializeRegularService eTS failed.\n");
		s_TsService.serviceType = 0;
		return;
	}

	uint8_t msgIDs[64];
	memset(msgIDs, 0, sizeof(msgIDs));

	unpack_ts_SLQSTsGetSupportedMsgs_t supMsgs;
	supMsgs.numMsgs = sizeof(msgIDs) / sizeof(uint8_t);
	supMsgs.pMsgIds = msgIDs;

	rtn = SENDRECEIVE(&s_TsService, pack_ts_SLQSTsGetSupportedMsgs, NULL, unpack_ts_SLQSTsGetSupportedMsgs, &supMsgs);
	if (rtn == 0)
	{
		if (supMsgs.numMsgs > 6)
			tsVer = 2;
		else if (supMsgs.numMsgs > 4)
			tsVer = 1;
	}

	if (tsVer > 1)
	{
		unpack_ts_SLQSTsGetNumSensors_t numSensors;
		numSensors.numSensors = 0;

		if (SENDRECEIVE(&s_TsService, pack_ts_SLQSTsGetNumSensors, NULL, unpack_ts_SLQSTsGetNumSensors, &numSensors) == 0)
		{
			dlog(eLOG_INFO, "Number of sensors: %d\n",  numSensors.numSensors);
			pTsSensors = calloc(numSensors.numSensors, sizeof(ts_sensorId));
		}
	}
	else
		pTsSensors = calloc(MAX_SENSOR_LIST_LEN, sizeof(ts_sensorId));

	if (pTsSensors == NULL)
	{
		dlog(eLOG_ERROR, "Unable to allocate memory for TsSensors\n");
		return;
	}

	unpack_ts_SLQSTsGetSensorList_t tsSensorList;
	tsNumSensors = 0;
	ulong listIdx = 0;

	do
	{
		memset(&tsSensorList, 0, sizeof(unpack_ts_SLQSTsGetSensorList_t));
		tsSensorList.sensorListLen = MAX_SENSOR_LIST_LEN;

		rtn = tsVer < 2 ? 
			SENDRECEIVE(&s_TsService, pack_ts_SLQSTsGetSensorList, NULL, unpack_ts_SLQSTsGetSensorList, &tsSensorList) :
			SENDRECEIVE(&s_TsService, pack_ts_SLQSTsGetSensorListV2, &listIdx, unpack_ts_SLQSTsGetSensorListV2, &tsSensorList), listIdx++;

		if (rtn != 0 || tsSensorList.sensorListLen == 0)
			break;

		memcpy(&pTsSensors[tsNumSensors], tsSensorList.sensorList, sizeof(ts_sensorId) * tsSensorList.sensorListLen);
		tsNumSensors += tsSensorList.sensorListLen;
	} while (tsVer > 1);

	dlog(eLOG_INFO, "Received list of %d thermal sensor(s)\n", tsNumSensors);

	reg_ts_notif(true);
}

void deregister_ts_ind(CtlService* pCtlSvc)
{
	if (pCtlSvc == NULL)
		return;

	dlog(eLOG_INFO, "\nDeregistering thermal sensor notification(s)\n");

	reg_ts_notif(false);

	free(pTsSensors);
	pTsSensors = NULL;
	tsNumSensors = 0;

	CtlService_ShutDownRegularService(pCtlSvc, &s_TsService);
}

void TsIndicationCallback(uint8_t* qmiPacket, uint16_t qmiPacketSize, void* pIndicationCallbackContext)
{
	if (g_exiting || IndicationCallback("TS", eTS, qmiPacket, qmiPacketSize, pIndicationCallbackContext) != 0x22)
		return;

	unpack_ts_SLQSTsTempRptCallback_ind_t ind_rsp;
	int rtn = tsVer < 2 ?
		unpack_ts_SLQSTsTempRptCallback_ind(qmiPacket, qmiPacketSize, &ind_rsp) :
		unpack_ts_SLQSTsTempRptCallback_indV2(qmiPacket, qmiPacketSize, &ind_rsp);
	if (rtn != 0)
		return;

	dlog(eLOG_INFO, "[unpack_ts_SLQSTsTempRptCallback_ind]\n");

	if (swi_uint256_get_bit(ind_rsp.ParamPresenceMask, 1))
	{
		printf("\tsensor id len: %d\n", ind_rsp.sensor.sensorIdLen);
		printf("\tsensor id: %s\n", ind_rsp.sensor.sensorId);
	}

	if (swi_uint256_get_bit(ind_rsp.ParamPresenceMask, 2))
		printf("\treport type: %d\n", ind_rsp.type);

	if (swi_uint256_get_bit(ind_rsp.ParamPresenceMask, 0x10))
		printf("\ttemperature: %.1f degree C\n", ind_rsp.temp);

	if (swi_uint256_get_bit(ind_rsp.ParamPresenceMask, 0x11))
		printf("\tseq #: %d\n", ind_rsp.seqNum);
}
