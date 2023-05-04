/**
 * \ingroup liteqmi
 * \ingroup qos
 * \file qos.h
 */

#ifndef __LITEQMI_QOS_H__
#define __LITEQMI_QOS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "common.h"
#include "msgid.h"

/**
* \ingroup qos
*
* LITEQMI_MAX_QOS_FLOW_PER_APN_STATS defined below
*/
#define LITEQMI_MAX_QOS_FLOW_PER_APN_STATS    10
/**
* \ingroup qos
*
* LITEQMI_MAX_QOS_FILTERS defined below
*/
#define LITEQMI_MAX_QOS_FILTERS               25
/**
* \ingroup qos
*
* LITEQMI_MAX_QOS_FLOWS defined below
*/
#define LITEQMI_MAX_QOS_FLOWS                  8
/**
 * \ingroup qos
 * 
 *  Function to pack command to retrieve QoS status of the network.
 *  This maps to SLQSQosGetNetworkStatus
 *
 *  \param[out]  pCtx
 *               - See \ref pack_qmi_t for more information
 *
 *  \param[in,out]  pReqBuf
 *                  - Buffer for packed QMI command to be provided by the host application
 *                  - Minimum expected size is 2048 bytes
 *
 *  \param[in,out]  pLen
 *                  - On input, size of pReqBuf
 *                  - On ouptut, number of bytes actually packed
 *		
 *  \return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  \sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 *  \note
 *          - Timeout: 2 seconds
 *          - Technology Supported: CDMA
 *          - PDN Specific: No
 */
int pack_qos_SLQSQosGetNetworkStatus (
        pack_qmi_t *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen
        ); 

/**
 * \ingroup qos
 * 
 *  Structure that contains the response to get NW QoS status command
 *  \param  NWQoSStatus
 *              Network QoS support status
 *              - 0 - No QoS support in network
 *              - 1 - Network supports QoS 
 *              - Bit to check in ParamPresenceMask - <B>1</B>
 *  \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct {
    uint8_t NWQoSStatus;
    swi_uint256_t  ParamPresenceMask;
} unpack_qos_SLQSQosGetNetworkStatus_t;

/**
 * \ingroup qos
 * 
 *  Function to unpack the response to get NW QoS status command
 *  This maps to SLQSQosGetNetworkStatus
 *
 *  \param[in]  pResp
 *              - Response from modem
 *
 *  \param[in]  respLen
 *              - Length of pResp from modem
 *
 *  \param[out]  pOutput
 *               - See \ref unpack_qos_SLQSQosGetNetworkStatus_t for more information
 *
 *  \return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  \sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int unpack_qos_SLQSQosGetNetworkStatus(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_qos_SLQSQosGetNetworkStatus_t *pOutput
        );

/**
 * \ingroup qos
 * 
 *  Structure that contains the APN ID to obtain extra APN parameters
 *  \param  apnId[IN]
 *          - APN id
 */
typedef struct {
    uint32_t apnId;
} pack_qos_SLQSQosSwiReadApnExtraParams_t;

/**
 * \ingroup qos
 * 
 *  Function to pack QMI command to query extra APN parameters 
 *  This maps to SLQSQosSwiReadApnExtraParams
 *
 *  \param[out]  pCtx
 *               - See \ref pack_qmi_t for more information
 *
 *  \param[in,out]  pReqBuf
 *                  - Buffer for packed QMI command to be provided by the host application
 *                  - Minimum expected size is 2048 bytes
 *
 *  \param[in,out]  pLen
 *                  - On input, size of pReqBuf
 *                  - On ouptut, number of bytes actually packed
 *		
 *  \param[in]  reqParam
 *              - See \ref pack_qos_SLQSQosSwiReadApnExtraParams_t for more information
 *
 *  \return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  \sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 *  \note   - Timeout: 2 seconds
 *          - PDN Specific: Yes
 * 
 *  \note   - This API is not supported by SWI 9x50 and newer devices 
 * 
 */
 int pack_qos_SLQSQosSwiReadApnExtraParams (
        pack_qmi_t *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen,
        pack_qos_SLQSQosSwiReadApnExtraParams_t  *reqParam 
        );

/**
 * \ingroup qos
 * 
 *  Structure that contains extra APN parameters
 *  \param  apnId
 *          - APN id
 *          - ID identifing the APN that the client would like to query the AMBR params
 *          - Bit to check in ParamPresenceMask - <B>3</B>
 *
 *  \param ambr_ul
 *          - APN AMBR uplink
 *          - APN AMBR uplink values from 1 kbps to 8640 kbps
 *          - Bit to check in ParamPresenceMask - <B>3</B>
 *
 *  \param ambr_dl
 *          - APN AMBR downlink
 *          - APN AMBR downlink values from 1 kbps to 8640 kbps
 *          - Bit to check in ParamPresenceMask - <B>3</B>
 *
 *  \param ambr_ul_ext
 *          - Extended APN AMBR uplink
 *          - APN AMBR uplink values from 8700 kbps  to 256 Mbps
 *          - Bit to check in ParamPresenceMask - <B>3</B>
 *
 *  \param ambr_dl_ext
 *          - Extended APN AMBR downlink
 *          - APN AMBR downlink values from 8700 kbps  to 256 Mbps
 *          - Bit to check in ParamPresenceMask - <B>3</B>
 *
 *  \param ambr_ul_ext2
 *          - Second extended APN AMBR uplink
 *          - APN AMBR uplink values from 256 Mbps to 65280 Mbps
 *          - Bit to check in ParamPresenceMask - <B>3</B>
 *
 *  \param ambr_dl_ext2
 *          - Second extended APN AMBR downlink
 *          - APN AMBR downlink values from 256 Mbps to 65280 Mbps
 *          - Bit to check in ParamPresenceMask - <B>3</B>
 *
 *  \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct {
    uint32_t    apnId;
    uint8_t     ambr_ul;
    uint8_t     ambr_dl;
    uint8_t     ambr_ul_ext;
    uint8_t     ambr_dl_ext;
    uint8_t     ambr_ul_ext2;
    uint8_t     ambr_dl_ext2;
    swi_uint256_t  ParamPresenceMask;
} unpack_qos_SLQSQosSwiReadApnExtraParams_t;

/**
 * \ingroup qos
 * 
 *  Function to unpack the response to get NW QoS status command
 *  This maps to SLQSQosSwiReadApnExtraParams
 *
 *  \param[in]  pResp
 *              - Response from modem
 *
 *  \param[in]  respLen
 *              - Length of pResp from modem
 *
 *  \param[out]  pOutput
 *               - See \ref unpack_qos_SLQSQosSwiReadApnExtraParams_t for more information
 *
 *  \return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  \sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 *  \note   - This API is not supported by SWI 9x50 and newer devices  
*/
int unpack_qos_SLQSQosSwiReadApnExtraParams(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_qos_SLQSQosSwiReadApnExtraParams_t *pOutput
        );

/**
 * \ingroup qos
 * 
 *  Structure that contains the APN ID to obtain data statistics
 *  \param  apnId[IN]
 *          - APN id
 */
typedef struct {
    uint32_t apnId;
} pack_qos_SLQSQosSwiReadDataStats_t;

/**
 * \ingroup qos
 * 
 *  Function to pack QMI command to query APN data statistics 
 *  This maps to SLQSQosSwiReadDataStats
 *
 *  \param[out]  pCtx
 *               - See \ref pack_qmi_t for more information
 *
 *  \param[in,out]  pReqBuf
 *                  - Buffer for packed QMI command to be provided by the host application
 *                  - Minimum expected size is 2048 bytes
 *
 *  \param[in,out]  pLen
 *                  - On input, size of pReqBuf
 *                  - On ouptut, number of bytes actually packed
 *
 *  \param[in]  reqParam
 *              - See \ref pack_qos_SLQSQosSwiReadDataStats_t for more information
 *
 *  \return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  \sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 *  \note   - Timeout: 2 seconds
 *          - PDN Specific: Yes
 * 
 *  \note   - This API is not supported by SWI 9x50 and newer devices  
 */
 int pack_qos_SLQSQosSwiReadDataStats (
        pack_qmi_t *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen,
        pack_qos_SLQSQosSwiReadDataStats_t  *reqParam 
        );

/**
 * \ingroup qos
 * 
 * This structure contains the Data statistic per QoS flow
 *
 *  \param  bearerId
 *          - Bearer ID
 *
 *  \param  tx_pkt
 *          - number of sent packets for the QoS flow ID
 *
 *  \param  tx_pkt_drp
 *          - number of dropped(TX) packets for the QoS flow ID
 *
 *  \param  tx_bytes
 *          - number of sent bytes for the QoS flow ID
 *
 *  \param  tx_bytes_drp
 *          - number of dropped(TX) bytes for the QoS flow ID
 */
typedef struct
{
    uint32_t   bearerId;
    uint32_t   tx_pkt;
    uint32_t   tx_pkt_drp;
    uint64_t   tx_bytes;
    uint64_t   tx_bytes_drp;
} unpack_QosFlowStat_t;
/**
 * \ingroup qos
 * 
 *  Structure that contains APN data statistics
 *  \param  apnId
 *          - APN id
 *          - ID identifing the connected APN that the client would like to query the data statistic for
 *          - Bit to check in ParamPresenceMask - <B>3</B>
 *
 *  \param  total_tx_pkt
 *          - sum of all packets sent
 *          - Bit to check in ParamPresenceMask - <B>3</B>
 *
 *  \param  total_tx_pkt_drp
 *          - sum of all(TX) packets dropped
 *          - Bit to check in ParamPresenceMask - <B>3</B>
 *
 *  \param  total_rx_pkt
 *          - sum of all packets received
 *          - Bit to check in ParamPresenceMask - <B>3</B>
 *
 *  \param  total_tx_bytes
 *          - sum of all bytes sent
 *          - Bit to check in ParamPresenceMask - <B>3</B>
 *
 *  \param  total_tx_bytes_drp
 *          - sum of all(TX) bytes dropped
 *          - Bit to check in ParamPresenceMask - <B>3</B>
 *
 *  \param  total_rx_bytes
 *          - number of received bytes for the QoS flow ID
 *          - Bit to check in ParamPresenceMask - <B>3</B>
 *
 *  \param  numQosFlow
 *          - pointer to number of QoS flow Stat
 *          - Bit to check in ParamPresenceMask - <B>4</B>
 *
 *  \param  qosFlow[LITEQMI_MAX_QOS_FLOW_PER_APN_STATS]
 *          - Data statistic per QoS flow
 *          - See \ref unpack_QosFlowStat_t for more information
 *          - See \ref LITEQMI_MAX_QOS_FLOW_PER_APN_STATS for more information
 *          - Bit to check in ParamPresenceMask - <B>4</B>
 *
 *  \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct {
    uint32_t             apnId;
    uint32_t             total_tx_pkt;
    uint32_t             total_tx_pkt_drp;
    uint32_t             total_rx_pkt;
    uint64_t             total_tx_bytes;
    uint64_t             total_tx_bytes_drp;
    uint64_t             total_rx_bytes;
    uint32_t             numQosFlow;
    unpack_QosFlowStat_t qosFlow[LITEQMI_MAX_QOS_FLOW_PER_APN_STATS];
    swi_uint256_t        ParamPresenceMask;
} unpack_qos_SLQSQosSwiReadDataStats_t;

/**
 * \ingroup qos
 * 
 *  Function to unpack APN data statistics response
 *  This maps to SLQSQosSwiReadDataStats
 *
 *  \param[in]  pResp
 *              - Response from modem
 *
 *  \param[in]  respLen
 *              - Length of pResp from modem
 *
 *  \param[out]  pOutput
 *               - See \ref unpack_qos_SLQSQosSwiReadDataStats_t for more information
 *
 *  \return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  \sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 *  \note   - This API is not supported by SWI 9x50 and newer devices  
 */
int unpack_qos_SLQSQosSwiReadDataStats(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_qos_SLQSQosSwiReadDataStats_t *pOutput
        );

/**
 * \ingroup qos
 * 
 *  Structure with network's QoS status
 *  \param  status
 *          Network QoS support status
 *          - 0x00 - Current network does not support QoS
 *          - 0x01 - Current network supports QoS
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 *  \note   - Technology Supported: CDMA 
 */
typedef struct {
    uint8_t status;
    swi_uint256_t  ParamPresenceMask;
} unpack_qos_SLQSSetQosNWStatusCallback_ind_t;

/**
 * \ingroup qos
 * 
 *  Function to unpack QoS NW status indication. 
 *  This maps to SLQSSetQosNWStatusCallback
 *
 *  \param[in]  pResp
 *              - Response from modem
 *
 *  \param[in]  respLen
 *              - Length of pResp from modem
 *
 *  \param[out]  pOutput
 *               - See \ref unpack_qos_SLQSSetQosNWStatusCallback_ind_t for more information
 *
 *  \return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  \sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 *  \note   
 *          - Technology Supported: CDMA 
 *          - This is a broadcast notification that is sent to the registered QoS service
 *          - No explicit function to register for this indication is needed
 *          - Please use eQMI_QOS_NETWORK_STATUS_IND indication to identify this event from QOS service read function
 */
int unpack_qos_SLQSSetQosNWStatusCallback_ind(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_qos_SLQSSetQosNWStatusCallback_ind_t *pOutput
        );

/**
 * \ingroup qos
 * 
 *  Structure with QoS status indication details
 *  \param  id
 *          - Index identifying the QoS flow whose status is being reported
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  \param  status
 *          Current QoS flow status:
 *          - 0x01 - QMI_QOS_STATUS_ACTIVATED
 *          - 0x02 - QMI_QOS_STATUS_SUSPENDED
 *          - 0x03 - QMI_QOS_STATUS_GONE
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  \param  event
 *          - 0x01 - QMI_QOS_ACTIVATED_EV
 *          - 0x02 - QMI_QOS_SUSPENDED_EV
 *          - 0x03 - QMI_QOS_GONE_EV
 *          - 0x04 - QMI_QOS_MODIFY_ACCEPTED_EV
 *          - 0x05 - QMI_QOS_MODIFY_REJECTED_EV
 *          - 0x06 - QMI_QOS_INFO_CODE_UPDATED_EV
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  \param  reason
 *          - 0x01 - QMI_QOS_INVALID_PARAMS
 *          - 0x02 - QMI_QOS_INTERNAL_CALL_ENDED
 *          - 0x03 - QMI_QOS_INTERNAL_ERROR
 *          - 0x04 - QMI_QOS_INSUFFICIENT_LOCAL_Resources
 *          - 0x05 - QMI_QOS_TIMED_OUT_OPERATION
 *          - 0x06 - QMI_QOS_INTERNAL_UNKNOWN_CAUSE_CODE
 *          - 0x07 - QMI_QOS_INTERNAL_MODIFY_IN_PROGRESS
 *          - 0x08 - QMI_QOS_NOT_SUPPORTED
 *          - 0x09 - QMI_QOS_NOT_AVAILABLE
 *          - 0x0A - QMI_QOS_NOT_GUARANTEED
 *          - 0x0B - QMI_QOS_INSUFFICIENT_NETWORK_RESOURCES
 *          - 0x0C - QMI_QOS_AWARE_SYSTEM
 *          - 0x0D - QMI_QOS_UNAWARE_SYSTEM
 *          - 0x0E - QOS_REJECTED_OPERATION
 *          - 0x0F - QMI_QOS_WILL_GRANT_WHEN_QOS_RESUMED
 *          - 0x10 - QMI_QOS_NETWORK_CALL_ENDED
 *          - 0x11 - QMI_QOS_NETWORK_SERVICE_NOT_AVAILABLE
 *          - 0x12 - QMI_QOS_NETWORK_L2_LINK_RELEASED
 *          - 0x13 - QMI_QOS_NETWORK_L2_LINK_REESTAB_REJ
 *          - 0x14 - QMI_QOS_NETWORK_L2_LINK_REESTAB_IND
 *          - 0x15 - QMI_QOS_NETWORK_UNKNOWN_CAUSE_CODE
 *          - 0x16 - QMI_NETWORK_BUSY
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct {
    uint32_t id;
    uint8_t  status;
    uint8_t  event;
    uint8_t  reason;
    swi_uint256_t  ParamPresenceMask;
} unpack_qos_SLQSSetQosStatusCallback_ind_t;

/**
 * \ingroup qos
 * 
 *  Function to unpack QoS status indications. 
 *  This maps to SLQSSetQosStatusCallback
 *
 *  \param[in]  pResp
 *              - Response from modem
 *
 *  \param[in]  respLen
 *              - Length of pResp from modem
 *
 *  \param[out]  pOutput
 *               - See \ref unpack_qos_SLQSSetQosStatusCallback_ind_t for more information
 *
 *  \return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  \sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 *  \note   
 *          - This is a broadcast notification that is sent to the registered QoS service
 *          - No explicit function to register for this indication is needed
 *          - Please use eQMI_QOS_FLOW_STATUS_IND indication to identify this event from QOS service read function
 */
int unpack_qos_SLQSSetQosStatusCallback_ind(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_qos_SLQSSetQosStatusCallback_ind_t *pOutput
        );

/**
 * \ingroup qos
 * 
 *  Structure with QoS primary flow events
 *  \param  event
 *          Event which causes this indication:
 *          - 0x0001 - Primary flow QoS modify operation success
 *          - 0x0002 - Primary flow QoS modify operation failure
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct {
    uint16_t  event;
    swi_uint256_t  ParamPresenceMask;
} unpack_qos_SLQSSetQosPriEventCallback_ind_t;

/**
 * \ingroup qos
 * 
 *  Function to unpack QoS primary flow events. 
 *  This maps to SLQSSetQosPriEventCallback
 *
 *  \param[in]  pResp
 *              - Response from modem
 *
 *  \param[in]  respLen
 *              - Length of pResp from modem
 *
 *  \param[out]  pOutput
 *               - See \ref unpack_qos_SLQSSetQosPriEventCallback_ind_t for more information
 *
 *  \return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  \sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 *  \note   
 *          - This is a broadcast notification that is sent to the registered QoS service
 *          - No explicit function to register for this indication is needed
 *          - Please use eQMI_QOS_PRIMARY_QOS_EVENT_IND indication to identify this event from QOS service read function
 *          - This is only generated when the primary flow is modified by the host
 */
int unpack_qos_SLQSSetQosPriEventCallback_ind(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_qos_SLQSSetQosPriEventCallback_ind_t *pOutput
        );

/**
 * \ingroup qos
 * 
 *  Structure that contains the Network-Supported QoS Profiles
 *  \param[in]  network_supported_qos_profile_change_reporting
 *          - Report network supported profile change.
 *           - Values:
 *              - 0 - Disable reporting
 *              - 1 - Enable reporting
 * 
 *  \param ext_technology_preference
 *          - Technology preference to be used while registering for network-supported QoS.
 *           - Values:
 *              - 0x8001 - CDMA
 *
 *  \param[in]  global_flow_reporting
 *          - Global flow reporting (Deprecated).
 *           - Values:
 *              - 0 - Disable reporting
 *              - 1 - Enable reporting
 * 
 */
typedef struct {
    uint8_t network_supported_qos_profile_change_reporting;
    uint16_t ext_technology_preference;
    uint8_t global_flow_reporting;
} pack_qos_SLQSSetQosEventCallback_t;

/**
 * \ingroup qos
 * 
 *  Function to pack QMI command to enable QoS event indications 
 *  This maps to SLQSSetQosEventCallback
 *
 *  \param[out]  pCtx
 *               - See \ref pack_qmi_t for more information
 *
 *  \param[in,out]  pReqBuf
 *                  - Buffer for packed QMI command to be provided by the host application
 *                  - Minimum expected size is 2048 bytes
 *
 *  \param[in,out]  pLen
 *                  - On input, size of pReqBuf
 *                  - On ouptut, number of bytes actually packed
 *
 *  \param[in]  reqParam
 *              - See \ref pack_qos_SLQSSetQosEventCallback_t for more information
 *
 *  \return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  \sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
 int pack_qos_SLQSSetQosEventCallback (
        pack_qmi_t *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen,
        pack_qos_SLQSSetQosEventCallback_t  *reqParam 
        );

/**
 *  This structure contains unpack QOS SLQSSetQosEventCallback.
 * \param Tlvresult
 *        - Unpack result.
 */
typedef struct {
    uint16_t       Tlvresult;
    swi_uint256_t   ParamPresenceMask;
}unpack_qos_SLQSSetQosEventCallback_t;
/**
 * \ingroup qos
 * 
 *  Function to unpack enable QoS event indications command's response
 *  This maps to SLQSSetQosEventCallback
 *
 *  \param[in]  pResp
 *              - Response from modem
 *
 *  \param[in]  respLen
 *              - Length of pResp from modem
 *
 *  \param[out]  pOutput
 *               - See \ref unpack_qos_SLQSSetQosEventCallback_t for more information
 *
 *  \return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  \sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int unpack_qos_SLQSSetQosEventCallback(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_qos_SLQSSetQosEventCallback_t *pOutput
        );

/**
 * \ingroup qos
 * 
 *  This structure contains QoS flow state
 *
 *  \param  id
 *          QoS identifier
 *
 *  \param  isNewFlow
 *          - 1 - Newly added flow
 *          - 0 - Existing flow
 *
 *  \param  state
 *          This indicates that the flow that was added/modified/deleted:
 *          - 0x01 - Flow activated
 *          - 0x02 - Flow modified
 *          - 0x03 - Flow deleted
 *          - 0x04 - Flow suspended
 *          - 0x05 - Flow enabled
 *          - 0x06 - Flow disabled
 */
typedef struct
{
    uint32_t   id;
    uint8_t    isNewFlow;
    uint8_t    state;
} unpack_qos_QosFlowInfoState_t;

/**
 * \ingroup qos
 * 
 * This structure contains the IP flow data rate min max
 *
 *  \param  dataRateMax
 *          Maximum required data rate (bits per second)
 *
 *  \param  guaranteedRate
 *          Minimum guaranteed data rate (bits per second)
 *
 */
typedef struct
{
    uint32_t   dataRateMax;
    uint32_t   guaranteedRate;
} unpack_qos_dataRate_t;

/**
 * \ingroup qos
 * 
 * This structure contains the TP flow data rate token bucket
 *
 *  \param  peakRate
 *          Maximum rate at which data can be transmitted when the token bucket is full (bits per second)
 *  \param  tokenRate
 *          Rate at which tokens will be put in the token bucket (bits per second); a token is required to be present in the bucket to send a byte of data
 *
 *  \param  bucketSz
 *          Maximum number of tokens that can be accumulated at any instance (bytes); controls the size of the burst that is allowed at any given time
 *
 */
typedef struct
{
    uint32_t   peakRate;
    uint32_t   tokenRate;
    uint32_t   bucketSz;
} unpack_qos_tokenBucket_t;

/**
 * \ingroup qos
 * 
 * This structure contains the IP flow packet error rate
 *
 *  \param  multiplier
 *          Factor m in calculating packet error rate:
 *          E = m*10**(-p)
 *
 *  \param  exponent
 *          Factor p in calculating packet error rate (see above)
 *
 */
typedef struct
{
    uint16_t    multiplier;
    uint16_t    exponent;
} unpack_qos_pktErrRate_t;

/**
 * \ingroup qos
 * 
 * This structure contains the QoS Flow Request.\n
 * Please check is_<Param_Name>_Available field for presence of optional parameters
 *
 *  \param  index
 *          - Mandatory parameter
 *          - IP flow index
 *          - Integer that uniquely identifies each flow instance
 *          - Unique index must be assigned by the control point to every flow_spec instance
 *
 *  \param  ProfileId3GPP2
 *          - IP flow 3GPP2 profile ID
 *          - A profile ID is shorthand for a defined set of QoS flow parameters specified by the network; to be present while requesting QoS for a CDMA device
 *
 *  \param  val_3GPP2Pri
 *          - IP flow 3GPP2 flow priority
 *          - Flow priority used by the network in case of contention between flows with same QoS; this parameter applies for CDMA devices
 *
 *  \param  TrafficClass
 *          - IP flow traffic class
 *          - Integer that designates the requested traffic class:
 *          - 0 - Conversational
 *          - 1 - Streaming
 *          - 2 - Interactive
 *          - 3 - Background
 *
 *  \param  DataRate
 *          - IP flow data rate min max
 *          - See \ref unpack_qos_dataRate_t for more information
 *
 *  \param  TokenBucket
 *          - IP flow data rate token bucket
 *          - See \ref unpack_qos_tokenBucket_t for more information
 *
 *  \param  Latency
 *          - IP flow latency
 *          - Maximum delay (in milliseconds) that can be tolerated by an IP packet during transfer through the wireless link
 *
 *  \param  Jitter
 *          - IP flow jitter
 *          - Difference between the maximum and minimum latency (in milliseconds) that can be tolerated by an IP packet during the transfer through the wireless link
 *
 *  \param  PktErrRate
 *          - IP flow packet error rate
 *          - See \ref unpack_qos_pktErrRate_t for more information
 *
 *  \param  MinPolicedPktSz
 *          - IP flow minimum policed packet size
 *          - Integer that defines the minimum packet size (in bytes) that will be policed for QoS guarantees; any IP packets that are smaller than the minimum specified policed size may not receive requested QoS
 *
 *  \param  MaxAllowedPktSz
 *          - IP flow maximum allowed packet size
 *          - Integer that defines the maximum packet size (in bytes) allowed in the IP flow; any IP packets greater in size than the maximum allowed packet size are not queued for transmission
 *
 *  \param  val_3GPPResResidualBER
 *          - IP flow 3GPP residual bit error rate
 *          - residual_bit_error_rate
 *          - 0 = 5*10-2 residual BER
 *          - 1 = 1*10-2 residual BER
 *          - 2 = 5*10-3 residual BER
 *          - 3 = 4*10-3 residual BER
 *          - 4 = 1*10-3 residual BER
 *          - 5 = 1*10-4 residual BER
 *          - 6 = 1*10-5 residual BER
 *          - 7 = 1*10-6 residual BER
 *          - 8 = 6*10-8 residual BER
 *          - Integer that indicates the undetected BER for each IP flow in the delivered packets; Tapplies only to 3GPP networks
 *
 *  \param  val_3GPPTraHdlPri
 *          - 3GPP traffic handling priority
 *          - 0 - Relative traffic handling priority 1
 *          - 1 - Relative traffic handling priority 2
 *          - 2 - Relative traffic handling priority 3
 *          - Defines the relative priority of the flow; applies only to 3GPP networks
 *
 *  \param  val_3GPPImCn
 *          - IP flow 3GPP IM CN flag
 *          - IM CN subsystem signaling flag:
 *          - 0x00 - FALSE
 *          - 0x01 - TRUE
 *          - This parameter applies only to 3GPP networks
 *
 *  \param  val_3GPPSigInd
 *          - IP flow 3GPP signaling indication
 *          - 0x00 - FALSE
 *          - 0x01 - TRUE
 *          - This parameter applies only to 3GPP networks
 *
 *  \param  LteQci
 *          - LTE QoS Class Identifier
 *          - QoS Class Identifier(QCI) is a required parameter to request QoS in LTE
 *          - QCI values:
 *            - QCI value 0 requests the network to assign the appropriate QCI value
 *            - QCI values 1-4 are associated with guaranteed bitrates
 *            - QCI values 5-9 are associated with nonguaranteed bitrates, so the values specified as guaranteed and maximum bitrates are ignored
 */
typedef struct
{
    uint8_t                  index;
	uint8_t                  is_ProfileId3GPP2_Available;
    uint16_t                 ProfileId3GPP2;
	uint8_t                  is_val_3GPP2Pri_Available;
    uint8_t                  val_3GPP2Pri;
	uint8_t                  is_TrafficClass_Available;
    uint8_t                  TrafficClass;
	uint8_t                  is_DataRate_Available;
    unpack_qos_dataRate_t    DataRate;
	uint8_t                  is_TokenBucket_Available;
    unpack_qos_tokenBucket_t TokenBucket;
	uint8_t                  is_Latency_Available;
    uint32_t                 Latency;
	uint8_t                  is_Jitter_Available;
    uint32_t                 Jitter;
	uint8_t                  is_PktErrRate_Available;
    unpack_qos_pktErrRate_t  PktErrRate;
	uint8_t                  is_MinPolicedPktSz_Available;
    uint32_t                 MinPolicedPktSz;
	uint8_t                  is_MaxAllowedPktSz_Available;
    uint32_t                 MaxAllowedPktSz;
	uint8_t                  is_val_3GPPResResidualBER_Available;
    uint16_t                 val_3GPPResResidualBER;
	uint8_t                  is_val_3GPPTraHdlPri_Available;
    uint8_t                  val_3GPPTraHdlPri;
	uint8_t                  is_val_3GPPImCn_Available;
    uint8_t                  val_3GPPImCn;
	uint8_t                  is_val_3GPPSigInd_Available;
    uint8_t                  val_3GPPSigInd;
	uint8_t                  is_LteQci_Available;
    uint8_t                  LteQci;
} unpack_qos_swiQosFlow_t;

/**
 * \ingroup qos
 * 
 * This structure contains the IPv4 filter address
 *
 *  \param  addr
 *          IPv4 address
 *
 *  \param  subnetMask
 *          A packet matches if:
 *          - (addr and subnetMask) == (IP pkt addr & subnetMask)
 *          Callers to set up a filter with a range of source addresses, if needed; subnet mask of all 1s (255.255.255.255) specifies a single address value
 *
 */
typedef struct
{
    uint32_t   addr;
    uint32_t   subnetMask;
} unpack_qos_IPv4Addr_t;

/**
 * \ingroup qos
 * 
 * This structure contains the IPv4 filter type of service
 *
 *  \param  val
 *          Type of service value
 *
 *  \param  mask
 *          Packet matches the TOS filter if:
 *          (IPv4_filter_tos_val and IPv4_filter_tos_mask) == (TOS value in the IP packet & IPv4_filter_tos_mask)
 *          Example:
 *          - IPv4_filter_tos_val = 00101000
 *          - IPv4_filter_tos_mask = 11111100
 *          The filter will compare only the first 6 bits in the IPv4_filter_type_of_service with the first 6 bits in the TOS field of the IP packet. The first 6 bits in the TOS field of the IP packet must be 001010 to match the filter. The last 2 bits can be anything since they are ignored by filtering.
 *
 */
typedef struct
{
    uint8_t   val;
    uint8_t   mask;
} unpack_qos_Tos_t;

/**
 * \ingroup qos
 * 
 * This structure contains the IPv6 filter address
 *
 *  \param  addr
 *          IPv6 address (in network byte order); this is a 16-byte byte array (in Big-endian format)
 *
 *  \param  prefixLen
 *          IPv6 filter prefix length; can take a value between 0 and 128
 *          Note: A packet matches if the IPv6 source address bytes until the prefix lengths are equal. Therefore prefix length can be used to set a filter with a range of source addresses. A prefix length of 128 specifies a single address value.
 *
 */
typedef struct
{
    uint8_t    addr[16];
    uint8_t    prefixLen;
} unpack_qos_IPv6Addr_t;

/**
 * \ingroup qos
 * 
 * This structure contains the IPv6 filter traffic class
 *
 *  \param  val
 *          The traffic class value
 *
 *  \param  mask
 *          The packet matches the traffic class filter if:
 *          (IPv6_filter_traffic_class_val and IPv6_filter_traffic_class_mask) == (Traffic class value in the IP packet & IPv6_filter_traffic_class_mask)
 *          Example:
 *          - IPv6_filter_tc_val = 00101000
 *          - IPv6_filter_tc_mask = 11111100
 *          Filter will compare only the first 6 bits in IPv6_filter_traffic_class with the first 6 bits in the traffic class field of the IP packet; first 6 bits in the traffic class field of the IP packet must be 001010 to match filter; last 2 bits can be anything, since they are ignored by filtering
 *
 */
typedef struct
{
    uint8_t   val;
    uint8_t   mask;
} unpack_qos_IPv6TrafCls_t;

/**
 * \ingroup qos
 * 
 * This structure contains the Port Filter
 *
 *  \param  port
 *          port value of the filter
 *
 *  \param  range
 *          range specifies the number of ports to be included in the filter starting from port; filter will match if port in the IP packet lies between port and (port + range )
 *          Range value of 0 implies that only one value of the port is valid, as specified by the port
 *
 */
typedef struct
{
    uint16_t   port;
    uint16_t   range;
} unpack_qos_Port_t;

/**
 * \ingroup qos
 * 
 * This structure contains the QoS Filter Request.\n
 * Please check is_<Param_Name>_Available field for presence of optional parameters
 *
 *  \param  index
 *          Mandatory parameter
 *          IP filter index
 *          Integer that uniquely identifies each filter instance
 *          This TLV must be present in the request
 *
 *  \param  version
 *          Mandatory parameter
 *          IP filter version
 *          Identifies whether the filter is associated with IPv4 or IPv6; value specified also implies that only TLVs defined for that IP version, i.e., TLVs with IPv4 or IPv6 in the name, can be specified
 *          - 0x04 - IPv4
 *          - 0x06 - Ipv6
 *
 *  \param  IPv4SrcAddr
 *          IPv4 filter soruce address
 *          See \ref unpack_qos_IPv4Addr_t for more information
 *          - Implemented only for unsolicited indication
 *
 *  \param  IPv4DstAddr
 *          IPv4 filter destination address
 *          See \ref unpack_qos_IPv4Addr_t for more information
 *          - Implemented only for unsolicited indication
 *
 *  \param  NxtHdrProto
 *          IP filter next header protocol
 *          This TLV must be present if any non-IP filter TLV(s) are provided
 *          If this field is specified, only IP packets belonging to specified higher layer protocol are considered when filtering
 *          The following protocols may be specified:
 *          - 0x01 = ICMP
 *          - 0x06 = TCP
 *          - 0x11 = UDP
 *          - 0x32 = ESP
 *          Note: The next header protocol field will be set to 0xFD (TCP & UDP)
 *                if a TFT is received specifying a source or destination port number,
 *                but IP next header type is not specified.
 *
 *  \param  IPv4Tos
 *          IPv4 filter type of service
 *          See \ref unpack_qos_Tos_t for more information
 *
 *  \param  IPv6SrcAddr
 *          IPv6 filter soruce address
 *          See \ref unpack_qos_IPv6Addr_t for more information
 *          - Implemented only for unsolicited indication
 *
 *  \param  IPv6DstAddr
 *          IPv6 filter destination address
 *          See \ref unpack_qos_IPv6Addr_t for more information
 *          - Implemented only for unsolicited indication
 *
 *  \param  IPv6TrafCls
 *          IPv6 filter traffic class
 *          See \ref unpack_qos_IPv6TrafCls_t for more information
 *
 *  \param  IPv6Label
 *          IPv6 flow label
 *          Packet matches the IPv6 flow label filter if:
 *          ( *pIPv6Label == flow label in the IPv6 header)
 *          - Implemented only for unsolicited indication
 *
 *  \param  TCPSrcPort
 *          TCP filter source port filter
 *          See \ref unpack_qos_Port_t for more information
 *          - Implemented only for unsolicited indication
 *
 *  \param  TCPDstPort
 *          TCP filter destination port filter
 *          See \ref unpack_qos_Port_t for more information
 *          - Implemented only for unsolicited indication
 *
 *  \param  UDPSrcPort
 *          UDP filter source port filter
 *          See \ref unpack_qos_Port_t for more information
 *          - Implemented only for unsolicited indication
 *
 *  \param  UDPDstPort
 *          UDP filter destination port filter
 *          See \ref unpack_qos_Port_t for more information
 *          - Implemented only for unsolicited indication
 *
 *  \param  EspSpi
 *          ESP filter security policy index
 *          Security policy index to uniquely identify each IP flow for filtering encrypted packets for encapsulating security payload
 *          - Implemented only for unsolicited indication
 *
 *  \param  Precedence
 *          Filter Precedence
 *          Specifies the order in which filters are applied; lower numerical value has higher precedence
 *          Note: This TLV only applies to network-initiated QoS; QoS requests containing this TLV from control points will be ignored
 *
 *  \param  Id
 *          Filter ID
 *          Unique identifier for each filter;filter ID is assigned by the modem
 *          Note: This TLV only applies to network-initiated QoS; QoS requests containing this TLV from control points will be ignored
 *
 *  \param  TranSrcPort
 *          Transport protocolfilter source port
 *          See \ref unpack_qos_Port_t for more information
 *          - Implemented only for unsolicited indication
 *
 *  \param  UDPDstPort
 *          Transport protocol filter destination port
 *          See \ref unpack_qos_Port_t for more information
 *          - Implemented only for unsolicited indication
 */
typedef struct
{
    uint8_t                  index;
    uint8_t                  version;
	uint8_t                  is_IPv4SrcAddr_Available;
    unpack_qos_IPv4Addr_t    IPv4SrcAddr;
	uint8_t                  is_IPv4DstAddr_Available;
    unpack_qos_IPv4Addr_t    IPv4DstAddr;
	uint8_t                  is_NxtHdrProto_Available;
    uint8_t                  NxtHdrProto;
	uint8_t                  is_IPv4Tos_Available;
    unpack_qos_Tos_t         IPv4Tos;
	uint8_t                  is_IPv6SrcAddr_Available;
    unpack_qos_IPv6Addr_t    IPv6SrcAddr;
	uint8_t                  is_IPv6DstAddr_Available;
    unpack_qos_IPv6Addr_t    IPv6DstAddr;
	uint8_t                  is_IPv6TrafCls_Available;
    unpack_qos_IPv6TrafCls_t IPv6TrafCls;
	uint8_t                  is_IPv6Label_Available;
    uint32_t                 IPv6Label;
	uint8_t                  is_TCPSrcPort_Available;
    unpack_qos_Port_t        TCPSrcPort;
	uint8_t                  is_TCPDstPort_Available;
    unpack_qos_Port_t        TCPDstPort;
	uint8_t                  is_UDPSrcPort_Available;
    unpack_qos_Port_t        UDPSrcPort;
	uint8_t                  is_UDPDstPort_Available;
    unpack_qos_Port_t        UDPDstPort;
	uint8_t                  is_EspSpi_Available;
    uint32_t                 EspSpi;
	uint8_t                  is_Precedence_Available;
    uint16_t                 Precedence;
	uint8_t                  is_Id_Available;
    uint16_t                 Id;
	uint8_t                  is_TranSrcPort_Available;
    unpack_qos_Port_t        TranSrcPort;
	uint8_t                  is_TranDstPort_Available;
    unpack_qos_Port_t        TranDstPort;
} unpack_qos_swiQosFilter_t;
		
/**
 * \ingroup qos
 * 
 *  Structure with QoS flow details.\n
 *  Please check is_<Param_Name>_Available field for presence of optional parameters
 *
 *  \param  QFlowState
 *          - QoS flow state information, please check \ref unpack_qos_QosFlowInfoState_t for more information
 *
 *  \param  is_TxQFlowGranted_Available
 *          - TRUE if optional TxQFlowGranted is available
 *
 *  \param  TxQFlowGranted
 *          - The Tx Qos flow granted, please check \ref unpack_qos_swiQosFlow_t for more information
 *
 *  \param  is_RxQFlowGranted_Available
 *          - TRUE if optional RxQFlowGranted is available
 * 
 *  \param  RxQFlowGranted
 *          - The Rx Qos flow granted, please check \ref unpack_qos_swiQosFlow_t for more information
 *
 *  \param  NumTxFilters
 *          - Number of Tx filters available
 * 
 *  \param  TxQFilter
 *          - The Tx Qos filter, please check \ref unpack_qos_swiQosFilter_t for more information
 *          - See \ref LITEQMI_MAX_QOS_FILTERS for more information
 *
 *  \param  NumRxFilters
 *          - Number of Tx filters available
 * 
 *  \param  RxQFilter
 *          - The Rx Qos filter, please check \ref unpack_qos_swiQosFilter_t for more information
 *          - See \ref LITEQMI_MAX_QOS_FILTERS for more information
 *
 *  \param  BearerID
 *          - The bearer ID
 *          - Bearer ID or Radio Link Protocol (RLP) ID of the activated flow.
 *          - Valid Values - 0 to 16
 *          - 0xFF - Invalid value.
 *
 *  \param  is_QosFlowType_Available
 *          - TRUE if optional QosFlowType is available
 *
 *  \param  QosFlowType
 *          - QOS Flow Type
 *          - Indicates whether the QoS flow type is network-initiated or UE-initiated.
 *          - 0x00 - UE-initiated QoS flow
 *          - 0x01 - Network-initiated QoS flow
 *
 *  \param  is_BearerID_Available
 *          - TRUE if optional BearerID is available
 *
 *  \param  is_FcSeqNum_Available
 *          - TRUE if optional FcSeqNum is available
 *
 *  \param  FcSeqNum
 *          - Flow Control Sequence Number
 *          - The sequence number of each flow enable and disable event.
 *          - Whenever the flow is disabled, the sequence number is incremented.
 *          - The sequence number remain the same when the flow is enabled. 
 */
typedef struct {
    unpack_qos_QosFlowInfoState_t QFlowState;
	uint8_t                       is_TxQFlowGranted_Available;
    unpack_qos_swiQosFlow_t       TxQFlowGranted;
	uint8_t                       is_RxQFlowGranted_Available;
    unpack_qos_swiQosFlow_t       RxQFlowGranted;
	uint8_t                       NumTxFilters;
    unpack_qos_swiQosFilter_t     TxQFilter[LITEQMI_MAX_QOS_FILTERS];
	uint8_t                       NumRxFilters;
    unpack_qos_swiQosFilter_t     RxQFilter[LITEQMI_MAX_QOS_FILTERS];
    uint8_t                       BearerID;
    uint8_t                       is_QosFlowType_Available;
    uint8_t                       QosFlowType;
    uint8_t                       is_BearerID_Available;
    uint8_t                       is_FcSeqNum_Available;
    uint16_t                      FcSeqNum;
} unpack_qos_QosFlowInfo_t;

/**
 * \ingroup qos
 * 
 *  Structure that contains the Network-Supported QoS Profiles
 *  \param Tech_pref [OUT]
 *          - Technology preference to be used while registering for network-supported QoS.
 *           - Values:
 *              - -32767 - CDMA
 * 
 *  \param Profile_count [IN][OUT]
 *          - Number of profile values that follow. If the count = 0, no additional data follows.
 * 
 *  \param pProfile_value [OUT]
 *          - This field repeats "count" number of times.
 */

typedef struct {
    uint16_t    Tech_pref;
    uint8_t     Profile_count;
    uint16_t    *pProfile_value;
} unpack_qos_EventCallback_t;

/**
 * \ingroup qos
 * 
 *  Structure that contains the Network-Supported QoS Profiles
 *  \param pNetworkSupportedQoSProfiles [OUT]
 *          - \sa Network-Supported QoS Profiles
 *
 * @param ParamPresenceMask [OUT]
 *          - bitmask representation to indicate valid parameters.
 *
 *  \param pQosFlowInfo [OUT]
 *          - \sa QoS Flow Info
 *
 */
typedef struct {
    unpack_qos_EventCallback_t *pNetworkSupportedQoSProfiles;
    swi_uint256_t  ParamPresenceMask;
    unpack_qos_QosFlowInfo_t* pQosFlowInfo;
} unpack_qos_SLQSSetQosEventCallback_ind_t;

/**
 * \ingroup qos
 * 
 *  Function to unpack QoS event indications  
 *  This maps to SLQSSetQosEventCallback
 *
 *  \param[in]  pResp
 *              - Response from modem
 *
 *  \param[in]  respLen
 *              - Length of pResp from modem
 *
 *  \param[out]  pOutput
 *          - See \ref unpack_qos_SLQSSetQosEventCallback_ind_t for more information
 *
 *  \return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  \sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 *  \note   
 *          - This is a broadcast notification that is sent to the registered QoS service
 *          - No explicit function to register for this indication is needed
 *          - Please use eQMI_QOS_NETWORK_STATUS_IND indication to identify this event from QOS service read function
 */
int unpack_qos_SLQSSetQosEventCallback_ind(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_qos_SLQSSetQosEventCallback_ind_t *pOutput
        );



/**
 * \ingroup qos
 * 
 *  Structure that contains the request Binds a control point to a data port Periapheral End Point Type data.
 *  \param  EndPointType
 *              Peripheral end point type. Values:
 *              - 0 - Reserved
 *              - 1 - HSIC 
 *              - 2 - HSUSB
 *              - 3 - PCIE 
 *              - 4 - Embedded 
 *
 *  \param  IfaceID
 *              Peripheral interface number.
 */
typedef struct {
    uint32_t EndPointType;
    uint32_t IfaceID;
} qos_BindDataPortPeripheralEndPointID_t;


/**
 * \ingroup qos
 * 
 *  Structure that contains the request Binds a control point to a data port Mux ID data.
 *  \param  MuxID
 *              Mux ID:
 *              - 0x80-0x8F : valid value
 */
typedef struct {
    uint8_t MuxID;
} qos_BindDataPortMuxID_t;

/**
 * \ingroup qos
 * 
 *  Structure that contains the request Binds a control point to a data port SIO Data Port data.
 *  \param  u16SIODataPort
 *              SIO Data Port to which the client binds
 */
typedef struct {
    uint16_t SIODataPort;
} qos_BindDataPortSIODataPort_t;


/**
 * \ingroup qos
 * 
 *  Structure that contains the request Binds a control point to a data port.
 *
 *  \param  pPeripheralEndPointID
 *       - See \ref qos_BindDataPortPeripheralEndPointID_t for more information.
 *
 *  \param  pMuxID
 *       - See \ref qos_BindDataPortMuxID_t for more information.
 *
 *  \param  pSIODataPort
 *       - See \ref qos_BindDataPortSIODataPort_t for more information.
 */
typedef struct {
    qos_BindDataPortPeripheralEndPointID_t *pPeripheralEndPointID;  
    qos_BindDataPortMuxID_t *pMuxID;
    qos_BindDataPortSIODataPort_t *pSIODataPort;
} pack_qos_BindDataPort_t;

/**
 * \ingroup qos
 * 
 *  Function to pack command to Binds a control point to a data port.
 *  This maps to PkQmiQosBindDataPort
 *
 *  \param[out]  pCtx
 *               - See \ref pack_qmi_t for more information
 *
 *  \param[in,out]  pReqBuf
 *                  - Buffer for packed QMI command to be provided by the host application
 *                  - Minimum expected size is 2048 bytes
 *
 *  \param[in,out]  pLen
 *                  - On input, size of pReqBuf
 *                  - On ouptut, number of bytes actually packed
 *
 *  \param[in]  req
 *              - See \ref pack_qos_BindDataPort_t for more information
 *
 *  \return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  \sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 *  \note
 *          - Timeout: 2 seconds
 */
int pack_qos_BindDataPort (
        pack_qmi_t *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen,
        pack_qos_BindDataPort_t *req
        ); 
/**
 * This structure contains unpack Qos BindDataPort.
 * \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
**/
typedef struct{
    swi_uint256_t  ParamPresenceMask;
}unpack_qos_BindDataPort_t;
/**
 * \ingroup qos
 * 
 *  Function to unpack the response to Binds a control point to a data port.
 *  This maps to UpkQmiQosBindDataPort
 *
 *  \param[in]  pResp
 *              - Response from modem
 *
 *  \param[in]  respLen
 *              - Length of pResp from modem
 *
 *  \param[out]  pOutput
 *          - See \ref unpack_qos_BindDataPort_t for more information
 *
 *  \return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  \sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int unpack_qos_BindDataPort(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_qos_BindDataPort_t *pOutput
        );

/**
 * \ingroup qos
 * 
 *  Structure that contains the QOS Identifier to QOS Information parameters
 *  \param  qosIdentifier[IN]        
 *          - Identifier for the QoS flow/instance that has been negotiated and that is being queried.
 */
typedef struct 
{
    uint32_t qosIdentifier;
} pack_qos_SLQSQosGetQosInfo_t;

/**
 * \ingroup qos
 * 
 *  Function to pack command to retrieve QoS Information.
 *  This maps to SLQSQosGetQosInfo
 *
 *  \param[out]  pCtx
 *               - See \ref pack_qmi_t for more information
 *
 *  \param[in,out]  pReqBuf
 *                  - Buffer for packed QMI command to be provided by the host application
 *                  - Minimum expected size is 2048 bytes
 *
 *  \param[in,out]  pLen
 *                  - On input, size of pReqBuf
 *                  - On ouptut, number of bytes actually packed
 *		
 *  \param[in] pQosIdentifier
 *              - QOS Identifier
 *              - \sa pack_qos_SLQSQosGetQosInfo_t
 *          
 *  \return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  \sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int pack_qos_SLQSQosGetQosInfo (
        pack_qmi_t *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen,
        pack_qos_SLQSQosGetQosInfo_t *pQosIdentifier
        ); 

/**
 * \ingroup qos
 * 
 * This structure contains the QoS Filter Specs
 *  \param flow_status[OUT][OPT]
 *          - Current flow status. 
 *           - Values:
 *              - QOS_STATUS_ACTIVATED (0x01) - Activated status
 *              - QOS_STATUS_SUSPENDED (0x02) - Suspended status
 * 
 *  \param flow_valid_params
 *          - Mask of parameters that are valid for this flow.
 *           - Values:
 *              - QMI_QOS_IP_FLOW_MASK_NONE (0x0000000000000000) - No parameters
 *              - QMI_QOS_IP_FLOW_MASK_TRF_CLASS (0x0000000000000001) - Traffic class
 *              - QMI_QOS_IP_FLOW_MASK_DATA_RATE_MIN_MAX (0x0000000000000002) - Data rate min/max
 *              - QMI_QOS_IP_FLOW_MASK_DATA_RATE_TOK_BUCKET (0x0000000000000004) - Data rate token bucket
 *              - QMI_QOS_IP_FLOW_MASK_LATENCY (0x0000000000000008) - Latency
 *              - QMI_QOS_IP_FLOW_MASK_JITTER (0x0000000000000010) - Jitter
 *              - QMI_QOS_IP_FLOW_MASK_PKT_ERR_RATE (0x0000000000000020) - Packet error rate
 *              - QMI_QOS_IP_FLOW_MASK_MIN_POLICED_PKT_SIZE (0x0000000000000040) - Minimum policed packet size
 *              - QMI_QOS_IP_FLOW_MASK_MAX_ALLOWED_PKT_SIZE (0x0000000000000080) - Maximum allowed packet size
 *              - QMI_QOS_IP_FLOW_MASK_3GPP_RES_BER (0x0000000000000100) - 3GPP residual bit error rate (BER)
 *              - QMI_QOS_IP_FLOW_MASK_3GPP_TRF_PRI (0x0000000000000200) - 3GPP traffic handling priority
 *              - QMI_QOS_IP_FLOW_MASK_3GPP2_PROFILE_ID (0x0000000000000400) - 3GPP2 profile ID
 *              - QMI_QOS_IP_FLOW_MASK_3GPP2_FLOW_PRIORITY (0x0000000000000800) - 3GPP2 flow priority
 *              - QMI_QOS_IP_FLOW_MASK_3GPP_IM_CN_FLAG (0x0000000000001000) - 3GPP IM CN subsystem signaling flag
 *              - QMI_QOS_IP_FLOW_MASK_3GPP_SIG_IND (0x0000000000002000) - 3GPP signaling indication
 *              - QMI_QOS_IP_FLOW_MASK_LTE_QCI (0x0000000000004000) - LTE QOS class identifier
 *              - QMI_QOS_IP_FLOW_MASK_5G_QCI (0x0000000000008000) - 5G QOS class identifier
 *              - QMI_QOS_IP_FLOW_MASK_AVG_WINDOW (0x0000000000010000) - Averaging window
 * 
 *  \param ip_flow_trf_cls
 *          - Requested traffic class.
 *           - Values:
 *              - QOS_IP_TRF_CLS_CONVERSATIONAL (0) - IP traffic class conversational
 *              - QOS_IP_TRF_CLS_STREAMING (1) - IP traffic class streaming
 *              - QOS_IP_TRF_CLS_INTERACTIVE (2) – IP traffic class interactive
 *              - QOS_IP_TRF_CLS_BACKGROUND (3) – IP traffic class background
 * 
 *  \param data_rate_max
 *          - Maximum required data rate (bits per second).
 * 
 *  \param guaranteed_rate
 *          - Minimum guaranteed data rate (bits per second).
 * 
 *  \param peak_rate
 *          - Maximum rate at which data can be transmitted when the token bucket is full (bits per second).
 * 
 *  \param token_rate
 *          - Rate at which tokens are put in the token bucket (bits per second); a token must be present in the bucket to send a byte of data.
 * 
 *  \param bucket_size
 *          - Maximum number of tokens that can be accumulated at any instance (bytes)
 *            controls the size of the burst that is allowed at any given time.
 * 
 *  \param ip_flow_latency
 *          - Maximum delay (in milliseconds) that can be tolerated by an IP packet during transfer through the wireless link.
 * 
 *  \param ip_flow_jitter
 *          - Difference between the maximum and minimum latency (in milliseconds) that can be tolerated by an IP packet during
 *            the transfer through the wireless link.
 * 
 *  \param ip_flow_pkt_error_rate_multiplier
 *          - Factor m in calculating packet error rate: E = m*10**(-p)
 *
 *  \param ip_flow_pkt_error_rate_exponen
 *          - Factor p in calculating packet error rate: E = m*10**(-p) 
 * 
 *  \param ip_flow_min_policed_packet_size
 *          - Integer that defines the minimum packet size (in bytes) that will be policed for QoS guarantees.
 *          - Any IP packets that are smaller than the minimum specified policed size may not receive the requested QoS.
 * 
 *  \param ip_flow_max_allowed_packet_size
 *          - Integer that defines the maximum packet size (in bytes) allowed in the IP flow.
 *          - Any IP packets greater in size than the maximum allowed packet size are not queued for transmission.
 * 
 *  \param ip_flow_3gpp_residual_bit_error_rate
 *          - Indicates the undetected BER for each IP flow in the delivered packets. Applies only to 3GPP networks.
 *           - Values:
 *              - QOS_FLOW_3GPP_RES_BIT_ERR_RATE1 (0) – 5*10-2
 *              - QOS_FLOW_3GPP_RES_BIT_ERR_RATE2 (1) – 1*10-2
 *              - QOS_FLOW_3GPP_RES_BIT_ERR_RATE3 (2) – 5*10-3
 *              - QOS_FLOW_3GPP_RES_BIT_ERR_RATE4 (3) – 4*10-3
 *              - QOS_FLOW_3GPP_RES_BIT_ERR_RATE5 (4) – 1*10-3
 *              - QOS_FLOW_3GPP_RES_BIT_ERR_RATE6 (5) – 1*10-4
 *              - QOS_FLOW_3GPP_RES_BIT_ERR_RATE7 (6) – 1*10-5
 *              - QOS_FLOW_3GPP_RES_BIT_ERR_RATE8 (7) – 1*10-6
 *              - QOS_FLOW_3GPP_RES_BIT_ERR_RATE9 (8) – 6*10-8
 * 
 *  \param ip_flow_3gpp_traffic_handling_priority
 *          - Defines the relative priority of the flow. Applies only to 3GPP networks.
 *           - Values:
 *              - QOS_FLOW_3GPP_TRAFFIC_HANDLING_PRI1 (0) – Priority level 1
 *              - QOS_FLOW_3GPP_TRAFFIC_HANDLING_PRI2 (1) – Priority level 2
 *              - QOS_FLOW_3GPP_TRAFFIC_HANDLING_PRI3 (2) – Priority level 3
 * 
 *  \param ip_flow_3gpp2_profile_id
 *          - A profile ID is shorthand for a defined set of QoS flow parameters specified by the network; 
 *          - to be present while requesting QoS for a CDMA device.
 * 
 *  \param ip_flow_3gpp2_flow_priority
 *          - Flow priority used by the network in case of contention between flows with the same QoS.
 *          - This parameter applies to CDMA devices.
 * 
 *  \param ip_flow_3gpp_im_cn_flag
 *          - IM CN subsystem signaling flag. This parameter applies only to 3GPP networks.
 *           - Values:
 *              - 0x00 - FALSE
 *              - 0x01 - TRUE
 * 
 *  \param ip_flow_3gpp_sig_ind
 *          - This parameter applies only to 3GPP networks.
 *           - Values:
 *              - 0x00 - FALSE
 *              - 0x01 - TRUE
 * 
 *  \param ip_flow_lte_qci
 *          - QoS Class Identifier (QCI) is a required parameter to request QoS in LTE QCI.
 *           - Values:
 *              - QCI value 0 requests the network to assign the appropriate QCI value
 *              - QCI values 1-4, 65, 66 are associated with guaranteed bitrates
 *              - QCI values 5-9, 69, 70 are associated with nonguaranteed bitrates, so the values 
 *                specified as guaranteed and maximum bitrates are ignored For more detailed information
*/
typedef struct
{
    uint8_t    flow_status;
    uint64_t   flow_valid_params; 
    uint32_t   ip_flow_trf_cls;
    uint64_t   data_rate_max;
    uint64_t   guaranteed_rate;
    uint32_t   peak_rate;
    uint32_t   token_rate;
    uint32_t   bucket_size;
    uint32_t   ip_flow_latency;
    uint32_t   ip_flow_jitter;
    uint16_t   ip_flow_pkt_error_rate_multiplier;
    uint16_t   ip_flow_pkt_error_rate_exponen;
    uint32_t   ip_flow_min_policed_packet_size;
    uint32_t   ip_flow_max_allowed_packet_size;
    uint32_t   ip_flow_3gpp_residual_bit_error_rate;
    uint32_t   ip_flow_3gpp_traffic_handling_priority;
    uint16_t   ip_flow_3gpp2_profile_id;
    uint8_t    ip_flow_3gpp2_flow_priority;
    uint8_t    ip_flow_3gpp_im_cn_flag;
    uint8_t    ip_flow_3gpp_sig_ind;
    uint32_t   ip_flow_lte_qci;
}unpack_qos_QosFlow_t;

/**
 * \ingroup qos
 * 
 * This structure contains the QoS Filter Specs
 *  \param ip_version
 *          - Depending on the IP version set, either the IPv4 or the IPv6 information is valid.
 *           - Values:
 *              - QOS_IP_FAMILY_IPV4 (0x04) - IPv4 family.
 *              - QOS_IP_FAMILY_IPV6 (0x06) - IPv6 family.
 *  \param ipv4_valid_params
 *          - The bits set in this mask denote which parameters contain valid values.
 *           - Values:
 *              - QMI_QOS_IPV4_FILTER_MASK_NONE (0x0000000000000000) - No parameters
 *              - QMI_QOS_IPV4_FILTER_MASK_SRC_ADDR (0x0000000000000001) - IPv4 source address
 *              - QMI_QOS_IPV4_FILTER_MASK_DEST_ADDR (0x0000000000000002) - IPv4 destination address
 *              - QMI_QOS_IPV4_FILTER_MASK_TOS (0x0000000000000004) - IPv4 type of service
 *  \param ipv4_addr_1
 *          - IPv4 address.
 *  \param ipv4_subnet_mask_1
 *          - IPv4 subnet mask.
 *  \param ipv4_addr_2
 *          - IPv4 address.
 *  \param ipv4_subnet_mask_2
 *          - IPv4 subnet mask.
 *  \param ipv4_val
 *          - Type of service value.
 *  \param ipv4_mask
 *          - Type of service mask.
 *  \param ipv6_valid_params
 *          - The bits set in this mask denote which parameters contain valid values.
 *           - Values:
 *              - QMI_QOS_IPV6_FILTER_MASK_NONE (0x0000000000000000) - No parameters
 *              - QMI_QOS_IPV6_FILTER_MASK_SRC_ADDR (0x0000000000000001) - IPv6 source address
 *              - QMI_QOS_IPV6_FILTER_MASK_DEST_ADDR (0x0000000000000002) - IPv6 destination address
 *              - QMI_QOS_IPV6_FILTER_MASK_TRAFFIC_CLASS (0x0000000000000004) - IPv6 traffic class
 *              - QMI_QOS_IPV6_FILTER_MASK_FLOW_LABEL (0x0000000000000008) - IPv6 flow label
 *  \param ipv6_address_1
 *          - IPv6 address.
 *  \param ipv6_prefix_len_1
 *          - IPv6 address prefix length.
 *  \param ipv6_address_2
 *          - IPv6 address.
 *  \param ipv6_prefix_len_2
 *          - IPv6 address prefix length.
 *  \param ipv6_val
 *          - Traffic class value.
 *  \param ipv6_mask
 *          - Traffic class mask.
 *  \param ipv6_flow_label
 *          - IPv6 flow label.
 *  \param ipv6_xport_protocol
 *          - Depending on the value in xport_protocol, only one field of icmp_info, tcp_info, udp_info, esp_info,
 *            or ah_info is valid. QOS_PROTO_NONE implies that no transport level protocol parameters are valid.
 *           - Values:
 *              - QOS_PROTO_NONE (0x00) - No transport protocol
 *              - QOS_PROTO_ICMP (0x01) - Internet Control Messaging Protocol
 *              - QOS_PROTO_TCP (0x06) - Transmission Control Protocol
 *              - QOS_PROTO_UDP (0x11) - User Datagram Protocol
 *              - QOS_PROTO_ESP (0x32) - Encapsulating Security Payload Protocol
 *              - QOS_PROTO_AH (0x33) - Authentication Header Protocol
 *              - QOS_PROTO_ICMPV6 (0x3A) - Internet Control Messaging Protocol for IPV6
 *  \param port_valid_params
 *          - The bits set in this mask denote which parameters contain valid values.
 *           - Values:
 *              - QMI_QOS_PORT_INFO_FILTER_MASK_NONE (0x0000000000000000) - No parameters
 *              - QMI_QOS_PORT_INFO_FILTER_MASK_SRC_PORT (0x0000000000000001) - Source port
 *              - QMI_QOS_PORT_INFO_FILTER_MASK_DEST_PORT (0x0000000000000002) - Destination port
 *  \param src_port
 *          - Port
 *  \param src_range
 *          - Range
 *  \param des_port
 *          - Port
 *  \param des_range
 *          - Range
 *  \param valid_params_4
 *          - The bits set in this mask denote which parameters contain valid values.
 *           - Values:
 *              - QMI_QOS_PORT_INFO_FILTER_MASK_NONE (0x0000000000000000) - No parameters
 *              - QMI_QOS_PORT_INFO_FILTER_MASK_SRC_PORT (0x0000000000000001) – Source port
 *              - QMI_QOS_PORT_INFO_FILTER_MASK_DEST_PORT (0x0000000000000002) – Destination port
 *  \param port_3
 *          - Port
 *  \param range_3
 *          - Range
 *  \param port_4
 *          - Port
 *  \param range_4
 *          - Range
 *  \param icmp_valid_params
 *          - The bits set in this mask denote which parameters contain valid values.
 *           - Values:
 *              - QMI_QOS_ICMP_FILTER_MASK_NONE (0x0000000000000000) - No parameters
 *              - QMI_QOS_ICMP_FILTER_MASK_MSG_TYPE (0x0000000000000001) - Message type
 *              - QMI_QOS_ICMP_FILTER_MASK_MSG_CODE (0x0000000000000002) - Message code
 *  \param icmp_type
 *          - ICMP type.
 *  \param icmp_code
 *          - ICMP code.
 *  \param ipsec_valid_params
 *          - The bits set in this mask denote which parameters contain valid values.
 *           - Values:
 *              - QMI_QOS_IPSEC_FILTER_MASK_NONE (0x0000000000000000) - No parameters
 *              - QMI_QOS_IPSEC_FILTER_MASK_SPI (0x0000000000000001) - Security parameter index
 *  \param ipsec_spi
 *          - Security parameter index for IPSec.
 *  \param ipsec_valid_params_2
 *          - The bits set in this mask denote which parameters contain valid values.
 *           - Values:
 *              - QMI_QOS_IPSEC_FILTER_MASK_NONE (0x0000000000000000) - No parameters
 *              - QMI_QOS_IPSEC_FILTER_MASK_SPI (0x0000000000000001) - Security parameter index
 *  \param ipsec_spi_2
 *          - Security parameter index for IPSec.
 *  \param ipsec_filter_id
 *          - Unique identifier for each filter.
 *  \param filter_precedence
 *          - Specifies the order in which filters are applied. A lower numerical value has a higher precedence.
 */
typedef struct
{
    uint8_t  ip_version;
    uint64_t ipv4_valid_params;
    uint32_t ipv4_addr_1;
    uint32_t ipv4_subnet_mask_1;
    uint32_t ipv4_addr_2;
    uint32_t ipv4_subnet_mask_2;
    uint8_t  ipv4_val;
    uint8_t  ipv4_mask;
    uint64_t ipv6_valid_params;
    uint8_t  ipv6_address_1[16];
    uint8_t  ipv6_prefix_len_1;
    uint8_t  ipv6_address_2[16];
    uint8_t  ipv6_prefix_len_2;
    uint8_t  ipv6_val;
    uint8_t  ipv6_mask;
    uint32_t ipv6_flow_label;
    uint32_t ipv6_xport_protocol;
    uint64_t port_valid_params_1;
    uint16_t src_port_1;
    uint16_t src_range_1;
    uint16_t des_port_1;
    uint16_t des_range_1;
    uint64_t port_valid_params_2;
    uint16_t src_port_2;
    uint16_t src_range_2;
    uint16_t des_port_2;
    uint16_t des_range_2;
    uint64_t icmp_valid_params;
    uint8_t  icmp_type;
    uint8_t  icmp_code;
    uint64_t ipsec_valid_params;
    uint32_t ipsec_spi;
    uint64_t ipsec_valid_params_2;
    uint32_t ipsec_spi_2;
    uint16_t ipsec_filter_id;
    uint16_t filter_precedence;
}unpack_qos_QosFilterSpecs_t;

/**
 * \ingroup qos
 * 
 * This structure contains the QoS Granted Flow
 *  \param tx_qos_filter_len [IN/OUT]
 *          - Number of sets of the pQoSFilterSpecs instances. Should be renamed to qos_filter_len
 *
 *  \param pQoSFilterSpecs [OUT]
 *          - Contains instances of the Tx filter specification.
 *          - \sa unpack_qos_QosFilterSpecs_t
 * 
 */
typedef struct
{
    uint8_t tx_qos_filter_len;
    unpack_qos_QosFilterSpecs_t *pQoSFilterSpecs;

}unpack_qos_QosFilterSpecsList_t;

/**
 * \ingroup qos
 * 
 * This structure contains the Tx Filter Match All
 *  \param tx_filter_match_all_len
 *          - Number of filter_id. 
 *
 *  \param pfilter_id
 *          - The filter ID identifying the filter that has match-all capability.
 * 
 */
typedef struct
{
    uint8_t tx_filter_match_all_len;
    uint16_t *pfilter_id;
}unpack_qos_TxFilterMatchAll_t;

/**
 * \ingroup qos
 * 
 *  Structure that contains the APN ID to obtain data statistics
 *  \param pFlow_status[OUT][OPT]
 *          - Current flow status. 
 *           - Values:
 *              - QOS_STATUS_ACTIVATED (0x01) - Activated status
 *              - QOS_STATUS_SUSPENDED (0x02) - Suspended status
 *              - Bit to check in ParamPresenceMask - <B>0x10</B>
 * 
 *  \param pTxQosGrantedFlow
 *          - Contains the TX flow specification granted by the network.
 *          - \sa unpack_qos_QosFlow_t
 *              - Bit to check in ParamPresenceMask - <B>0x11</B>
 *
 *  \param pRxQosGrantedFlow
 *          - Contains the RX flow specification granted by the network.
 *          - \sa unpack_qos_QosFlow_t
 *          - Bit to check in ParamPresenceMask - <B>0x12</B>
 *
 *  \param pTxQosFilterSpecs
 *          - Contains one or more instances of the TX filter specification. 
 *          - \sa unpack_qos_QosFilterSpecsList_t
 *          - Bit to check in ParamPresenceMask - <B>0x13</B>
 * 
 *  \param pRxQosFilterSpecs
 *          - Contains one or more instances of the RX filter specification. 
 *          - \sa unpack_qos_QosFilterSpecsList_t
 *          - Bit to check in ParamPresenceMask - <B>0x14</B>
 * 
 *  \param pExt_error_info
 *          - Extended Error Info
 *          - Data services error value returned by the IOCTL/lower layers. 
 *            Refer to the DS error numbers published in 80-V6415-1 for the possible values returned in this field.
 *          - Bit to check in ParamPresenceMask - <B>0x15</B>
 * 
 *  \param pTx_5g_qci
 *          - Tx 5G QCI
 *          - 5G Tx QoS Class Identifier (QCI). Valid if flow_valid_params of Tx QoS Flow TLV has a QMI_QOS_IP_FLOW_MASK_5G_QCI bit set).
 *          - Bit to check in ParamPresenceMask - <B>0x16</B>
 * 
 *  \param pRx_5g_qci
 *          - Rx 5G QCI
 *          - 5G Rx QoS Class Identifier (QCI). Valid if flow_valid_params of Rx QoS Flow TLV has a QMI_QOS_IP_FLOW_MASK_5G_QCI bit set.
 *          - Bit to check in ParamPresenceMask - <B>0x17</B>
 * 
 *  \param pTx_averaging_window
 *          - Tx QoS Averaging Window
 *          - Represents the duration in ms over which the GFBR and MFBR shall be calculated. 
 *          - Valid if flow_valid_params of Tx QoS Flow TLV has a QMI_QOS_IP_FLOW_MASK_AVG_WINDOW bit set.
 *          - Bit to check in ParamPresenceMask - <B>0x18</B>
 * 
 *  \param pRx_averaging_window
 *          - Rx QoS Averaging Window
 *          - Represents the duration in ms over which the GFBR and MFBR shall be calculated. 
 *          - Valid if flow_valid_params of Rx QoS Flow TLV has a QMI_QOS_IP_FLOW_MASK_AVG_WINDOW bit set.
 *          - Bit to check in ParamPresenceMask - <B>0x19</B>
 * 
 *  \param pTxFilterMatchAll
 *          - Tx Filter Match All, \sa unpack_qos_TxFilterMatchAll_t
 *          - List of filter IDs that have match-all capability.
 *          - Bit to check in ParamPresenceMask - <B>0x1A</B>
 * 
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct
{
    /* Response parameters */
    uint8_t                         *pFlow_status;
    unpack_qos_QosFlow_t            *pTxQosGrantedFlow;
    unpack_qos_QosFlow_t            *pRxQosGrantedFlow;
    unpack_qos_QosFilterSpecsList_t    *pTxQosFilterSpecs;
    unpack_qos_QosFilterSpecsList_t    *pRxQosFilterSpecs;  
    uint16_t                        *pExt_error_info;
    uint32_t                        *pTx_5g_qci;
    uint32_t                        *pRx_5g_qci;
    uint16_t                        *pTx_averaging_window;
    uint16_t                        *pRx_averaging_window;
    unpack_qos_TxFilterMatchAll_t   *pTxFilterMatchAll;

    swi_uint256_t  ParamPresenceMask;
}unpack_qos_SLQSQosGetQosInfo_t;

/**
 * \ingroup qos
 * 
 *  Function to unpack the response to get NW QoS status command
 *
 *  \param[in]  pResp
 *              - Response from modem
 *
 *  \param[in]  respLen
 *              - Length of pResp from modem
 *
 *  \param[out]  pOutput
 *               - See \ref unpack_qos_SLQSQosGetNetworkStatus_t for more information
 *
 *  \return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  \sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int unpack_qos_SLQSQosGetQosInfo(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_qos_SLQSQosGetQosInfo_t *pOutput
        );

typedef unpack_qos_QosFlow_t pack_qos_QosFlow_t;

/**
 * \ingroup qos
 * 
 * This structure contains the QoS Flow List
 *  \param tx_qos_flow_len [in][out]
 *          - Number of sets of the pQosFlow.
 *
 *  \param pQosFlow
 *          - List of QosFlow
 *          - \sa pack_qos_QosFlow_t
 */
typedef struct
{
    uint8_t tx_qos_flow_len;
    pack_qos_QosFlow_t *pQosFlow;
}pack_qos_QosFlowList_t;

/**
 * \ingroup qos
 * 
 * This structure contains the Tx or Rx 5G QCI
 *  \param tx_rx_5g_qci_len [in][out]
 *          - Number of pTxRx_5g_qci. 
 *
 *  \param pTxRx_5g_qci [out]
 *          - 5G Tx or Rx QoS Class Identifier (QCI). Valid if flow_valid_params of Tx or Rx QoS Flow TLV has a QMI_QOS_IP_FLOW_MASK_5G_QCI bit set.
 *          - The elements of this list correspond to the list elements of Tx or Rx QoS Flow TLV.
 * 
 */
typedef struct
{
    uint8_t    tx_rx_5g_qci_len;
    uint32_t   *pTxRx_5g_qci;
}pack_qos_TxRx5GQCI_t;

/**
 * \ingroup qos
 * 
 * This structure contains the Tx or Rx QoS Averaging Window
 *  \param tx_averaging_window_len [in][out]
 *          - Number of TxRx_averaging_window. 
 *
 *  \param pTxRx_averaging_window [out]
 *          - Represents the duration in ms over which the guaranteed flow bit rate (GFBR) and maximum flow bit rate (MFBR) shall be calculated. 
 *            Valid if the flow_valid_params of Tx or Rx QoS Flow has a QMI_QOS_IP_FLOW_MASK_AVG_WINDOW bit set. The elements of this list correspond 
 *            to the list elements of Tx or Rx QoS Flow TLV
 * 
 */
typedef struct
{
    uint8_t    tx_averaging_window_len;
    uint32_t   *pTxRx_averaging_window;

}pack_qos_TxRxQosAveragingWindow_t;

typedef unpack_qos_QosFilterSpecs_t pack_qos_QosFilterSpecs_t;
typedef unpack_qos_QosFilterSpecsList_t pack_qos_QosFilterSpecsList_t;

/**
 * \ingroup qos
 * 
 * This structure contains parameters to trigger QoS negotiation
 *  \param pTxQosFlowList
 *          - Tx QoS Flow
 *          - \sa pack_qos_QosFlowList
 * 
 *  \param pRxQosFlowList
 *          - Rx QoS Flow
 *          - \sa pack_qos_QosFlowList
 *  
 *  \param pTxQosFilterSpecsList
 *          - Tx QoS Filter
 *          - \sa pack_qos_QosFilterSpecsList
 * 
 *  \param pRxQosFilterSpecsList
 *          - Rx QoS Filter
 *          - \sa pack_qos_QosFilterSpecsList
 * 
 *  \param pTx5GQCI
 *          - Tx 5G QCI
 *          - \sa pack_qos_TxRx5GQCI
 * 
 *  \param pRx5GQCI
 *          - Rx 5G QCI
 *          - \sa pack_qos_TxRx5GQCI
 * 
 *  \param pTxQosAveragingWindow
 *          - Tx QoS Averaging Window
 *          - \sa pack_qos_TxRxQosAveragingWindow
 * 
 *  \param pRxQosAveragingWindow
 *          - Rx QoS Averaging Window
 *          - \sa pack_qos_TxRxQosAveragingWindow
 * 
 */
typedef struct
{
    /* Request parameters */
    pack_qos_QosFlowList_t *pTxQosFlowList;
    pack_qos_QosFlowList_t *pRxQosFlowList;
    pack_qos_QosFilterSpecsList_t *pTxQosFilterSpecsList;
    pack_qos_QosFilterSpecsList_t *pRxQosFilterSpecsList;
    pack_qos_TxRx5GQCI_t          *pTx5GQCI;
    pack_qos_TxRx5GQCI_t          *pRx5GQCI;
    pack_qos_TxRxQosAveragingWindow_t *pTxQosAveragingWindow;
    pack_qos_TxRxQosAveragingWindow_t *pRxQosAveragingWindow;

    swi_uint256_t  ParamPresenceMask;
}pack_qos_SLQSRequestQosExReq_t;

/**
 * \ingroup qos
 * 
 *  Function to pack command to Triggers QoS negotiation by providing QoS parameters.
 *  This maps to SLQSQosGetQosInfo
 *
 *  \param[out]  pCtx
 *               - See \ref pack_qmi_t for more information
 *
 *  \param[in,out]  pReqBuf
 *                  - Buffer for packed QMI command to be provided by the host application
 *                  - Minimum expected size is 2048 bytes
 *
 *  \param[in,out]  pLen
 *                  - On input, size of pReqBuf
 *                  - On ouptut, number of bytes actually packed
 *		
 *  \param[in] pRequestQosExReq
 *              - Request to trigger QoS negotiation by providing QoS parameters
 *              - \sa pack_qos_SLQSRequestQosExReq_t
 *          
 *  \return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  \sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int pack_qos_SLQSQosExRequest (
        pack_qmi_t *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen,
        pack_qos_SLQSRequestQosExReq_t *pRequestQosExReq
        );

/**
 * \ingroup qos
 * 
 * This structure contains the Tx or rX QoS Flow Parameters Error
 *  \param tx_rx_qos_flow_error_len [in][out]
 *          - Number of tx_qos_flow_error. 
 *
 *  \param pTxRx_qos_flow_error [out]
 *          - Tx QoS flow parameters error mask.
 *           - Values:
 *              - QMI_QOS_IP_FLOW_MASK_NONE (0x0000000000000000) - No parameters
 *              - QMI_QOS_IP_FLOW_MASK_TRF_CLASS (0x0000000000000001) - Traffic class
 *              - QMI_QOS_IP_FLOW_MASK_DATA_RATE_MIN_MAX (0x0000000000000002) - Data rate min/max
 *              - QMI_QOS_IP_FLOW_MASK_DATA_RATE_TOK_BUCKET (0x0000000000000004) - Data rate token bucket
 *              - QMI_QOS_IP_FLOW_MASK_LATENCY (0x0000000000000008) - Latency
 *              - QMI_QOS_IP_FLOW_MASK_JITTER (0x0000000000000010) - Jitter
 *              - QMI_QOS_IP_FLOW_MASK_PKT_ERR_RATE (0x0000000000000020) - Packet error rate
 *              - QMI_QOS_IP_FLOW_MASK_MIN_POLICED_PKT_SIZE (0x0000000000000040) - Minimum policed packet size
 *              - QMI_QOS_IP_FLOW_MASK_MAX_ALLOWED_PKT_SIZE (0x0000000000000080) - Maximum allowed packet size
 *              - QMI_QOS_IP_FLOW_MASK_3GPP_RES_BER (0x0000000000000100) - 3GPP residual bit error rate (BER)
 *              - QMI_QOS_IP_FLOW_MASK_3GPP_TRF_PRI (0x0000000000000200) - 3GPP traffic handling priority
 *              - QMI_QOS_IP_FLOW_MASK_3GPP2_PROFILE_ID (0x0000000000000400) - 3GPP2 profile ID
 *              - QMI_QOS_IP_FLOW_MASK_3GPP2_FLOW_PRIORITY (0x0000000000000800) - 3GPP2 flow priority
 *              - QMI_QOS_IP_FLOW_MASK_3GPP_IM_CN_FLAG (0x0000000000001000) - 3GPP IM CN subsystem signaling flag
 *              - QMI_QOS_IP_FLOW_MASK_3GPP_SIG_IND (0x0000000000002000) - 3GPP signaling indication
 *              - QMI_QOS_IP_FLOW_MASK_LTE_QCI (0x0000000000004000) - LTE QOS class identifier
 *              - QMI_QOS_IP_FLOW_MASK_5G_QCI (0x0000000000008000) - 5G QOS class identifier
 *              - QMI_QOS_IP_FLOW_MASK_AVG_WINDOW (0x0000000000010000) - Averaging window
 */
typedef struct
{
    uint8_t tx_rx_qos_flow_error_len;
    uint32_t *pTxRx_qos_flow_error;
}unpack_qos_TxRxQoSFlowParamError;

/**
 * \ingroup qos
 * 
 * This structure contains the Tx or Rx QoS Filter Parameters Error
 *  \param tx_rx_qos_filter_error_len [in][out]
 *          - Number of sets of the tx_rx_qos_filter_error
 *
 *  \param pTxRx_qos_filter_error [out]
 *          - Tx QoS filter parameters error mask.
 *           - Values:
 *              - QMI_QOS_FILTER_PARAM_NONE (0x0000000000000000) - No errors
 *              - QMI_QOS_FILTER_PARAM_IP_VERSION (0x0000000000000001) - IP version
 *              - QMI_QOS_FILTER_PARAM_IPV4_SRC_ADDR (0x0000000000000002) - IPv4 source address
 *              - QMI_QOS_FILTER_PARAM_IPV4_DEST_ADDR (0x0000000000000004) - IPv4 destination address
 *              - QMI_QOS_FILTER_PARAM_IPV4_TOS (0x0000000000000008) - IPv4 type of service
 *              - QMI_QOS_FILTER_PARAM_IPV6_SRC_ADDR (0x0000000000000010) - IPv6 source address
 *              - QMI_QOS_FILTER_PARAM_IPV6_DEST_ADDR (0x0000000000000020) - IPv6 destination address
 *              - QMI_QOS_FILTER_PARAM_IPV6_TRF_CLS (0x0000000000000040) - IPv6 traffic class
 *              - QMI_QOS_FILTER_PARAM_IPV6_FLOW_LABEL (0x0000000000000080) - IPv6 flow label
 *              - QMI_QOS_FILTER_PARAM_XPORT_PROT (0x0000000000000100) - Transport protocol
 *              - QMI_QOS_FILTER_PARAM_TCP_SRC_PORT (0x0000000000000200) - TCP source port
 *              - QMI_QOS_FILTER_PARAM_TCP_DEST_PORT (0x0000000000000400) - TCP destination port
 *              - QMI_QOS_FILTER_PARAM_UDP_SRC_PORT (0x0000000000000800) - UDP source port
 *              - QMI_QOS_FILTER_PARAM_UDP_DEST_PORT (0x0000000000001000) - UDP destination port
 *              - QMI_QOS_FILTER_PARAM_ICMP_TYPE (0x0000000000002000) - ICMP type
 *              - QMI_QOS_FILTER_PARAM_ICMP_CODE (0x0000000000004000) - ICMP code
 *              - QMI_QOS_FILTER_PARAM_ESP_SPI (0x0000000000008000) - Encapsulating SPI
 *              - QMI_QOS_FILTER_PARAM_AH_SPI (0x0000000000010000) - Authentication header SPI
 */
typedef struct
{
    uint8_t tx_rx_qos_filter_error_len;
    uint32_t *pTxRx_qos_filter_error;
}unpack_qos_TxRxQoSFilterParamError;

/**
 * \ingroup qos
 * 
 * This structure contains the QoS Granted Flow
 *  \param pQos_id [OUT]
 *          - Identifier for the QoS flow requested. 
 *
 *  \param pTxQoSFlowParamError [OUT]
 *          - Tx QoS Flow Parameters Error.
 *          - \sa unpack_qos_TxRxQoSFlowParamError
 * 
 *  \param pRxQoSFlowParamError [OUT]
 *          - Rx QoS Flow Parameters Error.
 *          - \sa unpack_qos_TxRxQoSFlowParamError
 * 
 *  \param pTxQoSFilterParamError [OUT]
 *          - Tx QoS Filter Parameters Error
 *          - \sa unpack_qos_TxRxQoSFilterParamError
 * 
 *  \param pRxQoSFilterParamError [OUT]
 *          - Rx QoS Filter Parameters Error
 *          - \sa unpack_qos_TxRxQoSFilterParamError 
 */
typedef struct 
{
    /* Response parameters */
    uint32_t                   *pQos_id;
    unpack_qos_TxRxQoSFlowParamError   *pTxQoSFlowParamError;
    unpack_qos_TxRxQoSFlowParamError   *pRxQoSFlowParamError;
    unpack_qos_TxRxQoSFilterParamError *pTxQoSFilterParamError;
    unpack_qos_TxRxQoSFilterParamError *pRxQoSFilterParamError;

    swi_uint256_t  ParamPresenceMask;
}unpack_qos_SLQSQosRequestQosExResp_t;

/**
 * \ingroup qos
 * 
 *  Function to unpack the response to Triggers QoS negotiation by providing QoS parameters
 *
 *  \param[in]  pResp
 *              - Response from modem
 *
 *  \param[in]  respLen
 *              - Length of pResp from modem
 *
 *  \param[out]  pOutput
 *               - See \ref unpack_qos_SLQSQosRequestQosExResp_t for more information
 *
 *  \return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  \sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int unpack_qos_SLQSQosExRequest(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_qos_SLQSQosRequestQosExResp_t *pOutput
        );

/**
 *  Structure that contains the QoS Flow State
 *  \param qos_id
 *          - QoS identifier
 *
 *  \param new_flow
 *          - Values :
 *			 - 0 - Existing flow
 *			 - 1 - Newly added flow
 *
 *  \param state_change
 *          - Flow state change flow.
 *			 - Values:
 *			 - QOS_FLOW_ACTIVATED (0) - Flow activated
 *			 - QOS_FLOW_MODIFIED (1) - Flow modified
 *			 - QOS_FLOW_DELETED (2) - Flow deleted
 *			 - QOS_FLOW_SUSPENDED (3) - Flow suspended
 *			 - QOS_FLOW_ENABLED (4) - Flow enabled
 *			 - QOS_FLOW_DISABLED (5) - Flow disabled
 *			 - QOS_FLOW_REBIND (6) - Flow rebind
 *
 */

typedef struct
{
	uint32_t   qos_id;
	uint8_t    new_flow;
	uint32_t   state_change;
}unpack_qos_QmiCbkQosFlowStatus_t;

/**
 *  Structure that contains the QoS Flow Granted
 *
 *  \param	flow_valid_params
 *          - Mask of parameters that are valid for this flow.
 *			 - Values:
 *				- QMI_QOS_IP_FLOW_MASK_NONE (0x0000000000000000) - No parameters
 *				- QMI_QOS_IP_FLOW_MASK_TRF_CLASS (0x0000000000000001) - Traffic class
 *				- QMI_QOS_IP_FLOW_MASK_DATA_RATE_MIN_MAX (0x0000000000000002) - Data rate min/max
 *				- QMI_QOS_IP_FLOW_MASK_DATA_RATE_TOK_BUCKET (0x0000000000000004) - Data rate token bucket
 *				- QMI_QOS_IP_FLOW_MASK_LATENCY (0x0000000000000008) - Latency
 *				- QMI_QOS_IP_FLOW_MASK_JITTER (0x0000000000000010) - Jitter
 *				- QMI_QOS_IP_FLOW_MASK_PKT_ERR_RATE (0x0000000000000020) - Packet error rate
 *				- QMI_QOS_IP_FLOW_MASK_MIN_POLICED_PKT_SIZE (0x0000000000000040) - Minimum policed packet size
 *				- QMI_QOS_IP_FLOW_MASK_MAX_ALLOWED_PKT_SIZE (0x0000000000000080) - Maximum allowed packet size
 *				- QMI_QOS_IP_FLOW_MASK_3GPP_RES_BER (0x0000000000000100) - 3GPP residual bit error rate (BER)
 *				- QMI_QOS_IP_FLOW_MASK_3GPP_TRF_PRI (0x0000000000000200) - 3GPP traffic handling priority
 *				- QMI_QOS_IP_FLOW_MASK_3GPP2_PROFILE_ID (0x0000000000000400) - 3GPP2 profile ID
 *				- QMI_QOS_IP_FLOW_MASK_3GPP2_FLOW_PRIORITY (0x0000000000000800) - 3GPP2 flow priority
 *				- QMI_QOS_IP_FLOW_MASK_3GPP_IM_CN_FLAG (0x0000000000001000) - 3GPP IM CN subsystem signaling flag
 *				- QMI_QOS_IP_FLOW_MASK_3GPP_SIG_IND (0x0000000000002000) - 3GPP signaling indication
 *				- QMI_QOS_IP_FLOW_MASK_LTE_QCI (0x0000000000004000) - LTE QOS class identifier
 *				- QMI_QOS_IP_FLOW_MASK_5G_QCI (0x0000000000008000) - 5G QOS class identifier
 *				- QMI_QOS_IP_FLOW_MASK_AVG_WINDOW (0x0000000000010000) - Averaging window
 *
 *  \param ip_flow_trf_cls
 *          - Requested traffic class.
 *			 - Values:
 *				- QOS_IP_TRF_CLS_CONVERSATIONAL (0) - IP traffic class conversational
 *				- QOS_IP_TRF_CLS_STREAMING (1)  -  IP traffic class streaming
 *				- QOS_IP_TRF_CLS_INTERACTIVE (2)  -  IP traffic class interactive
 *				- QOS_IP_TRF_CLS_BACKGROUND (3) - IP traffic class background
 *
 *  \param data_rate_max
 *			- Flow state change flow.
 *
 *  \param guaranteed_rate
 *			 - Minimum guaranteed data rate (bits per second).
 *
 *  \param peak_rate
 *		- Maximum rate at which data can be transmitted when the token bucket is full (bits per second).
 *
 *	\param token_rate
 *		- Rate at which tokens are put in the token bucket (bits per second); a token must be present in the bucket to send a byte of data.
 *
 *	\param bucket_size
 *		- Maximum number of tokens that can be accumulated at any instance (bytes); controls the size of the burst that is allowed at any given time.
 *
 *	\param ip_flow_latency
 *		- Maximum delay (in milliseconds) that can be tolerated by an IP packet during transfer through the wireless link.
 *
 *	\param ip_flow_jitter
 *		- Difference between the maximum and minimum latency (in milliseconds) that can be tolerated by an IP packet during the transfer through the wireless link.
 *
 *	\param ip_flow_pkt_error_rate_multiplier
 *		- Factor m in calculating packet error rate: E = m*10**(-p)
 *
 *	\param ip_flow_pkt_error_rate_exponent
 *		- Factor p in calculating packet error rate: E = m*10**(-p)
 *
 *	\param ip_flow_min_policed_packet_size
 *		- Integer that defines the minimum packet size (in bytes) that will be policed for QoS guarantees. Any IP packets that are smaller than the minimum specified
 *		  policed size may not receive the requested QoS.
 *
 *	\param ip_flow_max_allowed_packet_size
 *		- Integer that defines the maximum packet size (in bytes) allowed in the IP flow. Any IP packets greater in size than the maximum allowed packet size are not queued for transmission.
 *
 *	param ip_flow_3gpp_residual_bit_error_rate
 *		- Indicates the undetected BER for each IP flow in the delivered packets. Applies only to 3GPP networks.
 *		 -Values:
 *			- QOS_FLOW_3GPP_RES_BIT_ERR_RATE1 (0) - 5*10-2
 *			- QOS_FLOW_3GPP_RES_BIT_ERR_RATE2 (1) - 1*10-2
 *			- QOS_FLOW_3GPP_RES_BIT_ERR_RATE3 (2) - 5*10-3
 *			- QOS_FLOW_3GPP_RES_BIT_ERR_RATE4 (3) - 4*10-3
 *			- QOS_FLOW_3GPP_RES_BIT_ERR_RATE5 (4) - 1*10-3
 *			- QOS_FLOW_3GPP_RES_BIT_ERR_RATE6 (5) - 1*10-4
 *			- QOS_FLOW_3GPP_RES_BIT_ERR_RATE7 (6) - 1*10-5
 *			- QOS_FLOW_3GPP_RES_BIT_ERR_RATE8 (7) - 1*10-6
 *			- QOS_FLOW_3GPP_RES_BIT_ERR_RATE9 (8) - 6*10-8
 *
 *	\param ip_flow_3gpp_traffic_handling_priority
 *		- Defines the relative priority of the flow. Applies only to 3GPP networks.
 *		 - Values:
 *			- QOS_FLOW_3GPP_TRAFFIC_HANDLING_PRI1 (0) - Priority level 1
 *			- QOS_FLOW_3GPP_TRAFFIC_HANDLING_PRI2 (1) - Priority level 2
 *			- QOS_FLOW_3GPP_TRAFFIC_HANDLING_PRI3 (2) - Priority level 3
 *
 *	\param ip_flow_3gpp2_profile_id
 *			- A profile ID is shorthand for a defined set of QoS flow parameters specified by the network; to be present while requesting QoS for a CDMA device.
 *
 *	\param ip_flow_3gpp2_flow_priority
 *			- Flow priority used by the network in case of contention between flows with the same QoS. This parameter applies to CDMA devices.
 *
 *	\param ip_flow_3gpp_im_cn_flag
 *			- IM CN subsystem signaling flag. This parameter applies only to 3GPP networks.
 *			 - Values:
 *    - 0x00 - FALSE
 *    - 0x01 - TRUE
 *
 *	\param ip_flow_3gpp_sig_ind
 *			- This parameter applies only to 3GPP networks.
 * 			 - Values:
 *    - 0x00 - FALSE
 *    - 0x01 - TRUE
 *
 *	\param ip_flow_lte_qci
 *			- QoS Class Identifier (QCI) is a required parameter to request QoS in LTE QCI.
 *			 - Values:
 *				- QCI value 0 requests the network to assign the appropriate QCI value
 *				- QCI values 1-4, 65, 66 are associated with guaranteed bitrates
 *				- QCI values 5-9, 69, 70 are associated with nonguaranteed bitrates, so the values specified as guaranteed and maximum bitrates are ignored For more detailed information, refer to TA 23.203
 *
*/
typedef struct
{
	uint64_t	flow_valid_params;
	uint32_t	ip_flow_trf_cls;
	uint64_t	data_rate_max;
	uint64_t	guaranteed_rate;
	uint32_t	peak_rate;
	uint32_t	token_rate;
	uint32_t	bucket_size;
	uint32_t	ip_flow_latency;
    uint32_t	ip_flow_jitter;
    uint16_t	ip_flow_pkt_error_rate_multiplier;
	uint16_t	ip_flow_pkt_error_rate_exponent;
	uint32_t	ip_flow_min_policed_packet_size;
	uint32_t	ip_flow_max_allowed_packet_size;
	uint32_t	ip_flow_3gpp_residual_bit_error_rate;
	uint32_t	ip_flow_3gpp_traffic_handling_priority;
	uint16_t	ip_flow_3gpp2_profile_id;
	uint8_t		ip_flow_3gpp2_flow_priority;
	uint8_t		ip_flow_3gpp_im_cn_flag;
	uint8_t		ip_flow_3gpp_sig_ind;
	uint32_t	ip_flow_lte_qci;
}unpack_qos_QmiCbkQosFlowGranted_t;

/**
 *  Structure that contains the QoS Filter
 *
 *  \param	ip_version
 *			- Depending on the IP version set, either the IPv4 or the IPv6 information is valid.
 *			 - Values:
 *				- QOS_IP_FAMILY_IPV4 (0x04) - IPv4 family.
 *				- QOS_IP_FAMILY_IPV6 (0x06) - IPv6 family.
 *
 *  \param	valid_params_ipv4
 *			- The bits set in this mask denote which parameters contain valid values.
 *			 - Values:
 *				- QMI_QOS_IPV4_FILTER_MASK_NONE (0x0000000000000000) - No parameters
 *				- QMI_QOS_IPV4_FILTER_MASK_SRC_ADDR (0x0000000000000001) - IPv4 source address
 *				- QMI_QOS_IPV4_FILTER_MASK_DEST_ADDR (0x0000000000000002) - IPv4 destination address
 *				- QMI_QOS_IPV4_FILTER_MASK_TOS (0x0000000000000004) - IPv4 type of service
 *
 *  \param	ipv4_addr_1
 *			- IPv4 address.
 *
 *  \param	subnet_mask_1
 *			- IPv4 subnet mask.
 *
 *  \param	ipv4_addr_2
 *			- IPv4 address.
 *
 *  \param	subnet_mask_2
 *			- IPv4 subnet mask.
 *
 *  \param	val_ipv4
 *			- Type of service value.
 *
 *  \param	mask_ipv4
 *			- Type of service mask.
 *
 *  \param	valid_params_ipv6
 *			- The bits set in this mask denote which parameters contain valid values.
 *			 - Values:
 *				- QMI_QOS_IPV6_FILTER_MASK_NONE (0x0000000000000000) - No parameters
 *				- QMI_QOS_IPV6_FILTER_MASK_SRC_ADDR (0x0000000000000001) - IPv6 source address
 *				- QMI_QOS_IPV6_FILTER_MASK_DEST_ADDR (0x0000000000000002) - IPv6 destination address
 *				- QMI_QOS_IPV6_FILTER_MASK_TRAFFIC_CLASS (0x0000000000000004) - IPv6 traffic class
 *				- QMI_QOS_IPV6_FILTER_MASK_FLOW_LABEL (0x0000000000000008) - IPv6 flow label
 *
 *  \param	ipv6_address_1[16]
 *			- IPv6 address.
 *
 *  \param	prefix_len_1
 *			- IPv6 address prefix length.
 *
 *  \param	ipv6_address_2[16]
 *			- IPv6 address.
 *
 *  \param	prefix_len_2
 *			- IPv6 address prefix length.
 *
 *  \param	val_ipv6
 *			- Traffic class value.
 *
 *  \param	mask_ipv6
 *			- Traffic class mask.
 *
 *  \param	flow_label_ipv6
 *			- IPv6 flow label.
 *
 *  \param	xport_protocol
 *			- Depending on the value in xport_protocol, only one field of icmp_info, tcp_info, udp_info, esp_info, or ah_info is valid.
 *			- QOS_PROTO_NONE implies that no transport level protocol parameters are valid.
 *			 - Values:
 *				- QOS_PROTO_NONE (0x00) - No transport protocol
 *				- QOS_PROTO_ICMP (0x01) - Internet Control Messaging Protocol
 *				- QOS_PROTO_TCP (0x06) - Transmission Control Protocol
 *				- QOS_PROTO_UDP (0x11) - User Datagram Protocol
 *				- QOS_PROTO_ESP (0x32) - Encapsulating Security Payload Protocol
 *				- QOS_PROTO_AH (0x33) - Authentication Header Protocol
 *				- QOS_PROTO_ICMPV6 (0x3A) - Internet Control Messaging Protocol for IPV6
 *
 *  \param	valid_params_port_1
 *			- The bits set in this mask denote which parameters contain valid values.
 *			 - Values:
 *				- QMI_QOS_PORT_INFO_FILTER_MASK_NONE (0x0000000000000000) - No parameters
 *				- QMI_QOS_PORT_INFO_FILTER_MASK_SRC_PORT (0x0000000000000001) - Source port
 *				- QMI_QOS_PORT_INFO_FILTER_MASK_DEST_PORT (0x0000000000000002) - Destination port
 *
 *  \param	port_1
 *			- Port
 *
 *  \param	range_1
 *			- range
 *
 *  \param	port_2
 *			- Port
 *
 *  \param	range_2
 *			- range
 *
 *  \param	valid_params_port_2
 *			- The bits set in this mask denote which parameters contain valid values.
 *			 - Values:
 *				- QMI_QOS_PORT_INFO_FILTER_MASK_NONE (0x0000000000000000) - No parameters
 *				- QMI_QOS_PORT_INFO_FILTER_MASK_SRC_PORT (0x0000000000000001) - Source port
 *				- QMI_QOS_PORT_INFO_FILTER_MASK_DEST_PORT (0x0000000000000002) - Destination port
 *
 *  \param	port_3
 *			- Port
 *
 *  \param	range_3
 *			- range
 *
 *  \param	port_4
 *			- Port
 *
 *  \param	range_4
 *			- Range
 *
 *  \param	valid_params_icmp
 *			- The bits set in this mask denote which parameters contain valid values.
 *			 - Values:
 *				- QMI_QOS_ICMP_FILTER_MASK_NONE (0x0000000000000000) - No parameters
 *				- QMI_QOS_ICMP_FILTER_MASK_MSG_TYPE (0x0000000000000001) - Message type
 *				- QMI_QOS_ICMP_FILTER_MASK_MSG_CODE (0x0000000000000002) - Message code
 *
 *  \param	type_icmp
 *			- ICMP type.
 *
 *  \param	code_icmp
 *			- ICMP code.
 *
 *  \param	valid_params_spi_1
 *			- The bits set in this mask denote which parameters contain valid values.
 *			 - Values:
 *				- QMI_QOS_IPSEC_FILTER_MASK_NONE (0x0000000000000000) - No parameters
 *				- QMI_QOS_IPSEC_FILTER_MASK_SPI (0x0000000000000001) - Security parameter index
 *
 *  \param	spi_1
 *			- Security parameter index for IPSec.
 *
 *  \param	valid_params_spi_2
 *			- The bits set in this mask denote which parameters contain valid values.
 *			 - Values:
 *				- QMI_QOS_IPSEC_FILTER_MASK_NONE (0x0000000000000000) - No parameters
 *				- QMI_QOS_IPSEC_FILTER_MASK_SPI (0x0000000000000001) - Security parameter index
 *
 *  \param	spi_2
 *			- Security parameter index for IPSec.
 *
 *  \param	filter_id
 *			- Unique identifier for each filter.
 *
 *  \param	filter_precedence
 *			- Specifies the order in which filters are applied. A lower numerical value has a higher precedence
 *
*/
typedef struct
{
	uint8_t		ip_version;
	uint64_t	valid_params_ipv4;
	uint32_t	ipv4_addr_1;
	uint32_t	subnet_mask_1;
	uint32_t	ipv4_addr_2;
	uint32_t	subnet_mask_2;
	uint8_t		val_ipv4;
	uint8_t		mask_ipv4;
	uint64_t	valid_params_ipv6;
	uint8_t		ipv6_address_1[16];
	uint8_t		prefix_len_1;
	uint8_t		ipv6_address_2[16];
	uint8_t		prefix_len_2;
	uint8_t		val_ipv6;
	uint8_t		mask_ipv6;
	uint32_t	flow_label_ipv6;
	uint32_t	xport_protocol;
	uint64_t	valid_params_port_1;
	uint16_t	port_1;
	uint16_t	range_1;
	uint16_t	port_2;
	uint16_t	range_2;
	uint64_t	valid_params_port_2;
	uint16_t	port_3;
	uint16_t	range_3;
	uint16_t	port_4;
	uint16_t	range_4;
	uint64_t	valid_params_icmp;
	uint8_t		type_icmp;
	uint8_t		code_icmp;
	uint64_t	valid_params_spi_1;
	uint32_t	spi_1;
	uint64_t	valid_params_spi_2;
	uint32_t	spi_2;
	uint16_t	filter_id;
	uint16_t	filter_precedence;
}unpack_qos_QmiCbkQosFilter_t;

/**
 *  Structure that contains the QoS Filters
 *
 *  \param	qos_filters_len
 *          - Number of sets of the following elements
 *  \param	qos_filters
 *          - Array of unpack_qos_QmiCbkQosFilter_t elements
*/
typedef struct
{
    uint8_t		                 qos_filters_len;
    unpack_qos_QmiCbkQosFilter_t qos_filters[LITEQMI_MAX_QOS_FILTERS];
}unpack_qos_QmiCbkQosFilters_t;

/**
 *  Structure that contains the QoS Tx Filter Match All
 *
 *  \param	tx_filter_match_all_len
 *          - Number of sets of the following filter_id
 *	\param filter_id
 *			- The filter ID identifying the filter that has match-all capability.
*/
typedef struct
{
	uint8_t	 tx_filter_match_all_len;
	uint16_t filter_id[255];
}unpack_qos_QmiCbkQosTxFilterMatchAll_t;

/*
 * Name:    unpack_qos_SLQSQosGlobalQosFlow_ind_t
 *
 * Purpose: Structure used to store Indication of a change of state in a QOS flow.
 *
 *	\param pQosFlowStatus;
 *			- QoS Flow State
 *			- Bit to check in ParamPresenceMask - <B>1</B>
 *
 *	\param pTxQosFlowGranted
 *			- Tx QoS Flow Granted
 *			- Bit to check in ParamPresenceMask - <B>0x10</B>
 *
 *	\param pRxQosFlowGranted
 *			- Rx QoS Flow Granted
 *			- Bit to check in ParamPresenceMask - <B>0x11</B>
 *
 *	\param pTxQosFilters
 *			- Tx QoS Filters Filters that apply to a granted Tx QoS flow.
 *			- Bit to check in ParamPresenceMask - <B>0x12</B>
 *
 *	\param pRxQosFilters
 *			- Rx QoS Filters Filters that apply to a granted Rx QoS flow.
 *			- Bit to check in ParamPresenceMask - <B>0x13</B>
 *
 *	\param pFlow_type
 *			- QoS Flow Type
 *			- Indicates whether the QoS flow type is network-initiated or UE-initiated.
 *			 - Values:
 *				- QOS_FLOW_UE_INITIATED_ QOS(0) - UE-initiated QoS flow
 *				- QOS_FLOW_NETWORK_INITIATED_QOS (1) - Network-initiated QoS flow
 *			- Bit to check in ParamPresenceMask - <B>0x14</B>
 *
 *	\param pBearer_id
 *			- Bearer ID or Radio Link Protocol (RLP) ID of the activated flow.
 *			- Bit to check in ParamPresenceMask - <B>0x15</B>
 *
 *	\param pFc_seq_num
 *			- The sequence number of each flow enable and disable event. Whenever the flow is disabled, the sequence number is incremented. The sequence number remains the same when the flow is enabled
 *			- Bit to check in ParamPresenceMask - <B>0x16</B>
 *
 *	\param pTx_5g_qci
 *			- 5G Tx QoS Class Identifier (QCI). Valid if flow_valid_params of Tx QoS Flow Granted TLV has a QMI_QOS_IP_FLOW_MASK_5G_QCI bit set.
 *			- Bit to check in ParamPresenceMask - <B>0x17</B>
 *
 *	\param pRx_5g_qci
 *			- 5G Rx QoS Class Identifier (QCI). Valid if flow_valid_params of Rx QoS Flow Granted TLV has a QMI_QOS_IP_FLOW_MASK_5G_QCI bit set.
 *			- Bit to check in ParamPresenceMask - <B>0x18</B>
 *
 *	\param pTx_averaging_window
 *			- Represents the duration in ms over which the guaranteed flow bit rate (GFBR) and maximum flow bit rate (MFBR) shall be calculated. Valid if flow_valid_params
 *			- of Tx QoS Flow Granted TLV has a QMI_QOS_IP_FLOW_MASK_AVG_WINDOW bit set.
 *			- Bit to check in ParamPresenceMask - <B>0x19</B>
 *
 *	\param pRx_averaging_window
 *			- Represents the duration in ms over which the GFBR and MFBR shall be calculated. Valid if flow_valid_params of Rx QoS Flow Granted TLV has a QMI_QOS_IP_FLOW_MASK_AVG_WINDOW bit set.
 *			- Bit to check in ParamPresenceMask - <B>0x1A</B>
 *
 *	\param TxFilterMatchAll
 *			- Tx Filter Match All, List of filter IDs that have match-all capability.
 *			- Bit to check in ParamPresenceMask - <B>0x1B</B>
 *
 *	\param ParamPresenceMask
 *			- bitmask representation to indicate valid parameters.
 */
typedef struct
{
	unpack_qos_QmiCbkQosFlowStatus_t	*pQosFlowStatus;
	unpack_qos_QmiCbkQosFlowGranted_t	*pTxQosFlowGranted;
	unpack_qos_QmiCbkQosFlowGranted_t	*pRxQosFlowGranted;
	unpack_qos_QmiCbkQosFilters_t		*pTxQosFilters;
	unpack_qos_QmiCbkQosFilters_t		*pRxQosFilters;
	uint32_t							*pFlow_type;
	uint8_t								*pBearer_id;
	uint16_t							*pFc_seq_num;
	uint32_t							*pTx_5g_qci;
	uint32_t							*pRx_5g_qci;
	uint16_t							*pTx_averaging_window;
	uint16_t							*pRx_averaging_window;
	unpack_qos_QmiCbkQosTxFilterMatchAll_t *pTxFilterMatchAll;
	swi_uint256_t						ParamPresenceMask;
} unpack_qos_SLQSQosGlobalQosFlow_ind_t;

/**
 * \ingroup qos
 *
 *  Function to unpack the response to Triggers QoS negotiation state in a QOS flow
 *
 *  \param[in]  pResp
 *              - Response from modem
 *
 *  \param[in]  respLen
 *              - Length of pResp from modem
 *
 *  \param[out]  pOutput
 *               - See \ref unpack_qos_SLQSQosGlobalQosFlow_ind_t for more information
 *
 *  \return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  \sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int unpack_qos_SLQSQosGlobalQosFlow_ind(
	uint8_t *pResp,
	uint16_t respLen,
	unpack_qos_SLQSQosGlobalQosFlow_ind_t *pOutput
);

/**
 * \ingroup qos
 *
 * Structure that contains the QoS Indication Register
 *
 *  \param pReport_global_qos_flows
 *          - Report Global QOS Flows
 *           - Values:
 *              - 0 - Do not report
 *              - 1 - Report global QOS flows
 *              - Bit to check in ParamPresenceMask - <B>0x10</B>
 *
 *  \param pSuppress_report_flow_control
 *          - Suppress Report Flow Control
 *           - Values:
 *              0 - Report flow control events (default)
 *              1 - Do not report flow control events
 *              - Bit to check in ParamPresenceMask - <B>0x11</B>
 *
 *  \param pSuppress_network_status_ind
 *          - Suppress Network Status Indication
 *           - Values:
 *              0 - Do not suppress network status indication (default)
 *              1 - Suppress network status indication
 *              - Bit to check in ParamPresenceMask - <B>0x12</B>
 *	\param ParamPresenceMask
 *			- bitmask representation to indicate valid parameters.
 */
typedef struct
{
    /* Resquest parameters */
    uint8_t* pReport_global_qos_flows;
    uint8_t* pSuppress_report_flow_control;
    uint8_t* pSuppress_network_status_ind;
    swi_uint256_t  ParamPresenceMask;
}pack_qos_SLQSQosIndicationRegister_t;

/**
 * \ingroup qos
 *
 *  Function to pack command to Register for QoS Indications parameters.
 *
 *  \param[out]  pCtx
 *               - See \ref pack_qmi_t for more information
 *
 *  \param[in,out]  pReqBuf
 *                  - Buffer for packed QMI command to be provided by the host application
 *                  - Minimum expected size is 2048 bytes
 *
 *  \param[in,out]  pLen
 *                  - On input, size of pReqBuf
 *                  - On ouptut, number of bytes actually packed
 *
 *  \param[in] pIndicationRegister
 *              - Request to trigger QoS negotiation by providing QoS parameters
 *              - \sa pack_qos_SLQSQosIndicationRegister_t
 *
 *  \return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  \sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int pack_qos_SLQSQosIndicationRegister(
    pack_qmi_t* pCtx,
    uint8_t* pReqBuf,
    uint16_t* pLen,
    pack_qos_SLQSQosIndicationRegister_t* pIndicationRegister
);

/**
 * \ingroup qos
 * 
 * unpack QOS Indication Register struct
 */
typedef unpack_result_t  unpack_qos_SLQSQosIndicationRegister_t;

/**
 * \ingroup qos
 *
 *  Function to unpack the response to Register for QoS Indications
 *
 *  \param[in]  pResp
 *              - Response from modem
 *
 *  \param[in]  respLen
 *              - Length of pResp from modem
 *
 *  \param[out]  pOutput
 *               - See \ref unpack_qos_SLQSQosIndicationRegister_t for more information
 *
 *  \return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  \sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int unpack_qos_SLQSQosIndicationRegister(
    uint8_t* pResp,
    uint16_t respLen,
    unpack_qos_SLQSQosIndicationRegister_t *pOutput
);

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif //__LITEQMI_QOS_H__
