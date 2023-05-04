#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "lite-qmi-uim.h"
#include "uim.h"

#include "command_set.h"

typedef struct
{
	uint32_t value;
	const char* szText;
}Map_ValueText;

const char* GetMapStringFromValue(uint32_t val, Map_ValueText* pMaps, int sizeMap)
{
	for (int i = 0; i < sizeMap; i++)
	{
		if (pMaps[i].value == val)
			return pMaps[i].szText;
	}

	return "Unknown";
}

#define GET_MAP_STRING(v, m) GetMapStringFromValue((v), (m), sizeof((m))/sizeof(Map_ValueText))

static Map_ValueText g_Table_PhyCardStatus[] =
{
  {0, "Unknown"},
  {1, "Absent"},
  {2, "Present"},
};

static Map_ValueText g_Table_PhySlotStatus[] =
{
  {0, "Inactive"},
  {1, "Activate"},
};

static Map_ValueText g_Table_LogicalSlot[] =
{
  {1, "Slot 1"},
  {2, "Slot 2"},
  {3, "Slot 3"},
  {4, "Slot 4"},
  {5, "Slot 5"},
 };

void DisplaySlotsStatus(unpack_uim_SLQSUIMGetSlotsStatus_t *pSlotStatus)
{
    uint8_t idx = 0, jdx = 0;
    swi_uint256_print_mask (pSlotStatus->ParamPresenceMask);
    if((pSlotStatus->pNumberOfPhySlot) && (pSlotStatus->pUimSlotsStatus)  && (swi_uint256_get_bit (pSlotStatus->ParamPresenceMask, 16)))
    {
        SockPrintf("\nPhysical Slot Status Length:%d\n",*(pSlotStatus->pNumberOfPhySlot));
        for( idx = 0; idx < *(pSlotStatus->pNumberOfPhySlot); idx++)
        {
            SockPrintf("\t%d. Physical Card Status :%s\n", idx+1, GET_MAP_STRING(pSlotStatus->pUimSlotsStatus->uimSlotStatus[idx].uPhyCardStatus, g_Table_PhyCardStatus));
            SockPrintf("\t%d. Physical Slot Status :%s\n", idx+1, GET_MAP_STRING(pSlotStatus->pUimSlotsStatus->uimSlotStatus[idx].uPhySlotStatus, g_Table_PhySlotStatus));
            SockPrintf("\t%d. Logical Slot :%s\n", idx+1, GET_MAP_STRING(pSlotStatus->pUimSlotsStatus->uimSlotStatus[idx].bLogicalSlot, g_Table_LogicalSlot));
            SockPrintf("\t%d. ICCID Length :%d\n", idx+1, pSlotStatus->pUimSlotsStatus->uimSlotStatus[idx].bICCIDLength);
            SockPrintf("\t%d. ICCID :",idx+1);
            for(jdx=0; jdx<pSlotStatus->pUimSlotsStatus->uimSlotStatus[idx].bICCIDLength; jdx++)
                SockPrintf("%02X ",pSlotStatus->pUimSlotsStatus->uimSlotStatus[idx].bICCID[jdx]);
            SockPrintf("\n");
        }
    }
}

void DisplayVerifyPin(unpack_uim_VerifyPin_t *pVerifyPinResult)
{
    int lcount;

    swi_uint256_print_mask (pVerifyPinResult->ParamPresenceMask);
    SockPrintf("%s Result: %d\n",__FUNCTION__, pVerifyPinResult->Tlvresult);

     if (( NULL !=  pVerifyPinResult->pRemainingRetries ) && (swi_uint256_get_bit (pVerifyPinResult->ParamPresenceMask, 16)))
     {
         SockPrintf("Retry Remaining(Verify PIN) : %d \n",
                           pVerifyPinResult->pRemainingRetries->verifyLeft);
         SockPrintf("Retry Remaining(Unblock PIN): %d \n",
                           pVerifyPinResult->pRemainingRetries->unblockLeft);
     }
     if (( NULL !=  pVerifyPinResult->pEncryptedPIN1 ) && (swi_uint256_get_bit (pVerifyPinResult->ParamPresenceMask, 17)))
     {
         SockPrintf("Encrypted PIN1 Len : %d \n",
                           pVerifyPinResult->pEncryptedPIN1->pin1Len);
         SockPrintf("Encrypted PIN1 Value : ");
         for (lcount = 0;lcount < pVerifyPinResult->pEncryptedPIN1->pin1Len ;lcount++)
         {
             SockPrintf("%d,", pVerifyPinResult->pEncryptedPIN1->pin1Val[lcount]);
         }
         SockPrintf("\n");
     }
     if (( NULL != pVerifyPinResult->pIndicationToken ) && (swi_uint256_get_bit (pVerifyPinResult->ParamPresenceMask, 18)))
         SockPrintf("Indication Token : %d \n",*pVerifyPinResult->pIndicationToken);
}

void DisplayCardStatus(uim_cardStatus *pCardStatus)
{
    int lcount,lIcount1,lIcount;

    SockPrintf("Index of the primary GW   : 0x%x\n",
                        pCardStatus->indexGwPri);
    SockPrintf("Index of the primary 1X   : 0x%x\n",
                            pCardStatus->index1xPri);
    SockPrintf("Index of the secondary GW : 0x%x\n",
                            pCardStatus->indexGwSec);
    SockPrintf("Index of the secondary 1X : 0x%x\n",
                            pCardStatus->index1xSec);
    SockPrintf("Slots Available           : 0x%x\n",
                            pCardStatus->numSlot);

    for ( lcount=0 ; lcount < pCardStatus->numSlot; lcount++ )
    {
        uim_slotInfo *temp = &pCardStatus->SlotInfo[lcount];
        SockPrintf( "  Information for SLOT%d\n",lcount+1);
        SockPrintf( "  State of the Card         : %x\n", temp->cardState);
        SockPrintf( "  State of the UPIN         : %x\n", temp->upinState);
        SockPrintf( "  Retries Remaining(UPIN)   : %d\n", temp->upinRetries);
        SockPrintf( "  Retries Remaining(UPUK)   : %d\n", temp->upukRetries);
        SockPrintf( "  Reason For Error          : %x\n", temp->errorState);
        SockPrintf( "  No. of Apps Allowed       : %d\n", temp->numApp);
        for ( lIcount=0 ; lIcount < temp->numApp; lIcount++ )
        {
            uim_appStatus *lresp = &temp->AppStatus[lIcount];
            SockPrintf( "   Application Status Information for App%d\n",lIcount+1);
            SockPrintf( "   Type of Application       : 0x%x\n", lresp->appType);
            SockPrintf( "   State of Application      : 0x%x\n", lresp->appState);
            SockPrintf( "   State of perso for App    : 0x%x\n", lresp->persoState);
            SockPrintf( "   Indicates perso feature   : 0x%x\n", lresp->persoFeature);
            SockPrintf( "   Retries Remaining(Perso BL): %d\n",
                                    lresp->persoRetries);
            SockPrintf( "    Retries Remaining(Perso UB): %d\n",
                                    lresp->persoUnblockRetries);
            SockPrintf( "    Application Identifier Len: %d\n", lresp->aidLength);
            SockPrintf( "    Application Identifier Value : ");
            for ( lIcount1=0 ; lIcount1 < lresp->aidLength; lIcount1++ )
            {
                SockPrintf( "%02x ", lresp->aidVal[lIcount1]);
            }
            SockPrintf("\n");
            SockPrintf( "    Indication for UPIN       : 0x%x\n", lresp->univPin);
            SockPrintf( "    Indicates State of Pin1   : 0x%x\n", lresp->pin1State);
            SockPrintf( "    Retries Remaining(PIN1)   : 0x%d\n", lresp->pin1Retries);
            SockPrintf( "    Retries Remaining(PUK1)   : 0x%d\n", lresp->puk1Retries);
            SockPrintf( "    Indicates State of Pin2   : 0x%x\n", lresp->pin2State);
            SockPrintf( "    Retries Remaining(PIN2)   : 0x%d\n", lresp->pin2Retries);
            SockPrintf( "    Retries Remaining(PUK2)   : 0x%d\n", lresp->puk2Retries);
        }
    }
}

void DisplayGetCardStatus(unpack_uim_GetCardStatus_t *pGetCardStatus)
{
    int lcount;
    swi_uint256_print_mask (pGetCardStatus->ParamPresenceMask);
    SockPrintf("\n%s Result: %d\n",__FUNCTION__, pGetCardStatus->Tlvresult);
    if((pGetCardStatus->pCardStatus) && (swi_uint256_get_bit (pGetCardStatus->ParamPresenceMask, 16)))
    {
        DisplayCardStatus(pGetCardStatus->pCardStatus);
    }
    if (( pGetCardStatus->pHotSwapStatus ) && (swi_uint256_get_bit (pGetCardStatus->ParamPresenceMask, 17)))
    {
        SockPrintf("Hot Swap Length           : %d\n",
                pGetCardStatus->pHotSwapStatus->hotSwapLength);
        SockPrintf("Status of HotSwap Switch  : ");
        for ( lcount=0 ; lcount < pGetCardStatus->pHotSwapStatus->hotSwapLength; lcount++ )
        {
            SockPrintf("%x", pGetCardStatus->pHotSwapStatus->hotSwap[lcount]);
        }
        SockPrintf("\n");
    }
}

void DisplaySetPinProtection(unpack_uim_SetPinProtection_t *pSetPinProtection)
{
    int lcount;
    swi_uint256_print_mask (pSetPinProtection->ParamPresenceMask);
    SockPrintf("%s Result: %d\n",__FUNCTION__, pSetPinProtection->Tlvresult);

    if (( NULL !=  pSetPinProtection->pRemainingRetries ) && (swi_uint256_get_bit (pSetPinProtection->ParamPresenceMask, 16)))
    {
        SockPrintf("Retry Remaining(Verify PIN) : %d \n",
                          pSetPinProtection->pRemainingRetries->verifyLeft);
        SockPrintf("Retry Remaining(Unblock PIN): %d \n",
                           pSetPinProtection->pRemainingRetries->unblockLeft);
    }
    if (( NULL !=  pSetPinProtection->pEncryptedPIN1 ) && (swi_uint256_get_bit (pSetPinProtection->ParamPresenceMask, 17)))
    {
        SockPrintf("Encrypted PIN1 Len : %d \n",
                    pSetPinProtection->pEncryptedPIN1->pin1Len);
        SockPrintf("Encrypted PIN1 Value : ");
        for (lcount = 0;lcount < pSetPinProtection->pEncryptedPIN1->pin1Len ;lcount++)
        {
            SockPrintf("%d,", pSetPinProtection->pEncryptedPIN1->pin1Val[lcount]);
        }
        SockPrintf("\n");
    }
    if (( NULL != pSetPinProtection->pIndicationToken ) && (swi_uint256_get_bit (pSetPinProtection->ParamPresenceMask, 18)))
        SockPrintf("Indication Token : %d \n",*pSetPinProtection->pIndicationToken);
}

void DisplayUnblockPin(unpack_uim_UnblockPin_t *pUnblockPinResult)
{
    int lcount;
    swi_uint256_print_mask (pUnblockPinResult->ParamPresenceMask);
    SockPrintf("%s Result: %d\n",__FUNCTION__, pUnblockPinResult->Tlvresult);
    
     if (( NULL !=  pUnblockPinResult->pRemainingRetries ) && (swi_uint256_get_bit (pUnblockPinResult->ParamPresenceMask, 16)))
     {
         SockPrintf("Retry Remaining(Verify PIN) : %d \n",
                           pUnblockPinResult->pRemainingRetries->verifyLeft);
         SockPrintf("Retry Remaining(Unblock PIN): %d \n",
                           pUnblockPinResult->pRemainingRetries->unblockLeft);
     }
     if (( NULL !=  pUnblockPinResult->pEncryptedPIN1 ) && (swi_uint256_get_bit (pUnblockPinResult->ParamPresenceMask, 17)))
     {
         SockPrintf("Encrypted PIN1 Len : %d \n",
                           pUnblockPinResult->pEncryptedPIN1->pin1Len);
         SockPrintf("Encrypted PIN1 Value : ");
         for (lcount = 0;lcount < pUnblockPinResult->pEncryptedPIN1->pin1Len ;lcount++)
         {
             SockPrintf("%d,", pUnblockPinResult->pEncryptedPIN1->pin1Val[lcount]);
         }
         SockPrintf("\n");
     }
     if (( NULL != pUnblockPinResult->pIndicationToken ) && (swi_uint256_get_bit (pUnblockPinResult->ParamPresenceMask, 18)))
         SockPrintf("Indication Token : %d \n",*pUnblockPinResult->pIndicationToken);
}

void DisplayFileAttributes(unpack_uim_SLQSUIMGetFileAttributes_t *pGetFileAttributesResp)
{
    uint16_t lcount;
    swi_uint256_print_mask (pGetFileAttributesResp->ParamPresenceMask);
    if (( NULL != pGetFileAttributesResp->pCardResult ) && (swi_uint256_get_bit (pGetFileAttributesResp->ParamPresenceMask, 16)))
        {
            SockPrintf( "SW1 received from card :%x\n", pGetFileAttributesResp->pCardResult->sw1 );
            SockPrintf( "SW2 received from card :%x\n", pGetFileAttributesResp->pCardResult->sw2 );
        }
    if (( NULL != pGetFileAttributesResp->pFileAttributes ) && (swi_uint256_get_bit (pGetFileAttributesResp->ParamPresenceMask, 17)))
        {
            SockPrintf( "File Size        : %d\n",pGetFileAttributesResp->pFileAttributes->fileSize);
            SockPrintf( "File ID          : %x\n",pGetFileAttributesResp->pFileAttributes->fileID);
            SockPrintf( "File Type        : %x\n",pGetFileAttributesResp->pFileAttributes->fileType);
            SockPrintf( "Record Size      : %d\n",pGetFileAttributesResp->pFileAttributes->recordSize);
            SockPrintf( "Record Count     : %d\n",pGetFileAttributesResp->pFileAttributes->recordCount);
            SockPrintf( "Security Read    : %x\n",pGetFileAttributesResp->pFileAttributes->secRead);
            SockPrintf( "Security Read M  : %x\n",pGetFileAttributesResp->pFileAttributes->secReadMask);
            SockPrintf( "Security Write   : %x\n",pGetFileAttributesResp->pFileAttributes->secWrite);
            SockPrintf( "Security Write M : %x\n",pGetFileAttributesResp->pFileAttributes->secWriteMask);
            SockPrintf( "Security Inc     : %x\n",pGetFileAttributesResp->pFileAttributes->secIncrease);
            SockPrintf( "Security Inc M   : %x\n",pGetFileAttributesResp->pFileAttributes->secIncreaseMask);
            SockPrintf( "Security De-Act  : %x\n",pGetFileAttributesResp->pFileAttributes->secDeactivate);
            SockPrintf( "Security De-Act M: %x\n",pGetFileAttributesResp->pFileAttributes->secDeactivateMask);
            SockPrintf( "Security Act     : %x\n",pGetFileAttributesResp->pFileAttributes->secActivate);
            SockPrintf( "Security Act M   : %x\n",pGetFileAttributesResp->pFileAttributes->secActivateMask);
            SockPrintf( "Raw Len          : %d\n",pGetFileAttributesResp->pFileAttributes->rawLen);
            SockPrintf( "Raw Value        : ");
            for ( lcount=0 ; lcount < pGetFileAttributesResp->pFileAttributes->rawLen ; lcount++ )
                {
                    SockPrintf( "%x ",pGetFileAttributesResp->pFileAttributes->rawValue[lcount]);
                }
        }
    SockPrintf( "\n");
    if((pGetFileAttributesResp->pIndicationToken != NULL) && (swi_uint256_get_bit (pGetFileAttributesResp->ParamPresenceMask, 18)))
        SockPrintf( "Indication Token : %d\n",*pGetFileAttributesResp->pIndicationToken );
    if((pGetFileAttributesResp->pFileStatus != NULL) && (swi_uint256_get_bit (pGetFileAttributesResp->ParamPresenceMask, 19)))
        SockPrintf( "File Status : %x\n",*pGetFileAttributesResp->pFileStatus);
    SockPrintf("%s done\n", __func__);
}

void DisplayAuthenticate(unpack_uim_SLQSUIMAuthenticate_t *pAuthenticateResp)
{
    uint16_t lcount;

    swi_uint256_print_mask (pAuthenticateResp->ParamPresenceMask);
    if (( NULL != pAuthenticateResp->pCardResult ) && (swi_uint256_get_bit (pAuthenticateResp->ParamPresenceMask, 16)))
    {
        SockPrintf( "SW1 received from card :%x", pAuthenticateResp->pCardResult->sw1 );
        SockPrintf( "SW2 received from card :%x", pAuthenticateResp->pCardResult->sw2 );
    }
    if (( NULL != pAuthenticateResp->pAuthenticateResult ) && (swi_uint256_get_bit (pAuthenticateResp->ParamPresenceMask, 17)))
    {
        SockPrintf( "Content Len  : %d\n",pAuthenticateResp->pAuthenticateResult->contentLen );
        SockPrintf( "Content      : ");
        for ( lcount=0 ; lcount < pAuthenticateResp->pAuthenticateResult->contentLen ; lcount++ )
        {
            SockPrintf( "%c",pAuthenticateResp->pAuthenticateResult->content[lcount]);
        }
        SockPrintf( "\n");
    }
    if((pAuthenticateResp->pIndicationToken != NULL) && (swi_uint256_get_bit (pAuthenticateResp->ParamPresenceMask, 18)))
        SockPrintf( "Indication Token : %d\n",*pAuthenticateResp->pIndicationToken );
}

void DisplayConfiguration(unpack_uim_SLQSUIMGetConfiguration_t *pGetConfigurationResp)
{
    uint16_t count;
    swi_uint256_print_mask (pGetConfigurationResp->ParamPresenceMask);
    if((NULL != pGetConfigurationResp->pAutoSelection) && (swi_uint256_get_bit (pGetConfigurationResp->ParamPresenceMask, 0x10)))
        SockPrintf( "Automatic Selection : 0x%02X \n",*pGetConfigurationResp->pAutoSelection);
    if (( NULL != pGetConfigurationResp->pPersonalizationStatus ) && (swi_uint256_get_bit (pGetConfigurationResp->ParamPresenceMask, 0x11)))
        {
            SockPrintf( "Personalization Status: Num features = %d\n", pGetConfigurationResp->pPersonalizationStatus->numFeatures );
            for(count=0; count < pGetConfigurationResp->pPersonalizationStatus->numFeatures;count++)
            {
                SockPrintf( "feature: 0x%02X \n",pGetConfigurationResp->pPersonalizationStatus->feature[count] );
                SockPrintf( "verify left: 0x%02X \n",pGetConfigurationResp->pPersonalizationStatus->verifyLeft[count]);
                SockPrintf( "unblock left: 0x%02X \n",pGetConfigurationResp->pPersonalizationStatus->unblockLeft[count] );
            }
        }
    if((NULL != pGetConfigurationResp->pHaltSubscription) && (swi_uint256_get_bit (pGetConfigurationResp->ParamPresenceMask, 0x12)))
        SockPrintf( "HALT Subscription : 0x%02X \n", *pGetConfigurationResp->pHaltSubscription);

    if (( NULL != pGetConfigurationResp->pPersonalizationStatusOtherSlots ) && (swi_uint256_get_bit (pGetConfigurationResp->ParamPresenceMask, 0x13)))
    {
        SockPrintf( "Personalization Status: Num features = %d\n", pGetConfigurationResp->pPersonalizationStatusOtherSlots->extended_personalization_status_len );
        SockPrintf( "Personalization Status: Num features = %d\n", pGetConfigurationResp->pPersonalizationStatusOtherSlots->personalization_status_len );            
        for(count=0; count < pGetConfigurationResp->pPersonalizationStatusOtherSlots->extended_personalization_status_len; count++)
        {
            SockPrintf( "feature: 0x%02X \n",pGetConfigurationResp->pPersonalizationStatusOtherSlots->feature[count] );
            SockPrintf( "verify left: 0x%02X \n",pGetConfigurationResp->pPersonalizationStatusOtherSlots->verifyLeft[count]);
            SockPrintf( "unblock left: 0x%02X \n",pGetConfigurationResp->pPersonalizationStatusOtherSlots->unblockLeft[count] );
        }
        for(count=0; count < pGetConfigurationResp->pPersonalizationStatusOtherSlots->personalization_status_len; count++)
        {
            SockPrintf( "feature: 0x%02X \n",pGetConfigurationResp->pPersonalizationStatusOtherSlots->feature[count] );
            SockPrintf( "verify left: 0x%02X \n",pGetConfigurationResp->pPersonalizationStatusOtherSlots->verifyLeft[count]);
            SockPrintf( "unblock left: 0x%02X \n",pGetConfigurationResp->pPersonalizationStatusOtherSlots->unblockLeft[count] );
        }
    }
    if(swi_uint256_get_bit (pGetConfigurationResp->ParamPresenceMask, 0x14))
        SockPrintf( "USB UICC supported flag: %d \n", pGetConfigurationResp->usb_uicc_supported);
    if(swi_uint256_get_bit (pGetConfigurationResp->ParamPresenceMask, 0x15))
        SockPrintf( "Support for SAP in client mode: %d \n", pGetConfigurationResp->sap_client_supported);

    if (( NULL != pGetConfigurationResp->pTempDepersonalizationStatus ) && (swi_uint256_get_bit (pGetConfigurationResp->ParamPresenceMask, 0x16)))
    {
        SockPrintf( "temporary_depersonalization_status_len = %d\n", pGetConfigurationResp->pTempDepersonalizationStatus->temporary_depersonalization_status_len );
        SockPrintf( "temporary_unlock_status_len = %d\n", pGetConfigurationResp->pTempDepersonalizationStatus->temporary_unlock_status_len );            
        for(count=0; count < pGetConfigurationResp->pTempDepersonalizationStatus->temporary_depersonalization_status_len; count++)
        {
            SockPrintf( "feature: 0x%02X \n",pGetConfigurationResp->pTempDepersonalizationStatus->feature[count] );
            SockPrintf( "temporary_unlock_time_left: %d \n",pGetConfigurationResp->pTempDepersonalizationStatus->temporary_unlock_time_left[count]);
        }
        for(count=0; count < pGetConfigurationResp->pTempDepersonalizationStatus->temporary_unlock_status_len; count++)
        {
            SockPrintf( "feature: 0x%02X \n",pGetConfigurationResp->pTempDepersonalizationStatus->feature[count] );
            SockPrintf( "temporary_unlock_time_left: %d \n",pGetConfigurationResp->pTempDepersonalizationStatus->temporary_unlock_time_left[count]);
        }
    }

    if (( NULL != pGetConfigurationResp->pPersonalReactivationStatus ) && (swi_uint256_get_bit (pGetConfigurationResp->ParamPresenceMask, 0x17)))
    {
        SockPrintf( "perso_reactivation_status_len = %d\n", pGetConfigurationResp->pPersonalReactivationStatus->perso_reactivation_status_len );
        for(count=0; count < pGetConfigurationResp->pPersonalReactivationStatus->perso_reactivation_status_len; count++)
        {
            SockPrintf( "slot: %d \n",pGetConfigurationResp->pPersonalReactivationStatus->slot[count]);
            SockPrintf( "feature: 0x%02X \n",pGetConfigurationResp->pPersonalReactivationStatus->feature[count] );
            SockPrintf( "verifyLeft: %d \n",pGetConfigurationResp->pPersonalReactivationStatus->verifyLeft[count]);
            SockPrintf( "unblockLeft: %d \n",pGetConfigurationResp->pPersonalReactivationStatus->unblockLeft[count]);
        }
    }

    if (( NULL != pGetConfigurationResp->pPersonalControlKeyPresent ) && (swi_uint256_get_bit (pGetConfigurationResp->ParamPresenceMask, 0x18)))
    {
        SockPrintf( "perso_control_key_present_len = %d\n", pGetConfigurationResp->pPersonalControlKeyPresent->perso_control_key_present_len );
        SockPrintf( "feature_control_key_present_len = %d\n", pGetConfigurationResp->pPersonalControlKeyPresent->feature_control_key_present_len );
        for(count=0; count < pGetConfigurationResp->pPersonalControlKeyPresent->perso_control_key_present_len; count++)
        {
            SockPrintf( "feature: 0x%02X \n",pGetConfigurationResp->pPersonalControlKeyPresent->feature[count] );
            SockPrintf( "ck_present: %d \n",pGetConfigurationResp->pPersonalControlKeyPresent->ck_present[count]);
        }
    }

    if(swi_uint256_get_bit (pGetConfigurationResp->ParamPresenceMask, 0x19))
        SockPrintf( "remote_simlock_storage: %d \n", pGetConfigurationResp->remote_simlock_storage);
    if(swi_uint256_get_bit (pGetConfigurationResp->ParamPresenceMask, 0x1A))
        SockPrintf( "emergency_only_mode: %d \n", pGetConfigurationResp->emergency_only_mode);
    if(swi_uint256_get_bit (pGetConfigurationResp->ParamPresenceMask, 0x1B))
        SockPrintf( "extended_apdu: %d \n", pGetConfigurationResp->extended_apdu);

    if (( NULL != pGetConfigurationResp->pInactiveSimLockConfig ) && (swi_uint256_get_bit (pGetConfigurationResp->ParamPresenceMask, 0x1C)))
    {
        SockPrintf( "inactive_simlock_config_len = %d\n", pGetConfigurationResp->pInactiveSimLockConfig->inactive_simlock_config_len );

        for(count=0; count < pGetConfigurationResp->pInactiveSimLockConfig->inactive_simlock_config_len; count++)
        {
            SockPrintf( "config_id: %d \n",pGetConfigurationResp->pInactiveSimLockConfig->simLockConfig[count].config_id );
            SockPrintf( "config_nickname_len: %d \n",pGetConfigurationResp->pInactiveSimLockConfig->simLockConfig[count].config_nickname_len);
            SockPrintf( "config_nickname: %s \n",pGetConfigurationResp->pInactiveSimLockConfig->simLockConfig[count].config_nickname);
        }
    }
}

