#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <QmiService.h>
#include <CtlService.h>
#include <QmiSyncObject.h>
#include "lite-qmi-uim.h"
#include "uim.h"
#include "str_util.h"
#include "command_set.h"
#include "lite-qmi-demo.h"

extern void DisplaySlotsStatus(unpack_uim_SLQSUIMGetSlotsStatus_t *pSlotStatus);
extern void DisplayVerifyPin(unpack_uim_VerifyPin_t *pVerifyPinResult);
extern void DisplayGetCardStatus(unpack_uim_GetCardStatus_t *pVerifyPinResult);
extern void DisplaySetPinProtection(unpack_uim_SetPinProtection_t *pSetPinProtection);
extern void DisplayUnblockPin(unpack_uim_UnblockPin_t *pUnblockPinResult);
extern void DisplayFileAttributes(unpack_uim_SLQSUIMGetFileAttributes_t *pGetFileAttributesResp);
extern void DisplayAuthenticate(unpack_uim_SLQSUIMAuthenticate_t *pAuthenticateResp);
extern void DisplayConfiguration(unpack_uim_SLQSUIMGetConfiguration_t *pGetConfigurationResp);
extern void DisplayChangePin(unpack_uim_ChangePin_t *pChangePinResp);
extern void DisplayGetLastEvent(unpack_uim_SLQSUIMRefreshGetLastEvent_t *pRefreshGetLastEventResp);
extern void DisplayGetFileAttributesInd(unpack_uim_SLQSUIMGetFileAttibutes_Ind_t *pGetFileAttributesInd);
extern void DisplaySlotStatusChangeInd(unpack_uim_SetUimSlotStatusChangeCallback_ind_t *pSlotStatusChangeCallback_ind);
extern void DisplayVerifyPinInd(unpack_uim_VerifyPin_ind_t  *pVerifyPinInd);
extern void DisplaySetPinProtectionInd(unpack_uim_SetPinProtection_ind_t *pSetPinProtectionInd);
extern void DisplayUnblockPinInd(unpack_uim_UnblockPin_ind_t *pUnblockPinInd);
extern void DisplayIccid(unpack_uim_SLQSUIMGetIccid_t* getICCID);
extern void DisplayEventRegister(unpack_uim_SLQSUIMEventRegister_t* eventRegisterResult);
extern void DisplayDepersonalization(unpack_uim_SLQSUIMDepersonalization_t* depersonalizationResp);
extern void DisplayReadTransparent(unpack_uim_ReadTransparent_t* readTransparent);
extern void DisplayReadTransparent2(unpack_uim_ReadTransparent_t* output);
extern void DisplayChangePinInd(unpack_uim_ChangePin_ind_t  *pChangePinInd);
extern void DisplaySetStatusChangeInd(unpack_uim_SLQSUIMSetStatusChangeCallBack_ind_t *pSetStatusChangeInd);
extern void DisplayRefreshInd(unpack_uim_SLQSUIMRefreshCallback_Ind_t *pRefreshIndication);
extern void DisplayAuthenticateInd(unpack_uim_Authenticate_ind_t *pAuthenticateInd);

void ReadTransparent2(QmiService* pQmiService);

void GetSlotsStatus(QmiService* pQmiService)
{
    slots_t UimSlotsStatus[3];
    uint8_t    NumberOfPhySlot = sizeof(UimSlotsStatus)/sizeof(slots_t);
    unpack_uim_SLQSUIMGetSlotsStatus_t slotStatus = {&NumberOfPhySlot, UimSlotsStatus, SWI_UINT256_INT_VALUE} ;

    int ret = SENDRECEIVENOINPUT(pQmiService, pack_uim_SLQSUIMGetSlotsStatus, unpack_uim_SLQSUIMGetSlotsStatus, &slotStatus);
    DisplayResult(__FUNCTION__, ret, &slotStatus.ParamPresenceMask, (result_func)DisplaySlotsStatus, (void*)&slotStatus);
}

void GetCardStatus(QmiService* pQmiService)
{
    uim_cardStatus CardStatus;
    uim_hotSwapStatus HotSwapStatus;
    unpack_uim_GetCardStatus_t getCardStatus = {&CardStatus,&HotSwapStatus,0, SWI_UINT256_INT_VALUE};

    int ret = SENDRECEIVENOINPUT(pQmiService, pack_uim_GetCardStatus, unpack_uim_GetCardStatus, &getCardStatus);
    DisplayResult(__FUNCTION__, ret, &getCardStatus.ParamPresenceMask, (result_func)DisplayGetCardStatus, (void*)&getCardStatus);
}

void GetIccid(QmiService* pQmiService)
{
    uint8_t ICCIDLength = 255;
    uint8_t activeICCID[255] = {0};
    unpack_uim_SLQSUIMGetIccid_t getICCID = {&ICCIDLength, activeICCID};

    int ret = SENDRECEIVENOINPUT(pQmiService, pack_uim_SLQSUIMGetIccid, unpack_uim_SLQSUIMGetIccid, &getICCID);
    DisplayResult(__FUNCTION__, ret, NULL, (result_func)DisplayIccid, (void*)&getICCID);
}

void EventRegister(QmiService* pQmiService, uint32_t mask)
{
    pack_uim_SLQSUIMEventRegister_t eventRegister = {mask};
    unpack_uim_SLQSUIMEventRegister_t eventRegisterResult;

    int ret = SENDRECEIVE(pQmiService, pack_uim_SLQSUIMEventRegister, &eventRegister, unpack_uim_SLQSUIMEventRegister, &eventRegisterResult);
    DisplayResult(__FUNCTION__, ret, &eventRegisterResult.ParamPresenceMask, (result_func)DisplayEventRegister, (void*)&eventRegisterResult);
}

void SwitchSlot(QmiService* pQmiService, pack_uim_SLQSUIMSwitchSlot_t *pSwitchSlot)
{
    unpack_uim_SLQSUIMSwitchSlot_t switchSlotOut = {0, SWI_UINT256_INT_VALUE};

    int ret = SENDRECEIVE(pQmiService, pack_uim_SLQSUIMSwitchSlot, pSwitchSlot, unpack_uim_SLQSUIMSwitchSlot, &switchSlotOut);
    DisplayResult(__FUNCTION__, ret, &switchSlotOut.ParamPresenceMask, NULL, NULL);
}

void VerifyPin(QmiService* pQmiService, pack_uim_VerifyPin_t *pVerifyPin)
{
    uim_remainingRetries RemainingRetries;
    uim_encryptedPIN1    EncryptedPIN1;
    uint32_t             IndicationToken;
    unpack_uim_VerifyPin_t verifyPinResult ={&RemainingRetries,&EncryptedPIN1,&IndicationToken,0, SWI_UINT256_INT_VALUE};

    int ret = SENDRECEIVE(pQmiService, pack_uim_VerifyPin, pVerifyPin, unpack_uim_VerifyPin, &verifyPinResult);
    DisplayResult(__FUNCTION__, ret, &verifyPinResult.ParamPresenceMask, (result_func)DisplayVerifyPin, (void*)&verifyPinResult);
}

void SetPinProtection(QmiService* pQmiService, pack_uim_SetPinProtection_t *pRetPinProtectionReq)
{
    uint32_t IndicationToken = 5;
    uim_remainingRetries RemainingRetries;
    uim_encryptedPIN1    EncryptedPIN1;
    unpack_uim_SetPinProtection_t setPinProtection = {&RemainingRetries,&EncryptedPIN1,&IndicationToken,0, SWI_UINT256_INT_VALUE};

    int ret = SENDRECEIVE(pQmiService, pack_uim_SetPinProtection, pRetPinProtectionReq, unpack_uim_SetPinProtection, &setPinProtection);
    DisplayResult(__FUNCTION__, ret, &setPinProtection.ParamPresenceMask, (result_func)DisplaySetPinProtection, (void*)&setPinProtection);
}

void UnblockPin(QmiService* pQmiService, pack_uim_UnblockPin_t *pUnblockPinReq)
{
    uim_remainingRetries RemainingRetries;
    uim_encryptedPIN1    EncryptedPIN1;
    uint32_t             IndicationToken;
    unpack_uim_UnblockPin_t unblockPinResult = {&RemainingRetries,&EncryptedPIN1,&IndicationToken,0, SWI_UINT256_INT_VALUE};

    int ret = SENDRECEIVE(pQmiService, pack_uim_UnblockPin, pUnblockPinReq, unpack_uim_UnblockPin, &unblockPinResult);
    DisplayResult(__FUNCTION__, ret, &unblockPinResult.ParamPresenceMask, (result_func)DisplayUnblockPin, (void*)&unblockPinResult);
}

void PowerDown(QmiService* pQmiService)
{
    pack_uim_SLQSUIMPowerDown_t powerDownReq ={1};
    unpack_uim_SLQSUIMPowerDown_t powerDownResult = {0, SWI_UINT256_INT_VALUE};

    int ret = SENDRECEIVE(pQmiService, pack_uim_SLQSUIMPowerDown, &powerDownReq, unpack_uim_SLQSUIMPowerDown, &powerDownResult);
    DisplayResult(__FUNCTION__, ret, &powerDownResult.ParamPresenceMask, NULL, NULL);
}

void PowerUp(QmiService* pQmiService)
{
    uint8_t bCheckHotSwapSwitch = 0;
    pack_uim_SLQSUIMPowerUp_t   powerUpReq = {1,&bCheckHotSwapSwitch};
    unpack_uim_SLQSUIMPowerUp_t powerUpResult = {0, SWI_UINT256_INT_VALUE};

    int ret = SENDRECEIVE(pQmiService, pack_uim_SLQSUIMPowerUp, &powerUpReq, unpack_uim_SLQSUIMPowerUp, &powerUpResult);
    DisplayResult(__FUNCTION__, ret, &powerUpResult.ParamPresenceMask, NULL, NULL);
}

void Reset(QmiService* pQmiService)
{
    unpack_uim_SLQSUIMReset_t resetResult = {0, SWI_UINT256_INT_VALUE};

    int ret = SENDRECEIVENOINPUT(pQmiService, pack_uim_SLQSUIMReset, unpack_uim_SLQSUIMReset, &resetResult);
    DisplayResult(__FUNCTION__, ret, &resetResult.ParamPresenceMask, NULL, NULL);
}

void RefreshRegister(QmiService* pQmiService, pack_uim_SLQSUIMRefreshRegister_t *pRefreshRegister)
{
    unpack_uim_SLQSUIMRefreshRegister_t refreshRegisterResult = {0, SWI_UINT256_INT_VALUE};

    int ret = SENDRECEIVE(pQmiService, pack_uim_SLQSUIMRefreshRegister, pRefreshRegister, unpack_uim_SLQSUIMRefreshRegister, &refreshRegisterResult);
    DisplayResult(__FUNCTION__, ret, &refreshRegisterResult.ParamPresenceMask, NULL, NULL);
}

void RefreshGetLastEvent(QmiService* pQmiService, pack_uim_SLQSUIMRefreshGetLastEvent_t *pRefreshGetLastEventReq)
{
    uim_refreshevent refreshEvent;
    memset(&refreshEvent, 0, sizeof(refreshEvent));
    uint64_t refresh_enforcement_policy_mask = 0;
    unpack_uim_SLQSUIMRefreshGetLastEvent_t refreshGetLastEventResp={&refreshEvent, &refresh_enforcement_policy_mask, SWI_UINT256_INT_VALUE};

    int ret = SENDRECEIVE(pQmiService, pack_uim_SLQSUIMRefreshGetLastEvent, pRefreshGetLastEventReq, unpack_uim_SLQSUIMRefreshGetLastEvent, &refreshGetLastEventResp);
    DisplayResult(__FUNCTION__, ret, &refreshGetLastEventResp.ParamPresenceMask, (result_func)DisplayGetLastEvent, (void*)&refreshGetLastEventResp);
}

void GetFileAttributes(QmiService* pQmiService, pack_uim_SLQSUIMGetFileAttributes_t *pGetFileAttributesReq)
{
    uim_cardResult     cardresult;
    uim_fileAttributes fileattributes;
    uint32_t           indicationtoken;
    uint32_t           fileStatus;
    unpack_uim_SLQSUIMGetFileAttributes_t getFileAttributesResp = { &cardresult, &fileattributes, &indicationtoken, &fileStatus, SWI_UINT256_INT_VALUE};

    int ret = SENDRECEIVE(pQmiService, pack_uim_SLQSUIMGetFileAttributes, pGetFileAttributesReq, unpack_uim_SLQSUIMGetFileAttributes, &getFileAttributesResp);
    DisplayResult(__FUNCTION__, ret, &getFileAttributesResp.ParamPresenceMask, (result_func)DisplayFileAttributes, (void*)&getFileAttributesResp);
}

