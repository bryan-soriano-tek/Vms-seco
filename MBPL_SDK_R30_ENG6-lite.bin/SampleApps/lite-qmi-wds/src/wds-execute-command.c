#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <QmiService.h>
#include <CtlService.h>
#include <QmiSyncObject.h>
#include "lite-qmi-wds.h"
#include "qmux_util.h"
#include "wds.h"
#include "command_set.h"
#include "lite-qmi-demo.h"

extern void DisplayGetApnMsisdnInfo(unpack_wds_ApnMsisdnInfo_t *pApnMsisdnInfo);
extern void DisplayLteAttachParamsIndication(unpack_wds_SLQSLteAttachParams_ind_t *pLteAttachParams_ind);
extern void DisplayApnOpReservedPcoListChangeIndication(unpack_wds_SLQSApnOpReservedPcoListChange_ind_t *pApnOpReservedPcoListChange_ind);
extern void DisplayApnMsisdnInfoChangeIndication(unpack_wds_SLQSApnMsisdnInfoChange_ind_t *pApnMsisdnInfoChange_ind);
extern void DisplayPdnThrottleInfoIndication(unpack_wds_SLQSPdnThrottleInfo_ind_t *pPdnThrottleInfo_ind);
extern void DisplayModemAssistedKaStatusIndication(unpack_wds_SLQSModemAssistedKaStatus_ind_t  *pModemAssistedKaStatus_ind);
extern void DisplayApnOpReservedPcoList(unpack_wds_ApnOpReservedPcoList_t *pApnOpReservedPcoListChange_ind);
extern void DisplayWdsEventReport(unpack_wds_SLQSSetWdsEventReport_ind_t *pWdsEventReport_ind);
extern void Display3GPPConfigItems(unpack_wds_SLQSGet3GPPConfigItem_t *pGet3GPPConfigItem);
extern void DisplayThroughputInformationInd(unpack_wds_ThroughputInformationInd_t  *pThroughputInformationInd);
extern void DisplayDownlinkThroughputInformationInd(unpack_wds_DLThroughputInformationInd_t  *pDLThroughputInfoInd);
extern void DisplayQueryDLThroughputReportingStatus(unpack_wds_QueryDLThroughputReportingStatusInd_t  *pQueryDLThroughputReportingStatusInd);
extern void DisplayGetCurrentChannelRate(unpack_wds_SLQSGetCurrentChannelRate_t *pCurrentChannelRate);
extern void DisplayProfileChangeInd(unpack_wds_SLQSSWIProfileChange_ind_t *pSWIProfileChange);
extern void DisplayGetDefaultNssai(unpack_wds_swi_GetDefaultNssai_t *pDefaultNssai);
extern void DisplayGetProfileSnssai(unpack_wds_swi_GetProfileSnsaai_t *pGetProfileSnsaai);
extern void DisplayCreateSwiProfile(unpack_wds_SLQSCreateProfile_t* pCreateSwiProfile);

void SetKeepAliveDataSession(QmiService* pQmiService, bool enableKA)
{
    unpack_wds_Keep_Alive_Data_Session_t unpackObject;
    memset(&unpackObject, 0, sizeof(unpack_wds_Keep_Alive_Data_Session_t));

    int qcError = SENDRECEIVE(pQmiService, pack_wds_KeepAliveDataSession, &enableKA, unpack_wds_KeepAliveDataSession, &unpackObject);
    DisplayResult(__FUNCTION__, qcError, &unpackObject.ParamPresenceMask, NULL, NULL);
}

void ResetAndModifyProfileSettings(QmiService* pQmiService, uint8_t profileID, uint8_t profileType, wds_profileInfo *pProfile)
{
    pack_wds_ResetAndModifyProfileSettings_t reqArg;
	reqArg.ProfileId = profileID;
	reqArg.ProfileType = profileType;
	reqArg.pProfile = pProfile;

    unpack_wds_ResetAndModifyProfileSettings_t unpackObject;
    memset(&unpackObject, 0, sizeof(unpack_wds_ResetAndModifyProfileSettings_t));

    int qcError = SENDRECEIVE(pQmiService, pack_wds_ResetAndModifyProfileSettings, &reqArg, unpack_wds_ResetAndModifyProfileSettings, &unpackObject);
    DisplayResult(__FUNCTION__, qcError, &unpackObject.ParamPresenceMask, NULL, NULL);
}

