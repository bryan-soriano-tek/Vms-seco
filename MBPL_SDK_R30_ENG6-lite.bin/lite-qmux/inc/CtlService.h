/**
 * \ingroup liteqmux
 *
 * \file CtlService.h
 */
#ifndef __CTL_SERVICE_H__
#define __CTL_SERVICE_H__

#include "QmiService.h"

#ifdef __cplusplus
extern "C" {
#endif

// Forward decl.
struct QmuxTransport;


/**
 * \ingroup liteqmux
 * 
 *  This structure abstracts a CTL QMI service.
 *  It wraps a QMI service which is initialized to type CTL.
 *  Synchronous methods are provided for getting and releasing 
 *  client IDs on behalf of other (regular) QMI services.
 *   
 *  \param  service
 *          - QMI service object, initialized to be of type CTL.
 *
 */
typedef struct CtlService 
{
    QmiService service;
} CtlService;

/**
 * \ingroup liteqmux
 * 
 * Initialize CTL service.
 * @param[in] pThis         The primary object of this call.
 * @param[in] pTransport    Pointer to underlying transport layer which 
 *                          is responsible for sending and receiving 
 *                          QMUX packets
 * @param[in] skipSync      Don't send sync request to modem. Set to true when we wish to use QMI client IDs
 *                          which were acquired during a previous API invocation.
 *                          If skipSync is true, nWaitDelay is ignored.
 * @param[in] nWaitDelay    Number of seconds to delay after a CTL_SYNC_REQ/RESP exchange.
 *                          Zero means no delay.
 * @return 0 on success, ETIMEDOUT, or < 0 on failure.
 */
int CtlService_InitializeEx(CtlService* pThis, struct QmuxTransport* pTransport, bool skipSync, uint8_t nWaitDelay);

/**
 * \ingroup liteqmux
 * 
 * Initialize CTL service.
 * @param[in] pThis         The primary object of this call.
 * @param[in] pTransport    Pointer to underlying transport layer which 
 *                          is responsible for sending and receiving 
 *                          QMUX packets
 * @return 0 on success, ETIMEDOUT, or < 0 on failure.
 */
int CtlService_Initialize(CtlService* pThis, struct QmuxTransport* pTransport);

/**
 * \ingroup liteqmux
 * 
 * Shut down CTL service.
 * @param[in] pThis         The primary object of this call.
 */
void CtlService_ShutDown(CtlService* pThis);

/**
 * \ingroup liteqmux
 * 
 * Get a client ID for a given QMI service type.
 * @param[in] pThis         The primary object of this call.
 * @param[in] serviceType   QMI service type.
 * @param[out] clientId     Returned client ID.
 *       
 * @return 0 on success, ETIMEDOUT, or < 0 on failure. 
*/
int CtlService_GetClientId(CtlService* pThis, uint8_t serviceType, uint8_t* clientId);

/**
 * \ingroup liteqmux
 * 
 * Release a client ID for a given QMI service type.
 * Client ID will have beeb previously obtained by invoking 
 * CtlService_GetClientId.
 * @param[in] pThis         The primary object of this call.
 * @param[in] serviceType   QMI service type.
 * @param[in] clientId      Client ID to be released.
 *       
 * @return 0 on success, ETIMEDOUT, or < 0 on failure. 
*/
int CtlService_ReleaseClientId(CtlService* pThis, uint8_t serviceType, uint8_t clientId);

/**
 * \ingroup liteqmux
 * 
 * Convenience function to initialize a QMI service object.
 * Under the hood, it gets a client ID for a given QMI service type.
 * @param[in] pThis         The primary object of this call.
 * @param[in] pRegularService   Uninitialized QMI service object.
 * @param[in] serviceType   QMI service type.
 * @param[in] pIndicationCallback   User function to be be called when QMI
 *                                  indications are received by the service.    
 * @param[in] pIndicationCallbackContext   A user context for callback.    
 * @param[in] clientId   QMI client ID.
 *                       If 0, a request will be made to get a client ID and 
 *                       the returned ID will be applied to the QMI service.
 *                       If > 0, the request to get a client ID is skipped and
 *                       clientId is applied directly to the QMI service.
 *       
 * @return 0 on success, ETIMEDOUT, or < 0 on failure. 
*/
int CtlService_InitializeRegularServiceEx(
    CtlService* pThis,     
    QmiService* pRegularService,
    uint8_t serviceType, 
    QMI_INDICATION_CALLBACK pIndicationCallback,
    void* pIndicationCallbackContext,
    uint8_t clientId
);

/**
 * \ingroup liteqmux
 * 
 * Convenience function to initialize a QMI service object.
 * Under the hood, it gets a client ID for a given QMI service type.
 * @param[in] pThis         The primary object of this call.
 * @param[in] pRegularService   Uninitialized QMI service object.
 * @param[in] serviceType   QMI service type.
 * @param[in] pIndicationCallback   User function to be be called when QMI
 *                                  indications are received by the service.    
 * @param[in] pIndicationCallbackContext   A user context for callback.    
 *       
 * @return 0 on success, ETIMEDOUT, or < 0 on failure. 

 * @note A new QMI client ID will always be got for the service.
*/
int CtlService_InitializeRegularService(
    CtlService* pThis,     
    QmiService* pRegularService,
    uint8_t serviceType, 
    QMI_INDICATION_CALLBACK pIndicationCallback,
    void* pIndicationCallbackContext
);

/**
 * \ingroup liteqmux
 * 
 * Convenience function to shut down a QMI service object.
 * Under the hood, it releases a client ID for a given QMI service type.
 * @param[in] pThis         The primary object of this call.
 * @param[in] pRegularService   Previously initialized QMI service object.
 * @param[in] skipRelease   If true, skip releasing the QMI client ID 
 *                          associated with the service. This means that a subsequent
 *                          intantiation of the service (in this or a subsequent app) 
 *                          will be able to reuse the QMI client ID.     
 *       
 * @return 0 on success, < 0 on failure.
*/
int CtlService_ShutDownRegularServiceEx(
    CtlService* pThis,     
    QmiService* pRegularService,
    bool skipRelease
);

/**
 * \ingroup liteqmux
 * 
 * Convenience function to shut down a QMI service object.
 * Under the hood, it releases a client ID for a given QMI service type.
 * @param[in] pThis         The primary object of this call.
 * @param[in] pRegularService   Previously initialized QMI service object.
 *       
 * @return 0 on success, < 0 on failure.
 * 
 * @note The QMI client ID associated with the service will be released.
*/
int CtlService_ShutDownRegularService(
    CtlService* pThis,     
    QmiService* pRegularService
);


#ifdef __cplusplus
} /* extern "C" { */
#endif


#endif //__CTL_SERVICE_H__
