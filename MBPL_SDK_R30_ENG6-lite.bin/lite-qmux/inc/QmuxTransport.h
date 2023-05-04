/**
 * \ingroup liteqmux
 *
 * \file QmuxTransport.h
 */
#ifndef __QMUX_TRANSPORT_H__
#define __QMUX_TRANSPORT_H__


#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif

// Forward decl.
struct QmiService;

#define QMUX_INTERFACE_DIRECT 0
#define QMUX_INTERFACE_MBIM 1
#define QMUX_INTERFACE_ROUTER 2

/**
 * \ingroup liteqmux
 * 
 * QMUX transport error type definitions
 */
typedef enum
{
    QMUX_TRANSPORT_ERR_UNKNOWN, // Unknown error type
    QMUX_TRANSPORT_ERR_READ,    // Error occurred during read() operation
    QMUX_TRANSPORT_ERR_WRITE,   // Error occurred during write() operation
	QMUX_TRANSPORT_MSG_DEVMODE	// Inform device mode
} QMUX_TRANSPORT_ERR_TYPE;

/**
 * \ingroup liteqmux
 * 
 * This structure contains the detailed error info occurred in qmux transport layer.
 * 
 * \param   err_type
 *          - Type of error defined in QMUX_TRANSPORT_ERR_TYPE.
 * 
 * \param   errno_val
 *          - errno value set by the system when error occurs.
 */
typedef struct 
{
    QMUX_TRANSPORT_ERR_TYPE  err_type;
    int                      errno_val;
} QMUX_TRANSPORT_ERR_INFO;

/**
 * \ingroup liteqmux
 * 
 * QMUX transport error callback function.
 * 
 * @param[in]   pErrCallbackContext User context of the callback function
 * @param[in]   err_info    A QMUX_TRANSPORT_ERR_INFO structure which contains
 *                          the detailed error info.
 * 
 * @return      None
 */
typedef void (*QMUX_TRANSPORT_ERR_CALLBACK)(void * pErrCallbackContext, QMUX_TRANSPORT_ERR_INFO err_info);

/**
 * \ingroup liteqmux
 * 
 *  This structure abstracts a QMUX transport layer.
 *  It is responsible for applying QMUX headers to QMI packets 
 *  from QMI services and forwarding them to the device.
 *  It is responsible for receiving QMUX packets from the device.
 *  On the basis of QMUX headers, it distributes the SDUs (QMI packets) to the
 *  appropriate QMI service.  
 *  It maintains a list of connected QMI service objects.
 *
 *  \param  interfaceType
 *          - Using direct, MBIM, or router for data layer.
 * 
 *  \param  pDataLayer
 *          - Pointer to instantiated data layer.
 * 
 *  \param  deviceFd
 *          - File descriptor of device.
 * 
 *  \param  shutdownFd
 *          - Event descriptor. Used to signal read thread to terminate.
 * 
 *  \param  devRemoved
 *          - Flag indicating device has been removed or not.
 *
 *  \param  qmiServiceList
 *          - List of connected QMI service objects.
 *
 *  \param  writeLock
 *          - Provides mutual exclusion for write operations. 
 *
 *  \param  qmiServiceListLock
 *          - Provides thread safety for the service list.
 *             
 *  \param  readThread
 *          - Thread responsible for reading from device. 
 *
 *  \param  pErrCallback
 *          - Callback function for transport error events.
 * 
 *  \param  pErrCallbackContext
 *          - User context for MbimTransport error callback
 */
typedef struct QmuxTransport
{
    int interfaceType;
    void* pDataLayer;
    int deviceFd; 
    int shutdownFd; // FD of shutdown event.
    bool devRemoved;    // Flag indicating device has been removed.
    struct QmiService* qmiServiceList; // List of QMI services this transport is handling. 
    pthread_mutex_t writeLock;  // Protect write operations.
    pthread_mutex_t qmiServiceListLock;
    pthread_t readThread;
    QMUX_TRANSPORT_ERR_CALLBACK pErrCallback;
    void * pErrCallbackContext; 
    bool skipOpen;  // True to skip lower layer initialization. Used when modem state has persisted API invocations.
    bool skipClose; // True to skip lower layer shutdown. Used to persist modem state between API invocations.
} QmuxTransport;

/**
 * \ingroup liteqmux
 * 
 * Initialize the transport layer.
 * 
 * @param[in] pThis         The primary object of this call.
 * @param[in] devicePath    Absolute path to device.
 * @param[in] useMbim       Use MBIM interface as opposed to direct interface for data layer.
 * @param[in] pInterfaceSpecific A pointer to an object (may be NULL) related to the specific interface used.
 *                               Currently ignored for useMbim = false. 
 *                               If useMbim = true, it may point to an already initialized
 *                               MbimTransport object, in which case, this object will use that object
 *                               rather than try to create its own MbimTransport object.
 *         
 * @return 0 on success, < 0 on failure. 
*/
int QmuxTransport_Initialize(QmuxTransport* pThis, char *devicePath, bool useMbim, void* pInterfaceSpecific);

