/*************
 *
 * Filename:    command_set.h
 *
 * Purpose:     Contains function for handling user input functionalities for WDS
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
#include "wds.h"

#include "socket_server.h"
#include "user_input.h"

/* User options enumeration for WDS */
enum eUserOptions {
	eEXIT = -1,
	eUNKNOWN = 0,
	eSET_KEEP_ALIVE_DATA_SESSION = 1,
	eSET_RESET_MODIFY_PROFILE_SEETING,
	eGET_APN_OP_RESERVED_PCO,
	eGET_APN_MSISDN_INFO,
	eSET_DELETE_ALL_PROFILES,
	eGET_EHRPD_FALLBACK_APN,
	eSET_EHRPD_FALLBACK_APN,
	eSET_MODEM_ASSISTED_KA_START,
	eSET_MODEM_ASSISTED_KA_STOP,
	eSET_EVENT_REGISTER,
	eSET_INDICATION_REGISTER,
	eGET_DEFAULT_PROFILE_ID,
	eSET_DEFAULT_PROFILE_ID,
	eGET_3GPP_CONFIG_ITEMS,
	eSET_3GPP_CONFIG_ITEMS,
	eSET_DOWNLINK_THROUGHPUT_REPORT_PERIOD,
	eGET_DOWNLINK_THROUGHPUT_REPORTING_STATUS,
	eGET_CURRENT_CHANNEL_RATE,
	eGET_DEFAULT_NSAAI,
	eSET_DEFAULT_NSAAI,
	eGET_PROFILE_SNSAAI,
	eSET_CONFIGURE_PROFILE_SNSAAI,
	eSET_DELETE_PROFILE,
	eSET_CLEAR_PROFILE_SNSAAI,
	eHELP,
};
	
typedef struct
{
	union
	{
		uint8_t enableKA;
		pack_wds_ResetAndModifyProfileSettings_t sResetAndModifyProfileSettings;
		char ApnName[255]; //GetApnOpReservedPcoList and GetApnMsisdnInfo
		pack_wds_DeleteAllProfiles_t sDeleteAllProfiles;
		uint8_t   ProfileId; //ResetAndModifyProfileSettings		
		struct ModemAssistedKaStart
		{
			uint32_t	Timer_value;
			uint32_t	Dest_ipv4_address;
			//uint8_t	Dest_ipv6_address[16];
			uint32_t	Source_ipv4_address;
			//uint8_t	Source_ipv6_address[16];
			uint16_t	Dest_port;
			uint16_t	Source_port;
			uint8_t		apn_name_len;
			char		ApnName[255];
			pack_wds_modem_assisted_ka_start_t modemAssistedKaStart;
		} sModemAssistedKaStart;

		pack_wds_modem_assisted_ka_stop_t sModemAssistedKaStop;
		
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
		} sWdsSetEventReport;

		struct IndicationRegister
		{
			uint8_t SupperesPktSrvcInd;
			uint8_t ReportLteAttachPdnListChange;
			uint8_t ReportProfileChangeEvents;
			uint8_t ReportRoamingApnList;
			uint8_t ReportApnParamChangeInfo;
			uint8_t ReportLteAttachParams;
			uint8_t ReportMsisdnInfoChange;
			uint8_t ReportBearerType;
			uint8_t ReportPdnThrottleInfo;
			uint8_t ApnNameLen;
			char	ApnName[255];
			pack_wds_indication_register_t   indicationRegister;
		} sIndicationRegister;

		pack_wds_GetDefaultProfileNum_t sGetDefaultProfileNum;		
		pack_wds_SetDefaultProfileNum_t sSetDefaultProfileNum;
		struct Set3GPPConfigItem
		{
			uint16_t ProfileList[1];
			uint8_t  DefaultPDNEnabled;
			uint8_t  Release3gpp;
			uint16_t LTEAttachProfileList[1];
			pack_wds_SLQSSet3GPPConfigItem_t set3GPPConfigItem;
		} sSet3GPPConfigItem;

		uint32_t Downlink_throughput_report_period;
		char default_nssai_str[255];
		pack_wds_swi_SetDefaultNssai_t SetDefaultNssai;
		char configure_nssai_str[255];
		uint8_t Profile_index;
		pack_wds_SLQSDeleteProfile_t sDeleteProfile;
	};
} socketWdsCommandParam;

// Can be taken as-is to other apps
void PrintPrompt(void);

// Can be taken as-is to other apps
void PrintWdsCmdListUsage();

// Specific to WDS type map
enum ARGUMENT_AVAIL GetTypeValue(const char* valueStr, uint8_t* pValue);

// Can be taken as-is to other apps, if needed
enum eUserOptions GetWdsCommand(const char* command);

// Specific to WDS.  Need to implement accordling to each app
enum eUserOptions GetWdsSocketCommand(const char* procname, socketWdsCommandParam* cmdParam);

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif // __COMMAND_SET_H__
