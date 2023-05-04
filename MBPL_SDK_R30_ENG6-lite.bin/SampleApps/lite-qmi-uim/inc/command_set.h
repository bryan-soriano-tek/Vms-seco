/*************
 *
 * Filename:    command_set.h
 *
 * Purpose:     Contains function for handling user input functionalities for UIM
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
#include "uim.h"

#include "socket_server.h"
#include "user_input.h"

void GetUimSessionInformation(const char *pCharSI, uim_sessionInformation *pSessionInfo);
bool GetUimRefreshRegister(const char* pCharRR, uim_registerRefresh* pRegRefresh);
bool GetUimVerifyPinInfo(char *pCharPIN, pack_uim_VerifyPin_t *pVerifyPin);
void GetUimEncryptPin1Info(char *pCharEPV, uim_encryptedPIN1 *pEncryptedPIN1);
bool GetUimProtectionPinInfo(char *pCharPIN, pack_uim_SetPinProtection_t  *pSetPinProtection);
bool GetUimUnblockPinInfo(char *pCharPIN, pack_uim_UnblockPin_t *pUnblockPin);
void GetUimFileInfo(char *pCharFI, bool bSpace, pack_uim_SLQSUIMGetFileAttributes_t *pFileAttributes);
void GetUimMasks(char *pszMask, uint32_t *pMasks);
bool GetUimChangePin(char *pszChangePin, pack_uim_ChangePin_t *pChangePin);
bool GetUimAuthenticateData(char *pCharPIN, uim_authenticationData *pAuthData);
bool GetDepersonalizationParams(char *pCharDepersonalization, pack_uim_SLQSUIMDepersonalization_t *pDepersonalization);

/* User options enumeration for UIM */
enum eUserOptions {
	eEXIT = -1,
	eUNKNOWN = 0,
	eREG_GET_SLOT_STATUS = 1,
	eGET_CARD_STATUS,
	eGET_ICCID,
	eSET_EVENT_REGISTER,
	eSET_SWITCH_SLOT,
	eSET_VERIFY_PIN,
	eSET_PIN_PROTECTION,
	eSET_UNBLOCK_PIN,
	eSET_POWER_DOWN,
	eSET_POWER_UP,
	eSET_RESET,
	eSET_REFRESH_REGISTER,
	eGET_REFRESH_LAST_EVENT,
	eGET_FILE_ATTRIBUTES,
	eGET_DEPERSONALIZATION,
	eGET_AUTHENTICATE,
	eGET_CONFIGURATION,
	eSET_CHANGE_PIN,
	eGET_READ_TRANSPARENT,
	eHELP,
};
	
typedef struct
{
	union
	{
		pack_uim_SLQSUIMEventRegister_t eventRegister;
		pack_uim_SLQSUIMSwitchSlot_t switchSlotIn;
		
		struct VerifyPin
		{
			uim_encryptedPIN1    EncryptedPIN1;
			uint32_t indicationToken;
			uint8_t keyReferenceID;
			pack_uim_VerifyPin_t verifyPin;
		} sVerifyPin;
		
		struct PinProtection
		{
			uint32_t indicationToken;
			uint8_t keyReferenceID;
			pack_uim_SetPinProtection_t pinProtection;
		}sPinProtection;

		struct UnblockPin
		{
			uint32_t indicationToken;
			uint8_t keyReferenceID;
			pack_uim_UnblockPin_t unblockPin;
		}sUnblockPin;

		pack_uim_SLQSUIMRefreshRegister_t refreshRegister;
		pack_uim_SLQSUIMRefreshGetLastEvent_t refreshGetLastEvent;

		struct FileAttributes
		{
			uint32_t  indicationToken;
			uint8_t   securityAttributes;
			pack_uim_SLQSUIMGetFileAttributes_t getFileAttributes;
		}sFileAttributes;

		struct UIMGetConfiguration
		{
			uint32_t configurationMask;
			pack_uim_SLQSUIMGetConfiguration_t getConfiguration;
		}sUIMGetConfiguration;
		
		struct ChangePinInfo
		{
			uint32_t indicationToken;
			uint8_t keyReferenceID;
			pack_uim_ChangePin_t changePinInfo;
		}sChangePinInfo;

		struct Authenticate
		{
			uint32_t indicationToken;
			pack_uim_SLQSUIMAuthenticate_t authenticateData;
		} sAuthenticate;

		struct Depersonalization
		{
			uint8_t slot;
			pack_uim_SLQSUIMDepersonalization_t depersonalization;
		} sDepersonalization;		 
	};
} socketUimCommandParam;

// Can be taken as-is to other apps
void PrintPrompt(void);

// Can be taken as-is to other apps
void PrintUimCmdListUsage();

// Specific to DSD type map
enum ARGUMENT_AVAIL GetTypeValue(const char* valueStr, uint8_t* pValue);

// Can be taken as-is to other apps, if needed
enum eUserOptions GetUimCommand(const char* command);

// Specific to UIM.  Need to implement accordling to each app
enum eUserOptions GetUimSocketCommand(const char* procname, socketUimCommandParam* cmdParam);

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif // __COMMAND_SET_H__
