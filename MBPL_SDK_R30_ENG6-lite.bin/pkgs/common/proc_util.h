/*************
 *
 * Filename:    proc_util.h
 *
 * Purpose:     Contains function for managing processes
 *
 * Copyright: © 2022 Sierra Wireless Inc., all rights reserved
 *
 **************/
#ifndef __PROC_UTIL_H__
#define __PROC_UTIL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <syslog.h>
#include "common.h"

typedef void(*FNTERMHANDLER)(int signo, void* pTermContext);

#define DEFAULT_TERMHANDLER	((FNTERMHANDLER)-1)

void SetTermHandler(FNTERMHANDLER pfnTermHandler, void* pTermContext);

void runas_daemon();

void wl(int lvl, const char* buff);
void dlog(int lvl, const char* fmt, ...);
void writeAndLog(int handle, int lvl, const char* fmt, ...);
void outputPrint(int handle, const char* fmt, ...);

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif // __PROC_UTIL_H__

