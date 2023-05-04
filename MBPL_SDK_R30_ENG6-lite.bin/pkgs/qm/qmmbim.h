/*************
 *
 * Filename: qmmbim.h
 *
 * Purpose:  QMI over MBIM type interface
 *
 * Copyright: © 2018 Sierra Wireless Inc., all rights reserved
 *
 **************/

#ifndef QMMBIM_H
#define QMMBIM_H

/*-------
  Defines
 --------*/
#define MBIM_MESSAGE_FRAGEMET_HEADER_TOTAL_LENGTH       4
#define MBIM_MESSAGE_FRAGEMET_HEADER_CURRENT_LENGTH     4
#define MBIM_MESSAGE_FRAGEMET_HEADER_LENGTH             MBIM_MESSAGE_FRAGEMET_HEADER_TOTAL_LENGTH +\
                                                        MBIM_MESSAGE_FRAGEMET_HEADER_CURRENT_LENGTH
#define MBIM_MESSAGE_CMD_HEADER_SERVICE_ID_LENGTH 16
#define MBIM_MESSAGE_CMD_HEADER_CMD_LENGTH 4
#define MBIM_MESSAGE_CMD_HEADER_STATUS_LENGTH 4
#define MBIM_MESSAGE_CMD_HEADER_BUFFER_LENGTH 4


#define MBIM_DATA_DEBUG                   1

#define QMI_TYPE_RESP                     0x80
#define QMI_HDR_LEN                       6
#define QMI_MSG_MAX                       1024
#define MBIM_MSG_MAX                      1024

#define MBIM_OPEN_RSP_SIZE                256

#define MBIM_COMMON_HEADER_LEN            12
#define MBIM_MESSAGE_FRAGEMET_HEADER_TOTAL_LENGTH       4
#define MBIM_MESSAGE_FRAGEMET_HEADER_CURRENT_LENGTH     4
#define MBIM_MESSAGE_FRAGEMET_HEADER_LENGTH             MBIM_MESSAGE_FRAGEMET_HEADER_TOTAL_LENGTH +\
                                              MBIM_MESSAGE_FRAGEMET_HEADER_CURRENT_LENGTH
#define MBIM_MESSAGE_CMD_HEADER_SERVICE_ID_LENGTH       16
#define MBIM_MESSAGE_CMD_HEADER_CMD_LENGTH              4
#define MBIM_MESSAGE_CMD_HEADER_STATUS_LENGTH           4
#define MBIM_MESSAGE_CMD_HEADER_BUFFER_LENGTH           4

#define MBIM_MESSAGE_CMD_TYPE_HDR_LEN                   MBIM_MESSAGE_FRAGEMET_HEADER_LENGTH +\
                 MBIM_MESSAGE_CMD_HEADER_SERVICE_ID_LENGTH + MBIM_MESSAGE_CMD_HEADER_CMD_LENGTH+\
                 MBIM_MESSAGE_CMD_HEADER_STATUS_LENGTH + MBIM_MESSAGE_CMD_HEADER_BUFFER_LENGTH

#define MBIM_CMD_MSG_HDR_LEN              MBIM_COMMON_HEADER_LEN + MBIM_MESSAGE_CMD_TYPE_HDR_LEN

#define MBIM_IND_MSG_HDR_LEN              44


#define MBIM_QMI_SDU_HDR_INDEX            QMI_HDR_LEN + MBIM_CMD_MSG_HDR_LEN
#define MAX_MBIM_CONTROL_TRANSFER_SIZE    0x00001000
#define MBIM_INDEX_OPEN_DONE_STATUS_CODE  12
#define MBIM_TRANSACTION_ID_INVALID       0
#define MBIM_HDR_LENGTH_DATA_INDEX        4
#define MBIM_HDR_XID_DATA_INDEX           8
#define MBIM_HDR_QMI_UUID_DATA_INDEX      20
#define MBIM_HDR_CMD_ID_INDEX             36
#define MBIM_HDR_STATUSCODE_DATA_INDEX    40
#define MBIM_HDR_CMDLENGTH_DATA_INDEX     44
#define MBIM_HDR_INDLENGTH_DATA_INDEX     40
#define MBIM_HDR_QMI_UUID_LENGTH          16


#define MBIM_QMI_HDR_SVCTYPE_INDEX        4
#define MBIM_QMI_HDR_CLIENTID_INDEX       5
#define MBIM_QMI_SDU_MIN_LEN              6 /* 6 for QMI CTL, 7 for other services */


#define MBIM_SVC_ID_LENGTH                             16
#define MBIM_INCREASE_INDEX_INT32_SIZE                 4
#define MBIM_BASIC_CONNECT_NUM_SVC_REGISTER            1
#define MBIM_BASIC_CONNECT_NUM_SVC_FIELDSIZE           4
#define MBIM_BASIC_CONNECT_SINGLE_SVC_DESC_SIZE        8
#define MBIM_BASIC_CONNECT_QMISVC_DATA_INDEX           MBIM_BASIC_CONNECT_NUM_SVC_FIELDSIZE +\
                                                  MBIM_BASIC_CONNECT_SINGLE_SVC_DESC_SIZE

#define MBIM_BASIC_CONNECT_NUM_QMI_CID                 1
#define MBIM_BASIC_CONNECT_NUM_QMI_CID_FIELDSIZE       4
#define MBIM_BASIC_CONNECT_QMI_CID_LIST_SIZE           4 * MBIM_BASIC_CONNECT_NUM_QMI_CID
#define MBIM_BASIC_CONNECT_QMISVC_DATA_SIZE            MBIM_SVC_ID_LENGTH +\
            MBIM_BASIC_CONNECT_NUM_QMI_CID_FIELDSIZE + MBIM_BASIC_CONNECT_QMI_CID_LIST_SIZE

#define QM_MBIM_PUT_UINT32_LE(p,val) \
    do{ \
        (p)[0] = (val); \
        (p)[1] = (val) >> 8; \
        (p)[2] = (val) >> 16; \
        (p)[3] = (val) >> 24; \
    } while(0)


#define QM_MBIM_GET_UINT32_LE(p,val) \
    do { \
       (val) = ((p)[0] | (((p)[1] << 8) & 0x0000ff00) | \
       (((p)[2] << 16) & 0x00ff0000) | (((p)[3] << 24) & 0xff000000)); \
    } while(0)

#define QM_MBIM_PUT_UINT16_LE(p,val) \
    do{ \
        (p)[0] = (val); \
        (p)[1] = (val) >> 8; \
    } while(0)


#define QM_MBIM_GET_UINT16_LE(p,val) \
    do { \
       (val) = ((p)[0] | (((p)[1] << 8) & 0xff00)); \
    } while(0)

/*  MBIM delcarations */
struct qm_mbim_header {
  swi_uint32 type;
  swi_uint32 length;
  swi_uint32 transaction_id;
} __attribute__((packed));

#define QM_MBIM_MESSAGE_GET_MESSAGE_TYPE(self)                             \
    (QmMbimMessageType) GUINT32_FROM_LE (((struct header *)(self->data))->type)
#define Qm_MBIM_MESSAGE_GET_MESSAGE_LENGTH(self)                           \
    GUINT32_FROM_LE (((struct header *)(self->data))->length)
#define QM_MBIM_MESSAGE_GET_TRANSACTION_ID(self)                           \
    GUINT32_FROM_LE (((struct header *)(self->data))->transaction_id)

struct qm_mbim_open_message {
    swi_uint32 max_control_transfer;
} __attribute__((packed));

struct qm_mbim_open_done_message {
    swi_uint32 status_code;
} __attribute__((packed));

struct qm_mbim_error_message {
    swi_uint32 error_status_code;
} __attribute__((packed));

struct qm_mbim_fragment_header {
  swi_uint32 total;
  swi_uint32 current;
} __attribute__((packed));

struct qm_mbim_command_message {
    struct qm_mbim_fragment_header fragment_header;
    swi_uint8                 service_id[16];
    swi_uint32                command_id;
    swi_uint32                command_type;
    swi_uint32                buffer_length;
} __attribute__((packed));

struct qm_mbim_command_done_message {
    struct qm_mbim_fragment_header fragment_header;
    swi_uint8                 service_id[16];
    swi_uint32                command_id;
    swi_uint32                status_code;
    swi_uint32                buffer_length;
} __attribute__((packed));

struct qm_mbim_indicate_status_message {
    struct qm_mbim_fragment_header fragment_header;
    swi_uint8                 service_id[16];
    swi_uint32                command_id;
    swi_uint32                buffer_length;
} __attribute__((packed));


/* MBIM full message struct */
struct qm_mbim_full_message {
    struct qm_mbim_header header;
    union {
        struct qm_mbim_open_message            open;
        struct qm_mbim_open_done_message       open_done;
        struct qm_mbim_command_message         command;
        struct qm_mbim_command_done_message    command_done;
        struct qm_mbim_indicate_status_message indicate_status;
        struct qm_mbim_error_message           error;
    } message;
} __attribute__((packed));


/**
 * QmMbimMessageType:
 * QM_MBIM_MESSAGE_TYPE_INVALID: Invalid MBIM message.
 * QM_MBIM_MESSAGE_TYPE_OPEN: Initialization request.
 * QM_MBIM_MESSAGE_TYPE_CLOSE: Close request.
 * QM_MBIM_MESSAGE_TYPE_COMMAND: Command request.
 * QM_MBIM_MESSAGE_TYPE_HOST_ERROR: Host-reported error in the communication.
 * QM_MBIM_MESSAGE_TYPE_OPEN_DONE: Response to initialization request.
 * QM_MBIM_MESSAGE_TYPE_CLOSE_DONE: Response to close request.
 * QM_MBIM_MESSAGE_TYPE_COMMAND_DONE: Response to command request.
 * QM_MBIM_MESSAGE_TYPE_FUNCTION_ERROR: Function-reported error in the communication.
 * QM_MBIM_MESSAGE_TYPE_INDICATE_STATUS: Unsolicited message from the function.
 *
 * Type of MBIM messages.
 */
typedef enum {
    QM_MBIM_MESSAGE_TYPE_INVALID         = 0x00000000,
    /* From Host to Function */
    QM_MBIM_MESSAGE_TYPE_OPEN            = 0x00000001,
    QM_MBIM_MESSAGE_TYPE_CLOSE           = 0x00000002,
    QM_MBIM_MESSAGE_TYPE_COMMAND         = 0x00000003,
    QM_MBIM_MESSAGE_TYPE_HOST_ERROR      = 0x00000004,
    /* From Function to Host */
    QM_MBIM_MESSAGE_TYPE_OPEN_DONE       = 0x80000001,
    QM_MBIM_MESSAGE_TYPE_CLOSE_DONE      = 0x80000002,
    QM_MBIM_MESSAGE_TYPE_COMMAND_DONE    = 0x80000003,
    QM_MBIM_MESSAGE_TYPE_FUNCTION_ERROR  = 0x80000004,
    QM_MBIM_MESSAGE_TYPE_INDICATE_STATUS = 0x80000007
} QmMbimMessageType;


/**
 * QmMbimCidQmi:
 * MBIM_CID_QMI_UNKNOWN: Unknown command.
 * MBIM_CID_QMI_MSG: Configuration.
 *
 * MBIM command id for QMI service.
 */
typedef enum {
    QM_MBIM_CID_QMI_UNKNOWN = 0,
    QM_MBIM_CID_QMI_MSG     = 1
} QmMbimCidQmi;

/**
 * QmMbimCidBasic:
 * QM_MBIM_CID_BASIC_CONNECT_UNKNOWN: Unknown command.
 * QM_MBIM_CID_BASIC_CONNECT_DEVICE_CAPS: Device capabilities.
 * QM_MBIM_CID_BASIC_CONNECT_SUBSCRIBER_READY_STATUS: Subscriber ready status.
 * QM_MBIM_CID_BASIC_CONNECT_RADIO_STATE: Radio state.
 * QM_MBIM_CID_BASIC_CONNECT_PIN: PIN.
 * QM_MBIM_CID_BASIC_CONNECT_PIN_LIST: PIN list.
 * QM_MBIM_CID_BASIC_CONNECT_HOME_PROVIDER: Home provider.
 * QM_MBIM_CID_BASIC_CONNECT_PREFERRED_PROVIDERS: Preferred providers.
 * QM_MBIM_CID_BASIC_CONNECT_VISIBLE_PROVIDERS: Visible providers.
 * QM_MBIM_CID_BASIC_CONNECT_REGISTER_STATE: Register state.
 * QM_MBIM_CID_BASIC_CONNECT_PACKET_SERVICE: Packet service.
 * QM_MBIM_CID_BASIC_CONNECT_SIGNAL_STATE: Signal state.
 * QM_MBIM_CID_BASIC_CONNECT_CONNECT: Connect.
 * QM_MBIM_CID_BASIC_CONNECT_PROVISIONED_CONTEXTS: Provisioned contexts.
 * QM_MBIM_CID_BASIC_CONNECT_SERVICE_ACTIVATION: Service activation.
 * QM_MBIM_CID_BASIC_CONNECT_IP_CONFIGURATION: IP configuration.
 * QM_MBIM_CID_BASIC_CONNECT_DEVICE_SERVICES: Device services.
 * QM_MBIM_CID_BASIC_CONNECT_DEVICE_SERVICE_SUBSCRIBE_LIST: Device service subscribe list.
 * QM_MBIM_CID_BASIC_CONNECT_PACKET_STATISTICS: Packet statistics.
 * QM_MBIM_CID_BASIC_CONNECT_NETWORK_IDLE_HINT: Network idle hint.
 * QM_MBIM_CID_BASIC_CONNECT_EMERGENCY_MODE: Emergency mode.
 * QM_MBIM_CID_BASIC_CONNECT_IP_PACKET_FILTERS: IP packet filters.
 * QM_MBIM_CID_BASIC_CONNECT_MULTICARRIER_PROVIDERS: Multicarrier providers.
 *
 * MBIM command id for Basic Connect Service.
 */
typedef enum {
    QM_MBIM_CID_BASIC_CONNECT_UNKNOWN                        = 0,
    QM_MBIM_CID_BASIC_CONNECT_DEVICE_CAPS                    = 1,
    QM_MBIM_CID_BASIC_CONNECT_SUBSCRIBER_READY_STATUS        = 2,
    QM_MBIM_CID_BASIC_CONNECT_RADIO_STATE                    = 3,
    QM_MBIM_CID_BASIC_CONNECT_PIN                            = 4,
    QM_MBIM_CID_BASIC_CONNECT_PIN_LIST                       = 5,
    QM_MBIM_CID_BASIC_CONNECT_HOME_PROVIDER                  = 6,
    QM_MBIM_CID_BASIC_CONNECT_PREFERRED_PROVIDERS            = 7,
    QM_MBIM_CID_BASIC_CONNECT_VISIBLE_PROVIDERS              = 8,
    QM_MBIM_CID_BASIC_CONNECT_REGISTER_STATE                 = 9,
    QM_MBIM_CID_BASIC_CONNECT_PACKET_SERVICE                 = 10,
    QM_MBIM_CID_BASIC_CONNECT_SIGNAL_STATE                   = 11,
    QM_MBIM_CID_BASIC_CONNECT_CONNECT                        = 12,
    QM_MBIM_CID_BASIC_CONNECT_PROVISIONED_CONTEXTS           = 13,
    QM_MBIM_CID_BASIC_CONNECT_SERVICE_ACTIVATION             = 14,
    QM_MBIM_CID_BASIC_CONNECT_IP_CONFIGURATION               = 15,
    QM_MBIM_CID_BASIC_CONNECT_DEVICE_SERVICES                = 16,
    /* 17, 18 reserved */
    QM_MBIM_CID_BASIC_CONNECT_DEVICE_SERVICE_SUBSCRIBE_LIST  = 19,
    QM_MBIM_CID_BASIC_CONNECT_PACKET_STATISTICS              = 20,
    QM_MBIM_CID_BASIC_CONNECT_NETWORK_IDLE_HINT              = 21,
    QM_MBIM_CID_BASIC_CONNECT_EMERGENCY_MODE                 = 22,
    QM_MBIM_CID_BASIC_CONNECT_IP_PACKET_FILTERS              = 23,
    QM_MBIM_CID_BASIC_CONNECT_MULTICARRIER_PROVIDERS         = 24,
} QmMbimCidBasic;


/**
 * QmMbimMessageCommandType:
 * QM_MBIM_MESSAGE_COMMAND_TYPE_UNKNOWN: Unknown type.
 * QM_MBIM_MESSAGE_COMMAND_TYPE_QUERY: Query command.
 * QM_MBIM_MESSAGE_COMMAND_TYPE_SET: Set command.
 *
 * Type of command message.
 */
typedef enum {
    QM_MBIM_MESSAGE_COMMAND_TYPE_UNKNOWN = -1,
    QM_MBIM_MESSAGE_COMMAND_TYPE_QUERY   = 0,
    QM_MBIM_MESSAGE_COMMAND_TYPE_SET     = 1
} QmMbimMessageCommandType;


/*********************
       Functions
**********************/
void qm_mbim_add_qmi_header(
     swi_uint8 *buf,
     swi_uint16 msgLen,
     swi_uint8 svc,
     swi_uint8 cliId);

void qm_mbim_create_mbimcmdmsg(swi_uint8 *mbimbuf, 
     swi_uint8 *qmibuf, 
     swi_ulong qmiLen, 
     swi_ulong cmd_type, 
     swi_ulong *pTotalLen);

swi_bool qm_mbim_validate_rcv_msg(
    swi_uint8 *mbim_msg, 
    swi_ulong msgLen);

swi_bool qm_mbim_parse_rcv_msg(
    swi_uint8 *mbim_msg, 
    swi_ulong msgLen);

swi_bool qm_mbim_verify_qmi_hdr_in_resp(
    swi_uint8 *qmi_rsp,
    swi_uint8 cliId,
    swi_uint8 svc);

swi_uint8
qmmbim_ctlsvcxidassign(
    swi_uint8 xactionid);

void qm_print_hex(
   void *      pBuffer,
   int    	   bufSize,
   int         type );


 
#endif /* QMMBIM_H */
