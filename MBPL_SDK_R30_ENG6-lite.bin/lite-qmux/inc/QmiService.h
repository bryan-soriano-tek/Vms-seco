/**
 * \ingroup liteqmux
 *
 * \file QmiService.h
 */
#ifndef __QMI_SERVICE_H__
#define __QMI_SERVICE_H__

#include <stdbool.h>
#include <pthread.h>
#include "common.h"
#include "QmiSyncObject.h"
#include "QmiTransaction.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Signature of QMI API pack function with input parameter data pointer */
typedef int(*pack_func)(pack_qmi_t*, uint8_t*, uint16_t*, void*);

/* Signature of QMI API pack function that does not have input parameter data pointer */
typedef int(*pack_func_no_input)(pack_qmi_t*, uint8_t*, uint16_t*);

/* Signature of QMI API unpack function */
typedef int(*unpack_func)(uint8_t*, uint16_t, void*);

/*
 * Name:     SENDRECEIVE
 *
 * Purpose:  Macro for send QMI request with input parameter data pointer and receive QMI response.
 *
 * @param[in] SVC       The primary object of this call.
 * @param[in] PACK		Pointer to packer function.
 * @param[in] ARGI		Pointer to input argument structure.
 * @param[in] UNPACK	Pointer to unpacker function.
 * @param[out] ARGO		Pointer to output structure.
 *
 */
#define SENDRECEIVE(SVC, PACK, ARGI, UNPACK, ARGO) QmiService_SendSyncRequest((SVC), (pack_func)(PACK), #PACK, (ARGI), (unpack_func)(UNPACK), #UNPACK, (ARGO), DEFAULT_SYNC_REQUEST_TIMEOUT_S)

 /*
  * Name:     SENDRECEIVENOINPUT
  *
  * Purpose:  Macro for send QMI request without input parameter data pointer and receive QMI response.
  *
  * @param[in] SVC      The primary object of this call.
  * @param[in] PACK		Pointer to packer function.
  * @param[in] UNPACK	Pointer to unpacker function.
  * @param[out] ARGO	Pointer to output structure.
  *
  */
#define SENDRECEIVENOINPUT(SVC, PACK, UNPACK, ARGO) QmiService_SendSyncRequestNoInput((SVC), (pack_func_no_input)(PACK), #PACK, (unpack_func)(UNPACK), #UNPACK, (ARGO), DEFAULT_SYNC_REQUEST_TIMEOUT_S)

/*
 * Name:     SENDRECEIVETO
 *
 * Purpose:  Macro for send QMI request with input parameter data pointer and receive QMI response.  With explicit timeout value.
 *
 * @param[in] SVC       The primary object of this call.
 * @param[in] PACK		Pointer to packer function.
 * @param[in] ARGI		Pointer to input argument structure.
 * @param[in] UNPACK	Pointer to unpacker function.
 * @param[out] ARGO		Pointer to output structure.
 * @param[in] TO	    Timeout value in seconds.
 *
 */
#define SENDRECEIVETO(SVC, PACK, ARGI, UNPACK, ARGO, TO) QmiService_SendSyncRequest((SVC), (pack_func)(PACK), #PACK, (ARGI), (unpack_func)(UNPACK), #UNPACK, (ARGO), (TO))

/*
 * Name:     SENDRECEIVENOINPUTTO
 *
 * Purpose:  Macro for send QMI request without input parameter data pointer and receive QMI response.  With explicit timeout value.
 *
 * @param[in] SVC       The primary object of this call.
 * @param[in] PACK		Pointer to packer function.
 * @param[in] UNPACK	Pointer to unpacker function.
 * @param[out] ARGO		Pointer to output structure.
 * @param[in] TO	    Timeout value in seconds.
 *
 */
#define SENDRECEIVENOINPUTTO(SVC, PACK, UNPACK, ARGO, TO) QmiService_SendSyncRequestNoInput((SVC), (pack_func_no_input)(PACK), #PACK, (unpack_func)(UNPACK), #UNPACK, (ARGO), (TO))

/*
 * Name:     SENDRECEIVEWITHSYNCOBJ
 *
 * Purpose:  Macro for send QMI request with input parameter data pointer and receive QMI response.  With sync object pointer.
 *
 * @param[in] SVC       The primary object of this call.
 * @param[in] SYNCOBJ   Sync object for the call.
 * @param[in] PACK		Pointer to packer function.
 * @param[in] ARGI		Pointer to input argument structure.
 * @param[in] UNPACK	Pointer to unpacker function.
 * @param[out] ARGO		Pointer to output structure.
 *
 */
#define SENDRECEIVEWITHSYNCOBJ(SVC, SYNCOBJ, PACK, ARGI, UNPACK, ARGO) QmiService_SendSyncRequestWithSyncObj((SVC), (SYNCOBJ), (pack_func)(PACK), #PACK, (ARGI), (unpack_func)(UNPACK), #UNPACK, (ARGO))

/*
 * Name:     SENDRECEIVEWITHSYNCOBJNOINPUT
 *
 * Purpose:  Macro for send QMI request without input parameter data pointer and receive QMI response.  With sync object pointer.
 *
 * @param[in] SVC       The primary object of this call.
 * @param[in] SYNCOBJ   Sync object for the call.
 * @param[in] PACK		Pointer to packer function.
 * @param[in] UNPACK	Pointer to unpacker function.
 * @param[out] ARGO		Pointer to output structure.
 *
 */
#define SENDRECEIVEWITHSYNCOBJNOINPUT(SVC, SYNCOBJ, PACK, UNPACK, ARGO) QmiService_SendSyncRequestWithSyncObjNoInput((SVC), (SYNCOBJ), (pack_func_no_input)(PACK), #PACK, (unpack_func)(UNPACK), #UNPACK, (ARGO))

/*
 * Name:     SENDREQUEST
 *
 * Purpose:  Macro for send QMI request with input parameter data pointer, for async callback.
 *
 * @param[in] SVC       The primary object of this call.
 * @param[in] PACK		Pointer to packer function.
 * @param[in] ARGI		Pointer to input argument structure.
 * @param[in] CB	    Pointer to callback function.
 * @param[in] CONTEXT	Context of callback.
 * @param[out] PXID     Pointer to receive transaction ID.
 *
 */
#define SENDREQUEST(SVC, PACK, ARGI, CB, CONTEXT, PXID) QmiService_SendAsyncRequest((SVC), (pack_func)(PACK), #PACK, (ARGI), (CB), (CONTEXT), (PXID))

/*
 * Name:     SENDREQUESTNOINPUT
 *
 * Purpose:  Macro for send QMI request without input parameter data pointer, for async callback.
 *
 * @param[in] SVC       The primary object of this call.
 * @param[in] PACK		Pointer to packer function.
 * @param[in] CB	    Pointer to callback function.
 * @param[in] CONTEXT	Context of callback.
 * @param[out] PXID     Pointer to receive transaction ID.
 *
 */
#define SENDREQUESTNOINPUT(SVC, PACK, CB, CONTEXT, PXID) QmiService_SendAsyncRequestNoInput((SVC), (pack_func_no_input)(PACK), #PACK, (CB), (CONTEXT), (PXID))

/**
 * \ingroup liteqmux
 * 
 * This funcion prototype represents the callback which is called by the QMI service 
 * when a QMI indication is received.
 * 
 * @param[in] qmiPacket indication's QMI packet (note: this does not include QMUX header).
 *
 * @param[in] qmiPacketSize Number of bytes in indication's QMI packet.
 *
 * @param[in] pIndicationCallbackContext User context supplied when QMI service was initialized.
*/
typedef void (*QMI_INDICATION_CALLBACK)(
    uint8_t* qmiPacket, 
    uint16_t qmiPacketSize, 
    void* pIndicationCallbackContext
    );

// Forward decls.
struct QmuxTransport;

#define QMI_TRANSACTION_POOL_SIZE 10 /**< Number of concurrent QMI transactions that may be outstanding per QMI service. */

/**
 * \ingroup liteqmux
 * 
 *  This structure abstracts a QMI service.
 *  It is responsible issuing transaction IDs.
 *  It tracks QMI requests and responses using transaction objects from
 *  a pool.
 *  It invokes a user callback when QMI indications which match 
 *  its client ID (or a broadcast ID) are received from the transport 
 *  layer. 
 *
 *  \param  pNext
 *          - A link so we can store this object in a linked list by the
 *            transport layer.
 * 
 *  \param  serviceType
 *          - QMI service type, CTL, NAS, etc.
 *
 *  \param  clientId
 *          - QMI client ID
 *
 *  \param  pTransport
 *          - Pointer to underlying QMUX transport object. 
 *
 *  \param  transactionId
 *          - QMI transaction ID. 
 *            Upper limit 0xffff for regular QMI services,
 *            0xff for CTL service.
 *             
 *  \param  transactionIdLock
 *          - Mutex to make transactionId access thread-safe. 
 *
 *  \param  transactionPool
 *          - Pool of transaction objects which may be assigned to 
 *            QMI requests made by clients of this service.
 *
 *  \param  transactionPoolLock
 *          - Mutex to make transactionPool access thread-safe
 *
 *  \param  pIndicationCallback
 *          - User callback for QMI indications of this service.
 *
 *  \param  pIndicationCallbackContext
 *          - User context for user callback.
 *
 */
typedef struct QmiService
{
    struct QmiService* pNext;  
    uint8_t serviceType;
    uint8_t clientId;
    struct QmuxTransport* pTransport;
    uint16_t transactionId;
    pthread_mutex_t transactionIdLock;
    QmiTransaction transactionPool[QMI_TRANSACTION_POOL_SIZE];
    pthread_mutex_t transactionPoolLock;
    QMI_INDICATION_CALLBACK pIndicationCallback;
    void* pIndicationCallbackContext;
} QmiService;

/**
 * \ingroup liteqmux
 * 
 * Initialize QMI service.
 * @param[in] pThis         The primary object of this call.
 * @param[in] serviceType   QMI service e.g. NAS, etc.
 * @param[in] clientId      Value previously obtained by invoking 
 *                          CtlService_GetClientId
 * @param[in] pTransport    Pointer to underlying transport layer which 
 *                          is responsible for sending and receiving 
 *                          QMUX packets
 * @param[in] pIndicationCallback   User function to be be called when QMI
 *                                  indications are received.    
 * @param[in] pIndicationCallbackContext   A user context for callback.    
 *       
 */
void QmiService_Initialize(
    QmiService* pThis, 
    uint8_t serviceType, 
    uint8_t clientId,
    struct QmuxTransport* pTransport,
    QMI_INDICATION_CALLBACK pIndicationCallback,
    void* pIndicationCallbackContext
    );

/**
 * \ingroup liteqmux
 * 
 * Shut down QMI service.
 * Brings service to an uninitiaized state.
 * @param[in] pThis      The primary object of this call.
 *       
 */
void QmiService_ShutDown(QmiService* pThis);

/**
 * \ingroup liteqmux
 * 
 * Returns next transaction ID for a QMI service.
 * @param[in] pThis      The primary object of this call.
 *       
 * @return transaction ID
*/
uint16_t QmiService_GetNextTransactionId(QmiService* pThis);

/**
 * \ingroup liteqmux
 * 
 * Send a QMI request to the device and return immediately.
 * 
 * @param[in] pThis         The primary object of this call.
 * @param[in] transactionId transaction ID obtained by previous call to
 *                          QmiService_GetNextTransactionId.
 * @param[in] qmiRequest    QMI request (this becomes the QMUX SDU).
 * @param[in] qmiRequestSize Size in bytes of QMI request.
 * @param[in] pResponseCallback Callback called when QMI request completes.
 * @param[in] pResponseCallbackContext Context for callback.
 *       
 * @return 0 on success, < 0 on failure. 
*/
int QmiService_SendRequest(
    QmiService* pThis,
    uint16_t transactionId,
    uint8_t* qmiRequest, 
    uint16_t qmiRequestSize, 
    QMI_RESPONSE_CALLBACK pResponseCallback, 
    void* pResponseCallbackContext);

/**
 * \ingroup liteqmux
 * 
 * Cancel an outstanding QMI request.
 * @param[in] pThis         The primary object of this call.
 * @param[in] transactionId Transaction ID of outstanding request.
 *       
 */
void QmiService_CancelTransaction(QmiService* pThis, uint16_t transactionId);

/**
 * \ingroup liteqmux
 * 
 * Process a received QMI packet.
 * This function is called by the QMUX transport layer.
 * 
 * @param[in] pThis         The primary object of this call.
 * @param[in] serviceType   QMI service type of received packet.
 * @param[in] clientId      QMI Client ID of received packet.
 * @param[in] qmiPacket     Pointer to QMI packet.
 * @param[in] qmiPacketSize Pointer to size in bytes of QMI packet.
 *       
 * @return true if packet is consumed by function, false if it should
 *         be offered to another QMI service 
*/
bool QmiService_HandleQmiPacket(
    QmiService* pThis,
    uint8_t serviceType, 
    uint8_t clientId, 
    uint8_t* qmiPacket, 
    uint16_t qmiPacketSize);


/*
 * Name:     QmiService_SendSyncRequest
 *
 * Purpose:  Send QMI request and receive QMI response.
 *
 * @param[in] pThis         The primary object of this call.
 * @param[in] fnPacker		Pointer to packer function.
 * @param[in] pPackerName	Packer function name.
 * @param[in] pInput		Pointer to input argument structure.
 * @param[in] fnUnpacker	Pointer to unpacker function.
 * @param[in] pUnpackerName	Unpacker function name.
 * @param[out] pOutput		Pointer to output structure.
 * @param[in] timeout	    Timeout value in seconds.
 *
 * @return 0 on success, < 0 on failure.
 *
 * Notes:    Use SENDRECEIVE macro to simplify the call
 */
int QmiService_SendSyncRequest(QmiService* pThis, pack_func fnPacker, const char* pPackerName, void* pInput, unpack_func fnUnpacker, const char* pUnpackerName, void* pOutput, time_t timeout);

/*
 * Name:     QmiService_SendSyncRequestNoInput
 *
 * Purpose:  Send QMI request and receive QMI response.
 *
 * @param[in] pThis         The primary object of this call.
 * @param[in] fnPacker		Pointer to packer function.
 * @param[in] pPackerName	Packer function name.
 * @param[in] fnUnpacker	Pointer to unpacker function.
 * @param[in] pUnpackerName	Unpacker function name.
 * @param[out] pOutput		Pointer to output structure.
 * @param[in] timeout	    Timeout value in seconds.
 *
 * @return 0 on success, < 0 on failure.
 *
 * Notes:    Use SENDRECEIVENOINPUT macro to simplify the call
 */
int QmiService_SendSyncRequestNoInput(QmiService* pThis, pack_func_no_input fnPacker, const char* pPackerName, unpack_func fnUnpacker, const char* pUnpackerName, void* pOutput, time_t timeout);

/*
 * Name:     QmiService_SendSyncRequestWithSyncObj
 *
 * Purpose:  Send QMI request and receive QMI response.
 *
 * @param[in] pThis         The primary object of this call.
 * @param[in] pSyncObject   Sync object for the call.
 * @param[in] fnPacker		Pointer to packer function.
 * @param[in] pPackerName	Packer function name.
 * @param[in] pInput		Pointer to input argument structure.
 * @param[in] fnUnpacker	Pointer to unpacker function.
 * @param[in] pUnpackerName	Unpacker function name.
 * @param[out] pOutput		Pointer to output structure.
 *
 * @return 0 on success, < 0 on failure.
 *
 * Notes:    Use SENDRECEIVEWITHSYNCOBJ macro to simplify the call
 */
int QmiService_SendSyncRequestWithSyncObj(QmiService* pThis, QmiSyncObject* pSyncObject, pack_func fnPacker, const char* pPackerName, void* pInput, unpack_func fnUnpacker, const char* pUnpackerName, void* pOutput);

/*
 * Name:     QmiService_SendSyncRequestWithSyncObjNoInput
 *
 * Purpose:  Send QMI request and receive QMI response.
 *
 * @param[in] pThis         The primary object of this call.
 * @param[in] pSyncObject   Sync object for the call.
 * @param[in] fnPacker		Pointer to packer function.
 * @param[in] pPackerName	Packer function name.
 * @param[in] fnUnpacker	Pointer to unpacker function.
 * @param[in] pUnpackerName	Unpacker function name.
 * @param[out] pOutput		Pointer to output structure.
 *
 * @return 0 on success, < 0 on failure.
 *
 * Notes:    Use SENDRECEIVEWITHSYNCOBJNOINPUT macro to simplify the call
 */
int QmiService_SendSyncRequestWithSyncObjNoInput(QmiService* pThis, QmiSyncObject* pSyncObject, pack_func_no_input fnPacker, const char* pPackerName, unpack_func fnUnpacker, const char* pUnpackerName, void* pOutput);

/*
 * Name:     QmiService_SendAsyncRequest
 *
 * Purpose:  Send QMI request.
 *
 * @param[in] pThis         The primary object of this call.
 * @param[in] fnPacker		Pointer to packer function.
 * @param[in] pPackerName	Packer function name.
 * @param[in] pInput		Pointer to input argument structure.
 * @param[in] fnCallback	Pointer to callback function.
 * @param[in] pContext		Context of callback.
 * @param[out] pXid         Pointer to receive transaction ID.
 *
 * @return 0 on success, < 0 on failure.
 *
 * Notes:    Use SENDREQUEST macro to simplify the call
 */
int QmiService_SendAsyncRequest(QmiService* pThis, pack_func fnPacker, const char* pPackerName, void* pInput, QMI_RESPONSE_CALLBACK fnCallback, void* pContext, uint16_t* pXid);

/*
 * Name:     QmiService_SendAsyncRequestNoInput
 *
 * Purpose:  Send QMI request.
 *
 * @param[in] pThis         The primary object of this call.
 * @param[in] fnPacker		Pointer to packer function.
 * @param[in] pPackerName	Packer function name.
 * @param[in] fnCallback	Pointer to callback function.
 * @param[in] pContext		Context of callback.
 * @param[out] pXid         Pointer to receive transaction ID.
 *
 * @return 0 on success, < 0 on failure.
 *
 * Notes:    Use SENDREQUESTNOINPUT macro to simplify the call
 */
int QmiService_SendAsyncRequestNoInput(QmiService* pThis, pack_func_no_input fnPacker, const char* pPackerName, QMI_RESPONSE_CALLBACK fnCallback, void* pContext, uint16_t* pXid);

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif //__QMI_SERVICE_H__
