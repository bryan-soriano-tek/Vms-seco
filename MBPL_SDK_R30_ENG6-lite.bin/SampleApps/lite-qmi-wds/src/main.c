#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <syslog.h>
#include <stdlib.h>
#include <getopt.h>
#include "common.h"
#include "ctl.h"
#include "wds.h"
#include "lite-qmi-wds.h"
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

extern void wds_indication_handler(uint16_t msgid, uint8_t *msg, uint32_t rlen);
extern void SetKeepAliveDataSession(QmiService* pQmiService, bool enableKA);
extern void ResetAndModifyProfileSettings(QmiService* pService, uint8_t profileID, uint8_t profileType, wds_profileInfo *pProfile);
extern void GetApnOpReservedPcoList(QmiService* pQmiService, char *pApnName);
extern void GetApnMsisdnInfo(QmiService* pQmiService, char *pApnName);
extern void DeleteAllProfiles(QmiService* pQmiService, pack_wds_DeleteAllProfiles_t *pDeleteAllProfiles);
extern void SetEhrpdFallbackApnList(QmiService* pQmiService, uint8_t fallback_apn_name_list_len, WdsEhrpdFallbackApn_t *pWdsEhrpdFallbackApn);
extern void SetModemAssistedKaStart(QmiService* pQmiService, pack_wds_modem_assisted_ka_start_t *pReqParam);
extern void SetModemAssistedKaStop(QmiService* pQmiService, pack_wds_modem_assisted_ka_stop_t *pModemAssistedKaStop);
extern void GetEhrpdFallbackApnList(QmiService* pQmiService);
extern void RegisterWdsEventRegister(QmiService* pQmiService, pack_wds_SLQSWdsSetEventReport_t *pReqArg);
extern void RegisterWdsIndicationRegister(QmiService* pQmiService, pack_wds_indication_register_t   *pIndicationRegister);
extern void GetDefaultProfileId(QmiService* pQmiService, pack_wds_GetDefaultProfileNum_t *pGetDefaultProfileNum);
extern void SetDefaultProfileId(QmiService* pQmiService, pack_wds_SetDefaultProfileNum_t *pSetDefaultProfileNum);
extern void Get3GPPConfigItems(QmiService* pQmiService);
extern void Set3GPPConfigItems(QmiService* pQmiService, pack_wds_SLQSSet3GPPConfigItem_t *pSet3GPPConfigItem);
extern void SetDownlinkThroughputReportPeriod(QmiService* pQmiService, pack_wds_SetDLThroughputReportPeriod_t *pSetDLThroughputReportPeriod);
extern void QueryDownlinkThroughputReportingStatus(QmiService* pQmiService);
extern void GetCurrentChannelRate(QmiService* pQmiService);
extern void GetDefaultNssai(QmiService* pQmiService);
extern void SetDefaultNssai(QmiService* pQmiService, pack_wds_swi_SetDefaultNssai_t *pSetDefaultNssai);
extern void GetProfileSnssai(QmiService* pQmiService, pack_wds_swi_GetPrfileSnssai_t *pGetPrfileSnssai);
extern void ClearProfileSnssai(QmiService* pQmiService, pack_wds_swi_ClearProfileSnssai_t *pClearProfileSnssai);
extern void DeleteProfile(QmiService* pQmiService, pack_wds_SLQSDeleteProfile_t *pDeleteProfile);
extern void ConfigureProfileSNssai(QmiService* pQmiService, pack_wds_SLQSCreateProfile_t *pCreateProfile);
extern void enable_profile_change_notification(QmiService* pSvc, uint8_t enable);

static CtlService s_CtlService;
static QmiService s_WdsService;
static QmuxTransport s_Transport;

//////////////////////////////////////////////////////////
static bool PrintInvalidArguments();
static void PrintGetKeepAliveOptions();
static void PrintGetResetAndModifyProfileInfo();
static void PrintGetApnOpReservedPCO();
static void PrintGetApnMsisdnIfo();
static void PrintDeleteAllProfilesInfo();
static void PrintSetEhrpdFallbackApn();
static void PrintSetModemAssitedKAStartInfo();
static void PrintSetModemAssitedKAStartInfoOptions();
static void PrintGetModemAssitedKAStartInfo();
static void PrintRegisterWdsEventReport();
static void PrintIndicationRegister();
static void PrintGetDefaultProfileIdInfo();
static void PrintSetDefaultProfileIdInfo();
static void PrintSet3GPPConfigItems();
static void PrintSetDownlinkThroughputReportPeriod();
static void PrintSetDefultNssai();
static void PrintDeleteProfile();

//#ifdef Firmware_support
static void PrintGetProfileSnssaiIndex();
static void PrintClearProfileSnssaiIndex();
static void PrintConfigureProfileSNssai();
//#endif

enum AppStateType g_AppState = AppUninitialized;
static bool g_keepAliveDataSession = false;
static uint8_t g_SetDefultNssai_index = 0;
static pack_wds_swi_SetDefaultNssai_t g_setDefaultNssai;

#define DEVICE_PATH_MAX 256
char g_DevicePath[DEVICE_PATH_MAX]={0};
uint32_t g_keep_alive_type = 0;

bool g_PrintVersion = false;
int g_mode = QMUX_INTERFACE_UNKNOWN;
bool g_socketServer = false;
bool g_SkipSync = false;

#define APPNAME "lite-qmi-wds"
#define VERSION "1.0.2210.0"

///////////////////////////////////////////////////
static void WdsIndicationCallback(uint8_t* qmiPacket, uint16_t qmiPacketSize, void* pIndicationCallbackContext)
{
	(void)pIndicationCallbackContext;

	unpack_qmi_t rsp_ctx;
	SockPrintf (ANSI_COLOR_YELLOW);
	SockPrintf("<< receiving wds indication: %s\n", helper_get_resp_ctx(eWDS, qmiPacket, qmiPacketSize, &rsp_ctx));
	SockPrintf("msgid 0x%x, type:%x\n", rsp_ctx.msgid,rsp_ctx.type);
	SockPrintf (ANSI_COLOR_RESET);
	wds_indication_handler(rsp_ctx.msgid, qmiPacket,  qmiPacketSize);
}

static void PrintGetKeepAliveOptions()
{
    SockPrintf("\nPlease select Keep-Alive data session option"\
                        "  Or Press<Enter> to go to previous menu:\n"\
                        "  1. Enable Keep-Alive data session\n"\
                        "  2. Disable Keep-Alive data session\n" );
    SockPrintf("Option:" );
    g_AppState = AppGetKeepAliveOption;
}

static void PrintGetResetAndModifyProfileInfo()
{
    SockPrintf("\nPlease type profile ID"\
                        "  Or Press<Enter> to go to previous menu:\n");
    SockPrintf("ex. ID=1\n" );
    g_AppState = AppGetResetProfileInfo;
}

static void PrintGetApnOpReservedPCO()
{
    SockPrintf("\nPlease enter APN name:\n"\
                        "  Or Press<Enter> for default:\n");
    SockPrintf("APN Name: " );
    g_AppState = AppGetApnOpResPcoList;
}

static void PrintGetApnMsisdnIfo()
{
    SockPrintf("\nPlease enter APN name:\n"\
                        "  Or Press<Enter> for default:\n");
    SockPrintf("APN Name:" );
    g_AppState = AppGetApnMsisdnInfo;
}

static void PrintDeleteAllProfilesInfo()
{
    SockPrintf("\nPlease enter profile type mask (3GPP=1, 3GPP2=2, 3GPP&3GPP2=3) "\
                        "  Or Press<Enter> to go to previous menu:\n");
    SockPrintf("Option:" );
    g_AppState = AppGetDeleteAllProfilesInfo;
}

static void PrintSetEhrpdFallbackApn()
{
    SockPrintf("\nPlease enter APN name\n");
    SockPrintf("APN name:" );
    g_AppState = AppSetEhrpdFallbackApnList;
}

static void PrintSetModemAssitedKAStartInfo()
{
    SockPrintf("\nPlease enter Keep-Alive type (TYPE_NAT=0) "\
                        "  Or Press<Enter> to go to previous menu:\n");
    SockPrintf("Keep-Alive type:" );
    g_AppState = AppSetModemAssistedKaStart;
}

static void PrintSetModemAssitedKAStartInfoOptions()
{
    SockPrintf("\nPlease enter at least one of the optional parameter:\n");
    SockPrintf("timer-value, apn-name, dest-ipv4-address, source-ipv4-address, dest-port, source-port\n" );
    SockPrintf("ex. timer-value=xx, apn-name=xx, dest-ipv4-address=xx, \n" );
    SockPrintf("    source-ipv4-address=xx, dest-port=xx, source-port=xx\n\n" );

    g_AppState = AppSetModemAssistedKaStartOptions;
}

static void PrintGetModemAssitedKAStartInfo()
{
    SockPrintf("\nPlease enter Keep-Alive handle \n");
    SockPrintf("Keep-Alive handle:" );
    g_AppState = AppSetModemAssistedKaStop;
}

static void PrintRegisterWdsEventReport()
{
    SockPrintf("\nPlease enter at least one of the optional parameter:\n");
    SockPrintf("Current Channel Rate Indicator State Period(Optional) (0: Do not report 1: Reort) CCRI=0|1\n" );
    SockPrintf("Transfer Statistics Indicator(Optional) (0: Do not report 1: Other - Period between reports (in seconds) ) TSI=0|x\n" );
    SockPrintf("Transfer Statistics Indicator Mask(Optional) (0x1:Tx packets OK 0x2:Rx packets OK 0x4:Tx packet errors 0x8:Rx packet errors 0x10:Tx overflows 0x20:Rx overflows 0x40:Tx bytes OK 0x80:Rx bytes OK 0x100:Tx packets dropped 0x200:Rx packets dropped ) TSIM=\n" );
    SockPrintf("Data Bearer Technology Indicator(Optional) (0: Do not report 1: Reort) DBTI=0|1\n" );
    SockPrintf("Dormancy Status indicator(Optional) (0: Do not report 1: Reort) DSI=0|1\n" );
    SockPrintf("MIP Status Indicator(Optional) (0: Do not report 1: Reort) MSI=0|1\n" );
    SockPrintf("Data Call Status Change Indicator(Optional) (0: Do not report 1: Reort) DCSI=0|1\n" );
    SockPrintf("Current Preferred Data System Indicator(Optional) (0: Do not report 1: Reort) CPDSI=0|1\n" );
    SockPrintf("EV-DO Page Monitor Period Change Indicator(Optional) (0: Do not report 1: Reort) EPMCI=0|1\n" );
    SockPrintf("Uplink Flow Control Indicator(Optional) (0: Do not report 1: Reort) UFCI=0|1\n" );
    SockPrintf("Additional PDN Filters Removal Indicator(Optional) (0: Do not report 1: Reort) APFRI=0|1\n" );
    SockPrintf("Data Bearer Technology Extended Indicator(Optional) (0: Do not report 1: Reort) DBTXI=0|1\n" );
    SockPrintf("Dormancy Result Indicator(Optional) (0: Do not report 1: Reort) DRI=0|1\n" );
    
    SockPrintf("ex. CCRI=1 TSI=1 TSIM=0x08|0x100|0x80 DSI=1 MSI=0 DCSI=0 CPDSI=1 EPMCI=0 UFCI=1 APFRI=1 DBTXI=1 DRI=1\n" );
    SockPrintf("WDS Event Report Options:  " );
    g_AppState = AppSetWdsEventReport;
}

static void PrintIndicationRegister()
{
    SockPrintf("\nPlease enter at least one of the optional parameter:\n");
    SockPrintf("Service status indication (Optional) (0- Do not suppress 1- Suppress) SSI=0|1\n" );
    SockPrintf("LTE attach PDN list (Optional) (0- Do not report 1- Report changed LTE attach PDN list) LAP=0|1\n" );
    SockPrintf("Report Profile Changes (Optional) (0- Do not report 1- Report profile changed events) RPC=0|1\n" );
    SockPrintf("Report APN List in Roaming (Optional) (0- Do not report 1- Report the list of APNs in Roaming) AAL=0|1\n" );
    SockPrintf("Report APN parameter change information (Optional) (0- Do not report 1- Report APN parameter change) AAP=0|1\n" );
    SockPrintf("Report LTE attach parameters (Optional) (0- Do not report 1- Report LTE attach parameters) RLA=0|1\n" );
    SockPrintf("APN for which the client is interested in receiving changes in operator PCO change information: (Optional) () APN=abc|1\n" );
    SockPrintf("APN for which the client is interested in receiving changes in MSISDN information (Optional) () APNM=0|1\n" );
    SockPrintf("Report bearer type information (Optional) (0- Do not report 1- Report bearer type information) RBT=0|1\n" );
    SockPrintf("Report Throttled PDN Information (Optional) (0- Do not report 1- Report throttled PDN information) RTP=0|1\n" );
    
    SockPrintf("ex. SSI=1 LAP=1 RPC=1 AAL=1 AAP=1 RLA=1 APN=swi3.ca.apn APNM=xxx RBT=1 RTP=1\n" );
    SockPrintf("WDS Indication Register Options:  " );

    g_AppState = AppWdsIndicationRegister;
}

static void PrintGetDefaultProfileIdInfo()
{
    SockPrintf("\nPlease enter profile type and profile family:\n");
    SockPrintf("Profile family (0: Embedded 1: Tethered) PF=0|1\n" );
    SockPrintf("ex. PF=1\n\n" );

    g_AppState = AppWdsGetDefaultProfileId;
}

static void PrintSetDefaultProfileIdInfo()
{
    SockPrintf("\nPlease enter profile type, profile family, and Profile number to be set as default profile:\n");
    SockPrintf("Profile family (0: Embedded 1: Tethered) PF=0|1\n" );
    SockPrintf("Profile ID PID=xx\n" );
    SockPrintf("ex. PF=0 PID=2\n\n" );

    g_AppState = AppWdsSetDefaultProfileId;
}

static void PrintSet3GPPConfigItems()
{
    SockPrintf("\nPlease enter one or more 3GPP Configuration Items:\n");
    SockPrintf("Profile List (optional) (1 to 4 profiles) PA=x,xx,x,x\n" );
    SockPrintf("Always connect default PDN (optional)(0: disabled 1: enabled) AC=0|1\n" );
    SockPrintf("3GPP Release (optional)(0: Release99 1: Release5 2: Release6 3: Release7 4: Release8 5: Release9 6: Release10 7: Release11) GR=0|1|2|3|4|5|6|7\n" );
    SockPrintf("LTE attach profiles in order of decreasing priority (1-24 possible values) (optional)(1 to 56 profiles) LP=x,x,xx,x,...\n" );
    SockPrintf("ex. PA=1,3 AC=1 GR=3 LP=1,12,24\n\n" );

    g_AppState = AppWdsSet3GPPConfigItems;
}

static void PrintSetDownlinkThroughputReportPeriod()
{
    SockPrintf("\nPlease enter Set Downlink Throughput Report Period in milliseconds:\n");

    g_AppState = AppWdsSetSetDLThroughputRP;
}

static void PrintSetDefultNssai()
{
    if (g_SetDefultNssai_index == 0)
    {
        SockPrintf("\nPlease enter Default Network Slice Selection Assistance Information or enter to continue:\n");
    }
    else
    {
        SockPrintf("\nPlease enter next(%d) Default Network Slice Selection Assistance Information or enter to continue:\n", g_SetDefultNssai_index+1);
    }

    SockPrintf("Slice or Service Type, SST=x\n" );
    SockPrintf("Slice Differentiator, SD=x.x.x\n" );
    SockPrintf("Mapped SST present, MSSTP=0|1\n" );
    SockPrintf("Mapped SST, MSST=x\n" );
    SockPrintf("Mapped SD, MSD=x.x.x\n" );
    
    SockPrintf("ex. SST=1 SD=1.2.255 MSSTP=1 MSST=1 MSD=1.255.10\n" );
    SockPrintf("Default NSSAI: " );

    g_AppState = AppWdsSetDefaultNssai;
}

static void PrintDeleteProfile()
{
    SockPrintf("Profile Type (0: 3GPP, 1: 3GPP2, 2: EPC), PT=x\n" );
    SockPrintf("Profile Index PI=x\n" );

    SockPrintf("ex. PT=0 PI=1\n" );
    SockPrintf("Delete Profile: " );

    g_AppState = AppWdsDeleteProfile;

}

//#ifdef Firmware_support
static void PrintGetProfileSnssaiIndex()
{
    SockPrintf("\nPlease enter S-NSSAI profile index to query:\n");

    g_AppState = AppWdsGetProfileSnssai;
}

static void PrintClearProfileSnssaiIndex()
{
    SockPrintf("\nPlease enter S-NSSAI profile index to clear:\n");

    g_AppState = AppWdsClearProfileSnssai;
}

static void PrintConfigureProfileSNssai()
{
    SockPrintf("Profile Type (0: 3GPP, 1: 3GPP2), PT=x\n" );
    SockPrintf("Profile Index (1-24 3GPP, 101-106 3GPP2) PI=x\n" );
    SockPrintf("Profile APN APN=abc\n" );
    SockPrintf("Slice or Service Type (Optional), SST=x\n" );
    SockPrintf("Slice Differentiator (Optional), SD=x.x.x\n" );
    SockPrintf("Mapped SST present (Optional), MSSTP=0|1\n" );
    SockPrintf("Mapped SST (Optional), MSST=x\n" );
    SockPrintf("Mapped SD (Optional), MSD=x.x.x\n" );
    SockPrintf("Session and Service Continuity (1|2|3)(Optional), SSC=x\n" );
    SockPrintf("Preferred Access Type (0|1|2)(Optional), PAT=x\n" );
    SockPrintf("Always On Pdu Session (0|1)(Optional), AOPS=x\n");

    SockPrintf("ex. PT=0 PI=1 APN=internet SST=1 SD=1.2.255 MSSTP=1 MSST=1 MSD=1.255.10 SSC=1 PAT=1 AOPS=1\n" );
    SockPrintf("Default NSSAI: " );

    g_AppState = AppWdsSwiConfigureProfile;
}

//#endif

static bool PrintInvalidArguments()
{
    SockPrintf("\n     Invalid arquments."
           "\n     Press<Enter> to go to previous menu.");
    fflush(stdout);
    return true;
}

static bool ParceSetDefaultNssaiSettings (char *str_return, wds_swi_configured_nssai_type *pDefault_nssai_info )
{
    size_t sdSize = 3, mapped_sdSize = 3;
    return ExtractUInt8Value(str_return, "SST=", 0, &pDefault_nssai_info->sst) &&
        ExtractUInt8ArrayValues(str_return, "SD=", 0, '.', pDefault_nssai_info->sd, &sdSize) && sdSize == 3 &&
        ExtractUInt8Value(str_return, "MSSTP=", 0, &pDefault_nssai_info->mapped_sst_present) &&
        ExtractUInt8Value(str_return, "MSST=", 0, &pDefault_nssai_info->mapped_sst) &&
        ExtractUInt8ArrayValues(str_return, "MSD=", 0, '.', pDefault_nssai_info->mapped_sd, &mapped_sdSize) && mapped_sdSize == 3;
}

static bool ParceSwiConfigureProfileSNassai(char *str_return, pack_wds_SLQSCreateProfile_t *pCreateProfile,
                                              uint8_t *apn,
                                              uint16_t *apnSize,
                                              wds_swi_configured_nssai_type *pS_Nassai,
                                              uint8_t *pSsc,
                                              uint8_t *pPreferred_access_type,
                                              uint8_t *pAlwaysOnPduSession)
{
    if (pCreateProfile == NULL || pCreateProfile->pProfileType == NULL ||
        pCreateProfile->pProfileId == NULL || pCreateProfile->pCurProfile == NULL ||
        apn == NULL || apnSize == NULL)
        return false;

    if (!ExtractUInt8Value(str_return, "PT=", 0, pCreateProfile->pProfileType) ||
        !ExtractUInt8Value(str_return, "PI=", 0, pCreateProfile->pProfileId))
        return false;

    if (!ExtractSubStringValue(str_return, "APN=", 0, (char*)apn, *apnSize))
        return false;

    *apnSize = strlen((char*)apn) + 1;

    switch (*pCreateProfile->pProfileType)
    {
    case 0: // 3GPP
    {
        pCreateProfile->pCurProfile->SlqsProfile3GPP.pAPNName = apn;
        pCreateProfile->pCurProfile->SlqsProfile3GPP.pAPNnameSize = apnSize;

        size_t sdSize = 3, mapped_sdSize = 3;
        ExtractUInt8Value(str_return, "SST=", 0, &pS_Nassai->sst);
        ExtractUInt8ArrayValues(str_return, "SD=", 0, '.', pS_Nassai->sd, &sdSize);
        ExtractUInt8Value(str_return, "MSSTP=", 0, &pS_Nassai->mapped_sst_present);
        ExtractUInt8Value(str_return, "MSST=", 0, &pS_Nassai->mapped_sst);
        ExtractUInt8ArrayValues(str_return, "MSD=", 0, '.', pS_Nassai->mapped_sd, &mapped_sdSize);
        pCreateProfile->pCurProfile->SlqsProfile3GPP.pS_Nassai = pS_Nassai;

        if (ExtractUInt8Value(str_return, "SSC=", 0, pSsc))
            pCreateProfile->pCurProfile->SlqsProfile3GPP.pSsc = pSsc;

        if (ExtractUInt8Value(str_return, "PAT=", 0, pPreferred_access_type))
            pCreateProfile->pCurProfile->SlqsProfile3GPP.pPreferred_access_type = pPreferred_access_type;

        if (ExtractUInt8Value(str_return, "AOPS=", 0, pAlwaysOnPduSession))
            pCreateProfile->pCurProfile->SlqsProfile3GPP.pAlwaysOnPduSession = pAlwaysOnPduSession;
        break;

    }
    case 1: // 3GPP2
        pCreateProfile->pCurProfile->SlqsProfile3GPP2.pApnString = apn;
        pCreateProfile->pCurProfile->SlqsProfile3GPP2.pApnStringSize = apnSize;
        break;
    default:
        return false;
    }

    return true;
}

static void ExecuteWdsTestCase(enum eUserOptions operation, socketWdsCommandParam *cmdParam)
{
    switch(operation)
    {
	    case eSET_KEEP_ALIVE_DATA_SESSION:
        {
            SetKeepAliveDataSession(&s_WdsService, cmdParam->enableKA);
        }
        break;
	    case eSET_RESET_MODIFY_PROFILE_SEETING:
    	{
            ResetAndModifyProfileSettings(&s_WdsService, cmdParam->sResetAndModifyProfileSettings.ProfileId, 0, NULL);
	    }
        break;
        case eGET_APN_OP_RESERVED_PCO:
        {
            GetApnOpReservedPcoList(&s_WdsService, cmdParam->ApnName);
        }
        break;
        case eGET_APN_MSISDN_INFO:
        {
            GetApnMsisdnInfo(&s_WdsService, cmdParam->ApnName);
        }
        break;
        case eSET_DELETE_ALL_PROFILES:
        {
            DeleteAllProfiles(&s_WdsService, &cmdParam->sDeleteAllProfiles);
        }
        break;
	    case eGET_EHRPD_FALLBACK_APN:
            GetEhrpdFallbackApnList(&s_WdsService);
        break;
	    case eSET_EHRPD_FALLBACK_APN:
        {
            uint8_t fallback_apn_name_list_len = 1;
            WdsEhrpdFallbackApn_t wdsEhrpdFallbackApn;
            memset(&wdsEhrpdFallbackApn, 0, sizeof(WdsEhrpdFallbackApn_t));
            wdsEhrpdFallbackApn.apn_name_len = strlen(cmdParam->ApnName);
			StrNCpy(wdsEhrpdFallbackApn.apn_name, cmdParam->ApnName, wdsEhrpdFallbackApn.apn_name_len);

            SetEhrpdFallbackApnList(&s_WdsService, fallback_apn_name_list_len, &wdsEhrpdFallbackApn);
        }
        break;
        case eSET_MODEM_ASSISTED_KA_START:
        {
            if (strlen(cmdParam->sModemAssistedKaStart.ApnName) > 0)
            {
                cmdParam->sModemAssistedKaStart.apn_name_len = strlen(cmdParam->sModemAssistedKaStart.ApnName); 
                cmdParam->sModemAssistedKaStart.modemAssistedKaStart.apn_name_len = &cmdParam->sModemAssistedKaStart.apn_name_len; 
                cmdParam->sModemAssistedKaStart.modemAssistedKaStart.pApn_Name = cmdParam->sModemAssistedKaStart.ApnName;
            }
            else
            {
                cmdParam->sModemAssistedKaStart.modemAssistedKaStart.pApn_Name = NULL;
                cmdParam->sModemAssistedKaStart.modemAssistedKaStart.apn_name_len = 0; 
            }
            SetModemAssistedKaStart(&s_WdsService, &cmdParam->sModemAssistedKaStart.modemAssistedKaStart);
        }
        break;
        case eSET_MODEM_ASSISTED_KA_STOP:
        {
            SetModemAssistedKaStop(&s_WdsService, &cmdParam->sModemAssistedKaStop);
        }
        break;
        case eSET_EVENT_REGISTER:
        {
            RegisterWdsEventRegister(&s_WdsService, &cmdParam->sWdsSetEventReport.wdsSetEventReport);
        }
        break;
        case eSET_INDICATION_REGISTER:
        {
            RegisterWdsIndicationRegister(&s_WdsService, &cmdParam->sIndicationRegister.indicationRegister);
        }
        break;
        case eGET_DEFAULT_PROFILE_ID:
        {
            GetDefaultProfileId(&s_WdsService, &cmdParam->sGetDefaultProfileNum);
        }
        break;
        case eSET_DEFAULT_PROFILE_ID:
        {
            SetDefaultProfileId(&s_WdsService, &cmdParam->sSetDefaultProfileNum);
        }
        break;
        case eGET_3GPP_CONFIG_ITEMS:
        {
            Get3GPPConfigItems(&s_WdsService);
        }
        break;
        case eSET_3GPP_CONFIG_ITEMS:
        {
            Set3GPPConfigItems(&s_WdsService, &cmdParam->sSet3GPPConfigItem.set3GPPConfigItem);
        }
        break;
        case eSET_DOWNLINK_THROUGHPUT_REPORT_PERIOD:
        {
            pack_wds_SetDLThroughputReportPeriod_t sSetDLThroughputReportPeriod;
            sSetDLThroughputReportPeriod.pDownlink_throughput_report_period = &cmdParam->Downlink_throughput_report_period;
            SetDownlinkThroughputReportPeriod(&s_WdsService, &sSetDLThroughputReportPeriod);
        }
        break;
        case eGET_DOWNLINK_THROUGHPUT_REPORTING_STATUS:
        {
            QueryDownlinkThroughputReportingStatus(&s_WdsService);
        }
        break;
        case eGET_CURRENT_CHANNEL_RATE:
        {
            GetCurrentChannelRate(&s_WdsService);
        }
        break;
	    case eGET_DEFAULT_NSAAI:
        {
            GetDefaultNssai(&s_WdsService);
        }
        break;
	    case eSET_DEFAULT_NSAAI:
        {            
            memset(&g_setDefaultNssai, 0, sizeof(pack_wds_swi_SetDefaultNssai_t));
            g_SetDefultNssai_index = 0;
            bool bInvalidArgument = false;
            
            char *pDefaultNssai = cmdParam->default_nssai_str; 
            char *pCloseBrace = strstr(pDefaultNssai, ")");
            char szDefaultNssai[100] = {0};
            while (pDefaultNssai[0] == '(' && pCloseBrace)
            {
		        StrNCpy(szDefaultNssai, pDefaultNssai+1, pCloseBrace-pDefaultNssai-1);
                if (false == ParceSetDefaultNssaiSettings(szDefaultNssai, &g_setDefaultNssai.default_nssai_info[g_SetDefultNssai_index]))
                {
                    bInvalidArgument = true;
                    g_SetDefultNssai_index = 0;
                    break;
                }
                ++g_SetDefultNssai_index;
                pDefaultNssai = pCloseBrace + 1;
                pCloseBrace = strstr(pDefaultNssai, ")");
            }
            if (bInvalidArgument)
            {
                PrintInvalidArguments();
            }
            if(g_SetDefultNssai_index > 0)
            {
                g_setDefaultNssai.default_nssai_info_len = g_SetDefultNssai_index;
                SetDefaultNssai(&s_WdsService, &g_setDefaultNssai);
                g_SetDefultNssai_index = 0;
            }
        }
        break;
	    case eGET_PROFILE_SNSAAI:
        {
            pack_wds_swi_GetPrfileSnssai_t getPrfileSnssai;
            getPrfileSnssai.profile_index = cmdParam->Profile_index;
            GetProfileSnssai(&s_WdsService, &getPrfileSnssai);
        }
        break;
        case eSET_CONFIGURE_PROFILE_SNSAAI:
        {
            uint8_t profileType = 0, profileId = 0;
            uint8_t apn[64];
            uint16_t apnSize = 64;

            wds_profileInfo  curProfile;
            memset(&curProfile, 0, sizeof(wds_profileInfo));

            pack_wds_SLQSCreateProfile_t sCreateProfile;
            memset(&sCreateProfile, 0, sizeof(pack_wds_SLQSCreateProfile_t));
            sCreateProfile.pProfileType = &profileType;
            sCreateProfile.pProfileId = &profileId;
            sCreateProfile.pCurProfile = &curProfile;

            wds_swi_configured_nssai_type s_nassai;
            memset(&s_nassai, 0, sizeof(wds_swi_configured_nssai_type));
            uint8_t ssc = 0;
            uint8_t preferred_access_type = 0;
            uint8_t alwaysOnPduSession = 0;

            if (false == ParceSwiConfigureProfileSNassai(cmdParam->configure_nssai_str, &sCreateProfile, apn, &apnSize, &s_nassai, &ssc, &preferred_access_type, &alwaysOnPduSession))
            {
                PrintInvalidArguments();
            }
            else
            {
                ConfigureProfileSNssai(&s_WdsService, &sCreateProfile);                
            }
        }
        break;
	    case eSET_DELETE_PROFILE:
        {
            pack_wds_SLQSDeleteProfile_t deleteProfile;
            deleteProfile.profileType = cmdParam->sDeleteProfile.profileType;
            deleteProfile.profileIndex = cmdParam->sDeleteProfile.profileIndex;
            DeleteProfile(&s_WdsService, &deleteProfile);            
        }
        break;
	    case eSET_CLEAR_PROFILE_SNSAAI:
        {
            pack_wds_swi_ClearProfileSnssai_t clearProfileSnssai;
            clearProfileSnssai.profile_index = cmdParam->Profile_index;
            ClearProfileSnssai(&s_WdsService, &clearProfileSnssai);
        }
        break;
    	default:
		break;
    }
}

void ExecuteWdsSocketTestCase(const char* socketName, socketWdsCommandParam* cmdParam)
{
	if (OpenSocket(socketName) == 0)
		return;

	while (1)
	{
		int op = GetWdsSocketCommand(APPNAME, cmdParam);
		if (op == eEXIT)
			break;

		ExecuteWdsTestCase(op, cmdParam);
	}

	CloseSocket();
}

