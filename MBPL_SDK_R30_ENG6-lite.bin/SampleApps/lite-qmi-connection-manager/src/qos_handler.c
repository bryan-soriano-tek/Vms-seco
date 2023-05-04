#include <inttypes.h>
#include <string.h>
#include <arpa/inet.h>
#include "common.h"
#include "qmerrno.h"
#include "proc_util.h"
#include "qmux_util.h"
#include "user_input.h"
#include "qos_handler.h"
#include "socket_server.h"
#include "qos.h"
#include "lite-qmi-demo.h"

static QmiService s_QosService;

void QosIndicationCallback(uint8_t* qmiPacket, uint16_t qmiPacketSize, void* pIndicationCallbackContext);

int InitializeQosService(CtlService* pCtlSvc)
{
	int ret = pCtlSvc ? CtlService_InitializeRegularService(pCtlSvc, &s_QosService, eQOS, QosIndicationCallback, NULL) : -1;
	if (ret != 0)
	{
		dlog(eLOG_ERROR, "QOS service is not supported.\n");
		s_QosService.serviceType = 0;
	}

	return ret;
}

void ShutDownQosService(CtlService* pCtlSvc)
{
	if (pCtlSvc)
		CtlService_ShutDownRegularService(pCtlSvc, &s_QosService);
}

void OutputQosFlowGranted(unpack_qos_QmiCbkQosFlowGranted_t* pQosFlowGranted)
{
	SockPrintf("flow_valid_params= %"PRIu64"\n", pQosFlowGranted->flow_valid_params);
	SockPrintf("ip_flow_trf_cls= %d\n", pQosFlowGranted->ip_flow_trf_cls);
	SockPrintf("data_rate_max= %"PRIu64"\n", pQosFlowGranted->data_rate_max);
	SockPrintf("guaranteed_rates= %"PRIu64"\n", pQosFlowGranted->guaranteed_rate);
	SockPrintf("peak_rate= %d\n", pQosFlowGranted->peak_rate);
	SockPrintf("token_rate= %d\n", pQosFlowGranted->token_rate);
	SockPrintf("bucket_size= %d\n", pQosFlowGranted->bucket_size);
	SockPrintf("ip_flow_latency= %d\n", pQosFlowGranted->ip_flow_latency);
	SockPrintf("ip_flow_jitter= %d\n", pQosFlowGranted->ip_flow_jitter);
	SockPrintf("ip_flow_pkt_error_rate_multiplier= %d\n", pQosFlowGranted->ip_flow_pkt_error_rate_multiplier);
	SockPrintf("ip_flow_pkt_error_rate_exponent= %d\n", pQosFlowGranted->ip_flow_pkt_error_rate_exponent);
	SockPrintf("ip_flow_min_policed_packet_size= %d\n", pQosFlowGranted->ip_flow_min_policed_packet_size);
	SockPrintf("ip_flow_max_allowed_packet_size= %d\n", pQosFlowGranted->ip_flow_max_allowed_packet_size);
	SockPrintf("ip_flow_3gpp_residual_bit_error_rate= %d\n", pQosFlowGranted->ip_flow_3gpp_residual_bit_error_rate);
	SockPrintf("ip_flow_3gpp_traffic_handling_priority= %d\n", pQosFlowGranted->ip_flow_3gpp_traffic_handling_priority);
	SockPrintf("ip_flow_3gpp2_profile_id= %d\n", pQosFlowGranted->ip_flow_3gpp2_profile_id);
	SockPrintf("ip_flow_3gpp2_flow_priority= %d\n", pQosFlowGranted->ip_flow_3gpp2_flow_priority);
	SockPrintf("ip_flow_3gpp_im_cn_flag= %d\n", pQosFlowGranted->ip_flow_3gpp_im_cn_flag);
	SockPrintf(" ip_flow_3gpp_sig_ind= %d\n", pQosFlowGranted->ip_flow_3gpp_sig_ind);
	SockPrintf("ip_flow_lte_qci= %d\n", pQosFlowGranted->ip_flow_lte_qci);
}

void OutputQosFilters(unpack_qos_QmiCbkQosFilters_t* pQosFilters)
{
	SockPrintf("qos_filters_len= %d\n", pQosFilters->qos_filters_len);
	for (int i = 0; i < pQosFilters->qos_filters_len; i++)
	{
		SockPrintf("ip_version[%d]= %d\n", i, pQosFilters->qos_filters[i].ip_version);
		SockPrintf("valid_params_ipv4[%d]= %"PRIu64"\n", i, pQosFilters->qos_filters[i].valid_params_ipv4);
		if (pQosFilters->qos_filters[i].valid_params_ipv4)
		{
			SockPrintf("ipv4_addr_1[%d]= %d\n", i, pQosFilters->qos_filters[i].ipv4_addr_1);
			SockPrintf("subnet_mask_1[%d]= %d\n", i, pQosFilters->qos_filters[i].subnet_mask_1);
			SockPrintf("ipv4_addr_2[%d]= %d\n", i, pQosFilters->qos_filters[i].ipv4_addr_2);
			SockPrintf("subnet_mask_2[%d]= %d\n", i, pQosFilters->qos_filters[i].subnet_mask_2);
			SockPrintf("val_ipv4[%d]= %d\n", i, pQosFilters->qos_filters[i].val_ipv4);
			SockPrintf("mask_ipv4[%d]= %d\n", i, pQosFilters->qos_filters[i].mask_ipv4);
		}
		SockPrintf("valid_params_ipv6[%d]= %"PRIu64"\n", i, pQosFilters->qos_filters[i].valid_params_ipv6);
		if (pQosFilters->qos_filters[i].valid_params_ipv6)
		{
			SockPrintf("prefix_len_1[%d]= %d\n", i, pQosFilters->qos_filters[i].prefix_len_1);
			SockPrintf("IPv6[%d]: ");
			for (int idx = 0; idx < pQosFilters->qos_filters[i].prefix_len_1; ++idx)
				SockPrintf("%d:", pQosFilters->qos_filters[i].ipv6_address_1[idx]);

			SockPrintf("\nprefix_len_2[%d]= %d\n", i, pQosFilters->qos_filters[i].prefix_len_2);
			SockPrintf("IPv6[%d]: ");
			for (int idx = 0; idx < pQosFilters->qos_filters[i].prefix_len_2; ++idx)
				SockPrintf("%d:", pQosFilters->qos_filters[i].ipv6_address_2[idx]);

			SockPrintf("\nval_ipv6[%d]= %d\n", i, pQosFilters->qos_filters[i].val_ipv6);
			SockPrintf("mask_ipv6[%d]= %d\n", i, pQosFilters->qos_filters[i].mask_ipv6);
			SockPrintf("flow_label_ipv6[%d]= %d\n", i, pQosFilters->qos_filters[i].flow_label_ipv6);
			SockPrintf("xport_protocol[%d]= %d\n", i, pQosFilters->qos_filters[i].xport_protocol);
		}
		SockPrintf("valid_params_port_1[%d]= %"PRIu64"\n", i, pQosFilters->qos_filters[i].valid_params_port_1);
		if (pQosFilters->qos_filters[i].valid_params_port_1)
		{
			SockPrintf("port_1[%d]= %d\n", i, pQosFilters->qos_filters[i].port_1);
			SockPrintf("range_1[%d]= %d\n", i, pQosFilters->qos_filters[i].range_1);
			SockPrintf("port_2[%d]= %d\n", i, pQosFilters->qos_filters[i].port_2);
			SockPrintf("range_2[%d]= %d\n", i, pQosFilters->qos_filters[i].range_2);
		}
		SockPrintf("valid_params_port_2[%d]= %"PRIu64"\n", i, pQosFilters->qos_filters[i].valid_params_port_2);
		if (pQosFilters->qos_filters[i].valid_params_port_2)
		{
			SockPrintf("port_3[%d]= %d\n", i, pQosFilters->qos_filters[i].port_3);
			SockPrintf("range_3[%d]= %d\n", i, pQosFilters->qos_filters[i].range_3);
			SockPrintf("port_4[%d]= %d\n", i, pQosFilters->qos_filters[i].port_4);
			SockPrintf("range_4[%d]= %d\n", i, pQosFilters->qos_filters[i].range_4);
		}
		SockPrintf("valid_params_icmp[%d]= %"PRIu64"\n", i, pQosFilters->qos_filters[i].valid_params_icmp);
		if (pQosFilters->qos_filters[i].valid_params_icmp)
		{
			SockPrintf("type_icmp[%d]= %d\n", i, pQosFilters->qos_filters[i].type_icmp);
			SockPrintf("code_icmp[%d]= %d\n", i, pQosFilters->qos_filters[i].code_icmp);
		}
		SockPrintf("valid_params_spi_1[%d]= %"PRIu64"\n", i, pQosFilters->qos_filters[i].valid_params_spi_1);
		if (pQosFilters->qos_filters[i].valid_params_spi_1)
			SockPrintf("spi_1[%d]= %d\n", i, pQosFilters->qos_filters[i].spi_1);
		SockPrintf("valid_params_spi_2[%d]= %"PRIu64"\n", i, pQosFilters->qos_filters[i].valid_params_spi_2);
		if (pQosFilters->qos_filters[i].valid_params_spi_2)
			SockPrintf("spi_2[%d]= %d\n", i, pQosFilters->qos_filters[i].spi_2);
		SockPrintf("filter_id[%d]= %d\n", i, pQosFilters->qos_filters[i].filter_id);
		SockPrintf("filter_precedence[%d]= %d\n", i, pQosFilters->qos_filters[i].filter_precedence);
	}
}

void OutputSwiQosFlow(const char* szTxRx, unpack_qos_swiQosFlow_t* pQosFlow)
{
	SockPrintf(" %s QoS Flow:\n", szTxRx);
	SockPrintf("  Index: %d\n", pQosFlow->index);
	if (pQosFlow->is_ProfileId3GPP2_Available)
		SockPrintf("  3GPP2 Profile ID: %d\n", pQosFlow->ProfileId3GPP2);
	if (pQosFlow->is_TrafficClass_Available)
		SockPrintf("  Traff Class: %d\n", pQosFlow->TrafficClass);
	if (pQosFlow->is_DataRate_Available)
		SockPrintf("  Max Required Data Rate: %d, Min Guaranteed Data Rate: %d\n", pQosFlow->DataRate.dataRateMax, pQosFlow->DataRate.guaranteedRate);
	if (pQosFlow->is_TokenBucket_Available)
		SockPrintf("  Data Rate Token Bucket Peak Rate: %d, Token Rate: %d, Bucket Size: %d\n",
			pQosFlow->TokenBucket.peakRate, pQosFlow->TokenBucket.tokenRate, pQosFlow->TokenBucket.bucketSz);
	if (pQosFlow->is_Latency_Available)
		SockPrintf("  Latency: %d\n", pQosFlow->Latency);
	if (pQosFlow->is_Jitter_Available)
		SockPrintf("  Jitter: %d\n", pQosFlow->Jitter);
	if (pQosFlow->is_PktErrRate_Available)
		SockPrintf("  Error Rate Multiplier: %d, Exponent: %d\n", pQosFlow->PktErrRate.multiplier, pQosFlow->PktErrRate.exponent);
	if (pQosFlow->is_MinPolicedPktSz_Available)
		SockPrintf("  Min Policed Packet Size: %d\n", pQosFlow->MinPolicedPktSz);
	if (pQosFlow->is_MaxAllowedPktSz_Available)
		SockPrintf("  Max Allowed Packet Size: %d\n", pQosFlow->MaxAllowedPktSz);
	if (pQosFlow->is_val_3GPPResResidualBER_Available)
		SockPrintf("  3GPP Residual Bit Error Rate: %d\n", pQosFlow->val_3GPPResResidualBER);
	if (pQosFlow->is_val_3GPPTraHdlPri_Available)
		SockPrintf("  3GPP Traffic Handling Priority: %d\n", pQosFlow->val_3GPPTraHdlPri);
	if (pQosFlow->is_val_3GPP2Pri_Available)
		SockPrintf("  3GPP2 Flow Priority: %d\n", pQosFlow->val_3GPP2Pri);
	if (pQosFlow->is_val_3GPPImCn_Available)
		SockPrintf("  3GPP IM CN Flag: %d\n", pQosFlow->val_3GPPImCn);
	if (pQosFlow->is_val_3GPPSigInd_Available)
		SockPrintf("  3GPP Signaling Indication: %d\n", pQosFlow->val_3GPPSigInd);
	if (pQosFlow->is_LteQci_Available)
		SockPrintf("  LTE QoS Class Identifier: %d\n", pQosFlow->LteQci);
}

void OutputSwiQosFilter(const char* szTxRx, uint8_t num, unpack_qos_swiQosFilter_t* pQosFilter)
{
	SockPrintf(" %s QoS Filter(s): %d\n", szTxRx, num);

	for (uint8_t i = 0; i < num; i++)
	{
		SockPrintf("  %s QoS Filter[%d]:\n", szTxRx, i);
		SockPrintf("   Index: %d\n", pQosFilter[i].index);
		SockPrintf("   Version: %d\n", pQosFilter[i].version);
		if (pQosFilter[i].is_IPv4SrcAddr_Available)
		{
			char addr[INET_ADDRSTRLEN];
			SockPrintf("   Source IPv4 Addr: %s, subnet mask: %x\n", inet_ntop(AF_INET, &pQosFilter[i].IPv4SrcAddr.addr, addr, INET_ADDRSTRLEN), pQosFilter[i].IPv4SrcAddr.subnetMask);
		}
		if (pQosFilter[i].is_IPv4DstAddr_Available)
		{
			char addr[INET_ADDRSTRLEN];
			SockPrintf("   Destination IPv4 Addr: %s, subnet mask: %x\n", inet_ntop(AF_INET, &pQosFilter[i].IPv4DstAddr.addr, addr, INET_ADDRSTRLEN), pQosFilter[i].IPv4DstAddr.subnetMask);
		}
		if (pQosFilter[i].is_NxtHdrProto_Available)
			SockPrintf("   Next Header Protocol: 0x%x\n", pQosFilter[i].NxtHdrProto);
		if (pQosFilter[i].is_IPv4Tos_Available)
			SockPrintf("   Type of service value: %x, mask: %x\n", pQosFilter[i].IPv4Tos.val, pQosFilter[i].IPv4Tos.mask);
		if (pQosFilter[i].is_IPv6SrcAddr_Available)
		{
			char addr[INET6_ADDRSTRLEN];
			SockPrintf("   IPv6 Filter Soruce Address: %s, Prefix length: %d\n", inet_ntop(AF_INET6, pQosFilter[i].IPv6SrcAddr.addr, addr, INET6_ADDRSTRLEN), pQosFilter[i].IPv6SrcAddr.prefixLen);
		}
		if (pQosFilter[i].is_IPv6DstAddr_Available)
		{
			char addr[INET6_ADDRSTRLEN];
			SockPrintf("   IPv6 Filter Destination Address: %s, Prefix length: %d\n", inet_ntop(AF_INET6, pQosFilter[i].IPv6DstAddr.addr, addr, INET6_ADDRSTRLEN), pQosFilter[i].IPv6DstAddr.prefixLen);
		}
		if (pQosFilter[i].is_IPv6TrafCls_Available)
			SockPrintf("   IPv6 Filter Traffic Class value: %x, mask: %x\n", pQosFilter[i].IPv6TrafCls.val, pQosFilter[i].IPv6TrafCls.mask);
		if (pQosFilter[i].is_IPv6Label_Available)
			SockPrintf("   IPv6 Filter Flow Label: %d\n", pQosFilter[i].IPv6Label);
		if (pQosFilter[i].is_TCPSrcPort_Available)
			SockPrintf("   TCP Filter Source Port: %d, Range: %d\n", pQosFilter[i].TCPSrcPort.port, pQosFilter[i].TCPSrcPort.range);
		if (pQosFilter[i].is_TCPDstPort_Available)
			SockPrintf("   TCP Filter Destination Port: %d, Range: %d\n", pQosFilter[i].TCPDstPort.port, pQosFilter[i].TCPDstPort.range);
		if (pQosFilter[i].is_UDPSrcPort_Available)
			SockPrintf("   UDP Filter Source Port: %d, Range: %d\n", pQosFilter[i].UDPSrcPort.port, pQosFilter[i].UDPSrcPort.range);
		if (pQosFilter[i].is_UDPDstPort_Available)
			SockPrintf("   UDP Filter Destination Port: %d, Range: %d\n", pQosFilter[i].UDPDstPort.port, pQosFilter[i].UDPDstPort.range);
		if (pQosFilter[i].is_EspSpi_Available)
			SockPrintf("   ESP Filter Security Policy Index: %d\n", pQosFilter[i].EspSpi);
		if (pQosFilter[i].is_Precedence_Available)
			SockPrintf("   Filter Precedence: %d\n", pQosFilter[i].Precedence);
		if (pQosFilter[i].is_Id_Available)
			SockPrintf("   Filter ID: %d\n", pQosFilter[i].Id);
		if (pQosFilter[i].is_TranSrcPort_Available)
			SockPrintf("   Transport Protocol Filter Source Port: %d, Range: %d\n", pQosFilter[i].TranSrcPort.port, pQosFilter[i].TranSrcPort.range);
		if (pQosFilter[i].is_TranDstPort_Available)
			SockPrintf("   Transport Protocol Filter Destination Port: %d, Range: %d\n", pQosFilter[i].TranDstPort.port, pQosFilter[i].TranDstPort.range);
	}
}

void DisplayQosEventInd(unpack_qos_SLQSSetQosEventCallback_ind_t* setQosEventCallback)
{
	SockPrintf("QoS Flow Info:\n");

	if (swi_uint256_get_bit(setQosEventCallback->ParamPresenceMask, 0x10))
	{
		SockPrintf(" QoS Flow State:\n  ID: %d\n", setQosEventCallback->pQosFlowInfo->QFlowState.id);
		SockPrintf("  New Flow: %d\n", setQosEventCallback->pQosFlowInfo->QFlowState.isNewFlow);
		SockPrintf("  Global flow reporting state change: %d\n", setQosEventCallback->pQosFlowInfo->QFlowState.state);

		if (setQosEventCallback->pQosFlowInfo->is_TxQFlowGranted_Available)
			OutputSwiQosFlow("Tx", &setQosEventCallback->pQosFlowInfo->TxQFlowGranted);

		if (setQosEventCallback->pQosFlowInfo->is_RxQFlowGranted_Available)
			OutputSwiQosFlow("Rx", &setQosEventCallback->pQosFlowInfo->RxQFlowGranted);

		OutputSwiQosFilter("Tx", setQosEventCallback->pQosFlowInfo->NumTxFilters, setQosEventCallback->pQosFlowInfo->TxQFilter);
		OutputSwiQosFilter("Rx", setQosEventCallback->pQosFlowInfo->NumRxFilters, setQosEventCallback->pQosFlowInfo->RxQFilter);

		if (setQosEventCallback->pQosFlowInfo->is_QosFlowType_Available)
			SockPrintf(" QoS Flow Type: %d\n", setQosEventCallback->pQosFlowInfo->QosFlowType);

		if (setQosEventCallback->pQosFlowInfo->is_BearerID_Available)
			SockPrintf(" QoS Flow Bearer ID: %d\n", setQosEventCallback->pQosFlowInfo->BearerID);

		if (setQosEventCallback->pQosFlowInfo->is_FcSeqNum_Available)
			SockPrintf(" QoS Flow Control Sequence Number: %d\n", setQosEventCallback->pQosFlowInfo->FcSeqNum);
	}

	if (swi_uint256_get_bit(setQosEventCallback->ParamPresenceMask, 0x11))
	{
		SockPrintf("Technology preference: %d\n", setQosEventCallback->pNetworkSupportedQoSProfiles->Tech_pref);
		SockPrintf("Number of profile values: %d\n", setQosEventCallback->pNetworkSupportedQoSProfiles->Profile_count);
		for (int idx = 0; idx < setQosEventCallback->pNetworkSupportedQoSProfiles->Profile_count; ++idx)
			SockPrintf("profile values: %d\n", setQosEventCallback->pNetworkSupportedQoSProfiles->pProfile_value[idx]);
	}
}

void DisplayQosGlobalQosFlowInd(unpack_qos_SLQSQosGlobalQosFlow_ind_t* sQosGlobalQosFlowInd)
{
	if (swi_uint256_get_bit(sQosGlobalQosFlowInd->ParamPresenceMask, 0x01))
	{
		SockPrintf("\nQoS Flow State:\n");
		SockPrintf("QoS identifier= %d\n", sQosGlobalQosFlowInd->pQosFlowStatus->qos_id);
		SockPrintf("new flow= %d\n", sQosGlobalQosFlowInd->pQosFlowStatus->new_flow);
		SockPrintf("Flow state change flow= %d\n", sQosGlobalQosFlowInd->pQosFlowStatus->state_change);
	}
	if (swi_uint256_get_bit(sQosGlobalQosFlowInd->ParamPresenceMask, 0x10))
	{
		SockPrintf("\nTx QoS Flow Granted:\n");
		OutputQosFlowGranted(sQosGlobalQosFlowInd->pTxQosFlowGranted);
	}
	if (swi_uint256_get_bit(sQosGlobalQosFlowInd->ParamPresenceMask, 0x11))
	{
		SockPrintf("\nRx QoS Flow Granted:\n");
		OutputQosFlowGranted(sQosGlobalQosFlowInd->pRxQosFlowGranted);
	}
	if (swi_uint256_get_bit(sQosGlobalQosFlowInd->ParamPresenceMask, 0x12))
	{
		SockPrintf("\nTx QoS Filters:\n");
		OutputQosFilters(sQosGlobalQosFlowInd->pTxQosFilters);
	}
	if (swi_uint256_get_bit(sQosGlobalQosFlowInd->ParamPresenceMask, 0x13))
	{
		SockPrintf("\nRx QoS Filters:\n");
		OutputQosFilters(sQosGlobalQosFlowInd->pRxQosFilters);
	}
	if (swi_uint256_get_bit(sQosGlobalQosFlowInd->ParamPresenceMask, 0x14))
	{
		SockPrintf("Flow_type= %d\n", *sQosGlobalQosFlowInd->pFlow_type);
	}
	if (swi_uint256_get_bit(sQosGlobalQosFlowInd->ParamPresenceMask, 0x15))
	{
		SockPrintf("Bearer_id= %d\n", *sQosGlobalQosFlowInd->pBearer_id);
	}
	if (swi_uint256_get_bit(sQosGlobalQosFlowInd->ParamPresenceMask, 0x16))
	{
		SockPrintf("Fc_seq_num= %d\n", *sQosGlobalQosFlowInd->pFc_seq_num);
	}
	if (swi_uint256_get_bit(sQosGlobalQosFlowInd->ParamPresenceMask, 0x17))
	{
		SockPrintf("Tx_5g_qci= %d\n", *sQosGlobalQosFlowInd->pTx_5g_qci);
	}
	if (swi_uint256_get_bit(sQosGlobalQosFlowInd->ParamPresenceMask, 0x18))
	{
		SockPrintf("Rx_5g_qci= %d\n", *sQosGlobalQosFlowInd->pRx_5g_qci);
	}
	if (swi_uint256_get_bit(sQosGlobalQosFlowInd->ParamPresenceMask, 0x19))
	{
		SockPrintf("Tx_averaging_window= %d\n", *sQosGlobalQosFlowInd->pTx_averaging_window);
	}
	if (swi_uint256_get_bit(sQosGlobalQosFlowInd->ParamPresenceMask, 0x1A))
	{
		SockPrintf("Rx_averaging_window= %d\n", *sQosGlobalQosFlowInd->pRx_averaging_window);
	}
	if (swi_uint256_get_bit(sQosGlobalQosFlowInd->ParamPresenceMask, 0x1B))
	{
		SockPrintf("Number of filter ID= %d\n", sQosGlobalQosFlowInd->pTxFilterMatchAll->tx_filter_match_all_len);
		for (int idx = 0; idx < sQosGlobalQosFlowInd->pTxFilterMatchAll->tx_filter_match_all_len; ++idx)
			SockPrintf("filter ID[%d]= %d\n", idx, sQosGlobalQosFlowInd->pTxFilterMatchAll->filter_id[idx]);
	}
}

void QosIndicationCallback(uint8_t* qmiPacket, uint16_t qmiPacketSize, void* pIndicationCallbackContext)
{	uint16_t msgid = IndicationCallback("QOS", eQOS, qmiPacket, qmiPacketSize, pIndicationCallbackContext);
	int unpackRetCode = 0;

	switch (msgid)
	{
	case eQMI_QOS_EVENT_IND:
	{
		unpack_qos_SLQSSetQosEventCallback_ind_t setQosEventCallback;
		memset(&setQosEventCallback, 0, sizeof(unpack_qos_SLQSSetQosEventCallback_ind_t));
		unpack_qos_QosFlowInfo_t qosFlowInfo;
		memset(&qosFlowInfo, 0, sizeof(unpack_qos_QosFlowInfo_t));
		unpack_qos_EventCallback_t qosEventCallback;
		memset(&qosEventCallback, 0, sizeof(unpack_qos_EventCallback_t));
		uint16_t profile_value[10] = { 0 };
		qosEventCallback.Profile_count = 10;
		qosEventCallback.pProfile_value = profile_value;
		setQosEventCallback.pQosFlowInfo = &qosFlowInfo;
		setQosEventCallback.pNetworkSupportedQoSProfiles = &qosEventCallback;

		unpackRetCode = unpack_qos_SLQSSetQosEventCallback_ind(qmiPacket, qmiPacketSize, &setQosEventCallback);
		LockSocket();
		DisplayResult("unpack_qos_SLQSSetQosEventCallback_ind", unpackRetCode, NULL, (result_func)DisplayQosEventInd, (void*)&setQosEventCallback);
		UnlockSocket();
	}
	break;
	case eQMI_QOS_GLOBAL_QOS_FLOW_IND:
	{
		unpack_qos_QmiCbkQosFlowStatus_t	sQosFlowStatus;
		memset(&sQosFlowStatus, 0, sizeof(unpack_qos_QmiCbkQosFlowStatus_t));
		unpack_qos_QmiCbkQosFlowGranted_t	sTxQosFlowGranted;
		memset(&sTxQosFlowGranted, 0, sizeof(unpack_qos_QmiCbkQosFlowGranted_t));
		unpack_qos_QmiCbkQosFlowGranted_t	sRxQosFlowGranted;
		memset(&sRxQosFlowGranted, 0, sizeof(unpack_qos_QmiCbkQosFlowGranted_t));
		unpack_qos_QmiCbkQosFilters_t		sTxQosFilters;
		memset(&sTxQosFilters, 0, sizeof(unpack_qos_QmiCbkQosFilters_t));
		unpack_qos_QmiCbkQosFilters_t		sRxQosFilters;
		memset(&sRxQosFilters, 0, sizeof(unpack_qos_QmiCbkQosFilters_t));
		uint32_t							nFlow_type = 0;
		uint8_t								nBearer_id = 0;
		uint16_t							nFc_seq_num = 0;
		uint32_t							nTx_5g_qci = 0;
		uint32_t							nRx_5g_qci = 0;
		uint16_t							nTx_averaging_window = 0;
		uint16_t							nRx_averaging_window = 0;
		unpack_qos_QmiCbkQosTxFilterMatchAll_t sTxFilterMatchAll;
		memset(&sTxFilterMatchAll, 0, sizeof(unpack_qos_QmiCbkQosTxFilterMatchAll_t));

		unpack_qos_SLQSQosGlobalQosFlow_ind_t sQosGlobalQosFlowInd;
		sQosGlobalQosFlowInd.pQosFlowStatus = &sQosFlowStatus;
		sQosGlobalQosFlowInd.pTxQosFlowGranted = &sTxQosFlowGranted;
		sQosGlobalQosFlowInd.pRxQosFlowGranted = &sRxQosFlowGranted;
		sQosGlobalQosFlowInd.pTxQosFilters = &sTxQosFilters;
		sQosGlobalQosFlowInd.pRxQosFilters = &sRxQosFilters;
		sQosGlobalQosFlowInd.pFlow_type = &nFlow_type;
		sQosGlobalQosFlowInd.pBearer_id = &nBearer_id;
		sQosGlobalQosFlowInd.pFc_seq_num = &nFc_seq_num;
		sQosGlobalQosFlowInd.pTx_5g_qci = &nTx_5g_qci;
		sQosGlobalQosFlowInd.pRx_5g_qci = &nRx_5g_qci;
		sQosGlobalQosFlowInd.pTx_averaging_window = &nTx_averaging_window;
		sQosGlobalQosFlowInd.pRx_averaging_window = &nRx_averaging_window;
		sQosGlobalQosFlowInd.pTxFilterMatchAll = &sTxFilterMatchAll;

		unpackRetCode = unpack_qos_SLQSQosGlobalQosFlow_ind(qmiPacket, qmiPacketSize, &sQosGlobalQosFlowInd);
		LockSocket();
		DisplayResult("unpack_qos_SLQSQosGlobalQosFlow_ind", unpackRetCode, NULL, (result_func)DisplayQosGlobalQosFlowInd, (void*)&sQosGlobalQosFlowInd);
		UnlockSocket();
	}
	break;
	}
}

/*
 * Name:     qos_enable_qos_event
 *
 * Purpose:  enable/disable QoS events.
 *
 * Params:   None
 *
 * Return:   None.
 *
 * Notes:    None
 */
void qos_enable_qos_event(bool bEnable)
{
	pack_qos_SLQSSetQosEventCallback_t  sPackSetQosEventCallback;
	sPackSetQosEventCallback.global_flow_reporting = bEnable ? 1 : 0;
	sPackSetQosEventCallback.network_supported_qos_profile_change_reporting = bEnable ? 1 : 0;
	sPackSetQosEventCallback.ext_technology_preference = 0x8001;

	unpack_qos_SLQSSetQosEventCallback_t sUnpackSetQosEventCallback;
	sUnpackSetQosEventCallback.Tlvresult = 0;

	int ret = SENDRECEIVE(&s_QosService, pack_qos_SLQSSetQosEventCallback, &sPackSetQosEventCallback, unpack_qos_SLQSSetQosEventCallback, &sUnpackSetQosEventCallback);
	DisplayResult(__FUNCTION__, ret, &sUnpackSetQosEventCallback.ParamPresenceMask, NULL, NULL);
}

void GetQosFlow(pack_qos_QosFlow_t *pQosFlow)
{
	pQosFlow->flow_status = GetNumericValue(NULL, "Current flow status (Activated status=1 (default), Suspended status=2): ", g_enterActionDefault, 1, 1, 2);
	pQosFlow->flow_valid_params = GetNumericValue64(NULL, "Valid parameters mask: ", g_enterActionZero, 0, 0, MAX_UINT64_VALUE_SIZE);
	pQosFlow->ip_flow_trf_cls = GetNumericValue(NULL, "IP traffic class (conversational=0 streaming=1 interactive=2 background=3): ", g_enterActionZero, 0, 0, 3);
	pQosFlow->data_rate_max = GetNumericValue64(NULL, "Maximum required data rate (bits per second): ", g_enterActionZero, 0, 0, MAX_UINT64_VALUE_SIZE);
	pQosFlow->guaranteed_rate = GetNumericValue64(NULL, "Minimum guaranteed data rate (bits per second): ", g_enterActionZero, 0, 0, MAX_UINT64_VALUE_SIZE);
	pQosFlow->peak_rate = GetNumericValue(NULL, "Maximum rate at which data can be transmitted when the token bucket is full (bits per second): ", g_enterActionZero, 0, 0, MAX_INT32_VALUE_SIZE);
	pQosFlow->token_rate = GetNumericValue(NULL, "Rate at which tokens are put in the token bucket (bits per second): ", g_enterActionZero, 0, 0, MAX_INT32_VALUE_SIZE);
	pQosFlow->bucket_size = GetNumericValue(NULL, "Maximum number of tokens that can be accumulated at any instance (bytes): ", g_enterActionZero, 0, 0, MAX_INT32_VALUE_SIZE);
	pQosFlow->ip_flow_latency = GetNumericValue(NULL, "Maximum delay (in milliseconds): ", g_enterActionZero, 0, 0, MAX_INT32_VALUE_SIZE);
	pQosFlow->ip_flow_jitter = GetNumericValue(NULL, "Difference between the maximum and minimum latency (in milliseconds): ", g_enterActionZero, 0, 0, MAX_INT32_VALUE_SIZE);
	pQosFlow->ip_flow_pkt_error_rate_multiplier = GetNumericValue(NULL, "Factor m in calculating packet error rate: E = m*10**(-p): ", g_enterActionZero, 0, 0, MAX_INT32_VALUE_SIZE);
	pQosFlow->ip_flow_pkt_error_rate_exponen = GetNumericValue(NULL, "Factor p in calculating packet error rate: E = m*10**(-p): ", g_enterActionZero, 0, 0, MAX_INT32_VALUE_SIZE);
	pQosFlow->ip_flow_min_policed_packet_size = GetNumericValue(NULL, "Integer that defines the minimum packet size (in bytes) that will be policed for QoS guarantees: ", g_enterActionZero, 0, 0, MAX_INT32_VALUE_SIZE);
	pQosFlow->ip_flow_max_allowed_packet_size = GetNumericValue(NULL, "Integer that defines the maximum packet size (in bytes) allowed in the IP flow: ", g_enterActionZero, 0, 0, MAX_INT32_VALUE_SIZE);
	pQosFlow->ip_flow_3gpp_residual_bit_error_rate = GetNumericValue(NULL, "The undetected BER for each IP flow in the delivered packets (0 to 8): ", g_enterActionZero, 0, 0, 8);
	pQosFlow->ip_flow_3gpp_traffic_handling_priority = GetNumericValue(NULL, "Relative priority of the flow (0 to 3): ", g_enterActionZero, 0, 0, 3);
	pQosFlow->ip_flow_3gpp2_profile_id = GetNumericValue(NULL, "Profile ID shorthand for a defined set of QoS flow parameters (CDMA): ", g_enterActionZero, 0, 0, 16);
	pQosFlow->ip_flow_3gpp2_flow_priority = GetNumericValue(NULL, "Flow priority used by the network (CDMA): ", g_enterActionZero, 0, 0, MAX_INT32_VALUE_SIZE);
	pQosFlow->ip_flow_3gpp_im_cn_flag = GetNumericValue(NULL, "IM CN subsystem signaling flag (0: FALSE (default), 1: TRUE): ", g_enterActionDefault, 0, 0, 1);
	pQosFlow->ip_flow_3gpp_sig_ind = GetNumericValue(NULL, "This parameter applies only to 3GPP networks (0: FALSE (default), 1: TRUE): ", g_enterActionDefault, 0, 0, 1);
	pQosFlow->ip_flow_lte_qci = GetNumericValue(NULL, "QoS Class Identifier (QCI) 0-70: ", g_enterActionZero, 0, 0, 70);
}

void GetQosFilterSpecs(unpack_qos_QosFilterSpecs_t *pQoSFilterSpecs)
{
	char szIPv4v6[MAX_FIELD_SIZE] = { 0 };

	pQoSFilterSpecs->ip_version = GetNumericValue(NULL, "IP family (IPv4=4 (default), IPv6=6): ", g_enterActionDefault, 4, 4, 6);
	pQoSFilterSpecs->ipv4_valid_params = GetNumericValue64(NULL, "valid IPv4 parameters mask (No parameters=0 IPv4 source address=1 IPv4 destination address=2 IPv4 type of service=4): ", g_enterActionZero, 0, 0, 4);
	GetIPFromUser("IPv4 address", szIPv4v6, &pQoSFilterSpecs->ipv4_addr_1);
	GetIPFromUser("IPv4 subnet mask", szIPv4v6, &pQoSFilterSpecs->ipv4_subnet_mask_1);
	GetIPFromUser("IPv4-2 address", szIPv4v6, &pQoSFilterSpecs->ipv4_addr_2);
	GetIPFromUser("IPv4-2 subnet mask", szIPv4v6, &pQoSFilterSpecs->ipv4_subnet_mask_2);
	pQoSFilterSpecs->ipv4_val = GetNumericValue(NULL, "type of IPv4 service value: ", g_enterActionZero, 0, 0, 255);
	pQoSFilterSpecs->ipv4_mask = GetNumericValue(NULL, "Type of IPv4-2service mask: ", g_enterActionZero, 0, 0, 255);
	pQoSFilterSpecs->ipv6_valid_params = GetNumericValue64(NULL, "valid IPv6 parameters mask (No parameters=0 IPv6 source address=2 IPv6 destination address=2  IPv6 traffic class=4 IPv6 flow label=8): ", g_enterActionZero, 0, 0, 8);

	GetIPv6FromUser(szIPv4v6, pQoSFilterSpecs->ipv6_address_1, &pQoSFilterSpecs->ipv6_prefix_len_1);
	pQoSFilterSpecs->ipv6_prefix_len_1 -= 10;
	GetIPv6FromUser(szIPv4v6, pQoSFilterSpecs->ipv6_address_2, &pQoSFilterSpecs->ipv6_prefix_len_2);
	pQoSFilterSpecs->ipv6_prefix_len_2 -= 10;

	pQoSFilterSpecs->ipv6_val = GetNumericValue(NULL, "traffic class value-2: ", g_enterActionZero, 0, 0, 255);
	pQoSFilterSpecs->ipv6_mask = GetNumericValue(NULL, "Traffic class mask-2: ", g_enterActionZero, 0, 0, 255);
	pQoSFilterSpecs->ipv6_flow_label = GetNumericValue(NULL, "IPv6 flow label-2: ", g_enterActionZero, 0, 0, MAX_INT32_VALUE_SIZE);
	char szMessage[512] = { 0 };
	strcpy(szMessage, " xport_protocol:\nNo transport protocol=0\nInternet Control Messaging Protocol=1\nTransmission Control Protocol=6\n");
	strcat(szMessage, "User Datagram Protocol=17\nEncapsulating Security Payload Protocol=50\nAuthentication Header Protocol=51\nInternet Control Messaging Protocol for IPV6=58");
	pQoSFilterSpecs->ipv6_xport_protocol = GetNumericValue(NULL, szMessage, g_enterActionZero, 0, 0, 58);
	pQoSFilterSpecs->port_valid_params_1 = GetNumericValue64(NULL, "valid port info mask (No parameters=0 Source port=1 Destination port=2): ", g_enterActionZero, 0, 0, 4);
	pQoSFilterSpecs->src_port_1 = GetNumericValue(NULL, "source port 1: ", g_enterActionZero, 0, 0, MAX_INT16_VALUE_SIZE);
	pQoSFilterSpecs->src_range_1 = GetNumericValue(NULL, "source range 1: ", g_enterActionZero, 0, 0, MAX_INT16_VALUE_SIZE);
	pQoSFilterSpecs->src_port_1 = GetNumericValue(NULL, "destination port 1: ", g_enterActionZero, 0, 0, MAX_INT16_VALUE_SIZE);
	pQoSFilterSpecs->src_range_1 = GetNumericValue(NULL, "destination range 1: ", g_enterActionZero, 0, 0, MAX_INT16_VALUE_SIZE);
	pQoSFilterSpecs->port_valid_params_2 = GetNumericValue64(NULL, "valid port info mask (No parameters=0 Source port=1 Destination port=2): ", g_enterActionZero, 0, 0, 4);
	pQoSFilterSpecs->src_port_2 = GetNumericValue(NULL, "source port 2: ", g_enterActionZero, 0, 0, MAX_INT16_VALUE_SIZE);
	pQoSFilterSpecs->src_range_2 = GetNumericValue(NULL, "source range 2: ", g_enterActionZero, 0, 0, MAX_INT16_VALUE_SIZE);
	pQoSFilterSpecs->des_port_2 = GetNumericValue(NULL, "destination port 2: ", g_enterActionZero, 0, 0, MAX_INT16_VALUE_SIZE);
	pQoSFilterSpecs->des_range_2 = GetNumericValue(NULL, "destination range 2: ", g_enterActionZero, 0, 0, MAX_INT16_VALUE_SIZE);
	pQoSFilterSpecs->icmp_valid_params = GetNumericValue64(NULL, "valid ICMP filter mask (No parameters=0 Message type=1 Destination Message code=2): ", g_enterActionZero, 0, 0, 4);
	pQoSFilterSpecs->icmp_type = GetNumericValue(NULL, "source port 2: ", g_enterActionZero, 0, 0, 255);
	pQoSFilterSpecs->icmp_code = GetNumericValue(NULL, "source range 2: ", g_enterActionZero, 0, 0, 255);
	pQoSFilterSpecs->ipsec_valid_params = GetNumericValue64(NULL, "valid IPSEC filter mask (No parameters=0 Security parameter index=1): ", g_enterActionZero, 0, 0, 4);
	pQoSFilterSpecs->ipsec_spi = GetNumericValue(NULL, "Security parameter index for IPSec: ", g_enterActionZero, 0, 0, MAX_INT32_VALUE_SIZE);
	pQoSFilterSpecs->ipsec_valid_params_2 = GetNumericValue64(NULL, "valid IPSEC filter mask 2 (No parameters=0 Security parameter index=1): ", g_enterActionZero, 0, 0, 4);
	pQoSFilterSpecs->ipsec_spi_2 = GetNumericValue(NULL, "Security parameter index for IPSec 2: ", g_enterActionZero, 0, 0, MAX_INT32_VALUE_SIZE);
	pQoSFilterSpecs->ipsec_filter_id = GetNumericValue(NULL, "Unique identifier for each filter: ", g_enterActionZero, 0, 0, MAX_INT16_VALUE_SIZE);
	pQoSFilterSpecs->filter_precedence = GetNumericValue(NULL, "the order in which filters are applied: ", g_enterActionZero, 0, 0, MAX_INT16_VALUE_SIZE);
}

void DoInteractiveQosExRequest()
{
	pack_qos_SLQSRequestQosExReq_t sRequestQosExReq;
	memset(&sRequestQosExReq, 0, sizeof(pack_qos_SLQSRequestQosExReq_t));

	do
	{
		char ch[2] = { 0 };
		if (ENTER_KEY == GetStringFromUser(NULL, "'y' if you want to enter Tx QOS Flow Information:", g_enterActionExit, (char*)ch, 2))
			break;

		if (ch[0] == 'y')
		{
			sRequestQosExReq.pTxQosFlowList = calloc(1, sizeof(pack_qos_QosFlowList_t));
			if (sRequestQosExReq.pTxQosFlowList)
			{
				sRequestQosExReq.pTxQosFlowList->pQosFlow = calloc(1, sizeof(pack_qos_QosFlow_t));
				if (sRequestQosExReq.pTxQosFlowList->pQosFlow)
				{
					sRequestQosExReq.pTxQosFlowList->tx_qos_flow_len = 1;
					GetQosFlow(sRequestQosExReq.pTxQosFlowList->pQosFlow);
				}
				else
				{
					free(sRequestQosExReq.pTxQosFlowList);
					sRequestQosExReq.pTxQosFlowList = NULL;
				}
			}
		}

		if (ENTER_KEY == GetStringFromUser(NULL, "'y' if you want to enter Rx QOS Flow Information", g_enterActionExit, (char*)ch, 2))
			break;

		if (ch[0] == 'y')
		{
			sRequestQosExReq.pRxQosFlowList = calloc(1, sizeof(pack_qos_QosFlowList_t));
			if (sRequestQosExReq.pRxQosFlowList)
			{
				sRequestQosExReq.pRxQosFlowList->pQosFlow = calloc(1, sizeof(pack_qos_QosFlow_t));
				if (sRequestQosExReq.pRxQosFlowList->pQosFlow)
				{
					sRequestQosExReq.pRxQosFlowList->tx_qos_flow_len = 1;
					GetQosFlow(sRequestQosExReq.pRxQosFlowList->pQosFlow);
				}
				else
				{
					free(sRequestQosExReq.pRxQosFlowList);
					sRequestQosExReq.pRxQosFlowList = NULL;
				}
			}
		}

		if (ENTER_KEY == GetStringFromUser(NULL, "'y' if you want to enter TX QOS Filter Specs List", g_enterActionExit, (char*)ch, 2))
			break;

		if (ch[0] == 'y')
		{
			sRequestQosExReq.pTxQosFilterSpecsList = calloc(1, sizeof(pack_qos_QosFilterSpecsList_t));
			if (sRequestQosExReq.pTxQosFilterSpecsList)
			{
				sRequestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs = calloc(1, sizeof(unpack_qos_QosFilterSpecs_t));
				if (sRequestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs)
				{
					sRequestQosExReq.pTxQosFilterSpecsList->tx_qos_filter_len = 1;
					GetQosFilterSpecs(sRequestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs);
				}
				else
				{
					free(sRequestQosExReq.pTxQosFilterSpecsList);
					sRequestQosExReq.pTxQosFilterSpecsList = NULL;
				}
			}
		}

		if (ENTER_KEY == GetStringFromUser(NULL, "'y' if you want to enter Rx QoS Filter Specs List", g_enterActionExit, (char*)ch, 2))
			break;

		if (ch[0] == 'y')
		{
			sRequestQosExReq.pRxQosFilterSpecsList = calloc(1, sizeof(pack_qos_QosFilterSpecsList_t));
			if (sRequestQosExReq.pRxQosFilterSpecsList)
			{
				sRequestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs = calloc(1, sizeof(unpack_qos_QosFilterSpecs_t));
				if (sRequestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs)
				{
					sRequestQosExReq.pRxQosFilterSpecsList->tx_qos_filter_len = 1;
					GetQosFilterSpecs(sRequestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs);
				}
				else
				{
					free(sRequestQosExReq.pRxQosFilterSpecsList);
					sRequestQosExReq.pRxQosFilterSpecsList = NULL;
				}
			}
		}

		if (ENTER_KEY == GetStringFromUser(NULL, "'y' if you want to enter Tx 5G QCI", g_enterActionExit, (char*)ch, 2))
			break;

		if (ch[0] == 'y')
		{
			sRequestQosExReq.pTx5GQCI = calloc(1, sizeof(pack_qos_TxRx5GQCI_t));
			if (sRequestQosExReq.pTx5GQCI)
			{
				sRequestQosExReq.pTx5GQCI->pTxRx_5g_qci = calloc(1, sizeof(uint32_t));
				if (sRequestQosExReq.pTx5GQCI->pTxRx_5g_qci)
				{
					sRequestQosExReq.pTx5GQCI->tx_rx_5g_qci_len = 1;
					*sRequestQosExReq.pTx5GQCI->pTxRx_5g_qci = GetNumericValue64(NULL, "5G Tx QoS Class Identifier (QCI): ", g_enterActionZero, 0, 0, MAX_UINT32_VALUE_SIZE);
				}
				else
				{
					free(sRequestQosExReq.pTx5GQCI);
					sRequestQosExReq.pTx5GQCI = NULL;
				}
			}
		}

		if (ENTER_KEY == GetStringFromUser(NULL, "'y' if you want to enter Rx 5G QCI", g_enterActionExit, (char*)ch, 2))
			break;

		if (ch[0] == 'y')
		{
			sRequestQosExReq.pRx5GQCI = calloc(1, sizeof(pack_qos_TxRx5GQCI_t));
			if (sRequestQosExReq.pRx5GQCI)
			{
				sRequestQosExReq.pRx5GQCI->pTxRx_5g_qci = calloc(1, sizeof(uint32_t));
				if (sRequestQosExReq.pRx5GQCI->pTxRx_5g_qci)
				{
					sRequestQosExReq.pRx5GQCI->tx_rx_5g_qci_len = 1;
					*sRequestQosExReq.pRx5GQCI->pTxRx_5g_qci = GetNumericValue64(NULL, "5G Rx QoS Class Identifier (QCI): ", g_enterActionZero, 0, 0, MAX_UINT32_VALUE_SIZE);
				}
				else
				{
					free(sRequestQosExReq.pRx5GQCI);
					sRequestQosExReq.pRx5GQCI = NULL;
				}
			}
		}

		if (ENTER_KEY == GetStringFromUser(NULL, "'y' if you want to enter Tx QoS Averaging Window", g_enterActionExit, (char*)ch, 2))
			break;

		if (ch[0] == 'y')
		{
			sRequestQosExReq.pTxQosAveragingWindow = calloc(1, sizeof(pack_qos_TxRxQosAveragingWindow_t));
			if (sRequestQosExReq.pTxQosAveragingWindow)
			{
				sRequestQosExReq.pTxQosAveragingWindow->pTxRx_averaging_window = calloc(1, sizeof(uint32_t));
				if (sRequestQosExReq.pTxQosAveragingWindow->pTxRx_averaging_window)
				{
					sRequestQosExReq.pTxQosAveragingWindow->tx_averaging_window_len = 1;
					*sRequestQosExReq.pTxQosAveragingWindow->pTxRx_averaging_window = GetNumericValue64(NULL, "duration in ms over which the GFBR and MFBR shall be calculated: ", g_enterActionZero, 0, 0, MAX_UINT32_VALUE_SIZE);
				}
				else
				{
					free(sRequestQosExReq.pTxQosAveragingWindow);
					sRequestQosExReq.pTxQosAveragingWindow = NULL;
				}
			}
		}

		if (ENTER_KEY == GetStringFromUser(NULL, "'y' if you want to enter Rx QoS Averaging Window", g_enterActionExit, (char*)ch, 2))
			break;

		if (ch[0] == 'y')
		{
			sRequestQosExReq.pRxQosAveragingWindow = calloc(1, sizeof(pack_qos_TxRxQosAveragingWindow_t));
			if (sRequestQosExReq.pRxQosAveragingWindow)
			{
				sRequestQosExReq.pRxQosAveragingWindow->pTxRx_averaging_window = calloc(1, sizeof(uint32_t));
				if (sRequestQosExReq.pRxQosAveragingWindow->pTxRx_averaging_window)
				{
					sRequestQosExReq.pRxQosAveragingWindow->tx_averaging_window_len = 1;
					*sRequestQosExReq.pRxQosAveragingWindow->pTxRx_averaging_window = GetNumericValue64(NULL, "duration in ms over which the GFBR and MFBR shall be calculated: ", g_enterActionZero, 0, 0, MAX_UINT32_VALUE_SIZE);
				}
				else
				{
					free(sRequestQosExReq.pRxQosAveragingWindow);
					sRequestQosExReq.pRxQosAveragingWindow = NULL;
				}
			}
		}

		qos_request_qosex(&sRequestQosExReq);
	} while (0);

	if (sRequestQosExReq.pTxQosFlowList)
	{
		free(sRequestQosExReq.pTxQosFlowList->pQosFlow);
		free(sRequestQosExReq.pTxQosFlowList);
	}
	if (sRequestQosExReq.pRxQosFlowList)
	{
		free(sRequestQosExReq.pRxQosFlowList->pQosFlow);
		free(sRequestQosExReq.pRxQosFlowList);
	}
	if (sRequestQosExReq.pTxQosFilterSpecsList)
	{
		free(sRequestQosExReq.pTxQosFilterSpecsList->pQoSFilterSpecs);
		free(sRequestQosExReq.pTxQosFilterSpecsList);
	}
	if (sRequestQosExReq.pRxQosFilterSpecsList)
	{
		free(sRequestQosExReq.pRxQosFilterSpecsList->pQoSFilterSpecs);
		free(sRequestQosExReq.pRxQosFilterSpecsList);
	}
	if (sRequestQosExReq.pTx5GQCI)
	{
		free(sRequestQosExReq.pTx5GQCI->pTxRx_5g_qci);
		free(sRequestQosExReq.pTx5GQCI);
	}
	if (sRequestQosExReq.pRx5GQCI)
	{
		free(sRequestQosExReq.pRx5GQCI->pTxRx_5g_qci);
		free(sRequestQosExReq.pRx5GQCI);
	}
	if (sRequestQosExReq.pTxQosAveragingWindow)
	{
		free(sRequestQosExReq.pTxQosAveragingWindow->pTxRx_averaging_window);
		free(sRequestQosExReq.pTxQosAveragingWindow);
	}
	if (sRequestQosExReq.pRxQosAveragingWindow)
	{
		free(sRequestQosExReq.pRxQosAveragingWindow->pTxRx_averaging_window);
		free(sRequestQosExReq.pRxQosAveragingWindow);
	}
}

void qos_request_qosex(pack_qos_SLQSRequestQosExReq_t* sRequestQosExReq)
{
	unpack_qos_SLQSQosRequestQosExResp_t sQosRequestQosExResp;
	memset(&sQosRequestQosExResp, 0, sizeof(unpack_qos_SLQSQosRequestQosExResp_t));
	uint32_t                   		sQos_id;
	unpack_qos_TxRxQoSFlowParamError   sTxQoSFlowParamError;
	uint32_t arrTx_qos_flow_error[5];
	sTxQoSFlowParamError.tx_rx_qos_flow_error_len = 5;
	sTxQoSFlowParamError.pTxRx_qos_flow_error = arrTx_qos_flow_error;
	unpack_qos_TxRxQoSFlowParamError   sRxQoSFlowParamError;
	uint32_t arrRx_qos_flow_error[5];
	sRxQoSFlowParamError.tx_rx_qos_flow_error_len = 5;
	sRxQoSFlowParamError.pTxRx_qos_flow_error = arrRx_qos_flow_error;

	unpack_qos_TxRxQoSFilterParamError sTxQoSFilterParamError;
	uint32_t arrTx_qos_filter_error[2];
	sTxQoSFilterParamError.tx_rx_qos_filter_error_len = 2;
	sTxQoSFilterParamError.pTxRx_qos_filter_error = arrTx_qos_filter_error;
	unpack_qos_TxRxQoSFilterParamError sRxQoSFilterParamError;
	uint32_t arrRx_qos_filter_error[2];
	sRxQoSFilterParamError.tx_rx_qos_filter_error_len = 2;
	sRxQoSFilterParamError.pTxRx_qos_filter_error = arrRx_qos_filter_error;

	sQosRequestQosExResp.pQos_id = &sQos_id;
	sQosRequestQosExResp.pTxQoSFlowParamError = &sTxQoSFlowParamError;
	sQosRequestQosExResp.pRxQoSFlowParamError = &sRxQoSFlowParamError;
	sQosRequestQosExResp.pTxQoSFilterParamError = &sTxQoSFilterParamError;
	sQosRequestQosExResp.pRxQoSFilterParamError = &sRxQoSFilterParamError;

	int rtn = SENDRECEIVE(&s_QosService, pack_qos_SLQSQosExRequest, sRequestQosExReq, unpack_qos_SLQSQosExRequest, &sQosRequestQosExResp);
	DisplayResult(__FUNCTION__, rtn, &sQosRequestQosExResp.ParamPresenceMask, NULL, NULL);
}

/*
 * Name:     displayQosInformation
 *
 * Purpose:  Display quality os service information on a data call.
 *
 * Params:   None
 *
 * Return:   None
 *
 * Notes:    None
 */
void displayQosInformation(unpack_qos_SLQSQosGetQosInfo_t *pQosGetQosInfo)
{
	SockPrintf("\n  QOS Information\n\n");

	if (pQosGetQosInfo->pFlow_status && swi_uint256_get_bit(pQosGetQosInfo->ParamPresenceMask, 0x10))
	{
		SockPrintf("      Flow status: %d\n", *pQosGetQosInfo->pFlow_status);
	}
	if (pQosGetQosInfo->pTxQosGrantedFlow && swi_uint256_get_bit(pQosGetQosInfo->ParamPresenceMask, 0x11))
	{
		SockPrintf("\n  TX QOS Granted Flow\n\n");
		SockPrintf("      Flow status: %d\n", pQosGetQosInfo->pTxQosGrantedFlow->flow_status);
		SockPrintf("      Flow valid params: 0x%"PRIX64"\n", pQosGetQosInfo->pTxQosGrantedFlow->flow_valid_params);
		SockPrintf("      Requested traffic class: %d\n", pQosGetQosInfo->pTxQosGrantedFlow->ip_flow_trf_cls);
		SockPrintf("      Data rate max: %"PRIX64" bits per second\n", pQosGetQosInfo->pTxQosGrantedFlow->data_rate_max);
		SockPrintf("      Guaranteed rate: %"PRIX64" bits per second\n", pQosGetQosInfo->pTxQosGrantedFlow->guaranteed_rate);
		SockPrintf("      Peak rate: %d\n", pQosGetQosInfo->pTxQosGrantedFlow->peak_rate);
		SockPrintf("      Token rate: %d\n", pQosGetQosInfo->pTxQosGrantedFlow->token_rate);
		SockPrintf("      Bucket size: %d\n", pQosGetQosInfo->pTxQosGrantedFlow->bucket_size);
		SockPrintf("      Maximum delay (in milliseconds): %d\n", pQosGetQosInfo->pTxQosGrantedFlow->ip_flow_latency);
		SockPrintf("      IP flow jitter: %d\n", pQosGetQosInfo->pTxQosGrantedFlow->ip_flow_jitter);
		SockPrintf("      IP flow pkt error rate_multiplier: %d\n", pQosGetQosInfo->pTxQosGrantedFlow->ip_flow_pkt_error_rate_multiplier);
		SockPrintf("      IP flow pkt error rate exponen: %d\n", pQosGetQosInfo->pTxQosGrantedFlow->ip_flow_pkt_error_rate_exponen);
		SockPrintf("      IP flow min policed packet size: %d\n", pQosGetQosInfo->pTxQosGrantedFlow->ip_flow_min_policed_packet_size);
		SockPrintf("      IP flow max allowed packet size: %d\n", pQosGetQosInfo->pTxQosGrantedFlow->ip_flow_max_allowed_packet_size);
		SockPrintf("      IP flow 3gpp residual bit error rate: %d\n", pQosGetQosInfo->pTxQosGrantedFlow->ip_flow_3gpp_residual_bit_error_rate);
		SockPrintf("      IP flow 3gpp traffic handling priority: %d\n", pQosGetQosInfo->pTxQosGrantedFlow->ip_flow_3gpp_traffic_handling_priority);
		SockPrintf("      IP flow 3gpp2 profile id: %d\n", pQosGetQosInfo->pTxQosGrantedFlow->ip_flow_3gpp2_profile_id);
		SockPrintf("      IP flow 3gpp2 flow priority: %d\n", pQosGetQosInfo->pTxQosGrantedFlow->ip_flow_3gpp2_flow_priority);
		SockPrintf("      IP flow 3gpp im cn flag: %d\n", pQosGetQosInfo->pTxQosGrantedFlow->ip_flow_3gpp_im_cn_flag);
		SockPrintf("      IP flow 3gpp sig ind: %d\n", pQosGetQosInfo->pTxQosGrantedFlow->ip_flow_3gpp_sig_ind);
		SockPrintf("      IP flow lte qci: %d\n", pQosGetQosInfo->pTxQosGrantedFlow->ip_flow_lte_qci);
	}
	if (pQosGetQosInfo->pRxQosGrantedFlow && swi_uint256_get_bit(pQosGetQosInfo->ParamPresenceMask, 0x12))
	{
		SockPrintf("\n  Rx QOS Granted Flow\n\n");
		SockPrintf("      Flow status: %d\n", pQosGetQosInfo->pRxQosGrantedFlow->flow_status);
		SockPrintf("      Flow valid params: 0x%"PRIX64"\n", pQosGetQosInfo->pRxQosGrantedFlow->flow_valid_params);
		SockPrintf("      Requested traffic class: %d\n", pQosGetQosInfo->pRxQosGrantedFlow->ip_flow_trf_cls);
		SockPrintf("      Data rate max: %"PRIX64" bits per second\n", pQosGetQosInfo->pRxQosGrantedFlow->data_rate_max);
		SockPrintf("      Guaranteed rate: %"PRIX64" bits per second\n", pQosGetQosInfo->pRxQosGrantedFlow->guaranteed_rate);
		SockPrintf("      Peak rate: %d\n", pQosGetQosInfo->pRxQosGrantedFlow->peak_rate);
		SockPrintf("      Token rate: %d\n", pQosGetQosInfo->pRxQosGrantedFlow->token_rate);
		SockPrintf("      Bucket size: %d\n", pQosGetQosInfo->pRxQosGrantedFlow->bucket_size);
		SockPrintf("      Maximum delay (in milliseconds): %d\n", pQosGetQosInfo->pRxQosGrantedFlow->ip_flow_latency);
		SockPrintf("      IP flow jitter: %d\n", pQosGetQosInfo->pRxQosGrantedFlow->ip_flow_jitter);
		SockPrintf("      IP flow pkt error rate_multiplier: %d\n", pQosGetQosInfo->pRxQosGrantedFlow->ip_flow_pkt_error_rate_multiplier);
		SockPrintf("      IP flow pkt error rate exponen: %d\n", pQosGetQosInfo->pRxQosGrantedFlow->ip_flow_pkt_error_rate_exponen);
		SockPrintf("      IP flow min policed packet size: %d\n", pQosGetQosInfo->pRxQosGrantedFlow->ip_flow_min_policed_packet_size);
		SockPrintf("      IP flow max allowed packet size: %d\n", pQosGetQosInfo->pRxQosGrantedFlow->ip_flow_max_allowed_packet_size);
		SockPrintf("      IP flow 3gpp residual bit error rate: %d\n", pQosGetQosInfo->pRxQosGrantedFlow->ip_flow_3gpp_residual_bit_error_rate);
		SockPrintf("      IP flow 3gpp traffic handling priority: %d\n", pQosGetQosInfo->pRxQosGrantedFlow->ip_flow_3gpp_traffic_handling_priority);
		SockPrintf("      IP flow 3gpp2 profile id: %d\n", pQosGetQosInfo->pRxQosGrantedFlow->ip_flow_3gpp2_profile_id);
		SockPrintf("      IP flow 3gpp2 flow priority: %d\n", pQosGetQosInfo->pRxQosGrantedFlow->ip_flow_3gpp2_flow_priority);
		SockPrintf("      IP flow 3gpp im cn flag: %d\n", pQosGetQosInfo->pRxQosGrantedFlow->ip_flow_3gpp_im_cn_flag);
		SockPrintf("      IP flow 3gpp sig ind: %d\n", pQosGetQosInfo->pRxQosGrantedFlow->ip_flow_3gpp_sig_ind);
		SockPrintf("      IP flow lte qci: %d\n", pQosGetQosInfo->pRxQosGrantedFlow->ip_flow_lte_qci);
	}
	if (pQosGetQosInfo->pTxQosFilterSpecs && swi_uint256_get_bit(pQosGetQosInfo->ParamPresenceMask, 0x13))
	{
		SockPrintf("\n  TX QOS Filter Specs\n\n");
		SockPrintf("    TX QOS filter len: %d\n", pQosGetQosInfo->pTxQosFilterSpecs->tx_qos_filter_len);
		for (int idx = 0; idx < pQosGetQosInfo->pTxQosFilterSpecs->tx_qos_filter_len; ++idx)
		{
			SockPrintf("    \nTX QOS filter[%d]:\n", idx);
			SockPrintf("    IP version: %d\n", pQosGetQosInfo->pTxQosFilterSpecs->pQoSFilterSpecs[idx].ip_version);
			SockPrintf("    ipv4_valid_params: 0x%"PRIX64"\n", pQosGetQosInfo->pTxQosFilterSpecs->pQoSFilterSpecs[idx].ipv4_valid_params);
			SockPrintf("    ipv4_addr_1: %d\n", pQosGetQosInfo->pTxQosFilterSpecs->pQoSFilterSpecs[idx].ipv4_addr_1);
			SockPrintf("    ipv4_subnet_mask_1: %d\n", pQosGetQosInfo->pTxQosFilterSpecs->pQoSFilterSpecs[idx].ipv4_subnet_mask_1);
			SockPrintf("    ipv4_addr_2: %d\n", pQosGetQosInfo->pTxQosFilterSpecs->pQoSFilterSpecs[idx].ipv4_addr_2);
			SockPrintf("    ipv4_subnet_mask_2: %d\n", pQosGetQosInfo->pTxQosFilterSpecs->pQoSFilterSpecs[idx].ipv4_subnet_mask_2);
			SockPrintf("    ipv4_val: %d\n", pQosGetQosInfo->pTxQosFilterSpecs->pQoSFilterSpecs[idx].ipv4_val);
			SockPrintf("    ipv4_mask: %d\n", pQosGetQosInfo->pTxQosFilterSpecs->pQoSFilterSpecs[idx].ipv4_mask);
			SockPrintf("    ipv6_valid_params: 0x%"PRIX64"\n", pQosGetQosInfo->pTxQosFilterSpecs->pQoSFilterSpecs[idx].ipv6_valid_params);
			SockPrintf("    ipv6_prefix_len_1: %d\n", pQosGetQosInfo->pTxQosFilterSpecs->pQoSFilterSpecs[idx].ipv6_prefix_len_1);
			for (int idx = 0; idx < pQosGetQosInfo->pTxQosFilterSpecs->pQoSFilterSpecs[idx].ipv6_prefix_len_1; ++idx)
				SockPrintf("%d:", pQosGetQosInfo->pTxQosFilterSpecs->pQoSFilterSpecs[idx].ipv6_address_1[idx]);
			SockPrintf("    ipv6_prefix_len_2: %d\n", pQosGetQosInfo->pTxQosFilterSpecs->pQoSFilterSpecs[idx].ipv6_prefix_len_2);
			for (int idx = 0; idx < pQosGetQosInfo->pTxQosFilterSpecs->pQoSFilterSpecs[idx].ipv6_prefix_len_2; ++idx)
				SockPrintf("%d:", pQosGetQosInfo->pTxQosFilterSpecs->pQoSFilterSpecs[idx].ipv6_address_2[idx]);
			SockPrintf("    ipv6_val: %d\n", pQosGetQosInfo->pTxQosFilterSpecs->pQoSFilterSpecs[idx].ipv6_val);
			SockPrintf("    ipv6_mask: %d\n", pQosGetQosInfo->pTxQosFilterSpecs->pQoSFilterSpecs[idx].ipv6_mask);
			SockPrintf("    ipv6_flow_label: %d\n", pQosGetQosInfo->pTxQosFilterSpecs->pQoSFilterSpecs[idx].ipv6_flow_label);
			SockPrintf("    ipv6_xport_protocol: %d\n", pQosGetQosInfo->pTxQosFilterSpecs->pQoSFilterSpecs[idx].ipv6_xport_protocol);
			SockPrintf("    port_valid_params_1: 0x%"PRIX64"\n", pQosGetQosInfo->pTxQosFilterSpecs->pQoSFilterSpecs[idx].port_valid_params_1);
			SockPrintf("    src_port_1: %d\n", pQosGetQosInfo->pTxQosFilterSpecs->pQoSFilterSpecs[idx].src_port_1);
			SockPrintf("    src_range_1: %d\n", pQosGetQosInfo->pTxQosFilterSpecs->pQoSFilterSpecs[idx].src_range_1);
			SockPrintf("    des_port_1: %d\n", pQosGetQosInfo->pTxQosFilterSpecs->pQoSFilterSpecs[idx].des_port_1);
			SockPrintf("    des_range_1: %d\n", pQosGetQosInfo->pTxQosFilterSpecs->pQoSFilterSpecs[idx].des_range_1);
			SockPrintf("    port_valid_params_2: 0x%"PRIX64"\n", pQosGetQosInfo->pTxQosFilterSpecs->pQoSFilterSpecs[idx].port_valid_params_2);
			SockPrintf("    src_port_2: %d\n", pQosGetQosInfo->pTxQosFilterSpecs->pQoSFilterSpecs[idx].src_port_2);
			SockPrintf("    src_range_2: %d\n", pQosGetQosInfo->pTxQosFilterSpecs->pQoSFilterSpecs[idx].src_range_2);
			SockPrintf("    des_port_2: %d\n", pQosGetQosInfo->pTxQosFilterSpecs->pQoSFilterSpecs[idx].des_port_2);
			SockPrintf("    des_range_2: %d\n", pQosGetQosInfo->pTxQosFilterSpecs->pQoSFilterSpecs[idx].des_range_2);
			SockPrintf("    icmp_valid_params: 0x%"PRIX64"\n", pQosGetQosInfo->pTxQosFilterSpecs->pQoSFilterSpecs[idx].icmp_valid_params);
			SockPrintf("    icmp_type: %d\n", pQosGetQosInfo->pTxQosFilterSpecs->pQoSFilterSpecs[idx].icmp_type);
			SockPrintf("    icmp_code: %d\n", pQosGetQosInfo->pTxQosFilterSpecs->pQoSFilterSpecs[idx].icmp_code);
			SockPrintf("    ipsec_valid_params: 0x%"PRIX64"\n", pQosGetQosInfo->pTxQosFilterSpecs->pQoSFilterSpecs[idx].ipsec_valid_params);
			SockPrintf("    ipsec_spi: %d\n", pQosGetQosInfo->pTxQosFilterSpecs->pQoSFilterSpecs[idx].ipsec_spi);
			SockPrintf("    ipsec_valid_params_2: 0x%"PRIX64"\n", pQosGetQosInfo->pTxQosFilterSpecs->pQoSFilterSpecs[idx].ipsec_valid_params_2);
			SockPrintf("    ipsec_spi_2: %d\n", pQosGetQosInfo->pTxQosFilterSpecs->pQoSFilterSpecs[idx].ipsec_spi_2);
			SockPrintf("    ipsec_filter_id: %d\n", pQosGetQosInfo->pTxQosFilterSpecs->pQoSFilterSpecs[idx].ipsec_filter_id);
			SockPrintf("    filter_precedence: %d\n", pQosGetQosInfo->pTxQosFilterSpecs->pQoSFilterSpecs[idx].filter_precedence);
		}
	}
	if (pQosGetQosInfo->pRxQosFilterSpecs && swi_uint256_get_bit(pQosGetQosInfo->ParamPresenceMask, 0x14))
	{
		SockPrintf("\n  RX QOS Filter Specs\n\n");
		SockPrintf("    RX QOS filter len: %d\n", pQosGetQosInfo->pRxQosFilterSpecs->tx_qos_filter_len);
		for (int idx = 0; idx < pQosGetQosInfo->pRxQosFilterSpecs->tx_qos_filter_len; ++idx)
		{
			SockPrintf("    \nRX QOS filter[%d]: \n", idx);
			SockPrintf("    IP version: %d\n", pQosGetQosInfo->pRxQosFilterSpecs->pQoSFilterSpecs[idx].ip_version);
			SockPrintf("    ipv4_valid_params: 0x%"PRIX64"\n", pQosGetQosInfo->pRxQosFilterSpecs->pQoSFilterSpecs[idx].ipv4_valid_params);
			SockPrintf("    ipv4_addr_1: %d\n", pQosGetQosInfo->pRxQosFilterSpecs->pQoSFilterSpecs[idx].ipv4_addr_1);
			SockPrintf("    ipv4_subnet_mask_1: %d\n", pQosGetQosInfo->pRxQosFilterSpecs->pQoSFilterSpecs[idx].ipv4_subnet_mask_1);
			SockPrintf("    ipv4_addr_2: %d\n", pQosGetQosInfo->pRxQosFilterSpecs->pQoSFilterSpecs[idx].ipv4_addr_2);
			SockPrintf("    ipv4_subnet_mask_2: %d\n", pQosGetQosInfo->pRxQosFilterSpecs->pQoSFilterSpecs[idx].ipv4_subnet_mask_2);
			SockPrintf("    ipv4_val: %d\n", pQosGetQosInfo->pRxQosFilterSpecs->pQoSFilterSpecs[idx].ipv4_val);
			SockPrintf("    ipv4_mask: %d\n", pQosGetQosInfo->pRxQosFilterSpecs->pQoSFilterSpecs[idx].ipv4_mask);
			SockPrintf("    ipv6_valid_params: 0x%"PRIX64"\n", pQosGetQosInfo->pRxQosFilterSpecs->pQoSFilterSpecs[idx].ipv6_valid_params);
			SockPrintf("    ipv6_prefix_len_1: %d\n", pQosGetQosInfo->pRxQosFilterSpecs->pQoSFilterSpecs[idx].ipv6_prefix_len_1);
			for (int idx = 0; idx < pQosGetQosInfo->pRxQosFilterSpecs->pQoSFilterSpecs[idx].ipv6_prefix_len_1; ++idx)
				SockPrintf("%d:", pQosGetQosInfo->pRxQosFilterSpecs->pQoSFilterSpecs[idx].ipv6_address_1[idx]);
			SockPrintf("    ipv6_prefix_len_2: %d\n", pQosGetQosInfo->pRxQosFilterSpecs->pQoSFilterSpecs[idx].ipv6_prefix_len_2);
			for (int idx = 0; idx < pQosGetQosInfo->pRxQosFilterSpecs->pQoSFilterSpecs[idx].ipv6_prefix_len_2; ++idx)
				SockPrintf("%d:", pQosGetQosInfo->pRxQosFilterSpecs->pQoSFilterSpecs[idx].ipv6_address_2[idx]);
			SockPrintf("    ipv6_val: %d\n", pQosGetQosInfo->pRxQosFilterSpecs->pQoSFilterSpecs[idx].ipv6_val);
			SockPrintf("    ipv6_mask: %d\n", pQosGetQosInfo->pRxQosFilterSpecs->pQoSFilterSpecs[idx].ipv6_mask);
			SockPrintf("    ipv6_flow_label: %d\n", pQosGetQosInfo->pRxQosFilterSpecs->pQoSFilterSpecs[idx].ipv6_flow_label);
			SockPrintf("    ipv6_xport_protocol: %d\n", pQosGetQosInfo->pRxQosFilterSpecs->pQoSFilterSpecs[idx].ipv6_xport_protocol);
			SockPrintf("    port_valid_params_1: 0x%"PRIX64"\n", pQosGetQosInfo->pRxQosFilterSpecs->pQoSFilterSpecs[idx].port_valid_params_1);
			SockPrintf("    src_port_1: %d\n", pQosGetQosInfo->pRxQosFilterSpecs->pQoSFilterSpecs[idx].src_port_1);
			SockPrintf("    src_range_1: %d\n", pQosGetQosInfo->pRxQosFilterSpecs->pQoSFilterSpecs[idx].src_range_1);
			SockPrintf("    des_port_1: %d\n", pQosGetQosInfo->pRxQosFilterSpecs->pQoSFilterSpecs[idx].des_port_1);
			SockPrintf("    des_range_1: %d\n", pQosGetQosInfo->pRxQosFilterSpecs->pQoSFilterSpecs[idx].des_range_1);
			SockPrintf("    port_valid_params_2: 0x%"PRIX64"\n", pQosGetQosInfo->pRxQosFilterSpecs->pQoSFilterSpecs[idx].port_valid_params_2);
			SockPrintf("    src_port_2: %d\n", pQosGetQosInfo->pRxQosFilterSpecs->pQoSFilterSpecs[idx].src_port_2);
			SockPrintf("    src_range_2: %d\n", pQosGetQosInfo->pRxQosFilterSpecs->pQoSFilterSpecs[idx].src_range_2);
			SockPrintf("    des_port_2: %d\n", pQosGetQosInfo->pRxQosFilterSpecs->pQoSFilterSpecs[idx].des_port_2);
			SockPrintf("    des_range_2: %d\n", pQosGetQosInfo->pRxQosFilterSpecs->pQoSFilterSpecs[idx].des_range_2);
			SockPrintf("    icmp_valid_params: 0x%"PRIX64"\n", pQosGetQosInfo->pRxQosFilterSpecs->pQoSFilterSpecs[idx].icmp_valid_params);
			SockPrintf("    icmp_type: %d\n", pQosGetQosInfo->pRxQosFilterSpecs->pQoSFilterSpecs[idx].icmp_type);
			SockPrintf("    icmp_code: %d\n", pQosGetQosInfo->pRxQosFilterSpecs->pQoSFilterSpecs[idx].icmp_code);
			SockPrintf("    ipsec_valid_params: 0x%"PRIX64"\n", pQosGetQosInfo->pRxQosFilterSpecs->pQoSFilterSpecs[idx].ipsec_valid_params);
			SockPrintf("    ipsec_spi: %d\n", pQosGetQosInfo->pRxQosFilterSpecs->pQoSFilterSpecs[idx].ipsec_spi);
			SockPrintf("    ipsec_valid_params_2: 0x%"PRIX64"\n", pQosGetQosInfo->pRxQosFilterSpecs->pQoSFilterSpecs[idx].ipsec_valid_params_2);
			SockPrintf("    ipsec_spi_2: %d\n", pQosGetQosInfo->pRxQosFilterSpecs->pQoSFilterSpecs[idx].ipsec_spi_2);
			SockPrintf("    ipsec_filter_id: %d\n", pQosGetQosInfo->pRxQosFilterSpecs->pQoSFilterSpecs[idx].ipsec_filter_id);
			SockPrintf("    filter_precedence: %d\n", pQosGetQosInfo->pRxQosFilterSpecs->pQoSFilterSpecs[idx].filter_precedence);
		}
	}
	if (pQosGetQosInfo->pExt_error_info && swi_uint256_get_bit(pQosGetQosInfo->ParamPresenceMask, 0x15))
	{
		SockPrintf("\n  Extended Error Info\n\n");
		SockPrintf("      Ext_error_info: %d\n", *pQosGetQosInfo->pExt_error_info);
	}
	if (pQosGetQosInfo->pTx_5g_qci && swi_uint256_get_bit(pQosGetQosInfo->ParamPresenceMask, 0x16))
	{
		SockPrintf("\n  Tx 5G QCI\n\n");
		SockPrintf("      Tx_5g_qci: %d\n", *pQosGetQosInfo->pTx_5g_qci);
	}
	if (pQosGetQosInfo->pRx_5g_qci && swi_uint256_get_bit(pQosGetQosInfo->ParamPresenceMask, 0x17))
	{
		SockPrintf("\n  Rx 5G QCI\n\n");
		SockPrintf("      Rx_5g_qci: %d\n", *pQosGetQosInfo->pRx_5g_qci);
	}
	if (pQosGetQosInfo->pTx_averaging_window && swi_uint256_get_bit(pQosGetQosInfo->ParamPresenceMask, 0x18))
	{
		SockPrintf("\n  TX QoS Averaging Window\n\n");
		SockPrintf("      TX_averaging_window: %d\n", *pQosGetQosInfo->pTx_averaging_window);
	}
	if (pQosGetQosInfo->pRx_averaging_window && swi_uint256_get_bit(pQosGetQosInfo->ParamPresenceMask, 0x19))
	{
		SockPrintf("\n  RX QoS Averaging Window\n\n");
		SockPrintf("      RX_averaging_window: %d\n", *pQosGetQosInfo->pRx_averaging_window);
	}
	if (pQosGetQosInfo->pTxFilterMatchAll && swi_uint256_get_bit(pQosGetQosInfo->ParamPresenceMask, 0x1A))
	{
		SockPrintf("\n  Tx Filter Match All\n\n");
		SockPrintf("      tx_filter_match_all_len: %d\n", pQosGetQosInfo->pTxFilterMatchAll->tx_filter_match_all_len);
		for (int idx = 0; idx < pQosGetQosInfo->pTxFilterMatchAll->tx_filter_match_all_len; ++idx)
			SockPrintf("      filter_id[%d]: %d\n", idx, pQosGetQosInfo->pTxFilterMatchAll->pfilter_id[idx]);
	}
}

void GetQosGetQosInfoParams(uint32_t* qosIdentifier)
{
	*qosIdentifier = GetNumericValue(NULL, "Identifier for the QoS flow/instance that has been negotiated and that is being queried", g_enterActionExit, 1001, 0, 1000);
}

void GetQosApnId(uint32_t * qosIdentifier)
{
	*qosIdentifier = GetNumericValue(NULL, "Identifier of the profile for the APN that is being queried", g_enterActionExit, 1001, 0, 1000);
}

/*
 * Name:     qos_get_qosinfo
 *
 * Purpose:  retrieve QoS Information.
 *
 * Params:   None
 *
 * Return:   None.
 *
 * Notes:    None
 */
void qos_get_qosinfo(uint32_t qosIdentifier)
{
	/* If only <ENTER> is pressed by the user, return to main menu */
	if (1001 == qosIdentifier)
		return;

	pack_qos_SLQSQosGetQosInfo_t   sPackQosGetQosInfo;
	sPackQosGetQosInfo.qosIdentifier = qosIdentifier;
	unpack_qos_SLQSQosGetQosInfo_t sUnpackQosGetQosInfo;
	memset(&sUnpackQosGetQosInfo, 0, sizeof(unpack_qos_SLQSQosGetQosInfo_t));
	uint8_t                         flow_status = 0;
	unpack_qos_QosFlow_t            txQosGrantedFlow;
	memset(&txQosGrantedFlow, 0, sizeof(unpack_qos_QosFlow_t));
	unpack_qos_QosFlow_t            rxQosGrantedFlow;
	memset(&rxQosGrantedFlow, 0, sizeof(unpack_qos_QosFlow_t));

	unpack_qos_QosFilterSpecsList_t   txQosFilterSpecs;
	unpack_qos_QosFilterSpecs_t arrTxQoSFilterSpecs[16];
	memset(arrTxQoSFilterSpecs, 0, sizeof(arrTxQoSFilterSpecs));
	txQosFilterSpecs.tx_qos_filter_len = 16;
	txQosFilterSpecs.pQoSFilterSpecs = arrTxQoSFilterSpecs;

	unpack_qos_QosFilterSpecsList_t   rxQosFilterSpecs;
	unpack_qos_QosFilterSpecs_t arrRxQoSFilterSpecs[16];
	memset(arrRxQoSFilterSpecs, 0, sizeof(arrRxQoSFilterSpecs));
	rxQosFilterSpecs.tx_qos_filter_len = 16;
	rxQosFilterSpecs.pQoSFilterSpecs = arrRxQoSFilterSpecs;

	uint16_t                        ext_error_info = 0;
	uint32_t                        tx_5g_qci = 0;
	uint32_t                        rx_5g_qci = 0;
	uint16_t                        tx_averaging_window = 0;
	uint16_t                        rx_averaging_window = 0;

	unpack_qos_TxFilterMatchAll_t   txFilterMatchAll;
	uint16_t arrfilter_id[16];
	txFilterMatchAll.tx_filter_match_all_len = 16;
	txFilterMatchAll.pfilter_id = arrfilter_id;

	sUnpackQosGetQosInfo.pFlow_status = &flow_status;
	sUnpackQosGetQosInfo.pTxQosGrantedFlow = &txQosGrantedFlow;
	sUnpackQosGetQosInfo.pRxQosGrantedFlow = &rxQosGrantedFlow;
	sUnpackQosGetQosInfo.pTxQosFilterSpecs = &txQosFilterSpecs;
	sUnpackQosGetQosInfo.pRxQosFilterSpecs = &rxQosFilterSpecs;
	sUnpackQosGetQosInfo.pExt_error_info = &ext_error_info;
	sUnpackQosGetQosInfo.pTx_5g_qci = &tx_5g_qci;
	sUnpackQosGetQosInfo.pRx_5g_qci = &rx_5g_qci;
	sUnpackQosGetQosInfo.pTx_averaging_window = &tx_averaging_window;
	sUnpackQosGetQosInfo.pRx_averaging_window = &rx_averaging_window;
	sUnpackQosGetQosInfo.pTxFilterMatchAll = &txFilterMatchAll;

	int rtn = SENDRECEIVE(&s_QosService, pack_qos_SLQSQosGetQosInfo, &sPackQosGetQosInfo, unpack_qos_SLQSQosGetQosInfo, &sUnpackQosGetQosInfo);
	DisplayResult(__FUNCTION__, rtn, &sUnpackQosGetQosInfo.ParamPresenceMask, (result_func)displayQosInformation, (void*)&sUnpackQosGetQosInfo);
}

void GetQosIndicationRegisterParams(struct qosIndicationRegisterParams* pParams)
{
	pParams->Report_global_qos_flows = GetNumericValue(NULL, "Report Global QOS Flows (0: Do not report (default), 1: Report global QOS flows)", g_enterActionDefault, ENTER_KEY_PRESSED, 0, 1);
	pParams->Suppress_report_flow_control = GetNumericValue(NULL, "Suppress Report Flow Control (0: Report flow control events (default), 1: Do not report flow control events)", g_enterActionDefault, ENTER_KEY_PRESSED, 0, 1);
	pParams->Suppress_network_status_ind = GetNumericValue(NULL, "Suppress Network Status Indication (0: Do not suppress network status indication (default), 1: Suppress network status indication)", g_enterActionDefault, ENTER_KEY_PRESSED, 0, 1);
}

/*
 * Name:     qos_indicationregister
 *
 * Purpose:  QOS indication register.
 *
 * Params:   None
 *
 * Return:   None.
 *
 * Notes:    None
 */
void qos_indicationregister(struct qosIndicationRegisterParams* pParams)
{
	pack_qos_SLQSQosIndicationRegister_t sPackIndicationRegister;
	memset(&sPackIndicationRegister, 0, sizeof(pack_qos_SLQSQosIndicationRegister_t));
	if (pParams->Report_global_qos_flows != ENTER_KEY)
		sPackIndicationRegister.pReport_global_qos_flows = &pParams->Report_global_qos_flows;
	if (pParams->Suppress_report_flow_control != ENTER_KEY)
		sPackIndicationRegister.pSuppress_report_flow_control = &pParams->Suppress_report_flow_control;
	if (pParams->Suppress_network_status_ind != ENTER_KEY)
		sPackIndicationRegister.pSuppress_network_status_ind = &pParams->Suppress_network_status_ind;

	unpack_qos_SLQSQosIndicationRegister_t sUnpackIndicationRegister;
	memset(&sUnpackIndicationRegister, 0, sizeof(unpack_qos_SLQSQosIndicationRegister_t));

	int rtn = SENDRECEIVE(&s_QosService, pack_qos_SLQSQosIndicationRegister, &sPackIndicationRegister, unpack_qos_SLQSQosIndicationRegister, &sUnpackIndicationRegister);
	DisplayResult(__FUNCTION__, rtn, &sUnpackIndicationRegister.ParamPresenceMask, NULL, NULL);
}

void displayQosReadDatastats(unpack_qos_SLQSQosSwiReadDataStats_t * output)
{
	SockPrintf("APN ID            : %d\n", output->apnId);
	SockPrintf("total_tx_pkt      : %d\n", output->total_tx_pkt);
	SockPrintf("total_tx_pkt_drp  : %d\n", output->total_tx_pkt_drp);
	SockPrintf("total_rx_pkt      : %d\n", output->total_rx_pkt);
	SockPrintf("total_tx_bytes    : %ju\n", output->total_tx_bytes);
	SockPrintf("toal_tx_bytes_drp : %ju\n", output->total_tx_bytes_drp);
	SockPrintf("total_rx_bytes    : %ju\n", output->total_rx_bytes);
	SockPrintf("Number of flows   : %d\n", output->numQosFlow);
	for (unsigned long i = 0; i < output->numQosFlow; i++)
	{
		SockPrintf("\tbearerId     : %u\n", output->qosFlow[i].bearerId);
		SockPrintf("\ttx_pkt       : %u\n", output->qosFlow[i].tx_pkt);
		SockPrintf("\ttx_pkt_drp   : %u\n", output->qosFlow[i].tx_pkt_drp);
		SockPrintf("\ttx_bytes     : %ju\n", output->qosFlow[i].tx_bytes);
		SockPrintf("\ttx_bytes_drp : %ju\n", output->qosFlow[i].tx_bytes_drp);
	}
}

void qos_read_datastats(uint32_t qosIdentifier)
{
	pack_qos_SLQSQosSwiReadDataStats_t input;
	input.apnId = qosIdentifier;

	unpack_qos_SLQSQosSwiReadDataStats_t output;
	memset(&output, 0, sizeof(output));

	int rtn = SENDRECEIVE(&s_QosService, pack_qos_SLQSQosSwiReadDataStats, &input, unpack_qos_SLQSQosSwiReadDataStats, &output);
	DisplayResult(__FUNCTION__, rtn, &output.ParamPresenceMask, (result_func)displayQosReadDatastats, (void*)&output);
}

void displayQosSwiReadApnExtraParams(unpack_qos_SLQSQosSwiReadApnExtraParams_t* output)
{
	SockPrintf("APN ID       : %d\n", output->apnId);
	SockPrintf("ambr_ul      : %d\n", output->ambr_ul);
	SockPrintf("ambr_dl      : %d\n", output->ambr_dl);
	SockPrintf("ambr_ul_ext  : %d\n", output->ambr_ul_ext);
	SockPrintf("ambr_dl_ext  : %d\n", output->ambr_dl_ext);
	SockPrintf("ambr_ul_ext2 : %d\n", output->ambr_ul_ext2);
	SockPrintf("ambr_dl_ext2 : %d\n", output->ambr_dl_ext2);
}

void qos_read_extraapnparams(uint32_t qosIdentifier)
{
	pack_qos_SLQSQosSwiReadApnExtraParams_t input;
	input.apnId = qosIdentifier;

	unpack_qos_SLQSQosSwiReadApnExtraParams_t output;
	memset(&output, 0, sizeof(output));

	int rtn = SENDRECEIVE(&s_QosService, pack_qos_SLQSQosSwiReadApnExtraParams, &input, unpack_qos_SLQSQosSwiReadApnExtraParams, &output);
	DisplayResult(__FUNCTION__, rtn, &output.ParamPresenceMask, (result_func)displayQosSwiReadApnExtraParams, (void*)&output);
}

