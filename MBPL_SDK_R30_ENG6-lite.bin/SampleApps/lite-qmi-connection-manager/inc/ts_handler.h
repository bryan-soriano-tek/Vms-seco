/*************
 *
 * Filename:    ts_handler.h
 *
 * Purpose:     Contains function for handling QMI TS requests
 *
 * Copyright: © 2022 Sierra Wireless Inc., all rights reserved
 *
 **************/
#ifndef __TS_HANDLER_H__
#define __TS_HANDLER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <CtlService.h>

void register_ts_ind(CtlService* pCtlSvc);
void deregister_ts_ind(CtlService* pCtlSvc);

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif // __TS_HANDLER_H__
