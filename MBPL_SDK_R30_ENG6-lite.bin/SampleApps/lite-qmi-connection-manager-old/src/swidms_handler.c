#include <string.h>
#include "common.h"
#include "qmerrno.h"
#include "proc_util.h"
#include "qmux_util.h"
#include "swidms_handler.h"
#include "swidms.h"

int get_rmnet(CtlService* pCtlSvc, bool* pbRmNet)
{
	if (pCtlSvc == NULL || pbRmNet == NULL)
		return eQCWWAN_ERR_INVALID_ARG;

	QmiService SwiDmsService;
	int ret = CtlService_InitializeRegularService(pCtlSvc, &SwiDmsService, eSWIDMS, NULL, NULL);
	if (ret != eQCWWAN_ERR_NONE)
	{
		//dlog(eLOG_ERROR, "InitializeRegularService eSWIDMS failed.\n");
		return ret;
	}

	swidms_intfaceCfgTlv intfaceCfg = { 0, 0 };
	swidms_supportedIntBitmaskTlv supportIntBitmask = { 0 };
	unpack_swidms_SLQSSwiDmsGetUsbComp_t usbCompResp;
	memset(&usbCompResp, 0, sizeof(unpack_swidms_SLQSSwiDmsGetUsbComp_t));
	usbCompResp.pInterfaceCfg = &intfaceCfg;
	usbCompResp.pSupportedBitmasks = &supportIntBitmask;

	ret = SENDRECEIVENOINPUT(&SwiDmsService, pack_swidms_SLQSSwiDmsGetUsbComp, unpack_swidms_SLQSSwiDmsGetUsbComp, &usbCompResp);

	if (eQCWWAN_ERR_NONE != ret)
		printf("SwiDmsGetHostIntfComp failed (%d)", ret);
	else
	{
		if (supportIntBitmask.ValidBitmasks != 0)
			intfaceCfg.CfgValue &= supportIntBitmask.ValidBitmasks;
		*pbRmNet = (intfaceCfg.CfgValue & 0x0d00) != 0;
		printf("Device interface: %s\n", *pbRmNet ? "RmNet" : "MBIM");
	}

	CtlService_ShutDownRegularService(pCtlSvc, &SwiDmsService);

	return ret;
}

