/**
 * \ingroup liteqmi
 *
 * \file tmd.h
 */
#ifndef __LITEQMI_TMD_H__
#define __LITEQMI_TMD_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include <stdint.h>

#define TMD_MAX_DEV_LIST 255
#define MAX_MITIGATION_DEV_LIST_LEN 255
#define MAX_MITIGATION_DEV_ID_LEN  255

/**
 * \ingroup tmd
 *
 * To get mitigation device list pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] pInput not used
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */

int pack_tmd_SLQSTmdGetMitigationDevList(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    void* pInput);

/**
 * \ingroup tmd
 *
 * This structure contains mitigation devices list
 *
 * @param mitigationDevIdLen
 *        - Number of sets of the following elements
 *          - mitigation_dev_id
 *
 * @param mitigationDevId
 *        - Mitigation device ID.
 *
 * @param maxMitigationLevel
 *        - Maximum valid mitigation level.
 *        - Valid range - 0 to max_mitigation_level.
 */
typedef struct
{
    uint8_t mitigationDevIdLen;
    char    mitigationDevId[MAX_MITIGATION_DEV_LIST_LEN];
    uint8_t maxMitigationLevel;
}tmd_mitigationDevList;

/**
 * \ingroup tmd
 *
 * This structure contains mitigation devices list from the remote endpoint
 *
 *  @param  MitigationDevListLen
 *          - Mitigation Device List Length (Optional)
 *          - Number of sets of the following elements
 *            - MitigationDevList
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  @param  pMitigationDevList
 *          - Mitigation Device List (Optional)
 *          - See @ref tmd_mitigationDevList for more information.
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  @param  Tlvresult
 *          - Unpack Result
 *
 *  @param  ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct {
    uint8_t                MitigationDevListLen;
    tmd_mitigationDevList  MitigationDevList[TMD_MAX_DEV_LIST];
    uint16_t               Tlvresult;
    swi_uint256_t          ParamPresenceMask;
}unpack_tmd_SLQSTmdGetMitigationDevList_t;

/**
 * \ingroup tmd
 *
 * To mitigation device list unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */

int unpack_tmd_SLQSTmdGetMitigationDevList(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_tmd_SLQSTmdGetMitigationDevList_t *pOutput);

/**
 * \ingroup tmd
 *
 * This structure contains mitigation devices Level request parameters
 *
 * @param mitigationDevIDLen
 *        - Number of sets of the following elements
 *          - mitigation_dev_id
 *
 * @param mitigationDevID
 *        - Mitigation device ID
 */

typedef struct {
    uint8_t  mitigationDevIDLen;
    char     mitigationDevID[MAX_MITIGATION_DEV_ID_LEN];
}pack_tmd_SLQSTmdGetMitigationLvl_t;

/**
 * \ingroup tmd
 *
 * To get mitigation level pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[out] reqArg request argument.
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */

int pack_tmd_SLQSTmdGetMitigationLvl(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_tmd_SLQSTmdGetMitigationLvl_t *reqArg);

/**
 * \ingroup tmd
 *
 * This structure contains mitigation devices Level request parameters
 *
 *  @param  CurrentmitigationLvl
 *         - Current thermal mitigation level (Optional)
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  @param  ReqMitigationLvl
 *         - Requested Thermal Mitigation Level (Optional)
 *         - The requested thermal mitigation level from the client.
 *           The default is zero if the client has not previously set
 *           the mitigation level.
 *          - Bit to check in ParamPresenceMask - <B>17</B>
 *
 *  @param  Tlvresult
 *          - Unpack Result
 *
 *  @param  ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct {
    uint8_t   CurrentmitigationLvl;
    uint8_t   ReqMitigationLvl;
    uint16_t  Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_tmd_SLQSTmdGetMitigationLvl_t;

/**
 * \ingroup tmd
 *
 * To get mitigation level unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */

int unpack_tmd_SLQSTmdGetMitigationLvl(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_tmd_SLQSTmdGetMitigationLvl_t *pOutput);

/**
 * \ingroup tmd
 *
 * This structure contains mitigation devices Level request parameters
 *
 * @param mitigationDevIDLen
 *        - Number of sets of the following elements
 *          - mitigation_dev_id
 *
 * @param mitigationDevID
 *        - Mitigation device ID
 */

typedef struct {
    uint8_t  mitigationDevIDLen;
    char     mitigationDevID[MAX_MITIGATION_DEV_ID_LEN];
}pack_tmd_SLQSTmdRegNotMitigationLvl_t;

/**
 * \ingroup tmd
 *
 * To Register notification mitigation level pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[out] reqArg request argument.
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */

int pack_tmd_SLQSTmdRegNotMitigationLvl(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_tmd_SLQSTmdRegNotMitigationLvl_t *reqArg);

/**
 * \ingroup tmd
 *
 * This structure contains mitigation devices Level request parameters
 *
 *  @param  Tlvresult
 *          - Unpack Result
 *          - Bit to check in ParamPresenceMask - <B>2</B>
 *
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct {
    uint16_t  Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_tmd_SLQSTmdRegNotMitigationLvl_t;

/**
 * \ingroup tmd
 *
 * To Register notification mitigation level unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */

int unpack_tmd_SLQSTmdRegNotMitigationLvl(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_tmd_SLQSTmdRegNotMitigationLvl_t *pOutput);

/**
 * \ingroup tmd
 *
 * This structure contains mitigation devices Level request parameters
 *
 * @param mitigationDevIDLen
 *        - Number of sets of the following elements
 *          - mitigation_dev_id
 *
 * @param mitigationDevID
 *        - Mitigation device ID
 */

typedef struct {
    uint8_t  mitigationDevIDLen;
    char     mitigationDevID[MAX_MITIGATION_DEV_ID_LEN];
}pack_tmd_SLQSTmdDeRegNotMitigationLvl_t;

/**
 * \ingroup tmd
 *
 * To DeRegister notification mitigation level pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[out] reqArg request argument.
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */

int pack_tmd_SLQSTmdDeRegNotMitigationLvl(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_tmd_SLQSTmdDeRegNotMitigationLvl_t *reqArg);

/**
 * \ingroup tmd
 *
 * This structure contains mitigation devices Level request parameters
 *
 *  @param  Tlvresult
 *          - Unpack Result
 *          - Bit to check in ParamPresenceMask - <B>2</B>
 *
 *  @param  ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct {
    uint16_t  Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_tmd_SLQSTmdDeRegNotMitigationLvl_t;

/**
 * \ingroup tmd
 *
 * To De-Register notification mitigation level unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
*
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */

int unpack_tmd_SLQSTmdDeRegNotMitigationLvl(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_tmd_SLQSTmdDeRegNotMitigationLvl_t *pOutput);

/**
 * \ingroup tmd
 *
 * Mitigation Level Report
 *  @param  deviceIdLen
 *          - Mitigation Device ID Length
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param  deviceID
 *          - Mitigation Device ID
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param  lvl
 *          - Current thermal mitigation level
 *          - Bit to check in ParamPresenceMask - <B>2</B>
 *
 *  @param  ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct {
    uint8_t  deviceIdLen;
    char  deviceID [MAX_MITIGATION_DEV_ID_LEN];
    uint8_t lvl;
    swi_uint256_t  ParamPresenceMask;
}unpack_tmd_SLQSTmdMitigationLvlRptCallback_ind_t;

/**
 * \ingroup tmd
 *
 * Mitigiation Level Report Indication unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     indication unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_tmd_SLQSTmdMitigationLvlRptCallback_ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_tmd_SLQSTmdMitigationLvlRptCallback_ind_t *pOutput
    );

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif

