/**
 * \ingroup liteqmux
 *
 * \file QmiTransaction.h
 */
#ifndef __QMI_TRANSACTION_H__
#define __QMI_TRANSACTION_H__

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup liteqmux
 * 
 * This funcion prototype represents the callback which is called by the QMI service 
 * when a QMI response is received.
 * 
 * @param[in] qmiPacket Response's QMI packet (note: this does not include QMUX header).
 *
 * @param[in] qmiPacketSize Number of bytes in response's QMI packet.
 *
 * @param[in] pResponseCallbackContext User context supplied when QMI transaction was initialized.
*/
typedef void (*QMI_RESPONSE_CALLBACK)(
    uint8_t* qmiPacket, 
    uint16_t qmiPacketSize, 
    void* pResponseCallbackContext
    );


/**
 * \ingroup liteqmux
 * 
 *  This structure abstracts a QMI transaction.
 *  It is responsible for tracking a QMI request to its response.
 *
 *  \param  inUse
 *          - true indicates that this object has been allocated by the 
 *            QMI service and is un use.
 * 
 *  \param  transactionId
 *          - QMI transaction ID. 
 *            Upper limit 0xffff for regular QMI services,
 *            0xff for CTL service.
 *             
 *  \param  messageId
 *          - QMI message ID.
 * 
 *  \param  pResponseCallback
 *          - User callback for QMI response.
 *
 *  \param  pResponseCallbackContext
 *          - User context for user callback.
 *
 */
typedef struct QmiTransaction  
{
    bool inUse; // Currently allocated.
    uint16_t transactionId;
    uint16_t messageId;
    QMI_RESPONSE_CALLBACK pResponseCallback;
    void* pResponseCallbackContext;
} QmiTransaction;


/**
 * \ingroup liteqmux
 * 
 * Initialize QMI transaction.
 * @param[in] pThis         The primary object of this call.
 * @param[in] transactionId Transaction ID obtained from a call to 
 *                          QmiService_GetNextTransactionId.
 * @param[in] messageId     QMI message ID.
 * @param[in] pResponseCallback   User function to be be called when QMI
 *                                response is received.    
 * @param[in] pResponseCallbackContext   A user context for callback.    
 *       
 */
void QmiTransaction_Initialize(
    QmiTransaction* pThis,
    uint16_t transactionId,
    uint16_t messageId,
    QMI_RESPONSE_CALLBACK pResponseCallback,
    void* pResponseCallbackContext
);

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif //__QMI_TRANSACTION_H__
