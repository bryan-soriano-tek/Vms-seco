#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <arpa/inet.h>
#include "str_util.h"
#include "proc_util.h"
#include "command_set.h"

static ARGUMENT_SET g_session_arg_set[] =
{
	{"c", "mcc", "network MCC. If specified, -mnc must also be specified. If not specified, automatic network selection will be used.", "MCC", eDEPENDS},
	{"n", "mnc", "network MNC. If specified, -mcc must also be specified. If not specified, automatic network selection will be used.", "MNC", eDEPENDS},
	{"t", "ipType", "4: IPv4, 6: IPv6, 46: IPv4v6.", "IP type", eMANDATORY},
	{"a", "apn", "APN string. Either -apn or -profile must be specified, but not both.", NULL, eDEPENDS},
	{"T", "auth", "Authentication type: one of: none, pap, chap, papchap. Cannot be specified if -apn is not specified. If -apn is specified, -auth defaults to none if not specified.", "authentication type", eDEPENDS},
	{"u", "username", "User name string for authentication. Cannot be specified if -auth is not specified.", NULL, eDEPENDS},
	{"p", "password", "Password string for authentication. Cannot be specified if -auth is not specified.", NULL, eDEPENDS},
	{"f", "profile", "Profile number to connect with. Either -apn or -profile must be specified, but not both.", "profile number", eDEPENDS}
};

static ARGUMENT_SET g_session_arg_set2[] =
{
	{NULL, NULL, "same as startsingle command.", NULL, eDEPENDS}
};

static ARGUMENT_SET g_stop_arg_set[] =
{
	{"s", "session", "Session number to stop.", "session id", eMANDATORY}
};

static ARGUMENT_SET g_profile_arg_set[] =
{
	{"f", "profile", "Profile number to create.", "profile number", eMANDATORY},
	{"t", "pdptype", "IPv4, PPP, IPv6, or IPv4v6.", "PDP type", eMANDATORY},
	{"i", "ipaddr", "IP address.", "IP address", eOPTIONAL},
	{"1", "dns1", "Primary DNS address.", "primary DNS address", eOPTIONAL},
	{"2", "dns2", "Secondary DNS address.", "secondary DNS address", eOPTIONAL},
	{"T", "auth", "Authentication type: one of: none, pap, chap, papchap. Defaults to none if not specified.", "authentication type", eOPTIONAL},
	{"n", "name", "Profile name.", "profile name", eOPTIONAL},
	{"a", "apn", "APN string.", NULL, eOPTIONAL},
	{"u", "username", "User name string for authentication.", NULL, eOPTIONAL},
	{"p", "password", "Password string for authentication.", NULL, eOPTIONAL}
};

static ARGUMENT_SET g_profile_arg_set2[] =
{
	{NULL, NULL, "same as createprofile command.", NULL, eDEPENDS}
};

static ARGUMENT_SET g_del_profile_arg_set[] =
{
	{"p", "profile", "Profile number to delete.", "profile id", eMANDATORY}
};

static ARGUMENT_SET g_disp_profile_arg_set[] =
{
	{"p", "profile", "Profile number to display.", "profile id", eMANDATORY}
};

static ARGUMENT_SET g_request_qosex_arg_set[] =
{
	{"f", "txflow", "Current flow status for tx QOS flow", NULL, eOPTIONAL},
	{"k", "txmask", "Valid parameters mask for tx QOS flow", NULL, eOPTIONAL},
	{"c", "txclass", "IP traffic class for tx QOS flow", NULL, eOPTIONAL},
	{"a", "txmaxrate", "Maximum required data rate for tx QOS flow (bits per second)", NULL, eOPTIONAL},
	{"i", "txminrate", "Minimum guaranteed data rate for tx QOS flow (bits per second)", NULL, eOPTIONAL},
	{"u", "txfullrate", "Maximum rate at which data can be transmitted when the token bucket is full for tx QOS flow (bits per second)", NULL, eOPTIONAL},
	{"b", "txbucketrate", "Rate at which tokens are put in the token bucket for tx QOS flow (bits per second)", NULL, eOPTIONAL},
	{"t", "txmaxtokens", "Maximum number of tokens that can be accumulated at any instance for tx QOS flow (bytes)", NULL, eOPTIONAL},
	{"d", "txmaxdelay", "Maximum delay for tx QOS flow (in milliseconds)", NULL, eOPTIONAL},
	{"l", "txlatencydiff", "Difference between the maximum and minimum latency for tx QOS flow (in milliseconds)", NULL, eOPTIONAL},
	{"m", "txm", "Factor m in calculating packet error rate for tx QOS flow: E = m*10**(-p)", NULL, eOPTIONAL},
	{"p", "txp", "Factor p in calculating packet error rate for tx QOS flow: E = m*10**(-p)", NULL, eOPTIONAL},
	{"n", "txminpacket", "Integer that defines the minimum packet size (in bytes) that will be policed for QoS guarantees for tx QOS flow", NULL, eOPTIONAL},
	{"x", "txmaxpacket", "Integer that defines the maximum packet size (in bytes) allowed in the IP flow for tx QOS flow", NULL, eOPTIONAL},
	{"e", "txber", "The undetected BER for each IP flow in the delivered packets for tx QOS flow (0 to 8)", NULL, eOPTIONAL},
	{"r", "txpriority", "Relative priority of the flow for tx QOS flow (0 to 3)", NULL, eOPTIONAL},
	{"o", "txprofileid", "Profile ID shorthand for a defined set of QoS flow parameters for tx QOS flow (CDMA)", NULL, eOPTIONAL},
	{"y", "txnetpriority", "Flow priority used by the network for tx QOS flow (CDMA)", NULL, eOPTIONAL},
	{"g", "txflag", "IM CN subsystem signaling flag for tx QOS flow", NULL, eOPTIONAL},
	{"s", "txclassid", "QoS Class Identifier for tx QOS flow (QCI) 0-70", NULL, eOPTIONAL},
	{"F", "rxflow", "Current flow status for rx QOS flow", NULL, eOPTIONAL},
	{"K", "rxmask", "Valid parameters mask for rx QOS flow", NULL, eOPTIONAL},
	{"C", "rxclass", "IP traffic class for rx QOS flow", NULL, eOPTIONAL},
	{"A", "rxmaxrate", "Maximum required data rate for rx QOS flow (bits per second)", NULL, eOPTIONAL},
	{"I", "rxminrate", "Minimum guaranteed data rate for rx QOS flow (bits per second)", NULL, eOPTIONAL},
	{"U", "rxfullrate", "Maximum rate at which data can be transmitted when the token bucket is full for rx QOS flow (bits per second)", NULL, eOPTIONAL},
	{"B", "rxbucketrate", "Rate at which tokens are put in the token bucket for rx QOS flow (bits per second)", NULL, eOPTIONAL},
	{"T", "rxmaxtokens", "Maximum number of tokens that can be accumulated at any instance for rx QOS flow (bytes)", NULL, eOPTIONAL},
	{"D", "rxmaxdelay", "Maximum delay for rx QOS flow (in milliseconds)", NULL, eOPTIONAL},
	{"L", "rxlatencydiff", "Difference between the maximum and minimum latency for rx QOS flow (in milliseconds)", NULL, eOPTIONAL},
	{"M", "rxm", "Factor m in calculating packet error rate for rx QOS flow: E = m*10**(-p)", NULL, eOPTIONAL},
	{"P", "rxp", "Factor p in calculating packet error rate for rx QOS flow: E = m*10**(-p)", NULL, eOPTIONAL},
	{"N", "rxminpacket", "Integer that defines the minimum packet size (in bytes) that will be policed for QoS guarantees for rx QOS flow", NULL, eOPTIONAL},
	{"X", "rxmaxpacket", "Integer that defines the maximum packet size (in bytes) allowed in the IP flow for rx QOS flow", NULL, eOPTIONAL},
	{"E", "rxber", "The undetected BER for each IP flow in the delivered packets for rx QOS flow (0 to 8)", NULL, eOPTIONAL},
	{"R", "rxpriority", "Relative priority of the flow for rx QOS flow (0 to 3)", NULL, eOPTIONAL},
	{"O", "rxprofileid", "Profile ID shorthand for a defined set of QoS flow parameters for rx QOS flow (CDMA)", NULL, eOPTIONAL},
	{"Y", "rxnetpriority", "Flow priority used by the network for rx QOS flow (CDMA)", NULL, eOPTIONAL},
	{"G", "rxflag", "IM CN subsystem signaling flag for rx QOS flow", NULL, eOPTIONAL},
	{"S", "rxclassid", "QoS Class Identifier for rx QOS flow (QCI) 0-70", NULL, eOPTIONAL},
	{"v", "txfilteripversion", "IP family for TX QOS filter spec: one of: 4, 6", NULL, eOPTIONAL},
	{"h", "txfiltermask4", "valid IPv4 parameters mask for TX QOS filter spec", NULL, eOPTIONAL},
	{"j", "txfilteripv4addr", "IPV4 address for TX QOS filter spec", NULL, eOPTIONAL},
	{"q", "txfilteripv4mask", "IPV4 subnet mask for TX QOS filter spec", NULL, eOPTIONAL},
	{"w", "txfilteripv42addr", "IPV4-2 address for TX QOS filter spec", NULL, eOPTIONAL},
	{"z", "txfilteripv42mask", "IPV4-2 subnet mask for TX QOS filter spec", NULL, eOPTIONAL},
	{"", "txfilteripv4servicevalue", "Type of IPv4 service value for TX QOS filter spec", NULL, eOPTIONAL},
	{"", "txfilteripv4servicemask", "Type of IPv4 service value for TX QOS filter spec", NULL, eOPTIONAL},
	{"", "txfiltermask6", "valid IPv6 parameters mask for TX QOS filter spec", NULL, eOPTIONAL},
	{"", "txfilteripv6addr", "IPV6 address for TX QOS filter spec", NULL, eOPTIONAL},
	{"", "txfilteripv6prefixlength", "IPV6 address prefix length for tx QOS filter spec", NULL, eOPTIONAL},
	{"", "txfilteripv6addr2", "IPV6 address 2 for TX QOS filter spec", NULL, eOPTIONAL},
	{"", "txfilteripv6prefixlength2", "IPV6 address prefix length 2 for tx QOS filter spec", NULL, eOPTIONAL},
	{"", "txfiltertrafficclass", "traffic class value for TX QOS filter spec", NULL, eOPTIONAL},
	{"", "txfiltertrafficmask", "traffic class mask for TX QOS filter spec", NULL, eOPTIONAL},
	{"", "txfilterflowlabel", "IPv6 flow label for TX QOS filter spec", NULL, eOPTIONAL},
	{"", "txfilterxportprotocol", "xport protocol for TX QOS filter spec", NULL, eOPTIONAL},
	{"", "txfilterportmask", "valid port info mask 1 for TX QOS filter spec", NULL, eOPTIONAL},
	{"", "txfiltersourceport", "source port 1 for TX QOS filter spec", NULL, eOPTIONAL},
	{"", "txfiltersourcerange", "source range 1 for TX QOS filter spec", NULL, eOPTIONAL},
	{"", "txfilterdestport", "destination port 1 for TX QOS filter spec", NULL, eOPTIONAL},
	{"", "txfilterdestrange", "destination range 1 for TX QOS filter spec", NULL, eOPTIONAL},
	{"", "txfilterportmask2", "valid port info mask 2 for TX QOS filter spec", NULL, eOPTIONAL},
	{"", "txfiltersourceport2", "source port 2 for TX QOS filter spec", NULL, eOPTIONAL},
	{"", "txfiltersourcerange2", "source range 2 for TX QOS filter spec", NULL, eOPTIONAL},
	{"", "txfilterdestport2", "destination port 2 for TX QOS filter spec", NULL, eOPTIONAL},
	{"", "txfilterdestrange2", "destination range 2 for TX QOS filter spec", NULL, eOPTIONAL},
	{"", "txfiltericmpmask", "valid ICMP filter mask for TX QOS filter spec", NULL, eOPTIONAL},
	{"", "txfiltericmptype", "ICMP type for TX QOS filter spec", NULL, eOPTIONAL},
	{"", "txfiltericmpcode", "ICMP code for TX QOS filter spec", NULL, eOPTIONAL},
	{"", "txfilteripsecmask", "valid IPSEC filter mask 1 for TX QOS filter spec", NULL, eOPTIONAL},
	{"", "txfilteripsecparam", "security parameter index for IPSec 1 for TX QOS filter spec", NULL, eOPTIONAL},
	{"", "txfilteripsecmask2", "valid IPSEC filter mask 2 for TX QOS filter spec", NULL, eOPTIONAL},
	{"", "txfilteripsecparam2", "security parameter index for IPSec 2 for TX QOS filter spec", NULL, eOPTIONAL},
	{"", "txfilterid", "unique identifier for each filter for TX QOS filter spec", NULL, eOPTIONAL},
	{"", "txfilterprecedence", "the order in which filters are applied for TX QOS filter spec", NULL, eOPTIONAL},
	{"V", "rxfilteripversion", "IP family for rx QOS filter spec: one of: 4, 6nt", NULL, eOPTIONAL},
	{"H", "rxfiltermask4", "valid IPv4 parameters mask for rx QOS filter spec", NULL, eOPTIONAL},
	{"J", "rxfilteripv4addr", "IPV4 address for rx QOS filter spec", NULL, eOPTIONAL},
	{"Q", "rxfilteripv4mask", "IPV4 subnet mask for rx QOS filter spec", NULL, eOPTIONAL},
	{"W", "rxfilteripv4addr2", "IPV4 address 2 for rx QOS filter spec", NULL, eOPTIONAL},
	{"Z", "rxfilteripv4mask2", "IPV4 subnet mask 2 for rx QOS filter spec", NULL, eOPTIONAL},
	{"", "rxfilteripv4servicevalue", "Type of IPv4 service value for rx QOS filter spec", NULL, eOPTIONAL},
	{"", "rxfilteripv4servicemask", "Type of IPv4 service mask for rx QOS filter spec", NULL, eOPTIONAL},
	{"", "rxfiltermask6", "valid IPv6 parameters mask for rx QOS filter spec", NULL, eOPTIONAL},
	{"", "rxfilteripv6addr", "IPV6 address for rx QOS filter spec", NULL, eOPTIONAL},
	{"", "rxfilteripv6prefixlength", "IPV6 address prefix length for rx QOS filter spec", NULL, eOPTIONAL},
	{"", "rxfilteripv6addr2", "IPV6 address 2 for rx QOS filter spec", NULL, eOPTIONAL},
	{"", "rxfilteripv6prefixlength2", "IPV6 address prefix length 2 for rx QOS filter spec", NULL, eOPTIONAL},
	{"", "rxfiltertrafficclass", "traffic class value for rx QOS filter spec", NULL, eOPTIONAL},
	{"", "rxfiltertrafficmask", "traffic class mask for rx QOS filter spec", NULL, eOPTIONAL},
	{"", "rxfilterflowlabel", "IPv6 flow label for rx QOS filter spec", NULL, eOPTIONAL},
	{"", "rxfilterxportprotocol", "xport protocol for rx QOS filter spec", NULL, eOPTIONAL},
	{"", "rxfilterportmask", "valid port info mask 1 for rx QOS filter spec", NULL, eOPTIONAL},
	{"", "rxfiltersourceport", "source port 1 for rx QOS filter spec", NULL, eOPTIONAL},
	{"", "rxfiltersourcerange", "source range 1 for rx QOS filter spec", NULL, eOPTIONAL},
	{"", "rxfilterdestport", "destination port 1 for rx QOS filter spec", NULL, eOPTIONAL},
	{"", "rxfilterdestrange", "destination range 1 for rx QOS filter spec", NULL, eOPTIONAL},
	{"", "rxfilterportmask2", "valid port info mask 2 for rx QOS filter spec", NULL, eOPTIONAL},
	{"", "rxfiltersourceport2", "source port 2 for rx QOS filter spec", NULL, eOPTIONAL},
	{"", "rxfiltersourcerange2", "source range 2 for rx QOS filter spec", NULL, eOPTIONAL},
	{"", "rxfilterdestport2", "destination port 2 for rx QOS filter spec", NULL, eOPTIONAL},
	{"", "rxfilterdestrange2", "destination range 2 for rx QOS filter spec", NULL, eOPTIONAL},
	{"", "rxfiltericmpmask", "valid ICMP filter mask for rx QOS filter spec", NULL, eOPTIONAL},
	{"", "rxfiltericmptype", "ICMP type for rx QOS filter spec", NULL, eOPTIONAL},
	{"", "rxfiltericmpcode", "ICMP code for rx QOS filter spec", NULL, eOPTIONAL},
	{"", "rxfilteripsecmask", "valid IPSEC filter mask 1 for rx QOS filter spec", NULL, eOPTIONAL},
	{"", "rxfilteripsecparam", "security parameter index for IPSec 1 for rx QOS filter spec", NULL, eOPTIONAL},
	{"", "rxfilteripsecmask2", "valid IPSEC filter mask 1 for rx QOS filter spec", NULL, eOPTIONAL },
	{"", "rxfilteripsecparam2", "security parameter index for IPSec 1 for rx QOS filter spec", NULL, eOPTIONAL },
	{"", "rxfilterid", "unique identifier for each filter for rx QOS filter spec", NULL, eOPTIONAL},
	{"", "rxfilterprecedence", "the order in which filters are applied for rx QOS filter spec", NULL, eOPTIONAL},
	{"", "tx5gqci", "5G tx QOS class identifier", NULL, eOPTIONAL},
	{"", "rx5gqci", "5G rx QOS class identifier", NULL, eOPTIONAL},
	{"", "txavgwindow", "tx QOS Averaging Window", NULL, eOPTIONAL},
	{"", "rxavgwindow", "rx QOS Averaging Window", NULL, eOPTIONAL}
};

static ARGUMENT_SET g_get_qos_info_arg_set[] =
{
	{"i", "id", "Identifier for the QoS flow/instance that has been negotiated and that is being queried", NULL, eMANDATORY}
};

static ARGUMENT_SET g_qos_indication_register_arg_set[] =
{
	{"r", "report", "Report Global QOS Flows", NULL, eMANDATORY},
	{"s", "suppressreport", "Suppress Report Flow Control", NULL, eMANDATORY},
	{"n", "suppressnet", "Suppress Network Status Indication", NULL, eMANDATORY}
};

static ARGUMENT_SET g_qos_apn_params_arg_set[] =
{
	{"i", "id", "The APN Profile ID to obtain QOS info", NULL, eMANDATORY}
};

static ARGUMENT_SET g_set_data_format_arg_set[] =
{
	{"q", "qosheader", "Set QOS header present [0|1] or [Yes|No] or [Y|N].", "QOS header present", eOPTIONAL},
	{"u", "uldamaxdg", "Uplink data aggregation max datagram.", "Uplink data aggregation max datagram", eOPTIONAL},
	{"d", "dldamaxdg", "Downlink data aggregation max datagram.", "Downlink data aggregation max datagram", eOPTIONAL},
	{"U", "uldamaxsz", "Uplink data aggregation max size.", "Uplink data aggregation max size", eOPTIONAL},
	{"D", "dldamaxsz", "Downlink data aggregation max size.", "Downlink data aggregation max size", eOPTIONAL},
	{"e", "pepid", "Set peripheral endpoint ID [0|1] or [Yes|No] or [Y|N].  Default is 'no'.", "Set eripheral endpoint ID", eOPTIONAL},
	{"p", "dlpadding", "QMAP downlink minimum padding: 0-64, 4-byte aligned.", "Downlink padding", eOPTIONAL},
	{"f", "flowctrl", "Flow control done by TE [0|1] or [Yes|No] or [Y|N].", "Flow control by TE", eOPTIONAL}
};

static ARGUMENT_SET g_wds_register_event[] =
{
	{"A", "ccri", "0|1", NULL, eOPTIONAL},
	{"B", "tsi", "0|1", NULL, eOPTIONAL},
	{"C", "tsim", "Requested statistic bit mask (0x0001|0x0002|0x0004|0x0008|0x0020|0x0040|0x0080|0x0100|0x0200)", NULL, eOPTIONAL},
	{"D", "dbti", "0|1", NULL, eOPTIONAL},
	{"E", "dsi", "0|1", NULL, eOPTIONAL},
	{"H", "msi", "0|1", NULL, eOPTIONAL},
	{"I", "dcsi", "0|1", NULL, eOPTIONAL},
	{"J", "cpdsi", "0|1", NULL, eOPTIONAL},
	{"L", "epmsi", "0|1", NULL, eOPTIONAL},
	{"M", "ufci", "0|1", NULL, eOPTIONAL},
	{"N", "apfri", "0|1", NULL, eOPTIONAL},
	{"O", "dbtxi", "0|1", NULL, eOPTIONAL},
	{"P", "dri", "0|1", NULL, eOPTIONAL},
};

static ARGUMENT_SET g_enable_keep_alive[] =
{
	{"e", "enable", "Enable/disable keep data session alive", "0|1", eMANDATORY}
};

static ARGUMENT_SET g_help_arg_set[] =
{
	{"c", "command", "Command information.", NULL, eOPTIONAL}
};

static COMMAND_SET g_cmdset[] =
{
	{
		"startsingle",
		"start a single-PDN data session",
		sizeof(g_session_arg_set) / sizeof(ARGUMENT_SET),
		g_session_arg_set,
		eSTART_LTE_DATA_SESSION
	},
	{
		"start",
		"Start one connection of a multi-PDN data session",
		sizeof(g_session_arg_set2) / sizeof(ARGUMENT_SET),
		g_session_arg_set2,
		eSTART_MPDN_DATASESSION
	},
	{
		"stop",
		"Stop one connection",
		sizeof(g_stop_arg_set) / sizeof(ARGUMENT_SET),
		g_stop_arg_set,
		eSTOP_DATA_SESSION
	},
	{
		"stopall",
		"Stop all active connections",
		0,
		NULL,
		eSTOP_DATA_SESSIONS
	},
	{
		"displayallprofiles",
		"Display all profiles on the device",
		0,
		NULL,
		eDISPLAY_ALL_PROFILES
	},
	{
		"displayprofile",
		"Display one profile on the device",
		sizeof(g_disp_profile_arg_set) / sizeof(ARGUMENT_SET),
		g_disp_profile_arg_set,
		eDISPLAY_SINGLE_PROFILE
	},
	{
		"createprofile",
		"Create a profile on the device",
		sizeof(g_profile_arg_set) / sizeof(ARGUMENT_SET),
		g_profile_arg_set,
		eCREATE_PROFILE
	},
	{
		"modifyprofile",
		"Modify an existing profile on the device",
		sizeof(g_profile_arg_set2) / sizeof(ARGUMENT_SET),
		g_profile_arg_set2,
		eMODIFY_PROFILE_SETTINGS
	},
	{
		"deleteprofile",
		"Delete a profile from the device",
		sizeof(g_del_profile_arg_set) / sizeof(ARGUMENT_SET),
		g_del_profile_arg_set,
		eDELETE_PROFILE
	},
	{
		"scannetworks",
		"Scan available networks",
		0,
		NULL,
		eSCAN_NETWORKS
	},
	{
		"enableqosevent",
		"Enable QOS Event",
		0,
		NULL,
		eENABLE_QOS_EVENT
	},
	{
		"disableqosevent",
		"Disable QOS Event",
		0,
		NULL,
		eDISABLE_QOS_EVENT
	},
	{
		"reqqosex",
		"Request QOS Expanded",
		sizeof(g_request_qosex_arg_set) / sizeof(ARGUMENT_SET),
		g_request_qosex_arg_set,
		eREQUEST_QOSEX
	},
	{
		"getqosinfo",
		"Get QOS Information",
		sizeof(g_get_qos_info_arg_set) / sizeof(ARGUMENT_SET),
		g_get_qos_info_arg_set,
		eGET_QOSINFO
	},
	{
		"qosindreg",
		"QOS Indication Register",
		sizeof(g_qos_indication_register_arg_set) / sizeof(ARGUMENT_SET),
		g_qos_indication_register_arg_set,
		eSET_QOS_INDICATION_REGISTER
	},
	{
		"readqosdatastats",
		"Read QOS Data Statistics (SWIQOS)",
		sizeof(g_qos_apn_params_arg_set) / sizeof(ARGUMENT_SET),
		g_qos_apn_params_arg_set,
		eREAD_QOS_DATA_STATISTIC
	},
	{
		"readqosextraapnparams",
		"Read QOS Extra APN Parameters (SWIQOS)",
		sizeof(g_qos_apn_params_arg_set) / sizeof(ARGUMENT_SET),
		g_qos_apn_params_arg_set,
		eREAD_QOS_EXTRA_APN_PARAMS
	},
	{
		"getpktstats",
		"Get Packet Statistics",
		0,
		NULL,
		eGET_PKT_STATS
	},
	{
		"getcurchrate",
		"Get Current Channel Rate",
		0,
		NULL,
		eGET_CURRENT_CHANNEL_RATE
	},
	{
		"toggleping",
		"Toggle pinging on connection",
		0,
		NULL,
		eTOGGLE_PING
	},
	{
		"togglerouteupdate",
		"Toggle routing table update on connection",
		0,
		NULL,
		eTOGGLE_ROUTE_UPDATE
	},
	{
		"", // "getloopback"
		"", // "Get loopback"
		0,
		NULL,
		eGET_LOOPBACK
	},
	{
		"", // "setloopback"
		"", // "Set loopback"
		0,
		NULL,
		eSET_LOOPBACK
	},
	{
		"enableqmap",
		"Enable QMAP",
		sizeof(g_set_data_format_arg_set) / sizeof(ARGUMENT_SET),
		g_set_data_format_arg_set,
		eENABLE_QMAP
	},
	{
		"disableqmap",
		"Disable QMAP",
		0,
		NULL,
		eDISABLE_QMAP
	},
	{
		"SetWdsEventReport",
		"Enable/disable WDS event report indication",
		sizeof(g_wds_register_event) / sizeof(ARGUMENT_SET),
		g_wds_register_event,
		eSET_WDS_EVENT_REPORT
	},
	{
		"keepdatasessionalive",
		"Enable/disable keep data session alive",
		sizeof(g_enable_keep_alive) / sizeof(ARGUMENT_SET),
		g_enable_keep_alive,
		eSET_KEEP_ALIVE_DATA_SESSION
	},
	{
		"exit",
		"Stop all active connections and shut down the server",
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

static StrIntValMap g_IpTypeMap[] =
{
	{"4", IPv4_FAMILY_PREFERENCE},
	{"6", IPv6_FAMILY_PREFERENCE},
	{"46", IPv4v6_FAMILY_PREFERENCE}
};

static StrIntValMap g_PdpTypeMap[] =
{
	{"IPv4", 0},
	{"PPP", 1},
	{"IPv6", 2},
	{"IPv4v6", 3}
};

static StrIntValMap g_AuthTypeMap[] =
{
	{"none", 0},
	{"pap", 1},
	{"chap", 2},
	{"papchap", 3}
};

void PrintPrompt(void)
{
	OutputPrompt(g_cmdset, sizeof(g_cmdset) / sizeof(COMMAND_SET) - 2); // "- 2" so not to print "exit" and "help"
}

/*
 * Name:     GetPDPType
 *
 * Purpose:  Prompt the user to enter the PDP Type.
 *
 * Params:   None
 *
 * Return:   PDP Type value provided by the user(between 0 - 3),
 *           or hex value of enter key if pressed by the user.
 *
 * Notes:    None
 */
int GetPDPType()
{
	return GetNumericValue(NULL, "PDP Type value( 0 - IPv4, 1 - PPP, 2 - IPV6, 3 - IPV4V6 )",
		g_enterActionExit, ENTER_KEY, 0, 3);
}

/*
 * Name:     GetAuthenticationValue
 *
 * Purpose:  Prompt the user to enter the Authentication value.
 *
 * Params:   None
 *
 * Return:   Authentication value provided by the user(between 0 - 3),
 *           or hex value of enter key if pressed by the user.
 *
 * Notes:    None
 */
int GetAuthenticationValue()
{
	return GetNumericValue(NULL, "Authentication value (0 - None (default), 1 - PAP, 2 - CHAP, 3 - PAP/CHAP)",
		g_enterActionDefault, 0, 0, 3);
}

/*
 * Name:     GetIPFamilyPreference
 *
 * Purpose:  Prompt the user to enter the IP Family preference
 *
 * Params:   None
 *
 * Return:   IPFamilyPreference
 *
 * Notes:    None
 */
int GetIPFamilyPreference()
{
	// marc modification IPv4 only
	return IPv4_FAMILY_PREFERENCE;

	switch (GetNumericValue("1: IPV4 (default)\n2: IPV6\n3: IPV4V6",
		"IP family preference for the call", g_enterActionDefault, 1, 1, 3))
	{
	case 2:
		return IPv6_FAMILY_PREFERENCE;
	case 3:
		return IPv4v6_FAMILY_PREFERENCE;
		//case 1:
	default:
		break;
	}

	return IPv4_FAMILY_PREFERENCE;
}

/*
 * Name:     GetUserProfileId
 *
 * Purpose:  Prompt the user to enter the profile id whose information needs to
 *           be retrieved.
 *
 * Params:   None
 *
 * Return:   Profile index selected by the user(between 1 - 42),
 *           or hex value of enter key if pressed by the user else FALSE.
 *
 * Notes:    None
 */
int GetUserProfileId(int min, int max)
{
	//marc need to be modify 
	char fmt[64];
	snprintf(fmt, sizeof(fmt), "a profile id (%d-%d)", min, max);
	//return GetNumericValue(NULL, fmt, g_enterActionExit, ENTER_KEY_PRESSED, min, max);
	return 1; // select profile number 1
}

int GetProfileInfo(struct profileInformation* pProfileInfo)
{
	if (pProfileInfo == NULL)
		return ENTER_KEY;

	pProfileInfo->PDPType = GetPDPType();	// Get PDP Type

	if (ENTER_KEY == pProfileInfo->PDPType)
		return ENTER_KEY;	// 0x0A

	char IPAddress[MAX_FIELD_SIZE];

	/* Prompt the user to enter the profile parameter values */
	/* Get the IP Address */
	GetIPFromUser("IP", IPAddress, &pProfileInfo->IPAddress);

	/* Get the Primary DNS Address */
	GetIPFromUser("PrimaryDNS Address", IPAddress, &pProfileInfo->primaryDNS);

	/* Get the Secondary DNS Address */
	GetIPFromUser("SecondaryDNS Address", IPAddress, &pProfileInfo->secondaryDNS);

	/* Get Authentication From the user */
	pProfileInfo->Authentication = GetAuthenticationValue();

	/* Get Profile Name from the user, Max size is 14 characters */
	GetStringFromUser(NULL, "Profile Name", g_enterActionLeaveEmpty, (char*)pProfileInfo->profileName, MAX_PROFILE_NAME_SIZE);

	/* Get APN Name from the user */
	GetStringFromUser(NULL, "APN Name", g_enterActionLeaveEmpty, (char*)pProfileInfo->APNName, MAX_APN_SIZE);

	/* Get User Name from the user */
	GetStringFromUser(NULL, "User Name", g_enterActionLeaveEmpty, (char*)pProfileInfo->userName, MAX_USER_NAME_SIZE);

	/* Get Password from the user */
	GetStringFromUser(NULL, "Password", g_enterActionLeaveEmpty, (char*)pProfileInfo->password, MAX_FIELD_SIZE);

	return 0;
}

// Return the length of APN
int GetConnectionProfileInfo(struct profileInformation* pProfileInfo)
{
	memset(pProfileInfo, 0, sizeof(struct profileInformation));
	
	// marc modification
	return 0;
	if (GetNumericValue(NULL, "Connect via 0: existing profile (default) or 1: explicit APN", g_enterActionDefault, 0, 0, 1) == 0)
		return 0;

	GetStringFromUser(NULL, "APN Name", g_enterActionLeaveEmpty, pProfileInfo->APNName, sizeof(pProfileInfo->APNName));

	pProfileInfo->Authentication = GetAuthenticationValue();

	if (pProfileInfo->Authentication != 0)
	{
		/* Get User Name from the user */
		GetStringFromUser(NULL, "User Name", g_enterActionLeaveEmpty, pProfileInfo->userName, sizeof(pProfileInfo->userName));

		/* Get Password from the user */
		GetStringFromUser(NULL, "Password", g_enterActionLeaveEmpty, pProfileInfo->password, sizeof(pProfileInfo->password));
	}

	return strlen(pProfileInfo->APNName);
}

void GetUserNetworkSelectionPreference(struct netSelectionPref* pPref)
{
	// marc modification
	//pPref->netReg = GetNumericValue(NULL, "Network selection preference (0: Auto (default), 1: Manual)", g_enterActionDefault, 0, 0, 1);
	pPref->netReg=0;
	if (pPref->netReg == 1)
	{
		// Manual
		pPref->mcc = GetNumericValue(NULL, "3 digit MCC. If empty, use auto network selection", g_enterActionLeaveEmpty, 0, 100, 999);
		if (pPref->mcc != 0)
			pPref->mnc = GetNumericValue(NULL, "2 or 3 digit MNC. If empty, use auto network selection", g_enterActionLeaveEmpty, 0, 10, 999);

		if (pPref->mcc == 0 || pPref->mnc == 0)
		{
			pPref->netReg = 0;
			pPref->mcc = 0;
			pPref->mnc = 0;
		}
	}
}

void ReleaseQosExReqResource(pack_qos_SLQSRequestQosExReq_t* pRequestQosExReq)
{
	if (pRequestQosExReq == NULL)
		return;

	if (pRequestQosExReq->pTxQosFlowList)
	{
		free(pRequestQosExReq->pTxQosFlowList->pQosFlow);
		free(pRequestQosExReq->pTxQosFlowList);
		pRequestQosExReq->pTxQosFlowList = NULL;
	}

	if (pRequestQosExReq->pRxQosFlowList)
	{
		free(pRequestQosExReq->pRxQosFlowList->pQosFlow);
		free(pRequestQosExReq->pRxQosFlowList);
		pRequestQosExReq->pRxQosFlowList = NULL;
	}

	if (pRequestQosExReq->pTxQosFilterSpecsList)
	{
		free(pRequestQosExReq->pTxQosFilterSpecsList->pQoSFilterSpecs);
		free(pRequestQosExReq->pTxQosFilterSpecsList);
		pRequestQosExReq->pTxQosFilterSpecsList = NULL;
	}

	if (pRequestQosExReq->pRxQosFilterSpecsList)
	{
		free(pRequestQosExReq->pRxQosFilterSpecsList->pQoSFilterSpecs);
		free(pRequestQosExReq->pRxQosFilterSpecsList);
		pRequestQosExReq->pRxQosFilterSpecsList = NULL;
	}

	if (pRequestQosExReq->pTx5GQCI)
	{
		free(pRequestQosExReq->pTx5GQCI->pTxRx_5g_qci);
		free(pRequestQosExReq->pTx5GQCI);
		pRequestQosExReq->pTx5GQCI = NULL;
	}

	if (pRequestQosExReq->pRx5GQCI)
	{
		free(pRequestQosExReq->pRx5GQCI->pTxRx_5g_qci);
		free(pRequestQosExReq->pRx5GQCI);
		pRequestQosExReq->pRx5GQCI = NULL;
	}

	if (pRequestQosExReq->pTxQosAveragingWindow)
	{
		free(pRequestQosExReq->pTxQosAveragingWindow->pTxRx_averaging_window);
		free(pRequestQosExReq->pTxQosAveragingWindow);
		pRequestQosExReq->pTxQosAveragingWindow = NULL;
	}

	if (pRequestQosExReq->pRxQosAveragingWindow)
	{
		free(pRequestQosExReq->pRxQosAveragingWindow->pTxRx_averaging_window);
		free(pRequestQosExReq->pRxQosAveragingWindow);
		pRequestQosExReq->pRxQosAveragingWindow = NULL;
	}
}

enum ARGUMENT_AVAIL SetValidBoolValuePointer(const ARGUMENT_SET* pArg, unsigned char* pValue, unsigned char** ppValue)
{
	bool bSet = false;
	enum ARGUMENT_AVAIL ret = GetArgumentByteBool01ValueWithSetFlag(NULL, pArg, pValue, &bSet);

	*ppValue = bSet ? pValue : NULL;
	
	return ret;
}

enum eUserOptions GetCMSocketCommand(const char* procname, socketCommandParam* cmdParam, bool bQoSSupport/* To be replaced with swiwds , bool bSwinasSupport*/)
{
	memset(cmdParam, 0, sizeof(socketCommandParam));

	char* command = NULL;

	int cmd = GetSocketCommand(g_cmdset, sizeof(g_cmdset) / sizeof(COMMAND_SET), &command, eUNKNOWN);


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
	case eSTART_LTE_DATA_SESSION:
	case eSTART_MPDN_DATASESSION:
	{
		bool gotMcc = GetArgumentIntValue(command, &g_session_arg_set[0], &cmdParam->sessionInfo.netSelPref.mcc) == eFound;
		bool gotMnc = GetArgumentIntValue(NULL, &g_session_arg_set[1], &cmdParam->sessionInfo.netSelPref.mcc) == eFound;
		bool gotIpType = GET_ARG_MAPPED_STR_VALUE(NULL, &g_session_arg_set[2], g_IpTypeMap, &cmdParam->sessionInfo.profileInfo.PDPType) == eFound;
		bool gotApn = CLONE_ARG_STR_VALUE(NULL, &g_session_arg_set[3], cmdParam->sessionInfo.profileInfo.APNName) == eFound;
		bool gotAuthType = GET_ARG_MAPPED_STR_VALUE(NULL, &g_session_arg_set[4], g_AuthTypeMap, &cmdParam->sessionInfo.profileInfo.Authentication) == eFound;
		bool gotUsername = CLONE_ARG_STR_VALUE(NULL, &g_session_arg_set[5], cmdParam->sessionInfo.profileInfo.userName) == eFound;
		bool gotPassword = CLONE_ARG_STR_VALUE(NULL, &g_session_arg_set[6], cmdParam->sessionInfo.profileInfo.password) == eFound;
		bool gotProfileNumber = GetArgumentIntValue(NULL, &g_session_arg_set[7], &cmdParam->sessionInfo.profileInfo.profileNumber) == eFound;

		if (gotMcc && gotMnc)
		{
			cmdParam->sessionInfo.netSelPref.netReg = 1;
		}
		else if (gotMcc)
		{
			SockLog(eLOG_INFO, "Error: MCC was specified, but not MNC\n");
			cmd = eUNKNOWN;
			break;
		}
		else if (gotMnc)
		{
			SockLog(eLOG_INFO, "Error: MNC was specified, but not MCC\n");
			cmd = eUNKNOWN;
			break;
		}
		else
		{
			cmdParam->sessionInfo.netSelPref.netReg = 0;
		}

		if ((gotApn || gotAuthType || gotUsername || gotPassword) && gotProfileNumber)
		{
			SockLog(eLOG_INFO, "Error: Profile number cannot be specified with APN, authentication type, username, or password\n");
			cmd = eUNKNOWN;
			break;
		}

		if (!gotApn && (gotAuthType || gotUsername || gotPassword))
		{
			SockLog(eLOG_INFO, "Error: authentication type, username, and password cannot be specified without APN\n");
			cmd = eUNKNOWN;
			break;
		}

		if (!gotAuthType && (gotUsername || gotPassword))
		{
			SockLog(eLOG_INFO, "Error: username and password cannot be specified without authentication type\n");
			cmd = eUNKNOWN;
			break;
		}

		if (!gotApn && !gotProfileNumber)
		{
			SockLog(eLOG_INFO, "Error: Either APN or profile number must be specified\n");
			cmd = eUNKNOWN;
			break;
		}

		if (!gotIpType)
			cmd = eUNKNOWN;

		break;
	}
	case eSTOP_DATA_SESSION:
		if (GetArgumentIntValue(command, g_stop_arg_set, &cmdParam->sessionNumber) != eFound || cmdParam->sessionNumber >= NUM_WDS_SVC)
			cmd = eUNKNOWN;
		break;
	case eCREATE_PROFILE:
	case eMODIFY_PROFILE_SETTINGS:
	{
		//cmdParam->profileInfo.profileType = PROFILE_TYPE_UMTS;

		if (GetArgumentIntValue(command, &g_profile_arg_set[0], &cmdParam->profileInfo.profileNumber) != eFound ||
			GET_ARG_MAPPED_STR_VALUE(NULL, &g_profile_arg_set[1], g_PdpTypeMap, &cmdParam->profileInfo.PDPType) != eFound ||
			GetArgumentIpValue(NULL, &g_profile_arg_set[2], &cmdParam->profileInfo.IPAddress) == eValueNotFound ||
			GetArgumentIpValue(NULL, &g_profile_arg_set[3], &cmdParam->profileInfo.primaryDNS) == eValueNotFound ||
			GetArgumentIpValue(NULL, &g_profile_arg_set[4], &cmdParam->profileInfo.secondaryDNS) == eValueNotFound ||
			GET_ARG_MAPPED_STR_VALUE(NULL, &g_profile_arg_set[5], g_AuthTypeMap, &cmdParam->profileInfo.Authentication) == eValueNotFound ||
			CLONE_ARG_STR_VALUE(NULL, &g_profile_arg_set[6], cmdParam->profileInfo.profileName) == eValueNotFound ||
			CLONE_ARG_STR_VALUE(NULL, &g_profile_arg_set[7], cmdParam->profileInfo.APNName) == eValueNotFound ||
			CLONE_ARG_STR_VALUE(NULL, &g_profile_arg_set[8], cmdParam->profileInfo.userName) == eValueNotFound ||
			CLONE_ARG_STR_VALUE(NULL, &g_profile_arg_set[9], cmdParam->profileInfo.password) == eValueNotFound)
			cmd = eUNKNOWN;

		break;
	}
	case eDELETE_PROFILE:
	case eDISPLAY_SINGLE_PROFILE:
		if (GetArgumentIntValue(command, g_disp_profile_arg_set, &cmdParam->profileNumber) != eFound)
			cmd = eUNKNOWN;
		break;
	case eREQUEST_QOSEX:
		if (!bQoSSupport)
		{
			cmd = eUNKNOWN;
			break;
		}

		cmdParam->requestQosExReq.pTxQosFlowList = calloc(1, sizeof(pack_qos_QosFlowList_t));
		cmdParam->requestQosExReq.pRxQosFlowList = calloc(1, sizeof(pack_qos_QosFlowList_t));
		cmdParam->requestQosExReq.pTxQosFilterSpecsList = calloc(1, sizeof(pack_qos_QosFilterSpecsList_t));
		cmdParam->requestQosExReq.pRxQosFilterSpecsList = calloc(1, sizeof(pack_qos_QosFilterSpecsList_t));
		cmdParam->requestQosExReq.pTx5GQCI = calloc(1, sizeof(pack_qos_TxRx5GQCI_t));
		cmdParam->requestQosExReq.pRx5GQCI = calloc(1, sizeof(pack_qos_TxRx5GQCI_t));
		cmdParam->requestQosExReq.pTxQosAveragingWindow = calloc(1, sizeof(pack_qos_TxRxQosAveragingWindow_t));
		cmdParam->requestQosExReq.pRxQosAveragingWindow = calloc(1, sizeof(pack_qos_TxRxQosAveragingWindow_t));

		if (cmdParam->requestQosExReq.pTxQosFlowList == NULL ||
			cmdParam->requestQosExReq.pRxQosFlowList == NULL ||
			cmdParam->requestQosExReq.pTxQosFilterSpecsList == NULL ||
			cmdParam->requestQosExReq.pRxQosFilterSpecsList == NULL ||
			cmdParam->requestQosExReq.pTx5GQCI == NULL ||
			cmdParam->requestQosExReq.pRx5GQCI == NULL ||
			cmdParam->requestQosExReq.pTxQosAveragingWindow == NULL ||
			cmdParam->requestQosExReq.pRxQosAveragingWindow == NULL)
		{
			ReleaseQosExReqResource(&cmdParam->requestQosExReq);

			cmd = eUNKNOWN;
			break;
		}
		
		cmdParam->requestQosExReq.pTxQosFlowList->pQosFlow = calloc(1, sizeof(pack_qos_QosFlow_t));
		cmdParam->requestQosExReq.pRxQosFlowList->pQosFlow = calloc(1, sizeof(pack_qos_QosFlow_t));
		cmdParam->requestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs = calloc(1, sizeof(unpack_qos_QosFilterSpecs_t));
		cmdParam->requestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs = calloc(1, sizeof(unpack_qos_QosFilterSpecs_t));
		cmdParam->requestQosExReq.pTx5GQCI->pTxRx_5g_qci = calloc(1, sizeof(uint32_t));
		cmdParam->requestQosExReq.pRx5GQCI->pTxRx_5g_qci = calloc(1, sizeof(uint32_t));
		cmdParam->requestQosExReq.pTxQosAveragingWindow->pTxRx_averaging_window = calloc(1, sizeof(uint32_t));
		cmdParam->requestQosExReq.pRxQosAveragingWindow->pTxRx_averaging_window = calloc(1, sizeof(uint32_t));

		if (cmdParam->requestQosExReq.pTxQosFlowList->pQosFlow == NULL ||
			cmdParam->requestQosExReq.pRxQosFlowList->pQosFlow == NULL ||
			cmdParam->requestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs == NULL ||
			cmdParam->requestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs == NULL ||
			cmdParam->requestQosExReq.pTx5GQCI->pTxRx_5g_qci == NULL ||
			cmdParam->requestQosExReq.pRx5GQCI->pTxRx_5g_qci == NULL ||
			cmdParam->requestQosExReq.pTxQosAveragingWindow->pTxRx_averaging_window == NULL ||
			cmdParam->requestQosExReq.pRxQosAveragingWindow->pTxRx_averaging_window == NULL)
		{
			ReleaseQosExReqResource(&cmdParam->requestQosExReq);

			cmd = eUNKNOWN;
			break;
		}
		
		if (eFound == GetArgumentByteValue(command, &g_request_qosex_arg_set[0], &cmdParam->requestQosExReq.pTxQosFlowList->pQosFlow->flow_status) &&
			eFound == GetArgumentInt64Value(command, &g_request_qosex_arg_set[1], &cmdParam->requestQosExReq.pTxQosFlowList->pQosFlow->flow_valid_params) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[2], &cmdParam->requestQosExReq.pTxQosFlowList->pQosFlow->ip_flow_trf_cls) &&
			eFound == GetArgumentInt64Value(command, &g_request_qosex_arg_set[3], &cmdParam->requestQosExReq.pTxQosFlowList->pQosFlow->data_rate_max) &&
			eFound == GetArgumentInt64Value(command, &g_request_qosex_arg_set[4], &cmdParam->requestQosExReq.pTxQosFlowList->pQosFlow->guaranteed_rate) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[5], &cmdParam->requestQosExReq.pTxQosFlowList->pQosFlow->peak_rate) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[6], &cmdParam->requestQosExReq.pTxQosFlowList->pQosFlow->token_rate) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[7], &cmdParam->requestQosExReq.pTxQosFlowList->pQosFlow->bucket_size) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[8], &cmdParam->requestQosExReq.pTxQosFlowList->pQosFlow->ip_flow_latency) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[9], &cmdParam->requestQosExReq.pTxQosFlowList->pQosFlow->ip_flow_jitter) &&
			eFound == GetArgumentInt16Value(command, &g_request_qosex_arg_set[10], &cmdParam->requestQosExReq.pTxQosFlowList->pQosFlow->ip_flow_pkt_error_rate_multiplier) &&
			eFound == GetArgumentInt16Value(command, &g_request_qosex_arg_set[11], &cmdParam->requestQosExReq.pTxQosFlowList->pQosFlow->ip_flow_pkt_error_rate_exponen) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[12], &cmdParam->requestQosExReq.pTxQosFlowList->pQosFlow->ip_flow_min_policed_packet_size) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[13], &cmdParam->requestQosExReq.pTxQosFlowList->pQosFlow->ip_flow_max_allowed_packet_size) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[14], &cmdParam->requestQosExReq.pTxQosFlowList->pQosFlow->ip_flow_3gpp_residual_bit_error_rate) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[15], &cmdParam->requestQosExReq.pTxQosFlowList->pQosFlow->ip_flow_3gpp_traffic_handling_priority) &&
			eFound == GetArgumentInt16Value(command, &g_request_qosex_arg_set[16], &cmdParam->requestQosExReq.pTxQosFlowList->pQosFlow->ip_flow_3gpp2_profile_id) &&
			eFound == GetArgumentByteValue(command, &g_request_qosex_arg_set[17], &cmdParam->requestQosExReq.pTxQosFlowList->pQosFlow->ip_flow_3gpp2_flow_priority) &&
			eFound == GetArgumentByteValue(command, &g_request_qosex_arg_set[18], &cmdParam->requestQosExReq.pTxQosFlowList->pQosFlow->ip_flow_3gpp_im_cn_flag) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[19], &cmdParam->requestQosExReq.pTxQosFlowList->pQosFlow->ip_flow_lte_qci))
		{
			cmdParam->requestQosExReq.pTxQosFlowList->tx_qos_flow_len = 1;
		}
		else
		{
			free(cmdParam->requestQosExReq.pTxQosFlowList->pQosFlow);
			free(cmdParam->requestQosExReq.pTxQosFlowList);
			cmdParam->requestQosExReq.pTxQosFlowList = NULL;
		}

		if (eFound == GetArgumentByteValue(command, &g_request_qosex_arg_set[20], &cmdParam->requestQosExReq.pRxQosFlowList->pQosFlow->flow_status) &&
			eFound == GetArgumentInt64Value(command, &g_request_qosex_arg_set[21], &cmdParam->requestQosExReq.pRxQosFlowList->pQosFlow->flow_valid_params) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[22], &cmdParam->requestQosExReq.pRxQosFlowList->pQosFlow->ip_flow_trf_cls) &&
			eFound == GetArgumentInt64Value(command, &g_request_qosex_arg_set[23], &cmdParam->requestQosExReq.pRxQosFlowList->pQosFlow->data_rate_max) &&
			eFound == GetArgumentInt64Value(command, &g_request_qosex_arg_set[24], &cmdParam->requestQosExReq.pRxQosFlowList->pQosFlow->guaranteed_rate) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[25], &cmdParam->requestQosExReq.pRxQosFlowList->pQosFlow->peak_rate) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[26], &cmdParam->requestQosExReq.pRxQosFlowList->pQosFlow->token_rate) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[27], &cmdParam->requestQosExReq.pRxQosFlowList->pQosFlow->bucket_size) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[28], &cmdParam->requestQosExReq.pRxQosFlowList->pQosFlow->ip_flow_latency) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[29], &cmdParam->requestQosExReq.pRxQosFlowList->pQosFlow->ip_flow_jitter) &&
			eFound == GetArgumentInt16Value(command, &g_request_qosex_arg_set[30], &cmdParam->requestQosExReq.pRxQosFlowList->pQosFlow->ip_flow_pkt_error_rate_multiplier) &&
			eFound == GetArgumentInt16Value(command, &g_request_qosex_arg_set[31], &cmdParam->requestQosExReq.pRxQosFlowList->pQosFlow->ip_flow_pkt_error_rate_exponen) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[32], &cmdParam->requestQosExReq.pRxQosFlowList->pQosFlow->ip_flow_min_policed_packet_size) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[33], &cmdParam->requestQosExReq.pRxQosFlowList->pQosFlow->ip_flow_max_allowed_packet_size) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[34], &cmdParam->requestQosExReq.pRxQosFlowList->pQosFlow->ip_flow_3gpp_residual_bit_error_rate) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[35], &cmdParam->requestQosExReq.pRxQosFlowList->pQosFlow->ip_flow_3gpp_traffic_handling_priority) &&
			eFound == GetArgumentInt16Value(command, &g_request_qosex_arg_set[36], &cmdParam->requestQosExReq.pRxQosFlowList->pQosFlow->ip_flow_3gpp2_profile_id) &&
			eFound == GetArgumentByteValue(command, &g_request_qosex_arg_set[37], &cmdParam->requestQosExReq.pRxQosFlowList->pQosFlow->ip_flow_3gpp2_flow_priority) &&
			eFound == GetArgumentByteValue(command, &g_request_qosex_arg_set[38], &cmdParam->requestQosExReq.pRxQosFlowList->pQosFlow->ip_flow_3gpp_im_cn_flag) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[39], &cmdParam->requestQosExReq.pRxQosFlowList->pQosFlow->ip_flow_lte_qci))
		{
			cmdParam->requestQosExReq.pRxQosFlowList->tx_qos_flow_len = 1;
		}
		else
		{
			free(cmdParam->requestQosExReq.pRxQosFlowList->pQosFlow);
			free(cmdParam->requestQosExReq.pRxQosFlowList);
			cmdParam->requestQosExReq.pRxQosFlowList = NULL;
		}

		if (eFound == GetArgumentByteValue(command, &g_request_qosex_arg_set[40], &cmdParam->requestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs->ip_version) &&
			eFound == GetArgumentInt64Value(command, &g_request_qosex_arg_set[41], &cmdParam->requestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs->ipv4_valid_params) &&
			eFound == GetArgumentIpValue(command, &g_request_qosex_arg_set[42], &cmdParam->requestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs->ipv4_addr_1) &&
			eFound == GetArgumentIpValue(command, &g_request_qosex_arg_set[43], &cmdParam->requestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs->ipv4_subnet_mask_1) &&
			eFound == GetArgumentIpValue(command, &g_request_qosex_arg_set[44], &cmdParam->requestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs->ipv4_addr_2) &&
			eFound == GetArgumentIpValue(command, &g_request_qosex_arg_set[45], &cmdParam->requestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs->ipv4_subnet_mask_2) &&
			eFound == GetArgumentByteValue(command, &g_request_qosex_arg_set[46], &cmdParam->requestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs->ipv4_val) &&
			eFound == GetArgumentByteValue(command, &g_request_qosex_arg_set[47], &cmdParam->requestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs->ipv4_mask) &&
			eFound == GetArgumentInt64Value(command, &g_request_qosex_arg_set[48], &cmdParam->requestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs->ipv6_valid_params) &&
			eFound == GetArgumentIpv6Value(command, &g_request_qosex_arg_set[49], cmdParam->requestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs->ipv6_address_1, 16) &&
			eFound == GetArgumentByteValue(command, &g_request_qosex_arg_set[50], &cmdParam->requestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs->ipv6_prefix_len_2) &&
			eFound == GetArgumentIpv6Value(command, &g_request_qosex_arg_set[51], cmdParam->requestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs->ipv6_address_2, 16) &&
			eFound == GetArgumentByteValue(command, &g_request_qosex_arg_set[52], &cmdParam->requestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs->ipv6_prefix_len_2) &&
			eFound == GetArgumentByteValue(command, &g_request_qosex_arg_set[53], &cmdParam->requestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs->ipv6_val) &&
			eFound == GetArgumentByteValue(command, &g_request_qosex_arg_set[54], &cmdParam->requestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs->ipv6_mask) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[55], &cmdParam->requestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs->ipv6_flow_label) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[56], &cmdParam->requestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs->ipv6_xport_protocol) &&
			eFound == GetArgumentInt64Value(command, &g_request_qosex_arg_set[57], &cmdParam->requestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs->port_valid_params_1) &&
			eFound == GetArgumentInt16Value(command, &g_request_qosex_arg_set[58], &cmdParam->requestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs->src_port_1) &&
			eFound == GetArgumentInt16Value(command, &g_request_qosex_arg_set[59], &cmdParam->requestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs->src_range_1) &&
			eFound == GetArgumentInt16Value(command, &g_request_qosex_arg_set[60], &cmdParam->requestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs->des_port_1) &&
			eFound == GetArgumentInt16Value(command, &g_request_qosex_arg_set[61], &cmdParam->requestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs->des_range_1) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[62], (uint32_t*)&cmdParam->requestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs->port_valid_params_2) &&
			eFound == GetArgumentInt16Value(command, &g_request_qosex_arg_set[63], &cmdParam->requestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs->src_port_2) &&
			eFound == GetArgumentInt16Value(command, &g_request_qosex_arg_set[64], &cmdParam->requestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs->src_range_2) &&
			eFound == GetArgumentInt16Value(command, &g_request_qosex_arg_set[65], &cmdParam->requestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs->des_port_2) &&
			eFound == GetArgumentInt16Value(command, &g_request_qosex_arg_set[66], &cmdParam->requestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs->des_range_2) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[67], (uint32_t*)&cmdParam->requestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs->icmp_valid_params) &&
			eFound == GetArgumentByteValue(command, &g_request_qosex_arg_set[68], &cmdParam->requestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs->icmp_type) &&
			eFound == GetArgumentByteValue(command, &g_request_qosex_arg_set[69], &cmdParam->requestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs->icmp_code) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[70], (uint32_t*)&cmdParam->requestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs->ipsec_valid_params) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[71], &cmdParam->requestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs->ipsec_spi) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[72], (uint32_t*)&cmdParam->requestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs->ipsec_valid_params_2) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[73], &cmdParam->requestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs->ipsec_spi_2) &&
			eFound == GetArgumentInt16Value(command, &g_request_qosex_arg_set[74], &cmdParam->requestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs->ipsec_filter_id) &&
			eFound == GetArgumentInt16Value(command, &g_request_qosex_arg_set[75], &cmdParam->requestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs->filter_precedence))
		{
			cmdParam->requestQosExReq.pTxQosFilterSpecsList->tx_qos_filter_len = 1;
		}
		else
		{
			free(cmdParam->requestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs);
			free(cmdParam->requestQosExReq.pTxQosFilterSpecsList);
			cmdParam->requestQosExReq.pTxQosFilterSpecsList = NULL;
		}

		if (eFound == GetArgumentByteValue(command, &g_request_qosex_arg_set[76], &cmdParam->requestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs->ip_version) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[77], (uint32_t*)&cmdParam->requestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs->ipv4_valid_params) &&
			eFound == GetArgumentIpValue(command, &g_request_qosex_arg_set[78], &cmdParam->requestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs->ipv4_addr_1) &&
			eFound == GetArgumentIpValue(command, &g_request_qosex_arg_set[79], &cmdParam->requestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs->ipv4_subnet_mask_1) &&
			eFound == GetArgumentIpValue(command, &g_request_qosex_arg_set[80], &cmdParam->requestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs->ipv4_addr_2) &&
			eFound == GetArgumentIpValue(command, &g_request_qosex_arg_set[81], &cmdParam->requestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs->ipv4_subnet_mask_2) &&
			eFound == GetArgumentByteValue(command, &g_request_qosex_arg_set[82], &cmdParam->requestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs->ipv4_val) &&
			eFound == GetArgumentByteValue(command, &g_request_qosex_arg_set[83], &cmdParam->requestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs->ipv4_mask) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[84], (uint32_t*)&cmdParam->requestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs->ipv6_valid_params) &&
			eFound == GetArgumentIpv6Value(command, &g_request_qosex_arg_set[85], cmdParam->requestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs->ipv6_address_1, 16) &&
			eFound == GetArgumentByteValue(command, &g_request_qosex_arg_set[86], &cmdParam->requestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs->ipv6_prefix_len_1) &&
			eFound == GetArgumentIpv6Value(command, &g_request_qosex_arg_set[87], cmdParam->requestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs->ipv6_address_2, 16) &&
			eFound == GetArgumentByteValue(command, &g_request_qosex_arg_set[88], &cmdParam->requestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs->ipv6_prefix_len_2) &&
			eFound == GetArgumentByteValue(command, &g_request_qosex_arg_set[89], &cmdParam->requestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs->ipv6_val) &&
			eFound == GetArgumentByteValue(command, &g_request_qosex_arg_set[90], &cmdParam->requestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs->ipv6_mask) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[91], &cmdParam->requestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs->ipv6_flow_label) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[92], &cmdParam->requestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs->ipv6_xport_protocol) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[93], (uint32_t*)&cmdParam->requestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs->port_valid_params_1) &&
			eFound == GetArgumentInt16Value(command, &g_request_qosex_arg_set[94], &cmdParam->requestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs->src_port_1) &&
			eFound == GetArgumentInt16Value(command, &g_request_qosex_arg_set[95], &cmdParam->requestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs->src_range_1) &&
			eFound == GetArgumentInt16Value(command, &g_request_qosex_arg_set[96], &cmdParam->requestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs->des_port_1) &&
			eFound == GetArgumentInt16Value(command, &g_request_qosex_arg_set[97], &cmdParam->requestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs->des_range_1) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[98], (uint32_t*)&cmdParam->requestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs->port_valid_params_2) &&
			eFound == GetArgumentInt16Value(command, &g_request_qosex_arg_set[99], &cmdParam->requestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs->src_port_2) &&
			eFound == GetArgumentInt16Value(command, &g_request_qosex_arg_set[100], &cmdParam->requestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs->src_range_2) &&
			eFound == GetArgumentInt16Value(command, &g_request_qosex_arg_set[101], &cmdParam->requestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs->des_port_2) &&
			eFound == GetArgumentInt16Value(command, &g_request_qosex_arg_set[102], &cmdParam->requestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs->des_range_2) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[103], (uint32_t*)&cmdParam->requestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs->icmp_valid_params) &&
			eFound == GetArgumentByteValue(command, &g_request_qosex_arg_set[104], &cmdParam->requestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs->icmp_type) &&
			eFound == GetArgumentByteValue(command, &g_request_qosex_arg_set[105], &cmdParam->requestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs->icmp_code) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[106], (uint32_t*)&cmdParam->requestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs->ipsec_valid_params) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[107], &cmdParam->requestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs->ipsec_spi) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[108], (uint32_t*)&cmdParam->requestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs->ipsec_valid_params_2) &&
			eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[109], &cmdParam->requestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs->ipsec_spi_2) &&
			eFound == GetArgumentInt16Value(command, &g_request_qosex_arg_set[110], &cmdParam->requestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs->ipsec_filter_id) &&
			eFound == GetArgumentInt16Value(command, &g_request_qosex_arg_set[111], &cmdParam->requestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs->filter_precedence))
		{
			cmdParam->requestQosExReq.pRxQosFilterSpecsList->tx_qos_filter_len = 1;
		}
		else
		{
			free(cmdParam->requestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs);
			free(cmdParam->requestQosExReq.pRxQosFilterSpecsList);
			cmdParam->requestQosExReq.pRxQosFilterSpecsList = NULL;
		}

		if (eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[112], cmdParam->requestQosExReq.pTx5GQCI->pTxRx_5g_qci))
		{
			cmdParam->requestQosExReq.pTx5GQCI->tx_rx_5g_qci_len = 1;
		}
		else
		{
			free(cmdParam->requestQosExReq.pTx5GQCI->pTxRx_5g_qci);
			free(cmdParam->requestQosExReq.pTx5GQCI);
			cmdParam->requestQosExReq.pTx5GQCI = NULL;
		}

		if (eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[113], cmdParam->requestQosExReq.pRx5GQCI->pTxRx_5g_qci))
		{
			cmdParam->requestQosExReq.pRx5GQCI->tx_rx_5g_qci_len = 1;
		}
		else
		{
			free(cmdParam->requestQosExReq.pRx5GQCI->pTxRx_5g_qci);
			free(cmdParam->requestQosExReq.pRx5GQCI);
			cmdParam->requestQosExReq.pRx5GQCI = NULL;
		}

		if (eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[114], cmdParam->requestQosExReq.pTxQosAveragingWindow->pTxRx_averaging_window))
		{
			cmdParam->requestQosExReq.pTxQosAveragingWindow->tx_averaging_window_len = 1;
		}
		else
		{
			free(cmdParam->requestQosExReq.pTxQosAveragingWindow->pTxRx_averaging_window);
			free(cmdParam->requestQosExReq.pTxQosAveragingWindow);
			cmdParam->requestQosExReq.pTxQosAveragingWindow = NULL;
		}

		if (eFound == GetArgumentIntValue(command, &g_request_qosex_arg_set[115], cmdParam->requestQosExReq.pRxQosAveragingWindow->pTxRx_averaging_window))
		{
			cmdParam->requestQosExReq.pRxQosAveragingWindow->tx_averaging_window_len = 1;
		}
		else
		{
			free(cmdParam->requestQosExReq.pRxQosAveragingWindow->pTxRx_averaging_window);
			free(cmdParam->requestQosExReq.pRxQosAveragingWindow);
			cmdParam->requestQosExReq.pRxQosAveragingWindow = NULL;
		}

		if (cmdParam->requestQosExReq.pTxQosFlowList == NULL &&
			cmdParam->requestQosExReq.pRxQosFlowList == NULL &&
			cmdParam->requestQosExReq.pTxQosFilterSpecsList == NULL &&
			cmdParam->requestQosExReq.pRxQosFilterSpecsList == NULL &&
			cmdParam->requestQosExReq.pTx5GQCI == NULL &&
			cmdParam->requestQosExReq.pRx5GQCI == NULL &&
			cmdParam->requestQosExReq.pTxQosAveragingWindow == NULL &&
			cmdParam->requestQosExReq.pRxQosAveragingWindow == NULL)
		{
			// Nothing is provided
			cmd = eUNKNOWN;
		}

		break;

	case eGET_QOSINFO:
		if (!bQoSSupport || GetArgumentIntValue(command, &g_get_qos_info_arg_set[0], &cmdParam->id) != eFound)
			cmd = eUNKNOWN;
		break;

	case eSET_QOS_INDICATION_REGISTER:
		if (!bQoSSupport || 
			eValueNotFound == GetArgumentByteValue(command, &g_qos_indication_register_arg_set[0], &cmdParam->qosIndicationRegisterParams.Report_global_qos_flows) ||
			eValueNotFound == GetArgumentByteValue(command, &g_qos_indication_register_arg_set[1], &cmdParam->qosIndicationRegisterParams.Suppress_report_flow_control) ||
			eValueNotFound == GetArgumentByteValue(command, &g_qos_indication_register_arg_set[2], &cmdParam->qosIndicationRegisterParams.Suppress_network_status_ind))
			cmd = eUNKNOWN;
		break;

	case eREAD_QOS_DATA_STATISTIC:
		if (!bQoSSupport || GetArgumentIntValue(command, &g_qos_apn_params_arg_set[0], &cmdParam->id) != eFound)
			cmd = eUNKNOWN;
		break;

	case eREAD_QOS_EXTRA_APN_PARAMS:
		if (!bQoSSupport || GetArgumentIntValue(command, &g_qos_apn_params_arg_set[0], &cmdParam->id) != eFound)
			cmd = eUNKNOWN;
		break;

	case eENABLE_QMAP:
		if (GetArgumentByteBool01ValueWithSetFlag(command, &g_set_data_format_arg_set[0], &cmdParam->dataFormatParams.QosHrPres, &cmdParam->dataFormatParams.SetQosHrPres) == eValueNotFound ||
			GetArgumentIntValueWithSetFlag(command, &g_set_data_format_arg_set[1], &cmdParam->dataFormatParams.UL_Data_Aggregation_Max_Datagrams, &cmdParam->dataFormatParams.SetUL_Data_Aggregation_Max_Datagrams) == eValueNotFound ||
			GetArgumentIntValueWithSetFlag(command, &g_set_data_format_arg_set[2], &cmdParam->dataFormatParams.DL_Data_Aggregation_Max_Datagrams, &cmdParam->dataFormatParams.SetDL_Data_Aggregation_Max_Datagrams) == eValueNotFound ||
			GetArgumentIntValueWithSetFlag(command, &g_set_data_format_arg_set[3], &cmdParam->dataFormatParams.UL_Data_Aggregation_Max_Size, &cmdParam->dataFormatParams.SetUL_Data_Aggregation_Max_Size) == eValueNotFound ||
			GetArgumentIntValueWithSetFlag(command, &g_set_data_format_arg_set[4], &cmdParam->dataFormatParams.DL_Data_Aggregation_Max_Size, &cmdParam->dataFormatParams.SetDL_Data_Aggregation_Max_Size) == eValueNotFound ||
			GetArgumentBoolValue(command, &g_set_data_format_arg_set[5], &cmdParam->dataFormatParams.SetPeripheralEP_ID) == eValueNotFound ||
			GetArgumentIntValueWithSetFlag(command, &g_set_data_format_arg_set[6], &cmdParam->dataFormatParams.DL_Padding, &cmdParam->dataFormatParams.SetDL_Padding) == eValueNotFound ||
			cmdParam->dataFormatParams.DL_Padding > 64 ||
			GetArgumentByteBool01ValueWithSetFlag(command, &g_set_data_format_arg_set[7], &cmdParam->dataFormatParams.Flow_Control, &cmdParam->dataFormatParams.SetFlow_Control) == eValueNotFound)
			cmd = eUNKNOWN;
		cmdParam->dataFormatParams.DL_Padding &= 0xFC;	// Value 0 to 64, 4 aligned
		break;
	case eDISABLE_QMAP:
		break;
	case eSET_WDS_EVENT_REPORT:
	{
		enum ARGUMENT_AVAIL result = GetArgumentByteValue(command, &g_wds_register_event[1], &cmdParam->sWdsSetEventReport.TransferStatInd.statsPeriod);
		if (result == eValueNotFound ||
			(result == eFound && GetArgumentIntValue(NULL, &g_wds_register_event[2], &cmdParam->sWdsSetEventReport.TransferStatInd.statsMask) == eValueNotFound))
		{
			cmd = eUNKNOWN;
			break;
		}
		else
			cmdParam->sWdsSetEventReport.wdsSetEventReport.pTransferStatInd = &cmdParam->sWdsSetEventReport.TransferStatInd;

		if (SetValidBoolValuePointer(&g_wds_register_event[0], &cmdParam->sWdsSetEventReport.CurrChannelRateInd, &cmdParam->sWdsSetEventReport.wdsSetEventReport.pCurrChannelRateInd) == eValueNotFound ||
			SetValidBoolValuePointer(&g_wds_register_event[3], &cmdParam->sWdsSetEventReport.DataBearerTechInd, &cmdParam->sWdsSetEventReport.wdsSetEventReport.pDataBearerTechInd) == eValueNotFound ||
			SetValidBoolValuePointer(&g_wds_register_event[4], &cmdParam->sWdsSetEventReport.DormancyStatusInd, &cmdParam->sWdsSetEventReport.wdsSetEventReport.pDormancyStatusInd) == eValueNotFound ||
			SetValidBoolValuePointer(&g_wds_register_event[5], &cmdParam->sWdsSetEventReport.MIPStatusInd, &cmdParam->sWdsSetEventReport.wdsSetEventReport.pMIPStatusInd) == eValueNotFound ||
			SetValidBoolValuePointer(&g_wds_register_event[6], &cmdParam->sWdsSetEventReport.DataCallStatusChangeInd, &cmdParam->sWdsSetEventReport.wdsSetEventReport.pDataCallStatusChangeInd) == eValueNotFound ||
			SetValidBoolValuePointer(&g_wds_register_event[7], &cmdParam->sWdsSetEventReport.CurrPrefDataSysInd, &cmdParam->sWdsSetEventReport.wdsSetEventReport.pCurrPrefDataSysInd) == eValueNotFound ||
			SetValidBoolValuePointer(&g_wds_register_event[8], &cmdParam->sWdsSetEventReport.EVDOPageMonPerChangeInd, &cmdParam->sWdsSetEventReport.wdsSetEventReport.pEVDOPageMonPerChangeInd) == eValueNotFound ||
			SetValidBoolValuePointer(&g_wds_register_event[9], &cmdParam->sWdsSetEventReport.UlFlowControlInd, &cmdParam->sWdsSetEventReport.wdsSetEventReport.pUlFlowControlInd) == eValueNotFound ||
			SetValidBoolValuePointer(&g_wds_register_event[10], &cmdParam->sWdsSetEventReport.ReportAddPdnFiltersRemoval, &cmdParam->sWdsSetEventReport.wdsSetEventReport.pReportAddPdnFiltersRemoval) == eValueNotFound ||
			SetValidBoolValuePointer(&g_wds_register_event[11], &cmdParam->sWdsSetEventReport.DataBearerTechExtInd, &cmdParam->sWdsSetEventReport.wdsSetEventReport.pDataBearerTechExtInd) == eValueNotFound ||
			SetValidBoolValuePointer(&g_wds_register_event[12], &cmdParam->sWdsSetEventReport.DormancyResultIndicator, &cmdParam->sWdsSetEventReport.wdsSetEventReport.pDormancyResultIndicator) == eValueNotFound)
			cmd = eUNKNOWN;
		break;
	}
	case eSET_KEEP_ALIVE_DATA_SESSION:
		if (GetArgumentBoolValue(command, &g_enable_keep_alive[0], &cmdParam->enableKA) != eFound)
			cmd = eUNKNOWN;
		break;
	case eUNKNOWN:
		SockLog(eLOG_INFO, "Error: invalid command\n");
	default:
		break;
	}

	return cmd;
}