void Depersonalization(QmiService* pQmiService, pack_uim_SLQSUIMDepersonalization_t *pDepersonalizationReq)      
{
    uim_remainingRetries remainingRtries;
    unpack_uim_SLQSUIMDepersonalization_t depersonalizationResp = {&remainingRtries, SWI_UINT256_INT_VALUE};

    int ret = SENDRECEIVE(pQmiService, pack_uim_SLQSUIMDepersonalization, pDepersonalizationReq, unpack_uim_SLQSUIMDepersonalization, &depersonalizationResp);
    DisplayResult(__FUNCTION__, ret, &depersonalizationResp.ParamPresenceMask, (result_func)DisplayDepersonalization, (void*)&depersonalizationResp);
}

void Authenticate(QmiService* pQmiService, pack_uim_SLQSUIMAuthenticate_t *pAuthenticateData)
{
    uim_cardResult          cardrsult;
    uim_authenticateResult  authenticateresult;
    uint32_t                indicationToken;
    unpack_uim_SLQSUIMAuthenticate_t authenticateResp = {&cardrsult, &authenticateresult, &indicationToken, SWI_UINT256_INT_VALUE};

    int ret = SENDRECEIVE(pQmiService, pack_uim_SLQSUIMAuthenticate, pAuthenticateData, unpack_uim_SLQSUIMAuthenticate, &authenticateResp);
    DisplayResult(__FUNCTION__, ret, &authenticateResp.ParamPresenceMask, (result_func)DisplayAuthenticate, (void*)&authenticateResp);
}

void GetConfiguration(QmiService* pQmiService, pack_uim_SLQSUIMGetConfiguration_t *pGetConfiguration)
{
    unpack_uim_SLQSUIMGetConfiguration_t getConfigurationResp;
    memset(&getConfigurationResp, 0, sizeof(getConfigurationResp));
    uint8_t autoSelection = 0xFF;
    getConfigurationResp.pAutoSelection = &autoSelection;
    uim_personalizationStatus personalizationStatus;
    memset(&personalizationStatus, 0, sizeof(personalizationStatus));
    getConfigurationResp.pPersonalizationStatus = &personalizationStatus;
    uint8_t haltSubscription = 0;
    getConfigurationResp.pHaltSubscription = &haltSubscription;
    uim_personalStatusOtherSlots personalizationStatusOtherSlots;
    memset(&personalizationStatusOtherSlots, 0, sizeof(personalizationStatusOtherSlots));
    getConfigurationResp.pPersonalizationStatusOtherSlots = &personalizationStatusOtherSlots;
    uim_tempDepersonalizationStatus tempDepersonalizationStatus;
    memset(&tempDepersonalizationStatus, 0, sizeof(tempDepersonalizationStatus));
    getConfigurationResp.pTempDepersonalizationStatus = &tempDepersonalizationStatus;
    uim_personalReactivationStatus  personalReactivationStatus;
    memset(&personalReactivationStatus, 0, sizeof(personalReactivationStatus));
    getConfigurationResp.pPersonalReactivationStatus = &personalReactivationStatus;
    uim_personalControlKeyPresent personalControlKeyPresent;
    memset(&personalControlKeyPresent, 0, sizeof(personalControlKeyPresent));
    getConfigurationResp.pPersonalControlKeyPresent = &personalControlKeyPresent;
    uim_inactiveSimLockConfig inactiveSimLockConfig;
    memset(&inactiveSimLockConfig, 0, sizeof(inactiveSimLockConfig));
    getConfigurationResp.pInactiveSimLockConfig = &inactiveSimLockConfig;

    int ret = SENDRECEIVE(pQmiService, pack_uim_SLQSUIMGetConfiguration, pGetConfiguration, unpack_uim_SLQSUIMGetConfiguration, &getConfigurationResp);
    DisplayResult(__FUNCTION__, ret, &getConfigurationResp.ParamPresenceMask, (result_func)DisplayConfiguration, (void*)&getConfigurationResp);
}

void ChangePin(QmiService* pQmiService, pack_uim_ChangePin_t *pChangePin)
{
    uint32_t IndicationToken = 0;
    uim_remainingRetries RemainingRetries;
    uim_encryptedPIN1    EncryptedPIN1;
    unpack_uim_ChangePin_t changePinResp = {&RemainingRetries, &EncryptedPIN1, &IndicationToken,1, SWI_UINT256_INT_VALUE };

    int ret = SENDRECEIVE(pQmiService, pack_uim_ChangePin, pChangePin, unpack_uim_ChangePin, &changePinResp);
    DisplayResult(__FUNCTION__, ret, &changePinResp.ParamPresenceMask, (result_func)DisplayChangePin, (void*)&changePinResp);
}

void ReadTransparent(QmiService* pQmiService)
{    /* UIM_READ_TRANSPARENT :This parameter contains the file information for ICCID Elementary File */
    uim_UIMSessionInformation sessionInfo_ICCID = { 0x00, 0x00, "" };
    uim_fileInfo             fileEF_ICCID  = { 0x2FE2, 0x02, {0x3F00} };
    uim_readTransparentInfo  readtp_ICCID   = { 0, 0 };

    uim_cardResult   CardResult;
    uim_readResult   ReadResult;
    uint32_t        IndicationToken = 0xffffffff;
    uint8_t         EncryptedData = 0xff;

    pack_uim_ReadTransparent_t req;
    unpack_uim_ReadTransparent_t readTransparent;

    memset(&req,0,sizeof(req));
    memset(&readTransparent,0,sizeof(readTransparent));

    memset(&CardResult,0,sizeof(CardResult));
    memset(&ReadResult,0,sizeof(ReadResult));

    memcpy(&(req.sessionInfo),&sessionInfo_ICCID,sizeof(uim_UIMSessionInformation));
    memcpy(&(req.fileIndex),&fileEF_ICCID,sizeof(uim_fileInfo));
    memcpy(&(req.readTransparent),&readtp_ICCID,sizeof(uim_readTransparentInfo));   
    req.pIndicationToken = NULL;
    req.pEncryptData     = NULL;

    readTransparent.pCardResult      = &CardResult;
    readTransparent.pEncryptedData   = &EncryptedData;
    readTransparent.pIndicationToken = &IndicationToken;
    readTransparent.pReadResult      = &ReadResult;

    int ret = SENDRECEIVE(pQmiService, pack_uim_ReadTransparent, &req, unpack_uim_ReadTransparent, &readTransparent);
    DisplayResult(__FUNCTION__, ret, &readTransparent.ParamPresenceMask, (result_func)DisplayReadTransparent, (void*)&readTransparent);

    ReadTransparent2(pQmiService);
}

void ReadTransparent2(QmiService* pQmiService)
{    /* UIM_READ_TRANSPARENT :This parameter contains the file information for IMSI Elementary File */
    uim_UIMSessionInformation sessionInfo_IMSI = { 0x00, 0x01, "1" };
    // EF-IMSI file from from 3GPP TS 31.102, section 4.2.2
    uim_fileInfo fileEF_IMSI = {
        0x6F07, // EF-IMSI File ID
        0x04, // Path len, 4 nibbles
        {0x3F00 ,0x7FFF}
        //EF-IMSI path
    }; //IMSI

    uim_readTransparentInfo readtp_IMSI = { 0, 0 };
    uim_cardResult CardResult;
    uim_readResult ReadResult;
    uint32_t IndicationToken = 0xffffffff;
    uint8_t EncryptedData = 0xff;
    pack_uim_ReadTransparent_t req;
    unpack_uim_ReadTransparent_t output;

    memset(&req,0,sizeof(req));
    memset(&output,0,sizeof(output));
    memset(&CardResult,0,sizeof(CardResult));
    memset(&ReadResult,0,sizeof(ReadResult));

    memcpy(&(req.sessionInfo),&sessionInfo_IMSI,sizeof(uim_UIMSessionInformation));
    memcpy(&(req.fileIndex),&fileEF_IMSI,sizeof(uim_fileInfo));
    memcpy(&(req.readTransparent),&readtp_IMSI,sizeof(uim_readTransparentInfo));

    req.pIndicationToken = NULL;
    req.pEncryptData = NULL;
    output.pCardResult = &CardResult;
    output.pEncryptedData = &EncryptedData;
    output.pIndicationToken = &IndicationToken;
    output.pReadResult = &ReadResult;

    int ret = SENDRECEIVE(pQmiService, pack_uim_ReadTransparent, &req, unpack_uim_ReadTransparent, &output);
    DisplayResult(__FUNCTION__, ret, &output.ParamPresenceMask, (result_func)DisplayReadTransparent2, (void*)&output);
}

void uim_indication_handler(uint16_t msgid, uint8_t *qmiData, uint32_t qmiDataSize)
{
    int rtn = 0;
    switch (msgid)
    {
        case eQMI_UIM_GET_FILE_ATTRIBUTES_IND:
        {
            unpack_uim_SLQSUIMGetFileAttibutes_Ind_t sGetFileAttributesInd;
            memset(&sGetFileAttributesInd, 0, sizeof(unpack_uim_SLQSUIMGetFileAttibutes_Ind_t));

            rtn = unpack_uim_GetFileAttributesInd_ind(qmiData, qmiDataSize, &sGetFileAttributesInd);
            DisplayResult("unpack_uim_GetFileAttributesInd_ind", rtn, NULL, (result_func)DisplayGetFileAttributesInd, (void*)&sGetFileAttributesInd);
        }
        break;
        case eQMI_UIM_SET_PIN_PROTECTION_IND:
        {
            unpack_uim_SetPinProtection_ind_t sSetPinProtectionInd;
            memset(&sSetPinProtectionInd, 0, sizeof(unpack_uim_VerifyPin_ind_t));
            uim_remainingRetries sRemainingRetries;
            uim_encryptedPIN1    sEncryptedPIN1;
            uim_cardResult  sCardResult;
            memset(&sRemainingRetries, 0, sizeof(uim_remainingRetries));
            memset(&sEncryptedPIN1, 0, sizeof(uim_encryptedPIN1));
            memset(&sCardResult, 0, sizeof(sCardResult));
            sSetPinProtectionInd.pRemainingRetries = &sRemainingRetries;
            sSetPinProtectionInd.pEncryptedPIN1 = &sEncryptedPIN1;
            sSetPinProtectionInd.pCardResult = &sCardResult;

            rtn = unpack_uim_SLQSUIMSetPinProtection_ind(qmiData, qmiDataSize, &sSetPinProtectionInd);
            DisplayResult("unpack_uim_SLQSUIMSetPinProtection_ind", rtn, NULL, (result_func)DisplaySetPinProtectionInd, (void*)&sSetPinProtectionInd);
        }
        break;
        case eQMI_UIM_VERIFY_PIN_IND:
        {
            unpack_uim_VerifyPin_ind_t sVerifyPinInd;
            memset(&sVerifyPinInd, 0, sizeof(unpack_uim_VerifyPin_ind_t));
            uim_remainingRetries sRemainingRetries;
            uim_encryptedPIN1    sEncryptedPIN1;
            uim_cardResult  sCardResult;
            memset(&sRemainingRetries, 0, sizeof(uim_remainingRetries));
            memset(&sEncryptedPIN1, 0, sizeof(uim_encryptedPIN1));
            memset(&sCardResult, 0, sizeof(sCardResult));
            sVerifyPinInd.pRemainingRetries = &sRemainingRetries;
            sVerifyPinInd.pEncryptedPIN1 = &sEncryptedPIN1;
            sVerifyPinInd.pCardResult = &sCardResult;

            rtn = unpack_uim_SLQSUIMVerifyPin_ind(qmiData, qmiDataSize, &sVerifyPinInd);
            DisplayResult("unpack_uim_SLQSUIMVerifyPin_ind", rtn, NULL, (result_func)DisplayVerifyPinInd, (void*)&sVerifyPinInd);
        }
        break;
        case eQMI_UIM_UNBLOCK_PIN_IND:
        {
            unpack_uim_UnblockPin_ind_t sUnblockPinInd;
            memset(&sUnblockPinInd, 0, sizeof(unpack_uim_UnblockPin_ind_t));
            uim_remainingRetries sRemainingRetries;
            uim_encryptedPIN1    sEncryptedPIN1;
            uim_cardResult  sCardResult;
            memset(&sRemainingRetries, 0, sizeof(uim_remainingRetries));
            memset(&sEncryptedPIN1, 0, sizeof(uim_encryptedPIN1));
            memset(&sCardResult, 0, sizeof(sCardResult));
            sUnblockPinInd.pRemainingRetries = &sRemainingRetries;
            sUnblockPinInd.pEncryptedPIN1 = &sEncryptedPIN1;
            sUnblockPinInd.pCardResult = &sCardResult;

            rtn = unpack_uim_SLQSUIMUnblockPin_ind(qmiData, qmiDataSize, &sUnblockPinInd);
            DisplayResult("unpack_uim_SLQSUIMUnblockPin_ind", rtn, NULL, (result_func)DisplayUnblockPinInd, (void*)&sUnblockPinInd);
        }
        break;
        case eQMI_UIM_CHANGE_PIN_IND:
        {
            unpack_uim_ChangePin_ind_t sChangePinInd;
            memset(&sChangePinInd, 0, sizeof(unpack_uim_ChangePin_ind_t));
            uim_remainingRetries sRemainingRetries;
            uim_encryptedPIN1    sEncryptedPIN1;
            uim_cardResult  sCardResult;
            memset(&sRemainingRetries, 0, sizeof(uim_remainingRetries));
            memset(&sEncryptedPIN1, 0, sizeof(uim_encryptedPIN1));
            memset(&sCardResult, 0, sizeof(sCardResult));
            sChangePinInd.pRemainingRetries = &sRemainingRetries;
            sChangePinInd.pEncryptedPIN1 = &sEncryptedPIN1;
            sChangePinInd.pCardResult = &sCardResult;

            rtn = unpack_uim_SLQSUIMChangePin_ind(qmiData, qmiDataSize, &sChangePinInd);
            DisplayResult("unpack_uim_SLQSUIMChangePin_ind", rtn, NULL, (result_func)DisplayChangePinInd, (void*)&sChangePinInd);
        }
        break;
        case eQMI_UIM_STATUS_CHANGE_IND:
        {
            unpack_uim_SLQSUIMSetStatusChangeCallBack_ind_t sStatusChangeInd;
            memset(&sStatusChangeInd, 0, sizeof(unpack_uim_SLQSUIMSetStatusChangeCallBack_ind_t));
            uim_cardStatus sCardStatus;
            memset(&sCardStatus, 0, sizeof(uim_cardStatus));
            sStatusChangeInd.pCardStatus = &sCardStatus;

            rtn = unpack_uim_SLQSUIMSetStatusChangeCallBack_ind(qmiData, qmiDataSize, &sStatusChangeInd);
            DisplayResult("unpack_uim_SLQSUIMSetStatusChangeCallBack_ind", rtn, NULL, (result_func)DisplaySetStatusChangeInd, (void*)&sStatusChangeInd);
        }
        break;
        case eQMI_UIM_REFRESH_IND:
        {
            unpack_uim_SLQSUIMRefreshCallback_Ind_t sRefreshIndication;
            memset(&sRefreshIndication, 0, sizeof(unpack_uim_SLQSUIMRefreshCallback_Ind_t));
            rtn = unpack_uim_SLQSUIMRefreshCallback_Ind(qmiData, qmiDataSize, &sRefreshIndication);
            DisplayResult("unpack_uim_SLQSUIMRefreshCallback_Ind", rtn, NULL, (result_func)DisplayRefreshInd, (void*)&sRefreshIndication);
        }
        break;
        case eQMI_UIM_AUTHENTICATE_IND:
        {
            unpack_uim_Authenticate_ind_t sAuthenticateInd;
            memset(&sAuthenticateInd, 0, sizeof(unpack_uim_Authenticate_ind_t));
            uim_cardResult  sCardResult;
            memset(&sCardResult, 0, sizeof(uim_cardResult));
            uim_authenticationResult  sAuthenticationResult;
            uint8_t arrContent[1024] = {0};
            sAuthenticationResult.content_len = 1024;
            sAuthenticationResult.pContent = arrContent;

            sAuthenticateInd.pCardResult = &sCardResult;
            sAuthenticateInd.pAuthenticationResult = &sAuthenticationResult;

            rtn = unpack_uim_SLQSUIMAuthenticate_ind(qmiData, qmiDataSize, &sAuthenticateInd);
            DisplayResult("unpack_uim_SLQSUIMAuthenticate_ind", rtn, NULL, (result_func)DisplayAuthenticateInd, (void*)&sAuthenticateInd);
        }
        break;
        case eQMI_UIM_SLOT_STATUS_IND:
        {
            unpack_uim_SetUimSlotStatusChangeCallback_ind_t sSlotStatusChangeCallback_ind;
            memset(&sSlotStatusChangeCallback_ind, 0, sizeof(unpack_uim_SetUimSlotStatusChangeCallback_ind_t));
            rtn = unpack_uim_SetUimSlotStatusChangeCallback_ind(qmiData, qmiDataSize, &sSlotStatusChangeCallback_ind);
            DisplayResult("unpack_uim_SetUimSlotStatusChangeCallback_ind", rtn, NULL, (result_func)DisplaySlotStatusChangeInd, (void*)&sSlotStatusChangeCallback_ind);
        }
        break;
    }
}
