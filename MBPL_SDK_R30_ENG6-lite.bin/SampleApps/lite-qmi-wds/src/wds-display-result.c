#include <stdio.h>
#include <inttypes.h>
#include "lite-qmi-wds.h"
#include "wds.h"
#include "command_set.h"

void DisplayGetApnMsisdnInfo(unpack_wds_ApnMsisdnInfo_t *pApnMsisdnInfo)
{
	SockPrintf("\n  APN Msisdn Info List:\n");
	SockPrintf("\n  Number Number of MSISDN: %d", pApnMsisdnInfo->num_msisdn);

	for (int idx = 0; idx < pApnMsisdnInfo->num_msisdn; ++idx)
	{
		SockPrintf("  Msisdn[%d]: %d\n", idx, *pApnMsisdnInfo->pMsisdn);
		++pApnMsisdnInfo->pMsisdn;
	}	
}

void DisplayApnOpReservedPcoList(unpack_wds_ApnOpReservedPcoList_t *pApnOpReservedPcoList)
{
	SockPrintf("\n  APN Op Reserved Pco List:\n");
	SockPrintf("\n  Number of APN Op Reserved Pco List: %d", pApnOpReservedPcoList->numInstances);
	WdsApnOpReservedPco_t *pWdspApnOpReservedPcoList = pApnOpReservedPcoList->pWdsApnOpReservedPcoList;
	for (int idx = 0; idx < pApnOpReservedPcoList->numInstances; ++idx)
	{
		SockPrintf("\n  PcoId[%d]: %d\n", idx, pWdspApnOpReservedPcoList->PcoId);
		SockPrintf("  MCC[%d]: %d\n", idx, pWdspApnOpReservedPcoList->Mcc);
		SockPrintf("  MNC[%d]: %d\n", idx, pWdspApnOpReservedPcoList->Mnc);
		SockPrintf("  MncIncludesPcsDigit[%d]: %d\n", idx, pWdspApnOpReservedPcoList->MncIncludesPcsDigit);
		
		SockPrintf("  AppSpecificInfoLength[%d]: %d\n", idx, pWdspApnOpReservedPcoList->AppSpecificInfoLength);
		for(int idy = 0; idy < pWdspApnOpReservedPcoList->AppSpecificInfoLength; ++idy)
			SockPrintf("  pWdspApnOpReservedPcoList[%d].AppSpecificInfoLength[%d]: %d\n", idx, idy, pWdspApnOpReservedPcoList->AppSpecificInfo[idy]);

		SockPrintf("\n  ContainerId[%d]: %d\n", idx, pWdspApnOpReservedPcoList->ContainerId); 
	}	
}

void DisplayLteAttachParamsIndication(unpack_wds_SLQSLteAttachParams_ind_t *pLteAttachParams_ind)
{
	SockPrintf("\n  Lte Attach Params Indication:\n");
	SockPrintf("  pLteAttachParams_ind->AttachParamValidTlv: %d\n", pLteAttachParams_ind->AttachParamValidTlv); 

	if (pLteAttachParams_ind->AttachParamValidTlv)
	{
		if (swi_uint256_get_bit (pLteAttachParams_ind->ParamPresenceMask, 0x10))
			SockPrintf("\n  Apn Name: %s", pLteAttachParams_ind->pApnString);

		if (swi_uint256_get_bit (pLteAttachParams_ind->ParamPresenceMask, 0x11))
			SockPrintf("    Ip Type: %d", *pLteAttachParams_ind->pIp_Type);
		
		if (swi_uint256_get_bit (pLteAttachParams_ind->ParamPresenceMask, 0x12))
			SockPrintf("    IPv4 Address: %d", *pLteAttachParams_ind->pIPv4Address);
		
		if (swi_uint256_get_bit (pLteAttachParams_ind->ParamPresenceMask, 0x13))
			SockPrintf("    IPv4 Gateway Address: %d", *pLteAttachParams_ind->pIPv4GatewayAddress);
		
		if (swi_uint256_get_bit (pLteAttachParams_ind->ParamPresenceMask, 0x14))
			SockPrintf("    IPv4 Subnet Mask: %d", *pLteAttachParams_ind->pIPv4SubnetMask);
		
		if (swi_uint256_get_bit (pLteAttachParams_ind->ParamPresenceMask, 0x15))
		{
			SockPrintf("    Ipv6 Address Length: %d", pLteAttachParams_ind->pIpv6Address->Ipv6_prefix_length);
			for (int idx = 0; idx < pLteAttachParams_ind->pIpv6Address->Ipv6_prefix_length; ++idx)
				SockPrintf("    Ipv6 Address [%d]: %d", idx, pLteAttachParams_ind->pIpv6Address->Ipv6_address[idx]);
		}		
		if (swi_uint256_get_bit (pLteAttachParams_ind->ParamPresenceMask, 0x16))
		{
			SockPrintf("    Ipv6 Gateway Address Length: %d", pLteAttachParams_ind->pIpv6GatewayAddress->Ipv6_prefix_length);
			for (int idx = 0; idx < pLteAttachParams_ind->pIpv6GatewayAddress->Ipv6_prefix_length; ++idx)
				SockPrintf("    Ipv6 Gateway Address[%d]: %d", idx, pLteAttachParams_ind->pIpv6GatewayAddress->Ipv6_address[idx]);
		}
	}
}

void DisplayApnOpReservedPcoListChangeIndication(unpack_wds_SLQSApnOpReservedPcoListChange_ind_t *pApnOpReservedPcoListChange_ind)
{
	uint8_t      *pAppSpecificInfo;
	SockPrintf("\n  APN Operator Reserved PCO List Change Indication\n");
	SockPrintf("    Apn Name: %s", pApnOpReservedPcoListChange_ind->apn_name);

	SockPrintf("  PCO Count:  %d", pApnOpReservedPcoListChange_ind->PcoInfoLength);

	for (int idx = 0; idx < pApnOpReservedPcoListChange_ind->PcoInfoLength; ++idx)
	{
		SockPrintf("  PCO ID:  %d", pApnOpReservedPcoListChange_ind->pWdsApnOpReservedPcoList->PcoId);
		SockPrintf("  MCC:  %d", pApnOpReservedPcoListChange_ind->pWdsApnOpReservedPcoList->Mcc);
		SockPrintf("  MNC:  %d", pApnOpReservedPcoListChange_ind->pWdsApnOpReservedPcoList->Mnc);
		SockPrintf("  MNC Includes PCS Digit:  %d", pApnOpReservedPcoListChange_ind->pWdsApnOpReservedPcoList->MncIncludesPcsDigit);
		SockPrintf("  APP Specific Info Length:  %d", pApnOpReservedPcoListChange_ind->pWdsApnOpReservedPcoList->AppSpecificInfoLength);
		SockPrintf("  App Specific Info:");
		pAppSpecificInfo = pApnOpReservedPcoListChange_ind->pWdsApnOpReservedPcoList->AppSpecificInfo;
		for (int idy = 0; idy < pApnOpReservedPcoListChange_ind->pWdsApnOpReservedPcoList->AppSpecificInfoLength; ++idy)
		{
			SockPrintf("%d", *pAppSpecificInfo);
			++pAppSpecificInfo;
		}
		SockPrintf("  Container ID:  %d", pApnOpReservedPcoListChange_ind->pWdsApnOpReservedPcoList->ContainerId);
	}
}

void DisplayApnMsisdnInfoChangeIndication(unpack_wds_SLQSApnMsisdnInfoChange_ind_t *pApnMsisdnInfoChange_ind)
{
	SockPrintf("\n  APN MSISDN Info Change Indicationn");
	SockPrintf("    Apn Name: %s\n", pApnMsisdnInfoChange_ind->apn_name);
	SockPrintf("    MSISDN Count: %d\n", pApnMsisdnInfoChange_ind->msisdn_len);
	for (int idx = 0; idx < pApnMsisdnInfoChange_ind->msisdn_len; ++idx)
	{
		SockPrintf("  MSISDN:  %d\n", *pApnMsisdnInfoChange_ind->pMsisdn);
	}	
}

void DisplayPdnThrottleInfoIndication(unpack_wds_SLQSPdnThrottleInfo_ind_t *pPdnThrottleInfo_ind)
{
	SockPrintf("\n  PDN Throttle Info Indication\n");

	if (swi_uint256_get_bit (pPdnThrottleInfo_ind->ParamPresenceMask, 0x10))
	{
		SockPrintf("  Throttle Info Count:  %d\n", pPdnThrottleInfo_ind->throttle_info_len);	
		for (int idx = 0; idx < pPdnThrottleInfo_ind->throttle_info_len; ++idx)
		{
			SockPrintf("  Is IPv4 Throttled:  %d\n", pPdnThrottleInfo_ind->pPDNThrottleInformation->is_ipv4_throttled);
			SockPrintf("  Is IPv6 Throttled:  %d\n", pPdnThrottleInfo_ind->pPDNThrottleInformation->is_ipv6_throttled);
			SockPrintf("  Remaining IPv4 Throttled time:  %d\n", pPdnThrottleInfo_ind->pPDNThrottleInformation->remaining_ipv4_throttled_time);
			SockPrintf("  Remaining IPv6 Throttled time:  %d\n", pPdnThrottleInfo_ind->pPDNThrottleInformation->remaining_ipv6_throttled_time);
			SockPrintf("  APN Name:  %s\n", pPdnThrottleInfo_ind->pPDNThrottleInformation->ApnName);
		}
	}	
	
	if (swi_uint256_get_bit (pPdnThrottleInfo_ind->ParamPresenceMask, 0x11))
	{
		SockPrintf("  Throttle Info Extended Count:  %d\n", pPdnThrottleInfo_ind->throttle_info_ext_len);
		for (int idx = 0; idx < pPdnThrottleInfo_ind->throttle_info_len; ++idx)
		{
			SockPrintf("  Is IPv4 Throttled:  %d\n", pPdnThrottleInfo_ind->pExtPDNThrottleInformationList->is_ipv4_throttled);
			SockPrintf("  Is IPv6 Throttled:  %d\n", pPdnThrottleInfo_ind->pExtPDNThrottleInformationList->is_ipv6_throttled);
			SockPrintf("  Is Non-IP Throttled:  %d\n", pPdnThrottleInfo_ind->pExtPDNThrottleInformationList->is_non_ip_throttled);
			SockPrintf("  Remaining IPv4 Throttled time:  %d\n", pPdnThrottleInfo_ind->pExtPDNThrottleInformationList->remaining_ipv4_throttled_time);
			SockPrintf("  Remaining IPv6 Throttled time:  %d\n", pPdnThrottleInfo_ind->pExtPDNThrottleInformationList->remaining_ipv6_throttled_time);
			SockPrintf("  Remaining Non-IP Throttled time:  %d\n", pPdnThrottleInfo_ind->pExtPDNThrottleInformationList->remaining_non_ip_throttled_time);
			SockPrintf("  APN Name:  %s\n", pPdnThrottleInfo_ind->pExtPDNThrottleInformationList->ApnName);
		}
	}

	if (swi_uint256_get_bit (pPdnThrottleInfo_ind->ParamPresenceMask, 0x12))
	{
		SockPrintf("  Throttle Info Additional Params Count:  %d\n", pPdnThrottleInfo_ind->throttle_info_addn_params_len);
		for (int idx = 0; idx < pPdnThrottleInfo_ind->throttle_info_len; ++idx)
		{
			SockPrintf("  Is Emergency APN:  %d\n", pPdnThrottleInfo_ind->pAddPDNThrottleInformationList->is_emergency_apn);
			SockPrintf("  APN Blocked Oon All Plmns:  %d\n", pPdnThrottleInfo_ind->pAddPDNThrottleInformationList->apn_blocked_on_all_plmns);
			SockPrintf("  throttled_plmn_id:  %d", pPdnThrottleInfo_ind->pAddPDNThrottleInformationList->throttled_plmn_id[0]);
			SockPrintf("%d", pPdnThrottleInfo_ind->pAddPDNThrottleInformationList->throttled_plmn_id[1]);
			SockPrintf("%d\n", pPdnThrottleInfo_ind->pAddPDNThrottleInformationList->throttled_plmn_id[2]);
			SockPrintf("  APN Name:  %s\n", pPdnThrottleInfo_ind->pAddPDNThrottleInformationList->ApnName);
		}
	}
}

void DisplayModemAssistedKaStatusIndication(unpack_wds_SLQSModemAssistedKaStatus_ind_t  *pModemAssistedKaStatus_ind)
{
	SockPrintf("\n  Modem Assisted Keep-Alive Status Indication\n");
	SockPrintf("  	Status:  %d\n", pModemAssistedKaStatus_ind->Status);
	SockPrintf("  	Keep-Alive Handle:  %d\n", pModemAssistedKaStatus_ind->Keep_alive_handle);
}

void DisplayWdsEventReport(unpack_wds_SLQSSetWdsEventReport_ind_t *pWdsEventReport_ind)
{
	SockPrintf("\n  WDS Event Report Indication\n");
	if (swi_uint256_get_bit (pWdsEventReport_ind->ParamPresenceMask, 0x10))
		SockPrintf("  	tx_ok_count:  %d\n", pWdsEventReport_ind->tx_ok_count);
	if (swi_uint256_get_bit (pWdsEventReport_ind->ParamPresenceMask, 0x11))
		SockPrintf("  	rx_ok_count:  %d\n", pWdsEventReport_ind->rx_ok_count);
	if (swi_uint256_get_bit (pWdsEventReport_ind->ParamPresenceMask, 0x12))
		SockPrintf("  	tx_err_count:  %d\n", pWdsEventReport_ind->tx_err_count);
	if (swi_uint256_get_bit (pWdsEventReport_ind->ParamPresenceMask, 0x13))
		SockPrintf("  	rx_err_count:  %d\n", pWdsEventReport_ind->rx_err_count);
	if (swi_uint256_get_bit (pWdsEventReport_ind->ParamPresenceMask, 0x14))
		SockPrintf("  	tx_ofl_count:  %d\n", pWdsEventReport_ind->tx_ofl_count);
	if (swi_uint256_get_bit (pWdsEventReport_ind->ParamPresenceMask, 0x15))
		SockPrintf("  	rx_ofl_count:  %d\n", pWdsEventReport_ind->rx_ofl_count);
	if (swi_uint256_get_bit (pWdsEventReport_ind->ParamPresenceMask, 0x16))
	{	
		SockPrintf("  	ChannelRate.current_channel_tx_rate:  %d\n", pWdsEventReport_ind->channelRate.current_channel_tx_rate);
		SockPrintf("  	ChannelRate.current_channel_rx_rate:  %d\n", pWdsEventReport_ind->channelRate.current_channel_rx_rate);
	}
	if (swi_uint256_get_bit (pWdsEventReport_ind->ParamPresenceMask, 0x18))
		SockPrintf("  	dormancy_status:  %d\n", pWdsEventReport_ind->dormancy_status);
	if (swi_uint256_get_bit (pWdsEventReport_ind->ParamPresenceMask, 0x19))
		SockPrintf("  	tx_ok_bytes_count:  0x%"PRIX64"\n", pWdsEventReport_ind->tx_ok_bytes_count);
	if (swi_uint256_get_bit (pWdsEventReport_ind->ParamPresenceMask, 0x1A))
		SockPrintf("  	rx_ok_bytes_count:  0x%"PRIX64"\n", pWdsEventReport_ind->rx_ok_bytes_count);
	if (swi_uint256_get_bit (pWdsEventReport_ind->ParamPresenceMask, 0x1B))
		SockPrintf("  	mip_status:  %d\n", pWdsEventReport_ind->mip_status);
	if (swi_uint256_get_bit (pWdsEventReport_ind->ParamPresenceMask, 0x1F))
		SockPrintf("  	data_call_status:  %d\n", pWdsEventReport_ind->data_call_status);
	if (swi_uint256_get_bit (pWdsEventReport_ind->ParamPresenceMask, 0x20))
		SockPrintf("  	current_sys:  %d\n", pWdsEventReport_ind->current_sys);

	//DataCallTypeTlv_t               dataCallType; //22
	if (swi_uint256_get_bit (pWdsEventReport_ind->ParamPresenceMask, 0x22))
	{
		SockPrintf("  	dataCallType.data_call_type:  %d\n", pWdsEventReport_ind->dataCallType.data_call_type);
    	SockPrintf("  	dataCallType.tethered_call_type:  %d\n", pWdsEventReport_ind->dataCallType.tethered_call_type);
	}

	//EVDOPageMonitorPeriodChange_t   eVDOPageMonitorPeriodChange; //23
	if (swi_uint256_get_bit (pWdsEventReport_ind->ParamPresenceMask, 0x23))
	{
		SockPrintf("  	eVDOPageMonitorPeriodChange.evdo_page_monitor_period_change:  %d\n", pWdsEventReport_ind->eVDOPageMonitorPeriodChange.evdo_page_monitor_period_change);
    	SockPrintf("  	eVDOPageMonitorPeriodChange.evdo_force_long_sleep:  %d\n", pWdsEventReport_ind->eVDOPageMonitorPeriodChange.evdo_force_long_sleep);
	}

	if (swi_uint256_get_bit (pWdsEventReport_ind->ParamPresenceMask, 0x25))
		SockPrintf("  	tx_dropped_count:  %d\n", pWdsEventReport_ind->tx_dropped_count);
	if (swi_uint256_get_bit (pWdsEventReport_ind->ParamPresenceMask, 0x26))
		SockPrintf("  	rx_dropped_count:  %d\n", pWdsEventReport_ind->rx_dropped_count);
	if (swi_uint256_get_bit (pWdsEventReport_ind->ParamPresenceMask, 0x27))
		SockPrintf("  	uplink_flow_control:  %d\n", pWdsEventReport_ind->uplink_flow_control); 
	if (swi_uint256_get_bit (pWdsEventReport_ind->ParamPresenceMask, 0x28))
		SockPrintf("  	data_call_addr_family:  %d\n", pWdsEventReport_ind->data_call_addr_family);
	
	//AdditionalPdnFiltersRemoved_t   additionalPdnFiltersRemoved; //29
	if (swi_uint256_get_bit (pWdsEventReport_ind->ParamPresenceMask, 0x29))
	{
		for (int idx = 0; idx < pWdsEventReport_ind->additionalPdnFiltersRemoved.removed_filter_handles_len; ++idx)
		{
			SockPrintf("  	additionalPdnFiltersRemoved.removed_filter_handles[%d]:  %d\n", idx, pWdsEventReport_ind->additionalPdnFiltersRemoved.removed_filter_handles[idx]); 
		}
	}

	//DataBearerTechnologyExtended_t  dataBearerTechnologyExtended; //2A
	if (swi_uint256_get_bit (pWdsEventReport_ind->ParamPresenceMask, 0x2A))
	{
		SockPrintf("  	dataBearerTechnologyExtended.technology:  %d\n", pWdsEventReport_ind->dataBearerTechnologyExtended.technology);
		SockPrintf("  	dataBearerTechnologyExtended.rat_value:  %d\n", pWdsEventReport_ind->dataBearerTechnologyExtended.rat_value);
		SockPrintf("  	dataBearerTechnologyExtended.so_mask:  0x%"PRIX64"\n", pWdsEventReport_ind->dataBearerTechnologyExtended.so_mask);
	}

	if (swi_uint256_get_bit (pWdsEventReport_ind->ParamPresenceMask, 0x2B))
		SockPrintf("  	uplink_fc_seq_num:  %d\n", pWdsEventReport_ind->uplink_fc_seq_num);  //2B

	//DormancyResultIndicator_t       dormancyResultIndicator; //2C
	if (swi_uint256_get_bit (pWdsEventReport_ind->ParamPresenceMask, 0x2C))
	{
		SockPrintf("  	dormancyResultIndicator.status:  %d\n", pWdsEventReport_ind->dormancyResultIndicator.status);
		SockPrintf("  	dormancyResultIndicator.dormancy_failure_reason:  %d\n", pWdsEventReport_ind->dormancyResultIndicator.dormancy_failure_reason);
	}

	//ExtendedChannelRate_t           extendedChannelRate; //2D
	if (swi_uint256_get_bit (pWdsEventReport_ind->ParamPresenceMask, 0x2D))
	{	
		SockPrintf("  	extendedChannelRate.rate_type:  %d\n", pWdsEventReport_ind->extendedChannelRate.rate_type);
		SockPrintf("  	extendedChannelRate.channel_tx_rate_ex:  0x%"PRIX64"\n", pWdsEventReport_ind->extendedChannelRate.channel_tx_rate_ex);
		SockPrintf("  	extendedChannelRate.channel_rx_rate_ex:  0x%"PRIX64"\n", pWdsEventReport_ind->extendedChannelRate.channel_rx_rate_ex);
	}
}

void Display3GPPConfigItems(unpack_wds_SLQSGet3GPPConfigItem_t *pGet3GPPConfigItem)
{
	SockPrintf("\n  3GPP Configuration Items\n");

	if (swi_uint256_get_bit (pGet3GPPConfigItem->ParamPresenceMask, 0x10))
	{	
		SockPrintf("  	LTEAttachProfile:  %d\n", pGet3GPPConfigItem->LTEAttachProfile);
	}
	if (swi_uint256_get_bit (pGet3GPPConfigItem->ParamPresenceMask, 0x11))
	{	
		for (int idx = 0; idx < 4; ++idx)
		{
			SockPrintf("  	profileList[%d]:  %d\n", idx, pGet3GPPConfigItem->profileList[idx]);
		}
	}
	if (swi_uint256_get_bit (pGet3GPPConfigItem->ParamPresenceMask, 0x12))
	{	
		SockPrintf("  	defaultPDNEnabled:  %d\n", pGet3GPPConfigItem->defaultPDNEnabled);
	}
	if (swi_uint256_get_bit (pGet3GPPConfigItem->ParamPresenceMask, 0x13))
	{	
		SockPrintf("  	_3gppRelease:  %d\n", pGet3GPPConfigItem->_3gppRelease);
	}
	if (swi_uint256_get_bit (pGet3GPPConfigItem->ParamPresenceMask, 0x14))
	{	
		for (int idx = 0; idx < pGet3GPPConfigItem->LTEAttachProfileListLen; ++idx)
		{
			SockPrintf("  	LTEAttachProfileList[%d]:  %d\n", idx, pGet3GPPConfigItem->LTEAttachProfileList[idx]);
		}
	}
}

void DisplayThroughputInformationInd(unpack_wds_ThroughputInformationInd_t  *pThroughputInformationInd)
{
	SockPrintf("\n  Throughput Information Indication\n");

	if (swi_uint256_get_bit (pThroughputInformationInd->ParamPresenceMask, 0x10))
	{	
		SockPrintf("  	Throughput information count:  %d\n", pThroughputInformationInd->throughput_info_len);
		ThroughputInformationItem_t *pThroughputInformationList = pThroughputInformationInd->pThroughputInformationList;
		ThroughputInformationMac_t *pThroughputInformationMac = NULL;
		for (int idx = 0; idx < pThroughputInformationInd->throughput_info_len; ++idx)
		{
			SockPrintf("    ThroughputInformation[%d]->Apn: %s", idx, pThroughputInformationList->apn_string);
			SockPrintf("    ThroughputInformation[%d]->ip_type: %d", idx, pThroughputInformationList->ip_type);
			SockPrintf("    ThroughputInformation[%d]->tech_type: %d", idx, pThroughputInformationList->tech_type);
  			SockPrintf("    ThroughputInformation[%d]->subscription: %d", idx, pThroughputInformationList->subscription);
   			SockPrintf("    ThroughputInformation[%d]->uplink_actual_rate: %d", idx, pThroughputInformationList->uplink_actual_rate);
   			SockPrintf("    ThroughputInformation[%d]->uplink_allowed_rate: %d", idx, pThroughputInformationList->uplink_allowed_rate);
   			SockPrintf("    ThroughputInformation[%d]->uplink_queue_size: %d", idx, pThroughputInformationList->uplink_queue_size);
   			SockPrintf("    ThroughputInformation[%d]->throughput_signal: %d", idx, pThroughputInformationList->throughput_signal);
  			SockPrintf("    ThroughputInformation[%d]->valid_port: %d", idx, pThroughputInformationList->valid_port);
  			SockPrintf("    ThroughputInformation[%d]->data_port: %d", idx, pThroughputInformationList->data_port);
  			SockPrintf("    ThroughputInformation[%d]->ep_type: %d", idx, pThroughputInformationList->ep_type);
			SockPrintf("    ThroughputInformation[%d]->iface_id: %d", idx, pThroughputInformationList->iface_id);
  			SockPrintf("    ThroughputInformation[%d]->mux_id: %d", idx, pThroughputInformationList->mux_id);

  			SockPrintf("    ThroughputInformation[%d]->bearer_rlp_mac_id_throughput_info_len: %d", idx, pThroughputInformationList->bearer_rlp_mac_id_throughput_info_len);
  			pThroughputInformationMac = pThroughputInformationList->pThroughputInformationMac;
			for (int idy = 0; idy < pThroughputInformationList->bearer_rlp_mac_id_throughput_info_len; ++idy)
			{
  				SockPrintf("      ThroughputInformation[%d][%d]->bearer_rlp_mac_id: %d", idx, idy, pThroughputInformationMac->bearer_rlp_mac_id);
  				SockPrintf("      ThroughputInformation[%d][%d]->uplink_actual_rate: %d", idx, idy, pThroughputInformationMac->uplink_actual_rate);
  				SockPrintf("      ThroughputInformation[%d][%d]->uplink_queue_size: %d", idx, idy, pThroughputInformationMac->uplink_queue_size);
  				SockPrintf("      ThroughputInformation[%d][%d]->is_primary: %d", idx, idy, pThroughputInformationMac->is_primary); 
				++pThroughputInformationMac;
			}
			++pThroughputInformationList;
		}

	}
}

void DisplayDownlinkThroughputInformationInd(unpack_wds_DLThroughputInformationInd_t  *pDLThroughputInfoInd)
{
	SockPrintf("\n  Downlink Throughput Information Indication\n");

	if (swi_uint256_get_bit (pDLThroughputInfoInd->ParamPresenceMask, 0x10))
	{
		SockPrintf("  	Downlink_allowed_rate:  %d\n", *pDLThroughputInfoInd->pDownlink_allowed_rate);
	}
	if (swi_uint256_get_bit (pDLThroughputInfoInd->ParamPresenceMask, 0x11))
	{
		SockPrintf("  	Confidence_level:  %d\n", *pDLThroughputInfoInd->pConfidence_level);
	}
	if (swi_uint256_get_bit (pDLThroughputInfoInd->ParamPresenceMask, 0x12))
	{
		SockPrintf("  	Is_suspended:  %d\n", *pDLThroughputInfoInd->pIs_suspended);
	}

}
void DisplayQueryDLThroughputReportingStatus(unpack_wds_QueryDLThroughputReportingStatusInd_t  *pQueryDLThroughputReportingStatusInd)
{
	SockPrintf("\n  Query Downlink Throughput Reporting Status Indication\n");

	if (swi_uint256_get_bit (pQueryDLThroughputReportingStatusInd->ParamPresenceMask, 0x10))
	{
		switch(*pQueryDLThroughputReportingStatusInd->pReporting_status)
		{
			case 0:
				SockPrintf("  	Reporting_status:  Throughput reporting enabled\n");
			break;
			case 1:
				SockPrintf("  	Reporting_status:  No data call\n");
			break;
			case 2:
				SockPrintf("  	Reporting_status:  All calls dormant\n");
			break;
			case 3:
				SockPrintf("  	Reporting_status:  Unsupported RAT\n");
			break;
			default:
				SockPrintf("  	Reporting_status:  Returned value Unknown\n");
			break;
		}
	}
	if (swi_uint256_get_bit (pQueryDLThroughputReportingStatusInd->ParamPresenceMask, 0x11))
	{
		SockPrintf("  	Actual Interval:  %d\n", *pQueryDLThroughputReportingStatusInd->pActual_interval);
	}
}

void DisplayGetCurrentChannelRate(unpack_wds_SLQSGetCurrentChannelRate_t *pCurrentChannelRate)
{
	SockPrintf("\n  Get Current Channel Rate\n");

	if (swi_uint256_get_bit (pCurrentChannelRate->ParamPresenceMask, 0x01))
	{
		SockPrintf("  	current channel tx rate:  %d\n", pCurrentChannelRate->current_channel_tx_rate);
		SockPrintf("  	current channel rx rate:  %d\n", pCurrentChannelRate->current_channel_rx_rate);
		SockPrintf("  	max channel tx rate:  %d\n", pCurrentChannelRate->max_channel_tx_rate);
		SockPrintf("  	max channel rx rate:  %d\n", pCurrentChannelRate->max_channel_rx_rate);
	}
}

void DisplayProfileChangeInd(unpack_wds_SLQSSWIProfileChange_ind_t* pProfileChangeInd)
{
	SockPrintf("\n  Profile Change Indication\n");

	SockPrintf("  	Type of profile:  %d\n", pProfileChangeInd->type);
	SockPrintf("  	Index of profile:  %d\n", pProfileChangeInd->index);

	if (swi_uint256_get_bit(pProfileChangeInd->ParamPresenceMask, 0x10))
	{
		SockPrintf("  	Source of change:  %d\n", pProfileChangeInd->source);
	}
}

void DisplayGetDefaultNssai(unpack_wds_swi_GetDefaultNssai_t *pDefaultNssai)
{
	SockPrintf("\n  Default Network Slice Selection Assistance Information\n");

	SockPrintf("  	default_nssai_info_len:  %d\n", pDefaultNssai->default_nssai_info_len);

	for(uint8_t idx = 0; idx < pDefaultNssai->default_nssai_info_len; ++idx)
	{
		SockPrintf("  	default_nssai_info[%d].sst:  %d\n", idx, pDefaultNssai->default_nssai_info[idx].sst);

		SockPrintf("  	default_nssai_info[%d].sd:  %d %d %d\n", idx, pDefaultNssai->default_nssai_info[idx].sd[0],
																	pDefaultNssai->default_nssai_info[idx].sd[1],
																	pDefaultNssai->default_nssai_info[idx].sd[2]);
		SockPrintf("  	default_nssai_info[%d].mapped_sst_present:  %d\n", idx, pDefaultNssai->default_nssai_info[idx].mapped_sst_present);
		SockPrintf("  	default_nssai_info[%d].mapped_sst:  %d\n", idx, pDefaultNssai->default_nssai_info[idx].mapped_sst);
		SockPrintf("  	default_nssai_info[%d].mapped_sd:  %d %d %d\n", idx, pDefaultNssai->default_nssai_info[idx].mapped_sd[0],
																	pDefaultNssai->default_nssai_info[idx].mapped_sd[1],
																	pDefaultNssai->default_nssai_info[idx].mapped_sd[2]);
	}
	SockPrintf("  	default_nssai_info_str:  %s\n", pDefaultNssai->default_nssai_info_str);

}

void DisplayGetProfileSnssai(unpack_wds_swi_GetProfileSnsaai_t *pGetProfileSnsaai)
{
	SockPrintf("\n  Single Network Slice Selection Assistance Information\n");

	SockPrintf("  	profile_snssai.sstr:  %d\n", pGetProfileSnsaai->profile_snssai.sst);

	SockPrintf("  	profile_snssai.sd:  %d %d %d\n", pGetProfileSnsaai->profile_snssai.sd[0],
																pGetProfileSnsaai->profile_snssai.sd[1],
																pGetProfileSnsaai->profile_snssai.sd[2]);
	SockPrintf("  	profile_snssai.mapped_sst_present:  %d\n", pGetProfileSnsaai->profile_snssai.mapped_sst_present);
	SockPrintf("  	profile_snssai.mapped_sst:  %d\n", pGetProfileSnsaai->profile_snssai.mapped_sst);
	SockPrintf("  	profile_snssai.mapped_sd:  %d %d %d\n", pGetProfileSnsaai->profile_snssai.mapped_sd[0],
																pGetProfileSnsaai->profile_snssai.mapped_sd[1],
																pGetProfileSnsaai->profile_snssai.mapped_sd[2]);

	SockPrintf("  	profile_snssai_str:  %s\n", pGetProfileSnsaai->profile_snssai_str);
	SockPrintf("  	Session and Service Continuity:  %d\n", pGetProfileSnsaai->ssc);
	SockPrintf("  	Preferred Access Type:  %d\n", pGetProfileSnsaai->preferred_access_type);
}

void DisplayCreateSwiProfile(unpack_wds_SLQSCreateProfile_t* pCreateSwiProfile)
{
	if (pCreateSwiProfile && pCreateSwiProfile->pCreateProfileOut)
	{
		SockPrintf("Prifile Type: %d\n", pCreateSwiProfile->pCreateProfileOut->ProfileType);
		SockPrintf("Prifile Index: %d\n", pCreateSwiProfile->pCreateProfileOut->ProfileIndex);
	}
}