static void ExecuteWdsTestCaseSelection(void)
{
	char str_return[MAX_USER_INPUT_SIZE];
	char *pChar = NULL;
	PrintPrompt();
	
	while (1)
	{
		fflush(stdin);
		memset (str_return,0,MAX_USER_INPUT_SIZE);

		while (fgets(str_return, MAX_USER_INPUT_SIZE, stdin) == NULL);

		switch(g_AppState)
		{
			case AppCommandExecuted:
				g_AppState = AppRunning;
				PrintPrompt();
			break;
			case AppGetApnOpResPcoList:
            case AppGetApnMsisdnInfo:
            case AppWdsSetDefaultNssai:
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
			SockPrintf("quitting...\n");
			break;
		} else if (!strcmp(str_return, "d"))
		{
			PrintPrompt();
		} 
        if (g_AppState == AppGetKeepAliveOption)
        {
            g_keepAliveDataSession = !(strcmp(str_return, "1")) ? true : false;
            SetKeepAliveDataSession(&s_WdsService, g_keepAliveDataSession);                
            g_AppState = AppCommandExecuted;
        }
        else if (g_AppState == AppGetResetProfileInfo)
        {
            uint8_t resetProfileID = 0xFF;
            uint8_t resetProfileType = 0; //3gpp

            pChar = strstr(str_return, "ID=");
            if (pChar)
            {
                pChar += 3;
                resetProfileID = atoi( pChar );
            }
            if (resetProfileID == 0xFF)
            {
                PrintInvalidArguments();
            }
            else
            {
                wds_profileInfo  *pProfile = NULL;
                ResetAndModifyProfileSettings(&s_WdsService, resetProfileID, resetProfileType, pProfile);
            }
            
            g_AppState = AppCommandExecuted;
        }
        else if (g_AppState == AppGetApnOpResPcoList)
        {
            GetApnOpReservedPcoList(&s_WdsService, str_return);
            g_AppState = AppCommandExecuted;
        }
        else if (g_AppState == AppGetApnMsisdnInfo)
        {
            GetApnMsisdnInfo(&s_WdsService, str_return);
            g_AppState = AppCommandExecuted;
        }
        else if (g_AppState == AppGetDeleteAllProfilesInfo)
        {
            pack_wds_DeleteAllProfiles_t sDeleteAllProfiles;
            memset(&sDeleteAllProfiles, 0, sizeof(pack_wds_DeleteAllProfiles_t));
            sDeleteAllProfiles.ProfileTypeMask = atoi(str_return); 
            DeleteAllProfiles(&s_WdsService, &sDeleteAllProfiles);
            g_AppState = AppCommandExecuted;
        }
        else if (g_AppState == AppSetEhrpdFallbackApnList)
        {
            uint8_t fallback_apn_name_list_len = 1;
            WdsEhrpdFallbackApn_t wdsEhrpdFallbackApn;
            memset(&wdsEhrpdFallbackApn, 0, sizeof(WdsEhrpdFallbackApn_t));
            wdsEhrpdFallbackApn.apn_name_len = strlen(str_return);
			if (wdsEhrpdFallbackApn.apn_name_len >= sizeof(wdsEhrpdFallbackApn.apn_name))
				wdsEhrpdFallbackApn.apn_name_len = sizeof(wdsEhrpdFallbackApn.apn_name) - 1;
			StrNCpy(wdsEhrpdFallbackApn.apn_name, str_return, wdsEhrpdFallbackApn.apn_name_len);

            SetEhrpdFallbackApnList(&s_WdsService, fallback_apn_name_list_len, &wdsEhrpdFallbackApn);
            g_AppState = AppCommandExecuted;
        }
        else if (g_AppState == AppSetModemAssistedKaStart)
        {
            g_keep_alive_type = atoi(str_return);
            PrintSetModemAssitedKAStartInfoOptions();
        }
        else if(g_AppState == AppSetModemAssistedKaStartOptions)
        {
            if (strlen(str_return) == 0)
            {
                PrintInvalidArguments();
            }
            else
            {    
                pack_wds_modem_assisted_ka_start_t kaParam;
                memset(&kaParam, 0, sizeof(pack_wds_modem_assisted_ka_start_t));
                kaParam.keep_alive_type = g_keep_alive_type;

                uint32_t	Timer_value = 0;
                uint32_t	Dest_ipv4_address = 0;
                uint32_t	Source_ipv4_address = 0;
                uint16_t	Dest_port = 0;
                uint16_t	Source_port = 0;
                uint8_t		apn_name_len = 0;
                char		Apn_Name[255] = {0};
        
                if (ExtractUInt32Value(str_return, "timer-value=", ',', &Timer_value))
                    kaParam.pTimer_value = &Timer_value; 

                if (ExtractSubStringValue(str_return, "apn-name=", ',', Apn_Name, sizeof(Apn_Name)))
                {
                    apn_name_len = strlen(Apn_Name); 
                    if (apn_name_len > 0)
                    {
                        kaParam.apn_name_len = &apn_name_len;
                        kaParam.pApn_Name = Apn_Name;
                    }
                }
                if (ExtractUInt32Value(str_return, "dest-ipv4-address=", ',', &Dest_ipv4_address))
                    kaParam.pDest_ipv4_address = &Dest_ipv4_address;
                if (ExtractUInt32Value(str_return, "source-ipv4-address=", ',', &Source_ipv4_address))
                    kaParam.pSource_ipv4_address = &Source_ipv4_address; 
                if (ExtractUInt16Value(str_return, "dest-port=", ',', &Dest_port))
                    kaParam.pDest_port = &Dest_port; 
                if (ExtractUInt16Value(str_return, "source-port=", ',', &Source_port))
                    kaParam.pSource_port = &Source_port; 

                //At least one optional parameter must be set.
                if (kaParam.pTimer_value || kaParam.pApn_Name || kaParam.pDest_ipv4_address || 
                    kaParam.pSource_ipv4_address || kaParam.pDest_port || kaParam.pSource_port)
                {
                    SetModemAssistedKaStart(&s_WdsService, &kaParam);
                }
                else
                {
                    PrintInvalidArguments();
                }                
            }

            g_AppState = AppCommandExecuted;
        }
        else if (g_AppState == AppSetModemAssistedKaStop)
        {
            pack_wds_modem_assisted_ka_stop_t sModemAssistedKaStop;
            sModemAssistedKaStop.keep_alive_handle = atoi(str_return);
            SetModemAssistedKaStop(&s_WdsService, &sModemAssistedKaStop);
            g_AppState = AppCommandExecuted;
        }
        else if(g_AppState == AppSetWdsEventReport)
        {
            if (strlen(str_return) == 0)
            {
                PrintInvalidArguments();
            }
            else{
                //CCRI=1 TSI=1 TSIM=0x08|0x100|0x100 DSI=1 MSI=0 DCSI=0 CPDSI=1 EPMCI=0 UFCI=1 APFRI=1 DBTXI=1 DRI=
                uint8_t CCRI, DSI, MSI, DCSI, CPDSI, EPMCI, UFCI, APFRI, DBTXI, DRI;
                uint32_t TSIM[32];
                size_t TSIMSize = 32;
                memset(TSIM, 0, sizeof(uint32_t) * 32);

                wds_TrStatInd   TransferStatInd;

                pack_wds_SLQSWdsSetEventReport_t reqArg;
                memset (&reqArg, 0, sizeof(pack_wds_SLQSWdsSetEventReport_t));

                if (ExtractUInt8Value(str_return, "CCRI=", ' ', & CCRI))
                     reqArg.pCurrChannelRateInd = &CCRI;
 
                if (ExtractUInt8Value(str_return, "TSI=", ' ', &TransferStatInd.statsPeriod) &&
                    ExtractUInt32ArrayValues(str_return, "TSIM", ' ', '|', TSIM, &TSIMSize))
                {
                    for (size_t i = 0; i < TSIMSize; i++)
                        TransferStatInd.statsMask |= TSIM[i];

                    reqArg.pTransferStatInd = &TransferStatInd;
                }            
                if (ExtractUInt8Value(str_return, "DSI=", ' ', &DSI))
                    reqArg.pDormancyStatusInd = &DSI;
                if (ExtractUInt8Value(str_return, "MSI=", ' ', &MSI))
                    reqArg.pMIPStatusInd = &MSI;
                if (ExtractUInt8Value(str_return, "DCSI=", ' ', &DCSI))
                    reqArg.pDataCallStatusChangeInd = &DCSI;
                if (ExtractUInt8Value(str_return, "CPDSI=", ' ', &CPDSI))
                    reqArg.pCurrPrefDataSysInd = &CPDSI;
                if (ExtractUInt8Value(str_return, "EPMCI=", ' ', &EPMCI))
                    reqArg.pEVDOPageMonPerChangeInd = &EPMCI;
                if (ExtractUInt8Value(str_return, "UFCI=", ' ', &UFCI))
                    reqArg.pUlFlowControlInd = &UFCI;
                if (ExtractUInt8Value(str_return, "APFRI=", ' ', &APFRI))
                    reqArg.pReportAddPdnFiltersRemoval = &APFRI;
                if (ExtractUInt8Value(str_return, "DBTXI=", ' ', &DBTXI))
                    reqArg.pDataBearerTechExtInd = &DBTXI;
                if (ExtractUInt8Value(str_return, "DRI=", ' ', &DRI))
                    reqArg.pDormancyResultIndicator = &DRI;

                RegisterWdsEventRegister(&s_WdsService, &reqArg);
            }
            g_AppState = AppCommandExecuted;
        }
        else if(g_AppState == AppWdsIndicationRegister)
        {
            if (strlen(str_return) == 0)
            {
                PrintInvalidArguments();
            }
            else
            {
                //SSI=1 LAP=1 RPC=1 AAL=1 AAP=1 RLA=1 APN=swi3.ca.apn APNM=xxx RBT=1 RTP=1
                uint8_t SSI, LAP, RPC, AAL, AAP, RLA, RCP, RCM, RBT, RTP, ApnNameLen, ApnNameLenMsisdn;
                char szAPN[100];
                char szApnMsisdn[100];
                memset(szAPN, 0, 100*sizeof(char));
                memset(szApnMsisdn, 0, 100*sizeof(char));

                pack_wds_indication_register_t   sIndicationRegister;
                memset(&sIndicationRegister, 0, sizeof(pack_wds_indication_register_t));
                if (ExtractUInt8Value(str_return, "SSI=", ' ', &SSI))
                    sIndicationRegister.pSupperesPktSrvcInd = &SSI;
                if (ExtractUInt8Value(str_return, "LAP=", ' ', &LAP))
                    sIndicationRegister.pReportLteAttachPdnListChange = &LAP;
                if (ExtractUInt8Value(str_return, "RPC=", ' ', &RPC))
                    sIndicationRegister.pReportProfileChangeEvents = &RPC;
                if (ExtractUInt8Value(str_return, "AAL=", ' ', &AAL))
                    sIndicationRegister.pReportRoamingApnList = &AAL;
                if (ExtractUInt8Value(str_return, "AAP=", ' ', &AAP))
                    sIndicationRegister.pReportApnParamChangeInfo = &AAP;
                if (ExtractUInt8Value(str_return, "RLA=", ' ', &RLA))
                    sIndicationRegister.pReportLteAttachParams = &RLA;
                
                if (ExtractSubStringValue(str_return, "APN=", ' ', szAPN, sizeof(szAPN)))
                {   
                    sIndicationRegister.pApnName = szAPN;
                    ApnNameLen = strlen(szAPN);
                    sIndicationRegister.pApnNameLen = &ApnNameLen; 

                    RCP = 1;
                    sIndicationRegister.pReportOpResevedPcoListChange = &RCP;
                }
                if (ExtractSubStringValue(str_return, "APNM=", ' ', szApnMsisdn, sizeof(szApnMsisdn)))
                {
                    sIndicationRegister.pApnNameMsisdn = szApnMsisdn;
                    ApnNameLenMsisdn = strlen(szApnMsisdn);
                    sIndicationRegister.pApnNameMsisdnLen = &ApnNameLenMsisdn; 

                    RCM = 1;
                    sIndicationRegister.pReportMsisdnInfoChange = &RCM;
                }
                if (ExtractUInt8Value(str_return, "RBT=", ' ', &RBT))
                    sIndicationRegister.pReportBearerType = &RBT;
                if (ExtractUInt8Value(str_return, "RTP=", ' ', &RTP))
                
                RegisterWdsIndicationRegister(&s_WdsService, &sIndicationRegister);
            }
            g_AppState = AppCommandExecuted;
        }
        else if (g_AppState == AppWdsGetDefaultProfileId)
        {
            char *pPF  = strstr(str_return, "PF=");
            if (pPF == NULL)
            {
                PrintInvalidArguments();
            }
            else
            {
                pack_wds_GetDefaultProfileNum_t  sGetDefaultProfileNum;
                memset (&sGetDefaultProfileNum, 0, sizeof(pack_wds_GetDefaultProfileNum_t));
                pPF += 3;
                sGetDefaultProfileNum.type = 0; //3gpp
                sGetDefaultProfileNum.family = atoi(pPF);
                if (sGetDefaultProfileNum.family > 1)
                {
                    PrintInvalidArguments();
                }
                else
                {
                    GetDefaultProfileId(&s_WdsService, &sGetDefaultProfileNum);
                }
            }

            g_AppState = AppCommandExecuted;
        }
        else if (g_AppState == AppWdsSetDefaultProfileId)
        {
            pack_wds_SetDefaultProfileNum_t  sSetDefaultProfileNum;
            memset (&sSetDefaultProfileNum, 0, sizeof(pack_wds_SetDefaultProfileNum_t));
            sSetDefaultProfileNum.type = 0; //3gpp

            if (!ExtractUInt8Value(str_return, "PF=", ' ', &sSetDefaultProfileNum.family) ||
                !ExtractUInt8Value(str_return, "PID=", ' ', &sSetDefaultProfileNum.index))
            {
                PrintInvalidArguments();
            }
            else
            {
                if (sSetDefaultProfileNum.family > 1)
                {
                    PrintInvalidArguments();
                }
                else
                {
                    SetDefaultProfileId(&s_WdsService, &sSetDefaultProfileNum);
                }
            }

            g_AppState = AppCommandExecuted;
        }
        else if (g_AppState == AppWdsSet3GPPConfigItems)
        {
            bool bHasValue = false;
            //PA=1,3 AC=1 GR=3 LP=1,12,24

            pack_wds_SLQSSet3GPPConfigItem_t sSet3GPPConfigItem;
            memset (&sSet3GPPConfigItem, 0, sizeof(pack_wds_SLQSSet3GPPConfigItem_t));
            uint16_t ProfileList[4] = {0};
            size_t sizeProfileList = 4;
            uint8_t  nDefaultPDNEnabled = 0;
            uint8_t  n3gppRelease = 0;
            uint16_t LTEAttachProfileList[56] = {0};
            size_t sizeLTEAttachProfileList = 56;

            sSet3GPPConfigItem.pLTEAttachProfile = NULL;

            if (ExtractUInt16ArrayValues(str_return, "PA=", ' ', ',', ProfileList, &sizeProfileList) && sizeProfileList > 0)
            {
                bHasValue = true;
                sSet3GPPConfigItem.pProfileList = ProfileList;
            }
            if (ExtractUInt8Value(str_return, "AC=", ' ', &nDefaultPDNEnabled))
            {
                bHasValue = true;
                sSet3GPPConfigItem.pDefaultPDNEnabled = &nDefaultPDNEnabled;
            }
            if (ExtractUInt8Value(str_return, "GR=", ' ', &n3gppRelease))
            {
                bHasValue = true;
                sSet3GPPConfigItem.p3gppRelease = &n3gppRelease;
            }
            if (ExtractUInt16ArrayValues(str_return, "LP=", ' ', ',', LTEAttachProfileList, &sizeLTEAttachProfileList) && sizeLTEAttachProfileList > 0)
            {
                bHasValue = true;
                sSet3GPPConfigItem.pLTEAttachProfileList = LTEAttachProfileList;
                sSet3GPPConfigItem.LTEAttachProfileListLen = sizeLTEAttachProfileList;
            }

            if (!bHasValue)
            {
                PrintInvalidArguments();
            }
            else
            {
                Set3GPPConfigItems(&s_WdsService, &sSet3GPPConfigItem);
            }

            g_AppState = AppCommandExecuted;
        }
        else if (g_AppState == AppWdsSetSetDLThroughputRP)
        {
            pack_wds_SetDLThroughputReportPeriod_t sSetDLThroughputReportPeriod;
            uint32_t downlink_throughput_report_period = atoi(str_return);
            sSetDLThroughputReportPeriod.pDownlink_throughput_report_period = &downlink_throughput_report_period;
            SetDownlinkThroughputReportPeriod(&s_WdsService, &sSetDLThroughputReportPeriod);
            g_AppState = AppCommandExecuted;
        }
        else if(g_AppState == AppWdsSetDefaultNssai)
        {
            if (g_SetDefultNssai_index == 0)
            {
                memset(&g_setDefaultNssai, 0, sizeof(pack_wds_swi_SetDefaultNssai_t));
            }

            if (strlen(str_return) == 0)
            {
                if (g_SetDefultNssai_index > 0)
                {
                    g_setDefaultNssai.default_nssai_info_len = g_SetDefultNssai_index;
                    SetDefaultNssai(&s_WdsService, &g_setDefaultNssai);
                    g_SetDefultNssai_index = 0;
                    g_AppState = AppCommandExecuted;
                }
                else
                {
                    g_AppState = AppRunning;
                    PrintPrompt();
                }
            }
            else
            {
                if (false == ParceSetDefaultNssaiSettings(str_return, &g_setDefaultNssai.default_nssai_info[g_SetDefultNssai_index]))
                {
                    PrintInvalidArguments();
                    g_AppState = AppCommandExecuted;
                }
                else
                {
                    ++g_SetDefultNssai_index;
                    if (g_SetDefultNssai_index == QMI_WDS_SWI_DEFAULT_MAX_NSSAI_COUNT)
                    {
                        g_setDefaultNssai.default_nssai_info_len = g_SetDefultNssai_index;
                        SetDefaultNssai(&s_WdsService, &g_setDefaultNssai);
                        g_SetDefultNssai_index = 0;
                        g_AppState = AppCommandExecuted;
                    }
                    else
                    {
                        PrintSetDefultNssai();
                    }
                }
            }
        }
        else if(g_AppState == AppWdsGetProfileSnssai)
        {
            pack_wds_swi_GetPrfileSnssai_t getPrfileSnssai;
            getPrfileSnssai.profile_index = atoi(str_return);
            GetProfileSnssai(&s_WdsService, &getPrfileSnssai);
            g_AppState = AppCommandExecuted;
        }
        else if(g_AppState == AppWdsSwiConfigureProfile)
        {            
            uint8_t profileType = 0, profileId = 0;
            uint8_t apn[64];
            uint16_t apnSize = 64;

            wds_profileInfo  curProfile;
            memset(&curProfile, 0, sizeof(wds_profileInfo));

            pack_wds_SLQSCreateProfile_t sCreateProfile;
            memset(&sCreateProfile, 0, sizeof(pack_wds_SLQSCreateProfile_t));
            sCreateProfile.pProfileType = &profileType;
            sCreateProfile.pProfileId = &profileId;
            sCreateProfile.pCurProfile = &curProfile;

            wds_swi_configured_nssai_type s_nassai;
            memset(&s_nassai, 0, sizeof(wds_swi_configured_nssai_type));
            uint8_t ssc = 0;
            uint8_t preferred_access_type = 0;
            uint8_t alwaysOnPduSession = 0;

            if (false == ParceSwiConfigureProfileSNassai(str_return, &sCreateProfile, apn, &apnSize, &s_nassai, &ssc, &preferred_access_type, &alwaysOnPduSession))
            {
                PrintInvalidArguments();
            }
            else
            {
                ConfigureProfileSNssai(&s_WdsService, &sCreateProfile);                
            }
            g_AppState = AppCommandExecuted;
        }        
        else if(g_AppState == AppWdsDeleteProfile)
        {
            pack_wds_SLQSDeleteProfile_t deleteProfile;
            if (!ExtractUInt8Value(str_return, "PT=", ' ', &deleteProfile.profileType) ||
                !ExtractUInt8Value(str_return, "PI=", ' ', &deleteProfile.profileIndex))
            {
                PrintInvalidArguments();
            }
            else
            {
                DeleteProfile(&s_WdsService, &deleteProfile);
            }
            g_AppState = AppCommandExecuted;
        }
        else if(g_AppState == AppWdsClearProfileSnssai)
        {
            pack_wds_swi_ClearProfileSnssai_t clearProfileSnssai;
            clearProfileSnssai.profile_index = atoi(str_return);
            ClearProfileSnssai(&s_WdsService, &clearProfileSnssai);
            g_AppState = AppCommandExecuted;
        }
		else if (g_AppState == AppRunning)
        {
            if (!strcmp(str_return, "1"))
            {
                PrintGetKeepAliveOptions();
            }
            else if (!strcmp(str_return, "2") || !strcmp(str_return, "Reset and modify profile"))
            {
                PrintGetResetAndModifyProfileInfo();
            }
            else if (!strcmp(str_return, "3") || !strcmp(str_return, "Get APN Operator Reserved PCO List"))
            {
                PrintGetApnOpReservedPCO();
            }
            else if (!strcmp(str_return, "4") || !strcmp(str_return, "Get APN MSISDN Information"))
            {
                PrintGetApnMsisdnIfo();
            }
            else if (!strcmp(str_return, "5") || !strcmp(str_return, "Delete All Profiles"))
            {
                PrintDeleteAllProfilesInfo();
            }
            else if (!strcmp(str_return, "6") || !strcmp(str_return, "Get EHRPD Fallback APN List"))
            {
                GetEhrpdFallbackApnList(&s_WdsService);
            }
            else if (!strcmp(str_return, "7") || !strcmp(str_return, "Set EHRPD Fallback APN List"))
            {
                PrintSetEhrpdFallbackApn();
            }
            else if (!strcmp(str_return, "8") || !strcmp(str_return, "Set Modem Assisted Keep Alive Start"))
            {
                PrintSetModemAssitedKAStartInfo();
            }
            else if (!strcmp(str_return, "9") || !strcmp(str_return, "Set Modem Assisted Keep Alive Stop"))
            {
                PrintGetModemAssitedKAStartInfo();
            }
            else if (!strcmp(str_return, "10") || !strcmp(str_return, "Register WDS Event Register"))
            {
                PrintRegisterWdsEventReport();
            }
            else if (!strcmp(str_return, "11") || !strcmp(str_return, "Register WDS Indication Register"))
            {
                PrintIndicationRegister();
            }
            else if (!strcmp(str_return, "12") || !strcmp(str_return, "Get Default Profile ID"))
            {
                PrintGetDefaultProfileIdInfo();
            }
            else if (!strcmp(str_return, "13") || !strcmp(str_return, "Set Default Profile ID"))
            {
                PrintSetDefaultProfileIdInfo();
            }
            else if (!strcmp(str_return, "14") || !strcmp(str_return, "Get 3GPP Configuration Items"))
            {
                Get3GPPConfigItems(&s_WdsService);
            }
            else if (!strcmp(str_return, "15") || !strcmp(str_return, "Set 3GPP Configuration Items"))
            {
                PrintSet3GPPConfigItems();
            }
            else if (!strcmp(str_return, "16") || !strcmp(str_return, "Set Downlink Throughput Report Period"))
            {
                PrintSetDownlinkThroughputReportPeriod();
            }
            else if (!strcmp(str_return, "17") || !strcmp(str_return, "Get Downlink Throughput Reporting Status"))
            {
                QueryDownlinkThroughputReportingStatus(&s_WdsService);
            }
            else if (!strcmp(str_return, "18") || !strcmp(str_return, "Get Current Channel rate"))
            {
                GetCurrentChannelRate(&s_WdsService);
            }
//#ifdef firmware_support
            else if (!strcmp(str_return, "19"))
            {
                GetDefaultNssai(&s_WdsService);
            }
            else if (!strcmp(str_return, "20"))
            {
                PrintSetDefultNssai();
            }
            else if (!strcmp(str_return, "21"))
            {
                PrintGetProfileSnssaiIndex();
            }
            else if (!strcmp(str_return, "22"))
            {
                PrintConfigureProfileSNssai();
            }
            else if (!strcmp(str_return, "23"))
            {
                PrintDeleteProfile();
            }
            else if (!strcmp(str_return, "24"))
            {
                PrintClearProfileSnssaiIndex();
            }
//#endif            
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
    SockPrintf( "  -S  --skipsync\n");
    SockPrintf( "        Skip syncing QMI control IDs\n\n");
    SockPrintf( "  -h  --help  \n" );
    SockPrintf( "        This option prints the usage instructions.\n\n" );
    SockPrintf( "  -V  --version  \n" );
    SockPrintf( "        This option prints app version.\n\n" );
	SockPrintf( "  -o  --operation  \n");
	SockPrintf( "        Automatically perform the specifed action without user interaction.\n"); 
	SockPrintf( "        If the operation has required parameters, they must also be provided.\n");
	SockPrintf( "        Operation-specific parameters will be ignored if the -o flag is not present, or if they are not associated with the specified operation.\n");
	SockPrintf( "        Supported operations: \n");

    PrintWdsCmdListUsage();
}

const char * const s_ShortOptions = "VhmqrsSd:o:e:i:a:p:k:b:f:F:g:G:K:A:B:C:D:E:H:I:J:L:M:N:O:P:1:2:3:4:5:6:7:8:9:n:u:l:t:z:j:w:Q:W:";

const struct option s_LongOptions[] = {
    {"version",  no_argument, NULL, 'V'},
    {"help",   no_argument, NULL, 'h'},
    {"mbim",   no_argument, NULL, 'm'},
    {"qmi",    no_argument, NULL, 'q'},
	{"router", no_argument, NULL, 'r'},
	{"socket", no_argument, NULL, 's'},
	{"skipsync", no_argument, NULL, 'S'},
    {"device", required_argument, NULL, 'd'},
	{"operation", required_argument, NULL, 'o'},
	{"keep-alive-data-session", required_argument, NULL, 'e'},
	{"profile-id", required_argument, NULL, 'i'},
	{"apn", required_argument, NULL, 'a'},
	{"profile-type-mask", required_argument, NULL, 'p'},
	{"keep_alive_type", required_argument, NULL, 'k'},
	{"timer-value", required_argument, NULL, 'b'},
	{"dest-ipv4-address", required_argument, NULL, 'f'},
	{"source-ipv4-address", required_argument, NULL, 'F'},
	{"dest-port", required_argument, NULL, 'g'},
	{"source-port", required_argument, NULL, 'G'},
	{"keep-alive-handle", required_argument, NULL, 'K'},
	{"ccri", required_argument, NULL, 'A'},
	{"tsi", required_argument, NULL, 'B'},
	{"tsim", required_argument, NULL, 'C'},
    {"dbti", required_argument, NULL, 'D'},
	{"dsi", required_argument, NULL, 'E'},
	{"msi", required_argument, NULL, 'H'},
	{"dcsi", required_argument, NULL, 'I'},
	{"cpdsi", required_argument, NULL, 'J'},
	{"epmsi", required_argument, NULL, 'L'},
	{"ufci", required_argument, NULL, 'M'},
	{"apfri", required_argument, NULL, 'N'},
	{"dbtxi", required_argument, NULL, 'O'},
	{"dri", required_argument, NULL, 'P'},
	{"ssi", required_argument, NULL, '1'},
	{"lap", required_argument, NULL, '2'},
	{"rpc", required_argument, NULL, '3'},
	{"aal", required_argument, NULL, '4'},
	{"aap", required_argument, NULL, '5'},
	{"rla", required_argument, NULL, '6'},
	{"apnm", required_argument, NULL, '7'},
	{"rbt", required_argument, NULL, '8'},
	{"rtp", required_argument, NULL, '9'},
    {"always-connect-def-pdn", required_argument, NULL, 'n'},
    {"3gpp-release", required_argument, NULL, 'u'},
    {"lte-attach-profile", required_argument, NULL, 'l'},
	{"profile-family", required_argument, NULL, 't'},
	{"dl_throughput_report_period", required_argument, NULL, 'z'},
	{"profile_index", required_argument, NULL, 'h'},
	{"default_nssai", required_argument, NULL, 'w'},
	{"configure_nssai", required_argument, NULL, 'Q'},
	{"profile_type", required_argument, NULL, 'W'},
	{NULL,     0, NULL,  0 }       /* End of list */
};

static void ParseCommandLine( int argc, char **argv, 
	enum eUserOptions* operation,
	socketWdsCommandParam* cmdParam)
{
    int next_option;

    bool got_operation = false;
    uint8_t got_Params[42] = {0};

    memset(cmdParam, 0, sizeof(socketWdsCommandParam));
    uint8_t profile_family_type = 0;
    char	szApnName[255] = {0};
    uint8_t  ProfileId = 0;
    uint8_t  ProfileIndex = 0;

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
			case 'S':
				g_SkipSync = true;
				break;
			case 'o':
			    *operation = GetWdsCommand(optarg);
                got_operation = true;
				break;
			case 'e':
            //keep-alive-data-session
                cmdParam->enableKA = atoi(optarg);
                got_Params[0] = 1;
            break;
	        case 'i':
            //profile-id                
                ProfileId  = atoi(optarg);
                got_Params[1] = 1;
            break;
	        case 'a':
            //apn
                StrCpy(szApnName, optarg);
                got_Params[2] = 1;
            break;
        	case 'p':
            //profile-type-mask
                cmdParam->sDeleteAllProfiles.ProfileTypeMask = atoll(optarg);
                got_Params[3] = 1;
            break;
        	case 'k':
            //keep_alive_type
                cmdParam->sModemAssistedKaStart.modemAssistedKaStart.keep_alive_type = atoi(optarg);
                got_Params[4] = 1;
            break;
	        case 'b':
            //timer-value
                cmdParam->sModemAssistedKaStart.Timer_value = atoi(optarg);
                cmdParam->sModemAssistedKaStart.modemAssistedKaStart.pTimer_value = &cmdParam->sModemAssistedKaStart.Timer_value; 
                got_Params[5] = 1;
            break;
	        case 'f':
            //dest-ipv4-address
                cmdParam->sModemAssistedKaStart.Dest_ipv4_address = atoi(optarg);
                cmdParam->sModemAssistedKaStart.modemAssistedKaStart.pDest_ipv4_address = &cmdParam->sModemAssistedKaStart.Dest_ipv4_address; 
                got_Params[6] = 1;
            break;
	        case 'F':
            //source-ipv4-address
                cmdParam->sModemAssistedKaStart.Source_ipv4_address = atoi(optarg);
                cmdParam->sModemAssistedKaStart.modemAssistedKaStart.pSource_ipv4_address = &cmdParam->sModemAssistedKaStart.Source_ipv4_address; 
                got_Params[7] = 1;
            break;
	        case 'g':
            //dest-port
                cmdParam->sModemAssistedKaStart.Dest_port = atoi(optarg);
                cmdParam->sModemAssistedKaStart.modemAssistedKaStart.pDest_port = &cmdParam->sModemAssistedKaStart.Dest_port; 
                got_Params[8] = 1;
            break;
	        case 'G':
            //source-port
                cmdParam->sModemAssistedKaStart.Source_port = atoi(optarg);
                cmdParam->sModemAssistedKaStart.modemAssistedKaStart.pSource_port = &cmdParam->sModemAssistedKaStart.Source_port; 
                got_Params[9] = 1;
            break;
	        case 'K':
            //keep-alive-handle
                cmdParam->sModemAssistedKaStop.keep_alive_handle = atoi(optarg);
                got_Params[10] = 1;
            break;
	        case 'A':
            //ccri 
                cmdParam->sWdsSetEventReport.CurrChannelRateInd = atoi(optarg);
                cmdParam->sWdsSetEventReport.wdsSetEventReport.pCurrChannelRateInd = &cmdParam->sWdsSetEventReport.CurrChannelRateInd; 
                got_Params[11] = 1;
            break;
	        case 'B':
            //tsi
                cmdParam->sWdsSetEventReport.TransferStatInd.statsPeriod = atoi(optarg);
                got_Params[12] = 1;
            break;
	        case 'C':
            //tsim
                cmdParam->sWdsSetEventReport.TransferStatInd.statsMask = atoi(optarg);
                got_Params[13] = 1;
            break;
	        case 'D':
            //dbti
                cmdParam->sWdsSetEventReport.DataBearerTechInd = atoi(optarg);
                cmdParam->sWdsSetEventReport.wdsSetEventReport.pDataBearerTechInd = &cmdParam->sWdsSetEventReport.DataBearerTechInd; 
                got_Params[14] = 1;
            break;
	        case 'E':
            //dsi
                cmdParam->sWdsSetEventReport.DormancyStatusInd = atoi(optarg);
                cmdParam->sWdsSetEventReport.wdsSetEventReport.pDormancyStatusInd = &cmdParam->sWdsSetEventReport.DormancyStatusInd; 
                got_Params[15] = 1;
            break;
	        case 'H':
            //msi
                cmdParam->sWdsSetEventReport.MIPStatusInd = atoi(optarg);
                cmdParam->sWdsSetEventReport.wdsSetEventReport.pMIPStatusInd = &cmdParam->sWdsSetEventReport.MIPStatusInd; 
                got_Params[16] = 1;
            break;
	        case 'I':
            //dcsi
                cmdParam->sWdsSetEventReport.DataCallStatusChangeInd = atoi(optarg);
                cmdParam->sWdsSetEventReport.wdsSetEventReport.pDataCallStatusChangeInd = &cmdParam->sWdsSetEventReport.DataCallStatusChangeInd; 
                got_Params[17] = 1;
            break;
	        case 'J':
            //cpdsi
                cmdParam->sWdsSetEventReport.CurrPrefDataSysInd = atoi(optarg);
                cmdParam->sWdsSetEventReport.wdsSetEventReport.pCurrPrefDataSysInd = &cmdParam->sWdsSetEventReport.CurrPrefDataSysInd; 
                got_Params[18] = 1;
            break;
	        case 'L':
            //epmsi
                cmdParam->sWdsSetEventReport.EVDOPageMonPerChangeInd = atoi(optarg);
                cmdParam->sWdsSetEventReport.wdsSetEventReport.pEVDOPageMonPerChangeInd = &cmdParam->sWdsSetEventReport.EVDOPageMonPerChangeInd; 
                got_Params[19] = 1;
            break;
	        case 'M':
            //ufci
                cmdParam->sWdsSetEventReport.UlFlowControlInd = atoi(optarg);
                cmdParam->sWdsSetEventReport.wdsSetEventReport.pUlFlowControlInd = &cmdParam->sWdsSetEventReport.UlFlowControlInd;
                got_Params[20] = 1;
            break;
	        case 'N':
            //apfri
                cmdParam->sWdsSetEventReport.ReportAddPdnFiltersRemoval = atoi(optarg);
                cmdParam->sWdsSetEventReport.wdsSetEventReport.pReportAddPdnFiltersRemoval = &cmdParam->sWdsSetEventReport.ReportAddPdnFiltersRemoval; 
                got_Params[21] = 1;
            break;
	        case 'O':
            //dbtxi
                cmdParam->sWdsSetEventReport.DataBearerTechExtInd = atoi(optarg);
                cmdParam->sWdsSetEventReport.wdsSetEventReport.pDataBearerTechExtInd = &cmdParam->sWdsSetEventReport.DataBearerTechExtInd; 
                got_Params[22] = 1;
            break;
	        case 'P':
            //dri
                cmdParam->sWdsSetEventReport.DormancyResultIndicator = atoi(optarg);
                cmdParam->sWdsSetEventReport.wdsSetEventReport.pDormancyResultIndicator = &cmdParam->sWdsSetEventReport.DormancyResultIndicator; 
                got_Params[23] = 1;
            break;
	        case '1':
            //ssi
                cmdParam->sIndicationRegister.SupperesPktSrvcInd = atoi(optarg);
                cmdParam->sIndicationRegister.indicationRegister.pSupperesPktSrvcInd = &cmdParam->sIndicationRegister.SupperesPktSrvcInd; 
                got_Params[24] = 1;
            break;
	        case '2':
            //lap
                cmdParam->sIndicationRegister.ReportLteAttachPdnListChange = atoi(optarg);
                cmdParam->sIndicationRegister.indicationRegister.pReportLteAttachPdnListChange = &cmdParam->sIndicationRegister.ReportLteAttachPdnListChange; 
                got_Params[25] = 1;
            break;
	        case '3':
            //rpc
                cmdParam->sIndicationRegister.ReportProfileChangeEvents = atoi(optarg);
                cmdParam->sIndicationRegister.indicationRegister.pReportProfileChangeEvents = &cmdParam->sIndicationRegister.ReportProfileChangeEvents; 
                got_Params[26] = 1;
            break;
	        case '4':
            //aal
                cmdParam->sIndicationRegister.ReportRoamingApnList = atoi(optarg);
                cmdParam->sIndicationRegister.indicationRegister.pReportRoamingApnList = &cmdParam->sIndicationRegister.ReportRoamingApnList; 
                got_Params[27] = 1;
            break;
	        case '5':
            //aap
                cmdParam->sIndicationRegister.ReportApnParamChangeInfo = atoi(optarg);
                cmdParam->sIndicationRegister.indicationRegister.pReportApnParamChangeInfo = &cmdParam->sIndicationRegister.ReportApnParamChangeInfo; 
                got_Params[28] = 1;
            break;
	        case '6':
            //rla
                cmdParam->sIndicationRegister.ReportLteAttachParams = atoi(optarg);
                cmdParam->sIndicationRegister.indicationRegister.pReportLteAttachParams = &cmdParam->sIndicationRegister.ReportLteAttachParams; 
                got_Params[29] = 1;
            break;
	        case '7':
            //apnm
                cmdParam->sIndicationRegister.ReportMsisdnInfoChange = atoi(optarg);
                cmdParam->sIndicationRegister.indicationRegister.pReportMsisdnInfoChange = &cmdParam->sIndicationRegister.ReportMsisdnInfoChange; 
                got_Params[30] = 1;
            break;
	        case '8':           
            //rbt
                cmdParam->sIndicationRegister.ReportBearerType = atoi(optarg);
                cmdParam->sIndicationRegister.indicationRegister.pReportBearerType = &cmdParam->sIndicationRegister.ReportBearerType; 
                got_Params[31] = 1;
            break;
	        case '9':
            //rtp
                cmdParam->sIndicationRegister.ReportPdnThrottleInfo = atoi(optarg);
                cmdParam->sIndicationRegister.indicationRegister.pReportPdnThrottleInfo = &cmdParam->sIndicationRegister.ReportPdnThrottleInfo; 
                got_Params[32] = 1;
            break;                        
            case 't':
            //profile-family
                cmdParam->sGetDefaultProfileNum.type = 0; //3GPP
                profile_family_type = atoi(optarg);
                got_Params[33] = 1;
            break;
            case 'n':
                cmdParam->sSet3GPPConfigItem.DefaultPDNEnabled = atoi(optarg);
                got_Params[34] = 1;
            break;
            case 'u':
                cmdParam->sSet3GPPConfigItem.Release3gpp = atoi(optarg);
                got_Params[35] = 1;
            break;
            case 'l':
                cmdParam->sSet3GPPConfigItem.LTEAttachProfileList[0] = atoi(optarg);
                got_Params[36] = 1;
            break;
	        case 'z':
            //dl_throughput_report_period
                cmdParam->Downlink_throughput_report_period = atoi(optarg); 
                got_Params[37] = 1;
            break;
	        case 'j':
            //profile_index
                ProfileIndex = atoi(optarg);
                got_Params[39] = 1;
            break;
	        case 'w':
            //default_nssai
                StrCpy(cmdParam->default_nssai_str, optarg); 
                got_Params[38] = 1;
            break;
	        case 'Q':
            //configure profile nssai
                StrCpy(cmdParam->configure_nssai_str, optarg); 
                got_Params[40] = 1;
            break;
	        case 'W':
            //profile_type
                cmdParam->sDeleteProfile.profileType = atoi(optarg); 
                got_Params[41] = 1;
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
        SockPrintf (ANSI_COLOR_RED);
        switch(*operation)
		{
		case eSET_KEEP_ALIVE_DATA_SESSION:
			if (got_Params[0] == 0)
			{ 
				SockPrintf("\nError: SetKeepAliveDataSession operation missing keep-alive-data-session parameter\n");
				exit(EXIT_FAILURE);
			}
        break;        
		case eSET_RESET_MODIFY_PROFILE_SEETING:
			if (got_Params[1] == 0)
			{ 
				SockPrintf("\nError: ResetAndModifyProfileSettings operation missing profile-id parameter\n");
				exit(EXIT_FAILURE);
			}
            cmdParam->ProfileId = ProfileId;
        break;        
		case eGET_APN_OP_RESERVED_PCO:
			if (got_Params[2] == 0)
			{ 
				SockPrintf("\nError: GetApnOpReservedPcoList operation missing apn parameter\n");
				exit(EXIT_FAILURE);
			}
            StrCpy(cmdParam->ApnName, szApnName);
        break;        
		case eGET_APN_MSISDN_INFO:
			if (got_Params[2] == 0)
			{ 
				SockPrintf("\nError: GetApnMsisdnInfo operation missing apn parameter\n");
				exit(EXIT_FAILURE);
			}
            StrCpy(cmdParam->ApnName, szApnName);
        break;        
		case eSET_DELETE_ALL_PROFILES:
			if (got_Params[3] == 0)
			{ 
				SockPrintf("\nError: DeleteAllProfiles operation missing profile-type-mask parameter\n");
				exit(EXIT_FAILURE);
			}
        break;
		case eGET_EHRPD_FALLBACK_APN:
        break;
		case eSET_EHRPD_FALLBACK_APN:
			if (got_Params[2] == 0)
			{ 
				SockPrintf("\nError: SetEhrpdFallbackApnList operation missing apn parameter\n");
				exit(EXIT_FAILURE);
			}
        break;        
		case eSET_MODEM_ASSISTED_KA_START:
            //At least one optional parameter must be set.
			if (got_Params[4] == 0)
			{ 
				SockPrintf("\nError: SetModemAssistedKaStart operation missing keep_alive_type parameter\n");
				exit(EXIT_FAILURE);
			}
			if (got_Params[2] == 0 && got_Params[5] == 0 && got_Params[6] == 0 && got_Params[7] == 0 && got_Params[8] == 0 && got_Params[9] == 0)
            {
				SockPrintf("\nError: SetModemAssistedKaStart operation must have at least one optional parameter\n");
				exit(EXIT_FAILURE);
            }
            StrCpy(cmdParam->sModemAssistedKaStart.ApnName, szApnName);
        break;        
		case eSET_MODEM_ASSISTED_KA_STOP:
			if (got_Params[10] == 0)
			{ 
				SockPrintf("\nError: SetModemAssistedKaStop operation missing keep-alive-handle parameter\n");
				exit(EXIT_FAILURE);
			}
        break;        
		case eSET_EVENT_REGISTER:            
            if (got_Params[12] == 1 && got_Params[13] == 1)
            {
                cmdParam->sWdsSetEventReport.wdsSetEventReport.pTransferStatInd = &cmdParam->sWdsSetEventReport.TransferStatInd;
            }
        break;        
		case eSET_INDICATION_REGISTER:
			if (got_Params[2] == 0 && got_Params[24] == 0 && got_Params[25] == 0 && got_Params[26] == 0 && got_Params[27] == 0 && got_Params[28] == 0 && 
                got_Params[29] == 0 && got_Params[30] == 0 && got_Params[31] == 0 && got_Params[32] == 0 )
			{
				SockPrintf("\nError: RegisterWdsIndicationRegister operation at least one parameter required\n\n");
				exit(EXIT_FAILURE);
			}
            StrCpy(cmdParam->sIndicationRegister.ApnName, szApnName);
            cmdParam->sIndicationRegister.ApnNameLen = strlen(szApnName);
            cmdParam->sIndicationRegister.indicationRegister.pApnName = cmdParam->sIndicationRegister.ApnName;
            cmdParam->sIndicationRegister.indicationRegister.pApnNameLen = &cmdParam->sIndicationRegister.ApnNameLen;
        break;        
		case eGET_DEFAULT_PROFILE_ID:
			if (got_Params[33] == 0)
			{ 
				SockPrintf("\nError: GetDefaultProfileId operation missing profile_family_type parameter\n\n");
				exit(EXIT_FAILURE);
			}
            cmdParam->sGetDefaultProfileNum.family = profile_family_type;

        break;        
		case eSET_DEFAULT_PROFILE_ID:
			if (got_Params[1] == 0)
			{ 
				SockPrintf("\nError: SetDefaultProfileId operation missing profile-id parameter\n\n");
				exit(EXIT_FAILURE);
			}
			if (got_Params[33] == 0)
			{ 
				SockPrintf("\nError: SetDefaultProfileId operation missing profile_family_type parameter\n\n");
				exit(EXIT_FAILURE);
			}
            cmdParam->sSetDefaultProfileNum.index = ProfileId;
            cmdParam->sSetDefaultProfileNum.family = profile_family_type;
        break;
        case eSET_3GPP_CONFIG_ITEMS:
			if (got_Params[1] == 0 && got_Params[34] == 0 && got_Params[35] == 0 && got_Params[1] == 36)
			{ 
				SockPrintf("\nError: Set3GPPConfigItems operation no parameter\n\n");
				exit(EXIT_FAILURE);
			}
            cmdParam->sSet3GPPConfigItem.set3GPPConfigItem.pLTEAttachProfile = NULL;
            cmdParam->sSet3GPPConfigItem.set3GPPConfigItem.LTEAttachProfileListLen = 1;
			if (got_Params[1] == 1)
            {
                cmdParam->sSet3GPPConfigItem.ProfileList[0] = ProfileId;
                cmdParam->sSet3GPPConfigItem.set3GPPConfigItem.pProfileList = cmdParam->sSet3GPPConfigItem.ProfileList;
            }
			if (got_Params[34] == 1)
            {
                cmdParam->sSet3GPPConfigItem.set3GPPConfigItem.pDefaultPDNEnabled = &cmdParam->sSet3GPPConfigItem.DefaultPDNEnabled;
            }
			if (got_Params[35] == 1)
            {
                cmdParam->sSet3GPPConfigItem.set3GPPConfigItem.p3gppRelease = &cmdParam->sSet3GPPConfigItem.Release3gpp;
            }
			if (got_Params[36] == 1)
            {
                cmdParam->sSet3GPPConfigItem.set3GPPConfigItem.pLTEAttachProfileList = cmdParam->sSet3GPPConfigItem.LTEAttachProfileList;
            }
        break;
		case eSET_DOWNLINK_THROUGHPUT_REPORT_PERIOD:
			if (got_Params[37] == 0)
			{ 
				SockPrintf("\nError: SetDownlinkThroughputReportPeriod operation missing dl_throughput_report_period parameter\n\n");
				exit(EXIT_FAILURE);
			}
        break;        
		case eGET_DOWNLINK_THROUGHPUT_REPORTING_STATUS:
        break;        
		case eGET_CURRENT_CHANNEL_RATE:
    	case eGET_DEFAULT_NSAAI:
        break;
	    case eSET_DEFAULT_NSAAI:
            if (got_Params[38] == 0)
			{ 
				SockPrintf("\nError: SetDefaultNssai operation missing default_nssai parameter\n\n");
				exit(EXIT_FAILURE);
			}
        break;
	    case eGET_PROFILE_SNSAAI:
            if (got_Params[39] == 0)
			{ 
				SockPrintf("\nError: GetProfileSnssai operation missing profile_index parameter\n\n");
				exit(EXIT_FAILURE);
			}
            cmdParam->Profile_index = ProfileIndex; 
        break;
        case eSET_CONFIGURE_PROFILE_SNSAAI:
            if (got_Params[40] == 0)
			{ 
				SockPrintf("\nError: ConfigureProfileSnssai operation missing configure_nssai (-Q) parameter\n\n");
				exit(EXIT_FAILURE);
			}
        break;        
        case eSET_DELETE_PROFILE:
            if (got_Params[41] == 0)
			{ 
				SockPrintf("\nError: DeleteProfile operation missing profile_type (-W) parameter\n\n");
				exit(EXIT_FAILURE);
			}
            if (got_Params[39] == 0)
			{ 
				SockPrintf("\nError: DeleteProfile operation missing profile_index parameter\n\n");
				exit(EXIT_FAILURE);
			}
            cmdParam->sDeleteProfile.profileIndex = ProfileIndex; 
        break;
	    case eSET_CLEAR_PROFILE_SNSAAI:
            if (got_Params[39] == 0)
			{ 
				SockPrintf("\nError: ClearProfileSnssai operation missing profile_index parameter\n\n");
				exit(EXIT_FAILURE);
			}
            cmdParam->Profile_index = ProfileIndex; 
        break;
		default:
			break;
        }
        SockPrintf (ANSI_COLOR_RESET);
	}
}

int main(int argc, char **argv)
{
	int ret = FAILURE;
	bool bPCIe = false;
	g_PrintVersion = false;

   	enum eUserOptions operation = eUNKNOWN;
	socketWdsCommandParam cmdParam;
    memset(&cmdParam, 0, sizeof(socketWdsCommandParam));
    ParseCommandLine(argc, argv, &operation, &cmdParam);

    if (g_PrintVersion)
    {
        SockPrintf("\n%s v%s\n\n", APPNAME, VERSION);
       	if (argc == 2)
		    return 0;
    }

    memset(&s_Transport, 0, sizeof(QmuxTransport));
    memset(&s_CtlService, 0, sizeof(CtlService));

    if (OpenTransport(&s_Transport, g_DevicePath, sizeof(g_DevicePath), &g_mode, &bPCIe, NULL,
		true, PrintUsageManual, argv[0], false) != 0)
		return 0;

	if (CtlService_InitializeEx(&s_CtlService, &s_Transport, g_SkipSync, 1) != SUCCESS)
		SockPrintf("CtlService_InitializeEx failed\n");
	else
	{
		memset(&s_WdsService, 0, sizeof(QmiService));

        // We use the Ctl service to initialize the regular services because it knows how to 
        // acquire client IDs for them.

        // Use a do/while for easy exit. We have to clean up.
        do
        {
            // Infrastructure is now ready. Let's create some regular QMI services.

            ret = CtlService_InitializeRegularService(&s_CtlService, &s_WdsService, eWDS, WdsIndicationCallback, NULL);
            if (ret != SUCCESS)
            {
                SockPrintf("InitializeRegularService eWDS failed.\n");
                break;
            }
            g_AppState = AppRunning;

            enable_profile_change_notification(&s_WdsService, 1);
            
			if (g_socketServer)
			{
				ExecuteWdsSocketTestCase("/tmp/qmiwds-server-socket", &cmdParam);
			}
			else if (operation == eUNKNOWN)
			{
				ExecuteWdsTestCaseSelection();
			}
			else
			{
				ExecuteWdsTestCase(operation, &cmdParam);
			}

            enable_profile_change_notification(&s_WdsService, 0);
        } while (0);		

        // Shut down.
        g_AppState = AppShuttingDown;

        CtlService_ShutDownRegularService(&s_CtlService, &s_WdsService);

        CtlService_ShutDown(&s_CtlService);
    }

	QmuxTransport_ShutDown(&s_Transport);
	
	return ret;
}
