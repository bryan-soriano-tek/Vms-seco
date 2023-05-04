/*************
 *
 * Filename: qmdcs.h
 *
 * Purpose:  QMI Device Connectivity Service user types
 *
 * Copyright: © 2010 Sierra Wireless Inc., all rights reserved
 *
 **************/

#ifndef QMDCS_H
#define QMDCS_H
#include <sys/types.h>
#include "os/swi_ossdk.h"
#include "qm/qmudefs.h"

#define MAX_QOS_MAP (8)

/* User defined types */
/*************
 *
 * Name:    qm_dcs_deviceinfo
 *
 * Purpose: QMI device information
 *
 * Members: pdevnode        - QMI device path
 *          pdevkey         - connected device ID
 *          devnodestrsize  - length of QMI device path
 *          devkeystrsize   - length of device key
 *
 * Notes:   none
 *
 **************/
struct qm_dcs_deviceinfo{
    swi_uint8  devnode[QMI_DEVICE_PATH_MAX_SIZE];
    swi_uint8  devkey[QMI_MEID_BUF_SIZE];
    swi_uint16 devnodestrsize;
    swi_uint16 devkeystrsize;
};

/*************
 *
 * Name:    qm_dcs_usb_port_names
 *
 * Purpose: QMI USB port names information
 *
 * Members: AtCmdPort - AT cmd port name
 *          NmeaPort  - NMEA port name
 *          DmPort    - DM port name
 *
 * Notes:   none
 *
 **************/
struct qm_dcs_usb_port_names
{
    swi_char AtCmdPort[QMI_USB_PORT_NAME_SIZE];
    swi_char NmeaPort [QMI_USB_PORT_NAME_SIZE];
    swi_char DmPort   [QMI_USB_PORT_NAME_SIZE];
};

struct qm_dcs_net_tlv_values
{
    swi_ulong   q_depth;
    swi_uint8    isThrottle;
    swi_uint8    instanceId;
};

/*************
 *
 * Name:    qm_dcs_device_state_change_tlv_values
 *
 * Purpose: QMI DCS notification structure used for building the QMI
 *          notification being sent to the user application on a device state
 *          change or in response to the SLQSGetDeviceMode API.
 *
 * Members: devstate   - device state
 *
 * Notes:
 *
 **************/
struct qm_dcs_device_state_change_tlv_values
{
    swi_uint8   devstate;
};

struct qm_dcs_qmap_supported_tlv_values
{
    swi_uint8  isQmapSupported;
};

#define DCS_IPV6_ADDR_LEN 16
struct sipv6_addr
{
    swi_uint8 ipv6Address[DCS_IPV6_ADDR_LEN];
    swi_uint8 prefix_len;
};

struct qm_dcs_qmap_set_ip_table_tlv_values
{
    swi_uint8 muxId;
    swi_uint32 ipAddress;
    struct sipv6_addr ipv6addr;
};

/*************
 *
 * Name:    qm_dcs_sdk_terminated_tlv_values
 *
 * Purpose: QMI SDK notification structure used for building the QMI
 *          notification being sent to the user application in response to the
 *          SDK termination events.
 *
 * Members: reason   - String containing reason
 *
 * Notes:
 *
 **************/
struct qm_dcs_sdk_terminated_tlv_values
{
    swi_uint8   reason[128];
};

/*************
 *
 * Name:    qm_dcs_start_srv_tlv_values
 *
 * Purpose: QMI SDK notification structure used for building the QMI
 *          notification being sent to the user application in response to the
 *          Start service request.
 *
 * Members: reason   - String containing reason
 *
 * Notes:
 *
 **************/
struct qm_dcs_start_srv_tlv_values
{
    swi_uint8 srvStatus;
    swi_uint8 mask;
};

/*************
 *
 * Name:    qm_dcs_set_logging_mask_tlv_values
 *
 * Purpose: QMI SDK notification structure used for building the QMI
 *          notification being sent to the user application in response to the
 *          Disable Syslog request.
 *
 * Members: level   - level to limit syslogs
 *
 * Notes:
 *
 **************/
struct qm_dcs_set_logging_mask_tlv_values
{
    swi_uint8 level;
};

struct qm_dcs_qos_map_tlv_values
{
    swi_uint8 dscp;
    swi_uint32 qos_id;
    swi_uint8 state;
};

struct qm_dcs_set_net_change_tlv_values
{
    swi_uint32 hiMark;
    swi_uint32 loMark;
    swi_uint32 period;
};

/*************
 *
 * Name:    qm_dcs_cancel_response_parms
 *
 * Purpose: QMI DCS Cancel Response Structure used for building
 *          the QMI response returned to the user application making the
 *          request.
 *
 * Members: none
 *
 * Notes:
 *
 **************/
struct qm_dcs_cancel_response_tlv_values{
};

/*************
 *
 * Name:    qm_dcs_connected_deviceid_response_tlv_values
 *
 * Purpose: QMI DCS Connected Device ID Response Structure used for building
 *          the QMI response returned to the user application making the
 *          request.
 *
 * Members: (IN) pdevice    - device information
 *
 * Notes:
 *
 **************/
struct qm_dcs_connected_deviceid_response_tlv_values{
    struct qm_dcs_deviceinfo *pdevice;
};

/*************
 *
 * Name:    qm_dcs_disconnect_response_tlv_values
 *
 * Purpose: QMI DCS  Disconnect Response Structure used for building
 *          the QMI response returned to the user application making the
 *          request.
 *
 * Members: none
 *
 * Notes:
 *
 **************/
struct qm_dcs_disconnect_response_tlv_values{
};

/*************
 *
 * Name:    qm_dcs_connect_request_args
 *
 * Purpose: QMI device information
 *
 * Members: (IN) pdevnode   - QMI device path
 *          (IN) pdevkey    - connected device ID
 *
 * Notes:   none
 *
 **************/
struct qm_dcs_connect_request_args
{
    swi_char *pdevnode;
    swi_char *pdevkey;
};

/*************
 *
 * Name:    qm_dcs_start_srv_request_args
 *
 * Purpose: QMI device information
 *
 * Members: (IN) action
 *          (IN) mask
 *
 * Notes:   none
 *
 **************/
struct qm_dcs_start_srv_request_args
{
    swi_char action;
    swi_char mask;
};

/*************
 *
 * Name:    qm_dcs_set_logging_mask_request_args
 *
 * Purpose: QMI device information
 *
 * Members: (IN) level
 *
 * Notes:   none
 *
 **************/
struct qm_dcs_set_logging_mask_request_args
{
    swi_int8 level;
};

struct qm_dcs_qos_map_args
{
    swi_char dscp;
    swi_ulong qos_id;
};

/*************
 *
 * Name:    qm_dcs_connect_response_tlv_values
 *
 * Purpose: QMI DCS Connect Response Structure used for building
 *          the QMI response returned to the user application making the
 *          request.
 *
 * Members: dev - device information
 *
 * Notes:
 *
 **************/
struct qm_dcs_connect_response_tlv_values{
    struct qm_dcs_deviceinfo dev;
    pid_t sdk_pid;
};

/*************
 *
 * Name:    qm_dcs_enumerate_devices_response_tlv_values
 *
 * Purpose: QMI DCS Enumerate Devices Response Structure used for building
 *          the QMI response returned to the user application making the
 *          request.
 *
 * Notes:
 *
 **************/
struct qm_dcs_enumerate_devices_response_tlv_values{
    struct qm_dcs_deviceinfo dev;
};

/*************
 *
 * Name:    qm_dcs_usb_port_names_response_tlv_values
 *
 * Purpose: QMI DCS Get Usb Port Names Response Structure used for building
 *          the QMI response returned to the user application making the
 *          request.
 *
 * Members: (IN) pusbportnames    - port names
 *
 * Notes:
 *
 **************/
struct qm_dcs_usb_port_names_response_tlv_values{
    struct qm_dcs_usb_port_names usbportnames;
};

struct qm_dcs_get_net_stats_tlv_values {
   swi_uint32 rx_packets;
   swi_uint32 tx_packets;
   swi_uint64 rx_bytes;
   swi_uint64 tx_bytes;
   swi_uint32 rx_errors;
   swi_uint32 tx_errors;
   swi_uint32 rx_overflows;
   swi_uint32 tx_overflows;
};

/*************
 *
 * Name:    sNetStats
 *
 * Purpose: This struct will be used to get the ioctrl value, then struct
 *          qm_dcs_get_net_stats_tlv_values will copy the values from
 *          this struct, the reason is that the size of unsigned int is not same 
 *          as the size of swi_ulong in 64bit architecture
 *
 **************/
typedef struct {
   unsigned int rx_packets;
   unsigned int tx_packets;
   swi_uint64   rx_bytes;
   swi_uint64   tx_bytes;
   unsigned int rx_errors;
   unsigned int tx_errors;
   unsigned int rx_overflows;
   unsigned int tx_overflows;
}sNetStats;

/*************
 *
 * Name:    qm_qmi_dcs_tlv_values
 *
 * Purpose: Union of QMI TLV Value Structures to generalize the TLV
 *          construction of QMI DCS service responses.
 *
 * Members: enumerate           - enumerate response structure
 *          connect             - connect response structure
 *          disconnect          - disconnect response structure
 *          connecteddevid      - connecteddevid response structure
 *          cancel              - cancel response structure
 *          devstatechgnotif    - device state change notification
 *          portnames           - USB port names structure
 *          devicestate         - Device mode value
 *          mtu                 - Host MTU value
 * Notes:
 *
 **************/
union qm_qmi_dcs_tlv_values{
    struct qm_dcs_enumerate_devices_response_tlv_values     enumerate;
    struct qm_dcs_connect_response_tlv_values               connect;
    struct qm_dcs_disconnect_response_tlv_values            disconnect;
    struct qm_dcs_connected_deviceid_response_tlv_values    connecteddevid;
    struct qm_dcs_cancel_response_tlv_values                cancel;
    struct qm_dcs_device_state_change_tlv_values            devstatechgnotif;
    struct qm_dcs_usb_port_names_response_tlv_values        portnames;
    struct qm_dcs_device_state_change_tlv_values            devicestate;
    struct qm_dcs_sdk_terminated_tlv_values                 sdktermination;
    struct qm_dcs_start_srv_tlv_values                      StartSrv;
    struct qm_dcs_net_tlv_values                            netNotif;
    struct qm_dcs_qos_map_tlv_values                        qosMap;
    struct qm_dcs_qos_map_tlv_values                        qosMaps[MAX_QOS_MAP];
    struct qm_dcs_set_net_change_tlv_values                 netChange;
    struct qm_dcs_set_logging_mask_tlv_values               setloggingmask;
    struct qm_dcs_get_net_stats_tlv_values                  netStats;
    struct qm_dcs_qmap_supported_tlv_values                 qmapSupported;
    struct qm_dcs_qmap_set_ip_table_tlv_values              qmapTable;
};

#endif /* QMDCS_H */

