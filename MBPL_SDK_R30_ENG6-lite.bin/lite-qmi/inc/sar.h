/**
 * \ingroup liteqmi
 * \ingroup sar
 * \file sar.h
 */
#ifndef __LITEQMI_SAR_H__
#define __LITEQMI_SAR_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include <stdint.h>

/**
 * \ingroup sar
 * 
 * Gets the specified RF SAR state pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int pack_sar_SLQSGetRfSarState(
        pack_qmi_t  *pCtx,
        uint8_t     *pReqBuf,
        uint16_t    *pLen
        );
/**
 * \ingroup sar
 * 
 *  This structure contains unpack get RF SAR state parameter.
 *  @param  pSarRFState
 *          - SAR RF State
 *            - QMI_SAR_RF_STATE_DEFAULT
 *            - QMI_SAR_RF_STATE_1
 *            - QMI_SAR_RF_STATE_2
 *            - QMI_SAR_RF_STATE_3
 *            - QMI_SAR_RF_STATE_4
 *            - QMI_SAR_RF_STATE_5
 *            - QMI_SAR_RF_STATE_6
 *            - QMI_SAR_RF_STATE_7
 *            - QMI_SAR_RF_STATE_8
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct{
    uint32_t *pSarRFState;
    swi_uint256_t  ParamPresenceMask;
} unpack_sar_SLQSGetRfSarState_t;

/**
 * \ingroup sar
 * 
 * Gets the specified RF SAR state unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput      response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_sar_SLQSGetRfSarState(
        uint8_t   *pResp,
        uint16_t  respLen,
        unpack_sar_SLQSGetRfSarState_t *pOutput
        );

/**
 * \ingroup sar
 * 
 *  This sturcture contain sets the specified RF SAR state parameter.
 *  @param  RfSarState
 *          - SAR RF State
 *            - QMI_SAR_RF_STATE_DEFAULT
 *            - QMI_SAR_RF_STATE_1
 *            - QMI_SAR_RF_STATE_2
 *            - QMI_SAR_RF_STATE_3
 *            - QMI_SAR_RF_STATE_4
 *            - QMI_SAR_RF_STATE_5
 *            - QMI_SAR_RF_STATE_6
 *            - QMI_SAR_RF_STATE_7
 *            - QMI_SAR_RF_STATE_8
 */
typedef struct {
    uint32_t RfSarState;
} pack_sar_SLQSSetRfSarState_t;

typedef unpack_result_t  unpack_sar_SLQSSetRfSarState_t;

/**
 * \ingroup sar
 * 
 * Sets the specified RF SAR state pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int pack_sar_SLQSSetRfSarState(
        pack_qmi_t *pCtx,
        uint8_t *pReqBuf,
        uint16_t *pLen,
        pack_sar_SLQSSetRfSarState_t *reqArg
        );

/**
 * \ingroup sar
 * 
 * Sets the specified RF SAR state unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_sar_SLQSSetRfSarState(
        uint8_t *pResp,
        uint16_t respLen,
        unpack_sar_SLQSSetRfSarState_t *pOutput
        );

/**
 * \ingroup sar
 * 
 *  This structure contains information about the ModuleInfo.
 *
 *  \param  moduleId
 *          - ID of the module.
 *          - Range: 0 to 7.
 *
 *  \param  enableDetection
 *          - Flag denoting enable detection.
 *          - Range: 0 to 1.
 *
 *  \param  pmaxDbmQ7
 *          - Max power applied during single port transmission in Q7 format.
 *
 *  \param  pmaxDbmQ7Mimo
 *          - Max power applied during multiple port transmission in Q7 format.
 *
 *  \param  band
 *          - mmW band this power limit is being reported.
 *
 * @For_5G
 */
typedef struct
{
	uint32_t moduleId;
	uint8_t enableDetection;
	int32_t pmaxDbmQ7;
	int32_t pmaxDbmQ7Mimo;
	int32_t band;
} ModuleInfo_t;

/*
 * This structure contains the SarMpeBeamMtpl request parameters.
 */
typedef struct {
	uint8_t       moduleInfoLen;
	ModuleInfo_t moduleInfo[64];
} pack_sar_SLQSMpeBeamMtpl_t;

typedef unpack_result_t  unpack_sar_SLQSMpeBeamMtpl_t;

/**
 * \ingroup sar
 * 
 * Sets the specified SAR MPE MEAM MTPL pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 *  @For_5G
 *
 */
int pack_sar_SLQSMpeBeamMtpl(
	pack_qmi_t *pCtx,
	uint8_t *pReqBuf,
	uint16_t *pLen,
	pack_sar_SLQSMpeBeamMtpl_t *reqArg
);

/**
 * \ingroup sar
 * 
 * Sets the specified SAR MPE MEAM MTPL unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 *  @For_5G
 *
 */
int unpack_sar_SLQSMpeBeamMtpl(
	uint8_t *pResp,
	uint16_t respLen,
	unpack_sar_SLQSMpeBeamMtpl_t *pOutput
);

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif//#ifndef  __LITEQMI_SAR_H__

