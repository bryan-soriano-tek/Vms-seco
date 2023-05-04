#include <string.h>
#include <QmiSyncObject.h>
#include "qmerrno.h"
#include "proc_util.h"
#include "wda_handler.h"
#include "wda.h"	// For enabling QMAP

/*
 * Name:     EnableQmap
 *
 * Purpose:  Enable QMAP
 *
 * Params:   pCtlService	- Pointer to control service
 *			 bEnable		- TRUE to enable QMAP, FALSE to disable
 *			 pParams		- Pointer to WdaSetDataFormatParams structure containing WDA_SET_DATA_FORMAT parameters
 *
 * Return:   0 - success, other values - failure
 *
 * Notes:    QMAP settings should match those used by the PCIe device driver.
 */
int EnableQmap(CtlService* pCtlService, bool bEnable, WdaSetDataFormatParamsPtr pParams)
{
	#define LINK_PROTOCOL_IP_MODE	2
	#define DATA_AGG_PROTOCOL_QMAP_DISABLED	0
	#define DATA_AGG_PROTOCOL_QMAP_ENABLED	5

	if (pCtlService == NULL || pParams == NULL)
		return -1;

	QmiService wdaService;

	int ret = CtlService_InitializeRegularService(pCtlService, &wdaService, eWDA, NULL, NULL);
	if (ret != 0)
	{
		dlog(eLOG_ERROR, "InitializeRegularService eWDA failed.");
		return ret;
	}

	uint32_t ReqLinkProtocol = LINK_PROTOCOL_IP_MODE;
	uint32_t ReqULProtocol = bEnable ? DATA_AGG_PROTOCOL_QMAP_ENABLED : DATA_AGG_PROTOCOL_QMAP_DISABLED;
	uint32_t ReqDLProtocol = bEnable ? DATA_AGG_PROTOCOL_QMAP_ENABLED : DATA_AGG_PROTOCOL_QMAP_DISABLED;

	pack_wda_SetDataFormat_t dataFormat;
	memset(&dataFormat, 0, sizeof(pack_wda_SetDataFormat_t));
	dataFormat.pQlink_prot = &ReqLinkProtocol;
	dataFormat.pDl_data_aggregation_protocol = &ReqDLProtocol;
	dataFormat.pUl_data_aggregation_protocol = &ReqULProtocol;

	if (pParams->SetQosHrPres)
		dataFormat.pQos_format = &pParams->QosHrPres;
	if (pParams->SetUL_Data_Aggregation_Max_Datagrams)
		dataFormat.pUl_data_aggregation_max_datagrams = &pParams->UL_Data_Aggregation_Max_Datagrams;
	if (pParams->SetDL_Data_Aggregation_Max_Datagrams)
		dataFormat.pDl_data_aggregation_max_datagrams = &pParams->DL_Data_Aggregation_Max_Datagrams;
	if (pParams->SetUL_Data_Aggregation_Max_Size)
		dataFormat.pUl_data_aggregation_max_size = &pParams->UL_Data_Aggregation_Max_Size;
	if (pParams->SetDL_Data_Aggregation_Max_Size)
		dataFormat.pDl_data_aggregation_max_size = &pParams->DL_Data_Aggregation_Max_Size;
	if (pParams->SetPeripheralEP_ID)
	{
		dataFormat.pEp_type = &pParams->EP_Type;
		dataFormat.pIface_id = &pParams->Interface_ID;
	}
	if (pParams->SetDL_Padding)
		dataFormat.pDl_minimum_padding = &pParams->DL_Padding;
	if (pParams->SetFlow_Control)
		dataFormat.pFlow_control = &pParams->Flow_Control;

	uint8_t  RespQoS_header_presence = 0;
	uint32_t RespLink_Protocol = 0;
	uint32_t RespUL_Data_Aggregation_Protocol = 0;
	uint32_t RespDL_Data_Aggregation_Protocol = 0;
	uint32_t RespNdp_Signature = 0;
	uint32_t RespDL_Data_Aggregation_Max_Datagrams = 0;
	uint32_t RespDL_Data_Aggregation_Max_Size = 0;
	uint32_t RespUL_Data_Aggregation_Max_Datagrams = 0;
	uint32_t RespUL_Data_Aggregation_Max_Size = 0;
	uint32_t RespDL_Padding = 0;
	uint8_t  RespFlow_Control = 0;

	unpack_wda_SetDataFormat_t dataFormatOut;
	memset(&dataFormatOut, 0, sizeof(unpack_wda_SetDataFormat_t));
	dataFormatOut.pQos_format = &RespQoS_header_presence;
	dataFormatOut.pQlink_prot = &RespLink_Protocol;
	dataFormatOut.pUl_data_aggregation_protocol = &RespUL_Data_Aggregation_Protocol;
	dataFormatOut.pDl_data_aggregation_protocol = &RespDL_Data_Aggregation_Protocol;
	dataFormatOut.pNdp_signature = &RespNdp_Signature;
	dataFormatOut.pDl_data_aggregation_max_datagrams = &RespDL_Data_Aggregation_Max_Datagrams;
	dataFormatOut.pDl_data_aggregation_max_size = &RespDL_Data_Aggregation_Max_Size;
	dataFormatOut.pUl_data_aggregation_max_datagrams = &RespUL_Data_Aggregation_Max_Datagrams;
	dataFormatOut.pUl_data_aggregation_max_size = &RespUL_Data_Aggregation_Max_Size;
	dataFormatOut.pDl_minimum_padding = &RespDL_Padding;
	dataFormatOut.pFlow_control = &RespFlow_Control;

	ret = SENDRECEIVE(&wdaService, pack_wda_SetDataFormat, &dataFormat,	unpack_wda_SetDataFormat, &dataFormatOut);

	if (ret == eQCWWAN_ERR_NONE)
		printf("QMAP %s\n", bEnable ? "enabled" : "disabled");
	else
		printf("Failed to set QMAP data format\n");

	CtlService_ShutDownRegularService(pCtlService, &wdaService);

	return ret;
}

