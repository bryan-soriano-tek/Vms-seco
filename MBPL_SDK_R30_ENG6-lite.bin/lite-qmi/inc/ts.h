/**
 * \ingroup liteqmi
 *
 * \file ts.h
 */
#ifndef __LITEQMI_TS_H__
#define __LITEQMI_TS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include <stdint.h>

#define MAX_SENSOR_LIST_LEN 255
#define MAX_SENSOR_ID_LEN  255

/**
 * \ingroup ts
 *
 * To get thermal sensor supported messages list pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] pInput not used
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *  @For_5G
 */

int pack_ts_SLQSTsGetSupportedMsgs(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
	void* pInput);

/**
 * \ingroup ts
 *
 * This structure contains thermal sensor supported messages list
 *
 * @param numMsgs
 *        - Number of supported messages
 *
 * @param pMsgIds
 *        - Pointer to supported message IDs
 *
 *  @param  Tlvresult
 *          - Unpack Result
 *
 *  @For_5G
 */
typedef struct {
	uint16_t	 numMsgs;
	uint8_t*	 pMsgIds;
	uint16_t     Tlvresult;
}unpack_ts_SLQSTsGetSupportedMsgs_t;

/**
 * \ingroup ts
 *
 * To thermal sensor supported messages list unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *  @For_5G
 */

int unpack_ts_SLQSTsGetSupportedMsgs(
    uint8_t *pResp,
    uint16_t respLen,
	unpack_ts_SLQSTsGetSupportedMsgs_t* pOutput);

/**
 * \ingroup ts
 *
 * To get thermal sensor supported fields list pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] pMsgID message id
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *  @For_5G
 */

int pack_ts_SLQSTsGetSupportedFields(
	pack_qmi_t* pCtx,
	uint8_t* pReqBuf,
	uint16_t* pLen,
	uint16_t* pMsgID);

/**
 * \ingroup ts
 *
 * This structure contains thermal sensor supported fields list
 *
 * @param fieldListLen
 *        - Number of supported fields
 *
 * @param pFieldList
 *        - Pointer to supported field IDs
 *
 *  @param  Tlvresult
 *          - Unpack Result
 *
 *  @For_5G
 */
typedef struct
{
	uint8_t fieldListLen;
	uint8_t* pFieldList;
} TsSupportedFields;

/**
 * \ingroup ts
 *
 * This structure contains thermal sensor supported fields lists
 *
 * @param reqFields
 *        - Supported request fields
 *
 * @param respFields
 *        - Supported response fields
 *
 * @param indFields
 *        - Supported indication fields
 *
 *  @param  Tlvresult
 *          - Unpack Result
 *
 *  @param  ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 *  @For_5G
 */
typedef struct {
	TsSupportedFields reqFields;
	TsSupportedFields respFields;
	TsSupportedFields indFields;
	uint16_t     Tlvresult;
	swi_uint256_t  ParamPresenceMask;
}unpack_ts_SLQSTsGetSupportedFields_t;

/**
 * \ingroup ts
 *
 * To thermal sensor supported fields list unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *  @For_5G
 */

int unpack_ts_SLQSTsGetSupportedFields(
	uint8_t* pResp,
	uint16_t respLen,
	unpack_ts_SLQSTsGetSupportedFields_t* pOutput);

/**
 * \ingroup ts
 *
 * To get thermal sensor total number of sensors pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] pInput not used
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *  @For_5G
 */

int pack_ts_SLQSTsGetNumSensors(
	pack_qmi_t* pCtx,
	uint8_t* pReqBuf,
	uint16_t* pLen,
	void* pInput);

/**
 * \ingroup ts
 *
 * This structure contains total number of sensors
 *
 * @param numSensors
 *        - Total number of sensors
 *
 *  @param  Tlvresult
 *          - Unpack Result
 *
 *  @For_5G
 */
typedef struct {
	uint32_t	 numSensors;
	uint16_t     Tlvresult;
}unpack_ts_SLQSTsGetNumSensors_t;

/**
 * \ingroup ts
 *
 * To total number of sensors unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *  @For_5G
 */

int unpack_ts_SLQSTsGetNumSensors(
	uint8_t* pResp,
	uint16_t respLen,
	unpack_ts_SLQSTsGetNumSensors_t* pOutput);

/**
 * \ingroup ts
 *
 * To get thermal sensor list pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] pInput not used
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *  @For_5G
 */

int pack_ts_SLQSTsGetSensorList(
	pack_qmi_t* pCtx,
	uint8_t* pReqBuf,
	uint16_t* pLen,
	void* pInput);

/**
 * \ingroup ts
 *
 * To get thermal sensor list pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] pListIndex list index
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *  @For_5G
 */

int pack_ts_SLQSTsGetSensorListV2(
	pack_qmi_t* pCtx,
	uint8_t* pReqBuf,
	uint16_t* pLen,
	uint32_t* pListIndex);

/**
 * \ingroup ts
 *
 * This structure contains thermal sensor ID
 *
 * @param sensorIdLen
 *        - Number of sets of the following elements
 *          - sensorId
 *
 * @param sensorId
 *        - Senor ID.
 *  @For_5G
 */
typedef struct
{
	uint8_t sensorIdLen;
	char sensorId[MAX_SENSOR_ID_LEN];
}ts_sensorId;

/**
 * \ingroup ts
 *
 * This structure contains thermal sensor list
 *
 * @param pSensorListLen
 *        - Number of sets of the following elements
 *          - pSensorList
 *
 * @param pSensorList
 *        - List of Senor ID.
 *
 *  @param  Tlvresult
 *          - Unpack Result
 *
 *  @For_5G
 */
typedef struct {
	uint8_t		 sensorListLen;
	ts_sensorId  sensorList[MAX_SENSOR_LIST_LEN];
	uint16_t     Tlvresult;
}unpack_ts_SLQSTsGetSensorList_t;

/**
 * \ingroup ts
 *
 * To sensor list unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *  @For_5G
 */

int unpack_ts_SLQSTsGetSensorList(
	uint8_t* pResp,
	uint16_t respLen,
	unpack_ts_SLQSTsGetSensorList_t* pOutput);

/**
 * \ingroup ts
 *
 * To sensor list unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *  @For_5G
 */

int unpack_ts_SLQSTsGetSensorListV2(
	uint8_t* pResp,
	uint16_t respLen,
	unpack_ts_SLQSTsGetSensorList_t* pOutput);

/**
 * \ingroup ts
 *
 * This structure contains register temperature reqport request parameters
 *
 * @param sensor
 *        - Sensor ID
 *          - see ts_sensorId
 *
 * @param curTempReport
 *        - Report current temperature
 *
 * @param pHighThresTemp
 *        - High threshold temperature
 *
 * @param pLowThresTemp
 *        - Low threshold temperature
 *
 * @param pSeqNum
 *        - Sequence number
 *  @For_5G
 */

typedef struct {
	ts_sensorId	sensor;
	uint8_t curTempReport;
	float * pHighThresTemp;
	float * pLowThresTemp;
	uint32_t * pSeqNum;
}pack_ts_SLQSTsRegNotTempRpt_t;

/**
 * \ingroup ts
 *
 * To Register notification sensor temperature pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[out] reqArg request argument.
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *  @For_5G
 */

int pack_ts_SLQSTsRegNotTempRpt(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
	pack_ts_SLQSTsRegNotTempRpt_t *reqArg);

/**
 * \ingroup ts
 *
 * To Register notification sensor temperature pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[out] reqArg request argument.
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *  @For_5G
 */

int pack_ts_SLQSTsRegNotTempRptV2(
	pack_qmi_t* pCtx,
	uint8_t* pReqBuf,
	uint16_t* pLen,
	pack_ts_SLQSTsRegNotTempRpt_t* reqArg);

/**
 * \ingroup ts
 *
 * To Register notification temperature report unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response (not used)
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *  @For_5G
 */

int unpack_ts_SLQSTsRegNotTempRpt(
    uint8_t *pResp,
    uint16_t respLen,
	void* pOutput);

/**
 * \ingroup ts
 *
 * To Register notification temperature report unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response (not used)
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *  @For_5G
 */

int unpack_ts_SLQSTsRegNotTempRptV2(
	uint8_t* pResp,
	uint16_t respLen,
	void* pOutput);

/**
 * \ingroup ts
 *
 * Temperature Report
 *  @param  sensor
 *          - Sensor ID
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param  type
 *          - Report type
 *          - Bit to check in ParamPresenceMask - <B>2</B>
 *
 *  @param  temp
 *          - Temperature
 *          - Bit to check in ParamPresenceMask - <B>0x10</B>
 *
 *  @param  seqNum
 *          - Sequence number
 *          - Bit to check in ParamPresenceMask - <B>0x11</B>
 *
 *  @param  ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 *  @For_5G
 */
typedef struct {
	ts_sensorId	sensor;
	uint32_t type;
	float	temp;
	uint32_t	seqNum;
	swi_uint256_t  ParamPresenceMask;
}unpack_ts_SLQSTsTempRptCallback_ind_t;

/**
 * \ingroup ts
 *
 * Temperature Report Indication unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     indication unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *  @For_5G
 */
int unpack_ts_SLQSTsTempRptCallback_ind(
    uint8_t *pResp,
    uint16_t respLen,
	unpack_ts_SLQSTsTempRptCallback_ind_t *pOutput
    );

/**
 * \ingroup ts
 *
 * Temperature Report Indication unpack
 * @param[in]   pResp       qmi response from modem
 * @param[in]   respLen     qmi response length
 * @param[out]  pOutput     indication unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 *  @For_5G
 */
int unpack_ts_SLQSTsTempRptCallback_indV2(
	uint8_t* pResp,
	uint16_t respLen,
	unpack_ts_SLQSTsTempRptCallback_ind_t* pOutput
);

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif

