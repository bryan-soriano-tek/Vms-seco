/**
 * \ingroup liteqmi
 * \ingroup dms
 * \file swidms.h
 */
#ifndef __LITEQMI_SWIDMS_H__
#define __LITEQMI_SWIDMS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include <stdint.h>

#define QMI_SWI_DMS_AUTO_SIM_CONFIG_LEN_MAX   28
#define QMI_SWI_DMS_AUTO_SIM_FWVER_LEN_MAX    16
#define QMI_SWI_DMS_AUTO_SIM_KEY_LENGTH_MAX   7
#define QMI_SWI_DMS_AUTO_SIM_CARRIER_NAME_MAX 256
#define QMI_SWI_DMS_AUTO_SIM_LIST_COUNT_MAX   200

/**
 * \ingroup dms
 * 
 * pack function to get usb net numbers for QMAP configuration
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */

int pack_swidms_SLQSSwiDmsGetUsbNetNum(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen);

/**
 * \ingroup dms
 * 
 * This structure contains usb net numbers to get from remote 
 * endpoint for QMAP configuration
 *
 *  @param  usbNetNum
 *          - value of usb net numbers on the device
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param  ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct {
    uint8_t                usbNetNum;
    swi_uint256_t          ParamPresenceMask;
}unpack_swidms_SLQSSwiDmsGetUsbNetNum_t;

/**
 * \ingroup dms
 * 
 * unpack function to get usb net numbers for QMAP configuration
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */

int unpack_swidms_SLQSSwiDmsGetUsbNetNum(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_swidms_SLQSSwiDmsGetUsbNetNum_t *pOutput);

/**
 * \ingroup dms
 * 
 * This structure contains usb net number to set on remote endpoint for QMAP configuration
 *
 *  @param  nUsbNetNum
 *          - value of usb net numbers to set for the device
 *          - range is 0-8
 */
typedef struct {
    uint8_t                nUsbNetNum;
}pack_swidms_SLQSSwiDmsSetUsbNetNum_t;

typedef unpack_result_t  unpack_swidms_SLQSSwiDmsSetUsbNetNum_t;

/**
 * \ingroup dms
 * 
 * pack function to set usb net numbers for QMAP configuration
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] pReqParam request params
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */

int pack_swidms_SLQSSwiDmsSetUsbNetNum(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_swidms_SLQSSwiDmsSetUsbNetNum_t *pReqParam);

/**
 * \ingroup dms
 * 
 * unpack function to set usb net numbers for QMAP configuration
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */

int unpack_swidms_SLQSSwiDmsSetUsbNetNum(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_swidms_SLQSSwiDmsSetUsbNetNum_t *pOutput
    );

/**
 * \ingroup dms
 * 
 *  This structure contains the Set MTU  request parameter.
 *
 *  @param  MTUSize
 *          - Set MTU size
 *          - MTU Values
 *            - 0 - use default value
 *            - 576 to 2000 - other values required by carrier.
 *            - Set the same MTU for all RAT/interfaces.
 *            - New MTU size effective after modem reboot.
 *
 */
typedef struct{
    uint16_t MTUSize;
}pack_swidms_SLQSSwiDmsSetMTU_t;

/**
 * \ingroup dms
 * 
 *  This structure is used to store unpack_swidms_SLQSSwiDmsSetMTU_t parameters.
 *
 *  @param  Tlvresult
 *           - unpack Tlv result
 *           - Bit to check in ParamPresenceMask - <B>2</B>
 *
 *  @param  ParamPresenceMask
 *           - bitmask representation to indicate valid parameters.
 *
 */
typedef struct{
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_swidms_SLQSSwiDmsSetMTU_t;

/**
 * \ingroup dms
 * 
 * Sets the preferred MTU size for 3GPP, HRPD, EHRPD Interfaces pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_swidms_SLQSSwiDmsSetMTU(
    pack_qmi_t  *pCtx,
    uint8_t     *pReqBuf,
    uint16_t    *pLen,
    pack_swidms_SLQSSwiDmsSetMTU_t *reqArg
);

/**
 * \ingroup dms
 * 
 * Sets preferred MTU size for 3GPP, HRPD, EHRPD Interfaces unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_swidms_SLQSSwiDmsSetMTU(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_swidms_SLQSSwiDmsSetMTU_t *pOutput
);

/**
 * \ingroup dms
 * 
 * This structure contains the parameters for 3GPP MTU Size.
 *
 *  @param  MTUSize3gpp
 *          3GPP MTU size
 *          - Size of 3GPP MTU
 */
typedef struct
{
    uint16_t  MTUSize3gpp;
} swidms_mtuSize3gppTlv;

/**
 * \ingroup dms
 * 
 * This structure contains the parameters for HRPD MTU Size.
 *
 *  @param  hrpdMTUSize
 *          HRPD size
 *          - Size of HRPD MTU
 */
typedef struct
{
    uint16_t  hrpdMTUSize;
} swidms_hrpdMTUSizeTlv;

/**
 * \ingroup dms
 * 
 * This structure contains the parameters for EHRPD MTU Size.
 *
 *  @param  ehrpdMTUSize
 *          EHRPD size
 *          - Size of EHRPD MTU
 */
typedef struct
{
    uint16_t  ehrpdMTUSize;
} swidms_ehrpdMTUSizeTlv;

/**
 * \ingroup dms
 * 
 * This structure contains the parameters for USB MTU Size
 *
 *  @param  UsbMTUSize
 *          USB MTU size
 *          - Size of USB MTU
 */
typedef struct
{
    uint16_t  UsbMTUSize;
} swidms_usbMTUSizeTlv;

/**
 * \ingroup dms
 * 
 *  This structure contains the Get MTU Response parameter.
 *
 *  @param  pMTUSize3gpp [Optional]
 *          - See @ref swidms_mtuSize3gppTlv for more information
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  @param  pHrpdMTUSize [Optional]
 *          - See @ref swidms_hrpdMTUSizeTlv for more information
 *          - Bit to check in ParamPresenceMask - <B>17</B>
 *
 *  @param  pEhrpdMTUSize [Optional]
 *          - See @ref swidms_ehrpdMTUSizeTlv for more information
 *          - Bit to check in ParamPresenceMask - <B>18</B>
 *
 *  @param  pUsbMTUSize [Optional]
 *          - See @ref swidms_usbMTUSizeTlv for more information
 *          - Bit to check in ParamPresenceMask - <B>19</B>
 *
 *  @param  ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct
{
    swidms_mtuSize3gppTlv         *pMTUSize3gpp;
    swidms_hrpdMTUSizeTlv         *pHrpdMTUSize;
    swidms_ehrpdMTUSizeTlv        *pEhrpdMTUSize;
    swidms_usbMTUSizeTlv          *pUsbMTUSize;
    swi_uint256_t                 ParamPresenceMask;
 } unpack_swidms_SLQSSwiDmsGetMTU_t;

/**
 * \ingroup dms
 * 
 * Get the preferred MTU Size of the 3GPP, HRPD, EHRPD and USB descriptor Interfaces pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_swidms_SLQSSwiDmsGetMTU(
        pack_qmi_t  *pCtx,
        uint8_t     *pReqBuf,
        uint16_t    *pLen
        );

/**
 * \ingroup dms
 * 
 * Get the MTU Size of the 3GPP, HRPD, EHRPD and USB descriptor Interfaces unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_swidms_SLQSSwiDmsGetMTU(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_swidms_SLQSSwiDmsGetMTU_t *pOutput
        );

/**
 * \ingroup dms
 * 
 * This structure contains the parameters for host usb interface composition
 *
 *  @param  CurrentCfgType
 *          - Current configure type, see values below:
 *            - 1 - MBIM
 *            - 2 - USBIF + PCIE
 *            - 3 - RMNET
 *            - 4 - RNDIS
 *            - 5 - PCIE only
 *
 *  @param  CfgValue
 *          - Host composition bit mask, see supported USB interface bitmasks,
 *            not supported by QMI object setting for 9x50 modules
 *            - 0x00000001 - DIAG interface
 *            - 0x00000002 - ADB interface
 *            - 0x00000004 - NMEA interface
 *            - 0x00000008 - MODEM interface
 *            - 0x00000010 - RESERVED5
 *            - 0x00000020 - RESERVED6
 *            - 0x00000040 - RESERVED7
 *            - 0x00000080 - RESERVED8
 *            - 0x00000100 - RMENT0 interface
 *            - 0x00000200 - RESERVED10
 *            - 0x00000400 - RMENT1 interface
 *            - 0x00000800 - RESERVED12
 *            - 0x00001000 - MBIM interface
 *            - 0x00002000 - RESERVED14
 *            - 0x00004000 - RNDIS interface
 *            - 0x00008000 - RESERVED16
 *            - 0x00010000 - AUDIO interface
 *            - 0x00020000 - RESERVED18
 *            - 0x00080000 - ECM interface
 *            - 0x00100000 - RESERVED21
 *            - 0x00200000 - RESERVED22
 *            - 0xFFC00000 - RESERVED
 *
 */
typedef struct
{
    uint32_t CurrentCfgType;
    uint32_t CfgValue;
} swidms_intfaceCfgTlv;

/**
 * \ingroup dms
 * 
 * This structure contains the parameters for supported usb bitmasks
 *
 *  @param  ValidBitmasks
 *          - for current configuration type, this is the supported bitmasks
 *            that the host can change.
 *
 */

typedef struct
{
    uint32_t ValidBitmasks;
} swidms_supportedIntBitmaskTlv;


/**
 * \ingroup dms
 * 
 *  This structure contains the get usb composition response
 *
 *  @param  pInterfaceCfg
 *          - See @ref swidms_intfaceCfgTlv for more information
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param  pSupportedBitmasks [Optional]
 *          - See @ref swidms_supportedIntBitmaskTlv for more information
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  @param  ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct
{
    swidms_intfaceCfgTlv          *pInterfaceCfg;
    swidms_supportedIntBitmaskTlv *pSupportedBitmasks;
    swi_uint256_t                 ParamPresenceMask;

 } unpack_swidms_SLQSSwiDmsGetUsbComp_t;

/**
 * \ingroup dms
 * 
 * Gets the usb interface composition pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_swidms_SLQSSwiDmsGetUsbComp(
    pack_qmi_t  *pCtx,
    uint8_t     *pReqBuf,
    uint16_t    *pLen
);

/**
 * \ingroup dms
 * 
 * Gets the usb interface composition unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_swidms_SLQSSwiDmsGetUsbComp(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_swidms_SLQSSwiDmsGetUsbComp_t *pOutput
);


/**
 * \ingroup dms
 * 
 *  This structure contains the Set Usb Interface Config request parameter.
 *
 *  @param  CfgValue
 *          - Host composition bit mask, see supported USB interface bitmasks,
 *            not supported by QMI object setting for 9x50 modules
 *            - 0x00000001 - DIAG interface
 *            - 0x00000002 - ADB interface
 *            - 0x00000004 - NMEA interface
 *            - 0x00000008 - MODEM interface
 *            - 0x00000010 - RESERVED5
 *            - 0x00000020 - RESERVED6
 *            - 0x00000040 - RESERVED7
 *            - 0x00000080 - RESERVED8
 *            - 0x00000100 - RMENT0 interface
 *            - 0x00000200 - RESERVED10
 *            - 0x00000400 - RMENT1 interface
 *            - 0x00000800 - RESERVED12
 *            - 0x00001000 - MBIM interface
 *            - 0x00002000 - RESERVED14
 *            - 0x00004000 - RNDIS interface
 *            - 0x00008000 - RESERVED16
 *            - 0x00010000 - AUDIO interface
 *            - 0x00020000 - RESERVED18
 *            - 0x00080000 - ECM interface
 *            - 0x00100000 - RESERVED21
 *            - 0x00200000 - RESERVED22
 *            - 0xFFC00000 - RESERVED

 *
 */
typedef struct{
    uint32_t CfgValue;
}pack_swidms_SLQSSwiDmsSetUsbComp_t;

/**
 * \ingroup dms
 * 
 *  This structure is used to store unpack_swidms_SLQSSwiDmsSetUsbComp_t parameters.
 *
 *  @param  Tlvresult
 *           - unpack Tlv result
 *           - Bit to check in ParamPresenceMask - <B>2</B>
 *
 *  @param  ParamPresenceMask
 *           - bitmask representation to indicate valid parameters.
 *
 */
typedef struct{
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_swidms_SLQSSwiDmsSetUsbComp_t;

/**
 * \ingroup dms
 * 
 * Sets the usb interface config value pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values. This setting will be effective after modem reboot
 */
int pack_swidms_SLQSSwiDmsSetUsbComp(
    pack_qmi_t  *pCtx,
    uint8_t     *pReqBuf,
    uint16_t    *pLen,
    pack_swidms_SLQSSwiDmsSetUsbComp_t *reqArg
);

/**
 * \ingroup dms
 * 
 * Sets the usb interface config value unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values. This setting will be effective after modem reboot
 */
int unpack_swidms_SLQSSwiDmsSetUsbComp(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_swidms_SLQSSwiDmsSetUsbComp_t *pOutput
);

/**
 * \ingroup dms
 * 
 *  This structure contains the get debug policy info response
 *
 *  @param  DebugPolicyInfo
 *          - Bit mask of enabled debug levels.
 *
 *  @param  ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct
{
	uint64_t		DebugPolicyInfo;
	swi_uint256_t   ParamPresenceMask;

} unpack_swidms_SLQSSwiDmsGetDebugPolicyInfo_t;

/**
 * \ingroup dms
 * 
 * Gets the debug policy info pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_swidms_SLQSSwiDmsGetDebugPolicyInfo(
	pack_qmi_t  *pCtx,
	uint8_t     *pReqBuf,
	uint16_t    *pLen
);

/**
 * \ingroup dms
 * 
 * Gets the debug policy info unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_swidms_SLQSSwiDmsGetDebugPolicyInfo(
	uint8_t *pResp,
	uint16_t respLen,
	unpack_swidms_SLQSSwiDmsGetDebugPolicyInfo_t *pOutput
);

/**
 * \ingroup dms
 * 
 *  This structure contains the Get Auto-SIM list request parameter.
 *
 *  @param carrier
 *          - carrier name
 *          - NULL terminated string ASCII string. Absent means getting the list from all carriers.
 * 
 *  @param pConfig_index
 *          - Configuration index (must be less than max_config_count)
 *          - Absent means returning the list of first configuration (index=0)
 * 
 *  @param Plist_group_index
 *          - List group index. Each group can only describe up to 50 entries.
 *          - Current list group index (must be less than max-list-qroup_count)
 *          - for the given configuration index
 *          - Absent means returnning the first group of the list (index=0)
 */
typedef struct
{
  char carrier[QMI_SWI_DMS_AUTO_SIM_CARRIER_NAME_MAX];
  uint8_t *pConfig_index;
  uint16_t *pList_group_index;
}pack_swidms_SLQSSwiDmsGetAutoSimList_t;

/**
 * \ingroup dms
 * 
 *  @param  type
 *          - 0 - IIN, 1 - MCC:MNC
 *
 *  @param key_len
 *          - key length
 * 
 *  @param  key
 *          - value of IIN (first 7 digits of ICCID)
 *          - or MCC:MNC (seperator ':' is required)
 * 
 *  @param  rank
 *          - ranking for SIM switch
 *          - 0-127, 255 means any
 * 
 *  @param  subpri
 *          - subpri, subPri index, starting from 1
*/
typedef struct
{
  uint8_t type;
  uint8_t key_len;
  char key[QMI_SWI_DMS_AUTO_SIM_KEY_LENGTH_MAX+1];
  uint8_t rank;
  uint8_t subpri;
}swi_dms_auto_sim_attributes_type_t;

/**
 * \ingroup dms
 * 
 *  @param priid_len
 *          - PRI ID length
 *  
 *  @param  priid
 *          - PRI ID string
 *
 *  @param fwver_len
 *          - firmware version length
 * 
 *  @param  fwver
 *          - firmware version string
 * 
 *  @param  attribs_len
 *          - number of elements in attribs
 *  
 *  @param  attribs
 *          - AUTO-SIM attributes
 *          - Dynamic attributes list of the specified carrier
 * 
 *  @param  source_len
 *          - Number of elements in source
 * 
 *  @param  source
 *          - AUTO-SIM configuration source
 *          - Source, from where the configurations are collected
 *           - values
 *              - 0: PRI
 *              - 1: Custom
 *
 *  @param max_list_qroup_count
 *          - Maximum list group count
 *
 *  @param list_group_index
 *          - List group index
 */
typedef struct
{
  uint8_t priid_len;
  char priid[QMI_SWI_DMS_AUTO_SIM_CONFIG_LEN_MAX+1];
  uint8_t fwver_len;
  char fwver[QMI_SWI_DMS_AUTO_SIM_FWVER_LEN_MAX+1];
  uint8_t attribs_len;
  swi_dms_auto_sim_attributes_type_t attribs[QMI_SWI_DMS_AUTO_SIM_LIST_COUNT_MAX];
  uint8_t source_len;
  uint8_t source[QMI_SWI_DMS_AUTO_SIM_LIST_COUNT_MAX];
  uint16_t max_list_qroup_count;
  uint16_t list_group_index;
}swi_dms_auto_sim_configuration_type_t;

/**
 * \ingroup dms
 * 
 *  This structure contains the get auto SIM list response
 *
 *  @param  configuration
 *          - Configuration
 *          - see \ref swi_dms_auto_sim_configuration_type_t
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 * 
 *  @param  max_config_count
 *          - Maxinum configuration count
 *          - Bit to check in ParamPresenceMask - <B>3</B>
 * 
 *  @param config_index
 *          - Current config index (must be less than max_config_count)
 *          - Bit to check in ParamPresenceMask - <B>4</B>
 * 
 *  @param  ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct
{
    swi_dms_auto_sim_configuration_type_t configuration;
    uint8_t max_config_count;
    uint16_t config_index;
    uint16_t        Tlvresult;
	swi_uint256_t   ParamPresenceMask;
} unpack_swidms_SLQSSwiDmsGetAutoSimList_t;

/**
 * \ingroup dms
 * 
 * Gets AUTO-SIM matching list pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter [optional]
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_swidms_SLQSSwiDmsGetAutoSimList(
	pack_qmi_t  *pCtx,
	uint8_t     *pReqBuf,
	uint16_t    *pLen,
    pack_swidms_SLQSSwiDmsGetAutoSimList_t *reqArg
);

/**
 * \ingroup dms
 * 
 * Gets AUTO-SIM matching list unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_swidms_SLQSSwiDmsGetAutoSimList(
	uint8_t *pResp,
	uint16_t respLen,
	unpack_swidms_SLQSSwiDmsGetAutoSimList_t *pOutput
);

/**
 * \ingroup dms
 * 
 *  This structure contains the Set Auto-SIM List request parameter.
 *
 *  @param carrier
 *          - carrier name
 * 
 *  @param  pAttributes (optional)
 *          - AUTO-SIM attributes
 *          - Dynamic attributes of the specified carrier
 * 
 */
typedef struct
{
    char carrier[QMI_SWI_DMS_AUTO_SIM_CARRIER_NAME_MAX+1];
    swi_dms_auto_sim_attributes_type_t *pAttributes;

}pack_swidms_SLQSSwiDmsSetAutoSimList_t;

typedef unpack_result_t  unpack_swidms_SLQSSwiDmsSetAutoSimList_t;

/**
 * \ingroup dms
 * 
 * Sets AUTO-SIM matching list pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_swidms_SLQSSwiDmsSetAutoSimList(
	pack_qmi_t  *pCtx,
	uint8_t     *pReqBuf,
	uint16_t    *pLen,
    pack_swidms_SLQSSwiDmsSetAutoSimList_t *reqArg
);

/**
 * \ingroup dms
 * 
 * Gets AUTO-SIM matching list unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_swidms_SLQSSwiDmsSetAutoSimList(
	uint8_t *pResp,
	uint16_t respLen,
	unpack_swidms_SLQSSwiDmsSetAutoSimList_t *pOutput
);

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif

