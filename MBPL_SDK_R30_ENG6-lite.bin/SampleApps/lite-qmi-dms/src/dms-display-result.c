#include <stdio.h>
#include <inttypes.h>
#include "lite-qmi-dms.h"
#include "dms.h"
#include "swidms.h"
#include "command_set.h"

typedef struct
{
	uint32_t value;
	const char* szText;
}Map_ValueText;

const char* GetMapStringFromValue(uint32_t val, Map_ValueText* pMaps, int sizeMap)
{
	for (int i = 0; i < sizeMap; i++)
	{
		if (pMaps[i].value == val)
			return pMaps[i].szText;
	}

	return "Unknown";
}

#define GET_MAP_STRING(v, m) GetMapStringFromValue((v), (m), sizeof((m))/sizeof(Map_ValueText))

static Map_ValueText g_Table_ActivationStatus[] =
{
  {0, "Service not activated"},
  {1, "Service activated"},
  {2, "Activation connecting"},
  {3, "Activation connected"},
  {4, "OTASP security authenticated"},
  {5, "OTASP NAM downloaded"},
  {6, "OTASP MDN downloaded"},
  {7, "OTASP IMSI downloaded"},
  {8, "OTASP PRL downloaded"},
  {9, "OTASP SPC downloaded"},
  {10, "OTASP settings committed"},
};

static Map_ValueText g_Table_OperatingMode[] =
{
  {0, "Online"},
  {1, "Low power"},
  {2, "Factory test mode"},
  {3, "Offline"},
  {4, "Resetting"},
  {5, "Shutting down"},
  {6, "Persistent low power"},
  {7, "Mode-only low power"},
  {8, "Conducting network test for GSM/WCDMA"},
  {9, "Camp only"},
};

void DisplayGetBandCapability(unpack_dms_SLQSGetBandCapability_t *pBandCapability)
{
    SockPrintf("\n%s: Success\n", "GetBandCapability");
    if(swi_uint256_get_bit (pBandCapability->ParamPresenceMask, 1))
    {
        SockPrintf(" Band Cap    : 0x%"PRIX64"\n", pBandCapability->bandCapability);
    }
    if(swi_uint256_get_bit (pBandCapability->ParamPresenceMask, 16))
    {
        SockPrintf(" LTE Band Cap: 0x%"PRIX64"\n", pBandCapability->LteBandCapability);
    }
    if(swi_uint256_get_bit (pBandCapability->ParamPresenceMask, 17))
    {
            SockPrintf(" TDS Band Cap: 0x%"PRIX64"\n", pBandCapability->TdsBandCapability);
    }
	if (swi_uint256_get_bit(pBandCapability->ParamPresenceMask, 18))
	{
		SockPrintf(" LTE Band length: %d\n", pBandCapability->LteBands.bands_len);
		for (int i = 0; i < pBandCapability->LteBands.bands_len; i++)
			SockPrintf("  LTE Band %d: %d\n", i, pBandCapability->LteBands.bands[i]);
	}
	if (swi_uint256_get_bit(pBandCapability->ParamPresenceMask, 19))
	{
		SockPrintf(" NR5G band len: %d\n", pBandCapability->Nr5gBands.bands_len);
		for (int idx = 0; idx < pBandCapability->Nr5gBands.bands_len; idx++)
			SockPrintf("  NR5G band[%d]: %d\n", idx, pBandCapability->Nr5gBands.bands[idx]);
	}
}

void DisplayGetFirmwareInformation(unpack_dms_GetFirmwareInfo_t *pfirmwareInfo)
{
    SockPrintf("\n%s: %s\n", "GetFirmwareInformation", pfirmwareInfo->Tlvresult? "Fail" : "Success");
    if(swi_uint256_get_bit (pfirmwareInfo->ParamPresenceMask, 16))
        SockPrintf("  Model Id: %s\n", pfirmwareInfo->modelid_str);
    if(swi_uint256_get_bit (pfirmwareInfo->ParamPresenceMask, 17))
        SockPrintf("  Boot Version: %s\n", pfirmwareInfo->bootversion_str);
    if(swi_uint256_get_bit (pfirmwareInfo->ParamPresenceMask, 18))
        SockPrintf("  app version: %s\n", pfirmwareInfo->appversion_str);
    if(swi_uint256_get_bit (pfirmwareInfo->ParamPresenceMask, 19))
        SockPrintf("  SKU Id: %s\n", pfirmwareInfo->sku_str);
    if(swi_uint256_get_bit (pfirmwareInfo->ParamPresenceMask, 20))
        SockPrintf("  Package Id: %s\n", pfirmwareInfo->packageid_str);
    if(swi_uint256_get_bit (pfirmwareInfo->ParamPresenceMask, 21))
        SockPrintf("  Carrier: %s\n", pfirmwareInfo->carrier_str);
    if(swi_uint256_get_bit (pfirmwareInfo->ParamPresenceMask, 22))
        SockPrintf("  PRI Version: %s\n", pfirmwareInfo->priversion_str);
    if(swi_uint256_get_bit (pfirmwareInfo->ParamPresenceMask, 23))
        SockPrintf("  Carrier Name: %s\n", pfirmwareInfo->cur_carr_name);
    if(swi_uint256_get_bit (pfirmwareInfo->ParamPresenceMask, 24))
        SockPrintf("  Carrier Rev: %s\n", pfirmwareInfo->cur_carr_rev);
}

void DisplayGetSerialNumbers(unpack_dms_GetSerialNumbers_t *pSerialNumbers)
{
    SockPrintf("\nGetSerialNumbers : Success\n");
    if(swi_uint256_get_bit (pSerialNumbers->ParamPresenceMask, 16))
        SockPrintf("  ESN String : %s\n", pSerialNumbers->esn);
    if(swi_uint256_get_bit (pSerialNumbers->ParamPresenceMask, 17))
        SockPrintf("  IMEI String : %s\n", pSerialNumbers->imei_no);
    if(swi_uint256_get_bit (pSerialNumbers->ParamPresenceMask, 18))
        SockPrintf("  MEID String : %s\n", pSerialNumbers->meid);
    if(swi_uint256_get_bit (pSerialNumbers->ParamPresenceMask, 19))
        SockPrintf("  IMEI SV String : %s\n", pSerialNumbers->imeisv_svn);
}

void DisplayGetHostDevInfoSettings(unpack_dms_SLQSSwiGetHostDevInfo_t *pSwiGetHostDevInfo)
{
	SockPrintf("%s Result : %d\n", __FUNCTION__, pSwiGetHostDevInfo->Tlvresult);

	if (swi_uint256_get_bit (pSwiGetHostDevInfo->ParamPresenceMask, 0x10) && 
		pSwiGetHostDevInfo->manString != NULL && 
		pSwiGetHostDevInfo->manString[0] != 0x7f)
	{
		SockPrintf("Manufacturer : %s\n", pSwiGetHostDevInfo->manString);
	}
	if (swi_uint256_get_bit (pSwiGetHostDevInfo->ParamPresenceMask, 0x11) && 
		pSwiGetHostDevInfo->modelString != NULL &&
		pSwiGetHostDevInfo->modelString[0] != 0x7f)
	{
		SockPrintf("Model String : %s\n", pSwiGetHostDevInfo->modelString);
	}
	if (swi_uint256_get_bit (pSwiGetHostDevInfo->ParamPresenceMask, 0x12) && 
		pSwiGetHostDevInfo->swVerString != NULL &&
		pSwiGetHostDevInfo->swVerString[0] != 0x7f)
	{
		SockPrintf("Software Version : %s\n", pSwiGetHostDevInfo->swVerString);
	}
	if (swi_uint256_get_bit (pSwiGetHostDevInfo->ParamPresenceMask, 0x13) &&
		pSwiGetHostDevInfo->plasmaIDString != NULL &&
		pSwiGetHostDevInfo->plasmaIDString[0] != 0x7f)
	{
		SockPrintf("Plasma ID String : %s\n", pSwiGetHostDevInfo->plasmaIDString);
	}
	if (swi_uint256_get_bit (pSwiGetHostDevInfo->ParamPresenceMask, 0x14) &&
		pSwiGetHostDevInfo->hostID != NULL &&
		pSwiGetHostDevInfo->hostID[0] != 0x7f)
	{
		SockPrintf("Host ID : %s\n", pSwiGetHostDevInfo->hostID);
	}
	if (swi_uint256_get_bit (pSwiGetHostDevInfo->ParamPresenceMask, 0x14) &&
		pSwiGetHostDevInfo->pInstance != NULL)
	{
		SockPrintf("instance : %d\n", *pSwiGetHostDevInfo->pInstance);
	}
}

void DisplaySetEventReportInd(unpack_dms_SetEventReport_ind_t *pSetEventReport_ind)
{
	SockPrintf("\nDMS EventReport Indication:\n");
 
	if (swi_uint256_get_bit(pSetEventReport_ind->ParamPresenceMask, 0x13) && pSetEventReport_ind->ActivationStatusTlv.activationStatus < 11)
	{
		SockPrintf("Activation Status: %s\n", GET_MAP_STRING(pSetEventReport_ind->ActivationStatusTlv.activationStatus, g_Table_ActivationStatus));
	}

	if (swi_uint256_get_bit(pSetEventReport_ind->ParamPresenceMask, 0x14) && pSetEventReport_ind->OperatingModeTlv.operatingMode < 10)
	{
		SockPrintf("Operating Mode: %s\n", GET_MAP_STRING(pSetEventReport_ind->OperatingModeTlv.operatingMode, g_Table_OperatingMode));
	}
}

void DisplayGetPower(unpack_dms_GetPower_t *pUnpackGetPower)
{
	SockPrintf("\nGet Power:\n");
 
	if (swi_uint256_get_bit (pUnpackGetPower->ParamPresenceMask, 0x01))
	{
		SockPrintf("  Activation Status: %s\n", GET_MAP_STRING(pUnpackGetPower->OperationMode, g_Table_OperatingMode));
	}
	if (swi_uint256_get_bit (pUnpackGetPower->ParamPresenceMask, 0x10))
	{
		SockPrintf("  Offline reason:\n");
        if (pUnpackGetPower->OfflineReason & 0x01)
		    SockPrintf("    Host image misconfiguration\n");
        if (pUnpackGetPower->OfflineReason & 0x02)
		    SockPrintf("    PRI image misconfiguration\n");
        if (pUnpackGetPower->OfflineReason & 0x04)
		    SockPrintf("    PRI version incompatible\n");
        if (pUnpackGetPower->OfflineReason & 0x08)
		    SockPrintf("    Device memory is full,cannot copy PRI information\n");
	}
	if (swi_uint256_get_bit (pUnpackGetPower->ParamPresenceMask, 0x11))
	{
		SockPrintf("  hardware restricted mode: %s\n", pUnpackGetPower->HardwareControlledMode? "true" : "false");
	}
}

void DisplayAutoSimList(unpack_swidms_SLQSSwiDmsGetAutoSimList_t *pUnpackGetAutoSimList)
{
	SockPrintf("\nAuto SIM List Result:\n");
 
	if (swi_uint256_get_bit (pUnpackGetAutoSimList->ParamPresenceMask, 0x01))
	{
		SockPrintf("  PRI ID length: %d\n", pUnpackGetAutoSimList->configuration.priid_len);
		SockPrintf("  	PRI ID: %s\n", pUnpackGetAutoSimList->configuration.priid);
		SockPrintf("  Firmware version length: %d\n", pUnpackGetAutoSimList->configuration.fwver_len);
		SockPrintf("  	Firmware version: %s\n", pUnpackGetAutoSimList->configuration.fwver);

		SockPrintf("  Attribute List length: %d\n", pUnpackGetAutoSimList->configuration.attribs_len);
		for (int idx = 0; idx < pUnpackGetAutoSimList->configuration.attribs_len; ++idx)
		{
			SockPrintf("    type: %d  ", pUnpackGetAutoSimList->configuration.attribs[idx].type);
			SockPrintf("    key_len: %d  ", pUnpackGetAutoSimList->configuration.attribs[idx].key_len);
			SockPrintf("    key: %s  ", pUnpackGetAutoSimList->configuration.attribs[idx].key);
			SockPrintf("    rank: %d  ", pUnpackGetAutoSimList->configuration.attribs[idx].rank);
			SockPrintf("    subpri: %d", pUnpackGetAutoSimList->configuration.attribs[idx].subpri);
			if (pUnpackGetAutoSimList->configuration.source_len == pUnpackGetAutoSimList->configuration.attribs_len)
				SockPrintf("    source: %d  ", pUnpackGetAutoSimList->configuration.source[idx]);
			SockPrintf("\n");
		}
		if (pUnpackGetAutoSimList->configuration.source_len != pUnpackGetAutoSimList->configuration.attribs_len)
		{
			SockPrintf("  Source List length: %d\n", pUnpackGetAutoSimList->configuration.source_len);
			for (int idx = 0; idx < pUnpackGetAutoSimList->configuration.attribs_len; ++idx)
			{
				SockPrintf("    source: %d\n", pUnpackGetAutoSimList->configuration.source[idx]);
			}
		}
	}
}

void DisplayGetCustomFeaturesV2(unpack_dms_GetCustFeaturesV2_t *pUnpackGetCF)
{
	SockPrintf("\nGet Custom Features:\n");

	if (swi_uint256_get_bit(pUnpackGetCF->ParamPresenceMask, 0x20) && pUnpackGetCF->GetCustomFeatureV2.pCustSettingInfo)
	{
		SockPrintf("  Cust ID len: %d, value: %s\n", pUnpackGetCF->GetCustomFeatureV2.pCustSettingInfo->id_length, pUnpackGetCF->GetCustomFeatureV2.pCustSettingInfo->cust_id);
		SockPrintf("  Cust value len: %d, value:", pUnpackGetCF->GetCustomFeatureV2.pCustSettingInfo->value_length);
		for (int i = 0; i < pUnpackGetCF->GetCustomFeatureV2.pCustSettingInfo->value_length; i++)
			SockPrintf(" %d", pUnpackGetCF->GetCustomFeatureV2.pCustSettingInfo->cust_value[i]);
		SockPrintf(", attribute: %d\n", pUnpackGetCF->GetCustomFeatureV2.pCustSettingInfo->cust_attr);
	}

	if (swi_uint256_get_bit(pUnpackGetCF->ParamPresenceMask, 0x21) && pUnpackGetCF->GetCustomFeatureV2.pCustSettingList)
	{
		SockPrintf("  Cust list type: %d, len: %d\n", pUnpackGetCF->GetCustomFeatureV2.pCustSettingList->list_type, pUnpackGetCF->GetCustomFeatureV2.pCustSettingList->num_instances);
		for (int idx = 0; idx < pUnpackGetCF->GetCustomFeatureV2.pCustSettingList->num_instances; idx++)
		{
			SockPrintf("    Cust[%d] ID len: %d, value: %s\n", idx,
				pUnpackGetCF->GetCustomFeatureV2.pCustSettingList->custSetting[idx].id_length,
				pUnpackGetCF->GetCustomFeatureV2.pCustSettingList->custSetting[idx].cust_id);
			SockPrintf("    Cust[%d] value len: %d, value:", idx, pUnpackGetCF->GetCustomFeatureV2.pCustSettingList->custSetting[idx].value_length);
			for (int i = 0; i < pUnpackGetCF->GetCustomFeatureV2.pCustSettingList->custSetting[idx].value_length; i++)
				SockPrintf(" %d", pUnpackGetCF->GetCustomFeatureV2.pCustSettingList->custSetting[idx].cust_value[i]);
			SockPrintf(", attribute: %d\n", pUnpackGetCF->GetCustomFeatureV2.pCustSettingList->custSetting[idx].cust_attr);
		}
	}
}

void DisplayStoredImage(unpack_fms_GetStoredImages_t* stored_images)
{
	SockPrintf("%s: %s\n\n", __FUNCTION__, stored_images->Tlvresult ? "Fail" : "Success");

	for (uint32_t i = 0; i < stored_images->imageList.listSize; i++)
	{
		for (uint8_t j = 0; j < stored_images->imageList.imageIDEntries[i].imageIDSize; j++)
		{
			SockPrintf("  Type: %s\n", stored_images->imageList.imageIDEntries[i].imageType == 0 ? "Modem image" : "PRI image");
			SockPrintf("  Image ID: %s\n", stored_images->imageList.imageIDEntries[i].imageIDElement[j].imageID);
			SockPrintf("  Bulid ID: %s\n\n", stored_images->imageList.imageIDEntries[i].imageIDElement[j].buildID);
		}
	}
}

void DisplaySlqsStoredImage(unpack_fms_SlqsGetStoredImages_t* stored_images)
{
	SockPrintf("%s: %s\n\n", __FUNCTION__, stored_images->Tlvresult ? "Fail" : "Success");

	SockPrintf("Firmare Images:\n");
	SockPrintf("Max number of images: %d\n", stored_images->fw_images_list.max_images);
	SockPrintf("Running image: %d\n\n", stored_images->fw_images_list.running_image);
	for (uint8_t i = 0; i < stored_images->fw_images_list.num_of_sub_images; i++)
	{
		SockPrintf("Image[%d]:\n", i);
		SockPrintf("Storage index: 0x%x\n", stored_images->fw_images_list.sublist_entries[i].storage_index);
		SockPrintf("Failure count: 0x%x\n", stored_images->fw_images_list.sublist_entries[i].failure_count);
		SockPrintf("Image ID: %s\n", stored_images->fw_images_list.sublist_entries[i].image_id);
		SockPrintf("Build ID: %s\n", stored_images->fw_images_list.sublist_entries[i].build_id);
		SockPrintf("Least RU rank: 0x%x\n", stored_images->fw_images_list.sublist_entries[i].lru_rank);
		SockPrintf("Switch failure count: 0x%x\n", stored_images->fw_images_list.sublist_entries[i].switch_failure);
		SockPrintf("Download source: 0x%x\n\n", stored_images->fw_images_list.sublist_entries[i].dld_source);
	}

	SockPrintf("PRI Images:\n");
	SockPrintf("Max number of images: %d\n", stored_images->pri_images_list.max_images);
	SockPrintf("Running image: %d\n\n", stored_images->pri_images_list.running_image);
	for (uint8_t i = 0; i < stored_images->pri_images_list.num_of_sub_images; i++)
	{
		SockPrintf("Image[%d]:\n", i);
		SockPrintf("Storage index: 0x%x\n", stored_images->pri_images_list.sublist_entries[i].storage_index);
		SockPrintf("Failure count: 0x%x\n", stored_images->pri_images_list.sublist_entries[i].failure_count);
		SockPrintf("Image ID: %s\n", stored_images->pri_images_list.sublist_entries[i].image_id);
		SockPrintf("Build ID: %s\n", stored_images->pri_images_list.sublist_entries[i].build_id);
		SockPrintf("Least RU rank: 0x%x\n", stored_images->pri_images_list.sublist_entries[i].lru_rank);
		SockPrintf("Switch failure count: 0x%x\n", stored_images->pri_images_list.sublist_entries[i].switch_failure);
		SockPrintf("Download source: 0x%x\n\n", stored_images->pri_images_list.sublist_entries[i].dld_source);
	}
}

void DisplayModelID(unpack_dms_GetModelID_t* model)
{
	SockPrintf(" Model ID: %s\n", model->modelid);
}

void DisplayFsn(unpack_dms_GetFSN_t* FSN)
{
	SockPrintf(" FSN: %s\n", FSN->String);
}

void DisplayDeviceCapabilities(unpack_dms_GetDeviceCapabilities_t* deviceCap)
{
	SockPrintf("\n%s: Success \n", __FUNCTION__);
	SockPrintf(" Max TX Channel Rate : %X\n", deviceCap->maxTxChannelRate);
	SockPrintf(" Max RX Channel Rate : %X\n", deviceCap->maxRxChannelRate);
	SockPrintf(" Data Service Capability : %X\n", deviceCap->dataServiceCaCapability);
	SockPrintf(" SIM Capability : %X\n", deviceCap->simCapability);
	SockPrintf(" Radio Interfaces Size: %X\n", deviceCap->radioIfacesSize);
	for (uint8_t idx = 0; idx < deviceCap->radioIfacesSize; idx++)
	{
		SockPrintf("  radio Interface[%d] : %X\n", idx, deviceCap->RadioIfaces[idx]);
	}
}

void DisplayManufacturer(unpack_dms_GetManufacturer_t* getManufacturer)
{
	SockPrintf(" Device Manufacturer: %s\n", getManufacturer->manufacturer);
}

void DisplayMsisdn(unpack_dms_GetVoiceNumber_t* voiceNumber)
{
	if (swi_uint256_get_bit(voiceNumber->ParamPresenceMask, 16))
		SockPrintf("\tMobile ID: %s\n", voiceNumber->MIN);

	SockPrintf("\tVoice Number: %s\n", voiceNumber->VoiceNumber);
}
