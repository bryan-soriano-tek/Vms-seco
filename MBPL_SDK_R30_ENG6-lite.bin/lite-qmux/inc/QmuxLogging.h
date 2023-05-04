/**
 * \ingroup liteqmux
 * 
 * \file QmuxLogging.h
 */
#ifndef __QMUX_LOGGING_H__
#define __QMUX_LOGGING_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#define DEFAULT_SYSLOG_LEVEL    7

typedef void (* liteqmux_logger)(uint8_t lvl, const char* buff, ...);

/**
 * \ingroup liteqmux
 * 
 * Set external logging function.  If external logging function is not
 * configured, lite-qmux logging goes to syslog.
 */
void set_liteqmux_logger_func(liteqmux_logger func);

/**
 * \ingroup liteqmux
 * 
 * Log lite-qmux messages
 * 
 * @param[in] lvl   Logging level
 * @param[in] fmt   Logging format    
*/
void liteqmux_log(
    uint8_t lvl,
    const char* fmt, ...
);

/**
 * \ingroup liteqmux
 *
 * Log specified message in hex format
 *
 * @param[in] pBuffer: Pointer to the message buffer
 * @param[in] bufSize: The size of specified buffer
 * @param[in] read: true indicates an incoming read buffer
 *                  false indicates an outgoing write buffer
 *
 * @return None
 */
void lite_print_hex(
	void * pBuffer,
	int    bufSize,
	bool   read
);

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif // __QMUX_LOGGING_H__
