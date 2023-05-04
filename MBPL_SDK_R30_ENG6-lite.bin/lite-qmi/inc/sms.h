/**
 * \ingroup liteqmi
 * \ingroup sms
 * \file sms.h
 */
#ifndef __LITEQMI_SMS_H__
#define __LITEQMI_SMS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include <stdint.h>

#define MAX_SMS_MESSAGE_SIZE 2048
#define MAX_SMS_LIST_SIZE 255
#define MAX_MS_TRANSFER_ROUTE_MSG 256
#define MAX_MSE_TWS_MSG 1254
#define MAX_MSC_ADDRESS_SIZE 22 //Address of the SMSC given in ASCII digits; can be prefixed with + (maximum 20 digits, not including the +)
#define SMSC_TYPE_LEN 0x03
#define SMS_CONFIG_LEN         0x05
#define SMS_MAX_SMS_ROUTES     0x0A
#define SMS_NUM_OF_SET         0xFF

#define LEN_SMS_Timestamp			7
#define LEN_IMEI					16
#define LEN_MAX_String				0xFF
#define LEN_SMS_ADDRESS_BYTE		51	
#define	LEN_MAX_SEGMENTS            8
#define LINKTIMER 2
#define SMS_MAX_PDU_LEN             176

/**
 * \ingroup sms
 * 
 * This sturcture contains pack get SMS parameters.
 * @param storageType
 *          - SMS message storage type
 *              - 0 - UIM - Invalid in case of CDMA device that does not
 *                          require SIM
 *              - 1 - NV
 *
 * @param messageIndex
 *          - Message index
 *
 * @param pMessageMode
 *          - 0x00 - CDMA, LTE (if network type is CDMA)
 *          - 0x01 - GW, LTE (if network type is UMTS)
 *
 */
typedef struct{
    uint32_t storageType;
    uint32_t messageIndex;
    uint8_t *pMessageMode;
} pack_sms_SLQSGetSMS_t;

/**
 * \ingroup sms
 * 
 * This sturcture contains unpack get SMS parameters.
 * @param messageTag
 *          - Message tag
 *              - 0 - Read
 *              - 1 - Not read
 *              - 2 - Mobile originated and sent
 *              - 3 - Mobile originated but not yet sent
 *           - Bit to check in ParamPresenceMask - <B>1</B>
 *
 * @param messageFormat
 *          - Message format
 *              - 0 - CDMA (IS-637B)
 *              - 1 - 5 (Reserved)
 *              - 6 - GSM/WCDMA PP
 *           - Bit to check in ParamPresenceMask - <B>1</B>
 *
 * @param messageSize
 *          - Upon input the maximum number of bytes that can be written to the
 *            message array.
 *          - Upon successful output the actual number of bytes written to the
 *            message array.
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 * @param message
 *          - The message contents array
 *
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct {
    uint32_t  messageTag;
    uint32_t  messageFormat;
    uint32_t  messageSize;
    uint8_t   message[MAX_SMS_MESSAGE_SIZE];
    swi_uint256_t  ParamPresenceMask;
} unpack_sms_SLQSGetSMS_t;

/**
 * \ingroup sms
 * 
 * get sms pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param reqParam packed request
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_sms_SLQSGetSMS(
        pack_qmi_t  *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen,
        pack_sms_SLQSGetSMS_t *reqParam
        );

/**
 * \ingroup sms
 * 
 * get sms unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_sms_SLQSGetSMS(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_sms_SLQSGetSMS_t *pOutput
        );

/**
 * \ingroup sms
 * 
 * This sturcture contains unpack get SMS parameters.
 * @param messageTag
 *          - Message tag
 *              - 0 - Read
 *              - 1 - Not read
 *              - 2 - Mobile originated and sent
 *              - 3 - Mobile originated but not yet sent
 *           - Bit to check in ParamPresenceMask - <B>1</B>
 *
 * @param messageFormat
 *          - Message format
 *              - 0 - CDMA (IS-637B)
 *              - 1 - 5 (Reserved)
 *              - 6 - GSM/WCDMA PP
 *           - Bit to check in ParamPresenceMask - <B>1</B>
 *
 * @param messageSize
 *          - Upon input the maximum number of bytes that can be written to the
 *            message array.
 *          - Upon successful output the actual number of bytes written to the
 *            message array.
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 * @param pMessage
 *          - Pointer to message content
 *
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct {
    uint32_t  messageTag;
    uint32_t  messageFormat;
    uint32_t  messageSize;
    uint8_t   *pMessage;
    swi_uint256_t  ParamPresenceMask;
} unpack_sms_SLQSGetSmsExt_t;

/**
 * \ingroup sms
 * 
 * get sms unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_sms_SLQSGetSmsExt(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_sms_SLQSGetSmsExt_t *pOutput
        );

/**
 * \ingroup sms
 * 
 * This structure contains pack get SMS list parameters.
 * @param storageType
 *          - SMS message storage type
 *              - 0 - UIM - Invalid in case of CDMA device that does not
 *                          require SIM
 *              - 1 - NV
 *
 * @param pRequestedTag (Optional) 
 *          - Message tag
 *              - 0 - Read
 *              - 1 - Not read
 *              - 2 - Mobile originated and sent
 *              - 3 - Mobile originated but not yet sent
 *
 * @param pMessageMode (Optional) 
 *          - Message Mode
 *              - 0x00 - CDMA, LTE (if network type is CDMA)
 *              - 0x01 - GW, LTE (if network type is UMTS)
 */
typedef struct{
    uint32_t storageType;
    uint32_t *pRequestedTag;
    uint8_t  *pMessageMode;
} pack_sms_SLQSGetSMSList_t;

/**
 * \ingroup sms
 * 
 * This structure contains SMS message list.
 * @param messageIndex
 *          - Message index of each matched message
 * @param messageTag
 *          - Messagetag
 */
typedef struct 
{
    uint32_t messageIndex;
    uint32_t messageTag;
}qmiSmsMessageList;

/**
 * \ingroup sms
 * 
 * This structure contains unpack get SMS list parameters.
 * @param messageListSize
 *          - Upon input the maximum number of elements that the message list
 *            array can contain.
 *          - Upon successful output the actual number of elements in the
 *            message list array.
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 * @param messageList
 *          - Message List
 *          - See @ref qmiSmsMessageList for more information
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct{
    uint32_t    messageListSize;
    qmiSmsMessageList messageList[MAX_SMS_LIST_SIZE];
    swi_uint256_t  ParamPresenceMask;
} unpack_sms_SLQSGetSMSList_t;

/**
 * \ingroup sms
 * 
 * get sms list pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param reqParam packed request
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int pack_sms_SLQSGetSMSList(
        pack_qmi_t  *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen,
        pack_sms_SLQSGetSMSList_t *reqParam
        );

/**
 * \ingroup sms
 * 
 * get sms list unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int unpack_sms_SLQSGetSMSList(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_sms_SLQSGetSMSList_t *pOutput
        );

/**
 * \ingroup sms
 * 
 * This structure contains pack modify SMS status parameters.
 * @param storageType
 *          - SMS message storage type
 *              - 0 - UIM - Invalid in case of CDMA device that does not
 *                          require SIM
 *              - 1 - NV
 *
 * @param messageIndex
 *          - Message index
 *
 * @param messageTag
 *          - Message tag
 *              - 0 - Read
 *              - 1 - Not read
 *
 * @param pMessageMode
 *          - 0x00 - CDMA, LTE (if network type is CDMA)
 *          - 0x01 - GW, LTE (if network type is UMTS)
 *
 */
typedef struct{
    uint32_t storageType;
    uint32_t messageIndex;
    uint32_t messageTag;
    uint8_t *pMessageMode;
} pack_sms_SLQSModifySMSStatus_t;

/**
 * \ingroup sms
 * 
 * modify sms status pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param reqParam packed request
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int pack_sms_SLQSModifySMSStatus(
        pack_qmi_t  *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen,
        pack_sms_SLQSModifySMSStatus_t *reqParam
        );

/**
 * \ingroup sms
 * 
 * This structure contains unpack modify SMS status parameters.
 * 
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct{
    swi_uint256_t  ParamPresenceMask;
} unpack_sms_SLQSModifySMSStatus_t;

/**
 * \ingroup sms
 * 
 * modify sms status unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int unpack_sms_SLQSModifySMSStatus(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_sms_SLQSModifySMSStatus_t *pOutput
        );

/**
 * \ingroup sms
 * 
 * This structure contains pack delete SMS parameters.
 * @param storageType
 *          - SMS message storage type
 *              - 0 - UIM - Invalid in case of CDMA device that does not
 *                          require SIM
 *              - 1 - NV
 *
 * @param pMessageIndex
 *          - (Optional) message index
 *
 * @param pMessageTag
 *          - (Optional) message tag
 *              - 0 - Read
 *              - 1 - Not read
 *              - 2 - Mobile originated and sent
 *              - 3 - Mobile originated but not yet sent
 *
 * @param pMessageMode
 *        - (Optional) message mode
 *        - this must be included if the device is capable of supporting more than one protocol
 *        - e.g. CDMA and GW
 *          - 0x00 - CDMA, LTE (if network type is CDMA)
 *          - 0x01 - GW, LTE (if network type is UMTS)
 *
 */
typedef struct{
    uint32_t storageType;
    uint32_t *pMessageIndex;
    uint32_t *pMessageTag;
    uint8_t  *pMessageMode;
} pack_sms_SLQSDeleteSMS_t;

/**
 * \ingroup sms
 * 
 * delete sms pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param reqParam packed request
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int pack_sms_SLQSDeleteSMS(
        pack_qmi_t  *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen,
        pack_sms_SLQSDeleteSMS_t *reqParam
        );

/**
 * \ingroup sms
 * 
 * This structure contains unpack delete SMS parameters.
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */

typedef struct{
    swi_uint256_t  ParamPresenceMask;
} unpack_sms_SLQSDeleteSMS_t;

/**
 * \ingroup sms
 * 
 * delete sms unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int unpack_sms_SLQSDeleteSMS(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_sms_SLQSDeleteSMS_t *pOutput
        );

/**
 * \ingroup sms
 * 
 * This structure contains pack send SMS parameters.
 * @param messageFormat
 *          - Message format
 *              - 0 - CDMA (IS-637B)
 *              - 1 - 5 (Reserved)
 *              - 6 - GSM/WCDMA PP
 *
 * @param messageSize
 *          - The length of the message contents in bytes
 *
 * @param pLinktimer
 *          - GW SMS link open for the specified number of second
 *
 * @param pMessage
 *          - The message contents in PDU format contains SMS header and payload message
 *
 */
typedef struct{
    uint32_t messageFormat;
    uint32_t messageSize;
    uint8_t  *pMessage;
    uint8_t *pLinktimer;
} pack_sms_SendSMS_t;

/**
 * \ingroup sms
 * 
 * This structure contains unpack send SMS parameters.
 * @param messageID
 *          - WMS message ID
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 * @param messageFailureCode
 *          - WMS cause code per 3GPP2 N.S0005-0 Section 6.5.2.125; see Table A-1 for more information.
 *          - Bit to check in ParamPresenceMask - <B>0x10</B>
 *
 * @param error_class
 *          - Error class. 
 *              - Values:
 *                  - 0x00 - ERROR_CLASS_TEMPORARY
 *                  - 0x01 - ERROR_CLASS_PERMANENT
 *          - Bit to check in ParamPresenceMask - <B>0x11</B>
 * 
 * @param rp_cause
 *          - GW Cause Info
 *          - GW RP cause per 3GPP TS 24.011 Section 8.2.5.4; see Table A-2 for more information.
 *          - Bit to check in ParamPresenceMask - <B>0x12</B>
 * 
 * @param tp_cause
 *          - GW TP cause per 3GPP TS 23.040 Section 9.2.3.22; see Table A-3 for more information.
 *          - Bit to check in ParamPresenceMask - <B>0x12</B>
 * 
 * @param messag_delivery_failure_type
 *          - Message delivery failure type. 
 *              - Values:
 *                  - 0x00 - WMS_MESSAGE_DELIVERY_FAILURE_TEMPORARY
 *                  - 0x01 - WMS_MESSAGE_DELIVERY_FAILURE_PERMANENT
 *          - Bit to check in ParamPresenceMask - <B>0x13</B>
 * 
 * @param messg_delivery_failure_cause
 *          - Message Delivery Failure Cause
 *              - Message delivery failure cause.
 *              - Values:
 *                  - WMS_MESSAGE_BLOCKED_DUE_TO_CALL_CONTROL (0x00)
 *                  - WMS_MESSAGE_BLOCKED_DUE_TO_VOICE_OR_DATA_CALL (0x01)
 *                  - WMS_MESSAGE_BLOCKED_DUE_TO_ACCESS_BARRING (0x02)
 *          - Bit to check in ParamPresenceMask - <B>0x14</B>
 * 
 * @param alpha_id_len
 *          - Number of sets of the following pAlpha_id
 *          - Bit to check in ParamPresenceMask - <B>0x15</B>
 *          
 * @param pAlpha_id
 *          - Alpha ID
 *          - Bit to check in ParamPresenceMask - <B>0x15</B>
 * 
 * @param reject_type
 *          - Lower Layer Reject Cause Information (Indicates the reject type and the error code for lower layer failures)
 *          - Lower layer reject type 
 *              - Values:
 *                  - 0x01 - NAS OTA Reject (3GPP TS 24.008)
 *          - Bit to check in ParamPresenceMask - <B>0x16</B>
 * 
 * @param reject_value
 *          - Reject cause value
 *          - Bit to check in ParamPresenceMask - <B>0x16</B>
 * 
 * @param sms_ims_rej_cause_info
 *          - IMS reject cause Information
 *          - (Indicates the IMS reject cause)
 *          - Bit to check in ParamPresenceMask - <B>0x17</B>
 * 
 * @param barring_timer
 *          - Barring timer information
 *          - (Barring timer value in ms)
 *          - Bit to check in ParamPresenceMask - <B>0x18</B>
 *
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct{
    uint16_t  messageID;
    uint32_t  messageFailureCode;
    uint8_t   error_class;
    uint16_t  rp_cause;
    uint8_t   tp_cause;
    uint8_t   messag_delivery_failure_type;
    uint8_t   messg_delivery_failure_cause;
    uint8_t   alpha_id_len;
    uint8_t   *pAlpha_id;
    uint32_t  reject_type;
    uint8_t   reject_value;
    uint16_t  sms_ims_rej_cause_info;
    uint32_t  barring_timer;
    swi_uint256_t  ParamPresenceMask;
} unpack_sms_SendSMS_t;

/**
 * \ingroup sms
 * 
 * send sms list pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param reqParam packed request
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int pack_sms_SendSMS(
        pack_qmi_t  *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen,
        pack_sms_SendSMS_t *reqParam
        );

/**
 * \ingroup sms
 * 
 * send sms  unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int unpack_sms_SendSMS(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_sms_SendSMS_t *pOutput
        );

enum eqmiCbkSetStatus{
    LITEQMI_QMI_CBK_PARAM_RESET = 0,
    LITEQMI_QMI_CBK_PARAM_SET   = 1,
    LITEQMI_QMI_CBK_PARAM_NOCHANGE
};

/**
 * \ingroup sms
 * 
 * This strucure contains pack set new SMS callback parameters.
 * @param status callback parameter
 */
