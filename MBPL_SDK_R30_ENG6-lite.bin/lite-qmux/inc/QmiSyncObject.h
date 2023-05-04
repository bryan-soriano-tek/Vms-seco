/**
 * \ingroup liteqmux
 *
 * \file QmiSyncObject.h
 */
#ifndef __QMI_SYNC_OBJECT_H__
#define __QMI_SYNC_OBJECT_H__

#include <stdint.h>
#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
    * \ingroup liteqmux
    *
    * Default synchroize request timeout value in seconds.
    */
#define DEFAULT_SYNC_REQUEST_TIMEOUT_S     10

/**
 * \ingroup liteqmux
 * 
 * Maximum size in bytes of a QMI packet.
 * This does not include QMUX header. It becomes the maximum SDU of a QMUX packet, 
 * MAX_QMUX_PACKET_SIZE - sizeof(QMUX_HDR) 
 */
#define MAX_QMI_PACKET_SIZE (2048 - 6) 

/**
 * \ingroup liteqmux
 * 
 *  This structure is a wrapper around a mutex and condition object
 *  and a buffer. It is a convenience object which may be used to create 
 *  synchronous QMI APIs.   
 *
 *  \param  mutex
 *          - For thread safety.
 * 
 *  \param  condition
 *          - Triggered on completion.
 *             
 *  \param  timeout
 *          - Timeout value for the request, in seconds.
 *
 *  \param  buffer
 *          - QMI request packet is written to this buffer.
 *            On request completion, contains the QMI response packet.
 *
 *  \param  bufferSize
 *          - Set to size in bytes of QMI request packet.
 *            On request completion, set to size of QMI response packet.
 *
 * \note   The buffer is intended for QMI packet only i.e. QMI header and 
 *         QMI payload. This buffer becomes the SDU of a QMUX packet. 
*/
typedef struct QmiSyncObject
{
    pthread_mutex_t mutex;
    pthread_cond_t  condition;
    time_t timeout;
    uint8_t buffer[MAX_QMI_PACKET_SIZE];    // Can be used for outgoing and incoming data
    uint16_t bufferSize; // Will be set to number of incoming bytes
} QmiSyncObject;

/**
 * \ingroup liteqmux
 * 
 * Initialize sync object.
 * 
 * @param[in] pThis         The primary object of this call.
 *       
 * @return 0 on success, < 0 on failure. 
*/
int QmiSyncObject_Initialize(QmiSyncObject* pThis);

/**
 * \ingroup liteqmux
 * 
 * Destroy sync object.
 * 
 * @param[in] pThis         The primary object of this call.
 *       
 * @return 0 on success, < 0 on failure. 
*/
int QmiSyncObject_Destroy(QmiSyncObject* pThis);

/**
 * \ingroup liteqmux
 * 
 * Lock sync object.
 * 
 * @param[in] pThis         The primary object of this call.
 *       
 * @return 0 on success, < 0 on failure. 
*/
int QmiSyncObject_Lock(QmiSyncObject* pThis);

/**
 * \ingroup liteqmux
 * 
 * Unlock sync object.
 * 
 * @param[in] pThis         The primary object of this call.
 *       
 * @return 0 on success, < 0 on failure. 
*/
int QmiSyncObject_Unlock(QmiSyncObject* pThis);

/**
 * \ingroup liteqmux
 * 
 * Block, waiting on sync object.
 * 
 * @param[in] pThis         The primary object of this call.
 *       
 * @return 0 on success, < 0 on failure. 
*/
int QmiSyncObject_Wait(QmiSyncObject* pThis);

/**
 * \ingroup liteqmux
 * 
 * Block, waiting on sync object for a number of seconds.
 * 
 * @param[in] pThis         The primary object of this call.
 *       
 * @param[in] timeoutSeconds Timeout in seconds before abondoning wait.
 *       
 * @return 0 on success, ETIMEDOUT, or < 0 on failure. 
*/
int QmiSyncObject_TimedWait(QmiSyncObject* pThis, time_t timeoutSeconds);

/**
 * \ingroup liteqmux
 * 
 * Signal sync object. Waiting thread should wake up.
 * 
 * @param[in] pThis         The primary object of this call.
 *       
 * @return 0 on success, or < 0 on failure. 
*/
int QmiSyncObject_Signal(QmiSyncObject* pThis);

/**
 * \ingroup liteqmux
 * 
 * This funcion copies QMI response packet to buffer and signals the waiting thread.
 * 
 * @param[in] qmiPacket  Received QMI packet.
 * @param[in] qmiPacketSize  Received QMI packet size in bytes.
 * @param[in] pResponseCallbackContext Pointer to this sync object.
 *       
*/
void QmiSyncObject_ResponseCallback(uint8_t* qmiPacket, uint16_t qmiPacketSize, void* pResponseCallbackContext);


#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif //__QMI_SYNC_OBJECT_H__