void GetApnOpReservedPcoList(QmiService* pQmiService, char *pApnName)
{
    pack_wds_GetApnOpReservedPcoList_t reqArg;
    reqArg.pApnName = pApnName;
    unpack_wds_ApnOpReservedPcoList_t unpackObject;
    unpackObject.numInstances = 50;
    WdsApnOpReservedPco_t arrWdsApnOpReservedPcoList[50] = {{0,0,0,0,0,{0},0}};
    unpackObject.pWdsApnOpReservedPcoList = &arrWdsApnOpReservedPcoList[0];

    int qcError = SENDRECEIVE(pQmiService, pack_wds_GetApnOpReservedPcoList, &reqArg, unpack_wds_ApnOpReservedPcoList, &unpackObject);
    DisplayResult(__FUNCTION__, qcError, &unpackObject.ParamPresenceMask, (result_func)DisplayApnOpReservedPcoList, (void*) & unpackObject);
}

void GetApnMsisdnInfo(QmiService* pQmiService, char *pApnName)
{
    pack_wds_GetApnMsisdnInfo_t reqArg;
    reqArg.pApnName = pApnName;

    unpack_wds_ApnMsisdnInfo_t unpackObject;
    uint8_t   Msisdn[20] = {0};
    unpackObject.num_msisdn = 20;
    unpackObject.pMsisdn = &Msisdn[0];

    int qcError = SENDRECEIVE(pQmiService, pack_wds_GetApnMsisdnInfo, &reqArg, unpack_wds_ApnMsisdnInfo, &unpackObject);
    DisplayResult(__FUNCTION__, qcError, &unpackObject.ParamPresenceMask, (result_func)DisplayGetApnMsisdnInfo, (void*)&unpackObject);
}

void DeleteAllProfiles(QmiService* pQmiService, pack_wds_DeleteAllProfiles_t *reqArg)
{
    unpack_wds_delete_all_profiles_t unpackObject;
    memset(&unpackObject, 0, sizeof(unpack_wds_delete_all_profiles_t));

    int qcError = SENDRECEIVE(pQmiService, pack_wds_DeleteAllProfilesEx, reqArg, unpack_wds_DeleteAllProfiles, &unpackObject);
    DisplayResult(__FUNCTION__, qcError, &unpackObject.ParamPresenceMask, NULL, NULL);
}

void SetEhrpdFallbackApnList(QmiService* pQmiService, uint8_t fallback_apn_name_list_len, WdsEhrpdFallbackApn_t *pWdsEhrpdFallbackApn)
{
    pack_wds_SetEhrpdFallbackApnList_t reqArg;
	reqArg.fallback_apn_name_list_len = fallback_apn_name_list_len;
	reqArg.pWdsEhrpdFallbackApn = pWdsEhrpdFallbackApn;

    unpack_wds_SetDefaultProfile_t unpackObject;
    memset(&unpackObject, 0, sizeof(unpack_wds_SetDefaultProfile_t));

    int qcError = SENDRECEIVE(pQmiService, pack_wds_SetEhrpdFallbackApnList, &reqArg, unpack_wds_SetEhrpdFallbackApnList, &unpackObject);
    DisplayResult(__FUNCTION__, qcError, &unpackObject.ParamPresenceMask, NULL, NULL);
}

void SetModemAssistedKaStart(QmiService* pQmiService, pack_wds_modem_assisted_ka_start_t *pReqParam)
{
    unpack_wds_modem_assisted_ka_start_t unpackObject;
    memset(&unpackObject, 0, sizeof(unpack_wds_modem_assisted_ka_start_t));

    int qcError = SENDRECEIVE(pQmiService, pack_wds_ModemAssistedKaStart, pReqParam, unpack_wds_ModemAssistedKaStart, &unpackObject);
    DisplayResult(__FUNCTION__, qcError, &unpackObject.ParamPresenceMask, NULL, NULL);
}

void SetModemAssistedKaStop(QmiService* pQmiService, pack_wds_modem_assisted_ka_stop_t *pModemAssistedKaStop)
{
    unpack_wds_modem_assisted_ka_stop_t unpackObject;
    memset(&unpackObject, 0, sizeof(unpack_wds_modem_assisted_ka_stop_t));

    int qcError = SENDRECEIVE(pQmiService, pack_wds_ModemAssistedKaStopEx, pModemAssistedKaStop, unpack_wds_ModemAssistedKaStop, &unpackObject);
    DisplayResult(__FUNCTION__, qcError, &unpackObject.ParamPresenceMask, NULL, NULL);
}

void GetEhrpdFallbackApnList(QmiService* pQmiService)
{
    uint8_t   fallback_apn_name_list_len = 10;
    WdsEhrpdFallbackApn_t WdsEhrpdFallbackApn[fallback_apn_name_list_len];

    unpack_wds_GetEhrpdFallbackApnList_t unpackObject;
    memset(&unpackObject, 0, sizeof(unpack_wds_GetEhrpdFallbackApnList_t));
    unpackObject.fallback_apn_name_list_len = fallback_apn_name_list_len;
    unpackObject.pWdsEhrpdFallbackApn = &WdsEhrpdFallbackApn[0];

    int qcError = SENDRECEIVENOINPUT(pQmiService, pack_wds_GetEhrpdFallbackApnList, unpack_wds_GetEhrpdFallbackApnList, &unpackObject);
    DisplayResult(__FUNCTION__, qcError, &unpackObject.ParamPresenceMask, NULL, NULL);
}

extern void RegisterWdsEventRegister(QmiService* pQmiService, pack_wds_SLQSWdsSetEventReport_t *pReqArg)
{
    unpack_wds_SLQSWdsSetEventReport_t unpackObject;
    memset(&unpackObject, 0, sizeof(unpack_wds_SLQSWdsSetEventReport_t));

    int qcError = SENDRECEIVE(pQmiService, pack_wds_SLQSWdsSetEventReport, pReqArg, unpack_wds_SLQSWdsSetEventReport, &unpackObject);
    DisplayResult(__FUNCTION__, qcError, &unpackObject.ParamPresenceMask, NULL, NULL);
}

void RegisterWdsIndicationRegister(QmiService* pQmiService, pack_wds_indication_register_t   *pReqArg)
{
    unpack_wds_IndicationRegister_t unpackObject;
    memset(&unpackObject, 0, sizeof(unpack_wds_IndicationRegister_t));

    int qcError = SENDRECEIVE(pQmiService, pack_wds_IndicationRegister, pReqArg, unpack_wds_IndicationRegister, &unpackObject);
    DisplayResult(__FUNCTION__, qcError, &unpackObject.ParamPresenceMask, NULL, NULL);
}

void GetDefaultProfileId(QmiService* pQmiService, pack_wds_GetDefaultProfileNum_t   *pReqArg)
{
    unpack_wds_GetDefaultProfileNum_t unpackObject;
    memset(&unpackObject, 0, sizeof(unpack_wds_GetDefaultProfileNum_t));

    int qcError = SENDRECEIVE(pQmiService, pack_wds_GetDefaultProfileNum, pReqArg, unpack_wds_GetDefaultProfileNum, &unpackObject);
    DisplayResult(__FUNCTION__, qcError, &unpackObject.ParamPresenceMask, NULL, NULL);
}

void SetDefaultProfileId(QmiService* pQmiService, pack_wds_SetDefaultProfileNum_t   *pReqArg)
{
    unpack_wds_SetDefaultProfileNum_t unpackObject;
    memset(&unpackObject, 0, sizeof(unpack_wds_SetDefaultProfileNum_t));

    int qcError = SENDRECEIVE(pQmiService, pack_wds_SetDefaultProfileNum, pReqArg, unpack_wds_SetDefaultProfileNum, &unpackObject);
    DisplayResult(__FUNCTION__, qcError, &unpackObject.ParamPresenceMask, NULL, NULL);
}

void Get3GPPConfigItems(QmiService* pQmiService)
{
    unpack_wds_SLQSGet3GPPConfigItem_t unpackObject;
    memset(&unpackObject, 0, sizeof(unpack_wds_SLQSGet3GPPConfigItem_t));
    unpackObject.LTEAttachProfileListLen = MAX_WDS_3GPP_CONF_LTE_ATTACH_PROFILE_LIST_SIZE;

    int qcError = SENDRECEIVENOINPUT(pQmiService, pack_wds_SLQSGet3GPPConfigItem, unpack_wds_SLQSGet3GPPConfigItem, &unpackObject);
    DisplayResult(__FUNCTION__, qcError, &unpackObject.ParamPresenceMask, (result_func)Display3GPPConfigItems, (void*) & unpackObject);
}

void Set3GPPConfigItems(QmiService* pQmiService, pack_wds_SLQSSet3GPPConfigItem_t *reqArg)
{
    unpack_wds_SLQSSet3GPPConfigItem_t unpackObject;
    memset(&unpackObject, 0, sizeof(unpack_wds_SLQSSet3GPPConfigItem_t));

    int qcError = SENDRECEIVE(pQmiService, pack_wds_SLQSSet3GPPConfigItem, reqArg, unpack_wds_SLQSSet3GPPConfigItem, &unpackObject);
    DisplayResult(__FUNCTION__, qcError, &unpackObject.ParamPresenceMask, NULL, NULL);
}

void SetDownlinkThroughputReportPeriod(QmiService* pQmiService, pack_wds_SetDLThroughputReportPeriod_t *reqArg)
{
    unpack_wds_SetDLThroughputReportPeriod_t unpackObject;
    memset(&unpackObject, 0, sizeof(unpack_wds_SetDLThroughputReportPeriod_t));

    int qcError = SENDRECEIVE(pQmiService, pack_wds_SLQSSetDLThroughputReportPeriod, reqArg, unpack_wds_SLQSSetDLThroughputReportPeriod, &unpackObject);
    DisplayResult(__FUNCTION__, qcError, &unpackObject.ParamPresenceMask, NULL, NULL);
}

void QueryDownlinkThroughputReportingStatus(QmiService* pQmiService)
{
    unpack_wds_QueryDLThroughputReportingStatus_t unpackObject;
    memset(&unpackObject, 0, sizeof(unpack_wds_QueryDLThroughputReportingStatus_t));

    uint32_t  reporting_status = 0;
    uint32_t  actual_interval = 0;
    unpackObject.pReporting_status = &reporting_status;
    unpackObject.pActual_interval = &actual_interval;

    int qcError = SENDRECEIVENOINPUT(pQmiService, pack_wds_SLQSQueryDLThroughputReportingStatus, unpack_wds_SLQSQueryDLThroughputReportingStatus, &unpackObject);
    DisplayResult(__FUNCTION__, qcError, &unpackObject.ParamPresenceMask, (result_func)DisplayQueryDLThroughputReportingStatus, (void*)&unpackObject);
}

void GetCurrentChannelRate(QmiService* pQmiService)
{
    unpack_wds_SLQSGetCurrentChannelRate_t unpackObject;
    memset(&unpackObject, 0, sizeof(unpack_wds_SLQSGetCurrentChannelRate_t));

    int qcError = SENDRECEIVENOINPUT(pQmiService, pack_wds_SLQSSwiGetCurrentChannelRate, unpack_wds_SLQSSwiGetCurrentChannelRate, &unpackObject);
    DisplayResult(__FUNCTION__, qcError, &unpackObject.ParamPresenceMask, (result_func)DisplayGetCurrentChannelRate, (void*)&unpackObject);
}

void GetDefaultNssai(QmiService* pQmiService)
{
    unpack_wds_swi_GetDefaultNssai_t unpackObject;
    memset(&unpackObject, 0, sizeof(unpack_wds_swi_GetDefaultNssai_t));

    int qcError = SENDRECEIVENOINPUT(pQmiService, pack_wds_swi_GetDefaultNssai, unpack_wds_swi_GetDefaultNssai, &unpackObject);
    DisplayResult(__FUNCTION__, qcError, &unpackObject.ParamPresenceMask, (result_func)DisplayGetDefaultNssai, (void*)&unpackObject);
}

void SetDefaultNssai(QmiService* pQmiService, pack_wds_swi_SetDefaultNssai_t *pSetDefaultNssai)
{
    unpack_wds_swi_SetDefaultNssai_t unpackObject;
    memset(&unpackObject, 0, sizeof(unpack_wds_swi_SetDefaultNssai_t));

    int qcError = SENDRECEIVE(pQmiService, pack_wds_swi_SetDefaultNssai, pSetDefaultNssai, unpack_wds_swi_SetDefaultNssai, &unpackObject);
    DisplayResult(__FUNCTION__, qcError, &unpackObject.ParamPresenceMask, NULL, NULL);
}

void GetProfileSnssai(QmiService* pQmiService, pack_wds_swi_GetPrfileSnssai_t *pGetPrfileSnssai)
{
    unpack_wds_swi_GetProfileSnsaai_t unpackObject;
    memset(&unpackObject, 0, sizeof(unpack_wds_swi_GetProfileSnsaai_t));

    int qcError = SENDRECEIVE(pQmiService, pack_wds_swi_GetProfileSnssai, pGetPrfileSnssai, unpack_wds_swi_GetProfileSnssai, &unpackObject);
    DisplayResult(__FUNCTION__, qcError, &unpackObject.ParamPresenceMask, (result_func)DisplayGetProfileSnssai, (void*)&unpackObject);
}

void DeleteProfile(QmiService* pQmiService, pack_wds_SLQSDeleteProfile_t *pDeleteProfile)
{
    unpack_wds_SLQSDeleteProfile_t unpackObject;
    memset(&unpackObject, 0, sizeof(unpack_wds_SLQSDeleteProfile_t));

    int qcError = SENDRECEIVE(pQmiService, pack_wds_SLQSDeleteProfile, pDeleteProfile, unpack_wds_SLQSDeleteProfile, &unpackObject);
    DisplayResult(__FUNCTION__, qcError, &unpackObject.ParamPresenceMask, NULL, NULL);
}

void ClearProfileSnssai(QmiService* pQmiService, pack_wds_swi_ClearProfileSnssai_t *pClearProfileSnssai)
{
    unpack_wds_swi_ClearProfileSnssai_t unpackObject;
    memset(&unpackObject, 0, sizeof(unpack_wds_swi_ClearProfileSnssai_t));

    int qcError = SENDRECEIVE(pQmiService, pack_wds_swi_ClearProfileSnssai, pClearProfileSnssai, unpack_wds_swi_ClearProfileSnssai, &unpackObject);
    DisplayResult(__FUNCTION__, qcError, &unpackObject.ParamPresenceMask, NULL, NULL);
}

void ConfigureProfileSNssai(QmiService* pQmiService, pack_wds_SLQSCreateProfile_t* pCreateProfile)
{
    PackCreateProfileOut         profileInfoOut;
    memset(&profileInfoOut, 0, sizeof(profileInfoOut));

    unpack_wds_SLQSCreateProfile_t unpackObject;
    memset(&unpackObject, 0, sizeof(unpackObject));
    unpackObject.pCreateProfileOut = &profileInfoOut;
    unpackObject.pProfileID = pCreateProfile->pProfileId;

    int qcError = SENDRECEIVE(pQmiService, pack_wds_SLQSCreateProfile, pCreateProfile, unpack_wds_SLQSCreateProfile, &unpackObject);
    DisplayResult(__FUNCTION__, qcError, &unpackObject.ParamPresenceMask, (result_func)DisplayCreateSwiProfile, &unpackObject);
}

int enable_profile_change_notification(QmiService* pSvc, uint8_t enable)
{
    unpack_wds_SLQSSWIProfileChange_t output;

    int qcError = SENDRECEIVE(pSvc, pack_wds_SLQSSWIProfileChange, &enable, unpack_wds_SLQSSWIProfileChange, &output);
    DisplayResult(__FUNCTION__, qcError, &output.ParamPresenceMask, NULL, NULL);

    return qcError;
}