typedef struct{
    enum eqmiCbkSetStatus status;
} pack_sms_SetNewSMSCallback_t;

/**
 * \ingroup sms
 * 
 * set new sms callback pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param reqParam packed request
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int pack_sms_SetNewSMSCallback(
        pack_qmi_t  *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen,
        pack_sms_SetNewSMSCallback_t* reqParam
        );

/**
 * \ingroup sms
 * 
 * This structure contains unpack set new SMS callback.
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct{
    swi_uint256_t  ParamPresenceMask;
} unpack_sms_SetNewSMSCallback_t;

/**
 * \ingroup sms
 * 
 * set new sms callback unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] Output unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int unpack_sms_SetNewSMSCallback(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_sms_SetNewSMSCallback_t *Output
        );
/**
 * \ingroup sms
 * 
 * This structure contains MT message information.
 * @param storageType memory storage 0x00-UIM  0x01-NV
 * @param messageIndex MT Message index
 */
typedef struct
{
    uint32_t storageType;
    uint32_t messageIndex;
} sMSMTMessageInfo;

/**
 * \ingroup sms
 * 
 * This structure contains MT message TLV information.
 * @param MTMessageInfo
 *          - MT Message
 *          - See @ref sMSMTMessageInfo for more information
 *
 */
typedef struct
{
    sMSMTMessageInfo MTMessageInfo;
}newMTMessageTlv;

/**
 * \ingroup sms
 * 
 * This structure contains Transfer route MT message information.
 * @param ackIndicator
 *          - Parameter to indicate if ACK must be sent by the control point
 *              0x00 - Send ACK
 *              0x01 - Do not send ACK
 *
 * @param transactionID
 *          - Transaction ID of the message
 *
 * @param format
 *          - Message format
 *              0x00 - CDMA
 *              0x02 - 0x05 - Reserved
 *              0x06 - GW_PP
 *              0x07 - GW_BC
 *
 * @param length
 *          - Length of the raw message. This length should not exceed the
 *            maximum WMS payload length of 256 bytes
 *
 * @param data
 *          - Raw message data
 */
typedef struct
{
    uint8_t  ackIndicator;
    uint32_t transactionID;
    uint8_t  format;
    uint16_t  length;
    uint8_t  data[MAX_MS_TRANSFER_ROUTE_MSG];
} sMSTransferRouteMTMessageInfo;

/**
 * \ingroup sms
 * 
 * This structure contains Transfer route MT message TLV information.
 * @param TransferRouteMTMessageInfo
 *          - Transfer Route MT Message
 *          - See @ref sMSTransferRouteMTMessageInfo for more information
 */
typedef struct
{
    sMSTransferRouteMTMessageInfo TransferRouteMTMessageInfo;
}transferRouteMessageTlv;

/**
 * \ingroup sms
 * 
 * This structure contains message mode information.
 * @param messageMode
 *          - Message Mode
 *           - 0x00 - CDMA
 *           - 0x01 - GW
 */
typedef struct
{
    uint8_t  messageMode;
} sMSMessageModeInfo;

/**
 * \ingroup sms
 * 
 * This structure contains message mode TLV information.
 * @param MessageModeInfo
 *          - Message Mode
 *          - See @ref sMSMessageModeInfo for more information
 */
typedef struct
{
    sMSMessageModeInfo MessageModeInfo;
}messageModeTlv;

/**
 * \ingroup sms
 * 
 * This structure contains ETWS information
 * @param notificationType
 *          - Message mode
 *              0x00 - Primary
 *              0x01 - Secondary GSM
 *              0x02 - Secondary UMTS
 *
 * @param length
 *          - Number of sets of following elements
 *
 * @param data
 *          - Raw message data
 */

typedef struct
{
    uint8_t notificationType;
    uint16_t length;
    uint8_t data[MAX_MSE_TWS_MSG];
} sMSEtwsMessageInfo;

/**
 * \ingroup sms
 * 
 * This structure contains ETWS TLV information
 * @param EtwsMessageInfo
 *          - ETWS Message
 *          - See @ref sMSEtwsMessageInfo for more information
 */
typedef struct
{
    sMSEtwsMessageInfo EtwsMessageInfo;
}sMSEtwsMessageTlv;

/**
 * \ingroup sms
 * 
 * This structure contains ETWS PLMN information
 * @param mobileCountryCode
 *          - 16 bit representation of MCC
 *              value range : 0 -999
 *
 * @param mobileNetworkCode
 *          - 16 bit representation of MNC
 *              value range : 0 -999
 *
 */
typedef struct
{
    uint16_t mobileCountryCode;
    uint16_t mobileNetworkCode;
} sMSEtwsPlmnInfo;

/**
 * \ingroup sms
 * 
 * This structure contains ETWS PLMN TLV information
 * @param ETWSPLMNInfo
 *          - ETWS PLMN Information
 *          - See @ref sMSEtwsPlmnInfo for more information
 */
typedef struct
{
    sMSEtwsPlmnInfo ETWSPLMNInfo;
}eTWSPLMNInfoTlv;

/**
 * \ingroup sms
 * 
 * This structure contains SMSC information
 * @param length
 *          - Number of sets of following element
 *
 * @param data
 *          - SMSC address
 */

typedef struct
{
    uint8_t length;
    uint8_t data[MAX_MSC_ADDRESS_SIZE];
} sMSCAddressInfo;

/**
 * \ingroup sms
 * 
 * This structure contains SMSC TLV information
 * @param SMSCInfo
 *          - SMSC Address
 *          - See @ref sMSCAddressInfo for more information
 */
typedef struct
{
    sMSCAddressInfo SMSCInfo;
}sMSCAddressTlv;

/**
 * \ingroup sms
 * 
 * This structure contains SMS on IMS information
 * @param smsOnIMS SMS on IMS
 */
typedef struct
{
    uint8_t smsOnIMS;
}sMSOnIMSInfo;

/**
 * \ingroup sms
 * 
 * This structure contains SMS on IMS TLV information.
 * @param IMSInfo
 *          - SMS on IMS
 *          - See @ref sMSOnIMSInfo for more information
 */
typedef struct
{
    sMSOnIMSInfo IMSInfo;
}sMSOnIMSTlv;

/**
 * \ingroup sms
 * 
 *  This structure contains information related call control result
 *
 *  @param  notificationType
 *          - Message mode
 *              0x00 - WMS_MO_CONTROL_DISALLOW
 *              0x01 - WMS_MO_CONTROL_ALLOW
 *              0x02 - WMS_MO_CONTROL_ALLOW_BUT_MODIFIED
 *
 *  @param  length
 *          - Number of sets of following elements
 *
 *  @param  data
 *          - Raw message data
 */
typedef struct
{
	uint32_t notificationType;
	uint8_t length;
	uint8_t data[256];
} sCallCtrlResultInfo;

/*
 * This structure contains call control result TLV Value.
 *
 * @param CallCtrlResult       - Refer to CallCtrlResultInfo
 */
typedef struct 
{
	sCallCtrlResultInfo CallCtrlResult;
}sCallCtrlResultTlv;

/**
 * \ingroup sms
 * 
 *  This structure contains information related to broadcast SMS RAT
 *
 *  @param  bcSmsRatInfo
 *          - broadcast SMS RAT information
 *              0x00 - GSM
 *              0x01 - WCDMA
 *              0x02 - LTE
 *              0x03 - CDMA
 *              0x04 - NG5G
 */
typedef struct
{
	uint32_t bcSmsRatInfo;
}sBroadcastSmsRatInfo;

/*
 * This structure contains broadcast SMS RAT information TLV Value.
 *
 * @param BroadcastSmsRat       - Refer to BroadcastSmsRatInfo
 */
typedef struct 
{
	sBroadcastSmsRatInfo BroadcastSmsRat;
}sBroadcastSmsRatTlv;

/**
 * \ingroup sms
 * 
 *  This structure contains information related to IMS SMS Verstat Status
 *
 *  @param  imsSmsVerstatStatusInfo
 *          - SMS Verstat Status information
 *              0x00 - MT_IMS_TN_VALIDATION_NONE
 *              0x01 - MT_IMS_TN_VALIDATION_PASS
 *              0x02 - MT_IMS_TN_VALIDATION_FAIL
 */
typedef struct
{
	uint32_t imsSmsVerstatStatusInfo;
}sImsSmsVerstatStatusInfo;

/*
 * This structure contains IMS SMS Verstat Status information TLV Value.
 *
 * @param ImsSmsVerstatStatus       - Refer to ImsSmsVerstatStatusInfo
 */
typedef struct 
{
	sImsSmsVerstatStatusInfo ImsSmsVerstatStatus;
}sImsSmsVerstatStatusTlv;

/**
 * \ingroup sms
 * 
 *  This structure contains information related broadcast SMS Warning Area Coordinate
 *
 *  @param  length
 *          - Number of sets of following elements
 *
 *  @param  data
 *          - Raw message data
 */
typedef struct
{
	uint16_t length;
	uint8_t data[256];
} sBroadcastSmsWarningAreaInfo;

/*
 * This structure contains broadcast SMS Warning Area Coordinate information TLV Value.
 *
 * @param BroadcastSmsWarningArea       - Refer to BroadcastSmsWarningAreaInfo
 */
typedef struct 
{
	sBroadcastSmsWarningAreaInfo BroadcastSmsWarningArea;
}sBroadcastSmsWarningAreaTlv;

/**
 * \ingroup sms
 * 
 * This structure contains unpack new SMS callback indication.
 * @param NewMMTlv
 *          - MT message
 *          - See @ref newMTMessageTlv for more information
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 * @param TRMessageTlv
 *          - Transfer Route MT Message
 *          - See @ref transferRouteMessageTlv for more information
 *          - Bit to check in ParamPresenceMask - <B>17</B>
 *
 * @param MMTlv
 *          - Message mode
 *          - See @ref messageModeTlv for more information
 *          - Bit to check in ParamPresenceMask - <B>18</B>
 *
 * @param ETWSTlv
 *          - ETWS Message
 *          - See @ref sMSEtwsMessageTlv for more information
 *          - Bit to check in ParamPresenceMask - <B>19</B>
 *
 * @param ETWSPLMNTlv
 *          - ETWS PLMN Information
 *          - See @ref eTWSPLMNInfoTlv for more information
 *          - Bit to check in ParamPresenceMask - <B>20</B>
 *
 * @param SMSCTlv
 *          - SMSC Address
 *          - See @ref sMSCAddressTlv for more information
 *          - Bit to check in ParamPresenceMask - <B>21</B>
 *
 * @param IMSTlv
 *          - SMS on IMS
 *          - See @ref sMSOnIMSTlv for more information
 *          - Bit to check in ParamPresenceMask - <B>22</B>
 *
 * @param CallCtrlResultTlv
 *          - call control result
 *          - See @ref sCallCtrlResultTlv for more information
 *          - Bit to check in ParamPresenceMask - <B>23</B>
 *
 * @param BroadcastSmsRatTlv
 *          - broadcast SMS RAT
 *          - See @ref sBroadcastSmsRatTlv for more information
 *          - Bit to check in ParamPresenceMask - <B>24</B>
 *
 * @param ImsSmsVerstatStatusTlv
 *          - IMS SMS Verstat Status
 *          - See @ref sImsSmsVerstatStatusTlv for more information
 *          - Bit to check in ParamPresenceMask - <B>25</B>
 *
 * @param BroadcastSmsWarningAreaTlv
 *          - broadcast SMS Warning Area Coordinate
 *          - See @ref sBroadcastSmsWarningAreaTlv for more information
 *          - Bit to check in ParamPresenceMask - <B>26</B>
 *
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct{
    newMTMessageTlv         NewMMTlv;
    transferRouteMessageTlv TRMessageTlv;
    messageModeTlv          MMTlv;
    sMSEtwsMessageTlv       ETWSTlv;
    eTWSPLMNInfoTlv         ETWSPLMNTlv;
    sMSCAddressTlv          SMSCTlv;
    sMSOnIMSTlv             IMSTlv;
	sCallCtrlResultTlv      CallCtrlResTlv;
	sBroadcastSmsRatTlv     SMSRATTlv;
	sImsSmsVerstatStatusTlv IMSSMSTlv;
	sBroadcastSmsWarningAreaTlv WarnAreaTlv;
	swi_uint256_t           ParamPresenceMask;
}unpack_sms_SetNewSMSCallback_ind_t;

/**
 * \ingroup sms
 * 
 * set new sms callback indication unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int unpack_sms_SetNewSMSCallback_ind(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_sms_SetNewSMSCallback_ind_t *pOutput
        );

/**
 * \ingroup sms
 * 
 * This structure contains Transfer route MT message information.
 * @param ackIndicator
 *          - Parameter to indicate if ACK must be sent by the control point
 *              0x00 - Send ACK
 *              0x01 - Do not send ACK
 *
 * @param transactionID
 *          - Transaction ID of the message
 *
 * @param format
 *          - Message format
 *              0x00 - CDMA
 *              0x02 - 0x05 - Reserved
 *              0x06 - GW_PP
 *              0x07 - GW_BC
 *
 * @param length
 *          - Length of the raw message. This length should not exceed the
 *            maximum WMS payload length of 256 bytes
 *
 * @param pData
 *          - pointer to Raw message data
 */
typedef struct
{
    uint8_t  ackIndicator;
    uint32_t transactionID;
    uint8_t  format;
    uint16_t length;
    uint8_t  *pData;
} transferRouteMessageExt;

/**
 * \ingroup sms
 * 
 * This structure contains ETWS information
 * @param notificationType
 *          - Message mode
 *              0x00 - Primary
 *              0x01 - Secondary GSM
 *              0x02 - Secondary UMTS
 *
 * @param length
 *          - Number of sets of following elements
 *
 * @param pData
 *          - Pointer to Raw message data
 */

typedef struct
{
    uint8_t notificationType;
    uint16_t length;
    uint8_t *pData;
} sMSEtwsMessageExt;

/**
 * \ingroup sms
 * 
 * This structure contains SMSC information
 * @param length
 *          - Number of sets of following element
 *
 * @param pData
 *          - Pointer to SMSC address
 */

typedef struct
{
    uint8_t length;
    uint8_t *pData;
} sMSCAddressExt;

/**
 * \ingroup sms
 * 
 *  This structure contains information related call control result
 *
 *  @param  notificationType
 *          - Message mode
 *              0x00 - WMS_MO_CONTROL_DISALLOW
 *              0x01 - WMS_MO_CONTROL_ALLOW
 *              0x02 - WMS_MO_CONTROL_ALLOW_BUT_MODIFIED
 *
 *  @param  length
 *          - Number of sets of following elements
 *
 *  @param  pData
 *          - Pointer to Raw message data
 */
