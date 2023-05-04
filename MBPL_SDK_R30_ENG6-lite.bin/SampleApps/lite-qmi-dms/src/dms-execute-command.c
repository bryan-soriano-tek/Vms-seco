#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <QmiService.h>
#include <CtlService.h>
#include <QmiSyncObject.h>
#include "lite-qmi-dms.h"
#include "dms.h"
#include "fms.h"
#include "swidms.h"
#include "command_set.h"
#include "str_util.h"
#include "lite-qmi-demo.h"

extern void DisplayGetBandCapability(unpack_dms_SLQSGetBandCapability_t *pBandCapability);
extern void DisplayGetFirmwareInformation(unpack_dms_GetFirmwareInfo_t *pfirmwareInfo);
extern void DisplayGetSerialNumbers(unpack_dms_GetSerialNumbers_t *pSerialNumbers);
extern void DisplayGetHostDevInfoSettings(unpack_dms_SLQSSwiGetHostDevInfo_t *pSwiGetHostDevInfo);
extern void DisplaySetEventReportInd(unpack_dms_SetEventReport_ind_t *pSetEventReport_ind);
extern void DisplayGetPower(unpack_dms_GetPower_t *pUnpackGetPower);
extern void DisplayAutoSimList(unpack_swidms_SLQSSwiDmsGetAutoSimList_t *pUnpackGetAutoSimList);
extern void DisplayGetCustomFeaturesV2(unpack_dms_GetCustFeaturesV2_t *pUnpackGetCF);
extern void DeviceIsOffline();
extern void DisplayStoredImage(unpack_fms_GetStoredImages_t* stored_images);
extern void DisplaySlqsStoredImage(unpack_fms_SlqsGetStoredImages_t* stored_images);
extern void DisplayModelID(unpack_dms_GetModelID_t* model);
extern void DisplayFsn(unpack_dms_GetFSN_t* FSN);
extern void DisplayDeviceCapabilities(unpack_dms_GetDeviceCapabilities_t* deviceCap);
extern void DisplayManufacturer(unpack_dms_GetManufacturer_t* getManufacturer);
extern void DisplayMsisdn(unpack_dms_GetVoiceNumber_t* voiceNumber);

void DeleteStoredImage(QmiService* pQmiService, pack_fms_DeleteStoredImage_t * pDeleteStoredImage)
{
	unpack_fms_DeleteStoredImage_t unpackfmsDeleteStoredImage;
	memset(&unpackfmsDeleteStoredImage, 0, sizeof(unpack_fms_DeleteStoredImage_t));

    int ret = SENDRECEIVE(pQmiService, pack_fms_DeleteStoredImage, pDeleteStoredImage, unpack_fms_DeleteStoredImage, &unpackfmsDeleteStoredImage);
    DisplayResult(__FUNCTION__, ret, &unpackfmsDeleteStoredImage.ParamPresenceMask, NULL, NULL);
}

void GetStoredImages(QmiService* pQmiService)
{
    unpack_fms_GetStoredImages_t stored_images;
    memset(&stored_images, 0, sizeof(unpack_fms_GetStoredImages_t));

    int ret = SENDRECEIVE(pQmiService, pack_fms_GetStoredImages, NULL, unpack_fms_GetStoredImages, &stored_images);
    DisplayResult(__FUNCTION__, ret, &stored_images.ParamPresenceMask, (result_func)DisplayStoredImage, (void*)&stored_images);
}

void SlqsGetStoredImages(QmiService* pQmiService)
{
    unpack_fms_SlqsGetStoredImages_t stored_images;
    memset(&stored_images, 0, sizeof(unpack_fms_SlqsGetStoredImages_t));

    int ret = SENDRECEIVENOINPUT(pQmiService, pack_fms_SlqsGetStoredImages, unpack_fms_SlqsGetStoredImages, &stored_images);
    DisplayResult(__FUNCTION__, ret, &stored_images.ParamPresenceMask, (result_func)DisplaySlqsStoredImage, (void*)&stored_images);
}

void GetModelID(QmiService* pQmiService)
{
    unpack_dms_GetModelID_t model;
    memset(&model, 0, sizeof(unpack_dms_GetModelID_t));

    int ret = SENDRECEIVE(pQmiService, pack_dms_GetModelID, NULL, unpack_dms_GetModelID, &model);
    DisplayResult(__FUNCTION__, ret, &model.ParamPresenceMask, (result_func)DisplayModelID, (void*)&model);
}

void GetFsn(QmiService* pQmiService)
{
    unpack_dms_GetFSN_t FSN;
    memset(&FSN, 0, sizeof(unpack_dms_GetFSN_t));

    int ret = SENDRECEIVE(pQmiService, pack_dms_GetFSN, NULL, unpack_dms_GetFSN, &FSN);
    DisplayResult(__FUNCTION__, ret, &FSN.ParamPresenceMask, (result_func)DisplayFsn, (void*)&FSN);
}

void GetDeviceCapabilities(QmiService* pQmiService)
{
    unpack_dms_GetDeviceCapabilities_t deviceCap;
    memset(&deviceCap, 0, sizeof(unpack_dms_GetDeviceCapabilities_t));

    int ret = SENDRECEIVE(pQmiService, pack_dms_GetDeviceCapabilities, NULL, unpack_dms_GetDeviceCapabilities, &deviceCap);
    DisplayResult(__FUNCTION__, ret, &deviceCap.ParamPresenceMask, (result_func)DisplayDeviceCapabilities, (void*)&deviceCap);
}

void GetBandCapability(QmiService* pQmiService)
{
    uint16_t lteBands[32];
    uint16_t nr5gBands[32];
    unpack_dms_SLQSGetBandCapability_t dmsGetBandCapability = {
                                        0, 0, 0, 0, 0, 
                                        0, { 32, lteBands },
                                        0, { 32, nr5gBands },
                                        0,
                                        SWI_UINT256_INT_VALUE};

    int ret = SENDRECEIVE(pQmiService, pack_dms_SLQSGetBandCapability, NULL, unpack_dms_SLQSGetBandCapability, &dmsGetBandCapability);
    DisplayResult(__FUNCTION__, ret, &dmsGetBandCapability.ParamPresenceMask, (result_func)DisplayGetBandCapability, (void*)&dmsGetBandCapability);
}

void GetManufacturer(QmiService* pQmiService)
{
    unpack_dms_GetManufacturer_t    getManufacturer;
    memset(&getManufacturer, 0, sizeof(unpack_dms_GetManufacturer_t));

    int ret = SENDRECEIVENOINPUT(pQmiService, pack_dms_GetManufacturer, unpack_dms_GetManufacturer, &getManufacturer);
    DisplayResult(__FUNCTION__, ret, &getManufacturer.ParamPresenceMask, (result_func)DisplayManufacturer, (void*)&getManufacturer);
}

void GetMsisdn(QmiService* pQmiService)
{
    unpack_dms_GetVoiceNumber_t voiceNumber;
    memset(&voiceNumber, 0, sizeof(unpack_dms_GetVoiceNumber_t));

    int ret = SENDRECEIVE(pQmiService, pack_dms_GetVoiceNumber, NULL, unpack_dms_GetVoiceNumber, &voiceNumber);
    DisplayResult(__FUNCTION__, ret, &voiceNumber.ParamPresenceMask, (result_func)DisplayMsisdn, (void*)&voiceNumber);
}

void GetFirmwareInformation(QmiService* pQmiService)
{
    unpack_dms_GetFirmwareInfo_t firmwareInfo;
    memset(&firmwareInfo, 0, sizeof(unpack_dms_GetFirmwareInfo_t));

    int ret = SENDRECEIVE(pQmiService, pack_dms_SLQSSwiGetFirmwareInfo, NULL, unpack_dms_SLQSSwiGetFirmwareInfo, &firmwareInfo);
    DisplayResult(__FUNCTION__, ret, &firmwareInfo.ParamPresenceMask, (result_func)DisplayGetFirmwareInformation, (void*)&firmwareInfo);
}

void GetSerialNumber(QmiService* pQmiService)
{
    unpack_dms_GetSerialNumbers_t serialNumbers;
    memset(&serialNumbers, 0, sizeof(unpack_dms_GetSerialNumbers_t));

    int ret = SENDRECEIVE(pQmiService, pack_dms_GetSerialNumbers, NULL, unpack_dms_GetSerialNumbers, &serialNumbers);
    DisplayResult(__FUNCTION__, ret, &serialNumbers.ParamPresenceMask, (result_func)DisplayGetSerialNumbers, (void*)&serialNumbers);
}

void GetSwiHostDevInfo(QmiService* pQmiService)
{
    pack_dms_SLQSSwiGetHostDevInfo_t packdmsSLQSSwiGetHostDevInfo = { 0 };
	unpack_dms_SLQSSwiGetHostDevInfo_t unpackdmsSLQSSwiGetHostDevInfo;
	memset(&unpackdmsSLQSSwiGetHostDevInfo, 0, sizeof(unpack_dms_SLQSSwiGetHostDevInfo_t));

    int ret = SENDRECEIVE(pQmiService, pack_dms_SLQSSwiGetHostDevInfo, &packdmsSLQSSwiGetHostDevInfo, unpack_dms_SLQSSwiGetHostDevInfo, &unpackdmsSLQSSwiGetHostDevInfo);
    DisplayResult(__FUNCTION__, ret, &unpackdmsSLQSSwiGetHostDevInfo.ParamPresenceMask, (result_func)DisplayGetHostDevInfoSettings, (void*)&unpackdmsSLQSSwiGetHostDevInfo);
}

void SetSwiHostDevInfo(QmiService* pQmiService, pack_dms_SLQSSwiSetHostDevInfo_t *pSwiSetHostDevInfo)
{
    unpack_dms_SLQSSwiSetHostDevInfo_t unpackdmsSLQSSwiSetHostDevInfo;
	memset(&unpackdmsSLQSSwiSetHostDevInfo, 0, sizeof(unpack_dms_SLQSSwiSetHostDevInfo_t));

    int ret = SENDRECEIVE(pQmiService, pack_dms_SLQSSwiSetHostDevInfo, pSwiSetHostDevInfo, unpack_dms_SLQSSwiSetHostDevInfo, &unpackdmsSLQSSwiSetHostDevInfo);
    DisplayResult(__FUNCTION__, ret, &unpackdmsSLQSSwiSetHostDevInfo.ParamPresenceMask, NULL, NULL);
}

void SetEventReport(QmiService* pQmiService, pack_dms_SetEventReport_t *pSetEventReport)
{
    unpack_dms_SetEventReport_t sUnpackSetEventReport;
	memset(&sUnpackSetEventReport, 0, sizeof(unpack_dms_SetEventReport_t));

    int ret = SENDRECEIVE(pQmiService, pack_dms_SetEventReport, pSetEventReport, unpack_dms_SetEventReport, &sUnpackSetEventReport);
    DisplayResult(__FUNCTION__, ret, &sUnpackSetEventReport.ParamPresenceMask, NULL, NULL);
}

void SetPower(QmiService* pQmiService, pack_dms_SetPower_t *pSetPower)
{
    unpack_dms_SetPower_t sUnpackSetPower;
	memset(&sUnpackSetPower, 0, sizeof(unpack_dms_SetPower_t));

    int ret = SENDRECEIVE(pQmiService, pack_dms_SetPower, pSetPower, unpack_dms_SetPower, &sUnpackSetPower);
    DisplayResult(__FUNCTION__, ret, &sUnpackSetPower.ParamPresenceMask, NULL, NULL);
}

void GetPower(QmiService* pQmiService)
{
    unpack_dms_GetPower_t sUnpackGetPower;
	memset(&sUnpackGetPower, 0, sizeof(unpack_dms_GetPower_t));

    int ret = SENDRECEIVE(pQmiService, pack_dms_GetPower, NULL, unpack_dms_GetPower, &sUnpackGetPower);
    DisplayResult(__FUNCTION__, ret, &sUnpackGetPower.ParamPresenceMask, (result_func)DisplayGetPower, (void*)&sUnpackGetPower);
}

void GetAutoSimList(QmiService* pQmiService, pack_swidms_SLQSSwiDmsGetAutoSimList_t *pSwiDmsGetAutoSimList)
{
    unpack_swidms_SLQSSwiDmsGetAutoSimList_t sUnpackGetAutoSimList;
	memset(&sUnpackGetAutoSimList, 0, sizeof(unpack_swidms_SLQSSwiDmsGetAutoSimList_t));

    int ret = SENDRECEIVE(pQmiService, pack_swidms_SLQSSwiDmsGetAutoSimList, pSwiDmsGetAutoSimList, unpack_swidms_SLQSSwiDmsGetAutoSimList, &sUnpackGetAutoSimList);
    DisplayResult(__FUNCTION__, ret, &sUnpackGetAutoSimList.ParamPresenceMask, (result_func)DisplayAutoSimList, (void*)&sUnpackGetAutoSimList);

    for (uint8_t idx = sUnpackGetAutoSimList.config_index + 1;
        ret == eQCWWAN_ERR_NONE && strlen(pSwiDmsGetAutoSimList->carrier) == 0 && idx < sUnpackGetAutoSimList.max_config_count;
        ++idx)
    {     
        pSwiDmsGetAutoSimList->pConfig_index = &idx;
        memset(&sUnpackGetAutoSimList, 0, sizeof(unpack_swidms_SLQSSwiDmsGetAutoSimList_t));               

        ret = SENDRECEIVE(pQmiService, pack_swidms_SLQSSwiDmsGetAutoSimList, pSwiDmsGetAutoSimList, unpack_swidms_SLQSSwiDmsGetAutoSimList, &sUnpackGetAutoSimList);
        DisplayResult(__FUNCTION__, ret, &sUnpackGetAutoSimList.ParamPresenceMask, (result_func)DisplayAutoSimList, (void*)&sUnpackGetAutoSimList);
    }
}

void SetAutoSimList(QmiService* pQmiService, pack_swidms_SLQSSwiDmsSetAutoSimList_t *pSwiDmsSetAutoSimList)
{
    unpack_swidms_SLQSSwiDmsSetAutoSimList_t sUnpackSetAutoSimList;
	memset(&sUnpackSetAutoSimList, 0, sizeof(unpack_swidms_SLQSSwiDmsSetAutoSimList_t));

    int ret = SENDRECEIVE(pQmiService, pack_swidms_SLQSSwiDmsSetAutoSimList, pSwiDmsSetAutoSimList, unpack_swidms_SLQSSwiDmsSetAutoSimList, &sUnpackSetAutoSimList);
    DisplayResult(__FUNCTION__, ret, &sUnpackSetAutoSimList.ParamPresenceMask, NULL, NULL);
}

void GetCustomFeaturesV2(QmiService* pQmiService)
{
	pack_dms_GetCustFeaturesV2_t sPackGetCF;
	memset(&sPackGetCF, 0, sizeof(pack_dms_GetCustFeaturesV2_t));

	DMSgetCustomInput sGetCustomInput;
	memset(&sGetCustomInput, 0, sizeof(DMSgetCustomInput));
	DMScustSettingInfo sCustSettingInfo;
	memset(&sCustSettingInfo, 0, sizeof(DMScustSettingInfo));
	DMScustSettingList sCustSettingList;
	memset(&sCustSettingList, 0, sizeof(DMScustSettingList));

	unpack_dms_GetCustFeaturesV2_t sUnpackGetCF;
	memset(&sUnpackGetCF, 0, sizeof(unpack_dms_GetCustFeaturesV2_t));
	sUnpackGetCF.GetCustomFeatureV2.pGetCustomInput = &sGetCustomInput;
	sUnpackGetCF.GetCustomFeatureV2.pCustSettingInfo = &sCustSettingInfo;
	sUnpackGetCF.GetCustomFeatureV2.pCustSettingList = &sCustSettingList;

    int ret = SENDRECEIVE(pQmiService, pack_dms_GetCustFeaturesV2, &sPackGetCF, unpack_dms_GetCustFeaturesV2, &sUnpackGetCF);
    DisplayResult(__FUNCTION__, ret, &sUnpackGetCF.ParamPresenceMask, (result_func)DisplayGetCustomFeaturesV2, (void*)&sUnpackGetCF);
}

void SetCustomFeaturesV2(QmiService* pQmiService, pack_dms_SetCustFeaturesV2_t *pSetCustomFeatures)
{
    unpack_dms_SetCustFeaturesV2_t sUnpackSetCF;
	memset(&sUnpackSetCF, 0, sizeof(unpack_dms_SetCustFeaturesV2_t));

    int ret = SENDRECEIVE(pQmiService, pack_dms_SetCustFeaturesV2, pSetCustomFeatures, unpack_dms_SetCustFeaturesV2, &sUnpackSetCF);
    DisplayResult(__FUNCTION__, ret, &sUnpackSetCF.ParamPresenceMask, NULL, NULL);
}

void GetSdkVersion()
{
    char szSdkVersion[100] = {0};
    char *pSdkVersion = szSdkVersion;
    SLQSGetSDKVersion(&pSdkVersion);

	SockPrintf("SDK Version: %s\n", pSdkVersion);
}

void dms_indication_handler(uint16_t msgid, uint8_t *qmiData, uint32_t qmiDataSize)
{
    int rtn = 0;

    switch (msgid)
    {
        case eQMI_DMS_EVENT_IND:
        {
            unpack_dms_SetEventReport_ind_t sSetEventReport_ind;
            memset(&sSetEventReport_ind, 0, sizeof(unpack_dms_SetEventReport_ind_t));
            rtn = unpack_dms_SetEventReport_ind(qmiData, qmiDataSize, &sSetEventReport_ind);
            DisplayResult("unpack_dms_SetEventReport_ind", rtn, NULL, (result_func)DisplaySetEventReportInd, (void*)&sSetEventReport_ind);
            if (rtn == eQCWWAN_ERR_NONE &&
                swi_uint256_get_bit(sSetEventReport_ind.ParamPresenceMask, 0x14)  &&
                sSetEventReport_ind.OperatingModeTlv.operatingMode == 3)
            {
                //check for the offline mode if device reset occured 
                DeviceIsOffline();
            }
        }
        break;
        case eQMI_DMS_GET_MODEL_ID:
        case eQMI_DMS_GET_REV_ID:
        case eQMI_DMS_PSM_CFG_PARAMS_CHANGE_IND:
        case eQMI_DMS_SWI_EVENT_IND:
        case eQMI_DMS_SWI_GET_RESET_INFO_IND:
        break;
    }
}
