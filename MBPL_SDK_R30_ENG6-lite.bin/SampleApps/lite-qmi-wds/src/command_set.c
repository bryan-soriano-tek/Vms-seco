/**************
 *
 * Filename:    command_set.c
 *
 * Purpose:     Implements WDS specific command handling
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

static ARGUMENT_SET g_reg_keep_alive_data_session[] =
{
	{"e", "keep-alive-data-session", "0|1", NULL, eMANDATORY},
};

static ARGUMENT_SET g_set_reset_modify_profile_settings[] =
{
	{"i", "profile-id", "integer 1-24", NULL, eMANDATORY},
};

static ARGUMENT_SET g_get_apn_opreserved_pco[] =
{
	{"a", "apn", "APN Name", NULL, eMANDATORY},
};

static ARGUMENT_SET g_get_apn_msisdn_info[] =
{
	{"a", "apn", "APN Name", NULL, eMANDATORY},
};

static ARGUMENT_SET g_delete_all_profiles[] =
{
	{"p", "profile-type-mask", "1|2", NULL, eMANDATORY},
};

static ARGUMENT_SET g_set_ehrpd_fallback_apn[] =
{
	{"a", "apn", "APN Name", NULL, eMANDATORY},
};

static ARGUMENT_SET g_set_modem_assisted_ka_start[] =
{
	{"a", "apn", "APN Name", NULL, eOPTIONAL},
	{"k", "keep_alive_type", "0|1", NULL, eMANDATORY},
	{"b", "timer-value", "integer", NULL, eOPTIONAL},
	{"f", "dest-ipv4-address", "destination IPV4 string", NULL, eOPTIONAL},
	{"F", "source-ipv4-address", "source IPV4 string", NULL, eOPTIONAL},
	{"g", "dest-port", "destination port", NULL, eOPTIONAL},
	{"G", "source-port", "source port", NULL, eOPTIONAL},
};

static ARGUMENT_SET g_set_modem_assisted_ka_stop[] =
{
	{"K", "keep-alive-handle", "keep alive handle", NULL, eMANDATORY},
};

static ARGUMENT_SET g_register_event[] =
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

static ARGUMENT_SET g_register_indication[] =
{
	{"a", "apn", "string", NULL, eOPTIONAL},
	{"1", "ssi", "Service status indication (0|1)", NULL, eOPTIONAL},
	{"2", "lap", "LTE attach PDN list (0|1)", NULL, eOPTIONAL},
	{"3", "rpc", "Report Profile Changes (0|1)", NULL, eOPTIONAL},
	{"4", "aal", "Report APN List in Roaming (0|1)", NULL, eOPTIONAL},
	{"5", "aap", "Report APN parameter change information (0|1)", NULL, eOPTIONAL},
	{"6", "rla", "Report LTE attach parameters (0|1)", NULL, eOPTIONAL},
	{"7", "apnm", "APN for which the client is interested in receiving changes in MSISDN information", NULL, eOPTIONAL},
	{"8", "rbt", "Report bearer type information (0|1)", NULL, eOPTIONAL},
	{"9", "rtp", "Report Throttled PDN Information (0|1)", NULL, eOPTIONAL},
};

static ARGUMENT_SET g_get_default_prfile_id[] =
{
	{"t", "profile-family", "0: Embedded 1: Tethered", NULL, eMANDATORY},
};

static ARGUMENT_SET g_set_default_prfile_id[] =
{
	{"i", "profile-id", "integer", NULL, eMANDATORY},
	{"t", "profile-family", "0: Embedded 1: Tethered", NULL, eMANDATORY},
};

static ARGUMENT_SET g_set_3gpp_config_items[] =
{
	{"i", "profile-id", "integer", NULL, eOPTIONAL},
	{"n", "always-connect-def-pdn", "Always connect default PDN 0: disabled 1: enabled", NULL, eOPTIONAL},
	{"u", "3gpp-release", "0: Release99 1: Release5 2: Release6 3: Release7 4: Release8 5: Release9 6: Release10 7: Release11", NULL, eOPTIONAL},
	{"l", "lte-attach-profile", "1-24 possible values", NULL, eOPTIONAL},
};

static ARGUMENT_SET g_set_downlink_throughput_report_period[] =
{
	{"z", "dl_throughput_report_period", "integer", NULL, eMANDATORY},
};

static ARGUMENT_SET g_set_default_nssai[] =
{
	{"w", "default_nssai", "(SST=x,SD=x.x.x,MSSTP=x,MSST=x,MSD=x.x.x)(SST=x,SD=x.x.x,MSSTP=x,MSST=x,MSD=x.x.x)...", NULL, eMANDATORY},
};

static ARGUMENT_SET g_get_profile_snssai_index[] =
{
	{"j", "profile_index", "integer", NULL, eMANDATORY},
};

static ARGUMENT_SET g_configure_profile_snssai[] =
{
	{"Q", "configure_nssai", "PT=0,PI=1,APN=abc,SST=1,SD=1.2.255,MSSTP=1,MSST=1,MSD=1.255.10,SSC=1,PAT=1,AOPS=1", NULL, eMANDATORY},
};

static ARGUMENT_SET g_delete_profile[] =
{
	{"W", "profile_type", "integer (0: 3GPP, 1: 3GPP2, 2: EPC)", NULL, eMANDATORY},
	{"j", "profile_index", "integer", NULL, eMANDATORY},
};

static ARGUMENT_SET g_clear_profile_snssai_index[] =
{
	{"j", "profile_index", "integer", NULL, eMANDATORY},
};

static ARGUMENT_SET g_help_arg_set[] =
{
	{"c", "command", "Command information", NULL, eOPTIONAL}
};

// Each app has to define COMMAND_SET array
static COMMAND_SET g_cmdset[] =
{
	{
		"SetKeepAliveDataSession",
		"Set Keep Alive Data Session",
		sizeof(g_reg_keep_alive_data_session) / sizeof(ARGUMENT_SET),
		g_reg_keep_alive_data_session,
		eSET_KEEP_ALIVE_DATA_SESSION
	},
	{
		"ResetAndModifyProfileSettings",
		"Reset And Modify Profile Settings",
		sizeof(g_set_reset_modify_profile_settings) / sizeof(ARGUMENT_SET),
		g_set_reset_modify_profile_settings,
		eSET_RESET_MODIFY_PROFILE_SEETING
	},
	{
		"GetApnOpReservedPcoList",
		"Get APN Operator Reserved PCO List",
		sizeof(g_get_apn_opreserved_pco) / sizeof(ARGUMENT_SET),
		g_get_apn_opreserved_pco,
		eGET_APN_OP_RESERVED_PCO
	},
	{
		"GetApnMsisdnInfo",
		"Get APN MSISDN Information",
		sizeof(g_get_apn_msisdn_info) / sizeof(ARGUMENT_SET),
		g_get_apn_msisdn_info,
		eGET_APN_MSISDN_INFO
	},
	{
		"DeleteAllProfiles",
		"Delete All Profiles",
		sizeof(g_delete_all_profiles) / sizeof(ARGUMENT_SET),
		g_delete_all_profiles,
		eSET_DELETE_ALL_PROFILES
	},
	{
		"GetEhrpdFallbackApnList",
		"Get EHRPD Fallback APN List",
		0,
		NULL,
		eGET_EHRPD_FALLBACK_APN
	},
	{
		"SetEhrpdFallbackApnList",
		"Set EHRPD Fallback APN List",
		sizeof(g_set_ehrpd_fallback_apn) / sizeof(ARGUMENT_SET),
		g_set_ehrpd_fallback_apn,
		eSET_EHRPD_FALLBACK_APN
	},
	{
		"SetModemAssistedKaStart",
		"Set Modem Assisted Keep Alive Start",
		sizeof(g_set_modem_assisted_ka_start) / sizeof(ARGUMENT_SET),
		g_set_modem_assisted_ka_start,
		eSET_MODEM_ASSISTED_KA_START
	},
	{
		"SetModemAssistedKaStop",
		"Set Modem Assisted Keep Alive Stop",
		sizeof(g_set_modem_assisted_ka_stop) / sizeof(ARGUMENT_SET),
		g_set_modem_assisted_ka_stop,
		eSET_MODEM_ASSISTED_KA_STOP
	},
	{
		"RegisterWdsEventRegister",
		"Register WDS Event Register",
		sizeof(g_register_event) / sizeof(ARGUMENT_SET),
		g_register_event,
		eSET_EVENT_REGISTER
	},
	{
		"RegisterWdsIndicationRegister",
		"Register WDS Indication Register",
		sizeof(g_register_indication) / sizeof(ARGUMENT_SET),
		g_register_indication,
		eSET_INDICATION_REGISTER
	},
	{
		"GetDefaultProfileId",
		"Get Default Profile ID",
		sizeof(g_get_default_prfile_id) / sizeof(ARGUMENT_SET),
		g_get_default_prfile_id,
		eGET_DEFAULT_PROFILE_ID
	},
	{
		"SetDefaultProfileId",
		"Set Default Profile ID",
		sizeof(g_set_default_prfile_id) / sizeof(ARGUMENT_SET),
		g_set_default_prfile_id,
		eSET_DEFAULT_PROFILE_ID
	},
	{
		"Get3GPPConfigItems",
		"Get 3GPP Config Items",
		0,
		NULL,
		eGET_3GPP_CONFIG_ITEMS
	},
	{
		"Set3GPPConfigItems",
		"Set 3GPP Config Items",
		sizeof(g_set_3gpp_config_items) / sizeof(ARGUMENT_SET),
		g_set_3gpp_config_items,
		eSET_3GPP_CONFIG_ITEMS
	},
	{
		"SetDownlinkThroughputReportPeriod",
		"Set Downlink Throughput Report Period",
		sizeof(g_set_downlink_throughput_report_period) / sizeof(ARGUMENT_SET),
		g_set_downlink_throughput_report_period,
		eSET_DOWNLINK_THROUGHPUT_REPORT_PERIOD
	},
	{
		"QueryDownlinkThroughputReportingStatus",
		"Query Downlink Throughput Reporting Status",
		0,
		NULL,
		eGET_DOWNLINK_THROUGHPUT_REPORTING_STATUS
	},
	{
		"GetCurrentChannelRate",
		"Get Current Channel Rate",
		0,
		NULL,
		eGET_CURRENT_CHANNEL_RATE
	},
//#ifdef Firmware_support
	{
		"GetDefaultNssai",
		"Get the default Network Slice Selection Assistance Information (NSSAI)",
		0,
		NULL,
		eGET_DEFAULT_NSAAI
	},
	{
		"SetDefaultNssai",
		"Update the default Network Slice Selection Assistance Information (NSSAI)",
		sizeof(g_set_default_nssai) / sizeof(ARGUMENT_SET),
		g_set_default_nssai,
		eSET_DEFAULT_NSAAI
	},
	{
		"GetProfileSnssai",
		"Get the Single Network Slice Selection Assistance Information (S-NSSAI) for a profile",
		sizeof(g_get_profile_snssai_index) / sizeof(ARGUMENT_SET),
		g_get_profile_snssai_index,
		eGET_PROFILE_SNSAAI
	},
	{
		"ConfigureProfileSnssai",
		"Configure the Single Network Slice Selection Assistance Information (S-NSSAI) settings for a profile",
		sizeof(g_configure_profile_snssai) / sizeof(ARGUMENT_SET),
		g_configure_profile_snssai,
		eSET_CONFIGURE_PROFILE_SNSAAI
	},
	{
		"DeleteProfile",
		"Delete a configured profile",
		sizeof(g_delete_profile) / sizeof(ARGUMENT_SET),
		g_delete_profile,
		eSET_DELETE_PROFILE
	},	
	{
		"ClearProfileSnssai",
		"Clear the Single Network Slice Selection Assistance Information (S-NSSAI) settings for a profile",
		sizeof(g_clear_profile_snssai_index) / sizeof(ARGUMENT_SET),
		g_clear_profile_snssai_index,
		eSET_CLEAR_PROFILE_SNSAAI
	},
//#endif	
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

void PrintWdsCmdListUsage()
{
	PrintCmdListUsage(g_cmdset, sizeof(g_cmdset) / sizeof(COMMAND_SET) - 2); // "- 2" so not to print "exit" and "help"
}

enum eUserOptions GetWdsCommand(const char* command)
{
	int opt = atoi(command);
	return (opt >= eSET_KEEP_ALIVE_DATA_SESSION && opt <= eSET_CLEAR_PROFILE_SNSAAI) ? opt :
		Command2Option(g_cmdset, sizeof(g_cmdset) / sizeof(COMMAND_SET), command, eUNKNOWN);
}

// The format of this function for other apps should remain the same.
// The difference should be in each 'case' of command under 'switch'
enum eUserOptions GetWdsSocketCommand(const char* procname, socketWdsCommandParam* cmdParam)
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
	case eSET_KEEP_ALIVE_DATA_SESSION:
		if (GetArgumentByteValue(NULL, &g_reg_keep_alive_data_session[0], &cmdParam->enableKA) != eFound)
			cmd = eUNKNOWN;
		break;
	case eSET_RESET_MODIFY_PROFILE_SEETING:
	{
		memset(&cmdParam->sResetAndModifyProfileSettings, 0, sizeof(pack_wds_ResetAndModifyProfileSettings_t));
		if (GetArgumentByteValue(command, &g_set_reset_modify_profile_settings[0], &cmdParam->sResetAndModifyProfileSettings.ProfileId) != eFound)
			cmd = eUNKNOWN;
	}
	break;
	case eGET_APN_OP_RESERVED_PCO:
	{
		const char* pApnName = NULL;
		if (GetArgumentStrValue(NULL, &g_get_apn_opreserved_pco[0], &pApnName) != eFound)
			cmd = eUNKNOWN;
		else
		{
			strcpy_s(cmdParam->ApnName, 255, pApnName);
		}
	}
	break;
	case eGET_APN_MSISDN_INFO:
	{
		const char* pApnName = NULL;		
		if (GetArgumentStrValue(NULL, &g_get_apn_msisdn_info[0], &pApnName) != eFound)
			cmd = eUNKNOWN;
		else
		{
			strcpy_s(cmdParam->ApnName, 255, pApnName);
		}
	}
	break;
	case eSET_DELETE_ALL_PROFILES:
	{
		memset(&cmdParam->sDeleteAllProfiles, 0, sizeof(pack_wds_DeleteAllProfiles_t));
		if (GetArgumentInt64Value(NULL, &g_delete_all_profiles[0], &cmdParam->sDeleteAllProfiles.ProfileTypeMask) != eFound )
			cmd = eUNKNOWN;
	}
	break;
	case eGET_EHRPD_FALLBACK_APN:
	break;
	case eSET_EHRPD_FALLBACK_APN:
	{
		const char* pApnName = NULL;
		if (GetArgumentStrValue(NULL, &g_set_ehrpd_fallback_apn[0], &pApnName) != eFound)
			cmd = eUNKNOWN;
		else
		{
			strcpy_s(cmdParam->ApnName, 255, pApnName);
		}
	}
	break;
	case eSET_MODEM_ASSISTED_KA_START:
	{
		memset(&cmdParam->sModemAssistedKaStart.modemAssistedKaStart, 0, sizeof(pack_wds_modem_assisted_ka_start_t));
		const char* pApnName = NULL;
		while (true)
		{
			ret = GetArgumentStrValue(NULL, &g_set_modem_assisted_ka_start[0], &pApnName); 
			if ( ret == eValueNotFound)
			{
				cmd = eUNKNOWN;
				break;
			}
			else if ( ret != eFlagNotFound)
			{
				StrCpy(cmdParam->sModemAssistedKaStart.ApnName, pApnName);
				cmdParam->sModemAssistedKaStart.apn_name_len = strlen(cmdParam->sModemAssistedKaStart.ApnName);
				cmdParam->sModemAssistedKaStart.modemAssistedKaStart.apn_name_len = &cmdParam->sModemAssistedKaStart.apn_name_len;
				cmdParam->sModemAssistedKaStart.modemAssistedKaStart.pApn_Name = cmdParam->sModemAssistedKaStart.ApnName; 
			}

			if(	GetArgumentIntValue(NULL, &g_set_modem_assisted_ka_start[1], &cmdParam->sModemAssistedKaStart.modemAssistedKaStart.keep_alive_type) != eFound)
			{
				cmd = eUNKNOWN;
				break;
			}

			ret = GetArgumentIntValue(NULL, &g_set_modem_assisted_ka_start[2], &cmdParam->sModemAssistedKaStart.Timer_value); 
			if (ret == eValueNotFound)
			{
				cmd = eUNKNOWN;
				break;
			}
			else if ( ret != eFlagNotFound)
			{
				cmdParam->sModemAssistedKaStart.modemAssistedKaStart.pTimer_value = &cmdParam->sModemAssistedKaStart.Timer_value;
			}

			ret = GetArgumentIntValue(NULL, &g_set_modem_assisted_ka_start[3], &cmdParam->sModemAssistedKaStart.Dest_ipv4_address); 
			if (ret == eValueNotFound)
			{
				cmd = eUNKNOWN;
				break;
			}
			else if ( ret != eFlagNotFound)
			{
				cmdParam->sModemAssistedKaStart.modemAssistedKaStart.pDest_ipv4_address = &cmdParam->sModemAssistedKaStart.Dest_ipv4_address;
			}

			ret = GetArgumentIntValue(NULL, &g_set_modem_assisted_ka_start[4], &cmdParam->sModemAssistedKaStart.Source_ipv4_address); 
			if (ret == eValueNotFound)
			{
				cmd = eUNKNOWN;
				break;
			}
			else if ( ret != eFlagNotFound)
			{
				cmdParam->sModemAssistedKaStart.modemAssistedKaStart.pSource_ipv4_address = &cmdParam->sModemAssistedKaStart.Source_ipv4_address;
			}

			ret = GetArgumentInt16Value(NULL, &g_set_modem_assisted_ka_start[5], &cmdParam->sModemAssistedKaStart.Dest_port); 
			if (ret == eValueNotFound)
			{
				cmd = eUNKNOWN;
				break;
			}
			else if ( ret != eFlagNotFound)
			{
				cmdParam->sModemAssistedKaStart.modemAssistedKaStart.pDest_port = &cmdParam->sModemAssistedKaStart.Dest_port;
			}

			ret = GetArgumentInt16Value(NULL, &g_set_modem_assisted_ka_start[6], &cmdParam->sModemAssistedKaStart.Source_port); 
			if (ret == eValueNotFound)
			{
				cmd = eUNKNOWN;
				break;
			}
			else if ( ret != eFlagNotFound)
			{
				cmdParam->sModemAssistedKaStart.modemAssistedKaStart.pSource_port = &cmdParam->sModemAssistedKaStart.Source_port;
			}
			break;
		}
	}
	break;
	case eSET_MODEM_ASSISTED_KA_STOP:
		memset(&cmdParam->sModemAssistedKaStop, 0, sizeof(pack_wds_modem_assisted_ka_stop_t));
		if (GetArgumentIntValue(NULL, &g_set_modem_assisted_ka_stop[0], &cmdParam->sModemAssistedKaStop.keep_alive_handle) != eFound)
			cmd = eUNKNOWN;
	break;
	case eSET_EVENT_REGISTER:
		memset(&cmdParam->sWdsSetEventReport.wdsSetEventReport, 0, sizeof(pack_wds_SLQSWdsSetEventReport_t));
		while(true)
		{
			ret = GetArgumentByteValue(NULL, &g_register_event[0], &cmdParam->sWdsSetEventReport.CurrChannelRateInd); 
			if (ret == eValueNotFound)
			{
				cmd = eUNKNOWN;
				break;
			}
			else if (ret != eFlagNotFound)
			{
				cmdParam->sWdsSetEventReport.wdsSetEventReport.pCurrChannelRateInd = &cmdParam->sWdsSetEventReport.CurrChannelRateInd;
			}

			ret = GetArgumentByteValue(NULL, &g_register_event[1], &cmdParam->sWdsSetEventReport.TransferStatInd.statsPeriod);
			if (ret == eValueNotFound)
			{
				cmd = eUNKNOWN;
				break;
			}
			else if (ret != eFlagNotFound)
			{
				ret = GetArgumentIntValue(NULL, &g_register_event[2], &cmdParam->sWdsSetEventReport.TransferStatInd.statsMask);
				if (ret == eValueNotFound)
				{
					cmd = eUNKNOWN;
					break;
				}
				else if (ret != eFlagNotFound)
				{
					cmdParam->sWdsSetEventReport.wdsSetEventReport.pTransferStatInd = &cmdParam->sWdsSetEventReport.TransferStatInd;
				}
			}

			ret = GetArgumentByteValue(NULL, &g_register_event[3], &cmdParam->sWdsSetEventReport.DataBearerTechInd); 
			if (ret == eValueNotFound)
			{
				cmd = eUNKNOWN;
				break;
			}
			else if (ret != eFlagNotFound)
			{
				cmdParam->sWdsSetEventReport.wdsSetEventReport.pDataBearerTechInd = &cmdParam->sWdsSetEventReport.DataBearerTechInd;
			}

			ret = GetArgumentByteValue(NULL, &g_register_event[4], &cmdParam->sWdsSetEventReport.DormancyStatusInd); 
			if (ret == eValueNotFound)
			{
				cmd = eUNKNOWN;
				break;
			}
			else if (ret != eFlagNotFound)
			{
				cmdParam->sWdsSetEventReport.wdsSetEventReport.pDormancyStatusInd = &cmdParam->sWdsSetEventReport.DormancyStatusInd;
			}

			ret = GetArgumentByteValue(NULL, &g_register_event[5], &cmdParam->sWdsSetEventReport.MIPStatusInd); 
			if (ret == eValueNotFound)
			{
				cmd = eUNKNOWN;
				break;
			}
			else if (ret != eFlagNotFound)
			{
				cmdParam->sWdsSetEventReport.wdsSetEventReport.pMIPStatusInd = &cmdParam->sWdsSetEventReport.MIPStatusInd;
			}

			ret = GetArgumentByteValue(NULL, &g_register_event[6], &cmdParam->sWdsSetEventReport.DataCallStatusChangeInd); 
			if (ret == eValueNotFound)
			{
				cmd = eUNKNOWN;
				break;
			}
			else if (ret != eFlagNotFound)
			{
				cmdParam->sWdsSetEventReport.wdsSetEventReport.pDataCallStatusChangeInd = &cmdParam->sWdsSetEventReport.DataCallStatusChangeInd;
			}

			ret = GetArgumentByteValue(NULL, &g_register_event[7], &cmdParam->sWdsSetEventReport.CurrPrefDataSysInd); 
			if (ret == eValueNotFound)
			{
				cmd = eUNKNOWN;
				break;
			}
			else if (ret != eFlagNotFound)
			{
				cmdParam->sWdsSetEventReport.wdsSetEventReport.pCurrPrefDataSysInd = &cmdParam->sWdsSetEventReport.CurrPrefDataSysInd;
			}
			if (GetArgumentByteValue(NULL, &g_register_event[8], &cmdParam->sWdsSetEventReport.EVDOPageMonPerChangeInd) == eValueNotFound)
			{
				cmd = eUNKNOWN;
				break;
			}
			else if (ret != eFlagNotFound)
			{
				cmdParam->sWdsSetEventReport.wdsSetEventReport.pEVDOPageMonPerChangeInd = &cmdParam->sWdsSetEventReport.EVDOPageMonPerChangeInd;
			}

			ret = GetArgumentByteValue(NULL, &g_register_event[9], &cmdParam->sWdsSetEventReport.UlFlowControlInd); 
			if (ret == eValueNotFound)
			{
				cmd = eUNKNOWN;
				break;
			}
			else if (ret != eFlagNotFound)
			{
				cmdParam->sWdsSetEventReport.wdsSetEventReport.pUlFlowControlInd = &cmdParam->sWdsSetEventReport.UlFlowControlInd;
			}
			
			ret = GetArgumentByteValue(NULL, &g_register_event[10], &cmdParam->sWdsSetEventReport.ReportAddPdnFiltersRemoval); 
			if (ret == eValueNotFound)
			{
				cmd = eUNKNOWN;
				break;
			}
			else if (ret != eFlagNotFound)
			{
				cmdParam->sWdsSetEventReport.wdsSetEventReport.pReportAddPdnFiltersRemoval = &cmdParam->sWdsSetEventReport.ReportAddPdnFiltersRemoval;
			}
			
			ret = GetArgumentByteValue(NULL, &g_register_event[11], &cmdParam->sWdsSetEventReport.DataBearerTechExtInd); 
			if (ret == eValueNotFound)
			{
				cmd = eUNKNOWN;
				break;
			}
			else if (ret != eFlagNotFound)
			{
				cmdParam->sWdsSetEventReport.wdsSetEventReport.pDataBearerTechExtInd = &cmdParam->sWdsSetEventReport.DataBearerTechExtInd;
			}
			
			ret = GetArgumentByteValue(NULL, &g_register_event[12], &cmdParam->sWdsSetEventReport.DormancyResultIndicator); 
			if (ret == eValueNotFound)
			{
				cmd = eUNKNOWN;
				break;
			}
			else if (ret != eFlagNotFound)
			{
				cmdParam->sWdsSetEventReport.wdsSetEventReport.pDormancyResultIndicator = &cmdParam->sWdsSetEventReport.DormancyResultIndicator;
			}
			break;
		}
	break;
	case eSET_INDICATION_REGISTER:
		memset(&cmdParam->sIndicationRegister.indicationRegister, 0, sizeof(pack_wds_indication_register_t));
		while(true)
		{
			ret = GetArgumentByteValue(NULL, &g_register_indication[0], &cmdParam->sIndicationRegister.SupperesPktSrvcInd); 
			if (ret == eValueNotFound)
			{
				cmd = eUNKNOWN;
				break;
			}
			else if (ret != eFlagNotFound)
			{
				cmdParam->sIndicationRegister.indicationRegister.pSupperesPktSrvcInd = &cmdParam->sIndicationRegister.SupperesPktSrvcInd;
			}

			ret = GetArgumentByteValue(NULL, &g_register_indication[1], &cmdParam->sIndicationRegister.ReportLteAttachPdnListChange); 
			if (ret == eValueNotFound)
			{
				cmd = eUNKNOWN;
				break;
			}
			else if (ret != eFlagNotFound)
			{
				cmdParam->sIndicationRegister.indicationRegister.pReportLteAttachPdnListChange = &cmdParam->sIndicationRegister.ReportLteAttachPdnListChange;
			}

			ret = GetArgumentByteValue(NULL, &g_register_indication[2], &cmdParam->sIndicationRegister.ReportProfileChangeEvents); 
			if (ret == eValueNotFound)
			{
				cmd = eUNKNOWN;
				break;
			}
			else if (ret != eFlagNotFound)
			{
				cmdParam->sIndicationRegister.indicationRegister.pReportProfileChangeEvents = &cmdParam->sIndicationRegister.ReportProfileChangeEvents;
			}

			ret = GetArgumentByteValue(NULL, &g_register_indication[3], &cmdParam->sIndicationRegister.ReportRoamingApnList);
			if (ret == eValueNotFound)
			{
				cmd = eUNKNOWN;
				break;
			}
			else if (ret != eFlagNotFound)
			{
				cmdParam->sIndicationRegister.indicationRegister.pReportRoamingApnList = &cmdParam->sIndicationRegister.ReportRoamingApnList;
			}
			
			ret = GetArgumentByteValue(NULL, &g_register_indication[4], &cmdParam->sIndicationRegister.ReportApnParamChangeInfo);
			if (ret == eValueNotFound)
			{
				cmd = eUNKNOWN;
				break;
			}
			else if (ret != eFlagNotFound)
			{
				cmdParam->sIndicationRegister.indicationRegister.pReportApnParamChangeInfo = &cmdParam->sIndicationRegister.ReportApnParamChangeInfo;
			}

			ret = GetArgumentByteValue(NULL, &g_register_indication[5], &cmdParam->sIndicationRegister.ReportLteAttachParams);
			if (ret == eValueNotFound)
			{
				cmd = eUNKNOWN;
				break;
			}
			else if (ret != eFlagNotFound)
			{
				cmdParam->sIndicationRegister.indicationRegister.pReportLteAttachParams = &cmdParam->sIndicationRegister.ReportLteAttachParams;
			}
			
			ret = GetArgumentByteValue(NULL, &g_register_indication[6], &cmdParam->sIndicationRegister.ReportMsisdnInfoChange); 
			if (ret == eValueNotFound)
			{
				cmd = eUNKNOWN;
				break;
			}
			else if (ret != eFlagNotFound)
			{
				cmdParam->sIndicationRegister.indicationRegister.pReportMsisdnInfoChange = &cmdParam->sIndicationRegister.ReportMsisdnInfoChange;
			}
			
			ret = GetArgumentByteValue(NULL, &g_register_indication[7], &cmdParam->sIndicationRegister.ReportBearerType);
			if (ret == eValueNotFound)
			{
				cmd = eUNKNOWN;
				break;
			}
			else if (ret != eFlagNotFound)
			{
				cmdParam->sIndicationRegister.indicationRegister.pReportBearerType = &cmdParam->sIndicationRegister.ReportBearerType;
			}
			
			ret = GetArgumentByteValue(NULL, &g_register_indication[8], &cmdParam->sIndicationRegister.ReportPdnThrottleInfo);
			if (ret == eValueNotFound)
			{
				cmd = eUNKNOWN;
				break;
			}
			else if (ret != eFlagNotFound)
			{
				cmdParam->sIndicationRegister.indicationRegister.pReportPdnThrottleInfo = &cmdParam->sIndicationRegister.ReportPdnThrottleInfo;
			}
			const char* pApnName = NULL;
			
			ret = GetArgumentStrValue(NULL, &g_register_indication[9], &pApnName);
			if (ret == eValueNotFound)
			{
				cmd = eUNKNOWN;
				break;
			}
			else if (ret != eFlagNotFound)
			{
				StrCpy(cmdParam->sIndicationRegister.ApnName, pApnName);
				cmdParam->sIndicationRegister.ApnNameLen = strlen(cmdParam->sIndicationRegister.ApnName);
				cmdParam->sIndicationRegister.indicationRegister.pApnNameLen = &cmdParam->sIndicationRegister.ApnNameLen;
				cmdParam->sIndicationRegister.indicationRegister.pApnName = cmdParam->sIndicationRegister.ApnName; 
			}
			break;
		}
	break;
	case eGET_DEFAULT_PROFILE_ID:
		memset(&cmdParam->sGetDefaultProfileNum, 0, sizeof(pack_wds_GetDefaultProfileNum_t));
		if (GetArgumentByteValue(NULL, &g_get_default_prfile_id[0], &cmdParam->sGetDefaultProfileNum.family) != eFound)
			cmd = eUNKNOWN;
	break;
	case eSET_DEFAULT_PROFILE_ID:
		memset(&cmdParam->sSetDefaultProfileNum, 0, sizeof(pack_wds_SetDefaultProfileNum_t));
		if (GetArgumentByteValue(NULL, &g_set_default_prfile_id[0], &cmdParam->sSetDefaultProfileNum.index) != eFound ||
			GetArgumentByteValue(NULL, &g_set_default_prfile_id[1], &cmdParam->sSetDefaultProfileNum.family) != eFound)
			cmd = eUNKNOWN;
	break;
	case eGET_3GPP_CONFIG_ITEMS:
	break; 
	case eSET_3GPP_CONFIG_ITEMS:
		memset(&cmdParam->sSet3GPPConfigItem.set3GPPConfigItem, 0, sizeof(pack_wds_SLQSSet3GPPConfigItem_t));		
		while (true)
		{
			ret = GetArgumentInt16Value(NULL, &g_set_3gpp_config_items[0], &cmdParam->sSet3GPPConfigItem.ProfileList[0]);
			if (ret == eValueNotFound)
			{
				cmd = eUNKNOWN;
				break;
			}
			else if (ret != eFlagNotFound)
			{
				cmdParam->sSet3GPPConfigItem.set3GPPConfigItem.pProfileList = cmdParam->sSet3GPPConfigItem.ProfileList;
			}
			
			ret = GetArgumentByteValue(NULL, &g_set_3gpp_config_items[1], &cmdParam->sSet3GPPConfigItem.DefaultPDNEnabled);
			if (ret == eValueNotFound)
			{
				cmd = eUNKNOWN;
				break;
			}
			else if (ret != eFlagNotFound)
			{
				cmdParam->sSet3GPPConfigItem.set3GPPConfigItem.pDefaultPDNEnabled = &cmdParam->sSet3GPPConfigItem.DefaultPDNEnabled;
			}
			
			ret = GetArgumentByteValue(NULL, &g_set_3gpp_config_items[2], &cmdParam->sSet3GPPConfigItem.Release3gpp);
			if (ret == eValueNotFound)
			{
				cmd = eUNKNOWN;
				break;
			}
			else if (ret != eFlagNotFound)
			{
				cmdParam->sSet3GPPConfigItem.set3GPPConfigItem.p3gppRelease = &cmdParam->sSet3GPPConfigItem.Release3gpp;
			}
			
			ret = GetArgumentInt16Value(NULL, &g_set_3gpp_config_items[3], &cmdParam->sSet3GPPConfigItem.LTEAttachProfileList[0]); 
			if (ret == eValueNotFound)
			{
				cmd = eUNKNOWN;
				break;
			}
			else if (ret != eFlagNotFound)
			{
				cmdParam->sSet3GPPConfigItem.set3GPPConfigItem.pLTEAttachProfileList = cmdParam->sSet3GPPConfigItem.LTEAttachProfileList;
			}
			cmdParam->sSet3GPPConfigItem.set3GPPConfigItem.LTEAttachProfileListLen = 1;
			break;
		}		
	break; 
	case eSET_DOWNLINK_THROUGHPUT_REPORT_PERIOD:
		if (GetArgumentIntValue(NULL, &g_set_downlink_throughput_report_period[0], &cmdParam->Downlink_throughput_report_period) != eFound)
			cmd = eUNKNOWN;
	break;
	case eGET_DOWNLINK_THROUGHPUT_REPORTING_STATUS:
	case eGET_CURRENT_CHANNEL_RATE:
	case eGET_DEFAULT_NSAAI:
	break;
	case eSET_DEFAULT_NSAAI:
	{
		const char* pDefaultNssai = NULL;
		if (GetArgumentStrValue(NULL, &g_set_default_nssai[0], &pDefaultNssai) != eFound)
			cmd = eUNKNOWN;
		else
		{
			strcpy_s(cmdParam->default_nssai_str, 255, pDefaultNssai);
		}
	}
	break;
	case eGET_PROFILE_SNSAAI:
		if (GetArgumentByteValue(NULL, &g_get_profile_snssai_index[0], &cmdParam->Profile_index) != eFound)
			cmd = eUNKNOWN;
	break;
	case eSET_CONFIGURE_PROFILE_SNSAAI:
	{
		const char* pProfileNssai = NULL;
		if (GetArgumentStrValue(NULL, &g_configure_profile_snssai[0], &pProfileNssai) != eFound)
			cmd = eUNKNOWN;
		else
		{
			strcpy_s(cmdParam->configure_nssai_str, 255, pProfileNssai);
		}
	}
	break;
	case eSET_DELETE_PROFILE:
	{
		if (GetArgumentByteValue(NULL, &g_delete_profile[0], &cmdParam->sDeleteProfile.profileType) != eFound ||
		    GetArgumentByteValue(NULL, &g_delete_profile[1], &cmdParam->sDeleteProfile.profileIndex) != eFound)
			cmd = eUNKNOWN;
	}
	break;
	case eSET_CLEAR_PROFILE_SNSAAI:
		if (GetArgumentByteValue(NULL, &g_clear_profile_snssai_index[0], &cmdParam->Profile_index) != eFound)
			cmd = eUNKNOWN;
	break;
	case eUNKNOWN:
		SockLog(eLOG_INFO, "Error: invalid command\n");
	default:
		break;
	}

    UnlockSocket();

	return cmd;
}
