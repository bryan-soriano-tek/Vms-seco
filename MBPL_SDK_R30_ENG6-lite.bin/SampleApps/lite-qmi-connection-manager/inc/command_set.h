/*************
 *
 * Filename:    command_set.h
 *
 * Purpose:     Contains function for handling user input functionalities
 *
 * Copyright: © 2022 Sierra Wireless Inc., all rights reserved
 *
 **************/
#ifndef __COMMAND_SET_H__
#define __COMMAND_SET_H__

#ifdef __cplusplus
extern "C" {
#endif

#pragma once
#include "wds.h"
#include "qos.h"
#include "socket_server.h"
#include "user_input.h"
#include "wda_handler.h"

#define NUM_WDS_SVC	8

#define MAX_APN_SIZE            104
#define MAX_PROFILE_NAME_SIZE   17
#define MAX_USER_NAME_SIZE      129

#define PROFILE_TYPE_UMTS       0

#define IPv4_FAMILY_PREFERENCE   0x04
#define IPv6_FAMILY_PREFERENCE   0x06
#define IPv4v6_FAMILY_PREFERENCE 0x07

/* User options enumeration */
enum eUserOptions {
	eEXIT = -1,
	eUNKNOWN = 0,
	eSTART_LTE_DATA_SESSION = 1,
	eSTART_MPDN_DATASESSION,
	eSTOP_DATA_SESSION,
	eSTOP_DATA_SESSIONS,
	eDISPLAY_ALL_PROFILES,
	eDISPLAY_SINGLE_PROFILE,
	eCREATE_PROFILE,
	eMODIFY_PROFILE_SETTINGS,
	eDELETE_PROFILE,
	eSCAN_NETWORKS,
	eENABLE_QOS_EVENT,
	eDISABLE_QOS_EVENT,
	eREQUEST_QOSEX,
	eGET_QOSINFO,
	eSET_QOS_INDICATION_REGISTER,
	eREAD_QOS_DATA_STATISTIC,
	eREAD_QOS_EXTRA_APN_PARAMS,
	eGET_PKT_STATS,
	eGET_CURRENT_CHANNEL_RATE,
	eTOGGLE_PING,
	eTOGGLE_ROUTE_UPDATE,
	eGET_LOOPBACK,
	eSET_LOOPBACK,
	eENABLE_QMAP,
	eDISABLE_QMAP,
	eSET_WDS_EVENT_REPORT,
	eSET_KEEP_ALIVE_DATA_SESSION,
	eHELP,
};
	
struct netSelectionPref
{
	uint8_t netReg;
	unsigned int mcc;
	unsigned int mnc;
};

/* Profile Information structure */
struct profileInformation {
	unsigned int profileNumber;
	uint8_t profileType;
	uint8_t PDPType;
	uint32_t IPAddress;
	uint32_t primaryDNS;
	uint32_t secondaryDNS;
	uint8_t Authentication;
	char  profileName[MAX_PROFILE_NAME_SIZE];
	char  APNName[MAX_APN_SIZE];
	char  userName[MAX_USER_NAME_SIZE];
	char  password[MAX_FIELD_SIZE];
};

struct qosIndicationRegisterParams
{
	uint8_t Report_global_qos_flows;
	uint8_t Suppress_report_flow_control;
	uint8_t Suppress_network_status_ind;
};

struct dataSessionInfo
{
	struct netSelectionPref netSelPref;
	struct profileInformation profileInfo;
};

/* to be replaced with new APIs once available
struct pdpContextData
{
	swinas_key_profile_data keyPdpContext;
	swinas_ext_profile_data ExtPdpContext;
	bool bExtSet;
};
*/

struct WdsSetEventReport
{
	uint8_t         CurrChannelRateInd;
	wds_TrStatInd   TransferStatInd;
	uint8_t         DataBearerTechInd;
	uint8_t         DormancyStatusInd;
	uint8_t         MIPStatusInd;
	uint8_t         DataCallStatusChangeInd;
	uint8_t         CurrPrefDataSysInd;
	uint8_t         EVDOPageMonPerChangeInd;
	uint8_t			UlFlowControlInd;
	uint8_t         ReportAddPdnFiltersRemoval;
	uint8_t         DataBearerTechExtInd;
	uint8_t         DormancyResultIndicator;
	pack_wds_SLQSWdsSetEventReport_t wdsSetEventReport;
} ;

typedef struct
{
	union
	{
		struct dataSessionInfo sessionInfo;
		unsigned int sessionNumber;
		unsigned int profileNumber;
		unsigned int id;
		struct profileInformation profileInfo;
		WdaSetDataFormatParams dataFormatParams;
		pack_qos_SLQSRequestQosExReq_t requestQosExReq;
		struct qosIndicationRegisterParams qosIndicationRegisterParams;
		struct WdsSetEventReport sWdsSetEventReport;
		bool enableKA;
	};
} socketCommandParam;

void PrintPrompt(void);
int GetPDPType();
int GetAuthenticationValue();
int GetIPFamilyPreference();
int GetUserProfileId(int min, int max);
int GetProfileInfo(struct profileInformation* pProfileInfo);
int GetConnectionProfileInfo(struct profileInformation* pProfileInfo);
void GetUserNetworkSelectionPreference(struct netSelectionPref* pPref);
void ReleaseQosExReqResource(pack_qos_SLQSRequestQosExReq_t* pRequestQosExReq);

enum eUserOptions GetCMSocketCommand(const char* procname, socketCommandParam* cmdParam, bool bQoSSupport/* To be replaced with swiwds , bool bSwinasSupport*/);

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif // __COMMAND_SET_H__
