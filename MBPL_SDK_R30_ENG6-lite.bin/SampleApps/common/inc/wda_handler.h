/*************
 *
 * Filename:    wda_handler.h
 *
 * Purpose:     Contains function for handling QMI WDA requests
 *
 * Copyright: © 2022 Sierra Wireless Inc., all rights reserved
 *
 **************/
#ifndef __WDA_HANDLER_H__
#define __WDA_HANDLER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "qmux_util.h"

#define QOS_HDR_NOT_PRESENT	0
#define QOS_HDR_PRESENT	1
#define MAX_DL_PKT_AGGR  10
#define MAX_UL_PKT_AGGR  10
#define QMAP_RX_BUFFER_SIZE 0x4000
#define QMAP_TX_BUFFER_SIZE 0x4000
#define EP_TYPE_HSUSB	2
#define EP_TYPE_PCIE	3
#define FLOW_CTL_NO_TE	0

typedef struct
{
	bool SetQosHrPres;
	uint8_t  QosHrPres;
	bool SetUL_Data_Aggregation_Max_Datagrams;
	uint32_t UL_Data_Aggregation_Max_Datagrams;
	bool SetDL_Data_Aggregation_Max_Datagrams;
	uint32_t DL_Data_Aggregation_Max_Datagrams;
	bool SetUL_Data_Aggregation_Max_Size;
	uint32_t UL_Data_Aggregation_Max_Size;
	bool SetDL_Data_Aggregation_Max_Size;
	uint32_t DL_Data_Aggregation_Max_Size;
	bool SetPeripheralEP_ID;
	uint32_t EP_Type;
	uint32_t Interface_ID;
	bool SetDL_Padding;
	uint32_t DL_Padding;
	bool SetFlow_Control;
	uint8_t  Flow_Control;
} WdaSetDataFormatParams, * WdaSetDataFormatParamsPtr;

/*
 * Name:     EnableQmap
 *
 * Purpose:  Enable QMAP
 *
 * Params:   pCtlService	- Pointer to control service
 *			 bEnable		- true to enable QMAP, false to disable
 *			 pParams		- Pointer to WdaSetDataFormatParams structure containing WDA_SET_DATA_FORMAT parameters
 *
 * Return:   0 - success, other values - failure
 *
 * Notes:    QMAP settings should match those used by the PCIe device driver.
 */
int EnableQmap(CtlService* pCtlService, bool bEnable, WdaSetDataFormatParamsPtr pParams);

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif // __WDA_HANDLER_H__