typedef struct
{
	uint32_t notificationType;
	uint8_t length;
	uint8_t *pData;
} sCallCtrlResultExt;

/**
 * \ingroup sms
 * 
 *  This structure contains information related broadcast SMS Warning Area Coordinate
 *
 *  @param  length
 *          - Number of sets of following elements
 *
 *  @param  pData
 *          - Pointer to Raw message data
 */
typedef struct
{
	uint16_t length;
	uint8_t *pData;
} sBroadcastSmsWarningAreaExt;

/**
 * \ingroup sms
 * 
 * This structure contains unpack new SMS callback indication.
 * @param NewMMTlv
 *          - MT message
 *          - See @ref sMSMTMessageInfo for more information
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 * @param TRMessageTlv
 *          - Transfer Route MT Message
 *          - See @ref transferRouteMessageExt for more information
 *          - Bit to check in ParamPresenceMask - <B>17</B>
 *
 * @param MMTlv
 *          - Message mode
 *          - See @ref sMSMessageModeInfo for more information
 *          - Bit to check in ParamPresenceMask - <B>18</B>
 *
 * @param ETWSTlv
 *          - ETWS Message
 *          - See @ref sMSEtwsMessageExt for more information
 *          - Bit to check in ParamPresenceMask - <B>19</B>
 *
 * @param ETWSPLMNTlv
 *          - ETWS PLMN Information
 *          - See @ref sMSEtwsPlmnInfo for more information
 *          - Bit to check in ParamPresenceMask - <B>20</B>
 *
 * @param SMSCTlv
 *          - SMSC Address
 *          - See @ref sMSCAddressExt for more information
 *          - Bit to check in ParamPresenceMask - <B>21</B>
 *
 * @param IMSTlv
 *          - SMS on IMS
 *          - See @ref sMSOnIMSInfo for more information
 *          - Bit to check in ParamPresenceMask - <B>22</B>
 *
 * @param CallCtrlResultTlv
 *          - call control result
 *          - See @ref sCallCtrlResultExt for more information
 *          - Bit to check in ParamPresenceMask - <B>23</B>
 *
 * @param BroadcastSmsRatTlv
 *          - broadcast SMS RAT
 *          - See @ref sBroadcastSmsRatInfo for more information
 *          - Bit to check in ParamPresenceMask - <B>24</B>
 *
 * @param ImsSmsVerstatStatusTlv
 *          - IMS SMS Verstat Status
 *          - See @ref sImsSmsVerstatStatusInfo for more information
 *          - Bit to check in ParamPresenceMask - <B>25</B>
 *
 * @param BroadcastSmsWarningAreaTlv
 *          - broadcast SMS Warning Area Coordinate
 *          - See @ref sBroadcastSmsWarningAreaExt for more information
 *          - Bit to check in ParamPresenceMask - <B>26</B>
 *
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct{
    sMSMTMessageInfo        NewMMTlv;
    transferRouteMessageExt TRMessageTlv;
    sMSMessageModeInfo      MMTlv;
    sMSEtwsMessageExt       ETWSTlv;
    sMSEtwsPlmnInfo         ETWSPLMNTlv;
    sMSCAddressExt          SMSCTlv;
    sMSOnIMSInfo            IMSTlv;
	sCallCtrlResultExt      CallCtrlResTlv;
	sBroadcastSmsRatInfo     SMSRATTlv;
	sImsSmsVerstatStatusInfo IMSSMSTlv;
	sBroadcastSmsWarningAreaExt WarnAreaTlv;
	swi_uint256_t           ParamPresenceMask;
}unpack_sms_SetNewSMSCallbackExt_ind_t;

/**
 * \ingroup sms
 * 
 * set new sms callback indication unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int unpack_sms_SetNewSMSCallbackExt_ind(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_sms_SetNewSMSCallbackExt_ind_t *pOutput
        );

/**
 * \ingroup sms
 * 
 * This structure contains unpack SMS memory full callback indication.
 * @param storageType
 *          - SMS message storage type
 *              - 0 - UIM - Invalid in case of CDMA device that does not
 *                          require SIM
 *              - 1 - NV
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 * @param messageMode
 *          - 0x00 - CDMA, LTE (if network type is CDMA)
 *          - 0x01 - GW, LTE (if network type is UMTS)
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct{
    uint8_t storageType;
    uint8_t messageMode;
    swi_uint256_t  ParamPresenceMask;
}unpack_sms_SLQSWmsMemoryFullCallBack_ind_t;

/**
 * \ingroup sms
 * 
 * sms full callback indication unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int unpack_sms_SLQSWmsMemoryFullCallBack_ind(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_sms_SLQSWmsMemoryFullCallBack_ind_t *pOutput
        );

/**
 * \ingroup sms
 * 
 *  Structure contains Gets the SMS center address parameters.
 *
 *  @param  addressSize
 *          - The maximum number of characters (including NULL terminator) that
 *            the SMS center address array can contain.
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param  pSMSCAddress
 *          - The SMS center address represented as a NULL terminated string.
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param  typeSize
 *          - The maximum number of characters (including NULL terminator) that
 *            the SMS center address type array can contain.
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param  pSMSCType
 *          - The SMS center address type represented as a NULL terminated
 *            string.
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct{
    uint8_t addressSize;
    uint8_t *pSMSCAddress;
    uint8_t typeSize;
    uint8_t *pSMSCType;
    swi_uint256_t  ParamPresenceMask;
}unpack_sms_GetSMSCAddress_t;

/**
 * \ingroup sms
 * 
 * Gets the SMS center address pack.
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int pack_sms_GetSMSCAddress(
        pack_qmi_t  *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen
        );

/**
 * \ingroup sms
 * 
 * Gets the SMS center address unpack.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int unpack_sms_GetSMSCAddress(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_sms_GetSMSCAddress_t *pOutput
        );

/**
 * \ingroup sms
 * 
 *  Structure to Set the SMS center address.
 *
 *  @param  SMSCAddress
 *          - The SMS center address represented as a NULL terminated string
 *
 *  @param  SMSCType
 *          - The SMS center address type represented as a NULL terminated
 *          string (optional).
 *
 */
typedef struct{
    uint8_t  *pSMSCAddress;
    uint8_t  *pSMSCType;
} pack_sms_SetSMSCAddress_t;

/**
 * \ingroup sms
 * 
 * Set the SMS center address pack.
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param reqParam packed request
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_sms_SetSMSCAddress(
        pack_qmi_t  *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen,
        pack_sms_SetSMSCAddress_t *reqParam
        );

/**
 *  This structure contains unpack Set SMS Address parameter.
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
**/
typedef struct{
    swi_uint256_t  ParamPresenceMask;
} unpack_sms_SetSMSCAddress_t;

/**
 * \ingroup sms
 * 
 * Set the SMS center address unpack.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_sms_SetSMSCAddress(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_sms_SetSMSCAddress_t *pOutput
        );

/**
 * \ingroup sms
 * 
 *  Sutructure containing parameters to Save an SMS message to device memory
 *
 *  @param  storageType
 *          - SMS message storage type
 *              - 0 - UIM - Invalid in case of CDMA device that does not
 *                          require SIM
 *              - 1 - NV
 *
 *  @param  messageFormat
 *          - Message format
 *              - 0 - CDMA (IS-637B)
 *              - 1 - 5 (Reserved)
 *              - 6 - GSM/WCDMA PP
 *
 *  @param  messageSize
 *          - The length of the message contents in bytes
 *
 *  @param  pMessage
 *          - The message contents
 *
 *
 */
typedef struct{
    uint32_t storageType;
    uint32_t messageFormat;
    uint32_t messageSize;
    uint8_t  *pMessage;
} pack_sms_SaveSMS_t;

/**
 *  This structure contains unpack save SMS parameter.
 *  @param  pMessageIndex
 *          - The message index assigned by the device
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
**/
typedef struct{
    uint32_t *pMessageIndex;
    swi_uint256_t  ParamPresenceMask;
} unpack_sms_SaveSMS_t;

/**
 * \ingroup sms
 * 
 * Saves an SMS message to device memory pack.
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param reqParam packed request
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_sms_SaveSMS(
        pack_qmi_t  *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen,
        pack_sms_SaveSMS_t *reqParam
        );

/**
 * \ingroup sms
 * 
 * Saves an SMS message to device memory unpack.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_sms_SaveSMS(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_sms_SaveSMS_t *pOutput
        );

/**
 * \ingroup sms
 * 
 *  This structure contains BroadcastConfig parameters
 *
 *  @param  fromServiceId
 *          - Starting point of range of CBM message identifiers
 *
 *  @param  toServiceId
 *          - Ending point of range of CBM message identifiers
 *
 *  @param  selected
 *          - Range of CBM message identifiers indicated by
 *            from_service_id and to_service_id
 *               - 0x00 – Not selected
 *               - 0x01 – Selected
 *
 */
typedef struct
{
    uint16_t fromServiceId;
    uint16_t toServiceId;
    uint8_t  selected;
} sms_BroadcastConfig;

/**
 * \ingroup sms
 * 
 *  This structure contains the 3GPP Broadcast Configuration Information
 *  parameters
 *
 *  @param  activated_ind
 *          - Broadcast SMS
 *              - 0x00 - Deactivated
 *              - 0x01 - Activated
 *
 *  @param  num_instances
 *          - Number of sets (N) of parameters
 *            Following each set describes one entry in the broadcast
 *            configuration table.
 *              - fromServiceId
 *              - toServiceId
 *              - selected
 *
 *  @param  broadcastConfig
 *          - A BroadcastConfig structure array.
 *          - Further defined by the structure sms_BroadcastConfig
 *
 */
typedef struct {
    uint8_t             activated_ind;
    uint16_t            num_instances;
    sms_BroadcastConfig broadcastConfig[SMS_CONFIG_LEN];
} sms_qaQmi3GPPBroadcastCfgInfo;

/**
 * \ingroup sms
 * 
 *  This structure contains CDMABroadcastConfig parameters
 *
 *  @param  serviceCategory
 *          - Service category
 *
 *  @param  language
 *          - Language
 *
 *  @param  selected
 *          - Specified service_category and language
 *               - 0x00 – Not selected
 *               - 0x01 – Selected
 *
 */
typedef struct{
    uint16_t serviceCategory;
    uint16_t language;
    uint8_t  selected;
} sms_CDMABroadcastConfig;

/**
 * \ingroup sms
 * 
 *  This structure contains the 3GPP2 Broadcast Configuration Information
 *  parameters
 *
 *  @param  activated_ind
 *          - Broadcast SMS
 *              - 0x00 - Deactivated
 *              - 0x01 - Activated
 *
 *  @param  num_instances
 *          - Number of sets (N) of parameters
 *            Following each set describes one entry in the broadcast
 *            configuration table.
 *              - serviceCategory
 *              - language
 *              - selected
 *
 *  @param  broadcastConfig
 *          - A CDMABroadcastConfig structure array.
 *          - Further defined by the structure sms_CDMABroadcastConfig
 *
 */
typedef struct{
    uint8_t                 activated_ind;
    uint16_t                num_instances;
    sms_CDMABroadcastConfig CDMABroadcastConfig[SMS_CONFIG_LEN];
} sms_qaQmi3GPP2BroadcastCfgInfo;

/**
 * \ingroup sms
 * 
 *  Structure contain parameters that Provides Information about the SMS BroadcastConfiguration
 *
 * @param  pBroadcastConfig
 *         - The data for 3GPP Broadcast Information(Optional).
 *         - Bit to check in ParamPresenceMask - <B>16</B>
 *
 * @param  pCDMABroadcastConfig
 *         - The data for 3GPP2 Broadcast Information(Optional).
 *         - Bit to check in ParamPresenceMask - <B>17</B>
 *
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct{
    sms_qaQmi3GPPBroadcastCfgInfo  *pBroadcastConfig;
    sms_qaQmi3GPP2BroadcastCfgInfo *pCDMABroadcastConfig;
    swi_uint256_t  ParamPresenceMask;
} unpack_sms_SLQSGetSmsBroadcastConfig_t;

/**
 * \ingroup sms
 * 
 * This structure contains get SMS boardcast configure parameter.
 * @param  mode
 *         - Mode
 *          - 0x00 - CDMA, LTE (if network type is CDMA)
 *          - 0x01 - GW, LTE (if network type is UMTS)
*/
typedef struct{
    uint8_t mode;
} pack_sms_SLQSGetSmsBroadcastConfig_t;

/**
 * \ingroup sms
 * 
 * Provides Information about the SMS BroadcastConfiguration pack.
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param reqParam packed request
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int pack_sms_SLQSGetSmsBroadcastConfig(
        pack_qmi_t  *pCtx,
        uint8_t     *pReqBuf,
        uint16_t    *pLen,
        pack_sms_SLQSGetSmsBroadcastConfig_t *reqParam
        );

/**
 * \ingroup sms
 * 
 * Provides Information about the SMS BroadcastConfiguration unpack.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int unpack_sms_SLQSGetSmsBroadcastConfig(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_sms_SLQSGetSmsBroadcastConfig_t *pOutput
        );

/**
 * \ingroup sms
 * 
 * Structure containing parameters that provides the information about the SMS BroadcastConfiguration
 *
 * @param  mode
 *         - Mode
 *          - 0x00 - CDMA, LTE (if network type is CDMA)
 *          - 0x01 - GW, LTE (if network type is UMTS)
 *
 * @param  pBroadcastConfig
 *         - The data for 3GPP Broadcast Information(Optional).
 *
 * @param  pCDMABroadcastConfig
 *         - The data for 3GPP2 Broadcast Information(Optional).
 *
 */
typedef struct{
    uint8_t                        mode;
    sms_qaQmi3GPPBroadcastCfgInfo  *pBroadcastConfig;
    sms_qaQmi3GPP2BroadcastCfgInfo *pCDMABroadcastConfig;
} pack_sms_SLQSSetSmsBroadcastConfig_t;

/**
 * \ingroup sms
 * 
 * Sets the information about the SMS BroadcastConfiguration pack.
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param reqParam packed request
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_sms_SLQSSetSmsBroadcastConfig(
        pack_qmi_t  *pCtx,
        uint8_t     *pReqBuf,
        uint16_t    *pLen,
        pack_sms_SLQSSetSmsBroadcastConfig_t *reqParam
        );

/**
 * \ingroup sms
 * 
 * This structure contains unpack SLQSSetSmsBroadcastConfig parameters.
 *
 * @param  ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct{
    swi_uint256_t  ParamPresenceMask;
} unpack_sms_SLQSSetSmsBroadcastConfig_t;

/**
 * \ingroup sms
 * 
 * Sets the information about the SMS BroadcastConfiguration unpack.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_sms_SLQSSetSmsBroadcastConfig(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_sms_SLQSSetSmsBroadcastConfig_t *pOutput
        );

/**
 * \ingroup sms
 * 
 *  Structure contain parameters that Enables or disables the reception of broadcast SMS messages.
 *
 *  @param  Mode
 *          - Mode
 *          - 0x00 - CDMA, LTE (if network type is CDMA)
 *          - 0x01 - GW, LTE (if network type is UMTS)
 *
 *  @param  broadcastActivate
 *          - 0x00 - Disable broadcast
 *          - 0x01 - Activate broadcast
 *
 */
typedef struct{
    uint8_t mode;
    uint8_t broadcastActivate;
} pack_sms_SLQSSetSmsBroadcastActivation_t;

/**
 * \ingroup sms
 * 
 * Enables or disables the reception of broadcast SMS messages pack.
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param reqParam packed request
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_sms_SLQSSetSmsBroadcastActivation(
        pack_qmi_t  *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen,
        pack_sms_SLQSSetSmsBroadcastActivation_t *reqParam
        );

/**
 *   This structure contains unpack SLQSSetSmsBroadcastActivation parameter.
 *   @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
**/

typedef struct{
    swi_uint256_t  ParamPresenceMask;
} unpack_sms_SLQSSetSmsBroadcastActivation_t;

/**
 * \ingroup sms
 * 
 * Enables or disables the reception of broadcast SMS messages unpack.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_sms_SLQSSetSmsBroadcastActivation(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_sms_SLQSSetSmsBroadcastActivation_t *pOutput
        );

/**
 * \ingroup sms
 * 
 *  This structure contains Transport Layer Information
 *
 *  @param  TransType
 *          - Transport Type
 *              - 0x00 - IMS
 *
 *  @param  TransCap
 *          - Transport Capability
 *          - Values:
 *              - 0x00 - CDMA
 *              - 0x01 - GW
 */
typedef struct
{
    uint8_t TransType;
    uint8_t TransCap;
} sms_transLayerInfo;

/**
 * \ingroup sms
 * 
 *  This structure contains Get Transport Layer Info Response parameters
 *
 *  @param  pRegInd -
 *          - Optional parameter indicating if transport layer is registered
 *          - Values:
 *              - 0x00 - Transport layer is not registered
 *              - 0x01 - Transport layer is registered
 *          - returns a default value 0xFF
 *            if no response is received from the device.
 *
 *  @param  pTransLayerInfo
 *          - Pointer to structure of sms_transLayerInfo.
 *              - Optional parameter
 *              - See @ref sms_transLayerInfo for more information
 *          -  returns a default value 0xFF
 *            for parameter values if no response is received from the device.
 *
 */
typedef struct
{
    uint8_t            *pRegInd;
    sms_transLayerInfo *pTransLayerInfo;
} sms_getTransLayerInfo;

/**
 * \ingroup sms
 * 
 *  Structure contain parameters that gives information about the transport layer.
 *
 *  @param  pGetTransLayerInfo
 *          - Pointer to structure of getTransLayerInfo
 *              - See @ref sms_getTransLayerInfo for more information
 *              - pGetTransLayerInfo->pRegInd
 *                  - Bit to check in ParamPresenceMask - <B>16</B>
 *              - pGetTransLayerInfo->pTransLayerInfo
 *                  - Bit to check in ParamPresenceMask - <B>17</B>
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 *
 */
typedef struct
{
    sms_getTransLayerInfo  *pGetTransLayerInfo;
    swi_uint256_t  ParamPresenceMask;
} unpack_sms_SLQSGetTransLayerInfo_t;

/**
 * \ingroup sms
 * 
 * Gets information about the transport layer pack.
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int pack_sms_SLQSGetTransLayerInfo(
        pack_qmi_t  *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen
        );

/**
 * \ingroup sms
 * 
 * Gets information about the transport layer unpack.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int unpack_sms_SLQSGetTransLayerInfo(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_sms_SLQSGetTransLayerInfo_t *pOutput
        );

/**
 * \ingroup sms
 * 
 *  This structure contains transport network registration info
 *  parameter
 *
 *  @param  pRegStatus -
 *          - Optional parameter indicating transport layer network
 *            registration status
 *          - Values:
 *              - 0x00 - No service
 *              - 0x01 - In progress
 *              - 0x02 - Failed
 *              - 0x03 - Limited Service
 *              - 0x04 - Full Service
 *          - returns a default value 0xFF
 *            if no response is received from the device.

 */
typedef struct
{
    uint8_t *pRegStatus;
} sms_getTransNWRegInfo;

/**
 * \ingroup sms
 * 
 *  Structure containing parameters that provides transport layer network registration info.
 *
 *  @param  pGetTransNWRegInfo
 *          - Pointer to structure of getTransNWRegInfo
 *              - See @ref sms_getTransNWRegInfo for more information
 *              - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct
{
    sms_getTransNWRegInfo *pGetTransNWRegInfo;
    swi_uint256_t  ParamPresenceMask;
} unpack_sms_SLQSGetTransNWRegInfo_t;

 /**
 * \ingroup sms
 * 
  * Gets transport layer network registration info pack.
  * @param[in,out] pCtx qmi request context
  * @param[out] pReqBuf qmi request buffer
  * @param[out] pLen qmi request length
  *
  * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
  *
  * @sa     See qmerrno.h for eQCWWAN_xxx error values
  *
  */
int pack_sms_SLQSGetTransNWRegInfo(
        pack_qmi_t  *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen
        );

 /**
 * \ingroup sms
 * 
  * Gets transport layer network registration info unpack.
  * @param[in] pResp qmi response
  * @param[in] respLen qmi response length
  * @param[out] pOutput unpacked response
  *
  * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
  *
  * @sa     See qmerrno.h for eQCWWAN_xxx error values
  *
  */
int unpack_sms_SLQSGetTransNWRegInfo(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_sms_SLQSGetTransNWRegInfo_t *pOutput
        );

/**
 * \ingroup sms
 * 
 *  This structure contains Get Indication Register Response parameters
 *
 *  @param  pRegTransLayerInfoEvt -
 *          - Optional parameter indicating registration status of
 *            transport layer information events
 *          - Values:
 *              - 0x00 - Disabled
 *              - 0x01 - Enabled
 *
 *  @param  pRegTransNWRegInfoEvt -
 *          - Optional parameter indicating registration status of
 *            transport network registration information events
 *          - Values:
 *              - 0x00 - Disabled
 *              - 0x01 - Enabled
 *
 *  @param  pRegCallStatInfoEvt -
 *          - Optional parameter indicating registration status of call
 *            status information events
 *          - Values:
 *              - 0x00 - Disabled
 *              - 0x01 - Enabled
 *
 */
typedef struct
{
   uint8_t *pRegTransLayerInfoEvt;
   uint8_t *pRegTransNWRegInfoEvt;
   uint8_t *pRegCallStatInfoEvt;
} sms_getIndicationReg;

/**
 * \ingroup sms
 * 
 *  Structure containing Parameters that provides registration state of different WMS indications.
 *
 *  @param  pGetIndicationRegInfo
 *          - Pointer to structure of getIndicationReg
 *              - See @ref sms_getIndicationReg for more information
 *              - pRegTransLayerInfoEvt
 *                  - Bit to check in ParamPresenceMask - <B>16</B>
 *              - pRegTransNWRegInfoEvt
 *                  - Bit to check in ParamPresenceMask - <B>17</B>
 *              - pRegCallStatInfoEvt
 *                  - Bit to check in ParamPresenceMask - <B>18</B>
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct
{
   sms_getIndicationReg *pGetIndicationRegInfo;
   swi_uint256_t  ParamPresenceMask;
} unpack_sms_SLQSGetIndicationRegister_t;

/**
 * \ingroup sms
 * 
 * Gets registration state of different WMS indications pack.
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int pack_sms_SLQSGetIndicationRegister(
       pack_qmi_t  *pCtx,
       uint8_t *pReqBuf,
       uint16_t *pLen
       );

/**
 * \ingroup sms
 * 
 * Gets registration state of different WMS indications unpack.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int unpack_sms_SLQSGetIndicationRegister(
       uint8_t *pResp,
       uint16_t respLen,
       unpack_sms_SLQSGetIndicationRegister_t *pOutput
       );


/**
 * \ingroup sms
 * 
*  This structure contains Indication Register request parameters
*
*  @param  pRegTransLayerInfoEvt -
*          - Optional parameter indicating registration status of
*            transport layer information events
*          - Values:
*              - 0x00 - Disabled
*              - 0x01 - Enabled
*              - NULL - No change - specifying NULL indicates that the device
*                will continue to use the existing setting (disable/enable)
*                which has been previously set for the device
*
*  @param  pRegTransNWRegInfoEvt -
*          - Optional parameter indicating registration status of
*            transport network registration information events
*          - Values:
*              - 0x00 - Disabled
*              - 0x01 - Enabled
*              - NULL - No change - specifying NULL indicates that
*                the device will continue to use the existing setting
*                (disable/enable) which has been previously set for the device
*
*  @param  pRegCallStatInfoEvt -
*          - Optional parameter indicating registration status of call
*            status information events
*          - Values:
*              - 0x00 - Disabled
*              - 0x01 - Enabled
*              - NULL - No change - specifying NULL indicates that the device
*                will continue to use the existing setting (disable/enable)
*                which has been previously set for the device
*
*/
typedef struct
{
   uint8_t *pRegTransLayerInfoEvt;
   uint8_t *pRegTransNWRegInfoEvt;
   uint8_t *pRegCallStatInfoEvt;
} sms_setIndicationReg;

/**
 * \ingroup sms
 * 
*  Structure contain Parameter that sets the registration state of different WMS indications.
*
*  @param  pSetIndicationReg
*          - Pointer to structure of indicationRegReqParams
*              - See @ref sms_setIndicationReg for more information
*
*/
typedef struct
{
   sms_setIndicationReg *pSetIndicationRegReq;
} pack_sms_SLQSSetIndicationRegister_t;

/**
 * \ingroup sms
 * 
 * Sets the registration state of different WMS indications pack.
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param reqParam packed request
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_sms_SLQSSetIndicationRegister(
       pack_qmi_t  *pCtx,
       uint8_t *pReqBuf,
       uint16_t *pLen,
       pack_sms_SLQSSetIndicationRegister_t *reqParam
       );

/**
 * \ingroup sms
 * 
 *   This structure contains unpack SLQSSetIndicationRegister parameter.
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
*/
typedef struct
{
   swi_uint256_t  ParamPresenceMask;
} unpack_sms_SLQSSetIndicationRegister_t;

/**
 * \ingroup sms
 * 
 * Sets the registration state of different WMS indications unpack.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_sms_SLQSSetIndicationRegister(
       uint8_t *pResp,
       uint16_t respLen,
       unpack_sms_SLQSSetIndicationRegister_t *pOutput
       );

/**
 * \ingroup sms
 * 
 *  This structure contains SMS route entry details
 *
 *  @param  messageType -
 *          - Message type matching this route
 *          - Values:
 *              - 0x00 - MESSAGE_TYPE_POINT_TO_POINT
 *
 *  @param  messageClass -
 *          - Message Class
 *          - Values:
 *              - 0x00 - MESSAGE_CLASS_0
 *              - 0x01 - MESSAGE_CLASS_1
 *              - 0x02 - MESSAGE_CLASS_2
 *              - 0x03 - MESSAGE_CLASS_3
 *              - 0x04 - MESSAGE_CLASS_NONE
 *              - 0x05 - MESSAGE_CLASS_CDMA
 *
 *  @param  routeStorage -
 *          - If the receiptAction is store where to store the message
 *          - Values:
 *              - 0x00 - STORAGE_TYPE_UIM
 *              - 0x01 - STORAGE_TYPE_NV
 *              - 0xFF - STORAGE_TYPE_NONE
 *
 *  @param  receiptAction -
 *          - Action to be taken on receipt of a message matching the specified
 *            type and class for this route
 *          - Values:
 *              - 0x00 - DISCARD (discarded without notification)
 *              - 0x01 - STORE AND NOTIFY (stored and notified to the
 *                registered clients)
 *              - 0x02 - TRANSFER ONLY (transferred to the client, client
 *                expected to send the ACK)
 *              - 0x03 - TRANSFER AND ACK (transferred to the client, device
 *                expected to send the ACK)
 */
typedef struct
{
   uint8_t messageType;
   uint8_t messageClass;
   uint8_t routeStorage;
   uint8_t receiptAction;
} sms_routeEntry;

/**
 * \ingroup sms
 * 
 *  This structure contains SMS route request parameters
 *
 *  @param  numOfRoutes -
 *          - Number of sets of the following element
 *
 *  @param  routeList -
 *          - Array containing the set of @ref sms_routeEntry
 *
 *  @param  pTransferStatusReport -
 *          - 0x01 - Status report are transferred to the client (optional)
 */
typedef struct
{
   uint16_t       numOfRoutes;
   sms_routeEntry routeList[SMS_MAX_SMS_ROUTES];
   uint8_t        *pTransferStatusReport;
} sms_setRoutesReq;

/**
 * \ingroup sms
 * 
 *  Structure contain parameter that Sets the action performed on SMS message receipt for specified
 *  message routes. It also specifies the action performed on SMS receipt of
 *  status reports.
 *
 *  @param  pSetRoutesReq
 *          - Pointer to structure of smsSetRoutesReq
 *              - See @ref sms_setRoutesReq for more information
 *
 */
typedef struct
{
   sms_setRoutesReq *pSetRoutesReq;
} pack_sms_SLQSSmsSetRoutes_t;

/**
 * \ingroup sms
 * 
* Sets the action performed on SMS message receipt for specified
*  message routes. It also specifies the action performed on SMS receipt of
*  status reports pack.
* @param[in,out] pCtx qmi request context
* @param[out] pReqBuf qmi request buffer
* @param[out] pLen qmi request length
* @param reqParam packed request
*
* @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
*
* @sa     See qmerrno.h for eQCWWAN_xxx error values
*/
int pack_sms_SLQSSmsSetRoutes(
      pack_qmi_t  *pCtx,
      uint8_t *pReqBuf,
      uint16_t *pLen,
      pack_sms_SLQSSmsSetRoutes_t *reqParam
      );

/**
 *   This structure contains unpack SLQSSmsSetRoutes parameter.
 *   @param ParamPresenceMask
 *      - bitmask representation to indicate valid parameters.
 * 
**/
typedef struct 
{
    swi_uint256_t  ParamPresenceMask;
} unpack_sms_SLQSSmsSetRoutes_t;
/**
 * \ingroup sms
 * 
* Sets the action performed on SMS message receipt for specified
*  message routes. It also specifies the action performed on SMS receipt of
*  status reports unpack.
* @param[in] pResp qmi response
* @param[in] respLen qmi response length
* @param[out] pOutput unpacked response
* @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
*
* @sa     See qmerrno.h for eQCWWAN_xxx error values
*/
int unpack_sms_SLQSSmsSetRoutes(
      uint8_t *pResp,
      uint16_t respLen,
      unpack_sms_SLQSSmsSetRoutes_t *pOutput
      );

/**
 * \ingroup sms
 * 
* Sets the action performed on SMS message receipt for specified
*  message routes. It also specifies the action performed on SMS receipt of
*  status reports pack.
* @param[in,out] pCtx qmi request context
* @param[out] pReqBuf qmi request buffer
* @param[out] pLen qmi request length
*
* @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
*
* @sa     See qmerrno.h for eQCWWAN_xxx error values
*/
int pack_sms_SLQSSmsGetRoutes(
      pack_qmi_t  *pCtx,
      uint8_t *pReqBuf,
      uint16_t *pLen);

/**
 *   This structure contains unpack SLQSSmsGetRoutes parameter.
 *
 *  @param  numOfRoutes -
 *          - Number of sets of the following element
 *
 *  @param  routeList -
 *          - Array containing the set of @ref sms_routeEntry
 *
 *  @param  pTransferStatusReport -
 *          - 0x01 - Status report are transferred to the client (optional)
**/
typedef struct 
{
   uint16_t       numOfRoutes;
   sms_routeEntry routeList[SMS_MAX_SMS_ROUTES];
   uint8_t        *pTransferStatusReport;   
   swi_uint256_t  ParamPresenceMask;
} unpack_sms_SLQSSmsGetRoutes_t;

/**
 * \ingroup sms
 * 
* Sets the action performed on SMS message receipt for specified
*  message routes. It also specifies the action performed on SMS receipt of
*  status reports unpack.
* @param[in] pResp qmi response
* @param[in] respLen qmi response length
* @param[out] pOutput unpacked response
* @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
*
* @sa     See qmerrno.h for eQCWWAN_xxx error values
*/
int unpack_sms_SLQSSmsGetRoutes(
      uint8_t *pResp,
      uint16_t respLen,
      unpack_sms_SLQSSmsGetRoutes_t *pOutput
      );

/**
 * \ingroup sms
 * 
 *  This structure contains get message protocol response parameters
 *
 *  @param  msgProtocol -
 *          - Message Protocol
 *          - Values:
 *              - 0x00 - MESSAGE_PROTOCOL_CDMA
 *              - 0x01 - MESSAGE_PROTOCOL_WCDMA
 */
typedef struct
{
    uint8_t msgProtocol;
} sms_msgProtocolResp;

/**
 * \ingroup sms
 * 
 *  Structure contain Parameters that get the message protocol currently in use for the WMS client.
 *
 *  @param  pMessageProtocol
 *          - Pointer to smsMsgprotocolResp
 *              - See @ref sms_msgProtocolResp for more information
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct
{
    sms_msgProtocolResp *pMessageProtocol;
    swi_uint256_t  ParamPresenceMask;
} unpack_sms_SLQSSmsGetMessageProtocol_t;

/**
 * \ingroup sms
 * 
  * Gets the message protocol currently in use for the WMS client pack.
  * @param[in,out] pCtx qmi request context
  * @param[out] pReqBuf qmi request buffer
  * @param[out] pLen qmi request length
  *
  * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
  *
  * @sa     See qmerrno.h for eQCWWAN_xxx error values
  *
  */
int pack_sms_SLQSSmsGetMessageProtocol(
        pack_qmi_t  *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen
        );

 /**
 * \ingroup sms
 * 
  * Gets the message protocol currently in use for the WMS client unpack.
  * @param[in] pResp qmi response
  * @param[in] respLen qmi response length
  * @param[out] pOutput unpacked response
  *
  * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
  *
  * @sa     See qmerrno.h for eQCWWAN_xxx error values
  *
  */
int unpack_sms_SLQSSmsGetMessageProtocol(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_sms_SLQSSmsGetMessageProtocol_t *pOutput
        );

/**
 * \ingroup sms
 * 
 *  This structure contains get store max size request parameters
 *
 *  @param  storageType
 *          - SMS message storage type
 *              - 0 - UIM - Invalid in case of CDMA device that does not
 *                          require SIM
 *              - 1 - NV
 *
 *  @param  pMessageMode(optional parameter)
 *          - 0x00 - CDMA, LTE (if network type is CDMA)
 *          - 0x01 - GW, LTE (if network type is UMTS)
 *
 *  @note   The Message Mode TLV must be included if the device is capable of
 *          supporting more than one protocol
 */
typedef struct
{
    uint8_t storageType;
    uint8_t *pMessageMode;
} sms_maxStorageSizeReq;


/**
 * \ingroup sms
 * 
 *  This structure contains get store max size response parameters
 *
 *  @param  maxStorageSize -
 *          - Memory Store Size
 *
 *  @param  freeSlots -
 *          - Optional parameter indicating how much Memory is available
 *          -  returns a default value 0xFFFFFFFF for
 *             parameter values if no response is received from
 *            the device.
 */
typedef struct
{
    uint32_t maxStorageSize;
    uint32_t freeSlots;
} sms_maxStorageSizeResp;

/**
 * \ingroup sms
 * 
 *  This structure contains get maximum storage size.
 *  @param  pMaxStorageSizeReq
 *          - Request parameters for SmsSLQSGetMaxStorageSize
 *              - See @ref sms_maxStorageSizeReq for more information
 */
typedef struct
{
    sms_maxStorageSizeReq *pMaxStorageSizeReq;
} pack_sms_SLQSSmsGetMaxStorageSize_t;

/**
 * \ingroup sms
 * 
 *  Structure contain parameters that provides the maximum number of messages that can be stored in the
 *  specified memory storage. Also it provides the number of slots currently
 *  available
 *
 *  @param  pMaxStorageSizeResp
 *          - Response parameters for SmsSLQSGetMaxStorageSize
 *              - See @ref sms_maxStorageSizeResp for more information
 *          - pMaxStorageSizeResp->maxStorageSize
 *              - Bit to check in ParamPresenceMask - <B>1</B>
 *          - pMaxStorageSizeResp->freeSlots
 *              - Bit to check in ParamPresenceMask - <B>16</B>
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct
{
    sms_maxStorageSizeResp *pMaxStorageSizeResp;
    swi_uint256_t  ParamPresenceMask;
} unpack_sms_SLQSSmsGetMaxStorageSize_t;

/**
 * \ingroup sms
 * 
 * Get the maximum number of messages that can be stored in the
 * specified memory storage. Also it provides the number of slots currently
 * available pack.
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param reqParam packed request
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int pack_sms_SLQSSmsGetMaxStorageSize(
        pack_qmi_t  *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen,
        pack_sms_SLQSSmsGetMaxStorageSize_t *reqParam
        );

/**
 * \ingroup sms
 * 
 * Get the maximum number of messages that can be stored in the
 * specified memory storage. Also it provides the number of slots currently
 * available unpack.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int unpack_sms_SLQSSmsGetMaxStorageSize(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_sms_SLQSSmsGetMaxStorageSize_t *pOutput
        );

/**
 * \ingroup sms
 * 
 *  This structure contains message waiting information per instance
 *
 *  @param  msgType
 *          - Message type
 *              - 0x00 - MWI_MESSAGE_TYPE_VOICMAIL - Voicemail
 *              - 0x01 - MWI_MESSAGE_TYPE_FAX - Fax
 *              - 0X02 - MWI_MESSAGE_TYPE_EMAIL - Email
 *              - 0x03 - MWI_MESSAGE_TYPE_OTHER - Other
 *              - 0x04 - MWI_MESSAGE_TYPE_VIDEOMAIL - Videomail
 *
 *  @param  activeInd
 *          - Indicates whether the indication is active
 *              - 0x00 - Inactive
 *              - 0x01 - Active
 *
 *  @param  msgCount
 *          - Number of messages
 */
typedef struct
{
    uint8_t msgType;
    uint8_t activeInd;
    uint8_t msgCount;
} sms_messageWaitingInfoContent;

/**
 * \ingroup sms
 * 
 *  This structure contains Get Message Waiting Info Response parameters
 *
 *  @param  numInstances
 *          - Number of sets of the elements in structure sms_messageWaitingInfoContent
 *
 *  @param  pMsgWaitInfo
 *          - Pointer to structure of sms_messageWaitingInfoContent.
 *              - See @ref sms_messageWaitingInfoContent for more information.
 *
 */
typedef struct
{
    uint8_t                       numInstances;
    sms_messageWaitingInfoContent msgWaitInfo[SMS_NUM_OF_SET];
} sms_getMsgWaitingInfo;

/**
 * \ingroup sms
 * 
 *  Structure contain Parameter that provide information about the message waiting information.
 *
 *  @param  pGetMsgWaitingInfoResp
 *          - Pointer to structure of getMsgWaitingInfoResp
 *              - See @ref sms_getMsgWaitingInfo for more information
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct
{
    sms_getMsgWaitingInfo  *pGetMsgWaitingInfoResp;
    swi_uint256_t  ParamPresenceMask;
} unpack_sms_SLQSGetMessageWaiting_t;

/**
 * \ingroup sms
 * 
  * Gets the message waiting information pack.
  * @param[in,out] pCtx qmi request context
  * @param[out] pReqBuf qmi request buffer
  * @param[out] pLen qmi request length
  *
  * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
  *
  * @sa     See qmerrno.h for eQCWWAN_xxx error values
  *
  */
int pack_sms_SLQSGetMessageWaiting(
        pack_qmi_t  *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen
        );

 /**
 * \ingroup sms
 * 
  * Gets the message waiting information unpack.
  * @param[in] pResp qmi response
  * @param[in] respLen qmi response length
  * @param[out] pOutput unpacked response
  *
  * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
  *
  * @sa     See qmerrno.h for eQCWWAN_xxx error values
  *
  */
int unpack_sms_SLQSGetMessageWaiting(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_sms_SLQSGetMessageWaiting_t *pOutput
        );

/**
 * \ingroup sms
 * 
 *  This structure contains SMS parameters
 *
 *  @param  messageFormat
 *          - Message format
 *          - Values:
 *              - 0 - CDMA (IS-637B)
 *              - 1 - 5 (Reserved)
 *              - 6 - GSM/WCDMA PP
 *
 *  @param  messageSize
 *          - The length of the message contents in bytes
 *
 *  @param  pMessage
 *          - The message contents
 *
 *  @param  pForceOnDC
 *          - Force the message to be sent on the CDMA dedicated channel.
 *          - Values:
 *              - 0x00 - Do not care about the channel on which the message is sent
 *              - 0x01 - Request to send the message over the dedicated channel
 *
 *  @param  pServiceOption
 *          - Service option:
 *          - Values:
 *              - 0x00 - SO_AUTO - AUTO (choose the best service option)
 *              - 0x06 - SO_6 - Service option 6
 *              - 0x0E - SO_14 - Service option 14
 *
 *  @param  pFollowOnDC
 *          - Flag to request not to disconnect the CDMA dedicated channel
 *            after the send operation is complete.
 *          - This TLV can be included if more messages are expected to follow.
 *          - Values:
 *              - 0x01 - FOLLOW_ON_DC_ON - On (don't disconnect after send operation)
 *                Any value other than 0x01 is treated as an absence of this TLV.
 *
 *  @param  pLinktimer
 *          - Keeps the GW SMS link open for the specified number of seconds;
 *            can be enabled if more messages are expected to follow
 *
 *  @param  pSmsOnIms
 *          - Indicates whether the message is to be sent on IMS.
 *          - Values:
 *              - 0x00 - Message is not to be sent on IMS
 *              - 0x01 - Message is to be sent on IMS
 *              - 0x02 to 0xFF - Reserved
 *
 *  @param  pRetryMessage
 *          - Indicates this message is a retry message.
 *          - Values:
 *              - 0x01 - WMS_MESSAGE_IS_A_RETRY - Message is a retry message
 *              Note: Any value other than 0x01 in this field is treated
 *              as an absence of this TLV.
 *
 *
 *  @param  pRetryMessageId
 *          - Message ID to be used in the retry message.
 *          - The message ID specified here is used instead of the messsage ID
 *            encoded in the raw message.
 *
 *  @param  pUserData
 *          - Enables the control point to associate the request with the
 *            corresponding indication.
 *          - The control point might send numerous requests.
 *          - This TLV will help the control point to identify the request
 *            for which the received indication belongs.
 */
typedef struct
{
    uint32_t messageFormat;
    uint32_t messageSize;
    uint8_t  *pMessage;
    uint8_t  *pForceOnDC;
    uint8_t  *pServiceOption;
    uint8_t  *pFollowOnDC;
    uint8_t  *pLinktimer;
    uint8_t  *pSmsOnIms;
    uint8_t  *pRetryMessage;
    uint32_t *pRetryMessageId;
    uint32_t *pUserData;
} sms_sendAsyncsmsParams;

/**
 * \ingroup sms
 * 
 *  Structure contain Parameter to Send an SMS message for immediate over-the-air transmission
 *
 *  @param  pSendSmsParams
 *          - structure containing the SMS parameters. Refer sms_sendasyncsmsparams
 *
 */
typedef struct
{
    sms_sendAsyncsmsParams *pSendSmsParams;
} pack_sms_SLQSSendAsyncSMS_t;

/**
 * \ingroup sms
 * 
 * Sends an SMS message for immediate over-the-air transmission pack.
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param reqParam packed request
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_sms_SLQSSendAsyncSMS(
       pack_qmi_t  *pCtx,
       uint8_t *pReqBuf,
       uint16_t *pLen,
       pack_sms_SLQSSendAsyncSMS_t *reqParam
       );

/**
 *   This structure contains unpack SLQSSendAsyncSMS parameter.
 *   @param ParamPresenceMask
 *      - bitmask representation to indicate valid parameters.
**/
typedef struct
{
    swi_uint256_t  ParamPresenceMask;
} unpack_sms_SLQSSendAsyncSMS_t;

/**
 * \ingroup sms
 * 
 * Sends an SMS message for immediate over-the-air transmission unpack.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_sms_SLQSSendAsyncSMS(
       uint8_t *pResp,
       uint16_t respLen,
       unpack_sms_SLQSSendAsyncSMS_t *pOutput
       );

/**
 * \ingroup sms
 * 
 *  Structure contain Parameter to set the SMS Storage on the device
 *
 * @param  smsStorage
 *         - SMS Storage
 *          - 0x01 - device’s permanent memory
 *          - 0x02 - UICC
 *
 */
typedef struct
{
    uint8_t smsStorage;
} pack_sms_SLQSSetSmsStorage_t;

/**
 * \ingroup sms
 * 
 * Sets the SMS Storage on the device pack.
 * This command is deprecated. Please use pack_sms_SLQSSwiSetSmsStorage
 * 
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param reqParam packed request
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_sms_SLQSSetSmsStorage(
       pack_qmi_t  *pCtx,
       uint8_t *pReqBuf,
       uint16_t *pLen,
       pack_sms_SLQSSetSmsStorage_t *reqParam
       );

/**
 * \ingroup sms
 * 
 * Sets the SMS Storage on the device pack.
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param reqParam packed request
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_sms_SLQSSwiSetSmsStorage(
       pack_qmi_t  *pCtx,
       uint8_t *pReqBuf,
       uint16_t *pLen,
       pack_sms_SLQSSetSmsStorage_t *reqParam
       );

/**
 *   This structure contains unpack SLQSSetSmsStorage parameter.
 *   @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
**/
typedef struct
{
    swi_uint256_t  ParamPresenceMask;
} unpack_sms_SLQSSetSmsStorage_t;

/**
 * \ingroup sms
 * 
 * Sets the SMS Storage on the device unpack.
 * This command is deprecated. Please use unpack_sms_SLQSSwiSetSmsStorage
 * 
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_sms_SLQSSetSmsStorage(
       uint8_t *pResp,
       uint16_t respLen,
       unpack_sms_SLQSSetSmsStorage_t *pOutput
       );

/**
 * \ingroup sms
 * 
 * Sets the SMS Storage on the device unpack.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_sms_SLQSSwiSetSmsStorage(
       uint8_t *pResp,
       uint16_t respLen,
       unpack_sms_SLQSSetSmsStorage_t *pOutput
       );

/**
 * \ingroup sms
 * 
 *  Structure contain Parameters that  return current
 *  SMS configuration that is applied to all incoming and outgoing messages.
 *
 *  @param  pSmsStorage
 *          - Values:
 *              - 0x01 - device's permanent memory
 *              - 0x02 - UICC
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct
{
    uint32_t *pSmsStorage;
    swi_uint256_t  ParamPresenceMask;
} unpack_sms_SLQSSwiGetSMSStorage_t;

/**
 * \ingroup sms
 * 
 * Gets the current SMS configuration that is applied
 * to all incoming and outgoing messages pack.
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int pack_sms_SLQSSwiGetSMSStorage(
        pack_qmi_t  *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen
        );

 /**
 * \ingroup sms
 * 
 * Gets the current SMS configuration that is applied
 * to all incoming and outgoing messages unpack.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int unpack_sms_SLQSSwiGetSMSStorage(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_sms_SLQSSwiGetSMSStorage_t *pOutput
        );

/**
 * \ingroup sms
 * 
 *  Contains the parameters passed for the indication about change in 
 *  transport layer information 
 *
 *  @param  regInd
 *          - Indicates whether the transport layer is registered or not
 *          - Values:
 *              - 0x00 - Transport layer is not registered
 *              - 0x01 - Transport layer is registered
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param  pTransLayerInfo
 *          - Optional parameter
 *          - See @ref sms_transLayerInfo for more information
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 * @note    None
 *
 */
typedef struct
{
    uint8_t           regInd;
    sms_transLayerInfo *pTransLayerInfo;
    swi_uint256_t  ParamPresenceMask;
} unpack_sms_SLQSTransLayerInfoCallback_ind_t;

 /**
 * \ingroup sms
 * 
 * Unpack indication about change in transport layer info
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int unpack_sms_SLQSTransLayerInfoCallback_ind(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_sms_SLQSTransLayerInfoCallback_ind_t *pOutput
        );

/**
 * \ingroup sms
 * 
 *  Contains the parameters passed for indication about transport network 
 *  registration change by the device.
 *
 *  @param  NWRegStat
 *          - provides the transport network registration information
 *          - Values:
 *              - 0x00 - No Service
 *              - 0x01 - In Progress
 *              - 0x02 - Failed
 *              - 0x03 - Limited Service
 *              - 0x04 - Full Service
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 * @note    None
 *
 */
typedef struct
{
    uint8_t NWRegStat;
    swi_uint256_t  ParamPresenceMask;
} unpack_sms_SLQSNWRegInfoCallback_ind_t;

 /**
 * \ingroup sms
 * 
 * Unpack indication about change in transport layer info
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int unpack_sms_SLQSNWRegInfoCallback_ind(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_sms_SLQSNWRegInfoCallback_ind_t *pOutput
        );

/**
 * \ingroup sms
 * 
 *  This structure holds information related to message waiting information indication
 *
 *  @param  numInstances
 *          - Number of sets of the elements in structure sms_messageWaitingInfoContent
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param  msgWaitInfo
 *          - Pointer to structure of sms_messageWaitingInfoContent.
 *              - See @ref sms_messageWaitingInfoContent for more information.
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct
{
    uint8_t                      numInstances;
    sms_messageWaitingInfoContent msgWaitInfo[SMS_NUM_OF_SET];
    swi_uint256_t  ParamPresenceMask;
} unpack_sms_SLQSWmsMessageWaitingCallBack_ind_t;

 /**
 * \ingroup sms
 * 
 * Unpack indication for message waiting information
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int unpack_sms_SLQSWmsMessageWaitingCallBack_ind(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_sms_SLQSWmsMessageWaitingCallBack_ind_t *pOutput
        );

/**
 * \ingroup sms
 * 
 *  This structure contains SMS parameters for indication of RAW ASYNC SEND
 *
 *  @param  sendStatus
 *          - Send Status
 *          - Values:
 *              - QMI_ERR_NONE – No error in the request
 *              - QMI_ERR_CAUSE_CODE - SMS cause code
 *              - QMI_ERR_MESSAGE_DELIVERY_FAILURE - Message could not be delivered
 *              - QMI_ERR_NO_MEMORY - Device could not allocate memory to formulate
 *                a response
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param  messageID
 *          - Unique ID assigned by WMS for non-retry messages.
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  @param  causeCode
 *          - WMS cause code
 *          - Bit to check in ParamPresenceMask - <B>17</B>
 *
 *  @param  errorClass
 *          - Error Class
 *          - Values:
 *              - 0x00 - ERROR_CLASS_TEMPORARY
 *              - 0x01 - ERROR_CLASS_PERMANENT
 *          - Bit to check in ParamPresenceMask - <B>18</B>
 *
 *  @param  RPCause
 *          - GW RP cause
 *          - Bit to check in ParamPresenceMask - <B>19</B>
 *
 *  @param  TPCause
 *          - GW TP Cause
 *          - Bit to check in ParamPresenceMask - <B>19</B>
 *
 *  @param  msgDelFailureType
 *          - Message delivery failure type
 *          - Values:
 *              - 0x00 - WMS_MESSAGE_DELIVERY_FAILURE_TEMPORARY
 *              - 0x01 - WMS_MESSAGE_DELIVERY_FAILURE_PERMANENT
 *          - Bit to check in ParamPresenceMask - <B>20</B>
 *
 *  @param  msgDelFailureCause
 *          - Message delivery failure cause
 *          - Values:
 *              - 0x00 - WMS_MESSAGE_BLOCKED_DUE_TO_CALL_CONTROL
 *          - Bit to check in ParamPresenceMask - <B>21</B>
 *
 *  @param  alphaIDLen
 *          - Number of sets of the pAlphaID
 *          - Bit to check in ParamPresenceMask - <B>22</B>
 *
 *  @param  pAlphaID
 *          - Alpha ID
 *          - Bit to check in ParamPresenceMask - <B>22</B>
 *
 *  @param  userData
 *          - Identifies the request associated with this indication.
 *          - Bit to check in ParamPresenceMask - <B>23</B>
 *
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct
{
    uint16_t  sendStatus;
    uint16_t  messageID;
    uint16_t  causeCode;
    uint8_t  errorClass;
    uint16_t  RPCause;
    uint8_t  TPCause;
    uint8_t  msgDelFailureType;
    uint8_t  msgDelFailureCause;
    uint8_t  alphaIDLen;
    uint8_t  *pAlphaID;
    uint32_t userData;
    swi_uint256_t  ParamPresenceMask;
} unpack_sms_SLQSWmsAsyncRawSendCallBack_ind_t;

 /**
 * \ingroup sms
 * 
 * Unpack indication for sms async raw send
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int unpack_sms_SLQSWmsAsyncRawSendCallBack_ind(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_sms_SLQSWmsAsyncRawSendCallBack_ind_t *pOutput
        );


 /**
 * \ingroup sms
 * 
 * This function is used to decode a primary ETWS (Earthquake and Tsunami  Warning System) callback
 *
 * @param[in]  pdu
 *			Raw pdu
 *
 * @param[in]  pduLength
 *			Length of pdu in bytes
 *
 * @param[out]  pSerialNumber
 *			CMAS serial number
 *
 * @param[out]  pMessageIdentifier
 *			CMAS message identifier
 *
 * @param[out]  pWarningType
 *			Warning type (0: Eathquake, 1: Tsunami, 2: Eathquake and Tsunami, 3: Test, 4: Other (future use)
 *
 * @param[out]  pUserAlert
 *			Alert user by sound, viberation or other means
 *
 * @param[out]  pPopup
 *			Displaying a popup is required
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 */
int  sms_DecodePrimaryEtwstMsg(
	uint8_t*    pdu,
	uint8_t	    pduLength,
	uint32_t*   pSerialNumber,
	uint32_t*	pMessageIdentifier,
	uint8_t*    pWarningType,
	bool*	    pUserAlert,
	bool*	    pPopup
);

 /**
 * \ingroup sms
 * 
 * This function is used to decode a secondary ETWS (Earthquake and Tsunami  Warning System) callback
 * The text message will be returned in UCS2 along with related message information. 
 *
 * @param[in]  pdu
 *			raw pdu
 *
 * @param[in]  pduLength
 *			Length of pdu in byte
 *
 * @param[out]  pMsgType
 *			Type of the message.
 *
 * @param[out]  pMessageIdentifier
 *			CMAS message identifier
 *
 * @param[out]  pSerialNumber
 *			CMAS serial number
 *
 * @param[out]  pEncodingAlphabet
 *			Encoding alphabet
 *
 * @param[in,out]  pTextMsgLength
 *			[in]: size of the buffer, [out]: Number of message characters
 *
 * @param[out]  pTextMsg
 *			Returns the text message as  NULL-terminated UCS2 string
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 */
int sms_DecodeSecondaryEtwstMsg(uint8_t*    pdu,
                                uint32_t	pduLength,
                                uint8_t*    pMsgType,
                                uint32_t*	pMessageIdentifier,
                                uint32_t*   pSerialNumber,
                                uint32_t*   pEncodingAlphabet,
                                uint8_t*    pTextMsgLength,
                                wchar_t*    pTextMsg);

 /**
 * \ingroup sms
 * 
 * This function can be used to encode an outgoing WCDMA message.  The 
 * the resulting message can be either stored on the device or sent to the service center.  
 *
 * The caller must provide an UCS2 text message to be encoded, a message
 * reference number and a destination address.  All other information
 * is optional for the caller to specify.  Default values will be used in
 * the encoded when option parameter are not given.  
 *
 * The caller can specify what character set should be used to encode
 *	the given text message.  If the character set is not specified then this
 * function will encode the message using the character set that yields the
 * smallest encoded message.
 *
 * Some text messages will span multiple messages.  This function return
 * all the messages necessary to encode the entire given text message.
 *
 * @param[in,out]  pMessageListSize
 *			- Upon input, specifies the total number of Messages that can be 
 *					constructed in the memory indicated by pMessageList.  Note that
 *					in WCDMA it may take multiple message to encode a single text message
 *					Upon successful output, specifies the total number of Messages 
 *					required.
 *
 * @param[out]  pMessageList:
 *			- A list of constructed message where every member of the list takes
 *					the following form:
 *					- BYTE messageLength
 *					- BYTE message[176]
 *		
 * @param[in]  messageRefNum 
 *			- The message reference number for this message.  This value should 
 *					be incremented for every message the host application sends.
 *
 * @param[in]  pDestAddr
 *			- Gives NULL-terminated ASCII String containing destination address.
 *					International number will be prepended with a '+' character.
 *
 * @param[in]  textMsgLength
 *			- Number of UCS2 characters in the text message (excluding NULL)
 *
 * @param[in]  pTextMsg
 *			- UCS2 text message to be encoded
 *
 * @param[in]  pScAddr (optional)
 *			- Gives NULL-terminated ASCII String containing service center address.
 *					International number will be prepended with a '+' character.
 *      
 * @param[in]  pRejectDuplicates (optional)
 *         - Gives the reject duplicates parameter.  TRUE instructs the service
 *					center to reject new messages if they share the same message 
 *					reference number and destination address as a message already
 *					being held in the service center.  FALSE instructs the service 
 *					centre to accept new messages if they share the same message 
 *					reference number and destination address as a message already 
 *					being held in the service center (default setting if NULL 
 *					pointer is given)
 *              
 * @param[in]  pStatusReportReq (optional)
 *			- Gives the status report request parameter.  TRUE if a status report
 *					is requested.  FALSE if no status report is requested (default 
 *					setting if NULL pointer is given).
 *
 * @param[in]  pReplyPath (optional)
 *			- Gives the reply path parameter.  FALSE is the default setting if
 *					NULL pointer is given.  See 3GPP TS 23.040 Annex D for more information 
 *
 * @param[in]  pValidityFormat (optional)
 *			- Gives validity period format (see note for more information)
 *					- 0: no validity period present (default setting if NULL pointer given)
 *					- 1: relative validity period format (recommended as a validity period format)
 *					- 2: enhanced validity period format
 *					- 3: absolute validity period format
 *
 * @param[in]  validityPeriod (optional)
 *			- Gives the validity period (see note for more information)
 *					- Relative format:  only the first octet is used
 *					- Enhanced format:  all 7 bytes are used
 *					- Absolute format:  all 7 bytes are used
 *
 * @param[in,out]  pEncodingAlphabet (optional)
 *			- Upon input, specifies the alphabet the text message should be encoded in
 *					- 0: smallest possible alphabet (default if NULL pointer given)
 *					- 1: default 7-bit alphabet
 *					- 2: 8-bit alphabet (ASCII)
 *					- 3: UCS2
 *
 *					Upon successful output, specifies the alphabet used to encode the message.
 *
 *	@param[out]	nNationalLangId (optional)
 *			-	National language identifier to indicate what language character set
 *					should be used to encode the message.  This setting is only used when 
 *					7 bit alphabet encoding scheme or smallest alphabet set is specified in pEncodingAlphabet.
 *					- 0: National language identifier not used (default setting)
 *						 GSM 7 bit default alphabet table and GSM 7 bit default alphabet extension table are used
 *					- 1: Turkish single shift table
 *						 GSM 7 bit default alphabet and Turkish single shift table are used 
 *					- 2: Turkish locking shift table
 *						 Turkish locking shift table and GSM 7 bit default alphabet extension table are used
 *					- 3: Turkish locking and single shift table
 *						 Turkish locking shift table and Turkish single shift table are used.
 *
 * @note	Validity period formats:
 *			Relative format is 1 octet in length and takes the following form:
 *				- for values 0 to 143: validity period = (value + 1)* 5 minutes
 *				- for values 144 to 167: validity period = 12 hours + (value - 143)* 30 minutes
 *				- for values 168 to 196: validity period = (value - 166) * 1 day
 *				- for values 197 to 255: validity period = (value - 192) * 1 week
 * @par
 *         Absolute format is 7 octets in length and takes the following form:
 *				YYMMDDHHMMSSTZ where
 *				- YY: year
 *				- MM: month
 *				- DD: day
 *				- HH: hour
 *				- MM: minute
 *				- SS: second
 *				- TZ: timezone
 * @par
 *			The timezone is in relation to GMT, one unit is equal to 15  
 *			minutes and the MSB indicates a negative value
 * @par
 *			Enhanced format is 7 octets in length.  Please see 3GPP TS 23.040 for
 *			the form.
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 * 
 * @par
 *			5 if pMessageListSize is too small to accommodate given text message.  
 *			pMessageListSize shall return the required size.
 * @par
 *			897 if requested encoding alphabet can not accommodate the given text message.  
 *			pEncodingAlphabet shall return an appropriate encoding alphabet.
 */
int  sms_EncodeMOTextMsg(
	uint8_t*    pMessageListSize,
	uint8_t*    pMessageList,
	uint8_t     messageRefNum,
	char*       pDestAddr,
	uint32_t    textMsgLength,
	wchar_t*    pTextMsg,
	char*       pScAddr,
	bool*       pRejectDuplicates,
	bool*       pStatusReportReq,
	bool*       pReplyPath,
	uint8_t*    pValidityFormat,
	uint8_t     validityPeriod[7],
	uint8_t*    pEncodingAlphabet,
	uint8_t	    nNationalLangId );

 /**
 * \ingroup sms
 *
 * This function can be used to encode an outgoing CDMA message.
 * The resulting message can be either stored on the device or sent to the service center.
 *
 * The caller must provide an UCS2 text message to be encoded, a message
 * ID, a callback address and a destination address.  All other information
 * is optional for the caller to specify.  Default values will be used in
 * the encoded when option parameter are not given.  
 *
 * Note that currently this API can only encode 7bit ASCII messages.
 *
 * @param [in,out] pMessageListSize
 *			 - Upon input, specifies the total number of Messages that can be 
 *					constructed in the memory indicated by pMessageList.  Note that
 *					in CDMA it may take multiple message to encode a single text message
 *					Upon successful output, specifies the total number of Messages 
 *					required.
 * @param[out]  pMessage
 *			The constructed raw message 
 *
 * @param[in]  messageId 
 *			The message reference number for this message.  This value should 
 *			be incremented for every message the host application sends.
 *
 * @param[in]  pDestAddr
 *			Gives NULL-terminated ASCII String containing a destination address.
 *			International number will be prepended with a '+' character.
 *
 * @param[in]  pCallbackAddr
 *			Gives NULL-terminated ASCII String containing a callback address.
 *			International number will be prepended with a '+' character.
 *
 * @param[in]  textMsgLength
 *			Number of UCS2 characters in the text message (excluding NULL)
 *
 * @param[out]  pTextMsg
 *			UCS2 text message to be encoded
 *
 * @param[in]  pPriority (optional)
 *			Gives the priority of the outgoing message:
 *				- 0: normal (default if NULL pointer is given)
 *				- 1: interactive
 *				- 2: urgent
 *				- 3: emergency
 *				- 64 - 64: decoded value for URGENT VZAM Support interactive
 *				- 128 - 192: decoded value for URGENT VZAM Support urgent
 *				- 192 - 128: decoded value for URGENT VZAM Support emergency
 *
 * @param[in,out]  pEncodingAlphabet (optional)
 *			- Upon input, specifies the alphabet the text message should be encoded in
 *					- 0: smallest possible alphabet (default if NULL pointer given)
 *					- 1: default 7-bit alphabet
 *					- 2: 8-bit alphabet (ASCII)
 *					- 3: UCS2
 *
 * @note Upon successful output, specifies the alphabet used to encode the message.
 * 
 * @param[in]  pRelValidity (optional)
 *			Gives the relative validity period of the outgoing message per per 4.5.6-1 of spec
 *				- 0: Set Relative validity to 11 
 *				- 1: Set Relative validity to 71 
 *				- 2: Set Relative validity to 167 
 *				- 3: Set Relative validity to 169 
 *				- 4: Set Relative validity to 171 
 *				Values have the following meanings:
 *				- For values 0 to 143: validity period = (value + 1)* 5 minutes
 *				- For values 144 to 167: validity period = 12 hours + (value - 143)* 30 minutes
 *				- For values 168 to 196: validity period = (value - 166) * 1 day
 *				- For values 197 to 244: validity period = (value - 192) * 1 week
 *				- For value 245: validity period = indefinite
 *
 * @param[in]  pDeliveryAck (optional)
 *          - 1- Delivery acklowledgment request 0- No delivery acklowledgment request           
 * 
 * @param  nNationalLangId (optional)
 *			[ O ] - National language identifier to indicate what language character set
 *					should be used to encode the message. This setting is only used when
 *					7 bit alphabet encoding scheme or smallest alphabet set is specified in pEncodingAlphabet.
 *					- 0: National language identifier not used (default setting)
 *						 GSM 7 bit default alphabeet table and GSM 7 bit default alphabet extension table are used
 *					- 1: Turkish single shift table
 *						 GSM 7 bit default alphabet and Turkish single shift table are used
 *					- 2: Turkish locking shift table
 *						 Turkish locking shift table and GSM 7 bit default alphabet extension table are used
 *					- 3: Turkish locking and single shift table
 *						 Turkish locking shift table and Turkish single shift table are used.
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @par
 *			5 if pMessageListSize is too small to accommodate given text message.  
 *			pMessageListSize shall return the required size.
 * @par
 *			897 if requested encoding alphabet can not accommodate the given text 
 *			message.  pEncodingAlphabet shall return an appropriate encoding alphabet.
 */
int  sms_EncodeMOTextMsgCdma(
	uint8_t*    pMessageListSize,
	uint8_t*    pMessage,
	uint8_t     messageId,
	char*       pDestAddr,
	char*       pCallbackAddr,
	uint32_t    textMsgLength,
	wchar_t*    pTextMsg,
	uint8_t*    pPriority,
	uint8_t*    pEncodingAlphabet,
	uint8_t*    pRelValidity,
	uint8_t*	pDeliveryAck,
	uint8_t	    nNationalLangId);

 /**
 * \ingroup sms
 * 
 * This function can be used to decode a received WCDMA SMS message read off 
 * the device using the pack_sms_SLQSGetSMS/unpack_sms_SLQSGetSMS API. The text message will be returned in 
 * UCS2 along with related message information. 
 *
 * Note that some text messages span multiple messages.  Decoded messages can
 * be concatenated based on the information returned by this function.  All
 * text message segment share a message reference number and the same number of
 * total segments.
 *
 * @param[in]  pMessage
 *			Message read off the device via pack_sms_SLQSGetSMS/unpack_sms_SLQSGetSMS
 *
 * @param[in,out]  pSenderAddrLength
 *			 Upon input, indicates the maximum number of ASCII characters 
 *				(including NULL termination) that the pSenderAddr buffer can
 *				accommodate.  Note that a length of 14 is reasonable.
 *				Upon successful output, returns the length of destination 
 *				address string (including the NULL termination)
 *
 * @param[out]  pSenderAddr
 *			 Returns NULL-terminated ASCII String containing destination address
 *				International number will be prepended with a '+' character.
 *
 * @param[in]  pTextMsgLength
 *			 Upon input, specifies the number of UCS2 characters the given text 
 *				message buffer can accommodate.  Upon successful output, returns 
 *				the number of UCS2 characters returns in the given text message 
 *				buffer (including the NULL-terminator)
 *
 * @param[out]  pTextMsg
 *			 Returns the text message as  NULL-terminated UCS2 string
 *
 * @param[in,out]  pScAddrLength (optional)
 *			 Upon input, indicates the maximum number of ASCII characters 
 *				(including NULL termination) that the pScAddr buffer can 
 *				accommodate. Note that a length of 14 is reasonable.  Upon 
 *				successful output, returns the length of SC address string 
 *				(including the NULL termination)
 *				
 * @param[out]  pScAddr (optional)
 *				NULL-terminated ASCII String containing service center address
 *				International number will be prepended with a '+' character.
 *      
 * @param[out]  pMoreMsgSend (optional)
 *          Returns the more message to send parameter.  A value of TRUE 
 *				indicates that no more messages are waiting to be delivered
 *
 * @param[out]  pReplyPath (optional)
 *			Returns the reply path parameter.
 *             See 3GPP TS 23.040 Annex D for more information
 *
 * @param[out]  pStatusReportInd (optional)
 *			Returns the status report indication parameter.
 *             A value of TRUE indicates a that a status report will be returned 
 *				to the sender
 *
 * @param[out]  scTimeStamp (optional)
 *			Returns the timestamp of the SMS which takes the form:
 *					YYMMDDHHMMSSTZ where
 *					- YY: year
 *					- MM: month
 *					- DD: day 
 *					- HH: hour
 *					- MM: minute
 *					- SS: second
 *					- TZ: timezone
 *				All values are in decimal.  The timezone is in relation to GMT, 
 *             one unit is equal to 15 minutes and the MSB indicates a negative 
 *             value
 *
 * @param[out] pConcatenatedMsg (optional)
 *			Returns TRUE if this message is a segment of a concatenated message
 *          
 * @param[out]  pMsgRefNum (optional)
 *			Returns the message reference number
 *
 * @param[out] pTotalSegments (optional)
 *			Returns the total number of segments if this message is part of a 
 *				concatenated message.
 *
 * @param[out] pSegmentNum (optional)
 *			Returns the segment sequence number of this portion of the concatenated
 *				message.
 *
 * @param[out]  pEncodingAlphabet (optional)
 *			Return the alphabet the text message decoded
 *					- 1: default 7-bit alphabet
 *					- 2: 8-bit alphabet (ASCII)
 *					- 3: UCS2
 * @param[in]  status (optional - used when MB interface is used)
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 * @note
 *			5 if pSenderAddrLength, pTextMsgLength or pScAddrLength is too small 
 *			to accommodate the decoded data then the required length will be 
 *			returned in the problem parameter.
 * @note
 *			897 if the given message can not decoded by this function because 
 *			it is of a different format.
 */
uint32_t sms_DecodeMTTextMsg(uint8_t*    pMessage,
                        uint8_t*    pSenderAddrLength,
                        char*       pSenderAddr,
                        uint8_t*    pTextMsgLength,
                        wchar_t*    pTextMsg,
                        uint8_t*    pScAddrLength,
                        char*       pScAddr,
                        bool*       pMoreMsgSend,
                        bool*       pReplyPath,
                        bool*       pStatusReportInd,
                        uint8_t     scTimeStamp[7],
                        bool*       pConcatenatedMsg,
                        uint32_t*   pMsgRefNum,
                        uint8_t*    pTotalSegments,
                        uint8_t*    pSegmentNum,
                        uint8_t*    pEncodingAlphabet,
                        uint8_t	    status);

 /**
 * \ingroup sms
 *
 * This function can be used to decode a received CDMA SMS message read off 
 * the device using the GetSMS() API. The text message will be returned in 
 * UCS2 along with related message information. 
 *
 * @param[in]  messageLength:
 *			   Length of the message to be decoded in bytes
 *
 * @param[in]  pMessage:
 *		       Message read off the device via GetSMS
 * 
 * @param[in]  pMessageID:
 *			   Message ID
 *
 * @param[in,out]  pSenderAddrLength
 *			    Upon input, indicates the maximum number of ASCII characters 
 *				(including NULL termination) that the pSenderAddr buffer can
 *				accommodate.  Note that a length of 14 is reasonable.
 *				Upon successful output, returns the length of originating 
 *				address string (including the NULL termination)
 *
 * @param[out]  pSenderAddr
 *			    Returns NULL-terminated ASCII String containing the originating address
 *				International number will be prepended with a '+' character.
 *
 * @param[in,out]  pTextMsgLength
 *			    Upon input, specifies the number of UCS2 characters the given text 
 *				message buffer can accommodate.  Upon successful output, returns 
 *				the number of UCS2 characters returns in the given text message 
 *				buffer (including the NULL-terminator)
 *
 * @param[out]  pTextMsg
 *			    Returns the text message as  NULL-terminated UCS2 string
 *      
 * @param[out]  pPriority (optional)
 *              Returns the priority setting of the message
 *				- 0x00: normal
 *				- 0x01: interactive
 *				- 0x02: urgent
 *				- 0x03: emergency
 *				- 0xFF: unavailable setting
 *
 * @param[out]  pPrivacy (optional)
 *			    Returns the privacy setting of the message
 *				- 0x00: not restricted
 *				- 0x01: restricted
 *				- 0x02: confidential
 *				- 0x03: secret
 *				- 0xFF: unavailable setting
 *
 * @param[out]  pLanguage (optional)
 *			    Returns the language setting of the message
 *				- 0x00: unspecified
 *				- 0x01: english
 *				- 0x02: french
 *				- 0x03: spanish
 *				- 0x04: japanese
 *				- 0x05: korean
 *				- 0x06: chinese
 *				- 0x07: hebrew
 *				- 0xFF: unavailable setting
 *
 * @param[out]  mcTimeStamp (optional)
 *			    Returns the message center timestamp which takes the form:
 *					YYMMDDHHMMSSTZ where
 *					- YY: year
 *					- MM: month
 *					- DD: day 
 *					- HH: hour
 *					- MM: minute
 *					- SS: second
 *					- TZ: timezone
 *			    All values are in decimal.  The timezone is in relation to GMT, 
 *              one unit is equal to 15 minutes and the MSB indicates a negative 
 *              value.  If this information is unavailable for this message then
 *				this field will be filled with 0xFF.
 *
 * @param[out]  absoluteValidity (optional)
 *			Returns the absolute validity period setting for this message.  This
 * 			field takes the same form as mcTimeStamp.
 *          
 * @param[out]  pRelativeValidity (optional)
 *			    Returns the relative validity period.  Values have the following meanings:
 *				- For values 0 to 143: validity period = (value + 1)* 5 minutes
 *				- For values 144 to 167: validity period = 12 hours + (value - 143)* 30 minutes
 *				- For values 168 to 196: validity period = (value - 166) * 1 day
 *				- For values 197 to 244: validity period = (value - 192) * 1 week
 *				- For value 245: validity period = indefinite
 *				- For value 246: validity period = immediate
 *				- For value 247: validity period = valid until mobile becomes inactive
 *				- For value 248: validity period = valid until registration area changes
 *				- For values 249 to 254: reserved
 *				- For value 255: unavailable information
 *
 * @param[out]  pDisplayMode (optional)
 *			    Returns the display mode parameter
 *				- 0x00: immediate display
 *				- 0x01: mobile default setting
 *				- 0x02: user invoked
 *				- 0x03: reserved
 *				- 0xFF: unavailable parameter
 *
 * @param[out]  pUserAcknowledgementReq (optional)
 *			    Returns the user (manual) acknowledgment request parameter
 *				- TRUE means the user is requested to manually acknowledge the delivery of the message
 *				- FALSE means no such user acknowledgement is requested
 *
 * @param[out]  pReadAcknowledgementReq (optional)
 *			    Returns the read acknowledgement request parameter
 *				- TRUE means acknowledgment of the message being viewed is requested
 *				- FALSE means no such read acknowledgement is requested
 *
 * @param[out]  pAlertPriority (optional)
 *			    Returns the alerting parameter setting
 *				- 0x00: use default alert
 *				- 0x01: use low priority alert
 *				- 0x02: use medium priority alert
 *				- 0x03: use high priority alert
 *				- 0xFF: unavailable parameter
 *
 * @param[out]  pCallbkAddrLength (optional)
 *			    returns the length of Callback  
 *				address string (including the NULL termination)
 *
 * @param[out]  pCallbkAddr
 *			    Returns NULL-terminated ASCII String containing callback address String 
 *				containing the Call Back number with a 32 maximum characters.
 *
 * @param[out]  pEncodingAlphabet (optional)
 *			    - return the alphabet the text message decoded
 *					- 1: default 7-bit alphabet
 *					- 2: 8-bit alphabet (ASCII)
 *					- 3: UCS2
 * 
 * @param[out] pConcatenatedMsg (optional)
 *			Returns TRUE if this message is a segment of a concatenated message
 *          
 * @param[out]  pMsgRefNum (optional)
 *			Returns the message reference number
 *
 * @param[out] pTotalSegments (optional)
 *			Returns the total number of segments if this message is part of a 
 *				concatenated message.
 *
 * @param[out] pSegmentNum (optional)
 *			Returns the segment sequence number of this portion of the concatenated
 *				message.
 * 
 * @return 
 * @par
 *			5 if pSenderAddrLength, pTextMsgLength or pScAddrLength is too small
 *			to accommodate the decoded data then the required length will be 
 *			returned in the problem parameter.
 * @par
 *			897 if the given message can not decoded by this function because 
 *			it is of a different format.
 *
 */
uint32_t sms_CDMADecodeMTTextMsg(uint32_t    messageLength,
                        uint8_t*    pMessage,
                        uint32_t*   pMessageID,
                        uint8_t*    pSenderAddrLength,
                        char*       pSenderAddr,
                        uint8_t*    pTextMsgLength,
                        wchar_t*    pTextMsg,
                        uint8_t*    pPriority,
                        uint8_t*    pPrivacy,
                        uint8_t*    pLanguage,
                        uint8_t     mcTimeStamp[7],
                        uint8_t     absoluteValidity[7],
                        uint8_t*    pRelativeValidity,
                        uint8_t*    pDisplayMode,
                        bool*       pUserAcknowledgementReq,
                        bool*       pReadAcknowledgementReq,
                        uint8_t*    pAlertPriority,
                        uint8_t*    pCallbkAddrLength,
                        char*       pCallbkAddr,
                        uint8_t*    pEncodingAlphabet,
                        bool*       pConcatenatedMsg,
                        uint32_t*   pMsgRefNum,
                        uint8_t*    pTotalSegments,
                        uint8_t*    pSegmentNum);

 /**
 * \ingroup sms
 * 
 * This function can be used to decode a received Transfer Routing Mobile Terminaed SMS message read off 
 * the device using the pack_sms_SLQSGetSMS/unpack_sms_SLQSGetSMS API. The text message will be returned in 
 * UCS2 along with related message information. 
 *
 * Note that some text messages span multiple messages.  Decoded messages can
 * be concatenated based on the information returned by this function.  All
 * text message segment share a message reference number and the same number of
 * total segments.
 *
 * @param[in]  pMessage
 *			Message read off the device via pack_sms_SLQSGetSMS/unpack_sms_SLQSGetSMS
 *
 * @param[out]  pduSCAddr (optional)
 *				Service center number in decimal semi-octates
 *      
 * @param[in]  nSCAddrLen
 *				Service center number buffer size
 *      
 * @param[in,out]  pSenderAddrLength
 *			 Upon input, indicates the maximum number of ASCII characters 
 *				(including NULL termination) that the pSenderAddr buffer can
 *				accommodate.  Note that a length of 14 is reasonable.
 *				Upon successful output, returns the length of destination 
 *				address string (including the NULL termination)
 *
 * @param[out]  pSenderAddr
 *			 Returns NULL-terminated ASCII String containing destination address
 *				International number will be prepended with a '+' character.
 *
 * @param[in]  pTextMsgLength
 *			 Upon input, specifies the number of UCS2 characters the given text 
 *				message buffer can accommodate.  Upon successful output, returns 
 *				the number of UCS2 characters returns in the given text message 
 *				buffer (including the NULL-terminator)
 *
 * @param[out]  pTextMsg
 *			 Returns the text message as  NULL-terminated UCS2 string
 *
 * @param[in,out]  pScAddrLength (optional)
 *			 Upon input, indicates the maximum number of ASCII characters 
 *				(including NULL termination) that the pScAddr buffer can 
 *				accommodate. Note that a length of 14 is reasonable.  Upon 
 *				successful output, returns the length of SC address string 
 *				(including the NULL termination)
 *				
 * @param[out]  pScAddr (optional)
 *				NULL-terminated ASCII String containing service center address
 *				International number will be prepended with a '+' character.
 *      
 * @param[out]  scTimeStamp (optional)
 *			Returns the service center address which takes the form:
 *					YYMMDDHHMMSSTZ where
 *					- YY: year
 *					- MM: month
 *					- DD: day 
 *					- HH: hour
 *					- MM: minute
 *					- SS: second
 *					- TZ: timezone
 *				All values are in decimal.  The timezone is in relation to GMT, 
 *             one unit is equal to 15 minutes and the MSB indicates a negative 
 *             value
 *
 * @param[out] pConcatenatedMsg (optional)
 *			Returns TRUE if this message is a segment of a concatenated message
 *          
 * @param[out]  pMsgRefNum (optional)
 *			Returns the message reference number
 *
 * @param[out] pTotalSegments (optional)
 *			Returns the total number of segments if this message is part of a 
 *				concatenated message.
 *
 * @param[out] pSegmentNum (optional)
 *			Returns the segment sequence number of this portion of the concatenated
 *				message.
 *
 * @param[out]  pEncodingAlphabet (optional)
 *			Return the alphabet the text message decoded
 *					- 1: default 7-bit alphabet
 *					- 2: 8-bit alphabet (ASCII)
 *					- 3: UCS2
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 * @note
 *			5 if pSenderAddrLength, pTextMsgLength or pScAddrLength is too small 
 *			to accommodate the decoded data then the required length will be 
 *			returned in the problem parameter.
 * @note
 *			897 if the given message can not decoded by this function because 
 *			it is of a different format.
 */
int sms_DecodeTransRouteMTTextMsg(uint8_t*    pMessage,
                                    uint8_t*  pduSCAddr,
                                    uint8_t   nSCAddrLen,
                                    uint8_t*  pSenderAddrLength,
                                    char*     pSenderAddr,
                                    uint8_t*  pTextMsgLength,
                                    wchar_t*  pTextMsg,
                                    uint8_t*  pScAddrLength,
                                    char*     pScAddr,
                                    uint8_t   scTimeStamp[7],
                                    bool*     pConcatenatedMsg,
                                    uint32_t* pMsgRefNum,
                                    uint8_t*  pTotalSegments,
                                    uint8_t*  pSegmentNum,
                                    uint8_t*  pEncodingAlphabet);

/**
 * \ingroup sms
 * 
 * This function is used to decode a class 0 SMS payload
 * The text message will be returned in UCS2 along with. 
 *
 * @param[in]  pdu
 *			Raw pdu
 *
 * @param[out]  pMessageType
 *			returning message type, 0x04 = SMS delivery 0x06 = SMS sent delivery acknowledgement
 *
 * @param[out]  pSCNumberLength
 *			phone number length of class0 service center
 *
 * @param[out]  pSCNumber
 *			phone number of class0 SMS service center, UCS2
 *
 * @param[out]  pMONumberLength
 *			phone number length of class 0 SMS mobile originator
 *
 * @param[out]  pMONumber
 *			phone number of class 0 SMS mobile originator, UCS2
 *
 * @param[out]  pProtocolID
 *			Class 0 SMS protocol ID
 *
 * @param[out]  pEncodingAlphabet
 *			Encoding alphabet
 *
 * @param[out]  scTimeStamp
 *			recieved timestamp

 * @param[out]  pTextMsgLength
 *			SMS delivery type message length
 *
 * @param[out]  pTextMsg
 *			SMS delivery type message
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
*/
int sms_DecodeClass0Msg (uint8_t*   pdu,
	                    uint8_t*    pMessageType,
	                    uint8_t*    pSCNumberLength,
	                    wchar_t*    pSCNumber,
	                    uint8_t*    pMONumberLength,
	                    wchar_t*    pMONumber,
	                    uint8_t*	pProtocolID,
	                    uint8_t*    pEncodingAlphabet,
	                    uint8_t     scTimeStamp[7],
	                    uint16_t*   pTextMsgLength,
	                    wchar_t*    pTextMsg);

/**
 * \ingroup sms
 *
 * This function is used to decode a CMAS (Commercial Mobile Alert System) callback
 * The text message will be returned in UCS2 along with related message information. 
 *
 * @param[in]  pdu
 *			Raw pdu
 *
 * @param[in]  pduLength
 *			Length of pdu in bytes
 *
 * @param[out]  pSerialNumber
 *			CMAS serial number
 *
 * @param[out]  pMessageIdentifier
 *			CMAS message identifier
 *
 * @param[out]  pPageCount
 *			number of pages of CMAS message
 *
 * @param[out]  pPageIndex
 *			Pages segment number of CMAS message, 1 - N
 *
 * @param[out]  pEncodingAlphabet
 *			Encoding alphabet
 *
 * @param[in,out]  pTextMsgLength
 *			in: size of the buffer, out: Number of message characters
 *
 * @param[out]  pTextMsg
 *			Returns the text message as  NULL-terminated UCS2 string
 *
  * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
*/
int sms_DecodeCmasMsg ( uint8_t*    pdu,
                        uint8_t	    pduLength,
                        uint32_t*   pSerialNumber,
                        uint32_t*	pMessageIdentifier,
                        uint32_t*	pPageCount,
                        uint32_t*	pPageIndex,
                        uint32_t*   pEncodingAlphabet,
                        uint8_t*    pTextMsgLength,
                        wchar_t*    pTextMsg);

/**
 * \ingroup sms
 * 
 *  Structure contain Parameters that  return storage available for new SMS messages.
 *
 *  @param  pMemory_available
 *          - Values:
 *              - 1 if memory is available for storing new messages
 *              - 0 if memory capacity is exceeded
 *          - Bit to check in ParamPresenceMask - <B>0x10</B>
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct
{
    uint8_t *pMemory_available;
    swi_uint256_t  ParamPresenceMask;
} unpack_sms_MemoryStatus_t;

/**
 * \ingroup sms
 * 
 * Gets the current SMS configuration that is applied
 * to all incoming and outgoing messages pack.
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int pack_sms_ReportSmsMemoryStatus(
        pack_qmi_t  *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen
        );

 /**
 * \ingroup sms
 * 
 * Gets the current SMS configuration that is applied
 * to all incoming and outgoing messages unpack.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int unpack_sms_ReportSmsMemoryStatus(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_sms_MemoryStatus_t *pOutput
        );

/**
 * \ingroup sms
 * 
 *  - Message Priority
 *           - Values:
 *              - 0 - Normal
 *              - 1	- Urgent
 */
enum SMS_PRIORITY
{
	PRIORITY_Normal,
	PRIORITY_Urgent
};

/**
 * \ingroup sms
 * 
 *  - Message Broadcast Type
 *           - Values:
 *              - 0 - CMAS
 *              - 1	- Earthquake
 *              - 2 - Tsunami
 *              - 3 - Earthquake and Tsunami
 *              - 4 - Secondary ETWS message 
 */
enum TYPE_BROADCAST_Type
{
	BROADCAST_CMAS = 0,
	BROADCAST_ETWSPrim_Earthquake,
	BROADCAST_ETWSPrim_Tsunami,
	BROADCAST_ETWSPrim_EarthquakeTsunami,
	BROADCAST_EtwsSec
};

/**
 * \ingroup sms
 * 
 *          - Message status
 *           - Values:
 *              - 0 - New
 *              - 1	- Read
 *              - 2 - Draft
 *              - 3 - Sent
 */
typedef enum
{
	Message_Status_New = 0,
	Message_Status_Read,
	Message_Status_Draft,
	Message_Status_Sent
}TYPE_SMS_Message_Status;

/**
 * \ingroup sms
 * 
 *  - Message encoding type
 *      - Values:
 *          - 1 - 7bit Encoding
 *          - 2 - 8bit Encoding
 *          - 3	- UCS2 Encoding
 */
typedef enum
{
	Message_Encoding_7bit = 1,
	Message_Encoding_8bit,
	Message_Encoding_Ucs2
}TYPE_SMS_Message_Encoding;

/**
 * \ingroup sms
 * 
 * This sturcture contains STRUCT_SMS_Pdu struct parameters.
 * @param sms_Ref_Num
 *          - SMS message regference number
 * 
 * @param message_Status
 *          - Message status
 *           - Values:
 *              - 0 - New
 *              - 1	- Read
 *              - 2 - Draft
 *              - 3 - Sent
 *
 * @param message_Encoding
 *          - Message encoding type
 *           - Values:
 *              - 1 - 7bit Encoding
 *              - 2 - 8bit Encoding
 *              - 3	- UCS2 Encoding
 *
 * @param fragmented_message
 *          - Concatinated SMS 
 *          - 0: not a concatinated SMS
 *          - 1: not a concatinated SMS
 *
 * @param total_fragments
 *          - SMS total fragments count
 * 
 * @param fragment_index
 *          - SMS fragment index
 * 
 * @param timestamp
 *			- timestamp of the SMS:
 *					YYMMDDHHMMSSTZ where
 *					- timestamp[0] YY: year (year-2000, add 2000 to get the year)
 *					- timestamp[1] MM: month
 *					- timestamp[2] DD: day 
 *					- timestamp[3] HH: hour
 *					- timestamp[4] MM: minute
 *					- timestamp[5] SS: second
 *					- timestamp[6] TZ: timezone
 *				All values are in decimal.  The timezone is in relation to GMT, 
 *             one unit is equal to 15 minutes and the MSB indicates a negative 
 *             value
 * 
 * @param moAddress
 *          - Mobile originated address
 * 
 * @param scAddress
 *          - Service center address
 * 
 * @param pMessage
 *          - SMS text message
 */
typedef struct
{
	uint32_t					sms_Ref_Num;
	TYPE_SMS_Message_Status		message_Status;
	TYPE_SMS_Message_Encoding	message_Encoding;
	bool					    fragmented_message; 
	uint8_t						total_fragments;
	uint8_t						fragment_index; 
	uint8_t      				timestamp[LEN_SMS_Timestamp];
	char 						moAddress[LEN_SMS_ADDRESS_BYTE];
	char 						scAddress[MAX_MSC_ADDRESS_SIZE];
	wchar_t 					*pMessage;
} STRUCT_SMS_Pdu;

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif

