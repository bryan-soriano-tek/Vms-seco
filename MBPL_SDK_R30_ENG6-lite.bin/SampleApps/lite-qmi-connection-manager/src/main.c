/**************
 *
 * Filename:    main.c
 *
 * Purpose:     Connection Manager application
 *
 * Copyright: © 2017 Sierra Wireless Inc., all rights reserved
 *
 **************/
#define __STDC_FORMAT_MACROS
#include <pthread.h>
#include <inttypes.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/route.h>
#include <time.h>
#include <fcntl.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include "lite-qmi-demo.h"

#define VERSION	"1.0.2211.0"
const char* const appName = "lite-qmi-connection-manager";
//
// Compile Switch definitions for different behavior of the program
//

// Whether to show invalid profile error.  If set to 1, querying empty profiles will show error
#define SHOW_INVALID_PROFILE_ERROR 0

// When making IPv4v6 connection, connect to IPv6 first or IPv4 first
// Set to connect to IPv6 first as a workaround to HSWOEMP-1595
#define FIRST_CONNECTION_IPV6	1

//
// End of Compile Switches
//

#include "displaysettings.h"
#include "msgid.h"
#include "lite-qmi-demo.h"

#include "ping.h"
#include "netlink_util.h"
#include "dev_util.h"
#include "qmux_util.h"
#include "proc_util.h"
#include "str_util.h"
#include "command_set.h"
#include "socket_server.h"
#include "wda_handler.h"
#include "tmd_handler.h"
#include "ts_handler.h"
#include "qos_handler.h"
#include "swidms_handler.h"
#include "wds.h"
#include "dms.h"
#include "nas.h"
#include "qos.h"

/****************************************************************
*                       DEFINES
****************************************************************/

/* APN, User Name and Profile name size should be 3 greater than the actual
 * characters to be read. This will help to ensure that user should not enter
 * more than maximum allowed characters.
 */
#define MIN_PROFILES            1
#define MAX_PROFILES            42

#define IPV4 4
#define IPV6 6
#define MAX_QMAP_INSTANCE 8
#define MAX_IFLEN	64

 // Behavior upon connection establishment
#define PING_COUNT	4
#define PING_DELAY	3

// HSWOEMP-1595
#if FIRST_CONNECTION_IPV6
#define SPDN_CONN_START			1
#define SPDN_LIMIT				0
#define MPDN_CONN_START			3
#define MPDN_LIMIT				2
#else
#define SPDN_CONN_START			0
#define SPDN_LIMIT				2
#define MPDN_CONN_START			2
#define MPDN_LIMIT				4
#endif

int g_auto_test_enable = 1;
int g_mtu_auto_update_enable = 1;
int g_ip_auto_assign = 1;

/****************************************************************
*                       DATA STRUCTURE
****************************************************************/

enum
{
	eLITE_CONNECT_APP_OK,
	eLITE_CONNECT_APP_ERR_QMI,
};

enum eConnectionState {
	NONE,
	SINGLE,
	MULTIPDN
};

/* Profile indexes for profile existing on device */
struct profileIndexesInfo {
	uint8_t profileIndex[MAX_PROFILES];
	uint8_t totalProfilesOnDevice;
};

/****************************************************************
*                    GLOBAL DATA
****************************************************************/
const int nMaskPrefLenV4 = 0;//24;
const int nMaskPrefLenV6 = 124;

char szEthName[64];
const char* g_default_dev = NULL;

/* device connectivity */
static struct profileIndexesInfo indexInfo;

static CtlService s_CtlService;
static QmiService s_DmsService;
static QmiService s_NasService;
static QmuxTransport s_Transport;

static uint8_t g_NetSelPref = 0;
static uint16_t g_NasPendingXid = 0;

bool g_exiting = false;

struct session
{
	QmiService wdsSvc;			// Instance of WDS Service
	int idx;					// Index of the sesion in sessions array.  Used to identify the session in callback
	int domain;					// AF_INET or AF_INET6
	bool active;				// Flag indicating if the data session is active
	uint32_t sid;				// QMI connection session id
	char ip[INET6_ADDRSTRLEN];	// IP address of active data session
	int prefixlen;				// IP address prefix length
	unsigned int mtu;			// MTU size of the data session
	uint8_t uIPCount;			// IP count
	const char* ifname;			// Network Interface name QMUX or VLAN
	int ifid;					// Network Interface ID for QMUX or VLAN
} sessions[NUM_WDS_SVC];

int g_netnum_val = 4;// 0;
int g_mode = QMUX_INTERFACE_UNKNOWN;
bool g_online = true;
bool g_pcie = false;
bool g_bRmNet = false;
int g_rmnet_if_id = RMNET_IF_ID_UNSET;
bool g_vlan_added = false;
bool g_update_route = true;
bool g_qos_support = false;
// To be replaced with swiwds bool g_swinas_support = false;
enum eConnectionState g_connection_state = NONE;
unsigned int g_nMtu = 0xFFFFFFFF;

struct routeTable
{
	char szif[MAX_IFLEN];
	char dst[INET6_ADDRSTRLEN];
	char gw[INET6_ADDRSTRLEN];
} setrouteTable[NUM_WDS_SVC][MAX_QMAP_INSTANCE] =
{
	{
		//{{""},{"8.8.8.0"},{""}},
		{{""},{"0.0.0.0"},{"0.0.0.0"}},
		{{""},{"216.105.38.0"},{""}},
		{{""},{""},{""}},
		{{""},{""},{""}},
		{{""},{""},{""}},
		{{""},{""},{""}},
		{{""},{""},{""}},
		{{""},{""},{""}}
	},
	{
		//{{""},{"2607:f8b0:400a:800::2000"},{""}},
		//{{""},{"2001:4860:4860::8888"},{""}},
		{{""},{"::"},{""}},
		{{""},{""},{""}},
		{{""},{""},{""}},
		{{""},{""},{""}},
		{{""},{""},{""}},
		{{""},{""},{""}},
		{{""},{""},{""}},
		{{""},{""},{""}}
	},
	{
		//{{""},{"4.2.2.0"},{""}},
		{{""},{"0.0.0.0"},{"0.0.0.0"}},
		{{""},{"216.105.38.0"},{""}},
		{{""},{""},{""}},
		{{""},{""},{""}},
		{{""},{""},{""}},
		{{""},{""},{""}},
		{{""},{""},{""}},
		{{""},{""},{""}}
	},
	{
		{{""},{""},{""}},
		{{""},{""},{""}},
		{{""},{""},{""}},
		{{""},{""},{""}},
		{{""},{""},{""}},
		{{""},{""},{""}},
		{{""},{""},{""}},
		{{""},{""},{""}}
	}
};

char pingTable[NUM_WDS_SVC][MAX_QMAP_INSTANCE][INET6_ADDRSTRLEN] =
{
	{
	  {"8.8.8.8"},
	  {"216.105.38.13"},
	  {""},
	  {""},
	  {""},
	  {""},
	  {""},
	  {""}
	},
	{
	  //{"2607:f8b0:400a:800::200e"},
	  {"2001:4860:4860::8888"},
	  {""},
	  {""},
	  {""},
	  {""},
	  {""},
	  {""},
	  {""}
	},
	{
	  {"4.2.2.2"},
	  {"216.105.38.13"},
	  {""},
	  {""},
	  {""},
	  {""},
	  {""},
	  {""}
	},
	{
	  {"fc01:cafe::1"},
	  {""},
	  {""},
	  {""},
	  {""},
	  {""},
	  {""},
	  {""}
	}
};

/****************************************************************
*              FORWARD FUNCTION DECLARATION
****************************************************************/
void display_device_info(void);
void display_profile_info(uint8_t profileId, bool bDisplayHeader, bool bUpdateCache);
void display_all_profiles(bool bShowNoProfile);
void datasession_stopped(struct session* pSession);

/****************************************************************
*                       FUNCTIONS
****************************************************************/

void DisplayWdsEventReport(unpack_wds_SLQSSetWdsEventReport_ind_t* pWdsEventReport_ind)
{
	SockPrintf("\n  WDS Event Report Indication\n");
	if (swi_uint256_get_bit(pWdsEventReport_ind->ParamPresenceMask, 0x10))
		SockPrintf("  	tx_ok_count:  %d\n", pWdsEventReport_ind->tx_ok_count);
	if (swi_uint256_get_bit(pWdsEventReport_ind->ParamPresenceMask, 0x11))
		SockPrintf("  	rx_ok_count:  %d\n", pWdsEventReport_ind->rx_ok_count);
	if (swi_uint256_get_bit(pWdsEventReport_ind->ParamPresenceMask, 0x12))
		SockPrintf("  	tx_err_count:  %d\n", pWdsEventReport_ind->tx_err_count);
	if (swi_uint256_get_bit(pWdsEventReport_ind->ParamPresenceMask, 0x13))
		SockPrintf("  	rx_err_count:  %d\n", pWdsEventReport_ind->rx_err_count);
	if (swi_uint256_get_bit(pWdsEventReport_ind->ParamPresenceMask, 0x14))
		SockPrintf("  	tx_ofl_count:  %d\n", pWdsEventReport_ind->tx_ofl_count);
	if (swi_uint256_get_bit(pWdsEventReport_ind->ParamPresenceMask, 0x15))
		SockPrintf("  	rx_ofl_count:  %d\n", pWdsEventReport_ind->rx_ofl_count);
	if (swi_uint256_get_bit(pWdsEventReport_ind->ParamPresenceMask, 0x16))
	{
		SockPrintf("  	ChannelRate.current_channel_tx_rate:  %d\n", pWdsEventReport_ind->channelRate.current_channel_tx_rate);
		SockPrintf("  	ChannelRate.current_channel_rx_rate:  %d\n", pWdsEventReport_ind->channelRate.current_channel_rx_rate);
	}
	if (swi_uint256_get_bit(pWdsEventReport_ind->ParamPresenceMask, 0x18))
		SockPrintf("  	dormancy_status:  %d\n", pWdsEventReport_ind->dormancy_status);
	if (swi_uint256_get_bit(pWdsEventReport_ind->ParamPresenceMask, 0x19))
		SockPrintf("  	tx_ok_bytes_count:  0x%"PRIX64"\n", pWdsEventReport_ind->tx_ok_bytes_count);
	if (swi_uint256_get_bit(pWdsEventReport_ind->ParamPresenceMask, 0x1A))
		SockPrintf("  	rx_ok_bytes_count:  0x%"PRIX64"\n", pWdsEventReport_ind->rx_ok_bytes_count);
	if (swi_uint256_get_bit(pWdsEventReport_ind->ParamPresenceMask, 0x1B))
		SockPrintf("  	mip_status:  %d\n", pWdsEventReport_ind->mip_status);
	if (swi_uint256_get_bit(pWdsEventReport_ind->ParamPresenceMask, 0x1F))
		SockPrintf("  	data_call_status:  %d\n", pWdsEventReport_ind->data_call_status);
	if (swi_uint256_get_bit(pWdsEventReport_ind->ParamPresenceMask, 0x20))
		SockPrintf("  	current_sys:  %d\n", pWdsEventReport_ind->current_sys);

	//DataCallTypeTlv_t               dataCallType; //22
	if (swi_uint256_get_bit(pWdsEventReport_ind->ParamPresenceMask, 0x22))
	{
		SockPrintf("  	dataCallType.data_call_type:  %d\n", pWdsEventReport_ind->dataCallType.data_call_type);
		SockPrintf("  	dataCallType.tethered_call_type:  %d\n", pWdsEventReport_ind->dataCallType.tethered_call_type);
	}

	//EVDOPageMonitorPeriodChange_t   eVDOPageMonitorPeriodChange; //23
	if (swi_uint256_get_bit(pWdsEventReport_ind->ParamPresenceMask, 0x23))
	{
		SockPrintf("  	eVDOPageMonitorPeriodChange.evdo_page_monitor_period_change:  %d\n", pWdsEventReport_ind->eVDOPageMonitorPeriodChange.evdo_page_monitor_period_change);
		SockPrintf("  	eVDOPageMonitorPeriodChange.evdo_force_long_sleep:  %d\n", pWdsEventReport_ind->eVDOPageMonitorPeriodChange.evdo_force_long_sleep);
	}

	if (swi_uint256_get_bit(pWdsEventReport_ind->ParamPresenceMask, 0x25))
		SockPrintf("  	tx_dropped_count:  %d\n", pWdsEventReport_ind->tx_dropped_count);
	if (swi_uint256_get_bit(pWdsEventReport_ind->ParamPresenceMask, 0x26))
		SockPrintf("  	rx_dropped_count:  %d\n", pWdsEventReport_ind->rx_dropped_count);
	if (swi_uint256_get_bit(pWdsEventReport_ind->ParamPresenceMask, 0x27))
		SockPrintf("  	uplink_flow_control:  %d\n", pWdsEventReport_ind->uplink_flow_control);
	if (swi_uint256_get_bit(pWdsEventReport_ind->ParamPresenceMask, 0x28))
		SockPrintf("  	data_call_addr_family:  %d\n", pWdsEventReport_ind->data_call_addr_family);

	//AdditionalPdnFiltersRemoved_t   additionalPdnFiltersRemoved; //29
	if (swi_uint256_get_bit(pWdsEventReport_ind->ParamPresenceMask, 0x29))
	{
		for (int idx = 0; idx < pWdsEventReport_ind->additionalPdnFiltersRemoved.removed_filter_handles_len; ++idx)
		{
			SockPrintf("  	additionalPdnFiltersRemoved.removed_filter_handles[%d]:  %d\n", idx, pWdsEventReport_ind->additionalPdnFiltersRemoved.removed_filter_handles[idx]);
		}
	}

	//DataBearerTechnologyExtended_t  dataBearerTechnologyExtended; //2A
	if (swi_uint256_get_bit(pWdsEventReport_ind->ParamPresenceMask, 0x2A))
	{
		SockPrintf("  	dataBearerTechnologyExtended.technology:  %d\n", pWdsEventReport_ind->dataBearerTechnologyExtended.technology);
		SockPrintf("  	dataBearerTechnologyExtended.rat_value:  %d\n", pWdsEventReport_ind->dataBearerTechnologyExtended.rat_value);
		SockPrintf("  	dataBearerTechnologyExtended.so_mask:  0x%"PRIX64"\n", pWdsEventReport_ind->dataBearerTechnologyExtended.so_mask);
	}

	if (swi_uint256_get_bit(pWdsEventReport_ind->ParamPresenceMask, 0x2B))
		SockPrintf("  	uplink_fc_seq_num:  %d\n", pWdsEventReport_ind->uplink_fc_seq_num);  //2B

	//DormancyResultIndicator_t       dormancyResultIndicator; //2C
	if (swi_uint256_get_bit(pWdsEventReport_ind->ParamPresenceMask, 0x2C))
	{
		SockPrintf("  	dormancyResultIndicator.status:  %d\n", pWdsEventReport_ind->dormancyResultIndicator.status);
		SockPrintf("  	dormancyResultIndicator.dormancy_failure_reason:  %d\n", pWdsEventReport_ind->dormancyResultIndicator.dormancy_failure_reason);
	}

	//ExtendedChannelRate_t           extendedChannelRate; //2D
	if (swi_uint256_get_bit(pWdsEventReport_ind->ParamPresenceMask, 0x2D))
	{
		SockPrintf("  	extendedChannelRate.rate_type:  %d\n", pWdsEventReport_ind->extendedChannelRate.rate_type);
		SockPrintf("  	extendedChannelRate.channel_tx_rate_ex:  0x%"PRIX64"\n", pWdsEventReport_ind->extendedChannelRate.channel_tx_rate_ex);
		SockPrintf("  	extendedChannelRate.channel_rx_rate_ex:  0x%"PRIX64"\n", pWdsEventReport_ind->extendedChannelRate.channel_rx_rate_ex);
	}
}

void DisplayDmsEventInd(unpack_dms_SetEventReport_ind_t* ind_rsp)
{
	SockLog(eLOG_INFO, "[unpack_dms_SetEventReport_ind]\n");

	if (swi_uint256_get_bit(ind_rsp->ParamPresenceMask, 0x10))	// Power state
		SockPrintf("\tPower state\n");

	if (swi_uint256_get_bit(ind_rsp->ParamPresenceMask, 0x11))	// PIN 1 status (deprecated)
		SockPrintf("\tPIN 1 status (deprecated)\n");

	if (swi_uint256_get_bit(ind_rsp->ParamPresenceMask, 0x12))	// PIN 2 status (deprecated)
		SockPrintf("\tPIN 2 status (deprecated)\n");

	if (swi_uint256_get_bit(ind_rsp->ParamPresenceMask, 0x13))	// Activation state
		SockPrintf("\tActivation state: %d\n", ind_rsp->ActivationStatusTlv.activationStatus);

	if (swi_uint256_get_bit(ind_rsp->ParamPresenceMask, 0x14))	// Operating mode
		SockPrintf("\tOperating mode: %d\n", ind_rsp->OperatingModeTlv.operatingMode);

	if (swi_uint256_get_bit(ind_rsp->ParamPresenceMask, 0x15))	// UIM state (deprecated)
		SockPrintf("\tUIM state (deprecated)\n");

	if (swi_uint256_get_bit(ind_rsp->ParamPresenceMask, 0x16))	// Wireless disable state
		SockPrintf("\tWireless disable state\n");

	if (swi_uint256_get_bit(ind_rsp->ParamPresenceMask, 0x17))	// PRL init notif
		SockPrintf("\tPRL init notif\n");

	if (swi_uint256_get_bit(ind_rsp->ParamPresenceMask, 0x18))	// CDMA lock mode state
		SockPrintf("\tCDMA lock mode state\n");

	if (swi_uint256_get_bit(ind_rsp->ParamPresenceMask, 0x19))	// Device multiSIM cap (dprecated)
		SockPrintf("\tDevice multiSIM cap (dprecated)\n");

	if (swi_uint256_get_bit(ind_rsp->ParamPresenceMask, 0x1A))	// Device multiSIM voice data cap
		SockPrintf("\tDevice multiSIM voice data cap\n");

	if (swi_uint256_get_bit(ind_rsp->ParamPresenceMask, 0x1B))	// Current subscription cap
		SockPrintf("\tCurrent subscription cap\n");

	if (swi_uint256_get_bit(ind_rsp->ParamPresenceMask, 0x1C))	// Subscription voice data cap
		SockPrintf("\tSubscription voice data cap\n");

	if (swi_uint256_get_bit(ind_rsp->ParamPresenceMask, 0x1D))	// Max active data subscriptions
		SockPrintf("\tMax active data subscriptions\n");

	if (swi_uint256_get_bit(ind_rsp->ParamPresenceMask, 0x1E))	// PRL info
		SockPrintf("\tPRL info\n");

	if (swi_uint256_get_bit(ind_rsp->ParamPresenceMask, 0x1F))	// Max device config list
		SockPrintf("\tMax device config list\n");

	if (swi_uint256_get_bit(ind_rsp->ParamPresenceMask, 0x20))	// Explicit configruation index
		SockPrintf("\tExplicit configruation index\n");
}

static void DmsIndicationCallback(uint8_t* qmiPacket, uint16_t qmiPacketSize, void* pIndicationCallbackContext)
{
	switch (IndicationCallback("DMS", eDMS, qmiPacket, qmiPacketSize, pIndicationCallbackContext))
	{
	case eQMI_DMS_EVENT_IND:
	{
		unpack_dms_SetEventReport_ind_t ind_rsp;
		int rtn = unpack_dms_SetEventReport_ind(qmiPacket, qmiPacketSize, &ind_rsp);
		LockSocket();
		DisplayResult("unpack_dms_SetEventReport_ind", rtn, NULL, (result_func)DisplayDmsEventInd, (void*)&ind_rsp);
		UnlockSocket();
		break;
	}
	default:
		break;
	}
}

static void NasIndicationCallback(uint8_t* qmiPacket, uint16_t qmiPacketSize, void* pIndicationCallbackContext)
{
	IndicationCallback("NAS", eNAS, qmiPacket, qmiPacketSize, pIndicationCallbackContext);
}

static void WdsIndicationCallback(uint8_t* qmiPacket, uint16_t qmiPacketSize, void* pIndicationCallbackContext)
{
	switch (IndicationCallback("WDS", eWDS, qmiPacket, qmiPacketSize, pIndicationCallbackContext))
	{
	case eQMI_WDS_PKT_STATUS_IND:
	{
		unpack_wds_SLQSSetPacketSrvStatusCallback_t ind_rsp;
		int rtn = unpack_wds_SLQSSetPacketSrvStatusCallback(qmiPacket, qmiPacketSize, &ind_rsp);
		if (rtn != SUCCESS)
		{
			SockPrintf (ANSI_COLOR_RED);
			SockPrintf("\nunpack_wds_SLQSSetPacketSrvStatusCallback failed, rtn: %d: %s\n", rtn, helper_get_error_reason(rtn));
			SockPrintf (ANSI_COLOR_RESET);
			break;
		}

		SockLog(eLOG_INFO, "[unpack_wds_SLQSSetPacketSrvStatusCallback]\n");

		struct session* pSession = (struct session*)pIndicationCallbackContext;

		SockPrintf("\tPacket Service %d Status: 0x%x, Reconfig required: %d\n", pSession ? pSession->idx : -1, ind_rsp.conn_status, ind_rsp.reconfigReqd);

		bool bClientEnded = false;
		int nDomain = AF_UNSPEC;

		if (swi_uint256_get_bit(ind_rsp.ParamPresenceMask, 0x10))	// Call End Reason
		{
			SockPrintf("\tCall End Reason: %d\n", ind_rsp.sessionEndReason);
			if (ind_rsp.sessionEndReason == 2)
				bClientEnded = true;
		}

		if (swi_uint256_get_bit(ind_rsp.ParamPresenceMask, 0x11))	// Verbose Call End Reason
		{
			SockPrintf("\tVerbose Call End Reason.  Type: %d, Reason: %d\n", ind_rsp.verboseSessnEndReasonType, ind_rsp.verboseSessnEndReason);
			if (ind_rsp.verboseSessnEndReasonType == 3 && ind_rsp.verboseSessnEndReason == 2000)
				bClientEnded = true;
		}

		if (swi_uint256_get_bit(ind_rsp.ParamPresenceMask, 0x12))	// IP Family
		{
			SockPrintf("\tIP Family: %d\n", ind_rsp.ipFamily);

			switch (ind_rsp.ipFamily)
			{
			case 4:
				nDomain = AF_INET;
				break;
			case 6:
				nDomain = AF_INET6;
				break;
			default:
				break;
			}
		}

		if (swi_uint256_get_bit(ind_rsp.ParamPresenceMask, 0x13))	// Technology Name
			SockPrintf("\tTechnology: 0x%x\n", ind_rsp.techName);

		if (swi_uint256_get_bit(ind_rsp.ParamPresenceMask, 0x14))	// Bearer ID
			SockPrintf("\tBearer ID: 0x%x\n", ind_rsp.bearerID);

		if (pSession &&									// Valid session
			pSession->active && pSession->sid != 0 &&	// Active session
			ind_rsp.conn_status == 1 &&					// Disconnected notification
			pSession->domain == nDomain &&				// IP type matches
			!bClientEnded)								// Not disconnected by client
		{
			datasession_stopped(pSession);				// Disconnection cleanup
		}

		break;
	}
	case eQMI_WDS_EVENT_REPORT_IND:
	{
		unpack_wds_SLQSSetWdsEventReport_ind_t ind_rsp;
		memset(&ind_rsp, 0, sizeof(unpack_wds_SLQSSetWdsEventReport_ind_t));

		int rtn = unpack_wds_SLQSSetWdsEventReport_ind(qmiPacket, qmiPacketSize, &ind_rsp);
		DisplayResult("unpack_wds_SLQSSetWdsEventReport_ind", rtn, NULL, (result_func)DisplayWdsEventReport, (void*)&ind_rsp);
		break;
	}
	default:
		break;
	}
}

/****************************************************************
*                    COMMON FUNCTIONS
****************************************************************/

int GetDataSession()
{
	for (int i = 0; i < NUM_WDS_SVC; i++)
	{
		SockPrintf("Session %d: %s\n", i, sessions[i].active ? "Active" : "Inactive");
	}
	int session = GetNumericValue("Select an active session to disconnect", "session", g_enterActionExit, ENTER_KEY, 0, NUM_WDS_SVC - 1);

	if (session == ENTER_KEY)
	{
		return -1;
	}

	if (!sessions[session].active)
	{
		SockLog(eLOG_INFO, "Selected data session is not active.\n\n");
		return -1;
	}

	return session;
}

void DisplayProfileId(uint8_t *profileId)
{
	SockLog(eLOG_INFO, "Profile id: %d\n", *profileId);
}

void delete_profile_by_id(uint8_t profileId)
{
	pack_wds_SLQSDeleteProfile_t   deleteProfile;
	memset(&deleteProfile, 0, sizeof(deleteProfile));
	deleteProfile.profileIndex = profileId;
	deleteProfile.profileType = PROFILE_TYPE_UMTS;

	unpack_wds_SLQSDeleteProfile_t   deleteProfileOut;
	memset(&deleteProfileOut, 0, sizeof(deleteProfileOut));
	deleteProfileOut.extendedErrorCode = (uint16_t)-1;

	/* Delete the profile from the device */
	int rtn = SENDRECEIVE(&sessions[0].wdsSvc, pack_wds_SLQSDeleteProfile, &deleteProfile, unpack_wds_SLQSDeleteProfile, &deleteProfileOut);
	DisplayResult(__FUNCTION__, rtn, NULL, (result_func)DisplayProfileId, (void*)&profileId);
}

/*
 * Name:     delete_profile_from_device
 *
 * Purpose:  Delete the profile from the device for the profile id provided by
 *           the user.
 *
 * Params:   None
 *
 * Return:   None.
 *
 * Notes:    None
 */
void delete_profile_from_device()
{
	while (1)
	{
		/* Display all the profiles stored on the device */
		display_all_profiles(true);

		/* If no profile exist on the device, return */
		if (0 == indexInfo.totalProfilesOnDevice)
		{
			SockLog(eLOG_ERROR, "No Profile exist on the device for deletion or check device connectivity\n\n");
			break;
		}

		/* Receive the user input */
		uint8_t profileId = GetUserProfileId(MIN_PROFILES, MAX_PROFILES);

		/* If only <ENTER> is pressed by the user, return to main menu */
		if (ENTER_KEY_PRESSED == profileId)
			break;

		delete_profile_by_id(profileId);
	}
}

void SetQmapSettings(bool bEnable)
{
	WdaSetDataFormatParams param;
	memset(&param, 0, sizeof(param));

	if (bEnable)
	{
		param.SetQosHrPres = GetNumericValue(NULL, "Set QOS data format. 0: Not set (default) or 1: Set", g_enterActionDefault, 0, 0, 1);
		if (param.SetQosHrPres)
			param.QosHrPres = GetNumericValue(NULL, "QOS flow header. 0: Header not present (default) or 1: Header present", g_enterActionDefault, QOS_HDR_NOT_PRESENT, QOS_HDR_NOT_PRESENT, QOS_HDR_PRESENT);

		param.SetUL_Data_Aggregation_Max_Datagrams = GetNumericValue(NULL, "Set uplink data aggregation max datagram. 1: Set (default) or 0: Not set", g_enterActionDefault, 1, 0, 1);
		if (param.SetUL_Data_Aggregation_Max_Datagrams)
			param.UL_Data_Aggregation_Max_Datagrams = GetNumericValue(NULL, "Uplink data aggregation max datagrams.", "set default value 16384", QMAP_TX_BUFFER_SIZE, 0, MAX_INT32_VALUE_SIZE);

		param.SetDL_Data_Aggregation_Max_Datagrams = GetNumericValue(NULL, "Set downlink data aggregation max datagram. 1: Set (default) or 0: Not set", g_enterActionDefault, 1, 0, 1);
		if (param.SetDL_Data_Aggregation_Max_Datagrams)
			param.DL_Data_Aggregation_Max_Datagrams = GetNumericValue(NULL, "Downlink data aggregation max datagrams.", "set default value 16384", QMAP_RX_BUFFER_SIZE, 0, MAX_INT32_VALUE_SIZE);

		param.SetUL_Data_Aggregation_Max_Size = GetNumericValue(NULL, "Set uplink data aggregation max size. 1: Set (default) or 0: Not set", g_enterActionDefault, 1, 0, 1);
		if (param.SetUL_Data_Aggregation_Max_Size)
			param.UL_Data_Aggregation_Max_Size = GetNumericValue(NULL, "Uplink data aggregation max size.", "set default value 10", QMAP_TX_BUFFER_SIZE, 0, MAX_INT32_VALUE_SIZE);

		param.SetDL_Data_Aggregation_Max_Size = GetNumericValue(NULL, "Set downlink data aggregation max size. 1: Set (default) or 0: Not set", g_enterActionDefault, 1, 0, 1);
		if (param.SetDL_Data_Aggregation_Max_Size)
			param.DL_Data_Aggregation_Max_Size = GetNumericValue(NULL, "Downlink data aggregation max size.", "set default value 10", QMAP_RX_BUFFER_SIZE, 0, MAX_INT32_VALUE_SIZE);

		param.SetPeripheralEP_ID = GetNumericValue(NULL, "Set peripheral endpoint ID. 1: Set (default) or 0: Not set", g_enterActionDefault, 1, 0, 1);
		if (param.SetPeripheralEP_ID)
		{
			param.EP_Type = g_pcie ? EP_TYPE_PCIE : EP_TYPE_HSUSB;
			param.Interface_ID = g_rmnet_if_id;
		}

		param.SetDL_Padding = GetNumericValue(NULL, "Set QMAP downlink minimum padding. 0: Not set (default) or 1: Set", g_enterActionDefault, 0, 0, 1);
		if (param.SetDL_Padding)
		{
			param.DL_Padding = GetNumericValue(NULL, "Downlink data aggregation max size.", g_enterActionZero, 0, 0, 64);
			param.DL_Padding &= 0xFC;
		}

		param.SetFlow_Control = GetNumericValue(NULL, "Set flow control. 0: Not set (default) or 1: Set", g_enterActionDefault, 0, 0, 1);
		if (param.SetFlow_Control)
			param.Flow_Control = GetNumericValue(NULL, "Flow control. 0: Not done by TE (default) or 1: Done by TE", g_enterActionDefault, FLOW_CTL_NO_TE, 0, 1);
	}

	EnableQmap(&s_CtlService, bEnable, &param);
}

const char* GetInuse(uint32_t val)
{
	switch (val)
	{
	case 1:
		return "Current serving";
	case 2:
		return "Available";
	default:
		break;
	}

	return "Unknown";
}

const char* GetForbidden(uint32_t val)
{
	switch (val)
	{
	case 1:
		return "Forbidden";
	case 2:
		return "Not forbidden";
	default:
		break;
	}

	return "Unknown";
}

const char* GetPreferred(uint32_t val)
{
	switch (val)
	{
	case 1:
		return "Preferred";
	case 2:
		return "Not preferred";
	default:
		break;
	}

	return "Unknown";
}

const char* GetRoaming(uint32_t val)
{
	switch (val)
	{
	case 1:
		return "Home";
	case 2:
		return "Roam";
	default:
		break;
	}

	return "Unknown";
}

void DisplayPerformNetworkScanResult(unpack_nas_PerformNetworkScan_t *pNetworkScan)
{
	SockPrintf("\nNetwork Scan Result:");

	if (swi_uint256_get_bit(pNetworkScan->ParamPresenceMask, 0x13) && pNetworkScan->pScanResult)
		SockPrintf(" %d\n", *pNetworkScan->pScanResult);
	else
		SockPrintf("\n");

	static const char* ratGERAN = "GERAN";	// 0x04
	static const char* ratUMTS = "UMTS";	// 0x05
	static const char* ratLTE = "LTE";	// 0x08
	static const char* ratTDSCDMA = "TD-SCDMA";	// 0x09
	static const char* ratUnknown = "Unknown";

	for (uint8_t i = 0;
		swi_uint256_get_bit(pNetworkScan->ParamPresenceMask, 0x10) &&
		pNetworkScan->p3GppNetworkInfoInstances &&
		pNetworkScan->p3GppNetworkInstanceSize &&
		i < *pNetworkScan->p3GppNetworkInstanceSize;
		i++)
	{
		SockPrintf("   Network %d: %s\n", i, pNetworkScan->p3GppNetworkInfoInstances[i].Desription);
		SockPrintf("      MCC/MNC: %d/%d\n", pNetworkScan->p3GppNetworkInfoInstances[i].MCC, pNetworkScan->p3GppNetworkInfoInstances[i].MNC);
		SockPrintf("      In Use: %s(%d)\n", GetInuse(pNetworkScan->p3GppNetworkInfoInstances[i].InUse), pNetworkScan->p3GppNetworkInfoInstances[i].InUse);
		SockPrintf("      Forbidden: %s(%d)\n", GetForbidden(pNetworkScan->p3GppNetworkInfoInstances[i].Forbidden), pNetworkScan->p3GppNetworkInfoInstances[i].Forbidden);
		SockPrintf("      Preferred: %s(%d)\n", GetPreferred(pNetworkScan->p3GppNetworkInfoInstances[i].Preferred), pNetworkScan->p3GppNetworkInfoInstances[i].Preferred);
		SockPrintf("      Roaming: %s(%d)\n", GetRoaming(pNetworkScan->p3GppNetworkInfoInstances[i].Roaming), pNetworkScan->p3GppNetworkInfoInstances[i].Roaming);

		if (swi_uint256_get_bit(pNetworkScan->ParamPresenceMask, 0x11) &&
			pNetworkScan->pRATINstance &&
			pNetworkScan->pRATInstanceSize &&
			i < *pNetworkScan->pRATInstanceSize)
		{
			const char* pRat = ratUnknown;
			switch (pNetworkScan->pRATINstance[i].RAT)
			{
			case 4:
				pRat = ratGERAN;
				break;
			case 5:
				pRat = ratUMTS;
				break;
			case 8:
				pRat = ratLTE;
				break;
			case 9:
				pRat = ratTDSCDMA;
				break;
			default:
				break;
			}

			SockPrintf("      RAT: %s(%d)", pRat, pNetworkScan->pRATINstance[i].RAT);

			if (pNetworkScan->p3GppNetworkInfoInstances[i].MCC == pNetworkScan->pRATINstance[i].MCC &&
				pNetworkScan->p3GppNetworkInfoInstances[i].MNC == pNetworkScan->pRATINstance[i].MNC)
				SockPrintf("\n");
			else
				SockPrintf(" - MCC/MNC(%d/%d) doesn't match\n", pNetworkScan->pRATINstance[i].MCC, pNetworkScan->pRATINstance[i].MNC);
		}

		if (swi_uint256_get_bit(pNetworkScan->ParamPresenceMask, 0x12) &&
			pNetworkScan->pPCSInstance &&
			pNetworkScan->pPCSInstanceSize &&
			i < *pNetworkScan->pPCSInstanceSize)
		{
			SockPrintf("      MNC includes PCS digit: %s", pNetworkScan->pPCSInstance[i].includes_pcs_digit ? "TRUE" : "FALSE");

			if (pNetworkScan->p3GppNetworkInfoInstances[i].MCC == pNetworkScan->pPCSInstance[i].MCC &&
				pNetworkScan->p3GppNetworkInfoInstances[i].MNC == pNetworkScan->pPCSInstance[i].MNC)
				SockPrintf("\n");
			else
				SockPrintf(" - MCC/MNC(%d/%d) doesn't match\n", pNetworkScan->pPCSInstance[i].MCC, pNetworkScan->pPCSInstance[i].MNC);
		}
	}

	if (swi_uint256_get_bit(pNetworkScan->ParamPresenceMask, 0x17) && pNetworkScan->pPCIInfo)
	{
		for (uint8_t i = 0; i < pNetworkScan->pPCIInfo->PCICellInfoLen; i++)
		{
			SockPrintf("   PCI Cell Info %d: freq: %d, Cell ID: %d, Global Cell ID: %d\n", i,
				pNetworkScan->pPCIInfo->nasQmisNasSlqsNasPCICellInfo[i].freq,
				pNetworkScan->pPCIInfo->nasQmisNasSlqsNasPCICellInfo[i].cellID,
				pNetworkScan->pPCIInfo->nasQmisNasSlqsNasPCICellInfo[i].GlobalCellID);

			for (uint8_t j = 0; j < pNetworkScan->pPCIInfo->nasQmisNasSlqsNasPCICellInfo[i].PlmnLen; j++)
			{
				SockPrintf("    PLMN %d: MCC:%d, MNC:%d, Includes PCS digit: %d\n", j,
					pNetworkScan->pPCIInfo->nasQmisNasSlqsNasPCICellInfo[i].nasQmisNasPcsDigit[j].MCC,
					pNetworkScan->pPCIInfo->nasQmisNasSlqsNasPCICellInfo[i].nasQmisNasPcsDigit[j].MNC,
					pNetworkScan->pPCIInfo->nasQmisNasSlqsNasPCICellInfo[i].nasQmisNasPcsDigit[j].includes_pcs_digit);
			}
		}

		SockPrintf("   PCI Cell RSRP: %d, RSRP Rx0: %d, RSRP Rx1: %d, RSRQ: %d, RSRQ Rx0: %d, RSRQ Rx1: %d\n",
			pNetworkScan->pPCIInfo->rsrp, pNetworkScan->pPCIInfo->rsrpRx0, pNetworkScan->pPCIInfo->rsrpRx1,
			pNetworkScan->pPCIInfo->rsrq, pNetworkScan->pPCIInfo->rsrqRx0, pNetworkScan->pPCIInfo->rsrqRx1);
	}

	for (uint8_t i = 0; swi_uint256_get_bit(pNetworkScan->ParamPresenceMask, 0x18) && pNetworkScan->pLteOpModeTlv && i < pNetworkScan->pLteOpModeTlv->lteOpModeLen; i++)
	{
		SockPrintf("   LTE Op Mode %d: MCC/MNC: %d/%d, Mode: %d\n", i,
			pNetworkScan->pLteOpModeTlv->MCC[i], pNetworkScan->pLteOpModeTlv->MNC[i], pNetworkScan->pLteOpModeTlv->lteOpMode[i]);
	}

	SockPrintf("\n");
}

void ScanNetworkCallback(uint8_t* qmiPacket, uint16_t qmiPacketSize, void* pContext)
{
	(void)pContext;

	g_NasPendingXid = 0;

	uint8_t	                   NetworkInstanceSize = 1;
	uint8_t                    RATInstanceSize = 1;
	uint8_t                    PCSInstanceSize = 1;
	uint32_t                   ScanResult = 0;
	nas_QmisNasSlqsNasPCIInfo  PCIInfo;
	nas_lteOpModeTlv           LteOpModeTlv;

	unpack_nas_PerformNetworkScan_t output;
	memset(&output, 0, sizeof(output));
	output.p3GppNetworkInstanceSize = &NetworkInstanceSize;
	output.pRATInstanceSize = &RATInstanceSize;
	output.pPCSInstanceSize = &PCSInstanceSize;
	output.pScanResult = &ScanResult;
	output.pPCIInfo = &PCIInfo;
	output.pLteOpModeTlv = &LteOpModeTlv;

	int ret = 0;

	LockSocket();

	do
	{
		if (output.p3GppNetworkInfoInstances)
			free(output.p3GppNetworkInfoInstances);

		output.p3GppNetworkInfoInstances = NetworkInstanceSize == 0 ? NULL : malloc(sizeof(nas_QmiNas3GppNetworkInfo)*NetworkInstanceSize);

		if (NetworkInstanceSize > 0 && output.p3GppNetworkInfoInstances == NULL)
		{
			ret = eQCWWAN_ERR_MEMORY;
			break;
		}

		if (output.pRATINstance)
			free(output.pRATINstance);

		output.pRATINstance = RATInstanceSize == 0 ? NULL : malloc(sizeof(nas_QmiNas3GppNetworkRAT)*RATInstanceSize);

		if (RATInstanceSize > 0 && output.pRATINstance == NULL)
		{
			ret = eQCWWAN_ERR_MEMORY;
			break;
		}

		if (output.pPCSInstance)
			free(output.pPCSInstance);

		output.pPCSInstance = PCSInstanceSize == 0 ? NULL : malloc(sizeof(nas_QmisNasPcsDigit)*PCSInstanceSize);

		if (PCSInstanceSize > 0 && output.pPCSInstance == NULL)
		{
			ret = eQCWWAN_ERR_MEMORY;
			break;
		}

		ret = unpack_nas_PerformNetworkScan(qmiPacket, qmiPacketSize, &output);
		if (ret != eQCWWAN_ERR_NONE && ret != eQCWWAN_ERR_BUFFER_SZ)
			SockPrintf("unpack_nas_PerformNetworkScan: unpacking function error %d\n", ret);
	} while (ret == eQCWWAN_ERR_BUFFER_SZ);

	DisplayResult("unpack_nas_PerformNetworkScan", ret, NULL, (result_func)DisplayPerformNetworkScanResult, (void*)&output);

	UnlockSocket();

	if (output.p3GppNetworkInfoInstances)
		free(output.p3GppNetworkInfoInstances);

	if (output.pRATINstance)
		free(output.pRATINstance);

	if (output.pPCSInstance)
		free(output.pPCSInstance);
}

void DisplayPktStats(unpack_wds_GetPacketStatistics_t* sGetPktStatisticsResp)
{
	SockPrintf("\nPacket Statistics:\n");

	if (swi_uint256_get_bit(sGetPktStatisticsResp->ParamPresenceMask, 0x10))
		SockPrintf("\tTx Packets OK: %d\n", *sGetPktStatisticsResp->pTXPacketSuccesses);
	if (swi_uint256_get_bit(sGetPktStatisticsResp->ParamPresenceMask, 0x11))
		SockPrintf("\tRx Packets OK: %d\n", *sGetPktStatisticsResp->pRXPacketSuccesses);
	if (swi_uint256_get_bit(sGetPktStatisticsResp->ParamPresenceMask, 0x12))
		SockPrintf("\tTx Packets Errors: %d\n", *sGetPktStatisticsResp->pTXPacketErrors);
	if (swi_uint256_get_bit(sGetPktStatisticsResp->ParamPresenceMask, 0x13))
		SockPrintf("\tRx Packets Errors: %d\n", *sGetPktStatisticsResp->pRXPacketErrors);
	if (swi_uint256_get_bit(sGetPktStatisticsResp->ParamPresenceMask, 0x14))
		SockPrintf("\tTx Overflows: %d\n", *sGetPktStatisticsResp->pTXPacketOverflows);
	if (swi_uint256_get_bit(sGetPktStatisticsResp->ParamPresenceMask, 0x15))
		SockPrintf("\tRx Overflows: %d\n", *sGetPktStatisticsResp->pRXPacketOverflows);
	if (swi_uint256_get_bit(sGetPktStatisticsResp->ParamPresenceMask, 0x19))
		SockPrintf("\tTx Bytes OK: %"PRIu64"\n", *sGetPktStatisticsResp->pTXOkBytesCount);
	if (swi_uint256_get_bit(sGetPktStatisticsResp->ParamPresenceMask, 0x1A))
		SockPrintf("\tRx Bytes OK: %"PRIu64"\n", *sGetPktStatisticsResp->pRXOkBytesCount);
	if (swi_uint256_get_bit(sGetPktStatisticsResp->ParamPresenceMask, 0x1B))
		SockPrintf("\tLast Call Tx Bytes OK: %"PRIu64"\n", *sGetPktStatisticsResp->pTXOKBytesLastCall);
	if (swi_uint256_get_bit(sGetPktStatisticsResp->ParamPresenceMask, 0x1C))
		SockPrintf("\tLast Call Rx Bytes OK: %"PRIu64"\n", *sGetPktStatisticsResp->pRXOKBytesLastCall);
	if (swi_uint256_get_bit(sGetPktStatisticsResp->ParamPresenceMask, 0x1D))
		SockPrintf("\tTx Packets Dropped: %d\n", *sGetPktStatisticsResp->pTXDroppedCount);
	if (swi_uint256_get_bit(sGetPktStatisticsResp->ParamPresenceMask, 0x1E))
		SockPrintf("\tRx Packets Dropped: %d\n", *sGetPktStatisticsResp->pRXDroppedCount);
}

void get_pkt_stats()
{
	uint32_t statmask = 0xFF;
	pack_wds_GetPacketStatistics_t sGetPktStatisticsReq;
	memset(&sGetPktStatisticsReq, 0, sizeof(sGetPktStatisticsReq));
	sGetPktStatisticsReq.pStatMask = &statmask;

	uint32_t TXPacketSuccesses;
	uint32_t RXPacketSuccesses;
	uint32_t TXPacketErrors;
	uint32_t RXPacketErrors;
	uint32_t TXPacketOverflows;
	uint32_t RXPacketOverflows;
	uint64_t TXOkBytesCount;
	uint64_t RXOkBytesCount;
	uint64_t TXOKBytesLastCall;
	uint64_t RXOKBytesLastCall;
	uint32_t TXDroppedCount;
	uint32_t RXDroppedCount;
	unpack_wds_GetPacketStatistics_t sGetPktStatisticsResp;
	memset(&sGetPktStatisticsResp, 0, sizeof(sGetPktStatisticsResp));
	sGetPktStatisticsResp.pTXPacketSuccesses = &TXPacketSuccesses;
	sGetPktStatisticsResp.pRXPacketSuccesses = &RXPacketSuccesses;
	sGetPktStatisticsResp.pTXPacketErrors = &TXPacketErrors;
	sGetPktStatisticsResp.pRXPacketErrors = &RXPacketErrors;
	sGetPktStatisticsResp.pTXPacketOverflows = &TXPacketOverflows;
	sGetPktStatisticsResp.pRXPacketOverflows = &RXPacketOverflows;
	sGetPktStatisticsResp.pTXOkBytesCount = &TXOkBytesCount;
	sGetPktStatisticsResp.pRXOkBytesCount = &RXOkBytesCount;
	sGetPktStatisticsResp.pTXOKBytesLastCall = &TXOKBytesLastCall;
	sGetPktStatisticsResp.pRXOKBytesLastCall = &RXOKBytesLastCall;
	sGetPktStatisticsResp.pTXDroppedCount = &TXDroppedCount;
	sGetPktStatisticsResp.pRXDroppedCount = &RXDroppedCount;

	int rtn = SENDRECEIVE(&sessions[0].wdsSvc, pack_wds_GetPacketStatistics, &sGetPktStatisticsReq, unpack_wds_GetPacketStatistics, &sGetPktStatisticsResp);
	DisplayResult(__FUNCTION__, rtn, NULL, (result_func)DisplayPktStats, (void*)&sGetPktStatisticsResp);
}

void modify_profile_by_id(bool bCreate, struct profileInformation* pprofileInfo)
{
	if (pprofileInfo == NULL)
		return;

	pprofileInfo->profileType = PROFILE_TYPE_UMTS;
	uint16_t                  ProfileSize, APNSize, UserSize, PwdSize;

	pack_wds_SLQSModifyProfile_t modifyProfile;
	memset(&modifyProfile, 0, sizeof(modifyProfile));

	modifyProfile.curProfile.SlqsProfile3GPP.pPDPtype = &pprofileInfo->PDPType;
	modifyProfile.curProfile.SlqsProfile3GPP.pIPv4AddrPref = pprofileInfo->IPAddress != 0 ? &pprofileInfo->IPAddress : NULL;
	modifyProfile.curProfile.SlqsProfile3GPP.pPriDNSIPv4AddPref = pprofileInfo->primaryDNS != 0 ? &pprofileInfo->primaryDNS : NULL;
	modifyProfile.curProfile.SlqsProfile3GPP.pSecDNSIPv4AddPref = pprofileInfo->secondaryDNS != 0 ? &pprofileInfo->secondaryDNS : NULL;
	modifyProfile.curProfile.SlqsProfile3GPP.pAuthenticationPref = &pprofileInfo->Authentication;
	if (strlen((const char*)pprofileInfo->profileName) > 0)
	{
		modifyProfile.curProfile.SlqsProfile3GPP.pProfilename = (uint8_t*)pprofileInfo->profileName;
		ProfileSize = strlen((const char*)pprofileInfo->profileName);
		modifyProfile.curProfile.SlqsProfile3GPP.pProfilenameSize = &ProfileSize;
	}
	if (strlen((const char*)pprofileInfo->APNName) > 0)
	{
		modifyProfile.curProfile.SlqsProfile3GPP.pAPNName = (uint8_t*)pprofileInfo->APNName;
		APNSize = strlen((const char*)pprofileInfo->APNName);
		modifyProfile.curProfile.SlqsProfile3GPP.pAPNnameSize = &APNSize;
	}
	if (strlen((const char*)pprofileInfo->userName) > 0)
	{
		modifyProfile.curProfile.SlqsProfile3GPP.pUsername = (uint8_t*)pprofileInfo->userName;
		UserSize = strlen((const char*)pprofileInfo->userName);
		modifyProfile.curProfile.SlqsProfile3GPP.pUsernameSize = &UserSize;
	}
	if (strlen((const char*)pprofileInfo->password) > 0)
	{
		modifyProfile.curProfile.SlqsProfile3GPP.pPassword = (uint8_t*)pprofileInfo->password;
		PwdSize = strlen((const char*)pprofileInfo->password);
		modifyProfile.curProfile.SlqsProfile3GPP.pPasswordSize = &PwdSize;
	}

	int rtn = 0;
	uint8_t profileID = (uint8_t)pprofileInfo->profileNumber;

	if (bCreate)
	{
		pack_wds_SLQSCreateProfile_t createProfile;
		memset(&createProfile, 0, sizeof(createProfile));
		createProfile.pCurProfile = &modifyProfile.curProfile;
		createProfile.pProfileType = &pprofileInfo->profileType;

		PackCreateProfileOut         profileInfoOut;
		memset(&profileInfoOut, 0, sizeof(profileInfoOut));

		unpack_wds_SLQSCreateProfile_t createProfileOut;
		memset(&createProfileOut, 0, sizeof(createProfileOut));
		createProfileOut.pCreateProfileOut = &profileInfoOut;
		createProfileOut.pProfileID = &profileID;

		rtn = SENDRECEIVE(&sessions[0].wdsSvc, pack_wds_SLQSCreateProfile, &createProfile, unpack_wds_SLQSCreateProfile, &createProfileOut);
		DisplayResult("Create profile", rtn, NULL, (result_func)DisplayProfileId, (void*)&profileID);
	}
	else
	{
		modifyProfile.pProfileId = &profileID;
		modifyProfile.pProfileType = &pprofileInfo->profileType;
		//modifyProfile.curProfile.SlqsProfile3GPP.pPDPtype = &pprofileInfo->PDPType;

		uint16_t extendedErrorCode = (uint16_t)-1;

		unpack_wds_SLQSModifyProfile_t modifyProfileOut;
		memset(&modifyProfileOut, 0, sizeof(modifyProfileOut));
		modifyProfileOut.pExtErrorCode = &extendedErrorCode;

		rtn = SENDRECEIVE(&sessions[0].wdsSvc, pack_wds_SLQSModifyProfile, &modifyProfile, unpack_wds_SLQSModifyProfile, &modifyProfileOut);
		DisplayResult("Modify profile", rtn, NULL, (result_func)DisplayProfileId, (void*)&profileID);
	}
}

/*
 * Name:     modify_profile_settings
 *
 * Purpose:  Modify the Profile settings of the profile id selected by the user
 *           with the values entered by the user.
 *
 * Params:   None
 *
 * Return:   None
 *
 * Notes:    None
 */
void modify_profile_settings(bool bCreate)
{
	/* Display all the profiles stored on the device */
	display_all_profiles(!bCreate);

	if (0 == indexInfo.totalProfilesOnDevice && !bCreate)
	{
		SockLog(eLOG_ERROR, "No Profile exist on device for modification or check device connectivity\n\n");
		return;
	}

	uint8_t profileIdMatch = bCreate ? TRUE : FALSE;
	struct profileInformation profileInfo;
	memset(&profileInfo, 0, sizeof(profileInfo));

	while (!profileIdMatch)
	{
		/* Prompt the user to enter the profile id whose values need to be
			* modified.
			*/
		profileInfo.profileNumber = GetUserProfileId(MIN_PROFILES, MAX_PROFILES);

		/* If only <ENTER> is pressed by the user, return to main menu */
		if (ENTER_KEY_PRESSED == profileInfo.profileNumber)
			return;

		/* If the user has enter an invalid profile id */
		for (int idx = 0; idx < indexInfo.totalProfilesOnDevice && !profileIdMatch; idx++)
		{
			profileIdMatch = profileInfo.profileNumber == indexInfo.profileIndex[idx];
		}
	}

	if (GetProfileInfo(&profileInfo) != ENTER_KEY)
		modify_profile_by_id(bCreate, &profileInfo);
}

/******************************************************************************
* Option 5 : Display the settings for a particular profile stored on the device
******************************************************************************/

void display_profile_header()
{
	/* Display the header */
	int w3 = -3, w5 = -5, w8 = -8, w20 = -20;
	SockPrintf("\n%*s%*s%*s%*s%*s%*s%*s%*s%*s\n",
		w3, "ID", w8, "PDPType", w20, "IPAddress",
		w20, "PrimaryDNS", w20, "SecondaryDNS", w5, "Auth", w20, "ProfileName",
		w20, "APNName", w20, "UserName");
}

/*
 * Name:     display_profile_info
 *
 * Purpose:  Display the profile information for the profile index provided by
 *           the user.
 *
 * Params:   None
 *
 * Return:   None.
 *
 * Notes:    None
 */
void display_profile_info(uint8_t profileId, bool bDisplayHeader, bool bUpdateCache)
{
	int rtn;
	unpack_wds_SLQSGetProfileSettings_t profileSettingsRsp;
	UnPackGetProfileSettingOut profileSetOut;
	uint8_t profileType = PROFILE_TYPE_UMTS;
	uint8_t PDPType = (uint8_t)-1;
	uint32_t IPAddress = (uint32_t)-1;
	char  bufIPAddress[MAX_FIELD_SIZE];
	uint32_t primaryDNS = (uint32_t)-1;
	char  bufPrimaryDNS[MAX_FIELD_SIZE];
	uint32_t secondaryDNS = (uint32_t)-1;
	char  bufSecondaryDNS[MAX_FIELD_SIZE];
	uint8_t authentication = (uint8_t)-1;
	uint8_t  profileName[MAX_PROFILE_NAME_SIZE];
	uint16_t profileNameSize;
	uint8_t  APNName[MAX_APN_SIZE];
	uint16_t APNNameSize;
	uint8_t  Username[MAX_USER_NAME_SIZE];
	uint16_t UsernameSize;
	uint16_t  extendedErrorCode = (uint16_t)-1;
	int w3 = -3, w5 = -5, w8 = -8, w20 = -20;

	memset(&profileSettingsRsp, 0, sizeof(profileSettingsRsp));
	memset(&profileSetOut, 0, sizeof(UnPackGetProfileSettingOut));
	memset(profileName, 0, MAX_PROFILE_NAME_SIZE);
	memset(APNName, 0, MAX_APN_SIZE);
	memset(Username, 0, MAX_USER_NAME_SIZE);
	profileNameSize = sizeof(profileName);
	APNNameSize = sizeof(APNName);
	UsernameSize = sizeof(Username);
	profileSettingsRsp.pProfileSettings = &profileSetOut;
	profileSettingsRsp.pProfileSettings->curProfile.SlqsProfile3GPP.pPDPtype = &PDPType;
	profileSettingsRsp.pProfileSettings->curProfile.SlqsProfile3GPP.pIPv4AddrPref = &IPAddress;
	profileSettingsRsp.pProfileSettings->curProfile.SlqsProfile3GPP.pPriDNSIPv4AddPref = &primaryDNS;
	profileSettingsRsp.pProfileSettings->curProfile.SlqsProfile3GPP.pSecDNSIPv4AddPref = &secondaryDNS;
	profileSettingsRsp.pProfileSettings->curProfile.SlqsProfile3GPP.pAuthenticationPref = &authentication;
	profileSettingsRsp.pProfileSettings->curProfile.SlqsProfile3GPP.pProfilename = profileName;
	profileSettingsRsp.pProfileSettings->curProfile.SlqsProfile3GPP.pProfilenameSize = &profileNameSize;
	profileSettingsRsp.pProfileSettings->curProfile.SlqsProfile3GPP.pAPNName = APNName;
	profileSettingsRsp.pProfileSettings->curProfile.SlqsProfile3GPP.pAPNnameSize = &APNNameSize;
	profileSettingsRsp.pProfileSettings->curProfile.SlqsProfile3GPP.pUsername = Username;
	profileSettingsRsp.pProfileSettings->curProfile.SlqsProfile3GPP.pUsernameSize = &UsernameSize;
	profileSettingsRsp.pProfileSettings->pExtErrCode = &extendedErrorCode;

	pack_wds_SLQSGetProfileSettings_t reqarg;
	reqarg.ProfileId = profileId;
	reqarg.ProfileType = profileType;

	rtn = SENDRECEIVE(&sessions[0].wdsSvc, pack_wds_SLQSGetProfileSettings, &reqarg, unpack_wds_SLQSGetProfileSettings, &profileSettingsRsp);
	if (rtn != eLITE_CONNECT_APP_OK)
	{
		SockLog(eLOG_DEBUG, "Profile retrieving Failed. Cause - %d, Error Code - %d\n\n",
			rtn, (int)extendedErrorCode);
		return;
	}

	if (profileSettingsRsp.pProfileSettings->curProfile.SlqsProfile3GPP.pProfilename == NULL)
		strcpy((char*)profileName, "Unknown");
	if (profileSettingsRsp.pProfileSettings->curProfile.SlqsProfile3GPP.pAPNName == NULL)
		strcpy((char*)APNName, "Unknown");
	if (profileSettingsRsp.pProfileSettings->curProfile.SlqsProfile3GPP.pUsername == NULL)
		strcpy((char*)Username, "Unknown");

	/* Reset the buffers */
	memset(bufIPAddress, 0, MAX_FIELD_SIZE);
	memset(bufPrimaryDNS, 0, MAX_FIELD_SIZE);
	memset(bufSecondaryDNS, 0, MAX_FIELD_SIZE);

	/* Convert ULONG to Dot notation for display */
	inet_ntop(AF_INET, &IPAddress, bufIPAddress, MAX_FIELD_SIZE);
	inet_ntop(AF_INET, &primaryDNS, bufPrimaryDNS, MAX_FIELD_SIZE);
	inet_ntop(AF_INET, &secondaryDNS, bufSecondaryDNS, MAX_FIELD_SIZE);

	if (bDisplayHeader)
		display_profile_header();
		
	/* Display the retrieved profile information */
	SockPrintf("%*d%*u%*s%*s%*s%*u%*s%*s%*s\n",
		w3, profileId, w8, PDPType, w20, bufIPAddress,
		w20, bufPrimaryDNS, w20, bufSecondaryDNS, w5, authentication,
		w20, profileName, w20, APNName, w20, Username);

	if (bUpdateCache)
	{
		/* Store the profile indexes for successfully retrieved profiles */
		indexInfo.profileIndex[indexInfo.totalProfilesOnDevice] = profileId;
		indexInfo.totalProfilesOnDevice++;
	}
}

void display_profile()
{
	while (1)
	{
		/* Receive the user input */
		// marc modification
		uint8_t profileId = GetUserProfileId(MIN_PROFILES, MAX_PROFILES);

		/* If only <ENTER> is pressed by the user, return to main menu */
		if (ENTER_KEY_PRESSED == profileId)
			return;

		display_profile_info(profileId, true, false);
	}
}

/*************************************************************************
* Option 4 : Display all the profiles stored on the device
*************************************************************************/

/*
 * Name:     display_all_profiles
 *
 * Purpose:  Display all the profiles stored on the device.
 *
 * Params:   None
 *
 * Return:   None
 *
 * Notes:    None
 */
void display_all_profiles(bool bShowNoProfile)
{
	display_profile_header();

	indexInfo.totalProfilesOnDevice = 0;

	/* Retrieve the information for all the profiles loaded on the device */
	for (uint8_t profileId = MIN_PROFILES; profileId <= MAX_PROFILES; profileId++)
		display_profile_info(profileId, false, true);

	if (0 == indexInfo.totalProfilesOnDevice && bShowNoProfile)
		SockLog(eLOG_ERROR, "No Profile exist on the device or check device connectivity\n\n");
}

void datasession_stopped(struct session* pSession)
{
	pSession->active = false;
	pSession->sid = 0;
	pSession->mtu = 0xFFFFFFFF;

	if (pSession->uIPCount > 0)
		pSession->uIPCount--;

	if (g_update_route && strlen(setrouteTable[pSession->idx][pSession->uIPCount].dst) > 0)
		SetRoute(pSession->domain,
			setrouteTable[pSession->idx][pSession->uIPCount].szif,
			false,
			setrouteTable[pSession->idx][pSession->uIPCount].dst,
			pSession->domain == AF_INET ? nMaskPrefLenV4 : nMaskPrefLenV6,
			setrouteTable[pSession->idx][pSession->uIPCount].gw);

	if (g_ip_auto_assign)
		SetAdaptorAddress(pSession->domain, setrouteTable[pSession->idx][pSession->uIPCount].szif,
			false, pSession->ip, pSession->prefixlen);

	// If a session sharing the same networking interface is still active, do not bring it down
	if (sessions[pSession->domain == AF_INET ? pSession->idx + 1 : pSession->idx - 1].active)
		return;

	if (g_vlan_added || g_bRmNet)
		DownAdaptorInterface(pSession->ifname);

	if (g_vlan_added)
		DeleteVlan(pSession->ifname);

	for (int i = 0; i < NUM_WDS_SVC; i++)
	{
		if (sessions[i].active)
			return;	// There are data sessions still active
	}

	DownAdaptorInterface(szEthName);

	// All data sessions are down
	g_connection_state = NONE;

	g_vlan_added = false;
	g_default_dev = szEthName;
	g_nMtu = 0xFFFFFFFF;
}

/*
 * Name:     stop_datasession
 *
 * Purpose:  Stop the ongoing data session
 *
 * Params:   None
 *
 * Return:   None
 *
 * Notes:    None
 */
void stop_datasession(int session)
{
	if (session >= NUM_WDS_SVC || !sessions[session].active || sessions[session].sid == 0)
		return;

	pack_wds_SLQSStopDataSession_t stopSession;
	memset(&stopSession, 0, sizeof(stopSession));
	stopSession.psid = &sessions[session].sid;

	unpack_wds_SLQSStopDataSession_t resp;
	memset(&resp, 0, sizeof(unpack_wds_SLQSStopDataSession_t));

	int nIP = sessions[session].domain == AF_INET ? IPV4 : IPV6;
	int rtn = SENDRECEIVE(&sessions[session].wdsSvc, pack_wds_SLQSStopDataSession, &stopSession, unpack_wds_SLQSStopDataSession, &resp);

	if (rtn == 1026)	// QMI_ERR_NO_EFFECT, already stopped
		rtn = eLITE_CONNECT_APP_OK;

	SockLog(eLOG_INFO, "data session (ipv%d) %sstopped\n", nIP, rtn != eLITE_CONNECT_APP_OK ? "not " : "");

	if (rtn != eLITE_CONNECT_APP_OK)
		return;

	datasession_stopped(&sessions[session]);
}

void stop_all_datasessions()
{
	for (int i = 0; i < NUM_WDS_SVC; i++)
	{
		stop_datasession(i);
	}
}

void stop_one_datasession()
{
	int session = -1;
	session = GetDataSession();
	if (session == -1)
	{
		return;
	}
	stop_datasession(session);
}

int GetNextIdxOnSameIf(int idx)
{
	switch (idx)
	{
	case 0:
		return 1;
	case 1:
		return 0;
	case 2:
		return 3;
	case 3:
		return 2;
	case 4:
		return 5;
	case 5:
		return 4;
	case 6:
		return 7;
	case 7:
		return 6;
	default:
		break;
	}

	return 0;
}

/*************************************************************************
 * Option 2 : Start LTE Data Session
 ************************************************************************/

int UpdateIPRuntimeSettings(unpack_wds_SLQSGetRuntimeSettings_t *runtime, int nIdx, uint8_t isMultiPdn)
{
	if (runtime == NULL)
	{
		SockLog(eLOG_ERROR, "%s runtime data structure is NULL\n", __FUNCTION__);
		return 0;
	}

	swi_uint256_print_mask(runtime->ParamPresenceMask);

	const char* szIf = isMultiPdn == 0 ? szEthName : sessions[nIdx].ifname;
	char szFullIf[MAX_IFLEN*2+1];
	if (isMultiPdn == 0)
		strcpy(szFullIf, szEthName);
	else
		sprintf(szFullIf, "%s:%s", szEthName, szIf);

	char szGWAddress[INET6_ADDRSTRLEN] = { 0 };

	if (sessions[nIdx].domain == AF_INET)
	{
		// IPv4
		if (!swi_uint256_get_bit(runtime->ParamPresenceMask, 0x1E) ||	// IPv4
			!swi_uint256_get_bit(runtime->ParamPresenceMask, 0x20) ||	// IPv4 Gateway Address
			!swi_uint256_get_bit(runtime->ParamPresenceMask, 0x21) ||	// IPv4 Subnet Mask
			!swi_uint256_get_bit(runtime->ParamPresenceMask, 0x29))		// MTU
		{
			SockLog(eLOG_WARN, "%s(%d): No runtime IPv4 Info\n", __FUNCTION__, nIdx);
			return 0;
		}

		struct in_addr ip_addr;
		ip_addr.s_addr = htonl(runtime->IPv4);
		inet_ntop(AF_INET, &ip_addr, sessions[nIdx].ip, INET6_ADDRSTRLEN);

		struct in_addr gw_addr;
		gw_addr.s_addr = htonl(runtime->GWAddressV4);
		inet_ntop(AF_INET, &gw_addr, szGWAddress, sizeof(szGWAddress));

		sessions[nIdx].prefixlen = Mask2PrefixLenV4(runtime->SubnetMaskV4);
		sessions[nIdx].uIPCount++;
	}
	else
	{
		struct in6_addr ipv6;

		// IPv6
		if (inet_ntop(AF_INET6, htonl6(runtime->IPV6AddrInfo.IPAddressV6, &ipv6), sessions[nIdx].ip, INET6_ADDRSTRLEN))
			sessions[nIdx].uIPCount++;

		inet_ntop(AF_INET6, htonl6(runtime->IPV6GWAddrInfo.gwAddressV6, &ipv6), szGWAddress, sizeof(szGWAddress));
		sessions[nIdx].prefixlen = runtime->IPV6AddrInfo.IPV6PrefixLen;
	}

	if (swi_uint256_get_bit(runtime->ParamPresenceMask, 0x32))
	{
		// Output NSSAI PDN Info
		SockPrintf("NSSAI PDN Info\n");
		SockPrintf("  pduSessionId: %d\n", runtime->NssaiPdnInfo.pduSessionId);
		SockPrintf("  snssaiInfoIsValid: %d\n", runtime->NssaiPdnInfo.snssaiInfoIsValid);
		SockPrintf("  sst: %d\n", runtime->NssaiPdnInfo.sst);
		SockPrintf("  sd: 0x%02X%02X%02X\n", runtime->NssaiPdnInfo.sd[0], runtime->NssaiPdnInfo.sd[1], runtime->NssaiPdnInfo.sd[2]);
		SockPrintf("  mappingSstPresent: %d\n", runtime->NssaiPdnInfo.mappingSstPresent);
		SockPrintf("  mappedSst: %d\n", runtime->NssaiPdnInfo.mappedSst);
		SockPrintf("  mappedSd: 0x%02X%02X%02X\n", runtime->NssaiPdnInfo.mappedSd[0], runtime->NssaiPdnInfo.mappedSd[1], runtime->NssaiPdnInfo.mappedSd[2]);
		SockPrintf("  isSnssaiResolved: %d\n", runtime->NssaiPdnInfo.isSnssaiResolved);
		SockPrintf("  plmnId: 0x%02X%02X%02X\n", runtime->NssaiPdnInfo.plmnId[0], runtime->NssaiPdnInfo.plmnId[1], runtime->NssaiPdnInfo.plmnId[2]);
	}

	/* command to set mtu size */
	if (g_mtu_auto_update_enable && (runtime->Mtu != 0xFFFFFFFF) && (runtime->Mtu != 68)) // minimum mtu size is 68
	{
		sessions[nIdx].mtu = runtime->Mtu;

		// Set MTU of the only connection on the APN or the lesser value between V4 and V6
		if (runtime->Mtu < sessions[GetNextIdxOnSameIf(nIdx)].mtu)
		{
			SetAdaptorMtu(szIf, runtime->Mtu);

			if (isMultiPdn)
			{
				// MPDN.  Set higher MTU vaule to the parent interface
				unsigned int nIfMtu = runtime->Mtu;
				for (int i = 0; i <= nIdx; i += 2)
				{
					// Take the lesser MTU between IPv4 and IPv6 MTUs
					unsigned int nMinMtu = sessions[i].mtu < sessions[i + 1].mtu ? sessions[i].mtu : sessions[i + 1].mtu;
					if (nMinMtu > nIfMtu)
						nIfMtu = nMinMtu;	// Take the larger value amount different PDN
				}

				if (nIfMtu != g_nMtu)
				{
					g_nMtu = nIfMtu;
					SetAdaptorMtu(szEthName, nIfMtu);
				}
			}
		}
	}

	/* set ip address to driver */
	if (g_ip_auto_assign)
	{
		SetAdaptorAddress(sessions[nIdx].domain, szFullIf, true, sessions[nIdx].ip, sessions[nIdx].prefixlen);//isMultiPdn ? 0 : sessions[nIdx].mask);

		/* after setting the ip address, network adapter need sometime to become ready */
		int timeout = 0;
		while ((IsAdaptorUp(szEthName) == 0 || (isMultiPdn && IsAdaptorUp(szIf) == 0)) && timeout++ < 3)
			sleep(1);
	}

	if (sessions[nIdx].uIPCount > 0 && sessions[nIdx].uIPCount <= MAX_QMAP_INSTANCE)
	{
		StrCpy(setrouteTable[nIdx][sessions[nIdx].uIPCount - 1].szif, szIf);
		if (sessions[nIdx].domain != AF_INET)
			StrCpy(setrouteTable[nIdx][sessions[nIdx].uIPCount - 1].gw, isMultiPdn ? sessions[nIdx].ip : szGWAddress);

		if (g_update_route && strlen(setrouteTable[nIdx][sessions[nIdx].uIPCount - 1].dst) > 0)
			SetRoute(sessions[nIdx].domain, szIf, true, setrouteTable[nIdx][sessions[nIdx].uIPCount - 1].dst,
				sessions[nIdx].domain == AF_INET ? nMaskPrefLenV4 : nMaskPrefLenV6,
				setrouteTable[nIdx][sessions[nIdx].uIPCount - 1].gw);
	}

	if (strlen(pingTable[nIdx][sessions[nIdx].uIPCount - 1]) > 0 && g_auto_test_enable)
		ping(sessions[nIdx].domain == AF_INET ? IPV4 : IPV6, pingTable[nIdx][sessions[nIdx].uIPCount - 1], PING_COUNT, PING_DELAY);

	return 1;
}

int DisplayRuntimeSettings(int nIdx, uint8_t isMultiPdn)
{
	pack_wds_SLQSGetRuntimeSettings_t runtimeSettings;
	uint32_t reqSettings = 0x10A314;	// NSSAI/Get IP Family/MTU/IP Address/DNS Address/PDP type
	memset(&runtimeSettings, 0, sizeof(pack_wds_SLQSGetRuntimeSettings_t));
	runtimeSettings.pReqSettings = &reqSettings;

	unpack_wds_SLQSGetRuntimeSettings_t runtimeSettingsOut;
	memset(&runtimeSettingsOut, 0, sizeof(unpack_wds_SLQSGetRuntimeSettings_t));

	int rtn = SENDRECEIVE(&sessions[nIdx].wdsSvc, pack_wds_SLQSGetRuntimeSettings, &runtimeSettings, unpack_wds_SLQSGetRuntimeSettings, &runtimeSettingsOut);
	if (rtn != eLITE_CONNECT_APP_OK)
	{
		SockPrintf("Failed to get runtime settings\n");
		update_user_display(eIP_ADDRESS, "UNAVAILABLE");
	}
	else
	{
		char  bufIPAddress[INET6_ADDRSTRLEN];
		memset(bufIPAddress, 0, INET6_ADDRSTRLEN);

		if (sessions[nIdx].domain == AF_INET)
		{
			if (runtimeSettingsOut.IPv4 == 0)
				return -1;

			inet_ntop(AF_INET, &runtimeSettingsOut.IPv4, bufIPAddress, INET6_ADDRSTRLEN);
		}
		else
		{
			if (memcmp(&runtimeSettingsOut.IPV6AddrInfo.IPAddressV6, bufIPAddress, sizeof(runtimeSettingsOut.IPV6AddrInfo.IPAddressV6)) == 0)
				return -1;

			struct in6_addr ipv6;
			inet_ntop(AF_INET6, htonl6(runtimeSettingsOut.IPV6AddrInfo.IPAddressV6, &ipv6), bufIPAddress, INET6_ADDRSTRLEN);
		}

		update_user_display(eIP_ADDRESS, bufIPAddress);
	}

	if (rtn == eLITE_CONNECT_APP_OK)
	{
		/* Update the runtime settings field of the user window */
		UpdateIPRuntimeSettings(&runtimeSettingsOut, nIdx, isMultiPdn);
	}

	return rtn;
}

/*
 * Name:     DisplaySessionState
 *
 * Purpose:  Display the information about the connected device
 *
 * Params:   None
 *
 * Return:   None
 *
 * Notes:    None
 */
int DisplaySessionState(int nIdx, uint8_t isMultiPdn)
{
	unpack_wds_GetSessionState_t sessionState;
	memset(&sessionState, 0, sizeof(unpack_wds_GetSessionState_t));

	int rtn = SENDRECEIVENOINPUT(&sessions[nIdx].wdsSvc, pack_wds_GetSessionState, unpack_wds_GetSessionState, &sessionState);
	if (rtn != eLITE_CONNECT_APP_OK)
	{
		SockLog(eLOG_ERROR, "Failed to get session state (%d:ipv%d)\n", nIdx, sessions[nIdx].domain == AF_INET ? IPV4 : IPV6);
		update_user_display(eSESSION_STATE, "UNAVAILABLE");
	}
	else
	{
		char* pStatus = "unknown";
		switch (sessionState.connectionStatus)
		{
		case 1:
			pStatus = "Disconnected";
			break;
		case 2:
			pStatus = "Connected";
			break;
		case 3:
			pStatus = "Suspended";
			break;
		case 4:
			pStatus = "Authenticating";
			break;
		default:
			break;
		}

		SockPrintf("SessionStatus (%d:ipv%d): %s\n", nIdx, sessions[nIdx].domain == AF_INET ? IPV4 : IPV6, pStatus);
		update_user_display(eSESSION_STATE, pStatus);
	}

	if (sessionState.connectionStatus == 2)	// Connected
	{
		sleep(2);
		if ((rtn = DisplayRuntimeSettings(nIdx, isMultiPdn)) != 0)
			SockPrintf("Unable to obtain IP address\n");
	}

	return rtn;
}

bool get_rmnet_value()
{
	bool bRmNet = false;

	if (get_rmnet(&s_CtlService, &bRmNet) != eQCWWAN_ERR_NONE)
		return false;

	g_bRmNet = bRmNet;

	if (g_bRmNet && g_mode == QMUX_INTERFACE_MBIM)
	{
		SockPrintf("Device mode set to QMI\n");
		g_mode = QMUX_INTERFACE_DIRECT;
	}

	return true;
}

bool PowerUp()
{
	if (!g_online)
	{
		pack_dms_SetPower_t sSetPower;
		memset(&sSetPower, 0, sizeof(sSetPower));

		unpack_dms_SetPower_t sUnpackSetPower;
		memset(&sUnpackSetPower, 0, sizeof(unpack_dms_SetPower_t));

		g_online = SENDRECEIVE(&s_DmsService, pack_dms_SetPower, &sSetPower, unpack_dms_SetPower, &sUnpackSetPower) == eLITE_CONNECT_APP_OK;

		if (!g_online)
			SockPrintf("Unable to bring device online\n");
	}

	return g_online;
}

bool SetNetSelPref(struct netSelectionPref* pNetSelPref)
{
	if (pNetSelPref->netReg == 1 || pNetSelPref->netReg != g_NetSelPref)
	{
		struct nas_netSelectionPref netSelPref;
		netSelPref.netReg = pNetSelPref->netReg;
		netSelPref.mcc = pNetSelPref->mcc;
		netSelPref.mnc = pNetSelPref->mnc;

		pack_nas_SLQSSetSysSelectionPrefExt_t setNetSelPref;
		unpack_nas_SLQSSetSysSelectionPrefExt_t setNetSelPrefOut;
		memset(&setNetSelPref, 0, sizeof(pack_nas_SLQSSetSysSelectionPrefExt_t));
		memset(&setNetSelPrefOut, 0, sizeof(unpack_nas_SLQSSetSysSelectionPrefExt_t));
		setNetSelPref.pNetSelPref = &netSelPref;
		int rtn = SENDRECEIVE(&s_NasService, pack_nas_SLQSSetSysSelectionPrefExt, &setNetSelPref, unpack_nas_SLQSSetSysSelectionPrefExt, &setNetSelPrefOut);
		if (rtn != eLITE_CONNECT_APP_OK)
		{
			SockLog(eLOG_ERROR, "fail to set network selection preference. Error: %d\n", rtn);
			return false;
		}

		g_NetSelPref = pNetSelPref->netReg;
	}

	return true;
}

bool SetIpFamilyPref(int idx)
{
	pack_wds_SLQSSetIPFamilyPreference_t setIPfamily;
	memset(&setIPfamily, 0, sizeof(setIPfamily));
	setIPfamily.IPFamilyPreference = sessions[idx].domain == AF_INET ? IPv4_FAMILY_PREFERENCE : IPv6_FAMILY_PREFERENCE;

	unpack_wds_SLQSSetIPFamilyPreference_t setIPfamilyOut;
	memset(&setIPfamilyOut, 0, sizeof(setIPfamilyOut));

	int rtn = SENDRECEIVE(&sessions[idx].wdsSvc, pack_wds_SLQSSetIPFamilyPreference, &setIPfamily, unpack_wds_SLQSSetIPFamilyPreference, &setIPfamilyOut);
	SockLog(eLOG_INFO, "\nWDS[%d] setIPFamily preference %d returns %d\n", idx, setIPfamily.IPFamilyPreference, rtn);

	return rtn == 0;
}

bool SetMuxId(int idx, uint8_t nMuxID)
{
	// wds-bind-mux-data-port to bind the qmux ID.
	uint32_t nEpType = 2;	// HSUSB
	uint32_t nIfId = (uint32_t)g_rmnet_if_id;
	uint32_t nClientType = 1;	// Tethered
	pack_wds_SetMuxID_t tpack_wds_SetMuxID;
	memset(&tpack_wds_SetMuxID, 0, sizeof(tpack_wds_SetMuxID));

	if (g_bRmNet)
	{
		nMuxID++;
		tpack_wds_SetMuxID.pEpType = &nEpType;
		tpack_wds_SetMuxID.pIfId = &nIfId;
		tpack_wds_SetMuxID.pClientType = &nClientType;
	}

	tpack_wds_SetMuxID.pMuxID = &nMuxID;
	unpack_wds_SetMuxID_t tunpack_wds_SetMuxID;
	memset(&tunpack_wds_SetMuxID, 0, sizeof(tunpack_wds_SetMuxID));

	int rtn = SENDRECEIVE(&sessions[idx].wdsSvc, pack_wds_SetMuxID, &tpack_wds_SetMuxID, unpack_wds_SetMuxID, &tunpack_wds_SetMuxID);
	SockLog(eLOG_INFO, "WDS[%d] BindMuxID %d returns %d\n", idx, nMuxID, rtn);

	return rtn == 0;
}

bool DoConnection(int idx, struct profileInformation* pprofileInfo)
{
	int rtn = eLITE_CONNECT_APP_OK;

	uint32_t failReason = 0;
	unpack_wds_SLQSStartDataSession_t startSessionOut;
	memset(&startSessionOut, 0, sizeof(startSessionOut));

	startSessionOut.psid = &sessions[idx].sid;
	startSessionOut.pFailureReason = &failReason;

	if (pprofileInfo->profileNumber == 0)
	{
		pack_wds_SLQSStartDataSessionExp_t startSessionExp;
		memset(&startSessionExp, 0, sizeof(startSessionExp));

		if (strlen(pprofileInfo->APNName) > 0)
			startSessionExp.pApnName = pprofileInfo->APNName;
		
		uint32_t authType = pprofileInfo->Authentication;
		if (authType != 0)
		{
			startSessionExp.pAuthenticationPreference = &authType;
			if (strlen(pprofileInfo->userName) > 0)
				startSessionExp.pUserName = pprofileInfo->userName;
			if (strlen(pprofileInfo->password) > 0)
				startSessionExp.pPassword = pprofileInfo->password;
		}
		
		SockLog(eLOG_INFO, "Starting data session via APN \"%s\"\n", startSessionExp.pApnName);

		rtn = SENDRECEIVE(&sessions[idx].wdsSvc, pack_wds_SLQSStartDataSessionExp, &startSessionExp, unpack_wds_SLQSStartDataSession, &startSessionOut);
	}
	else
	{
		uint32_t profileId3gpp = pprofileInfo->profileNumber;
		pack_wds_SLQSStartDataSession_t startSession;
		memset(&startSession, 0, sizeof(startSession));

		startSession.pprofileid3gpp = &profileId3gpp;

		SockLog(eLOG_INFO, "Starting data session via profile %d\n", *startSession.pprofileid3gpp);

		rtn = SENDRECEIVE(&sessions[idx].wdsSvc, pack_wds_SLQSStartDataSession, &startSession, unpack_wds_SLQSStartDataSession, &startSessionOut);
	}

	if (rtn != eLITE_CONNECT_APP_OK)
		SockLog(eLOG_ERROR, "WDS[%d] failed to start data session. Failure cause - %d, Error Code - %u\n", idx, rtn, failReason);
	else
	{
		if (pprofileInfo->profileNumber == 0)
			SockLog(eLOG_INFO, "WDS[%d] IPv%d data session started successfully on %s\n",
				idx, sessions[idx].domain == AF_INET ? IPv4_FAMILY_PREFERENCE : IPv6_FAMILY_PREFERENCE, pprofileInfo->APNName);
		else
			SockLog(eLOG_INFO, "WDS[%d] IPv%d data session started successfully for Profile ID: %u\n", 
				idx, sessions[idx].domain == AF_INET ? IPv4_FAMILY_PREFERENCE : IPv6_FAMILY_PREFERENCE, pprofileInfo->profileNumber);

		sessions[idx].active = true;
		update_user_display(eCALL_STATUS, "CONNECTED");

		rtn = DisplaySessionState(idx, g_vlan_added || g_bRmNet);
	}

	return rtn == 0;
}

/*
 * Name:     start_datasession
 *
 * Purpose:  Starts a Data Session
 *
 * Params:   
 *			 
 *
 * Return:   None
 *
 * Notes:    None
 */
void start_datasession(struct netSelectionPref* pNetSelPref, struct profileInformation* pprofileInfo)
{
	for (int i = 0; i < NUM_WDS_SVC; i++)
	{
		if (sessions[i].active)
		{
			SockLog(eLOG_INFO, "Data session is already established, only one instance is supported\n\n");
			return;
		}
	}

	if (!SetNetSelPref(pNetSelPref))
		return;

	g_default_dev = szEthName;
		
	// Reset MTU
	g_nMtu = 0xFFFFFFFF;

	int i = SPDN_CONN_START;	// Where to start in the loop
	int limit = SPDN_LIMIT;

	int increament = 2;	// How much to increase in the loop, default for IPv4 or IPv6 only
	if (pprofileInfo->PDPType == IPv4v6_FAMILY_PREFERENCE)
		increament = 1;	// Increase by 1 to cover both IPv4 and IPv6
#if FIRST_CONNECTION_IPV6
	else if (pprofileInfo->PDPType == IPv4_FAMILY_PREFERENCE)
		i--;	// Start from IPv4

	for (; i >= limit; i -= increament)	// HSWOEMP-1595 Make IPv6 connection before IPv4
#else
	else if (pprofileInfo->PDPType == IPv6_FAMILY_PREFERENCE)
		i++;	// Start from IPv6

	for (; i < limit; i += increament)
#endif
	{
		if (g_vlan_added || g_bRmNet)
		{
			SetMuxId(i, i / 2);
		}
		
		SetIpFamilyPref(i);

		DoConnection(i, pprofileInfo);
	}

	g_connection_state = SINGLE;
}

void start_multipdn_datasession(struct netSelectionPref* pNetSelPref, struct profileInformation* pprofileInfo, bool bSingle)
{
	if (g_connection_state == SINGLE)
	{
		SockLog(eLOG_INFO, "Stop current data session before starting a multipdn data session\n\n");
		return;
	}

	int sessionNumber = -1;
	int maxSession = g_netnum_val < NUM_WDS_SVC ? g_netnum_val : NUM_WDS_SVC;
	for (int i = 0; i < maxSession; i += 2)
	{
		if (!sessions[i].active && !sessions[i + 1].active)
		{
			sessionNumber = i;
			break;
		}
	}

	if (sessionNumber == 0)
	{
		// Reset MTU
		g_nMtu = 0xFFFFFFFF;
	}

	if (sessionNumber == -1)
	{
		SockLog(eLOG_INFO, "Maximum supported number of data sessions are currently active\n\n");
		return;
	}

	if (!SetNetSelPref(pNetSelPref))
		return;

	if (!g_bRmNet)
	{
		if (AddVlan(szEthName, sessions[sessionNumber].ifname, sessions[sessionNumber].ifid) < 0)
		{
			SockLog(eLOG_ERROR, "Unable to add VLAN %s:%d for multiple PDN\n\n", sessions[sessionNumber].ifname, sessions[sessionNumber].ifid);
			return;
		}
		
		g_vlan_added = true;
	}

	g_default_dev = sessions[0].ifname;

	int i = sessionNumber + 1;	// Where to start in the loop
	int limit = i - 1;
	int increment = 2;	// How much to increase in the loop, default for IPv4 or IPv6 only
	if (pprofileInfo->PDPType == IPv4v6_FAMILY_PREFERENCE)
		increment = 1;	// Increase by 1 to cover both IPv4 and IPv6
#if FIRST_CONNECTION_IPV6
	else if (pprofileInfo->PDPType == IPv4_FAMILY_PREFERENCE)
		i--;	// Start from IPv4

	for (; i >= limit; i -= increment)	// HSWOEMP-1595 Make IPv6 connection before IPv4
#else
	else if (pprofileInfo->PDPType == IPv6_FAMILY_PREFERENCE)
		i++;	// Start from IPv6

	for (; i < limit; i += increament)
#endif
	{
		SetMuxId(i, sessionNumber / 2);

		SetIpFamilyPref(i);

		DoConnection(i, pprofileInfo);
	}

	g_connection_state = bSingle ? SINGLE : MULTIPDN;
}

void initiate_datasession(bool bMpdn, bool bSingle)
{
	if (!PowerUp())
		return;

	if (g_connection_state == SINGLE)
	{
		SockLog(eLOG_INFO, "Stop current data session before starting a new data session\n\n");
		return;
	}
	else if (g_connection_state == MULTIPDN && bSingle)
	{
		SockLog(eLOG_INFO, "Stop current multiple data sessions before starting a new single data session\n\n");
		return;
	}

	struct netSelectionPref netSelPref;
	GetUserNetworkSelectionPreference(&netSelPref);

	struct profileInformation profileInfo;
	if (GetConnectionProfileInfo(&profileInfo) == 0)
	{
		/* handle data connection for NON-SL9090 modules */
		/* Display all the profiles stored on the device */
		display_all_profiles(false);

		if (0 == indexInfo.totalProfilesOnDevice)
		{
			SockLog(eLOG_WARN, "No Profiles exist on the device for Data session\n"
				"or check device connectivity\n\n");
			return;
		}

		uint8_t profileIdMatch = FALSE;

		while (!profileIdMatch)
		{
			/* Get the profile id using which the data session needs to be started */
			// marc modification choose user
			profileInfo.profileNumber = GetUserProfileId(MIN_PROFILES, MAX_PROFILES);


			/* If only <ENTER> is pressed by the user, return to main menu */
			if (ENTER_KEY_PRESSED == profileInfo.profileNumber)
				return;

			/* If the user has enter an invalid profile id */
			for (int idx = 0; !profileIdMatch && idx < indexInfo.totalProfilesOnDevice; idx++)
			{
				profileIdMatch = profileInfo.profileNumber == indexInfo.profileIndex[idx];
			}
		}
	}

	profileInfo.PDPType = GetIPFamilyPreference();

	if (bMpdn)
		start_multipdn_datasession(&netSelPref, &profileInfo, bSingle);
	else
		start_datasession(&netSelPref, &profileInfo);
}

void DisplayGetPower(unpack_dms_GetPower_t* pUnpackGetPower)
{
	const char* opModeDesp[] =
	{
		"Online",
		"Low power",
		"Factory test mode",
		"Offline",
		"Resetting",
		"Shutting down",
		"Persistent low power",
		"Mode-only low power",
		"Conducting network test for GSM/WCDMA",
		"Camp only"
	};

	SockPrintf("Device Power Status: %d - %s\n", pUnpackGetPower->OperationMode,
		pUnpackGetPower->OperationMode <= 9 ? opModeDesp[pUnpackGetPower->OperationMode] : "unknown");

	if (swi_uint256_get_bit(pUnpackGetPower->ParamPresenceMask, 0x10))
	{
		SockPrintf("  Offline reason:\n");
		if (pUnpackGetPower->OfflineReason & 0x01)
			SockPrintf("    Host image misconfiguration\n");
		if (pUnpackGetPower->OfflineReason & 0x02)
			SockPrintf("    PRI image misconfiguration\n");
		if (pUnpackGetPower->OfflineReason & 0x04)
			SockPrintf("    PRI version incompatible\n");
		if (pUnpackGetPower->OfflineReason & 0x08)
			SockPrintf("    Device memory is full,cannot copy PRI information\n");
	}
	if (swi_uint256_get_bit(pUnpackGetPower->ParamPresenceMask, 0x11))
	{
		SockPrintf("  hardware restricted mode: %s\n", pUnpackGetPower->HardwareControlledMode ? "true" : "false");
	}
}

/*
 * Name:     display_device_info
 *
 * Purpose:  Display the information about the connected device
 *
 * Params:   None
 *
 * Return:   None
 *
 * Notes:    None
 */
void display_device_info()
{
	int rtn;
	unpack_dms_GetModelID_t modelId;
	unpack_nas_GetHomeNetwork_t homeNw;
	unpack_nas_SLQSGetSysSelectionPrefExt_t netSelPref;
	uint8_t NetSelPref = 0;
	uint16_t ModePref = 0xFFFF;
	uint32_t GWAcqPref = 0xFFFFFFFF;
	char  *pNAString = "UNAVAILABLE";

	/* Get the Device Model ID */
	memset(&modelId, 0, sizeof(unpack_dms_GetModelID_t));

	rtn = SENDRECEIVE(&s_DmsService, pack_dms_GetModelID, NULL, unpack_dms_GetModelID, &modelId);
	if (rtn != eLITE_CONNECT_APP_OK)
	{
		SockLog(eLOG_DEBUG, "Failed to get model ID\n");
		update_user_display(eMODEL_ID, pNAString);
	}
	else
	{
		/* Update the model ID field of the user window */
		SockPrintf("Model: %s\n", modelId.modelid);
		update_user_display(eMODEL_ID, modelId.modelid);
	}

	unpack_dms_GetPower_t sUnpackGetPower;
	memset(&sUnpackGetPower, 0, sizeof(unpack_dms_GetPower_t));

	rtn = SENDRECEIVE(&s_DmsService, pack_dms_GetPower, NULL, unpack_dms_GetPower, &sUnpackGetPower);
	if (rtn != eLITE_CONNECT_APP_OK)
	{
		SockLog(eLOG_DEBUG, "Failed to get device power state\n");
		update_user_display(eDEVICE_STATE, pNAString);
	}
	else
	{
		g_online = sUnpackGetPower.OperationMode == 0 || sUnpackGetPower.OperationMode > 9 /*unknown state*/;
		DisplayGetPower(&sUnpackGetPower);
		//update_user_display(eDEVICE_STATE, sUnpackGetPower.OperationMode);
	}

	/* Get the Home Network */
	memset(&homeNw, 0, sizeof(unpack_nas_GetHomeNetwork_t));

	rtn = SENDRECEIVENOINPUT(&s_NasService, pack_nas_GetHomeNetwork, unpack_nas_GetHomeNetwork, &homeNw);
	if (rtn != eLITE_CONNECT_APP_OK)
	{
		SockLog(eLOG_DEBUG, "Failed to get home network\n");
		update_user_display(eHOME_NETWORK, pNAString);
	}
	else
	{
		/* Update the model ID field of the user window */
		SockPrintf("HomeNetwork: %s\n", homeNw.name);
		update_user_display(eHOME_NETWORK, homeNw.name);
	}

	/* Get Network selection preference */
	memset(&netSelPref, 0, sizeof(unpack_nas_SLQSGetSysSelectionPrefExt_t));
	netSelPref.pNetSelPref = &NetSelPref;
	netSelPref.pModePref = &ModePref;
	netSelPref.pGWAcqOrderPref = &GWAcqPref;

	rtn = SENDRECEIVENOINPUT(&s_NasService, pack_nas_SLQSGetSysSelectionPrefExt, unpack_nas_SLQSGetSysSelectionPrefExt, &netSelPref);
	if (rtn != eLITE_CONNECT_APP_OK)
	{
		SockLog(eLOG_DEBUG, "Failed to get network selection preference\n");
		update_user_display(eNETWORK_PREF, pNAString);
	}
	else
	{
		/* Update the network selection preference field of the user window */
		SockPrintf("Network Selection Preference: ");
		if (swi_uint256_get_bit(netSelPref.ParamPresenceMask, 0x16))
			SockPrintf("%s\n", NetSelPref == 0 ? "auto" : "manual");
		else
			SockPrintf("unknown\n");
		update_user_display(eNETWORK_PREF, NetSelPref == 0 ? "auto" : "manual");
		g_NetSelPref = NetSelPref;
	}

	for (int i = 0; i < NUM_WDS_SVC; i++)
		DisplaySessionState(i, 0);

	SockPrintf("Auto-ping check on connection: %s\n", g_auto_test_enable ? "enabled" : "disabled");
	SockPrintf("Routing table update on connection: %s\n", g_update_route ? "enabled" : "disabled");
}

void get_Loopback()
{
	unpack_wds_SLQSSGetLoopback_t tunpack_wds_GetLoopback;
	memset(&tunpack_wds_GetLoopback, 0, sizeof(unpack_wds_SLQSSGetLoopback_t));
	
	int rtn = SENDRECEIVENOINPUT(&sessions[0].wdsSvc, pack_wds_SLQSSGetLoopback, unpack_wds_SLQSSGetLoopback, &tunpack_wds_GetLoopback);

	if (rtn != eLITE_CONNECT_APP_OK)
		SockLog(eLOG_INFO, "WDS[%d] GetLoopback returns %d\n", 0, rtn);
	else
	{
		SockPrintf("ByteLoopbackMode: %d\n", tunpack_wds_GetLoopback.ByteLoopbackMode);
		SockPrintf("ByteLoopbackMultiplier: %d\n", tunpack_wds_GetLoopback.ByteLoopbackMultiplier);
	}
}

void set_Loopback()
{
	pack_wds_SLQSSSetLoopback_t input;
	memset(&input, 0, sizeof(pack_wds_SLQSSSetLoopback_t));

	input.loopbackMode = GetNumericValue(NULL, "Loopback mode. 0: Disable (default) or 1: Enable", g_enterActionDefault, 0, 0, 1);
	input.loopbackMultiplier = GetNumericValue(NULL, "Loopback multiplier", g_enterActionZero, 0, 0, MAX_INT32_VALUE_SIZE);

	unpack_wds_SLQSSSetLoopback_t output;
	memset(&output, 0, sizeof(unpack_wds_SLQSSSetLoopback_t));

	int rtn = SENDRECEIVE(&sessions[0].wdsSvc, pack_wds_SLQSSSetLoopback, &input, unpack_wds_SLQSSSetLoopback, &output);

	if (rtn != eLITE_CONNECT_APP_OK)
		SockLog(eLOG_INFO, "WDS[%d] SetLoopback returns %d\n", 0, rtn);
}

void get_Current_channel_rate()
{
	unpack_wds_SLQSGetCurrentChannelRate_t sCurrentChannelRate;
	memset(&sCurrentChannelRate, 0, sizeof(unpack_wds_SLQSGetCurrentChannelRate_t));

	if (SENDRECEIVENOINPUT(&sessions[0].wdsSvc, pack_wds_SLQSSwiGetCurrentChannelRate, unpack_wds_SLQSSwiGetCurrentChannelRate, &sCurrentChannelRate) == eQCWWAN_ERR_NONE)
	{
		SockPrintf("\nGet Current Channel Rate\n");
		SockPrintf("\tcurrent channel tx rate:  %d\n", sCurrentChannelRate.current_channel_tx_rate);
		SockPrintf("\tcurrent channel rx rate:  %d\n", sCurrentChannelRate.current_channel_rx_rate);
		SockPrintf("\tmax channel tx rate:  %d\n", sCurrentChannelRate.max_channel_tx_rate);
		SockPrintf("\tmax channel rx rate:  %d\n", sCurrentChannelRate.max_channel_rx_rate);
	}
	else
	{
		SockPrintf("\nFailed to Get Current Channel Rate\n");
	}
}

void keep_alive_data_session(unsigned char enableKA)
{
	int nNumSessions = 0;

	for (int i = 0; i < NUM_WDS_SVC; i++)
	{
		if (sessions[i].active)
		{
			unpack_wds_Keep_Alive_Data_Session_t output;
			memset(&output, 0, sizeof(unpack_wds_Keep_Alive_Data_Session_t));

			SENDRECEIVE(&sessions[i].wdsSvc, pack_wds_KeepAliveDataSession, &enableKA, unpack_wds_KeepAliveDataSession, &output);

			nNumSessions++;
		}
	}

	if (nNumSessions > 0)
		SockPrintf("Keep %d data session%s alive %s\n", nNumSessions, nNumSessions > 1 ? "s" : "", enableKA ? "enabled" : "disabled");
	else
		SockPrintf("There is no active data session\n");
}

void GetNumericValueSetPointer(const char* pFieldName, int enterVal, int min, int max, uint8_t* pValue, uint8_t** ppValue, bool* bSet)
{
	*pValue = GetNumericValue(NULL, pFieldName, "not change", enterVal, min, max);

	if (*pValue != enterVal)
	{
		*bSet = true;
		*ppValue = pValue;
	}
}

bool GetWdsEventReportParams(struct WdsSetEventReport* pParams)
{
	bool bDataAvail = false;

	SockPrintf("\nPlease enter at least one of the optional parameter:\n");

	GetNumericValueSetPointer("Current Channel Rate Indicator State Period(Optional) (0: Do not report, 1: Report)", ENTER_KEY, 0, 1, &pParams->CurrChannelRateInd, &pParams->wdsSetEventReport.pCurrChannelRateInd, &bDataAvail);

	pParams->TransferStatInd.statsPeriod = GetNumericValue(NULL, "Transfer Statistics Indicator(Optional) (0: Do not report 1: Other - Period between reports (in seconds))", "not change", 255, 1, 254);
	if (pParams->TransferStatInd.statsPeriod != 255)
	{
		bDataAvail = true;
		pParams->TransferStatInd.statsMask = pParams->TransferStatInd.statsPeriod == 0 ? 0 :
			GetNumericValue(NULL, "Transfer Statistics Indicator Mask(Optional) (0x1:Tx packets OK 0x2:Rx packets OK 0x4:Tx packet errors 0x8:Rx packet errors 0x10:Tx overflows 0x20:Rx overflows 0x40:Tx bytes OK 0x80:Rx bytes OK 0x100:Tx packets dropped 0x200:Rx packets dropped)", "All 0", 0, 0, 0x3FF);
		pParams->wdsSetEventReport.pTransferStatInd = &pParams->TransferStatInd;
	}
	
	GetNumericValueSetPointer("Data Bearer Technology Indicator(Optional) (0: Do not report 1: Report)", ENTER_KEY, 0, 1, &pParams->DataBearerTechInd, &pParams->wdsSetEventReport.pDataBearerTechInd, &bDataAvail);
	GetNumericValueSetPointer("Dormancy Status indicator(Optional) (0: Do not report 1: Report)", ENTER_KEY, 0, 1, &pParams->DormancyStatusInd, &pParams->wdsSetEventReport.pDormancyStatusInd, &bDataAvail);
	GetNumericValueSetPointer("MIP Status Indicator(Optional) (0: Do not report 1: Report)", ENTER_KEY, 0, 1, &pParams->MIPStatusInd, &pParams->wdsSetEventReport.pMIPStatusInd, &bDataAvail);
	GetNumericValueSetPointer("Data Call Status Change Indicator(Optional) (0: Do not report 1: Report)", ENTER_KEY, 0, 1, &pParams->DataCallStatusChangeInd, &pParams->wdsSetEventReport.pDataCallStatusChangeInd, &bDataAvail);
	GetNumericValueSetPointer("Current Preferred Data System Indicator(Optional) (0: Do not report 1: Report)", ENTER_KEY, 0, 1, &pParams->CurrPrefDataSysInd, &pParams->wdsSetEventReport.pCurrPrefDataSysInd, &bDataAvail);
	GetNumericValueSetPointer("EV-DO Page Monitor Period Change Indicator(Optional) (0: Do not report 1: Report)", ENTER_KEY, 0, 1, &pParams->EVDOPageMonPerChangeInd, &pParams->wdsSetEventReport.pEVDOPageMonPerChangeInd, &bDataAvail);
	GetNumericValueSetPointer("Uplink Flow Control Indicator(Optional) (0: Do not report 1: Report)", ENTER_KEY, 0, 1, &pParams->UlFlowControlInd, &pParams->wdsSetEventReport.pUlFlowControlInd, &bDataAvail);
	GetNumericValueSetPointer("Additional PDN Filters Removal Indicator(Optional) (0: Do not report 1: Report)", ENTER_KEY, 0, 1, &pParams->ReportAddPdnFiltersRemoval, &pParams->wdsSetEventReport.pReportAddPdnFiltersRemoval, &bDataAvail);
	GetNumericValueSetPointer("Data Bearer Technology Extended Indicator(Optional) (0: Do not report 1: Report)", ENTER_KEY, 0, 1, &pParams->DataBearerTechExtInd, &pParams->wdsSetEventReport.pDataBearerTechExtInd, &bDataAvail);
	GetNumericValueSetPointer("Dormancy Result Indicator(Optional) (0: Do not report 1: Report)", ENTER_KEY, 0, 1, &pParams->DormancyResultIndicator, &pParams->wdsSetEventReport.pDormancyResultIndicator, &bDataAvail);

	return bDataAvail;
}

void run_socket()
{
	/* Display the information about the connected device */
	display_device_info();

	bool bExiting = OpenSocket("/tmp/qmicm-server-socket") == 0;

	while (!bExiting)
	{
		socketCommandParam cmdParam;
		//marc start
		int command = GetCMSocketCommand(appName, &cmdParam, g_qos_support/* To be replaced with swiwds , g_swinas_support*/);
		//int command=eSTART_LTE_DATA_SESSION;
		//marc stop
		LockSocket();
		switch (command)
		{
		case eEXIT:
			stop_all_datasessions();
			bExiting = true;
			break;

		case eUNKNOWN:
			break;

		case eSTART_LTE_DATA_SESSION:
			if (!PowerUp())
				break;;

			//if (g_netnum_val < 2)
			if (!g_bRmNet)
				start_datasession(&cmdParam.sessionInfo.netSelPref, &cmdParam.sessionInfo.profileInfo);
			else
				start_multipdn_datasession(&cmdParam.sessionInfo.netSelPref, &cmdParam.sessionInfo.profileInfo, true);
			break;

		case eSTART_MPDN_DATASESSION:
			if (!PowerUp())
				break;;

			if (g_netnum_val >= 2)
				start_multipdn_datasession(&cmdParam.sessionInfo.netSelPref, &cmdParam.sessionInfo.profileInfo, false);
			else
				SockPrintf("MPDN not supported\n");
			break;

		case eSTOP_DATA_SESSION:
			stop_datasession(cmdParam.sessionNumber);
			break;

		case eSTOP_DATA_SESSIONS:
			stop_all_datasessions();
			break;

		case eDISPLAY_ALL_PROFILES:
			display_all_profiles(true);
			break;

		case eDISPLAY_SINGLE_PROFILE:
			display_profile_info(cmdParam.profileNumber, true, false);
			break;

		case eCREATE_PROFILE:
			modify_profile_by_id(true, &cmdParam.profileInfo);
			break;

		case eMODIFY_PROFILE_SETTINGS:
			modify_profile_by_id(false, &cmdParam.profileInfo);
			break;

		case eDELETE_PROFILE:
			delete_profile_by_id(cmdParam.profileNumber);
			break;

		case eTOGGLE_PING:
			g_auto_test_enable = !g_auto_test_enable;
			SockLog(eLOG_INFO, "\nPinging upon connection is %s.\n", g_auto_test_enable ? "enabled" : "disabled");
			break;

		case eTOGGLE_ROUTE_UPDATE:
			g_update_route = !g_update_route;
			SockLog(eLOG_INFO, "\nUpdating routing table upon connection is %s.\n", g_update_route ? "enabled" : "disabled");
			break;

		case eSCAN_NETWORKS:
		{
			int ret = SENDREQUESTNOINPUT(&s_NasService, pack_nas_PerformNetworkScan, ScanNetworkCallback, NULL, &g_NasPendingXid);
			if (ret != SUCCESS)
				SockPrintf("QmiService_SendRequest returned error %d\n", ret);
			else
				SockPrintf("NetworkScan may take a few minutes.  Result will be displayed when available.  Please wait...\n");

			break;
		}

		case eENABLE_QOS_EVENT:
			if (!g_qos_support)
				SockPrintf("QOS is not supported\n");
			else
				qos_enable_qos_event(true);
			break;

		case eDISABLE_QOS_EVENT:
			if (!g_qos_support)
				SockPrintf("QOS is not supported\n");
			else
				qos_enable_qos_event(false);
			break;

		case eREQUEST_QOSEX:
			if (!g_qos_support)
				SockPrintf("QOS is not supported\n");
			else
				qos_request_qosex(&cmdParam.requestQosExReq);

			ReleaseQosExReqResource(&cmdParam.requestQosExReq);
			break;

		case eGET_QOSINFO:
			if (!g_qos_support)
				SockPrintf("QOS is not supported\n");
			else
				qos_get_qosinfo(cmdParam.id);
			break;

		case eSET_QOS_INDICATION_REGISTER:
			if (!g_qos_support)
				SockPrintf("QOS is not supported\n");
			else
				qos_indicationregister(&cmdParam.qosIndicationRegisterParams);
			break;

		case eREAD_QOS_DATA_STATISTIC:
			if (!g_qos_support)
				SockPrintf("QOS is not supported\n");
			else
				qos_read_datastats(cmdParam.id);
			break;

		case eREAD_QOS_EXTRA_APN_PARAMS:
			if (!g_qos_support)
				SockPrintf("QOS is not supported\n");
			else
				qos_read_extraapnparams(cmdParam.id);
			break;

		case eGET_PKT_STATS:
			get_pkt_stats();
			break;

		case eGET_CURRENT_CHANNEL_RATE:
			get_Current_channel_rate();
			break;

		case eGET_LOOPBACK:
			get_Loopback();
			break;

		case eSET_LOOPBACK:
			set_Loopback();
			break;

		case eENABLE_QMAP:
			cmdParam.dataFormatParams.EP_Type = g_pcie ? EP_TYPE_PCIE : EP_TYPE_HSUSB;
			cmdParam.dataFormatParams.Interface_ID = g_rmnet_if_id;
			if (EnableQmap(&s_CtlService, true, &cmdParam.dataFormatParams) != SUCCESS)
				SockLog(eLOG_ERROR, "EnableQmap failed.\n");
			break;

		case eDISABLE_QMAP:
			cmdParam.dataFormatParams.EP_Type = g_pcie ? EP_TYPE_PCIE : EP_TYPE_HSUSB;
			cmdParam.dataFormatParams.Interface_ID = g_rmnet_if_id;
			if (EnableQmap(&s_CtlService, false, &cmdParam.dataFormatParams) != SUCCESS)
				SockLog(eLOG_ERROR, "DisableQmap failed.\n");
			break;

		case eSET_WDS_EVENT_REPORT:
		{
			unpack_wds_SLQSWdsSetEventReport_t output;
			memset(&output, 0, sizeof(unpack_wds_SLQSWdsSetEventReport_t));

			SENDRECEIVE(&sessions[0].wdsSvc, pack_wds_SLQSWdsSetEventReport, &cmdParam.sWdsSetEventReport.wdsSetEventReport, unpack_wds_SLQSWdsSetEventReport, &output);
			break;
		}

		case eSET_KEEP_ALIVE_DATA_SESSION:
			keep_alive_data_session(cmdParam.enableKA ? 1 : 0);
			break;

		default:
			break;
		}
		UnlockSocket();
	}

	CloseSocket();
}

void run_tests(bool bTmMon, bool bTsMon)
{
	/* Initialize the output log file */
	initialize_display();

	/* Being here means, device is connected, update the required field */
	update_user_display(eDEVICE_STATE, "DEVICE CONNECTED");

	/* Display the information about the connected device */
	display_device_info();

	/* Register thermal mitigation and thermal sensor indications */
	if (bTmMon)
		register_mit_ind(&s_CtlService);
	if (bTsMon)
		register_ts_ind(&s_CtlService);

	bool bExiting = false;
	char selOption[OPTION_LEN];
	char *pEndOfLine = NULL;
	unsigned int len = 0;
	uint32_t userOption;

	while (!bExiting)
	{
		// marc important menu
		/* Print the menu */
		printf("\nmarc: Auto connect single PDN data\n");
		PrintPrompt();

		/* Receive the input from the user */
		//Marc modification - sdin = 1 for first choice (single PDN data)
		//while (fgets(selOption, (OPTION_LEN), stdin) == NULL);
		selOption[0]='1';
		selOption[1]='\n';
		bExiting = true; // to not loop indefinitly

		/* If '/n' character is not read, there are more characters in input
			* stream. Clear the input stream.
			*/
		pEndOfLine = strchr(selOption, ENTER_KEY);
		if (NULL == pEndOfLine)
		{
			FlushStdinStream();
		}

#ifdef DBG
		fprintf(stderr, "Selected Option : %s\n", selOption);
#endif

		len = strlen(selOption);

		/* If only <ENTER> is pressed by the user quit Application */
		if (ENTER_KEY == selOption[0])
			continue;	// Show menu options
		else
		{

			/* check descriptor is still valid or not */
			//ret = fcntl(wds_fd, F_GETFD);
			//if (ret < 0) {
			//	fprintf(stderr, "Device seems disconnected, exiting application!\n");
			//	break;
			//}

			/* Convert the option added by user into integer */
			selOption[len - 1] = '\0';
			userOption = atoi(selOption);
		}

		if (userOption == 0 && strcmp(selOption, "q") == 0)
		{
			stop_all_datasessions();
			bExiting = true;
			continue;
		}

		/* Process user input */
		switch (userOption) 
		{
		case eSTART_LTE_DATA_SESSION:
			initiate_datasession(g_bRmNet /*g_netnum_val >= 2*/, true);
			break;

		case eSTART_MPDN_DATASESSION:
			if (g_netnum_val >= 2)
				initiate_datasession(true, false);
			else
				SockPrintf("MPDN not supported\n");
			break;

		case eSTOP_DATA_SESSION:
			if (g_connection_state == NONE || g_connection_state == SINGLE)
				stop_all_datasessions();
			else
				stop_one_datasession();
			break;

		case eSTOP_DATA_SESSIONS:
			stop_all_datasessions();
			break;

		case eDISPLAY_ALL_PROFILES:
			display_all_profiles(true);
			break;

		case eDISPLAY_SINGLE_PROFILE:
			display_profile();
			break;

		case eCREATE_PROFILE:
			modify_profile_settings(true);
			break;

		case eMODIFY_PROFILE_SETTINGS:
			modify_profile_settings(false);
			break;

		case eDELETE_PROFILE:
			delete_profile_from_device();
		break;

		case eSCAN_NETWORKS:
		{
			int ret = SENDREQUESTNOINPUT(&s_NasService, pack_nas_PerformNetworkScan, ScanNetworkCallback, NULL, &g_NasPendingXid);
			if (ret != SUCCESS)
				SockPrintf("QmiService_SendRequest returned error %d\n", ret);
			else
				SockPrintf("NetworkScan may take a few minutes.  Result will be displayed when available.  Please wait...\n");

		}
			break;

		case eENABLE_QOS_EVENT:
			if (!g_qos_support)
				SockPrintf("QOS is not supported\n");
			else
				qos_enable_qos_event(true);
		break;

		case eDISABLE_QOS_EVENT:
			if (!g_qos_support)
				SockPrintf("QOS is not supported\n");
			else
				qos_enable_qos_event(false);
		break;

		case eREQUEST_QOSEX:
			if (!g_qos_support)
				SockPrintf("QOS is not supported\n");
			else
				DoInteractiveQosExRequest();
		break;

		case eGET_QOSINFO:
			if (!g_qos_support)
				SockPrintf("QOS is not supported\n");
			else
			{
				uint32_t qosIdentifier;
				GetQosGetQosInfoParams(&qosIdentifier);
				if (qosIdentifier != 1001)
					qos_get_qosinfo(qosIdentifier);
			}
		break;
		case eSET_QOS_INDICATION_REGISTER:
			if (!g_qos_support)
				SockPrintf("QOS is not supported\n");
			else
			{
				struct qosIndicationRegisterParams qosIndParams;
				GetQosIndicationRegisterParams(&qosIndParams);
				qos_indicationregister(&qosIndParams);
			}
		break;
		case eREAD_QOS_DATA_STATISTIC:
			if (!g_qos_support)
				SockPrintf("QOS is not supported\n");
			else
			{
				uint32_t qosIdentifier;
				GetQosApnId(&qosIdentifier);
				if (qosIdentifier != 1001)
					qos_read_datastats(qosIdentifier);
			}
			break;

		case eREAD_QOS_EXTRA_APN_PARAMS:
			if (!g_qos_support)
				SockPrintf("QOS is not supported\n");
			else
			{
				uint32_t qosIdentifier;
				GetQosApnId(&qosIdentifier);
				if (qosIdentifier != 1001)
					qos_read_extraapnparams(qosIdentifier);
			}
			break;

		case eGET_PKT_STATS:
			get_pkt_stats();
		break;
		case eGET_CURRENT_CHANNEL_RATE:
			get_Current_channel_rate();
		break;
		case eGET_LOOPBACK:
			get_Loopback();
			break;
		case eSET_LOOPBACK:
			set_Loopback();
			break;
		case eENABLE_QMAP:
			SetQmapSettings(true);
			break;
		case eDISABLE_QMAP:
			SetQmapSettings(false);
			break;
		case eTOGGLE_PING:
			g_auto_test_enable = !g_auto_test_enable;
			SockLog(eLOG_INFO, "\nPinging upon connection is %s.\n", g_auto_test_enable ? "enabled" : "disabled");
			break;
		case eTOGGLE_ROUTE_UPDATE:
			g_update_route = !g_update_route;
			SockLog(eLOG_INFO, "\nUpdating routing table upon connection is %s.\n", g_update_route ? "enabled" : "disabled");
			break;
		case eSET_WDS_EVENT_REPORT:
		{
			struct WdsSetEventReport params;
			memset(&params, 0, sizeof(params));

			if (GetWdsEventReportParams(&params))
			{
				unpack_wds_SLQSWdsSetEventReport_t output;
				memset(&output, 0, sizeof(unpack_wds_SLQSWdsSetEventReport_t));

				int ret = SENDRECEIVE(&sessions[0].wdsSvc, pack_wds_SLQSWdsSetEventReport, &params.wdsSetEventReport, unpack_wds_SLQSWdsSetEventReport, &output);
				if (ret == 0)
					SockLog(eLOG_INFO, "\nWDS Event Report set successfully.\n");
				else
					SockLog(eLOG_ERROR, "\nWDS Event Report set failed with error %d.\n", ret);
			}

			break;
		}
		case eSET_KEEP_ALIVE_DATA_SESSION:
			keep_alive_data_session(GetNumericValue(NULL, "Keep data session alive. 0: No (default) or 1: Yes", g_enterActionDefault, 0, 0, 1));
			break;
		default:
			break;
		}
	}

	g_exiting = true;

	// marc modification
	// leave without closing connection
	//printf("\nmarc: Leaving without closing connection\n");
	
	
	if (bTmMon)
		deregister_mit_ind(&s_CtlService);
	if (bTsMon)
		deregister_ts_ind(&s_CtlService);
	
}

void ShowHelp(const char* procName)
{
    SockPrintf("\r\n");
    SockPrintf("App usage: \r\n\r\n");
	SockPrintf("  %s [[[-m|-q] [-d <QMI/MBIM device path>]]|[-r]] [-P enable|disable] [-R enable|disable] [-s] [-tm] [-ts] [-V] [-h]\n\n", procName);
	SockPrintf("  -d  --device <QMI/MBIM device path>\n");
    SockPrintf("        Specifies the QMI or the MBIM device path\n\n");
	SockPrintf("  -m  --mbim\n");
	SockPrintf("        Use MBIM interface (MBIM over PCIe or USB)\n\n");
	SockPrintf("  -q  --qmi\n");
	SockPrintf("        Use direct QMUX interface (QMI over PCIe, or RmNet over USB)\n\n");
	SockPrintf("  -r  --router\n");
	SockPrintf("        Use QMUX Router\n\n");
	SockPrintf("  -P  --ping enable|disable\n");
	SockPrintf("        Set default value of pinging on connection.  Default is enalbed\n\n");
	SockPrintf("  -R  --routing enable|disable\n");
	SockPrintf("        Set default value of routing table update on connection.  Default is enalbed\n\n");
	SockPrintf("  -s  --socket\n");
	SockPrintf("        Run socket mode\n\n");
	SockPrintf("  -S  --skipsync\n");
	SockPrintf("        Skip syncing QMI control IDs\n\n");
	SockPrintf("  -tm  --thermal_mitigation\n");
	SockPrintf("        Enable thermal mitigation device monitoring.\n\n");
	SockPrintf("  -ts  --thermal_sensor\n" );
    SockPrintf("        Enable thermal sensor monitoring.\n\n" );
	SockPrintf("  -V  --version\n");
	SockPrintf("        Show version information.\n\n");
	SockPrintf("  -h  --help\n" );
    SockPrintf("        This option prints the usage instructions.\n\n" );
}

// The following function is a callback function for QMUX transport errors.
// It can be used to detect device removal scenarios.
void TransportErrorCallback(void * pErrCallbackContext, QMUX_TRANSPORT_ERR_INFO err_info)
{
	UNUSEDPARAM(pErrCallbackContext);
	
	SockLog(eLOG_INFO, "\nTransport callback is invoked, type: %d, value: %d.\n", err_info.err_type, err_info.errno_val);

	switch (err_info.err_type)
	{
	case QMUX_TRANSPORT_ERR_READ:
	case QMUX_TRANSPORT_ERR_WRITE:
		if (err_info.errno_val == ENODEV)
			SockLog(eLOG_INFO, "Device has been removed.\n");
		break;
	case QMUX_TRANSPORT_MSG_DEVMODE:
		g_mode = err_info.errno_val;
		SockLog(eLOG_INFO, "Device mode on router: %s\n", GetModeDesc(g_mode));
		break;
	default:
		break;
	}
}

/*
 * Name:     main
 *
 * Purpose:  Entry point of the application
 *
 * Params:   None
 *
 * Return:   EXIT_SUCCESS, EXIT_FAILURE on unexpected error
 *
 * Notes:    None
 */
int main(int argc, const char *argv[])
{
	SockPrintf("\n%s v%s\n\n", appName, VERSION);

	const char* muxname[] = { QMIMUX_0_NAME, QMIMUX_1_NAME, QMIMUX_2_NAME, QMIMUX_3_NAME };
	const int muxid[] = { QMIMUX_0_ID, QMIMUX_1_ID, QMIMUX_2_ID, QMIMUX_3_ID };

	const char* vlanname[] = { VLAN_0_NAME, VLAN_1_NAME, VLAN_2_NAME, VLAN_3_NAME };
	const int vlanid[] = { VLAN_0_ID, VLAN_1_ID, VLAN_2_ID, VLAN_3_ID };

	char dev_path[MAX_PATH_LEN];
	memset(dev_path, 0, MAX_PATH_LEN);

	bool bHelp = false;
	bool bVer = false;
	bool bSocket = false;
	bool bTmMon = false;
	bool bTsMon = false;
	bool bInvalidArg = false;
	bool bSkipSync = false;

	for (int i = 1; i < argc && !bInvalidArg; i++)
	{
		if (strcmp("-d", argv[i]) == 0 || strcmp("--device", argv[i]) == 0)
		{
			if (++i >= argc || argv[i][0] != '/')
				bInvalidArg = true;
			else
				StrCpy(dev_path, argv[i]);
		}
		else if (strcmp("-m", argv[i]) == 0 || strcmp("--mbim", argv[i]) == 0)
		{
			if (g_mode != QMUX_INTERFACE_UNKNOWN)
				bInvalidArg = true;
			g_mode = QMUX_INTERFACE_MBIM;
		}
		else if (strcmp("-q", argv[i]) == 0 || strcmp("--qmi", argv[i]) == 0)
		{
			if (g_mode != QMUX_INTERFACE_UNKNOWN)
				bInvalidArg = true;
			g_mode = QMUX_INTERFACE_DIRECT;
		}
		else if (strcmp("-r", argv[i]) == 0 || strcmp("--router", argv[i]) == 0)
		{
			if (g_mode != QMUX_INTERFACE_UNKNOWN)
				bInvalidArg = true;
			g_mode = QMUX_INTERFACE_ROUTER;
		}
		else if (strcmp("-P", argv[i]) == 0 || strcmp("--ping", argv[i]) == 0)
		{
			if (++i >= argc)
				bInvalidArg = true;
			else if (strcmp(argv[i], "enable") == 0)
				g_auto_test_enable = true;
			else if (strcmp(argv[i], "disable") == 0)
				g_auto_test_enable = false;
			else
				bInvalidArg = true;
		}
		else if (strcmp("-R", argv[i]) == 0 || strcmp("--routing", argv[i]) == 0)
		{
			if (++i >= argc)
				bInvalidArg = true;
			else if (strcmp(argv[i], "enable") == 0)
				g_update_route = true;
			else if (strcmp(argv[i], "disable") == 0)
				g_update_route = false;
			else
				bInvalidArg = true;
		}
		else if (strcmp("-s", argv[i]) == 0 || strcmp("--socket", argv[i]) == 0)
			bSocket = true;
		else if (strcmp("-S", argv[i]) == 0 || strcmp("--skipsync", argv[i]) == 0)
			bSkipSync = true;
		else if (strcmp("-tm", argv[i]) == 0 || strcmp("--thermal_mitigation", argv[i]) == 0)
			bTmMon = true;
		else if (strcmp("-ts", argv[i]) == 0 || strcmp("--thermal_sensor", argv[i]) == 0)
			bTsMon = true;
		else if (strcmp("-np", argv[i]) == 0 || strcmp("--no_ping", argv[i]) == 0)
			g_auto_test_enable = 0;
		else if ((strcmp("-V", argv[i]) == 0 || strcmp("--version", argv[i]) == 0))
		{
			bVer = true;
			if (argc == 2)
				return 0;
		}
		else if (strcmp("-h", argv[i]) == 0 || strcmp("--help", argv[i]) == 0)
			bHelp = true;
		else
			bInvalidArg = true;
	}

	if (bHelp && (argc == 2 || (bVer && argc == 3)))
	{
		ShowHelp(argv[0]);
		return 0;
	}

	if (OpenTransport(&s_Transport, dev_path, sizeof(dev_path), &g_mode, &g_pcie, &g_rmnet_if_id,
		!bInvalidArg /*&& (nMbimDevIdx == 0 || !bEnableQmap)*/, ShowHelp, argv[0], bHelp) != 0)
		return 0;

	QmuxTransport_RegisterErrCallback(&s_Transport, TransportErrorCallback, NULL);
	
	if (!GetNetInterfaceName(dev_path, szEthName, 64))
		SockLog(eLOG_ERROR, "Unable to detect network interface for %s\n", dev_path);
	else if (CtlService_InitializeEx(&s_CtlService, &s_Transport, bSkipSync, 1) != SUCCESS)
		SockLog(eLOG_ERROR, "CtlService_InitializeEx failed\n");
	else
	{
		if (!g_pcie && !get_rmnet_value())
			g_bRmNet = g_mode == QMUX_INTERFACE_DIRECT;

		memset(&sessions, 0, sizeof(sessions));

		// In RmNet mode, Set the raw IP mode by changing /sys/class/net/<adapter name>/qmi/raw_ip to 1 
		// and don't enable qmap here
		if (g_bRmNet && strncmp(dev_path, "/dev/mhi", 8) != 0)
			EnableQmiMuxRawIp(szEthName);

		if (g_mode == QMUX_INTERFACE_DIRECT)
		{
			WdaSetDataFormatParams param;
			memset(&param, 0, sizeof(param));

			param.SetQosHrPres = false;
			param.QosHrPres = QOS_HDR_NOT_PRESENT;
			param.SetUL_Data_Aggregation_Max_Datagrams = true;
			param.UL_Data_Aggregation_Max_Datagrams = MAX_UL_PKT_AGGR;
			param.SetDL_Data_Aggregation_Max_Datagrams = true;
			param.DL_Data_Aggregation_Max_Datagrams = MAX_DL_PKT_AGGR;
			param.SetUL_Data_Aggregation_Max_Size = true;
			param.UL_Data_Aggregation_Max_Size = QMAP_TX_BUFFER_SIZE;
			param.SetDL_Data_Aggregation_Max_Size = true;
			param.DL_Data_Aggregation_Max_Size = QMAP_RX_BUFFER_SIZE;
			param.SetPeripheralEP_ID = true;
			param.EP_Type = g_pcie ? EP_TYPE_PCIE : EP_TYPE_HSUSB;
			param.Interface_ID = g_rmnet_if_id;
			param.SetDL_Padding = false;
			param.DL_Padding = 0;
			param.SetFlow_Control = false;
			param.Flow_Control = FLOW_CTL_NO_TE;

			if (EnableQmap(&s_CtlService, true/*!g_bRmNet || g_netnum_val >= 2*/, &param) != SUCCESS)
				SockLog(eLOG_ERROR, "EnableQmap failed.\n");
		}

		// We use the Ctl service to initialize the regular services because it knows how to 
		// acquire client IDs for them.

		int ret = SUCCESS;

		// Use a do/while for easy exit. We have to clean up.
		do
		{
			//marc
			printf("marc: Begin While loop.\n");
			// Infrastructure is now ready. Let's create some regular QMI services.
			ret = CtlService_InitializeRegularService(&s_CtlService, &s_DmsService, eDMS, DmsIndicationCallback, NULL);
			if (ret != SUCCESS)
			{
				SockLog(eLOG_ERROR, "InitializeRegularService eDMS failed.\n");
				break;
			}

			ret = CtlService_InitializeRegularService(&s_CtlService, &s_NasService, eNAS, NasIndicationCallback, NULL);
			if (ret != SUCCESS)
			{
				SockLog(eLOG_ERROR, "InitializeRegularService eNAS failed.\n");
				break;
			}

			for (int i = 0; i < NUM_WDS_SVC; i++)
			{
				sessions[i].idx = i;
				sessions[i].domain = i % 2 == 0 ? AF_INET : AF_INET6;
				sessions[i].mtu = 0xFFFFFFFF;
				sessions[i].ifname = g_bRmNet ? muxname[i / 2] : vlanname[i / 2];
				sessions[i].ifid = g_bRmNet ? muxid[i / 2] : vlanid[i / 2];

				if (g_bRmNet && i % 2 == 0 && AddQmiMuxIf(szEthName, muxid[i / 2]) == 0)
				{
					SockLog(eLOG_ERROR, "Unable to add QmiMux for multiple PDN\n\n");
					return 0;
				}

				ret = CtlService_InitializeRegularService(&s_CtlService, &sessions[i].wdsSvc, eWDS, WdsIndicationCallback, &sessions[i]);
				if (ret != SUCCESS)
				{
					SockLog(eLOG_ERROR, "InitializeRegularService eWDS[%d] failed.\n", i);
					break;
				}
			}
			
			g_qos_support = InitializeQosService(&s_CtlService) == SUCCESS;
			// To be replaced with swiwds g_swinas_support = InitializeSwiNasService(&s_CtlService) == SUCCESS;
		} while (0);

		if (ret == SUCCESS)
		{
			SetTermHandler(DEFAULT_TERMHANDLER, NULL);

			if (bSocket)
				run_socket();
			else
				run_tests(bTmMon, bTsMon);

			SetTermHandler(NULL, NULL);
		}

		// marc modification
		// leaving without shutdown
		return 0;

		// Shut down.

		if (g_NasPendingXid != 0)
			QmiService_CancelTransaction(&s_NasService, g_NasPendingXid);

		// To be replaced with swiwds if (g_swinas_support)
		//	ShutDownSwiNasService(&s_CtlService);
	
		if (g_qos_support)
			ShutDownQosService(&s_CtlService);

		for (int i = 0; i < NUM_WDS_SVC; i++)
			CtlService_ShutDownRegularService(&s_CtlService, &sessions[i].wdsSvc);

		CtlService_ShutDownRegularService(&s_CtlService, &s_NasService);
		CtlService_ShutDownRegularService(&s_CtlService, &s_DmsService);

		CtlService_ShutDown(&s_CtlService);
	}

	QmuxTransport_RegisterErrCallback(&s_Transport, NULL, NULL);

	QmuxTransport_ShutDown(&s_Transport);

	return 0;
}
