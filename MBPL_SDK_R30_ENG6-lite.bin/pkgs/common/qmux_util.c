#include <string.h>
#include <inttypes.h>
#include <QmiSyncObject.h>
#include "qmerrno.h"

#include "dev_util.h"
#include "qmux_util.h"
#include "proc_util.h"

int OpenTransportEx(QmuxTransport* ptransport, char* dev_path, size_t dev_path_size, int* pmode, bool* ppcie, int* pif_adapter,
	bool valid, FNSHOWHELP pfnsh, const char* pProcName, bool showhelp, bool skipOpen, bool skipClose)
{
	if (dev_path == NULL || pmode == NULL || ppcie == NULL)
		return -1;

	if (ptransport == NULL)
		return 1;

	bool bGotDevInfo = false;
	
	if (*pmode != QMUX_INTERFACE_ROUTER)
		bGotDevInfo = GetDeviceInfo(dev_path, dev_path_size, pmode, ppcie, pif_adapter, valid, pfnsh, pProcName, showhelp);
	else
	{
		int mode = QMUX_INTERFACE_UNKNOWN;
		bGotDevInfo = GetDeviceInfo(dev_path, dev_path_size, &mode, ppcie, pif_adapter, valid, pfnsh, pProcName, showhelp);
	}

	if (!bGotDevInfo)
		return 1;

	dlog(eLOG_INFO, "Open transport \"%s\" on %s device in %s mode\n", dev_path, *ppcie ? "PCIe" : "USB", GetModeDesc(*pmode));

	if (*ppcie == false && *pmode != QMUX_INTERFACE_MBIM && pif_adapter)
		dlog(eLOG_INFO, "Interface id: %x\n", *pif_adapter);

	//if (QmuxTransport_Initialize(ptransport, dev_path, *pmode == QMUX_INTERFACE_MBIM, NULL) != 0)

	if (QmuxTransport_InitializeEx2(ptransport, *pmode != QMUX_INTERFACE_ROUTER ? dev_path : NULL, *pmode, NULL, skipOpen, skipClose) != 0)
	{
		dlog(eLOG_ERROR, "Transport_Initialize failed.\n");
		return 2;
	}

	return 0;
}

int OpenTransport(QmuxTransport* ptransport, char* dev_path, size_t dev_path_size, int* pmode, bool* ppcie, int* pif_adapter,
	bool valid, FNSHOWHELP pfnsh, const char* pProcName, bool showhelp)
{
	return OpenTransportEx(ptransport, dev_path, dev_path_size, pmode, ppcie, pif_adapter, valid, pfnsh, pProcName, showhelp, false, false);
}

// Return message ID of the indication
uint16_t IndicationCallback(const char* svcName, uint8_t svc, uint8_t* qmiPacket, uint16_t qmiPacketSize, void* pIndicationCallbackContext)
{
	(void)pIndicationCallbackContext;

	unpack_qmi_t rsp_ctx;
	dlog(eLOG_INFO, "\n<< receiving %s\n", helper_get_resp_ctx(svc, qmiPacket, qmiPacketSize, &rsp_ctx));
	dlog(eLOG_INFO, "%s IND: msgid 0x%x, type:%x\n", svcName, rsp_ctx.msgid, rsp_ctx.type);
	// TODO:

	return rsp_ctx.msgid;
}

/*
 * Name:     SaveClientId
 *
 * Purpose:  Save a serviceType/clientId pair to a file.
 *
 * Params:   serviceType	- QMI service type e.g. eUIM, eNAS.
 * 			 clientId		- QMI client ID.
 *           clientIdsPath  - Path of file in which the serviceType/clientId will be saved.
 *
 * Return:   SUCCESS	- If successful
 *           < 0 		- On failure
 *
 * Notes:    None
 */
int SaveClientId(uint8_t serviceType, uint8_t clientId, const char* clientIdsPath)
{
	// We don't realistically expect to have to save more than 20 serviceType/clientId pairs.
	uint8_t savedServiceType[20];
	uint8_t savedClientId[20];
	size_t i = 0;
	size_t numberOfSavedItems = 0;

	// Read existing file entire contents.

	FILE* pFile = fopen(clientIdsPath, "r");

	if (!pFile)
	{
		dlog(eLOG_INFO, "%s: File %s open failed, thats OK\n", __FUNCTION__, clientIdsPath);
	}
	else
	{
		int ret = 2;

		for (i = 0; i < sizeof(savedServiceType) / sizeof(savedServiceType[0]); i++)
		{
			ret = fscanf(pFile, "%" SCNu8 ",%" SCNu8 "\n", &savedServiceType[i], &savedClientId[i]);
			if (ret != 2)
			{
				break;
			}
		}

		numberOfSavedItems = i;
		fclose(pFile);
	}

	for (i = 0; i < numberOfSavedItems; i++)
	{
		if (savedServiceType[i] == serviceType)
		{
			// Already have an entry.
			if (savedClientId[i] == clientId)
			{
				// We're done. clientId is already correct.
				return 0;
			}
			else
			{
				savedClientId[i] = clientId;
				break;
			}
		}
	}

	if (i == numberOfSavedItems)
	{
		// We didn't find an entry so append new one.
		if (numberOfSavedItems == (sizeof(savedServiceType) / sizeof(savedServiceType[0])))
		{
			dlog(eLOG_ERROR, "%s: No room to save item\n", __FUNCTION__, clientIdsPath);
			return -1;
		}

		savedServiceType[i] = serviceType;
		savedClientId[i] = clientId;
		numberOfSavedItems++;
	}

	// File is dirty. We need to update it.

	pFile = fopen(clientIdsPath, "w");
	if (!pFile)
	{
		dlog(eLOG_ERROR, "%s: File %s open failed for writing\n", __FUNCTION__, clientIdsPath);
		return -1;
	}

	for (i = 0; i < numberOfSavedItems; i++)
	{
		fprintf(pFile, "%" PRIu8 ",%" PRIu8 "\n", savedServiceType[i], savedClientId[i]);
	}

	fclose(pFile);

	return 0;
}

/*
 * Name:     RestoreClientId
 *
 * Purpose:  Restore a serviceType/clientId pair from a file.
 *
 * Params:   serviceType	- QMI service type e.g. eUIM, eNAS.
 * 			 pClientId		- Restored QMI client ID.
 *           clientIdsPath  - Path of file in which the serviceType/clientId was saved.
 *
 * Return:   SUCCESS	- If successful
 *           < 0 		- On failure
 *
 * Notes:    None
 */
int RestoreClientId(uint8_t serviceType, uint8_t* pClientId, const char* clientIdsPath)
{
	FILE* pFile = fopen(clientIdsPath, "r");

	if (!pFile)
	{
		dlog(eLOG_ERROR, "%s: File %s open failed\n", __FUNCTION__, clientIdsPath);
		return -1;
	}

	int ret = 0;

	do
	{
		uint8_t savedServiceType = 0;
		uint8_t savedClientId = 0;
		
		ret = fscanf(pFile, "%" SCNu8 ",%" SCNu8 "\n", &savedServiceType, &savedClientId);

		if (ret == 2)
		{
			if (savedServiceType == serviceType)
			{
				*pClientId = savedClientId;
				fclose(pFile);
				return 0;
			}
		}
	} while (ret == 2);

	dlog(eLOG_ERROR, "%s: Lookup failure for serviceType %" PRIu8 "\n", __FUNCTION__, serviceType);
	fclose(pFile);
	return -1;
}

