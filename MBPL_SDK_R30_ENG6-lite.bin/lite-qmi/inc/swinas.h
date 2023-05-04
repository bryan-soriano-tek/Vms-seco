/**
 * \ingroup liteqmi
 * \ingroup nas
 * 
 * \file swinas.h
 */
#ifndef __LITEQMI_SWINAS_H__
#define __LITEQMI_SWINAS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include <stdint.h>

#define MAX_RF_STATUS_INSTS     55

/**
 * \ingroup nas
 * 
 * pack function to get rfdev status
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * 
 * @For_5G
 */

int pack_swinas_GetRfdevStatus(
    pack_qmi_t * pCtx,
    uint8_t * pReqBuf,
    uint16_t * pLen);

/**
 * \ingroup nas
 * 
 * This structure contains device RF status info
 *
 *  @param  inst_id
 *          - Instance ID
 * 
 *  @param  mfg_id
 *          - Manufacturer ID
 * 
 *  @param  prod_id
 *          - Product ID
 *
 *  @param  dev_status
 *          - 0: RF device is not connected or malfunctioning
 *          - 1: RF device present and functional
 * 
 *  @For_5G
 */
typedef struct {
    uint8_t     inst_id;
    uint16_t    mfg_id;
    uint16_t    prod_id;
    uint8_t     dev_status;
} rf_status_t;

/**
 * \ingroup nas
 * 
 * This structure contains RFC device status info
 * 
 *  @param  rf_init_status
 *          - RF initialization status
 *          - 0: RF initialization failed
 *          - 1: RF initialization completed.
 *               Refer to TLV RF Status for details
 * 
 *  @param  rf_status_num
 *          - Number of valid RF status instances included in rf_status array
 * 
 *  @param  rf_status
 *          - Array of RF status instances
 * 
 *  @For_5G
 */
typedef struct {
    uint8_t     rf_init_status;
    uint32_t    rf_status_num;
    rf_status_t rf_status[MAX_RF_STATUS_INSTS];
    swi_uint256_t ParamPresenceMask;
} unpack_swinas_GetRfdevStatus_t;

/**
 * \ingroup nas
 * 
 * unpack function to get rfdev status info
 * 
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * 
 * @For_5G
 */

int unpack_swinas_GetRfdevStatus(
    uint8_t * pResp,
    uint16_t respLen,
    unpack_swinas_GetRfdevStatus_t * pOutput);

/**
 * \ingroup nas
 * 
 *  This structure contains the info for mmWave RFC configuration.
 *
 *  @param  hw_id
 *          - mmWave hardware ID
 *          - Use 0 in case of disabling mmWave
 * 
 *  @param  board_id
 *          - mmWave board ID
 *          - Use 0 in case of disabling mmWave
 *
 *  @For_5G
 *
 */
typedef struct
{
	uint16_t    hw_id;
    uint16_t    board_id;
} pack_swinas_SetMmwaveConfig_t;

typedef unpack_result_t  unpack_swinas_SetMmwaveConfig_t;

/**
 * \ingroup nas
 * 
 *  Pack function for mmWave configuration.
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
 *  @note   Device Supported: MC75xx, EM75xx and WP76xx.
 *
 *  @For_5G
 *
 */
int pack_swinas_SetMmwaveConfig(
	pack_qmi_t * pCtx,
	uint8_t * pReqBuf,
	uint16_t * pLen,
	pack_swinas_SetMmwaveConfig_t * pReqParam);

/**
 * \ingroup nas
 * 
 *  Unpack function for mmWave configuration.
 * 
 *  @param[in]   pResp       qmi response from modem
 *  @param[in]   respLen     qmi response length
 *  @param[out]  pOutput     unpacked response
 *
 *  @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 *  @For_5G
 *
 */
int unpack_swinas_SetMmwaveConfig(
	uint8_t * pResp,
	uint16_t respLen,
	unpack_swinas_SetMmwaveConfig_t * pOutput);

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif
