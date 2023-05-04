/*************
 *
 * Filename:    swidms_handler.h
 *
 * Purpose:     Contains function for handling QMI SWIDMS requests
 *
 * Copyright: © 2022 Sierra Wireless Inc., all rights reserved
 *
 **************/
#ifndef __SWIDMS_HANDLER_H__
#define __SWIDMS_HANDLER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <CtlService.h>

int get_rmnet(CtlService* pCtlSvc, bool* pbRmNet);

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif // __SWIDMS_HANDLER_H__
