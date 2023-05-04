/**
 * \ingroup liteqmi
 * \ingroup uim
 * \file uim.h
 */
#ifndef __LITEQMI_UIM_H__
#define __LITEQMI_UIM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include <stdint.h>

#define UIM_UINT8_MAX_STRING_SZ 255
#define UIM_MAX_DESCRIPTION_LENGTH 255
#define UIM_MAX_NO_OF_SLOTS 5
#define UIM_MAX_NO_OF_APPLICATIONS 10
#define MAX_NO_OF_SLOTS        5
#define MAX_NO_OF_APPLICATIONS 10
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_SLOTS_STATUS       255
#define MAX_ICCID_LENGTH       255
#define UIM_MAX_CONTENT_LENGTH 1024
#define UIM_MAX_ACTIVE_PERS_FEATURES   12
#define UIM_MAX_READ_RESULT_SZ 1600


/**
 * \ingroup uim
 * 
 *  This structure contains Application Status Information loaded on the card.
 *
 *  \param  appType
 *          - Indicates the type of the application.
 *              - 0 - Unknown
 *              - 1 - SIM card
 *              - 2 - USIM application
 *              - 3 - RUIM card
 *              - 4 - CSIM application
 *              - 5 - ISIM application
 *          - Other values are reserved for the future and are
 *            to be handled as "Unknown".
 *
 *  \param  appState
 *          - Indicates the state of the application.
 *              - 0 - Unknown
 *              - 1 - Detected
 *              - 2 - PIN1 or UPIN is required
 *              - 3 - PUK1 or PUK for UPIN is required
 *              - 4 - Personalization state must be checked
 *              - 5 - PIN1 is blocked
 *              - 6 - Illegal
 *              - 7 - Ready
 *
 *  \param  persoState
 *          - Indicates the state of the personalization for the application.
 *              - 0 - Unknown
 *              - 1 - Personalization operation is in progress
 *              - 2 - Ready
 *              - 3 - Personalization code is required
 *              - 4 - PUK for personalization code is required
 *              - 5 - Permanently blocked
 *
 *  \param  persoFeature
 *          - Indicates the personalization feature.
 *          - This applies only when a personalization code is required to
 *            deactivate or unblock personalization.
 *              - 0 - GW network personalization
 *              - 1 - GW network subset personalization
 *              - 2 - GW service provider personalization
 *              - 3 - GW corporate personalization
 *              - 4 - GW UIM personalization
 *              - 5 - 1X network type 1 personalization
 *              - 6 - 1X network type 2 personalization
 *              - 7 - 1X HRPD personalization
 *              - 8 - 1X service provider personalization
 *              - 9 - 1X corporate personalization
 *              - 10 - 1X RUIM personalization
 *              - 11 - Unknown
 *
 *  \param  persoRetries
 *          - Indicates the number of retries remaining to disable the
 *            personalization.
 *
 *  \param  persoUnblockRetries
 *          - Indicates the number of retries remaining to unblock the
 *            personalization.
 *
 *  \param  aidLength
 *          - Number of sets of the following elements. i.e. aidVal
 *          - If zero(0) then no aidVal information exists.
 *
 *  \param  aidVal[MAX_DESCRIPTION_LENGTH]
 *          - Application identifier value.
 *
 *  \param  univPin
 *          - Indicates whether UPIN replaces PIN1.
 *              - 0 - PIN1 is used
 *              - 1 - UPIN replaces PIN1
 *
 *  \param  pin1State
 *          - Indicates the state of PIN1.
 *              - 0 - Unknown
 *              - 1 - Enabled and not verified
 *              - 2 - Enabled and verified
 *              - 3 - Disabled
 *              - 4 - Blocked
 *              - 5 - Permanently blocked
 *
 *  \param  pin1Retries
 *          - Indicates the number of retries remaining to verify PIN1.
 *
 *  \param  puk1Retries
 *          - Indicates the number of retries remaining to unblock PIN1.
 *
 *  \param  pin2State
 *          - Indicates the state of PIN2.
 *              - 0 - Unknown
 *              - 1 - Enabled and not verified
 *              - 2 - Enabled and verified
 *              - 3 - Disabled
 *              - 4 - Blocked
 *              - 5 - Permanently blocked
 *
 *  \param  pin2Retries
 *          - Indicates the number of retries remaining to verify PIN2.
 *
 *  \param  puk2Retries
 *          - Indicates the number of retries remaining to unblock PIN2.
 *
 */
typedef struct
{
    uint8_t appType;
    uint8_t appState;
    uint8_t persoState;
    uint8_t persoFeature;
    uint8_t persoRetries;
    uint8_t persoUnblockRetries;
    uint8_t aidLength;
    uint8_t aidVal[UIM_MAX_DESCRIPTION_LENGTH];
    uint8_t univPin;
    uint8_t pin1State;
    uint8_t pin1Retries;
    uint8_t puk1Retries;
    uint8_t pin2State;
    uint8_t pin2Retries;
    uint8_t puk2Retries;
} uim_appStatus;


/**
 * \ingroup uim
 * 
 *  This structure contains information about the SLOTS present.
 *
 *  \param  cardState
 *          - Indicates the state of the card for each slot.
 *              - 0 - Absent
 *              - 1 - Present
 *              - 2 - Error
 *
 *  \param  upinState
 *          - Indicates the state of UPIN.
 *              - 0 - Unknown
 *              - 1 - Enabled and not verified
 *              - 2 - Enabled and verified
 *              - 3 - Disabled
 *              - 4 - Blocked
 *              - 5 - Permanently blocked
 *              - 0xFF - Not Available
 *
 *  \param  upinRetries
 *          - Indicates the number of retries remaining to verify the UPIN.
 *          - If 0xFF, information not available.
 *
 *  \param  upukRetries
 *          - Indicates the number of retries remaining to unblock the UPIN.
 *          - If 0xFF, information not available.
 *
 *  \param  errorState
 *          - Indicates the reason for the card error, and is valid only when
 *            the card state is Error
 *              - 0 - Unknown
 *              - 1 - Power down
 *              - 2 - Poll error
 *              - 3 - No ATR received
 *              - 4 - Volt mismatch
 *              - 5 - Parity error
 *              - 6 - Unknown; possibly removed
 *              - 7 - Card returned technical problems
 *              - 0xFF - Not Available
 *          - Other values are possible and reserved for future use.
 *          - When an unknown value is received, it is to be handled as "Unknown".
 *
 *  \param  numApp
 *          - Indicates the number of applications available on the card.
 *          - The following block is repeated for each application. i.e. AppStatus.
 *          - If zero(0) then no AppStatus information exists.
 *
 *  \param  AppStatus
 *          - See \ref uim_appStatus for more information.
 *
 */
typedef struct
{
    uint8_t      cardState;
    uint8_t      upinState;
    uint8_t      upinRetries;
    uint8_t      upukRetries;
    uint8_t      errorState;
    uint8_t      numApp;
    uim_appStatus AppStatus[UIM_MAX_NO_OF_APPLICATIONS];
} uim_slotInfo;


/**
 * \ingroup uim
 * 
 *  This structure contains Card Status Information.
 *
 *  \param  indexGwPri
 *          - Index of the primary GW provisioning application.
 *          - The most significant byte indicates the slot (starting from 0),
 *            while the least significant byte indicates the application for
 *            that slot (starting from 0).
 *          - The value 0xFFFF identifies when the session does not exist.
 *
 *  \param  index1xPri
 *          - Index of the primary 1X provisioning application.
 *          - The most significant byte indicates the slot (starting from 0),
 *            while the least significant byte indicates the application for
 *            that slot (starting from 0).
 *          - The value 0xFFFF identifies when the session does not exist.
 *
 *  \param  indexGwSec
 *          - Index of the secondary GW provisioning application.
 *          - The most significant byte indicates the slot (starting from 0),
 *            while the least significant byte indicates the application for
 *            that slot (starting from 0).
 *          - The value 0xFFFF identifies when the session does not exist.
 *
 *  \param  index1xSec
 *          - Index of the secondary GW provisioning application.
 *          - The most significant byte indicates the slot (starting from 0),
 *            while the least significant byte indicates the application for
 *            that slot (starting from 0).
 *          - The value 0xFFFF identifies when the session does not exist.
 *
 *  \param  numSlot
 *          - Indicates the number of slots available on the device.
 *          - The following block is repeated for each slot. i.e. cardState
 *          - If zero(0) then no cardState information exists.
 *
 *  \param  SlotInfo
 *          - See \ref uim_slotInfo for more information.
 *
 */
typedef struct
{
    uint16_t     indexGwPri;
    uint16_t     index1xPri;
    uint16_t     indexGwSec;
    uint16_t     index1xSec;
    uint8_t     numSlot;
    uim_slotInfo SlotInfo[UIM_MAX_NO_OF_SLOTS];
} uim_cardStatus;

/**
 * \ingroup uim
 * 
 *  This structure contains Hot Swap Status Information.
 *
 *  \param  hotSwapLength
 *          - Number of sets of the following elements. i.e. hot_swap
 *
 *  \param  hotSwap
 *          - Indicates the status of the hot-swap switch.
 *              - 0 - Hot-swap is not supported
 *              - 1 - Hot-swap is supported, but the status of the switch
 *                    is not supported
 *              - 2 - Switch indicates that the card is present
 *              - 3 - Switch indicates that the card is not present
 *
 */
typedef struct
{
    uint8_t hotSwapLength;
    uint8_t hotSwap[UIM_MAX_DESCRIPTION_LENGTH];
} uim_hotSwapStatus;

/**
 * \ingroup uim
 * 
 *  This structure contains information of the response parameters associated
 *  with a Get Card Status API.
 *
 *  @param  pCardStatus(optional)
 *          - See \ref uim_cardStatus for more information.
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  @param  pHotSwapStatus(optional)
 *          - See \ref uim_hotSwapStatus for more information.
 *          - Bit to check in ParamPresenceMask - <B>17</B>
 *
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct{
    uim_cardStatus *pCardStatus;
    uim_hotSwapStatus *pHotSwapStatus;
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_uim_GetCardStatus_t;

/**
 * \ingroup uim
 * 
 *  This structure contains the encrypted PIN1 Information.
 *
 *  @param  pin1Len
 *          - Number of sets of the following elements ie encrypted PIN1 value.
 *          - If zero(0), no information follows.
 *
 *  @param  pin1Val
 *          - Encrypted PIN1 value.
 *
 *  @note   This value is returned only when PIN1 is enabled successfully
 *          and the feature is supported.
 *
 */
typedef struct
{
    uint8_t pin1Len;
    uint8_t pin1Val[UIM_MAX_DESCRIPTION_LENGTH];
} uim_encryptedPIN1;

/**
 * \ingroup uim
 * 
 *  This structure contains the information about the retries remaining.
 *
 *  @param  verifyLeft
 *          - Number of remaining attempts to verify the PIN.
 *          - 0xFF, if unavailable.
 *
 *  @param  unblockLeft
 *          - Number of remaining attempts to unblock the PIN.
 *          - 0xFF, if unavailable.
 *
 *  @note   This value is returned only when the enable/disable operation has
 *          failed.
 *          This information is not sent for a hidden key PIN type.
 *
 */
typedef struct
{
    uint8_t verifyLeft;
    uint8_t unblockLeft;
} uim_remainingRetries;

/**
 * \ingroup uim
 * 
 *  This structure contains the Session Information.
 *
 *  @param  sessionType
 *          - Indicates the session type.
 *              - 0 - Primary GW provisioning
 *              - 1 - Primary 1X provisioning
 *              - 2 - Secondary GW provisioning
 *              - 3 - Secondary 1X provisioning
 *              - 4 - Non-provisioning on slot 1
 *              - 5 - Non-provisioning on slot 2
 *              - 6 - Card on slot 1
 *              - 7 - Card on slot 2
 *              - 8 - Logical channel on slot 1
 *              - 9 - Logical channel on slot 2
 *
 *  @param  aidLength
 *          - Length of the following elements i.e. Application Identifier.
 *
 *  @param  aid
 *          - Application identifier value or channel ID.
 *          - This value is required for non-provisioning and for logical
 *            channel session types. It is ignored in all other cases.
 *
 */
typedef struct
{
    uint8_t   sessionType;
    uint8_t   aidLength;
    uint8_t   aid[UIM_MAX_DESCRIPTION_LENGTH];
} uim_sessionInformation ;

/**
 * \ingroup uim
 * 
 *  This structure contains the information about the pin parameters that need
 *  to be verified.
 *
 *  \param  pinID
 *          - Indicates the PIN ID to be verified.
 *              - 1 - PIN1 (also called PIN)
 *              - 2 - PIN2
 *              - 3 - Universal PIN
 *              - 4 - Hidden key
 *
 *  \param  pinLen
 *          - Length of the following elements i.e. pin value.
 *
 *  \param  pinVal[MAX_DESCRIPTION_LENGTH]
 *          - PIN value.
 *          - This value is a sequence of ASCII characters.
 *
 */
typedef struct{
    uint8_t pinID;
    uint8_t pinLen;
    uint8_t pinVal[UIM_MAX_DESCRIPTION_LENGTH];
} uim_verifyUIMPIN;

/**
 * \ingroup uim
 * 
 *  This structure contains the information about the unblock pin parameters.
 *
 *  @param  pinID
 *          - Indicates the PIN ID to be changed.
 *              - 1 - PIN1 (also called PIN)
 *              - 2 - PIN2
 *              - 3 - Universal PIN
 *
 *  @param  pukLen
 *          - Length of the following elements i.e. puk value.
 *
 *  @param  pukVal[UIM_MAX_DESCRIPTION_LENGTH]
 *          - PIN Unlock Key value.
 *          - This value is a sequence of ASCII characters.
 *
 *  @param  newPINLen
 *          - Length of the following elements i.e. new pin value.
 *
 *  @param  newPINVal[UIM_MAX_DESCRIPTION_LENGTH]
 *          - New PIN value.
 *          - This value is a sequence of ASCII characters.
 *
 */
typedef struct{
    uint8_t pinID;
    uint8_t pukLen;
    uint8_t pukVal[UIM_MAX_DESCRIPTION_LENGTH];
    uint8_t newPINLen;
    uint8_t newPINVal[UIM_MAX_DESCRIPTION_LENGTH];
} uim_unblockUIMPIN;

/**
 * \ingroup uim
 * 
 *  This structure contains the information about the card result.
 *
 *  @param  sw1
 *          - SW1 received from the card.
 *
 *  @param  sw2
 *          - SW2 received from the card.
 *
 */
typedef struct
{
    uint8_t sw1;
    uint8_t sw2;
} uim_cardResult;

