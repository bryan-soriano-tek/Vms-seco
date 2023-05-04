#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/sysinfo.h>
#include <limits.h>

#include <fcntl.h>
#include <stdbool.h>
#include "lite-fw.h"

#pragma once

#define VERSION_STRING      "1.0.2211.2\0"

#define QMI_MSG_MAX         2048
#define MAX_LINE_LEN        512
#define PID_NAME_SIZE       64

#define QMI_GET_SERVICE_FILE_IOCTL  0x8BE0 + 1

#define DEFAULT_SYNC_REQ_DELAY  1   // HSWOEMP-2205: 1-second delay

void litefw_syslog_proxy(uint8_t lvl, const char *buff, ...);

/*  MBIM declarations */

struct mbim_header {
  uint32_t type;
  uint32_t length;
  uint32_t transaction_id;
} __attribute__((packed));

#define MBIM_MESSAGE_GET_MESSAGE_TYPE(self)                             \
    (MbimMessageType) GUINT32_FROM_LE (((struct header *)(self->data))->type)
#define MBIM_MESSAGE_GET_MESSAGE_LENGTH(self)                           \
    GUINT32_FROM_LE (((struct header *)(self->data))->length)
#define MBIM_MESSAGE_GET_TRANSACTION_ID(self)                           \
    GUINT32_FROM_LE (((struct header *)(self->data))->transaction_id)

struct mbim_open_message {
    uint32_t max_control_transfer;
} __attribute__((packed));

struct mbim_open_done_message {
    uint32_t status_code;
} __attribute__((packed));

struct mbim_error_message {
    uint32_t error_status_code;
} __attribute__((packed));

struct mbim_fragment_header {
  uint32_t total;
  uint32_t current;
} __attribute__((packed));

struct mbim_command_message {
    struct mbim_fragment_header fragment_header;
    uint8_t                 service_id[16];
    uint32_t                command_id;
    uint32_t                command_type;
    uint32_t                buffer_length;
} __attribute__((packed));

struct mbim_command_done_message {
    struct mbim_fragment_header fragment_header;
    uint8_t                 service_id[16];
    uint32_t                command_id;
    uint32_t                status_code;
    uint32_t                buffer_length;
} __attribute__((packed));


/* MBIM full message struct */
struct mbim_full_message {
    struct mbim_header header;
    union {
        struct mbim_open_message            open;
        struct mbim_open_done_message       open_done;
        struct mbim_command_message         command;
        struct mbim_command_done_message    command_done;
        struct mbim_error_message           error;
    } message;
} __attribute__((packed));


/**
 * MbimMessageType:
 * MBIM_MESSAGE_TYPE_INVALID: Invalid MBIM message.
 * MBIM_MESSAGE_TYPE_OPEN: Initialization request.
 * MBIM_MESSAGE_TYPE_CLOSE: Close request.
 * MBIM_MESSAGE_TYPE_COMMAND: Command request.
 * MBIM_MESSAGE_TYPE_HOST_ERROR: Host-reported error in the communication.
 * MBIM_MESSAGE_TYPE_OPEN_DONE: Response to initialization request.
 * MBIM_MESSAGE_TYPE_CLOSE_DONE: Response to close request.
 * MBIM_MESSAGE_TYPE_COMMAND_DONE: Response to command request.
 * MBIM_MESSAGE_TYPE_FUNCTION_ERROR: Function-reported error in the communication.
 * MBIM_MESSAGE_TYPE_INDICATE_STATUS: Unsolicited message from the function.
 *
 * Type of MBIM messages.
 */
typedef enum {
    MBIM_MESSAGE_TYPE_INVALID         = 0x00000000,
    /* From Host to Function */
    MBIM_MESSAGE_TYPE_OPEN            = 0x00000001,
    MBIM_MESSAGE_TYPE_CLOSE           = 0x00000002,
    MBIM_MESSAGE_TYPE_COMMAND         = 0x00000003,
    MBIM_MESSAGE_TYPE_HOST_ERROR      = 0x00000004,
    /* From Function to Host */
    MBIM_MESSAGE_TYPE_OPEN_DONE       = 0x80000001,
    MBIM_MESSAGE_TYPE_CLOSE_DONE      = 0x80000002,
    MBIM_MESSAGE_TYPE_COMMAND_DONE    = 0x80000003,
    MBIM_MESSAGE_TYPE_FUNCTION_ERROR  = 0x80000004,
    MBIM_MESSAGE_TYPE_INDICATE_STATUS = 0x80000007
} MbimMessageType;


/**
 * MbimCidQmi:
 * MBIM_CID_QMI_UNKNOWN: Unknown command.
 * MBIM_CID_QMI_MSG: Configuration.
 *
 * MBIM command id for QMI service.
 */
typedef enum {
    MBIM_CID_QMI_UNKNOWN = 0,
    MBIM_CID_QMI_MSG     = 1
} MbimCidQmi;


/**
 * MbimMessageCommandType:
 * MBIM_MESSAGE_COMMAND_TYPE_UNKNOWN: Unknown type.
 * MBIM_MESSAGE_COMMAND_TYPE_QUERY: Query command.
 * MBIM_MESSAGE_COMMAND_TYPE_SET: Set command.
 *
 * Type of command message.
 */
typedef enum {
    MBIM_MESSAGE_COMMAND_TYPE_UNKNOWN = -1,
    MBIM_MESSAGE_COMMAND_TYPE_QUERY   = 0,
    MBIM_MESSAGE_COMMAND_TYPE_SET     = 1
} MbimMessageCommandType;