/**
 * \ingroup liteqmux
 * 
 * Initialize the transport layer.
 * 
 * @param[in] pThis         The primary object of this call.
 * @param[in] destination   For direct or MBIM, it is absolute path to device.
 *                          For router, it is the IP address of router or NULL for localhost
 * @param[in] interfaceType Use direct, MBIM, or router interface for data layer.
 *                            for direct, use QMUX_INTERFACE_DIRECT
 *                            for MBIM, use QMUX_INTERFACE_MBIM
 *                            for router, use QMUX_INTERFACE_ROUTER
*
 * @param[in] pInterfaceSpecific A pointer to an object (may be NULL) related to the specific interface used.
 *                               Currently ignored for useMbim = false. 
 *                               If useMbim = true, it may point to an already initialized
 *                               MbimTransport object, in which case, this object will use that object
 *                               rather than try to create its own MbimTransport object.
 *         
 * @return 0 on success, < 0 on failure. 
*/
int QmuxTransport_InitializeEx(QmuxTransport* pThis, char *destination, int interfaceType, void* pInterfaceSpecific);

/**
 * \ingroup liteqmux
 * 
 * Initialize the transport layer.
 * 
 * @param[in] pThis         The primary object of this call.
 * @param[in] destination   For direct or MBIM, it is absolute path to device.
 *                          For router, it is the IP address of router or NULL for localhost
 * @param[in] interfaceType Use direct, MBIM, or router interface for data layer.
 *                            for direct, use QMUX_INTERFACE_DIRECT
 *                            for MBIM, use QMUX_INTERFACE_MBIM
 *                            for router, use QMUX_INTERFACE_ROUTER
*
 * @param[in] pInterfaceSpecific A pointer to an object (may be NULL) related to the specific interface used.
 *                               Currently ignored for useMbim = false. 
 *                               If useMbim = true, it may point to an already initialized
 *                               MbimTransport object, in which case, this object will use that object
 *                               rather than try to create its own MbimTransport object.
 *         
 * @param[in] skipOpen      True to skip lower layer initialization. 
 *                          Used when modem state has persisted between API invocations.
 *
 * @param[in] skipClose     True to skip lower layer shutdown. 
 *                          Used to persist modem state between API invocations.
 *
 * @return 0 on success, < 0 on failure. 
*/
int QmuxTransport_InitializeEx2(QmuxTransport* pThis, char *destination, int interfaceType, void* pInterfaceSpecific, bool skipOpen, bool skipClose);

/**
 * \ingroup liteqmux
 * 
 * Shut down the transport layer.
 * 
 * @param[in] pThis         The primary object of this call.
*/
void QmuxTransport_ShutDown(QmuxTransport* pThis);

/**
 * \ingroup liteqmux
 * 
 * Attaches a QMI service to the transport layer.
 * 
 * @param[in] pThis         The primary object of this call.
 * @param[in] pQmiService   The QMI service to be attached.
*/
void QmuxTransport_AttachQmiService(QmuxTransport* pThis, struct QmiService* pQmiService);

/**
 * \ingroup liteqmux
 * 
 * Detaches a QMI service from the transport layer.
 * 
 * @param[in] pThis         The primary object of this call.
 * @param[in] pQmiService   The QMI service to be detached.
*/
void QmuxTransport_DetachQmiService(QmuxTransport* pThis, struct QmiService* pQmiService);

/**
 * \ingroup liteqmux
 * 
 * Send a QMI request to the device and return immediately.
 * 
 * @param[in] pThis         The primary object of this call.
 * @param[in] qmiServiceType QMI service type.
 * @param[in] qmiClientId   QMI client ID.
 * @param[in] qmiTransactionId QMI transaction ID. Can be used for tracking purposes.
 * @param[in] qmiPacket     Pointer to QMI request.
 * @param[in] qmiPacketSize Size in bytes of QMI packet.
 *       
 * @return 0 on success, < 0 on failure. 
*/
int QmuxTransport_SendQmiPacket( 
                            QmuxTransport* pThis,
						    uint8_t qmiServiceType, 
                            uint8_t qmiClientId,
                            uint16_t qmiTransactionId,
                            uint8_t* qmiPacket,  
                            uint16_t qmiPacketSize
						  );

/**
 * \ingroup liteqmux
 * 
 * This function is for client applications to register for transport error info callbacks.
 * The most recent callback registration is the only function that is invoked when 
 * device is removed.
 *
 * @param[in]   pThis           The primary object of this call.
 * @param[in]   pErrCallback    A valid function pointer to be notified when device is removed.
 *                              NULL to disable callback notifications.
 * @param[in]   pErrCallbackContext User context when transport error callback is called
 *
 * @return      None
 */ 
void QmuxTransport_RegisterErrCallback(QmuxTransport * pThis, QMUX_TRANSPORT_ERR_CALLBACK pErrCallback, void * pErrCallbackContext);

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif //__QMUX_TRANSPORT_H__
