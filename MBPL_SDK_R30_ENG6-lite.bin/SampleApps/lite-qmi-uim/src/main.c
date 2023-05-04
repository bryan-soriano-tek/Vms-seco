#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <syslog.h>
#include <stdlib.h>
#include <getopt.h>
#include <inttypes.h>
#include "common.h"
#include "ctl.h"
#include "uim.h"
#include "lite-qmi-uim.h"
#include <QmuxTransport.h>
#include <QmiService.h>
#include <CtlService.h>
#include <QmiSyncObject.h>

#include <locale.h>
#include <sys/time.h>
#include "msgid.h"

#include "dev_util.h"
#include "qmux_util.h"
#include "str_util.h"
#include "lite-qmi-demo.h"

#include "command_set.h"

extern void uim_indication_handler(uint16_t msgid, uint8_t *msg, uint32_t rlen);

extern void GetSlotsStatus(QmiService* pQmiService);
extern void GetCardStatus(QmiService* pQmiService);
extern void GetIccid(QmiService* pQmiService);
extern void EventRegister(QmiService* pQmiService, uint32_t mask);
extern void SwitchSlot(QmiService* pQmiService, pack_uim_SLQSUIMSwitchSlot_t *pSwitchSlot);
extern void VerifyPin(QmiService* pQmiService, pack_uim_VerifyPin_t *pVerifyPin);
extern void SetPinProtection(QmiService* pQmiService, pack_uim_SetPinProtection_t *pRetPinProtectionReq);
extern void UnblockPin(QmiService* pQmiService, pack_uim_UnblockPin_t *pUnblockPinReq);
extern void PowerDown(QmiService* pQmiService);
extern void PowerUp(QmiService* pQmiService);
extern void Reset(QmiService* pQmiService);
extern void RefreshRegister(QmiService* pQmiService, pack_uim_SLQSUIMRefreshRegister_t *pRefreshRegister);
extern void RefreshGetLastEvent(QmiService* pQmiService, pack_uim_SLQSUIMRefreshGetLastEvent_t *pRefreshGetLastEventReq);
extern void GetFileAttributes(QmiService* pQmiService, pack_uim_SLQSUIMGetFileAttributes_t *pGetFileAttributesReq);
extern void Depersonalization(QmiService* pQmiService, pack_uim_SLQSUIMDepersonalization_t *pDepersonalizationReq);
extern void Authenticate(QmiService* pQmiService, pack_uim_SLQSUIMAuthenticate_t *pAuthenticateData);
extern void GetConfiguration(QmiService* pQmiService, pack_uim_SLQSUIMGetConfiguration_t *pGetConfiguration);
extern void ChangePin(QmiService* pQmiService, pack_uim_ChangePin_t *pChangePin);
extern void ReadTransparent(QmiService* pQmiService);

static bool PrintInvalidArguments();
static void PrintUimEventsRegisterOption();
static void PrintUimSwitchSlotOption();
static void PrintUimVerifyPinOption();
static void PrintUimSetPinProtectionOption();
static void PrintUimUnblockPinOption();
static void PrintUimRefereshRegisterOption();
static void PrintUimRefereshGetLastEventOption();
static void PrintUimConfigurationMaskOption();
static void PrintUimChangePinOption();
static void PrintGetFileAttributesOptions();
static void PrintUimAuthenticateOptions();
static void PrintUimDepersonalizationOptions();

static CtlService s_CtlService;
static QmiService s_UimService;
static QmuxTransport s_Transport;

//////////////////////////////////////////////////////////
enum AppStateType g_AppState = AppUninitialized;

#define DEVICE_PATH_MAX 256
char g_DevicePath[DEVICE_PATH_MAX]={0};

bool g_PrintVersion = false;
int g_mode = QMUX_INTERFACE_UNKNOWN;
bool g_socketServer = false;

bool g_SkipGetClientIds = false;
bool g_SkipReleaseClientIds = false;
char g_ClientIdsPath[DEVICE_PATH_MAX]={0};

#define APPNAME "lite-qmi-uim"
#define VERSION "1.0.2210.0"

///////////////////////////////////////////////////
static void UimIndicationCallback(uint8_t* qmiPacket, uint16_t qmiPacketSize, void* pIndicationCallbackContext)
{
	(void)pIndicationCallbackContext;

	unpack_qmi_t rsp_ctx;
	printf (ANSI_COLOR_YELLOW);
	printf("<< receiving uim indication: %s\n", helper_get_resp_ctx(eUIM, qmiPacket, qmiPacketSize, &rsp_ctx));
	printf("msgid 0x%x, type:%x\n", rsp_ctx.msgid,rsp_ctx.type);
	printf (ANSI_COLOR_RESET);
	uim_indication_handler(rsp_ctx.msgid, qmiPacket,  qmiPacketSize);
}

static void ExecuteUimTestCase(enum eUserOptions operation, socketUimCommandParam *cmdParam)
{
    switch(operation)
    {
        case eREG_GET_SLOT_STATUS:
		    GetSlotsStatus(&s_UimService);
        break;
	    case eGET_CARD_STATUS:
		    GetCardStatus(&s_UimService);
        break;
        case eGET_ICCID:
            GetIccid(&s_UimService);
        break;
        case eSET_EVENT_REGISTER:
            EventRegister(&s_UimService, cmdParam->eventRegister.eventMask);
        break;
        case eSET_SWITCH_SLOT:
            SwitchSlot(&s_UimService, &cmdParam->switchSlotIn);
        break;
        case eSET_VERIFY_PIN:
            VerifyPin(&s_UimService, &cmdParam->sVerifyPin.verifyPin);
        break;
        case eSET_PIN_PROTECTION:
            SetPinProtection(&s_UimService, &cmdParam->sPinProtection.pinProtection);
        break;
        case eSET_UNBLOCK_PIN:
            UnblockPin(&s_UimService, &cmdParam->sUnblockPin.unblockPin);
        break;
        case eSET_POWER_DOWN:
            PowerDown(&s_UimService);
        break;
        case eSET_POWER_UP:
            PowerUp(&s_UimService);
        break;
        case eSET_RESET:
            Reset(&s_UimService);
        break;
        case eSET_REFRESH_REGISTER:
            RefreshRegister(&s_UimService, &cmdParam->refreshRegister);
        break;
        case eGET_REFRESH_LAST_EVENT:
            RefreshGetLastEvent(&s_UimService, &cmdParam->refreshGetLastEvent);
        break;
        case eGET_FILE_ATTRIBUTES:
            GetFileAttributes(&s_UimService, &cmdParam->sFileAttributes.getFileAttributes);
        break;
        case eGET_DEPERSONALIZATION:
            Depersonalization(&s_UimService, &cmdParam->sDepersonalization.depersonalization);
        break;
        case eGET_AUTHENTICATE:
            Authenticate(&s_UimService, &cmdParam->sAuthenticate.authenticateData);
        break;
        case eGET_CONFIGURATION:
            GetConfiguration(&s_UimService, &cmdParam->sUIMGetConfiguration.getConfiguration);
        break;
        case eSET_CHANGE_PIN:
            ChangePin(&s_UimService, &cmdParam->sChangePinInfo.changePinInfo);
        break;
        case eGET_READ_TRANSPARENT:
            ReadTransparent(&s_UimService);
        break;
		default:
			break;
    }
}

void ExecuteUimSocketTestCase(const char* socketName, socketUimCommandParam* cmdParam)
{
	if (OpenSocket(socketName) == 0)
		return;

	while (1)
	{
		int op = GetUimSocketCommand(APPNAME, cmdParam);
		if (op == eEXIT)
			break;

		ExecuteUimTestCase(op, cmdParam);
	}

	CloseSocket();
}

static void ExecuteUimTestCaseSelection(void)
{
	char str_return[MAX_USER_INPUT_SIZE];
	PrintPrompt();
	
	while (1)
	{
		fflush(stdin);
		memset (str_return,0,MAX_USER_INPUT_SIZE);

		fgets(str_return,MAX_USER_INPUT_SIZE,stdin);

		switch(g_AppState)
		{
			case AppCommandExecuted:
				g_AppState = AppRunning;
				PrintPrompt();
			break;
			default:
			if (!strcmp(str_return, "\n"))
			{
				g_AppState = AppRunning;
				PrintPrompt();
			}
			break;
		}

		size_t s = strlen(str_return);
		if (s > 0)
			str_return[s - 1] = 0;
		else
			str_return[0] = 0;

		if (!strcmp(str_return, "q"))
		{
			printf("quitting...\n");
			break;
		} 
        else if (!strcmp(str_return, "d"))
		{
			PrintPrompt();
		}
        else if(g_AppState == AppGetEventRegister)
        {
            uint32_t masks = 0x00;
            if (strlen(str_return) > 0)
            {
                GetUimMasks(str_return, &masks);
            }
            SockPrintf("Setting UIM events mask = 0x%04X\n", masks); 

            EventRegister(&s_UimService, masks);
            g_AppState = AppCommandExecuted;            
        }
        else if (g_AppState == AppSwitchSlot)
        {
            char *pChar = str_return;
            if (strlen(str_return) != 3 || *(pChar+1) != ',')
            {
                PrintInvalidArguments();
            }
            else
            {          
                uint8_t  logical_slot = 1;
                uint32_t physical_slot = 1;
                logical_slot = atoi( pChar );
                pChar += 2;
                physical_slot = atoi( pChar );
                pack_uim_SLQSUIMSwitchSlot_t switchSlotIn = {logical_slot, physical_slot};

                SwitchSlot(&s_UimService, &switchSlotIn);
                g_AppState = AppCommandExecuted;
            }
        }
        else if(g_AppState == AppVerifyPin)
        {
            char *pChar = str_return;
            char *pCharSI = strstr(pChar, "SI=");
            char *pCharPIN = strstr(pChar, "PIN=");
            char *pCharEPV = strstr(pChar, "EPV=");
            char *pCharPKI = strstr(pChar, "PKI=");
            char *pCharIT = strstr(pChar, "IT=");

            if (!pCharSI || !pCharPIN)
                PrintInvalidArguments();
            else
            {
                pack_uim_VerifyPin_t verifyPin;
                memset (&verifyPin, 0, sizeof(pack_uim_VerifyPin_t));
                pCharSI +=  3;
                GetUimSessionInformation(pCharSI, &verifyPin.sessionInfo);
                //PIN verify
                while (true)
                {
                    pCharPIN +=4;
                    if (false == GetUimVerifyPinInfo(pCharPIN, &verifyPin))
                    {
                        PrintInvalidArguments();
                        break;
                    }
                    verifyPin.pEncryptedPIN1 = NULL;
                    verifyPin.pKeyReferenceID = NULL;
                    verifyPin.pIndicationToken = NULL;

                    if (pCharEPV)
                    {
                        pCharEPV += 4;
                        uim_encryptedPIN1 encryptedPIN1;
                        GetUimEncryptPin1Info(pCharEPV, &encryptedPIN1);
                        verifyPin.pEncryptedPIN1 = &encryptedPIN1;
                    }

                    uint8_t keyReferenceID = 0;
                    uint32_t indicationToken = 0;
                    if (pCharPKI)
                    {

                        keyReferenceID = atoi(pCharPKI+4);
                        verifyPin.pKeyReferenceID = &keyReferenceID;
                    }

                    if (pCharIT)
                    {
                        indicationToken = atoi(pCharIT+3);
                        verifyPin.pIndicationToken = &indicationToken;
                    } 
                    VerifyPin(&s_UimService, &verifyPin);
                    break;
                }
            }
            g_AppState = AppCommandExecuted;            
        }
        else if (g_AppState == AppSetPinProtection)
        {
            char *pChar = str_return;
            char *pCharSI = strstr(pChar, "SI=");
            char *pCharPIN = strstr(pChar, "PIN=");
            char *pCharPKI = strstr(pChar, "PKI=");
            char *pCharIT = strstr(pChar, "IT=");

            if (!pCharSI || !pCharPIN)
                PrintInvalidArguments();
            else
            {
                pack_uim_SetPinProtection_t setPinProtectionReq;
                memset (&setPinProtectionReq, 0, sizeof(pack_uim_SetPinProtection_t));
                pCharSI += 3;
                GetUimSessionInformation(pCharSI, &setPinProtectionReq.sessionInfo);
                //Set PIN protection
                while (true)
                {
                    pCharPIN +=4;
                    if (false == GetUimProtectionPinInfo(pCharPIN, &setPinProtectionReq))
                    {
                        PrintInvalidArguments();
                        break;
                    }
                    setPinProtectionReq.pKeyReferenceID = NULL;
                    setPinProtectionReq.pIndicationToken = NULL;

                    uint8_t keyReferenceID = 0;
                    uint32_t indicationToken = 0;
                    if (pCharPKI)
                    {

                        keyReferenceID = atoi(pCharPKI+4);
                        setPinProtectionReq.pKeyReferenceID = &keyReferenceID;
                    }

                    if (pCharIT)
                    {
                        indicationToken = atoi(pCharIT+3);
                        setPinProtectionReq.pIndicationToken = &indicationToken;
                    } 
                    SetPinProtection(&s_UimService, &setPinProtectionReq);
                    break;
                }
            }
            g_AppState = AppCommandExecuted;            
        }
        else if(g_AppState == AppUnblockPin)
        {
            char *pChar = str_return;
            char *pCharSI = strstr(pChar, "SI=");
            char *pCharPIN = strstr(pChar, "PIN=");
            char *pCharPKI = strstr(pChar, "PKI=");
            char *pCharIT = strstr(pChar, "IT=");

            if (!pCharSI || !pCharPIN)
                PrintInvalidArguments();
            else
            {
                pack_uim_UnblockPin_t unblockPinReq;
                memset (&unblockPinReq, 0, sizeof(pack_uim_UnblockPin_t));
                pCharSI += 3;
                GetUimSessionInformation(pCharSI, &unblockPinReq.sessionInfo);

                pCharPIN +=4;
                if (GetUimUnblockPinInfo(pCharPIN, &unblockPinReq) == false)
                {
                    PrintInvalidArguments();
                }
                else
                {
                    unblockPinReq.pKeyReferenceID = NULL;
                    unblockPinReq.pIndicationToken = NULL;

                    uint8_t keyReferenceID = 0;
                    uint32_t indicationToken = 0;
                    if (pCharPKI)
                    {
                        keyReferenceID = atoi(pCharPKI+4);
                        unblockPinReq.pKeyReferenceID = &keyReferenceID;
                    }

                    if (pCharIT)
                    {
                        indicationToken = atoi(pCharIT+3);
                        unblockPinReq.pIndicationToken = &indicationToken;
                    } 
                    UnblockPin(&s_UimService, &unblockPinReq);
                }
            }
            g_AppState = AppCommandExecuted;            
        }
        else if(g_AppState == AppRefereshRegister)
        {
            char *pChar = str_return;
            char *pCharSI = strstr(pChar, "SI=");
            char *pCharRR = strstr(pChar, "RR=");
            if (!pCharSI || !pCharRR)
                PrintInvalidArguments();
            else
            {
                pack_uim_SLQSUIMRefreshRegister_t refreshRegister;
                memset (&refreshRegister, 0, sizeof(pack_uim_SLQSUIMRefreshRegister_t));
                pCharSI += 3;
                GetUimSessionInformation(pCharSI, &refreshRegister.sessionInfo);

                //Register Refresh
                pCharRR +=3;
                if (!GetUimRefreshRegister(pCharRR, &refreshRegister.regRefresh))
                    PrintInvalidArguments();
                else
                    RefreshRegister(&s_UimService, &refreshRegister);

                g_AppState = AppCommandExecuted;
            }
        }
        else if(g_AppState == AppRefereshGetLastEvent)
        {
            char *pChar = str_return;
            char *pCharSI = strstr(pChar, "SI=");
            if (!pCharSI)
                PrintInvalidArguments();
            else
            {
                pack_uim_SLQSUIMRefreshGetLastEvent_t refreshGetLastEvent;
                memset (&refreshGetLastEvent, 0, sizeof(pack_uim_SLQSUIMRefreshGetLastEvent_t));
                pCharSI += 3;
                GetUimSessionInformation(pCharSI, &refreshGetLastEvent.sessionInfo);

                RefreshGetLastEvent(&s_UimService, &refreshGetLastEvent);
            }
            g_AppState = AppCommandExecuted;
        }
        else if(g_AppState == AppGetFileAttributes)
        {
            char *pChar = str_return;
            char *pCharSI = strstr(pChar, "SI=");
            char *pCharFI = strstr(pChar, "FI=");
            char *pCharIT = strstr(pChar, "IT=");
            char *pCharSA = strstr(pChar, "SA=");

            if (!pCharSI || !pCharFI)
                PrintInvalidArguments();
            else
            {
                pack_uim_SLQSUIMGetFileAttributes_t getFileAttributesReq;
                memset (&getFileAttributesReq, 0, sizeof(pack_uim_SLQSUIMGetFileAttributes_t));
                pCharSI += 3;
                GetUimSessionInformation(pCharSI, &getFileAttributesReq.sessionInfo);

                while (true)
                {
                    //Check user input for FileIndex is not more than 100 characters
                    if (strlen(pCharFI) > 99)
                    {
                        PrintInvalidArguments();
                        break;
                    }
                    pCharFI +=3;
                    bool bSpace = pCharIT || pCharSA;
                    GetUimFileInfo(pCharFI, bSpace, &getFileAttributesReq);

                    uint32_t indication_token = 0;
                    uint8_t uicc_security_attributes = 0;
                    if (pCharIT)
                    {
                        indication_token = atoi(pCharIT+3);
                        getFileAttributesReq.pIndicationToken = &indication_token;
                    }

                    if (pCharSA)
                    {
                        uicc_security_attributes = atoi(pCharSA+3);
                        getFileAttributesReq.pUICCSecurityAttributes = &uicc_security_attributes;
                    } 
                    
                    GetFileAttributes(&s_UimService, &getFileAttributesReq);
                    break;
                }
            }
            g_AppState = AppCommandExecuted;
        }
        else if(g_AppState == AppGetConfigurationMask)
        {
            uint32_t masks = 0x00;
            if (strlen(str_return) > 0)
            {
                GetUimMasks(str_return, &masks);
            }
            SockPrintf("Setting UIM configuration mask = 0x%04X\n", masks);
            pack_uim_SLQSUIMGetConfiguration_t sGetConfiguration;
            sGetConfiguration.pConfigurationMask = masks > 0 ? &masks : NULL;          

            GetConfiguration(&s_UimService, &sGetConfiguration);
        }
        else if (g_AppState == AppAuthenticate)
        {
            char *pChar = str_return;
            char *pCharSI = strstr(pChar, "SI=");
            char *pCharCON = strstr(pChar, "CON=");
            char *pCharIT = strstr(pChar, "IT=");

            if (!pCharSI || !pCharCON)
                PrintInvalidArguments();
            else
            {
                pack_uim_SLQSUIMAuthenticate_t authenticateData;
                memset (&authenticateData, 0, sizeof(pack_uim_SLQSUIMAuthenticate_t));
                uint32_t indicationToken = 0;
                pCharSI += 3;
                GetUimSessionInformation(pCharSI, &authenticateData.sessionInfo);
                //Authenticate Data
                while (true)
                {
                    pCharCON +=4;
                    if (false == GetUimAuthenticateData(pCharCON, &authenticateData.authData))
                    {
                        PrintInvalidArguments();
                        break;
                    }
                    if (pCharIT)
                    {
                        indicationToken = atoi(pCharIT+3);
                        authenticateData.pIndicationToken = &indicationToken;
                    }
                    
                    Authenticate(&s_UimService, &authenticateData);
                    break;
                }
            }
            g_AppState = AppCommandExecuted;      
        }
        else if(g_AppState == AppDepersonalization)
        {
            //FE=13,OP=1,key=abcd SL=1
            char *pChar = str_return;
            char *pCharFE = strstr(pChar, "FE=");

            if (!pCharFE)
                PrintInvalidArguments();
            else
            {
                pack_uim_SLQSUIMDepersonalization_t sDepersonalization;
                memset(&sDepersonalization, 0, sizeof(pack_uim_SLQSUIMDepersonalization_t));
                pCharFE += 3;
                if (!GetDepersonalizationParams(pCharFE, &sDepersonalization))
                {
                    PrintInvalidArguments();
                }
                else
                {
                    char *pCharSL = strstr(pChar, "SL=");
                    uint8_t slot = 0;                     
                    if (pCharSL)
                    {
                        pCharSL += 3;
                        slot = atoi(pCharSL);
                        sDepersonalization.pSlot = &slot;
                    }
                    Depersonalization(&s_UimService, &sDepersonalization);
                }
            }
            g_AppState = AppCommandExecuted;
        }
        else if(g_AppState == AppChangePin)
        {
            char *pChar = str_return;
            char *pCharSI = strstr(pChar, "SI=");
            char *pCharPIN = strstr(pChar, "PIN=");
            char *pCharPKI = strstr(pChar, "PKI=");
            char *pCharIT = strstr(pChar, "IT=");

            if (!pCharSI || !pCharPIN)
                PrintInvalidArguments();
            else
            {
                pack_uim_ChangePin_t changePin;
                memset (&changePin, 0, sizeof(pack_uim_ChangePin_t));
                pCharSI += 3;
                GetUimSessionInformation(pCharSI, &changePin.sessionInfo);
                //PIN Change Refresh
                while (true)
                {
                    pCharPIN +=4;
                    if (false == GetUimChangePin(pCharPIN, &changePin))
                    {
                        PrintInvalidArguments();
                        break;
                    }
                    changePin.pKeyReferenceID = NULL;
                    changePin.pIndicationToken = NULL;

                    uint8_t keyReferenceID = 0;
                    uint32_t indicationToken = 0;
                    if (pCharPKI)
                    {
                        keyReferenceID = atoi(pCharPKI+4);
                        changePin.pKeyReferenceID = &keyReferenceID;
                    }

                    if (pCharIT)
                    {
                        indicationToken = atoi(pCharIT+3);
                        changePin.pIndicationToken = &indicationToken;
                    }
                    
                    ChangePin(&s_UimService, &changePin);
                    break;
                }
            }
            g_AppState = AppCommandExecuted;
        }
		else if (g_AppState == AppRunning)
        {
            if (!strcmp(str_return, "1") || !strcmp(str_return, "Get Slots Status"))
            {
                GetSlotsStatus(&s_UimService);
            } 
            else if (!strcmp(str_return, "2") || !strcmp(str_return, "Get Card Status"))
            {
                GetCardStatus(&s_UimService);
            } 
            else if (!strcmp(str_return, "3") || !strcmp(str_return, "Get ICCID"))
            {
                GetIccid(&s_UimService);
            } 
            else if (!strcmp(str_return, "4") || !strcmp(str_return, "Event Register"))
            {                
                PrintUimEventsRegisterOption();
            } 
            else if (!strcmp(str_return, "5") || !strcmp(str_return, "Switch Slot"))
            {
                PrintUimSwitchSlotOption();
            } 
            else if (!strcmp(str_return, "6") || !strcmp(str_return, "Verify PIN"))
            {
                PrintUimVerifyPinOption();                
            } 
            else if (!strcmp(str_return, "7") || !strcmp(str_return, "Set PIN Protection"))
            {
                PrintUimSetPinProtectionOption();
            } 
            else if (!strcmp(str_return, "8") || !strcmp(str_return, "Unblock PIN"))
            {
                PrintUimUnblockPinOption();
            } 
            else if (!strcmp(str_return, "9") || !strcmp(str_return, "Power Down"))
            {
                PowerDown(&s_UimService);
            } 
            else if (!strcmp(str_return, "10") || !strcmp(str_return, "Power Up"))
            {
                PowerUp(&s_UimService);
            } 
            else if (!strcmp(str_return, "11") || !strcmp(str_return, "Reset"))
            {
                Reset(&s_UimService);
            } 
            else if (!strcmp(str_return, "12") || !strcmp(str_return, "Refresh Register"))
            {
                PrintUimRefereshRegisterOption();
            } 
            else if (!strcmp(str_return, "13") || !strcmp(str_return, "Refresh Get Last Event"))
            {
                PrintUimRefereshGetLastEventOption();
            } 
            else if (!strcmp(str_return, "14") || !strcmp(str_return, "Get File Attributes"))
            {
                PrintGetFileAttributesOptions();
            } 
            else if (!strcmp(str_return, "15") || !strcmp(str_return, "Depersonalization"))
            {
                PrintUimDepersonalizationOptions();
            } 
            else if (!strcmp(str_return, "16") || !strcmp(str_return, "Authenticate"))
            {
                PrintUimAuthenticateOptions();
            } 
            else if (!strcmp(str_return, "17") || !strcmp(str_return, "Get Configuration"))
            {                
                PrintUimConfigurationMaskOption();
            } 
            else if (!strcmp(str_return, "18") || !strcmp(str_return, "Change PIN"))
            {
                PrintUimChangePinOption();
            } 
            else if (!strcmp(str_return, "19") || !strcmp(str_return, "Read Transparent"))
            {
                ReadTransparent(&s_UimService);
            } 
        }	
	}

	return;
}

void PrintUsageManual()
{
    SockPrintf( "\r\n" );
    SockPrintf( "App usage: \r\n\r\n" );
    SockPrintf( "  -d  --device \n" );
    SockPrintf( "        absolute path to qmux device\n\n" );
    SockPrintf( "  -m  --mbim \n" );
    SockPrintf( "        Device is an MBIM interface (defaults to direct QMUX interface)\n\n" );
	SockPrintf( "  -q  --qmi\n");
	SockPrintf( "        Use direct QMUX interface (QMI over PCIe, or RmNet over USB)\n\n");
	SockPrintf( "  -r  --router\n");
	SockPrintf( "        Use QMUX Router\n\n");
	SockPrintf( "  -s  --socket\n");
	SockPrintf( "        Run socket mode\n\n");
	SockPrintf( "  -h  --help  \n" );
    SockPrintf( "        This option prints the usage instructions.\n\n" );
    SockPrintf( "  -V  --version  \n" );
    SockPrintf( "        This option prints app version.\n\n" );
    SockPrintf( "  -G  --skipget  \n" );
    SockPrintf( "        Skip getting client IDs.\n\n" );
    SockPrintf( "  -R  --skiprelease  \n" );
    SockPrintf( "        Skip releasing client IDs.\n\n" );
    SockPrintf( "  -C  --clientidspath  \n" );
    SockPrintf( "        Path of file where client IDs may be \nsaved or retrieved when \n-G/-R options are used. \n" );
    SockPrintf( "        File format consists of lines, \none for each QMI service: QMI service,client ID.  \n" );
    SockPrintf( "        E.g. UIM,27\n" );
    SockPrintf( "             NAS,15\n" );
	SockPrintf( "  -o  --operation  \n");
	SockPrintf( "        Automatically perform the specifed action without user interaction.\n"); 
	SockPrintf( "        If the operation has required parameters, they must also be provided.\n");
	SockPrintf("        Operation-specific parameters will be ignored if the -o flag is not present, or if they are not associated with the specified operation.\n");
	SockPrintf( "        Supported operations: \n");
    
    PrintUimCmdListUsage();
}

const char * const s_ShortOptions = "VhmqrsGRd:o:C:a:b:w:e:f:g:i:j:k:n:t:u:v:z:y:l:p:";

const struct option s_LongOptions[] = {
    {"version",  no_argument, NULL, 'V'},
    {"help",   no_argument, NULL, 'h'},
    {"mbim",   no_argument, NULL, 'm'},
    {"qmi",    no_argument, NULL, 'q'},
	{"router", no_argument, NULL, 'r'},
	{"socket", no_argument, NULL, 's'},
	{"skipget", no_argument, NULL, 'G'},
	{"skiprelease", no_argument, NULL, 'R'},
    {"device", required_argument, NULL, 'd'},
    {"operation", required_argument, NULL, 'o'},
	{"clientidspath", required_argument, NULL, 'C'},
	{"event_mask", required_argument, NULL, 'a'},
	{"logical_slot", required_argument, NULL, 'b'},
	{"physical_slot", required_argument, NULL, 'w'},
	{"session_info", required_argument, NULL, 'e'},
	{"pin_id", required_argument, NULL, 'f'},
	{"encrypted_value", required_argument, NULL, 'g'},
	{"key_ref_id", required_argument, NULL, 'i'},
	{"indication_token", required_argument, NULL, 'j'},
	{"unblock_pin", required_argument, NULL, 'k'},
	{"referesh_registger", required_argument, NULL, 'n'},
	{"file_info", required_argument, NULL, 't'},
	{"event_mask", required_argument, NULL, 'u'},
	{"change_pin_info", required_argument, NULL, 'v'},
    {"security_attributes", required_argument, NULL, 'z'},
	{"authenticate_data", required_argument, NULL, 'y'},
	{"depersonalization", required_argument, NULL, 'l'},
	{"slot", required_argument, NULL, 'p'},
	{NULL,     0, NULL,  0 }       /* End of list */
};

static bool PrintInvalidArguments()
{
    SockPrintf("\n     Invalid arquments."
           "\n     Press<Enter> to go to previous menu.");
    fflush(stdout);
    return true;
}

static void PrintUimEventsRegisterOption()
{
    SockPrintf( "\nPlease select UIM Event Register Mask\n"\
                        "  Card status(0x00)\n"\
                        "  SAP connection(0x01)\n"\
                        "  Extended card status(0x04)\n"\
                        "  Close of provisioning sessions(0x08)\n"\
                        "  Physical slot status(0x10)\n"\
                        "  SIM busy status(0x20)\n"\
                        "  Reduced card status(0x40)\n"\
                        "  Recovery complete(0x80)\n"\
                        "  Supply voltage Vcc status(0x0100)\n"\
                        "  Card activation status(0x0200)\n"\
                        "  Remote SimLock configuration(0x0400)\n"\
                        "  SimLock temporary unlock status(0x0800)\n");

    SockPrintf( "  ex. 0x01|0x04|0x10\n\n");
    SockPrintf( "Events Mask: ");
    g_AppState = AppGetEventRegister;                
}

static void PrintUimSwitchSlotOption()
{
    SockPrintf( "\nPlease enter switch slot valures\n"\
                        "  Or Press<Enter> to go to previous menu:\n"
                        "  logical slot(Slot 1: 1, Slot 2: 2, Slot 3: 3, Slot 4: 4, Slot 5: 5)\n"\
                        "  physical slot(Slot 1: 1, Slot 2: 2, Slot 3: 3, Slot 4: 4, Slot 5: 5)\n");

    SockPrintf( "  ex. 1,3\n");

    g_AppState = AppSwitchSlot;                
}

static void PrintUimVerifyPinOption()
{
    SockPrintf( "\nPlease select verify PIN values\n"\
                        "  Or Press<Enter> to go to previous menu:\n"
                        "  Session Information(session type, app IDs): SI=type,id\n"\
                        "  Indication Token: IT=x\n"\
                        "  Verify PIN(PIN ID, PIN value): PIN=1|2|3|4,x..x\n"\
                        "  Encrypted Value of PIN1(optional): EPV=x..x\n"\
                        "  Key Ref ID(optional): PKI=1|2|3|4|5|6|7|8\n");

    SockPrintf( "  ex. SI=0,1 IT=x PIN=1,1234 EPV=x..x PKI=1\n\n");

    g_AppState = AppVerifyPin;                
}

static void PrintUimSetPinProtectionOption()
{
    SockPrintf( "\nPlease select Set PIN Protection values\n"\
                        "  Or Press<Enter> to go to previous menu:\n"
                        "  Session Information(session type, app IDs): SI=type,id\n"\
                        "  Indication Token: IT=x\n"\
                        "  Set PIN Protection(PIN ID, PIN Operation - Disable/Enable, PIN value): PIN=1|2|3|4,0|1,x..x\n"\
                        "  Key Ref ID(optional): PKI=1|2|3|4|5|6|7|8\n");

    SockPrintf( "  ex. SI=0,1 IT=x PIN=1,1,1234 PKI=1\n\n");

    g_AppState = AppSetPinProtection;                
}

static void PrintUimUnblockPinOption()
{
    SockPrintf( "\nPlease select Unblock PIN values\n"\
                        "  Or Press<Enter> to go to previous menu:\n"
                        "  Session Information(session type, app IDs): SI=type,id\n"\
                        "  Indication Token(optional): IT=x\n"\
                        "  Unblock PIN(PIN ID, PIN Unlock key value -ascii, new PIN value): PIN=1|2|3,x..x,y..y\n"\
                        "  Key Ref ID(optional): PKI=1|2|3|4|5|6|7|8\n");

    SockPrintf( "  ex. SI=0,1 IT=x PIN=1,a1b2c,1234 PKI=1\n\n");

    g_AppState = AppUnblockPin;
}

static void PrintUimRefereshRegisterOption()
{
    SockPrintf( "\nPlease select referesh register values\n"\
                        "  Or Press<Enter> to go to previous menu:\n"
                        "  Session Information(session type, app IDs): SI=type,id\n"\
                        "  Rgister Refresh(register flag,vote for init,file id,path value): RR=(0|1),(0|1),2,path\n");

    SockPrintf( "  ex. SI=0,1 RR=1,1,2,0x3f00\n\n");

    g_AppState = AppRefereshRegister;                
}

static void PrintGetFileAttributesOptions()
{
    SockPrintf( "\nPlease select Get File Attributes parameters\n"\
                        "  Or Press<Enter> to go to previous menu:\n"
                        "  Session Information(session type, app IDs): SI=type,id\n"\
                        "  File Info(File ID (3GPP 31.102 sec4.7), path): FI=ID,path\n"\
                        "  Indication Token(optional): IT=x\n"\
                        "  UICC Security Attributes(optional) (0: Skip security attributes, 1:return security attributes): SA=(0|1)\n");

    SockPrintf( "  ex1. SI=0 FI=0x6F07 IT=x\n");
    SockPrintf( "  ex2. SI=0 FI=0x2FE2,3F00 IT=x\n");
    SockPrintf( "  ex3. SI=0 FI=0x6FC9,0x3F00,0x7FFF IT=x\n\n");

    g_AppState = AppGetFileAttributes;                
}

void PrintUimAuthenticateOptions()
{
    SockPrintf( "\nPlease enter Authenticate request parameters\n"\
                        "  Or Press<Enter> to go to previous menu:\n"
                        "  Session Information(session type, app IDs): SI=type,id\n"\
                        "  Indication Token: IT=x\n"\
                        "  Autentication data(context, data): CON=1-17,abcde...\n");

    SockPrintf( "  ex. SI=0,1 IT=x CON=3,1234\n\n");

    g_AppState = AppAuthenticate;

}

void PrintUimDepersonalizationOptions()
{
    SockPrintf( "\nPlease enter Depersonalizatyion request parameters\n"\
                        "  Or Press<Enter> to go to previous menu:\n"
                        "  Depersonalization(feature, operation,control key): FE=0-15,0|1,abcd\n"\
                        "  slot (optional): SL=1|2|3|4|5\n");

    SockPrintf( "  ex. FE=0,0,000000 SL=1\n\n");

    g_AppState = AppDepersonalization;
}

static void PrintUimRefereshGetLastEventOption()
{
    SockPrintf( "\nPlease select referesh get last event values\n"\
                        "  Or Press<Enter> to go to previous menu:\n"
                        "  Session Information (session type, app IDs): SI=type,id\n");

    SockPrintf( "  ex. SI=0,1\n\n");

    g_AppState = AppRefereshGetLastEvent;
}

static void PrintUimConfigurationMaskOption()
{
    SockPrintf( "\nPlease enter Configuration Mask\n"\
                        "  UIM_GET_CONFIGURATION_AUTOMATIC_SELECTION (0x0001) - Automatic selection\n"\
                        "  UIM_GET_CONFIGURATION_PERSONALIZATION_STATUS(0x0002) - Personalization status\n"\
                        "  UIM_GET_CONFIGURATION_HALT_SUBSCRIPTION (0x0004) - Halt subscription\n"\
                        "  UIM_GET_CONFIGURATION_USB_UICC_SUPPORTED (0x0008) - USB UICC is supported\n"\
                        "  UIM_GET_CONFIGURATION_SAP_CLIENT_SUPPORTED (0x0010) - SAP in client mode is supported\n"\
                        "  UIM_GET_CONFIGURATION_PERSO_REACTIVATION_STATUS(0x0020) - Personalization reactivation status\n"\
                        "  UIM_GET_CONFIGURATION_REMOTE_SIMLOCK_STORAGE(0x0040) - Remote SimLock storage\n"\
                        "  UIM_GET_CONFIGURATION_EMERGENCY_ONLY (0x0080) - Emergency Only mode status\n"\
                        "  UIM_GET_CONFIGURATION_EXTENDED_APDU (0x0100) - Extended length APDUs are supported\n"\
                        "  UIM_GET_CONFIGURATION_INACTIVE_SIMLOCK_CONFIG(0x0200) - Inactive SimLock configuration\n");

    SockPrintf( "  ex. 0x01|0x04|0x10\n\n");
    SockPrintf( "Events Mask: ");
    g_AppState = AppGetConfigurationMask;                
}

static void PrintUimChangePinOption()
{
    SockPrintf( "\nPlease select change PIN values\n"\
                        "  Or Press<Enter> to go to previous menu:\n"
                        "  Session Information(session type, app IDs): SI=type,id\n"\
                        "  Indication Token(optional): IT=x\n"\
                        "  Change PIN(PIN ID, old PIN, new PIN): PIN=1|2|3|4,x..x,y..y\n"\
                        "  Key Ref ID(optional): PKI=1|2|3|4|5|6|7|8\n");

    SockPrintf( "  ex. SI=0,1 IT=x PIN=1,1234,4321 PKI=1\n\n");

    g_AppState = AppChangePin;                
}

static void ParseCommandLine( int argc, char **argv,
	enum eUserOptions* operation,
	socketUimCommandParam* cmdParam)
{
    int next_option;
   	bool got_operation = false;
	bool got_param_a = false;
	bool got_param_b = false;
	bool got_param_w = false;
	bool got_param_e = false;
	bool got_param_f = false;
	bool got_param_g = false;
	bool got_param_i = false;
	bool got_param_j = false;
	bool got_param_k = false;
	bool got_param_n = false;
	bool got_param_t = false;
	bool got_param_u = false;
	bool got_param_v = false;
	bool got_param_z = false;
	bool got_param_y = false;
	bool got_param_l = false;
	bool got_param_p = false;

    char szSessionInfo[50] = {0};
    char szPinId[50] = {0};
    char szEncryptedPIN1[50] = {0};
    char szUnblockPIN1[50] = {0};
    uint32_t IndicationToken;
    uint8_t KeyReferenceID;

    /* Parse the command line before doing anything else */
    do
    {
        /* Read the next option until there are no more */
        next_option = getopt_long( argc, argv,
                                   s_ShortOptions,
                                   s_LongOptions, NULL );

        switch( next_option )
        {
            case 'V':
                /* Print usage information */
                g_PrintVersion = true;
                break;
            case 'h':
                /* Print usage information */
                PrintUsageManual();
                exit (0);
                break;
            case 'd':
				StrCpy(g_DevicePath, optarg);
                break;
            case 'm':
                if (g_mode == QMUX_INTERFACE_UNKNOWN)
                    g_mode = QMUX_INTERFACE_MBIM;
                break;
            case 'q':
                if (g_mode == QMUX_INTERFACE_UNKNOWN)
                    g_mode = QMUX_INTERFACE_DIRECT;
                break;
			case 'r':
				if (g_mode == QMUX_INTERFACE_UNKNOWN)
					g_mode = QMUX_INTERFACE_ROUTER;
				break;
			case 's':
				g_socketServer = true;
				break;
			case 'o':
			    *operation = GetUimCommand(optarg);
				got_operation = true;
				break;
			case 'G':
                g_SkipGetClientIds = true;
				break;
			case 'R':
                g_SkipReleaseClientIds = true;
				break;
			case 'C':
				StrCpy(g_ClientIdsPath, optarg);
				break;
			case 'a':
			    GetUimMasks(optarg, &cmdParam->eventRegister.eventMask);
                got_param_a = true;
            break;
            case 'b':
                cmdParam->switchSlotIn.bLogicalSlot = atoi(optarg);
                got_param_b = true;
            break;
			case 'w':
                cmdParam->switchSlotIn.ulPhysicalSlot = atoi(optarg);
                got_param_w = true;
            break;
            case 'e':
                StrCpy(szSessionInfo, optarg);
                got_param_e = true;
            break;
            case 'f':
                StrCpy(szPinId, optarg);                
                got_param_f = true;
            break;
            case 'g':
                StrCpy(szEncryptedPIN1, optarg);
                got_param_g = true;
            break;
            case 'i':
                KeyReferenceID = atoi(optarg);
                got_param_i = true;
            break;
            case 'j':
                IndicationToken = atoi(optarg);
                got_param_j = true;
            break;
            case 'k':
                StrCpy(szUnblockPIN1, optarg);
                got_param_k = true;
            break;
            case 'n':
                cmdParam->refreshRegister.regRefresh.registerFlag = atoi(optarg);
                got_param_n = true;
            break;
            case 't':
                if (strlen(optarg) < 100)
                {
                    memset (&cmdParam->sFileAttributes.getFileAttributes, 0, sizeof(pack_uim_SLQSUIMGetFileAttributes_t));
                    GetUimFileInfo (optarg, false, &cmdParam->sFileAttributes.getFileAttributes);
                    got_param_t = true;
                }
            break;
            case 'u':                
                GetUimMasks(optarg, &cmdParam->sUIMGetConfiguration.configurationMask);
                got_param_u = true;
            break;
            case 'v':
                GetUimChangePin(optarg, &cmdParam->sChangePinInfo.changePinInfo);
                got_param_v = true;
            break;
            case 'z':
                cmdParam->sFileAttributes.securityAttributes = atoi(optarg);
                got_param_z = true;
            break;
            case 'y':
                GetUimAuthenticateData (optarg, &cmdParam->sAuthenticate.authenticateData.authData);
                got_param_y = true;
            break;
            case 'l':
                if (GetDepersonalizationParams (optarg, &cmdParam->sDepersonalization.depersonalization))
                {
                    got_param_l = true;
                }
            break;
            case 'p':
                cmdParam->sDepersonalization.slot = atoi(optarg);
                got_param_p = true;
            break;
			case -1:
                /* Done with options list */
                break;
            default:
                exit(EXIT_FAILURE);
                break;
        }
    }
    while( next_option != -1 );

	// check for operation arguments
	if (got_operation)
	{
        switch(*operation)
		{
		case eREG_GET_SLOT_STATUS:
		case eGET_CARD_STATUS:
		case eGET_ICCID:
        break;
		case eSET_EVENT_REGISTER:
			if (!got_param_a)
            {
				printf("Error: EventRegister operation missing --event_mask (-a) parameter\n");
				exit(EXIT_FAILURE);
            }
        break;
		case eSET_SWITCH_SLOT:
			if (!got_param_b)
            {
				printf("Error: SwitchSlot operation missing --logical_slot (-b) parameter\n");
				exit(EXIT_FAILURE);
            }
			if (!got_param_w)
            {
				printf("Error: SwitchSlot operation missing --physical_slot (-w) parameter\n");
				exit(EXIT_FAILURE);
            }
        break;
        case eSET_VERIFY_PIN:
            memset(&cmdParam->sVerifyPin.verifyPin, 0, sizeof(pack_uim_VerifyPin_t));
			if (!got_param_e)
            {
				printf("Error: VerifyPin operation missing --session_info (-e) parameter\n");
				exit(EXIT_FAILURE);
            }
			if (!got_param_f)
            {
				printf("Error: VerifyPin operation missing --pin_id (-f) parameter\n");
				exit(EXIT_FAILURE);
            }
            GetUimSessionInformation(szSessionInfo, &cmdParam->sVerifyPin.verifyPin.sessionInfo);

            if (false == GetUimVerifyPinInfo(szPinId, &cmdParam->sVerifyPin.verifyPin))
            {
				printf("Error: VerifyPin operation missing/wrong --pin_id (-f) parameter\n");
				exit(EXIT_FAILURE);
            }
            if (got_param_g)
            {
                GetUimEncryptPin1Info(szEncryptedPIN1, &cmdParam->sVerifyPin.EncryptedPIN1);
                cmdParam->sVerifyPin.verifyPin.pEncryptedPIN1 = &cmdParam->sVerifyPin.EncryptedPIN1;
            }
            if (got_param_i)
            {
                cmdParam->sVerifyPin.keyReferenceID = KeyReferenceID;
                cmdParam->sVerifyPin.verifyPin.pKeyReferenceID = &cmdParam->sVerifyPin.keyReferenceID;
            }
            if (got_param_j)
            {
                cmdParam->sVerifyPin.indicationToken = IndicationToken;
                cmdParam->sVerifyPin.verifyPin.pIndicationToken = &cmdParam->sVerifyPin.indicationToken;
            }
        break;
        case eSET_PIN_PROTECTION:
            memset(&cmdParam->sPinProtection.pinProtection, 0, sizeof(pack_uim_SetPinProtection_t));
			if (!got_param_e)
            {
				printf("Error: SetPinProtection operation missing --session_info (-e) parameter\n");
				exit(EXIT_FAILURE);
            }
			if (!got_param_f)
            {
				printf("Error: SetPinProtection operation missing --pin_id (-f) parameter\n");
				exit(EXIT_FAILURE);
            }
            
            GetUimSessionInformation(szSessionInfo, &cmdParam->sPinProtection.pinProtection.sessionInfo);

            if (false == GetUimProtectionPinInfo(szPinId, &cmdParam->sPinProtection.pinProtection))
            {
				printf("Error: SetPinProtection operation missing/wrong --pin_id (-f) parameter\n");
				exit(EXIT_FAILURE);
            }
            if (got_param_i)
            {
                cmdParam->sPinProtection.keyReferenceID = KeyReferenceID;
                cmdParam->sPinProtection.pinProtection.pKeyReferenceID = &cmdParam->sPinProtection.keyReferenceID;
            }
            if (got_param_j)
            {
                cmdParam->sPinProtection.indicationToken = IndicationToken;
                cmdParam->sPinProtection.pinProtection.pIndicationToken = &cmdParam->sPinProtection.indicationToken;
            }
        break;
        case eSET_UNBLOCK_PIN:
			if (!got_param_e)
            {
				printf("Error: UnblockPin operation missing --session_info (-e) parameter\n");
				exit(EXIT_FAILURE);
            }
			if (!got_param_k)
            {
				printf("Error: UnblockPin operation missing --unblock_pin (-k) parameter\n");
				exit(EXIT_FAILURE);
            }            
            GetUimSessionInformation(szSessionInfo, &cmdParam->sUnblockPin.unblockPin.sessionInfo);

            if (GetUimUnblockPinInfo(szUnblockPIN1, &cmdParam->sUnblockPin.unblockPin) == false)
            {
				printf("Error: UnblockPin operation invalid --unblock_pin (-k) parameter\n");
				exit(EXIT_FAILURE);
            }            
            if (got_param_i)
            {
                cmdParam->sUnblockPin.keyReferenceID = KeyReferenceID;
                cmdParam->sUnblockPin.unblockPin.pKeyReferenceID = &cmdParam->sUnblockPin.keyReferenceID;
            }
            if (got_param_j)
            {
                cmdParam->sUnblockPin.indicationToken = IndicationToken;
                cmdParam->sUnblockPin.unblockPin.pIndicationToken = &cmdParam->sUnblockPin.indicationToken;
            }
        break;
        case eSET_POWER_DOWN:
        case eSET_POWER_UP:
        case eSET_RESET:
        break;
        case eSET_REFRESH_REGISTER:
			if (!got_param_e)
            {
				printf("Error: RefreshRegister operation missing --session_info (-e) parameter\n");
				exit(EXIT_FAILURE);
            }
			if (!got_param_n)
            {
				printf("Error: RefreshRegister operation missing --referesh_registger (-n) parameter\n");
				exit(EXIT_FAILURE);
            }
            GetUimSessionInformation(szSessionInfo, &cmdParam->refreshRegister.sessionInfo);            
        break;
        case eGET_REFRESH_LAST_EVENT:
			if (!got_param_e)
            {
				printf("Error: RefreshGetLastEvent operation missing --session_info (-e) parameter\n");
				exit(EXIT_FAILURE);
            }
            GetUimSessionInformation(szSessionInfo, &cmdParam->refreshGetLastEvent.sessionInfo);            
        break;
        case eGET_FILE_ATTRIBUTES:
			if (!got_param_e)
            {
				printf("Error: GetFileAttributes operation missing --session_info (-e) parameter\n");
				exit(EXIT_FAILURE);
            }
			if (!got_param_t)
            {
				printf("Error: GetFileAttributes operation missing --file_info (-t) parameter\n");
				exit(EXIT_FAILURE);
            }
            GetUimSessionInformation(szSessionInfo, &cmdParam->sFileAttributes.getFileAttributes.sessionInfo);
            if (got_param_j)
            {
                cmdParam->sFileAttributes.indicationToken = IndicationToken;
                cmdParam->sFileAttributes.getFileAttributes.pIndicationToken = &cmdParam->sFileAttributes.indicationToken;
            }
            if (got_param_z)
            {
                cmdParam->sFileAttributes.getFileAttributes.pUICCSecurityAttributes = &cmdParam->sFileAttributes.securityAttributes; 
            }
        break;
        case eGET_DEPERSONALIZATION:
            cmdParam->sDepersonalization.depersonalization.pSlot = NULL;
			if (!got_param_l)
            {
				printf("Error: Depersonalization operation missing or invalid --depersonalization (-l) parameter\n");
				exit(EXIT_FAILURE);
            }
			if (got_param_p)
            {
                cmdParam->sDepersonalization.depersonalization.pSlot = &cmdParam->sDepersonalization.slot;
            }
        break;
        case eGET_AUTHENTICATE:
			if (!got_param_e)
            {
				printf("Error: Authenticate operation missing --session_info (-e) parameter\n");
				exit(EXIT_FAILURE);
            }
			if (!got_param_y)
            {
				printf("Error: Authenticate operation missing --authenticate_data (-y) parameter\n");
				exit(EXIT_FAILURE);
            }
            GetUimSessionInformation(szSessionInfo, &cmdParam->sAuthenticate.authenticateData.sessionInfo);

            if (got_param_j)
            {
                cmdParam->sAuthenticate.indicationToken = IndicationToken;
                cmdParam->sAuthenticate.authenticateData.pIndicationToken = &cmdParam->sAuthenticate.indicationToken;
            }
        break;
        case eGET_CONFIGURATION:
            if (got_param_u)
                cmdParam->sUIMGetConfiguration.getConfiguration.pConfigurationMask = &cmdParam->sUIMGetConfiguration.configurationMask;
            else
                cmdParam->sUIMGetConfiguration.getConfiguration.pConfigurationMask = NULL;
        break;
        case eSET_CHANGE_PIN:
			if (!got_param_e)
            {
				printf("Error: ChangePin operation missing --session_info (-e) parameter\n");
				exit(EXIT_FAILURE);
            }
			if (!got_param_v)
            {
				printf("Error: ChangePin operation missing --change_pin_info (-v) parameter\n");
				exit(EXIT_FAILURE);
            }
            GetUimSessionInformation(szSessionInfo, &cmdParam->sChangePinInfo.changePinInfo.sessionInfo);

            if (got_param_i)
            {
                cmdParam->sChangePinInfo.keyReferenceID = KeyReferenceID;
                cmdParam->sChangePinInfo.changePinInfo.pKeyReferenceID = &cmdParam->sChangePinInfo.keyReferenceID;
            }
            if (got_param_j)
            {
                cmdParam->sChangePinInfo.indicationToken = IndicationToken;
                cmdParam->sChangePinInfo.changePinInfo.pIndicationToken = &cmdParam->sChangePinInfo.indicationToken;
            }
        break;
        case eGET_READ_TRANSPARENT:
        break;
		default:
			break;
		}
	}
}

int main(int argc, char **argv)
{
	int ret = FAILURE;
	bool bPCIe = false;
	g_PrintVersion = false;

   	enum eUserOptions operation = eUNKNOWN;
	socketUimCommandParam cmdParam;
	memset(&cmdParam, 0, sizeof(socketUimCommandParam));
    ParseCommandLine(argc, argv, &operation, &cmdParam);

    if (g_PrintVersion)
    {
        printf("\n%s v%s\n\n", APPNAME, VERSION);
       	if (argc == 2)
		    return 0;
    }

    if (g_SkipGetClientIds || g_SkipReleaseClientIds)
    {
        if (strlen(g_ClientIdsPath) == 0)
        {
            printf("\nPlease specify a Client IDs path (-C)\n\n");
            return FAILURE;
        }
    }

    bool skipOpen = g_SkipGetClientIds; // By assumption, if we don't need to get client IDs, then the transport layer is already opened.
    bool skipClose = g_SkipReleaseClientIds; // By assumption, if we are not releasing client IDs, then the transport layer must not be closed.

    memset(&s_Transport, 0, sizeof(QmuxTransport));
    memset(&s_CtlService, 0, sizeof(CtlService));

    if (OpenTransportEx(&s_Transport, g_DevicePath, sizeof(g_DevicePath), &g_mode, &bPCIe, NULL,
		true, PrintUsageManual, argv[0], false, skipOpen, skipClose) != 0)
		return 0;

    bool skipSync = g_SkipGetClientIds; // By assumption, if we don't need to get client IDs, we have already synced with modem.

	if (CtlService_InitializeEx(&s_CtlService, &s_Transport, skipSync, 1) != SUCCESS)
		printf("CtlService_Initialize failed\n");
	else
	{
		memset(&s_UimService, 0, sizeof(QmiService));

        // We use the Ctl service to initialize the regular services because it knows how to 
        // acquire client IDs for them.

        // Use a do/while for easy exit. We have to clean up.
        do
        {
            uint8_t clientId = 0;

            if (g_SkipGetClientIds)
            {
                // We can initialize QmiService(s) directly with preexisting QMI client IDs.
                ret = RestoreClientId(eUIM, &clientId, g_ClientIdsPath);
                if (ret != SUCCESS)
                {
                    printf("RestoreClientId eUIM failed.\n");
                    break;
                }
            }

            // Infrastructure is now ready. Let's create some regular QMI services using the CTL service.

            ret = CtlService_InitializeRegularServiceEx(&s_CtlService, &s_UimService, eUIM, UimIndicationCallback, NULL, clientId);
            if (ret != SUCCESS)
            {
                printf("InitializeRegularServiceEx eUIM failed.\n");
                break;
            }

            g_AppState = AppRunning;
                        
			if (g_socketServer)
			{
				ExecuteUimSocketTestCase("/tmp/qmiuim-server-socket", &cmdParam);
			}
			else if (operation == eUNKNOWN)
			{
				ExecuteUimTestCaseSelection();
			}
			else
			{
				ExecuteUimTestCase(operation, &cmdParam);
			}

        } while (0);		

        // Shut down.
        g_AppState = AppShuttingDown;

        if (g_SkipReleaseClientIds)
        {
            // We are not releasing the client ID in this session.
            // so we should save it for next session.

            ret = SaveClientId(s_UimService.serviceType, s_UimService.clientId, g_ClientIdsPath);
            if (ret != SUCCESS)
            {
                printf("SaveClientId eUIM failed.\n");
            }
        }

        CtlService_ShutDownRegularServiceEx(&s_CtlService, &s_UimService, g_SkipReleaseClientIds);

        CtlService_ShutDown(&s_CtlService);
    }

	QmuxTransport_ShutDown(&s_Transport);
	
	return ret;
}