/**
 * \ingroup uim
 * 
 *  This structure contains the information about the pin protection parameters
 *  that need to be set.
 *
 *  @param  pinID
 *          - Indicates the PIN ID to be enabled or disabled.
 *              - 1 - PIN1 (also called PIN)
 *              - 2 - PIN2
 *              - 3 - Universal PIN
 *              - 4 - Hidden key
 *
 *  @param  pinOperation
 *          - Indicates whether the PIN is enabled or disabled.
 *              - 0 - Disable the PIN
 *              - 1 - Enable the PIN
 *
 *  @param  pinLength
 *          - Length of the following elements i.e. pin value.
 *
 *  @param  pinValue[MAX_DESCRIPTION_LENGTH]
 *          - PIN value.
 *          - This value is a sequence of ASCII characters.
 *
 */
typedef struct
{
    uint8_t pinID;
    uint8_t pinOperation;
    uint8_t pinLength;
    uint8_t pinValue[UIM_MAX_DESCRIPTION_LENGTH];
} uim_setPINProtection;

/**
 * \ingroup uim
 * 
 *  This structure contains the information about the pin parameters that need
 *  to be verified.
 *
 *  \param  pinID
 *          - Indicates the PIN ID to be changed.
 *              - 1 - PIN1 (also called PIN)
 *              - 2 - PIN2
 *              - 3 - Universal PIN
 *              - 4 - Hidden key
 *
 *  \param  oldPINLen
 *          - Length of the following elements i.e. old pin value.
 *
 *  \param  oldPINVal[UIM_MAX_DESCRIPTION_LENGTH]
 *          - Old PIN value.
 *          - This value is a sequence of ASCII characters.
 *
 *  \param  pinLen
 *          - Length of the following elements i.e. new pin value.
 *
 *  \param  pinVal[UIM_MAX_DESCRIPTION_LENGTH]
 *          - New PIN value.
 *          - This value is a sequence of ASCII characters.
 *
 */
typedef struct{
    uint8_t pinID;
    uint8_t oldPINLen;
    uint8_t oldPINVal[UIM_MAX_DESCRIPTION_LENGTH];
    uint8_t pinLen;
    uint8_t pinVal[UIM_MAX_DESCRIPTION_LENGTH];
} uim_changeUIMPIN;

/**
 * \ingroup uim
 * 
 *  This structure contains paramaters for file Information
 *
 *  @param  fileID
 *          - This is Identifier to SIM files;
 *            e.g. in UIM "6F07" is Identifier of IMSI File
 *
 *  @param  pathLen
 *          - Length of file Path in bytes
 *
 *  @param  path
 *          - Path value. This value must be the complete
 *            path of the file, which is a sequence block of 2
 *            bytes (e.g., 0x3F00 0x7FFF) is for LTE
 *            (0x3F00 ,0x7F20) is for GSM.
 */
typedef struct {
    uint16_t  fileID;
    uint8_t  pathLen;
    uint16_t  path[UIM_UINT8_MAX_STRING_SZ];
} uim_fileInfo;


/**
 * \ingroup uim
 * 
 *  This structure contains the Session Information.
 *
 *  @param  sessionType
 *          - Indicates the session type.
 *              - 0 - Primary GW provisioning
 *              - 1 - Primary 1X provisioning
 *              - 2 - Secondary GW provisioning
 *              - 3 - Secondary 1X provisioning
 *              - 4 - Non-provisioning on slot 1
 *              - 5 - Non-provisioning on slot 2
 *              - 6 - Card on slot 1
 *              - 7 - Card on slot 2
 *              - 8 - Logical channel on slot 1
 *              - 9 - Logical channel on slot 2
 *
 *  @param  aidLength
 *          - Length of the following elements i.e. Application Identifier.
 *
 *  @param  aid
 *          - Application identifier value or channel ID.
 *          - This value is required for non-provisioning and for logical
 *            channel session types. It is ignored in all other cases.
 *
 */
typedef struct
{
    uint8_t   sessionType;
    uint8_t   aidLength;
    uint8_t   aid[255];
} uim_UIMSessionInformation ;

/**
 * \ingroup uim
 * 
 *  This structure contains the information for read operation.
 *
 *  @param  offset
 *          - Offset for the read operation.
 *
 *  @param  length
 *          - Length of the content to be read.
 *          - The value 0 is used to read the complete file.
 *
 */
typedef struct
{
    uint16_t offset;
    uint16_t length;
} uim_readTransparentInfo;


/**
 * \ingroup uim
 * 
 *  This structure contains the information for write operation.
 *
 *  @param  contentLen
 *          - Number of sets of content.
 *
 *  @param  content[UIM_MAX_READ_RESULT_SZ]
 *          - Read content.
 *          - The content is the sequence of bytes as read from the card.
 */
typedef struct
{
    uint16_t contentLen;
    uint8_t content[UIM_MAX_READ_RESULT_SZ];
} uim_readResult;


/**
 * \ingroup uim
 * 
 * Get Card Status pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_uim_GetCardStatus(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen
);

/**
 * \ingroup uim
 * 
 * Get Card Status unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_uim_GetCardStatus(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_uim_GetCardStatus_t *pOutput
);

/**
 * \ingroup uim
 * 
 *  This structure contains information of the request parameters associated
 *  with a verify PIN API.
 *
 *  @param  sessionInfo
 *          - See \ref uim_sessionInformation for more information.
 *
 *  @param  verifyPIN
 *          - See \ref uim_verifyUIMPIN for more information.
 *
 *  @param  pEncryptedPIN1(optional)
 *          - See \ref uim_encryptedPIN1 for more information.
 *
 *  @param  pKeyReferenceID(optional)
 *          - Indicates the PIN key reference ID.
 *          - Indicates the PIN key reference ID. Valid values are from 1 to 8,
 *            respectively, for application 1 to application 8.
 *          - This TLV is used only for PIN1 and PIN2 and is ignored in all
 *            other cases.
 *
 *  @param  pIndicationToken(optional)
 *          - Response in Indication.
 *          - When this TLV is present, it indicates that the result must be
 *            provided in a subsequent indication.
 *          - Valid Values
 *            - 0 - Result of operation in response. Indication will not be generated by the modem
 *            - Any other positive number - Result of operation in indication.
 *              Indication will have same token value set by this function
 *
 *  @note   Using NULL for the pointers would make sure that the parameter is
 *          not added to the request.
 */
typedef struct{
    uim_encryptedPIN1    *pEncryptedPIN1;
    uint32_t *pIndicationToken;
    uint8_t *pKeyReferenceID;
    uim_sessionInformation sessionInfo;
    uim_verifyUIMPIN      verifyPIN;
    uint16_t Tlvresult;
}pack_uim_VerifyPin_t;

/**
 * \ingroup uim
 * 
 *  This structure contains information of the response parameters associated
 *  with a set of PIN related API's.
 *
 *  \param  pRemainingRetries(optional)
 *          - See \ref uim_remainingRetries for more information.
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  \param  pEncryptedPIN1(optional)
 *          - See \ref uim_encryptedPIN1 for more information.
 *          - Bit to check in ParamPresenceMask - <B>17</B>
 *
 *  \param  pIndicationToken(optional)
 *          - Response in Indication.
 *          - When this TLV is present, it indicates that the result is
 *            provided in a subsequent indication.
 *          - Bit to check in ParamPresenceMask - <B>18</B>
 *
 *  \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct{
    uim_remainingRetries *pRemainingRetries;
    uim_encryptedPIN1    *pEncryptedPIN1;
    uint32_t *pIndicationToken;
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_uim_VerifyPin_t;


/**
 * \ingroup uim
 * 
 * Verify Pin Status pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_uim_VerifyPin(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_uim_VerifyPin_t *reqArg
);

/**
 * \ingroup uim
 * 
 * Verify Pin unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_uim_VerifyPin(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_uim_VerifyPin_t *pOutput
);

/**
 * \ingroup uim
 * 
 *  This structure contains information of the request parameters associated
 *  with a Unblock PIN API.
 *
 *  @param  EncryptedPIN1
 *          - See \ref uim_encryptedPIN1 for more information.
 *
 *  @param  sessionInfo
 *          - See \ref uim_sessionInformation for more information.
 *
 *  @param  pinProtection
 *          - See \ref uim_unblockUIMPIN for more information.
 *
 *  @param  pKeyReferenceID(optional)
 *          - Indicates the PIN key reference ID.
 *          - Indicates the PIN key reference ID. Valid values are from 1 to 8,
 *            respectively, for application 1 to application 8.
 *          - This TLV is used only for PIN1 and PIN2 and is ignored in all
 *            other cases.
 *
 *  @param  pIndicationToken(optional)
 *          - Response in Indication.
 *          - When this TLV is present, it indicates that the result must be
 *            provided in a subsequent indication.
 *          - Valid Values
 *            - 0 - Result of operation in response. Indication will not be generated by the modem
 *            - Any other positive number - Result of operation in indication.
 *              Indication will have same token value set by this function
 *
 */
typedef struct{
    uim_encryptedPIN1    EncryptedPIN1;
    uint32_t *pIndicationToken;
    uint8_t *pKeyReferenceID;
    uim_sessionInformation sessionInfo;
    uim_unblockUIMPIN pinProtection;
    uint16_t Tlvresult;
}pack_uim_UnblockPin_t;

/**
 * \ingroup uim
 * 
 *  This structure contains information of the response parameters associated
 *  with a set of PIN related API's.
 *
 *  @param  pRemainingRetries(optional)
 *          - See \ref uim_remainingRetries for more information.
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  @param  pEncryptedPIN1(optional)
 *          - See \ref uim_encryptedPIN1 for more information.
 *          - Bit to check in ParamPresenceMask - <B>17</B>
 *
 *  @param  pIndicationToken(optional)
 *          - Response in Indication.
 *          - When this TLV is present, it indicates that the result is
 *            provided in a subsequent indication.
 *          - Bit to check in ParamPresenceMask - <B>18</B>
 *
 *  @param  ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct{
    uim_remainingRetries *pRemainingRetries;
    uim_encryptedPIN1    *pEncryptedPIN1;
    uint32_t *pIndicationToken;
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_uim_UnblockPin_t;


/**
 * \ingroup uim
 * 
 * Unblock Pin pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_uim_UnblockPin(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_uim_UnblockPin_t *reqArg
);

/**
 * \ingroup uim
 * 
 * Unblock Pin unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_uim_UnblockPin(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_uim_UnblockPin_t *pOutput
);

/**
 * \ingroup uim
 * 
 *  This structure contains information of the request parameters associated
 *  with a set pin protection API.
 *
 *  @param  sessionInfo
 *          - See \ref uim_sessionInformation for more information.
 *
 *  @param  pinProtection
 *          - See \ref uim_setPINProtection for more information.
 *
 *  @param  pKeyReferenceID(optional)
 *          - Indicates the PIN key reference ID.
 *          - Indicates the PIN key reference ID. Valid values are from 1 to 8,
 *            respectively, for application 1 to application 8.
 *          - This TLV is used only for PIN1 and PIN2 and is ignored in all
 *            other cases.
 *
 *  @param  pIndicationToken(optional)
 *          - Response in Indication.
 *          - When this TLV is present, it indicates that the result must be
 *            provided in a subsequent indication.
 *          - Valid Values
 *            - 0 - Result of operation in response. Indication will not be generated by the modem
 *            - Any other positive number - Result of operation in indication.
 *              Indication will have same token value set by this function
 *
 *  @note   Using NULL for the pointers would make sure that the parameter is
 *          not added to the request.
 */
typedef struct{
    uim_sessionInformation sessionInfo;
	uim_setPINProtection   pinProtection;
	uint8_t *pKeyReferenceID;
	uint32_t *pIndicationToken;
	uint16_t Tlvresult;
}pack_uim_SetPinProtection_t;

/**
 * \ingroup uim
 * 
 *  This structure contains information of the response parameters associated
 *  with a set of PIN related API's.
 *
 *  @param  pRemainingRetries(optional)
 *          - See \ref uim_remainingRetries for more information.
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  @param  pEncryptedPIN1(optional)
 *          - See \ref uim_encryptedPIN1 for more information.
 *          - Bit to check in ParamPresenceMask - <B>17</B>
 *
 *  @param  pIndicationToken(optional)
 *          - Response in Indication.
 *          - When this TLV is present, it indicates that the result is
 *            provided in a subsequent indication.
 *          - Bit to check in ParamPresenceMask - <B>18</B>
 *
 *  @param  ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct{
    uim_remainingRetries *pRemainingRetries;
    uim_encryptedPIN1    *pEncryptedPIN1;
    uint32_t *pIndicationToken;
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_uim_SetPinProtection_t;


/**
 * \ingroup uim
 * 
 * Set Pin Protection pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_uim_SetPinProtection(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_uim_SetPinProtection_t *reqArg
);

/**
 * \ingroup uim
 * 
 * Set Pin Protection unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_uim_SetPinProtection(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_uim_SetPinProtection_t *pOutput
);

/**
 * \ingroup uim
 * 
 *  This structure contains information of the request parameters associated
 *  with a Change PIN API.
 *
 *  \param  sessionInfo
 *          - See \ref uim_sessionInformation for more information.
 *
 *  \param  changePIN
 *          - See \ref uim_changeUIMPIN for more information.
 *
 *  \param  pKeyReferenceID(optional)
 *          - Indicates the PIN key reference ID.
 *          - Indicates the PIN key reference ID. Valid values are from 1 to 8,
 *            respectively, for application 1 to application 8.
 *          - This TLV is used only for PIN1 and PIN2 and is ignored in all
 *            other cases.
 *
 *  \param  pIndicationToken(optional)
 *          - Response in Indication.
 *          - When this TLV is present, it indicates that the result must be
 *            provided in a subsequent indication.
 *          - Valid Values
 *            - 0 - Result of operation in response. Indication will not be generated by the modem
 *            - Any other positive number - Result of operation in indication.
 *              Indication will have same token value set by this function
 *
 *  \note   Using NULL for the pointers would make sure that the parameter is
 *          not added to the request.
 */
typedef struct{
    uim_encryptedPIN1    EncryptedPIN1;
    uint32_t *pIndicationToken;
    uint8_t *pKeyReferenceID;
    uim_sessionInformation sessionInfo;
    uim_changeUIMPIN      changePIN;
    uint16_t Tlvresult;
}pack_uim_ChangePin_t;

