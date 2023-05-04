/*************
 *
 * Filename:    ping.h
 *
 * Purpose:     Contains function for network ping
 *
 * Copyright: © 2022 Sierra Wireless Inc., all rights reserved
 *
 **************/
#ifndef __PING_H__
#define __PING_H__

#ifdef __cplusplus
extern "C" {
#endif

	int ping(int ipFamily, const char *szAddress, unsigned int cnt, unsigned int delay);

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif	// __PING_H__
