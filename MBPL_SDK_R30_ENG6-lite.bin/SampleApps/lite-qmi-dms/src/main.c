#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <syslog.h>
#include <stdlib.h>
#include <getopt.h>
#include "common.h"
#include "ctl.h"
#include "dms.h"
#include "swidms.h"
#include "fms.h"
#include "lite-qmi-dms.h"
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

void WaitForDevices(int timeOut, enum eUserOptions operation, socketDmsCommandParam* cmdParam);

extern void dms_indication_handler(uint16_t msgid, uint8_t *msg, uint32_t rlen);

extern void GetMsisdn(QmiService* pQmiService);
extern void GetFirmwareInformation(QmiService* pQmiService);
extern void GetSerialNumber(QmiService* pQmiService);
extern void GetModelID(QmiService* pQmiService);
extern void GetFsn(QmiService* pQmiService);
extern void GetDeviceCapabilities(QmiService* pQmiService);
extern void GetBandCapability(QmiService* pQmiService);
extern void GetManufacturer(QmiService* pQmiService);
extern void GetSwiHostDevInfo(QmiService* pQmiService);
extern void SetSwiHostDevInfo(QmiService* pQmiService, pack_dms_SLQSSwiSetHostDevInfo_t *pSwiSetHostDevInfo);
extern void SetEventReport(QmiService* pQmiService, pack_dms_SetEventReport_t *pSetEventReport);
extern void GetStoredImages(QmiService * pQmiService);
extern void SlqsGetStoredImages(QmiService * pQmiService);
extern void DeleteStoredImage(QmiService * pQmiService, pack_fms_DeleteStoredImage_t * pDeleteStoredImage);
extern void SetPower(QmiService* pQmiService, pack_dms_SetPower_t *pSetPower);
extern void GetPower(QmiService* pQmiService);
extern void GetAutoSimList(QmiService* pQmiService, pack_swidms_SLQSSwiDmsGetAutoSimList_t *pSwiDmsGetAutoSimList);
extern void SetAutoSimList(QmiService* pQmiService, pack_swidms_SLQSSwiDmsSetAutoSimList_t *pSwiDmsGetAutoSimList);
extern void GetCustomFeaturesV2(QmiService* pQmiService);
extern void SetCustomFeaturesV2(QmiService* pQmiService, pack_dms_SetCustFeaturesV2_t *pSetCustomFeatures);
extern void GetSdkVersion();

static CtlService s_CtlService;
static QmiService s_DmsService;
static QmiService s_SwiDmsService;
static QmuxTransport s_Transport;

//Set Auto-SIM List
static char s_carrier[QMI_SWI_DMS_AUTO_SIM_CARRIER_NAME_MAX+1];
static swi_dms_auto_sim_attributes_type_t s_Attributes;
static bool g_bExitLoop = false;

//////////////////////////////////////////////////////////
static void PrintSetSwiHostDevInfo();
static void PrintSetEventReport();
static void PrintSetPower();

enum AppStateType g_AppState = AppUninitialized;

#define DEVICE_PATH_MAX 256
char g_DevicePath[DEVICE_PATH_MAX]={0};
char g_ProcName[MAX_PATH_LEN]={0};

bool g_PrintVersion = false;
int g_mode = QMUX_INTERFACE_UNKNOWN;
bool g_socketServer = false;

#define APPNAME "lite-qmi-dms"
#define VERSION "1.0.2210.0"

#define MILLISECOND    1000
#define SECOND        (1000*MILLISECOND)

///////////////////////////////////////////////////
static void DmsIndicationCallback(uint8_t* qmiPacket, uint16_t qmiPacketSize, void* pIndicationCallbackContext)
{
	(void)pIndicationCallbackContext;

	unpack_qmi_t rsp_ctx;
	printf(ANSI_COLOR_YELLOW);
	SockPrintf("<< receiving dms indication: %s\n", helper_get_resp_ctx(eDMS, qmiPacket, qmiPacketSize, &rsp_ctx));
	SockPrintf("msgid 0x%x, type:%x\n", rsp_ctx.msgid,rsp_ctx.type);
	printf(ANSI_COLOR_RESET);
	dms_indication_handler(rsp_ctx.msgid, qmiPacket,  qmiPacketSize);
}

static void PrintDeleteStoredImage()
{
    fprintf(stderr, "\nPlease enter information of the image to be deleted:\n"\
                    "\nType(0: Modem, 1: PRI)= ImageID= BuildID=\n"\
                    "\nex. Type=1 ImageID=002.007_000 BuildID=01.08.04.00_?\n"\
                    "  Or Press<Enter> to go to previous menu:\n");
    g_AppState = AppDeleteStoredImage;
}

static void PrintSetSwiHostDevInfo()
{
    fprintf( stderr, "\nPlease enter SWI Host Dev Info [all params optional]:\n"\
                     "\nManufacturer=,Model=,Version=,PlasmaID=,HostID=,Instance=\n"\
                     "\nex. Manufacturer=Sierra Wireless,Model=SDX55,Version=05.05.58.00,PlasmaID=PL110,HostID=SWI\n"\
                     "  Or Press<Enter> to go to previous menu:\n");
    g_AppState = AppSetSwiHostDevInfo;
}

static void PrintSetEventReport()
{
    fprintf( stderr, "\nPlease enter Set Event Report Mode(0: reset 1: set 2: no change):\n"\
                     "  Or Press<Enter> to go to previous menu:\n");
    g_AppState = AppSetEventReport;
}

static void PrintSetPower()
{
    fprintf( stderr, "\nPlease enter Power Mode(0- Online 1- Low power 2- Factory Test mode 3- Offline 4- Resetting 5- Shutting down\n"\
                     "6- Persistent low power 7- Mode-only low power 8- Conducting network test for GSM/WCDMA 9- Camp only\n"\
                     "  Or Press<Enter> to go to previous menu:\n");
    g_AppState = AppSetPower;
}

static void PrintCarrierName()
{
    fprintf(stderr, "\nPlease enter carrier name to get the carrier Auto-SIM List:\n"\
                    "  Or Press<Enter> to get list for all carriers:\n");
    g_AppState = AppGetAutoSimList;
}

static void PrintSetAutoSimList()
{
    fprintf(stderr, "\nPlease enter carrier name to set the carrier auto-SIM attributes:\n"\
                    "  Or Press<Enter> to go to previous menu:\n");
    g_AppState = AppSetAutoSimList;
}

static void PrintSetAutoSimListAttributes()
{
    fprintf(stderr, "\nPlease enter attribute (type=(0|1) key=(ICCID (first 7 digit)|MCC:MNC) rank=(1-127|255) subpri=xx:\n"\
                    "  ex1. type=0 key=8930272 rank=1 subpri=1\n"\
                    "  ex2. type=1 key=302:720 rank=2 subpri=255\n"\
                    "  Or type \"del\" to delete all custom entries of the specified carrier\n"\
                    "  Or Press<Enter> to go to previous menu:\n\n");
    g_AppState = AppSetAutoSimList2;
}

static void PrintSetCustomFeatures()
{
    fprintf( stderr, "\nPlease enter Custom Feature to set\n"\
                     "  Or Press<Enter> to go to previous menu:\n");
    g_AppState = AppSetCustomFeatures;
}

static void ExecuteDmsTestCase(enum eUserOptions operation, socketDmsCommandParam* cmdParam)
{
	switch (operation)
	{
	case eGET_MODEL_ID:
		GetModelID(&s_DmsService);
		break;
	case eGET_FSN:
		GetFsn(&s_DmsService);
		break;
	case eGET_DEV_CAP:
		GetDeviceCapabilities(&s_DmsService);
		break;
	case eGET_BAND_CAP:
		GetBandCapability(&s_DmsService);
		break;
	case eGET_DEV_MANUFACTURER:
		GetManufacturer(&s_DmsService);
		break;
	case eGET_MSISDN:
		GetMsisdn(&s_DmsService);
		break;
	case eGET_FW_INFO:
		GetFirmwareInformation(&s_DmsService);
		break;
	case eGET_MEID_IMEI:
		GetSerialNumber(&s_DmsService);
		break;
	case eGET_SWI_HOST_DEV_INFO:
		GetSwiHostDevInfo(&s_DmsService);
		break;
	case eSET_SWI_HOST_DEV_INFO:
		SetSwiHostDevInfo(&s_DmsService, &cmdParam->sSetHostDevInfo.packdmsSLQSSwiSetHostDevInfo);
		break;
	case eGET_STORED_IMAGES:
		GetStoredImages(&s_DmsService);
		break;
	case eSLQS_GET_STORED_IMAGES:
		SlqsGetStoredImages(&s_DmsService);
		break;
	case eDEL_STORED_IMAGES:
		DeleteStoredImage(&s_DmsService, &cmdParam->packfmsDeleteStoredImage);
		break;
	case eSET_POWER:
		SetPower(&s_DmsService, &cmdParam->sSetPower);
		break;
	case eGET_POWER:
		GetPower(&s_DmsService);
		break;
	case eGET_AUTO_SIM_LIST:
		GetAutoSimList(&s_SwiDmsService, &cmdParam->getAutoSimList);
		break;
	case eSET_AUTO_SIM_LIST:
		SetAutoSimList(&s_SwiDmsService, &cmdParam->sSetAutoSimList.setAutoSimList);
		break;
	case eGET_CUST_FEATURES:
		GetCustomFeaturesV2(&s_DmsService);
		break;
	case eSET_CUST_FEATURES:
		SetCustomFeaturesV2(&s_DmsService, &cmdParam->sSetCustomFeatures);
		break;
	case eGET_SDK_VERSION:
		GetSdkVersion();
		break;
	default:
		break;
	}
}

void ExecuteDmsSocketTestCase(const char* socketName, socketDmsCommandParam* cmdParam)
{
	if (OpenSocket(socketName) == 0)
		return;

	while (1)
	{
		int op = GetDmsSocketCommand(APPNAME, cmdParam);
		if (op == eEXIT)
			break;

		ExecuteDmsTestCase(op, cmdParam);
	}

	CloseSocket();
}

void ExecuteDmsTestCaseSelection(void)
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
            case AppCommandWaitForDevice:
                StrCpy(str_return, "q\n");
            break;
            case AppGetAutoSimList:
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
            if(g_AppState == AppCommandWaitForDevice)
                SockPrintf("Waiting for the device...\n");
            else
			    SockPrintf("quitting...\n");
			break;
		} 
        else if (!strcmp(str_return, "d"))
		{
			PrintPrompt();
		}
        else if (g_AppState == AppDeleteStoredImage)
        {
            // Type=,ImageID=,BuildID=
            pack_fms_DeleteStoredImage_t packfmsDeleteStoredImage;
            memset(&packfmsDeleteStoredImage, 0, sizeof(pack_fms_DeleteStoredImage_t));

            sscanf(str_return, "Type=%hhu ImageID=%99s BuildID=%99s", &packfmsDeleteStoredImage.ImageInfo.imageType,
                packfmsDeleteStoredImage.ImageInfo.imageId, packfmsDeleteStoredImage.ImageInfo.buildId);
            packfmsDeleteStoredImage.ImageInfo.buildIdLength = (uint8_t)strlen((char *)packfmsDeleteStoredImage.ImageInfo.buildId);

            DeleteStoredImage(&s_DmsService, &packfmsDeleteStoredImage);

            g_AppState = AppCommandExecuted;
        }
        else if (g_AppState == AppSetSwiHostDevInfo)
        {
            //Manufacturer=,Model=,Version=,PlasmaID=,HostID=,Instance=
	        pack_dms_SLQSSwiSetHostDevInfo_t packdmsSLQSSwiSetHostDevInfo;
            memset(&packdmsSLQSSwiSetHostDevInfo, 0, sizeof(pack_dms_SLQSSwiSetHostDevInfo_t));
            
			ExtractSubStringValue(str_return, "Manufacturer=", ',', packdmsSLQSSwiSetHostDevInfo.manString, sizeof(packdmsSLQSSwiSetHostDevInfo.manString));
			ExtractSubStringValue(str_return, "Model=", ',', packdmsSLQSSwiSetHostDevInfo.modelString, sizeof(packdmsSLQSSwiSetHostDevInfo.modelString));
			ExtractSubStringValue(str_return, "Version=", ',', packdmsSLQSSwiSetHostDevInfo.swVerString, sizeof(packdmsSLQSSwiSetHostDevInfo.swVerString));
			ExtractSubStringValue(str_return, "PlasmaID=", ',', packdmsSLQSSwiSetHostDevInfo.plasmaIDString, sizeof(packdmsSLQSSwiSetHostDevInfo.plasmaIDString));
			ExtractSubStringValue(str_return, "HostID=", ',', packdmsSLQSSwiSetHostDevInfo.hostID, sizeof(packdmsSLQSSwiSetHostDevInfo.hostID));

            uint8_t inst = 1;
			if (ExtractUInt8Value(str_return, "Instance=", ',', & inst))
                packdmsSLQSSwiSetHostDevInfo.pInstance = &inst;
            
            SetSwiHostDevInfo(&s_DmsService, &packdmsSLQSSwiSetHostDevInfo);

            g_AppState = AppCommandExecuted;
        }
        else if (g_AppState == AppSetEventReport)
        {
            pack_dms_SetEventReport_t sSetEventReport;
            sSetEventReport.mode = 0xFF;
            sSetEventReport.mode = atoi(str_return);

            if (sSetEventReport.mode > 2)
               	SockPrintf("\nInvalid argument\n");
            else
                SetEventReport (&s_DmsService, &sSetEventReport);

            g_AppState = AppCommandExecuted;
            PrintPrompt();
        }
        else if (g_AppState == AppSetPower)
        {
            pack_dms_SetPower_t sSetPower;
            sSetPower.mode = 0xFF;
            sSetPower.mode = atoi(str_return);

            if (sSetPower.mode > 9)
               	SockPrintf("\nInvalid argument\n");
            else
                SetPower (&s_DmsService, &sSetPower);

            g_AppState = AppCommandExecuted;
        }
        else if(g_AppState == AppGetAutoSimList)
        {
            uint32_t strLen = strlen(str_return); 
            pack_swidms_SLQSSwiDmsGetAutoSimList_t getAutoSimList;
            memset (&getAutoSimList, 0, sizeof(getAutoSimList));

            if (strLen > QMI_SWI_DMS_AUTO_SIM_CARRIER_NAME_MAX)
               	SockPrintf("\nCarrier name is too long\n");
            else if (strLen > 0)
            {
				StrCpy(getAutoSimList.carrier, str_return);
                GetAutoSimList(&s_SwiDmsService, &getAutoSimList);
            }
            else
            {
                GetAutoSimList(&s_SwiDmsService, &getAutoSimList);
            }
            g_AppState = AppCommandExecuted;
        }
        else if(g_AppState == AppSetAutoSimList)
        {
            memset (&s_Attributes, 0, sizeof(swi_dms_auto_sim_attributes_type_t));
            memset (s_carrier, 0, sizeof(s_carrier));

            uint32_t strLen = strlen(str_return); 
            if (strLen > QMI_SWI_DMS_AUTO_SIM_CARRIER_NAME_MAX)
            {
               	SockPrintf("\nCarrier name is too long\n");
                g_AppState = AppCommandExecuted;
            }
            else
            {
				StrCpy(s_carrier, str_return);
                PrintSetAutoSimListAttributes();
            }
        }
        else if(g_AppState == AppSetAutoSimList2)
        {
            uint32_t strLen = strlen(str_return);
            if (strLen == 0)
            {
                g_AppState = AppCommandExecuted;
            }
            else if (strLen == 3 && StrCpy(str_return, "del")) //delete attributes
            {
                pack_swidms_SLQSSwiDmsSetAutoSimList_t setAutoSimList;
                memset(&setAutoSimList, 0, sizeof(setAutoSimList));
				StrCpy(setAutoSimList.carrier, s_carrier);
                SetAutoSimList(&s_SwiDmsService, &setAutoSimList);
                g_AppState = AppCommandExecuted;
            }
            else
            {
                //type=0 key=8930272 rank=1 subpri=1
                //type=1 key=302:720 rank=1 subpri=1
                char *pType = strstr(str_return, "type=");
                char *pKey = strstr(str_return, "key=");
                char *pRank = strstr(str_return, "rank=");
                char *pSubpri = strstr(str_return, "subpri=");
                if (!pType || !pKey || !pRank || !pSubpri)
                {
                    SockPrintf("\nInvalid arguments\n");
                    g_AppState = AppCommandExecuted;
                }
                else
                {
                    pType += 5;
                    s_Attributes.type = atoi( pType );
                    pKey += 4;
                    pRank += 5;
                    StrNCpy(s_Attributes.key, pKey, pRank - pKey - 6 );
                    s_Attributes.key_len = strlen(s_Attributes.key);
                    if (s_Attributes.key_len == 7)
                    {
                        s_Attributes.rank = atoi(pRank);
                        pSubpri += 7;
                        s_Attributes.subpri = atoi(pSubpri);

                        pack_swidms_SLQSSwiDmsSetAutoSimList_t setAutoSimList;
                        memset(&setAutoSimList, 0, sizeof(setAutoSimList));
						StrCpy(setAutoSimList.carrier, s_carrier);
                        setAutoSimList.pAttributes = &s_Attributes;
                        SetAutoSimList(&s_SwiDmsService, &setAutoSimList);
                        g_AppState = AppCommandExecuted;
                    }
                    else
                    {
                        SockPrintf("\nInvalid key size\n");
                        g_AppState = AppCommandExecuted;
                    }
                }
            }
        }
        else if (g_AppState == AppSetCustomFeatures)
        {
			//<ID>=value
			char *pCharEnd = strstr(str_return, "=");
			if (!pCharEnd)
				SockPrintf("\nInvalid argument\n");
			else
			{
				pack_dms_SetCustFeaturesV2_t sSetCustomFeatures;
				memset(&sSetCustomFeatures, 0, sizeof(pack_dms_SetCustFeaturesV2_t));

				strncpy_s((char*)sSetCustomFeatures.cust_id, DMS_MAX_CUST_ID_LEN, str_return, pCharEnd - str_return);
				sSetCustomFeatures.value_length = 1;
				sSetCustomFeatures.cust_value[0] = atoi(++pCharEnd);

				SetCustomFeaturesV2(&s_DmsService, &sSetCustomFeatures);
			}

            g_AppState = AppCommandExecuted;
        }
		else if (g_AppState == AppRunning)
        {
			switch (GetDmsCommand(str_return))
			{
			case eGET_MODEL_ID:
				GetModelID(&s_DmsService);
				break;
			case eGET_FSN:
				GetFsn(&s_DmsService);
				break;
			case eGET_DEV_CAP:
				GetDeviceCapabilities(&s_DmsService);
				break;
			case eGET_BAND_CAP:
				GetBandCapability(&s_DmsService);
				break;
			case eGET_DEV_MANUFACTURER:
				GetManufacturer(&s_DmsService);
				break;
			case eGET_MSISDN:
				GetMsisdn(&s_DmsService);
				break;
			case eGET_FW_INFO:
				GetFirmwareInformation(&s_DmsService);
				break;
			case eGET_MEID_IMEI:
				GetSerialNumber(&s_DmsService);
				break;
			case eGET_SWI_HOST_DEV_INFO:
				GetSwiHostDevInfo(&s_DmsService);
				break;
			case eSET_SWI_HOST_DEV_INFO:
				PrintSetSwiHostDevInfo();
				break;
			case eSET_EVENT_REPORT:
				PrintSetEventReport();
				break;
			case eGET_STORED_IMAGES:
				GetStoredImages(&s_DmsService);
				break;
			case eSLQS_GET_STORED_IMAGES:
				SlqsGetStoredImages(&s_DmsService);
				break;
			case eDEL_STORED_IMAGES:
				PrintDeleteStoredImage();
				break;
			case eSET_POWER:
				PrintSetPower();
				break;
			case eGET_POWER:
				GetPower(&s_DmsService);
				g_AppState = AppCommandExecuted;
				break;
			case eGET_AUTO_SIM_LIST:
				PrintCarrierName();
				break;
			case eSET_AUTO_SIM_LIST:
				PrintSetAutoSimList();
				break;
			case eGET_CUST_FEATURES:
				GetCustomFeaturesV2(&s_DmsService);
				g_AppState = AppCommandExecuted;
				break;
			case eSET_CUST_FEATURES:
				PrintSetCustomFeatures();
				break;
			case eGET_SDK_VERSION:
				GetSdkVersion();
				break;
			default:
				break;
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
	SockPrintf( "  -o  --operation  \n");
	SockPrintf( "        Automatically perform the specifed action without user interaction.\n"); 
	SockPrintf( "        If the operation has required parameters, they must also be provided.\n");
	SockPrintf("        Operation-specific parameters will be ignored if the -o flag is not present, or if they are not associated with the specified operation.\n");
	SockPrintf( "        Supported operations: \n");

	PrintDmsCmdListUsage();
}

const char * const s_ShortOptions = "Vhmqrsd:o:u:M:v:p:H:i:t:I:b:P:c:k:R:S:f:T:";

const struct option s_LongOptions[] = {
    {"version",  no_argument, NULL, 'V'},
    {"help",   no_argument, NULL, 'h'},
    {"mbim",   no_argument, NULL, 'm'},
    {"qmi",    no_argument, NULL, 'q'},
	{"router", no_argument, NULL, 'r'},
	{"socket", no_argument, NULL, 's'},
    {"device", required_argument, NULL, 'd'},
	{"operation", required_argument, NULL, 'o'},
	{"manufacturer", required_argument, NULL, 'u'},
	{"model", required_argument, NULL, 'M'},
	{"version", required_argument, NULL, 'v'},
	{"plasmaId", required_argument, NULL, 'p'},
	{"hostId", required_argument, NULL, 'H'},
	{"instance", required_argument, NULL, 'i'},
	{"type", required_argument, NULL, 't'},
	{"imageId", required_argument, NULL, 'I'},
	{"buildId", required_argument, NULL, 'b'},
	{"powerState", required_argument, NULL, 'P'},
	{"carrierName", required_argument, NULL, 'c'},
	{"key", required_argument, NULL, 'k'},
	{"rank", required_argument, NULL, 'R'},
	{"subpri", required_argument, NULL, 'S'},
	{"feature", required_argument, NULL, 'f'},
	{"imageType", required_argument, NULL, 'T'},
	{NULL,     0, NULL,  0 }       /* End of list */
};

void ParseCommandLine(int argc, char **argv, 
	enum eUserOptions* operation,
	socketDmsCommandParam* cmdParam
	)
{
    int next_option;
    
	const int PARAM_SIZE = 128;

	char manufacturer[PARAM_SIZE];
	memset(manufacturer, 0, PARAM_SIZE);
	char model[PARAM_SIZE];
	memset(model, 0, PARAM_SIZE);
	char version[PARAM_SIZE];
	memset(version, 0, PARAM_SIZE);
	char plasmaId[PARAM_SIZE];
	memset(plasmaId, 0, PARAM_SIZE);
	char hostId[PARAM_SIZE];
	memset(hostId, 0, PARAM_SIZE);
	int instance = 0;
	uint8_t type = 0;
	char imageId[PARAM_SIZE];
	memset(imageId, 0, PARAM_SIZE);
	char buildId[PARAM_SIZE];
	memset(buildId, 0, PARAM_SIZE);
	char powerState[PARAM_SIZE];
	memset(powerState, 0, PARAM_SIZE);
	char key[PARAM_SIZE];
	memset(key, 0, PARAM_SIZE);
	int rank = 0;
	int subpri = 0;
	char feature[PARAM_SIZE];
	memset(feature, 0, PARAM_SIZE);
	uint8_t image_type = 0;

	bool got_operation = false;
	bool got_type = false;
	bool got_image_type = false;
	bool got_imageId = false;
	bool got_buildId = false;
	bool got_powerState = false;
	bool got_carrierName = false;
	bool got_key = false;
	bool got_rank = false;
	bool got_subpri = false;
	bool got_feature = false;

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
				*operation = GetDmsCommand(optarg);
				got_operation = true;
				break;
			case 'u':
				StrCpy(manufacturer, optarg);
				break;
			case 'M':
				StrCpy(model, optarg);
				break;
			case 'v':
				StrCpy(version, optarg);
				break;
			case 'p':
				StrCpy(plasmaId, optarg);
				break;
			case 'H':
				StrCpy(hostId, optarg);
				break;
			case 'i':
				instance = atoi(optarg);
				break;
			case 't':
				type = atoi(optarg);
				if (type !=  0 && type != 1)
				{
					printf("Error: --type (-t) parameter is not '0' for the ICCID or '1' for the MCC:MNC\n");
					exit(EXIT_FAILURE);
				}
				got_type = true;
				break;
			case 'I':
				StrCpy(imageId, optarg);
				got_imageId = true;
				break;
			case 'b':
				StrCpy(buildId, optarg);
				got_buildId = true;
				break;
			case 'P':
				StrCpy(powerState, optarg);
				got_powerState = true;
				break;
			case 'c':
				StrCpy(s_carrier, optarg);
				got_carrierName = true;
				break;
			case 'k':
				StrCpy(key, optarg);
				got_key = true;
				break;
			case 'R':
				rank = atoi(optarg);
				got_rank = true;
				break;
			case 'S':
				subpri = atoi(optarg);
				got_subpri = true;
				break;
			case 'f':
				StrCpy(feature, optarg);
				got_feature = true;
				break;
			case 'T':
				got_image_type = true;
				if (strcmp(optarg, "modem") == 0)
					image_type = 0;
				else if (strcmp(optarg, "pri") == 0)
					image_type = 1;
				else
					got_image_type = false;
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
		case eSET_SWI_HOST_DEV_INFO:
		{
			memset(&cmdParam->sSetHostDevInfo.packdmsSLQSSwiSetHostDevInfo, 0, sizeof(pack_dms_SLQSSwiSetHostDevInfo_t));

			StrCpy(cmdParam->sSetHostDevInfo.packdmsSLQSSwiSetHostDevInfo.manString, manufacturer);
			StrCpy(cmdParam->sSetHostDevInfo.packdmsSLQSSwiSetHostDevInfo.modelString, model);
			StrCpy(cmdParam->sSetHostDevInfo.packdmsSLQSSwiSetHostDevInfo.swVerString, version);
			StrCpy(cmdParam->sSetHostDevInfo.packdmsSLQSSwiSetHostDevInfo.plasmaIDString, plasmaId);
			StrCpy(cmdParam->sSetHostDevInfo.packdmsSLQSSwiSetHostDevInfo.hostID, hostId);
			cmdParam->sSetHostDevInfo.inst = instance;
			cmdParam->sSetHostDevInfo.packdmsSLQSSwiSetHostDevInfo.pInstance = &cmdParam->sSetHostDevInfo.inst;
		}
		break;
		case eDEL_STORED_IMAGES:
			if (!got_image_type)
			{ 
				printf("Error: DeleteStoredImage operation missing --imageType (-T) parameter (modem|pri)\n");
				exit(EXIT_FAILURE);
			}
			if (!got_imageId)
			{
				printf("Error: DeleteStoredImage operation missing --imageId (-I) parameter\n");
				exit(EXIT_FAILURE);
			}
			if (!got_buildId)
			{
				printf("Error: DeleteStoredImage operation missing --buildId (-b) parameter\n");
				exit(EXIT_FAILURE);
			}

			memset(&cmdParam->packfmsDeleteStoredImage, 0, sizeof(pack_fms_DeleteStoredImage_t));

			cmdParam->packfmsDeleteStoredImage.ImageInfo.imageType = image_type;
			strncpy_s((char*)cmdParam->packfmsDeleteStoredImage.ImageInfo.imageId, sizeof(cmdParam->packfmsDeleteStoredImage.ImageInfo.imageId), imageId, strlen(imageId));
			strncpy_s((char*)cmdParam->packfmsDeleteStoredImage.ImageInfo.buildId, sizeof(cmdParam->packfmsDeleteStoredImage.ImageInfo.buildId), buildId, strlen(buildId));

			cmdParam->packfmsDeleteStoredImage.ImageInfo.buildIdLength = (uint8_t)strlen((char *)cmdParam->packfmsDeleteStoredImage.ImageInfo.buildId);
			break;
		case eSET_POWER:
			if (!got_powerState || GetPowerModeValue(powerState, &cmdParam->sSetPower.mode) != eFound)
			{
				printf("Error: SetPower operation missing --powerState (-P) parameter\n");
				exit(EXIT_FAILURE);
			}
			break;
		case eGET_AUTO_SIM_LIST:
			if (!got_carrierName)
			{
				printf("Error: GetAutoSimList operation missing --carrierName (-c) parameter\n");
				exit(EXIT_FAILURE);
			}

			memset(&cmdParam->getAutoSimList, 0, sizeof(pack_swidms_SLQSSwiDmsGetAutoSimList_t));

			if (strcmp(s_carrier, "all") != 0)
				strcpy_s(cmdParam->getAutoSimList.carrier, DMS_IMGDETAILS_LEN, s_carrier);
			break;
		case eSET_AUTO_SIM_LIST:
			if (!got_carrierName)
			{
				printf("Error: SetAutoSimList operation missing --carrierName (-c) parameter\n");
				exit(EXIT_FAILURE);
			}
			if (!got_key)
			{
				printf("Error: SetAutoSimList operation missing --key (-k) parameter\n");
				exit(EXIT_FAILURE);
			}
			if (strcmp(key, "all") != 0)
			{
				if (!got_rank)
				{
					printf("Error: SetAutoSimList operation missing --rank (-R) parameter, and --key parameter is not 'all'\n");
					exit(EXIT_FAILURE);
				}
				if (!got_subpri)
				{
					printf("Error: SetAutoSimList operation missing --subpri (-s) parameter, and --key parameter is not 'all'\n");
					exit(EXIT_FAILURE);
				}
			}

			memset(&cmdParam->sSetAutoSimList.setAutoSimList, 0, sizeof(pack_swidms_SLQSSwiDmsSetAutoSimList_t));

			strcpy_s(cmdParam->sSetAutoSimList.setAutoSimList.carrier, DMS_IMGDETAILS_LEN, s_carrier);

			if (strcmp(key, "all") != 0) //delete attributes
			{
				memset(&cmdParam->sSetAutoSimList.attributes, 0, sizeof(swi_dms_auto_sim_attributes_type_t));

				if (got_type)
					cmdParam->sSetAutoSimList.attributes.type = type;

				StrNCpy(cmdParam->sSetAutoSimList.attributes.key, key, strlen(key));
				cmdParam->sSetAutoSimList.attributes.key_len = strlen(cmdParam->sSetAutoSimList.attributes.key);
				if (cmdParam->sSetAutoSimList.attributes.key_len == 7)
				{
					cmdParam->sSetAutoSimList.attributes.rank = rank;
					cmdParam->sSetAutoSimList.attributes.subpri = subpri;

					cmdParam->sSetAutoSimList.setAutoSimList.pAttributes = &cmdParam->sSetAutoSimList.attributes;
				}
				else
				{
					printf("\nInvalid key size\n");
					exit(EXIT_FAILURE);
				}
			}
			break;
		case eSET_CUST_FEATURES:
			if (!got_feature)
			{
				printf("Error: SetCustomFeatures operation missing --feature (-f) parameter\n");
				exit(EXIT_FAILURE);
			}

			memset(&cmdParam->sSetCustomFeatures, 0, sizeof(pack_dms_SetCustFeaturesV2_t));

			if (GetNameByteValuePair(feature, (char*)cmdParam->sSetCustomFeatures.cust_id, DMS_MAX_CUST_ID_LEN, (char*)cmdParam->sSetCustomFeatures.cust_value) != eFound)
			{
				printf("\nInvalid argument\n");
				exit(EXIT_FAILURE);
			}

			cmdParam->sSetCustomFeatures.value_length = 1;
			break;
		default:
			break;
		}
	}
}

int InitializeAndRun(enum eUserOptions operation, socketDmsCommandParam* cmdParam)
{
    int ret = FAILURE;
    memset(&s_CtlService, 0, sizeof(CtlService));

	if (CtlService_Initialize(&s_CtlService, &s_Transport) != SUCCESS)
		printf("CtlService_Initialize failed\n");
	else
	{
		memset(&s_DmsService, 0, sizeof(QmiService));
        memset(&s_SwiDmsService, 0, sizeof(QmiService));

        // We use the Ctl service to initialize the regular services because it knows how to 
        // acquire client IDs for them.

        // Use a do/while for easy exit. We have to clean up.
        do
        {
            // Infrastructure is now ready. Let's create some regular QMI services.

            ret = CtlService_InitializeRegularService(&s_CtlService, &s_SwiDmsService, eSWIDMS, DmsIndicationCallback, NULL);
            if (ret != SUCCESS)
            {
				printf("InitializeRegularService eSWIDMS failed.\n");
                break;
            }
            ret = CtlService_InitializeRegularService(&s_CtlService, &s_DmsService, eDMS, DmsIndicationCallback, NULL);
            if (ret != SUCCESS)
            {
				printf("InitializeRegularService eDMS failed.\n");
                break;
            }
            g_AppState = AppRunning;

            //enable device event report 
            pack_dms_SetEventReport_t sSetEventReport;
            sSetEventReport.mode = 1;
            SetEventReport (&s_DmsService, &sSetEventReport);
            
			if (g_socketServer)
			{
				ExecuteDmsSocketTestCase("/tmp/qmidms-server-socket", cmdParam);
			}
			else if (operation == eUNKNOWN)
			{
				ExecuteDmsTestCaseSelection();
			}
			else 
			{
				ExecuteDmsTestCase(operation, cmdParam);
			}

        } while (0);
    
        // Shut down.
        if (g_AppState != AppCommandWaitForDevice)
            g_AppState = AppShuttingDown;

        CtlService_ShutDownRegularService(&s_CtlService, &s_SwiDmsService);
        CtlService_ShutDownRegularService(&s_CtlService, &s_DmsService);

        CtlService_ShutDown(&s_CtlService);
    }

	QmuxTransport_ShutDown(&s_Transport);

    return ret;
}

void DeviceIsOffline()
{
    SockPrintf("\nDevice is offline\n");
    g_AppState = AppCommandWaitForDevice;
	printf("\nPress<Enter> to proceed...\n");
    g_bExitLoop = false;
}

void WaitForDevices(int timeOut, enum eUserOptions operation, socketDmsCommandParam* cmdParam)
{
    int timeElapsed = 0;

    do 
    {
        sleep(3);

		bool bPCIe = false;
        if (OpenTransport(&s_Transport, g_DevicePath, sizeof(g_DevicePath), &g_mode, &bPCIe, NULL,
            true, PrintUsageManual, g_ProcName, false) == 0)
        {
            g_bExitLoop = true;
            InitializeAndRun(operation, cmdParam);
        }
        else
        {
            SockPrintf("Waiting for the device...\n");
        }

        timeElapsed++;
    } while (false == g_bExitLoop && timeElapsed < timeOut);

    if (!g_bExitLoop || timeElapsed >= timeOut)
        SockPrintf("\nStopped waiting for the device.\n");    
}

bool DeviceExist(const char* dev)
{
	bool bDeviceExist = false;
	FILE *pf = NULL;
	char command[40] = { 0 };
	char data[512] = { 0 };

	// list command 
	sprintf(command, "ls %s* 2>&1", dev);

	// Setup our pipe for reading and execute our command.
	pf = popen(command, "r");

	// Check for device
	if (pf != NULL)
	{
		char noaccess[40] = { 0 };
		sprintf(noaccess, "cannot access '%s*'", dev);

		fgets(data, 512, pf);
		if (strstr(data, noaccess) == NULL && strstr(data, dev) != NULL)
			bDeviceExist = true;

		pclose(pf);
		pf = NULL;
	}

	return bDeviceExist;
}

bool IsDevicePresent()
{
	return DeviceExist("/dev/cdc-wdm") || DeviceExist("/dev/mhi");
}

int main(int argc, char **argv)
{
    int ret = FAILURE;
    g_PrintVersion = false;

	enum eUserOptions operation = eUNKNOWN;
	socketDmsCommandParam cmdParam;
	memset(&cmdParam, 0, sizeof(socketDmsCommandParam));

    ParseCommandLine(argc, argv, &operation, &cmdParam);
    if (g_PrintVersion)
    {
		printf("\n%s v%s\n\n", APPNAME, VERSION);
       	if (argc == 2)
		    return 0;
    }

    bool bDevicePreset = IsDevicePresent();
    if (bDevicePreset == false)
    {
        printf(ANSI_COLOR_RED);
		printf("\nNo SWI USB or PCIe device is preset.\n\n");
        printf(ANSI_COLOR_RESET);

		//quit if running in script mode
		if (operation == eEXIT || operation == eUNKNOWN || operation == eHELP)
		{
			return ret;
		}
    }
    while (bDevicePreset == false)
    {
		printf("Enter <y> to wait 30 secods for the device or any other key to exit.\n\n");
        char ch = getchar();
        getchar();

        if (ch == 'y')
        {
            int cntSecond = 30;
			printf("Waiting for device...\n\n");
            do 
            {
                sleep(3);
                cntSecond -= 3;
                bDevicePreset = IsDevicePresent();

            } while (bDevicePreset == false && cntSecond > 0);
        }
        else
            return ret;
    }

    StrCpy(g_ProcName, argv[0]);
    memset(&s_Transport, 0, sizeof(QmuxTransport));

	bool bPCIe = false;
    if (OpenTransport(&s_Transport, g_DevicePath, sizeof(g_DevicePath), &g_mode, &bPCIe, NULL,
        true, PrintUsageManual, argv[0], false) != 0)
        return 0;

    ret = InitializeAndRun(operation, &cmdParam);

    if (g_AppState != AppShuttingDown)
        WaitForDevices(60, operation, &cmdParam);

    return ret;
}
