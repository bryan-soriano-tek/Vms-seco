/*************
 *
 * Filename:    tmd_handler.h
 *
 * Purpose:     Contains function for handling QMI TMD requests
 *
 * Copyright: © 2022 Sierra Wireless Inc., all rights reserved
 *
 **************/
#ifndef __TMD_HANDLER_H__
#define __TMD_HANDLER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <CtlService.h>

void register_mit_ind(CtlService* pCtlSvc);
void deregister_mit_ind(CtlService* pCtlSvc);

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif // __TMD_HANDLER_H__
