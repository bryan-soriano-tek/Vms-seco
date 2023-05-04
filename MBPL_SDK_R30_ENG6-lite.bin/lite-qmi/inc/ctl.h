/**
 * \ingroup liteqmi
 *
 * \file ctl.h
 */
#ifndef __LITEQMI_CTL_H__
#define __LITEQMI_CTL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include <stdint.h>

void helper_get_ctl_resp_ctx(
        uint8_t *rsp,
        uint32_t len,
        unpack_qmi_t *pCtx
        );

/**
 *  Structure to store get QMI client ID for service.
 *
 *  @param  serviceType
 *          - Selected service from which  a client ID is to be obtained.
 *  @param Tlvresult 
 *          - pack Tlv Result.
 *
 */
typedef struct{
    uint8_t serviceType;
}pack_ctl_GetClientId_t;

/**
 *  Structure to unpack the QMI client ID for service.
 *
 *  @param serviceType
 *          - QMI service for which client ID has been obtained.
 *  @param clientId
 *          - client ID that has been obtained.
 *  @param Tlvresult 
 *          - unpack Tlv Result.
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct{
    uint8_t serviceType;
    uint8_t clientId;     
    uint16_t  Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_ctl_GetClientId_t;

/**
 * Get Client ID pack
 *  Gets a client ID for a given QMI service.
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_ctl_GetClientId(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_ctl_GetClientId_t *reqArg
);

/**
 * Get Client ID unpack.
 * Gets a client ID for a given QMI service.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_ctl_GetClientId(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_ctl_GetClientId_t *pOutput
);

/**
 *  Structure to store release QMI client ID for service.
 *
 *  @param  serviceType
 *          - Selected service from which  a client ID is to be released.
 *  @param  serviceType
 *          - Previously assigned client ID is to be released.
 *  @param Tlvresult 
 *          - pack Tlv Result.
 *
 */
typedef struct{
    uint8_t serviceType;
    uint8_t clientId;
}pack_ctl_ReleaseClientId_t;

/**
 *  Structure to unpack the QMI release client ID for service.
 *
 *  @param serviceType
 *          - QMI service for which client ID is to be released.
 *  @param clientId
 *          - client ID that has been obtained.
 *  @param Tlvresult 
 *          - unpack Tlv Result.
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct{
    uint8_t serviceType;
    uint8_t clientId;     
    uint16_t  Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_ctl_ReleaseClientId_t;

/**
 * Release Client ID pack
 *  Releases a client ID for a given QMI service.
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_ctl_ReleaseClientId(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_ctl_ReleaseClientId_t *reqArg
);

/**
 * Release Client ID unpack.
 * Releases a client ID for a given QMI service.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_ctl_ReleaseClientId(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_ctl_ReleaseClientId_t *pOutput
);



#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif//#ifndef  _LITEQMI_CTL_H_