/**
 * \ingroup uim
 * 
 *  This structure contains information of the response parameters associated
 *  with a set of PIN related API's.
 *
 *  \param  pRemainingRetries(optional)
 *          - See \ref uim_remainingRetries for more information.
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  \param  pEncryptedPIN1(optional)
 *          - See \ref uim_encryptedPIN1 for more information.
 *          - Bit to check in ParamPresenceMask - <B>17</B>
 *
 *  \param  pIndicationToken(optional)
 *          - Response in Indication.
 *          - When this TLV is present, it indicates that the result is
 *            provided in a subsequent indication.
 *          - Bit to check in ParamPresenceMask - <B>18</B>
 *
 *  \param  ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct{
    uim_remainingRetries *pRemainingRetries;
    uim_encryptedPIN1    *pEncryptedPIN1;
    uint32_t *pIndicationToken;
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_uim_ChangePin_t;


/**
 * \ingroup uim
 * 
 * Change Pin pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_uim_ChangePin(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_uim_ChangePin_t *reqArg
);

/**
 * \ingroup uim
 * 
 * Change Pin unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_uim_ChangePin(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_uim_ChangePin_t *pOutput
);


/**
 * \ingroup uim
 * 
 *  This structure contains information of the request parameters associated
 *  with a Read Transparent API.
 *
 *  @param  sessionInfo
 *          - See \ref uim_sessionInformation for more information.
 *
 *  @param  fileIndex
 *          - See \ref uim_fileInfo for more information.
 *
 *  @param  readTransparent
 *          - See \ref uim_readTransparentInfo for more information.
 *
 *  @param  pIndicationToken(optional)
 *          - Response in Indication.
 *          - When this TLV is present, it indicates that the result must be
 *            provided in a subsequent indication.
 *          - Valid Values
 *            - 0 - Result of operation in response. Indication will not be generated by the modem
 *            - Any other positive number - Result of operation in indication.
 *              Indication will have same token value set by this function
 *
 *  @param  pEncryptData(optional)
 *          - Encrypt Data.
 *          - Indicates whether the data read from the card is to be encrypted.
 *
 *  @note   Using NULL for the pointers would make sure that the parameter is
 *          not added to the request.
 */
typedef struct{
    uim_sessionInformation sessionInfo;
    uim_fileInfo              fileIndex;
    uim_readTransparentInfo   readTransparent;
    uint32_t                 *pIndicationToken;
    uint8_t                  *pEncryptData;
    uint16_t Tlvresult;
}pack_uim_ReadTransparent_t;

/**
 * \ingroup uim
 * 
 *  This structure contains information of the response parameters associated
 *  with a Read Transparent API.
 *
 *  \param  pCardResult
 *          - See \ref uim_cardResult for more information.
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  \param  pReadResult
 *          - See \ref uim_readResult for more information.
 *          - Bit to check in ParamPresenceMask - <B>17</B>
 *
 *  \param  pIndicationToken(optional)
 *          - Response in Indication.
 *          - When this TLV is present, it indicates that the result must be
 *            provided in a subsequent indication.
 *          - Bit to check in ParamPresenceMask - <B>18</B>
 *
 *  \param  pEncryptedData(optional)
 *          - Encrypted Data.
 *          - Indicates whether the data from the card passed in read_result is encrypted.
 *          - Bit to check in ParamPresenceMask - <B>19</B>
 *
 *  \param  ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct{
    uim_cardResult  *pCardResult;
    uim_readResult  *pReadResult;
    uint32_t        *pIndicationToken;
    uint8_t         *pEncryptedData;
    uint16_t        Tlvresult;
    swi_uint256_t   ParamPresenceMask;
}unpack_uim_ReadTransparent_t;


/**
 * \ingroup uim
 * 
 * SLQS ReadTransparent pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_uim_ReadTransparent(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_uim_ReadTransparent_t *reqArg
);

/**
 * \ingroup uim
 * 
 * SLQS ReadTransparent unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_uim_ReadTransparent(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_uim_ReadTransparent_t *pOutput
);

/**
 * \ingroup uim
 * 
 * This structure contains pack event register parameter.
 * @param eventMask 
 *					- Bit 0 – Card status
 *					- Bit 1 – SAP connection
 *					- Bit 2 – Extended card status
 *					- Bit 3 – Close of provisioning sessions
 *					- Bit 4 – Physical slot status
 *					- Bit 5 – SIM busy status
 *					- Bit 6 – Reduced card status
 *					- Bit 7 – Recovery complete
 *					- Bit 8 – Supply voltage Vcc status
 *					- Bit 9 – Card activation status
 *					- Bit 10 – Remote SimLock configuration
 *					- Bit 11 – SimLock temporary unlock
 */
typedef struct{
    uint32_t eventMask;
}pack_uim_SLQSUIMEventRegister_t;

/**
 * \ingroup uim
 * 
 * UIM Status Change callback enable pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_uim_SLQSUIMEventRegister (
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_uim_SLQSUIMEventRegister_t *reqArg
);

/**
 * \ingroup uim
 * 
 * This structure contains unpack event register parameter.
 * @param eventMask - bit 0 - card status
 *                  - bit 1 - SAP connection
 *                  - bit 4 - physical slot status
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 * @param ParamPresenceMask
 *        - bitmask representation to indicate valid parameters.
 *
 */
typedef struct{
    uint32_t eventMask;
    swi_uint256_t  ParamPresenceMask;
}unpack_uim_SLQSUIMEventRegister_t;

/**
 * \ingroup uim
 * 
 * UIM Status Change callback enable unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_uim_SLQSUIMEventRegister(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_uim_SLQSUIMEventRegister_t *pOutput
);

/**
 * \ingroup uim
 * 
 *  This structure contains Application Status Information loaded on the card.
 *
 *  \param  appType
 *          - Indicates the type of the application.
 *              - 0 - Unknown
 *              - 1 - SIM card
 *              - 2 - USIM application
 *              - 3 - RUIM card
 *              - 4 - CSIM application
 *              - 5 - ISIM application
 *          - Other values are reserved for the future and are
 *            to be handled as "Unknown".
 *
 *  \param  appState
 *          - Indicates the state of the application.
 *              - 0 - Unknown
 *              - 1 - Detected
 *              - 2 - PIN1 or UPIN is required
 *              - 3 - PUK1 or PUK for UPIN is required
 *              - 4 - Personalization state must be checked
 *              - 5 - PIN1 is blocked
 *              - 6 - Illegal
 *              - 7 - Ready
 *
 *  \param  persoState
 *          - Indicates the state of the personalization for the application.
 *              - 0 - Unknown
 *              - 1 - Personalization operation is in progress
 *              - 2 - Ready
 *              - 3 - Personalization code is required
 *              - 4 - PUK for personalization code is required
 *              - 5 - Permanently blocked
 *
 *  \param  persoFeature
 *          - Indicates the personalization feature.
 *          - This applies only when a personalization code is required to
 *            deactivate or unblock personalization.
 *              - 0 - GW network personalization
 *              - 1 - GW network subset personalization
 *              - 2 - GW service provider personalization
 *              - 3 - GW corporate personalization
 *              - 4 - GW UIM personalization
 *              - 5 - 1X network type 1 personalization
 *              - 6 - 1X network type 2 personalization
 *              - 7 - 1X HRPD personalization
 *              - 8 - 1X service provider personalization
 *              - 9 - 1X corporate personalization
 *              - 10 - 1X RUIM personalization
 *              - 11 - Unknown
 *
 *  \param  persoRetries
 *          - Indicates the number of retries remaining to disable the
 *            personalization.
 *
 *  \param  persoUnblockRetries
 *          - Indicates the number of retries remaining to unblock the
 *            personalization.
 *
 *  \param  aidLength
 *          - Number of sets of the following elements. i.e. aidVal
 *          - If zero(0) then no aidVal information exists.
 *
 *  \param  aidVal[MAX_DESCRIPTION_LENGTH]
 *          - Application identifier value.
 *
 *  \param  univPin
 *          - Indicates whether UPIN replaces PIN1.
 *              - 0 - PIN1 is used
 *              - 1 - UPIN replaces PIN1
 *
 *  \param  pin1State
 *          - Indicates the state of PIN1.
 *              - 0 - Unknown
 *              - 1 - Enabled and not verified
 *              - 2 - Enabled and verified
 *              - 3 - Disabled
 *              - 4 - Blocked
 *              - 5 - Permanently blocked
 *
 *  \param  pin1Retries
 *          - Indicates the number of retries remaining to verify PIN1.
 *
 *  \param  puk1Retries
 *          - Indicates the number of retries remaining to unblock PIN1.
 *
 *  \param  pin2State
 *          - Indicates the state of PIN2.
 *              - 0 - Unknown
 *              - 1 - Enabled and not verified
 *              - 2 - Enabled and verified
 *              - 3 - Disabled
 *              - 4 - Blocked
 *              - 5 - Permanently blocked
 *
 *  \param  pin2Retries
 *          - Indicates the number of retries remaining to verify PIN2.
 *
 *  \param  puk2Retries
 *          - Indicates the number of retries remaining to unblock PIN2.
 *
 */
typedef struct
{
    uint8_t appType;
    uint8_t appState;
    uint8_t persoState;
    uint8_t persoFeature;
    uint8_t persoRetries;
    uint8_t persoUnblockRetries;
    uint8_t aidLength;
    uint8_t aidVal[MAX_DESCRIPTION_LENGTH];
    uint8_t univPin;
    uint8_t pin1State;
    uint8_t pin1Retries;
    uint8_t puk1Retries;
    uint8_t pin2State;
    uint8_t pin2Retries;
    uint8_t puk2Retries;
} appStats;

/**
 * \ingroup uim
 * 
 *  This structure contains information about the SLOTS present.
 *
 *  \param  cardState
 *          - Indicates the state of the card for each slot.
 *              - 0 - Absent
 *              - 1 - Present
 *              - 2 - Error
 *
 *  \param  upinState
 *          - Indicates the state of UPIN.
 *              - 0 - Unknown
 *              - 1 - Enabled and not verified
 *              - 2 - Enabled and verified
 *              - 3 - Disabled
 *              - 4 - Blocked
 *              - 5 - Permanently blocked
 *              - 0xFF - Not Available
 *
 *  \param  upinRetries
 *          - Indicates the number of retries remaining to verify the UPIN.
 *          - If 0xFF, information not available.
 *
 *  \param  upukRetries
 *          - Indicates the number of retries remaining to unblock the UPIN.
 *          - If 0xFF, information not available.
 *
 *  \param  errorState
 *          - Indicates the reason for the card error, and is valid only when
 *            the card state is Error
 *              - 0 - Unknown
 *              - 1 - Power down
 *              - 2 - Poll error
 *              - 3 - No ATR received
 *              - 4 - Volt mismatch
 *              - 5 - Parity error
 *              - 6 - Unknown; possibly removed
 *              - 7 - Card returned technical problems
 *              - 0xFF - Not Available
 *          - Other values are possible and reserved for future use.
 *          - When an unknown value is received, it is to be handled as "Unknown".
 *
 *  \param  numApp
 *          - Indicates the number of applications available on the card.
 *          - The following block is repeated for each application. i.e. AppStatus.
 *          - If zero(0) then no AppStatus information exists.
 *
 *  \param  AppStatus[MAX_NO_OF_APPLICATIONS]
 *          - See \ref appStats for more information.
 *
 */
typedef struct
{
    uint8_t      cardState;
    uint8_t      upinState;
    uint8_t      upinRetries;
    uint8_t      upukRetries;
    uint8_t      errorState;
    uint8_t      numApp;
    appStats    AppStatus[MAX_NO_OF_APPLICATIONS];
} slotInf;

/**
 * \ingroup uim
 * 
 * This structure contains information about Status change callback.
 *
 *  @param  pCardStatus Card Status
 *          - See \ref uim_cardStatus for more information.
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  @param  ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct{
    uim_cardStatus *pCardStatus;
    swi_uint256_t  ParamPresenceMask;
}unpack_uim_SLQSUIMSetStatusChangeCallBack_ind_t;

/**
 * \ingroup uim
 * 
 * UIM Status Change indication unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * @note use pack_uim_SLQSUIMEventRegister to subscribe 
 */
int unpack_uim_SLQSUIMSetStatusChangeCallBack_ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_uim_SLQSUIMSetStatusChangeCallBack_ind_t *pOutput
);

/**
 * \ingroup uim
 * 
 * Pack get slots status.
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_uim_SLQSUIMGetSlotsStatus (
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen
);

/**
 * \ingroup uim
 * 
 *  This structure contains information of the response parameters associated
 *  with a Get Slots Status API.
 *
 *  \param  uPhyCardStatus
 *          - State of the card in the Pyhsical Slot Status.
 *              - 0x00 - Unknown.
 *              - 0x01 - Absent.
 *              - 0x02 - Present.
 *
 *  \param  uPhySlotStatus
 *          - State of the Physical Slot status.
 *              - 0x00 Inactive.
 *              - 0x01 Activate.
 *
 *  \param  bLogicalSlot
 *          - Logical Slot associated with this physical slot. THis is valid if the physical slot is active.
 *              - 1 - Slot 1.
 *              - 2 - Slot 2.
 *              - 3 - Slot 3.
 *              - 4 - Slot 4.
 *              - 5 - Slot 5.
 *
 *  \param  bLogicalSlot
 *          - Number of sets the sets of ICCCID
 *
 *  \param  bICCID[MAX_ICCID_LENGTH]
 *          - Contains the ICCID of the card in the physical slot.
 *
 */
typedef struct
{
    uint32_t   uPhyCardStatus;
    uint32_t   uPhySlotStatus;
    uint8_t    bLogicalSlot;
    uint8_t    bICCIDLength;
    uint8_t    bICCID[MAX_ICCID_LENGTH];
}slot_t;

/**
 * \ingroup uim
 * 
 *  This structure contains slots status.
 *  \param  uimSlotStatus
 *          - See \ref slot_t
 */

typedef struct
{
    slot_t uimSlotStatus[MAX_SLOTS_STATUS];
}slots_t;

/**
 * \ingroup uim
 * 
 *  This structure contains information of the response parameters associated
 *  with a Get Slots Status API.
 *
 *  \param  pNumberOfPhySlot
 *          - Number of sets of the Slot Status.
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  \param  pUimSlotsStatus
 *          - Slots Status  See \ref slots_t for more information..
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  \param  ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct{
    uint8_t    *pNumberOfPhySlot;
    slots_t    *pUimSlotsStatus;
    swi_uint256_t  ParamPresenceMask;
}unpack_uim_SLQSUIMGetSlotsStatus_t;

/**
 * \ingroup uim
 * 
 * get slot status unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput      response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_uim_SLQSUIMGetSlotsStatus(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_uim_SLQSUIMGetSlotsStatus_t *pOutput
);

/**
 * \ingroup uim
 * 
 * Pack get iccid.
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_uim_SLQSUIMGetIccid(
	pack_qmi_t  *pCtx,
	uint8_t *pReqBuf,
	uint16_t *pLen
);

/**
 * \ingroup uim
 * 
 *  This structure contains information of the response parameters associated
 *  with a Get Iccid API.
 * 
 *  \param  bICCIDLength
 *          - Length of ICCID in the active physical slot.
 *
 *  \param  bICCID
 *          - Contains the ICCID of the card in the active slot.
 *
 */
typedef struct {
    uint8_t    *bICCIDLength;
	uint8_t    *bICCID;
}unpack_uim_SLQSUIMGetIccid_t;

/**
 * \ingroup uim
 * 
 * get iccid unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput      response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_uim_SLQSUIMGetIccid(
	uint8_t *pResp,
	uint16_t respLen,
	unpack_uim_SLQSUIMGetIccid_t *pOutput
);

/**
 * \ingroup uim
 * 
 *  This structure contains information of the request parameters associated
 *  with a Switch Slot.
 *
 *  \param  bLogicalSlot
 *          - Indicates the slot to be used.
 *              - 1 - Slot 1
 *              - 2 - Slot 2
 *              - 3 - Slot 3
 *              - 4 - Slot 4
 *              - 5 - Slot 5
 *
 *  \param  ulPhysicalSlot
 *              - 1 - Slot 1
 *              - 2 - Slot 2
 *              - 3 - Slot 3
 *              - 4 - Slot 4
 *              - 5 - Slot 5
 *
 */
typedef struct{
    uint8_t bLogicalSlot;
    uint32_t ulPhysicalSlot;
}pack_uim_SLQSUIMSwitchSlot_t;

/**
 * \ingroup uim
 * 
 * switch slot pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_uim_SLQSUIMSwitchSlot (
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_uim_SLQSUIMSwitchSlot_t *reqArg
);

typedef unpack_result_t  unpack_uim_SLQSUIMSwitchSlot_t;

/**
 * \ingroup uim
 * 
 * switch slot unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_uim_SLQSUIMSwitchSlot(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_uim_SLQSUIMSwitchSlot_t *pOutput
);

/**
 * \ingroup uim
 * 
 *  Structure consist of card status params
 *
 *  \param  slotsstatusChange
 *          - See \ref slot_t for more information
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  \param  bNumberOfPhySlots
 *          - Number of Physical Slot(s)
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  \param  ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct{
    slots_t slotsstatusChange;
    uint8_t bNumberOfPhySlots;
    swi_uint256_t  ParamPresenceMask;
}unpack_uim_SetUimSlotStatusChangeCallback_ind_t;

/**
 * \ingroup uim
 * 
 * UIM Slot Status Change indication unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * @note use pack_uim_SLQSUIMEventRegister to subscribe 
 */
int unpack_uim_SetUimSlotStatusChangeCallback_ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_uim_SetUimSlotStatusChangeCallback_ind_t *pOutput
);

/**
 * \ingroup uim
 * 
 *  This structure contains information of the request parameters associated
 *  with a Power Down.
 *
 *  @param  slot
 *          - Indicates the slot to be used.
 *              - 1 - Slot 1
 *              - 2 - Slot 2
 *
 *  @param  pIgnoreHotSwapSwitch(optional)
 *          - Hot-swap switch status.
 *              - 0 - Checks the hot-swap switch status
 *              - 1 - Ignores the hot-swap switch status
 *
 */
typedef struct{
    uint8_t slot;
    uint8_t *pIgnoreHotSwapSwitch;
}pack_uim_SLQSUIMPowerUp_t;

/**
 * \ingroup uim
 * 
 * Powers up the card  pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_uim_SLQSUIMPowerUp (
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_uim_SLQSUIMPowerUp_t *reqArg
);

typedef unpack_result_t  unpack_uim_SLQSUIMPowerUp_t;

/**
 * \ingroup uim
 * 
 * Powers up the card unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_uim_SLQSUIMPowerUp(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_uim_SLQSUIMPowerUp_t *pOutput
);

/**
 * \ingroup uim
 * 
 *  This structure contains information of the request parameters associated
 *  with a Power Down.
 *
 *  @param  slot
 *          - Indicates the slot to be used.
 *              - 1 - Slot 1
 *              - 2 - Slot 2
 *
 */
typedef struct{
    uint8_t slot;
}pack_uim_SLQSUIMPowerDown_t;

/**
 * \ingroup uim
 * 
 * Powers down the card  pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_uim_SLQSUIMPowerDown (
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_uim_SLQSUIMPowerDown_t *reqArg
);

typedef unpack_result_t  unpack_uim_SLQSUIMPowerDown_t;

/**
 * \ingroup uim
 * 
 * Powers down the card unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_uim_SLQSUIMPowerDown(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_uim_SLQSUIMPowerDown_t *pOutput
);

/**
 * \ingroup uim
 * 
 * Resets the issuing control points state kept by the service pack.
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_uim_SLQSUIMReset(
    pack_qmi_t  *pCtx,
    uint8_t     *pReqBuf,
    uint16_t    *pLen
);

typedef unpack_result_t  unpack_uim_SLQSUIMReset_t;

/**
 * \ingroup uim
 * 
 * Resets the issuing control points state kept by the service unpack.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_uim_SLQSUIMReset(
    uint8_t  *pResp,
    uint16_t respLen,
    unpack_uim_SLQSUIMReset_t *pOutput
);

/**
 * \ingroup uim
 * 
 *  This structure contains Parameters of the Session Information
 *
 *  @param  sessionInfo
 *          - Session Information
 *          - See @ref uim_sessionInformation for more information
 *
 *  @param  OKtoRefresh
 *          - Indicates whether a refresh is OK. Valid values:
 *            - 0 - Not OK to refresh
 *            - 1 - OK to refresh
 */
typedef struct
{
    uim_sessionInformation sessionInfo;
    uint8_t                OKtoRefresh;
} pack_uim_SLQSUIMRefreshOK_t;

/**
 * \ingroup uim
 * 
 * Enables the client to indicate whether it is OK to start the
 * Refresh procedure pack.
 *
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_uim_SLQSUIMRefreshOK (
    pack_qmi_t  *pCtx,
    uint8_t     *pReqBuf,
    uint16_t    *pLen,
    pack_uim_SLQSUIMRefreshOK_t *reqArg
);

typedef unpack_result_t  unpack_uim_SLQSUIMRefreshOK_t;

/**
 * \ingroup uim
 * 
 * Enables the client to indicate whether it is OK to start the
 * Refresh procedure unpack.
 *
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_uim_SLQSUIMRefreshOK(
    uint8_t  *pResp,
    uint16_t respLen,
    unpack_uim_SLQSUIMRefreshOK_t *pOutput
);

/**
 * \ingroup uim
 * 
 *  This structure contains parameters of refresh Information
 *
 *  @param  registerFlag
 *          - Flag that indicates whether to register or
 *            deregister for refresh indications. Valid values:
 *            - 0 - Deregister
 *            - 1 - Register
 *
 *  @param  voteForInit
 *          - Flag that indicates whether to vote for the init
 *            when there is a refresh. Valid values:
 *            - 0 - Client does not vote for initialization
 *            - 1 - Client votes for initialization
 *
 *  @param  numFiles
 *          - Number of sets of the following elements:
 *            - file_id
 *            - path_len
 *            - path
 *
 *  @param  arrfileInfo
 *          - Array of file Information structure.
 *          - See @ref uim_fileInfo for more information
 */
typedef struct
{
    uint8_t     registerFlag;
    uint8_t     voteForInit;
    uint16_t    numFiles;
    uim_fileInfo arrfileInfo[MAX_DESCRIPTION_LENGTH];
} uim_registerRefresh;

/**
 * \ingroup uim
 * 
 *  This structure contains information of the request parameters associated
 *  with a Refresh Register.
 *
 *  @param  sessionInfo
 *          - Session Information params
 *          - See @ref uim_sessionInformation for more information
 *
 *  @param  regRefresh
 *          - Register Refresh parameters
 *          - See @ref uim_registerRefresh for more information
 *
 */
typedef struct
{
    uim_sessionInformation sessionInfo;
    uim_registerRefresh    regRefresh;
} pack_uim_SLQSUIMRefreshRegister_t;

/**
 * \ingroup uim
 * 
 * Registers for file change notifications triggered by the card pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_uim_SLQSUIMRefreshRegister(
    pack_qmi_t  *pCtx,
    uint8_t     *pReqBuf,
    uint16_t    *pLen,
    pack_uim_SLQSUIMRefreshRegister_t *reqArg
);

typedef unpack_result_t  unpack_uim_SLQSUIMRefreshRegister_t;

/**
 * \ingroup uim
 * 
 * Registers for file change notifications triggered by the card unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_uim_SLQSUIMRefreshRegister(
    uint8_t  *pResp,
    uint16_t respLen,
    unpack_uim_SLQSUIMRefreshRegister_t *pOutput
);

/**
 * \ingroup uim
 * 
 *  This structure contains information of the request parameters associated
 *  with a Refresh Complete event.
 *
 *  @param  sessionInfo(Mandatory)
 *          - See @ref uim_sessionInformation for more information.
 *
 *  @param  refreshComplete(Mandatory)
 *          - Indicates whether the refresh was successful.
 *            Valid values:
 *            - 0 - Refresh was not completed successfully
 *            - 1 - Refresh was completed successfully
 *
 */
typedef struct
{
    uim_sessionInformation  sessionInfo;
    uint8_t                 refreshComplete;
} pack_uim_SLQSUIMRefreshComplete_t;

/**
 * \ingroup uim
 * 
 * Enables the terminal response to be sent to the card
 * When the client finished Refresh procedure pack
 *
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_uim_SLQSUIMRefreshComplete(
    pack_qmi_t  *pCtx,
    uint8_t     *pReqBuf,
    uint16_t    *pLen,
    pack_uim_SLQSUIMRefreshComplete_t *reqArg
);

typedef unpack_result_t  unpack_uim_SLQSUIMRefreshComplete_t;

/**
 * \ingroup uim
 * 
 * Enables the terminal response to be sent to the card
 * When the client finished Refresh procedure unpack.
 *
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_uim_SLQSUIMRefreshComplete(
    uint8_t  *pResp,
    uint16_t respLen,
    unpack_uim_SLQSUIMRefreshComplete_t *pOutput
);

/**
 * \ingroup uim
 * 
 *  This structure contains information of parameters associated with
 *  the Refresh Event.
 *
 *  @param  stage
 *          - Indicates the stage of the Refresh procedure.
 *            - 0 - Waiting for OK to refresh
 *            - 1 - Refresh started
 *            - 2 - Refresh ended successfully
 *            - 3 - Refresh failed
 *
 *  @param  mode
 *          - Indicates the Refresh mode.
 *            - 0 - Reset
 *            - 1 - Init
 *            - 2 - Init and FCN
 *            - 3 - FCN
 *            - 4 - Init and Full FCN
 *            - 5 - Application reset
 *            - 6 - 3G session reset
 *
 *  @param  sessionType
 *          - Indicates the session type.
 *            - 0 - Primary GW provisioning
 *            - 1 - Primary 1X provisioning
 *            - 2 - Secondary GW provisioning
 *            - 3 - Secondary 1X provisioning
 *            - 4 - Nonprovisioning on slot 1
 *            - 5 - Nonprovisioning on slot 2
 *            - 6 - Card on slot 1
 *            - 7 - Card on slot 2
 *            - 8 - Logical channel on slot 1
 *            - 9 - Logical channel on slot 2
 *
 *  @param  aidLength
 *          - Number of sets of the following elements
 *            - Application Identifier
 *
 *  @param  aid
 *          - Application identifier value or channel ID. This
 *            value is required for non-provisioning and for
 *            logical channel session types. It is ignored in all
 *            other cases
 *
 *  @param  numFiles
 *          - Number of sets of the following elements:
 *            - file_id
 *            - path_len
 *            - path
 *
 *  @param  arrfileInfo
 *          - Array of file Information struct
 */
typedef struct
{
    uint8_t      stage;
    uint8_t      mode;
    uint8_t      sessionType;
    uint8_t      aidLength;
    uint8_t      aid[MAX_DESCRIPTION_LENGTH];
    uint16_t     numOfFiles;
    uim_fileInfo arrfileInfo[MAX_DESCRIPTION_LENGTH];
} uim_refreshevent;

/**
 * \ingroup uim
 * 
 *  This structure contains information of the request parameters associated
 *  with a Refresh Get Last Event.
 *
 *  @param  sessionInfo(Mandatory)
 *          - See @ref uim_sessionInformation for more information.
 *
 */
typedef struct
{
    uim_sessionInformation sessionInfo;
} pack_uim_SLQSUIMRefreshGetLastEvent_t;

/**
 * \ingroup uim
 * 
 *  This structure contains information of the response parameters associated
 *  with a Refresh Get Last Event.
 *
 *  @param  refreshEvent(Optional)
 *          - See @ref uim_refreshevent for more information.
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  @param pRefresh_enforcement_policy_mask
 *          Refresh enforcement policy.
 *          - Values:
 *              - UIM_REFRESH_ENFORCEMENT_POLICY_NAVIGATING_MENU (0x0001) - Force immediate refresh when navigating the menu
 *              - UIM_REFRESH_ENFORCEMENT_POLICY_DATA_CALL (0x0002) - Force immediate refresh when a data call is in progress
 *              - UIM_REFRESH_ENFORCEMENT_POLICY_VOICE_CALL (0x0004) - Force immediate refresh when a voice call is in progress
 *              - All other bits are reserved for future use
 *          - Bit to check in ParamPresenceMask - <B>17</B>
 *
 *  @param  ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct
{
    uim_refreshevent *pRefreshEvent;
    uint64_t *pRefresh_enforcement_policy_mask;
    swi_uint256_t  ParamPresenceMask;
} unpack_uim_SLQSUIMRefreshGetLastEvent_t;

/**
 * \ingroup uim
 * 
 * Retrieve the last refresh event pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
  *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_uim_SLQSUIMRefreshGetLastEvent(
    pack_qmi_t  *pCtx,
    uint8_t     *pReqBuf,
    uint16_t    *pLen,
    pack_uim_SLQSUIMRefreshGetLastEvent_t *reqArg
);

/**
 * \ingroup uim
 * 
 * Retrieve the last refresh event unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_uim_SLQSUIMRefreshGetLastEvent(
    uint8_t  *pResp,
    uint16_t respLen,
    unpack_uim_SLQSUIMRefreshGetLastEvent_t *pOutput
);

/**
 * \ingroup uim
 * 
 *  This structure contains information of the request parameters associated
 *  with a Get File Attributes
 *
 *  @param  sessionInfo
 *          - See @ref uim_sessionInformation for more information.
 *
 *  @param  fileIndex
 *          - See @ref uim_fileInfo for more information.
 *
 *  @param  pIndicationToken(optional)
 *          - Response in Indication.
 *          - When this TLV is present, it indicates that the result must be
 *            provided in a subsequent indication.
 *
 *  @param pUICCSecurityAttributes(optional)
 *          - Indicates whether the security attributes are required by the client. 
 *           - Valid values:
 *            - 0 - Skip security attributes of the file for the UICC card
 *            - 1 - Return security attributes of the file for the UICC card If the UICC Security Attributes TLV is
 *              missing, security attributes are returned. This TLV is ignored for ICC cards.
 *
 *  @note   Using NULL for the pointers would make sure that the parameter is
 *          not added to the request.
 */
typedef struct
{
    uim_sessionInformation sessionInfo;
    uim_fileInfo           fileIndex;
    uint32_t               *pIndicationToken;
    uint8_t                *pUICCSecurityAttributes;
} pack_uim_SLQSUIMGetFileAttributes_t;

/**
 * \ingroup uim
 * 
 *  This structure contains the information about the File Attributes.
 *
 *  @param  fileSize
 *          - Indicates the size of the file.
 *
 *  @param  fileID
 *          - Indicates the ID of the file.
 *
 *  @param  fileType
 *          - Indicates the type of the file.
 *              - 0 - Transparent
 *              - 1 - Cyclic
 *              - 2 - Linear fixed
 *              - 3 - Dedicated file
 *              - 4 - Master file
 *
 *  @param  recordSize
 *          - Indicates the size of the records.
 *          - Only for cyclic and linear fixed files
 *
 *  @param  recordCount
 *          - Indicates the total no. of the records.
 *          - Only for linear fixed files
 *
 *  @param  secRead
 *          - Read security attributes.
 *              - 0 - Always
 *              - 1 - Never
 *              - 2 - AND condition
 *              - 3 - OR condition
 *              - 4 - Single condition
 *
 *  @param  secReadMask
 *          - Mask with read security attributes.
 *          - This field is valid only when required by security attributes.
 *              - Bit 0 - PIN1
 *              - Bit 1 - PIN2
 *              - Bit 2 - UPIN
 *              - Bit 3 - ADM
 *
 *  @param  secWrite
 *          - Write security attributes.
 *              - 0 - Always
 *              - 1 - Never
 *              - 2 - AND condition
 *              - 3 - OR condition
 *              - 4 - Single condition
 *
 *  @param  secWriteMask
 *          - Mask with write security attributes.
 *          - This field is valid only when required by security attributes.
 *              - Bit 0 - PIN1
 *              - Bit 1 - PIN2
 *              - Bit 2 - UPIN
 *              - Bit 3 - ADM
 *
 *  @param  secIncrease
 *          - Increase security attributes.
 *              - 0 - Always
 *              - 1 - Never
 *              - 2 - AND condition
 *              - 3 - OR condition
 *              - 4 - Single condition
 *
 *  @param  secIncreaseMask
 *          - Mask with increase security attributes.
 *          - This field is valid only when required by security attributes.
 *              - Bit 0 - PIN1
 *              - Bit 1 - PIN2
 *              - Bit 2 - UPIN
 *              - Bit 3 - ADM
 *
 *  @param  secDeactivate
 *          - Deactivate security attributes.
 *              - 0 - Always
 *              - 1 - Never
 *              - 2 - AND condition
 *              - 3 - OR condition
 *              - 4 - Single condition
 *
 *  @param  secDeactivateMask
 *          - Mask with deactivate security attributes.
 *          - This field is valid only when required by security attributes.
 *              - Bit 0 - PIN1
 *              - Bit 1 - PIN2
 *              - Bit 2 - UPIN
 *              - Bit 3 - ADM
 *
  *  @param  secActivate
 *          - Activate security attributes.
 *              - 0 - Always
 *              - 1 - Never
 *              - 2 - AND condition
 *              - 3 - OR condition
 *              - 4 - Single condition
 *
 *  @param  secActivateMask
 *          - Mask with activate security attributes.
 *          - This field is valid only when required by security attributes.
 *              - Bit 0 - PIN1
 *              - Bit 1 - PIN2
 *              - Bit 2 - UPIN
 *              - Bit 3 - ADM
 *
 *  @param  rawLen
 *          - Length of the following elements i.e. raw value.
 *
 *  @param  rawValue[MAX_DESCRIPTION_LENGTH]
 *          - Raw value of file attributes.
 *
 */
typedef struct
{
    uint16_t  fileSize;
    uint16_t  fileID;
    uint8_t   fileType;
    uint16_t  recordSize;
    uint16_t  recordCount;
    uint8_t   secRead;
    uint16_t  secReadMask;
    uint8_t   secWrite;
    uint16_t  secWriteMask;
    uint8_t   secIncrease;
    uint16_t  secIncreaseMask;
    uint8_t   secDeactivate;
    uint16_t  secDeactivateMask;
    uint8_t   secActivate;
    uint16_t  secActivateMask;
    uint16_t  rawLen;
    uint8_t   rawValue[MAX_DESCRIPTION_LENGTH];
} uim_fileAttributes;

/**
 * \ingroup uim
 * 
 *  This structure contains information of the response parameters associated
 *  with a Get File Attributes
 *
 *  @param  pCardResult(optional)
 *          - See @ref uim_cardResult for more information.
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  @param  pFileAttributes(optional)
 *          - See @ref uim_fileAttributes for more information.
 *          - Bit to check in ParamPresenceMask - <B>17</B>
 *
 *  @param  pIndicationToken(optional)
 *          - Response in Indication.
 *          - When this TLV is present, it indicates that the result must be
 *            provided in a subsequent indication.
 *          - Bit to check in ParamPresenceMask - <B>18</B>
 *
 *  @param  pFileStatus
 *          - Indicates the status of the file.
 *           - Valid values:
 *              - UIM_FILE_STATUS_DEACTIVATED(0x00) â€“ File is deactivated.
 *              - UIM_FILE_STATUS_ACTIVATED(0x01) â€“ File is activated. 
 *              - Other values are reserved for future use and are to be ignored by the client.
 * 
 *  @param  ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct
{
    uim_cardResult     *pCardResult;
    uim_fileAttributes *pFileAttributes;
    uint32_t           *pIndicationToken;
    uint32_t           *pFileStatus;
    swi_uint256_t      ParamPresenceMask;
} unpack_uim_SLQSUIMGetFileAttributes_t;

/**
 * \ingroup uim
 * 
 * Retrieves the file attributes for any EF(Elementary File) or DF(Dedicated File) in the card and provides access by the path pack.
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_uim_SLQSUIMGetFileAttributes(
    pack_qmi_t  *pCtx,
    uint8_t     *pReqBuf,
    uint16_t    *pLen,
    pack_uim_SLQSUIMGetFileAttributes_t *reqArg
);

/**
 * \ingroup uim
 * 
 * Retrieves the file attributes for any EF(Elementary File) or DF(Dedicated File) in the card and provides access by the path unpack.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_uim_SLQSUIMGetFileAttributes(
    uint8_t  *pResp,
    uint16_t respLen,
    unpack_uim_SLQSUIMGetFileAttributes_t *pOutput
);

/**
 * \ingroup uim
 * 
 *  This structure contains the Depersonalization Information.
 *
 *  @param  feature
 *          - Indicates the personalization feature to de-activate or unblock.
 *              - Valid values:
 *              - UIM_PERSO_FEATURE_GW_NETWORK (0x00) - GW network personalization
 *              - UIM_PERSO_FEATURE_GW_NETWORK_SUBSET (0x01) - GW network subset personalization
 *              - UIM_PERSO_FEATURE_GW_SERVICE_PROVIDER (0x02) - GW service provider personalization
 *              - UIM_PERSO_FEATURE_GW_CORPORATE (0x03) - GW corporate personalization
 *              - UIM_PERSO_FEATURE_GW_UIM (0x04) - GW UIM personalization
 *              - UIM_PERSO_FEATURE_1X_NETWORK_TYPE_1 (0x05) - 1X network type 1 personalization
 *              - UIM_PERSO_FEATURE_1X_NETWORK_TYPE_2 (0x06) - 1X network type 2 personalization
 *              - UIM_PERSO_FEATURE_1X_HRPD (0x07) - 1X HRPD personalization
 *              - UIM_PERSO_FEATURE_1X_SERVICE_PROVIDER (0x08) - 1X service provider personalization
 *              - UIM_PERSO_FEATURE_1X_CORPORATE (0x09) - 1X corporate personalization
 *              - UIM_PERSO_FEATURE_1X_RUIM (0x0A) - 1X RUIM personalization
 *              - UIM_PERSO_FEATURE_GW_SPN (0x0B) - GW SPN personalization
 *              - UIM_PERSO_FEATURE_GW_SP_EHPLMN (0x0C) - GW SP + EHPLMN personalization
 *              - UIM_PERSO_FEATURE_GW_ICCID (0x0D) - GW ICCID personalization
 *              - UIM_PERSO_FEATURE_GW_IMPI (0x0E) - GW IMPI personalization
 *              - UIM_PERSO_FEATURE_GW_NETWORK_SUBSET_SERVICE_PROVIDER (0x0F) - GW network subset and service provider personalization
 *
 *  @param  operation
 *          - Indicates the operation to perform.
 *              - 0 - Deactivate personalization.
 *              - 1 - Unblock personalization.
 *
 *  @param  ckLen
 *          - Length of the following elements i.e. control key value.
 *
 *  @param  ckVal[MAX_DESCRIPTION_LENGTH]
 *          - Control key value.
 *          - This value is a sequence of ASCII characters.
 * 
 *  @param  pSlot [Optional]
 *          Indicates the slot to be used. 
 *            - Valid values:
 *              - UIM_SLOT_1 (0x01) - Slot 1
 *              - UIM_SLOT_2 (0x02) - Slot 2
 *              - UIM_SLOT_3 (0x03) - Slot 3
 *              - UIM_SLOT_4 (0x04) - Slot 4
 *              - UIM_SLOT_5 (0x05) - Slot 5

 */
typedef struct
{
    uint8_t  feature;
    uint8_t  operation;
    uint8_t  ckLen;
    uint8_t  ckVal[MAX_DESCRIPTION_LENGTH];
    uint8_t  *pSlot;
} pack_uim_SLQSUIMDepersonalization_t;

/**
 * \ingroup uim
 * 
 *  This structure contains information of the response parameters associated
 *  with a Depersonalization.
 *
 *  @param  pRemainingRetries(optional)
 *          - See @ref uim_remainingRetries for more information.
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  @param  ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct
{
    uim_remainingRetries *pRemainingRetries;
    swi_uint256_t        ParamPresenceMask;
} unpack_uim_SLQSUIMDepersonalization_t;

/**
 * \ingroup uim
 * 
 * De-activates or unblocks the personalization on the phone pack.
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_uim_SLQSUIMDepersonalization(
    pack_qmi_t  *pCtx,
    uint8_t     *pReqBuf,
    uint16_t    *pLen,
    pack_uim_SLQSUIMDepersonalization_t *reqArg
);

/**
 * \ingroup uim
 * 
 * De-activates or unblocks the personalization on the phone unpack.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_uim_SLQSUIMDepersonalization(
    uint8_t  *pResp,
    uint16_t respLen,
    unpack_uim_SLQSUIMDepersonalization_t *pOutput
);

/**
 * \ingroup uim
 * 
 *  This structure contains the Session Information.
 *
 *  @param  context
 *          - Authenticate context.
 *              - 0 - Runs the GSM algorithm (valid only on a 2GSIM card)
 *              - 1 - Runs the CAVE algorithm (valid only on a RUIM card)
 *              - 2 - GSM security context (valid only on a USIM application)
 *              - 3 - 3G security context (valid only on a USIM application)
 *              - 4 - VGCS/VBS security context
 *                  (valid only on aUSIM application)
 *              - 5 - GBA security context, Bootstrapping mode
 *                  (valid only on a USIM or ISIM application)
 *              - 6 - GBA security context, NAF Derivation mode
 *                  (valid only on a USIM or ISIM application)
 *              - 7 - MBMS security context, MSK Update mode
 *                  (valid only on a USIM application)
 *              - 8 - MBMS security context, MTK Generation mode
 *                  (valid only on a USIM application)
 *              - 9 - MBMS security context, MSK Deletion mode
 *                  (valid only on a USIM application)
 *              - 10 - MBMS security context, MUK Deletion mode
 *                  (valid only on a USIM application)
 *              - 11 - IMS AKA security context
 *                  (valid only on aISIM application)
 *              - 12 - HTTP-digest security context
 *                  (valid only onan ISIM application)
 *              - 13 - Compute IP authentication, CHAP
 *                  (valid onlyon RUIM or CSIM)
 *              - 14 - Compute IP authentication, MN-HA authenticator
 *                  (valid only on RUIM or CSIM)
 *              - 15 - Compute IP authentication, MIP-RRQ hash
 *                  (valid only on RUIM or CSIM)
 *              - 16 - Compute IP authentication, MN-AAA authenticator
 *                  (valid only on RUIM or CSIM)
 *              - 17 - Compute IP authentication, HRPD access authenticator
 *                  (valid only on RUIM or CSIM)
 *          - Other values are possible and reserved for future use.
 *
 *  @param  dataLen
 *          - Length of the following elements i.e. data.
 *
 *  @param  data[UIM_MAX_DESCRIPTION_LENGTH]
 *          - Authenticate Data.
 *
 */
typedef struct
{
    uint8_t  context;
    uint16_t dataLen;
    uint8_t  data[UIM_MAX_CONTENT_LENGTH];
} uim_authenticationData;

/**
 * \ingroup uim
 * 
 *  This structure contains information of the request parameters associated
 *  with a SLQSUIMAuthenticate.
 *
 *  @param  sessionInfo
 *          - See @ref uim_sessionInformation for more information.
 *
 *  @param  authData
 *          - See @ref uim_authenticationData for more information.
 *
 *  @param  pIndicationToken(optional)
 *          - Response in Indication.
 *          - When this TLV is present, it indicates that the result must be
 *            provided in a subsequent indication.
 *
 *  @note   Using NULL for the pointers would make sure that the parameter is
 *          not added to the request.
 */
typedef struct
{
    uim_sessionInformation sessionInfo;
    uim_authenticationData authData;
    uint32_t               *pIndicationToken;
} pack_uim_SLQSUIMAuthenticate_t;

/**
 * \ingroup uim
 * 
 *  This structure contains the information about the authenticate result.
 *
 *  @param  contentLen
 *          - Length of the following elements i.e. content.
 *
 *  @param  content[UIM_MAX_CONTENT_LENGTH]
 *          - Authenticate data.
 *          - This value is a sequence of bytes returned from the card.
 *
 */
typedef struct
{
    uint16_t contentLen;
    uint8_t  content[UIM_MAX_CONTENT_LENGTH];
} uim_authenticateResult;

