/**
 * \ingroup liteqmi
 * \ingroup wds
 * \file wds.h
 *
 * \section     TableWDSSOMask SO Mask
 * \li          SO mask to indicate the service option or type of application.
 *              - An SO mask value of zero indicates that
 *                this field is ignored. \n
 *              - Values:
 *                  - 0x00 - DONT_CARE
 *              - CDMA 1X SO mask:
 *                  - 0x01 - CDMA_1X_IS95
 *                  - 0x02 - CDMA_1X_IS2000
 *                  - 0x04 - CDMA_1X_IS2000_REL_A
 *              - CDMA EV-DO Rev 0 SO mask:
 *                  - 0x01 - DPA
 *              - CDMA EV-DO Rev A SO mask:
 *                  - 0x01 - DPA
 *                  - 0x02 - MFPA
 *                  - 0x04 - EMPA
 *                  - 0x08 - EMPA_EHRPD
 *              - CDMA EV-DO Rev B SO mask:
 *                  - 0x01 - DPA
 *                  - 0x02 - MFPA
 *                  - 0x04 - EMPA
 *                  - 0x08 - EMPA_EHRPD
 *                  - 0x10 - MMPA
 *                  - 0x20 - MMPA_EHRPD
 *
 * \section     TableWDSRatMask RAT Mask
 * \li          RAT mask to indicate the type of
 *              technology. A RAT mask value of zero
 *              indicates that this field is ignored.\n
 *              Values:
 *                  - 0x00 - DONT_CARE
 *                  - 0x8000 - NULL_BEARER
 *              - CDMA RAT mask:
 *                  - 0x01 - CDMA_1X
 *                  - 0x02 - EVDO_REV0
 *                  - 0x04 - EVDO_REVA
 *                  - 0x08 - EVDO_REVB
 *                  - 0x10 - EHRPD
 *                  - 0x20 - FMC
 *              - UMTS RAT mask:
 *                  - 0x01 - WCDMA
 *                  - 0x02 - GPRS
 *                  - 0x04 - HSDPA
 *                  - 0x08 - HSUPA
 *                  - 0x10 - EDGE
 *                  - 0x20 - LTE
 *                  - 0x40 - HSDPA+
 *                  - 0x80 - DC_HSDPA+
 *                  - 0x100 - 64_QAM
 *                  - 0x200 - TD-SCDMA
 *
 **/
#ifndef __LITEQMI_WDS_H__
#define __LITEQMI_WDS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include <stdint.h>

#define _LEGACY_WDS_START_NETWORK_INTERFACE_ 1

#define IPV6_ADDRESS_ARRAY_SIZE 8
#define MAX_WDS_3GPP_CONF_LTE_ATTACH_PROFILE_LIST_SIZE 24
#define PACK_WDS_IPV4                          4
#define PACK_WDS_IPV6                          6
#define BYT_STAT_STAT_MASK 0X000000C0
#define WDS_DHCP_MAX_NUM_OPTIONS       30
#define WDS_DHCP_OPTION_DATA_BUF_SIZE  2048  /* current max size of raw message in SDK process is 2048 */
#define WDS_TFTID_SOURCE_IP_SIZE 8
#define WDS_PROFILE_3GPP 0
#define WDS_PROFILE_3GPP2 1
#define WDS_MAX_STRING 255
#define WDS_AUTH_MAX_STRING 100
#define WDS_QMI_MSG_IPV6_LEN            16
#define WDS_QMI_MSG_PRIMARY_DNSV6_LEN   16
#define WDS_QMI_MSG_SECONDARY_DNSV6_LEN 16
#define WDS_LABEL_3GPP_MAX_STRING 100
#define MAX_APP_SPECIFIC_INFO 0xFF
#define MAX_APN_STRING 100

//Default max NSSAI count from AMSS and 3GPP TS 24.501
#define QMI_WDS_SWI_DEFAULT_MAX_NSSAI_COUNT 8
//Format of Slice Differentiator(SD) specified in 3GPP TS 27.007 
#define QMI_WDS_SWI_SNSSAI_SIZE 3
//Max S_NSSAI string size from AMSS
#define QMI_WDS_SWI_MAX_SNSSAI_STR_SIZE 100
//Max NSSAI string size from AMSS
#define QMI_WDS_SWI_MAX_NSSAI_STR_SIZE 350

/**
 * \ingroup wds
 * 
 *  This structure contains 3GPP LTE QoS parameters
 *  - Parameter values default to their data type's maximum unsigned value
 *    unless explicitly stated otherwise.
 *
 *  \param  QCI
 *          - QOS specified using the QOS Class Identifier (QOS) values
 *            QCI value 0    - Requests the network to assign the
 *                             appropriate QCI value
 *            QCI values 1-4 - Associated with guaranteed bit rates
 *            QCI values 5-9 - Associated with non-guaranteed bit rates
 *
 *  \param  gDlBitRate
 *          - Guaranteed DL bit rate
 *
 *  \param  maxDlBitRate
 *          - Maximum DL bit rate
 *
 *  \param  gUlBitRate
 *          - Guaranteed UL bit rate
 *
 *  \param  maxUlBitRate
 *          - Maximum UL bit rate
 *
 */
typedef struct 
{
    uint8_t QCI;
    uint32_t gDlBitRate;
    uint32_t maxDlBitRate;
    uint32_t gUlBitRate;
    uint32_t maxUlBitRate;
}LibPackQosClassID;

/**
 * \ingroup wds
 * 
 *  This structure contains traffic flow template parameters
 *  - Parameter values default to their data type's maximum unsigned value
 *    unless explicitly stated otherwise.
 *
 *  \param  filterId
 *          - Filter identifier
 *
 *  \param  eValid
 *          - Evaluation precedence index
 *
 *  \param  ipVersion
 *          - IP version number
 *            - 4 - IPv4
 *            - 6 - IPv6
 *
 *  \param  pSourceIP
 *          - Source IP address
 *           - IPv4 - Fill the first 4 uint8_ts
 *           - IPv6 - Fill all the 16 uint8_ts
 *
 *  \param  sourceIPMask
 *          - Mask value for the source address
 *
 *  \param  nextHeader
 *          - Next header/protocol value
 *
 *  \param  destPortRangeStart
 *          - Start value of the destination port range
 *
 *  \param  destPortRangeEnd
 *          - End value of the destination port range
 *
 *  \param  srcPortRangeStart
 *          - Start value of the source port range
 *
 *  \param  srcPortRangeEnd
 *          - End value of the source port range
 *
 *  \param  IPSECSPI
 *          - IPSEC security parameter index
 *
 *  \param  tosMask
 *          - TOS mask (Traffic class for IPv6)
 *
 *  \param  flowLabel
 *          - Flow label
 *
 */
typedef struct 
{
    uint8_t  filterId;
    uint8_t  eValid;
    uint8_t  ipVersion;
    uint16_t  *pSourceIP;
    uint8_t  sourceIPMask;
    uint8_t  nextHeader;
    uint16_t  destPortRangeStart;
    uint16_t  destPortRangeEnd;
    uint16_t  srcPortRangeStart;
    uint16_t  srcPortRangeEnd;
    uint32_t IPSECSPI;
    uint16_t  tosMask;
    uint32_t flowLabel;
}LibPackTFTIDParams;



/**
 * \ingroup wds
 * 
 * This structure contains the GPRS Quality Of Service Information
 *
 *  @param  precedenceClass
 *          - Precedence class
 *
 *  @param  delayClass
 *          - Delay class
 *
 *  @param  reliabilityClass
 *          - Reliability class
 *
 *  @param  peakThroughputClass
 *          - Peak throughput class
 *
 *  @param  meanThroughputClass
 *          - Mean throughput class
 *
 */
typedef struct 
{
    uint32_t precedenceClass;
    uint32_t delayClass;
    uint32_t reliabilityClass;
    uint32_t peakThroughputClass;
    uint32_t meanThroughputClass;
}LibPackGPRSRequestedQoS;


/**
 * \ingroup wds
 * 
 * This structure contains the UMTS Quality Of Service Information
 *  - Parameter values default to their data type's maximum unsigned value
 *    unless explicitly stated otherwise.
 *
 *  \param  trafficClass
 *          - 0x00 - Subscribed
 *          - 0x01 - Conversational
 *          - 0x02 - Streaming
 *          - 0x03 - Interactive
 *          - 0x04 - Background
 *          - 0xff - Invalid UMTS Quality Of Service Information.
 *
 *  \param  maxUplinkBitrate
 *          - Maximum uplink bit rate in bits/sec
 *
 *  \param  maxDownlinkBitrate
 *          - Maximum downlink bit rate in bits/sec
 *
 *  \param  grntUplinkBitrate
 *          - Guaranteed uplink bit rate in bits/sec
 *
 *  \param  grntDownlinkBitrate
 *          - Guranteed downlink bit rate in bits/sec
 *
 *  \param  qosDeliveryOrder - Qos delivery order
 *          - 0x00 - Subscribe
 *          - 0x01 - delivery order on
 *          - 0x02 - delivery order off
 *
 *  \param  maxSDUSize
 *          - Maximum SDU size
 *
 *  \param  sduErrorRatio - SDU error ratio
 *          - Target value for fraction of SDUs lost or
 *            detected as erroneous.
 *          - 0x00 - Subscribe
 *          - 0x01 - 1*10^(-2)
 *          - 0x02 - 7*10^(-3)
 *          - 0x03 - 1*10^(-3)
 *          - 0x04 - 1*10^(-4)
 *          - 0x05 - 1*10^(-5)
 *          - 0x06 - 1*10^(-6)
 *          - 0x07 - 1*10^(-1)
 *
 *  \param  resBerRatio - Residual bit error ratio
 *          - Target value for undetected bit error ratio in
 *            in the delivered SDUs.
 *          - 0x00 - Subscribe
 *          - 0x01 - 5*10^(-2)
 *          - 0x02 - 1*10^(-2)
 *          - 0x03 - 5*10^(-3)
 *          - 0x04 - 4*10^(-3)
 *          - 0x05 - 1*10^(-3)
 *          - 0x06 - 1*10^(-4)
 *          - 0x07 - 1*10^(-5)
 *          - 0x08 - 1*10^(-6)
 *          - 0x09 - 1*10^(-8)
 *
 *  \param  deliveryErrSDU - Delivery of erroneous SDUs
 *          - Indicates whether SDUs detected as erroneous shall be
 *            delivered or not.
 *          - 0x00 - Subscribe
 *          - 0x01 - 5*10^(-2)
 *          - 0x02 - 1*10^(-2)
 *          - 0x03 - 5*10^(-3)
 *          - 0x04 - 4*10^(-3)
 *          - 0x05 - 1*10^(-3)
 *          - 0x06 - 1*10^(-4)
 *          - 0x07 - 1*10^(-5)
 *          - 0x08 - 1*10^(-6)
 *          - 0x09 - 1*10^(-8)
 *
 *  \param  transferDelay - Transfer delay (ms)
 *          - Indicates the targeted time between a request to transfer an
 *            SDU at one SAP to its delivery at the other SAP in milliseconds.
 *
 *  \param  trafficPriority - Transfer handling priority
 *          - Specifies the relative importance for handling of SDUs that
 *            belong to the UMTS bearer, compared to the SDUs of other bearers.
 *
 *  \note Check trafficClass before use.
 *
 */
typedef struct 
{
    uint8_t  trafficClass;
    uint32_t maxUplinkBitrate;
    uint32_t maxDownlinkBitrate;
    uint32_t grntUplinkBitrate;
    uint32_t grntDownlinkBitrate;
    uint8_t  qosDeliveryOrder;
    uint32_t maxSDUSize;
    uint8_t  sduErrorRatio;
    uint8_t  resBerRatio;
    uint8_t  deliveryErrSDU;
    uint32_t transferDelay;
    uint32_t trafficPriority;
}LibPackUMTSQoS;

/**
 * \ingroup wds
 * 
 *  This structure contains UMTS requested QoS with Signaling Indication flag
 *  - Parameter values default to their data type's maximum unsigned value
 *    unless explicitly stated otherwise.
 *
 *  @param  UMTSReqQoS
 *          - Contains the UMTS Quality Of Service Information
 *          - See \ref LibPackUMTSQoS
 *
 *  @param  SigInd - Signaling Indication flag
 *          - TRUE  - Signaling indication ON
 *          - FALSE - Signaling indication OFF
 *
 */
typedef struct
{
    LibPackUMTSQoS UMTSReqQoS;
    uint8_t           SigInd;
}LibPackUMTSReqQoSSigInd;


/**
 * \ingroup wds
 * 
 * This structure contains pack Start Data Session Information.
 * 
 * @param pTech
 *          - Indicates the technology preference
 *              - 1 - UMTS
 *              - 2 - CDMA
 *              - 3 - eMBMS
 *              - 4 - Modem Link Label.
 *                    Modem Link is an interface for transferring data between
 *                    entities on AP and modem.
 *          - optional
 * @param pprofileid3gpp
 *          - pointer to 3GPP profile id
 *          - optional
 * @param pprofileid3gpp2
 *          - pointer to 3GPP2 profile id
 *          - optional
 * @param pAuth
 *          - Authentication type, it can be PAP or CHAP
 *          - optional
 * @param pUser
 *          - username for authentication process
 *          - optional
 * @param pPass
 *          - password for authentication process
 *          - optional
 */
typedef struct {
    uint8_t *pTech;
    uint32_t *pprofileid3gpp;
    uint32_t *pprofileid3gpp2;
    uint32_t *pAuth;
    char *pUser;
    char *pPass;
} pack_wds_SLQSStartDataSession_t;

/**
 * \ingroup wds
 *
 * This structure contains pack Start Data Session Information.
 *
 * @param pTechnology
 *          - Indicates the technology preference
 *              - 1 - UMTS
 *              - 2 - CDMA
 *              - 3 - eMBMS
 *              - 4 - Modem Link Label.
 *                    Modem Link is an interface for transferring data between
 *                    entities on AP and modem.
 *          - optional
 * @param pPrimaryDNS
 *          - pointer to Primary DNS Address Preference
 *          - optional
 * @param pSecondaryDNS
 *          - pointer to Secondary DNS Address Preference
 *          - optional
 * @param pPrimaryNBNS
 *          - pointer to Primary NetBIOS Name Server (NBNS) Address Preference
 *          - optional
 * @param pSecondaryNBNS
 *          - pointer to Secondar NetBIOS Name Server (NBNS) Address Preference
 *          - optional
 * @param pPrimaryDNSv6
 *          - pointer to Primary IPv6 DNS Address Preference
 *          - optional
 * @param pSecondaryDNSv6
 *          - pointer to Secondary IPv6 DNS Address Preference
 *          - optional
 * @param pApnName
 *          - pointer to Context Access Point Node (APN) Name
 *          - optional
 * @param pIpAddressPreference
 *          - pointer to IP Address Preference
 *          - optional
 * @param pIPAddressv6
 *          - pointer to IPv6 Address Preference
 *          - optional
 * @param pAuthenticationPreference
 *          - Authentication Preference
 *            Bitmap that indicates the authentication algorithm preference. Values:
 *            Bit 0 – PAP preference:
 *              - 0 – PAP is never performed
 *              - 1 – PAP might be performed
 *            Bit 1 – CHAP preference:
 *              - 0 – CHAP is never performed
 *              - 1 – CHAP might be performed
 *            All other bits are reserved and ignored
 *          - optional
 * @param pUserName
 *          - username for authentication process
 *          - optional
 * @param pPassword
 *          - password for authentication process
 *          - optional
 * @param pSessionId
 *          - pointer to PDU session ID.
 *          - optional
 * @param pFailureReason
 *          - pointer to failure reason
 *          - optional
 * @param pIPFamilyPreference
 *          - pointer to IP Family Preference
 *              - 2 - Non IP
 *              - 4 - IPv4
 *              - 6 - IPv6
 *              - 8 - Unspecified
 *          - optional
 * @param pEnableAutoconnect
 *          - pointer to Enable Autoconnect
 *              - 1 - Device attempts to bring up a call automatically
 *              - 0 - Default
 *          - optional
 */
typedef struct {
	uint32_t  *pTechnology;
	uint32_t  *pPrimaryDNS;
	uint32_t  *pSecondaryDNS;
	uint32_t  *pPrimaryNBNS;
	uint32_t  *pSecondaryNBNS;
	uint16_t *pPrimaryDNSv6;
	uint16_t *pSecondaryDNSv6;
	char   *pApnName;
	uint32_t  *pIpAddressPreference;
	uint16_t *pIPAddressv6;
	uint32_t  *pAuthenticationPreference;
	char   *pUserName;
	char   *pPassword;
	uint32_t  *pSessionId;
	uint32_t  *pFailureReason;
	char   *pIPFamilyPreference;
	char   *pEnableAutoconnect;
} pack_wds_SLQSStartDataSessionExp_t;

/**
 * \ingroup wds
 * 
 * This structure contains unpack Start Data Session Information.
 * 
 * @param  psid
 *         - Assigned session ID when starting a data session
 *         - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param  pFailureReason
 *          - Reason data session failed to be established
 *          - See qaGobiApiTableCallEndReasons.h for Call End Reason
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  @param  pVerboseFailReasonType
 *          - Parameter describing type of verbose failure reason
 *          - See qaGobiApiTableCallEndReasons.h for Call End Reason Type
 *          - Bit to check in ParamPresenceMask - <B>17</B>
 *
 *  @param  pVerboseFailureReason
 *          - Verbose reason explaining why call failed. Depends on
 *            verbFailReasonType parameter
 *          - See qaGobiApiTableCallEndReasons.h for Call End Reason
 *          - Bit to check in ParamPresenceMask - <B>17</B>
 *
 * @param  Tlvresult - unpack Tlv Result.
 * 
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct {
    uint32_t *psid;
    uint32_t *pFailureReason;
    uint32_t *pVerboseFailReasonType;
    uint32_t *pVerboseFailureReason;
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
} unpack_wds_SLQSStartDataSession_t;

/**
 * \ingroup wds
 * 
 * Start data session
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */
int pack_wds_SLQSStartDataSession(
        pack_qmi_t *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen,
        pack_wds_SLQSStartDataSession_t *reqArg
        );

#if _LEGACY_WDS_START_NETWORK_INTERFACE_
/**
 * \ingroup wds
 *
 * Start data session
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */
int pack_wds_SLQSStartDataSessionExp(
	pack_qmi_t *pCtx,
	uint8_t *pReqBuf,
	uint16_t *pLen,
	pack_wds_SLQSStartDataSessionExp_t *reqArg
);
#endif

/**
 * \ingroup wds
 * 
 * Start Data Session unpack
 * 
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput      response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_SLQSStartDataSession(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_wds_SLQSStartDataSession_t *pOutput
        );

/**
 * \ingroup wds
 * 
 * This structure contains unpack set packet service status callback information.
 * @param conn_status connection status.
 *              - Current link status. Values:
 *                  - 1 - DISCONNECTED
 *                  - 2 - CONNECTED
 *                  - 3 - SUSPENDED
 *                  - 4 - AUTHENTICATING
 *              - Bit to check in ParamPresenceMask - <B>1</B>
 *
 * @param reconfigReqd Indicates whether the network interface
 *        on the host needs to be reconfigured.
 *                  - Values:
 *                      - 0 - No need to reconfigure.
 *                      - 1 - Reconfiguration required.
 *              - Bit to check in ParamPresenceMask - <B>1</B>
 *
 * @param sessionEndReason Call End Reason
 *                  - See qaGobiApiTableCallEndReasons.h for Call End Reason
 *                  - Bit to check in ParamPresenceMask - <B>16</B>
 *
 * @param verboseSessnEndReasonType Verbose call end reason type
 *                  - Call end reason type. Values:
 *                      - 0 - Unspecified
 *                      - 1 - Mobile IP
 *                      - 2 - Internal
 *                      - 3 - Call Manager defined
 *                      - 6 - 3GPP Specification defined
 *                      - 7 - PPP
 *                      - 8 - EHRPD
 *                      - 9 - IPv6
 *                  - Bit to check in ParamPresenceMask - <B>17</B>
 *                  
 * @param verboseSessnEndReason Reason the call ended (verbose)
 *                  - See qaGobiApiTableCallEndReasons.h for Call End Reason
 *                  - Bit to check in ParamPresenceMask - <B>17</B>
 *
 * @param ipFamily IP family of the packet data connection.
 *                  - Values
 *                      - 4 - IPv4
 *                      - 6 - IPv6
 *                  - Bit to check in ParamPresenceMask - <B>18</B>
 *
 * @param techName Technology name of the packet data connection.
 *                  - Values
 *                      - 32767 - CDMA
 *                      - 32764 - UMTS
 *                      - 30592 - EPC
 *                      - 30590 - EMBMS
 *                      - 30584 - Modem Link Local
 *                         EPC is a logical interface to support
 *                         LTE/eHRPD handoff. It is returned if the
 *                         device supports IP session continuity.
 *                         Modem Link Local is an interface for
 *                         transferring data between entities on the
 *                         AP and modem.
 *                  - Bit to check in ParamPresenceMask - <B>19</B>
 * @param bearerID 
 *          - bearer ID (3GPP) or RLP ID (3GPP2) of the
 *            packet data connection.
 *          - Valid Values - 0 to 16
 *                  - Bit to check in ParamPresenceMask - <B>20</B>
 * @param  Tlvresult - unpack Tlv Result.
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct{
    uint8_t   conn_status;
    uint8_t   reconfigReqd;
    uint16_t  sessionEndReason;
    uint16_t  verboseSessnEndReasonType;
    uint16_t  verboseSessnEndReason;
    uint8_t   ipFamily;
    uint16_t  techName;
    uint8_t   bearerID;
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
} unpack_wds_SLQSSetPacketSrvStatusCallback_t;

/**
 * \ingroup wds
 * 
 * Set Packet Service Status Callback unpack
 * 
 * @param[in] pResp qmi response
 * @param[in] respLen length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_SLQSSetPacketSrvStatusCallback(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_wds_SLQSSetPacketSrvStatusCallback_t *pOutput
        );

/**
 * \ingroup wds
 * 
 * This structure contains pack stop data session information.
 *
 * @param psid session id
 */
typedef struct {
    uint32_t *psid;
} pack_wds_SLQSStopDataSession_t;

/**
 * \ingroup wds
 * 
 * stop data session pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */
int pack_wds_SLQSStopDataSession(
        pack_qmi_t *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen,
        pack_wds_SLQSStopDataSession_t *reqArg
        );

typedef unpack_result_t  unpack_wds_SLQSStopDataSession_t;

/**
 * \ingroup wds
 * 
 * Stop Data Session unpack
 * 
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_SLQSStopDataSession(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_wds_SLQSStopDataSession_t *pOutput
        );
/**
 * \ingroup wds
 * 
 * This structure contains the Profile Identifier Information
 *
 *  @param  profileType
 *          - Identifies the type of profile
 *            0x00 = 3GPP
 *
 *  @param  profileIndex
 *          - Index of profile whose settings were loaded prior to
 *            session parameter negotiation for the current call.
 *            If this TLV is not present, data call parameters are
 *            based on device default settings for each parameter
 *
 *  @note Data invalid when all parameters are equal to 0xff.
 *
 */
struct wds_ProfileIdentifier
{
    uint8_t profileType;
    uint8_t profileIndex;
};


/**
 * \ingroup wds
 * 
 * This structure contains the GPRS Quality Of Service Information
 *
 *  @param  precedenceClass
 *          - Precedence class
 *
 *  @param  delayClass
 *          - Delay class
 *
 *  @param  reliabilityClass
 *          - Reliability class
 *
 *  @param  peakThroughputClass
 *          - Peak throughput class
 *
 *  @param  meanThroughputClass
 *          - Mean throughput class
 *
 *  @note Data invalid when all parameters are equal to 0xffffffff.
 */
struct wds_GPRSQoS
{
    uint32_t precedenceClass;
    uint32_t delayClass;
    uint32_t reliabilityClass;
    uint32_t peakThroughputClass;
    uint32_t meanThroughputClass;
};

/**
 * \ingroup wds
 * 
 * This structure contains the PCSCFIPv4ServerAddressList Information
 *
 *  @param  numInstances
 *          - number of address following
 *
 *  @param  pscsfIPv4Addr
 *          - P-CSCF IPv4 server addresses(Max 16 address, 4 bytes each)
 *
 *  @note Data invalid when numInstances equal 0xff and pscsfIPv4Addr equal to 0xffffffff.
 */
struct wds_PCSCFIPv4ServerAddressList
{
    uint8_t  numInstances;
    uint32_t pscsfIPv4Addr[64];
};

/**
 * \ingroup wds
 * 
 * This structure contains the PCSCFFQDNAddress Information
 *
 *  @param  fqdnLen
 *          - length of the received FQDN address
 *
 *  @param  fqdnAddr
 *          - FQDN address(Max 256 characters)
 */
struct wds_PCSCFFQDNAddress
{
    uint16_t fqdnLen;
    uint8_t fqdnAddr[256];
};

/**
 * \ingroup wds
 * 
 * This structure contains the PCSCFFQDNAddressList Information
 *
 *  @param  numInstances
 *          - Number of FQDN addresses received
 *
 *  @param  pcsfFQDNAddress
 *          - FQDN address information(Max 10 addresses)
 *
 *  @note Data invalid when numInstances equal 0xff.
 */
struct wds_PCSCFFQDNAddressList
{
    uint8_t                    numInstances;
    struct wds_PCSCFFQDNAddress pcsfFQDNAddress[10];
};

/**
 * \ingroup wds
 * 
 * This structure contains the DomainName Information
 *
 *  @param  domainLen
 *          - length of the recieved Domain name
 *
 *  @param  domainName
 *          - Domain name(Max 256 characters)
 */
struct wds_Domain
{
    uint16_t domainLen;
    uint8_t domainName[256];
};

/**
 * \ingroup wds
 * 
 * This structure contains the DomainNameList Information
 *
 *  @param  numInstances
 *          - Number of Domain name receieved
 *
 *  @param  domain
 *          - Domain name information(Max 10 Domain names)
 *
 *  @note Data invalid when numInstances equal 0xff.
 */
struct wds_DomainNameList
{
    uint8_t          numInstances;
    struct wds_Domain domain[10];
};

/**
 * \ingroup wds
 * 
 * This structure contains the IPV6 Address Information
 *
 *  @param  IPV6PrefixLen
 *          - Length of the received IPv6 address in no. of bits;
 *            can take value between 0 and 128
 *              - 0xFF - Not Available
 *
 *  @param  IPAddressV6
 *          - IPv6 address(in network byte order);
 *            This is an 8-element array of 16 bit numbers,
 *            each of which is in big endian format.
 */
struct wds_IPV6AddressInfo
{
    uint8_t   IPV6PrefixLen;
    uint16_t IPAddressV6[8];
};

/**
 * \ingroup wds
 * 
 * This structure contains the IPV6 Gateway Address Information
 *
 *  @param  gwV6PrefixLen
 *          - Length of the received IPv6 Gateway address in no. of bits;
 *            can take value between 0 and 128
 *
 *  @param  IPAddressV6
 *          - IPv6 Gateway address(in network byte order);
 *            This is an 8-element array of 16 bit numbers,
 *            each of which is in big endian format.
 *
 *  @note Data invalid when IPV6PrefixLen equal 0xff.
 */
struct wds_IPV6GWAddressInfo
{
    uint8_t   gwV6PrefixLen;
    uint16_t gwAddressV6[8];
};

/**
 * \ingroup wds
 *
 * This structure contains the SNSSAI PDN Information
 *
 *  @param  pduSessionId
 *          - PDU session ID
 *
 *  @param  snssaiInfoIsValid
 *          - Indicates whether SNSSAI information is present
 *
 *  @param  sst
 *          - Slice service type; valid values are 0 to 255
 *
 *  @param  sd
 *          - Slice differentiator; value "FFFFFF" indicates no SD associated with this SST
 *
 *  @param  mappingSstPresent
 *          - Flag indicating nwhether the mapped SST is present
 *
 *  @param  mappedSst
 *          - SST value for the HPLMN to which the SST value is mapped
 *
 *  @param  mappedSd
 *          - SD value for the HPLMN to which the SD value is mapped.
 *            Value "FFFFFF" indicates no SD associated with the mapped SST
 *
 *  @param  isSnssaiResolved
 *          - Indicates whether SNSSAI is resolved
 *
 *  @param  plmnId
 *          - PLMN ID of slice
 *
 * @For_5G
 */
struct wds_NssaiPdnInfo
{
    uint8_t pduSessionId;
    uint8_t snssaiInfoIsValid;
    uint8_t sst;
    uint8_t sd[3];
    uint8_t mappingSstPresent;
    uint8_t mappedSst;
    uint8_t mappedSd[3];
    uint8_t isSnssaiResolved;
    uint8_t plmnId[3];
};

/**
 * \ingroup wds
 * 
 * This structure contains unpack get runtime settings information.
 * @param IPv4 ipv4 address
 *        - Bit to check in ParamPresenceMask - <B>30</B>
 * @param ProfileName profile name
 *        - Bit to check in ParamPresenceMask - <B>16</B>
 * @param PDPType PDP type
 *        - Bit to check in ParamPresenceMask - <B>17</B>
 * @param APNName APN name
 *        - Bit to check in ParamPresenceMask - <B>20</B>
 * @param PrimaryDNSV4 primary dns IPV4 
 *        - Bit to check in ParamPresenceMask - <B>21</B>
 * @param SecondaryDNSV4 secondary dns IPV4
 *        - Bit to check in ParamPresenceMask - <B>22</B>
 * @param UMTSGrantedQoS UMTS Granted Qos
 *        - Bit to check in ParamPresenceMask - <B>23</B>
 * @param GPRSGrantedQoS GPRS Granted QoS
 *        - Bit to check in ParamPresenceMask - <B>25</B>
 * @param Username username for authentication process
 *        - Bit to check in ParamPresenceMask - <B>27</B>
 * @param Authentication authentication for authentication process
 *        - Bit to check in ParamPresenceMask - <B>29</B>
 * @param ProfielID profile ID
 *        - Bit to check in ParamPresenceMask - <B>31</B>
 * @param GWAddressV4 Gateway IPv4
 *        - Bit to check in ParamPresenceMask - <B>32</B>
 * @param SubnetMaskV4 Subnet mask IPV4
 *        - Bit to check in ParamPresenceMask - <B>33</B>
 * @param PCSCFAddrPCO PCSCF address PCO
 *        - Bit to check in ParamPresenceMask - <B>34</B>
 * @param ServerAddrList PCSCF server address list IPV4
 *        - Bit to check in ParamPresenceMask - <B>35</B>
 * @param PCSCFFQDNAddrList PCSCF FQDN address list IPV4
 *        - Bit to check in ParamPresenceMask - <B>36</B>
 * @param PrimaryDNSV6 Primary DNS IPV6
 *        - Bit to check in ParamPresenceMask - <B>39</B>
 * @param SecondryDNSV6 Secondry DNS IPV6
 *        - Bit to check in ParamPresenceMask - <B>40</B>
 * @param Mtu actual (runtime) Maximum Transfer Unit
 *        - Bit to check in ParamPresenceMask - <B>41</B>
 * @param DomainList domain list
 *        - Bit to check in ParamPresenceMask - <B>42</B>
 * @param IPFamilyPreference ip family preference, it could be IPV4 or IPV6
 *        - Bit to check in ParamPresenceMask - <B>43</B>
 * @param IMCNflag IM control flag, value: TRUE or FALSE
 *        - Bit to check in ParamPresenceMask - <B>44</B>
 * @param Technology technology on which current packet data session is in progress
 *        - Values:
 *          - 32767 - CDMA
 *          - 32764 - UMTS
 *          - 30592 - EPC
 *          - 30584 - modem link local
 *        - Bit to check in ParamPresenceMask - <B>45</B>
 * @param IPV6AddrInfo address information IPV6
 *        - Bit to check in ParamPresenceMask - <B>37</B>
 * @param IPV6GWAddrInfo gateway address information IPV6
 *        - Bit to check in ParamPresenceMask - <B>38</B>
 * @param NssaiPdnInfo snssai pdn information
 *        - Bit to check in ParamPresenceMask - <B>50</B>
 * @param  Tlvresult - unpack Tlv Result.
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 * @For_5G
 */
typedef struct{
    uint32_t                        IPv4;
    uint8_t                         ProfileName[128];
    uint32_t                        PDPType;
    uint8_t                         APNName[128];
    uint32_t                        PrimaryDNSV4;
    uint32_t                        SecondaryDNSV4;
    LibPackUMTSQoS                  UMTSGrantedQoS;
    struct wds_GPRSQoS              GPRSGrantedQoS;
    uint8_t                         Username[128];
    uint32_t                        Authentication;
    struct wds_ProfileIdentifier    ProfileID;
    uint32_t                        GWAddressV4;
    uint32_t                        SubnetMaskV4;
    uint8_t                         PCSCFAddrPCO;
    struct wds_PCSCFIPv4ServerAddressList ServerAddrList;
    struct wds_PCSCFFQDNAddressList       PCSCFFQDNAddrList;
    uint16_t                        PrimaryDNSV6[8];
    uint16_t                        SecondaryDNSV6[8];
    uint32_t                        Mtu;
    struct wds_DomainNameList       DomainList;
    uint8_t                         IPFamilyPreference;
    uint8_t                         IMCNflag;
    uint16_t                        Technology;
    struct wds_IPV6AddressInfo      IPV6AddrInfo;
    struct wds_IPV6GWAddressInfo    IPV6GWAddrInfo;
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
    struct wds_NssaiPdnInfo         NssaiPdnInfo;
} unpack_wds_SLQSGetRuntimeSettings_t;

/**
 * \ingroup wds
 * 
 * get runtime settings unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput      response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_SLQSGetRuntimeSettings(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_wds_SLQSGetRuntimeSettings_t *pOutput
        );
/**
 * \ingroup wds
 * 
 * Network information structure
 *
 *  @param  NetworkType
 *          - Values:
 *              - 0 - 3GPP
 *              - 1 - 3GPP2
 *
 *  @param  RATMask
 *          - @ref TableWDSRatMask
 *
 *  @param  SOMask
 *          - @ref TableWDSSOMask
 */
typedef struct
{
    uint8_t  NetworkType;
    uint32_t RATMask;
    uint32_t SOMask;
}wds_currNetworkInfo;

/**
 * \ingroup wds
 * 
 * Name:    DataCallTypeTlv
 *
 * Purpose: Structure used to store data call type TLV info.
 *
 *   @param  data_call_type
 *            Values:
 *              - WDS_DATA_CALL_NONE (0x00) - None
 *              - WDS_DATA_CALL_EMBEDDED (0x01) - Embedded call (application)
 *              - WDS_DATA_CALL_TETHERED (0x02) - Tethered call
 *              - WDS_DATA_CALL_MODEM_EMBEDDED (0x03) - Modem embedded call 
 * 
 *   @param  tethered_call_type
 *            Values:
 *              - WDS_TETHERED_CALL_NONE (0x00) - Non-tethered call
 *              - WDS_TETHERED_CALL_RMNET (0x01) - RmNet call
 *              - WDS_TETHERED_CALL_DUN (0x02) - DUN call
 */
typedef struct
{
    uint8_t data_call_type;
    uint8_t tethered_call_type;
}DataCallTypeTlv_t;

/**
 * \ingroup wds
 * 
 * Name:    EVDOPageMonitorPeriodChange
 *
 * Purpose: Structure used to store EV-DO Page Monitor Period Change TLV info.
 *
 *  @param  evdo_page_monitor_period_change
 *            - EV-DO slot cycle and long sleep info.:
 * 
 *  @param  evdo_force_long_sleep
 *            -  Set to 1 if EV-DO is forced to ignore the slot cycle setting and instead sleep for
 *               long periods, potentially missing pages
 */
typedef  struct 
{
    uint8_t evdo_page_monitor_period_change;
    uint8_t evdo_force_long_sleep;
}EVDOPageMonitorPeriodChange_t;

/**
 * \ingroup wds
 * 
 * Name:    AdditionalPdnFiltersRemoved
 *
 * Purpose: Structure used to store Additional PDN Filters Removed TLV info.
 *
 *  @param  removed_filter_handles_len
 *            - Number of sets of the following removed_filter_handles
 * 
 *  @param  removed_filter_handles
 *            -  Removed filter handles. This TLV contains the list of all removed filters that
 *               were set by the client on the RmNet port. Each filter is identified by a filter handle.
 */
typedef struct
{
    uint8_t removed_filter_handles_len;
    uint32_t removed_filter_handles[255]; 
}AdditionalPdnFiltersRemoved_t;

/**
 * \ingroup wds
 * 
 * Name:    DataBearerTechnologyExtended
 *
 * Purpose: Structure used to store Data Bearer Technology Extended TLV info.
 *
 *  @param  technology
 *            - Technology type. 
 *              - Values:
 *                - WDS_BEARER_TECH_NETWORK_3GPP (0) - 3GPP
 *                - WDS_BEARER_TECH_NETWORK_3GPP2 (1) - 3GPP2
 * 
 *  @param  rat_value
 *            -  RAT value. 
 *              - Values:
 *                - WDS_BEARER_TECH_RAT_EX_NULL_BEARER (0x00) - NULL bearer
 *                - WDS_BEARER_TECH_RAT_EX_3GPP_WCDMA (0x01) - 3GPPWCDMA
 *                - WDS_BEARER_TECH_RAT_EX_3GPP_GERAN (0x02) - 3GPP GERAN
 *                - WDS_BEARER_TECH_RAT_EX_3GPP_LTE (0x03) - 3GPP LTE
 *                - WDS_BEARER_TECH_RAT_EX_3GPP_TDSCDMA (0x04) - 3GPPTD-SCDMA
 *                - WDS_BEARER_TECH_RAT_EX_3GPP_WLAN (0x05) - 3GPP WLAN
 *                - WDS_BEARER_TECH_RAT_EX_3GPP_5G (0x06) - 3GPP 5G
 *                - WDS_BEARER_TECH_RAT_EX_3GPP_MAX (0x64) - 3GPP maximum
 *                - WDS_BEARER_TECH_RAT_EX_3GPP2_1X (0x65) - 3GPP2 1X
 *                - WDS_BEARER_TECH_RAT_EX_3GPP2_HRPD (0x66) - 3GPP2 HRPD
 *                - WDS_BEARER_TECH_RAT_EX_3GPP2_EHRPD (0x67) - 3GPP2EHRPD
 *                - WDS_BEARER_TECH_RAT_EX_3GPP2_WLAN (0x68) - 3GPP2 WLAN
 *                - WDS_BEARER_TECH_RAT_EX_3GPP2_MAX (0xC8) - 3GPP2 maximum
 * 
 *  @param  so_mask
 *            - SO mask indicating the service option or type of application.
 *              An SO mask value of zero indicates that this field is ignored. 
 *             - Values:
 *                - 0x00 - SO mask unspecified 
 *                - 3GPP SO mask:
 *                  - 0x01 - WCDMA
 *                  - 0x02 - HSDPA
 *                  - 0x04 - HSUPA
 *                  - 0x08 - HSDPAPLUS
 *                  - 0x10 - DC HSDPAPLUS
 *                  - 0x20 - 64 QAM
 *                  - 0x40 - HSPA
 *                  - 0x80 - GPRS
 *                  - 0x100 - EDGE
 *                  - 0x200 - GSM
 *                  - 0x400 - S2B
 *                  - 0x800 - LTE limited service, 3GPP limited service
 *                  - 0x1000 - LTE FDD, 3GPP FDD
 *                  - 0x2000 - LTE TDD
 *                  - 0x4000 - TD-SCDMA
 *                  - 0x8000 - DC HSUPA
 *                  - 0x10000 - LTE CA DL
 *                  - 0x20000 - LTE CA UL
 *                  - 0x80000 - 4.5G
 *                  - 0x100000 - 4.5G+
 *                - 3GPP2 SO mask:
 *                  - 0x01000000 - 1X IS95
 *                  - 0x02000000 - 1X IS2000
 *                  - 0x04000000 - 1X IS2000 REL A
 *                  - 0x08000000 - HDR REV0 DPA
 *                  - 0x10000000 - HDR REVA DPA
 *                  - 0x20000000 - HDR REVB DPA
 *                  - 0x40000000 - HDR REVA MPA
 *                  - 0x80000000 - HDR REVB MPA
 *                  - 0x100000000 - HDR REVA EMPA
 *                  - 0x200000000 - HDR REVB EMPA
 *                  - 0x400000000 - HDR REVB MMPA
 *                  - 0x800000000 - HDR EVDO FMC 
 *                - 5G SO mask:
 *                  - 0x10000000000 - 5G TDD
 *                  - 0x20000000000 - 5G SUB6
 *                  - 0x40000000000 - 5G MMWAVE
 *                  - 0x80000000000 - 5G NSA
 *                  - 0x100000000000 - 5G SA              
 */
typedef struct
{
    uint32_t technology;
    uint32_t rat_value;
    uint64_t so_mask;
}DataBearerTechnologyExtended_t;

/**
 * \ingroup wds
 * 
 * Name:    DormancyResultIndicator
 *
 * Purpose: Structure used to store Dormancy Result Indicator TLV info.
 *
 *  @param  status
 *            - Values:
 *              - 0x00 - Success
 *              - 0x01 - Failure
 * 
 *  @param  dormancy_failure_reason
 *            - Values:
 *              - WDS_DORM_FAIL_NONE (0) - No failure
 *              - WDS_DORM_FAIL_RRC (1) - Failure - RRC
 *              - WDS_DORM_FAIL_DATA_ACTIVITY (2) - Failure - Data activity
 *              - WDS_DORM_FAIL_OTHER_PDN_UP (3) - Failure - Another PDN is up
 *              - WDS_DORM_FAIL_INVALID_PDN_STATE (4) - Failure - Invalid PDN state
 * 
*/
typedef struct
{
    uint8_t status;
    uint32_t dormancy_failure_reason;
}DormancyResultIndicator_t;

/**
 * \ingroup wds

 * Name:    ChannelRate
 *
 * Purpose: Structure used to store Extended Channel Rate TLV info.
 *
 * Members: 
 *          current_channel_tx_rate
 *            - Max channel Tx rate in bits per second.
 * 
 *          current_channel_tx_rate
 *            - Max channel Rx rate in bits per second.
*/
typedef struct
{
    uint32_t current_channel_tx_rate;
    uint32_t current_channel_rx_rate;
}ChannelRate_t;

/**
 * \ingroup wds
 * 
 * Name:    ExtendedChannelRate
 *
 * Purpose: Structure used to store Extended Channel Rate TLV info.
 *
 *  @param  rate_type
 *            - rate Type
 *             -values:
 *              - WDS_CHANNEL_RATE_UNIT_BPS_V01 = 0
 *              - WDS_CHANNEL_RATE_UNIT_KBPS_V01 = 1
 *              - WDS_CHANNEL_RATE_UNIT_MBPS_V01 = 2
 *              - WDS_CHANNEL_RATE_UNIT_GBPS_V01 = 3
 *              - WDS_CHANNEL_RATE_UNIT_Invalid = 0x7FFF FFFF
 * 
 *  @param  channel_tx_rate_ex
 *            - Channel Tx rate.
 * 
 *  @param  channel_rx_rate_ex
 *            - Channel Rx rate.
*/
typedef struct 
{
    uint32_t rate_type;
    uint64_t channel_tx_rate_ex;
    uint64_t channel_rx_rate_ex;
}ExtendedChannelRate_t;

/**
 * \ingroup wds
 * 
 * Name:    QmiWdsServStatusInd
 *
 * Purpose: Structure used to store all Data Bearer Notification Parameters.
 *
 *  @param  tx_ok_count
 *              - Tx Packets OK
 *                 - Number of packets transmitted without error.
 *                 - Bit to check in ParamPresenceMask - <B>0x10</B>
 *  @param  rx_ok_count
 *              - Rx Packets OK
 *                 - Number of packets received without error.  
 *                 - Bit to check in ParamPresenceMask - <B>0x11</B>
 *  @param  tx_err_count
 *              - Tx Packet Errors
 *                 - Number of outgoing packets with framing errors.
 *                 - Bit to check in ParamPresenceMask - <B>0x12</B>
 *  @param  rx_err_count
 *              - Rx Packet Errors
 *                 - Number of incoming packets with framing errors.
 *                 - Bit to check in ParamPresenceMask - <B>0x13</B>
 *  @param tx_ofl_count
 *              - Tx Overflows
 *                 - Number of packets dropped because Tx buffer overflowed (out of memory).
 *                 - Bit to check in ParamPresenceMask - <B>0x14</B>
 *  @param  rx_ofl_count
 *              - Rx Overflows
 *                 - Number of packets dropped because Rx buffer overflowed (out of memory).
 *                 - Bit to check in ParamPresenceMask - <B>0x15</B>
 *  @param  dormancy_status
 *              - Dormancy Status
 *                 - Values:
 *                   - WDS_DORMANCY_STATUS_DORMANT (0x01) - Traffic channel dormant
 *                   - WDS_DORMANCY_STATUS_ACTIVE (0x02) - Traffic channel active
 *                 - Bit to check in ParamPresenceMask - <B>0x18</B>
 *  @param  tx_ok_bytes_count 
 *              - Tx Bytes OK
 *                 - Number of bytes transmitted without error
 *                 - Bit to check in ParamPresenceMask - <B>0x19</B>
 *  @param  rx_ok_bytes_count
 *              - Rx Bytes OK
 *                 - Number of bytes received without error
 *                 - Bit to check in ParamPresenceMask - <B>0x1A</B>
 *  @param  mip_status
 *              - Status of the last MIP call (or attempt).
 *                - Values:
 *                 - 0x00 - Success
 *                 - 0 - Error code (as defined in RFC 2002)
 *                 - Bit to check in ParamPresenceMask - <B>0x1B</B>
 *  @param  data_call_status
 *              - Data Call Status Change
 *                - Values:
 *                 - WDS_DATA_CALL_UNKNOWN(0x00) - Unknown
 *                 - WDS_DATA_CALL_ACTIVATED(0x01) - Data call activated
 *                 - WDS_DATA_CALL_TERMINATED(0x02) - Data call terminate
 *                 - Bit to check in ParamPresenceMask - <B>0x1F</B>
 *  @param  current_sys
 *              - Current Preferred Data System
 *                - Values:
 *                 - WDS_CURR_PREF_SYS_UNKNOWN(0x00) - Unknown
 *                 - WDS_CURR_PREF_SYS_CDMA_1X (0x01) - CMDA_1X
 *                 - WDS_CURR_PREF_SYS_EVDO(0x02) - EVDO
 *                 - WDS_CURR_PREF_SYS_GPRS(0x03) - GPRS
 *                 - WDS_CURR_PREF_SYS_WCDMA(0x04) - WCDMA
 *                 - WDS_CURR_PREF_SYS_LTE (0x05) - LTE
 *                 - WDS_CURR_PREF_SYS_TDSCDMA(0x06) - TD-SCDMA
 *                 - Bit to check in ParamPresenceMask - <B>0x20</B>
 *  @param  dataCallType
 *              - Data Call Type
 *                 - \ref DataCallTypeTlv_t 
 *                 - Bit to check in ParamPresenceMask - <B>0x22</B>
 *  @param  eVDOPageMonitorPeriodChange
 *              - EV-DO Page Monitor Period Change
 *                 - \ref EVDOPageMonitorPeriodChange_t
 *                 - Bit to check in ParamPresenceMask - <B>0x23</B>
 *  @param  tx_dropped_count
 *              - Tx Packets Dropped
 *                 - Number of outgoing packets dropped.
 *                 - Bit to check in ParamPresenceMask - <B>0x25</B>
 *  @param  rx_dropped_count
 *              - Rx Packets Dropped
 *                 - Number of incoming packets dropped.
 *                 - Bit to check in ParamPresenceMask - <B>0x26</B>
 *  @param  uplink_flow_control
 *              - Uplink flow control status.
 *               - Values:
 *                 - 0 - Not flow controlled
 *                 - 1 - Flow controlled
 *                 - Bit to check in ParamPresenceMask - <B>0x27</B>
 *  @param  data_call_addr_family
 *              - Data Call Address Family. This TLV is sent in conjunction with the Data Call
 *                 Status Change TLV (0x1F) to indicate the IP family type of the call activated or
 *                 terminated. 
 *               - Values:
 *                 - WDS_DATA_CALL_ADDR_FAMILY_UNKNOWN (0) - Unknown
 *                 - WDS_DATA_CALL_ADDR_FAMILY_IPV4 (4) - IPv4
 *                 - WDS_DATA_CALL_ADDR_FAMILY_IPV6 (6) - IPv6
 *                 - Note: For legacy control points that do not bind to an IP type or do not specify
 *                   the IP type when bringing up a call, unknown is returned if the call fails.
 *                 - Bit to check in ParamPresenceMask - <B>0x28</B>
 *  @param  additionalPdnFiltersRemoved
 *              - Additional PDN Filters Removed
 *               - Bit to check in ParamPresenceMask - <B>0x29</B>
 *  @param  dataBearerTechnologyExtended
 *              - Data Bearer Technology Extended
 *              - \ref DataBearerTechnologyExtended_t
 *               - Bit to check in ParamPresenceMask - <B>0x2A</B>
 *  @param  uplink_fc_seq_num
 *              - Uplink Flow Control Sequence Number
 *                 - Sequence number of each flow enable and disable event. This TLV is sent with the Uplink 
 *                    Flow Control TLV. Each time the flow is disabled (flow controlled), the sequence number 
 *                    is increased. It can be used in conjunction with the QMAP in-band flow control sequence 
 *                    number to determine the validity of the message received by the control point.
 *                 - Bit to check in ParamPresenceMask - <B>0x2B</B>
 *  @param  dormancyResultIndicator
 *              - Dormancy Result Indicator
 *                 - \ref DormancyResultIndicator_t
 *                 - Bit to check in ParamPresenceMask - <B>0x2C</B>
 *  @param  extendedChannelRate
 *              - Extended Channel Rate
 *                 - \ref ExtendedChannelRate_t
 *                 - Bit to check in ParamPresenceMask - <B>0x2D</B>
 *  @param  Tlvresult - unpack Tlv Result.
 *  @param  ParamPresenceMask
 *              - parameters presence mask
*/
typedef struct{
    uint32_t                        tx_ok_count;
    uint32_t                        rx_ok_count;
    uint32_t                        tx_err_count;
    uint32_t                        rx_err_count;
    uint32_t                        tx_ofl_count;
    uint32_t                        rx_ofl_count;
    ChannelRate_t                   channelRate;
    uint8_t                         dormancy_status;
    uint64_t                        tx_ok_bytes_count;
    uint64_t                        rx_ok_bytes_count;
    uint8_t                         mip_status;
    uint8_t                         data_call_status;
    uint32_t                        current_sys;
    DataCallTypeTlv_t               dataCallType;
    EVDOPageMonitorPeriodChange_t   eVDOPageMonitorPeriodChange;
    uint32_t                        tx_dropped_count;
    uint32_t                        rx_dropped_count;
    uint8_t                         uplink_flow_control;
    uint32_t                        data_call_addr_family;
    AdditionalPdnFiltersRemoved_t   additionalPdnFiltersRemoved; 
    DataBearerTechnologyExtended_t  dataBearerTechnologyExtended;
    uint16_t                        uplink_fc_seq_num;
    DormancyResultIndicator_t       dormancyResultIndicator;
    ExtendedChannelRate_t           extendedChannelRate;
    uint16_t Tlvresult;
    swi_uint256_t                   ParamPresenceMask;
} unpack_wds_SLQSSetWdsEventReport_ind_t;

/**
 * \ingroup wds
 * 
 * set event callback unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput      response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_SLQSSetWdsEventReport_ind(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_wds_SLQSSetWdsEventReport_ind_t *pOutput
        );

/**
 * This structure contains pack get runtime settings information
 *
 * @param pReqSettings Requested Settings (Optional Parameter)
          - Set bits to 1, corresponding to requested information.
            All other bits must be set to 0.
          - If the values are not available, the corresponding TLVs are
            not returned in the response.
          - Absence of this mask TLV results in the device returning all
            of the available information corresponding to bits 0 through 12.
          - In cases where the information from bit 13 or greater is required,
            this TLV with all the necessary bits set must be present in the request.
          - Values
            - Bit 0 - Profile identifier
            - Bit 1 - Profile name
            - Bit 2 - PDP type
            - Bit 3 - APN name
            - Bit 4 - DNS address
            - Bit 5 - UMTS/GPRS granted QoS
            - Bit 6 - Username
            - Bit 7 - Authentication Protocol
            - Bit 8 - IP address
            - Bit 9 - Gateway info (address and subnet mask)
            - Bit 10 - PCSCF address using PCO flag
            - Bit 11 - PCSCF server address list
            - Bit 12 - PCSCF domain name list
            - Bit 13 - MTU
            - Bit 14 - domain name list
            - Bit 15 - IP family
            - Bit 16 - IM_CM flag
            - Bit 17 - Technology name
            - Bit 18 - Operator reserved PCO (Not Supported on MC/EM73xx)
 */
typedef struct{
    uint32_t         *pReqSettings;
} pack_wds_SLQSGetRuntimeSettings_t;

/**
 * \ingroup wds
 * 
 * get runtime settings pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */
int pack_wds_SLQSGetRuntimeSettings(
        pack_qmi_t *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen,
        pack_wds_SLQSGetRuntimeSettings_t     *reqArg
        );

/**
 * \ingroup wds
 * 
 * This structure contains the UMTS Quality Of Service Information
 *
 *  @param  trafficClass
 *          - 0x00 - Subscribed
 *          - 0x01 - Conversational
 *          - 0x02 - Streaming
 *          - 0x03 - Interactive
 *          - 0x04 - Background
 *
 *  @param  maxUplinkBitrate
 *          - Maximum uplink bit rate in bits/sec
 *
 *  @param  maxDownlinkBitrate
 *          - Maximum downlink bit rate in bits/sec
 *
 *  @param  grntUplinkBitrate
 *          - Guaranteed uplink bit rate in bits/sec
 *
 *  @param  grntDownlinkBitrate
 *          - Guaranteed downlink bit rate in bits/sec
 *
 *  @param  qosDeliveryOrder - Qos delivery order
 *          - 0x00 - Subscribe
 *          - 0x01 - Delivery order on
 *          - 0x02 - Delivery order off
 *
 *  @param  maxSDUSize
 *          - Maximum SDU size
 *
 *  @param  sduErrorRatio - SDU error ratio
 *          - Target value for fraction of SDUs lost or
 *            detected as erroneous.
 *          - 0x00 - Subscribe
 *          - 0x01 - 1*10^(-2)
 *          - 0x02 - 7*10^(-3)
 *          - 0x03 - 1*10^(-3)
 *          - 0x04 - 1*10^(-4)
 *          - 0x05 - 1*10^(-5)
 *          - 0x06 - 1*10^(-6)
 *          - 0x07 - 1*10^(-1)
 *
 *  @param  resBerRatio - Residual bit error ratio
 *          - Target value for undetected bit error ratio in
 *            in the delivered SDUs.
 *          - 0x00 - Subscribe
 *          - 0x01 - 5*10^(-2)
 *          - 0x02 - 1*10^(-2)
 *          - 0x03 - 5*10^(-3)
 *          - 0x04 - 4*10^(-3)
 *          - 0x05 - 1*10^(-3)
 *          - 0x06 - 1*10^(-4)
 *          - 0x07 - 1*10^(-5)
 *          - 0x08 - 1*10^(-6)
 *          - 0x09 - 1*10^(-8)
 *
 *  @param  deliveryErrSDU - delivery of erroneous SDUs
 *          - Indicates whether SDUs detected as erroneous shall be
 *            delivered or not.
 *          - 0x00 - Subscribe
 *          - 0x01 - 5*10^(-2)
 *          - 0x02 - 1*10^(-2)
 *          - 0x03 - 5*10^(-3)
 *          - 0x04 - 4*10^(-3)
 *          - 0x05 - 1*10^(-3)
 *          - 0x06 - 1*10^(-4)
 *          - 0x07 - 1*10^(-5)
 *          - 0x08 - 1*10^(-6)
 *          - 0x09 - 1*10^(-8)
 *
 *  @param  transferDelay - Transfer delay (ms)
 *          - Indicates the targeted time between a request to transfer an
 *            SDU at one SAP to its delivery at the other SAP in milliseconds.
 *
 *  @param  trafficPriority - Transfer handling priority
 *          - Specifies the relative importance for handling of SDUs that
 *            belong to the UMTS bearer, compared to the SDUs of other bearers.
 */
struct wds_UMTSMinQoS
{
    uint8_t  trafficClass;
    uint32_t maxUplinkBitrate;
    uint32_t maxDownlinkBitrate;
    uint32_t grntUplinkBitrate;
    uint32_t grntDownlinkBitrate;
    uint8_t  qosDeliveryOrder;
    uint32_t maxSDUSize;
    uint8_t  sduErrorRatio;
    uint8_t  resBerRatio;
    uint8_t  deliveryErrSDU;
    uint32_t transferDelay;
    uint32_t trafficPriority;
};

/**
 * \ingroup wds
 *
 * This structure contains configured Network Slice Selection Assistance Information (NSSAI)
 *
 *  @param  profile_type
 *          - Profile Type
 *             - Values
 *              - 0x00: 3GPP
 *              - 0x01: 3GPP2
 *
 *  @param  profile_index
 *          - Profile Index
 *            - Values:
 *              - 1-16 (9x15 and before) or
 *              - 1-24 (9x30 and onwards) valid for 3GPP profile type
 *              - 101-106 valid for 3GPP2
 *
 *  @For_5G
 */
typedef struct {
    uint8_t profile_type;
    uint8_t profile_index;
}wds_swi_profile_type_index;

/**
 * \ingroup wds
 *
 * This structure contains configured Network Slice Selection Assistance Information (NSSAI)
 *
 *  @param  sst
 *          - Slice or Service Type (SST)
 *          - Describes expected network behavior
 *
 *  @param  sd
 *          - Slice Differentiator (SD)
 *          - optional, further differentiation. "FF FF FF" to indicate "no SD associated with this SST"
 *
 *  @param  mapped_sst_present
 *          - Mapped SST present
 *          - Flag to indicate if mapped SST is present or not
 *
 *  @param mapped_sst
 *          - Mapped SST
 *          - SST value of an S-NSSAI in the HPLMN to which the configured SST is mapped
 *
 *  @param mapped_sd
 *          - Mapped SD
 *          - SD value of an S-NSSAI in the HPLMN to which the configured SD value is mapped. "FF FF FF" to indicate "no SD associated with this SST"
 *
 *  @For_5G
 */
typedef struct {
    uint8_t sst;
    uint8_t sd[QMI_WDS_SWI_SNSSAI_SIZE];
    uint8_t mapped_sst_present;
    uint8_t mapped_sst;
    uint8_t mapped_sd[QMI_WDS_SWI_SNSSAI_SIZE];
}wds_swi_configured_nssai_type;

/**
 * \ingroup wds
 * 
 * This structure contains Input/Output parameters of pack_wds_SLQSCreateProfile
 *
 *  - Parameter values default to their data type's maximum unsigned value
 *    unless explicitly stated otherwise.
 *
 *  @param  pProfileName
 *          - One or more bytes describing the profile
 *
 *  @param  pProfilenameSize;
 *          - This parameter is an input parameter and should be initialised
 *            to the size of pProfileName field. Size of this parameter is 2
 *            bytes.
 *
 *  @param  pPDPType
 *          - Packet Data Protocol (PDP) type specifies the
 *            type of data payload exchanged over the air link
 *            when the packet data session is established with
 *            this profile
 *            - 0x00 - PDP-IP (IPv4)
 *            - 0x01 - PDP-PPP
 *            - 0x02 - PDP-IPV6
 *            - 0x03 - PDP-IPV4V6
 *
 *  @param  pPdpHdrCompType
 *          - PDP header compression type
 *            - 0 - PDP header compression is OFF
 *            - 1 - Manufacturer preferred compression
 *            - 2 - PDP header compression based on RFC 1144
 *            - 3 - PDP header compression based on RFC 25074
 *                  PDP header compression based on RFC 3095
 *
 *  @param  pPdpDataCompType
 *          - PDP data compression type
 *            - 0 - PDP data compression is OFF
 *            - 1 - Manufacturer preferred compression
 *            - 2 - V.42BIS data compression
 *            - 3 - V.44 data compression
 *
 *  @param  pAPNName
 *          - Access point name
 *
 *  @param  pAPNnameSize;
 *          - This parameter is an input parameter and should be initialised
 *            to the size of pAPNName field. Size of this parameter is 2
 *            bytes.
 *
 *  @param  pPriDNSIPv4AddPref
 *          - Primary DNS IPv4 Address Preference
 *
 *  @param  pSecDNSIPv4AddPref
 *          - Secondary DNS IPv4 Address Preference
 *
 *  @param  pUMTSReqQoS
 *          - UMTS Requested QoS
 *
 *  @param  pUMTSMinQoS
 *          - UMTS Minimum QoS
 *
 *  @param  pGPRSRequestedQoS
 *          - GPRS Minimum QoS
 *
 *  @param  pUsername
 *          - User name
 *
 *  @param  pUsernameSize;
 *          - This parameter is an input parameter and should be initialised
 *            to the size of pUsername field. Size of this parameter is 2
 *            bytes.
 *
 *  @param  pPassword
 *          - Password
 *
 *  @param  pPasswordSize;
 *          - This parameter is an input parameter and should be initialised
 *            to the size of pPassword field. Size of this parameter is 2
 *            bytes.
 *
 *  @param  pAuthenticationPref
 *          - Authentication Preference
 *             - Bit map that indicates the authentication
 *               algorithm preference
 *               - Bit 0 - PAP preference
 *                 - 0 - PAP is never performed
 *                 - 1 - PAP may be performed
 *               - Bit 1 - CHAP preference
 *                 - 0 - CHAP is never performed
 *                 - 1 - CHAP may be performed
 *               - If more than one bit is set, then the device decides
 *                 which authentication procedure is performed while setting
 *                 up the data session. For example, the device may have a
 *                 policy to select the most secure authentication mechanism.
 *
 *  @param  pIPv4AddrPref
 *          - IPv4 Address Preference
 *
 *  @param  pPcscfAddrUsingPCO
 *          - P-CSCF Address using PCO Flag
 *            - 1 - (TRUE) implies request PCSCF address using PCO
 *            - 0 - (FALSE) implies do not request
 *                  By default, this value is 0
 *
 *  @param  pPdpAccessConFlag
 *          - PDP access control flag
 *            - 0 - PDP access control none
 *            - 1 - PDP access control reject
 *            - 2 - PDP access control permission
 *
 *  @param  pPcscfAddrUsingDhcp
 *          - P-CSCF address using DHCP
 *            - 1 - (TRUE) implies Request PCSCF address using DHCP
 *            - 0 - (FALSE) implies do not request
 *                  By default, value is 0
 *
 *  @param  pImCnFlag
 *          - IM CN flag
 *            - 1 - (TRUE) implies request IM CN flag for
 *                   this profile
 *            - 0 - (FALSE) implies do not request IM CN
 *                  flag for this profile
 *
 *  @param  pTFTID1Params
 *          - Traffic Flow Template
 *
 *  @param  pTFTID2Params
 *          - Traffic Flow Template
 *
 *  @param  pPdpContext
 *          - PDP context number
 *
 *  @param  pSecondaryFlag
 *          - PDP context secondary flag
 *            - 1 - (TRUE) implies this is secondary profile
 *            - 0 - (FALSE) implies this is not secondary profile
 *
 *  @param  pPrimaryID
 *          - PDP context primary ID
 *          - function SLQSGetProfileSettings() returns a default value
 *            0xFF if this parameter is not returned by the device
 *
 *  @param  pIPv6AddPref
 *          - IPv6 address preference
 *            Preferred IPv6 address to be assigned to the TE; actual
 *            assigned address is negotiated with the network and may
 *            differ from this value; if not specified, the IPv6
 *            address is obtained automatically from the network
 *
 *  @param  pUMTSReqQoSSigInd
 *          - UMTS requested QoS with Signalling Indication flag
 *
 *  @param  pUMTSMinQoSSigInd
 *          - UMTS minimum QoS with Signalling Indication flag
 *
 *  @param  pPrimaryDNSIPv6addpref
 *          - Primary DNS IPv6 address preference
 *            - The value may be used as a preference during
 *              negotiation with the network; if not specified, the
 *              wireless device will attempt to obtain the DNS
 *              address automatically from the network; the
 *              negotiated value is provided to the host via DHCP
 *
 *  @param  pSecondaryDNSIPv6addpref
 *          - Secondary DNS IPv6 address preference
 *
 *  @param  paddrAllocationPref
 *          - DHCP/NAS preference
 *            - This enumerated value may be used to indicate
 *              the address allocation preference
 *               - 0 - NAS signaling is used for address allocation
 *               - 1 - DHCP is used for address allocation
 *
 *  @param  pQosClassID
 *          - 3GPP LTE QoS parameters
 *
 *  @param  pAPNDisabledFlag
 *          - Optional 1 uint8_t Flag indicating if the APN is disabled/enabled
 *          - If set, the profile can not be used for making data calls
 *          - Any data call is failed locally
 *          - Values:
 *            - 0 - FALSE(default)
 *            - 1 - True
 *          - This parameter is currently read only and can be read by using
 *            the function SLQSGetProfileSettings().
 *
 *  @param  pPDNInactivTimeout
 *          - Optional 4 Bytes indicating the duration of inactivity timer
 *            in seconds
 *          - If the PDP context/PDN connection is inactive for this duration
 *            i.e. No data Tx/Rx occurs, the PDP context/PDN connection is
 *            disconnected
 *          - Default value of zero indicates infinite value
 *          - This parameter is currently read only and can be read by using
 *            the function SLQSGetProfileSettings().
 *
 *  @param  pAPNClass
 *          - Optional 1 uint8_t numeric identifier representing the APN in profile
 *          - Can be set and queried but is not used by the modem
 *          - This parameter is currently read only and can be read by using
 *            the function SLQSGetProfileSettings().
 *
 *  @param  pSupportEmergencyCalls
 *          - Optional 1 Byte Flag indicating if the emergency call support is disabled/enabled
 *          - If set, the profile can be used for making emergency calls
 *          - Values:
 *            - 0 - FALSE(default)
 *            - 1 - TRUE
 *
 *  \param  pAlwaysOnPduSession
 *          - Optional 1 Byte Flag indicating if always on PDU session is disabled/enabled
 *          - Values:
 *            - 0 - FALSE - Not supported (default)
 *            - 1 - TRUE - Always on PDU
 *
 *  @param  pS_Nassai (optional)
 *          - Profile S-NSSAI
 *          - \ref wds_swi_configured_nssai_type for more information
 *
 *  @param pSsc (optional)
 *          - Session and Service Continuity (SSC)
 *           - values:
 *              -1: SSC Mode One (Default)
 *              -2: SSC Mode Two,
 *              -3: SSC Mode Three
 *
 *  @param pPreferred_access_type (optional)
 *          - Preferred Access Type
 *           - values:
 *              - 0: Unspecified
 *              - 1: 3GPP (Default)
 *              - 2: Non-3GPP
 *  @For_5G
 *
 */
typedef struct
{
    uint8_t                    *pProfilename;
    uint16_t                   *pProfilenameSize;
    uint8_t                    *pPDPtype;
    uint8_t                    *pPdpHdrCompType;
    uint8_t                    *pPdpDataCompType;
    uint8_t                    *pAPNName;
    uint16_t                   *pAPNnameSize;
    uint32_t                   *pPriDNSIPv4AddPref;
    uint32_t                   *pSecDNSIPv4AddPref;
    LibPackUMTSQoS             *pUMTSReqQoS;
    LibPackUMTSQoS             *pUMTSMinQoS;
    LibPackGPRSRequestedQoS    *pGPRSRequestedQos;
    LibPackGPRSRequestedQoS    *pGPRSMinimumQoS;
    uint8_t                    *pUsername;
    uint16_t                    *pUsernameSize;
    uint8_t                    *pPassword;
    uint16_t                   *pPasswordSize;
    uint8_t                    *pAuthenticationPref;
    uint32_t                   *pIPv4AddrPref;
    uint8_t                    *pPcscfAddrUsingPCO;
    uint8_t                    *pPdpAccessConFlag;
    uint8_t                    *pPcscfAddrUsingDhcp;
    uint8_t                    *pImCnFlag;
    LibPackTFTIDParams         *pTFTID1Params;
    LibPackTFTIDParams         *pTFTID2Params;
    uint8_t                    *pPdpContext;
    uint8_t                    *pSecondaryFlag;
    uint8_t                    *pPrimaryID;
    uint16_t                   *pIPv6AddPref;
    LibPackUMTSReqQoSSigInd    *pUMTSReqQoSSigInd;
    LibPackUMTSReqQoSSigInd    *pUMTSMinQosSigInd;
    uint16_t                   *pPriDNSIPv6addpref;
    uint16_t                   *pSecDNSIPv6addpref;
    uint8_t                    *pAddrAllocPref;
    LibPackQosClassID          *pQosClassID;
    uint8_t                    *pAPNDisabledFlag;
    uint32_t                   *pPDNInactivTimeout;
    uint8_t                    *pAPNClass;
    uint8_t                    *pSupportEmergencyCalls;
    uint8_t                    *pAlwaysOnPduSession;
    wds_swi_configured_nssai_type* pS_Nassai;
    uint8_t                    *pSsc;
    uint8_t                    *pPreferred_access_type;
} LibPackprofile_3GPP;

/**
 * \ingroup wds
 * 
 * This structure contains the 3GPP2 profile parameters
 *  - Parameter values default to their data type's maximum unsigned value
 *    unless explicitly stated otherwise.
 *
 *  @param  pNegoDnsSrvrPref
 *          - Negotiate DNS Server Preference
 *            - 1 - (TRUE)implies request DNS addresses
 *             from the PDSN
 *            - 0 - (FALSE)implies do not request DNS
 *             addresses from the PDSN
 *            - Default value is 1 (TRUE)
 *
 *  @param  pPppSessCloseTimerDO
 *          - PPP Session Close Timer for DO
 *            - Timer value (in seconds) on DO indicating how
 *              long the PPP Session should linger before
 *              closing down
 *
 *  @param  pPppSessCloseTimer1x
 *          - PPP Session Close Timer for 1X
 *            - Timer value (in seconds) on 1X indicating how
 *              long the PPP session should linger before closing down
 *
 *  @param  pAllowLinger
 *          - Allow/disallow lingering of interface
 *            - 1 -(TRUE) implies allow lingering
 *            - 0 -(FALSE) implies do not allow lingering
 *
 *  @param  pLcpAckTimeout
 *          - LCP ACK Timeout
 *            - Value of LCP ACK Timeout in milliseconds
 *
 *  @param  pIpcpAckTimeout
 *          - IPCP ACK Timeout
 *            - Value of IPCP ACK Timeout in milliseconds
 *
 *  @param  pAuthTimeout
 *          - AUTH Timeout
 *            - Value of Authentication Timeout in milliseconds
 *
 *  @param  pLcpCreqRetryCount
 *          - LCP Configuration Request Retry Count
 *
 *  @param  pIpcpCreqRetryCount
 *          - IPCP Configuration Request Retry Count
 *
 *  @param  pAuthRetryCount
 *          - Authentication Retry Count value
 *
 *  @param  pAuthProtocol
 *          - Authentication Protocol
 *            - 1 - PAP
 *            - 2 - CHAP
 *            - 3 - PAP or CHAP
 *
 *  @param  pUserId
 *          - User ID to be used during data network authentication
 *          - maximum length allowed is 127 bytes;
 *          - QMI_ERR_ARG_TOO_LONG will be returned if the storage on the
 *            wireless device is insufficient in size to hold the value.
 *
 *  @param  pUserIdSize;
 *          - This parameter is an input parameter and should be initialised
 *            to the size of pUserId field. Size of this parameter is 2
 *            bytes.
 *
 *  @param  pAuthPassword
 *          - Password to be used during data network authentication;
 *          - maximum length allowed is 127 bytes
 *          - QMI_ERR_ARG_TOO_LONG will be returned if the storage on the
 *            wireless device is insufficient in size to hold the value.
 *
 *  @param  pAuthPasswordSize;
 *          - This parameter is an input parameter and should be initialised
 *            to the size of pAuthPassword field. Size of this parameter is 2
 *            bytes.
 *
 *  @param  pDataRate
 *          - Data Rate Requested
 *            - 0 - Low (Low speed Service Options (SO15) only)
 *            - 1 - Medium (SO33 + low R-SCH)
 *            - 2 - High (SO33 + high R-SCH)
 *            - Default is 2
 *
 *  @param  pAppType
 *          - Application Type:
 *            - 0x00000001 - Default Application Type
 *            - 0x00000020 - LBS Application Type
 *            - 0x00000040 - Tethered Application Type
 *            - This parameter is not used while creating/modifying a profile
 *
 *  @param  pDataMode
 *          - Data Mode to use:
 *            - 0 - CDMA or HDR (Hybrid 1X/1xEV-DO)
 *            - 1 - CDMA Only (1X only)
 *            - 2 - HDR Only (1xEV-DO only)
 *            - Default is 0
 *
 *  @param  pAppPriority
 *          - Application Priority
 *            - Numerical 1 uint8_t value defining the application
 *              priority; higher value implies higher priority
 *            - This parameter is not used while creating/modifying a profile
 *
 *  @param  pApnString
 *          - String representing the Access Point Name
 *          - maximum length allowed is 100 bytes
 *          - QMI_ERR_ARG_TOO_LONG will be returned if the APN
 *            name is too long.
 *
 *  @param  pApnStringSize;
 *          - This parameter is an input parameter and should be initialised
 *            to the size of pApnString field. Size of this parameter is 2
 *            bytes.
 *
 *  @param  pPdnType
 *          - Packed Data Network Type Requested:
 *            - 0 - IPv4 PDN Type
 *            - 1 - IPv6 PDN Type
 *            - 2 - IPv4 or IPv6 PDN Type
 *            - 3 - Unspecified PDN Type (implying no preference)
 *
 *  @param  pIsPcscfAddressNedded
 *          - This boolean value is used to control if PCSCF
 *            address is requested from PDSN
 *            - 1 -(TRUE) implies request for PCSCF value from the PDSN
 *            - 0 -(FALSE) implies do not request for PCSCF value from the PDSN
 *
 *  @param  pPrimaryV4DnsAddress
 *          - IPv4 Primary DNS address
 *            - The Primary IPv4 DNS address that can be statically assigned
 *              to the UE
 *
 *  @param  pSecondaryV4DnsAddress
 *          - IPv4 Secondary DNS address
 *            - The Secondary IPv4 DNS address that can be statically assigned
 *              to the UE
 *
 *  @param  pPriV6DnsAddress
 *          - Primary IPv6 DNS address
 *            - The Primary IPv6 DNS address that can be statically assigned
 *              to the UE
 *
 *  @param  pSecV6DnsAddress
 *          - Secondary IPv6 DNS address
 *            - The Secondary IPv6 DNS address that can be statically assigned
 *              to the UE
 *
 *  @param  pRATType
 *          - Optional 1 uint8_t Flag indicating RAT Type
 *          - Values:
 *            - 1 - HRPD
 *            - 2 - EHRPD
 *            - 3 - HRPD_EHRPD
 *          - This parameter is currently read only and can be read by using
 *            the function SLQSGetProfileSettings().
 *
 *  @param  pAPNEnabled3GPP2
 *          - Optional 1 uint8_t Flag indicating if the APN is disabled/enabled
 *          - If disabled, the profile can not be used for making data calls
 *          - Values:
 *            - 0 - Disabled
 *            - 1 - Enabled(default value)
 *          - This parameter is currently read only and can be read by using
 *            the function SLQSGetProfileSettings().
 *
 *  @param  pPDNInactivTimeout3GPP2
 *          - Optional 4 Bytes indicating the duration of inactivity timer
 *            in seconds
 *          - If the PDP context/PDN connection is inactive for this duration
 *            i.e. No data Tx/Rx occurs, the PDP context/PDN connection is
 *            disconnected
 *          - Default value of zero indicates infinite value
 *          - This parameter is currently read only and can be read by using
 *            the function SLQSGetProfileSettings().
 *
 *  @param  pAPNClass3GPP2
 *          - Optional 1 uint8_t numeric identifier representing the APN in profile
 *          - Can be set and queried but is not used by the modem
 *          - This parameter is currently read only and can be read by using
 *            the function SLQSGetProfileSettings().
 *
 */
typedef struct 
{
    uint8_t   *pNegoDnsSrvrPref;
    uint32_t  *pPppSessCloseTimerDO;
    uint32_t  *pPppSessCloseTimer1x;
    uint8_t   *pAllowLinger;
    uint16_t  *pLcpAckTimeout;
    uint16_t  *pIpcpAckTimeout;
    uint16_t  *pAuthTimeout;
    uint8_t   *pLcpCreqRetryCount;
    uint8_t   *pIpcpCreqRetryCount;
    uint8_t   *pAuthRetryCount;
    uint8_t   *pAuthProtocol;
    uint8_t   *pUserId;
    uint16_t  *pUserIdSize;
    uint8_t   *pAuthPassword;
    uint16_t  *pAuthPassword_tSize;
    uint8_t   *pDataRate;
    uint32_t  *pAppType;
    uint8_t   *pDataMode;
    uint8_t   *pAppPriority;
    uint8_t   *pApnString;
    uint16_t  *pApnStringSize;
    uint8_t   *pPdnType;
    uint8_t   *pIsPcscfAddressNedded;
    uint32_t  *pPrimaryV4DnsAddress;
    uint32_t  *pSecondaryV4DnsAddress;
    uint16_t  *pPriV6DnsAddress;
    uint16_t  *pSecV6DnsAddress;
    uint8_t   *pRATType;
    uint8_t   *pAPNEnabled3GPP2;
    uint32_t  *pPDNInactivTimeout3GPP2;
    uint8_t   *pAPNClass3GPP2;
}LibPackprofile_3GPP2;

/**
 * \ingroup wds
 * 
 * This union  consist of profile_3GPP and profile_3GPP2
 * out of which one will be used to create profile.
 *  @param  SlqsProfile3GPP 3GPP profile
 *          See \ref LibPackprofile_3GPP
 *  @param  SlqsProfile3GPP2 3GPP2 profile
 *          See \ref LibPackprofile_3GPP2
 *
 */
typedef union
{
    LibPackprofile_3GPP  SlqsProfile3GPP;
    LibPackprofile_3GPP2 SlqsProfile3GPP2;
}wds_profileInfo;

/**
 * \ingroup wds
 * 
 *  This structure contains pack create profile.
 *
 *  @param  pProfileId (out)
 *          - 1 to 16 for 3GPP profile (EM/MC73xx or earlier)
 *          - 1 to 24 for 3GPP profile (EM/MC74xx onwards)
 *          - 101 to 106 for 3GPP2 profile
 *
 *  @param  pProfileType
 *          - Identifies the technology type of the profile.
 *           - Values:
 *              - WDS_PROFILE_TYPE_3GPP (0x00) - 3GPP
 *              - WDS_PROFILE_TYPE_3GPP2 (0x01) - 3GPP2
 *              - WDS_PROFILE_TYPE_EPC (0x02) - EPC
 *
 *  @param  pCurProfile
 *          - union of 3GPP and 3GPP2 profile
 *          - See \ref wds_profileInfo
 *
 *  @note   - If profileID is NULL, 3GPP profile will be created
 *            and index will be assigned based on availability in device.
 *  @note   - If profileID is not NULL depending on pProfileType 3GPP/3GPP2
 *            relevant profile will be created
 *
 */
typedef struct
{
    uint8_t   *pProfileId;
    uint8_t   *pProfileType;
    wds_profileInfo  *pCurProfile;
} pack_wds_SLQSCreateProfile_t;

/**
 * \ingroup wds
 * 
 * Create Profile pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */
int pack_wds_SLQSCreateProfile(
        pack_qmi_t  *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen,
        pack_wds_SLQSCreateProfile_t *reqArg
        );

/**
 * \ingroup wds
 * 
 *  This structure contains out parameter Information
 *
 *  @param  ProfileType
 *          - Identifies the type of profile
 *            0x00 = 3GPP
 *            0x01 = 3GPP2
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param  ProfileIndex
 *          - Index identifying the profile that was created
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param  ExtErrorCode
 *          - The extended error code received from DS Profile
 *           subsystem
 *          - Bit to check in ParamPresenceMask - <B>224</B>
 */
typedef struct 
{
    uint8_t   ProfileType;
    uint8_t   ProfileIndex;
    uint16_t  ExtErrorCode;
}PackCreateProfileOut;

/**
 * \ingroup wds
 * 
 *  This structure contains unpack create profile information.
 *
 *  @param  pCreateProfileOut
 *          - SLQS Create profile Information
 *          - See \ref PackCreateProfileOut
 *
 *  @param  pProfileID
 *          - SLQS profile identifier information
 *
 *  @param  Tlvresult
 *          - TLV present flag, TURE if presented, otherwise FALSE
 *
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */

typedef struct
{
    PackCreateProfileOut *pCreateProfileOut;
    uint8_t  *pProfileID;
    uint16_t   Tlvresult;
    swi_uint256_t  ParamPresenceMask;
} unpack_wds_SLQSCreateProfile_t;

/**
 * \ingroup wds
 * 
 * Create Profile unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response structure to fill
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */

int unpack_wds_SLQSCreateProfile(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_wds_SLQSCreateProfile_t *pOutput
        );

/**
 * \ingroup wds
 * 
 *  This structure contains pack modify profile information.
 *  @param  pProfileId
 *          - 1 to 16 for 3GPP profile (EM/MC73xx or earlier)
 *          - 1 to 24 for 3GPP profile (EM/MC74xx onwards)
 *          - 101 to 106 for 3GPP2 profile
 *
 *  @param  pProfileType
 *          - Identifies the technology type of the profile
 *            - 0x00 - 3GPP
 *            - 0x01 - 3GPP2
 *            - NULL is not allowed
 *
 *  @param  curProfile
 *          - union of 3GPP and 3GPP2 profile
 *          - See \ref wds_profileInfo
 *
 *  @note   - If profileID is NULL, 3GPP profile will be created
 *            and index will be assigned based on availability in device.
 *  @note   - If profileID is not NULL depending on pProfileType 3GPP/3GPP2
 *            relevant profile will be created
 *
 */
typedef struct
{
    uint8_t   *pProfileId;
    uint8_t   *pProfileType;
    wds_profileInfo  curProfile;
} pack_wds_SLQSModifyProfile_t;

/**
 * \ingroup wds
 * 
 * Modify Profile pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */
int pack_wds_SLQSModifyProfile(
        pack_qmi_t  *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen,
        pack_wds_SLQSModifyProfile_t *reqArg
        );

/**
 * \ingroup wds
 * 
 * This structure contains out parameters for unpack_wds_SLQSModifyProfile
 *
 *  @param  pExtErrorCode
 *          - The extended error code received from DS Profile subsystem of type
 *            eWDS_ERR_PROFILE_REG_xxx.
 *          - Error code will only will be present if error code
 *            eQCWWAN_ERR_QMI_EXTENDED_INTERNAL is returned by device.
 *          - See \ref qm_wds_ds_profile_extended_err_codes enum in qmerrno.h
 *            for received error description.
 *          - Bit to check in ParamPresenceMask - <B>224</B>
 *
 *  @param  Tlvresult - unpack Tlv Result.
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct
{
   uint16_t  *pExtErrorCode;
   uint16_t Tlvresult;
   swi_uint256_t  ParamPresenceMask;
} unpack_wds_SLQSModifyProfile_t;


/**
 * \ingroup wds
 * 
 * Modify Profile unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response structure to fill
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */

int unpack_wds_SLQSModifyProfile(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_wds_SLQSModifyProfile_t *pOutput
        );

/**
 * \ingroup wds
 * 
 *  This structure contains pack get profile settings information.
 *
 *  @param  ProfileID
 *          - 1 to 16 for 3GPP profile (EM/MC73xx or earlier)
 *          - 1 to 24 for 3GPP profile (EM/MC74xx onwards)
 *          - 101 to 106 for 3GPP2 profile
 *
 *  @param  ProfileType
 *          - Identifies the technology type of the profile
 *            - 0x00 - 3GPP
 *            - 0x01 - 3GPP2
 *
 *  @note   - If profileID is NULL, 3GPP profile will be fetched
 *            and index will be assigned based on availability in device.
 *  @note   - If profileID is not NULL depending on pProfileType 3GPP/3GPP2
 *            relevant profile will be fetched
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
typedef struct
{
    uint8_t   ProfileId;
    uint8_t   ProfileType;
} pack_wds_SLQSGetProfileSettings_t;

/**
 * \ingroup wds
 * 
 * Get Profile Settings pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */
int pack_wds_SLQSGetProfileSettings(
        pack_qmi_t  *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen,
        pack_wds_SLQSGetProfileSettings_t *reqArg
        );

/**
 * \ingroup wds
 * 
 * This structure contains Input parameters of unpack_wds_SLQSGetProfileSettings_t
 * Parameter values default to their data type's maximum unsigned value
 *    unless explicitly stated otherwise.
 *
 *  @param  pProfileName
 *          - One or more uint8_ts describing the profile
 *          - NULL pointer - Invalid data.
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  @param  pProfilenameSize;
 *          - This parameter is an input parameter and should be initialised
 *            to the size of pProfileName field. Size of this parameter is 2
 *            uint8_ts.
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  @param  pPDPType
 *          - Packet Data Protocol (PDP) type specifies the
 *            type of data payload exchanged over the air link
 *            when the packet data session is established with
 *            this profile
 *            - 0x00 - PDP-IP (IPv4)
 *            - 0x01 - PDP-PPP
 *            - 0x02 - PDP-IPV6
 *            - 0x03 - PDP-IPV4V6
 *          - Bit to check in ParamPresenceMask - <B>17</B>
 *
 *  @param  pPdpHdrCompType
 *          - PDP header compression type
 *            - 0 - PDP header compression is OFF
 *            - 1 - Manufacturer preferred compression
 *            - 2 - PDP header compression based on RFC 1144
 *            - 3 - PDP header compression based on RFC 25074
 *                  PDP header compression based on RFC 3095
 *          - Bit to check in ParamPresenceMask - <B>18</B>
 *
 *  @param  pPdpDataCompType
 *          - PDP data compression type
 *            - 0 - PDP data compression is OFF
 *            - 1 - Manufacturer preferred compression
 *            - 2 - V.42BIS data compression
 *            - 3 - V.44 data compression
 *          - Bit to check in ParamPresenceMask - <B>19</B>
 *
 *  @param  pAPNName
 *          - Access point name
 *          - Bit to check in ParamPresenceMask - <B>20</B>
 *
 *  @param  pAPNnameSize;
 *          - This parameter is an input parameter and should be initialised
 *            to the size of pAPNName field. Size of this parameter is 2
 *            uint8_ts.
 *          - Bit to check in ParamPresenceMask - <B>20</B>
 *
 *  @param  pPriDNSIPv4AddPref
 *          - Primary DNS IPv4 Address Preference
 *          - Bit to check in ParamPresenceMask - <B>21</B>
 *
 *  @param  pSecDNSIPv4AddPref
 *          - Secondary DNS IPv4 Address Preference
 *          - Bit to check in ParamPresenceMask - <B>22</B>
 *
 *  @param  pUMTSReqQoS
 *          - UMTS Requested QoS
 *          - Bit to check in ParamPresenceMask - <B>23</B>
 *
 *  @param  pUMTSMinQoS
 *          - UMTS Minimum QoS
 *          - Bit to check in ParamPresenceMask - <B>24</B>
 *
 *  @param  pGPRSRequestedQoS
 *          - GPRS Requested QoS
 *          - Bit to check in ParamPresenceMask - <B>25</B>
 *
 *  @param  pGPRSMinimumQoS
 *          - GPRS Minimum QoS
 *          - Bit to check in ParamPresenceMask - <B>26</B>
 *
 *  @param  pUsername
 *          - User name
 *          - Bit to check in ParamPresenceMask - <B>27</B>
 *
 *  @param  pUsernameSize;
 *          - This parameter is an input parameter and should be initialised
 *            to the size of pUsername field. Size of this parameter is 2
 *            uint8_ts.
 *          - Bit to check in ParamPresenceMask - <B>27</B>
 *
 *  @param  pPassword
 *          - Password
 *          - Bit to check in ParamPresenceMask - <B>28</B>
 *
 *  @param  pPasswordSize;
 *          - This parameter is an input parameter and should be initialised
 *            to the size of pPassword field. Size of this parameter is 2
 *            uint8_ts.
 *          - Bit to check in ParamPresenceMask - <B>28</B>
 *
 *  @param  pAuthenticationPref
 *          - Authentication Preference
 *             - Bit map that indicates the authentication
 *               algorithm preference
 *               - Bit 0 - PAP preference
 *                 - 0 - PAP is never performed
 *                 - 1 - PAP may be performed
 *               - Bit 1 - CHAP preference
 *                 - 0 - CHAP is never performed
 *                 - 1 - CHAP may be performed
 *               - If more than one bit is set, then the device decides
 *                 which authentication procedure is performed while setting
 *                 up the data session. For example, the device may have a
 *                 policy to select the most secure authentication mechanism.
 *          - Bit to check in ParamPresenceMask - <B>29</B>
 *
 *  @param  pIPv4AddrPref
 *          - IPv4 Address Preference
 *          - Bit to check in ParamPresenceMask - <B>30</B>
 *
 *  @param  pPcscfAddrUsingPCO
 *          - P-CSCF Address using PCO Flag
 *            - 1 - (TRUE) implies request PCSCF address using PCO
 *            - 0 - (FALSE) implies do not request
 *                  By default, this value is 0
 *          - Bit to check in ParamPresenceMask - <B>31</B>
 *
 *  @param  pPdpAccessConFlag
 *          - PDP access control flag
 *            - 0 - PDP access control none
 *            - 1 - PDP access control reject
 *            - 2 - PDP access control permission
 *          - Bit to check in ParamPresenceMask - <B>32</B>
 *
 *  @param  pPcscfAddrUsingDhcp
 *          - P-CSCF address using DHCP
 *            - 1 - (TRUE) implies Request PCSCF address using DHCP
 *            - 0 - (FALSE) implies do not request
 *                  By default, value is 0
 *          - Bit to check in ParamPresenceMask - <B>33</B>
 *
 *  @param  pImCnFlag
 *          - IM CN flag
 *            - 1 - (TRUE) implies request IM CN flag for
 *                   this profile
 *            - 0 - (FALSE) implies do not request IM CN
 *                  flag for this profile
 *          - Bit to check in ParamPresenceMask - <B>34</B>
 *
 *  @param  pTFTID1Params
 *          - Traffic Flow Template
 *          - Bit to check in ParamPresenceMask - <B>35</B>
 *
 *  @param  pTFTID2Params
 *          - Traffic Flow Template
 *          - Bit to check in ParamPresenceMask - <B>36</B>
 *
 *  @param  pPdpContext
 *          - PDP context number
 *          - Bit to check in ParamPresenceMask - <B>37</B>
 *
 *  @param  pSecondaryFlag
 *          - PDP context secondary flag
 *            - 1 - (TRUE) implies this is secondary profile
 *            - 0 - (FALSE) implies this is not secondary profile
 *          - Bit to check in ParamPresenceMask - <B>38</B>
 *
 *  @param  pPrimaryID
 *          - PDP context primary ID
 *          - function SLQSGetProfileSettings() returns a default value
 *            0xFF if this parameter is not returned by the device
 *          - Bit to check in ParamPresenceMask - <B>39</B>
 *
 *  @param  pIPv6AddPref
 *          - IPv6 address preference
 *            Preferred IPv6 address to be assigned to the TE; actual
 *            assigned address is negotiated with the network and may
 *            differ from this value; if not specified, the IPv6
 *            address is obtained automatically from the network
 *          - Bit to check in ParamPresenceMask - <B>40</B>
 *
 *  @param  pUMTSReqQoSSigInd
 *          - UMTS requested QoS with Signalling Indication flag
 *          - Bit to check in ParamPresenceMask - <B>41</B>
 *
 *  @param  pUMTSMinQoSSigInd
 *          - UMTS minimum QoS with Signalling Indication flag
 *          - Bit to check in ParamPresenceMask - <B>42</B>
 *
 *  @param  pPrimaryDNSIPv6addpref
 *          - Primary DNS IPv6 address preference
 *            - The value may be used as a preference during
 *              negotiation with the network; if not specified, the
 *              wireless device will attempt to obtain the DNS
 *              address automatically from the network; the
 *              negotiated value is provided to the host via DHCP
 *          - Bit to check in ParamPresenceMask - <B>43</B>
 *
 *  @param  pSecondaryDNSIPv6addpref
 *          - Secondary DNS IPv6 address preference
 *          - Bit to check in ParamPresenceMask - <B>44</B>
 *
 *  @param  paddrAllocationPref
 *          - DHCP/NAS preference
 *            - This enumerated value may be used to indicate
 *              the address allocation preference
 *               - 0 - NAS signaling is used for address allocation
 *               - 1 - DHCP is used for address allocation
 *          - Bit to check in ParamPresenceMask - <B>45</B>
 *
 *  @param  pQosClassID
 *          - 3GPP LTE QoS parameters
 *          - Bit to check in ParamPresenceMask - <B>46</B>
 *
 *  @param  pAPNDisabledFlag
 *          - Optional 1 uint8_t Flag indicating if the APN is disabled/enabled
 *          - If set, the profile can not be used for making data calls
 *          - Any data call is failed locally
 *          - Values:
 *            - 0 - FALSE(default)
 *            - 1 - True
 *          - This parameter is currently read only and can be read by using
 *            the function SLQSGetProfileSettings().
 *          - Bit to check in ParamPresenceMask - <B>47</B>
 *
 *  @param  pPDNInactivTimeout
 *          - Optional 4 uint8_ts indicating the duration of inactivity timer
 *            in seconds
 *          - If the PDP context/PDN connection is inactive for this duration
 *            i.e. No data Tx/Rx occurs, the PDP context/PDN connection is
 *            disconnected
 *          - Default value of zero indicates infinite value
 *          - This parameter is currently read only and can be read by using
 *            the function SLQSGetProfileSettings().
 *          - Bit to check in ParamPresenceMask - <B>48</B>
 *
 *  @param  pAPNClass
 *          - Optional 1 uint8_t numeric identifier representing the APN in profile
 *          - Can be set and queried but is not used by the modem
 *          - This parameter is currently read only and can be read by using
 *            the function SLQSGetProfileSettings().
 *          - Bit to check in ParamPresenceMask - <B>49</B>
 *
 * @param  pSupportEmergencyCalls
 *          - Optional 1 Byte Flag indicating if the emergency call support is disabled/enabled
 *          - Can be queried to get current status
 *          - Values:
 *            - 0 - FALSE(default)
 *            - 1 - TRUE
 *          - Bit to check in ParamPresenceMask - <B>54</B>
 *
 */
typedef struct 
{
    uint8_t                    *pProfilename;
    uint16_t                    *pProfilenameSize;
    uint8_t                    *pPDPtype;
    uint8_t                    *pPdpHdrCompType;
    uint8_t                    *pPdpDataCompType;
    uint8_t                    *pAPNName;
    uint16_t                    *pAPNnameSize;
    uint32_t                   *pPriDNSIPv4AddPref;
    uint32_t                   *pSecDNSIPv4AddPref;
    LibPackUMTSQoS          *pUMTSReqQoS;
    LibPackUMTSQoS          *pUMTSMinQoS;
    LibPackGPRSRequestedQoS *pGPRSRequestedQos;
    LibPackGPRSRequestedQoS *pGPRSMinimumQoS;
    uint8_t                    *pUsername;
    uint16_t                    *pUsernameSize;
    uint8_t                    *pPassword;
    uint16_t                    *pPasswordSize;
    uint8_t                    *pAuthenticationPref;
    uint32_t                   *pIPv4AddrPref;
    uint8_t                    *pPcscfAddrUsingPCO;
    uint8_t                    *pPdpAccessConFlag;
    uint8_t                    *pPcscfAddrUsingDhcp;
    uint8_t                    *pImCnFlag;
    LibPackTFTIDParams      *pTFTID1Params;
    LibPackTFTIDParams      *pTFTID2Params;
    uint8_t                    *pPdpContext;
    uint8_t                    *pSecondaryFlag;
    uint8_t                    *pPrimaryID;
    uint16_t                  *pIPv6AddPref;
    LibPackUMTSReqQoSSigInd *pUMTSReqQoSSigInd;
    LibPackUMTSReqQoSSigInd *pUMTSMinQosSigInd;
    uint16_t                  *pPriDNSIPv6addpref;
    uint16_t                  *pSecDNSIPv6addpref;
    uint8_t                    *pAddrAllocPref;
    LibPackQosClassID       *pQosClassID;
    uint8_t                    *pAPNDisabledFlag;
    uint32_t                   *pPDNInactivTimeout;
    uint8_t                    *pAPNClass;
    uint8_t                    *pSupportEmergencyCalls;
}LibpackProfile3GPP;
/**
 * \ingroup wds
 * 
 * This structure contains the 3GPP2 profile parameters
 *  - Parameter values default to their data type's maximum unsigned value
 *    unless explicitly stated otherwise.
 *
 *  @param  pNegoDnsSrvrPref
 *          - Negotiate DNS Server Preference
 *            - 1 - (TRUE)implies request DNS addresses
 *             from the PDSN
 *            - 0 - (FALSE)implies do not request DNS
 *             addresses from the PDSN
 *            - Default value is 1 (TRUE)
 *          - Bit to check in ParamPresenceMask - <B>144</B>
 *
 *  @param  pPppSessCloseTimerDO
 *          - PPP Session Close Timer for DO
 *            - Timer value (in seconds) on DO indicating how
 *              long the PPP Session should linger before
 *              closing down
 *          - Bit to check in ParamPresenceMask - <B>145</B>
 *
 *  @param  pPppSessCloseTimer1x
 *          - PPP Session Close Timer for 1X
 *            - Timer value (in seconds) on 1X indicating how
 *              long the PPP session should linger before closing down
 *          - Bit to check in ParamPresenceMask - <B>146</B>
 *
 *  @param  pAllowLinger
 *          - Allow/disallow lingering of interface
 *            - 1 -(TRUE) implies allow lingering
 *            - 0 -(FALSE) implies do not allow lingering
 *          - Bit to check in ParamPresenceMask - <B>147</B>
 *
 *  @param  pLcpAckTimeout
 *          - LCP ACK Timeout
 *            - Value of LCP ACK Timeout in milliseconds
 *          - Bit to check in ParamPresenceMask - <B>148</B>
 *
 *  @param  pIpcpAckTimeout
 *          - IPCP ACK Timeout
 *            - Value of IPCP ACK Timeout in milliseconds
 *          - Bit to check in ParamPresenceMask - <B>149</B>
 *
 *  @param  pAuthTimeout
 *          - AUTH Timeout
 *            - Value of Authentication Timeout in milliseconds
 *          - Bit to check in ParamPresenceMask - <B>150</B>
 *
 *  @param  pLcpCreqRetryCount
 *          - LCP Configuration Request Retry Count
 *          - Bit to check in ParamPresenceMask - <B>151</B>
 *
 *  @param  pIpcpCreqRetryCount
 *          - IPCP Configuration Request Retry Count
 *          - Bit to check in ParamPresenceMask - <B>152</B>
 *
 *  @param  pAuthRetryCount
 *          - Authentication Retry Count value
 *          - Bit to check in ParamPresenceMask - <B>153</B>
 *
 *  @param  pAuthProtocol
 *          - Authentication Protocol
 *            - 1 - PAP
 *            - 2 - CHAP
 *            - 3 - PAP or CHAP
 *          - Bit to check in ParamPresenceMask - <B>154</B>
 *
 *  @param  pUserId
 *          - User ID to be used during data network authentication
 *          - maximum length allowed is 127 uint8_ts;
 *          - QMI_ERR_ARG_TOO_LONG will be returned if the storage on the
 *            wireless device is insufficient in size to hold the value.
 *          - Bit to check in ParamPresenceMask - <B>155</B>
 *
 *  @param  pUserIdSize;
 *          - This parameter is an input parameter and should be initialised
 *            to the size of pUserId field. Size of this parameter is 2
 *            uint8_ts.
 *          - Bit to check in ParamPresenceMask - <B>155</B>
 *
 *  @param  pAuthPassword
 *          - Password to be used during data network authentication;
 *          - maximum length allowed is 127 uint8_ts
 *          - QMI_ERR_ARG_TOO_LONG will be returned if the storage on the
 *            wireless device is insufficient in size to hold the value.
 *          - Bit to check in ParamPresenceMask - <B>156</B>
 *
 *  @param  pAuthPasswordSize;
 *          - This parameter is an input parameter and should be initialised
 *            to the size of pAuthPassword field. Size of this parameter is 2
 *            uint8_ts.
 *          - Bit to check in ParamPresenceMask - <B>156</B>
 *
 *  @param  pDataRate
 *          - Data Rate Requested
 *            - 0 - Low (Low speed Service Options (SO15) only)
 *            - 1 - Medium (SO33 + low R-SCH)
 *            - 2 - High (SO33 + high R-SCH)
 *            - Default is 2
 *          - Bit to check in ParamPresenceMask - <B>157</B>
 *
 *  @param  pAppType
 *          - Application Type:
 *            - 0x00000001 - Default Application Type
 *            - 0x00000020 - LBS Application Type
 *            - 0x00000040 - Tethered Application Type
 *            - This parameter is not used while creating/modifying a profile
 *          - Bit to check in ParamPresenceMask - <B>158</B>
 *
 *  @param  pDataMode
 *          - Data Mode to use:
 *            - 0 - CDMA or HDR (Hybrid 1X/1xEV-DO)
 *            - 1 - CDMA Only (1X only)
 *            - 2 - HDR Only (1xEV-DO only)
 *            - Default is 0
 *          - Bit to check in ParamPresenceMask - <B>159</B>
 *
 *  @param  pAppPriority
 *          - Application Priority
 *            - Numerical 1 uint8_t value defining the application
 *              priority; higher value implies higher priority
 *            - This parameter is not used while creating/modifying a profile
 *          - Bit to check in ParamPresenceMask - <B>160</B>
 *
 *  @param  pApnString
 *          - String representing the Access Point Name
 *          - maximum length allowed is 100 uint8_ts
 *          - QMI_ERR_ARG_TOO_LONG will be returned if the APN
 *            name is too long.
 *          - Bit to check in ParamPresenceMask - <B>161</B>
 *
 *  @param  pApnStringSize;
 *          - This parameter is an input parameter and should be initialised
 *            to the size of pApnString field. Size of this parameter is 2
 *            uint8_ts.
 *          - Bit to check in ParamPresenceMask - <B>161</B>
 *
 *  @param  pPdnType
 *          - Packed Data Network Type Requested:
 *            - 0 - IPv4 PDN Type
 *            - 1 - IPv6 PDN Type
 *            - 2 - IPv4 or IPv6 PDN Type
 *            - 3 - Unspecified PDN Type (implying no preference)
 *          - Bit to check in ParamPresenceMask - <B>162</B>
 *
 *  @param  pIsPcscfAddressNedded
 *          - This boolean value is used to control if PCSCF
 *            address is requested from PDSN
 *            - 1 -(TRUE) implies request for PCSCF value from the PDSN
 *            - 0 -(FALSE) implies do not request for PCSCF value from the PDSN
 *          - Bit to check in ParamPresenceMask - <B>163</B>
 *
 *  @param  pPrimaryV4DnsAddress
 *          - IPv4 Primary DNS address
 *            - The Primary IPv4 DNS address that can be statically assigned
 *              to the UE
 *          - Bit to check in ParamPresenceMask - <B>164</B>
 *
 *  @param  pSecondaryV4DnsAddress
 *          - IPv4 Secondary DNS address
 *            - The Secondary IPv4 DNS address that can be statically assigned
 *              to the UE
 *          - Bit to check in ParamPresenceMask - <B>165</B>
 *
 *  @param  pPriV6DnsAddress
 *          - Primary IPv6 DNS address
 *            - The Primary IPv6 DNS address that can be statically assigned
 *              to the UE
 *          - Bit to check in ParamPresenceMask - <B>166</B>
 *
 *  @param  pSecV6DnsAddress
 *          - Secondary IPv6 DNS address
 *            - The Secondary IPv6 DNS address that can be statically assigned
 *              to the UE
 *          - Bit to check in ParamPresenceMask - <B>167</B>
 *
 *  @param  pRATType
 *          - Optional 1 uint8_t Flag indicating RAT Type
 *          - Values:
 *            - 1 - HRPD
 *            - 2 - EHRPD
 *            - 3 - HRPD_EHRPD
 *          - This parameter is currently read only and can be read by using
 *            the function SLQSGetProfileSettings().
 *          - Bit to check in ParamPresenceMask - <B>168</B>
 *
 *  @param  pAPNEnabled3GPP2
 *          - Optional 1 uint8_t Flag indicating if the APN is disabled/enabled
 *          - If disabled, the profile can not be used for making data calls
 *          - Values:
 *            - 0 - Disabled
 *            - 1 - Enabled(default value)
 *          - This parameter is currently read only and can be read by using
 *            the function SLQSGetProfileSettings().
 *          - Bit to check in ParamPresenceMask - <B>169</B>
 *
 *  @param  pPDNInactivTimeout3GPP2
 *          - Optional 4 uint8_ts indicating the duration of inactivity timer
 *            in seconds
 *          - If the PDP context/PDN connection is inactive for this duration
 *            i.e. No data Tx/Rx occurs, the PDP context/PDN connection is
 *            disconnected
 *          - Default value of zero indicates infinite value
 *          - This parameter is currently read only and can be read by using
 *            the function SLQSGetProfileSettings().
 *          - Bit to check in ParamPresenceMask - <B>170</B>
 *
 *  @param  pAPNClass3GPP2
 *          - Optional 1 uint8_t numeric identifier representing the APN in profile
 *          - Can be set and queried but is not used by the modem
 *          - This parameter is currently read only and can be read by using
 *            the function SLQSGetProfileSettings().
 *          - Bit to check in ParamPresenceMask - <B>171</B>
 *
 */
typedef struct 
{
    uint8_t   *pNegoDnsSrvrPref;
    uint32_t  *pPppSessCloseTimerDO;
    uint32_t  *pPppSessCloseTimer1x;
    uint8_t   *pAllowLinger;
    uint16_t *pLcpAckTimeout;
    uint16_t *pIpcpAckTimeout;
    uint16_t *pAuthTimeout;
    uint8_t   *pLcpCreqRetryCount;
    uint8_t   *pIpcpCreqRetryCount;
    uint8_t   *pAuthRetryCount;
    uint8_t   *pAuthProtocol;
    uint8_t   *pUserId;
    uint16_t   *pUserIdSize;
    uint8_t   *pAuthPassword;
    uint16_t   *pAuthPasswordSize;
    uint8_t   *pDataRate;
    uint32_t  *pAppType;
    uint8_t   *pDataMode;
    uint8_t   *pAppPriority;
    uint8_t   *pApnString;
    uint16_t   *pApnStringSize;
    uint8_t   *pPdnType;
    uint8_t   *pIsPcscfAddressNedded;
    uint32_t  *pPrimaryV4DnsAddress;
    uint32_t  *pSecondaryV4DnsAddress;
    uint16_t *pPriV6DnsAddress;
    uint16_t *pSecV6DnsAddress;
    uint8_t   *pRATType;
    uint8_t   *pAPNEnabled3GPP2;
    uint32_t  *pPDNInactivTimeout3GPP2;
    uint8_t   *pAPNClass3GPP2;
}LibpackProfile3GPP2;

/**
 * \ingroup wds
 * 
 * This union WdsProfileParam consists of Profile3GPP and Profile3GPP2
 * out of which one will be used to create profile.
 *
 *  @param  SlqsProfile3GPP 3GPP profile
 *          - See \ref LibpackProfile3GPP
 *
 *  @param  SlqsProfile3GPP2 3GPP2 profile
 *          - See \ref LibpackProfile3GPP2
 */
typedef union unpackWdsProfileParam
{
    LibpackProfile3GPP  SlqsProfile3GPP;
    LibpackProfile3GPP2 SlqsProfile3GPP2;
}UnpackQmiProfileInfo;

/**
 * \ingroup wds
 * 
 * This structure contains the profile settings output
 *
 *  @param  curProfile
 *          - Structure containing details of the current profile
 *          - See \ref UnpackQmiProfileInfo
 *
 *  @param  pExtErrCode
 *          - pointer to a 2 byte extended error code
 *          - Error code will only will be present if error code
 *            eQCWWAN_ERR_QMI_EXTENDED_INTERNAL is returned by device.
 *          - See \ref qm_wds_ds_profile_extended_err_codes enum in qmerrno.h
 *            for received error description.
 *          - Bit to check in ParamPresenceMask - <B>224</B>
 *
 */
typedef struct
{
    UnpackQmiProfileInfo curProfile;
    uint16_t           *pExtErrCode;
}UnPackGetProfileSettingOut;

/**
 * \ingroup wds
 * 
 * This structure contains the profile setting information of parameter pOutput
 * for API unpack_wds_SLQSGetProfileSettings
 *
 *  @param  pProfileSettings - Profile Settings
 *
 *  @param  ProfileType - Profile Type
 *          - 0 - Profile 3GPP
 *          - 1 - Profile 3GPP2
 *
 *  @param  Tlvresult - unpack Tlv Result.
 *
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct
{
    UnPackGetProfileSettingOut *pProfileSettings;
    uint8_t  ProfileType;
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
} unpack_wds_SLQSGetProfileSettings_t;

/**
 * \ingroup wds
 * 
 * Get Profile Settings unpack
 * 
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response structure to fill
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_SLQSGetProfileSettings(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_wds_SLQSGetProfileSettings_t *pOutput
        );

/**
 * \ingroup wds
 * 
 * This structure contains unpack get session state information.
 *
 * @param connectionStatus - state of the current packet data session.
 *        - 1 - Disconnected.
 *        - 2 - Connected.
 *        - 3 - Suspended.
 *        - 4 - Authenticating.
 *        - Bit to check in ParamPresenceMask - <B>1</B>
 *
 * @param  Tlvresult - unpack Tlv Result.
 * 
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct {
    uint32_t    connectionStatus;
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
} unpack_wds_GetSessionState_t;

/**
 * \ingroup wds
 * 
 * get session state pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */
int pack_wds_GetSessionState(
        pack_qmi_t  *pCtx,
        uint8_t     *pReqBuf,
        uint16_t    *pLen
        );

/**
 * \ingroup wds
 * 
 * Get Session State unpack
 * 
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput      response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_GetSessionState(
        uint8_t   *pResp,
        uint16_t  respLen,
        unpack_wds_GetSessionState_t *pOutput
        );

/**
 * \ingroup wds
 * 
 * This structure contains pack get default profile information.
 *
 * @param profiletype profile type
 *        - 0 - WDS_PROFILE_TYPE_3GPP (0x00) - 3GPP
 *        - 1 - WDS_PROFILE_TYPE_3GPP (0x01) - 3GPP2
 *        - 2 - WDS_PROFILE_TYPE_EPC  (0x02) - EPC
 */
typedef struct {
    uint32_t profiletype;
} pack_wds_GetDefaultProfile_t;

/**
 * \ingroup wds
 * 
 *  Reads the default profile settings from the device. The default profile is
 *  used to establish an auto connect data session.
 *
 *  @param  pdptype
 *          - Packet Data Protocol (PDP) type specifies the type of data payload
 *            exchanged over the air link when the packet data session is
 *            established with this profile
 *              - 0 - PDP-IP (IPv4)
 *              - 1 - PDP-PPP
 *              - 2 - PDP-IPv6
 *              - 3 - PDP-IPv4v6
 *          - Bit to check in ParamPresenceMask - <B>17</B>
 *
 *  @param  ipaddr
 *          - Preferred IPv4 address to be assigned to device
 *          - Bit to check in ParamPresenceMask - <B>30</B>
 *
 *  @param  pridns
 *          - Primary DNS IPv4 address preference
 *          - Bit to check in ParamPresenceMask - <B>21</B>
 *
 *  @param  secdns
 *          - Secondary DNS IPv4 address preference
 *          - Bit to check in ParamPresenceMask - <B>22</B>
 *
 *  @param  ipaddrv6
 *          - Preferred IPv6 address to be assigned to device
 *          - Bit to check in ParamPresenceMask - <B>143</B>
 *
 *  @param  pridnsv6
 *          - Primary DNS Pv6 address preference
 *          - Bit to check in ParamPresenceMask - <B>143</B>
 *
 *  @param  secdnsv6
 *          - Secondary DNS IPv6 address preference
 *          - Bit to check in ParamPresenceMask - <B>143</B>
 *
 *  @param  auth
 *          - Bitmap that indicates authentication algorithm preference
 *              - 0x00000001 - PAP preference
 *                  - 0 - Never performed
 *                  - 1 - May be performed
 *              - 0x00000002 - CHAP preference
 *                  - 0 - Never performed
 *                  - 1 - May be performed
 *              - All other bits are reserved and must be set to 0
 *              - If more than 1 bit is set, then device decides which
 *                authentication procedure is performed while setting up data
 *                session e.g. the device may have a policy to select the most
 *                secure authentication mechanism.
 *          - Bit to check in ParamPresenceMask - <B>29</B>
 *
 *  @param  namesize
 *          - Maximum number of characters (including NULL terminator) that
 *            profile name array can contain.
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  @param  name
 *          - Profile name
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  @param  apnsize
 *          - Maximum number of characters (including NULL terminator) that APN
 *            name array can contain
 *          - Bit to check in ParamPresenceMask - <B>20</B>
 *
 *  @param  apnname
 *          - Access point name. NULL-terminated string parameter that is a
 *            logical name used to select GGSN and external packet data
 *            network.
 *          - If value is NULL or omitted, then subscription default value will
 *            be requested.
 *          - Bit to check in ParamPresenceMask - <B>20</B>
 *
 *  @param  usersize
 *          - Maximum number of characters (including NULL terminator) that
 *            username array can contain.
 *          - Bit to check in ParamPresenceMask - <B>27</B>
 *
 *  @param  username
 *          - Username used during network authentication
 *          - Bit to check in ParamPresenceMask - <B>27</B>
 *
 * @param  Tlvresult - unpack Tlv Result.
 * 
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct{
    uint32_t         pdptype;
    uint32_t         ipaddr;
    uint32_t         pridns;
    uint32_t         secdns;
    uint16_t         ipaddrv6;
    uint16_t         pridnsv6;
    uint16_t         secdnsv6;
    uint32_t         auth;
    uint8_t          namesize;
    int8_t           name[255];
    uint8_t          apnsize;
    int8_t           apnname[255];
    uint8_t          usersize;
    int8_t           username[255];
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
} unpack_wds_GetDefaultProfile_t;

/**
 * \ingroup wds
 * 
 * get default profile pack.
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  reqParam request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */
int pack_wds_GetDefaultProfile(
        pack_qmi_t  *pCtx,
        uint8_t     *pReqBuf,
        uint16_t    *pLen,
        pack_wds_GetDefaultProfile_t *reqParam
        );

/**
 * \ingroup wds
 * 
 * Get Default Profile unpack
 * 
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput      response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_GetDefaultProfile(
        uint8_t   *pResp,
        uint16_t  respLen,
        unpack_wds_GetDefaultProfile_t *pOutput
        );

/**
 * \ingroup wds
 * 
 *  This structure contains unpack get connection rate information.
 *
 *  @param  currentChannelTXRate
 *          - Current channel Tx rate (in bps)
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param  currentChannelRXRate
 *          - Current channel Rx rate (in bps)
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param  maxChannelTXRate
 *          - Maximum Tx rate (bps) that may be assigned  to device by serving
 *            system.
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param  maxChannelRXRate
 *          - Maximum Rx rate (bps) that may be assigned to device by serving
 *            system.
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 * 
 *  @param  pRateType[OUT]
 *          - Rate Type.
 *
 *  @param  pCurrentChannelTXRate[OUT]
 *          - Instantaneous channel Tx rate in bits per second.
 *
 *  @param  pCurrentChannelRXRate[OUT]
 *          - Instantaneous channel Rx rate in bits per second.
 *
 *  @param   pMaxChannelTXRate[OUT]
 *          - Maximum Tx rate that can be assigned to the device by the
 *          - serving system in bits per second
 *
 *  @param   pMaxChannelRXRate[OUT]
 *          - Maximum Rx rate that can be assigned to the device by the
 *          - serving system in bits per second
 *
 *  @param  Tlvresult - unpack Tlv Result.
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
*/
typedef struct{
    uint32_t         currentChannelTXRate;
    uint32_t         currentChannelRXRate;
    uint32_t         maxChannelTXRate;
    uint32_t         maxChannelRXRate;
    uint32_t         extRateType;
    uint64_t         extCurrentChannelTXRate;
    uint64_t         extCurrentChannelRXRate;
    uint64_t         extMaxChannelTXRate;
    uint64_t         extMaxChannelRXRate;
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
} unpack_wds_GetConnectionRate_t;

/**
 * \ingroup wds
 * 
 * get connection rate pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: No
 */
int pack_wds_GetConnectionRate(
        pack_qmi_t  *pCtx,
        uint8_t     *pReqBuf,
        uint16_t    *pLen
        );

/**
 * \ingroup wds
 * 
 * get connection rate unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput      response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_GetConnectionRate(
        uint8_t   *pResp,
        uint16_t  respLen,
        unpack_wds_GetConnectionRate_t *pOutput
        );

/**
 * \ingroup wds
 * 
 * Deprecated.  Use pack_wds_GetPacketStatistics_t instead
 * This structure contains pack get packet status information.
 *
 * @param statmask packet statistics mask
 *    - 0x00000001 - Tx packets OK
 *    - 0x00000002 - Rx packets OK
 *    - 0x00000004 - Tx packet errors
 *    - 0x00000008 - Rx packet errors
 *    - 0x00000010 - Tx overflows
 *    - 0x00000020 - Rx overflows
 *    - 0x00000040 - Tx bytes OK
 *    - 0x00000080 - Rx bytes OK
 *    - 0x00000100 - Tx packets dropped
 *    - 0x00000200 - Rx packets dropped
 */
typedef struct{
    uint32_t         statmask;
} pack_wds_GetPacketStatus_t;

/**
 * \ingroup wds
 * 
 *  Deprecated.  Use unpack_wds_GetPacketStatistics_t instead
 *  Returns the packet data transfer statistics since the start of the current
 *  packet data.
 *
 *  @param  tXPacketSuccesses
 *          - No. of packets transmitted without error
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  @param  rXPacketSuccesses
 *          - No. of packets received without error
 *          - Bit to check in ParamPresenceMask - <B>17</B>
 *
 *  @param  tXPacketErrors
 *          - No. of outgoing packets with framing errors
 *          - Bit to check in ParamPresenceMask - <B>18</B>
 *
 *  @param  rXPacketErrors
 *          - No. of incoming packets with framing errors
 *          - Bit to check in ParamPresenceMask - <B>19</B>
 *
 *  @param  txPacketOverflows
 *          - Number of packets dropped  because Tx buffer overflowed
 *          - Bit to check in ParamPresenceMask - <B>20</B>
 *
 *  @param  rxPacketOverflows
 *          - Number of packets dropped because Rx buffer overflowed
 *          - Bit to check in ParamPresenceMask - <B>21</B>
 *
 *  @param  txOkBytesCount
 *          - No of bytes transmitted without error.
 *          - Bit to check in ParamPresenceMask - <B>25</B>
 *
 *  @param  rxOkBytesCount
 *          - No of bytes received without error.
 *          - Bit to check in ParamPresenceMask - <B>26</B>
 *
 *  @param  txOKBytesLastCall
 *          - No of bytes transmitted without error during the
 *            last data call (0 if no call was made earlier).
 *            Returned only if not in a call, and when the previous call was
 *            made using RmNet (for any devices that support
 *          - Bit to check in ParamPresenceMask - <B>27</B>
 *
 *  @param  rxOKBytesLastCall
 *          - Number of bytes received without error
 *            during the last data call (0 if no call was
 *            made earlier). Returned only if not in a
 *            call, and when the previous call was
 *            made using RmNet (for any devices that
 *            support
 *          - Bit to check in ParamPresenceMask - <B>28</B>
 *
 *  @param  txDroppedCount
 *          - Number of outgoing packets dropped.
 *          - Bit to check in ParamPresenceMask - <B>29</B>
 *
 *  @param  rxDroppedCount
 *          - Number of incoming packets dropped.
 *          - Bit to check in ParamPresenceMask - <B>30</B>
 *
 * @param  Tlvresult - unpack Tlv Result.
 * 
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct{
    uint32_t        tXPacketSuccesses;
    uint32_t        rXPacketSuccesses;
    uint32_t        tXPacketErrors;
    uint32_t        rXPacketErrors;
    uint32_t        tXPacketOverflows;
    uint32_t        rXPacketOverflows;
    uint64_t        tXOkBytesCount;
    uint64_t        rXOkBytesCount;
    uint64_t        tXOKBytesLastCall;
    uint64_t        rXOKBytesLastCall;
    uint32_t        tXDroppedCount;
    uint32_t        rXDroppedCount;
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
} unpack_wds_GetPacketStatus_t;

/**
 * \ingroup wds
 * 
 * get packet status pack
 * Deprecated.  Use pack_wds_GetPacketStatistics instead
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  reqParam request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */
int pack_wds_GetPacketStatus(
        pack_qmi_t  *pCtx,
        uint8_t     *pReqBuf,
        uint16_t    *pLen,
        pack_wds_GetPacketStatus_t *reqParam
        );

/**
 * \ingroup wds
 * 
 * get packet status unpack
 * Deprecated.  Use unpack_wds_GetPacketStatistics instead
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_GetPacketStatus(
        uint8_t   *pResp,
        uint16_t  respLen,
        unpack_wds_GetPacketStatus_t *pOutput
        );

/**
 * \ingroup wds
 * 
 *  This structure contains unpack get session duration information.
 *
 *  @param  callDuration
 *          - Duration of the current packet session in milliseconds
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param  Tlvresult - unpack Tlv Result.
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct{
    uint64_t      callDuration;
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
} unpack_wds_GetSessionDuration_t;

/**
 * \ingroup wds
 * 
 *  This structure contains pack get session duration information.
 *
 *  @param  NULL
 *          - this is a dummy structure
 */
typedef struct{

}pack_wds_GetSessionDuration_t;

/**
 * \ingroup wds
 * 
 * get session duration pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  reqParam request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: No
 */
int pack_wds_GetSessionDuration(
        pack_qmi_t  *pCtx,
        uint8_t     *pReqBuf,
        uint16_t    *pLen,
        pack_wds_GetSessionDuration_t *reqParam
        );

/**
 * \ingroup wds
 * 
 * get session duration unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_GetSessionDuration(
        uint8_t   *pResp,
        uint16_t  respLen,
        unpack_wds_GetSessionDuration_t *pOutput
        );

/**
 * \ingroup wds
 * 
 *  This structure contains unpack get dormancy state information.
 *
 *  @param  dormancyState
 *          - Dormancy state of current packet data session
 *              - 1 - Traffic channel dormant
 *              - 2 - Traffic channel active
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 * @param  Tlvresult - unpack Tlv Result.
 * 
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct{
    uint32_t    dormancyState;
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
} unpack_wds_GetDormancyState_t;

/**
 * \ingroup wds
 * 
 *  This structure contains pack get dormancy state information.
 *
 *  @param  NULL
 *          - this is a dummy structure
 */
typedef struct{
    
}pack_wds_GetDormancyState_t;

/**
 * \ingroup wds
 * 
 * get dormancy state pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  reqParam request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: No
 */
int pack_wds_GetDormancyState(
        pack_qmi_t  *pCtx,
        uint8_t     *pReqBuf,
        uint16_t    *pLen,
        pack_wds_GetDormancyState_t *reqParam
        );

/**
 * \ingroup wds
 * 
 * get dormancy state unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_GetDormancyState(
        uint8_t   *pResp,
        uint16_t  respLen,
        unpack_wds_GetDormancyState_t *pOutput
        );

/**
 * \ingroup wds
 * 
 * This structure contains the information about the profile to be deleted.
 *
 *  @param  profileType
 *          - Identifies the type of profile
 *            - 0x00 - 3GPP
 *          - Note: Deletion of 3GPP2 profiles is not supported.
 *
 *  @param  profileIndex
 *          - Index of the configured profile to be deleted
 *               - Value between 1 - 16 (EM/MC73xx or earlier)
 *               - Value between 1 - 24 (EM/MC74xx onwards)
 *
 */
typedef struct{
    uint8_t profileType;
    uint8_t profileIndex;
} pack_wds_SLQSDeleteProfile_t;

/**
 * \ingroup wds
 * 
 *  This structure contains unpack delete profile information.
 *
 *  @param  extendedErrorCode[OUT]
 *          - The extended error code received from DS Profile subsystem of type
 *            eWDS_ERR_PROFILE_REG_xxx.
 *          - Error code will only will be present if error code
 *            eQCWWAN_ERR_QMI_EXTENDED_INTERNAL is returned by device.
 *          - See \ref qm_wds_ds_profile_extended_err_codes enum in qmerrno.h
 *            for received error description.
 *          - Bit to check in ParamPresenceMask - <B>224</B>
 *
 *  @param  Tlvresult - unpack Tlv Result.
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct{
    uint16_t extendedErrorCode;
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
} unpack_wds_SLQSDeleteProfile_t;

/**
 * \ingroup wds
 * 
 * delete stored profile pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  reqParam request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */
int pack_wds_SLQSDeleteProfile(
        pack_qmi_t  *pCtx,
        uint8_t     *pReqBuf,
        uint16_t    *pLen,
        pack_wds_SLQSDeleteProfile_t *reqParam
        );

/**
 * \ingroup wds
 * 
 * delete stored profile unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_SLQSDeleteProfile(
        uint8_t   *pResp,
        uint16_t  respLen,
        unpack_wds_SLQSDeleteProfile_t *pOutput
        );

/**
 * \ingroup wds
 * 
 *  Writes the default profile settings to the device. The default profile is
 *  used to establish an autoconnect data session.
 *
 *  @param  profileType
 *          - Type of profile
 *              - 0 - 3GPP
 *              - 1 - 3GPP2
 *
 *  @param  pdpType
 *          - Packet Data Protocol (PDP) type specifies the type of data payload
 *            exchanged over the air link when the packet data session is
 *            established with this profile (optional)
 *              - 0 - PDP-IP (IPv4)
 *              - 1 - PDP-PPP
 *              - 2 - PDP-IPv6
 *              - 3 - PDP-IPv4v6
 *
 *  @param  ipAddress
 *          - Preferred IPv4 addr to be assigned to device (optional)
 *
 *  @param  primaryDNS
 *          - Primary DNS Ipv4 address preference (optional)
 *
 *  @param  secondaryDNS
 *          - Secondary DNS Ipv4 address preference (optional)
 *
 *  @param  authentication
 *          - Bitmap that indicates authentication algorithm preference (optional)
 *              - 0x00000001 - PAP preference\n
 *                  - 0 - Never performed
 *                  - 1 - May be performed
 *              - 0x00000002 - CHAP preference\n
 *                  - 0 - Never performed
 *                  - 1 - May be performed
 *              - All other bits are reserved and must be set to 0
 *              - If more than 1 bit is set, then device decides which
 *                authentication procedure is performed while setting up data
 *                session e.g. the device may have a policy to select the most
 *                secure authentication mechanism.
 *
 *  @param  pName
 *          - profile Name (optional)
 *
 *  @param  pUsername
 *          - Username used during network authentication (optional)
 *
 *  @param  pAPNName
 *          - Access point name. NULL-terminated string parameter that is a
 *            logical name used to select GGSN and external packet data
 *            network (optional)
 *          - If value is NULL or omitted, then subscription default value will
 *            be requested.
 *
 *  @param  pPassword
 *          - Password used during network authentication (optional)
 */
typedef struct{
	uint8_t		index;
    uint32_t    profileType;
    uint32_t    pdpType;
    uint32_t    ipAddress;
    uint32_t    primaryDNS;
    uint32_t    secondaryDNS;
    uint32_t    authentication;
    uint8_t     *pName;
    uint8_t     *pUsername;
    uint8_t     *pApnname;
    uint8_t     *pPassword;
} pack_wds_SetDefaultProfile_t;

/**
 * \ingroup wds
 * 
 * set default profile pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  reqParam request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */
int pack_wds_SetDefaultProfile(
        pack_qmi_t  *pCtx,
        uint8_t     *pReqBuf,
        uint16_t    *pLen,
        pack_wds_SetDefaultProfile_t *reqParam
        );

typedef unpack_result_t unpack_wds_SetDefaultProfile_t;

/**
 * \ingroup wds
 * 
 * set default profile unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_SetDefaultProfile(
        uint8_t   *pResp,
        uint16_t  respLen,
        unpack_wds_SetDefaultProfile_t *pOutput
        );

/**
 * \ingroup wds
 * 
 * This structure contains unpack get 3GPP configure item information.
 *
 * @param  LTEAttachProfile
 *        - LTE Attach Profile
 *            - points to a single WORD Value indicating the
 *              attached LTE Profile
 *            - Optional parameter with possible values 1-16 (EM/MC73xx or earlier)
 *        - This setting is deprecated on MC/EM74xx
 *        - Bit to check in ParamPresenceMask - <B>16</B>
 *
 * @param profileList Profile List
 *        - an array of 4 profile configurations
 *        - Each element points to a single WORD value indicating profile
 *        - Optional parameter with possible values
 *            - 1 - 16 (MC/EM73xx and before)
 *            - 1 - 24 (MC/EM74xx and onwards)
 *        - function SLQSGet3GPPConfigItem() returns a default value 255
 *          if no 3gpp configuration is present
 *        - Bit to check in ParamPresenceMask - <B>17</B>
 *        - Note: the 5th entry is currently ignored, please set it to zero
 *
 * @param[out] defaultPDNEnabled 
 *        - 0 - disabled 
 *        - 1 - enabled
 *        - Bit to check in ParamPresenceMask - <B>18</B>
 *
 * @param[out] _3gppRelease 3GPP release 
 *        - 0 - Release_99 
 *        - 1 - Release_5 
 *        - 2 - Release_6 
 *        - 3 - Release_7 
 *        - 4 - Release_8 
 *        - 5 - Release_9  (In 9x30 and toworads)
 *        - 6 - Release_10 (In 9x30 and toworads)
 *        - 7 - Release_11 (In 9x30 and toworads)
 *        - Bit to check in ParamPresenceMask - <B>19</B>
 *
 * @param[out] LTEAttachProfileList
 *          - pointer to WORD array indiciating LTE Attach Profile List
 *              - Optional parameter
 *              - possible values: 1-24
 *              - This setting is only supported for MC/EM74xx onwards
 *              - Please provide attach profiles in order of decreasing priority in this list. 
 *          - Bit to check in ParamPresenceMask - <B>20</B>
 *
 * @param[in,out] LTEAttachProfileListLen
 *          - Number of element in pLTEAttachProfileList
 *             - valid range: 1-24
 *             - This setting is only supported for MC/EM74xx onwards
 *          - Bit to check in ParamPresenceMask - <B>20</B>
 *
 * @param  Tlvresult - unpack Tlv Result.
 * 
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct{
    uint16_t LTEAttachProfile;
    uint16_t profileList[4];
    uint8_t  defaultPDNEnabled;
    uint8_t  _3gppRelease;
    uint16_t LTEAttachProfileList[MAX_WDS_3GPP_CONF_LTE_ATTACH_PROFILE_LIST_SIZE];
    uint16_t LTEAttachProfileListLen;
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
} unpack_wds_SLQSGet3GPPConfigItem_t;

/**
 * \ingroup wds
 * 
 * get 3Gpp config items pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */
int pack_wds_SLQSGet3GPPConfigItem(
        pack_qmi_t  *pCtx,
        uint8_t     *pReqBuf,
        uint16_t    *pLen
        );

/**
 * \ingroup wds
 * 
 * get 3GPP config items unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_SLQSGet3GPPConfigItem(
        uint8_t   *pResp,
        uint16_t  respLen,
        unpack_wds_SLQSGet3GPPConfigItem_t *pOutput
        );

/**
 * \ingroup wds
 * 
 * This structure contains pack set 3GPP configuration item information.
 *
 * @param  pLTEAttachProfile
 *        - Optional parameter
 *        - LTE Attach Profile
 *            - points to a single WORD Value indicating the
 *              attached LTE Profile
 *            - Optional parameter with possible values 1-16 (EM/MC73xx or earlier)
 *        - This setting is deprecated on MC/EM74xx
 *
 * @param ProfileList Profile List
 *        - an array of 4 profile configurations
 *        - Each element points to a single WORD value indicating profile
 *        - Optional parameter with possible values
 *            - 1 - 16 (MC/EM73xx and before)
 *            - 1 - 24 (MC/EM74xx and onwards)
 *        - function SLQSGet3GPPConfigItem() returns a default value 255
 *          if no 3gpp configuration is present
 *
 * @param pDefaultPDNEnabled
 *        - Optional parameter
 *          - 0 - disabled
 *          - 1 - enabled
 *
 * @param p3gppRelease 3GPP release
 *        - Optional parameter
 *          - 0 - Release_99
 *          - 1 - Release_5
 *          - 2 - Release_6
 *          - 3 - Release_7
 *          - 4 - Release_8
 *        - In 9x30 and onwards
 *          - 5 - Release 9
 *          - 6 - Release 10
 *          - 7 - Release 11
 *
 * @param pLTEAttachProfileList
 *          - pointer to WORD array indicating LTE Attach Profile List
 *              - Optional parameter
 *              - possible values: 1-24
 *              - This setting is only supported for MC/EM74xx onwards
 *              - Please provide attach profiles in order of decreasing priority in this list. 
 *
 * @param LTEAttachProfileListLen
 *          - Number of element in pLTEAttachProfileList
 *             - valid range: 1-24
 *             - This setting is only supported for MC/EM74xx onwards
 */
typedef struct{
    uint16_t *pLTEAttachProfile;
    uint16_t *pProfileList;
    uint8_t  *pDefaultPDNEnabled;
    uint8_t  *p3gppRelease;
    uint16_t *pLTEAttachProfileList;
    uint16_t  LTEAttachProfileListLen;
} pack_wds_SLQSSet3GPPConfigItem_t;

/**
 * \ingroup wds
 * 
 * set 3Gpp config items pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  reqParam request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */
int pack_wds_SLQSSet3GPPConfigItem(
        pack_qmi_t  *pCtx,
        uint8_t     *pReqBuf,
        uint16_t    *pLen,
        pack_wds_SLQSSet3GPPConfigItem_t *reqParam
        );

typedef unpack_result_t unpack_wds_SLQSSet3GPPConfigItem_t;

/**
 * \ingroup wds
 * 
 * Set 3GPP Configuration Items unpack
 * 
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput unpacked response
 */
int unpack_wds_SLQSSet3GPPConfigItem(
        uint8_t   *pResp,
        uint16_t  respLen,
        unpack_wds_SLQSSet3GPPConfigItem_t *pOutput
        );

/**
 * \ingroup wds
 * 
 *  This structure contains unpack get mobile IP information.
 *  @param  mipMode
 *          - Mobile IP setting
 *              - 0 - Mobile IP off (simple IP only)
 *              - 1 - Mobile IP preferred
 *              - 2 - Mobile IP only
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 * @param  Tlvresult - unpack Tlv Result.
 * 
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
*/
typedef struct{
uint32_t         mipMode;
uint16_t Tlvresult;
swi_uint256_t  ParamPresenceMask;
} unpack_wds_GetMobileIP_t;

/**
 * \ingroup wds
 * 
 *  This structure contains pack get mobile IP information.
 *
 *  @param  NULL
 *          - this is a dummy structure
*/
typedef struct{

}pack_wds_GetMobileIP_t;

/**
 * \ingroup wds
 * 
 * get mobile ip mode pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  pReqParam request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: No
 */
int pack_wds_GetMobileIP(
    pack_qmi_t  *pCtx,
    uint8_t     *pReqBuf,
    uint16_t    *pLen,
    pack_wds_GetMobileIP_t *pReqParam
    );

/**
 * \ingroup wds
 * 
 * Get Mobile IP Mode unpack
 * 
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput      response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
*/
int unpack_wds_GetMobileIP(
    uint8_t   *pResp,
    uint16_t  respLen,
    unpack_wds_GetMobileIP_t *pOutput
    );

/**
 * \ingroup wds
 * 
 *  This structure contains pack get mobile IP profile information.
 *
 *  @param  index
 *          - Mobile IP profile ID
 */
typedef struct{
uint8_t   index;
} pack_wds_GetMobileIPProfile_t;

/**
 * \ingroup wds
 * 
 *  This structure contains unpack get mobile IP profile information.
 *
 *  @param  enabled
 *          - Profile enabled:
 *              - 0 - Disabled
 *              - 1 - Enabled
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  @param  address
 *          - Home IPv4 address:
 *          - Bit to check in ParamPresenceMask - <B>17</B>
 *
 *  @param  primaryHA
 *          - Primary home agent IPv4 address
 *          - Bit to check in ParamPresenceMask - <B>18</B>
 *
 *  @param  secondaryHA
 *          - Secondary home agent IPv4 address
 *          - Bit to check in ParamPresenceMask - <B>19</B>
 *
 *  @param  revTunneling
 *          - Reverse tunneling enabled
 *              - 0 - Disabled
 *              - 1 - Enabled
 *          - Bit to check in ParamPresenceMask - <B>20</B>
 *
 *  @param  naiSize
 *          - The maximum number of characters (including NULL terminator) that
 *            the NAI array can contain.
 *          - Bit to check in ParamPresenceMask - <B>21</B>
 *
 *  @param  NAI
 *          - Network access identifier string
 *          - Bit to check in ParamPresenceMask - <B>21</B>
 *
 *  @param  HASPI
 *          - Home agent security parameter index
 *          - Bit to check in ParamPresenceMask - <B>22</B>
 *
 *  @param  AAASPI
 *          - AAA server security parameter index
 *          - Bit to check in ParamPresenceMask - <B>23</B>
 *
 *  @param  HAState
 *          - Home agent key state
 *              - 0 - Unset
 *              - 1 - Set, default value
 *              - 2 - Set, modified from default
 *              - 3 - 0xFFFFFFFF - Unknown
 *          - Bit to check in ParamPresenceMask - <B>26</B>
 *
 *  @param  AAAState
 *          - AAA key state
 *              - 0 - Unset
 *              - 1 - Set, default value
 *              - 2 - Set, modified from default
 *              - 3 - 0xFFFFFFFF - Unknown
 *          - Bit to check in ParamPresenceMask - <B>27</B>
 *
 *  @param  Tlvresult - unpack Tlv Result.
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
*/
typedef struct{
uint8_t   enabled;
uint32_t  address;
uint32_t  primaryHA;
uint32_t  secondaryHA;
uint8_t   revTunneling;
uint8_t   naiSize;
int8_t    NAI[255];
uint32_t  HASPI;
uint32_t  AAASPI;
uint32_t  HAState;
uint32_t  AAAState;
uint16_t Tlvresult;
swi_uint256_t  ParamPresenceMask;
} unpack_wds_GetMobileIPProfile_t;

/**
 * \ingroup wds
 * 
 * get mobile ip profile pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  reqParam request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */
int pack_wds_GetMobileIPProfile(
    pack_qmi_t  *pCtx,
    uint8_t     *pReqBuf,
    uint16_t    *pLen,
    pack_wds_GetMobileIPProfile_t *reqParam
    );

/**
 * \ingroup wds
 * 
 * Get Mobile IP Profile Unpack
 * 
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_GetMobileIPProfile(
    uint8_t   *pResp,
    uint16_t  respLen,
    unpack_wds_GetMobileIPProfile_t *pOutput
    );

/**
 * \ingroup wds
 * 
 * Network information structure
 *
 *  @param  NetworkType
 *          - Values:
 *              - 0 - 3GPP
 *              - 1 - 3GPP2
 *
 *  @param  RATMask
 *          @ref TableWDSRatMask
 *
 *  @param  SOMask
 *          @ref TableWDSSOMask
 */
typedef struct
{
uint8_t  NetworkType;
uint32_t RATMask;
uint32_t SOMask;
}currNetworkInfo;

/**
 * \ingroup wds
 * 
 * Data System Status
 *
 *  @param  prefNetwork
 *          - Preferred Network
 *          - Values:
 *              - 0 - 3GPP
 *              - 1 - 3GPP2
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  @param  networkInfoLen
 *          - As input parameter size assigned to next parameter i.e.
 *            network information
 *          - As output the actual number of network information elements
 *            returned by the device
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  @param   currNetworkInfo
 *          - Network information
 *          - See \ref currNetworkInfo for more details
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  @param  Tlvresult - unpack Tlv Result.
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct{
uint8_t             prefNetwork;
uint8_t             networkInfoLen;
currNetworkInfo     currNetworkInfo[255];
uint16_t Tlvresult;
swi_uint256_t  ParamPresenceMask;
} unpack_wds_SLQSGetCurrDataSystemStat_t;

/**
 * \ingroup wds
 * 
 *  This structure contains pack get current data system state information.
 *
 *  @param  NULL
 *          - this is a dummy structure
*/
typedef struct{

}pack_wds_SLQSGetCurrDataSystemStat_t;
/**
 * \ingroup wds
 * 
 * get current data system pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  pReqParam request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */
int pack_wds_SLQSGetCurrDataSystemStat(
    pack_qmi_t  *pCtx,
    uint8_t     *pReqBuf,
    uint16_t    *pLen,
    pack_wds_SLQSGetCurrDataSystemStat_t *pReqParam
    );

/**
 * \ingroup wds
 * 
 * get current data system unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_SLQSGetCurrDataSystemStat(
    uint8_t   *pResp,
    uint16_t  respLen,
    unpack_wds_SLQSGetCurrDataSystemStat_t *pOutput
    );

/**
 * \ingroup wds
 * 
 * structure to store last mobile IP error.
 *
 *  @param  error
 *          - Status of last MIP call (or attempt)
 *              - Zero - Success
 *              - NonZero - Error code \n
 *              See \ref qaGobiApiTableCallEndReasons.h for Mobile IP
 *              Error codes
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param  Tlvresult - unpack Tlv Result.
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct{
uint32_t             error;
uint16_t Tlvresult;
swi_uint256_t  ParamPresenceMask;
} unpack_wds_GetLastMobileIPError_t;

/**
 * \ingroup wds
 * 
 *  This structure contains pack get last mobile IP error information.
 *
 *  @param  NULL
 *          - this is a dummy structure
*/
typedef struct{

}pack_wds_GetLastMobileIPError_t;

/**
 * \ingroup wds
 * 
 * get current data system pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  pReqParam request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: No
 */
int pack_wds_GetLastMobileIPError(
    pack_qmi_t  *pCtx,
    uint8_t     *pReqBuf,
    uint16_t    *pLen,
    pack_wds_GetLastMobileIPError_t *pReqParam
    );

/**
 * \ingroup wds
 * 
 * get current data system unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_GetLastMobileIPError(
    uint8_t   *pResp,
    uint16_t  respLen,
    unpack_wds_GetLastMobileIPError_t *pOutput
    );

/**
 * \ingroup wds
 * 
  * RM Transfer Satistics Structure
  *  @param  bResetStatistics
  *          - Reset Statistics
  *          - Values:
  *          - 0 - Not Reset
  *          - Other - Reset
  *
  *  @param  ulMask
  *         - Enable/Disable RM Transfer Satatistics Indiscation Mask
  *         - Bit 0: Tx Packet Ok
  *         - Bit 1: Rx Packet Ok
  *         - Bit 2: Tx Bytes Ok
  *         - Bit 3: Rx Bytes Ok
  *         - Bit 4: Tx Packets Dropped
  *         - Bit 5: Rx Packets Dropped
  *         - Value:
  *         -0 - Disable
  *         -1 - Enable
  */
typedef struct
{
uint8_t   bResetStatistics;
uint32_t  ulMask;
} rmTrasnferStaticsReq;

/**
 * \ingroup wds
 * 
 *  This structure contains pack fetch current data system transfer statistics information.
 *
 *  @param  RmTrasnferStaticsReq[IN]
 *          - See \ref rmTrasnferStaticsReq for more information
 *
 */
typedef struct{
rmTrasnferStaticsReq   RmTrasnferStaticsReq;
} pack_wds_RMSetTransferStatistics_t;

/**
 * \ingroup wds
 * 
 * RM set transfer statistics pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  reqParam request parameter
 *
 * @note PDN Specific: No
 */
int pack_wds_RMSetTransferStatistics(
    pack_qmi_t  *pCtx,
    uint8_t     *pReqBuf,
    uint16_t    *pLen,
    pack_wds_RMSetTransferStatistics_t *reqParam
    );

/**
 * \ingroup wds
 * 
 *  This structure contains unpack fetch current data system transfer statistics information.
 *
 *  @param  Tlvresult - unpack Tlv Result.
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
*/
typedef struct
{
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_wds_RMSetTransferStatistics_t;

/**
 * \ingroup wds
 * 
 * RM set transfer statistics unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_RMSetTransferStatistics(
    uint8_t   *pResp,
    uint16_t  respLen,
    unpack_wds_RMSetTransferStatistics_t *pOutput
    );

/**
 * \ingroup wds
 * 
 *  Sets the mobile IP parameters.
 *
 *  @param  spc
 *          - Six digit service programming code string
 *
 *  @param  index
 *          - Index of the profile to modify
 *
 *  @param  pEnabled
 *          - (Optional) Enable profile?
 *           0       - Disabled
 *           Nonzero - Enabled
 *
 *  @param  pAddress
 *          - (Optional) Home IPv4 address
 *
 *  @param  pPrimaryHA
 *          - (Optional) Primary home agent IPv4 address
 *
 *  @param  pSecondaryHA
 *          - (Optional) Secondary home agent IPv4 address
 *
 *  @param  pRevTunneling
 *          - (Optional) Enable reverse tunneling?
 *           0       - Disabled
 *           Nonzero - Enabled
 *
 *  @param  pNAI
 *          - (Optional) Network access identifier string
 *
 *  @param  pHASPI
 *          - (Optional) Home agent security parameter index
 *
 *  @param  pAAASPI
 *          - (Optional) AAA server security parameter index
 *
 *  @param  pMNHA
 *          - (Optional) MN-HA key string
 *
 *  @param  pMNAAA
 *          - (Optional) MN-AAA key string
 */
typedef struct{
int8_t   spc[10];
uint8_t  index;
uint8_t  *pEnabled;
uint32_t *pAddress;
uint32_t *pPrimaryHA;
uint32_t *pSecondaryHA;
uint8_t  *pRevTunneling;
int8_t   *pNAI;
uint32_t *pHASPI;
uint32_t *pAAASPI;
int8_t   *pMNHA;
int8_t   *pMNAAA;
} pack_wds_SetMobileIPProfile_t;

/**
 * \ingroup wds
 * 
 * set mobile ip profile pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  reqParam request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */
int pack_wds_SetMobileIPProfile(
    pack_qmi_t  *pCtx,
    uint8_t     *pReqBuf,
    uint16_t    *pLen,
    pack_wds_SetMobileIPProfile_t *reqParam
    );

/**
 * \ingroup wds
 * 
 *  This structure contains set mobile IP profile information.
 *
 * @param  Tlvresult - unpack Tlv Result.
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
*/
typedef struct
{
uint16_t Tlvresult;
swi_uint256_t  ParamPresenceMask;
}unpack_wds_SetMobileIPProfile_t;
/**
 * \ingroup wds
 * 
 * set mobile ip profile unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_SetMobileIPProfile(
    uint8_t   *pResp,
    uint16_t  respLen,
    unpack_wds_SetMobileIPProfile_t *pOutput
    );

/**
 * \ingroup wds
 * 
 * This structure contains the PDP Runtime Settings Request parameters.
 *
 *  @param  contextId
 *          - Context Identifier
 *
 *  @param  contextType
 *          - Identifies technology type
 *             - 0 - 3GPP
 *             - 1 - 3GPP2
 *
 */
typedef struct
{
uint8_t  contextId;
uint8_t  contextType;
} pack_wds_SLQSWdsSwiPDPRuntimeSettings_t;

/**
 * \ingroup wds
 * 
 * This structure contains the IPv6 address information
 *
 * @param IPV6PrefixLen Length of the received IPv6 address
 *              - 0xff - Invalid IPv6 address information.
 * @param IPAddressV6 IPv6 address(in network byte order)
 */
typedef struct
{
uint8_t   IPV6PrefixLen;
uint16_t  IPAddressV6[IPV6_ADDRESS_ARRAY_SIZE];
}ipv6AddressInfo;

/**
 * \ingroup wds
 * 
 * This structure contains the unpack parameters retrieved by the API
 * unpack_wds_SLQSWdsSwiPDPRuntimeSettings
 *
 *  @param  contextId (optional)
 *          - Context Identifier
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  @param  bearerId (optional)
 *          - Bearer Identity
 *          - An EPS bearer identity uniquely identifies an EPS bearer for one
 *            UE accessing via E-UTRAN. The EPS Bearer Identity is allocated by
 *            the MME.
 *          - Bit to check in ParamPresenceMask - <B>17</B>
 *
 *  @param  apnName (optional)
 *          - APN name associated with the context id
 *          - Bit to check in ParamPresenceMask - <B>18</B>
 *
 *  @param  ipv4Address (optional)
 *          - IPv4 Address
 *          - Bit to check in ParamPresenceMask - <B>19</B>
 *
 *  @param  ipv4GWAddress (optional)
 *          - IPv4 Gateway Address
 *          - Bit to check in ParamPresenceMask - <B>20</B>
 *
 *  @param  prDNSIPv4Address (optional)
 *          - Primary DNS IPv4 Address
 *          - Bit to check in ParamPresenceMask - <B>21</B>
 *
 *  @param  seDNSIPv4Address (optional)
 *          - Secondary DNS IPv4 Address
 *          - Bit to check in ParamPresenceMask - <B>22</B>
 *
 *  @param  ipv6Address (optional)
 *          - IPv6 Address
 *          - Bit to check in ParamPresenceMask - <B>23</B>
 *
 *  @param  ipv6GWAddress (optional)
 *          - IPv6 Gateway Address
 *          - See \ref ipv6AddressInfo for more information
 *          - Bit to check in ParamPresenceMask - <B>24</B>
 *
 *  @param  prDNSIPv6Address (optional)
 *          - Primary IPv6 DNS Address(in network byte order)
 *          - This is an 8-element array of 16-bit numbers, each of which is
 *            in big-endian format
 *          - Bit to check in ParamPresenceMask - <B>25</B>
 *
 *  @param  seDNSIPv6Address (optional)
 *          - Secondary IPv6 DNS Address(in network byte order)
 *          - This is an 8-element array of 16-bit numbers, each of which is
 *            in big-endian format
 *          - Bit to check in ParamPresenceMask - <B>26</B>
 *
 *  @param  prPCSCFIPv4Address (optional)
 *          - Primary PCSCF IPv4 Address
 *          - Bit to check in ParamPresenceMask - <B>27</B>
 *
 *  @param  sePCSCFIPv4Address (optional)
 *          - Secondary PCSCF IPv4 Address
 *          - Bit to check in ParamPresenceMask - <B>28</B>
 *
 *  @param  prPCSCFIPv6Address (optional)
 *          - Primary PCSCF IPv6 Address
 *          - This is an 8-element array of 16-bit numbers, each of which is
 *            in big-endian format
 *          - Bit to check in ParamPresenceMask - <B>29</B>
 *
 *  @param  sePCSCFIPv6Address (optional)
 *          - Secondary PCSCF IPv6 Address
 *          - This is an 8-element array of 16-bit numbers, each of which is
 *            in big-endian format
 *          - Bit to check in ParamPresenceMask - <B>30</B>
 *
 *  @param  Tlvresult - unpack Tlv Result.
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct
{
uint8_t                   contextId;
uint8_t                   bearerId;
int8_t                    apnName[100];
uint32_t                  ipv4Address;
uint32_t                  ipv4GWAddress;
uint32_t                  prDNSIPv4Address;
uint32_t                  seDNSIPv4Address;
ipv6AddressInfo           ipv6Address;
ipv6AddressInfo           ipv6GWAddress;
uint16_t                  prDNSIPv6Address[IPV6_ADDRESS_ARRAY_SIZE];
uint16_t                  seDNSIPv6Address[IPV6_ADDRESS_ARRAY_SIZE];
uint32_t                  prPCSCFIPv4Address;
uint32_t                  sePCSCFIPv4Address;
uint16_t                  prPCSCFIPv6Address[IPV6_ADDRESS_ARRAY_SIZE];
uint16_t                  sePCSCFIPv6Address[IPV6_ADDRESS_ARRAY_SIZE];
uint16_t                  Tlvresult;
swi_uint256_t             ParamPresenceMask;
} unpack_wds_SLQSWdsSwiPDPRuntimeSettings_t;

/**
 * \ingroup wds
 * 
 * swi pdp runtime settings pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  reqParam request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */
int pack_wds_SLQSWdsSwiPDPRuntimeSettings(
    pack_qmi_t  *pCtx,
    uint8_t     *pReqBuf,
    uint16_t    *pLen,
    pack_wds_SLQSWdsSwiPDPRuntimeSettings_t *reqParam
    );

/**
 * \ingroup wds
 * 
 * get Swi PDP Runtime Settings unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_SLQSWdsSwiPDPRuntimeSettings(
    uint8_t   *pResp,
    uint16_t  respLen,
    unpack_wds_SLQSWdsSwiPDPRuntimeSettings_t *pOutput
    );

/**
 * \ingroup wds
 * 
 * This structure contains the transfer statistic indication information
 *
 * @param StatsPeriod Field Period between transfer statistic reports.
 *            - 0 - Do not report.
 *            - 1 - Other - Period between reports (in seconds).
 *
 * @param StatsMask requested statistic bit mask.
 *            - 0x00000040 - Tx bytes OK
 *            - 0x00000080 - Rx bytes OK
 */
typedef struct
{
uint8_t  StatsPeriod;
uint32_t StatsMask;
} wds_transferStatInd;

/**
 * \ingroup wds
 * 
 * This structure contains the DUN Call Info Request parameters.
 *
 *  @param  Mask
 *          - Mandatory parameter
 *          - Set the bits corresponding to the information requested to 1
 *          - All other bits must be set to 0.
 *          - If any values are not available or applicable, the corresponding
 *            TLVs are not returned in the response.
 *              - Bit 0 - Connection Status
 *              - Bit 1 - Last call end reason
 *              - Bit 2 - Tx/Rx bytes OK
 *              - Bit 3 - Dormancy status
 *              - Bit 4 - Data bearer
 *              - Bit 5 - Channel rate
 *              - Bit 6 - Call active duration
 *
 *  @param  pReportConnStatus
 *          - Connect Status Indicator
 *              - 0 - Do not report
 *              - 1 - Report connection status and call end reason
 *
 *  @param  pTransferStatInd
 *          - See \ref wds_transferStatInd for more information
 *
 *  @param  pReportDormStatus
 *          - Dormancy Status Indicator
 *              - 0 - Do not report
 *              - 1 - Report traffic channel state of interface used for
 *                    data connection
 *
 *  @param  pReportDataBearerTech
 *          - Current Data Bearer Technology Indicator
 *              - 0 - Do not report
 *              - 1 - Report radio interface used for data transfer when
 *                    it changes
 *
 *  @param  pReportChannelRate
 *          - Channel Rate Indicator
 *              - 0 - Do not report
 *              - 1 - Report channel rate
 */
typedef struct
{
uint32_t           Mask;
uint8_t            *pReportConnStatus;
wds_transferStatInd    *pTransferStatInd;
uint8_t            *pReportDormStatus;
uint8_t            *pReportDataBearerTech;
uint8_t            *pReportChannelRate;
} pack_wds_SLQSGetDUNCallInfo_t;

/**
 * \ingroup wds
 * 
 *  This structure contains modem connection status
 *
 *  @param  MDMConnStatus
 *          - Current link status
 *              - 0x01 - DISCONNECTED
 *              - 0x02 - CONNECTED
 *              - 0xff - Invalid data.
 *
 *  @param  MDMCallDuration
 *          - Call duration in milliseconds.
 *          - If the modem connection status is connected,
 *            this represent the duration of the current DUN call.
 *          - If the modem connection status is disconnected, this
 *            represents the duration of the last DUN call since the
 *            device was powered up (zero, if no call has been made or
 *            if the last call was not DUN).
 *              - 0xffffffffffffffff - Invalid data.
 */
typedef struct
{
uint8_t      MDMConnStatus;
uint64_t     MDMCallDuration;
} connectionStatus;

/**
 * \ingroup wds
 * 
 *  This structure contains Channel Rate
 *
 *  @param  CurrChanTxRate
 *          - Instantaneous channel Tx rate in bits per second
 *          - 0xffffffff - Invalid data.
 *
 *  @param  CurrChanRxRate
 *          - Instantaneous channel Rx rate in bits per second
 *          - 0xffffffff - Invalid data.
 *
 *  @param  MaxChanTxRate
 *          - maximum Tx rate that can be assigned to the device
 *            by the serving system in bits per second
 *          - 0xffffffff - Invalid data.
 *
 *  @param  MaxChanRxRate
 *          - maximum Rx rate that can be assigned to the device
 *            by the serving system in bits per second
 *          - 0xffffffff - Invalid data.
 */
typedef struct
{
uint32_t CurrChanTxRate;
uint32_t CurrChanRxRate;
uint32_t MaxChanTxRate;
uint32_t MaxChanRxRate;
} dunchannelRate;

/**
 * \ingroup wds
 * 
 * This structure contains the DUN Call Info response parameters
 *
 *  @param  connectionStatus
 *          - See \ref connectionStatus for more information
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  @param  callEndReason
 *          - Last modem call end reason
 *          - See qaGobiApiTableCallEndReasons.h for Call End Reason
 *          - Only valid if the last call made was DUN, else zero is returned
 *          - Bit to check in ParamPresenceMask - <B>17</B>
 *
 *  @param  txOKBytesCount
 *          - Number of bytes transmitted without error
 *          - Returned only if a data call is up
 *          - Bit to check in ParamPresenceMask - <B>18</B>
 *
 *  @param  rxOKBytesCount
 *          - Number of bytes received without error
 *          - Returned only if a data call is up
 *          - Bit to check in ParamPresenceMask - <B>19</B>
 *
 *  @param  dormancyStatus
 *          - Current traffic channel status
 *          - Returned if a data call is up
 *              - 0x01 - Traffic channel dormant
 *              - 0x02 - Traffic channel active
 *          - Bit to check in ParamPresenceMask - <B>20</B>
 *
 *  @param  dataBearerTech
 *          - Current data bearer technology
 *          - Returned only if a data call is up
 *              - 0x01 - cdma2000 1X
 *              - 0x02 - cdma2000 HRPD (1xEV-DO)
 *              - 0x03 - GSM
 *              - 0x04 - UMTS
 *              - 0x05 - cdma200 HRPD ( 1xEV-DO RevA)
 *              - 0x06 - EDGE
 *              - 0x07 - HSDPA and WCDMA
 *              - 0x08 - WCDMA and HSUPA
 *              - 0x09 - HSDPA and HSUPA
 *              - 0x0A - LTE
 *              - 0x0B - cdma2000 EHRPD
 *              - 0x0C - HSDPA+ and WCDMA
 *              - 0x0D - HSDPA+ and HSUPA
 *              - 0x0E - DC_HSDPA+ and WCDMA
 *              - 0x0F - DC_HSDPA+ and HSUPA
 *              - 0x10 - HSDPA+ and 64QAM
 *              - 0x11 - HSDPA+, 64QAM and HSUPA
 *              - 0x12 - TDSCDMA
 *              - 0x13 - TDSCDMA and HSDPA
 *          - Bit to check in ParamPresenceMask - <B>21</B>
 *
 *  @param  channelRate
 *          - See \ref dunchannelRate for more information
 *          - Bit to check in ParamPresenceMask - <B>22</B>
 *
 *  @param  lastCallTXOKBytesCnt
 *          - Number of bytes transmitted without error during the last
 *            data call ( 0 if no call was made ).
 *          - Return only if not in a call and the previous call was made
 *            using DUN.
 *          - Bit to check in ParamPresenceMask - <B>23</B>
 *
 *  @param  lastCallRXOKBytesCnt
 *          - Number of bytes transmitted without error during the last
 *            data call ( 0 if no call was made ).
 *          - Return only if not in a call and the previous call was made
 *            using DUN.
 *          - Bit to check in ParamPresenceMask - <B>24</B>
 *
 *  @param  mdmCallDurationActive
 *          - Duration that the call is active in milliseconds
 *          - If the modem connection status is connected, this represents
 *            the active duration of the current DUN call
 *          - If the modem connection status is disconnected, this represents
 *            the duration of the last DUN call since the device was powered
 *            up (0 if no call has been made or if the last call was not DUN)
 *          - Bit to check in ParamPresenceMask - <B>25</B>
 *
 *  @param  lastCallDataBearerTech
 *          - Last Call Data Bearer Technology
 *          - Returned only if not in a call and when the previous call was
 *            made using DUN
 *              - 0x01 - cdma2000 1X
 *              - 0x02 - cdma2000 HRPD (1xEV-DO)
 *              - 0x03 - GSM
 *              - 0x04 - UMTS
 *              - 0x05 - cdma200 HRPD (1xEV-DO Rev A)
 *              - 0x06 - EDGE
 *              - 0x07 - HSDPA and WCDMA
 *              - 0x08 - WCDMA and HSUPA
 *              - 0x09 - HSDPA and HSUPA
 *              - 0x0A - LTE
 *              - 0x0B - cdma2000 EHRPD
 *              - 0x0C - HSDPA+ and WCDMA
 *              - 0x0D - HSDPA+ and HSUPA
 *              - 0x0E - DC_HSDPA+ and WCDMA
 *              - 0x0F - DC_HSDPA+ and HSUPA
 *              - 0x10 - HSDPA+ and 64QAM
 *              - 0x11 - HSDPA+, 64QAM and HSUPA
 *              - 0x12 - TDSCDMA
 *              - 0x13 - TDSCDMA and HSDPA
 *          - Bit to check in ParamPresenceMask - <B>32</B>
 *
 * @param  Tlvresult - unpack Tlv Result.
 * 
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct
{
connectionStatus    connectionStatus;
uint16_t            callEndReason;
uint64_t            txOKBytesCount;
uint64_t            rxOKBytesCount;
uint8_t             dormancyStatus;
uint8_t             dataBearerTech;
dunchannelRate         channelRate;
uint64_t            lastCallTXOKBytesCnt;
uint64_t            lastCallRXOKBytesCnt;
uint64_t            mdmCallDurationActive;
uint8_t             lastCallDataBearerTech;
uint16_t Tlvresult;
swi_uint256_t       ParamPresenceMask;
} unpack_wds_SLQSGetDUNCallInfo_t;

/**
 * \ingroup wds
 * 
 * get dun call info pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  reqParam request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */
int pack_wds_SLQSGetDUNCallInfo(
    pack_qmi_t  *pCtx,
    uint8_t     *pReqBuf,
    uint16_t    *pLen,
    pack_wds_SLQSGetDUNCallInfo_t *reqParam
    );

/**
 * \ingroup wds
 * 
 * get dun call info unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
*/
int unpack_wds_SLQSGetDUNCallInfo(
    uint8_t   *pResp,
    uint16_t  respLen,
    unpack_wds_SLQSGetDUNCallInfo_t *pOutput
    );

/**
 * \ingroup wds
 * 
 *  Structure to hold the current data bearer technology values
 *
 *  @param  currentNetwork[OUT]
 *          - current selected network\n
 *              - 0 - UNKNOWN
 *              - 1 - 3GPP2
 *              - 2 - 3GPP
 *              - 0xff - Invalid data.
 *
 *  @param  ratMask[OUT]
 *          @ref TableWDSRatMask
 *
 *  @param  soMask[OUT]
 *          @ref TableWDSSOMask
 */
typedef struct
{
uint8_t  currentNetwork;
uint32_t ratMask;
uint32_t soMask;
} qmiWDSDataBearerTechnology;

/**
 * \ingroup wds
 * 
 *  Bit mask values to indicate the presence of data bearer information for the
 *  current and last data calls
 */
enum liteQmiDataBearerMasks
{
    QMI_LITE_WDS_CURRENT_CALL_DB_MASK = 0x01,
    QMI_LITE_WDS_LAST_CALL_DB_MASK    = 0x02
};
/**
 * \ingroup wds
 * 
 *  Structure to hold the data bearer technology values
 *
 *  @param  dataBearerMask[OUT]
 *          - This bit mask indicates if data bearer information for the current
 *            and/or last call has been received from the device. If a bit is
 *            set, then the information is available in the corresponding
 *            structure i.e. the one provided by the caller.
 *            Refer to \ref liteQmiDataBearerMasks for bit-mask positions.
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param  curDataBearerTechnology[OUT]
 *          - current data bearer technology value.
 *          - See \ref qmiWDSDataBearerTechnology
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param  lastCallDataBearerTechnology[OUT]
 *          - last call data bearer technology value.
 *          - See \ref qmiWDSDataBearerTechnology
 *              - NULL if the parameter is not required
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  @param  Tlvresult - unpack Tlv Result.
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct
{
uint8_t dataBearerMask;
qmiWDSDataBearerTechnology curDataBearerTechnology;
qmiWDSDataBearerTechnology lastCallDataBearerTechnology;
uint16_t Tlvresult;
swi_uint256_t  ParamPresenceMask;
} unpack_wds_SLQSGetDataBearerTechnology_t;

/**
 * \ingroup wds
 * 
 *  This structure contains pack get data bearer technology information.
 *
 *  @param  NULL
 *          - this is a dummy structure
 */
typedef struct{

}pack_wds_SLQSGetDataBearerTechnology_t;
/**
 * \ingroup wds
 * 
 * get data bearer technology pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  pReqParam request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */
int pack_wds_SLQSGetDataBearerTechnology(
    pack_qmi_t  *pCtx,
    uint8_t     *pReqBuf,
    uint16_t    *pLen,
    pack_wds_SLQSGetDataBearerTechnology_t *pReqParam
    );

/**
 * \ingroup wds
 * 
 * get data bearer technology unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_SLQSGetDataBearerTechnology(
    uint8_t   *pResp,
    uint16_t  respLen,
    unpack_wds_SLQSGetDataBearerTechnology_t *pOutput
    );

/**
 * \ingroup wds
 * 
 * This structure contains pack set IP family preference information
 *
 * @param IPFamilyPreference IP Family preference
 *                               - PACK_WDS_IPV4 IP Version 4
 *                               - PACK_WDS_IPV6 IP Version 6
 */

typedef struct{
    uint8_t IPFamilyPreference;
}pack_wds_SLQSSetIPFamilyPreference_t;

/**
 * \ingroup wds
 * 
 * This structure contains unpack Set IP family preference information
 * @param Tlvresult unpack result
 *
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct{
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_wds_SLQSSetIPFamilyPreference_t;

/**
 * \ingroup wds
 * 
 * Set IP Family Preference pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  pReqParam request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_wds_SLQSSetIPFamilyPreference(
    pack_qmi_t  *pCtx,
    uint8_t     *pReqBuf,
    uint16_t    *pLen,
    pack_wds_SLQSSetIPFamilyPreference_t *pReqParam
);

/**
 * \ingroup wds
 * 
 * Set IP Family Preference unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_SLQSSetIPFamilyPreference(
    uint8_t   *pResp,
    uint16_t  respLen,
    unpack_wds_SLQSSetIPFamilyPreference_t *pOutput
);

/**
 * \ingroup wds
 * 
 * This structure to hold Set default profile number
 *
 * @param type profile type
 *          - Identifies the technology type of the profile.
 *           - Values:
 *              - WDS_PROFILE_TYPE_3GPP (0x00) - 3GPP
 *              - WDS_PROFILE_TYPE_3GPP2 (0x01) - 3GPP2
 *              - WDS_PROFILE_TYPE_EPC (0x02) - EPC
 *
 * @param family profile family
 *          - Identifies the family of the profile.
 *           - Values:
 *              - WDS_PROFILE_FAMILY_EMBEDDED (0x00) - Embedded
 *              - WDS_PROFILE_FAMILY_TETHERED (0x01) - Tethered
 *              - WDS_PROFILE_FAMILY_SOCKET (0x01) â€“ Sockets (deprecated)
 *
 *  @param  index Profile number to be set as default profile.
 *
 */
typedef struct{
    uint8_t type;
    uint8_t family;
    uint8_t index;
}pack_wds_SetDefaultProfileNum_t;

/**
 * \ingroup wds
 * 
 * set default profile number pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  pReqParam request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_wds_SetDefaultProfileNum(
    pack_qmi_t  *pCtx,
    uint8_t     *pReqBuf,
    uint16_t    *pLen,
    pack_wds_SetDefaultProfileNum_t *pReqParam
    );

typedef unpack_result_t unpack_wds_SetDefaultProfileNum_t;
/**
 * \ingroup wds
 * 
 * set default profile number unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_SetDefaultProfileNum(
    uint8_t   *pResp,
    uint16_t  respLen,
    unpack_wds_SetDefaultProfileNum_t *pOutput
    );

/**
 * \ingroup wds
 * 
 * This structure contains pack Get Default Profile Number information.
 *
 * @param type profile type
 *          - Identifies the technology type of the profile.
 *           - Values:
 *              - WDS_PROFILE_TYPE_3GPP (0x00) - 3GPP
 *              - WDS_PROFILE_TYPE_3GPP2 (0x01) - 3GPP2
 *              - WDS_PROFILE_TYPE_EPC (0x02) - EPC
 *
 * @param family profile family
 *          - Identifies the family of the profile.
 *           - Values:
 *              - WDS_PROFILE_FAMILY_EMBEDDED (0x00) - Embedded
 *              - WDS_PROFILE_FAMILY_TETHERED (0x01) - Tethered
 *              - WDS_PROFILE_FAMILY_SOCKET (0x01) â€“ Sockets (deprecated)
 */
typedef struct{
    uint8_t type;
    uint8_t family;
}pack_wds_GetDefaultProfileNum_t;

/**
 * \ingroup wds
 * 
 * This structure contains unpack Get Default Profile Number information.
 *
 * @param index profile index 
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 * @param  Tlvresult - unpack Tlv Result.
 * 
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct{
    uint8_t index;
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_wds_GetDefaultProfileNum_t;

/**
 * \ingroup wds
 * 
 * get default profile number pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  pReqParam request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_wds_GetDefaultProfileNum(
        pack_qmi_t  *pCtx,
        uint8_t     *pReqBuf,
        uint16_t    *pLen,
        pack_wds_GetDefaultProfileNum_t *pReqParam
        );

/**
 * \ingroup wds
 * 
 * get default profile number unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_GetDefaultProfileNum(
        uint8_t   *pResp,
        uint16_t  respLen,
        unpack_wds_GetDefaultProfileNum_t *pOutput
        );

/**
 * \ingroup wds
 * 
 * This structure contains DHCP v4 ProfielID Information.
 * @param profileType profile type
 *           - 0 - 3GPP
 *
 * @param profileId profile index
 *           - index identifiying the profile 1-24 valid for 3GPP profile type (EM74xx and onwards)
 *
 *  This is deprecated
 *
 */
typedef struct
{
    uint8_t profileType;
    uint8_t profileId;
} wdsDhcpv4ProfileId;

/**
 * \ingroup wds
 * 
 * Structure contain DHCP V4 Hardware Configuration.
 * @param hwType DHCP HW Type, examples:
 *           - 0 - Ethernet
 *           - 20 - Serial
 *
 * @param chaddrLen Length of chaddr field, examples:
 *           - 6 for Ethernet MAC address
 *
 * @param chaddr Client hardware address
 *
 *  This is deprecated
 */
typedef struct
{
    uint8_t hwType;
    uint8_t chaddrLen;
    uint8_t chaddr[16];
} wdsDhcpv4HwConfig;

/**
 * \ingroup wds
 * 
 * This structure contains DHCP V4 Option information.
 *
 * @param optCode Option code
 *           - 0 - 255
 *
 * @param optValLen Option value length
 *           - 0 - 255
 *
 * @param optVal Option Value
 *
 *  This is deprecated
 */
typedef struct
{
    uint8_t optCode;
    uint8_t optValLen;
    uint8_t optVal[255];
} wdsDhcpv4Option;

/**
 * \ingroup wds
 * 
 * Structure contain DHCP V4 Option List
 * @param numOpt number of options
 *           - 0 - 255
 *
 * @param pOptList pointer to list of DHCP Options
 *           - See \ref wdsDhcpv4Option
 *
 *  This is deprecated
 */
typedef struct
{
    uint8_t numOpt;
    wdsDhcpv4Option *pOptList;
} wdsDhcpv4OptionList;

/**
 * \ingroup wds
 * 
 *  This structure contain get DHCPv4 client configure.
 *
 *  @param  pProfileId pointer to Profile Id structure
 *          - See \ref wdsDhcpv4ProfileId
 *          
 *  This is deprecated
 *
*/ 
typedef struct
{
    wdsDhcpv4ProfileId   *pProfileId;
} pack_wds_SLQSSGetDHCPv4ClientConfig_t;

/**
 * \ingroup wds
 * 
 * WDS SWI DHCPv4 Config Structure
 *
 *  @param  pHWConfig
 *          - pointer to HW Config structure
 *          - See \ref wdsDhcpv4HwConfig
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  @param  pRequestOptionList
 *          - pointer to Option List structure to be sent in
 *            DHCP request
 *          - See \ref wdsDhcpv4OptionList
 *          - Bit to check in ParamPresenceMask - <B>17</B>
 *
 *  @param  Tlvresult - unpack Tlv Result.
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 *  This is deprecated
 */
typedef struct
{
    wdsDhcpv4HwConfig    *pHwConfig;
    wdsDhcpv4OptionList  *pRequestOptionList;
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
} unpack_wds_SLQSSGetDHCPv4ClientConfig_t;

/**
 * \ingroup wds
 * 
 * get DHCPv4 Client Config pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  pReq request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  This API is deprecated
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
 int pack_wds_SLQSSGetDHCPv4ClientConfig(
        pack_qmi_t  *pCtx,
        uint8_t     *pReqBuf,
        uint16_t    *pLen,
        pack_wds_SLQSSGetDHCPv4ClientConfig_t *pReq);

 /**
 * \ingroup wds
 * 
 * get DHCPv4 Client Config  unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  This API is deprecated
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_SLQSSGetDHCPv4ClientConfig(
        uint8_t   *pResp,
        uint16_t  respLen,
        unpack_wds_SLQSSGetDHCPv4ClientConfig_t *pOutput
        );

/**
 * \ingroup wds
 * 
 *  This structure contains pack get packet statistics information.
 *
 *  @param  pStatMask
 *          - Packet Statistics Mask
 *             - 0x00000001 - Tx packets OK
 *             - 0x00000002 - Rx packets OK
 *             - 0x00000004 - Tx packet errors
 *             - 0x00000008 - Rx packet errors
 *             - 0x00000010 - Tx overflows
 *             - 0x00000020 - Rx overflows
 *             - 0x00000040 - Tx bytes OK
 *             - 0x00000080 - Rx bytes OK
 */
typedef struct
{
    uint32_t *pStatMask;
} pack_wds_GetPacketStatistics_t;

/**
 * \ingroup wds
 * 
 * gets current packet transfer counter values pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  pReq request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
 int pack_wds_GetPacketStatistics(
        pack_qmi_t  *pCtx,
        uint8_t     *pReqBuf,
        uint16_t    *pLen,
        pack_wds_GetPacketStatistics_t *pReq);

/**
 * \ingroup wds
 * 
 *  This structure contains unpack get packet statistics information.
 *
 *  @param  pTXPacketSuccesses
 *          - No of transmitted Packets without error.
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  @param  pRXPacketSuccesses
 *          - No of received Packets without error.
 *          - Bit to check in ParamPresenceMask - <B>17</B>
 *
 *  @param  pTXPacketErrors
 *          - Number of outgoing packets with framing errors.
 *          - Bit to check in ParamPresenceMask - <B>18</B>
 *
 *  @param  pRXPacketErrors
 *          - Number of incoming packets with framing errors.
 *          - Bit to check in ParamPresenceMask - <B>19</B>
 *
 *  @param  pTXPacketOverflows
 *          - Number of packets dropped because Tx buffer overflowed (out of memory).
 *          - Bit to check in ParamPresenceMask - <B>20</B>
 *
 *  @param  pRXPacketOverflows
 *          - Number of packets dropped because Rx buffer overflowed (out of memory).
 *          - Bit to check in ParamPresenceMask - <B>21</B>
 *
 *  @param  pTXOkBytesCount
 *          - Number of bytes transmitted without error.
 *          - Bit to check in ParamPresenceMask - <B>25</B>
 *
 *  @param  pRXOkBytesCount
 *          - Number of bytes received without error.
 *          - Bit to check in ParamPresenceMask - <B>26</B>
 *
 *  @param  pTXOKBytesLastCall
 *          - Number of bytes transmitted without error during the
 *            last data call (0 if no call was made earlier).
 *            Returned only if not in a call, and when the previous call was
 *            made using RmNet (for any devices that support
 *          - Bit to check in ParamPresenceMask - <B>27</B>
 *
 *  @param  pRXOKBytesLastCall
 *          - Number of bytes received without error
 *            during the last data call (0 if no call was
 *            made earlier). Returned only if not in a
 *            call, and when the previous call was
 *            made using RmNet (for any devices that
 *            support
 *          - Bit to check in ParamPresenceMask - <B>28</B>
 *
 *  @param  pTXDroppedCount
 *          - Number of outgoing packets dropped.
 *          - Bit to check in ParamPresenceMask - <B>29</B>
 *
 *  @param  pRXDroppedCount
 *          - Number of incoming packets dropped.
 *          - Bit to check in ParamPresenceMask - <B>30</B>
 *
 * @param  Tlvresult - unpack Tlv Result.
 * 
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
 typedef struct
 {
    uint32_t    *pTXPacketSuccesses;
    uint32_t    *pRXPacketSuccesses;
    uint32_t    *pTXPacketErrors;
    uint32_t    *pRXPacketErrors;
    uint32_t    *pTXPacketOverflows;
    uint32_t    *pRXPacketOverflows;
    uint64_t    *pTXOkBytesCount;
    uint64_t    *pRXOkBytesCount;
    uint64_t    *pTXOKBytesLastCall;
    uint64_t    *pRXOKBytesLastCall;
    uint32_t    *pTXDroppedCount;
    uint32_t    *pRXDroppedCount;
    uint16_t    Tlvresult;
    swi_uint256_t  ParamPresenceMask;
 } unpack_wds_GetPacketStatistics_t;

 /**
 * \ingroup wds
 * 
 * gets current packet transfer counter values unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_GetPacketStatistics(
        uint8_t   *pResp,
        uint16_t  respLen,
        unpack_wds_GetPacketStatistics_t *pOutput
        );

/**
 * \ingroup wds
 * 
 * get Rx/Tx byte counts since the start of the last packet data session pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */
int pack_wds_GetByteTotals(
        pack_qmi_t  *pCtx,
        uint8_t     *pReqBuf,
        uint16_t    *pLen
        );
/**
 * \ingroup wds
 * 
 *  This structure contains unpack get byte totals information.
 *
 *  @param  pTXTotalBytes
 *          - Bytes transmitted without error
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  @param  pRXTotalBytes
 *          - Bytes received without error
 *          - Bit to check in ParamPresenceMask - <B>17</B>
 *
 * @param  Tlvresult - unpack Tlv Result.
 * 
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct{
    uint64_t *pTXTotalBytes;
    uint64_t *pRXTotalBytes;
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
} unpack_wds_GetByteTotals_t;

/**
 * \ingroup wds
 * 
 * get Rx/Tx byte counts since the start of the last packet data session unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_GetByteTotals(
        uint8_t   *pResp,
        uint16_t  respLen,
        unpack_wds_GetByteTotals_t *pOutput
        );

/**
 * \ingroup wds
 * 
 * get current Tx/Rx channel bitrate of the current packet data pack
 * This command is deprecated. Please use pack_wds_SLQSSwiGetCurrentChannelRate
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */
int pack_wds_SLQSGetCurrentChannelRate(
        pack_qmi_t  *pCtx,
        uint8_t     *pReqBuf,
        uint16_t    *pLen
        );

/**
 * \ingroup wds
 * 
 * get current Tx/Rx channel bitrate of the current packet data pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */
int pack_wds_SLQSSwiGetCurrentChannelRate(
        pack_qmi_t  *pCtx,
        uint8_t     *pReqBuf,
        uint16_t    *pLen
        );

/**
 * \ingroup wds
 * 
 *  This structure contains unpack get current channel rate information.
 *  
 *  @param  current_channel_tx_rate
 *          - Current Channel Tx Rate.
 *          - Instantaneous channel Tx rate in bits per second.
 *          - In 9x15, this is the total current channel rate for all PDNs combined.
 *          - In 9x30 and later, this is the channel rate for a specific PDN.
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param  current_channel_rx_rate
 *          - Current Channel Rx Rate.
 *          - Instantaneous channel Rx rate in bits per second.
 *          - In 9x15, this is the total current channel rate for all PDNs combined.
 *          - In 9x30 and later, this is the channel rate for a specific PDN
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param  max_channel_tx_rate
 *          - Max Channel Tx Rate.
 *          - Maximum total Tx rate that modem is able to support in current serving
 *            system in bits per second.
 *          - In 9x15, this is a default hard coded value for the current serving system.
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param  max_channel_rx_rate
 *          - Max Channel Rx Rate.
 *          - Maximum total Rx rate that modem is able to support in current serving
 *            system in bits per second.
 *          - In 9x15, this is a default hard coded value for the current serving system.
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 * @param  Tlvresult - unpack Tlv Result.
 * 
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct{
    uint32_t current_channel_tx_rate;
    uint32_t current_channel_rx_rate;
    uint32_t max_channel_tx_rate;
    uint32_t max_channel_rx_rate;
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
} unpack_wds_SLQSGetCurrentChannelRate_t;

/**
 * \ingroup wds
 * 
 * get current Tx/Rx channel bitrate of the current packet data unpack
 * This command is deprecated. Please use unpack_wds_SLQSSwiGetCurrentChannelRate
 * 
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_SLQSGetCurrentChannelRate(
        uint8_t   *pResp,
        uint16_t  respLen,
        unpack_wds_SLQSGetCurrentChannelRate_t *pOutput
        );

/**
 * \ingroup wds
 * 
 * get current Tx/Rx channel bitrate of the current packet data unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_SLQSSwiGetCurrentChannelRate(
        uint8_t   *pResp,
        uint16_t  respLen,
        unpack_wds_SLQSGetCurrentChannelRate_t *pOutput
        );

/**
 * \ingroup wds
 * 
 * get the value of loopback mode and multiplier pack
 * This command is deprecated. Please use pack_wds_SLQSSwiGetLoopback
 * 
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */
int pack_wds_SLQSSGetLoopback(
        pack_qmi_t  *pCtx,
        uint8_t     *pReqBuf,
        uint16_t    *pLen
        );
/**
 * \ingroup wds
 * 
 * get the value of loopback mode and multiplier pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */
int pack_wds_SLQSSwiGetLoopback(
        pack_qmi_t  *pCtx,
        uint8_t     *pReqBuf,
        uint16_t    *pLen
        );

/**
 * \ingroup wds
 * 
 *  This structure contains unpack Get loopback information.
 *
 *  @param  ByteLoopbackMode
 *          - Loopback Mode.
 *              - 0 - Disable
 *              - 1 - Enable
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  @param  ByteLoopbackMultiplier
 *          - Loopback multiplier. Number of downlink bytes to send for each uplink byte.
 *          - Bit to check in ParamPresenceMask - <B>17</B>
 *
 *  @param  Tlvresult - unpack Tlv Result.
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct{
    uint8_t ByteLoopbackMode;
    uint8_t ByteLoopbackMultiplier;
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
} unpack_wds_SLQSSGetLoopback_t;

/**
 * \ingroup wds
 * 
 * get the value of loopback mode and multiplier unpack
 * This command is deprecated/ Please use unpack_wds_SLQSSwiGetLoopback
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_SLQSSGetLoopback(
        uint8_t   *pResp,
        uint16_t  respLen,
        unpack_wds_SLQSSGetLoopback_t *pOutput
        );

/**
 * \ingroup wds
 * 
 * get the value of loopback mode and multiplier unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_SLQSSwiGetLoopback(
        uint8_t   *pResp,
        uint16_t  respLen,
        unpack_wds_SLQSSGetLoopback_t *pOutput
        );

/**
 * \ingroup wds
 * 
 *  This structure contains pack set loopback information.
 *
 *  @param  loopbackMode
 *          - Loopback Mode.
 *            - 0 - Disable
 *            - 1 - Enable
 *
 *  @param  loopbackMultiplier
 *          - Loopback multiplier. Number of downlink bytes to send for each uplink byte.
 */
typedef struct {
    uint8_t loopbackMode;
    uint8_t loopbackMultiplier;
} pack_wds_SLQSSSetLoopback_t;

/**
 * \ingroup wds
 * 
 * Enable/disable Data Loopback Mode and set the value of loopback multiplier pack
 * This command is deprecated. Please use pack_wds_SLQSwiSSetLoopback
 * 
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */
int pack_wds_SLQSSSetLoopback(
        pack_qmi_t *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen,
        pack_wds_SLQSSSetLoopback_t *reqArg
        );

/**
 * \ingroup wds
 * 
 * Enable/disable Data Loopback Mode and set the value of loopback multiplier pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */
int pack_wds_SLQSSwiSetLoopback(
        pack_qmi_t *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen,
        pack_wds_SLQSSSetLoopback_t *reqArg
        );

typedef unpack_result_t unpack_wds_SLQSSSetLoopback_t;

/**
 * \ingroup wds
 * 
 * Enable/disable Data Loopback Mode and set the value of loopback multiplier unpack
 * This command is deprecated. Please use unpack_wds_SLQSSwiSetLoopback
 * 
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_SLQSSSetLoopback(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_wds_SLQSSSetLoopback_t *pOutput
        );

/**
 * \ingroup wds
 * 
 * Enable/disable Data Loopback Mode and set the value of loopback multiplier unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_SLQSSwiSetLoopback(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_wds_SLQSSSetLoopback_t *pOutput
        );

/**
 * \ingroup wds
 * 
 *  This structure contains Data unsigned long TLV data.
 *
 *  @param  ulData unsigend long data in 32bit
 */
typedef struct
{
    uint32_t   ulData;
}wds_DataULongTlv;

/**
 * \ingroup wds
 * 
 *  This structure contains Data unsigned long long TLV data.
 *
 *  @param  ullData unsigend long long data in 64bit
 */
typedef struct
{
    uint64_t   ullData;
}wds_DataULongLongTlv;

/**
 * \ingroup wds
 * 
 * WDS packet RM Transfer Statistics data structure for individual session
 *
 *  @param  TxOkConutTlv
 *          - Tx Ok Packet Tlv Value.
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  @param  RxOkConutTlv
 *          - Rx Ok Packet Tlv Value.
 *          - Bit to check in ParamPresenceMask - <B>17</B>
 *
 *  @param  TxOkByteCountTlv
 *          - Tx Ok Byte Count Packet Tlv Value.
 *          - Bit to check in ParamPresenceMask - <B>25</B>
 *
 *  @param  RxOkByteCountTlv
 *          - Rx Ok Byte Count Packet Tlv Value.
 *          - Bit to check in ParamPresenceMask - <B>26</B>
 *
 *  @param  TxDropConutTlv
 *          - Tx Drop Count Packet Tlv Value.
 *          - Bit to check in ParamPresenceMask - <B>37</B>
 *
 *  @param  RxDropConutTlv
 *          - Rx Drop Count Packet Tlv Value.
 *          - Bit to check in ParamPresenceMask - <B>38</B>
 */
typedef struct {
    wds_DataULongTlv        TxOkConutTlv;
    wds_DataULongTlv        RxOkConutTlv;
    wds_DataULongLongTlv    TxOkByteCountTlv;
    wds_DataULongLongTlv    RxOkByteCountTlv;
    wds_DataULongTlv        TxDropConutTlv;
    wds_DataULongTlv        RxDropConutTlv;
    swi_uint256_t  ParamPresenceMask;
}unpack_RMTransferStatistics_ind_t;

/**
 * \ingroup wds
 * 
 * RM transfer statistics indication unpack
 * This command is deprecated. Please use unpack_wds_SLQSSwiRMTransferStatistics_ind
 * 
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput      response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_RMTransferStatistics_ind(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_RMTransferStatistics_ind_t *pOutput
        );

/**
 * \ingroup wds
 * 
 * RM transfer statistics indication unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput      response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_SLQSSwiRMTransferStatistics_ind(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_RMTransferStatistics_ind_t *pOutput
        );

/**
 * \ingroup wds
 * 
 * WDS SWI DHCPv4 Client Lease Change Structure
 *
 *  This is deprecated
 *
 *  @param  pEnableNotification
 *          - Enable Notification or not
 */
typedef struct {
    uint8_t *pEnableNotification;
} pack_wds_DHCPv4ClientLeaseChange_t;

/**
 * \ingroup wds
 * 
 * DHCP profile id TLV information
 *
 *  @param  profileType identifying the type of the profile
 *          - 0 - 3GPP
 *
 *  @param  profileId index identifying the profile
 *          - 1-24 valid for 3GPP profile type (9x30 and onwards)
 */
typedef struct
{
    uint8_t profileType;
    uint8_t profileId;
} wds_DHCPProfileIdTlv;

/**
 * \ingroup wds
 * 
 * DHCP lease state information
 *
 *  @param  leaseState lease state
 *          - 0 - active, newly acquired
 *          - 1 - active, renewed
 *          - 2 - active, renewing
 *          - 3 - active, rebinding
 *          - 4 - inactive, expired
 *          - 5 - inactive, renew refused
 *          - 6 - inactive, rebind refused
 *          - 7 - inactive, other
 */
typedef struct
{
    uint8_t leaseState;
} wds_DHCPLeaseStateTlv;

/**
 * \ingroup wds
 * 
 * IPv4 address TLV information
 *
 *  @param  IPv4Addr IPv4 address
 */
typedef struct
{
    uint32_t IPv4Addr;
} wds_IPv4AdTlv;

/**
 * \ingroup wds
 * 
 * DHCP option code information
 *
 *  @param  optCode option code
 *          - values:
 *             - 0 - 255
 *
 *  @param  optValLen length of option code
 *          - values:
 *             - 0 - 255
 *
 *  @param  pOptVal option value
 */
typedef struct
{
    uint8_t optCode;
    uint8_t optValLen;
    uint8_t *pOptVal;
} wds_DHCPOpt;

/**
 * \ingroup wds
 * 
 * DHCP lease option information
 *
 *  @param  numOpt number of sets of \ref wds_DHCPOpt
 *
 *  @param  optList option list
 *
 *  @param  optListData option list data
 */
typedef struct
{
    uint8_t     numOpt;
    wds_DHCPOpt optList[WDS_DHCP_MAX_NUM_OPTIONS];
    uint8_t     optListData[WDS_DHCP_OPTION_DATA_BUF_SIZE]; /* internal buffer to store option data */
} wds_DHCPLeaseOptTlv;


/**
 * \ingroup wds
 * 
 * This structure contains DHCP IPv4 client lease information
 *
 *  @param  ProfileIdTlv profile identifier information, see \ref wds_DHCPProfileIdTlv for more details
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param  DHCPv4LeaseStateTlv lease state, see \ref wds_DHCPLeaseStateTlv for more details
 *          - Bit to check in ParamPresenceMask - <B>2</B>
 *
 *  @param  IPv4AddrTlv IPv4 address, see \ref wds_IPv4AdTlv for more details
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  @param  DHCPv4LeaseOptTlv DHCP lease option, see \ref wds_DHCPLeaseOptTlv for more details
 *          - Bit to check in ParamPresenceMask - <B>17</B>
 *
 *  @param  Tlvresult - unpack Tlv Result.
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 *  This is deprecated
 */
typedef struct {
    wds_DHCPProfileIdTlv   ProfileIdTlv;
    wds_DHCPLeaseStateTlv  DHCPv4LeaseStateTlv;
    wds_IPv4AdTlv          IPv4AddrTlv;
    wds_DHCPLeaseOptTlv    DHCPv4LeaseOptTlv;
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
} unpack_wds_DHCPv4ClientLease_ind_t;

/**
 * \ingroup wds
 * 
 *  This structure contains set mobile IP pack information.
 *
 *  @param  mode
 *          - Mobile IP setting
 *              - 0 - Mobile IP off (simple IP only)
 *              - 1 - Mobile IP preferred
 *              - 2 - Mobile IP only
 */
typedef struct {
    uint32_t mode;
} pack_wds_SetMobileIP_t;

/**
 * \ingroup wds
 * 
 * Sets the current mobile IP setting pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */
int pack_wds_SetMobileIP(
        pack_qmi_t *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen,
        pack_wds_SetMobileIP_t *reqArg
        );

typedef unpack_result_t unpack_wds_SetMobileIP_t;

/**
 * \ingroup wds
 * 
 * Sets the current mobile IP setting unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_SetMobileIP(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_wds_SetMobileIP_t *pOutput
        );

/**
 * \ingroup wds
 * 
 *  Mobile IP parameters information.
 *
 *  @param  pSPC
 *          - NULL-terminated string representing six digit service
 *            programming code.
 *
 *  @param  pMode
 *          - Mode to be set (optional)
 *              - 0 - Mobile IP off (simple IP only)
 *              - 1 - Mobile IP preferred
 *              - 2 - Mobile IP only
 *
 *  @param  pRetryLimit
 *          - Registration retry attempt limit (optional)
 *
 *  @param  pRetryInterval
 *          - Registration retry attempt interval used to determine the time
 *            between registration attempts (optional)
 *
 *  @param  pReRegPeriod
 *          - Period (in minutes) to attempt re-registration before current
 *            registration expires (optional)
 *
 *  @param  pReRegTraffic
 *          - Re-registration only if traffic since last attempt (optional)
 *              - Zero    - Disabled
 *              - NonZero - Enabled
 *
 *  @param  pHAAuthenticator
 *          - MH-HA authenticator calculator (optional)
 *              - Zero    - Disabled
 *              - NonZero - Enabled
 *
 *  @param  pHA2002bis
 *          - MH-HA RFC 2002bis authentication instead of RFC2002 (optional)
 *              - Zero    - Disabled
 *              - NonZero - Enabled
 *
 */
typedef struct {
    char     *pSPC;
    uint32_t *pMode;
    uint8_t  *pRetryLimit;
    uint8_t  *pRetryInterval;
    uint8_t  *pReRegPeriod;
    uint8_t  *pReRegTraffic;
    uint8_t  *pHAAuthenticator;
    uint8_t  *pHA2002bis;
}pack_wds_SetMobileIPParameters_t;

/**
 * \ingroup wds
 * 
 * Sets the specified mobile IP parameters pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */
int pack_wds_SetMobileIPParameters(
        pack_qmi_t *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen,
        pack_wds_SetMobileIPParameters_t *reqArg
        );

typedef unpack_result_t unpack_wds_SetMobileIPParameters_t;
/**
 * \ingroup wds
 * 
 * Sets the specified mobile IP parameters unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */

int unpack_wds_SetMobileIPParameters(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_wds_SetMobileIPParameters_t *pOutput
        );

/**
 * \ingroup wds
 * 
 *  auto connect data session parameters.
 *
 *  @param  acsetting
 *          - Current autoconnect setting:
 *            - 0x00 - Autoconnect disabled
 *            - 0x01 - Autoconnect enabled
 *            - 0x02 - Autoconnect paused (resume on powercycle)
 *
 *  @param  acroamsetting
 *          - Current autoconnect roaming status
 *            - 0x00 - Autoconnect always allowed
 *            - 0x01 - Autoconnect while in home service area only
 */
typedef struct {
  uint8_t acsetting;
  uint8_t acroamsetting;
}pack_wds_SetAutoconnect_t;

/**
 * \ingroup wds
 * 
 * Auto connect data session parameters pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */
int pack_wds_SetAutoconnect(
        pack_qmi_t *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen,
        pack_wds_SetAutoconnect_t *reqArg
        );

typedef unpack_result_t unpack_wds_SetAutoconnect_t;
/**
 * \ingroup wds
 * 
 * Auto connect data session parameters unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_SetAutoconnect(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_wds_SetAutoconnect_t *pOutput
        );

/**
 * \ingroup wds
 * 
 *  auto connect data session setting parameter.
 *
 *  @param  pSetting
 *          - NDIS auto connect setting
 *              - 0 - Disabled
 *              - 1 - Enabled
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param  Tlvresult - unpack Tlv Result.
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct {
  uint32_t *psetting;
  uint16_t Tlvresult;
  swi_uint256_t  ParamPresenceMask;
}unpack_wds_GetAutoconnect_t;

/**
 * \ingroup wds
 * 
 * Gets auto connect data session setting pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */

int pack_wds_GetAutoconnect(
        pack_qmi_t *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen
        );

/**
 * \ingroup wds
 * 
 * Gets auto connect data session setting unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_GetAutoconnect(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_wds_GetAutoconnect_t *pOutput);

/**
 * \ingroup wds
 * 
 * This structure contains the information about the Transfer Statistics
 * Indicator parameters.
 *
 *  @param  statsPeriod
 *          - Period between transfer statistics reports.
 *              - 0 - Do not report
 *              - Other - Period between reports (in seconds)
 *
 *  @param  statsMask
 *          - Requested statistic bit mask.
 *              - 0x00000001 - Tx packets OK
 *              - 0x00000002 - Rx packets OK
 *              - 0x00000004 - Tx packet errors
 *              - 0x00000008 - Rx packet errors
 *              - 0x00000010 - Tx overflows
 *              - 0x00000020 - Rx overflows
 *              - 0x00000040 - Tx bytes OK
 *              - 0x00000080 - Rx bytes OK
 *              - 0x00000100 - Tx packets dropped
 *              - 0x00000200 - Rx packets dropped
 *          - Each bit set causes the corresponding optional information to be
 *            sent in SLQSWdsEventReportCallBack.
 *          - All unlisted bits are reserved for future use and must be set to
 *            zero.
 *
 */
typedef struct
{
    uint8_t  statsPeriod;
    uint32_t statsMask;
} wds_TrStatInd;

/**
 * \ingroup wds
 * 
 * This structure contains the information about the Set Event Report Request
 * parameters.
 *
 *  @param  pCurrChannelRateInd (optional)
 *          - Current Channel Rate Indicator.
 *              - 0 - Do not report
 *              - 1 - Report channel rate when it changes
 *
 *  @param  pTransferStatInd (optional)
 *          - Transfer Statistics Indicator
 *          - See \ref wds_TrStatInd for more information.
 *
 *  @param  pDataBearerTechInd (optional) (Deprecated)
 *          - Data Bearer Technology Indicator.
 *              - 0 - Do not report
 *              - 1 - Report radio interface used for data transfer when it
 *                    changes
 *
 *  @param  pDormancyStatusInd (optional)
 *          - Dormancy Status indicator.
 *              - 0 - Do not report
 *              - 1 - Report traffic channel state of interface used for data
 *                    connection
 *
 *  @param  pMIPStatusInd (optional)
 *          - MIP Status Indicator.
 *              - 0 - Do not report
 *              - 1 - Report MIP status
 *
 *  @param  pCurrDataBearerTechInd (optional) (Deprecated)
 *          - Current Data Bearer Technology Indicator.
 *              - 0 - Do not report
 *              - 1 - Report current data bearer technology when it changes
 *
 *  @param  pDataCallStatusChangeInd (optional)
 *          - Data Call Status Change Indicator.
 *              - 0 - Do not report
 *              - 1 - Report data call status change when it changes
 *
 *  @param  pCurrPrefDataSysInd (optional)
 *          - Current Preferred Data System Indicator.
 *              - 0 - Do not report
 *              - 1 - Report preferred data system when it changes
 *
 *  @param  pEVDOPageMonPerChangeInd (optional)
 *          - EV-DO Page Monitor Period Change Indicator.
 *              - 0 - Do not report
 *              - 1 - Report EV-DO page monitor period change event
 *
 *  @param  pDataSystemStatusChangeInd (optional) (Deprecated)
 *          - Data System Status Change Indicator.
 *              - 0 - Do not report
 *              - 1 - Report data system status change event
 * 
 *  @param pUlFlowControlInd (optional)
 *          - Uplink Flow Control Indicator
 *           - Values:
 *              - 0 - Do not report
 *              - 1 - Report uplink flow control change event
 * 
 *  @param  pReportAddPdnFiltersRemoval (optional)
 *          - Additional PDN Filters Removal Indicator
 *              - 0 - Do not report
 *              - 1 - Report additional PDN filters removal event
 *
 *  @param  pDataBearerTechExtInd (optional)
 *          - Data Bearer Technology Extended Indicator.
 *              - 0 - Do not report
 *              - 1 - Report data bearer technology extended when it changes
 * 
 *  @param pDormancyResultIndicator
 *          - Dormancy Result Indicator
 *              - 0 - Do not report
 *              - 1- Report dormancy result
 *
 *  @note At least one parameter should be present.
 *
 */

typedef struct
{
    uint8_t         *pCurrChannelRateInd;
    wds_TrStatInd   *pTransferStatInd;
    uint8_t         *pDataBearerTechInd;
    uint8_t         *pDormancyStatusInd;
    uint8_t         *pMIPStatusInd;
    uint8_t         *pCurrDataBearerTechInd;
    uint8_t         *pDataCallStatusChangeInd;
    uint8_t         *pCurrPrefDataSysInd;
    uint8_t         *pEVDOPageMonPerChangeInd;
    uint8_t         *pDataSystemStatusChangeInd;
	uint8_t			*pUlFlowControlInd;
    uint8_t         *pReportAddPdnFiltersRemoval;
    uint8_t         *pDataBearerTechExtInd;
    uint8_t         *pDormancyResultIndicator;
}pack_wds_SLQSWdsSetEventReport_t;

/**
 * \ingroup wds
 * 
 * Sets the event report parameters pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */

int pack_wds_SLQSWdsSetEventReport(
        pack_qmi_t *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen,
        pack_wds_SLQSWdsSetEventReport_t *reqArg
        );

typedef unpack_result_t unpack_wds_SLQSWdsSetEventReport_t;

/**
 * \ingroup wds
 * 
 * Sets the event report parameters unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_SLQSWdsSetEventReport(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_wds_SLQSWdsSetEventReport_t *pOutput
        );

/**
 * \ingroup wds
 * 
 * Gets the device into dormant state pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */

int pack_wds_SLQSWdsGoDormant(
        pack_qmi_t *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen
        );

typedef unpack_result_t unpack_wds_SLQSWdsGoDormant_t;

/**
 * \ingroup wds
 * 
 * Gets the device into dormant state unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_SLQSWdsGoDormant(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_wds_SLQSWdsGoDormant_t *pOutput
        );

/**
 * \ingroup wds
 * 
 * Gets the device into Active state pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */

int pack_wds_SLQSWdsGoActive(
        pack_qmi_t *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen
        );
typedef unpack_result_t unpack_wds_SLQSWdsGoActive_t;

/**
 * \ingroup wds
 * 
 * Gets the device into Active state unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_SLQSWdsGoActive(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_wds_SLQSWdsGoActive_t *pOutput
        );

/**
 * \ingroup wds
 * 
 * Reset packet data transfer statistics pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 *
*/
int pack_wds_SLQSResetPacketStatics(
        pack_qmi_t *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen);

typedef unpack_result_t unpack_wds_SLQSResetPacketStatics_t;

/**
 * \ingroup wds
 * 
 * Reset packet data transfer statistics unpack.
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_SLQSResetPacketStatics(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_wds_SLQSResetPacketStatics_t *pOutput
        );

/**
 * \ingroup wds
 * 
 * WDS SWI DHCPv4 Profile Identifier Structure
 *
 *  @param  profileType
 *          - 0 for 3GPP
 *  @param  profileId
 *          - 1 to 24 for 3GPP profile
 *
 *  This is deprecated
 *
 */
typedef struct
{
    uint8_t profileType;
    uint8_t profileId;
} wds_DHCPv4ProfileId;

/**
 * \ingroup wds
 * 
 * WDS SWI DHCPv4 HW Config Structure.
 *
 *  @param  hwType
 *           - HW Type
 *           1 - Ethernet
 *           20 - Serial
 *
 *  @param  chaddrlen
 *          - chaddrlen
 *
 *  @param  chaddr
 *          - chaddr. Max size 16 bytes
 *
 *  This is deprecated
 *
 */
typedef struct
{
    uint8_t hwType;
    uint8_t chaddrLen;
    uint8_t chaddr[16];
}wds_DHCPv4HWConfig;

/**
 * \ingroup wds
 * 
 * WDS SWI DHCPv4 Option Structure
 *
 *  @param  optCode
 *          - Option code
 *              - 0 - 255
 *
 *  @param  optValLen
 *          - Option value length
 *              - 0 - 255
 *
 *  @param  optVal
 *          - Option value
 *
 *  This is deprecated
 *
 */
typedef struct
{
    uint8_t optCode;
    uint8_t optValLen;
    uint8_t optVal[255];
}wds_DHCPv4Option;

/**
 * \ingroup wds
 * 
 * WDS SWI DHCPv4 Option List Structure
 *
 *  @param  numOpt
 *          - number of options
 *              - 0 - 255
 *
 *  @param  pOptList
 *          - pointer to list of DHCP Options
 *
 *  This is deprecated
 *
 */
typedef struct
{
    uint8_t          numOpt;
    wds_DHCPv4Option *pOptList;
}wds_DHCPv4OptionList;

/**
 * \ingroup wds
 * 
 * WDS SWI DHCPv4 Config Structure
 *
 *  @param  pProfileId
 *          - pointer to Profile Id structure
 *
 *  @param  pHWConfig
 *          - pointer to HW Config structure
 *
 *  @param  pRequestOptionList
 *          - pointer to Option List structure to be sent in
 *            DHCP request
 *
 *  This is deprecated
 *
 */
typedef struct
{
    wds_DHCPv4ProfileId   *pProfileId;
    wds_DHCPv4HWConfig    *pHwConfig;
    wds_DHCPv4OptionList  *pRequestOptionList;
}pack_wds_SLQSSSetDHCPv4ClientConfig_t;

typedef unpack_result_t unpack_wds_SLQSSSetDHCPv4ClientConfig_t;


/**
 * \ingroup wds
 * 
 * get current data bearer technology pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */
int pack_wds_GetDataBearerTechnology(
        pack_qmi_t  *pCtx,
        uint8_t     *pReqBuf,
        uint16_t    *pLen
        );

/**
 * \ingroup wds
 * 
 *  This structure contains unpack get data bearer technology information.
 *
 *  @param  pDataBearer[OUT]
 *          - Data bearer technology\n
 *              - 0x01 - CDMA2000 1x
 *              - 0x02 - CDMA 1xEV-DO Rev 0
 *              - 0x03 - GSM
 *              - 0x04 - UMTS
 *              - 0x05 - CDMA2000 HRPD (1xEV-DO Rev A)
 *              - 0x06 - EDGE
 *              - 0x07 - HSDPA AND WCDMA
 *              - 0x08 - WCDMA AND HSUPA
 *              - 0x09 - HSDPA AND HSUPA
 *              - 0x0A - LTE
 *              - 0x0B - CDMA2000 EHRPD
 *              - 0x0C - HSDPA+ and WCDMA
 *              - 0x0D - HSDPA+ and HSUPA
 *              - 0x0E - DC_HSDPA+ and WCDMA
 *              - 0x0F - DC_HSDPA+ and HSUPA
 *              - 0x10 - HSDPA+ and 64QAM
 *              - 0x11 - HSDPA+, 64QAM and HSUPA
 *              - 0x12 - TDSCDMA
 *              - 0x13 - TDSCDMA and HSDPA
 *              - 0xFF - Unknown
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 * @param  Tlvresult - unpack Tlv Result.
 * 
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct{
    uint32_t    *pDataBearer;
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
} unpack_wds_GetDataBearerTechnology_t;

/**
 * \ingroup wds
 * 
 * get current data bearer technology unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_GetDataBearerTechnology(
        uint8_t   *pResp,
        uint16_t  respLen,
        unpack_wds_GetDataBearerTechnology_t *pOutput
        );

/**
 * \ingroup wds
 * 
 * get current data bearer technology ext pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */
int pack_wds_GetDataBearerTechnologyExt(
	pack_qmi_t  *pCtx,
	uint8_t     *pReqBuf,
	uint16_t    *pLen
);

/**
 * \ingroup wds
 * 
 * Network information structure
 *
 *  \param  TechType
 *          - Technology type
 *          - Values:
 *              - 0 - WDS_BEARER_TECH_NETWORK_3GPP - 3GPP
 *              - 1 - WDS_BEARER_TECH_NETWORK_3GPP2 - 3GPP2
 *
 *  \param  ratValue
 *          - Radio Access Technology (RAT) value
 *          - Values:
 *              - 0x00 - WDS_BEARER_TECH_RAT_EX_NULL_BEARER - NULL bearer
 *              - 0x01 - WDS_BEARER_TECH_RAT_EX_3GPP_WCDMA - 3GPP WCDMA
 *              - 0x02 - WDS_BEARER_TECH_RAT_EX_3GPP_GERAN - 3GPP GERAN
 *              - 0x03 - WDS_BEARER_TECH_RAT_EX_3GPP_LTE - 3GPP LTE
 *              - 0x04 - WDS_BEARER_TECH_RAT_EX_3GPP_TDSCDMA - 3GPP TDSCDMA
 *              - 0x05 - WDS_BEARER_TECH_RAT_EX_3GPP_WLAN - 3GPP WLAN
 *              - 0x64 - WDS_BEARER_TECH_RAT_EX_3GPP_MAX - 3GPP maximum
 *              - 0x65 - WDS_BEARER_TECH_RAT_EX_3GPP2_1X - 3GPP2 1X
 *              - 0x66 - WDS_BEARER_TECH_RAT_EX_3GPP2_HRPD - 3GPP2 HRPD
 *              - 0x67 - WDS_BEARER_TECH_RAT_EX_3GPP2_EHRPD - 3GPP2 EHRPD
 *              - 0x68 - WDS_BEARER_TECH_RAT_EX_3GPP2_WLAN - 3GPP2 WLAN
 *              - 0xC8 - WDS_BEARER_TECH_RAT_EX_3GPP2_MAX - 3GPP2 maximum
 *
 *  \param  SOMask
 *          - Service Option (SO) mask to indicate the
 *            service option or type of application.
 *            An SO mask value of zero indicates that
 *            this field is ignored.
 *          - Values:
 *              - 0x00 - SO mask unspecified
 *          - 3GPP SO mask:
 *              - 0x01 - WCDMA
 *              - 0x02 - HSDPA
 *              - 0x04 - HSUPA
 *              - 0x08 - HSDPAPLUS
 *              - 0x10 - DC HSDPAPLUS
 *              - 0x20 - 64 QAM
 *              - 0x40 - HSPA
 *              - 0x80 - GPRS
 *              - 0x100 - EDGE
 *              - 0x200 - GSM
 *              - 0x400 - S2B
 *              - 0x800 - LTE limited service
 *              - 0x1000 - LTE FDD
 *              - 0x2000 - LTE TDD
 *
 *          - 3GPP2 SO mask:
 *              - 0x01000000 - 1X IS95
 *              - 0x02000000 - 1X IS2000
 *              - 0x04000000 - 1X IS2000 REL A
 *              - 0x08000000 - HDR REV0 DPA
 *              - 0x10000000 - HDR REVA DPA
 *              - 0x20000000 - HDR REVB DPA
 *              - 0x40000000 - HDR REVA MPA
 *              - 0x80000000 - HDR REVB MPA
 *              - 0x100000000 - HDR REVA EMPA
 *              - 0x200000000 - HDR REVB EMPA
 *              - 0x400000000 - HDR REVB MMPA
 *              - 0x800000000 - HDR EVDO FMC
 */
typedef struct
{
	uint32_t techType;
	uint32_t ratValue;
	uint64_t soMask;
}wds_DataBearerTech;

/**
 * \ingroup wds
 * 
 *  This structure contains unpack get data bearer technology ext information.
 *
 *  @param  pDataBearerTechExt[OUT]
 *          - See \ref wds_DataBearerTech for more information
 *
 * @param  Tlvresult - unpack Tlv Result.
 * 
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct {
	wds_DataBearerTech *pBearerTech;
	wds_DataBearerTech *pLastBearerTech;
    uint16_t Tlvresult;
	swi_uint256_t  ParamPresenceMask;
} unpack_wds_GetDataBearerTechnologyExt_t;

/**
 * \ingroup wds
 * 
 * get current data bearer technology ext unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_GetDataBearerTechnologyExt(
	uint8_t   *pResp,
	uint16_t  respLen,
	unpack_wds_GetDataBearerTechnologyExt_t *pOutput
);


/**
 * \ingroup wds
 * 
 * WDS SWI Set Mux ID Structure
 *
 *  @param  pEpType
 *          - pointer to end point type
 *
 *  @param  pIfId
 *          - pointer to interface ID
 *
 *  @param  pMuxID
 *          - pointer to mux ID
 *             - 0x80 to 0x88
 *
 *  @param  pReversed
 *          - pointer to reversed RmNet flag
 *
 *  @param  pClientType
 *          - pointer to client type
 *
 */
typedef struct
{
	uint32_t *pEpType;
	uint32_t *pIfId;
	uint8_t  *pMuxID;
	uint8_t  *pReversed;
	uint32_t *pClientType;
}pack_wds_SetMuxID_t;

/**
 * \ingroup wds
 * 
 * Set MUX ID pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int pack_wds_SetMuxID(        
      pack_qmi_t  *pCtx,
        uint8_t     *pReqBuf,
        uint16_t    *pLen,
	pack_wds_SetMuxID_t     *reqArg);

typedef unpack_result_t unpack_wds_SetMuxID_t;

/**
 * \ingroup wds
 * 
 * Set MUX ID unpack.
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_SetMuxID(
        uint8_t   *pResp,
        uint16_t  respLen,
        unpack_wds_SetMuxID_t *pOutput
        );

/**
 * \ingroup wds
 * 
 *  This structure stores information about modem connection status TLV. 
 *  @param MDMConnStatus
 *          -Modem connecton status
 *              - 0x01 - disconnected
 *              - 0x02 - connected
 */
typedef struct
{
    uint8_t MDMConnStatus;
} wds_ConnStatusTlv;

/**
 * \ingroup wds
 * 
 *  This structure stores information about modem last call end reason TLV. 
 *  @param CallEndReason
 *          -Modem call end reason
 *             - See qaGobiApiTableCallEndReasons.h for Call End Reason
 */
typedef struct
{
    uint16_t CallEndReason;
} wds_LastMdmCallEndRsnTlv;

/**
 * \ingroup wds
 * 
 *  This structure stores information about Tx Bytes OK TLV. 
 *  @param TxByteOKCnt
 *          - Number of bytes transmitted without error
 */
typedef struct
{
    uint64_t TxByteOKCnt;
} wds_TXBytesOKTlv;

/**
 * \ingroup wds
 * 
 *  This structure stores information about Rx Bytes OK TLV. 
 *  @param RxByteOKCnt
 *          -Number of bytes received without error
 */
typedef struct
{
    uint64_t RxByteOKCnt;
} wds_RXBytesOKTlv;


/**
 * \ingroup wds
 * 
 *  This structure stores information about dormancy status TLV. 
 *  @param DormancyStat
 *          -Dormancy status
 *              - 0x01 - Traffic channel dormant
 *              - 0x02 - Traffic channel active
 */
typedef struct
{
    uint8_t DormancyStat;
} wds_DormStatTlv;

/**
 * \ingroup wds
 * 
 *  This structure hold parameters about data bearer technology TLV. 
 *  @param DataBearerTech
 *          - Data bear technology
 *              - 0x01 - cdma2000 1X
 *              - 0x02 - cdma2000 HRPD (1xEV-DO)
 *              - 0x03 - GSM
 *              - 0x04 - UMTS
 *              - 0x05 - cdma200 HRPD ( 1xEV-DO RevA)
 *              - 0x06 - EDGE
 *              - 0x07 - HSDPA and WCDMA
 *              - 0x08 - WCDMA and HSUPA
 *              - 0x09 - HSDPA and HSUPA
 *              - 0x0A - LTE
 *              - 0x0B - cdma2000 EHRPD
 *              - 0x0C - HSDPA+ and WCDMA
 *              - 0x0D - HSDPA+ and HSUPA
 *              - 0x0E - DC_HSDPA+ and WCDMA
 *              - 0x0F - DC_HSDPA+ and HSUPA
 *              - 0x10 - HSDPA+ and 64QAM
 *              - 0x11 - HSDPA+, 64QAM and HSUPA
 *              - 0x12 - TDSCDMA
 *              - 0x13 - TDSCDMA and HSDPA
 *              - 0xFF - Unknown
 */
typedef struct
{
    uint8_t DataBearerTech;
} wds_DataBearTechTlv;

/**
 * \ingroup wds
 * 
 *  This structure contains Channel Rate
 *
 *  @param  CurrChanTxRate
 *          - Max channel Tx rate in bits per second
 *
 *  @param  CurrChanRxRate
 *          - Max channel Rx rate in bits per second
 *
 */
typedef struct
{
    uint32_t CurrChanTxRate;
    uint32_t CurrChanRxRate;
} wds_channelRate;

/**
 * \ingroup wds
 * 
 *  This structure stores information about channel rate TLV. 
 *  @param ChannelRate
 *          - see @ref wds_channelRate for more info 
 */
typedef struct
{
    wds_channelRate ChannelRate;
} wds_ChannelRateTlv;

/**
 * \ingroup wds
 * 
 *  Structure used to store Reg Mgr Config Indication Parameters. 
 *  @param  CSTlv
 *          - Connection status tlv
 *          - See @ref wds_ConnStatusTlv for more information
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *  @param  LMCERTlv
 *          - last modem call end reason tlv
 *          - see @ref wds_LastMdmCallEndRsnTlv for more information
 *          - Bit to check in ParamPresenceMask - <B>17</B>
 *  @param TXBOTlv
 *          - Tx bytes OK tlv
 *          - see @ref wds_TXBytesOKTlv for more information
 *          - Bit to check in ParamPresenceMask - <B>18</B>
 *  @param RXBOTlv
 *          - Rx bytes OK tlv
 *          - see @ref wds_RXBytesOKTlv for more information
 *          - Bit to check in ParamPresenceMask - <B>19</B>
 *  @param DSTlv
 *          - Dormancy status tlv
 *          - see @ref wds_DormStatTlv for more information
 *          - Bit to check in ParamPresenceMask - <B>20</B>
 *  @param DBTTlv
 *          - Data bear technology  tlv
 *          - see @ref wds_DataBearTechTlv for more information
 *          - Bit to check in ParamPresenceMask - <B>21</B>
 *  @param CRTlv
 *          - Channel rate Tlv
 *          - see @ref wds_ChannelRateTlv for more information
 *          - Bit to check in ParamPresenceMask - <B>22</B>
 *
 * @param  Tlvresult - unpack Tlv Result.
 * 
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 * @note:    None
 */
typedef struct{
    wds_ConnStatusTlv        CSTlv;
    wds_LastMdmCallEndRsnTlv LMCERTlv;
    wds_TXBytesOKTlv         TXBOTlv;
    wds_RXBytesOKTlv         RXBOTlv;
    wds_DormStatTlv          DSTlv;
    wds_DataBearTechTlv      DBTTlv;
    wds_ChannelRateTlv       CRTlv;
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
} unpack_wds_SLQSDUNCallInfoCallBack_ind_t;

/**
 * \ingroup wds
 * 
 * unpack DUN call info indication
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_SLQSDUNCallInfoCallBack_ind(
        uint8_t   *pResp,
        uint16_t  respLen,
        unpack_wds_SLQSDUNCallInfoCallBack_ind_t *pOutput
        );

/**
 * \ingroup wds
 * 
 *  This structure stores information about Data Bearer Type TLV.
 *  @param  BearerId
 *          - Bearer ID for which the associated bearer type infomation is reported
 *
 *  @param  UlDirection
 *          - Bearer type information for uplink transmission
 *
 *  @param  DlDirection
 *          - Bearer type information for downlink transmission
 *
 */
typedef struct
{
	uint8_t BearerId;
	uint32_t UlDirection;
	uint32_t DlDirection;
} wds_DataBearerTypeTlv;

/**
 * \ingroup wds
 * 
 *  Structure used to store Data Bearer Type Indication Parameters.
 *
 *  @param  BearerId
 *          - Bearer ID for which the associated bearer type infomation is reported
 *
 *  @param  UlDirection
 *          - Bearer type information for uplink transmission
 *
 *  @param  DlDirection
 *          - Bearer type information for downlink transmission
 *
 * @param  Tlvresult - unpack Tlv Result.
 * 
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct
{
	wds_DataBearerTypeTlv DBTTlv;
    uint16_t Tlvresult;
	swi_uint256_t  ParamPresenceMask;
} unpack_wds_SLQSDataBearerType_ind_t;

/**
 * \ingroup wds
 * 
 * unpack Data Bearer Type indication
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int unpack_wds_SLQSDataBearerType_ind(
	uint8_t *pResp,
	uint16_t respLen,
	unpack_wds_SLQSDataBearerType_ind_t *pOutput
);

/**
 * \ingroup wds
 * 
 * This structure contains pack Start Data Session Information.
 *
 * @param peMbmsTmgiList (optional)
 *          - eMBMS TMGI List
 *           - Values: 
 *              - 0 - Do not report 
 *              - 1 - Report eMBMS TMGI list
 * 
 * @param pSupperesPktSrvcInd (optional)
 *          - Indicates whether to suppress the packet service status indication 
 *           - Values:
 *              - 0 - Do not suppress 
 *              - 1 - Suppress
 *
 * @param pExtIPConfigurationChange
 *          - Extended IP Configuration Change
 *           - Values:
 *              - 0 - Do not report
 *              - 1 - Report extended IP configuration information change
 * 
 * @param pReportLteAttachPdnListChange (optional)
 *          - LTE attach PDN list Values
 *          - Indicates whether to report a changed
 *           - Values:
 *              - 0 - Do not report
 *              - 1 - Report changed LTE attach PDN list
 *
 * @param pReportHandoffInformation (optional)
 *          - Report Handoff Information
 *           - Indicates whether to report handoff information
 *            - Values:
 *              - 0 - Do not report
 *              - 1 - Report handoff information TLV 0x16 is reserved.
 * @param pReporteMbmsSAIListChanges (optional)
 *          - Report eMBMS SAI List Changes
 *          - Indicates whether to report an eMBMS SAI list change
 *           - Values:
 *              - 0 - Do not report
 *              - 1 - Report eMBMS SAI list change
 * 
 * @param pReportUplinkThroughputInfo (optional)
 *          - Report Uplink Throughput Information
 *            - Values:
 *              - 0 - Do not report
 *              - 1 - Report uplink throughput information
 * 
 * @param pReportProfileChangeEvents (optional)
 *          - Report Profile Changes: 
 *           - Values:
 *              - 0 - Do not report
 *              - 1 - Report profile changed events
 *
 * @param pReportRoamingApnList (optional)
 *          - Report APN List in Roaming
 *           -Values:
 *              - 0 - Do not report 
 *              - 1 - Report the list of APNs in Roaming
 *
 * @param pReportDlThroughputInfo (optional)
 *          - Report Downlink Throughput Information
 *           - Values:
 *              - 0 - Do not report
 *              - 1 - Report downlink throughput information
 * 
 * @param pReporteMbmsContentDescCtl (optional)
 *          - Report eMBMS Content Description Control
 *           - Values:
 *              - 0 - Do not report
 *              - 1 - Report eMBMS content description control
 * 
 * @param pReportPolicyReady (optional)
 *          - Report Policy Ready
 *           - Values:
 *              - 0 - Do not report
 *              - 1 - Report policy ready
 * 
 * @param pReportApnParamChangeInfo (optional)
 *          - Report APN parameter change information
 *           - Values:
 *               - 0 - Do not report
 *               - 1 - Report APN parameter change
 *
 * @param pReportConfiguredThroughput (option)
 *          - Report Configured Throughput
 *           - Values:
 *              - 0 - Do not report
 *              - 1 - Report configured throughput information
 * 
 * @param pReporteMbmsServiceInterest (optionl)
 *          - Report eMBMS Service Interest
 *           - Values:
 *              - 0 - Do not report
 *              - 1 - Report eMBMS service interest
 * 
 * @param pReportDlThroughputInterval
 *          - Report Downlink Throughput Interval
 *          - Report changes in downlink throughput interval
 *           - Values:
 *              - 0 - Do not report
 *              - 1 - Report downlink throughput interval change
 * 
 * @param pReportLteAttachParams (optional)
 *          - Report LTE attach parameters
 *           Values:
 *              - 0 - Do not report
 *              - 1 - Report LTE attach parameters
 *
 * @param pReportOpResevedPcoListChange (optional)
 *          - Report changes in the PCO list for the following APN
 *           - Values:
 *              - 0 - Do not report
 *              - 1 - Report PCO list change
 *
 * @param pApnNameLen (optional)
 *          - Number of characters in the apn_name
 *
 * @param pApnName (optional)
 *          - APN for which the client is interested in receiving changes in operator PCO change information
 *
 * @param pReportMsisdnInfoChange (optional)
 *          - Report changes in MSISDN for the following APN
 *           - Values:
 *              - 0 - Do not report
 *              - 1 - Report MSISDN info change
 *
 * @param pApnNameLenMsisdn (optional)
 *          - Number of characters in pApnNameMsisdn
 *
 * @param pApnNameMsisdn (optional)
 *          - Access point node name for MSIDN
 *          - APN for which the client is interested in receiving changes in MSISDN information.
 *
 * @param pReport3GppRabRejectInfo (optional)
 *          - Report 3GPP RAB Reject Information
 *          - Report RAB reject information.
 *          
 * @param pReportPdnThrottleInfo (optional)
 *          - Report Throttled PDN Information
 *          - Values:
 *              - 0 - Do not report
 *              - 1 - Report throttled PDN information
 *
 * @param pReportModemAssistKAliveStatus (optional)
 *          - Report Modem Assisted Keep Alive Status
 *
 * @param pReportV2XSpsFlowRegResult (optional)
 *          - Report V2X SPS Flow Registration Result
 *           - Values:
 *              - 0 - Do not report
 *              - 1 - Report V2X SPS flow registration result
 * 
 * @param pReportV2XSpsFlowUpdateResult (optional)
 *          - Report V2X SPS flow update result
 *           - Values:
 *              - 0 - Do not report
 *              - 1 - Report V2X SPS flow update result
 * 
 * @param pReportV2XSPSFlowDeregistResult (optional)
 *          - Report V2X SPS flow deregistration result
 *           - Values:
 *              - 0 - Do not report
 *              - 1 - Report V2X SPS flow deregistration result
 * 
 * @param pReportV2XServiceSubscriptResult (optional)
 *          - Report V2X service subsription result
 *           - Values:
 *              - 0 - Do not report
 *              - 1 - Report V2X service subscription result
 * 
 * @param pReportRANAssistMediaAdaptInfo (optional)
 *          - Report RAN-assisted media adaptation information
 *           - Values:
 *              - 0 - Do not report
 *              - 1 - Report RAN-assisted media adaptation information
 * 
 * @param pReportV2XSpsSchedulingInfo (optional)
 *          - Report V2X SPS scheduling information
 *           - Values:
 *              - 0 - Do not report
 *              - 1 - Report V2X SPS scheduling information
 * 
 * @param pReportV2XSourceL2Info (optional)
 *          - Report V2X source L2 information
 *           - Values:
 *              - 0 - Do not report
 *              - 1 - Report V2X source L2 information
 *
 * @param pReportBearerType (optional)
 *          - Report bearer type information
 *           - Values: 
 *              - 0 - Do not report
 *              - 1 - Report bearer type information
 *
 * @param pReportV2XCapabilityInfo (optional)
 *          - Report V2X capability information
 *           - Values:
 *              - 0 - Do not report
 *              - 1 - Report V2X capability information
 * 
 * @param pReportLadnInfo (optional)
 *          - Report LADN information
 *           - Values:
 *              - 0 - Do not report
 *              - 1 - Report LADN information
 * 
 * @param pReportDefaultFlowRebind (optional)
 *          - Report default flow rebind information
 *           - Values:
 *              - 0 - Do not report
 *              - 1 - Report default flow rebind information
 * 
 * @param pReportLteAttachFailInfo (optional)
 *          - Report LTE Attach Failure Information
 *           - Values:
 *              - 0 - Do not report LTE attach failure information
 *              - 1 - Report LTE attach failure information
 * 
 * @param pReportDataPrioritInfo (optional)
 *          - Report Data Prioritization Information
 *           - Values:
 *              - 0 - Do not report
 *              - 1 - Report data prioritization information
 * 
 * @param pReportV2XConfigChange (optional)
 *          - Report V2X Configuration Change
 *           - Values:
 *              - 0 - Do not report
 *              - 1 - Report V2X configuration change
 * 
 * @param pReportV2XConfigFileContent (optional)
 *          - Report V2X Configuration File Content
 *           - Values:
 *              - 0 - Do not report
 *              - 1 - Report V2X configuration file content
 *
 * @For_5G
 */
typedef struct
{
    uint8_t  *peMbmsTmgiList;
	uint8_t  *pSupperesPktSrvcInd;
    uint8_t  *pExtIPConfigurationChange;
	uint8_t  *pReportLteAttachPdnListChange;
    uint8_t  *pReportHandoffInformation;
    uint8_t  *pReporteMbmsSAIListChanges;
    uint8_t  *pReportUplinkThroughputInfo;
	uint8_t  *pReportProfileChangeEvents;
	uint8_t  *pReportRoamingApnList;
    uint8_t  *pReportDlThroughputInfo;
    uint8_t  *pReporteMbmsContentDescCtl;
    uint8_t  *pReportPolicyReady;
	uint8_t  *pReportApnParamChangeInfo;
    uint8_t  *pReportConfiguredThroughput;
    uint8_t  *pReporteMbmsServiceInterest;
    uint8_t  *pReportDlThroughputInterval;
	uint8_t  *pReportLteAttachParams;
	uint8_t  *pReportOpResevedPcoListChange;
	uint8_t  *pApnNameLen;
	char     *pApnName;
	uint8_t  *pReportMsisdnInfoChange;
    uint8_t  *pApnNameMsisdnLen;
	char     *pApnNameMsisdn;
    uint8_t  *pReport3GppRabRejectInfo;
    uint8_t  *pReportPdnThrottleInfo;
    uint8_t  *pReportModemAssistKAliveStatus;
    uint8_t  *pReportV2XSpsFlowRegResult;
    uint8_t  *pReportV2XSpsFlowUpdateResult;
    uint8_t  *pReportV2XSPSFlowDeregistResult;
    uint8_t  *pReportV2XServiceSubscriptResult;
    uint8_t  *pReportRANAssistMediaAdaptInfo;
    uint8_t  *pReportV2XSpsSchedulingInfo;
    uint8_t  *pReportV2XSourceL2Info;
	uint8_t  *pReportBearerType;
    uint8_t  *pReportV2XCapabilityInfo;
    uint8_t  *pReportLadnInfo;
    uint8_t  *pReportDefaultFlowRebind;
    uint8_t  *pReportLteAttachFailInfo;
    uint8_t  *pReportDataPrioritInfo;
    uint8_t  *pReportV2XConfigChange;
    uint8_t  *pReportV2XConfigFileContent;

} pack_wds_indication_register_t;

/**
 * \ingroup wds
 * 
 * Indication Register pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  pIndicationRegister indications to register for.
 *             - 0x80 to 0x88
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * @For_5G
 */
int pack_wds_IndicationRegister(
	pack_qmi_t  *pCtx,
	uint8_t   *pReqBuf,
	uint16_t  *pLen,
	pack_wds_indication_register_t *pIndicationRegister);

typedef unpack_result_t unpack_wds_IndicationRegister_t;

/**
 * \ingroup wds
 * 
 * Indicatio nRegister Unpack.
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * @For_5G
 */
int unpack_wds_IndicationRegister(
	uint8_t   *pResp,
	uint16_t  respLen,
	unpack_wds_IndicationRegister_t *pOutput
);


/**
 * \ingroup wds
 * 
 * Keep Alive Data Session Flag pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  pKeepAliveDataSessionFlag Keep Alive Data Session Flag.
 *             - 0x80 to 0x88
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_wds_KeepAliveDataSession(
	pack_qmi_t  *pCtx,
	uint8_t   *pReqBuf,
	uint16_t  *pLen,
    uint8_t   *pKeepAliveDataSessionFlag);

typedef unpack_result_t unpack_wds_Keep_Alive_Data_Session_t;

/**
 * \ingroup wds
 * 
 * SetKeep Alive Data Session.
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_KeepAliveDataSession(
	uint8_t   *pResp,
	uint16_t  respLen,
	unpack_wds_Keep_Alive_Data_Session_t *pOutput
);

/**
 * \ingroup wds
 * 
 *  This structure contains pack Reset_And_Modify_Profile_Settings.
 *
 *  @param  ProfileId
 *          - 1 to 16 for 3GPP profile (EM/MC73xx or earlier)
 *          - 1 to 24 for 3GPP profile (EM/MC74xx onwards)
 *          - 101 to 106 for 3GPP2 profile
 *
 *  @param  ProfileType
 *          - Identifies the technology type of the profile
 *            - 0x00 - 3GPP
 *            - 0x01 - 3GPP2
 *            - NULL is not allowed
 *
 *  @param  pProfile
 *          - union of 3GPP and 3GPP2 profile
 *          - See \ref wds_profileInfo
 *
 *  @note   - If profileID is NULL, 3GPP profile will be created
 *            and index will be assigned based on availability in device.
 *  @note   - If profileID is not NULL depending on pProfileType 3GPP/3GPP2
 *            relevant profile will be created
 *
 */
typedef struct
{
	uint8_t   ProfileId;
	uint8_t   ProfileType;
	wds_profileInfo  *pProfile;
} pack_wds_ResetAndModifyProfileSettings_t;

/**
 * \ingroup wds
 * 
 * Create Profile pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 * 
 */
int pack_wds_ResetAndModifyProfileSettings(
	pack_qmi_t  *pCtx,
	uint8_t *pReqBuf,
	uint16_t *pLen,
	pack_wds_ResetAndModifyProfileSettings_t *reqArg
);

/**
 * \ingroup wds
 * 
 *  This structure contains out parameter Information
 *
 *  @param  ProfileType
 *          - Identifies the type of profile
 *            0x00 = 3GPP
 *            0x01 = 3GPP2
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param  ProfileIndex
 *          - Index identifying the profile that was created
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param  ExtErrorCode
 *          - The extended error code received from DS Profile
 *           subsystem
 *          - Bit to check in ParamPresenceMask - <B>224</B>
 * 
 */
typedef struct
{
	uint8_t   ProfileType;
	uint8_t   ProfileIndex;
	uint16_t  ExtErrorCode;
}PackResetAndModifyProfileSettingsOut;

/**
 * \ingroup wds
 * 
 *  This structure contains unpack create profile information.
 *
 *  @param  extended_error_code
 *          - Error code from the DS profile
 *
 *  @param  Tlvresult
 *          - TLV present flag, TURE if presented, otherwise FALSE
 *
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */

typedef struct
{
    uint16_t   extended_error_code;
	uint16_t   Tlvresult;
    swi_uint256_t  ParamPresenceMask;
} unpack_wds_ResetAndModifyProfileSettings_t;

/**
 * \ingroup wds
 * 
 * Reset_And_Modify_Profile_Settings unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response structure to fill
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * 
 */

int unpack_wds_ResetAndModifyProfileSettings(
	uint8_t *pResp,
	uint16_t respLen,
	unpack_wds_ResetAndModifyProfileSettings_t *pOutput
);

/**
 * \ingroup wds
 * 
 * GetApnOpReservedPcoList pack
 * @param[in]   pApnName
 *              - APN Name
 */
typedef struct
{
	char *pApnName;
}pack_wds_GetApnOpReservedPcoList_t;

/**
 * \ingroup wds
 * 
 * get runtime settings pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] pReqParam request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */
int pack_wds_GetApnOpReservedPcoList(
	pack_qmi_t  *pCtx,
	uint8_t     *pReqBuf,
	uint16_t    *pLen,
	pack_wds_GetApnOpReservedPcoList_t   *pReqParam
);

/**
 * \ingroup wds
 * 
 * This structure contains the WdsApnOpReservedPco_t Information
 *  - Parameter values default to their data type's maximum unsigned value
 *    unless explicitly stated otherwise.
 *
 *  @param  PcoId
 *          - PCO ID of this PCO. Range: 0xFF00 to 0xFFFF.
 *  @param  Mcc
 *          - A 16-bit integer representation of MCC. Range: 0 to 999.
 *  @param  Mnc
 *          - A 16-bit integer representation of MNC. Range: 0 to 999.
 *  @param  MncIncludesPcsDigit
 *          - Interprets the length of the corresponding
 *          MNC reported in the TLV. Values:\n
 *          TRUE - MNC is a three-digit value; for
 *          example, a reported value of 90\n
 *          corresponds to an MNC value of 090
 *          FALSE - MNC is a two-digit value; for
 *          example, a reported value of 90\n
 *          corresponds to an MNC value of 90.
 *  @param  AppSpecificInfoLength
 *          - Number of sets of the following elements: app_specific_info
 *  @param  pAppSpecificInfo
 *          - Points to the application-specific information from the network. The
 *          format for this field complies with 3GPP TS 24.008. The field is populated in this\n
 *          format for both 3GPP and 3GPP2.
 *  @param  ContainerId
 *          - Container ID of this PCO.
 *
 */
typedef struct
{
	uint16_t    PcoId;
	uint16_t    Mcc;
	uint16_t    Mnc;
	uint8_t     MncIncludesPcsDigit;
	uint8_t     AppSpecificInfoLength;
	uint8_t     AppSpecificInfo[MAX_APP_SPECIFIC_INFO];
	uint16_t    ContainerId;
} WdsApnOpReservedPco_t;

/**
 * \ingroup wds
 * 
 * This structure contains the WdsApnOpReservedPcoList Information
 *  - Parameter values default to their data type's maximum unsigned value
 *    unless explicitly stated otherwise.
 *
 *  \param  numInstances
 *          - Number of Wds_Apn_Operatore_Reserved_PCO.
 *          - Bit to check in ParamPresenceMask - <B>0x10</B>
 * 
 *  \param  pWdsApnOpReservedPcoList
 *          - Wds Apn Operatore Reserved PCO list.
 *          - Bit to check in ParamPresenceMask - <B>0x10</B>
 *
 *  @param  Tlvresult
 *          - TLV present flag, TURE if presented, otherwise FALSE
 *
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
*/
typedef struct
{
	uint8_t  numInstances;
	WdsApnOpReservedPco_t *pWdsApnOpReservedPcoList;
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_wds_ApnOpReservedPcoList_t;

/**
 * \ingroup wds
 * 
 * Reset_And_Modify_Profile_Settings unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response structure to fill
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * 
 */
int unpack_wds_ApnOpReservedPcoList(
	uint8_t *pResp,
	uint16_t respLen,
	unpack_wds_ApnOpReservedPcoList_t*  pOutput
);

/**
 * \ingroup wds
 * 
 * GetApnMsisdnInfo pack
 * @param[in]   pApnName
 *              - APN Name
 */
typedef struct
{
	char *pApnName;
}pack_wds_GetApnMsisdnInfo_t;

/**
 * \ingroup wds
 * 
 * get runtime settings pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */
int pack_wds_GetApnMsisdnInfo(
        pack_qmi_t  *pCtx,
        uint8_t     *pReqBuf,
        uint16_t    *pLen,
        pack_wds_GetApnMsisdnInfo_t    *reqArg
        );

/**
 * \ingroup wds
 * 
 * This structure contains the WdsApnMsisdnInfo Information
 *  - Parameter values default to their data type's maximum unsigned value
 *    unless explicitly stated otherwise.
 *
 *  \param  num_msisdn
 *          - Number of MSISDN.
 *          - Bit to check in ParamPresenceMask - <B>0x10</B>
 *  \param  pMsisdn
 *          - Wds Apn MSISDN Info.
 *          - Bit to check in ParamPresenceMask - <B>0x10</B>
 *  @param  Tlvresult
 *          - TLV present flag, TURE if presented, otherwise FALSE
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct
{
    uint8_t     num_msisdn;
    uint8_t     *pMsisdn;
    uint16_t    Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_wds_ApnMsisdnInfo_t;

/**
 * \ingroup wds
 * 
 * Reset_And_Modify_Profile_Settings unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response structure to fill
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * 
 */
int unpack_wds_ApnMsisdnInfo(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_wds_ApnMsisdnInfo_t*  pOutput        
        );


/**
 * \ingroup wds
 * 
 * Delete All Profiles pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  ProfileTypeMask Profile Type Mask. 
 *                             - Identifies the technology type of the profile. 
 *                               - Values:
 *                                  - QMI_WDS_MASK_PROFILE_TYPE_3GPP (0x01) - 3GPP
 *                                  - QMI_WDS_MASK_PROFILE_TYPE_3GPP2 (0x02) - 3GPP2
 * @param[in] pProfilePersistenceMask [optional] Profile Persistence Mask.
 *                             - Identifies the persistence property of the profiles to delete.
 *                               - Values:
 *                                  - QMI_WDS_PROFILE_NON_PERSISTENT(0x01) - Nonpersistent
 *                                  - QMI_WDS_PROFILE_PERSISTENT(0x02) - Persistent
 * @param[in] pProfileClientTypeMask [optional] Profile Client Type Mask
 *                             - Identifies the client that created the profiles that must be deleted using this message.
 *                               - Values:
 *                                  - WDS_PROFILE_CLIENT_TE (0x01) - Profiles created using QMI from the TE
 *                                  - WDS_PROFILE_CLIENT_ANY (0x80) – Profiles created by any client (default value)
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * 
 */
int pack_wds_DeleteAllProfiles(        
        pack_qmi_t  *pCtx,
        uint8_t   *pReqBuf,
        uint16_t  *pLen,
        uint64_t  ProfileTypeMask,
        uint64_t  *pProfilePersistenceMask,
        uint64_t  *pProfileClientTypeMask);


/**
 * \ingroup wds
 * 
 * This structure contains the Delete All Profiles Information
 *  - Parameter values default to their data type's maximum unsigned value
 *    unless explicitly stated otherwise.
 *
 * @param[in]  ProfileTypeMask Profile Type Mask. 
 *                             - Identifies the technology type of the profile. 
 *                               - Values:
 *                                  - QMI_WDS_MASK_PROFILE_TYPE_3GPP (0x01) - 3GPP
 *                                  - QMI_WDS_MASK_PROFILE_TYPE_3GPP2 (0x02) - 3GPP2
 * @param[in] pProfilePersistenceMask [optional] Profile Persistence Mask.
 *                             - Identifies the persistence property of the profiles to delete.
 *                               - Values:
 *                                  - QMI_WDS_PROFILE_NON_PERSISTENT(0x01) - Nonpersistent
 *                                  - QMI_WDS_PROFILE_PERSISTENT(0x02) - Persistent
 * @param[in] pProfileClientTypeMask [optional] Profile Client Type Mask
 *                             - Identifies the client that created the profiles that must be deleted using this message.
 *                               - Values:
 *                                  - WDS_PROFILE_CLIENT_TE (0x01) - Profiles created using QMI from the TE
 *                                  - WDS_PROFILE_CLIENT_ANY (0x80) - Profiles created by any client (default value)
 */
typedef struct
{
    uint64_t  ProfileTypeMask;
    uint64_t  *pProfilePersistenceMask;
    uint64_t  *pProfileClientTypeMask;
}pack_wds_DeleteAllProfiles_t;

/**
 * \ingroup wds
 * 
 * Delete All Profiles pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  pReqParam request parameter
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * 
 */
int pack_wds_DeleteAllProfilesEx(
        pack_qmi_t  *pCtx,
        uint8_t   *pReqBuf,
        uint16_t  *pLen,
        pack_wds_DeleteAllProfiles_t *pReqParam);

typedef unpack_result_t unpack_wds_delete_all_profiles_t;

/**
 * \ingroup wds
 * 
 * Delete All Profiles unpack.
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * 
 */
int unpack_wds_DeleteAllProfiles(
        uint8_t   *pResp,
        uint16_t  respLen,
        unpack_wds_delete_all_profiles_t *pOutput
        );

/**
 * \ingroup wds
 * 
 * This structure to hold Set Throttled PDN Reject Timer
 *
 *  @param  throttled_pdn_reject_timer Specifies the value to which the
 *										throttling time on the modem is set.
 *
 */
typedef struct {
	uint32_t throttled_pdn_reject_timer;
}pack_wds_SetThrottledPdnRejectTimer_t;

/**
 * \ingroup wds
 * 
 * set default profile number pack ThrottledPdnRejectTimer
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  pReqParam request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * 
 * @note This API is deprecated
 * 
 */
int pack_wds_SetThrottledPdnRejectTimer(
	pack_qmi_t  *pCtx,
	uint8_t     *pReqBuf,
	uint16_t    *pLen,
	pack_wds_SetThrottledPdnRejectTimer_t *pReqParam
);

typedef unpack_result_t unpack_wds_SetThrottledPdnRejectTimer_t;
/**
 * \ingroup wds
 * 
 * set default profile number unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * 
 * @note This API is deprecated
 * 
 */
int unpack_wds_SetThrottledPdnRejectTimer(
	uint8_t   *pResp,
	uint16_t  respLen,
	unpack_wds_SetThrottledPdnRejectTimer_t *pOutput
);

/**
 * \ingroup wds
 * 
 * This structure contains unpack Get Default Profile Number information.
 *
 * @param throttled_pdn_reject_timer
 *          - Specifies the value to which the
 *			  throttling time on the modem is set.
 *          - Bit to check in ParamPresenceMask - <B>0x10</B>
 *
 *  @param  Tlvresult
 *          - TLV present flag, TURE if presented, otherwise FALSE
 *
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct {
	uint32_t throttled_pdn_reject_timer;
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_wds_GetThrottledPdnRejectTimer_t;

/**
 * \ingroup wds
 * 
 * get default profile number pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * 
 * @note This API is deprecated
 * 
 */
int pack_wds_GetThrottledPdnRejectTimer(
	pack_qmi_t  *pCtx,
	uint8_t     *pReqBuf,
	uint16_t    *pLen
);

/**
 * \ingroup wds
 * 
 * get throttled PDN Reject Timer unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * 
 * @note This API is deprecated
 * 
*/
int unpack_wds_GetThrottledPdnRejectTimer(
	uint8_t   *pResp,
	uint16_t  respLen,
	unpack_wds_GetThrottledPdnRejectTimer_t *pOutput
);

/**
 * \ingroup wds
 * 
 * This structure contains the WdsApnOpReservedPco_t Information
 *  - Parameter values default to their data type's maximum unsigned value
 *    unless explicitly stated otherwise.
 *
 *  @param  apn_name_len
 *          - Number of sets of the apn_name.
 *  @param  apn_name
 *          - Name of the APN.
 *
 */
typedef struct
{
	uint8_t   apn_name_len;
	char      apn_name[MAX_APN_STRING];
}WdsEhrpdFallbackApn_t;

/**
 * \ingroup wds
 * 
 * This structure contains unpack Get Default Profile Number information.
 *
 * @param fallback_apn_name_list_len
 *          - Number of sets of WdsEhrpdFallbackApn instances
 *		  pWdsEhrpdFallbackApn
 *			- EHRPD fallback APN info
 *          - Bit to check in ParamPresenceMask - <B>0x10</B>
 *
 *  @param  Tlvresult
 *          - TLV present flag, TURE if presented, otherwise FALSE
 *
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct {
	uint8_t   fallback_apn_name_list_len;
    WdsEhrpdFallbackApn_t *pWdsEhrpdFallbackApn;
    uint16_t    Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_wds_GetEhrpdFallbackApnList_t;

/**
 * \ingroup wds
 * 
 * get default profile number pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_wds_GetEhrpdFallbackApnList(
	pack_qmi_t  *pCtx,
	uint8_t     *pReqBuf,
	uint16_t    *pLen
);

/**
 * \ingroup wds
 * 
 * get throttled PDN Reject Timer unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * 
 */
int unpack_wds_GetEhrpdFallbackApnList(
	uint8_t   *pResp,
	uint16_t  respLen,
	unpack_wds_GetEhrpdFallbackApnList_t    *pOutput
);

typedef unpack_wds_GetEhrpdFallbackApnList_t pack_wds_SetEhrpdFallbackApnList_t;

/**
 * \ingroup wds
 * 
 * set default profile pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  reqParam request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int pack_wds_SetEhrpdFallbackApnList(
	pack_qmi_t  *pCtx,
	uint8_t     *pReqBuf,
	uint16_t    *pLen,
	pack_wds_SetEhrpdFallbackApnList_t *reqParam
);

/**
 * \ingroup wds
 * 
 * set default profile unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * 
 */
int unpack_wds_SetEhrpdFallbackApnList(
	uint8_t   *pResp,
	uint16_t  respLen,
	unpack_wds_SetDefaultProfile_t *pOutput
);

/**
 * \ingroup wds
 * 
 * This structure contains pack Modem Assisted Keep-Alive Start Information.
 * 
 * @param  keep_alive_type
 *          - Keep Alive type. Value: WDS_KEEPALIVE_TYPE_NAT (0) – NAT
 * @param  pTimer_value
 *          - Timer value in milliseconds to indicate the frequency of the keep alive message
 * 			  that must be sent from the modem.
 *          - optional
 *          - Source Port.
 *          - optional
 * @param  apn_name_len
 *          - APN Name length.
 *          - optional
 * @param  pApn_Name
 *          - APN Name.
 *          - optional
 * 
 */
typedef struct 
{
	uint32_t	keep_alive_type;
	uint32_t	*pTimer_value;
	uint32_t	*pDest_ipv4_address;
	uint8_t		*pDest_ipv6_address; //[16]
	uint32_t	*pSource_ipv4_address;
	uint8_t		*pSource_ipv6_address; //[16]
	uint16_t	*pDest_port;
	uint16_t	*pSource_port;
	uint8_t		*apn_name_len;
	char		*pApn_Name;

} pack_wds_modem_assisted_ka_start_t;

/**
 * \ingroup wds
 * 
 * pack_wds_ModemAssistedKaStart
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] pReqParam 
 *             pack modem assisted keep-alive start information
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * 
 */
int pack_wds_ModemAssistedKaStart(        
        pack_qmi_t  *pCtx,
        uint8_t   *pReqBuf,
        uint16_t  *pLen,
        pack_wds_modem_assisted_ka_start_t *pReqParam);

/**
 * \ingroup wds
 * 
 *  @param keep_alive_handle
 *          - Keep alive handle
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 * 
 *  @param  Tlvresult
 *          - TLV present flag, TURE if presented, otherwise FALSE
 *
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct
{
    uint32_t keep_alive_handle;
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
} unpack_wds_modem_assisted_ka_start_t;

/**
 * \ingroup wds
 * 
 * unpack_wds_ModemAssistedKaStart
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * 
 */
int unpack_wds_ModemAssistedKaStart(
        uint8_t   *pResp,
        uint16_t  respLen,
        unpack_wds_modem_assisted_ka_start_t *pOutput
        );

/**
 * \ingroup wds
 * 
 * pack_wds_ModemAssistedKaStart
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  KeepAliveHandle 
 *             pack keep-alive handle
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * 
 */
int pack_wds_ModemAssistedKaStop(        
        pack_qmi_t  *pCtx,
        uint8_t     *pReqBuf,
        uint16_t    *pLen,
        uint32_t    KeepAliveHandle);

/**
 * \ingroup wds
 * 
 * This structure contains pack Modem Assisted Keep-Alive Stop Information.
 * 
 * @param  keep_alive_handle
 *          - pack keep-alive handle
 * 
 */
typedef struct 
{
	uint32_t	keep_alive_handle;
} pack_wds_modem_assisted_ka_stop_t;

/**
 * \ingroup wds
 * 
 * pack_wds_ModemAssistedKaStart
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  pReqParam parameter
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * 
 */
int pack_wds_ModemAssistedKaStopEx(        
        pack_qmi_t  *pCtx,
        uint8_t     *pReqBuf,
        uint16_t    *pLen,
        pack_wds_modem_assisted_ka_stop_t *pReqParam);

typedef unpack_result_t unpack_wds_modem_assisted_ka_stop_t;

/**
 * \ingroup wds
 * 
 * unpack_wds_ModemAssistedKaStop
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * 
 */
int unpack_wds_ModemAssistedKaStop(
        uint8_t   *pResp,
        uint16_t  respLen,
        unpack_wds_modem_assisted_ka_stop_t *pOutput
        );

typedef enum
{
    TYPE_IPV4 = 0x00,
    TYPE_IPV6 = 0x01,
    TYPE_IPV4V6 = 0x02,
}eQMI_WDS_IP_TYPE_t;

/**
 * \ingroup wds
 * 
 * Name:   IPv6AddressTlv
 *
 *  @param Ipv6_address   - IPv6 address (in network byte order).
 *                         The address is a 16-element array of
 *                         8-bit numbers, each of which is in big-endian format.
 *
 *  @param ipv6_prefix_length  - IPv6 prefix length in number of bits. Range: 0 to 128.
 *
 */
typedef struct
{
    uint8_t   Ipv6_address[16];
    uint8_t   Ipv6_prefix_length;
} IPv6AddressTlv_t;

/**
 * \ingroup wds
 * 
 * Name:    unpack_wds_SLQSLteAttachParams_ind_t
 *
 * Purpose: Structure used to store all Data Bearer Notification Parameters.
 *
 * @param  AttachParamValidTlv
 *          - Attach Parameters Valid
 *              1 - TRUE - Attach parameters are valid 
 *              0 - FALSE - Attach parameters not valid
 * @param  ApnStringLen
 *          - String length representing the APN. Maximum length is 100 bytes.       
 * 
 * @param  pApnString                
 *          - String representing the APN. Maximum length is 100 bytes.
 *          - Bit to check in ParamPresenceMask - <B>0x10</B>*  
 * @param  pIp_Type                  
 *          - IP Support Type
 *          - Bit to check in ParamPresenceMask - <B>0x11</B>*  
 * @param  pIPv4Address              
 *          - IPv4 address
 *          - Bit to check in ParamPresenceMask - <B>0x12</B>*  
 * @param  pIPv4GatewayAddress       
 *          - IPv4 Gateway Address
 *          - Bit to check in ParamPresenceMask - <B>0x13</B>*  
 * @param  pIPv4SubnetMask           
 *          - IPv4 Subnet Mask
 *          - Bit to check in ParamPresenceMask - <B>0x14</B>*  
 * @param  pIpv6Address              
 *          - Structure containing IPv6 address
 *          - Bit to check in ParamPresenceMask - <B>0x15</B>*  
 * @param  pIpv6Address              
 *          - Structure containing IPv6 gateway address
 *          - Bit to check in ParamPresenceMask - <B>0x16</B>*  
 * @param  Tlvresult - unpack Tlv Result.
 * @param  ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct
{
    uint8_t         AttachParamValidTlv;
    uint16_t        ApnStringLen;
    char            *pApnString;
    eQMI_WDS_IP_TYPE_t *pIp_Type;
    uint32_t        *pIPv4Address;
    uint32_t        *pIPv4GatewayAddress;
    uint32_t        *pIPv4SubnetMask;
    IPv6AddressTlv_t *pIpv6Address;
    IPv6AddressTlv_t *pIpv6GatewayAddress;
    uint16_t Tlvresult;
    swi_uint256_t     ParamPresenceMask;
}unpack_wds_SLQSLteAttachParams_ind_t;

/**
 * \ingroup wds
 * 
 * Lte Attach Params Indication Indication unpack
 * 
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_SLQSLteAttachParams_ind(
	uint8_t *pResp,
	uint16_t respLen,
	unpack_wds_SLQSLteAttachParams_ind_t *pOutput);

/**
 * \ingroup wds
 * 
 * This structure contains the WdsApnOpReservedPcoListChange Information
 *  - Parameter values default to their data type's maximum unsigned value
 *    unless explicitly stated otherwise.
 *
 *  @param  apn_name
 *          - APN Name.
 *  @param  PcoInfoLength
 *          - Number of Wds_Apn_Operatore_Reserved_PCO.
 *  @param  pWdsApnOpReservedPco
 *          - Wds Apn Operator Reserved PCO list.
 *  @param  Tlvresult
 *          - TLV present flag, TURE if presented, otherwise FALSE
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct
{
    char    apn_name[MAX_APN_STRING];
  	uint8_t PcoInfoLength;
	WdsApnOpReservedPco_t *pWdsApnOpReservedPcoList;
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_wds_SLQSApnOpReservedPcoListChange_ind_t;

/**
 * \ingroup wds
 * 
 * APN Operator Reserved PCO List Change Indication unpack
 * 
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_SLQSApnOpReservedPcoListChange_ind(
	uint8_t *pResp,
	uint16_t respLen,
	unpack_wds_SLQSApnOpReservedPcoListChange_ind_t *pOutput);

/**
 * \ingroup wds
 * 
 * This structure contains the WdsApnMsisdnInfoChange Information
 *  - Parameter values default to their data type's maximum unsigned value
 *    unless explicitly stated otherwise.
 *
 *  @param  apn_name
 *          - APN Name
 *  @param  msisdn_len
 *          - Number of MSISDN.
 *  @param  pMsisdn
 *          - MSISDN associated with the APN. Max 64 items.
 *  @param  Tlvresult
 *          - TLV present flag, TURE if presented, otherwise FALSE
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct
{
    char        apn_name[MAX_APN_STRING];
    uint16_t    msisdn_len;
    uint8_t     *pMsisdn;
    uint16_t    Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_wds_SLQSApnMsisdnInfoChange_ind_t;

/**
 * \ingroup wds
 * 
 * APN MSISDN Information Change Indication unpack
 * 
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_SLQSApnMsisdnInfoChange_ind(
	uint8_t *pResp,
	uint16_t respLen,
	unpack_wds_SLQSApnMsisdnInfoChange_ind_t *pOutput);

/**
 * \ingroup wds
 * 
 * This structure contains the WdsPDNThrottleInformation Information
 *  - Parameter values default to their data type's maximum unsigned value
 *    unless explicitly stated otherwise.
 *
 *  @param  is_ipv4_throttled
 *          - Values: 0 - IPv4 not throttled 1 - IPv4 throttled.
 *  @param  is_ipv6_throttled
 *          - Values: 0 - IPv6 not throttled 1 - IPv6 throttled.
 *  @param  remaining_ipv4_throttled_time
 *          - Remaining IPv4 throttled time in milliseconds.
 *  @param  remaining_ipv6_throttled_time
 *          - Remaining IPv6 throttled time in milliseconds.
 *  @param  apn_string_len
 *          - Number of sets of the apn_string.
 *  @param  ApnName
 *          - APN Name.
 *
 */
typedef struct
{
	uint8_t    is_ipv4_throttled;
	uint8_t    is_ipv6_throttled;
	uint32_t   remaining_ipv4_throttled_time;
	uint32_t   remaining_ipv6_throttled_time;
	uint8_t    apn_string_len;
	char       ApnName[MAX_APN_STRING];
}WdsPDNThrottleInformationTlv_t;

/**
 * \ingroup wds
 * 
 * This structure contains the WdsPDNThrottleInformation Information
 *  - Parameter values default to their data type's maximum unsigned value
 *    unless explicitly stated otherwise.
 *
 *  \param  is_ipv4_throttled
 *          - Values: 0 - IPv4 not throttled 1 - IPv4 throttled.
 *  \param  is_ipv6_throttled
 *          - Values: 0 - IPv6 not throttled 1 - IPv6 throttled.
 *  \param  is_non_ip_throttled
 *			- Values: 0 - NON_IP not throttled 1 - NON_IP throttled.
 *  \param  remaining_ipv4_throttled_time
 *          - Remaining IPv4 throttled time in milliseconds.
 *  \param  remaining_ipv6_throttled_time
 *          - Remaining IPv6 throttled time in milliseconds.
 *  \param  remaining_non_ip_throttled_time
 *			- Remaining NON_IP throttled time in milliseconds.
 *  \param  apn_string_len
 *          - Number of sets of the apn_string.
 *  \param  ApnName
 *          - APN Name.
 *
 */
typedef struct
{
	uint8_t is_ipv4_throttled;
	uint8_t is_ipv6_throttled;
	uint8_t is_non_ip_throttled;
	uint32_t remaining_ipv4_throttled_time;
	uint32_t remaining_ipv6_throttled_time;
	uint32_t remaining_non_ip_throttled_time;
	uint8_t  apn_string_len;
	char    ApnName[MAX_APN_STRING];
}WdsExtPDNThrottleInformationTlv_t;

/**
 * \ingroup wds
 * 
 * This structure contains the WdsExtPDNThrottleInformation Information
 *  - Parameter values default to their data type's maximum unsigned value
 *    unless explicitly stated otherwise.
 *
 *  @param  is_emergency_apn
 *          - Values: - APN is not emergency APN 1 - APN is emergency APN.
 *  @param  apn_blocked_on_all_plmns
 *          - Values: 0 - APN is not blocked on all PLMNs 1 - APN is blocked on all PLMNs.
 *  @param  throttled_plmn_id
 *			- PLMN ID on which the APN is throttled.
 *  @param  apn_string_len
 *          - Number of sets of the apn_string.
 *  @param  ApnName
 *          - APN Name.
 *
 */
typedef struct
{
	uint8_t is_emergency_apn;
	uint8_t apn_blocked_on_all_plmns;
	uint8_t throttled_plmn_id[3];
	uint8_t apn_string_len;
	char    ApnName[MAX_APN_STRING];
}WdsAddPDNThrottleInformationTlv_t;

/**
 * \ingroup wds
 * 
 * This structure contains the Wds PDN Throttle Info Indication
 *  - Parameter values default to their data type's maximum unsigned value
 *    unless explicitly stated otherwise.
 *
 *  @param  throttle_info_len
 *          - Number of WdsPDNThrottleInformation instances.
 *  @param  throttle_info_ext_len
 *          - Number of WdsPDNThrottleInformation instances.
 *  @param  throttle_info_addn_params_len
 *          - Number of WdsExtPDNThrottleInformation instance.
 *  @param  pWdsPDNThrottleInformation
 *          - PDN Throttle Information.
 *          - Bit to check in ParamPresenceMask - <B>0x10</B>
 *  @param  pWdsExtPDNThrottleInformation
 *          - Extended PDN Throttle Information.
 *          - Bit to check in ParamPresenceMask - <B>0x11</B>
 *  @param  pWdsAddPDNThrottleInformation
 *          - Additional PDN Throttle Information.
 *          - Bit to check in ParamPresenceMask - <B>0x12</B>
 * @param  Tlvresult - unpack Tlv Result.
 *	@param ParamPresenceMask
 *		    - TLVs parameters mask
 */
typedef struct
{
	uint8_t throttle_info_len;
	uint8_t throttle_info_ext_len;
	uint8_t throttle_info_addn_params_len;
	WdsPDNThrottleInformationTlv_t    *pPDNThrottleInformation;
	WdsExtPDNThrottleInformationTlv_t *pExtPDNThrottleInformationList;
	WdsAddPDNThrottleInformationTlv_t *pAddPDNThrottleInformationList;
    uint16_t Tlvresult;
    swi_uint256_t     ParamPresenceMask;
}unpack_wds_SLQSPdnThrottleInfo_ind_t;

/**
 * \ingroup wds
 * 
 * unpack_wds_SLQSPdnThrottleInfo_ind
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_SLQSPdnThrottleInfo_ind(
	uint8_t *pResp,
	uint16_t respLen,
	unpack_wds_SLQSPdnThrottleInfo_ind_t *pOutput);

/**
 * \ingroup wds
 * 
 * This structure contains the WdsApnOpReservedPco Information
 *  - Parameter values default to their data type's maximum unsigned value
 *    unless explicitly stated otherwise.
 *
 *  @param  profile_type
 *          - Identifies the technology type of the profile.
 *  @param  profile_index
 *          - Index identifying the profile.
 *  @param  apn_name_len
 *          - Number of sets of the ApnName.
 *  @param  ApnName
 *          - Name of the APN.
 *  @param  pdp_type
 *          -  PDP type of the profile. Values:
 *                      WDS_PDP_TYPE_PDP_IPV4 (0x00) - PDP-IP (IPv4)
 *                      WDS_PDP_TYPE_PDP_PPP (0x01) - PDP-PPP
 *                      WDS_PDP_TYPE_PDP_IPV6 (0x02) - PDP-IPv6
 *                      WDS_PDP_TYPE_PDP_IPV4V6 (0x03) - PDP-IPv4 and IPv6
 *                      WDS_PDP_TYPE_PDP_NON_ IP (0x04) - PDP-NON IP
 */
typedef struct
{
    uint8_t   profile_type;
    uint8_t   profile_index;
    uint8_t   apn_name_len;
    char      apn_name[MAX_APN_STRING];
    uint8_t   pdp_type;
} WdsDeletedProfileResult_t;

/**
 * \ingroup wds
 * 
 * This structure contains the WdsDeleteAllProfileresultList Information
 *  - Parameter values default to their data type's maximum unsigned value
 *    unless explicitly stated otherwise.
 *
 *  @param  deleted_profiles_list_len
 *          - Number of WdsDeletedProfileResult instances.
 *  @param  pWWdsDeleteAllProfileresult
 *          - Deleted Profiles list.
 *
 */
typedef struct
{
    uint8_t   deleted_profiles_list_len;
    WdsDeletedProfileResult_t *pWdsDeleteAllProfileresult; 
}QmiWdsDeletedProfileresultList_t;

/**
 * \ingroup wds
 * 
 * This structure contains the QmiCbkWdsDeleteAllProfilesResultInd_t Information
 *  - Parameter values default to their data type's maximum unsigned value
 *    unless explicitly stated otherwise.
 *
 *  @param   Status
 *               Values:
 *                  0x00 - Delete all operation succeeded
 *                  0x01 - Failure to delete any profiles
 *                  0x02 - Failure occurred in the middle of the operation (only some profiles got deleted)
 *  @param  ApnMsisdnChangeInfo_len
 *          - Number of ApnMsisdnChangeInfo.
 *  @param  pApnMsisdnChangeInfo
 *          - Wds Apn Operatore Reserved PCO list. Max 64 items.
  *	@param ParamPresenceMask
 *		    - TLVs parameters mask
 */
typedef struct
{
    uint8_t   Status;
    QmiWdsDeletedProfileresultList_t *pWdsDeleteProfileList; 
    swi_uint256_t       ParamPresenceMask;
} QmiCbkWdsDeleteAllProfilesResultInd_t;

/**
 * \ingroup wds
 * 
 * unpack_wds_SLQSDeleteAllProfilesResult_ind
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_SLQSDeleteAllProfilesResult_ind(
	uint8_t *pResp,
	uint16_t respLen,
	QmiCbkWdsDeleteAllProfilesResultInd_t *pOutput);

/**
 * \ingroup wds
 * 
 * This structure contains the ModemAssisted Keep Alive Status Indication Information
 *  - Parameter values default to their data type's maximum unsigned value
 *    unless explicitly stated otherwise.
 *
 *  @param  Status
 *          - Values: WDS_KEEP_ALIVE_RESULT_ OK(0) - Result OK. 
 *          - WDS_KEEP_ALIVE_RESULT_ERROR (1) - Result error.
 *          - WDS_KEEP_ALIVE_NETWORK_DOWN_ERROR (2) - Network down error.
 *  @param  Keep_alive_handle
 *          - Keep Alive Handle.
 *  @param  Tlvresult
 *          - TLV present flag, TURE if presented, otherwise FALSE
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct
{
    uint32_t  Status;
    uint32_t  Keep_alive_handle;
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_wds_SLQSModemAssistedKaStatus_ind_t;

/**
 * \ingroup wds
 * 
 * Modem Assisted Keep Alive Status indication unpack
 * 
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_SLQSModemAssistedKaStatus_ind(
	uint8_t *pResp,
	uint16_t respLen,
	unpack_wds_SLQSModemAssistedKaStatus_ind_t *pOutput);

/**
 * \ingroup wds
 * 
 * This structure contains pack get default profile information.
 *
 * @param profiletype profile type
 *        - 0 - WDS_PROFILE_TYPE_3GPP (0x00) - 3GPP
 *        - 1 - WDS_PROFILE_TYPE_3GPP2 (0x01) - 3GPP2
 *        - 2 - WDS_PROFILE_TYPE_EPC  (0x02) - EPC
 */
typedef struct {
    uint32_t profiletype;
} pack_wds_GetDefaultSettings_t;

/**
 * \ingroup wds
 * 
 * This structure contains the UMTS Requested QoS TLV=0x17 and 0x18 of Get Default Settings response parameters.
 *
 * @param pTraffic_class
 *              - Traffic class
 *              - Values:
 *               - WDS_TRAFFIC_CLASS_SUBSCRIBED (0x00) - Subscribed
 *               - WDS_TRAFFIC_CLASS_CONVERSATIONAL (0x01) - Conversational
 *               - WDS_TRAFFIC_CLASS_STREAMING (0x02) - Streaming
 *               - WDS_TRAFFIC_CLASS_INTERACTIVE (0x03) - Interactive
 *               - WDS_TRAFFIC_CLASS_BACKGROUND (0x04) - Background
 * @param max_uplink_bitrate
 *              - Maximum uplink bitrate in bits per second.
 * @param max_downlink_bitrate
 *              - Maximum downlink bitrate in bits per second.
 * @param guaranteed_uplink_bitrate
 *              - Guaranteed uplink bitrate in bits per second.
 * @param guaranteed_downlink_bitrate
 *              - Guaranteed downlink bitrate in bits per second.
 * @param qos_delivery_order
 *              - Values:
 *                - WDS_QOS_DELIVERY_ORDER_SUBSCRIBE (0x00) - Subscribe
 *                - WDS_QOS_DELIVERY_ORDER_ON (0x01) - Delivery order on
 *                - WDS_QOS_DELIVERY_ORDER_OFF (0x02) - Delivery order off
 * @param max_sdu_size
 *              - Maximum SDU size.
 * @param sdu_error_ratio
 *              - Target value for the fraction of SDUs lost or detected as erroneous. 
 *                - Values:
 *                  - 0 - Subscribe
 *                  - 1 - 1x10 2
 *                  - 2 - 7x10 3
 *                  - 3 - 1x10 3
 *                  - 4 - 1x10 4
 *                  - 5 - 1x10 5
 *                  - 6 - 1x10 6
 *                  - 7 - 1x10 1
 * @param residual_bit_error_ratio
 *              - Target value for the undetected bit error ratio in the delivered SDUs.
 *                - Values:
 *                  - 0 - Subscribe
 *                  - 1 - 5x10 2
 *                  - 2 - 1x10 2
 *                  - 3 - 5x10 3
 *                  - 4 - 4x10 3
 *                  - 5 - 1x10 3
 *                  - 6 - 1x10 4
 *                  - 7 - 1x10 5
 *                  - 8 - 1x10 6
 *                  - 9 - 6x10 8
 * @param delivery_erroneous_SDUs
 *              - Delivery of erroneous SDUs. Indicates whether SDUs detected as erroneous are delivered.
 *                - Values:
 *                  - WDS_DELIVERY_ERRONEOUS_SDUS_SUBSCRIBE (0x00) - Subscribe
 *                  - WDS_DELIVERY_ERRONEOUS_SDUS_NO_DETECTION (0x01) - No detection
 *                  - WDS_DELIVERY_ERRONEOUS_SDUS_YES (0x02) - Erroneous SDU is delivered
 *                  - WDS_DELIVERY_ERRONEOUS_SDUS_NO (0x03) - Erroneous SDU is not delivered
 * @param transfer_delay
 *              - Transfer delay. Indicates the targeted time between a request to transfer an SDU at one SAP 
 *                to its delivery at the other SAP, in milliseconds; if the parameter is set to 0, the subscribed
 *                value is requested.
 * @param traffic_handling_priority
 *              - Traffic handling priority. Specifies the relative importance for handling of SDUs that belong 
 *                to the UMTS bearer, compared to the SDUs of other bearers. If the parameter is set to 0, the
 *                subscribed value is requested.
 */
struct UmtsRequestedMinQos_t
{
    uint8_t     traffic_class; 
    uint32_t    max_uplink_bitrate; 
    uint32_t    max_downlink_bitrate; 
    uint32_t    guaranteed_uplink_bitrate;
    uint32_t    guaranteed_downlink_bitrate;
    uint8_t     qos_delivery_order;
    uint32_t    max_sdu_size;
    uint8_t     sdu_error_ratio;
    uint8_t     residual_bit_error_ratio;
    uint8_t     delivery_erroneous_SDUs;
    uint32_t    transfer_delay;
    uint32_t    traffic_handling_priority;
};

/**
 * \ingroup wds
 * 
 * This structure contains the GPRS Requested QoS TLV=0x19 and 0x1A of Get Default Settings response parameters.
 *
 * @param precedence_class
 *          - Precedence class
 * @param delay_class
 *          - Delay class
 * @param reliability_class
 *          - Reliability class
 * @param peak_throughput_class
 *          - Peak throughput class
 * @param mean_throughput_class
 *          - Mean throughput class
*/
struct GprsRequestedMinQos_t
{
    uint32_t    precedence_class;
    uint32_t    delay_class;
    uint32_t    reliability_class;
    uint32_t    peak_throughput_class;
    uint32_t    mean_throughput_class;
};

/**
 * \ingroup wds
 * 
 * This structure contains the Traffic Flow Template (TFT) ID1 Parameters of Get Default Settings response parameters.
 *
 * @param precedence_class
 *          - Precedence class
 * @param filter_id
 *          - Filter identifier.
 * @param eval_id
 *          - Evaluation precedence index.
 * @param ip_version
 *          - IP version number. 
 *            - Values:
 *              - WDS_IP_VERSION_IPV4 (0x04) - IPv4
 *              - WDS_IP_VERSION_IPV6 (0x06) - IPv6
 * @param source_ip
 *          - Values:
 *            - IPv4 - Fill the first 4 bytes
 *            - IPv6 - Fill all the 16 bytes
 * @param source_ip_mask
 *          - Mask value for the source address.
 * @param next_header
 *          - Next header/protocol value.
 * @param dest_port_range_start
 *          - Start value for the destination port range.
 * @param dest_port_range_end
 *          - End value for the destination port range.
 * @param src_port_range_start
 *          - Start value for the source port range.
 * @param src_port_range_end
 *          - End value for the source port range.
 * @param ipsec_spi
 *          - IPSec security parameter index.
 * @param tos_mask
 *          - TOS mask (traffic class for IPv6).
 * @param flow_label
 *          - Flow label.
*/
struct TrafficFlow_t
{
    uint8_t filter_id;
    uint8_t eval_id;
    uint8_t ip_version;
    uint8_t source_ip;
    uint8_t source_ip_mask;
    uint8_t next_header;
    uint16_t dest_port_range_start;
    uint16_t dest_port_range_end;
    uint16_t src_port_range_start;
    uint16_t src_port_range_end;
    uint32_t ipsec_spi;
    uint16_t tos_mask;
    uint32_t flow_label;
};

/**
 * \ingroup wds
 * 
 * This structure contains the 3GPP LTE QoS Parameters of Get Default Settings response parameters.
 *
 * @param qci
 *          - For LTE, the requested QoS must be specified using the QoS Class Identifier (QoS). 
 *            - Values:
 *              - QCI value 0 - Requests the network to assign the appropriate QCI value
 *              - QCI values 1 to 4 - Associated with guaranteed bitrates
 *              - QCI values 5 to 9 - Associated with nonguaranteed bitrates, the values specified as 
 *                guaranteed and maximum bitrates are ignored.
 * @param g_dl_bit_rate
 *          - Guaranteed DL bitrate.
 * @param max_dl_bit_rate
 *          - Maximum DL bitrate.
 * @param g_ul_bit_rate
 *          - Guaranteed UL bitrate.
 * @param max_ul_bit_rate
 *          - Maximum UL bitrate.
 */
struct SGpp_Lte_Qos_Param_t
{
    uint8_t qci;
    uint32_t g_dl_bit_rate;
    uint32_t max_dl_bit_rate;
    uint32_t g_ul_bit_rate;
    uint32_t max_ul_bit_rate;
};

/**
 * \ingroup wds
 * 
 * This structure contains the UMTS Requested QoS With Signaling Indication Flag of Get Default Settings response parameters.
 *
 * @param umtsRequestedQos
 *          - ref UmtsRequestedQos 
 * @param sig_ind
 *          - Signaling indication flag. 
 *            - Values:
 *              - 0 - Signaling indication off
 *              - 1 - Signaling indication on
 */
struct UmtsReqQoSWithSigInd_t
{
    struct UmtsRequestedMinQos_t umtsRequestedQos;
    uint8_t sig_ind;    
};

/**
 * \ingroup wds
 * 
 * This structure contains the 3GPP LTE QoS Parameters of Get Default Settings response parameters.
 *
 * @param auth_type
 *          - Authentication type
 * @param username_len
 *          - Number of sets of the username
 * @param user_name
 *          - Username
 * @param password_len
 *          - Number of sets of the password
 * @param password
 *          - Password
 * @param certificate_path_len
 *          - Number of sets of the Certificate_path 
 * @param certificate_path
*/
struct EapAuthentication_t
{
    uint32_t auth_type;
    uint8_t  username_len;
    char     user_name[WDS_AUTH_MAX_STRING];
    uint8_t  password_len;
    char     password[WDS_AUTH_MAX_STRING];
    uint8_t  certificate_path_len;
    char     certificate_path[WDS_AUTH_MAX_STRING];
};

/**
 * \ingroup wds
 * 
 *  Reads the default profile settings from the device. The default profile is
 *  used to establish an auto connect data session.
 *
 * @param Profile_name_size
 *          - profile name buffer size
 * @param Profile_name
 *          - One or more bytes describing the profile. The description is a user-defined name for the profile.
 *            QMI_ERR_ARG_TOO_LONG is returned if the profile_name is too long.
 *          - Bit to check in ParamPresenceMask - <B>0x10</B>
 * @param Pdp_type
 *          - Specifies the type of data payload exchanged over the airlink when the packet data session is established 
 *            with this profile. 
 *              Values:
 *              WDS_PDP_TYPE_PDP_IPV4 (0x00) - PDP-IP (IPv4)
 *              WDS_PDP_TYPE_PDP_PPP (0x01) - PDP-PPP
 *              WDS_PDP_TYPE_PDP_IPV6 (0x02) - PDP-IPv6
 *              WDS_PDP_TYPE_PDP_IPV4V6 (0x03) - PDP-IPv4 and IPv6
 *              WDS_PDP_TYPE_PDP_NON_ IP (0x04) - PDP-NON IP
 *          - Bit to check in ParamPresenceMask - <B>0x11</B>
 * @param Pdp_hdr_compression_type
 *          - PDP Header Compression Type
 *              Values:
 *              WDS_PDP_HDR_COMPR_TYPE_OFF (0x00) - PDP header compression is off
 *              WDS_PDP_HDR_COMPR_TYPE_MANUFACTURER_PREF (0x01) - Manufacturer preferred compression
 *              WDS_PDP_HDR_COMPR_TYPE_RFC_1144 (0x02) - PDP header compression based on RFC 1144
 *              WDS_PDP_HDR_COMPR_TYPE_RFC_2507 (0x03) - PDP header compression based on RFC 2507
 *              WDS_PDP_HDR_COMPR_TYPE_RFC_3095 (0x04) - PDP header compression based on RFC 3095
 *          - Bit to check in ParamPresenceMask - <B>0x12</B>
 * @param Pdp_data_compression_type
 *          - PDP Data Compression Type
 *              Values:
 *              WDS_PDP_DATA_COMPR_TYPE_OFF (0x00) - PDP data compression is off
 *              WDS_PDP_DATA_COMPR_TYPE_MANUFACTURER_PREF (0x01) - Manufacturer preferred compression
 *              WDS_PDP_DATA_COMPR_TYPE_V42 (0x02) - V.42BIS data compression
 *              WDS_PDP_DATA_COMPR_TYPE_V44 (0x03) - V.44 data compression
 *          - Bit to check in ParamPresenceMask - <B>0x13</B>
 * @param Apn_name_size
 *          - APN name buffer size
 * @param Apn_name
 *          - Context Access Point Node (APN) Name
 *              String parameter that is a logical name used to select the GGSN and external packet data network. 
 *              If the value is NULL or omitted, the subscription default value is requested.
 *              QMI_ERR_ARG_TOO_LONG is returned if the APN name is too long.
 *          - Bit to check in ParamPresenceMask - <B>0x14</B>
 * @param Primary_DNS_IPv4_address_preference
 *          - Used as a preference during negotiation with the network; if not specified, the wireless device attempts
 *            to obtain the DNS address automatically from the network. The negotiated value is provided to the host via DHCP.
 *          - Bit to check in ParamPresenceMask - <B>0x15</B>
 * @param Secondary_DNS_IPv4_address_preference
 *          - Used as a preference during negotiation with the network; if not specified, the wireless device attempts to 
 *            obtain the DNS address automatically from the network. The negotiated value is provided to the host via DHCP.
 *          - Bit to check in ParamPresenceMask - <B>0x16</B>
 * @param umtsRequestedQos
 *          - UMTS Requested QoS
 *          - Bit to check in ParamPresenceMask - <B>0x17</B>
 * @param umtsMinimumQos
 *          - UMTS Minimum QoS
 *          - Bit to check in ParamPresenceMask - <B>0x18</B>
 * @param gprsRequestedQos
 *          - GPRS Requested QoS
 *          - Bit to check in ParamPresenceMask - <B>0x19</B>
 * @param gprsMinimumQos
 *          - GPRS minimum QoS
 *          - Bit to check in ParamPresenceMask - <B>0x1A</B>
 * @param UserNameSize [in]
 *          - Username buffer size
 * @param UserName
 *          - Username
 *          - Bit to check in ParamPresenceMask - <B>0x1B</B>
 * @param PasswordSize [in]
 *          - Password buffer size
 * @param Password
 *          - Password
 *          - Bit to check in ParamPresenceMask - <B>0x1C</B>
 * @param Authentication_preference
 *          - Authentication Preference
 *            Bitmap that indicates the authentication algorithm preference. 
 *            - Values:
 *              - Bit 0 - PAP preference: 
 *                  - 0 - PAP is never performed
 *                  - 1 - PAP can be performed
 *              - Bit 1 - CHAP preference:
 *                  - 0 - CHAP is never performed
 *                  - 1 - CHAP can be performed
 *              - All other bits are reserved and are ignored. They must be set to zero by the client.
 *                If more than one bit is set, the device decides which authentication procedure is performed
 *                while setting up the data session. For example, the device might have a policy to select the 
 *                most secure authentication mechanism.
 *          - Bit to check in ParamPresenceMask - <B>0x1D</B>
 * @param Ipv4_address_preference
 *          - IPv4 Address Preference
 *              - Preferred IPv4 address assigned to the TE - The actual assigned address is negotiated with the 
 *                network and can differ from this value. If not specified, the IPv4 Address is obtained automatically 
 *                from the network. The assigned value is provided to the host via DHCP.
 *          - Bit to check in ParamPresenceMask - <B>0x1E</B>
 * @param Pcscf_addr_using_pco
 *          - PCSCF Address Using PCO Flag
 *            - Values:
 *              - 1 - TRUE - Request PCSCF address using PCO
 *              - 0 - FALSE - Do not request (default)
 *          - Bit to check in ParamPresenceMask - <B>0x1F</B>
 * @param Pdp_access_control_flag
 *          - PDP Access Control Flag
 *            - Values:
 *              - WDS_PDP_ACCESS_CONTROL_NONE (0x00) - None
 *              - WDS_PDP_ACCESS_CONTROL_REJECT (0x01) - Reject
 *              - WDS_PDP_ACCESS_CONTROL_PERMISSION (0x02) - Permission
 *          - Bit to check in ParamPresenceMask - <B>0x20</B>
 * @param Pcscf_addr_using_dhcp
 *          - PCSCF Address Using DHCP
 *            - Values:
 *              - 1 - TRUE - Request PCSCF address using DHCP
 *              - 0 - FALSE - Do not request (default)
 *          - Bit to check in ParamPresenceMask - <B>0x21</B>
 * @param Im_cn_flag
 *          - IM CN Flag
 *            - Values:
 *              - 1 - TRUE - Request IM CN flag for this profile
 *              - 0 - FALSE - Do not request IM CN flag for this profile
 *          - Bit to check in ParamPresenceMask - <B>0x22</B>
 * @param trafficFlow
 *          - Traffic Flow Template (TFT) ID1 Parameters
 *          - Bit to check in ParamPresenceMask - <B>0x23</B>
 * @param tftId2Parameters
 *          - Traffic Flow Template ID2 Parameters
 *          - Bit to check in ParamPresenceMask - <B>0x24</B>
 * @param Pdp_context
 *          - PDP Context Number
 *          - Bit to check in ParamPresenceMask - <B>0x25</B>
 * @param Secondary_flag
 *          - PDP Context Secondary Flag
 *            - Values:
 *              - 1 - TRUE - This is the secondary profile
 *              - 0 - FALSE - This is not the secondary profile
 *          - Bit to check in ParamPresenceMask - <B>0x26</B>
 * @param Primary_id
 *          - PDP context number primary ID.
 *          - Bit to check in ParamPresenceMask - <B>0x27</B>
 * @param Ipv6_address_preference
 *          - The preferred IPv6 address to assign to the TE; the actual assigned address is
 *            negotiated with the network and can differ from this value. If not specified,
 *            the IPv6 address is obtained automatically from the network.
 *          - Bit to check in ParamPresenceMask - <B>0x28</B>
 * @param umtsReqQoSWithSigInd
 *          - UMTS requested QoS With Signaling Indication
 *          - Bit to check in ParamPresenceMask - <B>0x29</B>
 * @param umtsMinQoSWithSigInd
 *          - UMTS Minimum QoS With Signaling Indication
 *          - Bit to check in ParamPresenceMask - <B>0x2A</B>
 * @param Primary_dns_ipv6_address_preference
 *          - Primary DNS IPv6 Address Preference
 *          - Used as a preference during negotiation with the network; if not specified, the
 *            wireless device attempts to obtain the DNS address automatically from the network. 
 *            The negotiated value is provided to the host via DHCP.
 *          - Bit to check in ParamPresenceMask - <B>0x2B</B>
 * @param Secondary_dns_ipv6_address_preference
 *          - Secondary DNS IPv6 Address Preference
 *          - Used as a preference during negotiation with the network; if not specified, the
 *            wireless device attempts to obtain the DNS address automatically from the network. The negotiated 
 *            value is provided to the host via DHCP.
 *          - Bit to check in ParamPresenceMask - <B>0x2C</B>
 * @param Addr_allocation_preference
 *          - DHCP/NAS Preference
 *          - Indicates the address allocation preference. 
 *            Values:
 *            - WDS_ADDR_ALLOC_PREF_NAS(0x00) - Use NAS signaling for address allocation
 *            - WDS_ADDR_ALLOC_PREF_DHCP(0x01) - Use DHCP for address allocation
 *          - Bit to check in ParamPresenceMask - <B>0x2D</B>
 * @param 3Gpp_Lte_Qos_Param
 *          - 3GPP LTE QoS Parameters
 *          - Bit to check in ParamPresenceMask - <B>0x2E</B>
 * @param Apn_disabled_flag
 *          - APN Disabled Flag
 *          - Setting this flag disables the use of this profile for making data calls. Any data call with this profile fails locally.
 *            - Values:
 *              - 0 - FALSE (default)
 *              - 1 - TRUE
 *          - Bit to check in ParamPresenceMask - <B>0x2F</B>
 * @param Pdn_inactivity_timeout
 *          - PDN Inactivity Timeout
 *            - Duration of the inactivity timer in seconds. When a PDP context or PDN connection is inactive (that is, no data Rx or Tx)
 *              for this duration of time, PDP context or PDN connection is disconnected. The default setting of zero is treated as an infinite value.
 *          - Bit to check in ParamPresenceMask - <B>0x30</B>
 * @param Apn_class
 *          - An opaque, numeric identifier representing the APN in the profile. This can be transparently set for any profile and queried later.
 *          - Bit to check in ParamPresenceMask - <B>0x31</B>
 * @param Attach_wo_pdn
 *          - Attach Without PDN
 *          - Indicates whether attach without PDN capability is supported. 
 *            - Values:
 *              - 1 - Attach without PDN is supported
 *              - 0 - Attach without PDN is not supported (default)
 *          - Bit to check in ParamPresenceMask - <B>0x49</B>
 * @param Pdn_label_3gpp_size
 *          - size of pPdn_label_3gpp 
 * @param Pdn_label_3gpp
 *          - PDN Label for 3GPP
 *          - Logical name used to map the APN name for selecting the packet data network. Maximum length allowed is 100 bytes.
 *          - Bit to check in ParamPresenceMask - <B>0x4A</B>
 * @param EapAuthentication_t
 *          - EAP Authentication
 *          - Bit to check in ParamPresenceMask - <B>0x4B</B>
 * @param Rqos_support
 *          - Reflective QoS Support
 *            - Values:
 *              - 1 - TRUE - Reflective QoS supported
 *              - 0 - FALSE - Not supported (default)
 *          - Bit to check in ParamPresenceMask - <B>0x4C</B>
 * @param Mhipv6_support
 *          - Multi-homed IPV6 PDU Session Support
 *            - Values:
 *              - 1 - TRUE - Multi-homed IPv6 PDU session supported
 *              - 0 - FALSE - Not supported (default)
 *          - Bit to check in ParamPresenceMask - <B>0x4D</B>
 * @param Always_on_pdu
 *          - Always on PDU Session
 *            - Values:
 *              - 1 - TRUE - Always on PDU
 *              - 0 - FALSE - Not supported (default)
 *          - Bit to check in ParamPresenceMask - <B>0x4E</B>
 * @param Negotiate_dns_server_preference
 *          - Negotiate DNS Server Preference
 *            - Values:
 *              - 1 - TRUE - Request DNS address from the PDSN (default)
 *              - 0 - FALSE - Do not request DNS addresses from the PDSN
 *          - Bit to check in ParamPresenceMask - <B>0x90</B>
 * @param Ppp_session_close_timer_DO
 *          - PPP Session Close Timer for DO
 *          - Timer value (in seconds) on the DO indicating how long the PPP session lingers before closing down.
 *          - Bit to check in ParamPresenceMask - <B>0x91</B>
 * @param Ppp_session_close_timer_1x
 *          - The timer value (in seconds) on 1X indicating how long the PPP session lingers before closing.
 *          - Bit to check in ParamPresenceMask - <B>0x92</B>
 * @param Allow_linger
 *          - Allow/Disallow Lingering of Interface
 *            - Values:
 *              - 1 - TRUE - Allow lingering
 *              - 0 - FALSE - Do not allow lingering
 *          - Bit to check in ParamPresenceMask - <B>0x93</B>
 * @param Lcp_ack_timeout
 *          - LCP ACK Timeout
 *            - Value of LCP ACK timeout in milliseconds.
 *          - Bit to check in ParamPresenceMask - <B>0x94</B>
 * @param Ipcp_ack_timeout
 *          - IPCP ACK Timeout
 *          - Value of IPCP ACK timeout in milliseconds.
 *          - Bit to check in ParamPresenceMask - <B>0x95</B>
 * @param Auth_timeout
 *          - AUTH Timeout
 *          - Value of authentication timeout in milliseconds.
 *          - Bit to check in ParamPresenceMask - <B>0x96</B>
 * @param Lcp_creq_retry_count
 *          - LCP Configuration Request Retry Count Value.
 *          - Bit to check in ParamPresenceMask - <B>0x97</B>
 * @param Ipcp_creq_retry_count
 *          - IPCP configuration request retry count value.
 *          - Bit to check in ParamPresenceMask - <B>0x98</B>
 * @param Auth_retry_count
 *          - Authentication retry count value.
 *          - Bit to check in ParamPresenceMask - <B>0x99</B>
 * @param Auth_protocol
 *          - Authentication Protocol
 *            - Values:
 *              - WDS_PROFILE_AUTH_PROTOCOL_NONE (0) - None
 *              - WDS_PROFILE_AUTH_PROTOCOL_PAP (1) - PAP
 *              - WDS_PROFILE_AUTH_PROTOCOL_CHAP (2) - CHAP
 *              - WDS_PROFILE_AUTH_PROTOCOL_PAP_CHAP (3) - PAP or CHAP
 *          - Bit to check in ParamPresenceMask - <B>0x9A</B>
 * @param User_id_size
 *          - user_id size
 * @param User_id
 *          - User ID used during data network authentication; maximum length allowed is 127 bytes.
 *            QMI_ERR_ARG_TOO_LONG is returned if the storage on the wireless device is insufficient in size to hold the value.
 *          - Bit to check in ParamPresenceMask - <B>0x9B</B>
 * @param Auth_Password_size
 *          - Authentication Password size
 * @param Auth_Password
 *          - Authentication Password
 *          - Password used during data network authentication; maximum length allowed is 127 bytes. QMI_ERR_ARG_TOO_LONG is
 *            returned if the storage on the wireless device is insufficient in size to hold the value.
 *          - Bit to check in ParamPresenceMask - <B>0x9C</B>
 * @param Data_rate
 *          - Data rate
 *            - Values:
 *              - WDS_PROFILE_DATA_RATE_ LOW(0) - Low (Low speed Service Options (SO15) only)
 *              - WDS_PROFILE_DATA_RATE_MEDIUM (1) - Medium (SO33 + low R-SCH)
 *              - WDS_PROFILE_DATA_RATE_HIGH (2) - High (SO33 + high R-SCH) Note: Default is 2.
 *          - Bit to check in ParamPresenceMask - <B>0x9D</B>
 * @param App_type
 *          - Application Type
 *            - Values:
 *              - WDS_PROFILE_APP_TYPE_DEFAULT (0x00000001) - Default application type
 *              - WDS_PROFILE_APP_TYPE_ LBS (0x00000020) - LBS application type
 *              - WDS_PROFILE_APP_TYPE_TETHERED (0x00000040) - Tethered application type
 *              - Note: Application type value in a profile cannot be modified. It can only be used to search for the 
 *                profile ID numbers that have the specified application type.
 *          - Bit to check in ParamPresenceMask - <B>0x9E</B>
 * @param Data_mode
 *          - Data Mode
 *            - Values:
 *              - WDS_PROFILE_DATA_MODE_CDMA_HDR (0) - CDMA or HDR (Hybrid 1X and 1xEV-DO)
 *              - WDS_PROFILE_DATA_MODE_CDMA (1) - CDMA only (1X only)
 *              - WDS_PROFILE_DATA_MODE_HDR (2) - HDR only (1xEV-DO only)
 *          - Bit to check in ParamPresenceMask - <B>0x9F</B>
 * @param App_priority
 *          - Application Priority
 *            - Numerical one byte value defining the application priority; higher value means higher priority.
 *              Note: Application priority value in a profile cannot be modified. It is listed for future extensibility 
 *              of profile ID search based on application priority. Note: Default is 0.
 *          - Bit to check in ParamPresenceMask - <B>0xA0</B>
 * @param Apn_string_size
 *          - APN Name character count
 * @param Apn_string
 *          - APN String
 *            - String representing the APN; maximum length allowed is 100 bytes. QMI_ERR_ARG_TOO_LONG is returned if the 
 *              APN name is too long.
 *          - Bit to check in ParamPresenceMask - <B>0xA1</B>
 * @param Pdn_type
 *          - PDN Type
 *            - Values:
 *              - WDS_PROFILE_PDN_TYPE_ IPV4 (0) - IPv4 PDN type
 *              - WDS_PROFILE_PDN_TYPE_ IPV6 (1) - IPv6 PDN type
 *              - WDS_PROFILE_PDN_TYPE_IPV4_IPV6 (2) - IPv4 or IPv6 PDN type
 *              - WDS_PROFILE_PDN_TYPE_UNSPECIFIED (3) - Unspecified PDN type (implying no preference)
 *          - Bit to check in ParamPresenceMask - <B>0xA2</B>
 * @param Is_pcscf_address_needed
 *          - Is PCSCF Address Needed 
 *          - Used to control whether the PCSCF address is requested from PDSN. 
 *              - Values:
 *                - 1 - TRUE - Request for PCSCF value from the PDSN
 *                - 0 - FALSE - Do not request for PCSCF value from the PDSN
 *          - Bit to check in ParamPresenceMask - <B>0xA3</B>
 * @param Primary_v4_dns_address
 *          - IPv4 Primary DNS Address
 *          - Primary IPv4 DNS address that can be statically assigned to the UE.
 *          - Bit to check in ParamPresenceMask - <B>0xA4</B>
 * @param Secondary_v4_dns_address
 *          - IPv4 Secondary DNS Address
 *          - Secondary IPv4 DNS address that can be statically assigned to the UE.
 *          - Bit to check in ParamPresenceMask - <B>0xA5</B>
 * @param Primary_v6_dns_address
 *          - Primary IPv6 DNS address that can be statically assigned to the UE.
 *          - Bit to check in ParamPresenceMask - <B>0xA6</B>
 * @param Secondary_v6_dns_address
 *          - Secondary IPv6 DNS address that can be statically assigned to the UE.
 *          - Bit to check in ParamPresenceMask - <B>0xA7</B>
 * @param Rat_type
 *          - RAT Type
 *            - Values:
 *              - WDS_RAT_TYPE_HRPD (1) - HRPD
 *              - WDS_RAT_TYPE_EHRPD (2) - EHRPD
 *              - WDS_RAT_TYPE_HRPD_EHRPD (3) - HRPD_EHRPD
 *          - Bit to check in ParamPresenceMask - <B>0xA8</B>
 * @param Apn_enabled_3gpp2
 *          - APN Enabled
 *            - Specifies whether the APN in that profile is enabled or disabled. If the APN is disabled, 
 *              the data call cannot be established using that APN.
 *            - Values:
 *              - 1 - Enabled (default)
 *              - 0 - Disabled
 *          - Bit to check in ParamPresenceMask - <B>0xA9</B>
 * @param Pdn_inactivity_timeout_3gpp2
 *          - PDN Inactivity Timeout
 *            - Duration of inactivity timer in minutes. When a PDP context or PDN connection is 
 *              inactive (that is, no data Rx or Tx) for this duration of time, the PDP context or PDN connection is disconnected. 
 *              The default setting of zero is treated as an infinite value.
 *          - Bit to check in ParamPresenceMask - <B>0xAA</B>
 * @param Apn_class_3gpp2
 *          - APN Class
 *            - Opaque, numeric identifier representing the APN in the profile. This can be transparently set for any profile and
 *              queried later.
 *          - Bit to check in ParamPresenceMask - <B>0xAB</B>
 * @param Extended_error_code
 *          - Profile Extended Error Code
 *            - Extended error code received from the DS profile subsystem. These error codes are explained in Appendix C.
 *          - Bit to check in ParamPresenceMask - <B>0xE0</B>
 * @param  Tlvresult - unpack Tlv Result.
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */

typedef struct{
    uint8_t     Profile_name_size;
    char        Profile_name[WDS_MAX_STRING];
    uint8_t     Pdp_type;
    uint8_t     Pdp_hdr_compression_type;
    uint8_t     Pdp_data_compression_type;
    uint8_t     Apn_name_size;
    char        Apn_name[WDS_MAX_STRING];
    uint32_t    Primary_DNS_IPv4_address_preference;
    uint32_t    Secondary_DNS_IPv4_address_preference;
    struct UmtsRequestedMinQos_t umtsRequestedQos;
    struct UmtsRequestedMinQos_t umtsMinimumQos;
    struct GprsRequestedMinQos_t gprsRequestedQos;
    struct GprsRequestedMinQos_t gprsMinimumQos;
    uint8_t     UserNameSize;
    char        UserName[WDS_MAX_STRING];
    uint8_t     PasswordSize;
    char        Password[WDS_MAX_STRING];
    uint8_t     Authentication_preference;
    uint32_t    Ipv4_address_preference;
    uint8_t     Pcscf_addr_using_pco;
    uint8_t     Pdp_access_control_flag;
    uint8_t     Pcscf_addr_using_dhcp;
    uint8_t     Im_cn_flag;
    struct TrafficFlow_t trafficFlow;
    struct TrafficFlow_t tftId2Parameters;
    uint8_t     Pdp_context;
    uint8_t     Secondary_flag;
    uint8_t     Primary_id;
    uint8_t     Ipv6_address_preference[WDS_QMI_MSG_IPV6_LEN];
    struct UmtsReqQoSWithSigInd_t umtsReqQoSWithSigInd;
    struct UmtsReqQoSWithSigInd_t umtsMinQoSWithSigInd;
    uint8_t     Primary_dns_ipv6_address_preference[WDS_QMI_MSG_PRIMARY_DNSV6_LEN];
    uint8_t     Secondary_dns_ipv6_address_preference[WDS_QMI_MSG_SECONDARY_DNSV6_LEN];
    uint8_t     Addr_allocation_preference;
    struct SGpp_Lte_Qos_Param_t s3Gpp_Lte_Qos_Param;
    uint8_t     Apn_disabled_flag;
    uint32_t    Pdn_inactivity_timeout;
    uint8_t     Apn_class;
    uint8_t     Attach_wo_pdn;
    uint8_t     Pdn_label_3gpp_size;
    char        Pdn_label_3gpp[WDS_LABEL_3GPP_MAX_STRING];
    struct EapAuthentication_t eapAuthentication;
    uint8_t     Rqos_support;
    uint8_t     Mhipv6_support;
    uint8_t     Always_on_pdu;
    uint8_t     Negotiate_dns_server_preference;
    uint32_t    Ppp_session_close_timer_DO;
    uint32_t    Ppp_session_close_timer_1x;
    uint8_t     Allow_linger;
    uint16_t    Lcp_ack_timeout;
    uint16_t    Ipcp_ack_timeout;
    uint16_t    Auth_timeout;
    uint8_t     Lcp_creq_retry_count;
    uint8_t     Ipcp_creq_retry_count;
    uint8_t     Auth_retry_count;
    uint8_t     Auth_protocol;
    uint8_t     User_id_size;
    char        User_id[WDS_MAX_STRING];
    uint8_t     Auth_Password_size;
    char        Auth_Password[255];
    uint8_t     Data_rate;
    uint32_t    App_type;
    uint8_t     Data_mode;
    uint8_t     App_priority;
    uint8_t     Apn_string_size;
    char        Apn_string[WDS_MAX_STRING];
    uint8_t     Pdn_type;
    uint8_t     Is_pcscf_address_needed;
    uint32_t    Primary_v4_dns_address;
    uint32_t    Secondary_v4_dns_address;
    uint32_t    Primary_v6_dns_address;
    uint8_t     Secondary_v6_dns_address[WDS_QMI_MSG_SECONDARY_DNSV6_LEN];
    uint8_t     Rat_type;
    uint8_t     Apn_enabled_3gpp2;
    uint32_t    Pdn_inactivity_timeout_3gpp2;
    uint8_t     Apn_class_3gpp2;
    uint16_t    Extended_error_code;
    uint16_t    Tlvresult;
    swi_uint256_t  ParamPresenceMask;    
} unpack_wds_GetDefaultSettings_t;

/**
 * \ingroup wds
 * 
 * get default profile pack.
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  reqParam request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */
int pack_wds_GetDefaultSettings(
        pack_qmi_t  *pCtx,
        uint8_t     *pReqBuf,
        uint16_t    *pLen,
        pack_wds_GetDefaultSettings_t *reqParam
        );

/**
 * \ingroup wds
 * 
 * get default profile unpack.
 * 
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput      response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_GetDefaultSettings(
        uint8_t   *pResp,
        uint16_t  respLen,
        unpack_wds_GetDefaultSettings_t *pOutput
        );

/**
 * Name:    ThroughputInformationMac_t
 *
 * Purpose: Structure used to store information about Throughput Information Item MAC.
 *
 *  @param bearer_rlp_mac_id
 *          - Bearer ID representing the bearer, or RLP_MAC ID for which the throughput is being reported.
 * 
 * @param  uplink_actual_rate
 *          - Uplink actual rate in kb per second corresponding to the bearer or RLP_MAC ID.
 * 
 * @param  uplink_queue_size
 *          - Number of bytes pending in the uplink queue corresponding to the bearer or RLP_MAC ID.
 * 
 * @param is_primary
 *          - Determines whether the bearer or RLP_MAC ID is the default.
 */
typedef struct
{
  uint32_t bearer_rlp_mac_id;
  uint32_t uplink_actual_rate;
  uint32_t uplink_queue_size;
  uint8_t is_primary; 
}ThroughputInformationMac_t;


/**
 * Name:    ThroughputInformationItem_t
 *
 * Purpose: Structure used to store information about  Throughput Information Item.
 *
 * Members: results  - Structure containing the result TLV
 *
 * @param pDownlink_allowed_rate
 *          - Downlink Rate
 *          - Downlink rate per UE in kbps. The downlink rate is the sum of served and allowed rates.
 * 
 * @param throughput_info_len
 *          - Number of sets of the apn_string_len, apn_string, ip_type, tech_type, subscription, uplink_actual_rate, uplink_allowed_rate, uplink_queue_size,
 *          - throughput_signal, valid_port, data_port, ep_type, iface_id, mux_id, bearer_rlp_mac_id, uplink_actual_rate, uplink_queue_size, is_primary
 * 
 * @param apn_string_len
 *          - Number of characters in the apn_string.
 * 
 * @param apn_string
 *          - String representing the APN. Maximum length is 100 bytes.
 * 
 * @param  ip_type
 *          - IP type.
 *           - Values:
 *              - WDS_IP_TYPE_IPV4 (0) - IPv4
 *              - WDS_IP_TYPE_IPV6 (1) - IPv6
 * 
 * @param  tech_type
 *          - Technology type.
 *           - Values:
 *              - WDS_TECHNOLOGY_TYPE_3GPP (0) - 3GPP
 *              - WDS_TECHNOLOGY_TYPE_3GPP2 (1) - 3GPP2
 * 
 * @param  subscription
 *          - Subscription to which the APN is bound.
 *           - Values:
 *              - WDS_DEFAULT_SUBS (0x0000) - Default data subscription
 *              - WDS_PRIMARY_SUBS (0x0001) - Primary
 *              - WDS_SECONDARY_SUBS (0x0002) - Secondary
 *              - WDS_TERTIARY_SUBS (0x0003) - Tertiary
 *              - WDS_DONT_CARE_SUBS (0x00FF) - Default value used in the absence of explicit binding
 * 
 * @param  uplink_actual_rate
 *          - Uplink actual rate in kb per second.
 * 
 * @param  uplink_allowed_rate
 *          - Uplink allowed rate per UE in kb per second.
 * 
 * @param  uplink_queue_size
 *          - Number of bytes pending in the uplink queue.
 * 
 * @param  throughput_signalQMI_WDS_THROUGHPUT_INFO_INDity is unknown
 *          - WDS_HIGHER_THROUGHPUT_NOT_POSSIBLE (1) - Best throughput possible
 *          - WDS_HIGHER_THROUGHPUT_POSSIBLE (2) - Better throughput than current throughput is possible
 * 
 * @param  valid_port
 *          - Indicates which of the following IDs are valid:
 *          - WDS_SIO_PORT_ID (0) - Use the data_port field
 *          - WDS_END_POINT_ID (1) - Use the ep_type, iface_id, and mux_id fields
 * 
 * @param  data_port
 *          - SIO data port to which the client binds.
 * 
 * @param  ep_type
 *          - Peripheral endpoint type.
 *           - Values:
 *              - DATA_EP_TYPE_RESERVED (0x00) - Reserved
 *              - DATA_EP_TYPE_HSIC (0x01) - High-speed inter-chip interface
 *              - DATA_EP_TYPE_HSUSB (0x02) - High-speed universal serial bus
 *              - DATA_EP_TYPE_PCIE (0x03) - Peripheral component interconnect express
 *              - DATA_EP_TYPE_EMBEDDED (0x04) - Embedded
 *              - DATA_EP_TYPE_BAM_DMUX (0x05) - Bus access manager data multiplexer
 *              - All other values are reserved and are ignored.
 * 
 * @param  iface_id
 *          - Peripheral interface number.
 * 
 * @param mux_id
 *          - Mux ID of the RmNet instance where the data call is already present.
 * 
 * @param bearer_rlp_mac_id_throughput_info_len
 *          - Number of sets of the ThroughputInformationMac
 * 
 * @param  pThroughputInformationMac
 *          - See \ref ThroughputInformationMac_t.
 * 
 */
typedef struct
{
  uint8_t apn_string_len;
  char apn_string[101];
  uint32_t ip_type;
  uint32_t tech_type;
  uint32_t subscription;
  uint32_t uplink_actual_rate;
  uint32_t uplink_allowed_rate;
  uint32_t uplink_queue_size;
  uint32_t throughput_signal;
  uint32_t valid_port;
  uint16_t data_port;
  uint32_t ep_type;
  uint32_t iface_id;
  uint8_t mux_id;
  uint8_t bearer_rlp_mac_id_throughput_info_len;
  ThroughputInformationMac_t *pThroughputInformationMac;
}ThroughputInformationItem_t;

/**
 * Name:    ThroughputInformation
 *
 * Purpose: Structure used to store information about  Throughput Information TLV.
 *
 * @param throughput_info_len
 *          - Number of sets of ThroughputInformationItem
 *          - Bit to check in ParamPresenceMask - <B>0x10</B>
 * 
 * @param pThroughputInformationList
 *          - Number of characters in the apn_string.
 *          - See \ref ThroughputInformationItem_t
 *          - Bit to check in ParamPresenceMask - <B>0x10</B>
 * 
 * @param  Tlvresult - unpack Tlv Result.
 * 
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct
{
  uint8_t throughput_info_len;
  ThroughputInformationItem_t *pThroughputInformationList;
  uint16_t Tlvresult;
  swi_uint256_t  ParamPresenceMask;
}unpack_wds_ThroughputInformationInd_t;

/**
 * \ingroup wds
 * 
 * get Throuput Information Indicationunpack.
 * 
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput      response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_ThroughputInformationInd(
        uint8_t   *pResp,
        uint16_t  respLen,
        unpack_wds_ThroughputInformationInd_t *pOutput
        );

/*
 * Name:    unpack_wds_DLThroughputInformationInd_t
 *
 * Purpose: Structure used to store information about Downlink Throughput Information.
 *
 * @param pDownlink_allowed_rate
 *          - Downlink Rate
 *          - Downlink rate per UE in kbps. The downlink rate is the sum of served and allowed rates.
 *          - Bit to check in ParamPresenceMask - <B>0x10</B>
 * 
 * @param pActual_interval
 *          - Confidence Level
 *          - Level of accuracy at which the throughput information is generated on a cale of 0 through 7. 0 indicates the least
 *          - accuracy and 7 indicates the highest accuracy of reporting.
 *          - Bit to check in ParamPresenceMask - <B>0x11</B>
 * 
 * @param pIs_suspended
 *          - Suspend Flag
 *           - Values:
 *            - 0 - FALSE  Downlink throughput reporting is enabled (default)
 *            - 1 - TRUE - Downlink throughput reporting is suspended
 *          - Bit to check in ParamPresenceMask - <B>0x12</B>
 * @param  Tlvresult - unpack Tlv Result.
 * 
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
*/
typedef struct
{
  uint32_t *pDownlink_allowed_rate;
  uint8_t  *pConfidence_level;
  uint8_t  *pIs_suspended;
  uint16_t Tlvresult;
  swi_uint256_t  ParamPresenceMask;
}unpack_wds_DLThroughputInformationInd_t;

/**
 * \ingroup wds
 * 
 * Get Downlink Throughput Information Indication unpack.
 * 
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput      response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_DLThroughputInformationInd(
        uint8_t   *pResp,
        uint16_t  respLen,
        unpack_wds_DLThroughputInformationInd_t *pOutput
        );

/**
 * Name:    unpack_wds_QmiWdsQueryDLThroughputReportingStatusInd_t
 *
 * Purpose: Structure used to store information about Data Bearer Type TLV Value.
 *
 * @param pReporting_status
 *          - Reporting status.
 *            - Values:
 *              - WDS_THRPT_REPORT_ENABLED (0) - Throughput reporting enabled
 *              - WDS_THRPT_REPORT_DISABLED_NO_DATA_CALL (1) - No data call
 *              - WDS_THRPT_REPORT_DISABLED_ALL_CALLS_DORMANT (2) - All calls dormant
 *              - WDS_THRPT_REPORT_DISABLED_UNSUPPORTED_RAT (3) - Unsupported RAT
 *          - Bit to check in ParamPresenceMask - <B>0x10</B>
 * 
 * @param pActual_interval
 *          - Actual Interval
 *          - The actual interval at which throughput is generated.
 *          - Bit to check in ParamPresenceMask - <B>0x11</B>
 * 
 * @param  Tlvresult - unpack Tlv Result.
 * 
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct
{
  uint32_t  *pReporting_status;
  uint32_t  *pActual_interval;
  uint16_t Tlvresult;
  swi_uint256_t  ParamPresenceMask;
}unpack_wds_QueryDLThroughputReportingStatusInd_t;

/**
 * \ingroup wds
 * 
 * Query Downlink Throughput Reporting Status unpack.
 * 
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput      response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_QueryDLThroughputReportingStatusInd(
        uint8_t   *pResp,
        uint16_t  respLen,
        unpack_wds_QueryDLThroughputReportingStatusInd_t *pOutput
        );

/**
 * WDS SWI Set Downlink Throughput Report Period Req
 *
 *  \param  pDownlink_throughput_report_period
 *          - Downlink Throughput Reporting Period.
 *          - Period in milliseconds at which the downlink throughput is calculated.
 */
typedef struct 
{
	uint32_t *pDownlink_throughput_report_period;
}pack_wds_SetDLThroughputReportPeriod_t;

/**
 * \ingroup wds
 * 
 * 
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  reqParam request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */
int pack_wds_SLQSSetDLThroughputReportPeriod(
        pack_qmi_t  *pCtx,
        uint8_t     *pReqBuf,
        uint16_t    *pLen,
        pack_wds_SetDLThroughputReportPeriod_t *reqParam
        );

typedef unpack_result_t unpack_wds_SetDLThroughputReportPeriod_t;

/**
 * \ingroup wds
 * 
 * Set Downlink Throughput Report Period unpack
 * 
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * 
 */
int unpack_wds_SLQSSetDLThroughputReportPeriod(
        uint8_t   *pResp,
        uint16_t  respLen,
        unpack_wds_SetDLThroughputReportPeriod_t *pOutput
        );

/**
 * \ingroup wds
 * 
 * 
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */
int pack_wds_SLQSQueryDLThroughputReportingStatus(
        pack_qmi_t  *pCtx,
        uint8_t     *pReqBuf,
        uint16_t    *pLen
        );

typedef unpack_wds_QueryDLThroughputReportingStatusInd_t unpack_wds_QueryDLThroughputReportingStatus_t;

/**
 * \ingroup wds
 * 
 * Query Downlink Throughput Reporting Status unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * 
 */
int unpack_wds_SLQSQueryDLThroughputReportingStatus(
        uint8_t   *pResp,
        uint16_t  respLen,
        unpack_wds_QueryDLThroughputReportingStatus_t *pOutput
        );

/**
 * \ingroup wds
 *
 * Profile change notification pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] pEnable 0 - disable, 1 - enable
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 * @note PDN Specific: Yes
 */
int pack_wds_SLQSSWIProfileChange(
    pack_qmi_t* pCtx,
    uint8_t* pReqBuf,
    uint16_t* pLen,
    uint8_t* pEnable
);

typedef unpack_result_t unpack_wds_SLQSSWIProfileChange_t;

/**
 * \ingroup wds
 *
 * Profile change notification unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int unpack_wds_SLQSSWIProfileChange(
    uint8_t* pResp,
    uint16_t  respLen,
    unpack_wds_SLQSSWIProfileChange_t* pOutput
);

/**
 * \ingroup wds
 *
 * This structure contains the Profile Change Indication Information
 *
 *  @param  type
 *          - Type of profile, valid for TLV 0x01
 *            0x00 - 3GPP
 *            0x01 - 3GPP2
 *  @param  index
 *          - Index identifying the profile, valid for TLV 0x01
 *            1-16 (9x15 and before) or
 *            1-24 (9x30 and onwards) valid for 3GPP profile type
 *            101-106 valid for 3GPP2
 *  @param  source
 *          - Soruce of change, , valid for TLV 0x10
 *            0 - Modem (AT)
 *            1 - Host (QMI client)
 *            2 - OMADM
 *  @param  Tlvresult
 *          - TLV present flag, TURE if presented, otherwise FALSE
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct
{
    uint8_t  type;
    uint8_t  index;
    uint8_t  source;
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_wds_SLQSSWIProfileChange_ind_t;

/**
 * \ingroup wds
 *
 * get Profile Change Indication unpack.
 *
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wds_SLQSSWIProfileChange_ind(
    uint8_t* pResp,
    uint16_t  respLen,
    unpack_wds_SLQSSWIProfileChange_ind_t* pOutput
);

/**
 * \ingroup wds
 * 
 * This structure contains Network Slice Selection Assistance Information (NSSAI)
 * 
 *  @param default_nssai_info_len
 *          - Number of sets of the default_nssai_info
 *          - Bit to check in ParamPresenceMask - <B>0x01</B>
 * 
 *  @param default_nssai_info
 *          - Array of default NSSAI info
 *          - Bit to check in ParamPresenceMask - <B>0x01</B>
 * 
 *  @param pDefault_nssai_info
 *          - Default NSSAI in string format
 *          - Bit to check in ParamPresenceMask - <B>0x03</B>
 * 
 *  @For_5G
 */
typedef struct {
    uint8_t default_nssai_info_len;
    wds_swi_configured_nssai_type default_nssai_info[QMI_WDS_SWI_DEFAULT_MAX_NSSAI_COUNT];
    char default_nssai_info_str[QMI_WDS_SWI_MAX_NSSAI_STR_SIZE];
    uint16_t Tlvresult;
    swi_uint256_t ParamPresenceMask;
} unpack_wds_swi_GetDefaultNssai_t;

/**
 * \ingroup wds
 * 
 * pack function to get default Network Slice Selection Assistance Information (NSSAI) stored in UE
 *
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * 
 * @note   This API is deprecated and no longer Supported
 *
 * @For_5G
 */

int pack_wds_swi_GetDefaultNssai(
    pack_qmi_t * pCtx,
    uint8_t * pReqBuf,
    uint16_t * pLen);

/**
 * \ingroup wds
 * 
 * unpack function to get default Network Slice Selection Assistance Information (NSSAI) stored in UE
 * 
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * 
 * @note   This API is deprecated and no longer Supported
 *
 * @For_5G
 */
int unpack_wds_swi_GetDefaultNssai(
    uint8_t * pResp,
    uint16_t respLen,
    unpack_wds_swi_GetDefaultNssai_t *pOutput);

/**
 * \ingroup wds
 * 
 * This structure contains Default Network Slice Selection Assistance Information (NSSAI)
 * 
 *  @param  default_nssai_info_len
 *          - Number of sets of the default_nssai_info
 * 
 *  @param default_nssai_info
 *          - Indicates the default NSSAI
 * 
 *  @For_5G
 */
typedef struct {
    uint8_t default_nssai_info_len;
    wds_swi_configured_nssai_type default_nssai_info[QMI_WDS_SWI_DEFAULT_MAX_NSSAI_COUNT];
} pack_wds_swi_SetDefaultNssai_t;

/**
 * \ingroup wds
 * 
 *  pack function to updates the Default Network Slice Selection Assistance Information (NSSAI) stored in UE
 * 
 *  @param[in,out] pCtx qmi request context
 *  @param[out] pReqBuf qmi request buffer
 *  @param[out] pLen qmi request length
 *  @param[in] pReqParam request prarmeters
 *
 *  @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  @note   This API is deprecated and no longer Supported
 *
 *  @For_5G
 *
 */
int pack_wds_swi_SetDefaultNssai(
	pack_qmi_t * pCtx,
	uint8_t * pReqBuf,
	uint16_t * pLen,
	pack_wds_swi_SetDefaultNssai_t *pReqParam);

typedef unpack_result_t  unpack_wds_swi_SetDefaultNssai_t;

/**
 * \ingroup wds
 * 
 *  Unpack function to updates the Default Network Slice Selection Assistance Information (NSSAI) stored in UE
 * 
 *  @param[in]   pResp       qmi response from modem
 *  @param[in]   respLen     qmi response length
 *  @param[out]  pOutput     unpacked response
 *
 *  @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 *  @note   This API is deprecated and no longer Supported
 *
 *  @For_5G
 *
 */
int unpack_wds_swi_SetDefaultNssai(
	uint8_t * pResp,
	uint16_t respLen,
	unpack_wds_swi_SetDefaultNssai_t *pOutput);

/**
 * \ingroup wds
 * 
 * This structure contains profile index of Single Network Slice Selection Assistance to be read
 * 
 *  @param  profile_index	
 *          - The profile index	of the profile to be read.
 * 
 *  @For_5G
 */
typedef struct {
    uint8_t profile_index;
} pack_wds_swi_GetPrfileSnssai_t;

/**
 * \ingroup wds
 * 
 * This structure contains Single Network Slice Selection Assistance info
 * 
 *  @param  profile_snssai
 *          - Profile S-NSSAI
 * 
 *  @param profile_snssai_str
 *          - Reponse to get the profile S-NSSAI
 * 
 *  @param ssc
 *          - Session and Service Continuity (SSC)
 *          - 1: SSC Mode One (Default), 2: SSC Mode Two, 3: SSC Mode Three
 * 
 *  @param  preferred_access_type
 *          - Preferred Access Type
 *          - 0: Unspecified, 1: 3GPP (Default), 2: Non-3GPP
 * 
 *  @param  Tlvresult - unpack Tlv Result.
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *  @For_5G
 */
typedef struct {
    wds_swi_configured_nssai_type profile_snssai;
    char profile_snssai_str[QMI_WDS_SWI_MAX_SNSSAI_STR_SIZE];
    uint8_t ssc;
    uint8_t preferred_access_type;
    uint16_t Tlvresult;
    swi_uint256_t ParamPresenceMask;
} unpack_wds_swi_GetProfileSnsaai_t;

/**
 * \ingroup wds
 * 
 * pack function to get the Single Network Slice Selection Assistance Information (S-NSSAI) for a profile
 *
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] pReqParam request prarmeters
 *          - See \ref pack_wds_swi_GetPrfileSnssai_t
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * 
 * @note   This API is deprecated and no longer Supported
 *
 * @For_5G
 */
int pack_wds_swi_GetProfileSnssai(
    pack_qmi_t * pCtx,
    uint8_t * pReqBuf,
    uint16_t * pLen,
    pack_wds_swi_GetPrfileSnssai_t *pReqParam);

/**
 * \ingroup wds
 * 
 * unpack function to get the Single Network Slice Selection Assistance Information (S-NSSAI) for a profile
 * 
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * 
 * @note   This API is deprecated and no longer Supported
 *
 * @For_5G
 */

int unpack_wds_swi_GetProfileSnssai(
    uint8_t * pResp,
    uint16_t respLen,
    unpack_wds_swi_GetProfileSnsaai_t *pOutput);

/**
 * \ingroup wds
 * 
 * This structure contains profile index of Single Network Slice Selection Assistance to be cleared
 * 
 *  @param  profile_index	
 *          - The profile_index	of the profile to be cleared.
 * 
 *  @For_5G
 */
typedef struct {
    uint8_t profile_index;
} pack_wds_swi_ClearProfileSnssai_t;

/**
 * \ingroup wds
 * 
 *  Pack function to clear the Single Network Slice Selection Assistance Information (S-NSSAI) settings for a profile
 * 
 *  @param[in,out] pCtx qmi request context
 *  @param[out] pReqBuf qmi request buffer
 *  @param[out] pLen qmi request length
 *  @param[in] pReqParam request prarmeters
 *
 *  @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 *  @note   This API is deprecated and no longer Supported
 *
 *  @For_5G
 *
 */
int pack_wds_swi_ClearProfileSnssai(
	pack_qmi_t * pCtx,
	uint8_t * pReqBuf,
	uint16_t * pLen,
	pack_wds_swi_ClearProfileSnssai_t *pReqParam);

typedef unpack_result_t  unpack_wds_swi_ClearProfileSnssai_t;

/**
 * \ingroup wds
 * 
 *  Unpack function to clear the Single Network Slice Selection Assistance Information (S-NSSAI) settings for a profile
 * 
 *  @param[in]   pResp       qmi response from modem
 *  @param[in]   respLen     qmi response length
 *  @param[out]  pOutput unpacked response
 *
 *  @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 *  @note   This API is deprecated and no longer Supported
 *
 *  @For_5G
 *
 */
int unpack_wds_swi_ClearProfileSnssai(
	uint8_t * pResp,
	uint16_t respLen,
	unpack_wds_swi_ClearProfileSnssai_t *pOutput);

/**
 * \ingroup wds
 * 
 * This structure contains Create WDS SWI Profile Information
 * 
 *  @param profile_type_index
 *          - Profile type and index inforrmation
 *          - \ref wds_swi_profile_type_index 
 * 
 *  @param pApn
 *          - String representing the Access Point Name
 *          - maximum length allowed is 100 bytes
 *          - QMI_ERR_ARG_TOO_LONG will be returned if the APN
 *            name is too long.
 * 
 *  @param  pS_Nassai (optional)
 *          - Profile S-NSSAI
 *          - \ref wds_swi_configured_nssai_type for more information
 *
 *  @param pSsc (optional)
 *          - Session and Service Continuity (SSC)
 *           - values:
 *              -1: SSC Mode One (Default)
 *              -2: SSC Mode Two,
 *              -3: SSC Mode Three
 *
 *  @param pPreferred_access_type (optional)
 *          - Preferred Access Type
 *           - values:
 *              - 0: Unspecified
 *              - 1: 3GPP (Default)
 *              - 2: Non-3GPP
 *  @For_5G
 */
typedef struct {
    wds_swi_profile_type_index profile_type_index;
    char Apn[MAX_APN_STRING];
    wds_swi_configured_nssai_type *pS_Nassai;
    uint8_t *pSsc;
    uint8_t *pPreferred_access_type;
} pack_wds_swi_CreateProfile_t;

/**
 * \ingroup wds
 * 
 *  pack function to updates the Default Network Slice Selection Assistance Information (NSSAI) stored in UE
 * 
 *  @param[in,out] pCtx qmi request context
 *  @param[out] pReqBuf qmi request buffer
 *  @param[out] pLen qmi request length
 *  @param[in] pReqParam request prarmeters
 *
 *  @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  @note   This API is deprecated and no longer Supported
 *
 *  @For_5G
 *
 */
int pack_wds_swi_CreateProfile(
	pack_qmi_t * pCtx,
	uint8_t * pReqBuf,
	uint16_t * pLen,
	pack_wds_swi_CreateProfile_t *pReqParam);

/**
 * \ingroup wds
 * 
 * This structure contains Single Network Slice Selection Assistance info
 * 
 *  @param  profile_type_index
 *          - Profile type and profile index
 *          - \ref wds_swi_profile_type_index
 * 
 * @param  Tlvresult - unpack Tlv Result.
 * 
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *  @For_5G
 */
typedef struct {
    wds_swi_profile_type_index profile_type_index;
    uint16_t Tlvresult;
    swi_uint256_t ParamPresenceMask;
} unpack_wds_swi_CreateProfile_t;


/**
 * \ingroup wds
 * 
 *  Unpack function to updates the Default Network Slice Selection Assistance Information (NSSAI) stored in UE
 * 
 *  @param[in]   pResp       qmi response from modem
 *  @param[in]   respLen     qmi response length
 *  @param[out]  pOutput     unpacked response
 *
 *  @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 *  @note   This API is deprecated and no longer Supported
 *
 *  @For_5G
 *
 */
int unpack_wds_swi_CreateProfile(
	uint8_t * pResp,
	uint16_t respLen,
	unpack_wds_swi_CreateProfile_t *pOutput);


#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif

