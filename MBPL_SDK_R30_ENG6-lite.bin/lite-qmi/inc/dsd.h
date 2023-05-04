/**
 * \ingroup liteqmi
 * \ingroup dsd
 * \file dsd.h
 *
 * \section     TableDSDSOMask SO Mask
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
 * \section     TableDSDRatMask RAT Mask
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
#ifndef __LITEQMI_DSD_H__
#define __LITEQMI_DSD_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include <stdint.h>

#define MAX_APN_STRING 100
#define MAX_AVAIL_SYSTEM_INFO 255

/**
 * \ingroup dsd
 * 
 * This structure contains the Dsd System Information
 *  - Parameter values default to their data type's maximum unsigned value
 *    unless explicitly stated otherwise.
 *
 *  \param  technology
 *          - Technology type. Values:
 *              - DSD_SYS_NETWORK_3GPP (0) - 3GPP
 *              - DSD_SYS_NETWORK_3GPP2 (1) - 3GPP2
 *              - DSD_SYS_NETWORK_WLAN (2) - WLAN
 *  \param  rat_value
 *          - RAT value. Values:
 *              - DSD_SYS_RAT_EX_NULL_BEARER(0x0) - NULL bearer
 *              - DSD_SYS_RAT_EX_3GPP_WCDMA(0x1) - 3GPP WCDMA
 *              - DSD_SYS_RAT_EX_3GPP_GERAN(0x2) - 3GPP GERAN
 *              - DSD_SYS_RAT_EX_3GPP_LTE(0x3) - 3GPP LTE
 *              - DSD_SYS_RAT_EX_3GPP_TDSCDMA(0x4) - 3GPP TDSCDMA
 *              - DSD_SYS_RAT_EX_3GPP_WLAN(0x5) - 3GPP WLAN
 *              - DSD_SYS_RAT_EX_3GPP_5G (0x6)- 3GPP 5G
 *              - DSD_SYS_RAT_EX_3GPP_MAX(0x64) - 3GPP maximum
 *              - DSD_SYS_RAT_EX_3GPP2_ 1X(0x65) - 3GPP2 1X
 *              - DSD_SYS_RAT_EX_3GPP2_ HRPD(0x66) - 3GPP2 HRPD
 *              - DSD_SYS_RAT_EX_3GPP2_ EHRPD(0x67) - 3GPP2 EHRPD
 *              - DSD_SYS_RAT_EX_3GPP2_ WLAN(0x68) - 3GPP2 WLAN
 *              - DSD_SYS_RAT_EX_3GPP2_ MAX(0xC8) - 3GPP2 maximum
 *              - DSD_SYS_RAT_EX_WLAN (0xC9) - WLAN
 *              - DSD_SYS_RAT_EX_WLAN_MAX(0x12C) - WLAN maximum
 *  \param  so_mask
 *          - Service Option (SO) mask to indicate the service option or type of application.
 *          - An SO mask value of zero indicates that this field is ignored. 
 * 			- Values:
 *             	- 0x00 - SO Mask Unspecified 
 *            	- 3GPP SO Mask:
 *             		- 0x01 - WCDMA
 *             		- 0x02 - HSDPA
 *             		- 0x04 - HSUPA
 *             		- 0x08 - HSDPAPLUS
 *             		- 0x10 - DC HSDPAPLUS
 *             		- 0x20 - 64 QAM
 *             		- 0x40 - HSPA
 *             		- 0x80 - GPRS
 *             		- 0x100 - EDGE
 *             		- 0x200 - GSM
 *             		- 0x400 - S2B
 *             		- 0x800 - LTE Limited Service, , 3GPP Limited Service
 *             		- 0x1000 - LTE FDD, 3GPP FDD
 *             		- 0x2000 - LTE TDD
 *             		- 0x4000 - TDSCDMA
 *             		- 0x8000 - DC HSUPA
 *             		- 0x10000 - LTE CA DL
 *             		- 0x20000 - LTE CA UL
 *             		- 0x40000 - S2B Limited Service
 *             		- 0x80000 - 4.5G
 *             		- 0x100000 - 4.5G+ 
 *            	- 3GPP2 SO Mask:
 *             		- 0x0001000000 - 1X IS95
 *             		- 0x0002000000 - 1X IS2000
 *             		- 0x0004000000 - 1X IS2000 REL A
 *             		- 0x0008000000 - HDR REV0 DPA
 *             		- 0x0010000000 - HDR REVA DPA
 *             		- 0x0020000000 - HDR REVB DPA
 *             		- 0x0040000000 - HDR REVA MPA
 *             		- 0x0080000000 - HDR REVB MPA
 *             		- 0x0100000000 - HDR REVA EMPA
 *             		- 0x0200000000 - HDR REVB EMPA
 *             		- 0x0400000000 - HDR REVB MMPA
 *             		- 0x0800000000 - HDR EVDO FMC
 *             		- 0x1000000000 - 1X Circuit Switched 
 *            	- 5G SO Mask:
 *             		- 0x10000000000 - 5G TDD
 *             		- 0x20000000000 - 5G SUB6
 *             		- 0x40000000000 - 5G MMWAVE
 *             		- 0x80000000000 - 5G NSA
 *             		- 0x100000000000 - 5G SA
 * @For_5G
 */
typedef struct
{
	uint32_t    technology;
	uint32_t    rat_value;
	uint64_t 	so_mask;
}DsdSystemInfo_t;

/**
 * \ingroup dsd
 * 
 * This structure contains the APN Current and Recommended Preferred System Info
 *  - Parameter values default to their data type's maximum unsigned value
 *    unless explicitly stated otherwise.
 *
 *  \param  apn_name_len
 *          - apn name length
 *  \param  apn_name
 *          - apn name
 * 
 *  \param  apn_avail_sys_len
 *          - length APN available system info
 *
 *  \param  dsdGlobalAvailableSystem
 *          - Array of DSD Global available system info  value
 * * 
 * @For_5G
 */
typedef struct
{
	uint8_t   	apn_name_len;
    char   		apn_name[MAX_APN_STRING];
	uint8_t   	apn_avail_sys_len;
	DsdSystemInfo_t dsdGlobalAvailableSystem[MAX_AVAIL_SYSTEM_INFO];
}DsdApnAvailableSystemInfo_t;

/**
 * \ingroup dsd
 * 
 * This structure contains the APN Current and Recommended Preferred System Info
 *  - Parameter values default to their data type's maximum unsigned value
 *    unless explicitly stated otherwise.
 *
 *  \param  dsdCurrentPreferdSystem
 *          - Current DSD current prefered system info
 *
 *  \param  dsdRecommendedPreferdSystem
 *          - Recommended DSD current prefered system info
 *
 * @For_5G
 */
typedef struct
{
	DsdSystemInfo_t dsdCurrentPreferdSystem;
	DsdSystemInfo_t dsdRecommendedPreferdSystem;
}DsdApnCurRecAvailableSystemInfo_t;

/**
 * \ingroup dsd
 * 
 * This structure contains the APN Current and Recommended Preferred System Info
 *  - Parameter values default to their data type's maximum unsigned value
 *    unless explicitly stated otherwise.
 *
 *  \param  apn_name_len
 *          - apn name length
 *  \param  apn_name
 *          - apn name
 *
 *  \param  dsdApnCurRecPreferredSystemInfo
 *          - Array of DSD APN Current and Recommended Preferred System Info
 * * 
 * @For_5G
 */
typedef struct
{
	uint8_t apn_name_len;
    char   	apn_name[MAX_APN_STRING];
	DsdApnCurRecAvailableSystemInfo_t dsdApnCurRecPreferredSystemInfo;
}DsdApnCurRecPreferredSystemInfo_t;

/**
 * \ingroup dsd
 * 
 * This structure contains the Null Bearer reason enumeration
 *
 *  \param  null_bearer_reason
 *          - Null Bearer reason for global current preferred system.
 * 			  - Values : 
 *              - DSD_NULL_BEARER_REASON_UNSPECIFIED (0x0000000000000000)
 *              - DSD_NULL_BEARER_REASON_CSFB (0x0000000000000001)
 *              - DSD_NULL_BEARER_REASON_OOS (0x0000000000000002) 
 *              - DSD_NULL_BEARER_REASON_LIMITED_SRVC (0x0000000000000004)
 *              - DSD_NULL_BEARER_REASON_VOICE_ON_SAME_SUB (0x0000000000000008)
 *              - DSD_NULL_BEARER_REASON_VOICE_ON_OTHER_SUB (0x0000000000000010)
 *              - DSD_NULL_BEARER_REASON_SRVCC (0x0000000000000020)
 *              - DSD_NULL_BEARER_REASON_CS_ONLY (0x0000000000000040)
 *              - DSD_NULL_BEARER_REASON_ATTACH_PENDING (0x0000000000000080) 
 * @For_5G
 */
typedef struct
{
	uint64_t   null_bearer_reason;
}DsdNullBearerReason_t;

/**
 * \ingroup dsd
 * 
 * Get System Status pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * @For_5G
 */
int pack_dsd_SLQSGetSystemStatus(
        pack_qmi_t *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen
        );

/**
 * \ingroup dsd
 * 
 * This structure contains the DSD Get System Status response parameters.
 *
 * \sa qaGobiApiDsd.h for parameter descriptions
 * 
 *  @param  Avail_sys_len
 *          - count of DSD Available System instances.
 *  @param  Apn_avail_sys_info_len
 *          - count of Dsd APN Available System Info instances.
 *  @param  Apn_pref_sys_len
 *          - count of DSD APN Current and Recommended Global Preferred System instances.
 * 
 *  @param  pDsdAvailableSystem
 *          - Available Systems Array of all available systems.
 * 
 *  @param  pDsdApnAvailableSystemInfo
 *          - DSD APN Available System Info
 * 
 *  @param  pDsdCurRecGlobalPrefSystem
 *          - Current and Recommended APN Available System Info
 * 
 *  @param pDsdApnCurRecGlobalPrefSystem
 *          - Current and Recommended Global Preferred System Info.
 * 
 *  @param pDsdNullBearerReason
 *          - Null Bearer reason.
 * 
 * @param  Tlvresult - unpack Tlv Result.
 * 
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 * @FOR_5G
 */
typedef struct
{
   	uint8_t   Avail_sys_len;           
	uint8_t   Apn_avail_sys_info_len; 
    uint8_t   Apn_pref_sys_len;

    DsdSystemInfo_t        	 			*pDsdAvailableSystem;
    DsdApnAvailableSystemInfo_t			*pDsdApnAvailableSystemInfo;
    DsdApnCurRecAvailableSystemInfo_t  	*pDsdCurRecGlobalPrefSystem;
    DsdApnCurRecPreferredSystemInfo_t  	*pDsdApnCurRecGlobalPrefSystem;
    DsdNullBearerReason_t       		*pDsdNullBearerReason;

    uint16_t Tlvresult;
    swi_uint256_t ParamPresenceMask;

}unpack_dsd_SLQSGetSystemStatus_t;

/**
 * \ingroup dsd
 * 
 * Get System Status unpack
 * @param[in]   pResp       qmi response
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * @For_5G
 */
int unpack_dsd_SLQSGetSystemStatus(
	uint8_t *pResp,
	uint16_t respLen,
	unpack_dsd_SLQSGetSystemStatus_t *pOutput);

/**
 * \ingroup dsd
 * 
 * This structure contains the Global UI Information Global UIinformation.
 *
 *  \param  dsdAvailableSystem
 *          - \ref DsdSystemInfo_t
 * 
 *  \param  ui_mask
 *          - UI mask to indicate the UI icon Values:
 * 				- QMI_DSD_UI_MASK_UNSPECIFIED (0x0000000000000000) - Unspecified
 * 				- QMI_DSD_UI_MASK_3GPP_5G_BASIC (0x0000000000000001) - 5G basic
 * 				- QMI_DSD_UI_MASK_3GPP_5G_UWB (0x0000000000000002) - 5G ultrawide band
 * 				- QMI_DSD_UI_MASK_3GPP_SIB2_PLMN_R15 (0x0000000000000004) - SIB2 PLMN R15 
 * 				- QMI_DSD_UI_MASK_3GPP_SIB2_ULI (0x0000000000000008) - SIB2 upper layer indication
 * 				- QMI_DSD_UI_MASK_3GPP_RESTRICT_DCNR (0x0000000000000010) - Restrict decoded channel number register
 * @FOR_5G
 */
typedef struct
{
	DsdSystemInfo_t  dsdAvailableSystem;
	uint64_t	ui_mask;		
}DsdGlobalUIInformation_t;

/**
 * \ingroup dsd
 * 
 * This structure contains the APN UI Information Array of UI information
 *
 *  \param  apn_name_len
 *          - apn name length
 *  \param  apn_name
 *          - apn name
 * 
 * 	\param  apn_type_mask
 * 			- APN Type Mask Values
 * 				- QMI_DSD_APN_TYPE_MASK_UNSPECIFIED (0x0000000000000000)
 * 				- QMI_DSD_APN_TYPE_MASK_DEFAULT (0x0000000000000001) -APN type for Default/Internet traffic
 * 				- QMI_DSD_APN_TYPE_MASK_ IMS (0x0000000000000002) - APN type for IP Multimedia Subsystem
 * 				- QMI_DSD_APN_TYPE_MASK_MMS (0x0000000000000004) - APN type for Multimedia Messaging Service
 * 				- QMI_DSD_APN_TYPE_MASK_DUN (0x0000000000000008) - APN type for Dial Up Network
 * 				- QMI_DSD_APN_TYPE_MASK_SUPL (0x0000000000000010) - APN type for Secure User Plane Location
 * 				- QMI_DSD_APN_TYPE_MASK_HIPRI (0x0000000000000020) - APN type for High Priority Mobile Data
 * 				- QMI_DSD_APN_TYPE_MASK_FOTA (0x0000000000000040) - APN type for over the air administration
 * 				- QMI_DSD_APN_TYPE_MASK_CBS (0x0000000000000080) - APN type for Carrier Branded Services
 * 				- QMI_DSD_APN_TYPE_MASK_ IA (0x0000000000000100) - APN type for Initial Attach
 * 				- QMI_DSD_APN_TYPE_MASK_EMERGENCY (0x0000000000000200) - APN type for emergency
 * 
 *  \param  technology
 *          - Technology type
 *
 *  \param  rat_value
 *          - RAT value
 *
 *  \param  so_mask
 *          - Service Option (SO) mask to indicate the service option or type of application.
 * 
 *  \param  ui_mask
 *
 * 	\param	is_internet
 * 			Values: FALSE - APN is not for internet service. TRUE - APN is for internet service. 
 * @For_5G
 */
typedef struct
{
	uint8_t    	apn_name_len;
    char      	apn_name[MAX_APN_STRING];
	uint64_t    apn_type_mask;
	uint32_t   	technology;
	uint32_t  	rat_value;
	uint64_t 	so_mask;
	uint64_t	ui_mask;
	uint8_t		is_internet;
} DsdUIApnAvailableSystemInfo_t;

/**
 * \ingroup dsd
 * 
 * Get UI Information pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * @For_5G
 */
int pack_dsd_SLQSGetUIInfo(
        pack_qmi_t *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen
        );

/**
 * \ingroup dsd
 * 
 * This structure contains the DSD APN UI Information. Array of UI information per APN.
 *
 *  @param  Apn_info_len
 *          - Number of setsof the DsdUIApnAvailableSystemInfo_t instances
 * 
 *  @param  pDsdGlobalUIInformation
 *          - UI information
 * 			-\ref DsdGlobalUIInformation_t
 * 
 *  @param  pDsdApnAvailableSystemInfo
 *          - APN UI Information. Array of UI information per APN
 * 			- \ref DsdUIApnAvailableSystemInfo_t
 *  
 *  @param  pDsdNullBearerReason
 * 			- Null Bearer reason
 *          - \ref DsdNullBearerReason_t
 * 
 * @param  Tlvresult - unpack Tlv Result.
 * 
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 * @FOR_5G
 */
typedef struct
{
	uint8_t   Apn_info_len;

    DsdGlobalUIInformation_t 	  *pDsdGlobalUIInformation;
    DsdUIApnAvailableSystemInfo_t *pDsdApnAvailableSystemInfo;
    DsdNullBearerReason_t         *pDsdNullBearerReason;

    uint16_t Tlvresult;
    swi_uint256_t     ParamPresenceMask;
}unpack_dsd_SLQSGetDsdUIInfo_t;

/**
 * \ingroup dsd
 * 
 * Get UI Information unpack
 * 
 * @param[in]   pResp       qmi response
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * @For_5G
 */
int unpack_dsd_SLQSGetUIInfo(
	uint8_t *pResp,
	uint16_t respLen,
	unpack_dsd_SLQSGetDsdUIInfo_t *pOutput);

/**
 * \ingroup dsd
 * 
 * This structure contains SYSTEM Status Change Req info
 *  - Parameter values default to their data type's maximum unsigned value
 *    unless explicitly stated otherwise.
 *
 *  @param  pLimit_so_mask_change_ind
 *          - If this TLV is provided in the request message, the indication is generated only
 * 			  if the rat_value changes from the last indication.
 *  @param  pReport_data_system_status_changes
 *          - Register/Deregister for Data System Status Changes
 * 			  Values: 0 - Do not report 1 - Report data system status change(default).
 *  @param  pReport_pref_tech_change_only
 *          - Report only Preferred technology changes
 * 			  If this TLV is provided and set to true in the request message, the indication is
 * 			  generated only if the Preferred Technology value (i.e. only technology field of the 
 * 			  Preferred System) changes from the last indication.
 *  @param  pReport_null_bearer_reason
 *          - Report NULL Bearer Reason
 * 			  Report NULL bearer reason with global preferred system status.
 * @For_5G
 */
typedef struct
{
	uint8_t  *pLimit_so_mask_change_ind;
	uint8_t  *pReport_data_system_status_changes;
	uint8_t  *pReport_pref_tech_change_only;
	uint8_t  *pReport_null_bearer_reason;
}pack_dsd_system_status_changes_t;

/**
 * \ingroup dsd
 * 
 * System Status Changes flag pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  pSystemStatusChange indications to register for.
 *             - 0x80 to 0x88
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * @For_5G
 */
int pack_dsd_SystemStatusChange(
	pack_qmi_t  *pCtx,
	uint8_t   *pReqBuf,
	uint16_t  *pLen,
	pack_dsd_system_status_changes_t *pSystemStatusChange);

typedef unpack_result_t unpack_dsd_SystemStatusChange_t;

/**
 * \ingroup dsd
 * 
 * Unpack System Status Change response.
 * @param[in]   pResp       qmi response
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * @For_5G
 */
int unpack_dsd_SystemStatusChange(
	uint8_t   *pResp,
	uint16_t  respLen,
	unpack_dsd_SystemStatusChange_t *pOutput
);

/**
 * \ingroup dsd
 * 
 * This structure contains the DSD Register ui changes request parameters.
 * 
 *  @param  pReport_ui_changes
 *          - Register/Deregister for UI information changes.
 * 				Values:  0 - Do not report 1 - Report UI change (default).
 *  @param  pSuppress_so_change
 *          - Suppress SO mask. Values:
 * 				- 0 - Do not suppress only SO mask changes (Default).
 * 				- 1 - Suppress SO mask change. The indication is not generated only if SO mask changes from
 * 					  the last indication. Ex: Indiation is sent when technology, rat_value, or ui_mask change 
 * 					  from the last indication.
 *  @param PSuppress_null_bearer_reason
 *          - Suppress null bearer reason. 
 * 				Values:
 * 				- 0 - Do not suppress only null bearer reason changes (Default).
 * 				- 1 - Suppress null bearer reason change. The indication is not generated only if null
 * 					  bearer reason changes from the last indication.
 * 
 * @FOR_5G
 */
typedef struct
{
	uint8_t *pReport_ui_changes;
	uint8_t *pSuppress_so_change;
	uint8_t *pSuppress_null_bearer_reason;

}pack_dsd_register_ui_info_changes_t;

/**
 * \ingroup dsd
 * 
 * System Status Changes flag pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in]  pRegisterUIInfoChange indications to register for.
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * @For_5G
 */
int pack_dsd_RegisterUIInfoChange(
	pack_qmi_t  *pCtx,
	uint8_t   *pReqBuf,
	uint16_t  *pLen,
	pack_dsd_register_ui_info_changes_t *pRegisterUIInfoChange);

typedef unpack_result_t unpack_dsd_RegisterUIInfoChange_t;

/**
 * \ingroup dsd
 * 
 * Register UI Information Change unpack
 * 
 * @param[in]   pResp       qmi response
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * @For_5G
 */
int unpack_dsd_RegisterUIInfoChange(
	uint8_t   *pResp,
	uint16_t  respLen,
	unpack_dsd_RegisterUIInfoChange_t *pOutput
);

/**
 * \ingroup dsd
 * 
 * This structure contains the DSD System Status Change Indication response parameters.
 *
 * \sa qaGobiApiDsd.h for parameter descriptions
 * 
 *  @param  Tlvresult
 *          - Unpack Result
 *  @param  Avail_sys_len
 *          - count of DSD Available System instances.
 *  @param  Apn_avail_sys_info_len
 *          - count of Dsd APN Available System Info instances.
 *  @param  Apn_pref_sys_len
 *          - count of DSD APN Current and Recommended Global Preferred System instances.
 * 
 *  @param  pDsdAvailableSystem
 *          - Available Systems Array of all available systems.
 * 
 *  @param  pDsdApnAvailableSystemInfo
 *          - DSD APN Available System Info
 * 
 *  @param  pDsdCurRecGlobalPrefSystem
 *          - Current and Recommended APN Available System Info
 * 
 *  @param pDsdApnCurRecGlobalPrefSystem
 *          - Current and Recommended Global Preferred System Info.
 * 
 *  @param pDsdNullBearerReason
 *          - Null Bearer reason.
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 * @FOR_5G
 */

typedef struct
{
	uint16_t  Tlvresult;
   	uint8_t   Avail_sys_len;           
	uint8_t   Apn_avail_sys_info_len; 
    uint8_t   Apn_pref_sys_len;
    uint8_t   CurRecGlobalPrefTlvPresent;
    uint8_t   NullBearerReasonTlvPresent;

    DsdSystemInfo_t        	 			*pDsdAvailableSystem;
    DsdApnAvailableSystemInfo_t			*pDsdApnAvailableSystemInfo;
    DsdApnCurRecAvailableSystemInfo_t  	*pDsdCurRecGlobalPrefSystem;
    DsdApnCurRecPreferredSystemInfo_t  	*pDsdApnCurRecGlobalPrefSystem;
    DsdNullBearerReason_t       		*pDsdNullBearerReason;

    swi_uint256_t ParamPresenceMask;
    
}unpack_dsd_SLQSSystemStatusChange_Ind_t;

/**
 * \ingroup dsd
 * 
 * System Status Change Indication unpack
 * 
 * @param[in]   pResp       qmi response
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * @For_5G
 */
int unpack_dsd_SLQSSystemStatusChangeInd(
	uint8_t *pResp,
	uint16_t respLen,
	unpack_dsd_SLQSSystemStatusChange_Ind_t *pOutput);

/**
 * \ingroup dsd
 * 
 * This structure contains the DSD Get UI Info indication parameters.
 *
 * \sa qaGobiApiDsd.h for parameter descriptions
 * 
 *  @param  Tlvresult
 *          - Unpack Result
 *  @param  Apn_info_len
 *          - count of DsdApnAvailableSystemInfo instances.
 *  @param  pDsdGlobalUIInformation
 *          - APN Available Sysyem Information.
 *  @param  pDsdApnAvailableSystemInfo
 *          - APN Available System Info.
 *  @param pDsdNullBearerReason
 *          - Null Bearer reason.
 *  @param results
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 * @FOR_5G
 */
typedef struct
{
    /* Every response message must have a results structure */
	uint16_t  Tlvresult;
	uint8_t   Apn_info_len;
	uint8_t   GlobalUIInfoTlvPresent;
	uint8_t   NullBearerReasonTlvPresent;
	
    DsdGlobalUIInformation_t      *pDsdGlobalUIInformation;
    DsdUIApnAvailableSystemInfo_t *pDsdApnAvailableSystemInfo;
    DsdNullBearerReason_t         *pDsdNullBearerReason;

    swi_uint256_t ParamPresenceMask;
}unpack_dsd_SLQSUIInfo_Ind_t;

/**
 * \ingroup dsd
 * 
 * UI Information Change Indication unpack
 * @param[in]   pResp       qmi response
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * @For_5G
 */
int unpack_dsd_SLQSUIInfoChangeInd(
	uint8_t *pResp,
	uint16_t respLen,
	unpack_dsd_SLQSUIInfo_Ind_t *pOutput);

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif

