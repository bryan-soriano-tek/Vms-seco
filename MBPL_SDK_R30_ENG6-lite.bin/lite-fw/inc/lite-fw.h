/**
 *
 * @ingroup litefw
 *
 * @file lite-fw.h
 * Filename:    lite-fw.h
 *
 * Purpose:     Global definitions used inside the SDK
 *
 * Copyright: © 2016 Sierra Wireless Inc., all rights reserved
 *
 */
#ifndef _LITE_FW_H_
#define _LITE_FW_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Pragmas */
#pragma once
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <syslog.h>
#include "qmerrno.h"
#include "fms.h"
#include "dms.h"
#include "dev_util.h"
#include <stdbool.h>

#define IMG_MASK_MDM (1<<0)
#define IMG_MASK_PRI (1<<1)
#define IMG_MASK_CLEAR   (0x000)
#define IMG_MASK_GENERIC (0xFFFF)
#define IMG_MASK_ALL     (0xFFFFFFF)

// Carrier package SKU Info
#define LITEFW_CARRIER_PACKAGE_SKU "9999999"
#define LITEFW_SKU_STRING_LENGTH   7

// Fimware Info String size
#define FIRMWARE_INFO_STRING_SIZE  20
#define NULL_TERMINATOR_CHAR_SIZE 1

#define DEV_MODE_STR_LEN    8

#define MAX_USB_PATH_LEN 512
#define USB_PATH_LEN 16

#define DEFAULT_DL_MODE_WAIT_TIME 60    // 60 seconds
#define DEFAULT_APP_MODE_WAIT_TIME 240   // 240 seconds

#define MILLISECOND    1000
#define HALF_A_SECOND (500*MILLISECOND)
#define SECOND        (1000*MILLISECOND)

#define DEFAULT_DEV_CONN_RETRY_INTERVAL 5   // Retry interval 5 seconds
#define DEFAULT_DEV_CONN_RETRIES        48  // Default retry 48 times, which is 4 minutes

#define FW_UPDATE_STATUS_SUCCESSFUL     1
#define FW_UPDATE_STATUS_UNKNOWN        0xFFFFFFFF

#define SH_RESP_BUF_LEN 512

#define PCIE_QDL_PORT   "/dev/mhiqdl0"

/**
 * \ingroup litefw
 * 
 * Image list file name
 * 
 * \param   full_file_name
 *          - The full file name including the absolute path
 * 
 * \param   next
 *          - Pointer to the next element in the list
 */
typedef struct image_node
{
    char * full_file_name;
    struct image_node * next;
} image_node_t;

/**
 * \ingroup litefw
 * 
 * litefw internal error codes 
 */
enum litefw_fwdwl_error_codes
{
    /*! Success */
    eSDP_FWDWL_SUCCESS = 0,
    /*! Generic FW download error */
    eSDP_FWDWL_ERR_GENERAL = 100,
    /*! SDK specific error */
    eSDP_FWDWL_ERR_SDK,
    /*! Error in setting SDK callbacks */
    eSDP_FWDWL_ERR_SET_CBK,
    /*! Path is too long */
    eSDP_FWDWL_ERR_PATH_TOO_LONG,
    /*! Mandatory SDK/FW path not set */
    eSDP_FWDWL_ERR_PATH_NOT_SPECIFIED,
    /*! Post FW download check indicates that the FW upgrade has failed.
        For example, PRI not updated as expected, FW version not updated etc. */
    eSDP_FWDWL_ERR_FW_UPGRADE,
    /*! Invalid device */
    eSDP_FWDWL_ERR_INVALID_DEV,
    /*! Invalid Path or No valid firmware or nvu file exist in the path */
    eSDP_FWDWL_ERR_INVALID_PATH,
    /*! Download Process Timeout */
    eSDP_FWDWL_ERR_TIMEOUT,
    /*! Download Process Fail */
    eSDP_FWDWL_ERR_FAIL,
    /*! Download PRI Fail */
    eSDP_FWDWL_ERR_PRI_FAIL,
    /*! Download Fail Version Not Match */
    eSDP_FWDWL_ERR_FW_VERSION_FAIL,
    /*! SSDP mode timeout */
    eSDP_FWDWL_ERR_SDP_TIMEOUT,
    eReserved,
    /*! Sahara state error */
    eSDP_FWDWL_ERR_SARAHA_STATE_ERR,
    /*! No images to download */
    eSDP_FWDWL_ERR_NO_IMG_TO_DWLD_ERR,
    /*! Failed when sending data */
    eSDP_FWDWL_ERR_DATA_SENDING_ERR,
    /*! Out of sync with device */
    eSDP_FWDWL_ERR_OUT_OF_SYNC,
    /*! Failed to get SPKG string from image file */
    eSDP_FWDWL_ERR_SPKG_STR_FAIL,
    /*! Invalid argument */
    eSDP_FWDWL_ERR_INVALID_ARGUMENT,
    /*! State timeout or error in Firehose */
    eSDP_FWDWL_ERR_FIREHOSE_STATE_ERR,
    /*! Device reported an error in Firehose */
    eSDP_FWDWL_ERR_FIREHOSE_DEV_REPORT_ERR,
    /*! Device not responsive in Sahara */
    eSDP_FWDWL_ERR_SAHARA_UNRESPONSIVE,
    eSDP_FWDWL_ERR_END
};

/**
 * \ingroup litefw
 * 
 * This enum matches with fw_image_type_e in imudefs.h
 * 
 */
enum litefw_Fw_Type{
    eFW_TYPE_MBN_GOBI, // Not supported in litefw
    eFW_TYPE_MBN,      // Not supported in litefw
    /*! CWE File */
    eFW_TYPE_CWE,
    /*! NVU File */
    eFW_TYPE_NVU,
    /*! SPK File */
    eFW_TYPE_SPK,
    /*! Invalid File */
    eFW_TYPE_INVALID,
    /*! CWE and NVU */
    eFW_TYPE_CWE_NVU,
};

/**
 * \ingroup litefw
 * 
 * Device model family
 */
enum litefw_Models{
    /*! Chipset family unknown */
    eModel_Unknown=-1,
    /*! 9x15 chipset based */
    eModel_9X15=0,
    /*! WP devices based on 9x15 chipset */
    eModel_WP9X15=1,
    /*! 9x30 chipset based or equivalent */
    eModel_9X30=2,
    /*! 9x07 chipset based or equivalent */
    eModel_9x07=3,
    /*! 9x06 chipset based or equivalent */
    eModel_9x06=4
};

/* QDL mode */
enum litefw_QDL_MODEs{
    /*! QDL mode unknown */
    eQDL_MODE_Unknown=-1,
    /*! QDL mode initialized */
    eQDL_MODE_INIT=0,
    /*! QDL mode Serial over USB */
    eQDL_MODE_TTYUSB=1,
    /*! QDL mode UART */
    eQDL_MODE_UART0=2,
};

/* QDL mode Hardware flow control */
enum litefw_QDL_FLOW_CONTROLs{
    /*! HW flow control unknown */
    eQDL_HW_FLOW_Unknown=-1,
    /*! HW flow control initialized */
    eQDL_HW_FLOW_INIT=0,
    /*! HW flow control enabled */
    eQDL_HW_FLOW_ENABLE=1,
    /*! HW flow control disabled */
    eQDL_HW_FLOW_DISABLE=2,
};

/**
 * \ingroup litefw
 * 
 * Modem state enum
 */
enum fwdwl_modem_states
{
    /*! Modem boot and hold mode */
    eFWDWL_STATE_BOOT_AND_HOLD,
    /*! Modem online mode */
    eFWDWL_STATE_ONLINE,
    /*! Modem disconnected */
    eFWDWL_STATE_DISCONNECTED,
    /*! Modem state unknown */
    eFWDWL_STATE_UNKNOWN,
};

/**
 * \ingroup litefw
 * 
 * Modem adapter mode enum 
 */
enum fwdwl_modem_mode
{
    /*! Modem adapter in RmNet mode */
    eLITE_MODEM_MODE_QMI=1,                         // modem is in QMI mode
    /*! Modem adapter in MBIM mode */
    eLITE_MODEM_MODE_MBIM,                          // modem is in MBIM mode
};

/**
 * \ingroup litefw
 * 
 * Error codes for applications 
 */
enum litefw_app_error_code
{
    /*! Success */
    eLITE_FWDWL_APP_OK,
    /*! Generic error. Check logs. */
    eLITE_FWDWL_APP_ERR_GEN=101,
    /*! Invalid arguments provided */
    eLITE_FWDWL_APP_ERR_INVALID_ARG,
    /*! Error in communicating with QMI FDs. Check logs. */
    eLITE_FWDWL_APP_ERR_QMI,
    /*! A lite-fw API has failed. Check logs. */
    eLITE_FWDWL_APP_ERR_LITEFW,
    /*! Modem state is unknown. Maybe not connected to host. */
    eLITE_FWDWL_APP_ERR_MODEM_STATE,
    /*! Error in setting modem crash action to reset */
    eLITE_FWDWL_APP_ERR_INVALID_CRASH_ACTION_STATE,
    /*! Error getting Model Family */
    eLITE_FWDWL_APP_ERR_INVALID_MODEL_FAMILY,
    /*! Error in communicating with QDL FDs. Check logs. */
    eLITE_FWDWL_APP_ERR_QDL,
    /*! Error when sending QMI requests */
    eLITE_FWDWL_APP_ERR_QMI_SEND_FAILURE,
    /*! Error when waiting for QMI responses */
    eLITE_FWDWL_APP_ERR_QMI_WAIT_RSP_FAILURE,
    /*! Error when switching modem operating mode */
    eLITE_FWDWL_APP_ERR_SWITCH_MODE_FAILURE,
    /*! Failed to initialize QMUX transport */
    eLITE_FWDWL_APP_ERR_TRANSPORT_INIT_FAILURE,
    /*! Failed to get service client ID */
    eLITE_FWDWL_APP_ERR_GET_SVC_CLIENT_ID_FAILURE,
    /*! Failed to initialize QmiSyncObject */
    eLITE_FWDWL_APP_ERR_SYNC_OBJECT_INIT_FAILURE,
    /*! Failed to enter Download mode */
    eLITE_FWDWL_APP_ERR_WAIT_DL_MODE_FAILURE,
    /*! Failed to enter APP mode */
    eLITE_FWDWL_APP_ERR_WAIT_APP_MODE_FAILURE,
    /*! No image to download */
    eLITE_FWDWL_APP_ERR_NO_IMAGE_TO_DOWNLOAD,
    /*! Error when packing objects */
    eLITE_FWDWL_APP_ERR_PACK_OBJ_FAILURE,
    /*! Error when unpacking objects */
    eLITE_FWDWL_APP_ERR_UNPACK_OBJ_FAILURE,
    /*! Conflict with Modem Manager */
    eLITE_FWDWL_APP_ERR_MODEM_MANAGER_CONFLICT,
    /*! Device unresponsive in B&H mode */
    eLITE_FWDWL_APP_ERR_UNRESPONSIVE_IN_DOWNLOAD_MODE,
    /*! Failed to initialize control service */
    eLITE_FWDWL_APP_ERR_INIT_CTRL_FAILURE,
    /*! Device unexpectedly removed */
    eLITE_FWDWL_APP_ERR_UNEXPECTED_REMOVAL,
    /*! Images not stored in device FW slots */
    eLITE_FWDWL_APP_ERR_IMAGE_NOT_STORED,
    /*! Undefined initialization value.  Application should not finish with this code. */
    eLITE_FWDWL_APP_UNDEFINED = 0xffffffff
};

/**
 * \ingroup litefw
 * 
 * Firmware download type 
 */
enum fwdwl_type
{
    /*! Firmware download type not specified */
    eFWDWL_TYPE_UNSPECIFIED,        // Download type not specified
    /*! Image switch type of firmware download */
    eFWDWL_TYPE_IMG_SWITCH,         // Image switch scenario, set images preference (0x0048)
    /*! Non image switch type of firmware download */
    eFWDWL_TYPE_REG_DWLD,           // Non image switch scenario, plain switch to B&H mode (0x003E)
    /*! Factory multi-image scenario */
    eFWDWL_TYPE_FACTORY_MULTI_IMAGE
};

/**
 * \ingroup litefw
 * 
 * Structure containing user options related to FW download
 * 
 * \param   is_pcie_dev
 *          - Flag indicating if device is in PCIe mode.
 *          - true: Device is in PCIe mode.
 *          - false: Device is in USB mode
 * 
 * \param   dev_mode_str
 *          - Device mode string
 *          - MBIM: Device is configured to MBIM mode
 *          - QMI: Device is configure to RmNet mode
 * 
 * \param   qdl_dev_path
 *          - Device QDL port path
 * 
 * \param   dev_path
 *          - Device network adapter path
 * 
 * \param   dm_path
 *          - Device DM port path
 * 
 * \param   fw_image_path
 *          - Path to FW image folder.  Mandatory field from user input.
 * 
 * \param   log_file_path
 *          - Path to log file
 * 
 * \param   qdl_usb_path
 *          - Reserved
 * 
 * \param   cwe_image_pref
 *          - File name of the FW image specified for image preference
 * 
 * \param   nvu_image_pref
 *          - File name of the carrier PRI image specified for image preference
 * 
 * \param   usb_path
 *          - USB device path in a format of bus#_port#
 * 
 * \param   num_of_dev_retries
 *          - Number of device connection retries after a successful FW download
 *          - Retry interval is 5 seconds
 * 
 * \param   modelfamily
 *          - Device chipset family
 *          - 1: 9x15
 *          - 3: 9x30
 *          - 4: 9x07/9x50/sdx55
 * 
 * \param   download_type
 *          - Type of the FW download
 *          - 1: Image switch
 *          - 2: Non image switch
 *          - 3: Factory multi-image download
 * 
 * \param   force_download
 *          - Flag indicating a force image download during an image switch scenario
 *          - true: Force image download
 *          - false: Only download images if device does not have them already
 * 
 * \param   show_img_info
 *          - Flag to display image info. This is not a FW download related option.
 *          - true: Display image info. No further FW download.
 *          - false: Do FW download.  No image info display.
 * 
 * \param   lBlockSize
 *          - File read block size in bytes
 * 
 * \param   enable_auto_sim
 *          - True indicates to enable device based image switching based on SIM
 * 
 * \param   is_openwrt
 *          - True indicates the host platform is an openwrt platform
 * 
 * \param   sync_delay
 *          - Number of seconds to delay after a CTL_SYNC_REQ/RESP exchange
 *          - Zero means no delay
 *          
 * \param   usb_dev_loc
 *          - USB device location information
 *          - See usb_dev_loc_info for details
 * 
 * \param   pcie_dev_loc
 *          - PCIe device location information
 *          - See pcie_dev_loc_info for details
 */
struct _userOptions
{
    bool is_pcie_dev;
    char dev_mode_str[DEV_MODE_STR_LEN];
    char qdl_dev_path[MAX_PATH_LEN];
    char dev_path[MAX_PATH_LEN];
    char dm_path[MAX_PATH_LEN];
    char fw_image_path[MAX_PATH_LEN];
    char log_file_path[MAX_PATH_LEN];
    char qdl_usb_path[MAX_USB_PATH_LEN];
    char cwe_image_pref[NAME_MAX];
    char nvu_image_pref[NAME_MAX];
    char single_file[NAME_MAX];
    char usb_path[USB_PATH_LEN];
    int  num_of_dev_retries;
    int  modelfamily;
    int  download_type;
    bool force_download;
    bool show_img_info;
    unsigned long lBlockSize;
    bool enable_auto_sim;
    image_node_t * images_list;
    int images_list_size;
    bool is_openwrt;    // OpenWrt platforms have limited resources, and many commands are not supported.
                        // We will have to trim down unsupported commands.
    unsigned char sync_delay;   // Number of seconds to delay after a CTL_SYNC_REQ/RESP exchange 
    bool reset_device;
    bool delete_images;
    uint8_t image_type_to_delete;
    usb_dev_loc_info usb_dev_loc;
    pcie_dev_loc_info pcie_dev_loc;
};

/**
 * \ingroup litefw
 * 
 *  This function prints pBuffer in hex format.
 *
 *  \param[in]  pBuffer
 *              - Data buffer
 *
 *  \param[in]  bufSize
 *              - Data buffer size
 *
 *  \param[in]  read
 *              - Flag indicating the data buffer is for read or write packet
 *              - true: read data buffer
 *              - false: write data buffer
 */
void print_hex(void * pBuffer, int bufSize, bool read );

/**
 * \ingroup litefw
 * 
 *  This function enables/disables lite firmware debug logs.
 *
 *  \param[in]  log_en
 *              - Logs enable/disable flag.
 */
void litefw_logsenable(int log_en);

/**
 * \ingroup litefw
 * 
 *  This structure contains information of the response parameters associated
 *  with a Read Transparent API.
 *
 *  \param  szModelid_str
 *          - Model Name String
 *
 *  \param  szFwversion_str
 *          - Firmware Version String.
 *
 *  \param  szSku_str
 *          - SKU String.
 *
 *  \param  szPackageid_str
 *          - Package ID String.
 *
 *  \param  szCarrier_str
 *          - Carrier String.
 *
 *  \param  szCarrierPriversion_str
 *          - Carrier PRI Version String.
 */
typedef struct _litefw_FirmwareInfo_
{
    char szModelid_str[SLQSIMINFO_MODELID_SZ+NULL_TERMINATOR_CHAR_SIZE];
    char szFwversion_str[SLQSIMINFO_FWVERSION_SZ+NULL_TERMINATOR_CHAR_SIZE];
    char szSku_str[SLQSIMINFO_SKU_SZ+NULL_TERMINATOR_CHAR_SIZE];
    char szPackageid_str[SLQSIMINFO_PACKAGEID_SZ+NULL_TERMINATOR_CHAR_SIZE];
    char szCarrier_str[SLQSIMINFO_CARRIER_SZ+NULL_TERMINATOR_CHAR_SIZE];
    char szCarrierPriversion_str[SLQSIMINFO_PRIVERSION_SZ+NULL_TERMINATOR_CHAR_SIZE];
}litefw_FirmwareInfo;

/**
 * \ingroup litefw
 * 
 *  This API extracts the image info of the specified image
 * 
 *  \param[in]  img
 *              - Image file path and name
 * 
 *  \param[out] info
 *              - Image info
 *              - See \ref litefw_FirmwareInfo for more information
 * 
 *  \return 0 on success or \ref litefw_fwdwl_error_codes for error scenarios
 */
int litefw_ExtractImageParamsByFile(char * img, litefw_FirmwareInfo * info);

/**
 * \ingroup litefw
 * 
 *  This API Extrace Firmware Parameters From FW and PRI Files specified.
 *
 *  \param[in]  fw
 *              - Firmware file path and name.
 *
 *  \param[in]  pri
 *              - Carrier PRI file path and name
 *
 *  \param[out]  info
 *               - See \ref litefw_FirmwareInfo for more information.
 *
 *  \return 0 on success, \ref litefw_fwdwl_error_codes error value otherwise
 */
int litefw_ExtractFirmwareParametersByFile(char * fw, char * pri, litefw_FirmwareInfo * info);

/**
 * \ingroup litefw
 * 
 *  This API Extrace Firmware Parameters From Path.
 *
 *  \param[in]  pImagePath
 *              - Firmware Folder Path.
 *
 *  \param[out] info
 *              - See \ref litefw_FirmwareInfo for more information.
 * 
 *  \param[out] bIsSpkImg
 *              - True indicates the image is an spk image; otherwise, false.
 *
 *  \return 0 on success, \ref litefw_fwdwl_error_codes error value otherwise
 */
int litefw_ExtractFirmwareParametersByPath(char *pImagePath, litefw_FirmwareInfo *info, bool * bIsSpkImg);

/**
 * \ingroup litefw
 * 
 *  This API Build Image Preference Request Using Firmware Information.
 *
 *  \param[in]  info
 *              - See \ref litefw_FirmwareInfo for more information.
 *
 *  \param[out] pack
 *              - See \ref pack_fms_SetImagesPreference_t for more information.
 *
 *	\param[in]	force
 *				- Flag indicating force image download or not
 *				  1: Force download
 *				  0: Device decides what images need to be downloaded
 *
 *  \param[in]  factory_mode
 *              - Flag indicating factory mode that requires storing FW images in slots.
 *                1: Factory_mode
 *                0: Not factory_mode
 *
 *  \return 0 on success, \ref litefw_fwdwl_error_codes error value otherwise
 */
int litefw_BuildImagesPreferenceRequest(litefw_FirmwareInfo info, pack_fms_SetImagesPreference_t * pack, bool force, bool factory_mode);

/**
 * \ingroup litefw
 * 
 *  This API build image preference request for device AUTO-SIM feature.
 *
 *  \param[out] pack
 *              - See \ref pack_fms_SetImagesPreference_t for more information.
 *
 *  \return 0 on success, \ref litefw_fwdwl_error_codes error value otherwise
 */
int litefw_BuildAutoSimImgPrefRequest(pack_fms_SetImagesPreference_t * pack);

/**
 * \ingroup litefw
 * 
 *  This API Calculate Image Mask for Firmware Download.
 *
 *  \param[in]  SetPrefRspFromModem
 *              - See \ref unpack_fms_SetImagesPreference_t for more information.
 *
 *  \return Image Mask
 *          - IMG_MASK_MDM | IMG_MASK_PRI
 */
int litefw_CalculateImageMask (unpack_fms_SetImagesPreference_t SetPrefRspFromModem);

/**
 * \ingroup litefw
 * 
 *  This API Get File Type By Path
 *
 *  \param[in]  szPath
 *              - See \ref litefw_FirmwareInfo for more information.
 *
 *  \return eFW_TYPE_INVALID on error, \ref litefw_Fw_Type value otherwise
 */
int litefw_getFileType(char* szPath);

/**
 * \ingroup litefw
 * 
 *  This API Get Firmware Download Type By Path
 *
 *  \param[in]  szPath
 *              - See \ref litefw_FirmwareInfo for more information.
 *
 *  \return eFW_TYPE_INVALID on error, \ref litefw_Fw_Type value otherwise
 */
int litefw_getFwDownloadType(char* szPath);

/**
 * \ingroup litefw
 * 
 *  This API Download Firmware.
 *
 *  \param[in]  pImagePath
 *              - Firmware Folder Path.
 *
 *  \param[in]  szTTYPath
 *              - QDL Device Path.
 *
 *  \param[in]  iFWImageType
 *              - Firmware Type.
 *              - See \ref litefw_Fw_Type
 *
 *  \param[in]  image_mask
 *              - Image Mask.
 *                - IMG_MASK_MDM | IMG_MASK_PRI
 *
 *  \param[in]  iModelFamily
 *              - Modem Family.
 *              - See \ref litefw_Models
 *
 *  \param[in]  img_list_size
 *              - Size of images list
 * 
 *  \param[in]  img_list
 *              - Images list
 * 
 *  \return 0 on success, \ref litefw_fwdwl_error_codes error value otherwise
 */
unsigned int litefw_DownloadFW(char *pImagePath,char *szTTYPath,int iFWImageType, int image_mask, int iModelFamily, int img_list_size, image_node_t * img_list);

/**
 * \ingroup litefw
 * 
 *  This API Get Model Famliy from a model string.
 *
 *  \param[in]  pModelString
 *              - Model String.
 *
 *  \return eModel_Unknown on Error, \ref litefw_Models value otherwise
 */
int litefw_GetModelFamily(char *pModelString);

/**
 * \ingroup litefw
 * 
 *  This API Check Valid Firmware Information to build Image Prefernce Request.
 *
 *  \param[in]  info
 *              - See \ref litefw_FirmwareInfo for more information.
 *
 *  \return 0 on success, -1 error value otherwise
 */
int litefw_CheckValidFirmwareInfo(litefw_FirmwareInfo info);

/**
 * \ingroup litefw
 * 
 *  This API Get Lib SDP Version.
 *
 *  \return Version String
 */
char* litefw_GetVersion();

/**
 * \ingroup litefw
 * 
 *  This function is the Custom Log prototype.
 *
 *  \param[in]  lvl
 *              - Log level.
 *
 *  \param[in]  buff
 *              - Log String.
 *
 *  \return none
 */
typedef void (* litefwlogger)(uint8_t lvl, const char* buff);

/**
 * \ingroup litefw
 * 
 *  This API Set Custom Log function.
 *
 *  \param[in]  func
 *              - See \ref litefwlogger for more information.
 *
 *  \return none
 */
int litefw_set_log_func(logger func);

/**
 * \ingroup litefw
 * 
 *  This API Set Read BlockSize.
 *
 *  \param[in] lBlockSize
 *             - Firmware Read Block Size.
 *
 *  \return none
 */
void litefw_SetReadBlockSize(unsigned long lBlockSize);

/**
 * \ingroup litefw
 * 
 *  This API switch 9x07 modem to download mode.
 *
 *  \param[in]  szTTYPath
 *              - QDL Device Path.
 *
 * \return 0 on success, -1 error value otherwise
 */
int litefw_switch_9x07_to_downloadmode(char *szTTYPath);


/**
 * \ingroup litefw
 * 
 *  This API switch modem to boot hold modem via QDL port.
 *
 *  \param[in]  szTTYPath
 *              - QDL Device Path.
 *
 * \return 0 on success, -1 error value otherwise
 */
int litefw_switch_to_BootHoldMode(char *szTTYPath);

/**
 * \ingroup litefw
 * 
 *  This API set QDL port donwload mode.
 *
 *  \param[in]  iMode
 *              - QDL Download Mode.
 *                  - litefw_QDL_MODEs
 *
 * \return 0 on success, -1 error value otherwise
 */
int litefw_SetQTLDownloadMode(int iMode);

/**
 * \ingroup litefw
 * 
 *  This API Get QDL port donwload mode.
 *
 * \return eQDL_MODE_Unknown on Error, \ref litefw_QDL_MODEs value otherwise
 */
int litefw_GetQTLDownloadMode();

/**
 * \ingroup litefw
 * 
 * This API Set QDL port Hardware flow control.
 *
 * \param[in]  iMode
 *              - \ref litefw_QDL_FLOW_CONTROLs
 *
 * \return 0 on success, -1 error value otherwise
 */
int litefw_SetQTLHWFlowControl(int iMode);

/**
 * \ingroup litefw
 * 
 *  This API Get QDL port Hardware flow control.
 *
 *
 * \return eQDL_HW_FLOW_Unknown on Error, \ref litefw_QDL_FLOW_CONTROLs value otherwise
 */
int litefw_GetQTLHWFlowControl();

/**
 * \ingroup litefw
 * 
 * This API sends image preferences to device for image switching type of FW download.
 *
 * \param[in]   pPack_request
 *              - QMI request in \ref pack_fms_SetImagesPreference_t
 * 
 * \param[out]  pSetPrefRspFromModem
 *              - Device QMI response in \ref unpack_fms_SetImagesPreference_t
 * 
 * \param[in]   pUserOption
 *              - User options
 *
 * \return 0 on success, \ref litefw_app_error_code error values otherwise
 */
int SendImagesPreference(pack_fms_SetImagesPreference_t * pPack_request, unpack_fms_SetImagesPreference_t * pSetPrefRspFromModem, 
    struct _userOptions * pUserOption);

/**
 * \ingroup litefw
 * 
 * This API switch device to download mode for non image switching type of FW download
 *
 * \param[in]   user_options
 *              - User specified options
 *              - See \ref _userOptions for more details
 * 
 * \param[out]  pSetFirmwarePref
 *              - Device QMI response in unpack_dms_SetFirmwarePreference_t
 *
 * \return 0 on success, \ref litefw_app_error_code error values otherwise
 */
int SetFirmwarePref(struct _userOptions * user_options, unpack_dms_SetFirmwarePreference_t * pSetFirmwarePref);

/**
 * \ingroup litefw
 * 
 * This API reset device
 *
 * \return 0 on success, \ref litefw_app_error_code error values otherwise
 */
int ResetModem();

/**
 * \ingroup litefw
 * 
 * This API verify the FW download status and device images after FW download
 *
 * \param[in]   user_options
 *              - User specified options
 *              - See \ref _userOptions for more details
 * 
 * \return 0 on success, \ref litefw_app_error_code error values otherwise
 */
int VerificationAfterDownload(struct _userOptions * user_options);

/**
 * \ingroup litefw
 * 
 * This API verify the device AUTO-SIM based image switch feature
 *
 * \param[in]   user_options
 *              - User specified options
 * 
 * \return 0 on success, \ref litefw_app_error_code error values otherwise
 *
 */
int VerifyAutoSimImageSwitch(struct _userOptions * user_options);

/**
 * \ingroup litefw
 * 
 * This API locate modem network adapter device path
 *
 * \param[in]   user_opt_data
 *              - User specified options
 *              - See \ref _userOptions for more details
 * 
 * \return true if adapter path located successfully, false otherwise.
 */
bool locate_adapter_path(struct _userOptions * user_opt_data);

/**
 * \ingroup litefw
 * 
 * This API locate modem QDL port device path
 *
 * \param[in]   user_opt_data
 *              - User specified options
 *              - See \ref _userOptions for more details
 * 
 * \return true if QDL path located successfully, false otherwise.
 */
bool locate_qdl_path(struct _userOptions * user_opt_data);

/**
 * \ingroup litefw
 * 
 * This API finds device adapter path
 *
 * \param[in]   user_opt_data
 *              - User specified options
 *              - See \ref _userOptions for more details
 * 
 * \return true if device adapter path found successfully, false otherwise.
 */
bool find_adapter_path(struct _userOptions * user_opt_data);

/**
 * \ingroup litefw
 * 
 * This API create an image list which includes all the image files from the user specified
 * FW location folder.
 *
 * \param[in]   pUserOptData
 *              - User specified options
 *              - See \ref _userOptions for more details
 * 
 * \param[out]  num_of_images
 *              - Number of images included in the list upon a successful return
 * 
 * \param[in,out]   image_list
 *              - A linked list including all the images from FW location folder
 *              - See \ref image_node_t for more details
 * 
 * \param[in]   no_check
 *              - A flag indicating if further image validation is required or not.
 *              - true means no image validation is required.
 * 
 * \return true if image list created successfully, false otherwise
 */
bool get_image_list(struct _userOptions * pUserOptData, int * num_of_images, image_node_t ** image_list, bool no_check);

/**
 * \ingroup litefw
 * 
 * This API checks device mode.
 *
 * \param[in]   pUserOptData
 *              - User specified options
 *              - See \ref _userOptions for more details
 * 
 * \return true on success, false on failure
 */
bool litefw_cfg_dev_mode(struct _userOptions * pUserOptData);

/**
 * \ingroup litefw
 * 
 * This API checks device chip set family.
 *
 * \param[in]   pUserOption
 *              - User specified options
 *              - See \ref _userOptions for more details
 * 
 * \return 0 on success, litefw_app_error_code error values otherwise
 */
int check_dev_family(struct _userOptions * pUserOption);

/**
 * \ingroup litefw
 * 
 * This API deletes all device stored images which have the same image type
 * as the specified image type.
 *
 * \param[in]   pUserOption
 *              - User specified options
 *              - See \ref _userOptions for more details
 * 
 * \return 0 on success, litefw_app_error_code error values otherwise
 */
int delete_all_images(struct _userOptions * pUserOption);

/**
 * \ingroup litefw
 * 
 * This API initiate a FW download session based on the specified user options.
 *
 * \param[in]   userOptData
 *              - User specified options
 *              - See \ref _userOptions for more details
 * 
 * \return 0 on success, litefw_app_error_code error values otherwise
 * 
 * \note The log_file_path parameter in userOptData is not used in this function.
 *       Message logging is done by either external logging routine (if registered
 *       via litefw_set_log_func), or syslog (if no external logging routine is in use).
 */
int litefw_download(struct _userOptions userOptData);

/**
 * \ingroup litefw
 * 
 * This API resets device when device is in B&H mode.
 *
 * \param[in]   userOptData
 *              - User specified options
 *              - See \ref _userOptions for more details
 * 
 * \return 0 on success, litefw_app_error_code error values otherwise
 */
int litefw_reset_device(struct _userOptions * userOptData);

/**
 * \ingroup litefw
 * 
 *  This API deletes all device stored images.
 *
 *  \param[in]  image_type
 *              - Type of images to be deleted.
 *              - 0: FW images
 *              - 1: PRI images
 *              - 0xFF: All images
 *
 *  \return 0 on success, litefw_fwdwl_error_codes error values otherwise
 */
int litefw_delete_all_images(uint8_t image_type);

#define libSDP_GetVersion litefw_GetVersion
#define libSDP_CalculateImageMask litefw_CalculateImageMask
#define libSDP_getFileType litefw_getFileType
#define libSDP_ExtractFirmwareParametersByPath litefw_ExtractFirmwareParametersByPath
#define libSDP_GetModelFamily litefw_GetModelFamily
#define libSDP_CheckValidFirmwareInfo litefw_CheckValidFirmwareInfo
#define libSDP_BuildImagesPreferenceRequest litefw_BuildImagesPreferenceRequest
#define libSDP_DownloadFW litefw_DownloadFW
#define libsdp_set_log_func litefw_set_log_func
#define libsdp_SetReadBlockSize litefw_SetReadBlockSize
#define LIBSDP_CARRIER_PACKAGE_SKU LITEFW_CARRIER_PACKAGE_SKU
#define LIBSDP_SKU_STRING_LENGTH LITEFW_SKU_STRING_LENGTH
typedef litefw_FirmwareInfo libSDP_FirmwareInfo;
typedef litefwlogger libsdplogger;

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif // _LITE_FW_H_

