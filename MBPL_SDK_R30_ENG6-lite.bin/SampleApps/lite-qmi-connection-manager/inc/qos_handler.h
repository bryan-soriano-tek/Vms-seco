/*************
 *
 * Filename:    qos_handler.h
 *
 * Purpose:     Contains function for handling QMI QOS requests
 *
 * Copyright: © 2022 Sierra Wireless Inc., all rights reserved
 *
 **************/
#ifndef __QOS_HANDLER_H__
#define __QOS_HANDLER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <CtlService.h>
#include "command_set.h"

int InitializeQosService(CtlService* pCtlSvc);
void ShutDownQosService(CtlService* pCtlSvc);
void qos_enable_qos_event(bool bEnable);
void qos_request_qosex(pack_qos_SLQSRequestQosExReq_t* sRequestQosExReq);
void qos_get_qosinfo(uint32_t qosIdentifier);
void qos_indicationregister(struct qosIndicationRegisterParams* pParams);
void DoInteractiveQosExRequest();
void GetQosGetQosInfoParams(uint32_t* qosIdentifier);
void GetQosIndicationRegisterParams(struct qosIndicationRegisterParams* pParams);
void GetQosApnId(uint32_t* qosIdentifier);
void qos_read_datastats(uint32_t qosIdentifier);
void qos_read_extraapnparams(uint32_t qosIdentifier);

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif // __QOS_HANDLER_H__
