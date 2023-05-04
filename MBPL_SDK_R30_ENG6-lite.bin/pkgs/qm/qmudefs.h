/*************
 *
 * Filename:  qmudefs.h
 *
 * Purpose:   User definitions for qm package
 *
 * Copyright: © 2011-2014 Sierra Wireless Inc., all rights reserved
 *
 **************/
#include <string.h>

#ifndef QMUDEFS_H
#define QMUDEFS_H

/*
    QMI REQUEST PACKET SENT OVER IPC CHANNEL AND RECEIVED BY QMRR TASK
    -------------------------------------------
    | QMUXSDU PREAMBLE  | QMI SERVICE MESSAGE |
    -------------------------------------------
bytes:      8                  m

    QMUX SDU PREAMBLE
    ----------------------------------------------------------------------------------
    | QMI Service Type | QMI Request Timeout | QMI Transaction Length | QMI Instance |
    ----------------------------------------------------------------------------------
bytes:      1               4                           2                   1

    QMI SERVICE MESSAGE
    --------------------------------------
    | QMI SVC MSG HDR | QMI SVC MSG TLVs |
    --------------------------------------
bytes:      4               n

    QMI SVC MSG HDR
    ------------------------
    | MSG ID  | MSG LENGTH |
    ------------------------
bytes:   2          2

*/

/* Includes */
#include "aa/aaglobal.h"
#include "msgid.h"

/* QMI Error storage array size. This is used to size the array
 * on the API side for storing the last error received from the
 * modem when the QMI Error Flag is set in a response header.
 * The size is the same as is defined in the Windows SDK
 */
#define QMFWERRORSZ    200

/*******************************
 *  QMI DRIVER IOCTL COMMANDS  *
 ******************************/
/* Device I/O control code for setting QMI service */
#define QMI_GET_SERVICE_FILE_IOCTL  0x8BE0 + 1

/* Device I/O control code for obtaining device VIDPID */
#define QMI_GET_VIDPID_IOCTL        0x8BE0 + 2

/* Device I/O control code for obtaining device MEID */
#define QMI_GET_MEID_IOCTL          0x8BE0 + 3

/* Device path size - last octet reserved for null termination */
#define QMI_DEVICE_PATH_MAX_SIZE    256

/* Device MEID size - last octet reserved for null termination */
#define QMI_MEID_BUF_SIZE           15

/* USB port name size - last octet reserved for null termination */
#define QMI_USB_PORT_NAME_SIZE      32

/* Device I/O control code for releasing a QMI service client */
#define QMI_RELEASE_SERVICE_FILE_IOCTL  (0x8BE0 + 4)

#define QMI_QOS_ADD_MAPPING         0x8BE0 + 5
#define QMI_QOS_DEL_MAPPING         0x8BE0 + 6
#define QMI_QOS_CLR_MAPPING         0x8BE0 + 7

#define IOCTL_QMI_GET_TX_Q_LEN      0x8BE0 + 9

#define QMI_QOS_EDIT_MAPPING         0x8BE0 + 10
#define QMI_QOS_READ_MAPPING         0x8BE0 + 11
#define QMI_QOS_DUMP_MAPPING         0x8BE0 + 12
#define QMI_GET_USBNET_STATS         0x8BE0 + 13
#define QMI_GET_QMAP_SUPPORT         0x8BE0 + 15
#define QMI_SET_QMAP_IP_TABLE        0x8BE0 + 16
#define QMI_SET_QMAP_IPv6_TABLE      0x8BE0 + 17
#define QMI_GET_SVC_VERSION_IOCTL    0x8BE0 + 19

/**********************
 *  QMUX SDU DEFINES  *
 **********************/
/* The preamble contains any data the SDK QM task requires to carry out the QMI
 * request that does not form the QMI (request) Message sent to the device.
 * Current preamble fields include:
 *  QMI service pertaining to th QMI request (swi_uint8)
 *  QMI request timeout (swi_ulong)
 *  QMI Transaction length (swi_uint16)
 *  QMI Instance Identifier
 */
#define QMUXSDU_PREAMBLE    (8+1) //prepend one byte ipc-xid

/* QMI Parameter field (QMUX SDU) maximum size */
#define QMPARAMMAX          4 * 1024

/*** QMI Protocol Field definitions ***/

/* QMI Service Message definitions */
#define QMISVC_MSGID_SZ             2   /* QMI service message, message ID size */
#define QMISVC_MSGLENSZ             2   /* QMI service message, message length */
#define QMISVC_MSGHDR_SZ            (QMISVC_MSGID_SZ + QMISVC_MSGLENSZ)
#define QMISVC_MSGID_OFFSET         0
#define QMISVC_MSGLEN_OFFSET        (QMISVC_MSGID_OFFSET + QMISVC_MSGID_SZ)

/* QMI Service Transaction (QMUX SDU) definitions */
#define QMUXSDU_CTRLFLGS_SZ         1   /* QMI service transaction control flags size */
#define QMUXSDU_XACTIONID_SZ        2   /* QMI service transaction transaction ID size */
#define QMUXSDU_HDR_SZ              (QMUXSDU_CTRLFLGS_SZ +\
                                     QMUXSDU_XACTIONID_SZ)

#define QMUXSDU_CTRLFLGS_OFFSET     0
#define QMUXSDU_XACTIONID_OFFSET    (QMUXSDU_CTRLFLGS_OFFSET +\
                                     QMUXSDU_CTRLFLGS_SZ)
#define QMUXSDU_QMISVCMSG_OFFSET    (QMUXSDU_XACTIONID_OFFSET +\
                                     QMUXSDU_XACTIONID_SZ)

/* QMI TLV definitions */
#define QMITLV_TYPE_SZ               1   /* QMI TLV, type size */
#define QMITLV_LENGTH_SZ             2   /* QMI TLV,  TLV length */
#define QMITLV_HDR_SZ                (QMITLV_TYPE_SZ + QMITLV_LENGTH_SZ)

/* Invalid QMI transaction ID */
#define QMI_TRANSACTION_ID_INVALID   0
#define QMI_MSG_ID_INVALID          -1
#define QMI_CLIENT_ID_INVALID       -1

/* supported QMI clients */
#define QMIWDSSVCNAM     "WDS"
#define QMIDMSSVCNAM     "DMS"
#define QMINASSVCNAM     "NAS"
#define QMIQOSSVCNAM     "QOS"
#define QMIWMSSVCNAM     "WMS"
#define QMIPDSSVCNAM     "PDS"
#define QMIAUTSVCNAM     "AUT"
#define QMIUIMSVCNAM     "UIM"
#define QMIRMSSVCNAM     "RMS"
#define QMIOMASVCNAM     "OMA"
#define QMISWIOMASVCNAM  "SWIOMA"
#define QMIPBMSVCNAM     "PBM"
#define QMICATSVCNAM     "CAT"
#define QMIDCSSVCNAM     "DCS"
#define QMIFMSSVCNAM     "FMS"
#define QMISARSVCNAM     "SAR"
#define QMIAUDIOSVCNAM   "AUDIO"
#define QMIVOICESVCNAM   "VOICE"
#define QMIIMSSVCNAM     "IMS"
#define QMISWIAUDIOSVCNAM "SWIAUDIO"
#define QMILOCSVCNAM     "LOC"
#define QMIIMSASVCNAM    "IMSA"
#define QMITMDSVCNAM     "TMD"
#define QMIAVMSNAM       "AVMS"
#define QMIINVSVCNAM     "INV"  /* invalid service */

/* WDS service defines */
#define IPv4_FAMILY_PREFERENCE  0x04
#define IPv6_FAMILY_PREFERENCE  0x06

/* Maximun PDN Number*/
#define MAX_PDN_NUMBER 8


/*************
 *
 * Name:    qmisupportedclients
 *
 * Purpose: QMI service clients
 *
 * Members: QMI<QMI Service>CLNT
 *
 * Notes:   DCS/FMS clients are serviced by QMI services provided by the SDK.
 *          Hence, the corresponding requests are processed locally by the SDK,
 *          and are therefore not sent out to the device.
 *
 **************/
enum qmisupportedclients
{
    QMI_SUPPORTED_CLNT_MIN,
    QMIWDSCLNT = QMI_SUPPORTED_CLNT_MIN,
    QMIDMSCLNT,
    QMINASCLNT,
    QMIQOSCLNT,
    QMIWMSCLNT,
    QMIPDSCLNT,
    QMIAUTCLNT,
    QMIUIMCLNT,
    QMICATCLNT,
    QMIRMSCLNT,
    QMIOMACLNT,
    QMIPBMCLNT,
    QMIDCSCLNT, /* see Notes in header above */
    QMIDCSCLNT2,
    QMIDCSCLNT3,
    QMIDCSCLNT4,
    QMIDCSCLNT5,
    QMIDCSCLNT6,
    QMIDCSCLNT7,
    QMIDCSCLNT8,
    QMISWIOMACLNT,
    QMIFMSCLNT,
    QMISARCLNT,
    QMIVOICECLNT,
    QMIAUDIOCLNT,
    QMIIMSCLNT,
    QMISWIAUDIOCLNT,
    QMISWILOCCLNT,
    QMIWDSV6CLNT,
    QMISWIOMAEXTCLNT,
    QMILOCCLNT,
    QMIIMSACLNT,
    QMIDSDCLNT,
    QMITMDCLNT,
    QMISWIM2MCLNT,
    QMISWIDMSCLNT,
    /* add new clients for QMI Instance 1 above this line */
    QMINSTANCE1LASTCLIENT=QMISWIDMSCLNT,
    /* clients for 2nd QMI interface */
    QMIWDSCLNT2,
    QMIWDSV6CLNT2,
    /* add new clients for QMI Instance 2 above this line */
    QMIINSTANCE2LASTCLIENT=QMIWDSV6CLNT2,
    /* clients for 3rd QMI interface */
    QMIWDSCLNT3,
    QMIWDSV6CLNT3,
    /* add new clients for QMI Instance 3 above this line */
    QMIINSTANCE3LASTCLIENT=QMIWDSV6CLNT3,
    /* clients for 4th QMI interface */
    QMIWDSCLNT4,
    QMIWDSV6CLNT4,
    /* add new clients for QMI Instance 4 above this line */
    QMIINSTANCE4LASTCLIENT=QMIWDSV6CLNT4,
    /* clients for 5th QMI interface */
    QMIWDSCLNT5,
    QMIWDSV6CLNT5,
    /* add new clients for QMI Instance 5 above this line */
    QMIINSTANCE5LASTCLIENT=QMIWDSV6CLNT5,
    /* clients for 6th QMI interface */
    QMIWDSCLNT6,
    QMIWDSV6CLNT6,
    /* add new clients for QMI Instance 6 above this line */
    QMIINSTANCE6LASTCLIENT=QMIWDSV6CLNT6,
    /* clients for 7th QMI interface */
    QMIWDSCLNT7,
    QMIWDSV6CLNT7,
    /* add new clients for QMI Instance 7 above this line */
    QMIINSTANCE7LASTCLIENT=QMIWDSV6CLNT7,
    /* clients for 8th QMI interface */
    QMIWDSCLNT8,
    QMIWDSV6CLNT8,
    /* qos client for QMI instance 2 */
    QMIQOSCLNT2,
    /* qos client for QMI instance 3 */
    QMIQOSCLNT3,
    /* qos client for QMI instance 4 */
    QMIQOSCLNT4,
    /* qos client for QMI instance 5 */
    QMIQOSCLNT5,
    /* qos client for QMI instance 6 */
    QMIQOSCLNT6,
    /* qos client for QMI instance 7 */
    QMIQOSCLNT7,
    /* qos client for QMI instance 8 */
    QMIQOSCLNT8,
    /* DO NOT add new clients below this line */
    QMI_SUPPORTED_CLNT_MAX,
    QMIUNSUPPORTEDCLNT
};


/* QMI Call End Reason Enumeration */
enum eQMICallEndReason
{
    eQMI_CALL_END_REASON_BEGIN = -1,

   // General
   eQMI_CALL_END_REASON_UNSPECIFIED = 1,           // 1
   eQMI_CALL_END_REASON_CLIENT_END,                // 2
   eQMI_CALL_END_REASON_NO_SRV,                    // 3
   eQMI_CALL_END_REASON_FADE,                      // 4
   eQMI_CALL_END_REASON_REL_NORMAL,                // 5
   eQMI_CALL_END_REASON_ACC_IN_PROG,               // 6
   eQMI_CALL_END_REASON_ACC_FAIL,                  // 7
   eQMI_CALL_END_REASON_REDIR_OR_HANDOFF,          // 8
   eQMI_CALL_END_REASON_CLOSE_IN_PROGRESS,         // 9
   eQMI_CALL_END_REASON_AUTH_FAILED,               // 10
   eQMI_CALL_END_REASON_INTERNAL,                  // 11

   // CDMA
   eQMI_CALL_END_REASON_CDMA_LOCK = 500,           // 500
   eQMI_CALL_END_REASON_INTERCEPT,                 // 501
   eQMI_CALL_END_REASON_REORDER,                   // 502
   eQMI_CALL_END_REASON_REL_SO_REJ,                // 503
   eQMI_CALL_END_REASON_INCOM_CALL,                // 504
   eQMI_CALL_END_REASON_ALERT_STOP,                // 505
   eQMI_CALL_END_REASON_ACTIVATION,                // 506
   eQMI_CALL_END_REASON_MAX_ACCESS_PROBE,          // 507
   eQMI_CALL_END_REASON_CCS_NOT_SUPPORTED_BY_BS,   // 508
   eQMI_CALL_END_REASON_NO_RESPONSE_FROM_BS,       // 509
   eQMI_CALL_END_REASON_REJECTED_BY_BS,            // 510
   eQMI_CALL_END_REASON_INCOMPATIBLE,              // 511
   eQMI_CALL_END_REASON_ALREADY_IN_TC,             // 512
   eQMI_CALL_END_REASON_USER_CALL_ORIG_DURING_GPS, // 513
   eQMI_CALL_END_REASON_USER_CALL_ORIG_DURING_SMS, // 514
   eQMI_CALL_END_REASON_NO_CDMA_SRV,               // 515

   // GSM/WCDMA
   eQMI_CALL_END_REASON_CONF_FAILED = 1000,        // 1000
   eQMI_CALL_END_REASON_INCOM_REJ,                 // 1001
   eQMI_CALL_END_REASON_NO_GW_SRV,                 // 1002
   eQMI_CALL_END_REASON_NETWORK_END,               // 1003

   eQMI_CALL_END_REASON_LLC_SNDCP_FAILURE,         // 1004
   eQMI_CALL_END_REASON_INSUFFICIENT_RESOURCES,    // 1005
   eQMI_CALL_END_REASON_OPTION_TEMP_OOO,           // 1006
   eQMI_CALL_END_REASON_NSAPI_ALREADY_USED,        // 1007
   eQMI_CALL_END_REASON_REGULAR_DEACTIVATION,      // 1008
   eQMI_CALL_END_REASON_NETWORK_FAILURE,           // 1009
   eQMI_CALL_END_REASON_UMTS_REATTACH_REQ,         // 1010
   eQMI_CALL_END_REASON_UMTS_PROTOCOL_ERROR,       // 1011
   eQMI_CALL_END_REASON_OPERATOR_BARRING,          // 1012
   eQMI_CALL_END_REASON_UNKNOWN_APN,               // 1013
   eQMI_CALL_END_REASON_UNKNOWN_PDP,               // 1014
   eQMI_CALL_END_REASON_GGSN_REJECT,               // 1015
   eQMI_CALL_END_REASON_ACTIVATION_REJECT,         // 1016
   eQMI_CALL_END_REASON_OPTION_NOT_SUPPORTED,      // 1017
   eQMI_CALL_END_REASON_OPTION_UNSUBSCRIBED,       // 1018
   eQMI_CALL_END_REASON_QOS_NOT_ACCEPTED,          // 1019
   eQMI_CALL_END_REASON_TFT_SEMANTIC_ERROR,        // 1020
   eQMI_CALL_END_REASON_TFT_SYNTAX_ERROR,          // 1021
   eQMI_CALL_END_REASON_UNKNOWN_PDP_CONTEXT,       // 1022
   eQMI_CALL_END_REASON_FILTER_SEMANTIC_ERROR,     // 1023
   eQMI_CALL_END_REASON_FILTER_SYNTAX_ERROR,       // 1024
   eQMI_CALL_END_REASON_PDP_WITHOUT_ACTIVE_TFT,    // 1025
   eQMI_CALL_END_REASON_INVALID_TRANSACTION_ID,    // 1026
   eQMI_CALL_END_REASON_MESSAGE_SEMANTIC_ERROR,    // 1027
   eQMI_CALL_END_REASON_INVALID_MANDATORY_INFO,    // 1028
   eQMI_CALL_END_REASON_TYPE_UNSUPPORTED,          // 1029
   eQMI_CALL_END_REASON_MSG_TYPE_WRONG_FOR_STATE,  // 1030
   eQMI_CALL_END_REASON_UNKNOWN_INFO_ELEMENT,      // 1031
   eQMI_CALL_END_REASON_CONDITIONAL_IE_ERROR,      // 1032
   eQMI_CALL_END_REASON_MSG_WRONG_FOR_PROTOCOL,    // 1033
   eQMI_CALL_END_REASON_APN_TYPE_CONFLICT,         // 1034
   eQMI_CALL_END_REASON_NO_GPRS_CONTEXT,           // 1035
   eQMI_CALL_END_REASON_FEATURE_NOT_SUPPORTED,     // 1036

   // CDMA 1xEV-DO (HDR)
   eQMI_CALL_END_REASON_CD_GEN_OR_BUSY = 1500,     // 1500
   eQMI_CALL_END_REASON_CD_BILL_OR_AUTH,           // 1501
   eQMI_CALL_END_REASON_CHG_HDR,                   // 1502
   eQMI_CALL_END_REASON_EXIT_HDR,                  // 1503
   eQMI_CALL_END_REASON_HDR_NO_SESSION ,           // 1504
   eQMI_CALL_END_REASON_HDR_ORIG_DURING_GPS_FIX,   // 1505
   eQMI_CALL_END_REASON_HDR_CS_TIMEOUT ,           // 1506
   eQMI_CALL_END_REASON_HDR_RELEASED_BY_CM,        // 1507

   eQMI_CALL_END_REASON_END
};

/*************
 *
 * Name:    eQMITlvCommon
 *
 * Purpose: enumerated common TLV operation codes
 *
 * Members:
 *
 * Notes:
 *
 **************/
enum eQMITlvCommon
{
    eTLV_RESULT_CODE  = 0x02,
    eTLV_TYPE_INVALID = 0xFF
};

/*************
 *
 * Name:    eQMITlvCommonLength
 *
 * Purpose: Common TLV Length codes for responses/indications
 *
 * Members:
 *
 * Notes:
 *
 **************/
enum eQMITlvCommonLength
{
    eTLV_LENGTH_VARIABLE = -1
};

/*************
 *
 * Name:    eQMITimeout
 *
 * Purpose: enumerated timeout values used for call to APIs.
 *
 * Members:
 *
 * Notes:   Don't change the order or the enumeration of this list
 *
 **************/
enum eQMITimeout
{
    eQMI_TIMEOUT_2_S        = 2000,
    eQMI_TIMEOUT_5_S        = 5000,
    eQMI_TIMEOUT_8_S        = 8000,
    eQMI_TIMEOUT_10_S       = 10000,
    eQMI_TIMEOUT_20_S       = 20000,
    eQMI_TIMEOUT_30_S       = 30000,
    eQMI_TIMEOUT_60_S       = 60000,
    eQMI_TIMEOUT_120_S      = 120000,
    eQMI_TIMEOUT_300_S      = 300000,
    eQMI_TIMEOUT_DEFAULT    = eQMI_TIMEOUT_8_S
};

/*************
 *
 * Name:    qmTBuffer
 *
 * Purpose: QM pack/unpack helper structure
 *
 * Members: Size        - Maximum size of QMI request/response Value (TLVs)
 *          Index       - QMI request/response Message buffer index used during pack/unpack
 *          Datap       - pointer to QMI message Value buffer (TLVs) for pack/unpack
 *
 * Notes:
 *
 **************/
struct qmTBuffer
{
    swi_uint16  Size;  /* Max number of swi_uint8s in data */
    swi_uint16  Index; /* Location wrt start of data for next read */
    swi_uint8   *Datap; /* pointer to contiguous data */
    swi_uint16  tlvLen;
    swi_uint8   tlvIdx;
};

/*************
 *
 * Name:    qmMessage
 *
 * Purpose: QMI service request message structure
 *
 * Members: MessageID   - QMI Message ID
 *          Length      - QMI Message Value length
 *          Bufferp     - pointer to QMI message Value (TLVs)
 *
 * Notes:
 *
 **************/
struct qmMessage
{
    swi_uint16          MessageId;
    swi_uint16          Length;
    struct qmTBuffer    *Bufferp;
};

/*************
 *
 * Name:    qmTlvBuilderItem
 *
 * Purpose: QM Builder message information
 *
 * Members: tlvType     - QMI Message TLV's Type field value
 *          Builder     - Function invoked to pack the QMI message TLV for the
 *                        specified TLV Type.
 *
 * Notes:
 *
 **************/
struct qmTlvBuilderItem
{
    swi_uint8         tlvType;
    enum eQCWWANError (*Builder)(swi_uint8*, swi_uint8*);
};

/*************
 *
 * Name:    qmTlvUnpackerItem
 *
 * Purpose: QM Unpack message information
 *
 * Members: tlvType     - QMI Message TLV's Type field value
 *          Unpackere   - Function invoked to unpack the QMI message TLV for
 *                        the specified TLV Type.
 *
 * Notes:
 *
 **************/
struct qmTlvUnpackerItem
{
    swi_uint8         tlvType;
    enum eQCWWANError (*Unpacker)(swi_uint8*, swi_uint8*) ;
};

#include "qm/qmuproto.h"

void qaSetDeviceState(swi_uint8 state);

#endif /* QMUDEFS_H */
