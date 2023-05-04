/**************
 *
 * Filename:    command_set.c
 *
 * Purpose:     Implements UIM specific command handling
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
static ARGUMENT_SET g_event_register[] =
{
	{"a", "event_mask", "event register mask", NULL, eMANDATORY}
};

static ARGUMENT_SET g_switch_slot[] =
{
	{"b", "logical_slot", "logical slot(Slot 1: 1, Slot 2: 2, Slot 3: 3, Slot 4: 4, Slot 5: 5)", NULL, eMANDATORY},
	{"w", "physical_slot", "physical slot(Slot 1: 1, Slot 2: 2, Slot 3: 3, Slot 4: 4, Slot 5: 5)", NULL, eMANDATORY},
};

static ARGUMENT_SET g_verify_pin[] =
{	
	{"e", "session_info", "session type, app ID", NULL, eMANDATORY},
	{"f", "pin_id", "PIN ID, PIN Code: 1|2|3|4,xxxx", NULL, eMANDATORY},
	{"g", "encrypted_value", "Encrypted Value of PIN1 (xxx)", NULL, eOPTIONAL},
	{"i", "key_ref_id", "1|2|3|4|5|6|7|8", NULL, eOPTIONAL},
	{"j", "indication_token", "x", NULL, eOPTIONAL},
};

static ARGUMENT_SET g_authenticate[] =
{	
	{"e", "session_info", "session type, app ID", NULL, eMANDATORY},
	{"y", "authenticate_data", "context, data: 1-17,xxxx", NULL, eMANDATORY},
	{"j", "indication_token", "x", NULL, eOPTIONAL},
};

static ARGUMENT_SET g_set_pin_protection[] =
{
	{"e", "session_info", "session type, app ID", NULL, eMANDATORY},
	{"f", "pin_id", "PIN ID, PIN Operation(Disable/Enable), PIN code: PIN=1|2|3|4,0|1,xxxx", NULL, eMANDATORY},
	{"i", "key_ref_id", "1|2|3|4|5|6|7|8", NULL, eOPTIONAL},
	{"j", "indication_token", "x", NULL, eOPTIONAL},
};

static ARGUMENT_SET g_set_unblock_pin[] =
{
	{"e", "session_info", "session type, 0", NULL, eMANDATORY},
	{"k", "unblock_pin", "PIN ID, PIN Unlock key value -ascii, new PIN value", NULL, eMANDATORY},
	{"i", "key_ref_id", "1|2|3|4|5|6|7|8", NULL, eOPTIONAL},
	{"j", "indication_token", "xx", NULL, eOPTIONAL},
};

static ARGUMENT_SET g_set_referesh_register[] =
{
	{"e", "session_info", "session type, app ID", NULL, eMANDATORY},
	{"n", "referesh_registger", "Rgister Refresh(register flag,vote for init,file id,path value): (0|1),(0|1),2,path", NULL, eMANDATORY},
};

static ARGUMENT_SET g_set_refresh_get_laset_event[] =
{
	{"e", "session_info", "session type, app ID", NULL, eMANDATORY},
};

static ARGUMENT_SET g_get_file_attributes[] =
{
	{"e", "session_info", "session type, app ID", NULL, eMANDATORY},
	{"t", "file_info", "File Info(File ID, path(optional), UICC Security Attributes(optional 0:Skip security attributes, 1:return security attributes)): ID,path", NULL, eMANDATORY},
	{"j", "indication_token", "x", NULL, eOPTIONAL},
	{"z", "security_attributes", "x", NULL, eOPTIONAL},
};

static ARGUMENT_SET g_depersonalization[] =
{
	{"l", "depersonalization", "feature (0-10), operation(0|1), key (ASCII Control key value)", NULL, eMANDATORY},
	{"p", "slot", "1-5", NULL, eOPTIONAL},
};

static ARGUMENT_SET g_get_configuration[] =
{
	{"u", "event_mask", "ex. 0x03FF", NULL, eOPTIONAL},
};

static ARGUMENT_SET g_set_change_pin[] =
{
	{"e", "session_info", "session type, app ID", NULL, eMANDATORY},
	{"v", "change_pin_info", "PIN ID, old PIN, new PIN, e.x. 1|2|3|4,xxxx,yyyy", NULL, eMANDATORY},
	{"i", "key_ref_id", "1|2|3|4|5|6|7|8", NULL, eOPTIONAL},
	{"j", "indication_token", "x", NULL, eOPTIONAL},
};

static ARGUMENT_SET g_help_arg_set[] =
{
	{"c", "command", "Command information", NULL, eOPTIONAL}
};

// Each app has to define COMMAND_SET array
static COMMAND_SET g_cmdset[] =
{
	{
		"GetSlotsStatus",
		"Get Slots Status",
		0,
		NULL,
		eREG_GET_SLOT_STATUS
	},
	{
		"GetCardStatus",
		"Get Card Status",
		0,
		NULL,
		eGET_CARD_STATUS
	},
	{
		"GetIccid",
		"Get ICCID",
		0,
		NULL,
		eGET_ICCID
	},
	{
		"EventRegister",
		"Event Register",
		sizeof(g_event_register) / sizeof(ARGUMENT_SET),
		g_event_register,
		eSET_EVENT_REGISTER
	},
	{
		"SwitchSlot",
		"Switch Slot",
		sizeof(g_switch_slot) / sizeof(ARGUMENT_SET),
		g_switch_slot,
		eSET_SWITCH_SLOT
	},
	{
		"VerifyPin",
		"Verify PIN",
		sizeof(g_verify_pin) / sizeof(ARGUMENT_SET),
		g_verify_pin,
		eSET_VERIFY_PIN
	},
	{
		"SetPinProtection",
		"Set PIN Protection",
		sizeof(g_set_pin_protection) / sizeof(ARGUMENT_SET),
		g_set_pin_protection,
		eSET_PIN_PROTECTION
	},
	{
		"UnblockPin",
		"Unblock PIN",
		sizeof(g_set_unblock_pin) / sizeof(ARGUMENT_SET),
		g_set_unblock_pin,
		eSET_UNBLOCK_PIN
	},
	{
		"PowerDown",
		"Power Down",
		0,
		NULL,
		eSET_POWER_DOWN
	},
	{
		"PowerUp",
		"Power Up",
		0,
		NULL,
		eSET_POWER_UP
	},
	{
		"Reset",
		"Reset the state of the issuing control point kept by the service",
		0,
		NULL,
		eSET_RESET
	},
	{
		"RefreshRegister",
		"Refresh Register",
		sizeof(g_set_referesh_register) / sizeof(ARGUMENT_SET),
		g_set_referesh_register,
		eSET_REFRESH_REGISTER
	},
	{
		"RefreshGetLastEvent",
		"Refresh Get Last Event",
		sizeof(g_set_refresh_get_laset_event) / sizeof(ARGUMENT_SET),
		g_set_refresh_get_laset_event,
		eGET_REFRESH_LAST_EVENT
	},
	{
		"GetFileAttributes",
		"Get File Attributes",
		sizeof(g_get_file_attributes) / sizeof(ARGUMENT_SET),
		g_get_file_attributes,
		eGET_FILE_ATTRIBUTES
	},	
	{
		"Depersonalization",
		"Depersonalization",
		sizeof(g_depersonalization) / sizeof(ARGUMENT_SET),
		g_depersonalization,
		eGET_DEPERSONALIZATION
	},
	{
		"Authenticate",
		"Authenticate",
		sizeof(g_authenticate) / sizeof(ARGUMENT_SET),
		g_authenticate,
		eGET_AUTHENTICATE
	},
	{
		"GetConfiguration",
		"Get Configuration",
		sizeof(g_get_configuration) / sizeof(ARGUMENT_SET),
		g_get_configuration,
		eGET_CONFIGURATION
	},	
	{
		"ChangePin",
		"Change PIN",
		sizeof(g_set_change_pin) / sizeof(ARGUMENT_SET),
		g_set_change_pin,
		eSET_CHANGE_PIN
	},	
	{
		"ReadTransparent",
		"Read Transparent",
		0,
		NULL,
		eGET_READ_TRANSPARENT
	},
	{
		"exit",
		"shut down the server",
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

void PrintUimCmdListUsage()
{
	PrintCmdListUsage(g_cmdset, sizeof(g_cmdset) / sizeof(COMMAND_SET) - 2); // "- 2" so not to print "exit" and "help"
}

enum eUserOptions GetUimCommand(const char* command)
{
	int opt = atoi(command);
	return (opt >= eREG_GET_SLOT_STATUS && opt <= eGET_READ_TRANSPARENT) ? opt :
		Command2Option(g_cmdset, sizeof(g_cmdset) / sizeof(COMMAND_SET), command, eUNKNOWN);
}

// The format of this function for other apps should remain the same.
// The difference should be in each 'case' of command under 'switch'
enum eUserOptions GetUimSocketCommand(const char* procname, socketUimCommandParam* cmdParam)
{
	char* command = NULL;
	int cmd = GetSocketCommand(g_cmdset, sizeof(g_cmdset) / sizeof(COMMAND_SET), &command, eUNKNOWN);
	enum ARGUMENT_AVAIL ret = eFlagNotFound;

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
	case eREG_GET_SLOT_STATUS:
	case eGET_CARD_STATUS:
	case eGET_ICCID:
	break;
	case eSET_EVENT_REGISTER:
	{
		const char* pMasks = NULL;
		char szMasks[50] = {0};
		if (GetArgumentStrValue(NULL, &g_event_register[0], &pMasks) != eFound)
			cmd = eUNKNOWN;
		else
		{
			StrCpy(szMasks, pMasks);
			GetUimMasks(szMasks, &cmdParam->eventRegister.eventMask);
		}	
	}
	break;
	case eSET_SWITCH_SLOT:
		if (GetArgumentByteValue(command, &g_switch_slot[0], &cmdParam->switchSlotIn.bLogicalSlot) != eFound ||
			GetArgumentIntValue(command, &g_switch_slot[1], &cmdParam->switchSlotIn.ulPhysicalSlot) != eFound)
		{
			cmd = eUNKNOWN;
		}
	break;
	case eSET_VERIFY_PIN:
	{
        memset(&cmdParam->sVerifyPin.verifyPin, 0, sizeof(pack_uim_VerifyPin_t));
		const char *pSessionInfo = NULL;
		const char *pPinId = NULL;
		const char *pEncryptedPIN1 = NULL;
		char szSessionInfo[50] = {0};
		char szPinId[50] = {0};
		char szEncryptedPIN1[50] = {0};

		if (GetArgumentStrValue(command, &g_verify_pin[0], &pSessionInfo) != eFound ||
			GetArgumentStrValue(command, &g_verify_pin[1], &pPinId) != eFound)
		{
			cmd = eUNKNOWN;
			break;
		}
		StrCpy(szSessionInfo, pSessionInfo);
		StrCpy(szPinId, pPinId);
        GetUimSessionInformation(szSessionInfo, &cmdParam->sVerifyPin.verifyPin.sessionInfo);
		if (false == GetUimVerifyPinInfo(szPinId, &cmdParam->sVerifyPin.verifyPin))
		{
			SockLog(eLOG_INFO, "Error: VerifyPin operation wrong --pin_id (-f) parameter\n");
			cmd = eUNKNOWN;
			break;
		}
		if (GetArgumentStrValue(command, &g_verify_pin[2], &pEncryptedPIN1) == eValueNotFound)
		{
			SockLog(eLOG_INFO, "Error: VerifyPin operation wrong/missing --encrypted_value (-g) parameter\n");
			cmd = eUNKNOWN;
			break;
		}
		else if (ret != eFlagNotFound) 
		{
			StrCpy(szEncryptedPIN1, pEncryptedPIN1);
			GetUimEncryptPin1Info(szEncryptedPIN1, &cmdParam->sVerifyPin.EncryptedPIN1);
			cmdParam->sVerifyPin.verifyPin.pEncryptedPIN1 = &cmdParam->sVerifyPin.EncryptedPIN1;
		}
		ret = GetArgumentByteValue(command, &g_verify_pin[3], &cmdParam->sVerifyPin.keyReferenceID); 
		
		if (ret == eValueNotFound)
		{
			SockLog(eLOG_INFO, "Error: VerifyPin operation wrong/missing --key_ref_id (-i) parameter\n");
			cmd = eUNKNOWN;
			break;
		}
		else if (ret != eFlagNotFound)
		{
			cmdParam->sVerifyPin.verifyPin.pKeyReferenceID = &cmdParam->sVerifyPin.keyReferenceID;
		}

		ret = GetArgumentIntValue(command, &g_verify_pin[4], &cmdParam->sVerifyPin.indicationToken); 
		if ( ret == eValueNotFound)
		{
			SockLog(eLOG_INFO, "Error: VerifyPin operation wrong/missing --indication_token (-j) parameter\n");
			cmd = eUNKNOWN;
			break;
		}
		else if (ret != eFlagNotFound)
		{
			cmdParam->sVerifyPin.verifyPin.pIndicationToken = &cmdParam->sVerifyPin.indicationToken;
		}
	}
	break;
	case eSET_PIN_PROTECTION:
		{
            memset(&cmdParam->sPinProtection.pinProtection, 0, sizeof(pack_uim_SetPinProtection_t));
			const char *pSessionInfo = NULL;
			const char *pPinId = NULL;
			char szSessionInfo[50] = {0};
			char szPinId[50] = {0};

			if (GetArgumentStrValue(command, &g_set_pin_protection[0], &pSessionInfo) != eFound ||
				GetArgumentStrValue(command, &g_set_pin_protection[1], &pPinId) != eFound)
			{
				cmd = eUNKNOWN;
				break;
			}
			StrCpy(szSessionInfo, pSessionInfo);
			StrCpy(szPinId, pPinId);
			GetUimSessionInformation(szSessionInfo, &cmdParam->sPinProtection.pinProtection.sessionInfo);
			if (false == GetUimProtectionPinInfo(szPinId, &cmdParam->sPinProtection.pinProtection))
			{
				SockLog(eLOG_INFO, "Error: SetPinProtection operation wrong --pin_id (-f) parameter\n");
				cmd = eUNKNOWN;
				break;
			}
			ret = GetArgumentByteValue(command, &g_set_pin_protection[2], &cmdParam->sPinProtection.keyReferenceID);
			if (ret == eValueNotFound)
			{
				SockLog(eLOG_INFO, "Error: SetPinProtection operation wrong/missing --key_ref_id (-i) parameter\n");
				cmd = eUNKNOWN;
				break;
			}
			else if (ret != eFlagNotFound)
			{
				cmdParam->sVerifyPin.verifyPin.pKeyReferenceID = &cmdParam->sPinProtection.keyReferenceID;
			}

			ret = GetArgumentIntValue(command, &g_set_pin_protection[3], &cmdParam->sPinProtection.indicationToken); 
			if ( ret == eValueNotFound)
			{
				SockLog(eLOG_INFO, "Error: SetPinProtection operation wrong/missing --indication_token (-j) parameter\n");
				cmd = eUNKNOWN;
				break;
			}
			else if (ret != eFlagNotFound)
			{
				cmdParam->sVerifyPin.verifyPin.pIndicationToken = &cmdParam->sPinProtection.indicationToken;
			}
		}
	break;
	case eSET_UNBLOCK_PIN:
	{
		memset(&cmdParam->sUnblockPin.unblockPin, 0, sizeof(pack_uim_UnblockPin_t));
		const char *pSessionInfo = NULL;
		const char *pUnblockPIN1 = NULL;
		char szSessionInfo[50] = {0};
		char szUnblockPIN1[50] = {0};

		if (GetArgumentStrValue(command, &g_set_unblock_pin[0], &pSessionInfo) != eFound ||
			GetArgumentStrValue(command, &g_set_unblock_pin[1], &pUnblockPIN1) != eFound)
		{
			cmd = eUNKNOWN;
			break;
		}
		StrCpy(szSessionInfo, pSessionInfo);
		StrCpy(szUnblockPIN1, pUnblockPIN1);
		GetUimSessionInformation(szSessionInfo, &cmdParam->sUnblockPin.unblockPin.sessionInfo);

		if (GetUimUnblockPinInfo(szUnblockPIN1, &cmdParam->sUnblockPin.unblockPin) == false)
		{
			SockLog(eLOG_INFO, "Error: UnblockPin operation invalid --unblock_pin (-k) parameter\n");
			cmd = eUNKNOWN;
			break;
		}
		ret = GetArgumentByteValue(command, &g_set_unblock_pin[2], &cmdParam->sUnblockPin.keyReferenceID);             
		if (ret == eValueNotFound)
		{
			SockLog(eLOG_INFO, "Error: UnblockPin operation wrong/missing --key_ref_id (-i) parameter\n");
			cmd = eUNKNOWN;
			break;
		}
		else if (ret != eFlagNotFound)
		{
			cmdParam->sUnblockPin.unblockPin.pKeyReferenceID = &cmdParam->sUnblockPin.keyReferenceID;
		}

		ret = GetArgumentIntValue(command, &g_set_unblock_pin[3], &cmdParam->sUnblockPin.indicationToken); 
		if (ret == eValueNotFound)
		{
			SockLog(eLOG_INFO, "Error: UnblockPin operation wrong/missing --indication_token (-j) parameter\n");
			cmd = eUNKNOWN;
			break;
		}
		else if (ret != eFlagNotFound)
		{
			cmdParam->sUnblockPin.unblockPin.pIndicationToken = &cmdParam->sUnblockPin.indicationToken;
		}
	}
	break;
	case eSET_POWER_DOWN:
	case eSET_POWER_UP:
	case eSET_RESET:
	break;
	case eSET_REFRESH_REGISTER:
	{
		memset(&cmdParam->refreshRegister, 0, sizeof(pack_uim_SLQSUIMRefreshRegister_t));
		const char *pSI = NULL;
		const char* pRR = NULL;

		if (GetArgumentStrValue(command, &g_set_referesh_register[0], &pSI) != eFound ||
			GetArgumentStrValue(command, &g_set_referesh_register[1], &pRR) != eFound ||
			!GetUimRefreshRegister(pRR, &cmdParam->refreshRegister.regRefresh))
		{
			printf("Error: RefreshRegister missing parameter(s)\n");
			cmd = eUNKNOWN;
			break;
		}
		GetUimSessionInformation(pSI, &cmdParam->refreshRegister.sessionInfo);
	}
	break;
	case eGET_REFRESH_LAST_EVENT:
		memset(&cmdParam->refreshGetLastEvent, 0, sizeof(pack_uim_SLQSUIMRefreshGetLastEvent_t));
		const char *pSessionInfo = NULL;
		char szSessionInfo[50] = {0};

		if (GetArgumentStrValue(command, &g_set_refresh_get_laset_event[0], &pSessionInfo) != eFound)
		{
			cmd = eUNKNOWN;
			break;
		}
		StrCpy(szSessionInfo, pSessionInfo);
		GetUimSessionInformation(szSessionInfo, &cmdParam->refreshGetLastEvent.sessionInfo);
	break;
	case eGET_FILE_ATTRIBUTES:
	{
		memset (&cmdParam->sFileAttributes.getFileAttributes, 0, sizeof(pack_uim_SLQSUIMGetFileAttributes_t));
		const char *pSessionInfo = NULL;
		char szSessionInfo[50] = {0};
		const char *pFileInfo = NULL;
		char szFileInfo[50] = {0};

		if (GetArgumentStrValue(command, &g_get_file_attributes[0], &pSessionInfo) != eFound)
		{
			cmd = eUNKNOWN;
			break;
		}
		StrCpy(szSessionInfo, pSessionInfo);
		GetUimSessionInformation(szSessionInfo, &cmdParam->sFileAttributes.getFileAttributes.sessionInfo);

		if (GetArgumentStrValue(command, &g_get_file_attributes[1], &pFileInfo) != eFound)
		{
			cmd = eUNKNOWN;
			break;
		}
		StrCpy(szFileInfo, pFileInfo);
		GetUimFileInfo (szFileInfo, false, &cmdParam->sFileAttributes.getFileAttributes);
		
		ret = GetArgumentIntValue(command, &g_get_file_attributes[2], &cmdParam->sFileAttributes.indicationToken);
		if (ret == eValueNotFound)
		{
			SockLog(eLOG_INFO, "Error: GetFileAttributes operation missing --indication_token (-j) value\n");
			cmd = eUNKNOWN;
			break;
		}
		else if (ret != eFlagNotFound)
		{
			cmdParam->sFileAttributes.getFileAttributes.pIndicationToken = &cmdParam->sFileAttributes.indicationToken;
		}
		
		ret = GetArgumentByteValue(command, &g_get_file_attributes[3], &cmdParam->sFileAttributes.securityAttributes);
		if (ret == eValueNotFound)
		{
			SockLog(eLOG_INFO, "Error: GetFileAttributes operation missing --security_attributes (-x) value\n");
			cmd = eUNKNOWN;
			break;
		}
		else if (ret != eFlagNotFound)
		{
			cmdParam->sFileAttributes.getFileAttributes.pUICCSecurityAttributes = &cmdParam->sFileAttributes.securityAttributes;
		}
	}
	break;
	case eGET_DEPERSONALIZATION:
	{
		memset (&cmdParam->sDepersonalization.depersonalization, 0, sizeof(pack_uim_SLQSUIMDepersonalization_t));
		const char *pDepersonalization = NULL;
		char szDepersonalization[50] = {0};

		if (GetArgumentStrValue(command, &g_depersonalization[0], &pDepersonalization) != eFound)
		{
			cmd = eUNKNOWN;
			break;
		}
		StrCpy(szDepersonalization, pDepersonalization);
		GetDepersonalizationParams(szDepersonalization, &cmdParam->sDepersonalization.depersonalization);

		ret = GetArgumentByteValue(command, &g_depersonalization[1], &cmdParam->sDepersonalization.slot);
		if (ret == eValueNotFound)
		{
			SockLog(eLOG_INFO, "Error: Depersonalization operation missing --slot (-p) value\n");
			cmd = eUNKNOWN;
			break;
		}
		else if (ret != eFlagNotFound)
		{
			cmdParam->sDepersonalization.depersonalization.pSlot = &cmdParam->sDepersonalization.slot;
		}
	}
	break;
	case eGET_AUTHENTICATE:
	{
        memset(&cmdParam->sAuthenticate.authenticateData.sessionInfo, 0, sizeof(uim_sessionInformation));
        memset(&cmdParam->sAuthenticate.authenticateData.authData, 0, sizeof(uim_authenticationData));
		const char *pSessionInfo = NULL;
		const char *pAthenticateData = NULL;
		char szSessionInfo[50] = {0};
		char szAuthenticatData[1024] = {0};

		if (GetArgumentStrValue(command, &g_authenticate[0], &pSessionInfo) != eFound ||
			GetArgumentStrValue(command, &g_authenticate[1], &pAthenticateData) != eFound)
		{
			cmd = eUNKNOWN;
			break;
		}
		StrCpy(szSessionInfo, pSessionInfo);
		StrCpy(szAuthenticatData, pAthenticateData);
        GetUimSessionInformation(szSessionInfo, &cmdParam->sAuthenticate.authenticateData.sessionInfo);
		if (false == GetUimAuthenticateData(szAuthenticatData, &cmdParam->sAuthenticate.authenticateData.authData))
		{
			SockLog(eLOG_INFO, "Error: Authenticate operation wrong -- (-) parameter\n");
			cmd = eUNKNOWN;
			break;
		}

		ret = GetArgumentIntValue(command, &g_authenticate[2], &cmdParam->sAuthenticate.indicationToken); 
		if ( ret == eValueNotFound)
		{
			SockLog(eLOG_INFO, "Error: Authenticate operation wrong/missing --indication_token (-j) parameter\n");
			cmd = eUNKNOWN;
			break;
		}
		else if (ret != eFlagNotFound)
		{
			cmdParam->sAuthenticate.authenticateData.pIndicationToken = &cmdParam->sAuthenticate.indicationToken;
		}
	}
	break;
	case eGET_CONFIGURATION:
	{
		cmdParam->sUIMGetConfiguration.getConfiguration.pConfigurationMask = NULL;
		const char *pMasks = NULL;
		char szMasks[50] = {0};

		ret = GetArgumentStrValue(command, &g_get_configuration[0], &pMasks); 
		if (ret == eValueNotFound)
		{
			SockLog(eLOG_INFO, "Error: GetCofiguration operation missing --event_mask (-u) value\n");
			cmd = eUNKNOWN;
		}
		else if (ret != eFlagNotFound)
		{
			StrCpy(szMasks, pMasks);
			GetUimMasks(szMasks, &cmdParam->sUIMGetConfiguration.configurationMask);
			cmdParam->sUIMGetConfiguration.getConfiguration.pConfigurationMask = &cmdParam->sUIMGetConfiguration.configurationMask;
		}			
	}
	break;
	case eSET_CHANGE_PIN:
		{
			memset(&cmdParam->sChangePinInfo.changePinInfo, 0, sizeof(pack_uim_ChangePin_t));
			const char *pSessionInfo = NULL;
			const char *pPinInfo = NULL;
			char szSessionInfo[50] = {0};
			char szPinInfo[50] = {0};

			if (GetArgumentStrValue(command, &g_set_change_pin[0], &pSessionInfo) != eFound ||
				GetArgumentStrValue(command, &g_set_change_pin[1], &pPinInfo) != eFound)
			{
				SockLog(eLOG_INFO, "Error: ChangePin operation missin parameter(s)\n");
				cmd = eUNKNOWN;
				break;
			}
			StrCpy(szSessionInfo, pSessionInfo);
			StrCpy(szPinInfo, pPinInfo);
			GetUimSessionInformation(szSessionInfo, &cmdParam->sChangePinInfo.changePinInfo.sessionInfo);

			if (GetUimChangePin(szPinInfo, &cmdParam->sChangePinInfo.changePinInfo) == false)
			{
				SockLog(eLOG_INFO, "Error: ChangePin operation invalid --change_pin_info (-v) parameter\n");
				cmd = eUNKNOWN;
				break;
			}

			ret = GetArgumentByteValue(command, &g_set_change_pin[2], &cmdParam->sChangePinInfo.keyReferenceID);
			if (ret == eValueNotFound)
			{
				SockLog(eLOG_INFO, "Error: ChangePin operation wrong/missing --key_ref_id (-i) parameter\n");
				cmd = eUNKNOWN;
				break;
			}
			else if (ret != eFlagNotFound)
			{
				cmdParam->sChangePinInfo.changePinInfo.pKeyReferenceID = &cmdParam->sChangePinInfo.keyReferenceID;
			}

			ret = GetArgumentIntValue(command, &g_set_change_pin[3], &cmdParam->sChangePinInfo.indicationToken);
			if (ret == eValueNotFound)
			{
				SockLog(eLOG_INFO, "Error: ChangePin operation wrong/missing --indication_token (-j) parameter\n");
				cmd = eUNKNOWN;
				break;
			}
			else if (ret != eFlagNotFound)
			{
				cmdParam->sChangePinInfo.changePinInfo.pIndicationToken = &cmdParam->sChangePinInfo.indicationToken;
			}
		}
	break;
	case eGET_READ_TRANSPARENT:
	break;
	case eUNKNOWN:
		SockLog(eLOG_INFO, "Error: invalid command\n");
	default:
		break;
	}

    UnlockSocket();

	return cmd;
}

void GetUimSessionInformation(const char *pCharSI, uim_sessionInformation *pSessionInfo)
{
	memset(pSessionInfo, 0, sizeof(uim_sessionInformation));
    pSessionInfo->sessionType = 0xFF;
    char *pPos = strchr(pCharSI, ' ');
    char szCharSI[30] = {0};

    if (pPos)
	{
        StrNCpy(szCharSI, pCharSI, pPos-pCharSI);
	}
    else
	{
        StrCpy(szCharSI, pCharSI);
	}

	//Get the session type
	pPos = strchr(szCharSI, ',');
	if (pPos == NULL)
	{
		pSessionInfo->sessionType = atoi(szCharSI);
		return; 
	}
	char szSessionType[10] = {0};
	StrNCpy(szSessionType, szCharSI, pPos - szCharSI);
	pSessionInfo->sessionType = atoi(szSessionType);

	++pPos;
	size_t idx = 0;
	size_t cnt = strlen(pPos);

	while (cnt > 0)
    {
		pSessionInfo->aid[idx] = pPos[idx] - '0';
		pSessionInfo->aidLength += 1;
		--cnt;
		++idx;
    }                
}

bool GetUimRefreshRegister(const char* pCharRR, uim_registerRefresh* pRegRefresh)
{
	pRegRefresh->registerFlag = atoi(pCharRR);
	++pCharRR;
	if (*pCharRR != ',')
		return false;

	++pCharRR;
	pRegRefresh->voteForInit = atoi(pCharRR);
	++pCharRR;
	if (*pCharRR != ',')
		return false;

	++pCharRR;
	pRegRefresh->numFiles = 1; //for this test only 1 data set is used
	pRegRefresh->arrfileInfo[0].fileID = atoi(pCharRR);
	++pCharRR;
	if (*pCharRR != ',')
		return false;

	++pCharRR;

	pRegRefresh->arrfileInfo[0].pathLen = 1;  //for this test only 1 path is used
	pRegRefresh->arrfileInfo[0].path[0] = strtol(pCharRR, NULL, 16);

	return true;
}

bool GetUimVerifyPinInfo(char *pCharPIN, pack_uim_VerifyPin_t *pVerifyPin)
{
    pVerifyPin->verifyPIN.pinID = atoi(pCharPIN);
    ++pCharPIN;
    if (*pCharPIN != ',')
    {
        return false;
    }
    ++pCharPIN;

    char *pPos2 =  NULL;
    pPos2 =  strchr(pCharPIN, ' ');
    char szPin[20] = {0};
    uint32_t idx = 0;
    if (pPos2)
        StrNCpy(szPin, pCharPIN, pPos2-pCharPIN);
    else
        StrCpy(szPin, pCharPIN);
    
    pVerifyPin->verifyPIN.pinLen = 0;
    for (idx = 0; idx < strlen(szPin); ++idx)
    {
        pVerifyPin->verifyPIN.pinVal[idx] = szPin[idx];
        ++pVerifyPin->verifyPIN.pinLen;
    }
    return true;
}

void GetUimEncryptPin1Info(char *pCharEPV, uim_encryptedPIN1 *pEncryptedPIN1)
{
    char *pPos2 =  NULL;
    pPos2 =  strchr(pCharEPV, ' ');
    pEncryptedPIN1->pin1Len = 0;
    char szPin[20] = {0};

    if (pPos2)
        StrNCpy(szPin, pCharEPV, pPos2-pCharEPV);
    else
        StrCpy(szPin, pCharEPV);
    
    for (size_t idx = 0; idx < strlen(szPin); ++idx)
    {
        pEncryptedPIN1->pin1Val[idx] = szPin[idx];
        ++pEncryptedPIN1->pin1Len;
    }
}

bool GetUimProtectionPinInfo(char *pCharPIN, pack_uim_SetPinProtection_t  *pSetPinProtection)
{
    pSetPinProtection->pinProtection.pinID = atoi(pCharPIN);
    ++pCharPIN;
    if (*pCharPIN != ',')
    {
        return false;
    }
    ++pCharPIN;
    pSetPinProtection->pinProtection.pinOperation = atoi(pCharPIN);
    pCharPIN += 2;

    char *pPos2 =  NULL;
    pPos2 =  strchr(pCharPIN, ' ');
    char szPin[20] = {0};
    uint32_t idx = 0;
    if (pPos2)
        StrNCpy(szPin, pCharPIN, pPos2-pCharPIN);
    else
        StrCpy(szPin, pCharPIN);
    
    for (idx = 0; idx < strlen(szPin); ++idx)
    {
        pSetPinProtection->pinProtection.pinValue[idx] = szPin[idx];
        ++pSetPinProtection->pinProtection.pinLength;
    }
    return true;
}

bool GetUimUnblockPinInfo(char *pCharPIN, pack_uim_UnblockPin_t *pUnblockPin)
{
    bool result = false;
    char szPin[20] = {0};
    uint32_t idx = 0;
    char *pPos2 =  NULL;

    while (true)
    { 
        pUnblockPin->pinProtection.pinID = atoi(pCharPIN);
        ++pCharPIN;
        if (*pCharPIN != ',')
        {
            break;
        }
        ++pCharPIN;
        pPos2 =  strchr(pCharPIN, ',');
        if (!pPos2)
        {
            break;
        }                    
        StrNCpy(szPin, pCharPIN, pPos2-pCharPIN);
        pUnblockPin->pinProtection.pukLen = strlen(szPin);
        for (idx = 0; idx < pUnblockPin->pinProtection.pukLen; ++idx)
        {
            pUnblockPin->pinProtection.pukVal[idx] = szPin[idx];
        }

        pCharPIN = pPos2 + 1;

        pPos2 =  strchr(pCharPIN, ' ');
        if (pPos2)
            StrNCpy(szPin, pCharPIN, pPos2-pCharPIN);
        else
            StrCpy(szPin, pCharPIN);

        pUnblockPin->pinProtection.newPINLen = 0;

        for (idx = 0; idx < strlen(szPin); ++idx)
        {
            pUnblockPin->pinProtection.newPINVal[idx] = szPin[idx];
            ++pUnblockPin->pinProtection.newPINLen;
        }
        result = true;
        break;
    }

    return result;
}

void GetUimFileInfo(char *pCharFI, bool bSpace, pack_uim_SLQSUIMGetFileAttributes_t *pFileAttributes)
{
    char szBuffer[100] = {0};
    uint32_t fileID = 0;
    char *pPos2 =  NULL;

    pPos2 = strchr(pCharFI, ',');
    if (!pPos2 && bSpace)
    {
        pPos2 = strchr(pCharFI, ' ');
    }

    if (pPos2)
        StrNCpy(szBuffer, pCharFI, pPos2-pCharFI);
    else
        StrCpy(szBuffer, pCharFI);

    sscanf( pCharFI, "%x" , &fileID);
    pFileAttributes->fileIndex.fileID = (uint16_t)fileID;

    if (pPos2)
    {
        pCharFI = pPos2 + 1;
        pPos2 =  strchr(pCharFI, ' ');
        if (pPos2)
            StrNCpy(szBuffer, pCharFI, pPos2-pCharFI);
        else
            StrCpy(szBuffer, pCharFI);
        
        char *pFilePath = szBuffer; 
        int filePathLen = strlen(szBuffer);

        if (filePathLen > 0)
        {
            uint32_t pathValue = 0;
            char szPath[20] = {0};
            char *pPos1 = pFilePath;
            char *pPos2 = 0;
            int idx = 0;
            do
            {
                memset(szPath, 0, sizeof(szPath));

                pPos2 = strchr(pPos1, ',');
                if (pPos2 == NULL)
                {
                    sscanf( pPos1, "%x" , &pathValue);
                    pFileAttributes->fileIndex.path[idx] = (uint16_t)pathValue;
                    ++idx;
                    break;
                }
                StrNCpy(szPath, pPos1, pPos2 - pPos1);
                sscanf( szPath, "%x", &pathValue);
                pFileAttributes->fileIndex.path[idx] = (uint16_t)pathValue;
                pPos1 = pPos2 + 1;
                ++idx;

            }while (pPos1 < (pFilePath + filePathLen - 1));

            pFileAttributes->fileIndex.pathLen = idx*2;
        }
    }
}

void GetUimMasks(char *pszMask, uint32_t *pMasks)
{   
    *pMasks = 0;
    if (strlen(pszMask) > 0)
    {
        uint64_t mask = 0x00;
        char szMask[20] = {0};
        char *pPos1 = pszMask;
        char *pPos2 = 0;
        while (pPos1 < (pszMask + strlen(pszMask)))
        {
            pPos2 = strchr(pPos1, '|');
            if (pPos2 == NULL)
            {
                sscanf( pPos1, "%"SCNx64 , &mask);
                *pMasks |= mask; 
                break;
            }
            StrNCpy(szMask, pPos1, pPos2 - pPos1);
            sscanf( szMask, "%"SCNx64, &mask);
            *pMasks |= mask; 
            pPos1 = pPos2 + 1;
        }                
    }
}

bool GetUimChangePin(char *pCharPIN, pack_uim_ChangePin_t *pChangePin)
{
    char *pPos2 =  NULL;

    pChangePin->changePIN.pinID = atoi(pCharPIN);
    ++pCharPIN;
    if (*pCharPIN != ',')
    {
        return false;
    }
    ++pCharPIN;
    pPos2 =  strchr(pCharPIN, ',');
    if (!pPos2)
    {
        return false;
    }
    char szPin[20] = {0};
    uint32_t idx = 0;
    StrNCpy(szPin, pCharPIN, pPos2-pCharPIN);
        
    for (idx = 0; idx < strlen(szPin); ++idx)
        pChangePin->changePIN.oldPINVal[idx] = szPin[idx];
    pChangePin->changePIN.oldPINLen = idx;
    pCharPIN = pPos2 + 1;

    pPos2 =  strchr(pCharPIN, ' ');
	if (pPos2 == NULL)
	{
    	StrCpy(szPin, pCharPIN);
	}
	else
	{
    	StrNCpy(szPin, pCharPIN, pPos2-pCharPIN);
	}
    
    pChangePin->changePIN.pinLen = 0;
    for (idx = 0; idx < strlen(szPin); ++idx)
    {
        pChangePin->changePIN.pinVal[idx] = szPin[idx];
        ++pChangePin->changePIN.pinLen;
    }
    return true;
}

bool GetUimAuthenticateData(char *pCharPIN, uim_authenticationData *pAuthData)
{
    pAuthData->context = atoi(pCharPIN);
    ++pCharPIN;
	if (pAuthData->context > 17)
		return false;
	if (pAuthData->context > 9)
		++pCharPIN;

    if (*pCharPIN != ',')
    {
        return false;
    }
    ++pCharPIN;

    char *pPos2 =  NULL;
    pPos2 =  strchr(pCharPIN, ' ');
    char szAuthenData[20] = {0};
    uint32_t idx = 0;
    if (pPos2)
        StrNCpy(szAuthenData, pCharPIN, pPos2-pCharPIN);
    else
        StrCpy(szAuthenData, pCharPIN);
    
    pAuthData->dataLen = 0;
    for (idx = 0; idx < strlen(szAuthenData); ++idx)
    {
        pAuthData->data[idx] = szAuthenData[idx];
        ++pAuthData->dataLen;
    }
    return true;
}

bool GetDepersonalizationParams(char *pCharDepersonalization, pack_uim_SLQSUIMDepersonalization_t *pDepersonalization)
{
    pDepersonalization->feature = atoi(pCharDepersonalization);
    ++pCharDepersonalization;
	if (pDepersonalization->feature > 15)
		return false;
	if (pDepersonalization->feature > 9)
		++pCharDepersonalization;

    if (*pCharDepersonalization != ',')
    {
        return false;
    }
    ++pCharDepersonalization;

    pDepersonalization->operation = atoi(pCharDepersonalization);
    ++pCharDepersonalization;
	if (pDepersonalization->operation > 1)
		return false;

    if (*pCharDepersonalization != ',')
    {
        return false;
    }
    ++pCharDepersonalization;

	char *pPos2 =  strchr(pCharDepersonalization, ' ');
    char szCharDepersonalization[100] = {0};

    if (pPos2)
        StrNCpy(szCharDepersonalization, pCharDepersonalization, pPos2-pCharDepersonalization);
    else
        StrCpy(szCharDepersonalization, pCharDepersonalization);
    
    pDepersonalization->ckLen = strlen(szCharDepersonalization);
    for (uint8_t idx = 0; idx < pDepersonalization->ckLen; ++idx)
    {
        pDepersonalization->ckVal[idx] = szCharDepersonalization[idx];
    }
	return true;
}
