/**************
 *
 * Filename:    command_set.c
 *
 * Purpose:     Implements DMS specific command handling
 *
 * Copyright: � 2022 Sierra Wireless Inc., all rights reserved
 *
 **************/
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <arpa/inet.h>
#include "str_util.h"

#include "command_set.h"

// ARGUMENT_SET array has to be defined for each command requring arguments

static ARGUMENT_SET g_set_swi_host_dev_info_arg_set[] =
{
	{"u", "manufacturer", "Manufacturer string", NULL, eOPTIONAL},
	{"M", "model", "Model string", NULL, eOPTIONAL},
	{"v", "version", "Version string", NULL, eOPTIONAL},
	{"p", "plasmaId", "Plasma ID string", NULL, eOPTIONAL},
	{"H", "hostId", "Host ID string", NULL, eOPTIONAL},
	{"i", "instance", "Instance string", NULL, eOPTIONAL}
};

static ARGUMENT_SET g_set_event_report_arg_set[] =
{
	{"r", "report", "Set Event Report Mode(0: reset 1: set 2: no change)", NULL, eMANDATORY}
};

static ARGUMENT_SET g_del_stored_image_arg_set[] =
{
	{"T", "imageType", "'modem'|'pri', e.g. --type cfg", NULL, eMANDATORY},
	{"I", "imageId", "Image ID string", NULL, eMANDATORY},
	{"b", "buildId", "Build ID string", NULL, eMANDATORY}
};

// StrIntValMap array should be defined for list of strings map to values
static StrIntValMap g_StoredImageTypeMap[] =
{
	{"modem", 0},	// Firmware
	{"pri", 1}	// configuration
};

static ARGUMENT_SET g_set_power_arg_set[] =
{
	{"P", "powerState", "'online'|'lowPower'|'factoryTestMode'|'offline'|'resetting'|'shuttingDown'|'persistentLowPower'|'modeOnlyLowPower'|'networkTest'|'campOnly', e.g. --powerState resetting", "Power state", eMANDATORY}
};

static StrIntValMap g_PowerModeMap[] =
{
	{"online", 0},
	{"lowPower", 1},
	{"factoryTestMode", 2},
	{"offline", 3},
	{"resetting", 4},
	{"shuttingDown", 5},
	{"persistentLowPower", 6},
	{"modeOnlyLowPower", 7},
	{"networkTest", 8},
	{"campOnly", 9}
};

static ARGUMENT_SET g_get_auto_sim_list_arg_set[] =
{
	{"c", "carrierName", "Carrier name string, e.g. --carrierName all", NULL, eMANDATORY}
};

static ARGUMENT_SET g_set_auto_sim_list_arg_set[] =
{
	{"c", "carrierName", "Carrier name string, e.g. --carrierName all", NULL, eMANDATORY},
	{"k", "key", "<ICCID>|<MCC:MNC>|'all', e.g. --key 302:690", NULL, eMANDATORY},
	{"t", "type", "ICCID: 0 MCCMNC: 1', e.g. --type 1", NULL, eOPTIONAL},
	{"R", "rank", "1-127|255. Required if 'key' is not 'all'", NULL, eDEPENDS},
	{"S", "subpri", "integer. Required if 'key' is not 'all'", NULL, eDEPENDS}
};

static StrIntValMap g_AutoSimTypeMap[] =
{
	{"modem", 0},
	{"pri", 1}
};

static ARGUMENT_SET g_set_cust_features_arg_set[] =
{
	{"f", "feature", "<featureId>=<featureValue>, e.g. --feature customSetting=3", NULL, eMANDATORY}
};

static ARGUMENT_SET g_help_arg_set[] =
{
	{"c", "command", "Command information", NULL, eOPTIONAL}
};

// Each app has to define COMMAND_SET array
static COMMAND_SET g_cmdset[] =
{
	{
		"GetModelId",
		"Get Model ID",
		0,
		NULL,
		eGET_MODEL_ID
	},
	{
		"GetFSN",
		"Get FSN",
		0,
		NULL,
		eGET_FSN
	},
	{
		"GetDeviceCapabilities",
		"Get Device Capabilities",
		0,
		NULL,
		eGET_DEV_CAP
	},
	{
		"GetBandCapabilities",
		"Get Band Capabilities",
		0,
		NULL,
		eGET_BAND_CAP
	},
	{
		"GetDeviceManufacturer",
		"Get Device Manufacturer",
		0,
		NULL,
		eGET_DEV_MANUFACTURER
	},
	{
		"GetMSISDN",
		"Get MSISDN",
		0,
		NULL,
		eGET_MSISDN
	},
	{
		"GetFirmwareInformation",
		"Get Firmware Information",
		0,
		NULL,
		eGET_FW_INFO
	},
	{
		"GetMeidImei",
		"Get MEID/IMEI",
		0,
		NULL,
		eGET_MEID_IMEI
	},
	{
		"GetSwiHostDevInfo",
		"Get SWI Host Dev Info",
		0,
		NULL,
		eGET_SWI_HOST_DEV_INFO
	},
	{
		"SetSwiHostDevInfo",
		"Set SWI Host Dev Info",
		sizeof(g_set_swi_host_dev_info_arg_set) / sizeof(ARGUMENT_SET),
		g_set_swi_host_dev_info_arg_set,
		eSET_SWI_HOST_DEV_INFO
	},
	{
		"SetEventReport",
		"Set Event Report",
		sizeof(g_set_event_report_arg_set) / sizeof(ARGUMENT_SET),
		g_set_event_report_arg_set,
		eSET_EVENT_REPORT
	},
	{
		"GetStoredImages",
		"Get Stored Images",
		0,
		NULL,
		eGET_STORED_IMAGES
	},
	{
		"SlqsGetStoredImages",
		"Get Stored Images (SLQS)",
		0,
		NULL,
		eSLQS_GET_STORED_IMAGES
	},
	{
		"DeleteStoredImage",
		"Delete Stored Image",
		sizeof(g_del_stored_image_arg_set) / sizeof(ARGUMENT_SET),
		g_del_stored_image_arg_set,
		eDEL_STORED_IMAGES
	},
	{
		"SetPower",
		"Set Power",
		sizeof(g_set_power_arg_set) / sizeof(ARGUMENT_SET),
		g_set_power_arg_set,
		eSET_POWER
	},
	{
		"GetPower",
		"Get Power",
		0,
		NULL,
		eGET_POWER
	},
	{
		"GetAutoSimList",
		"Get Auto-SIM List",
		sizeof(g_get_auto_sim_list_arg_set) / sizeof(ARGUMENT_SET),
		g_get_auto_sim_list_arg_set,
		eGET_AUTO_SIM_LIST
	},
	{
		"SetAutoSimList",
		"Set Auto-SIM List",
		sizeof(g_set_auto_sim_list_arg_set) / sizeof(ARGUMENT_SET),
		g_set_auto_sim_list_arg_set,
		eSET_AUTO_SIM_LIST
	},
	{
		"GetCustomFeatures",
		"Get Custom Features",
		0,
		NULL,
		eGET_CUST_FEATURES
	},
	{
		"SetCustomFeatures",
		"Set Custom Features",
		sizeof(g_set_cust_features_arg_set) / sizeof(ARGUMENT_SET),
		g_set_cust_features_arg_set,
		eSET_CUST_FEATURES
	},
	{
		"GetSdkVersion",
		"Get SDK Version",
		0,
		NULL,
		eGET_SDK_VERSION
	},
	{
		"exit",
		"Quit and exit the server",
		0,
		NULL,
		eEXIT
	},
	{
		"help",
		"Print this text",
		sizeof(g_help_arg_set) / sizeof(ARGUMENT_SET),
		g_help_arg_set,
		eHELP
	}
};

void PrintPrompt(void)
{
	OutputPrompt(g_cmdset, sizeof(g_cmdset) / sizeof(COMMAND_SET) - 2); // "- 2" so not to print "exit" and "help"
}

void PrintDmsCmdListUsage()
{
	PrintCmdListUsage(g_cmdset, sizeof(g_cmdset) / sizeof(COMMAND_SET) - 2); // "- 2" so not to print "exit" and "help"
}

enum eUserOptions GetDmsCommand(const char* command)
{
	int opt = atoi(command);
	return (opt >= eGET_MODEL_ID && opt <= eGET_SDK_VERSION) ? opt :
		Command2Option(g_cmdset, sizeof(g_cmdset) / sizeof(COMMAND_SET), command, eUNKNOWN);
}

enum ARGUMENT_AVAIL GetPowerModeValue(const char* valueStr, uint32_t* pValue)
{
	uint8_t val;
	enum ARGUMENT_AVAIL rtn = GetMappedStrValue(valueStr, g_PowerModeMap, sizeof(g_PowerModeMap) / sizeof(StrIntValMap), &val);
	*pValue = val;
	return rtn;
}

enum ARGUMENT_AVAIL GetTypeValue(const char* valueStr, uint8_t* pValue)
{
	return GetMappedStrValue(valueStr, g_AutoSimTypeMap, sizeof(g_AutoSimTypeMap) / sizeof(StrIntValMap), pValue);
}

// The format of this function for other apps should remain the same.
// The difference should be in each 'case' of command under 'switch'
enum eUserOptions GetDmsSocketCommand(const char* procname, socketDmsCommandParam* cmdParam)
{
	char* command = NULL;
	int cmd = GetSocketCommand(g_cmdset, sizeof(g_cmdset) / sizeof(COMMAND_SET), &command, eUNKNOWN);

    LockSocket();

	switch (cmd)
	{
	case eEXIT:
		SockLog(eLOG_INFO, "Exit %s\n", procname);
		break;
	case eHELP:
	{
		const char* pCmd = NULL;
		GetArgumentStrValue(NULL, &g_help_arg_set[0], &pCmd);
		PrintHelp(procname, g_cmdset, sizeof(g_cmdset) / sizeof(COMMAND_SET), pCmd);
		break;
	}
	case eSET_SWI_HOST_DEV_INFO:
		memset(&cmdParam->sSetHostDevInfo.packdmsSLQSSwiSetHostDevInfo, 0, sizeof(pack_dms_SLQSSwiSetHostDevInfo_t));

		enum ARGUMENT_AVAIL rtn = GetArgumentByteValue(command, &g_set_swi_host_dev_info_arg_set[5], &cmdParam->sSetHostDevInfo.inst);

		if (rtn == eValueNotFound ||
			CLONE_ARG_STR_VALUE(NULL, &g_set_swi_host_dev_info_arg_set[0], cmdParam->sSetHostDevInfo.packdmsSLQSSwiSetHostDevInfo.manString) == eValueNotFound ||
			CLONE_ARG_STR_VALUE(NULL, &g_set_swi_host_dev_info_arg_set[1], cmdParam->sSetHostDevInfo.packdmsSLQSSwiSetHostDevInfo.modelString) == eValueNotFound ||
			CLONE_ARG_STR_VALUE(NULL, &g_set_swi_host_dev_info_arg_set[2], cmdParam->sSetHostDevInfo.packdmsSLQSSwiSetHostDevInfo.swVerString) == eValueNotFound ||
			CLONE_ARG_STR_VALUE(NULL, &g_set_swi_host_dev_info_arg_set[3], cmdParam->sSetHostDevInfo.packdmsSLQSSwiSetHostDevInfo.plasmaIDString) == eValueNotFound ||
			CLONE_ARG_STR_VALUE(NULL, &g_set_swi_host_dev_info_arg_set[4], cmdParam->sSetHostDevInfo.packdmsSLQSSwiSetHostDevInfo.hostID) == eValueNotFound)
		{
			cmd = eUNKNOWN;
			break;
		}

		if (rtn == eFound)
			cmdParam->sSetHostDevInfo.packdmsSLQSSwiSetHostDevInfo.pInstance = &cmdParam->sSetHostDevInfo.inst;
		
		break;
	case eDEL_STORED_IMAGES:
		memset(&cmdParam->packfmsDeleteStoredImage, 0, sizeof(pack_fms_DeleteStoredImage_t));
		
		if (GET_ARG_MAPPED_STR_VALUE(command, &g_del_stored_image_arg_set[0], g_StoredImageTypeMap, &cmdParam->packfmsDeleteStoredImage.ImageInfo.imageType) != eFound ||
			CLONE_ARG_STR_VALUE(NULL, &g_del_stored_image_arg_set[1], (char*)cmdParam->packfmsDeleteStoredImage.ImageInfo.imageId) != eFound ||
			CLONE_ARG_STR_VALUE(NULL, &g_del_stored_image_arg_set[2], (char*)cmdParam->packfmsDeleteStoredImage.ImageInfo.buildId) != eFound)
			cmd = eUNKNOWN;

		cmdParam->packfmsDeleteStoredImage.ImageInfo.buildIdLength = (uint8_t)strlen((char*)cmdParam->packfmsDeleteStoredImage.ImageInfo.buildId);
		
		break;
	case eSET_POWER:
		memset(&cmdParam->sSetPower, 0, sizeof(pack_dms_SetPower_t));
		if (GET_ARG_MAPPED_UINT32_VALUE(command, &g_set_power_arg_set[0], g_PowerModeMap, &cmdParam->sSetPower.mode) != eFound)
			cmd = eUNKNOWN;
		break;
	case eGET_AUTO_SIM_LIST:
	{
		memset(&cmdParam->getAutoSimList, 0, sizeof(pack_swidms_SLQSSwiDmsGetAutoSimList_t));

		const char* pCmd = NULL;
		if (GetArgumentStrValue(command, &g_get_auto_sim_list_arg_set[0], &pCmd) == eFound &&
			strcmp(pCmd, "all") != 0)
			strcpy_s(cmdParam->getAutoSimList.carrier, QMI_SWI_DMS_AUTO_SIM_CARRIER_NAME_MAX, pCmd);
		
		break;
	}
	case eSET_AUTO_SIM_LIST:
	{
		memset(&cmdParam->sSetAutoSimList.setAutoSimList, 0, sizeof(pack_swidms_SLQSSwiDmsSetAutoSimList_t));
		memset(&cmdParam->sSetAutoSimList.attributes, 0, sizeof(swi_dms_auto_sim_attributes_type_t));

		const char* pCmd = NULL;
		if (GetArgumentStrValue(command, &g_set_auto_sim_list_arg_set[0], &pCmd) != eFound)
		{
			cmd = eUNKNOWN;
			break;
		}

		if (strcmp(pCmd, "all") != 0)
		{
			strcpy_s(cmdParam->sSetAutoSimList.setAutoSimList.carrier, QMI_SWI_DMS_AUTO_SIM_CARRIER_NAME_MAX, pCmd);

			if (GET_ARG_MAPPED_STR_VALUE(command, &g_set_auto_sim_list_arg_set[2], g_AutoSimTypeMap, (uint8_t*)&cmdParam->sSetAutoSimList.attributes.type) == eValueNotFound ||
				GetArgumentStrValue(NULL, &g_set_auto_sim_list_arg_set[1], &pCmd) != eFound)
			{
				cmd = eUNKNOWN;
				break;
			}
			
			if (strcmp(pCmd, "all") != 0)
			{
				cmdParam->sSetAutoSimList.attributes.key_len = strlen(pCmd);
				
				if (cmdParam->sSetAutoSimList.attributes.key_len != 7 || 
					GetArgumentByteValue(NULL, &g_set_auto_sim_list_arg_set[3], &cmdParam->sSetAutoSimList.attributes.rank) != eFound ||
					GetArgumentByteValue(NULL, &g_set_auto_sim_list_arg_set[4], &cmdParam->sSetAutoSimList.attributes.subpri) != eFound)
				{
					cmd = eUNKNOWN;
					break;
				}

				strcpy_s(cmdParam->sSetAutoSimList.attributes.key, QMI_SWI_DMS_AUTO_SIM_KEY_LENGTH_MAX, pCmd);
				cmdParam->sSetAutoSimList.setAutoSimList.pAttributes = &cmdParam->sSetAutoSimList.attributes;
			}
		}

		break;
	}
	case eSET_CUST_FEATURES:
	{
		memset(&cmdParam->sSetCustomFeatures, 0, sizeof(pack_dms_SetCustFeaturesV2_t));

		const char* pCmd = NULL;
		if (GetArgumentStrValue(command, &g_set_cust_features_arg_set[0], &pCmd) == eFound &&
			GetNameByteValuePair(pCmd,
				(char*)cmdParam->sSetCustomFeatures.cust_id, DMS_MAX_CUST_ID_LEN,
				(char*)cmdParam->sSetCustomFeatures.cust_value) == eFound)
			cmdParam->sSetCustomFeatures.value_length = 1;
		else
			cmd = eUNKNOWN;

		break;
	}
	case eUNKNOWN:
		SockLog(eLOG_INFO, "Error: invalid command\n");
	default:
		break;
	}

    UnlockSocket();

	return cmd;
}
