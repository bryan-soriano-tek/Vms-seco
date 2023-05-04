/**
 * \ingroup liteqmi
 * \ingroup fms
 * \file fms.h
 */
#ifndef __FMS_PACH_H_
#define __FMS_PACH_H_ 

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include <stdint.h>

#define FMS_GOBI_MBN_IMG_ID_SIZE      16
#define LITE_TOTAL_IMAGE_ID_STRING_SIZE 100
#define FMS_GOBI_MBN_IMG_ID_STR_LEN   LITE_TOTAL_IMAGE_ID_STRING_SIZE
#define FMS_GOBI_MBN_BUILD_ID_STR_LEN LITE_TOTAL_IMAGE_ID_STRING_SIZE
#define FMS_GOBI_LISTENTRIES_MAX      2
#define FMS_MAX_IMAGE_PREFERENCE_IMAGE_SIZE 255
#define FMS_MAX_IMAGE_ID_ELEMENT 50
#define FMS_IMAGE_ID_MAX_ENTRIES 2
#define FMS_FW_PRI_BUILD_MATCH_LEN 11
#define FMS_IMAGE_ID_IMG_ID_LEN   16
#define FMS_IMAGE_ID_BUILD_ID_LEN   32
#define FMS_IMAGE_ID_MDM_IMGTYPE    0x0
#define FMS_IMAGE_ID_PRI_IMGTYPE    0x1
#define FMS_IMAGE_ID_ALL_IMGTYPE    0xFF

#define AUTO_SIM_MDM_IMG_ID "000.000_000"
#define AUTO_SIM_MDM_BLD_ID "00.00.00.00_AUTO-SIM"
#define AUTO_SIM_PRI_IMG_ID "000.000_000"
#define AUTO_SIM_PRI_BLD_ID "00.00.00.00_AUTO-SIM"

#define FORCE_DOWNLOAD_DISABLED 0
#define FORCE_DOWNLOAD_ENABLED  1

#define MDM_SLOT_MODEM_DECIDE   0xFF
#define MDM_SLOT_FACTORY        0xFE

/* CWE Sierra Package String parameter defines */
#define SLQSIMINFO_SKU_SZ           10 // SLQSIMINFO_MAX_SZ
#define SLQSIMINFO_PARTNO_SZ        10 // SLQSIMINFO_MAX_SZ
#define SLQSIMINFO_MODELID_SZ       10 // SLQSIMINFO_MAX_SZ
#define SLQSIMINFO_FWVERSION_SZ     15 // SLQSIMINFO_MAX_SZ
#define SLQSIMINFO_BOOTBLK_SZ       2 // SLQSIMINFO_MAX_SZ
#define SLQSIMINFO_CARRIER_SZ       15 // SLQSIMINFO_MAX_SZ
#define SLQSIMINFO_PRIVERSION_SZ    7 // SLQSIMINFO_MAX_SZ
#define SLQSIMINFO_PACKAGEID_SZ     3 // SLQSIMINFO_MAX_SZ

/**
 * \ingroup fms
 * 
 * This structure contains the Carrier Image parameters.
 *
 *  \param  m_nCarrierId
 *          - Unique numeric carrier ID indicating the carrier that
 *            the following images belong to
 *
 *  \param  m_nFolderId
 *          - Unique numeric folder ID indicating the folder where the
 *            images should reside on the host storage.
 *
 *  \param  m_nStorage
 *          - Information of storage type
 *          - Values
 *            - 0 - Device
 *            - 1 - Host
 *
 *  \param  m_FwImageId
 *          - Firmware image ID
 *
 *  \param  m_FwBuildId
 *          - Firmware build ID
 *
 *  \param  m_PriImageId
 *          - PRI image ID
 *
 *  \param  m_PriBuildId
 *          - PRI build ID
 *
 */

typedef struct
{
    uint32_t     m_nCarrierId;
    uint32_t     m_nFolderId;
    uint32_t     m_nStorage;
    uint8_t      m_FwImageId[FMS_GOBI_MBN_IMG_ID_STR_LEN];
    uint8_t      m_FwBuildId[FMS_GOBI_MBN_BUILD_ID_STR_LEN];
    uint8_t      m_PriImageId[FMS_GOBI_MBN_IMG_ID_STR_LEN];
    uint8_t      m_PriBuildId[FMS_GOBI_MBN_BUILD_ID_STR_LEN];
}CarrierImage_t;

/**
 * \ingroup fms
 * 
 * This structure contains the Get Image Preference information pack
 *
 *  \param  Tlvresult
 *              - Pack result
 */

typedef struct{
    uint16_t Tlvresult;
}pack_fms_GetImagesPreference_t;

/**
 * \ingroup fms
 * 
 * This structure contains the Image Element information
 *
 *  \param  imageType
 *              - Type of image
 *                 0 - Modem
 *                 1 - PRI
 *
 *  \param  imageId
 *              - Unique image identifier
 *
 *  \param  buildIdLength
 *              - Length of the build ID string (may be zero)
 *
 *  \param  pBuildId
 *              - Build ID ANSI string with length provided
 *              by the previous field
 *
 */
 
typedef struct
{
    uint8_t imageType;
    uint8_t imageId[FMS_GOBI_MBN_IMG_ID_STR_LEN];
    uint8_t buildIdLength;
    uint8_t buildId[FMS_GOBI_MBN_BUILD_ID_STR_LEN];
}FMSImageElement;

/**
 * \ingroup fms
 * 
 * This structure contains the Preference Image List information
 *
 *  \param  listSize
 *              - The number of elements in the image list
 *
 *  \param  pListEntries
 *              - Array of Image entries with size provided by
 *                previous field
 *              - See \ref FMSImageElement
 *
 */
 
typedef struct 
{
    uint8_t         listSize;
    FMSImageElement listEntries[FMS_GOBI_LISTENTRIES_MAX];
}FMSPrefImageList;

/**
 * \ingroup fms
 * 
 * This structure contains the Get Image Preference information unpack
 *
 *  \param  listSize
 *              - The number of elements in the image list
 *
 *  \param  pListEntries
 *              - Array of Image entries with size provided by
 *                previous field
 *              - See \ref FMSImageElement
 *              - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  \param  Tlvresult
 *              - Unpack result
 */


typedef struct{
    uint32_t         ImageListSize;
    FMSPrefImageList *pImageList;
    uint16_t         Tlvresult;
    swi_uint256_t    ParamPresenceMask;
}unpack_fms_GetImagesPreference_t;

/**
 * \ingroup fms
 * 
 * Get Images Preference pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 */
int pack_fms_GetImagesPreference(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    void *reqArg
);

/**
 * \ingroup fms
 * 
 * Get Images Preference unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 */
int unpack_fms_GetImagesPreference(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_fms_GetImagesPreference_t *pOutput
);


/**
 * \ingroup fms
 * 
 * This structure contains the Get Stored Images pack
 *
 *  \param  Tlvresult
 *              - Pack result
 */

typedef struct{
    uint16_t Tlvresult;
}pack_fms_GetStoredImages_t;

/**
 * \ingroup fms
 * 
 * This structure contains the Image ID list element Information
 *
 *  \param  storageIndex
 *          - Index in storage where the image is located(a value of 0xFF
 *            indicates that the storage for this type of image is not relevant)
 *
 *  \param  failureCount
 *          - Number of consecutive write attempts to this storage index
 *            that have failed(a value of 0xFF indicates unspecified)
 *
 *  \param  imageID
 *          - Image unique identifier(max 16 chars.)
 *
 *  \param  buildIDLength
 *          - Length of the build ID string. If there is no build ID, this
 *            field will be 0 and no data will follow.
 *
 *  \param  buildID
 *          - String containing image build information( Max 100 characters )
 */
typedef struct 
{
    uint8_t storageIndex;
    uint8_t failureCount;
    uint8_t imageID[FMS_GOBI_MBN_IMG_ID_STR_LEN];
    uint8_t buildIDLength;
    uint8_t buildID[FMS_GOBI_MBN_BUILD_ID_STR_LEN];
}FMSImageIdElement;


/**
 * \ingroup fms
 * 
 * This structure contains the list entry Information
 *
 *  \param  imageType
 *          - Type of image
 *              - 0 - Modem
 *              - 1 - PRI
 *
 *  \param  maxImages
 *          - Maximum number of images of this type that may be stored
 *            concurrently on the device
 *
 *  \param  executingImage
 *          - Index (into the next array) of image that is currently executing
 *
 *  \param  imageIDSize
 *          - The number of elements in the image ID list
 *
 *  \param  imageIDElement
 *          - Array of ImageIDElement Structure ( Max 50 elements )
 *          - See \ref FMSImageIdElement
 */
typedef struct
{
    uint8_t                  imageType;
    uint8_t                  maxImages;
    uint8_t                  executingImage;
    uint8_t                  imageIDSize;
    FMSImageIdElement imageIDElement[FMS_MAX_IMAGE_ID_ELEMENT];
}FMSImageIDEntries;


/**
 * \ingroup fms
 * 
 * This structure contains the Get Stored Images List
 *
 *  \param  listSize
 *          - The number of elements in the image list
 *
 *  \param  imageIDEntries
 *          - Array of ImageIDEntries Structure ( Max 2 entries )
 */
typedef struct
{
    uint8_t                  listSize;
    FMSImageIDEntries imageIDEntries[FMS_IMAGE_ID_MAX_ENTRIES];
}FMSImageList;


/**
 * \ingroup fms
 * 
 * This structure contains the Get Stored Images unpack
 *
 *  \param  imagelistSize
 *              - The total number of bytes in imageList
 *
 *  \param  imageList
 *              - Array of Image entries with size provided by
 *                previous field
 *              - See \ref FMSImageElement
 *              - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  \param  Tlvresult
 *              - Unpack result
 */


typedef struct{
    uint32_t       imagelistSize;
    FMSImageList   imageList;
    uint16_t       Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_fms_GetStoredImages_t;


/**
 * \ingroup fms
 * 
 * Get Images Preference pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 */
int pack_fms_GetStoredImages(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_fms_GetStoredImages_t *reqArg
);

/**
 * \ingroup fms
 * 
 * Get Images Preference unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 */

int unpack_fms_GetStoredImages(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_fms_GetStoredImages_t *pOutput);


/**
 * \ingroup fms
 * 
 * This structure contains the Set Images Preference pack
 *
 *  \param  imageListSize
 *              - Image List Size
 *
 *  \param  pImageList
 *              - Image List
 *              - See \ref FMSPrefImageList
 *
 *  \param  bForceDownload
 *              - 0 - Not Force Donwload.
 *              - 1 - Focrce Download.
 *
 *  \param  modemindex
 *              - Modem Index.
 *
 *  \param  Tlvresult
 *              - Unpack result
 */

typedef struct{
    uint32_t imageListSize;
    FMSPrefImageList  *pImageList;
    uint32_t bForceDownload;
    uint8_t modemindex;
    uint16_t Tlvresult;
}pack_fms_SetImagesPreference_t;

/**
 * \ingroup fms
 * 
 * This structure contains the Set Images Preference unpack
 *
 *  \param  ImageTypesSize
 *              - Image Type Size
 *
 *  \param  ImageTypes
 *              - Image Type
 *              - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  \param  Tlvresult
 *              - Unpack result
 */
typedef struct{
    uint32_t       ImageTypesSize;
    uint8_t        ImageTypes[FMS_MAX_IMAGE_PREFERENCE_IMAGE_SIZE];
    uint16_t       Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_fms_SetImagesPreference_t;

/**
 * \ingroup fms
 * 
 * Set Images Preference pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 */
int pack_fms_SetImagesPreference(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_fms_SetImagesPreference_t *reqArg
);

/**
 * \ingroup fms
 * 
 * Set Images Preference unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 */

int unpack_fms_SetImagesPreference(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_fms_SetImagesPreference_t *pOutput);

/**
 * \ingroup fms
 * 
 *  This API distills valid Firmware/PRI combinations from GetStoredImages result
 *
 *  \param[in]  pStoredImageList
 *          - image list returned from GetStoredImages 
 *          - See \ref FMSImageList
 *
 *  \param[in,out]  pValidCombinationSize
 *          - number of combination passed in and returned
 *
 *  \param[out]  pValidCombinations
 *          - valid combinations returned
 *          - See \ref CarrierImage_t
 *
 *  \return
 *          - eQCWWAN_ERR_INVALID_ARG - Invalid parameters
 *          - eQCWWAN_ERR_BUFFER_SZ - No enough element to store combinatons returned
 *
 *  \sa     See qmerrno.h for eQCWWAN_xxx error values
 */

uint32_t GetValidFwPriCombinations(FMSImageList *pStoredImageList,
        uint32_t *pValidCombinationSize,
        CarrierImage_t *pValidCombinations);

/**
 * \ingroup fms
 * 
 *  Image information of the image to be removed from device memory .
 *
 *  @param  ImageInfo
 *          - Information of the image to be removed
 *
 */
typedef struct
{
	FMSImageElement ImageInfo;
} pack_fms_DeleteStoredImage_t;

typedef unpack_result_t  unpack_fms_DeleteStoredImage_t;

/**
 * \ingroup fms
 * 
 *  Pack function for deleting a specified stored image.
 * 
 *  @param[in,out] pCtx qmi request context
 *  @param[out] pReqBuf qmi request buffer
 *  @param[out] pLen qmi request length
 *  @param[in] pReqParam request prarmeters
 *
 *  @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int pack_fms_DeleteStoredImage(
	pack_qmi_t  *pCtx,
	uint8_t *pReqBuf,
	uint16_t *pLen,
	pack_fms_DeleteStoredImage_t *pReqParam
);

/**
 * \ingroup fms
 * 
 *  Unpack function for deleting a specified image.
 * 
 *  @param[in]   pResp       qmi response from modem
 *  @param[in]   respLen     qmi response length
 *  @param[out]  pOutput     response unpacked
 *
 *  @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  @sa     See qmerrno.h for eQCWWAN_xxx error values
 *
 */
int unpack_fms_DeleteStoredImage(
	uint8_t *pResp,
	uint16_t respLen,
	unpack_fms_DeleteStoredImage_t *pOutput
);

/**
 * \ingroup fms
 * 
 *  This structure contains device stored image sublist entry.
 *
 *  @param  storage_index
 *          Index in storage where the image is located.
 *          If not relevant for the image type, this field is set to 0xFF.
 *
 *  @param  failure_count
 *          Number of consecutive write attempts to this storage index that have failed.
 *          If not relevant for the image type, this field is set to 0xFF.
 *
 *  @param  image_id
 *          Image unique identifier
 * 
 *  @param  build_id_len
 *          Build identifier length
 * 
 *  @param  lru_rank
 *          Least Recently Used rank for the firmware image.
 *          This field is not relevant to PRI image and set to 0xFF.
 * 
 *  @param  switch_failure
 *          Number of consecutive firmware image switching failures using this storage index.
 *          If not relevant for the image type or not supported, this field is set to 0xFF.
 * 
 *  @param  dld_source
 *          Source info on how the image was downloaded to device
 *          - 0x0:  Local download
 *          - 0x1:  FOTA download
 *          - 0xFF: Not applicable
 *          This field is only relevant to firmware image.  
 *          For other image types, such as PRI images, this field is set to 0xFF.
 * 
 */
typedef struct {
    uint8_t         storage_index;
    uint8_t         failure_count;
    uint8_t         image_id[FMS_IMAGE_ID_IMG_ID_LEN  + 1];
    uint8_t         build_id_len;
    uint8_t         build_id[FMS_IMAGE_ID_BUILD_ID_LEN + 1];
    uint8_t         lru_rank;
    uint8_t         switch_failure;
    uint8_t         dld_source;
} image_sublist_entry_t;

#define FMS_MAX_SUBLIST_ENTRIES 50

/**
 * \ingroup fms
 * 
 *  This structure contains device stored image list info.
 *
 *  @param  max_images
 *          Maximum number of images of this type that may be stored on the device concurrently.
 *
 *  @param  running_image
 *          Index of the currently running image in the following sublist.
 *          This value starts at 0.  If the currently running image is not saved in the device storage,
 *          for example if has been deleted, this field is set to 0xFF.
 * 
 *  @param  num_of_sub_images
 *          Number of sub images in the following sublist_entries array
 * 
 *  @param  sublist_entries
 *          Image sublist entries.
 * 
 */
typedef struct {
    uint8_t                 max_images;
    uint8_t                 running_image;
    uint8_t                 num_of_sub_images;
    image_sublist_entry_t   sublist_entries[FMS_MAX_SUBLIST_ENTRIES];
} stored_images_list_t;

/**
 * \ingroup fms
 * 
 *  This structure contains all device stored images info (both FW and PRI)
 *
 *  @param  fw_images_list
 *          FW images list.
 *
 *  @param  pri_images_list
 *          PRI images list.
 *
 *  @param  Tlvresult
 *          unpack result
 * 
 *  @param  ParamPresenceMask
 *          Bitmask representation to indicate valid parameters.
 * 
 */
typedef struct {
    stored_images_list_t    fw_images_list;
    stored_images_list_t    pri_images_list;
    uint16_t                Tlvresult;
    swi_uint256_t           ParamPresenceMask;
} unpack_fms_SlqsGetStoredImages_t;

/**
 * \ingroup fms
 * 
 *  Pack function to retrieve device stored images
 *
 *  @param[in,out] pCtx qmi request context
 *  @param[out] pReqBuf qmi request buffer
 *  @param[out] pLen qmi request length
 *
 *  @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_fms_SlqsGetStoredImages(
    pack_qmi_t *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen
);

/**
 * \ingroup fms
 * 
 *  Unpack function to retrieve device stored images
 *
 *  @param[in]   pResp          qmi response from modem
 *  @param[in]   respLen        qmi response length
 *  @param[out]  pOutput        response unpacked
 *
 *  @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 *  @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_fms_SlqsGetStoredImages(
    uint8_t * pResp,
    uint16_t respLen,
    unpack_fms_SlqsGetStoredImages_t * pOutput
);

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif
