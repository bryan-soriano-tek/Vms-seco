#include <string.h>
#include "common.h"
#include "proc_util.h"
#include "qmux_util.h"
#include "tmd_handler.h"
#include "tmd.h"

extern bool g_exiting;

static QmiService s_TmdService;
static unpack_tmd_SLQSTmdGetMitigationDevList_t tmdDevList;

void TmdIndicationCallback(uint8_t* qmiPacket, uint16_t qmiPacketSize, void* pIndicationCallbackContext);

void register_mit_ind(CtlService* pCtlSvc)
{
	if (pCtlSvc == NULL)
		return;

	dlog(eLOG_INFO, "\nRegistering thermal mitigation device notification(s)\n");

	memset(&tmdDevList, 0, sizeof(unpack_tmd_SLQSTmdGetMitigationDevList_t));
	tmdDevList.MitigationDevListLen = TMD_MAX_DEV_LIST;

	int rtn = CtlService_InitializeRegularService(pCtlSvc, &s_TmdService, eTMD, TmdIndicationCallback, NULL);
	if (rtn != 0)
	{
		dlog(eLOG_ERROR, "InitializeRegularService eTMD failed.\n");
		s_TmdService.serviceType = 0;
		return;
	}

	rtn = SENDRECEIVE(&s_TmdService, pack_tmd_SLQSTmdGetMitigationDevList, NULL, unpack_tmd_SLQSTmdGetMitigationDevList, &tmdDevList);
	if (rtn != 0)
	{
		tmdDevList.MitigationDevListLen = 0;
		dlog(eLOG_ERROR, "Unable to get mitigation device list - %d\n", rtn);
		return;
	}

	for (uint8_t i = 0; i < tmdDevList.MitigationDevListLen; i++)
	{
		unpack_tmd_SLQSTmdRegNotMitigationLvl_t regOutput;
		int rtn = SENDRECEIVE(&s_TmdService, pack_tmd_SLQSTmdRegNotMitigationLvl, (pack_tmd_SLQSTmdRegNotMitigationLvl_t*)&tmdDevList.MitigationDevList[i], unpack_tmd_SLQSTmdRegNotMitigationLvl, &regOutput);

		if (rtn == 0)
			dlog(eLOG_INFO, "  Thermal mitigation device \"%s\" notification registered\n",
				tmdDevList.MitigationDevList[i].mitigationDevId);
		else
			dlog(eLOG_ERROR, "  Thermal mitigation device \"%s\" notification registeration error %d\n",
				tmdDevList.MitigationDevList[i].mitigationDevId, rtn);
	}
}

void deregister_mit_ind(CtlService* pCtlSvc)
{
	if (pCtlSvc == NULL)
		return;

	dlog(eLOG_INFO, "\nDeregistering thermal mitigation device notification(s)\n");

	for (uint8_t i = 0; i < tmdDevList.MitigationDevListLen; i++)
	{
		unpack_tmd_SLQSTmdDeRegNotMitigationLvl_t deregOutput;
		int rtn = SENDRECEIVE(&s_TmdService, pack_tmd_SLQSTmdDeRegNotMitigationLvl, (pack_tmd_SLQSTmdDeRegNotMitigationLvl_t*)&tmdDevList.MitigationDevList[i], unpack_tmd_SLQSTmdDeRegNotMitigationLvl, &deregOutput);

		if (rtn == 0)
			dlog(eLOG_INFO, "  Thermal mitigation device \"%s\" notification deregistered\n",
				tmdDevList.MitigationDevList[i].mitigationDevId);
		else
			dlog(eLOG_ERROR, "  Thermal mitigation device \"%s\" notification deregisteration error %d\n",
				tmdDevList.MitigationDevList[i].mitigationDevId, rtn);
	}

	CtlService_ShutDownRegularService(pCtlSvc, &s_TmdService);
}

void TmdIndicationCallback(uint8_t* qmiPacket, uint16_t qmiPacketSize, void* pIndicationCallbackContext)
{
	if (g_exiting || IndicationCallback("TMD", eTMD, qmiPacket, qmiPacketSize, pIndicationCallbackContext) != 0x25)
		return;

	unpack_tmd_SLQSTmdMitigationLvlRptCallback_ind_t ind_rsp;
	if (unpack_tmd_SLQSTmdMitigationLvlRptCallback_ind(qmiPacket, qmiPacketSize, &ind_rsp) != 0)
		return;

	dlog(eLOG_INFO, "[unpack_tmd_SLQSTmdMitigationLvlRptCallback_ind]\n");

	if (swi_uint256_get_bit(ind_rsp.ParamPresenceMask, 1))
	{
		printf("\tdevice id len: %d\n", ind_rsp.deviceIdLen);
		printf("\tdevice id: %s\n", ind_rsp.deviceID);
	}

	if (swi_uint256_get_bit(ind_rsp.ParamPresenceMask, 2))
		printf("\tlevel: %d\n", ind_rsp.lvl);
}
