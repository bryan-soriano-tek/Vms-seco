/*************
 *
 * Filename: qmidefs.h
 *
 * Purpose:  QM package private constants and structures
 *
 * Copyright: © 2011 Sierra Wireless Inc., all rights reserved
 *
 **************/

#ifndef QMIDEFS_H
#define QMIDEFS_H

/* Includes */
#include "aa/aaglobal.h"
#include "qm/qmerrno.h"
#include "am/amudefs.h"
#include "dl/dludefs.h"
#include "mm/mmudefs.h"
#include "ic/icudefs.h"
#include "os/swi_ossdk.h"
#include "qm/qmudefs.h"
#include "ds/dsudefs.h"

/* Transmit Buffer Pool Definitions */
#define QMTXPOOLSZ      5
#define QMTXBUFSIZE     QMUXSDU_HDR_SZ + QMPARAMMAX

/* Transmit Small Buffer Pool Definitions */
#define QMTXSMALLPLSZ   20
#define QMTXSMLBUFSIZE  QMUXSDU_HDR_SZ + 256

/* Timeout guard interval. This value is the basic timeout applied by the API
 * side whenever it calls icapi_rcv(). It is added to the application's
 * specified timeout on API calls, while the caller's timeout is used directly
 * by the SDK when it is awaiting a response from the modem for a QMI response.
 * This ensure that the modem timeout will always happen first. If the
 * icapi_rcv() times out, then this is some kind of system failure like the SDK
 * process has died.
 */
#define QMTIMEGUARD         1000

/* Timeout value to use in QM package when calling icsmt_rcv() */
#define QMNOTIMEOUT         0

/* QMI Request/Response task Event IDs */
#define QMRESPONSE          1    /* Event ID for QMI Response packet */

/* Request/Response (RR) Task */
#define QMMRESPTIMEOUT    5000 /* Modem response timeout in ms */
#define QMEVTPOOLSZ       30   /* # of buffers in event pool */
#define QMMSGDEPTH        (QMEVTPOOLSZ + 1) /* QM RR Task msg queue depth */

/* Logging masks */
#define QMLOG_CLASSA        0x0001
#define QMLOG_CLASSB        0x0002
#define QMLOG_CLASSC        0x0004

#define QM_MAX_QMI_INST_SUPPORTED   8
#define QM_MIN_QMI_INST_ID          0
#define NUM_IP_FAMILIES             2
#define QMI_MSG_MAX_BUF             1024

/* File format extensions */
#define CWE_EXT ".cwe"
#define MBN_EXT ".mbn"
#define SPK_EXT ".spk"
#define NVU_EXT ".nvu"
#define QM_MAX_APP_SUPPORTED   3
#define QM_APP_CHANNEL_UNKNOWN 0xFF

#define QMMBIM_DCS_CLEAR_REQ_PARAMS(val) \
    do{ \
            val->mbimdcs_data.mbimdcsinprogress = FALSE;\
            val->mbimdcs_data.reqctx = NULL;\
            val->mbimdcs_data.mbimdcsvalidrsprcvd = FALSE;\
            val->mbimdcs_data.rsplen = 0;\
            slmemset( (char *)val->mbimdcs_data.mbimdcsrsp, 0x0, sizeof( val->mbimdcs_data.mbimdcsrsp ));\
       }while(0)

/*************
 *
 * Name:    qmeventtypes
 *
 * Purpose: Enumerated list of event block types. These are the types
 *          that get written into the QMI Event Block whenever an
 *          inter-task message is to be sent to the QM Task.
 *
 * Members: QM_QMIREQ_EVT   - QMI service request event
 *          QM_QMIRSP_EVT   - QMI service response event
 *          QM_TMRTICK_EVT  - Timer Tick event
 *          QM_APPDEV_EVT
 * Notes:   None
 *
 **************/
enum qmeventtype {
    QM_MIN_EVT,
    QM_QMIREQ_EVT = QM_MIN_EVT,
    QM_QMIRSP_EVT,
    QM_TMRTICK_EVT,
    QM_DS_DEVICE_EVT,
    QM_DS_THROTTLE_EVT,
    QM_DS_UNTHROTTLE_EVT,
    QM_MBIM_DCSREQ_EVT,
    QM_MBIM_DCSDISCONNECT_EVT,
};

/*************
 *
 * Name:    qmevtblock
 *
 * Purpose: Structure used to pass information into the QMI
 *          Request/Response task.
 *
 * Members: qmeventtype     - Indicates the remaining content of this block
 *          qmevtdatap      - Pointer to a buffer containing data to be handled
 *                            by the QM RR Task.
 *          qmevtmemfreep   - Pointer to the address to use when releasing the
 *                            memory containing the data. NULL if nothing needs
 *                            to be released.
 *          qmevtipcchan    - IPC channel pertaining to a QMI request event
 *
 * Notes:   None
 *
 **************/
struct qmevtblock
{
    enum qmeventtype qmeventtype;
    swi_uint8        *qmevtdatap;
    swi_uint8        *qmevtmemfreep;
    swi_uint8        qmevtipcchan;
    enum qmisupportedclients client;
    swi_uint8        instanceid;
};

/*************
 *
 * Name:    qmwdata
 *
 * Purpose: Structure to hold key information about the outstanding packet
 *          being sent to the modem. When the response is received it must
 *          correlate directly with this information.
 *
 * Members: qmsbusy         - Whether the QM RR task is already waiting
 *                            for a QMI response from the modem.
 *          qmtimeoutflag   - Indicates whether the thread timed out
 *                            waiting for a response from the modem.
 *          qmoperation     - The value we expect to see in the operation
 *                            type field of the response packet.
 *          qmipcchannel    - The IPC channel that the QMI request came through
 *
 * Notes:
 *
 **************/
struct qmwdata
{
    swi_bool   qmbusy;
    swi_bool   qmtimeoutflag;
    swi_uint8  qmoperation;
    swi_uint8  qmipcchannel;
};

/*************
 *
 * Name:    qm_fms_info
 *
 * Purpose: Information required by the Image Management task for performing
 *          firmware upgrades.
 *
 * Members: path    - fully qualified path to directory containing candidate
 *                    firmware image(s).
 *          isMDM9x15 - Indicates if the modem connected is 9x15 or not.
 *
 *          imgMask - Image Mask indicating requested images for download.
 *          start_t - the time stamp when user application set the firmware path.
 *          needDMReset - a flag indicates whether DM Reset is required or not
 *          mdmProtocol - firmware download download protocol should be used
 *                        values:
 *                        - 0 - SSDP protocol (used by MC77xx,MC73xx/EM73xx, MC74xx/EM74xx
 *                        - 1 - Firehose protocol (used by 9x07 and 9x50 modems such as WP76xx
 * Notes:   none
 *
 **************/
struct qm_fms_info{
    swi_char   path[QM_FMS_IMAGE_PATH_MAX_SZ];
    swi_bool   fw_download_requested;
    swi_bool   fw_download_started;
    swi_int32  fw_download_status;
    swi_ulong isMDM9x15;
    swi_uint16 imgMask;
    time_t     start_t;
    swi_bool   needDMReset;
    swi_uint16 mdmProtocol;
};

/*************
 *
 * Name:    qm_wds_info
 *
 * Purpose: Information required for servicing internal WDS service related
 *          requests.
 *
 * Members: wdsflagInternal - flag indicating whether current wds request must
 *                            be served internally or sent to device.
 *          sessnIDMap      - Map to store session ID's( max 8 instances )
 *                            sessnIDMap[x][0] - indicates IPV4 session ID
 *                                               for x instance ID
 *                            sessnIDMap[x][1] - indicates IPV6 session ID
 *                                               for x instance ID
 *          msgID           - Message ID ( if ) to be handled internally
 * Notes:   none
 *
 **************/
struct qm_wds_info{
    swi_bool   wdsflagInternal;
    swi_ulong sessnIDMap[QM_MAX_QMI_INST_SUPPORTED][NUM_IP_FAMILIES];
    swi_uint16 msgID;
};

/*************
 *
 * Name:    qm_app_info
 *
 * Purpose: Information required by the QM task on the registered applications
 *
 * Members: qmipcchannel    - channel used by the application
 *          qmappregistered - user application registered with SDK flag
 *
 * Notes:   none
 *
 **************/
struct qm_app_info{
    swi_uint8 qmipcchannel;
    swi_bool  qmappregistered;
};

/*************
 *
 * Name:    mbim_dcs_info
 *
 * Purpose: Information required by the QM task on the registered applications
 *
 * Members: mbimdcswaiter     - mbim dcs waiter
 *          mbimdcsinprogress - flag to specify MBIM-QMI request is sent down for response
 *          mbimdcsvalidrsprcvd- flag to track the resonse of the request
 *          mbimdcsrsp        - buffer to hold response data
 *          rsplen            - response length
 * Notes:   none
 *
 **************/
struct mbim_dcs_info{
    struct swi_oswaiter mbimdcswaiter;
    void                *reqctx;
    swi_bool            mbimdcsinprogress;
    swi_bool            mbimdcsvalidrsprcvd;
    swi_uint8           mbimdcsrsp[QMI_MSG_MAX_BUF];
    swi_uint16          rsplen;
   
};

/*************
 *
 * Name:    qmtcb
 *
 * Purpose: QM RR Task control block structure
 *
 * Members: qmdlcb      -   DL package control block for logging
 *          qmicmsgque      IC SMT Message queue
 *          qmevtpool   -   MM pool structure. Contains buffers used
 *                          to store information about QMI Reponses.
 *                          Groups several arguments that can be referenced
 *                          by a single handle
 *          qmwdata     -   Structure to hold the information about
 *                          the current transaction awaiting a response
 *                          from the modem
 *          qmictthndl  -   IC package timer handle used by this task to
 *                          use the periodic timer tick facility of the IC
 *                          package.
 *          qmmdmwaittmr -  Downcounting timer used to detect timeouts when
 *                          waiting for modem responses. Tick interval is
 *                          given by:
 *                                  <timeout(ms)>/ICTICKINTERVAL
 *          qmtxpool        - qm task request large buffer pool
 *          qmtxsmlpool     - qm task request small buffer pool
 *          qmdsshell       - qm task ds shell
 *          qmideviceready  - qcqmi device ready flag
 *          qmappInfo       - information about the registered applications
 *          fmsdata         - firmware download metadata
 *
 * Notes:   none
 *
 **************/
struct qmtcb
{
    struct dlusercb     qmdlcb;
    struct icsmtcb      qmicmsgque;
    struct mmpool       qmevtpool;
    struct qmwdata      qmwdata;
    struct icttregqblk  qmictthndl;
    swi_ulong          qmmdmwaittmr;

    struct mmpool       qmtxpool;
    struct mmpool       qmtxsmlpool;

    struct dsipcshell   qmdsshell[QM_MAX_QMI_INST_SUPPORTED][QMI_SUPPORTED_CLNT_MAX];
    swi_uint8           qmidevicestate;
    struct qm_app_info  qmappInfo[QM_MAX_APP_SUPPORTED];
    struct qm_fms_info  fms_data;
    struct qm_wds_info  wds_data;
    int                 qminstance2devmap[QM_MAX_QMI_INST_SUPPORTED];
    int                 mbiminstance2devmap;  //Support for single MBIM instance at this moment
    struct dsipcshell   mbimdsshell;
    struct swi_oswaiter mbimrspwaiter;
    struct swi_ossemaphore mbimreqmutex;
    struct mbim_dcs_info mbimdcs_data;
    swi_uint8           ipc_xid;
};

/*************
 *
 * Name:    qmgcb
 *
 * Purpose: QM RR Globl Control Block
 *
 * Members:
 *
 * Notes:   none
 *
 **************/
struct qmgcb
{
    struct qmtcb *qmtcbp;
    struct dlusercb qmdlcb;
    struct qmiclientmanager *pclntmgr;
};

/*************
 *
 * Name:    amqmimsgtype
 *
 * Purpose: QMI message type
 *
 * Members: eQMIREQ - QMI request
 *          eQMIRES - QMI response
 *          eQMINOT - QMI notification
 *          eQMIINVALID - invalid QMI message type
 * Notes:
 *
 **************/
enum amqmimsgtype{
    eQMIREQ,
    /* NB: QMI documentation and Firmware do not agree. The doc states that
     * Response = 1 and Notification = 2, but they are coded with values of
     * 2 and 4, respectively.
     */
    eQMIRES = 2,
    eQMINOT = 4,
    eQMIINVALID
};

/*************
 *
 * Name:    qmmbimdcsqmireqtype
 *
 * Purpose: DCS request type in MBIM mode
 *
 * Members:
 *          eQMMBIM_DCSQMIUNKNOWN - unknown request type
 *          eQMMBIM_DCSQMISTARTSRV - QMI start service type
 *          eQMMBIM_DCSQMICMD - QMI command (request/response) type
 * Notes:
 *
 **************/
enum qmmbimdcsqmireqtype{
    eQMMBIM_DCSQMIUNKNOWN,
    eQMMBIM_DCSQMISTARTSRV,
    eQMMBIM_DCSQMICMD
};

/*************
 *
 * Name:    struct qmmbim_dcs_startqmisrv
 *
 * Purpose: Structure for QMI start/stop service request in MBIM mode
 *
 * Members: action      - register or deregister service
 *          qmiinstance - qmi instance id
 *          client      - client to start a service
 * Notes:   None
 *
 **************/
struct qmmbim_dcs_startqmisrv
{
    swi_int8 action;
    int qmiinstance;
    enum qmisupportedclients  client;
};

/*************
 *
 * Name:    struct qmmbim_dcs_qmicmd
 *
 * Purpose: Structure for QMI cmd type request in MBIM mode
 *
 * Members: reqbuf     - Buffer for QMI request packet (Without QMI header)
 *          reqlen     - length of QMI request
 *          svctype    - Type of service for which QMI request is formed
 *          msgid      - Type of message id of QMI cmd for the particular service
 * Notes:   None
 *
 **************/
struct qmmbim_dcs_qmicmd
{
    swi_uint8    reqbuf[QMI_MSG_MAX_BUF];
    swi_uint16   reqlen;
    swi_int16    svctype;
    swi_uint16   msgid;
};


/*************
 *
 * Name:    qmmbim_dcsqmireq
 *
 * Purpose: Structure used to pass MBIM DCS request in the form of QMI packet
 *          to Request/Response task.
 *
 * Members: 
 *          reqtype    - DCS request type
 *          mbimdcsmsg - union for DCS requests in MBIM mode
 * Notes:   None
 *
 **************/
struct qmmbim_dcsqmireq
{
    enum qmmbimdcsqmireqtype reqtype;
    union {
        struct qmmbim_dcs_startqmisrv dcsstartsrv;
        struct qmmbim_dcs_qmicmd dcscmd;
    } mbimdcsmsg;
};


/*************
 *
 * Name:    qmicontrolpoint
 *
 * Purpose: QMI Service Client record. Contains the necessary fields for matching
 *          up a QMI client request with a QMI service response
 *
 * Members: qmisvcname  - QMI service name
 *          svctype     - QMI Service Type for which the client has issued
 *                        a request.
 *          clientid    - id for this client if QMI is transported over MBIM
 *          registered  - QMI client registered with service?
 *          notifchan   - Incoming Notification IPC channel
 *                        (SDK to APP notifications).
 *          xactionid   - Transaction ID of the last issued QMI service request.
 *          clientbusy  - awaiting a QMI response from the device
 *          msgid       - QMI Message ID of the last issued QMI service request
 *          unotifications_supported - Specifies if unsolicited notifications
 *                                     are supported by the service
 *
 * Notes:
 *
 **************/
struct qmicontrolpoint{
    char        qmisvcname[8];
    swi_int16   svctype;
    swi_int8    clientid;
    swi_bool    registered;
    swi_int32   notifchan;
    swi_uint16  xactionid;
    swi_bool    clientbusy;
    swi_int16   msgid;
    swi_bool    unotifications_supported;
};

#define MAXQCQMI 8
/*************
 *
 * Name:    qmiclientmanager
 *
 * Purpose: QMI Service Client manager handling all QMI clients. It also carries
 *          information required to work QMI over MBIM 
 *
 * Members: qmiclients           - array for record of all QMI clients
 *          activeclient         - currently active client
 *          activewdsclient      - array for active wds clients
 *          prevactivewdsclient  - previous active wds client
 *          activeHandle         - handle for currenta ctive client
 *          isMbimMode           - MBIM mode for QMI is enabled or not
 *          isMbimOpen           - MBIM is opened and configured or not
 *          mbim_xid             - transaction id of MBIM for current request
 *          mbim_uuid_qmi        - MBIM UUID for QMI
 *
 * Notes:
 *
 **************/
struct qmiclientmanager{
    struct qmicontrolpoint qmiclients[QMI_SUPPORTED_CLNT_MAX];
    enum qmisupportedclients activeclient;
    enum qmisupportedclients activewdsclient[MAXQCQMI];
    enum qmisupportedclients prevactivewdsclient;
    enum qmisupportedclients actgetclientid;
    swi_int32  activeHandle ;
    swi_bool   isMbimMode;
    swi_bool   isMbimOpen;
    swi_bool   isMbimDSshellOpened;
    swi_uint32 mbim_xid;
    swi_uint8 mbim_uuid_qmi[16];
};

package void qmmbim_dcssubmitreq(struct qmmbim_dcsqmireq *pqmidcsreq);

#include "qm/qmiproto.h"

#endif /* QMIDEFS_H */
