/*************
 *
 * Filename:    command_set.h
 *
 * Purpose:     Contains function for handling user input functionalities for DMS
 *
 * Copyright: � 2022 Sierra Wireless Inc., all rights reserved
 *
 **************/
#ifndef __COMMAND_SET_H__
#define __COMMAND_SET_H__

#ifdef __cplusplus
extern "C" {
#endif

#pragma once
#include "dms.h"
#include "swidms.h"
#include "fms.h"

#include "socket_server.h"
#include "user_input.h"

/* User options enumeration for DMS */
enum eUserOptions {
	eEXIT = -1,
	eUNKNOWN = 0,
	eGET_MODEL_ID = 1,
	eGET_FSN,
	eGET_DEV_CAP,
	eGET_BAND_CAP,
	eGET_DEV_MANUFACTURER,
	eGET_MSISDN,
	eGET_FW_INFO,
	eGET_MEID_IMEI,
	eGET_SWI_HOST_DEV_INFO,
	eSET_SWI_HOST_DEV_INFO,
	eSET_EVENT_REPORT,
	eGET_STORED_IMAGES,
	eSLQS_GET_STORED_IMAGES,
	eDEL_STORED_IMAGES,
	eSET_POWER,
	eGET_POWER,
	eGET_AUTO_SIM_LIST,
	eSET_AUTO_SIM_LIST,
	eGET_CUST_FEATURES,
	eSET_CUST_FEATURES,
	eGET_SDK_VERSION,
	eHELP,
};
	
typedef struct
{
	union
	{
		struct SETHOSTDEVINFO
		{
			pack_dms_SLQSSwiSetHostDevInfo_t packdmsSLQSSwiSetHostDevInfo;
			uint8_t inst;
		} sSetHostDevInfo;
		pack_fms_DeleteStoredImage_t packfmsDeleteStoredImage;
		pack_dms_SetPower_t sSetPower;
		pack_swidms_SLQSSwiDmsGetAutoSimList_t getAutoSimList;
		struct SETAUTOSIMLIST
		{
			pack_swidms_SLQSSwiDmsSetAutoSimList_t setAutoSimList;
			swi_dms_auto_sim_attributes_type_t attributes;
		} sSetAutoSimList;
		pack_dms_SetCustFeaturesV2_t sSetCustomFeatures;
	};
} socketDmsCommandParam;

// Can be taken as-is to other apps
void PrintPrompt(void);

// Can be taken as-is to other apps
void PrintDmsCmdListUsage();

// Specific to DMS power mode map
enum ARGUMENT_AVAIL GetPowerModeValue(const char* valueStr, uint32_t* pValue);

// Specific to DMS type map
enum ARGUMENT_AVAIL GetTypeValue(const char* valueStr, uint8_t* pValue);

// Can be taken as-is to other apps, if needed
enum eUserOptions GetDmsCommand(const char* command);

// Specific to DMS.  Need to implement accordling to each app
enum eUserOptions GetDmsSocketCommand(const char* procname, socketDmsCommandParam* cmdParam);

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif // __COMMAND_SET_H__