void wds_indication_handler(uint16_t msgid, uint8_t *qmiData, uint32_t qmiDataSize)
{
    int rtn = 0;

    switch (msgid)
    {
        case eQMI_WDS_EVENT_REPORT_IND:
        {
            unpack_wds_SLQSSetWdsEventReport_ind_t sWdsEventReport_ind;
            memset(&sWdsEventReport_ind, 0, sizeof(unpack_wds_SLQSSetWdsEventReport_ind_t));

            rtn = unpack_wds_SLQSSetWdsEventReport_ind(qmiData, qmiDataSize, &sWdsEventReport_ind);
            DisplayResult("unpack_wds_SLQSSetWdsEventReport_ind", rtn, NULL, (result_func)DisplayWdsEventReport, (void*)&sWdsEventReport_ind);
        }
        break;
        case eQMI_WDS_LTE_ATTACH_PARAMS_IND:
        {
	        unpack_wds_SLQSLteAttachParams_ind_t   sLteAttachParams_ind;
            eQMI_WDS_IP_TYPE_t Ip_Type;
            uint32_t IPv4Address;
            uint32_t IPv4GatewayAddress;
            uint32_t IPv4SubnetMask;
            IPv6AddressTlv_t Ipv6Address;
            IPv6AddressTlv_t Ipv6GatewayAddress;

            sLteAttachParams_ind.AttachParamValidTlv = 0;
            sLteAttachParams_ind.ApnStringLen = 100;
            char ApnString[100] = {0};
            sLteAttachParams_ind.pApnString = &ApnString[0];
            sLteAttachParams_ind.pIp_Type = &Ip_Type;
            sLteAttachParams_ind.pIPv4Address = &IPv4Address;
            sLteAttachParams_ind.pIPv4GatewayAddress = &IPv4GatewayAddress;
            sLteAttachParams_ind.pIPv4SubnetMask = &IPv4SubnetMask;
            sLteAttachParams_ind.pIpv6Address = &Ipv6Address;
            sLteAttachParams_ind.pIpv6GatewayAddress = &Ipv6GatewayAddress;
            swi_uint256_init(&sLteAttachParams_ind.ParamPresenceMask);

            rtn = unpack_wds_SLQSLteAttachParams_ind(qmiData, qmiDataSize, &sLteAttachParams_ind);
            DisplayResult("unpack_wds_SLQSLteAttachParams_ind", rtn, NULL, (result_func)DisplayLteAttachParamsIndication, (void*)&sLteAttachParams_ind);
        }   
        break;
        case eQMI_WDS_APN_OP_RESERVED_PCO_LIST_CHANGE_IND:
        {
	        unpack_wds_SLQSApnOpReservedPcoListChange_ind_t sApnOpReservedPcoListChange_ind;
            sApnOpReservedPcoListChange_ind.PcoInfoLength = 10;
	        WdsApnOpReservedPco_t WdsApnOpReservedPcoList[10];
            sApnOpReservedPcoListChange_ind.pWdsApnOpReservedPcoList = &WdsApnOpReservedPcoList[0];

            rtn = unpack_wds_SLQSApnOpReservedPcoListChange_ind(qmiData, qmiDataSize, &sApnOpReservedPcoListChange_ind);
            DisplayResult("unpack_wds_SLQSApnOpReservedPcoListChange_ind", rtn, NULL, (result_func)DisplayApnOpReservedPcoListChangeIndication, (void*)&sApnOpReservedPcoListChange_ind);
        }
        break;
        case eQMI_WDS_APN_MSISDN_INFO_CHANGE_IND:
        {
	        unpack_wds_SLQSApnMsisdnInfoChange_ind_t        sApnMsisdnInfoChange_ind;
            memset(&sApnMsisdnInfoChange_ind, 0, sizeof(unpack_wds_SLQSApnMsisdnInfoChange_ind_t));
            sApnMsisdnInfoChange_ind.msisdn_len = 20;
            uint8_t  Msisdn[20] = {0};
            sApnMsisdnInfoChange_ind.pMsisdn = &Msisdn[0];

            rtn = unpack_wds_SLQSApnMsisdnInfoChange_ind(qmiData, qmiDataSize, &sApnMsisdnInfoChange_ind);
            DisplayResult("unpack_wds_SLQSApnMsisdnInfoChange_ind", rtn, NULL, (result_func)DisplayApnMsisdnInfoChangeIndication, (void*)&sApnMsisdnInfoChange_ind);
        }            
        break;
        case eQMI_WDS_PDN_THROTTLE_INFO_IND:
        {
	        unpack_wds_SLQSPdnThrottleInfo_ind_t   sPdnThrottleInfo_ind;
           	sPdnThrottleInfo_ind.throttle_info_len = 10;
            sPdnThrottleInfo_ind.throttle_info_ext_len = 10;
            sPdnThrottleInfo_ind.throttle_info_addn_params_len = 10;
            WdsPDNThrottleInformationTlv_t    PDNThrottleInformation[10];
            WdsExtPDNThrottleInformationTlv_t ExtPDNThrottleInformationList[10];
            WdsAddPDNThrottleInformationTlv_t AddPDNThrottleInformationList[10];
            sPdnThrottleInfo_ind.pPDNThrottleInformation = &PDNThrottleInformation[0];
            sPdnThrottleInfo_ind.pExtPDNThrottleInformationList = &ExtPDNThrottleInformationList[0];
            sPdnThrottleInfo_ind.pAddPDNThrottleInformationList = &AddPDNThrottleInformationList[0];
            swi_uint256_init(&sPdnThrottleInfo_ind.ParamPresenceMask);

            rtn = unpack_wds_SLQSPdnThrottleInfo_ind(qmiData, qmiDataSize, &sPdnThrottleInfo_ind);
            DisplayResult("unpack_wds_SLQSPdnThrottleInfo_ind", rtn, NULL, (result_func)DisplayPdnThrottleInfoIndication, (void*)&sPdnThrottleInfo_ind);
        }
        break;
        case eQMI_WDS_MODEM_ASSISTED_KA_STATUS_IND:
        {
	        unpack_wds_SLQSModemAssistedKaStatus_ind_t      sModemAssistedKaStatus_ind;
            rtn = unpack_wds_SLQSModemAssistedKaStatus_ind(qmiData, qmiDataSize, &sModemAssistedKaStatus_ind);
            DisplayResult("unpack_wds_SLQSModemAssistedKaStatus_ind", rtn, NULL, (result_func)DisplayModemAssistedKaStatusIndication, (void*)&sModemAssistedKaStatus_ind);
        }            
        break;
        case eQMI_WDS_THROUGHPUT_INFO_IND:
        {
	        unpack_wds_ThroughputInformationInd_t  sThroughputInformationInd;
            sThroughputInformationInd.throughput_info_len = 20;
            ThroughputInformationItem_t sThroughputInformationList[20];
            ThroughputInformationMac_t arrThroughputInformationMac[20][10];
            memset(arrThroughputInformationMac, 0, sizeof (arrThroughputInformationMac));
            sThroughputInformationInd.pThroughputInformationList = &sThroughputInformationList[0];
            for (int idx = 0; idx < sThroughputInformationInd.throughput_info_len; ++idx)
            {
                sThroughputInformationInd.pThroughputInformationList[idx].pThroughputInformationMac = arrThroughputInformationMac[idx]; 
            }

            rtn = unpack_wds_ThroughputInformationInd(qmiData, qmiDataSize, &sThroughputInformationInd);
            DisplayResult("unpack_wds_ThroughputInformationInd", rtn, NULL, (result_func)DisplayThroughputInformationInd, (void*)&sThroughputInformationInd);
        }            
        break;
        case eQMI_WDS_DOWNLINK_THROUGHPUT_INFO_IND:
        {
	        unpack_wds_DLThroughputInformationInd_t  sDLThroughputInfoInd;
			memset(&sDLThroughputInfoInd, 0, sizeof(unpack_wds_DLThroughputInformationInd_t));

            uint32_t downlink_allowed_rate = 0;
            uint8_t  confidence_level = 0;
            uint8_t  is_suspended = 0;
            sDLThroughputInfoInd.pDownlink_allowed_rate = &downlink_allowed_rate;
            sDLThroughputInfoInd.pConfidence_level = &confidence_level;
            sDLThroughputInfoInd.pIs_suspended = &is_suspended;

            rtn = unpack_wds_DLThroughputInformationInd(qmiData, qmiDataSize, &sDLThroughputInfoInd);
            DisplayResult("unpack_wds_DLThroughputInformationInd", rtn, NULL, (result_func)DisplayDownlinkThroughputInformationInd, (void*)&sDLThroughputInfoInd);
        }            
        break;
        case eQMI_WDS_DOWNLINK_THROUGHPUT_REPORTING_STATUS_IND:
        {
	        unpack_wds_QueryDLThroughputReportingStatusInd_t  sQueryDLThroughputReportingStatusInd;
			memset(&sQueryDLThroughputReportingStatusInd, 0, sizeof(unpack_wds_QueryDLThroughputReportingStatusInd_t));

            rtn = unpack_wds_QueryDLThroughputReportingStatusInd(qmiData, qmiDataSize, &sQueryDLThroughputReportingStatusInd);
            DisplayResult("unpack_wds_QueryDLThroughputReportingStatusInd", rtn, NULL, (result_func)DisplayQueryDLThroughputReportingStatus, (void*)&sQueryDLThroughputReportingStatusInd);
        }            
        break;
        case eQMI_WDS_SWI_PROFILE_CHANGE:
        {
            unpack_wds_SLQSSWIProfileChange_ind_t sProfileChangeInd;
            memset(&sProfileChangeInd, 0, sizeof(unpack_wds_SLQSSWIProfileChange_ind_t));

            rtn = unpack_wds_SLQSSWIProfileChange_ind(qmiData, qmiDataSize, &sProfileChangeInd);
            DisplayResult("unpack_wds_SLQSSWIProfileChange_ind", rtn, NULL, (result_func)DisplayProfileChangeInd, (void*)&sProfileChangeInd);
        }
        break;
    }
}