void DisplayChangePin(unpack_uim_ChangePin_t *pChangePinResp)
{
    int lcount;
    swi_uint256_print_mask (pChangePinResp->ParamPresenceMask);
    SockPrintf("%s Result: %d\n",__FUNCTION__, pChangePinResp->Tlvresult);

     if (( NULL !=  pChangePinResp->pRemainingRetries ) && (swi_uint256_get_bit (pChangePinResp->ParamPresenceMask, 16)))
     {
         SockPrintf("Retry Remaining(Verify PIN) : %d \n",
                           pChangePinResp->pRemainingRetries->verifyLeft);
         SockPrintf("Retry Remaining(Unblock PIN): %d \n",
                           pChangePinResp->pRemainingRetries->unblockLeft);
     }
     if (( NULL !=  pChangePinResp->pEncryptedPIN1 ) && (swi_uint256_get_bit (pChangePinResp->ParamPresenceMask, 17)))
     {
         SockPrintf("Encrypted PIN1 Len : %d \n",
                           pChangePinResp->pEncryptedPIN1->pin1Len);
         SockPrintf("Encrypted PIN1 Value : ");
         for (lcount = 0;lcount < pChangePinResp->pEncryptedPIN1->pin1Len ;lcount++)
         {
             SockPrintf("%d,", pChangePinResp->pEncryptedPIN1->pin1Val[lcount]);
         }
         SockPrintf("\n");
     }
     if (( NULL != pChangePinResp->pIndicationToken ) && (swi_uint256_get_bit (pChangePinResp->ParamPresenceMask, 18)))
         SockPrintf("Indication Token : %d \n",*pChangePinResp->pIndicationToken);
}

void DisplayGetLastEvent(unpack_uim_SLQSUIMRefreshGetLastEvent_t *pRefreshGetLastEventResp)
{
    uint16_t lCount;
    uint16_t lIcount;

    swi_uint256_print_mask (pRefreshGetLastEventResp->ParamPresenceMask);
    if((pRefreshGetLastEventResp->pRefreshEvent!=NULL) && (swi_uint256_get_bit (pRefreshGetLastEventResp->ParamPresenceMask, 16)))
    {
        SockPrintf("Parameter Indication refresh\n");
        SockPrintf("Stage:      %d\n", pRefreshGetLastEventResp->pRefreshEvent->stage );
        SockPrintf("Mode:       %d\n", pRefreshGetLastEventResp->pRefreshEvent->mode );
        SockPrintf("sessionType:%d\n", pRefreshGetLastEventResp->pRefreshEvent->sessionType);
        SockPrintf("aidLength: %d\n", pRefreshGetLastEventResp->pRefreshEvent->aidLength);

        uim_refreshevent *pTemp = pRefreshGetLastEventResp->pRefreshEvent;
        for ( lCount = 0; lCount < pTemp->aidLength ; lCount++ )
        {
            SockPrintf("Mode of Refresh = %d\n", pTemp->aid[lCount]);
        }

        SockPrintf(" Number of files = %d\n", pTemp->numOfFiles);
        for ( lCount = 0; lCount < pTemp->numOfFiles; lCount++ )
        {
            SockPrintf("FileID= %d\n", pRefreshGetLastEventResp->pRefreshEvent->arrfileInfo[lCount].fileID);
            SockPrintf("Path Length = %d\n", pRefreshGetLastEventResp->pRefreshEvent->arrfileInfo[lCount].pathLen);
            for ( lIcount = 0;lIcount < pRefreshGetLastEventResp->pRefreshEvent->arrfileInfo[lCount].pathLen; lIcount++ )
            {
                SockPrintf(" Path = %x", pRefreshGetLastEventResp->pRefreshEvent->arrfileInfo[lCount].path[lIcount]);
            }
        }
    }
    if((pRefreshGetLastEventResp->pRefresh_enforcement_policy_mask!=NULL) && (swi_uint256_get_bit (pRefreshGetLastEventResp->ParamPresenceMask, 16)))
    {
        SockPrintf("Refresh enforcement policy\n");
        SockPrintf("    Mask:      %d\n", *pRefreshGetLastEventResp->pRefresh_enforcement_policy_mask );
    }
}

void DisplayGetFileAttributesInd(unpack_uim_SLQSUIMGetFileAttibutes_Ind_t *pGetFileAttributesInd)
{
    swi_uint256_print_mask (pGetFileAttributesInd->ParamPresenceMask);

    if (swi_uint256_get_bit (pGetFileAttributesInd->ParamPresenceMask, 1))
    {
        SockPrintf( "Indication Token:%d\n", pGetFileAttributesInd->indication_token );
    }
    if (swi_uint256_get_bit (pGetFileAttributesInd->ParamPresenceMask, 0x10))
    {
        SockPrintf( "SW1 received from card :%x\n", pGetFileAttributesInd->cardResult.sw1 );
        SockPrintf( "SW2 received from card :%x\n", pGetFileAttributesInd->cardResult.sw2 );
    }
    if (swi_uint256_get_bit (pGetFileAttributesInd->ParamPresenceMask, 0x11))
    {
        int lcount;

        SockPrintf( "File Size        : %d\n",pGetFileAttributesInd->fileAttributes.fileSize);
        SockPrintf( "File ID          : %x\n",pGetFileAttributesInd->fileAttributes.fileID);
        SockPrintf( "File Type        : %x\n",pGetFileAttributesInd->fileAttributes.fileType);
        SockPrintf( "Record Size      : %d\n",pGetFileAttributesInd->fileAttributes.recordSize);
        SockPrintf( "Record Count     : %d\n",pGetFileAttributesInd->fileAttributes.recordCount);
        SockPrintf( "Security Read    : %x\n",pGetFileAttributesInd->fileAttributes.secRead);
        SockPrintf( "Security Read M  : %x\n",pGetFileAttributesInd->fileAttributes.secReadMask);
        SockPrintf( "Security Write   : %x\n",pGetFileAttributesInd->fileAttributes.secWrite);
        SockPrintf( "Security Write M : %x\n",pGetFileAttributesInd->fileAttributes.secWriteMask);
        SockPrintf( "Security Inc     : %x\n",pGetFileAttributesInd->fileAttributes.secIncrease);
        SockPrintf( "Security Inc M   : %x\n",pGetFileAttributesInd->fileAttributes.secIncreaseMask);
        SockPrintf( "Security De-Act  : %x\n",pGetFileAttributesInd->fileAttributes.secDeactivate);
        SockPrintf( "Security De-Act M: %x\n",pGetFileAttributesInd->fileAttributes.secDeactivateMask);
        SockPrintf( "Security Act     : %x\n",pGetFileAttributesInd->fileAttributes.secActivate);
        SockPrintf( "Security Act M   : %x\n",pGetFileAttributesInd->fileAttributes.secActivateMask);
        SockPrintf( "Raw Len          : %d\n",pGetFileAttributesInd->fileAttributes.rawLen);
        SockPrintf( "Raw Value        : ");
        for ( lcount=0 ; lcount < pGetFileAttributesInd->fileAttributes.rawLen ; lcount++ )
        {
            SockPrintf( "%x ",pGetFileAttributesInd->fileAttributes.rawValue[lcount]);
        }
    }
    SockPrintf( "\n");

    if(swi_uint256_get_bit (pGetFileAttributesInd->ParamPresenceMask, 0x12))
        SockPrintf( "File Status : %x\n",pGetFileAttributesInd->file_status);
    SockPrintf("\n");
}

void DisplaySlotStatusChangeInd(unpack_uim_SetUimSlotStatusChangeCallback_ind_t *pSlotStatusChangeCallback_ind)
{
    if(swi_uint256_get_bit (pSlotStatusChangeCallback_ind->ParamPresenceMask, 16))
    {
        SockPrintf("Slot Status Change Indication:\n");

        for (int idx = 0; idx < pSlotStatusChangeCallback_ind->bNumberOfPhySlots; ++idx)
        {            
            SockPrintf("  State of the card in the Pyhsical Slot Status = %d\n", 
                    pSlotStatusChangeCallback_ind->slotsstatusChange.uimSlotStatus[idx].uPhyCardStatus);            
            SockPrintf("  State of the Physical Slot status = %d\n", 
                    pSlotStatusChangeCallback_ind->slotsstatusChange.uimSlotStatus[idx].uPhySlotStatus);            
            SockPrintf("  Logical Slot associated with this physical slot = %d\n", 
                    pSlotStatusChangeCallback_ind->slotsstatusChange.uimSlotStatus[idx].bLogicalSlot);

            SockPrintf("  ICCID of the card in the physical slot: ");
            for (int idy = 0; idy < pSlotStatusChangeCallback_ind->slotsstatusChange.uimSlotStatus[idx].bICCIDLength; ++idy)
            {
                SockPrintf("%d", pSlotStatusChangeCallback_ind->slotsstatusChange.uimSlotStatus[idx].bICCID[idy]);
            }
            SockPrintf("\n");
        }
    }
}

void DisplayIccid(unpack_uim_SLQSUIMGetIccid_t* getICCID)
{
    if ((getICCID->bICCIDLength))
    {
        SockPrintf("\nICCID: ");
        for (uint8_t i = 0; i < *(getICCID->bICCIDLength); i++)
            SockPrintf("%c", getICCID->bICCID[i]);

        SockPrintf("\n");
    }
}

void DisplayEventRegister(unpack_uim_SLQSUIMEventRegister_t* eventRegisterResult)
{
    if (swi_uint256_get_bit(eventRegisterResult->ParamPresenceMask, 16))
        SockPrintf("event mask returned 0x%04X\n", eventRegisterResult->eventMask);
}

void DisplayDepersonalization(unpack_uim_SLQSUIMDepersonalization_t* depersonalizationResp)
{
    if ((NULL != depersonalizationResp->pRemainingRetries) && (swi_uint256_get_bit(depersonalizationResp->ParamPresenceMask, 16)))
    {
        SockPrintf("SLQSUIMDepersonalization Unsuccessful\n");
        SockPrintf("Verify Left  :%d\n", depersonalizationResp->pRemainingRetries->verifyLeft);
        SockPrintf("Unblock Left :%d\n", depersonalizationResp->pRemainingRetries->unblockLeft);
    }
}

typedef struct {
    char szICCID[UIM_UINT8_MAX_STRING_SZ];
    uint8_t szPUK[UIM_UINT8_MAX_STRING_SZ];
}iccid_puk;

pack_uim_UnblockPin_t UnblockPinReq = {
    {0,{0}}, //uim_encryptedPIN1    EncryptedPIN1;
    NULL,//  &IndicationToken,//uint32_t IndicationToken;
    NULL,
    { 0x00, 0x01, "1" },//uim_sessionInformation sessionInfo;
    { 0x01, 0x08, "52075361", 0x04, "1234" },//Smartone LTE SIM (RED)
    //{ 0x01, 0x08, "64159849", 0x04, "1234" },//Smartone 3G SIM (WHITE)
    //{ 0x01, 0x08, "20624355", 0x04, "1234" },//Three LTE SIM
    //{ 0x01, 0x08, "79915593", 0x04, "1234" },//Three 3G SIM
    0//uint16_t Tlvresult;
};

void change_default_puk(char* ICCIDString, uint16_t uLength)
{
    iccid_puk sims[] = {
       {"","88456232"},//Smartone LTE SIM (RED)
       {"8985203000049613960f","64159849"},//Smartone 3G SIM (WHITE)
       {"8985203000057115684f","20624355"},//Three LTE SIM
       {"8985203000049613960f","79915593"},//Three 3G SIM
       {"89852061012131090341","64159849"}
    };
    int i = 0;
    SockPrintf("ICCID:%s\n", ICCIDString);
    for (i = 0; i < (int)(sizeof(sims) / sizeof(iccid_puk)); i++)
    {
        if ((int)strlen(sims[i].szICCID) == (int)uLength)
        {
            int j = 0;
            for (j = 0; j < (int)strlen(sims[i].szICCID); j++)
            {
                if (sims[i].szICCID[j] != ICCIDString[j])
                {
                    break;
                }
            }
            if (j == (int)strlen(sims[i].szICCID))
            {
                for (j = 0; j < 8; j++)
                    UnblockPinReq.pinProtection.pukVal[j] = sims[i].szPUK[j];
                SockPrintf("ICCID:%s,", sims[i].szICCID);
                SockPrintf("PUK:%s\n", sims[i].szPUK);
                return;
            }
        }
    }
}

void DisplayReadTransparent(unpack_uim_ReadTransparent_t* readTransparent)
{
    if ((NULL != readTransparent->pCardResult) && (swi_uint256_get_bit(readTransparent->ParamPresenceMask, 16)))
    {
        SockPrintf("\n  SW1 received from card :%x\n", readTransparent->pCardResult->sw1);
        SockPrintf("  SW2 received from card :%x\n", readTransparent->pCardResult->sw2);
    }

    if ((NULL != readTransparent->pReadResult) && (swi_uint256_get_bit(readTransparent->ParamPresenceMask, 17)))
    {
        char szcontent[UIM_UINT8_MAX_STRING_SZ] = { 0 };
        SockPrintf("   ICCID No: ");
        for (uint16_t count = 0; count < readTransparent->pReadResult->contentLen; count++)
        {
            SockPrintf("%x", readTransparent->pReadResult->content[count] & 0x0f);
            SockPrintf("%x", (readTransparent->pReadResult->content[count] >> 4) & 0x0f);
            sprintf(szcontent + count * 2, "%x%x", readTransparent->pReadResult->content[count] & 0x0f, (readTransparent->pReadResult->content[count] >> 4) & 0x0f);
        }
        SockPrintf("\n   ");
        change_default_puk(szcontent, readTransparent->pReadResult->contentLen * 2);
    }
}

void DisplayReadTransparent2(unpack_uim_ReadTransparent_t* output)
{
    if ((NULL != output->pCardResult) && (swi_uint256_get_bit(output->ParamPresenceMask, 16)))
    {
        SockPrintf("\n  SW1 received from card :%x\n", output->pCardResult->sw1);
        SockPrintf("  SW2 received from card :%x\n", output->pCardResult->sw2);
    }
    if ((NULL != output->pReadResult) && (swi_uint256_get_bit(output->ParamPresenceMask, 17)))
    {
        SockPrintf("   length: %d\n", output->pReadResult->contentLen);
        SockPrintf("   IMSI: ");
        for (uint16_t count = 1; count < output->pReadResult->contentLen; count++)
        {
            if (count != 1)/*Skip the first nibble */
                SockPrintf("%x", output->pReadResult->content[count] & 0x0f);

            SockPrintf("%x", (output->pReadResult->content[count] >> 4) & 0x0f);
        }
        SockPrintf("\n");
    }
}

void DisplayVerifyPinInd(unpack_uim_VerifyPin_ind_t  *pVerifyPinInd)
{
    swi_uint256_print_mask (pVerifyPinInd->ParamPresenceMask);
    SockPrintf("indication_token: %d\n", pVerifyPinInd->indication_token);

    if (( NULL !=  pVerifyPinInd->pRemainingRetries ) && (swi_uint256_get_bit (pVerifyPinInd->ParamPresenceMask, 0x10)))
    {
        SockPrintf("Retry Remaining(Verify PIN) : %d \n",
                        pVerifyPinInd->pRemainingRetries->verifyLeft);
        SockPrintf("Retry Remaining(Unblock PIN): %d \n",
                        pVerifyPinInd->pRemainingRetries->unblockLeft);
    }
    if (( NULL !=  pVerifyPinInd->pEncryptedPIN1 ) && (swi_uint256_get_bit (pVerifyPinInd->ParamPresenceMask, 0x11)))
    {
        uint8_t lcount = 0;
        SockPrintf("Encrypted PIN1 Len : %d \n",
                        pVerifyPinInd->pEncryptedPIN1->pin1Len);
        SockPrintf("Encrypted PIN1 Value : ");
        for (lcount = 0;lcount < pVerifyPinInd->pEncryptedPIN1->pin1Len ;lcount++)
        {
            SockPrintf("%d,", pVerifyPinInd->pEncryptedPIN1->pin1Val[lcount]);
        }
        SockPrintf("\n");
    }
    if (( NULL != pVerifyPinInd->pCardResult ) && (swi_uint256_get_bit (pVerifyPinInd->ParamPresenceMask, 0x12)))
    {
        SockPrintf( "SW1 received from card :%x\n", pVerifyPinInd->pCardResult->sw1 );
        SockPrintf( "SW2 received from card :%x\n", pVerifyPinInd->pCardResult->sw2 );
    }
}

void DisplaySetPinProtectionInd(unpack_uim_SetPinProtection_ind_t *pSetPinProtectionInd)
{
    swi_uint256_print_mask (pSetPinProtectionInd->ParamPresenceMask);
    SockPrintf("indication_token: %d\n", pSetPinProtectionInd->indication_token);

    if (( NULL !=  pSetPinProtectionInd->pRemainingRetries ) && (swi_uint256_get_bit (pSetPinProtectionInd->ParamPresenceMask, 0x10)))
    {
        SockPrintf("Retry Remaining(Verify PIN) : %d \n",
                        pSetPinProtectionInd->pRemainingRetries->verifyLeft);
        SockPrintf("Retry Remaining(Unblock PIN): %d \n",
                        pSetPinProtectionInd->pRemainingRetries->unblockLeft);
    }
    if (( NULL !=  pSetPinProtectionInd->pEncryptedPIN1 ) && (swi_uint256_get_bit (pSetPinProtectionInd->ParamPresenceMask, 0x11)))
    {
        uint8_t lcount = 0;
        SockPrintf("Encrypted PIN1 Len : %d \n",
                        pSetPinProtectionInd->pEncryptedPIN1->pin1Len);
        SockPrintf("Encrypted PIN1 Value : ");
        for (lcount = 0;lcount < pSetPinProtectionInd->pEncryptedPIN1->pin1Len ;lcount++)
        {
            SockPrintf("%d,", pSetPinProtectionInd->pEncryptedPIN1->pin1Val[lcount]);
        }
        SockPrintf("\n");
    }
    if (( NULL != pSetPinProtectionInd->pCardResult ) && (swi_uint256_get_bit (pSetPinProtectionInd->ParamPresenceMask, 0x12)))
    {
        SockPrintf( "SW1 received from card :%x\n", pSetPinProtectionInd->pCardResult->sw1 );
        SockPrintf( "SW2 received from card :%x\n", pSetPinProtectionInd->pCardResult->sw2 );
    }
}

void DisplayUnblockPinInd(unpack_uim_UnblockPin_ind_t *pUnblockPinInd)
{
    swi_uint256_print_mask (pUnblockPinInd->ParamPresenceMask);
    SockPrintf("indication_token: %d\n", pUnblockPinInd->indication_token);

    if (( NULL !=  pUnblockPinInd->pRemainingRetries ) && (swi_uint256_get_bit (pUnblockPinInd->ParamPresenceMask, 0x10)))
    {
        SockPrintf("Retry Remaining(Verify PIN) : %d \n",
                        pUnblockPinInd->pRemainingRetries->verifyLeft);
        SockPrintf("Retry Remaining(Unblock PIN): %d \n",
                        pUnblockPinInd->pRemainingRetries->unblockLeft);
    }
    if (( NULL !=  pUnblockPinInd->pEncryptedPIN1 ) && (swi_uint256_get_bit (pUnblockPinInd->ParamPresenceMask, 0x11)))
    {
        uint8_t lcount = 0;
        SockPrintf("Encrypted PIN1 Len : %d \n",  pUnblockPinInd->pEncryptedPIN1->pin1Len);
        SockPrintf("Encrypted PIN1 Value : ");
        for (lcount = 0;lcount < pUnblockPinInd->pEncryptedPIN1->pin1Len ;lcount++)
        {
            SockPrintf("%d,", pUnblockPinInd->pEncryptedPIN1->pin1Val[lcount]);
        }
        SockPrintf("\n");
    }
    if (( NULL != pUnblockPinInd->pCardResult ) && (swi_uint256_get_bit (pUnblockPinInd->ParamPresenceMask, 0x12)))
    {
        SockPrintf( "SW1 received from card :%x\n", pUnblockPinInd->pCardResult->sw1 );
        SockPrintf( "SW2 received from card :%x\n", pUnblockPinInd->pCardResult->sw2 );
    }
}

void DisplayChangePinInd(unpack_uim_ChangePin_ind_t  *pChangePinInd)
{
    swi_uint256_print_mask (pChangePinInd->ParamPresenceMask);
    SockPrintf("indication_token: %d\n", pChangePinInd->indication_token);

    if (( NULL !=  pChangePinInd->pRemainingRetries ) && (swi_uint256_get_bit (pChangePinInd->ParamPresenceMask, 0x10)))
    {
        SockPrintf("Retry Remaining(Change PIN) : %d \n",
                        pChangePinInd->pRemainingRetries->verifyLeft);
        SockPrintf("Retry Remaining(Unblock PIN): %d \n",
                        pChangePinInd->pRemainingRetries->unblockLeft);
    }
    if (( NULL !=  pChangePinInd->pEncryptedPIN1 ) && (swi_uint256_get_bit (pChangePinInd->ParamPresenceMask, 0x11)))
    {
        uint8_t lcount = 0;
        SockPrintf("Encrypted PIN1 Len : %d \n",  pChangePinInd->pEncryptedPIN1->pin1Len);
        SockPrintf("Encrypted PIN1 Value : ");
        for (lcount = 0;lcount < pChangePinInd->pEncryptedPIN1->pin1Len ;lcount++)
        {
            SockPrintf("%d,", pChangePinInd->pEncryptedPIN1->pin1Val[lcount]);
        }
        SockPrintf("\n");
    }
    if (( NULL != pChangePinInd->pCardResult ) && (swi_uint256_get_bit (pChangePinInd->ParamPresenceMask, 0x12)))
    {
        SockPrintf( "SW1 received from card :%x\n", pChangePinInd->pCardResult->sw1 );
        SockPrintf( "SW2 received from card :%x\n", pChangePinInd->pCardResult->sw2 );
    }
}

void DisplaySetStatusChangeInd(unpack_uim_SLQSUIMSetStatusChangeCallBack_ind_t *pSetStatusChangeInd)
{
    swi_uint256_print_mask (pSetStatusChangeInd->ParamPresenceMask);

    if((pSetStatusChangeInd->pCardStatus) && (swi_uint256_get_bit (pSetStatusChangeInd->ParamPresenceMask, 0x10)))
    {
        DisplayCardStatus(pSetStatusChangeInd->pCardStatus);
    }
}

void DisplayRefreshInd(unpack_uim_SLQSUIMRefreshCallback_Ind_t *pRefreshIndication)
{
    swi_uint256_print_mask (pRefreshIndication->ParamPresenceMask);

    if ((swi_uint256_get_bit (pRefreshIndication->ParamPresenceMask, 0x10)))
    {
        SockPrintf("Stage:      %d\n", pRefreshIndication->refreshEvent.stage );
        SockPrintf("Mode:       %d\n", pRefreshIndication->refreshEvent.mode );
        SockPrintf("sessionType:%d\n", pRefreshIndication->refreshEvent.sessionType);
        SockPrintf("aidLength: %d\n", pRefreshIndication->refreshEvent.aidLength);
        for (uint8_t lCount = 0; lCount < pRefreshIndication->refreshEvent.aidLength; lCount++ )
        {
            SockPrintf("aid = %d\n", pRefreshIndication->refreshEvent.aid[lCount]);
        }

        SockPrintf(" Number of files = %d\n", pRefreshIndication->refreshEvent.numOfFiles);
        for (uint8_t lCount = 0; lCount < pRefreshIndication->refreshEvent.numOfFiles; lCount++ )
        {
            SockPrintf("FileID= %d\n", pRefreshIndication->refreshEvent.arrfileInfo[lCount].fileID);
            SockPrintf("Path Length = %d\n", pRefreshIndication->refreshEvent.arrfileInfo[lCount].pathLen);
            for ( uint8_t lIcount = 0; lIcount < pRefreshIndication->refreshEvent.arrfileInfo[lCount].pathLen; lIcount++ )
            {
                SockPrintf(" Path = %x", pRefreshIndication->refreshEvent.arrfileInfo[lCount].path[lIcount]);
            }
        }
    }
}

void DisplayAuthenticateInd(unpack_uim_Authenticate_ind_t *pAuthenticateInd)
{
    swi_uint256_print_mask (pAuthenticateInd->ParamPresenceMask);
    if (swi_uint256_get_bit (pAuthenticateInd->ParamPresenceMask, 1))
    {
        SockPrintf( "Indication Token:%d\n", pAuthenticateInd->indication_token );
    }
    if((pAuthenticateInd->pCardResult) && (swi_uint256_get_bit (pAuthenticateInd->ParamPresenceMask, 0x10)))
    {
        SockPrintf( "SW1 received from card :%x\n", pAuthenticateInd->pCardResult->sw1 );
        SockPrintf( "SW2 received from card :%x\n", pAuthenticateInd->pCardResult->sw2 );
    }

    if( (pAuthenticateInd->pAuthenticationResult) && (swi_uint256_get_bit (pAuthenticateInd->ParamPresenceMask, 0x11)))
    {
        SockPrintf("Content length : %d \n", pAuthenticateInd->pAuthenticationResult->content_len);
        SockPrintf("Authenticate data : ");
        for (uint16_t idx = 0; idx < pAuthenticateInd->pAuthenticationResult->content_len; idx++)
        {
            SockPrintf("%d,", pAuthenticateInd->pAuthenticationResult->pContent[idx]);
        }
        SockPrintf("\n");
    }
}