/**
 * \ingroup uim
 * 
 *  This structure contains information of the response parameters associated
 *  with a SLQSUIMAuthenticate.
 *
 *  @param  pCardResult(optional)
 *          - See @ref uim_cardResult for more information.
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  @param  pAuthenticateResult(optional)
 *          - See @ref uim_authenticateResult for more information.
 *          - Bit to check in ParamPresenceMask - <B>17</B>
 *
 *  @param  pIndicationToken(optional)
 *          - Response in Indication.
 *          - When this TLV is present, it indicates that the result must be
 *            provided in a subsequent indication.
 *          - Bit to check in ParamPresenceMask - <B>18</B>
 *
 *  @param  ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct
{
    uim_cardResult            *pCardResult;
    uim_authenticateResult    *pAuthenticateResult;
    uint32_t                  *pIndicationToken;
    swi_uint256_t             ParamPresenceMask;
} unpack_uim_SLQSUIMAuthenticate_t;

/**
 * \ingroup uim
 * 
 * Send a security command to the card pack.
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_uim_SLQSUIMAuthenticate(
    pack_qmi_t  *pCtx,
    uint8_t     *pReqBuf,
    uint16_t    *pLen,
    pack_uim_SLQSUIMAuthenticate_t *reqArg
);

/**
 * \ingroup uim
 * 
 * Unpack the status code received from the card when card responded to the read request
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_uim_SLQSUIMAuthenticate(
    uint8_t  *pResp,
    uint16_t respLen,
    unpack_uim_SLQSUIMAuthenticate_t *pOutput
);

/**
 * \ingroup uim
 * 
 *  This structure contains the information about the card result.
 *
 *  @param  numFeatures
 *          - Number of active personalization features.
 *            The following block is repeated for each feature.
 *
 *  @param  feature
 *          - Indicates the personalization feature to deactivate or unblock.
 *              - Valid values:
 *              - UIM_PERSO_FEATURE_GW_NETWORK (0x00) - GW network personalization
 *              - UIM_PERSO_FEATURE_GW_NETWORK_SUBSET (0x01) - GW network subset personalization
 *              - UIM_PERSO_FEATURE_GW_SERVICE_PROVIDER (0x02) - GW service provider personalization
 *              - UIM_PERSO_FEATURE_GW_CORPORATE (0x03) - GW corporate personalization
 *              - UIM_PERSO_FEATURE_GW_UIM (0x04) - GW UIM personalization
 *              - UIM_PERSO_FEATURE_1X_NETWORK_TYPE_1 (0x05) - 1X network type 1 personalization
 *              - UIM_PERSO_FEATURE_1X_NETWORK_TYPE_2 (0x06) - 1X network type 2 personalization
 *              - UIM_PERSO_FEATURE_1X_HRPD (0x07) - 1X HRPD personalization
 *              - UIM_PERSO_FEATURE_1X_SERVICE_PROVIDER (0x08) - 1X service provider personalization
 *              - UIM_PERSO_FEATURE_1X_CORPORATE (0x09) - 1X corporate personalization
 *              - UIM_PERSO_FEATURE_1X_RUIM (0x0A) - 1X RUIM personalization
 *              - UIM_PERSO_FEATURE_GW_SPN (0x0B) - GW SPN personalization
 *              - UIM_PERSO_FEATURE_GW_SP_EHPLMN (0x0C) - GW SP + EHPLMN personalization
 *              - UIM_PERSO_FEATURE_GW_ICCID (0x0D) - GW ICCID personalization
 *              - UIM_PERSO_FEATURE_GW_IMPI (0x0E) - GW IMPI personalization
 *              - UIM_PERSO_FEATURE_GW_NETWORK_SUBSET_SERVICE_PROVIDER (0x0F) - GW network subset and service provider personalization
 *              - Other values are reserved for future use and are to be handled as unknown personalization features by the client.
 * 
 *
 *  @param  verifyLeft
 *          - Number of the remaining attempts to verify
 *            the personalization feature.
 *
 *  @param  unblockLeft
 *          - Number of the remaining attempts to unblock
 *            the personalization feature.
 *
 */
typedef struct
{
    uint8_t numFeatures;
    uint8_t feature[UIM_MAX_ACTIVE_PERS_FEATURES];
    uint8_t verifyLeft[UIM_MAX_ACTIVE_PERS_FEATURES];
    uint8_t unblockLeft[UIM_MAX_ACTIVE_PERS_FEATURES];
} uim_personalizationStatus;


/**
 * \ingroup uim
 * 
 *  This structure contains the information about the card result.
 *
 *  @param  extended_personalization_status_len
 *          - Number of sets of the feature, verify_left, and unblock_left.
 *
 *  @param  personalization_status_len
 *          - Number of sets of the following feature, verify_left, and unblock_left
 * 
 *  @param  feature
 *          - Indicates the personalization feature to deactivate or unblock.
 *              - Valid values:
 *              - UIM_PERSO_FEATURE_GW_NETWORK (0x00) - GW network personalization
 *              - UIM_PERSO_FEATURE_GW_NETWORK_SUBSET (0x01) - GW network subset personalization
 *              - UIM_PERSO_FEATURE_GW_SERVICE_PROVIDER (0x02) - GW service provider personalization
 *              - UIM_PERSO_FEATURE_GW_CORPORATE (0x03) - GW corporate personalization
 *              - UIM_PERSO_FEATURE_GW_UIM (0x04) - GW UIM personalization
 *              - UIM_PERSO_FEATURE_1X_NETWORK_TYPE_1 (0x05) - 1X network type 1 personalization
 *              - UIM_PERSO_FEATURE_1X_NETWORK_TYPE_2 (0x06) - 1X network type 2 personalization
 *              - UIM_PERSO_FEATURE_1X_HRPD (0x07) - 1X HRPD personalization
 *              - UIM_PERSO_FEATURE_1X_SERVICE_PROVIDER (0x08) - 1X service provider personalization
 *              - UIM_PERSO_FEATURE_1X_CORPORATE (0x09) - 1X corporate personalization
 *              - UIM_PERSO_FEATURE_1X_RUIM (0x0A) - 1X RUIM personalization
 *              - UIM_PERSO_FEATURE_GW_SPN (0x0B) - GW SPN personalization
 *              - UIM_PERSO_FEATURE_GW_SP_EHPLMN (0x0C) - GW SP + EHPLMN personalization
 *              - UIM_PERSO_FEATURE_GW_ICCID (0x0D) - GW ICCID personalization
 *              - UIM_PERSO_FEATURE_GW_IMPI (0x0E) - GW IMPI personalization
 *              - UIM_PERSO_FEATURE_GW_NETWORK_SUBSET_SERVICE_PROVIDER (0x0F) - GW network subset and service provider personalization
 *              - Other values are reserved for future use and are to be handled as unknown personalization features by the client.
 *
 *  @param  verifyLeft
 *          - Number of the remaining attempts to verify
 *            the personalization feature.
 *
 *  @param  unblockLeft
 *          - Number of the remaining attempts to unblock
 *            the personalization feature.
 */
typedef struct
{
    uint8_t extended_personalization_status_len;
    uint8_t personalization_status_len;
    uint8_t feature[UIM_MAX_ACTIVE_PERS_FEATURES];
    uint8_t verifyLeft[UIM_MAX_ACTIVE_PERS_FEATURES];
    uint8_t unblockLeft[UIM_MAX_ACTIVE_PERS_FEATURES];
} uim_personalStatusOtherSlots;

/**
 * \ingroup uim
 * 
 *  This structure contains information of the request parameters associated
 *  with Get Configuration to get the modem configuration for the UIM module
 *
 *  @param  pConfigurationMask(optional)
 *          - Requested configurations
 *            - Bit 0 - Automatic selection
 *            - Bit 1 - Personalization status
 *            - Bit 2 - Halt subscription
 *            - All other bits are reserved for future use
 *
 *  @note     - if the TLV is missing, the service returns all
 *              configuration items in the response.
 */
typedef struct
{
    uint32_t *pConfigurationMask;
} pack_uim_SLQSUIMGetConfiguration_t;


/**
 * \ingroup uim
 * 
 *  This structure contains information of Temporary Depersonalization Status
 *
 *  @param  temporary_depersonalization_status_len
 *          - Number of sets of the feature and temporary_unlock_time_left
 *
 *  @param  temporary_unlock_status_len
 *          - Number of sets of the feature and temporary_unlock_time_left
 * 
 *  @param  feature
 *          - Indicates the personalization feature to deactivate or unblock.
 *              - Valid values:
 *              - UIM_PERSO_FEATURE_GW_NETWORK (0x00) - GW network personalization
 *              - UIM_PERSO_FEATURE_GW_NETWORK_SUBSET (0x01) - GW network subset personalization
 *              - UIM_PERSO_FEATURE_GW_SERVICE_PROVIDER (0x02) - GW service provider personalization
 *              - UIM_PERSO_FEATURE_GW_CORPORATE (0x03) - GW corporate personalization
 *              - UIM_PERSO_FEATURE_GW_UIM (0x04) - GW UIM personalization
 *              - UIM_PERSO_FEATURE_1X_NETWORK_TYPE_1 (0x05) - 1X network type 1 personalization
 *              - UIM_PERSO_FEATURE_1X_NETWORK_TYPE_2 (0x06) - 1X network type 2 personalization
 *              - UIM_PERSO_FEATURE_1X_HRPD (0x07) - 1X HRPD personalization
 *              - UIM_PERSO_FEATURE_1X_SERVICE_PROVIDER (0x08) - 1X service provider personalization
 *              - UIM_PERSO_FEATURE_1X_CORPORATE (0x09) - 1X corporate personalization
 *              - UIM_PERSO_FEATURE_1X_RUIM (0x0A) - 1X RUIM personalization
 *              - UIM_PERSO_FEATURE_GW_SPN (0x0B) - GW SPN personalization
 *              - UIM_PERSO_FEATURE_GW_SP_EHPLMN (0x0C) - GW SP + EHPLMN personalization
 *              - UIM_PERSO_FEATURE_GW_ICCID (0x0D) - GW ICCID personalization
 *              - UIM_PERSO_FEATURE_GW_IMPI (0x0E) - GW IMPI personalization
 *              - UIM_PERSO_FEATURE_GW_NETWORK_SUBSET_SERVICE_PROVIDER (0x0F) - GW network subset and service provider personalization
 *              - Other values are reserved for future use and are to be handled as unknown personalization features by the client.
 *
 *  @param  temporary_unlock_time_left
 *          - Number of seconds remaining before the personalization feature gets reactivated.
 */
typedef struct
{
    uint8_t temporary_depersonalization_status_len;
    uint8_t temporary_unlock_status_len;
    uint8_t feature[UIM_MAX_ACTIVE_PERS_FEATURES];
    uint32_t temporary_unlock_time_left[UIM_MAX_ACTIVE_PERS_FEATURES];
} uim_tempDepersonalizationStatus;

/**
 * \ingroup uim
 * 
 *  This structure contains information of Personalization Reactivation Status
 *
 *  @param  perso_reactivation_status_len
 *          - Number of sets of the following slot, feature, verify_left, and unblock_left
 *
 *  @param  slot
 *          - Indicates the slot to be used.
 *            - Valid values:
 *              - UIM_SLOT_1 (0x01) - Slot 1
 *              - UIM_SLOT_2 (0x02) - Slot 2
 *              - UIM_SLOT_3 (0x03) - Slot 3
 *              - UIM_SLOT_4 (0x04) - Slot 4
 *              - UIM_SLOT_5 (0x05) - Slot 5
 * 
 *  @param  feature
 *          - Indicates the personalization feature to deactivate or unblock.
 *              - Valid values:
 *              - UIM_PERSO_FEATURE_GW_NETWORK (0x00) - GW network personalization
 *              - UIM_PERSO_FEATURE_GW_NETWORK_SUBSET (0x01) - GW network subset personalization
 *              - UIM_PERSO_FEATURE_GW_SERVICE_PROVIDER (0x02) - GW service provider personalization
 *              - UIM_PERSO_FEATURE_GW_CORPORATE (0x03) - GW corporate personalization
 *              - UIM_PERSO_FEATURE_GW_UIM (0x04) - GW UIM personalization
 *              - UIM_PERSO_FEATURE_1X_NETWORK_TYPE_1 (0x05) - 1X network type 1 personalization
 *              - UIM_PERSO_FEATURE_1X_NETWORK_TYPE_2 (0x06) - 1X network type 2 personalization
 *              - UIM_PERSO_FEATURE_1X_HRPD (0x07) - 1X HRPD personalization
 *              - UIM_PERSO_FEATURE_1X_SERVICE_PROVIDER (0x08) - 1X service provider personalization
 *              - UIM_PERSO_FEATURE_1X_CORPORATE (0x09) - 1X corporate personalization
 *              - UIM_PERSO_FEATURE_1X_RUIM (0x0A) - 1X RUIM personalization
 *              - UIM_PERSO_FEATURE_GW_SPN (0x0B) - GW SPN personalization
 *              - UIM_PERSO_FEATURE_GW_SP_EHPLMN (0x0C) - GW SP + EHPLMN personalization
 *              - UIM_PERSO_FEATURE_GW_ICCID (0x0D) - GW ICCID personalization
 *              - UIM_PERSO_FEATURE_GW_IMPI (0x0E) - GW IMPI personalization
 *              - UIM_PERSO_FEATURE_GW_NETWORK_SUBSET_SERVICE_PROVIDER (0x0F) - GW network subset and service provider personalization
 *              - Other values are reserved for future use and are to be handled as unknown personalization features by the client.
 *
 *  @param  verifyLeft
 *          - Number of the remaining attempts to verify
 *            the personalization feature.
 *
 *  @param  unblockLeft
 *          - Number of the remaining attempts to unblock
 *            the personalization feature.
*/
typedef struct
{
    uint8_t perso_reactivation_status_len;
    uint8_t slot[UIM_MAX_ACTIVE_PERS_FEATURES];
    uint8_t feature[UIM_MAX_ACTIVE_PERS_FEATURES];
    uint8_t verifyLeft[UIM_MAX_ACTIVE_PERS_FEATURES];
    uint8_t unblockLeft[UIM_MAX_ACTIVE_PERS_FEATURES];
} uim_personalReactivationStatus;

/**
 * \ingroup uim
 * 
 *  This structure contains information of Personalization Control Key Present
 *
 *  @param  perso_control_key_present_len
 *          - Number of sets of the following feature and ck_present
 * 
 *  @param  feature_control_key_present_len
 *          - Number of sets of the following feature and ck_present
 *
 *  @param  feature
 *          - Indicates the personalization feature to deactivate or unblock.
 *              - Valid values:
 *              - UIM_PERSO_FEATURE_GW_NETWORK (0x00) - GW network personalization
 *              - UIM_PERSO_FEATURE_GW_NETWORK_SUBSET (0x01) - GW network subset personalization
 *              - UIM_PERSO_FEATURE_GW_SERVICE_PROVIDER (0x02) - GW service provider personalization
 *              - UIM_PERSO_FEATURE_GW_CORPORATE (0x03) - GW corporate personalization
 *              - UIM_PERSO_FEATURE_GW_UIM (0x04) - GW UIM personalization
 *              - UIM_PERSO_FEATURE_1X_NETWORK_TYPE_1 (0x05) - 1X network type 1 personalization
 *              - UIM_PERSO_FEATURE_1X_NETWORK_TYPE_2 (0x06) - 1X network type 2 personalization
 *              - UIM_PERSO_FEATURE_1X_HRPD (0x07) - 1X HRPD personalization
 *              - UIM_PERSO_FEATURE_1X_SERVICE_PROVIDER (0x08) - 1X service provider personalization
 *              - UIM_PERSO_FEATURE_1X_CORPORATE (0x09) - 1X corporate personalization
 *              - UIM_PERSO_FEATURE_1X_RUIM (0x0A) - 1X RUIM personalization
 *              - UIM_PERSO_FEATURE_GW_SPN (0x0B) - GW SPN personalization
 *              - UIM_PERSO_FEATURE_GW_SP_EHPLMN (0x0C) - GW SP + EHPLMN personalization
 *              - UIM_PERSO_FEATURE_GW_ICCID (0x0D) - GW ICCID personalization
 *              - UIM_PERSO_FEATURE_GW_IMPI (0x0E) - GW IMPI personalization
 *              - UIM_PERSO_FEATURE_GW_NETWORK_SUBSET_SERVICE_PROVIDER (0x0F) - GW network subset and service provider personalization
 *              - Other values are reserved for future use and are to be handled as unknown personalization features by the client.
 *
 *  @param  ck_present
 *          - Indicates whether the control key is present.
*/
typedef struct
{
    uint8_t perso_control_key_present_len;
    uint8_t feature_control_key_present_len;
    uint8_t feature[UIM_MAX_ACTIVE_PERS_FEATURES];
    uint8_t ck_present[UIM_MAX_ACTIVE_PERS_FEATURES];
} uim_personalControlKeyPresent;

/**
 * \ingroup uim
 * 
 *  This structure contains information of Inactive SimLock Configuration Lists all available inactive SimLock configurations.
 *
 *  @param  config_id
 *          - Configuration ID for inactive SimLock configuration.
 *
 *  @param  config_nickname_len
 *          - Number of sets of the following config_nickname.
 *
 *  @param  config_nickname     
 *          - Configuration nickname for the operator that corresponds to the inactive SimLock configuration.
*/
typedef struct
{
    uint8_t config_id;
    uint8_t config_nickname_len;
    uint8_t config_nickname[255];
} uim_simLockConfig;

/**
 * \ingroup uim
 * 
 *  This structure contains information of Inactive SimLock Configuration Lists all available inactive SimLock configurations.
 *
 *  @param  inactive_simlock_config_len
 *          - Number of sets of the following config_id. config_nickname_len, and config_nickname.
 * 
 *  @param  config_id
 *          - \ref uim_simLockConfig.
*/
typedef struct
{
    uint8_t inactive_simlock_config_len;
    uim_simLockConfig simLockConfig[255];
} uim_inactiveSimLockConfig;

/**
 * \ingroup uim
 * 
 *  This structure contains information of the response parameters associated
 *  with Get Configuration.
 *
 *  @param  pAutoSelection
 *          - Indicates whether the modem is configured to
 *            automatically select the provisioning sessions
 *            at powerup.
 *          - Valid values
 *           - 0 - Automatic provisioning is off
 *           - 1 - Automatic provisioning is on
 *          - Bit to check in ParamPresenceMask - <B>0x10</B>
 *
 *  @param  pPersonalizationStatus
 *          - See @ref uim_personalizationStatus for more information.
 *          - Bit to check in ParamPresenceMask - <B>0x11</B>
 *
 *  @param  pHaltSubscription
 *          - Indicates if the modem is configured to publish
 *            the subscription after successful initialization.
 *          - Valid values
 *           - 0 - Modem proceeds with publishing the subscription
 *           - 1 - Modem does not publish the subscription
 *          - Bit to check in ParamPresenceMask - <B>0x12</B>
 *
 *  @param  pPersonalizationStatusOtherSlots
 *          - Personalization Status of Other Slots
 *          - \ref uim_personalStatusOtherSlots
 *          - Bit to check in ParamPresenceMask - <B>0x13</B>
 * 
 *  @param  usb_uicc_supported
 *          - USB UICC supported flag
 *          - Indicates if the modem is configured to support the USB UICC feature.
 *            - Valid values:
 *              - 0: Modem does not support the USB UICC feature
 *              - 1: Modem supports the USB UICC feature
 *          - Bit to check in ParamPresenceMask - <B>0x14</B>
 * 
 *  @param  sap_client_supported
 *          - Support for SAP in client mode
 *          - Indicates if the modem is configured to support for SAP in client mode.
 *            - Valid values:
 *              - 0: Modem does not support SAP in client mode
 *              - 1: Modem supports SAP in client mode
 *          - Bit to check in ParamPresenceMask - <B>0x15</B>
 * 
 *  @param  pTempDepersonalizationStatus
 *          - Temporary Depersonalization Status
 *          - \ref uim_tempDepersonalizationStatus
 *          - Bit to check in ParamPresenceMask - <B>0x16</B>
 * 
 *  @param  pPersonalReactivationStatus
 *          - Personalization Reactivation Status
 *          - \ref uim_personalReactivationStatus
 *          - Bit to check in ParamPresenceMask - <B>0x17</B>
 * 
 *  @param  pPersonalControlKeyPresent
 *          - Personalization Control Key Present
 *          - \ref uim_personalControlKeyPresent
 *          - Bit to check in ParamPresenceMask - <B>0x18</B>
 * 
 *  @param  remote_simlock_storage
 *          - Remote SimLock Storage
 *          - Indicates whether the modem stores the SimLock configuration on the local file system or on a remote storage.
 *            - Valid values:
 *              - 0: Local SimLock configuration storage
 *              - 1: Remote SimLock configuration storage
 *          - Bit to check in ParamPresenceMask - <B>0x19</B>
 * 
 *  @param  emergency_only_mode
 *          - Emergency Only Mode
 *          - Indicates whether the modem is restricted to emergency calls only.
 *            - Valid values:
 *              - 0: Modem is not in Emergency Only mode
 *              - 1: Modem is in Emergency Only mode 
 *          - Bit to check in ParamPresenceMask - <B>0x1A</B>
 * 
 *  @param extended_apdu
 *          - Support for Extended Length APDU
 *          - Indicates whether the modem supports extended length APDUs.
 *            - Valid values:
 *              - 0: Modem does not support extended length APDUs
 *              - 1: Modem supports extended length APDUs
 *          - Bit to check in ParamPresenceMask - <B>0x1B</B>
 * 
 *  @param  pInactiveSimLockConfig
 *          - Inactive SimLock Configuration Lists all available inactive SimLock configurations.
 *          - \ref uim_inactiveSimLockConfig 
 *          - Bit to check in ParamPresenceMask - <B>0x1C</B>
 * 
 *  @param  ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct
{
    uint8_t                   *pAutoSelection;
    uim_personalizationStatus *pPersonalizationStatus;
    uint8_t                   *pHaltSubscription;
    uim_personalStatusOtherSlots *pPersonalizationStatusOtherSlots;
    uint8_t usb_uicc_supported;
    uint8_t sap_client_supported;
    uim_tempDepersonalizationStatus *pTempDepersonalizationStatus;
    uim_personalReactivationStatus  *pPersonalReactivationStatus;
    uim_personalControlKeyPresent *pPersonalControlKeyPresent;
    uint8_t remote_simlock_storage;
    uint8_t emergency_only_mode;
    uint8_t extended_apdu;
    uim_inactiveSimLockConfig *pInactiveSimLockConfig;
    swi_uint256_t             ParamPresenceMask;
} unpack_uim_SLQSUIMGetConfiguration_t;

/**
 * \ingroup uim
 * 
 * Gets the modem configuration for the UIM module pack.
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_uim_SLQSUIMGetConfiguration(
    pack_qmi_t  *pCtx,
    uint8_t     *pReqBuf,
    uint16_t    *pLen,
    pack_uim_SLQSUIMGetConfiguration_t *reqArg
);

/**
 * \ingroup uim
 * 
 * Gets the modem configuration for the UIM module unpack.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_uim_SLQSUIMGetConfiguration(
    uint8_t  *pResp,
    uint16_t respLen,
    unpack_uim_SLQSUIMGetConfiguration_t *pOutput
);

/**
 * \ingroup uim
 * 
 *  This structure hold parameters about  UIM refresh event indication. 
 *  @param refreshEvent[OPTIONAL]
 *          - see @ref uim_refreshevent
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct
{
    uim_refreshevent refreshEvent;
    swi_uint256_t  ParamPresenceMask;
} unpack_uim_SLQSUIMRefreshCallback_Ind_t;

/**
 * \ingroup uim
 * 
 * Unpack UIM refresh event indication.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_uim_SLQSUIMRefreshCallback_Ind(
    uint8_t  *pResp,
    uint16_t respLen,
    unpack_uim_SLQSUIMRefreshCallback_Ind_t *pOutput
);

/**
 * \ingroup uim
 * 
 *  This structure hold parameters about  UIM refresh event indication. 
 *  \param  indication_token
 *          - Token of the Original Request
 *          - Indicates the token of the original request.
 *  \param  cardResult(optional)
 *          - See \ref uim_cardResult for more information.
 *          - Bit to check in ParamPresenceMask - <B>10</B>
 *
 *  \param  fileAttributes(optional)
 *          - See \ref uim_fileInfo for more information.
 *          - Bit to check in ParamPresenceMask - <B>0x11</B>
 *
 *  \param  file_status(optional)
 *          - File Status.
 *          - Indicates the status of the file. Valid
 *            - Values:
 *              - UIM_FILE_STATUS_DEACTIVATED(0x00) - File is deactivated.
 *              - UIM_FILE_STATUS_ACTIVATED(0x01) â€“ File is activated.
 *              - Other values are reserved for future use and are to be ignored by the client.
 *          - Bit to check in ParamPresenceMask - <B>0x12</B>
 *
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct
{
    uint32_t            indication_token; 
    uim_cardResult      cardResult;
    uim_fileAttributes  fileAttributes;
    uint32_t            file_status;
    swi_uint256_t       ParamPresenceMask;
}unpack_uim_SLQSUIMGetFileAttibutes_Ind_t;

/**
 * \ingroup uim
 * 
 * Unpack UIM refresh event indication.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_uim_GetFileAttributesInd_ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_uim_SLQSUIMGetFileAttibutes_Ind_t *pOutput
);

/**
 * \ingroup uim
 * 
 *  This structure contains the information for write operation.
 *
 *  \param  offset
 *          - Offset for the write operation.
 *
 *  \param  dataLen
 *          - Length of the following elements i.e. data.
 *
 *  \param  data[UIM_MAX_CONTENT_LENGTH]
 *          - Content to write.
 *
 */
typedef struct
{
    uint16_t offset;
    uint16_t dataLen;
    uint8_t data[UIM_MAX_CONTENT_LENGTH];
} uim_writetransparentInfo;

/**
 * \ingroup uim
 * 
 *  This structure contains information of the request parameters associated
 *  with a Write Transparent API.
 *
 *  \param  sessionInfo
 *          - See \ref UIMSessionInformation for more information.
 *
 *  \param  fileId
 *          - See \ref fileInfo for more information.
 *
 *  \param  writeTransparent
 *          - See \ref writetransparentInfo for more information.
 *
 *  \param  pIndicationToken(optional)
 *          - Response in Indication.
 *          - When this TLV is present, it indicates that the result must be
 *            provided in a subsequent indication.
 *
 *  \note   Using NULL for the pointers would make sure that the parameter is
 *          not added to the request.
 */
typedef struct
{
    uim_sessionInformation sessionInfo;
    uim_fileInfo              fileIndex;
    uim_writetransparentInfo  writeTransparent;
    uint32_t                  *pIndicationToken;
} pack_uim_WriteTransparent_t;

/**
 * \ingroup uim
 * 
 * SLQS WriteTransparent pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_uim_WriteTransparent(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_uim_WriteTransparent_t *reqArg
);

/**
 * \ingroup uim
 * 
 *  This structure contains information of the response parameters associated
 *  with a Write Transparent API.
 *
 *  \param  pCardResult(optional)
 *          - See \ref cardResult for more information.
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  \param  pIndicationToken(optional)
 *          - Response in Indication.
 *          - When this TLV is present, it indicates that the result must be
 *            provided in a subsequent indication.
 *          - Bit to check in ParamPresenceMask - <B>17</B>
 *
 *  \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 *  \note   Using NULL for the pointers would make sure that the parameter is
 *          not returned.
 */
typedef struct
{
    uim_cardResult *pCardResult;
    uint32_t       *pIndicationToken;
    swi_uint256_t  ParamPresenceMask;
} unpack_uim_WriteTransparent_t;

/**
 * \ingroup uim
 * 
 * SLQS WriteTransparent unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_uim_WriteTransparent(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_uim_WriteTransparent_t *pOutput
);

/**
 * \ingroup uim
 * 
 *  This structure contains the information for read record information.
 *
 *  \param  record
 *          - Record number (starting from 1).
 *
 *  \param  length
 *          - Length of the content to be read.
 *          - The value 0 is used to read the complete record.
 *
 */
typedef struct
{
    uint16_t record;
    uint16_t length;
} uim_readRecordInfo;

/**
 * \ingroup uim
 * 
 *  This structure contains information of the request parameters associated
 *  with a Read Record API.
 *
 *  \param  sessionInfo
 *          - See \ref UIMSessionInformation for more information.
 *
 *  \param  fileIndex
 *          - See \ref uim_fileInfo for more information.
 *
 *  \param  readRecord
 *          - See \ref uim_readRecordInfo for more information.
 *
 *  \param  pLastRecord
 *          - Last record. 
 *            This value is used to read multiple records at the same time.
 *
 *  \param  pIndicationToken(optional)
 *          - Response in Indication.
 *          - When this TLV is present, it indicates that the result must be
 *            provided in a subsequent indication.
 *
 *  \note   Using NULL for the pointers would make sure that the parameter is
 *          not added to the request.
 */
typedef struct
{
    uim_sessionInformation sessionInfo;
    uim_fileInfo              fileIndex;
    uim_readRecordInfo        readRecord;
    uint16_t                  *pLastRecord;
    uint32_t                  *pIndicationToken;
} pack_uim_ReadRecord_t;

/**
 * \ingroup uim
 * 
 * SLQS ReadRecord pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_uim_ReadRecord(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_uim_ReadRecord_t *reqArg
);

/**
 * \ingroup uim
 * 
 *  This structure contains the information for read operation.
 *
 *  \param  additionalRecordLen
 *          - Number of sets of additionalRecord.
 *
 *  \param  additionalRecord[MAX_DESCRIPTION_LENGTH]
 *          - Read content of all the additional records. Each record has 
 *            the same size as the first record.
 *
 */
typedef struct
{
    uint16_t additionalRecordLen;
    uint8_t  additionalRecord[MAX_DESCRIPTION_LENGTH];
} uim_additionalReadResult;

/**
 * \ingroup uim
 * 
 *  This structure contains information of the response parameters associated
 *  with a Read Record API.
 *
 *  \param  pCardResult
 *          - See \ref cardResult for more information.
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  \param  pReadResult
 *          - See \ref readResult for more information.
 *          - Bit to check in ParamPresenceMask - <B>17</B>
 *
 *  \param  pAdditionalReadResult
 *          - See \ref additionalReadResult for more information.
 *          - Bit to check in ParamPresenceMask - <B>18</B>
 *
 *  \param  pIndicationToken(optional)
 *          - Response in Indication.
 *          - When this TLV is present, it indicates that the result must be
 *            provided in a subsequent indication.
 *          - Bit to check in ParamPresenceMask - <B>19</B>
 *
 *  \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 *  \note   Using NULL for the pointers would make sure that the parameter is
 *          not added to the request.
 */
typedef struct
{
    uim_cardResult            *pCardResult;
    uim_readResult            *pReadResult;
    uim_additionalReadResult  *pAdditionalReadResult;
    uint32_t                  *pIndicationToken;
    swi_uint256_t             ParamPresenceMask;
} unpack_uim_ReadRecord_t;

/**
 * \ingroup uim
 * 
 * SLQS ReadRecord unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_uim_ReadRecord(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_uim_ReadRecord_t *pOutput
);

/**
 * \ingroup uim
 * 
 *  This structure contains the information for write operation.
 *
 *  \param  record
 *          - Record number (starting from 1).
 *          - This field is ignored for cyclic files.
 *
 *  \param  dataLen
 *          - Number of sets of content.
 *
 *  \param  data[MAX_DESCRIPTION_LENGTH]
 *          - Content to write.
 *
 */
typedef struct
{
    uint16_t record;
    uint16_t dataLen;
    uint8_t  data[MAX_DESCRIPTION_LENGTH];
} uim_writeRecordInfo;

/**
 * \ingroup uim
 * 
 *  This structure contains information of the request parameters associated
 *  with a Write Transparent API.
 *
 *  \param  sessionInfo
 *          - See \ref UIMSessionInformation for more information.
 *
 *  \param  fileIndex
 *          - See \ref fileInfo for more information.
 *
 *  \param  writeRecord
 *          - See \ref writeRecordInfo for more information.
 *
 *  \param  pIndicationToken(optional)
 *          - Response in Indication.
 *          - When this TLV is present, it indicates that the result must be
 *            provided in a subsequent indication.
 *
 *  \note   Using NULL for the pointers would make sure that the parameter is
 *          not added to the request.
 */
typedef struct
{
    uim_sessionInformation sessionInfo;
    uim_fileInfo              fileIndex;
    uim_writeRecordInfo       writeRecord;
    uint32_t                  *pIndicationToken;
} pack_uim_WriteRecord_t;

/**
 * \ingroup uim
 * 
 * SLQS WriteRecord pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_uim_WriteRecord(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_uim_WriteRecord_t *reqArg
);

/**
 * \ingroup uim
 * 
 *  This structure contains information of the response parameters associated
 *  with a Write Record API.
 *
 *  \param  pCardResult
 *          - See \ref cardResult for more information.
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  \param  pIndicationToken(optional)
 *          - Response in Indication.
 *          - When this TLV is present, it indicates that the result must be
 *            provided in a subsequent indication.
 *          - Bit to check in ParamPresenceMask - <B>17</B>
 *
 *  \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 *  \note   Using NULL for the pointers would make sure that the parameter is
 *          not added to the request.
 */
typedef struct
{
    uim_cardResult  *pCardResult;
    uint32_t        *pIndicationToken;
    swi_uint256_t   ParamPresenceMask;
} unpack_uim_WriteRecord_t;

/**
 * \ingroup uim
 * 
 * SLQS WriteRecord unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_uim_WriteRecord(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_uim_WriteRecord_t *pOutput
);

/**
 * \ingroup uim
 * 
 *  This structure contains information of the Open Logical Channel.
 *
 *  \param  aidLength
 *          - Number of sets of the following elements
 *            - Application Identifier
 *
 *  \param  aid
 *          - Application identifier value or channel ID. This
 *            value is required for non-provisioning and for
 *            logical channel session types. It is ignored in all
 *            other cases
 */
typedef struct
{
    uint8_t   aidLength;
    uint8_t   aid[MAX_DESCRIPTION_LENGTH];
} uim_openChannel;

/**
 * \ingroup uim
 * 
 *  This structure contains information of the request parameters associated
 *  with Opens and closes a logical channel to an application on a UICC card.
 *
 *  \param  bSlot
 *          - Indicates the slot to be used.
 *              - 1 - Slot 1
 *              - 2 - Slot 2
 *              - 3 - Slot 3
 *              - 4 - Slot 4
 *              - 5 - Slot 5
 *
 *  \param  pOpenCh(optional)
 *          - See \ref openChannel for more information.
 *
 *  \param  pChID(optional)
 *          - ID of the logical channel to be closed.
 *
 *  \param  pFileControlInfo(optional)
 *          - Template requested from the card in the SELECT command when the 
 *            application is selected. When this TLV is missing, FCP is 
 *            requested by default. Valid values:
 *               - 0 â€“ No data
 *               - 1 â€“ FCP
 *               - 2 â€“ FCI
 *               - 3 â€“ FCI with interfaces
 *               - 4 â€“ FMD
 *
 *  \param  pTerminate(optional)
 *          - Indicates whether the application is terminated with a SELECT request
 *            before closing the associated logical channel. When the Termination of the
 *            Application TLV is missing, the default behavior is TRUE to terminate the
 *            application. 
 *
 *  \note     - if the TLV is missing, the service returns all
 *              configuration items in the response.
 */
typedef struct
{
    uint8_t            bSlot;
    uim_openChannel    *pOpenCh;
    uint8_t            *pChID;
    uint8_t            *pFileControlInfo;
    uint8_t            *pTerminate;
} pack_uim_LogicalChannel_t;

/**
 * \ingroup uim
 * 
 * SLQS LogicalChannel pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_uim_LogicalChannel(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_uim_LogicalChannel_t *reqArg
);

/**
 * \ingroup uim
 * 
 *  This structure contains response to SELECT.
 *
 *  \param  respLen
 *          - Number of sets of the resp.
 *
 *  \param  resp
 *          - Raw value of the response sent by the
 *            card to the initial SELECT command.
 */
typedef struct
{
    uint8_t   respLen;
    uint8_t   resp[MAX_DESCRIPTION_LENGTH];
} uim_selectResp;

/**
 * \ingroup uim
 * 
 *  This structure contains information of Card Result.
 *
 *  \param  sw1
 *          - SW1 received from the card.
 *
 *  \param  sw2
 *          - SW2 received from the card.
 */
typedef struct
{
    uint8_t   sw1;
    uint8_t   sw2;
} uim_logicalChCardResult;

/**
 * \ingroup uim
 * 
 *  This structure contains information of the response parameters associated
 *  with Opens and closes a logical channel to an application on a UICC card.
 *
 *  \param  pChID(optional)
 *          - ID of the logical channel that was opened.
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  \param  pCardResult(optional)
 *          - See \ref logicalChCardResult for more information.
 *          - Bit to check in ParamPresenceMask - <B>17</B>
 *
 *  \param  pSelectResp(optional)
 *          - See \ref selectResp for more information.
 *          - Bit to check in ParamPresenceMask - <B>18</B>
 *
 *  \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct
{
    uint8_t                 *pChID;
    uim_logicalChCardResult *pCardResult;
    uim_selectResp          *pSelectResp;
    swi_uint256_t           ParamPresenceMask;
} unpack_uim_LogicalChannel_t;

/**
 * \ingroup uim
 * 
 * SLQS LogicalChannel unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_uim_LogicalChannel(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_uim_LogicalChannel_t *pOutput
);

/**
 *  This structure contains information of the request parameters associated
 *  with a Set Service Status API.
 *
 *  \param  sessionInfo
 *          - See \ref UIMSessionInformation for more information.
 *
 *  \param  pFDNStatus (Optional)
 *          - 0: Disables the FDN
 *          - 1: Enables the FDN
 *
 *  \note   Using NULL for the pointers would make sure that the parameter is
 *          not added to the request.
 */
typedef struct
{
    uim_sessionInformation sessionInfo;
    uint8_t                *pFDNStatus;
} pack_uim_SetServiceStatus_t;

/**
 * \ingroup uim
 * 
 * SLQS SetServiceStatus pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_uim_SetServiceStatus(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_uim_SetServiceStatus_t *reqArg
);

typedef unpack_result_t  unpack_uim_SetServiceStatus_t;

/**
 * \ingroup uim
 * 
 * SLQS SetServiceStatus unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_uim_SetServiceStatus(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_uim_SetServiceStatus_t *pOutput
);

/**
 *  This structure contains information of the request parameters associated
 *  with a Get Service Status API.
 *
 *  \param  sessionInfo
 *          - See \ref UIMSessionInformation for more information.
 *
 *  \param  capMask
 *          Bitmask of the capabilities the client retrieves from the card
 *              - Bit 0 - FDN status
 *              - Bit 1 - Hidden key PIN status (only for USIM cards)
 *              - Bit 2 â€“ Index in the EF-DIR (only for UICC cards)
 *
 *  \note   Using NULL for the pointers would make sure that the parameter is
 *          not added to the request.
 */
typedef struct
{
    uim_sessionInformation sessionInfo;
    uint32_t               capMask;
} pack_uim_GetServiceStatus_t;

/**
 * \ingroup uim
 * 
 * SLQS GetServiceStatus pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_uim_GetServiceStatus(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_uim_GetServiceStatus_t *reqArg
);

/**
 *  This structure contains information of the response parameters associated
 *  with a Authenticate API.
 *
 *  \param  pFDNStatus(optional)
 *          0 â€“ FDN is not available
 *          1 â€“ FDN is available and disabled
 *          2 â€“ FDN is available and enabled
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  \param  pHiddenKeyStatus(optional)
 *          0 â€“ Not supported
 *          1 â€“ Enabled and not verified
 *          2 â€“ Enabled and verified
 *          3 â€“ Disabled
 *          - Bit to check in ParamPresenceMask - <B>17</B>
 *
 *  \param  pIndex(optional)
 *          - Index of the application in EF_DIR file, starting from 1.
 *          - Bit to check in ParamPresenceMask - <B>18</B>
 *
 *  \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 z blurb
 *
 *  \note   Using NULL for the pointers would make sure that the parameter is
 *          not returned.
 */
typedef struct
{
    uint8_t       *pFDNStatus;
    uint8_t       *pHiddenKeyStatus;
    uint8_t       *pIndex;
    swi_uint256_t ParamPresenceMask;
} unpack_uim_GetServiceStatus_t;

/**
 * \ingroup uim
 * 
 * SLQS GetServiceStatus unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_uim_GetServiceStatus(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_uim_GetServiceStatus_t *pOutput
);

/**
 * \ingroup uim
 * 
 *  This structure contains information of the response parameters associated
 *  with a set of PIN related API's.
 *
 *  \param  indication_token - Token of the Original Request
 *          - Indicates the token of the original request.
 *          - Bit to check in ParamPresenceMask - <B>0x01</B>
 *
 *  \param  pRemainingRetries(optional)
 *          - See \ref uim_remainingRetries for more information.
 *          - Bit to check in ParamPresenceMask - <B>0x10</B>
 *
 *  \param  pEncryptedPIN1(optional)
 *          - See \ref uim_encryptedPIN1 for more information.
 *          - Bit to check in ParamPresenceMask - <B>0x11</B>
 *
 *  \param  pCardResult
 *          - See \ref uim_cardResult for more information.
 *          - Bit to check in ParamPresenceMask - <B>0x12</B>
 * 
 *  @param  Tlvresult
 *           - unpack Tlv result
 * 
 *  \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct{
    uint32_t indication_token;
    uim_remainingRetries *pRemainingRetries;
    uim_encryptedPIN1    *pEncryptedPIN1;
    uim_cardResult  *pCardResult;
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_uim_VerifyPin_ind_t;

/**
 * \ingroup uim
 * 
 * Verify PIN Indication.
 *
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 *  @param  pVerifyPinInd
 *          - See \ref unpack_uim_VerifyPin_ind_t for more information.
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 */
int unpack_uim_SLQSUIMVerifyPin_ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_uim_VerifyPin_ind_t *pVerifyPinInd
);

typedef unpack_uim_VerifyPin_ind_t unpack_uim_SetPinProtection_ind_t;
/**
 * \ingroup uim
 * 
 * PIN Protection indication unpack API.
 *
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 *  @param  pSetPinProtectionInd
 *          - See \ref unpack_uim_VerifyPin_ind_t for more information.
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 */
int unpack_uim_SLQSUIMSetPinProtection_ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_uim_SetPinProtection_ind_t *pSetPinProtectionInd
);

typedef unpack_uim_VerifyPin_ind_t unpack_uim_UnblockPin_ind_t;
/**
 * \ingroup uim
 * 
 * PIN Unblock indication unpack API.
 *
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 *  @param  pUnblockPinInd
 *          - See \ref unpack_uim_VerifyPin_ind_t for more information.
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 */
int unpack_uim_SLQSUIMUnblockPin_ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_uim_UnblockPin_ind_t *pUnblockPinInd
);

typedef unpack_uim_VerifyPin_ind_t unpack_uim_ChangePin_ind_t;
/**
 * \ingroup uim
 * 
 * PIN Change indication unpack API.
 *
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param  pChangePinInd
 *          - See \ref unpack_uim_VerifyPin_ind_t for more information.
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 */
int unpack_uim_SLQSUIMChangePin_ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_uim_ChangePin_ind_t *pChangePinInd
);

/**
 * \ingroup uim
 * 
 *  This structure contains the Authentication Result.
 *
 *  @param  content_len [IN/OUT] 
 *          - Number of sets of the content
 *
 *  @param  pContent
 *          Authenticate data. This value is a sequence of bytes returned from the card.
 */
typedef struct
{
    uint16_t content_len;
    uint8_t *pContent;
}uim_authenticationResult;

/**
 * \ingroup uim
 * 
 *  This structure contains information of Authenticate Indication.
 *
 *  \param  indication_token - Token of the Original Request
 *          - Indicates the token of the original request.
 *          - Bit to check in ParamPresenceMask - <B>0x01</B>
 *
 *  \param  pCardResult(optional)
 *          - See \ref uim_cardResult for more information.
 *          - Bit to check in ParamPresenceMask - <B>0x10</B>
 * 
 *  \param  pAuthenticationResult(optional)
 *          - See \ref uim_remainingRetries for more information.
 *          - Bit to check in ParamPresenceMask - <B>0x11</B>
 *
 *  @param  Tlvresult
 *           - unpack Tlv result
 * 
 *  \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct{
    uint32_t indication_token;
    uim_cardResult  *pCardResult;
    uim_authenticationResult  *pAuthenticationResult;
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_uim_Authenticate_ind_t;

/**
 * \ingroup uim
 * 
 * Authentication indication.
 *
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 *  @param  pAuthenticationInd
 *          - See \ref unpack_uim_Authenticate_ind_t for more information.
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 */
int unpack_uim_SLQSUIMAuthenticate_ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_uim_Authenticate_ind_t *pAuthenticationInd
);

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif

