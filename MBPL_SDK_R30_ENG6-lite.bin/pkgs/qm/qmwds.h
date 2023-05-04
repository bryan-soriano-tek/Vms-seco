/*************
 *
 * Filename: qmwds.h
 *
 * Purpose:  QMI Wireless Device Service user types
 *
 * Copyright: © 2014 Sierra Wireless Inc., all rights reserved
 *
 **************/

#ifndef QMWDS_H
#define QMWDS_H

/*************
 *
 * Name:    qm_wds_set_session_id_request_tlv_values
 *
 * Purpose: QMI WDS set session id request structure used for unpacking
 *          the QMI request sent by the user application.
 *
 * Members: sessionID  - session ID
 *          instanceID - instance ID
 *
 * Notes:
 *
 **************/
struct qm_wds_set_session_id_request_tlv_values{
    swi_uint32 sessionID;
    swi_uint8  instanceID;
};

/*************
 *
 * Name:    qm_wds_get_instance_id_request_tlv_values
 *
 * Purpose: QMI WDS get instance id request structure used for unpacking
 *          the QMI request sent by the user application.
 *
 * Members: sessionID - session ID
 *
 * Notes:
 *
 **************/
struct qm_wds_get_instance_id_request_tlv_values{
    swi_uint32 sessionID;
};

/*************
 *
 * Name:    qm_wds_get_instance_id_response_tlv_values
 *
 * Purpose: QMI WDS get instance id response structure used for packing
 *          the QMI response sent by the SDK process.
 *
 * Members: instanceID - Instance ID
 *          IPFamily - Indicates if the modem is 9x15 or not
 *          imgMask   - Bit mask describing requested images for dwnld
 *
 * Notes:
 *
 **************/
struct qm_wds_get_instance_id_response_tlv_values{
    swi_uint8  instanceID;
    swi_uint8  IPFamily;
};

/*************
 *
 * Name:    qm_wds_get_session_id_request_tlv_values
 *
 * Purpose: QMI WDS get session id request structure used for unpacking
 *          the QMI request sent by the user application.
 *
 * Members: instanceID - instance ID
 *
 * Notes:
 *
 **************/
struct qm_wds_get_session_id_request_tlv_values{
    swi_uint8 instanceID;
};

/*************
 *
 * Name:    qm_wds_get_session_id_response_tlv_values
 *
 * Purpose: QMI WDS get session id response structure used for unpacking
 *          the QMI request sent by the user application.
 *
 * Members: sessionIDv4 - IPv4 session ID
 *          sessionIDv6 - IPv6 session ID
 *
 * Notes:
 *
 **************/
struct qm_wds_get_session_id_response_tlv_values{
    swi_ulong sessionIDv4;
    swi_ulong sessionIDv6;
};

/*************
 *
 * Name:    qm_qmi_wds_tlv_values
 *
 * Purpose: Union of QMI TLV Value Structures to generalize the TLV
 *          construction of QMI WDS service responses.
 *
 * Members: set_session_id_req - set session id request structure
 *          get_instance_id_req - get instance id request structure
 *          get_instance_id_resp - get instance id response structure
 *          get_session_id_req - get session id request structure
 *          get_session_id_resp - get session id response structure
 *
 * Notes:
 *
 **************/
union qm_qmi_wds_tlv_values{
    struct qm_wds_set_session_id_request_tlv_values   set_session_id_req;
    struct qm_wds_get_instance_id_request_tlv_values  get_instance_id_req;
    struct qm_wds_get_instance_id_response_tlv_values get_instance_id_resp;
    struct qm_wds_get_session_id_request_tlv_values   get_session_id_req;
    struct qm_wds_get_session_id_response_tlv_values  get_session_id_resp;
};
#endif /* QMWDS_H */
