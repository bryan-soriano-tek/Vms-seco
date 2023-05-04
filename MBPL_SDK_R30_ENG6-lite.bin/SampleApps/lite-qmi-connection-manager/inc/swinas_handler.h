/*************
 *
 * Filename:    swinas_handler.h
 *
 * Purpose:     Contains function for handling QMI SWINAS requests
 *
 * Copyright: © 2022 Sierra Wireless Inc., all rights reserved
 *
 **************/
#ifndef __SWINAS_HANDLER_H__
#define __SWINAS_HANDLER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <CtlService.h>
#include "qmi_requests.h"

int InitializeSwiNasService(CtlService* pCtlSvc);
void ShutDownSwiNasService(CtlService* pCtlSvc);
int SwiNasGetDefaultNssaiInfo(unpack_swinas_GetDefaultNssai_t* psDefNssai);
int SwiNasSetDefaultNssaiInfo(pack_swinas_SetDefaultNssai_t* psDefNssai);
int SwiNasGetPdpProfileSettings(pack_swinas_GetPdpContextParams_t* pInput, unpack_swinas_GetPdpContextParams_t* pOutput);
int SwiNasSetPdpProfileSettings(swinas_key_profile_data* pKeyPdpContext, swinas_ext_profile_data* pExtPdpContext);

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif // __SWINAS_HANDLER_H__
