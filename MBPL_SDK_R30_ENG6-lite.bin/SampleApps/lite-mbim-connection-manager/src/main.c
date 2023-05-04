#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <syslog.h>
#include <inttypes.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/sockios.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <net/route.h>
#include <MbimTransport.h>
#include <BasicConnectDeviceService.h>
#include <MbimSyncObject.h>
#include <MbimTransaction.h>
#include "qmerrno.h"
#include "netlink_util.h"
#include "dev_util.h"
#include "proc_util.h"
#include "str_util.h"
#include "ping.h"

#define VERSION	"1.0.2210.0"

#ifndef ARRAYSIZE
#define ARRAYSIZE(a)                (sizeof(a)/sizeof(a[0]))
#endif

#ifndef MIN
#define  MIN( x, y ) ( ((x) < (y)) ? (x) : (y) )
#endif

#define SUCCESS 0
#define FAILURE -1

#ifndef UNUSEDPARAM
#define UNUSEDPARAM( x ) (void)x
#endif 

#define PING_COUNT	4
#define PING_DELAY	3

static char s_SettingsPath[256];
static char s_DevicePath[256];
static char s_InterfaceName[256];

MbimTransport s_Transport;

// Network error.
uint32_t s_NwError;

// SubscriberReadyState.
MBIM_SUBSCRIBER_READY_STATE s_ReadyState;
wchar_t s_SubscriberId[31];
uint32_t s_SubscriberIdLen = ARRAYSIZE(s_SubscriberId) - 1;
wchar_t s_SimIccId[41];
uint32_t s_SimIccIdLen = ARRAYSIZE(s_SimIccId) - 1;
MBIM_UNIQUE_ID_FLAGS s_ReadyInfo;
MbimTelephoneNumber s_TelephoneNumbers[10];
uint32_t s_TelephoneNumberCount = ARRAYSIZE(s_TelephoneNumbers);

// PinStatus.
MBIM_PIN_TYPE s_PinType;
MBIM_PIN_STATE s_PinState;
uint32_t s_RemainingAttempts;

// RadioState.
MBIM_RADIO_SWITCH_STATE s_HwRadioState;
MBIM_RADIO_SWITCH_STATE s_SwRadioState;

// RegisterState.
MBIM_REGISTER_STATE s_RegisterState;
MBIM_REGISTER_MODE s_RegisterMode;
uint32_t s_AvailableDataClasses;
uint32_t s_CurrentCellularClass;
wchar_t s_ProviderId[7];
uint32_t s_ProviderIdLen = ARRAYSIZE(s_ProviderId) - 1;
wchar_t s_ProviderName[21];
uint32_t s_ProviderNameLen = ARRAYSIZE(s_ProviderName) - 1;
wchar_t s_RoamingText[64];
uint32_t s_RoamingTextLen = ARRAYSIZE(s_RoamingText) - 1;
uint32_t s_RegistrationFlag;

// PacketService.
MBIM_PACKET_SERVICE_STATE s_PacketServiceState;
uint32_t s_HighestAvailableDataClass;
uint64_t s_UplinkSpeed;
uint64_t s_DownlinkSpeed;


typedef struct
{
	char szInterface[IF_NAMESIZE];
	char szDst[INET_ADDRSTRLEN];
	uint32_t dstPrefixLength;	// This is the number of leftmost bits that make up the network mask.
	char szGateway[INET_ADDRSTRLEN];
} IPv4RouteTableEntry;

static void ModifyIPv4RouteEntry(
	IPv4RouteTableEntry* pEntry,
	char* szInterface,
	char* szDst,
	uint32_t* pDstPrefixLength,	// This is the number of leftmost bits that make up the network mask.
	char* szGateway)
{
	// Modifies only non-NULL parameters. Other members are left unchanged.

	if (szInterface)
	{
		StrCpy(pEntry->szInterface, szInterface);
	}

	if (szDst)
	{
		StrCpy(pEntry->szDst, szDst);
	}
	
	if (pDstPrefixLength)
	{
		pEntry->dstPrefixLength = *pDstPrefixLength;
	}

	if (szGateway)
	{
		StrCpy(pEntry->szGateway, szGateway);
	}
}

typedef struct
{
	char szInterface[IF_NAMESIZE];
	char szDst[INET6_ADDRSTRLEN];
	uint32_t dstPrefixLength;	// This is the number of leftmost bits that make up the network mask.
	char szGateway[INET6_ADDRSTRLEN];
} IPv6RouteTableEntry;

static void ModifyIPv6RouteEntry(
	IPv6RouteTableEntry* pEntry,
	char* szInterface,
	char* szDst,
	uint32_t* pDstPrefixLength,	// This is the number of leftmost bits that make up the network mask.
	char* szGateway)
{
	// Modifies only non-NULL parameters. Other members are left unchanged.
	
	if (szInterface)
	{
		StrCpy(pEntry->szInterface, szInterface);
	}

	if (szDst)
	{
		StrCpy(pEntry->szDst, szDst);
	}
	
	if (pDstPrefixLength)
	{
		pEntry->dstPrefixLength = *pDstPrefixLength;
	}

	if (szGateway)
	{
		StrCpy(pEntry->szGateway, szGateway);
	}
}

typedef struct 
{
    wchar_t accessString[MBIM_ACCESS_STRING_MAX_LEN + 1];
    wchar_t userName[MBIM_USER_NAME_MAX_LEN + 1];
    wchar_t password[MBIM_PASSWORD_MAX_LEN + 1];
    MBIM_COMPRESSION compression;
    MBIM_AUTH_PROTOCOL authProtocol;
    MBIM_CONTEXT_IP_TYPE ipType;
	uint8_t contextType[MBIM_UUID_SIZE];
} Profile;

#define MAX_SESSIONS 4			// Arbitrary. May be changed by developer.
#define MAX_IP_ADDRESSES 4		// Arbitrary. May be changed by developer.
#define MAX_DNS_SERVERS 4		// Arbitrary. May be changed by developer.
#define MAX_ROUTES 4			// Arbitrary. May be changed by developer.
#define MAX_PING_DESTINATIONS 4	// Arbitrary. May be changed by developer.

typedef struct
{
	// Profile info used for connect request
	uint32_t sessionId;
	Profile profile;

	// Connect response/indication
	MBIM_ACTIVATION_STATE activationState;
	MBIM_VOICE_CALL_STATE voiceCallState;
	MBIM_CONTEXT_IP_TYPE ipType;
	uint8_t contextType[MBIM_UUID_SIZE];
	uint32_t nwError;

	// IP configuration response/indication
	uint32_t iPv4ConfigurationAvailable;
	uint32_t iPv6ConfigurationAvailable;

	// Note: MBIM can return multiple IPv4addresses. 
	// For the purposes of this program, we'll only use the first array element.
	MBIM_IPV4_ELEMENT iPv4Addresses[MAX_IP_ADDRESSES]; 
	uint32_t iPv4AddressCount;

	// Note: MBIM can return multiple IPv6addresses. 
	// For the purposes of this program, we'll only use the first array element.
	MBIM_IPV6_ELEMENT iPv6Addresses[MAX_IP_ADDRESSES]; 
	uint32_t iPv6AddressCount;

	MBIM_IPV4_ADDRESS iPv4Gateway; 
	MBIM_IPV6_ADDRESS iPv6Gateway; 
	MBIM_IPV4_ADDRESS iPv4DnsServers[MAX_DNS_SERVERS]; 
	uint32_t iPv4DnsServerCount;
	MBIM_IPV6_ADDRESS iPv6DnsServers[MAX_DNS_SERVERS]; 
	uint32_t iPv6DnsServerCount;
	uint32_t iPv4Mtu;
	uint32_t iPv6Mtu;

	// VLAN.
	bool useVlan;	// true if this session is through a VLAN interface.	
	char vlanName[IF_NAMESIZE];	// VLAN associated with this session.
	uint16_t vlanId;	// ID of VLAN.

	// Routing tables. 
	uint32_t iPv4RouteCount;
	IPv4RouteTableEntry iPv4Routes[MAX_ROUTES];	
	uint32_t iPv6RouteCount;
	IPv6RouteTableEntry iPv6Routes[MAX_ROUTES];	

	// Ping destinations. Should align with routing table entries.
	// TODO: undecided whether these should be global to app and not specific to a session.
	uint32_t iPv4PingDestinationCount;
	char iPv4PingDestinations[MAX_PING_DESTINATIONS][INET_ADDRSTRLEN];
	uint32_t iPv6PingDestinationCount;
	char iPv6PingDestinations[MAX_PING_DESTINATIONS][INET6_ADDRSTRLEN];

} Session;

uint16_t s_SessionCount;
Session* s_Sessions[MAX_SESSIONS];

static void PrintUsage()
{
    printf( "\n" );
    printf( "App usage: \n\n" );
    printf( "  lite-mbim-connection-manager -s <path to settings config file> [-V] [-h]\n\n" );
    printf( "  -s  --settingsPath <path to settings config file>\n" );
    printf( "        path to settings configuration file (defaults to settings.conf)\n\n" );
	printf( "  -V  --version\n");
	printf( "        Show version information.\n\n");
	printf( "  -h  --help\n" );
    printf( "        This option prints the usage instructions.\n\n" );
}

const char * const s_ShortOptions = "s:Vh";

/* Command line long options for firmware download tool */
const struct option s_LongOptions[] = {
    {"settingsPath",   1, NULL, 's'},    
	{"version",   0, NULL, 'V'},
	{"help",   0, NULL, 'h'},
    {NULL,     0, NULL,  0 }       /* End of list */
};

static void ParseCommandLine( int argc, char **argv)
{
    int next_option;

    do
    {
        /* Read the next option until there are no more */
        next_option = getopt_long( argc, argv,
                                   s_ShortOptions,
                                   s_LongOptions, NULL );

        switch( next_option )
        {
            case 's':
				StrCpy(s_SettingsPath, optarg);
                break;
            case 'h':
                /* Print usage information */
                PrintUsage();
                exit(0);
                break;
			case 'V':
				break;
            case -1:
                /* Done with options list */
                break;
            default:
              	//  exit(EXIT_FAILURE);
                break;
        }
    }
    while( next_option != -1 );
}

static uint32_t RadioStateCallback(
    uint8_t* informationBuffer, 
    uint32_t informationBufferLength, 
    void* pParseCallbackContext
	)
{
	UNUSEDPARAM(pParseCallbackContext);
	
	uint32_t mbimRet = BasicConnectDeviceService_RadioStateParse(
				informationBuffer, 
				informationBufferLength,
				&s_HwRadioState,
				&s_SwRadioState
	);
	if (mbimRet == MBIM_STATUS_SUCCESS)
	{
		printf("hwRadioState = %s\n", MBIMRadioToString(s_HwRadioState));
		printf("swRadioState = %s\n", MBIMRadioToString(s_SwRadioState));
	}
	else
	{
		printf("BasicConnectDeviceService_RadioStateParse failed\n");
	}

	return mbimRet;
}

static uint32_t RadioStateSet(
	MBIM_RADIO_SWITCH_STATE radioState) 
{
    uint32_t mbimRet = MBIM_STATUS_FAILURE;

    uint8_t informationBuffer[MBIM_MAX_CTRL_TRANSFER]; 
    uint32_t informationBufferLength = sizeof(informationBuffer);

	const uint8_t* deviceService;
	uint32_t cid;	// 
	uint32_t commandType;  

    mbimRet = BasicConnectDeviceService_RadioStateSetBuild(
		&deviceService,
		&cid,
		&commandType,
		informationBuffer,
		&informationBufferLength,
		radioState
		);
	if (mbimRet != MBIM_STATUS_SUCCESS)
	{
		printf("RadioStateSetBuild failed\n");
		return mbimRet;
	}

	mbimRet = MbimTransport_ExecuteCommandSynchronously(
		&s_Transport, 
		deviceService, 
		cid, 
		commandType, 
		NULL, 
		0, 
		RadioStateCallback, 
		NULL, 
		5);

	return mbimRet;
}

static uint32_t RadioStateQuery()
{
    uint32_t mbimRet = MBIM_STATUS_FAILURE;

	const uint8_t* deviceService;
	uint32_t cid;	// 
	uint32_t commandType;  

    mbimRet = BasicConnectDeviceService_RadioStateQueryBuild(
		&deviceService,
		&cid,
		&commandType
		);
	if (mbimRet != MBIM_STATUS_SUCCESS)
	{
		printf("RadioStateQueryBuild failed\n");
		return mbimRet;
	}

	mbimRet = MbimTransport_ExecuteCommandSynchronously(
		&s_Transport, 
		deviceService, 
		cid, 
		commandType, 
		NULL, 
		0, 
		RadioStateCallback, 
		NULL, 
		5);

	return mbimRet;
}

static uint32_t PinCallback(
    uint8_t* informationBuffer, 
    uint32_t informationBufferLength, 
    void* pParseCallbackContext
	)
{
	UNUSEDPARAM(pParseCallbackContext);
	
	uint32_t mbimRet = BasicConnectDeviceService_PinParse(
				informationBuffer, 
				informationBufferLength,
				&s_PinType,
				&s_PinState,
				&s_RemainingAttempts
				);
	if (mbimRet == MBIM_STATUS_SUCCESS)
	{
		printf("pinType = %s\n", MBIMPinTypeToString(s_PinType));
		printf("pinState = %s\n", MBIMPinStateToString(s_PinState));
		printf("remainingAttempts = %"PRIu32"\n", s_RemainingAttempts);
	}
	else
	{
		printf("%s: Parse failed\n", __FUNCTION__);
	}

	return mbimRet;
}

static int PinSet(
    MBIM_PIN_TYPE pinType,
    MBIM_PIN_OPERATION pinOperation,
    wchar_t* pPin,
    wchar_t* pNewPin)
{
    uint32_t mbimRet = MBIM_STATUS_FAILURE;

    uint8_t informationBuffer[MBIM_MAX_CTRL_TRANSFER]; 
    uint32_t informationBufferLength = sizeof(informationBuffer);

	const uint8_t* deviceService;
	uint32_t cid;	// 
	uint32_t commandType;  

    mbimRet = BasicConnectDeviceService_PinSetBuild(
		&deviceService,
		&cid,
		&commandType,
		informationBuffer, 
		&informationBufferLength, 
		pinType, 
		pinOperation, 
		pPin, 
		pNewPin
		);
	if (mbimRet != MBIM_STATUS_SUCCESS)
	{
		printf("PinSetBuild failed\n");
		return mbimRet;
	}

	mbimRet = MbimTransport_ExecuteCommandSynchronously(
		&s_Transport,
		deviceService, 
		cid, 
		commandType, 
		informationBuffer, 
		informationBufferLength, 
		PinCallback, 
		NULL,
		5);

	return mbimRet;
}

static int PinQuery()
{
    uint32_t mbimRet = MBIM_STATUS_FAILURE;

	const uint8_t* deviceService;
	uint32_t cid;	// 
	uint32_t commandType;  

    mbimRet = BasicConnectDeviceService_PinQueryBuild(
		&deviceService,
		&cid,
		&commandType
		);
	if (mbimRet != MBIM_STATUS_SUCCESS)
	{
		printf("PinSetBuild failed\n");
		return mbimRet;
	}

	mbimRet = MbimTransport_ExecuteCommandSynchronously(
		&s_Transport, 
		deviceService, 
		cid, 
		commandType, 
		NULL, 
		0, 
		PinCallback, 
		NULL, 
		5);

	return mbimRet;
}

static uint32_t RegisterStateCallback(
    uint8_t* informationBuffer, 
    uint32_t informationBufferLength, 
    void* pParseCallbackContext
	)
{
	UNUSEDPARAM(pParseCallbackContext);
	
	s_ProviderIdLen = ARRAYSIZE(s_ProviderId) - 1;
	s_ProviderNameLen = ARRAYSIZE(s_ProviderName) - 1;
	s_RoamingTextLen = ARRAYSIZE(s_RoamingText) - 1;

	uint32_t mbimRet = BasicConnectDeviceService_RegisterStateParse(
				informationBuffer, 
				informationBufferLength,
				&s_NwError,
				&s_RegisterState,
				&s_RegisterMode,
				&s_AvailableDataClasses,
				&s_CurrentCellularClass,
				&s_ProviderIdLen,
				s_ProviderId,
				&s_ProviderNameLen,
				s_ProviderName,
				&s_RoamingTextLen,
				s_RoamingText,
				&s_RegistrationFlag
	);
	if (mbimRet == MBIM_STATUS_SUCCESS)
	{
		printf("nwError = %"PRIu32"\n", s_NwError);
		printf("registerState = %s\n", MBIMRegisterStateToString(s_RegisterState));
		printf("registerMode = %s\n", MBIMRegisterModeToString(s_RegisterMode));
		printf("availableDataClasses = 0x%8.8"PRIx32"\n", s_AvailableDataClasses);
		printf("currentCellularClass = 0x%8.8"PRIx32"\n", s_CurrentCellularClass);
		printf("providerIdLen = %"PRIu32"\n", s_ProviderIdLen);
		printf("providerId = %S\n", s_ProviderId);
		printf("providerNameLen = %"PRIu32"\n", s_ProviderNameLen);
		printf("providerName = %S\n", s_ProviderName);
		printf("roamingTextLen = %"PRIu32"\n", s_RoamingTextLen);
		printf("roamingText = %S\n", s_RoamingText);
		printf("registrationFlag = 0x%8.8"PRIx32"\n", s_RegistrationFlag);
	}
	else
	{
		printf("BasicConnectDeviceService_RegisterStateParse failed\n");
	}

	return mbimRet;
}

static int RegisterStateQuery()
{
    uint32_t mbimRet = MBIM_STATUS_FAILURE;

	const uint8_t* deviceService;
	uint32_t cid;	// 
	uint32_t commandType;  

    mbimRet = BasicConnectDeviceService_RegisterStateQueryBuild(
		&deviceService,
		&cid,
		&commandType
		);
	if (mbimRet != MBIM_STATUS_SUCCESS)
	{
		printf("RegisterStateQueryBuild failed\n");
		return mbimRet;
	}

	mbimRet = MbimTransport_ExecuteCommandSynchronously(
		&s_Transport, 
		deviceService, 
		cid, 
		commandType, 
		NULL, 
		0, 
		RegisterStateCallback, 
		NULL, 
		5);

	return mbimRet;
}

static uint32_t PacketServiceCallback(
    uint8_t* informationBuffer, 
    uint32_t informationBufferLength, 
    void* pParseCallbackContext
	)
{
	UNUSEDPARAM(pParseCallbackContext);
	
	uint32_t mbimRet = BasicConnectDeviceService_PacketServiceParse(
				informationBuffer, 
				informationBufferLength,
				&s_NwError,
				&s_PacketServiceState,
				&s_HighestAvailableDataClass,
				&s_UplinkSpeed,
				&s_DownlinkSpeed
	);
	if (mbimRet == MBIM_STATUS_SUCCESS)
	{
		printf("nwError = %"PRIu32"\n", s_NwError);
		printf("packetServiceState = %s\n", MBIMPacketServiceStateToString(s_PacketServiceState));
		printf("highestAvailableDataClass = 0x%8.8"PRIx32"\n", s_HighestAvailableDataClass);
		printf("uplinkSpeed = %"PRIu64"\n", s_UplinkSpeed);
		printf("downlinkSpeed = %"PRIu64"\n", s_DownlinkSpeed);
	}
	else
	{
		printf("BasicConnectDeviceService_PacketServiceParse failed\n");
	}

	return mbimRet;
}

static int PacketServiceQuery()
{
    uint32_t mbimRet = MBIM_STATUS_FAILURE;

	const uint8_t* deviceService;
	uint32_t cid;	// 
	uint32_t commandType;  

    mbimRet = BasicConnectDeviceService_PacketServiceQueryBuild(
		&deviceService,
		&cid,
		&commandType
		);
	if (mbimRet != MBIM_STATUS_SUCCESS)
	{
		printf("PacketServiceQueryBuild failed\n");
		return mbimRet;
	}

	mbimRet = MbimTransport_ExecuteCommandSynchronously(
		&s_Transport, 
		deviceService, 
		cid, 
		commandType, 
		NULL, 
		0, 
		PacketServiceCallback, 
		NULL, 
		5);

	return mbimRet;
}

static uint32_t SubscriberReadyStatusCallback(
    uint8_t* informationBuffer, 
    uint32_t informationBufferLength, 
    void* pParseCallbackContext
	)
{
	UNUSEDPARAM(pParseCallbackContext);
	
	s_SubscriberIdLen = ARRAYSIZE(s_SubscriberId) - 1;
	s_SimIccIdLen = ARRAYSIZE(s_SimIccId) - 1;
	s_TelephoneNumberCount = ARRAYSIZE(s_TelephoneNumbers);

	uint32_t mbimRet = BasicConnectDeviceService_SubscriberReadyStatusParse(
				informationBuffer, 
				informationBufferLength,
				&s_ReadyState,
				&s_SubscriberIdLen,
				s_SubscriberId,
				&s_SimIccIdLen,
				s_SimIccId,
				&s_ReadyInfo,
				s_TelephoneNumbers,
				&s_TelephoneNumberCount
	);
	if (mbimRet == MBIM_STATUS_SUCCESS)
	{
		printf("readyState = %s\n", MBIMSubscriberReadyStateToString(s_ReadyState));
		printf("subscriberIdLen = %"PRIu32"\n", s_SubscriberIdLen);
		printf("subscriberId = %S\n", s_SubscriberId);
		printf("simIccIdLen = %"PRIu32"\n", s_SimIccIdLen);
		printf("simIccId = %S\n", s_SimIccId);
		printf("readyInfo = %s\n", MBIMReadyInfoFlagsToString(s_ReadyInfo));

		uint32_t i;
		for (i = 0; i < s_TelephoneNumberCount; i++)
		{
			printf("telephoneNumber[%d] = %S\n", i, s_TelephoneNumbers[i].value);
		}
	}
	else
	{
		printf("BasicConnectDeviceService_SubscriberReadyStatusParse failed\n");
	}

	return mbimRet;
}

static int SubscriberReadyStatusQuery()
{
    uint32_t mbimRet = MBIM_STATUS_FAILURE;

	const uint8_t* deviceService;
	uint32_t cid;	// 
	uint32_t commandType;  

    mbimRet = BasicConnectDeviceService_SubscriberReadyStatusQueryBuild(
		&deviceService,
		&cid,
		&commandType
		);
	if (mbimRet != MBIM_STATUS_SUCCESS)
	{
		printf("SubscriberReadyStatusQueryBuild failed\n");
		return mbimRet;
	}

	mbimRet = MbimTransport_ExecuteCommandSynchronously(
		&s_Transport, 
		deviceService, 
		cid, 
		commandType, 
		NULL, 
		0, 
		SubscriberReadyStatusCallback, 
		NULL, 
		5);

	return mbimRet;
}

static uint32_t ConnectCallback(
    uint8_t* informationBuffer, 
    uint32_t informationBufferLength, 
    void* pParseCallbackContext
	)
{
	Session* pSession = (Session*)pParseCallbackContext;
	
	uint32_t returnedSessionId;

	uint32_t mbimRet = BasicConnectDeviceService_ConnectParse(
				informationBuffer, 
				informationBufferLength,
				&returnedSessionId,
				&pSession->activationState,
				&pSession->voiceCallState,
				&pSession->ipType,
				pSession->contextType,
				&pSession->nwError
	);
	if (mbimRet == MBIM_STATUS_SUCCESS)
	{
		printf("sessionId = %"PRIu32"\n", returnedSessionId);
		printf("activationState = %s\n", MBIMActivationStateToString(pSession->activationState));
		printf("voiceCallState = %s\n", MBIMVoiceCallStateToString(pSession->voiceCallState));
		printf("ipType = %s\n", MBIMContextIPTypeToString(pSession->ipType));
		printf("contextType = %s\n", MBIMContextTypeToString(pSession->contextType));
		printf("nwError = %"PRIu32"\n", pSession->nwError);
	}
	else
	{
		printf("BasicConnectDeviceService_ConnectParse failed\n");
	}

	return mbimRet;
}

static int ConnectSet(
	Session* pSession,
    MBIM_ACTIVATION_COMMAND activationCommand
) 
{
    uint32_t mbimRet = MBIM_STATUS_FAILURE;

    uint8_t informationBuffer[MBIM_MAX_CTRL_TRANSFER]; 
    uint32_t informationBufferLength = sizeof(informationBuffer);

	const uint8_t* deviceService;
	uint32_t cid;	// 
	uint32_t commandType;  

    mbimRet = BasicConnectDeviceService_ConnectSetBuild(
		&deviceService,
		&cid,
		&commandType,
		informationBuffer, 
		&informationBufferLength, 
		pSession->sessionId,
		activationCommand,
		pSession->profile.accessString,
		pSession->profile.userName,
		pSession->profile.password,
		pSession->profile.compression,
		pSession->profile.authProtocol,
		pSession->profile.ipType,
		pSession->profile.contextType
		);
	if (mbimRet != MBIM_STATUS_SUCCESS)
	{
		printf("ConnectSetBuild failed\n");
		return mbimRet;
	}

	mbimRet = MbimTransport_ExecuteCommandSynchronously(
		&s_Transport,
		deviceService, 
		cid, 
		commandType, 
		informationBuffer, 
		informationBufferLength, 
		ConnectCallback, 
		pSession,
		5);

	return mbimRet;
}

static uint32_t IpConfigurationCallback(
    uint8_t* informationBuffer, 
    uint32_t informationBufferLength, 
    void* pParseCallbackContext
	)
{
	Session* pSession = (Session*)pParseCallbackContext;
	
	uint32_t returnedSessionId;
	pSession->iPv4AddressCount = ARRAYSIZE(pSession->iPv4Addresses);
	pSession->iPv6AddressCount = ARRAYSIZE(pSession->iPv6Addresses);
	pSession->iPv4DnsServerCount = ARRAYSIZE(pSession->iPv4DnsServers);
	pSession->iPv6DnsServerCount = ARRAYSIZE(pSession->iPv6DnsServers);

	uint32_t mbimRet = BasicConnectDeviceService_IpConfigurationParse(
				informationBuffer, 
				informationBufferLength,
				&returnedSessionId,
				&pSession->iPv4ConfigurationAvailable,
				&pSession->iPv6ConfigurationAvailable,
				&pSession->iPv4AddressCount,
				pSession->iPv4Addresses,
				&pSession->iPv6AddressCount,
				pSession->iPv6Addresses,
				&pSession->iPv4Gateway,
				&pSession->iPv6Gateway,
				&pSession->iPv4DnsServerCount,
				pSession->iPv4DnsServers,
				&pSession->iPv6DnsServerCount,
				pSession->iPv6DnsServers,
				&pSession->iPv4Mtu,
				&pSession->iPv6Mtu
			);
	if (mbimRet == MBIM_STATUS_SUCCESS)
	{
		printf("sessionId = %"PRIu32"\n", returnedSessionId);
		printf("iPv4ConfigurationAvailable = 0x%8.8"PRIx32"\n", pSession->iPv4ConfigurationAvailable);
		printf("iPv6ConfigurationAvailable = 0x%8.8"PRIx32"\n", pSession->iPv6ConfigurationAvailable);

		uint32_t i;
		for (i = 0; i < pSession->iPv4AddressCount; i++)
		{
			char szAddress[INET_ADDRSTRLEN] = {'\0'};
			inet_ntop(AF_INET, pSession->iPv4Addresses[i].Address.value, szAddress, INET_ADDRSTRLEN);
			printf("iPv4Address[%d] = %s\n", i, szAddress); 
			printf("onLinkPrefixLength[%d] = %"PRIu32"\n", i, pSession->iPv4Addresses[i].OnLinkPrefixLength); 
		}

		for (i = 0; i < pSession->iPv6AddressCount; i++)
		{
			char szAddress[INET6_ADDRSTRLEN] = {'\0'};
			inet_ntop(AF_INET6, pSession->iPv6Addresses[i].Address.value, szAddress, INET6_ADDRSTRLEN);
			printf("iPv6Address[%d] = %s\n", i, szAddress); 
			printf("onLinkPrefixLength[%d] = %"PRIu32"\n", i, pSession->iPv6Addresses[i].OnLinkPrefixLength); 
		}

		{
			char szAddress[INET_ADDRSTRLEN] = {'\0'};
			inet_ntop(AF_INET, pSession->iPv4Gateway.value, szAddress, INET_ADDRSTRLEN);
			printf("iPv4Gateway = %s\n", szAddress); 
		}
		
		{
			char szAddress[INET6_ADDRSTRLEN] = {'\0'};
			inet_ntop(AF_INET6, pSession->iPv6Gateway.value, szAddress, INET6_ADDRSTRLEN);
			printf("iPv6Gateway = %s\n", szAddress); 
		}
		
		for (i = 0; i < pSession->iPv4DnsServerCount; i++)
		{
			char szAddress[INET_ADDRSTRLEN] = {'\0'};
			inet_ntop(AF_INET, pSession->iPv4DnsServers[i].value, szAddress, INET_ADDRSTRLEN);
			printf("iPv4DnsServer[%d] = %s\n", i, szAddress); 
		}

		for (i = 0; i < pSession->iPv6DnsServerCount; i++)
		{
			char szAddress[INET6_ADDRSTRLEN] = {'\0'};
			inet_ntop(AF_INET6, pSession->iPv6DnsServers[i].value, szAddress, INET6_ADDRSTRLEN);
			printf("iPv6DnsServer[%d] = %s\n", i, szAddress); 
		}

		printf("iPv4Mtu = %"PRIu32"\n", pSession->iPv4Mtu);
		printf("iPv6Mtu = %"PRIu32"\n", pSession->iPv6Mtu);
	}
	else
	{
		printf("BasicConnectDeviceService_IpConfigurationParse failed\n");
	}

	return mbimRet;
}

static int IpConfigurationQuery(Session* pSession)
{
    uint32_t mbimRet = MBIM_STATUS_FAILURE;

    uint8_t informationBuffer[MBIM_MAX_CTRL_TRANSFER]; 
    uint32_t informationBufferLength = sizeof(informationBuffer);

	const uint8_t* deviceService;
	uint32_t cid;	// 
	uint32_t commandType;  

    mbimRet = BasicConnectDeviceService_IpConfigurationQueryBuild(
		&deviceService,
		&cid,
		&commandType,
		informationBuffer,
		&informationBufferLength,
		pSession->sessionId
		);
	if (mbimRet != MBIM_STATUS_SUCCESS)
	{
		printf("IpConfigurationQueryBuild failed\n");
		return mbimRet;
	}

	mbimRet = MbimTransport_ExecuteCommandSynchronously(
		&s_Transport, 
		deviceService, 
		cid, 
		commandType, 
		informationBuffer, 
		informationBufferLength, 
		IpConfigurationCallback, 
		pSession, 
		5);

	return mbimRet;
}

Session* CreateSession(
	uint32_t sessionId,
	char* szUserName,
	char* szPassword,
	char* szAccessString,
	char* szCompressionType,
	char* szAuthProtocolType,
	char* szIpType,
	char* szUseVlan,
	char* szVlanName,
	uint16_t vlanId
	)
{
	Session* pSession = (Session*)calloc(1, sizeof(Session));
	if (!pSession)
	{
		printf("calloc failed\n");
		return NULL;
	}

	pSession->sessionId = sessionId;

	// Must be stored as wchar_t.
	swprintf(pSession->profile.userName, ARRAYSIZE(pSession->profile.userName), L"%s", szUserName);
	swprintf(pSession->profile.password, ARRAYSIZE(pSession->profile.password), L"%s", szPassword);
	swprintf(pSession->profile.accessString, ARRAYSIZE(pSession->profile.accessString), L"%s", szAccessString);

	if (strcmp(szCompressionType, "MBIMCompressionNone") == 0)
	{
		pSession->profile.compression = MBIMCompressionNone;
	}
	else if (strcmp(szCompressionType, "MBIMCompressionEnable") == 0)
	{
		pSession->profile.compression = MBIMCompressionEnable;
	}
	else 
	{
		printf("Invalid compression type.\n");
		free(pSession);
		return NULL;
	}

	if (strcmp(szAuthProtocolType, "MBIMAuthProtocolNone") == 0)
	{
		pSession->profile.authProtocol = MBIMAuthProtocolNone;
	}
	else if (strcmp(szAuthProtocolType, "MBIMAuthProtocolPap") == 0)
	{
		pSession->profile.authProtocol = MBIMAuthProtocolPap;
	}
	else if (strcmp(szAuthProtocolType, "MBIMAuthProtocolChap") == 0)
	{
		pSession->profile.authProtocol = MBIMAuthProtocolChap;
	}
	else if (strcmp(szAuthProtocolType, "MBIMAuthProtocolMsChapV2") == 0)
	{
		pSession->profile.authProtocol = MBIMAuthProtocolMsChapV2;
	}
	else 
	{
		printf("Invalid authProtocol type.\n");
		free(pSession);
		return NULL;
	}

	if (strcmp(szIpType, "MBIMContextIPTypeIPv4") == 0)
	{
		pSession->profile.ipType = MBIMContextIPTypeIPv4;
	}
	else if (strcmp(szIpType, "MBIMContextIPTypeIPv6") == 0)
	{
		pSession->profile.ipType = MBIMContextIPTypeIPv6;
	}
	else if (strcmp(szIpType, "MBIMContextIPTypeIPv4v6") == 0)
	{
		pSession->profile.ipType = MBIMContextIPTypeIPv4v6;
	}
	else if (strcmp(szIpType, "MBIMContextIPTypeIPv4AndIPv6") == 0)
	{
		pSession->profile.ipType = MBIMContextIPTypeIPv4AndIPv6;
	}
	else 
	{
		printf("Invalid ipType.\n");
		free(pSession);
		return NULL;
	}

	if (strcmp(szUseVlan, "true") == 0)
	{
		pSession->useVlan = true;
	}
	else if (strcmp(szUseVlan, "false") == 0)
	{
		pSession->useVlan = false;
	}
	else 
	{
		printf("Invalid useVlan.\n");
		free(pSession);
		return NULL;
	}

	StrCpy(pSession->vlanName, szVlanName);

	pSession->vlanId = vlanId;

	uint8_t contextType[] = MBIMContextTypeInternet;	// Always.   
	memcpy(pSession->profile.contextType, contextType, ARRAYSIZE(contextType));

	// Working variables.
	pSession->activationState = MBIMActivationStateUnknown;
	pSession->voiceCallState = MBIMVoiceCallStateNone;
	pSession->nwError = 0;
	pSession->iPv4ConfigurationAvailable = 0x0;
	pSession->iPv6ConfigurationAvailable = 0x0;
	pSession->iPv4AddressCount = 0;
	pSession->iPv6AddressCount = 0;
	pSession->iPv4DnsServerCount = 0;
	pSession->iPv6DnsServerCount = 0;
	pSession->iPv4Mtu = 0;
	pSession->iPv6Mtu = 0;
	pSession->iPv4RouteCount = 0;	// Routes added later.
	pSession->iPv6RouteCount = 0;
	pSession->iPv4PingDestinationCount = 0;	// Ping destinations added later.
	pSession->iPv6PingDestinationCount = 0;

	return pSession;
}

static int AddRouteEntry(Session* pSession, char* szDst, uint32_t dstPrefixLength)
{
	// Determine if IP4 or IPv6.

	struct in_addr iPv4;
	memset(&iPv4, 0, sizeof(iPv4));
	if (inet_pton(AF_INET, szDst, (void *)&iPv4) == 1)
	{
		// IPv4
		if (pSession->iPv4RouteCount < ARRAYSIZE(pSession->iPv4Routes))
		{
			// Gateway and interface names will be filled in on successful connection.
			ModifyIPv4RouteEntry(&pSession->iPv4Routes[pSession->iPv4RouteCount], "", szDst, &dstPrefixLength, "");  
			pSession->iPv4RouteCount++;
			return 0;
		}
		else
		{
			printf("Too many IPv4 routes defined. Ignoring\n");
		}
		return 0;
	}

	struct in6_addr iPv6;
	memset(&iPv6, 0, sizeof(iPv6));
	if (inet_pton(AF_INET6, szDst, (void *)&iPv6) == 1)
	{
		// IPv6
		if (pSession->iPv6RouteCount < ARRAYSIZE(pSession->iPv6Routes))
		{
			// Gateway and interface names will be filled in on successful connection.
			ModifyIPv6RouteEntry(&pSession->iPv6Routes[pSession->iPv6RouteCount], "", szDst, &dstPrefixLength, "");  
			pSession->iPv6RouteCount++;
			return 0;
		}
		else
		{
			printf("Too many IPv6 routes defined. Ignoring\n");
		}
		return 0;
	}

	return -1;
}

static int AddPingDestination(Session* pSession, char* szDst)
{
	// Determine if IP4 or IPv6.

	struct in_addr iPv4;
	memset(&iPv4, 0, sizeof(iPv4));
	if (inet_pton(AF_INET, szDst, (void *)&iPv4) == 1)
	{
		// IPv4
		if (pSession->iPv4PingDestinationCount < ARRAYSIZE(pSession->iPv4PingDestinations))
		{
			// Gateway and interface names will be filled in on successful connection.
			StrCpy(pSession->iPv4PingDestinations[pSession->iPv4PingDestinationCount], szDst);  
			pSession->iPv4PingDestinationCount++;
			return 0;
		}
		else
		{
			printf("Too many IPv4 ping destinations defined. Ignoring\n");
		}
		return 0;
	}

	struct in6_addr iPv6;
	memset(&iPv6, 0, sizeof(iPv6));
	if (inet_pton(AF_INET6, szDst, (void *)&iPv6) == 1)
	{
		// IPv6
		if (pSession->iPv6PingDestinationCount < ARRAYSIZE(pSession->iPv6PingDestinations))
		{
			// Gateway and interface names will be filled in on successful connection.
			StrCpy(pSession->iPv6PingDestinations[pSession->iPv6PingDestinationCount], szDst);
			pSession->iPv6PingDestinationCount++;
			return 0;
		}
		else
		{
			printf("Too many IPv6 ping destinations defined. Ignoring\n");
		}
		return 0;
	}

	return -1;
}

int SetAdapterIPv4Address(bool bAdd, const char *szInterface, MBIM_IPV4_ELEMENT* pElement)
{
	char szIpAddress[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, pElement->Address.value, szIpAddress, INET_ADDRSTRLEN);

	printf("%s %s address = %s\n", bAdd ? "Adding" : "Removing", szInterface, szIpAddress);
	SetAdaptorAddress(AF_INET, szInterface, bAdd, szIpAddress, pElement->OnLinkPrefixLength);

	return 0;
}

int SetAdapterIPv6Address(bool bAdd, const char *szInterface, MBIM_IPV6_ELEMENT* pElement)
{
	char szIpAddress[INET6_ADDRSTRLEN];
	inet_ntop(AF_INET6, pElement->Address.value, szIpAddress, INET6_ADDRSTRLEN);

	printf("%s %s address = %s\n", bAdd ? "Adding" : "Removing", szInterface, szIpAddress);
	SetAdaptorAddress(AF_INET6, szInterface, bAdd, szIpAddress, pElement->OnLinkPrefixLength);

	return 0;
}

uint32_t FindMaxMtuAcrossAllSessions()
{ 
	uint32_t maxMtuAcrossAllSessions = 0;

	uint32_t sessionIdx;
	for (sessionIdx = 0; sessionIdx != s_SessionCount; sessionIdx++)
	{
		if (s_Sessions[sessionIdx]->iPv4ConfigurationAvailable & MBIM_IPV4_CONFIGURATION_AVAILABLE_MTU)
		{
			if (s_Sessions[sessionIdx]->iPv4Mtu > maxMtuAcrossAllSessions)
			{
				maxMtuAcrossAllSessions = s_Sessions[sessionIdx]->iPv4Mtu;
			}
			if (s_Sessions[sessionIdx]->iPv6Mtu > maxMtuAcrossAllSessions)
			{
				maxMtuAcrossAllSessions = s_Sessions[sessionIdx]->iPv6Mtu;
			}
		}
	}

	return maxMtuAcrossAllSessions;
}

void UpdateRuntimeSettings(Session* pSession)
{
	bool updatingIPv4 = false;
	bool updatingIPv6 = false;

	// Hardware constraint. We have to set interface MTU to minimum MTU of all availabe in session.
	uint32_t minMtu = UINT32_MAX;	

	if (pSession->iPv4ConfigurationAvailable & MBIM_IPV4_CONFIGURATION_AVAILABLE_MTU)
	{
		if (pSession->iPv4Mtu < minMtu)
		{
			minMtu = pSession->iPv4Mtu;
		}
		updatingIPv4 = true;
	}

	if (pSession->iPv6ConfigurationAvailable & MBIM_IPV6_CONFIGURATION_AVAILABLE_MTU)
	{
		if (pSession->iPv6Mtu < minMtu)
		{
			minMtu = pSession->iPv6Mtu;
		}
		updatingIPv6 = true;
	}

	if (minMtu != UINT32_MAX)
	{
		if (pSession->useVlan)
		{
			printf("Setting %s MTU = %" PRIu32 "\n", pSession->vlanName, minMtu);
			SetAdaptorMtu(pSession->vlanName, minMtu);
		}
		else
		{
			printf("Setting %s MTU = %" PRIu32 "\n", s_InterfaceName, minMtu);
			SetAdaptorMtu(s_InterfaceName, minMtu);
		}
	}

	if (pSession->iPv4ConfigurationAvailable & MBIM_IPV4_CONFIGURATION_AVAILABLE_ADDRESS)
	{
		// Note: MBIM can return multiple IP addresses. 
		// For the purposes of this program, we'll only use the first.
		uint32_t i;
		for (i = 0; i < MIN(pSession->iPv4AddressCount, 1); i++)
		{
			if (pSession->useVlan)
			{
				SetAdapterIPv4Address(true, pSession->vlanName, &pSession->iPv4Addresses[i]);
			}
			else
			{
				SetAdapterIPv4Address(true, s_InterfaceName, &pSession->iPv4Addresses[i]);
			}
			updatingIPv4 = true;
		} 
	}	

	if (pSession->iPv6ConfigurationAvailable & MBIM_IPV6_CONFIGURATION_AVAILABLE_ADDRESS)
	{
		// Note: MBIM can return multiple IP addresses. 
		// For the purposes of this program, we'll only use the first.
		uint32_t i;
		for (i = 0; i < MIN(pSession->iPv6AddressCount, 1); i++)
		{
			if (pSession->useVlan)
			{
				SetAdapterIPv6Address(true, pSession->vlanName, &pSession->iPv6Addresses[i]);
			}
			else
			{
				SetAdapterIPv6Address(true, s_InterfaceName, &pSession->iPv6Addresses[i]);
			}
			updatingIPv6 = true;
		} 
	}	

	// After setting the ip address, network adapter needs some time to become ready.
	int timeout = 0;
	if (updatingIPv4 || updatingIPv6)
	{
		UpAdaptorInterface(s_InterfaceName);

		while (!IsAdaptorUp(s_InterfaceName) && timeout++ < 6)
		{
			sleep(1);
		}

		if (pSession->useVlan)
		{
			UpAdaptorInterface(pSession->vlanName);

			while (!IsAdaptorUp(pSession->vlanName) && timeout++ < 6)
			{
				sleep(1);
			}
		}
	}

	// Now set up routes.

	if (updatingIPv4)
	{
		uint32_t i;
		for (i = 0; i < pSession->iPv4RouteCount; i++)
		{
			//char szGateway[INET_ADDRSTRLEN] = {'\0'};
			//inet_ntop(AF_INET, pSession->iPv4Gateway.value, szGateway, INET_ADDRSTRLEN);
			char* szGateway = "0.0.0.0";
			if (pSession->useVlan)
			{
				ModifyIPv4RouteEntry(&pSession->iPv4Routes[i], pSession->vlanName, NULL, NULL, szGateway);
			}
			else
			{
				ModifyIPv4RouteEntry(&pSession->iPv4Routes[i], s_InterfaceName, NULL, NULL, szGateway);
			}
			SetRoute(AF_INET, pSession->iPv4Routes[i].szInterface, true, pSession->iPv4Routes[i].szDst, pSession->iPv4Routes[i].dstPrefixLength, pSession->iPv4Routes[i].szGateway);
		}
	}

	if (updatingIPv6)
	{
		uint32_t i;
		for (i = 0; i < pSession->iPv6RouteCount; i++)
		{
			char szGateway[INET6_ADDRSTRLEN] = {'\0'};
			inet_ntop(AF_INET6, pSession->iPv6Gateway.value, szGateway, INET6_ADDRSTRLEN);
			if (pSession->useVlan)
			{
				ModifyIPv6RouteEntry(&pSession->iPv6Routes[i], pSession->vlanName, NULL, NULL, szGateway);
			}
			else
			{
				ModifyIPv6RouteEntry(&pSession->iPv6Routes[i], s_InterfaceName, NULL, NULL, szGateway);
			}
			SetRoute(AF_INET6, pSession->iPv6Routes[i].szInterface, true, pSession->iPv6Routes[i].szDst, pSession->iPv6Routes[i].dstPrefixLength, pSession->iPv6Routes[i].szGateway);
		} 
	}
}

void ClearRuntimeSettings(Session* pSession)
{
	uint32_t i;

	if (pSession->iPv4ConfigurationAvailable & MBIM_IPV4_CONFIGURATION_AVAILABLE_ADDRESS)
	{
		for (i = 0; i < pSession->iPv4RouteCount; i++)
		{
			SetRoute(AF_INET, pSession->iPv4Routes[i].szInterface, false, pSession->iPv4Routes[i].szDst, pSession->iPv4Routes[i].dstPrefixLength, pSession->iPv4Routes[i].szGateway);
			ModifyIPv4RouteEntry(&pSession->iPv4Routes[i], "", NULL, NULL, "");  
		} 

		for (i = 0; i < MIN(pSession->iPv4AddressCount, 1); i++)
		{
			// Clear adapter address.
			if (pSession->useVlan)
			{
				SetAdapterIPv4Address(false, pSession->vlanName, &pSession->iPv4Addresses[i]);
			}
			else
			{
				SetAdapterIPv4Address(false, s_InterfaceName, &pSession->iPv4Addresses[i]);
			}
		}
	}

	if (pSession->iPv6ConfigurationAvailable & MBIM_IPV6_CONFIGURATION_AVAILABLE_ADDRESS)
	{
		for (i = 0; i < pSession->iPv6RouteCount; i++)
		{
			SetRoute(AF_INET6, pSession->iPv6Routes[i].szInterface, false, pSession->iPv6Routes[i].szDst, pSession->iPv6Routes[i].dstPrefixLength, pSession->iPv6Routes[i].szGateway);
			ModifyIPv6RouteEntry(&pSession->iPv6Routes[i], "", NULL, NULL, "");  
		} 

		for (i = 0; i < MIN(pSession->iPv6AddressCount, 1); i++)
		{
			// Clear adapter address.
			if (pSession->useVlan)
			{
				SetAdapterIPv6Address(false, pSession->vlanName, &pSession->iPv6Addresses[i]);
			}
			else
			{
				SetAdapterIPv6Address(false, s_InterfaceName, &pSession->iPv6Addresses[i]);
			}
		}
	}

	if (pSession->useVlan)
	{
		DownAdaptorInterface(pSession->vlanName);
	}
}

static int ParseSettingsFile(FILE* pFile)
{
	char line[512];
	int linenum=0;

	Session* pSession = NULL;	// Current session under construction.

	while(fgets(line, ARRAYSIZE(line), pFile) != NULL)
	{
		linenum++;
		if(line[0] == '#') continue;

		if ((strstr(line, "session ") == line))
		{
			if (pSession)
			{
				// Use this as an indicator that current session has been constructed and we're attempting a new one.
				pSession = NULL;
			}

			if (s_SessionCount < ARRAYSIZE(s_Sessions))
			{
				uint32_t sessionId = 0;
				char szUserName[32];
				char szPassword[32];
				char szAccessString[32];
				char szCompressionType[32];
				char szAuthProtocolType[32];
				char szIpType[32];
				char szUseVlan[32];
				char szVlanName[32];
				uint16_t vlanId = 0;

				char* pLine = line;
				char* token;
				char* delims = " ,";   
				int tokenIdx = 0;
				token = strsep(&pLine, delims);
				tokenIdx++;

				/* walk through other tokens */
				while( token != NULL ) {
					printf( " %s\n", token );
					
					token = strsep(&pLine, delims);
					switch (tokenIdx)
					{
						case 1:
							if (sscanf(token, "%"SCNu32"", &sessionId) != 1)
							{
								printf("Failed to parse line %d\n", linenum);
								return -1;
							}
							break;
						case 2:
							StrCpy(szUserName, token);
							break;
						case 3:
							StrCpy(szPassword, token);
							break;
						case 4:
							StrCpy(szAccessString, token);
							break;
						case 5:
							StrCpy(szCompressionType, token);
							break;
						case 6:
							StrCpy(szAuthProtocolType, token);
							break;
						case 7:
							StrCpy(szIpType, token);
							break;
						case 8:
							StrCpy(szUseVlan, token);
							break;
						case 9:
							StrCpy(szVlanName, token);
							break;
						case 10:
							if (sscanf(token, "%"SCNu16"", &vlanId) != 1)
							{
								printf("Failed to parse line %d\n", linenum);
								return -1;
							}
							break;
					}
					tokenIdx++;
				}

				// Allocate and initialize a session.
				pSession = CreateSession(
					sessionId,
					szUserName,
					szPassword,
					szAccessString,
					szCompressionType,
					szAuthProtocolType,
					szIpType,
					szUseVlan,
					szVlanName,
					vlanId
					);
				if (pSession)
				{
					// We've created a session. Add it to our array.
					// We'll add any routes and ping destinations that immediately follow this session declaration
					// and before next session declaration.
					s_Sessions[s_SessionCount] = pSession;
					s_SessionCount++;
				}	
				else
				{
					// Something was wrong.
					return -1;
				}
			}
			else
			{
				printf("Too many sessions have been declared. Ignoring this one.\n");
			}
		}
		else if ((strstr(line, "route ") == line))
		{
			if (pSession)
			{
				char szDst[64] = { 0 };
				uint16_t dstPrefixLength = 0;

				char* pLine = line;
				char* token;
				char* delims = " ,";   
				int tokenIdx = 0;
				token = strsep(&pLine, delims);
				tokenIdx++;

				/* walk through other tokens */
				while( token != NULL ) {
					printf( " %s\n", token );
					
					token = strsep(&pLine, delims);
					switch (tokenIdx)
					{
						case 1:
							StrCpy(szDst, token);
							break;
						case 2:
							if (sscanf(token, "%"SCNu16"", &dstPrefixLength) != 1)
							{
								printf("Failed to parse line %d\n", linenum);
								return -1;
							}
							break;
					}
					tokenIdx++;
				}

				if (AddRouteEntry(pSession, szDst, dstPrefixLength) == -1)
				{
					printf("Failed to parse route %s\n", szDst);
					return -1;	
				}
			}
			else
			{
				printf("Orphan route, not associated with any session, ignoring.\n");
			}
		}
		else if ((strstr(line, "pingDst ") == line))
		{
			if (pSession)
			{
				char szPingDst[64];
				if (sscanf(
					line, 
					"pingDst %64s", 
					szPingDst
					) != 1)
				{
					printf("Failed to parse line %d\n", linenum);
					return -1;	
				}

				if (AddPingDestination(pSession, szPingDst) == -1)
				{
					printf("Failed to parse ping destination %s\n", szPingDst);
					return -1;	
				}
			}
			else
			{
				printf("Orphan pingDst, not associated with any session, ignoring.\n");
			}
		}
	}	

	int mode = QMUX_INTERFACE_MBIM;
	bool bpcie = false;
	if (!GetDeviceInfo(s_DevicePath, sizeof(s_DevicePath), &mode, &bpcie, NULL, true, NULL, NULL, false))
	{
		printf("Unable to identify MBIM device %s\n", s_DevicePath);
		return -1;
	}

	if (!GetNetInterfaceName(s_DevicePath, s_InterfaceName, 256))
	{
		printf("Unable to detect network interface for %s\n", s_DevicePath);
		return -1;
	}

	if (strlen(s_DevicePath) == 0 || strlen(s_InterfaceName) == 0)
	{
		return -1;
	}

	return 0;
}

int main(int argc, char **argv)
{
	printf("\nlite-mbim-connection-manager v%s\n\n", VERSION);

	int ret = SUCCESS;
	uint32_t mbimRet = MBIM_STATUS_FAILURE;
	uint32_t sessionIdx = 0;
	int retries;

	for (sessionIdx = 0; sessionIdx < ARRAYSIZE(s_Sessions); sessionIdx++)
	{
		s_Sessions[sessionIdx] = NULL;
	}
	s_SessionCount = 0;

	// Set default.
	strcpy(s_SettingsPath, "settings.conf");
	strcpy(s_DevicePath, "");
	strcpy(s_InterfaceName, "");

	ParseCommandLine(argc, argv);

	// Open settings file.
	if (argc == 2 && (strcmp("-V", argv[1]) == 0 || strcmp("--version", argv[1]) == 0))
		return 0;

	FILE* pSettingsFile = fopen(s_SettingsPath, "r");
	if (!pSettingsFile)
	{
		printf("Failed to open %s\n", s_SettingsPath);
		ret = FAILURE;
		goto cleanup2;
	}

	if (ParseSettingsFile(pSettingsFile) == -1)
	{
		fclose(pSettingsFile);
		ret = FAILURE;
		goto cleanup2;
	}

	fclose(pSettingsFile);

	memset(&s_Transport, 0, sizeof(MbimTransport));
	s_Transport.initRetry = 5;
	s_Transport.timeOut = 5;

	ret = MbimTransport_Initialize(&s_Transport, s_DevicePath, 4096, false);
	printf("MbimTransport_Initialize %s\n", ret == SUCCESS ? "success" : "failure");
	if (ret != SUCCESS)
	{
		printf("MbimTransport_Initialize failed for %s\n", s_DevicePath);
		goto cleanup2;
	}

	retries = 20;
	do 
	{
		printf("--------------------------\n");
		printf("SubscriberReadyStatusQuery\n");
		printf("--------------------------\n");

		mbimRet = SubscriberReadyStatusQuery();
		printf("API: %s\n\n", ret == MBIM_STATUS_SUCCESS ? "success" : "failure");
		if (mbimRet != MBIM_STATUS_SUCCESS)
		{
			ret = FAILURE;
			goto cleanup1;
		}

		if (s_ReadyState == MBIMSubscriberReadyStateInitialized || s_ReadyState == MBIMSubscriberReadyStateDeviceLocked)
		{
			// OK to proceed to next step.
			break;
		}

		retries--;
		sleep(1);
	} while (retries > 0); 

	if (retries == 0)
	{
		printf("Problem with SIM.\n");
		ret = FAILURE;
		goto cleanup1;
	}

	printf("--------\n");
	printf("PinQuery\n");
	printf("--------\n");

	mbimRet = PinQuery();
	printf("API: %s\n\n", mbimRet == MBIM_STATUS_SUCCESS ? "success" : "failure");
	if (mbimRet != MBIM_STATUS_SUCCESS)
	{
		ret = FAILURE;
		goto cleanup1;
	}

	// Modem may require entry of several PINs. We don't need a Pin2 for basic connectivity so ignore.
	while (s_PinState == MBIMPinStateLocked && s_PinType != MBIMPinTypePin2 && s_PinType != MBIMPinTypePuk2)
	{
		wchar_t userInput[64];

		printf("Device is requesting PIN of type %s\n", MBIMPinTypeToString(s_PinType));
		printf(
			"\t(1) Enter PIN\n"
			"\t(2) Exit program\n");
		while (fgetws(userInput, ARRAYSIZE(userInput), stdin) == NULL);
		if (wcscmp(userInput, L"1\n")	== 0)
		{
			printf("Please enter %s: ", MBIMPinTypeToString(s_PinType));
			while (fgetws(userInput, ARRAYSIZE(userInput), stdin) == NULL);

			// Last char is \n. Strip it off.
			int len = wcslen(userInput);
			if (len > 0)
				userInput[len - 1] = L'\0';

			printf("--------\n");
			printf("PinSet\n");
			printf("--------\n");
			mbimRet = PinSet(s_PinType, MBIMPinOperationEnter, userInput, L"");
			printf("API: %s\n\n", mbimRet == MBIM_STATUS_SUCCESS ? "success" : "failure");
			// Regardless, go to start of loop.
		}
		else
		{
			goto cleanup1;
		}	
	}	// while

	printf("---------------\n");
	printf("RadioStateQuery\n");
	printf("---------------\n");
	mbimRet = RadioStateQuery();
	if (mbimRet != MBIM_STATUS_SUCCESS)
	{
		ret = FAILURE;
		goto cleanup1;
	}

	if (s_HwRadioState == MBIMRadioOff || s_SwRadioState == MBIMRadioOff)
	{
		// Turn on radio.
		printf("-------------\n");
		printf("RadioStateSet\n");
		printf("-------------\n");
		mbimRet = RadioStateSet(MBIMRadioOn);
		printf("API: %s\n\n", mbimRet == MBIM_STATUS_SUCCESS ? "success" : "failure");
		if (mbimRet != MBIM_STATUS_SUCCESS)
		{
			ret = FAILURE;
			goto cleanup1;
		}
	}

	retries = 20;
	do 
	{
		printf("------------------\n");
		printf("RegisterStateQuery\n");
		printf("------------------\n");

		mbimRet = RegisterStateQuery();
		printf("API: %s\n\n", mbimRet == MBIM_STATUS_SUCCESS ? "success" : "failure");
		if (mbimRet != MBIM_STATUS_SUCCESS)
		{
			goto cleanup1;
		}

		if (s_RegisterState == MBIMRegisterStateHome ||
		    s_RegisterState == MBIMRegisterStateRoaming ||
			s_RegisterState == MBIMRegisterStatePartner)
		{
			break;
		}

		retries--;
		sleep(1);
	} while (retries > 0); 

	if (retries == 0)
	{
		printf("Problem with registering on network.\n");
		goto cleanup1;
	}

	// For completeness, query packet service as well.
	printf("------------------\n");
	printf("PacketServiceQuery\n");
	printf("------------------\n");
	mbimRet = PacketServiceQuery();
	if (mbimRet != MBIM_STATUS_SUCCESS)
	{
		goto cleanup1;
	}

	// Create VLANs if needed.
	for (sessionIdx = 0; sessionIdx != s_SessionCount; sessionIdx++)
	{
		if (s_Sessions[sessionIdx]->useVlan)
		{
			printf("Adding vlan %s ID %" PRIu16 " to %s\n",
			s_Sessions[sessionIdx]->vlanName, 
			s_Sessions[sessionIdx]->vlanId, 
			s_InterfaceName);
			int ret = AddVlan(s_InterfaceName, s_Sessions[sessionIdx]->vlanName, s_Sessions[sessionIdx]->vlanId);
			if (ret < 0)
			{
				printf("AddVlan failed with ret %d, ignoring\n", ret);
			}
		}
	}

	for (sessionIdx = 0; sessionIdx != s_SessionCount; sessionIdx++)
	{
		// Establish data connection.
		printf("-------------------\n");
		printf("ConnectSet activate\n");
		printf("-------------------\n");
		mbimRet = ConnectSet(s_Sessions[sessionIdx], MBIMActivationCommandActivate);

		printf("API: %s\n\n", mbimRet == MBIM_STATUS_SUCCESS ? "success" : "failure");

		printf("--------------------\n");
		printf("IpConfigurationQuery\n");
		printf("--------------------\n");
		mbimRet = IpConfigurationQuery(s_Sessions[sessionIdx]);
		printf("API: %s\n\n", mbimRet == MBIM_STATUS_SUCCESS ? "success" : "failure");
	}

	// Find the max MTU across all sessions.
	uint32_t maxMTUAcrossAllSessions = FindMaxMtuAcrossAllSessions();
	// Set base device MTU accordingly. Otherwise we'll get a ERANGE error if we try to set
	// a vlan MTU greater than this.
	printf("Setting %s MTU = %" PRIu32 "\n", s_InterfaceName, maxMTUAcrossAllSessions);
	SetAdaptorMtu(s_InterfaceName, maxMTUAcrossAllSessions);

	// Let OS know about established IP addresses etc. for each session.
	for (sessionIdx = 0; sessionIdx != s_SessionCount; sessionIdx++)
	{
		UpdateRuntimeSettings(s_Sessions[sessionIdx]);
	}

	// All our sessions are now fully running.

	// Ping each of the preconfigured destinations (if any) to check data connectivity.
	for (sessionIdx = 0; sessionIdx != s_SessionCount; sessionIdx++)
	{
		// Ping tests.
		Session* pSession = s_Sessions[sessionIdx];
		uint32_t pingDstIdx;

		if (pSession->iPv4ConfigurationAvailable & MBIM_IPV4_CONFIGURATION_AVAILABLE_ADDRESS)
		{	
			// IPv4.

		 	for (pingDstIdx = 0; pingDstIdx < pSession->iPv4PingDestinationCount; pingDstIdx++)
			{ 
				char szGateway[INET_ADDRSTRLEN] = {'\0'};
				int ret = 0;
				char* szInterface =NULL;

				if (pSession->useVlan)
				{
					szInterface = pSession->vlanName;
				}
				else
				{
					szInterface = s_InterfaceName;
				}

				inet_ntop(AF_INET, pSession->iPv4Gateway.value, szGateway, INET_ADDRSTRLEN);
				printf(
					"ping (IPv4) dst=%s gateway=%s -I=%s \n ", 
					pSession->iPv4PingDestinations[pingDstIdx], 
					szGateway, 
					szInterface
					);

				ret = ping(4, pSession->iPv4PingDestinations[pingDstIdx], PING_COUNT, PING_DELAY);

				printf("%s\n\n", ret == SUCCESS ? "success" : "failure");
			}
		}

		if (pSession->iPv6ConfigurationAvailable & MBIM_IPV6_CONFIGURATION_AVAILABLE_ADDRESS)
		{	
			sleep(3);	// TODO: This is ugly but a delay is needed when we only have IPV6 or the intial ping
						//       recvfrom returns EAGIN continuously.

			// IPv6.
		 	for (pingDstIdx = 0; pingDstIdx < pSession->iPv6PingDestinationCount; pingDstIdx++)
			{ 
				char szGateway[INET6_ADDRSTRLEN] = {'\0'};
				int ret = 0;
				char* szInterface =NULL;

				if (pSession->useVlan)
				{
					szInterface = pSession->vlanName;
				}
				else
				{
					szInterface = s_InterfaceName;
				}

				inet_ntop(AF_INET6, pSession->iPv6Gateway.value, szGateway, INET6_ADDRSTRLEN);
				printf(
					"ping (IPv6) dst=%s gateway=%s -I=%s \n ", 
					pSession->iPv6PingDestinations[pingDstIdx], 
					szGateway, 
					szInterface
					);

				ret = ping(6, pSession->iPv6PingDestinations[pingDstIdx], PING_COUNT, PING_DELAY);

				printf("%s\n\n", ret == SUCCESS ? "success" : "failure");
			}
		}
	}	

	// Wait for user input.
	wchar_t userValue[32];
	printf("\n\nPress Enter to disconnect and terminate ....\n");
	while (fgetws(userValue, ARRAYSIZE(userValue), stdin) == NULL);

	for (sessionIdx = 0; sessionIdx != s_SessionCount; sessionIdx++)
	{
		// Stop data session.

		printf("---------------------\n");
		printf("ConnectSet deactivate\n");
		printf("---------------------\n");

		mbimRet = ConnectSet(s_Sessions[sessionIdx], MBIMActivationCommandDeactivate);

		printf("API: %s\n\n", mbimRet == MBIM_STATUS_SUCCESS ? "success" : "failure");
	}

	for (sessionIdx = 0; sessionIdx != s_SessionCount; sessionIdx++)
	{
		ClearRuntimeSettings(s_Sessions[sessionIdx]);
	}

	DownAdaptorInterface(s_InterfaceName);

	for (sessionIdx = 0; sessionIdx != s_SessionCount; sessionIdx++)
	{
		if (s_Sessions[sessionIdx]->useVlan)
		{
			printf("Removing vlan %s\n", s_Sessions[sessionIdx]->vlanName);
			ret = DeleteVlan(s_Sessions[sessionIdx]->vlanName);
			if (ret < 0)
			{
				printf("DeleteVlan failed with ret %d, ignoring\n", ret);
			}
		}
	}

cleanup1:

	MbimTransport_ShutDown(&s_Transport, false);

cleanup2:

	// Free the sessions.
	for (sessionIdx = 0; sessionIdx < s_SessionCount; sessionIdx++)
	{
		free(s_Sessions[sessionIdx]);
		s_Sessions[sessionIdx] = NULL;
	}

	s_SessionCount = 0;

	return ret;
}
