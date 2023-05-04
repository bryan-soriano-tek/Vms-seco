/*************
 *
 * Filename:    qmux_util.h
 *
 * Purpose:     Contains function for managing qmux functionalities
 *
 * Copyright: � 2022 Sierra Wireless Inc., all rights reserved
 *
 **************/
#ifndef __QMUX_UTIL_H__
#define __QMUX_UTIL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdbool.h>
#include <CtlService.h>
#include <QmiService.h>
#include <QmuxTransport.h>
#include <QmiTransaction.h>
#include "common.h"
#include "dev_util.h"

#define RMNET_IF_ID_UNSET -1

/* Return values:
 *   0 - succeed
 *   1 - invalid argument
 *   2 - failed to open transport
 */
int OpenTransportEx(
	QmuxTransport* ptransport,	// [out]	Pointer to QmuxTransport structure
	char* dev_path,				// [in/out]	Path to Device.  If empty, will be filled
	size_t dev_path_size,		// [in]		Size of buffer dev_path points to
	int* pmode,					// [in/out]	Interface mode, if unknown, will be filled
	bool* ppcie,				// [out]	Return if device is on PCIe interface
	int* pif_adapter,			// [out]	adapter interface.  Invalid for USB only
	bool valid,					// [in]		Valid preconditions
	FNSHOWHELP pfnsh,			// [in]		Pointer to ShowHelp function
	const char* pProcName,		// [in]		Process name to be passed to pfhsh
	bool showhelp,				// [in]		Always show help flag
	bool skipOpen,				// [in]		True to skip lower layer initialization. 
	                        	//          Used when modem state has persisted between API invocations.
	bool skipClose);			// [in]		True to skip lower layer shutdown. 
                        		//          Used to persist modem state between API invocations.

/* Return values:
 *   0 - succeed
 *   1 - invalid argument
 *   2 - failed to open transport
 */
int OpenTransport(
	QmuxTransport* ptransport,	// [out]	Pointer to QmuxTransport structure
	char* dev_path,				// [in/out]	Path to Device.  If empty, will be filled
	size_t dev_path_size,		// [in]		Size of buffer dev_path points to
	int* pmode,					// [in/out]	Interface mode, if unknown, will be filled
	bool* ppcie,				// [out]	Return if device is on PCIe interface
	int* pif_adapter,			// [out]	adapter interface.  Invalid for USB only
	bool valid,					// [in]		Valid preconditions
	FNSHOWHELP pfnsh,			// [in]		Pointer to ShowHelp function
	const char* pProcName,		// [in]		Process name to be passed to pfhsh
	bool showhelp);				// [in]		Always show help flag

uint16_t IndicationCallback(const char* svcName, uint8_t svc, uint8_t* qmiPacket, uint16_t qmiPacketSize, void* pIndicationCallbackContext);

/*
 * Name:     SaveClientId
 *
 * Purpose:  Save a serviceType/clientId pair to a file.
 *
 * Params:   serviceType	- QMI service type e.g. eUIM, eNAS.
 * 			 clientId		- QMI client ID.
 *           clientIdsPath  - Path of file in which the serviceType/clientId will be saved.
 *
 * Return:   SUCCESS	- If successful
 *           < 0 		- On failure
 *
 * Notes:    None
 */
int SaveClientId(uint8_t serviceType, uint8_t clientId, const char* clientIdsPath);

/*
 * Name:     RestoreClientId
 *
 * Purpose:  Restore a serviceType/clientId pair from a file.
 *
 * Params:   serviceType	- QMI service type e.g. eUIM, eNAS.
 * 			 pClientId		- Restored QMI client ID.
 *           clientIdsPath  - Path of file in which the serviceType/clientId was saved.
 *
 * Return:   SUCCESS	- If successful
 *           < 0 		- On failure
 *
 * Notes:    None
 */
int RestoreClientId(uint8_t serviceType, uint8_t* pClientId, const char* clientIdsPath);

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif // __QMUX_UTIL_H__

