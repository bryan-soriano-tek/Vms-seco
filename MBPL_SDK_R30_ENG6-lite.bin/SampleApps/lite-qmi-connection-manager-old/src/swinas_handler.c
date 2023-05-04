#include <string.h>
#include "common.h"
#include "qmerrno.h"
#include "proc_util.h"
#include "qmux_util.h"
#include "swinas_handler.h"

static QmiService s_SwiNasService;

int InitializeSwiNasService(CtlService* pCtlSvc)
{
	int ret = pCtlSvc ? CtlService_InitializeRegularService(pCtlSvc, &s_SwiNasService, eSWINAS, NULL, NULL) : -1;
	if (ret != 0)
	{
		dlog(eLOG_ERROR, "SwiNas service is not supported.\n");
		s_SwiNasService.serviceType = 0;
	}

	return ret;
}

void ShutDownSwiNasService(CtlService* pCtlSvc)
{
	if (pCtlSvc)
		CtlService_ShutDownRegularService(pCtlSvc, &s_SwiNasService);
}

int SwiNasGetDefaultNssaiInfo(unpack_swinas_GetDefaultNssai_t* psDefNssai)
{
	if (s_SwiNasService.serviceType == 0)
		return eQCWWAN_ERR_QMI_NOT_SUPPORTED;

	if (psDefNssai == NULL)
		return eQCWWAN_ERR_INVALID_ARG;

	int ret = get_default_nssai_info(&s_SwiNasService, psDefNssai);

	if (eQCWWAN_ERR_NONE != ret)
		printf("get_default_nssai_info failed (%d)\n", ret);

	return ret;
}

int SwiNasSetDefaultNssaiInfo(pack_swinas_SetDefaultNssai_t* psDefNssai)
{
	if (s_SwiNasService.serviceType == 0)
		return eQCWWAN_ERR_QMI_NOT_SUPPORTED;

	if (psDefNssai == NULL)
		return eQCWWAN_ERR_INVALID_ARG;

	int ret = set_default_nssai_info(&s_SwiNasService, psDefNssai);

	if (eQCWWAN_ERR_NONE != ret)
		printf("set_default_nssai_info failed (%d)\n", ret);

	return ret;
}

int SwiNasGetPdpProfileSettings(pack_swinas_GetPdpContextParams_t* pInput, unpack_swinas_GetPdpContextParams_t* pOutput)
{
	if (s_SwiNasService.serviceType == 0)
		return eQCWWAN_ERR_QMI_NOT_SUPPORTED;

	if (pInput == NULL || pOutput == NULL)
		return eQCWWAN_ERR_INVALID_ARG;

	int ret = get_pdp_profile_settings(&s_SwiNasService, pInput, pOutput);

	if (eQCWWAN_ERR_NONE != ret)
		printf("get_pdp_profile_settings failed (%d)\n", ret);

	return ret;
}

int SwiNasSetPdpProfileSettings(swinas_key_profile_data* pKeyPdpContext, swinas_ext_profile_data* pExtPdpContext)
{
	if (s_SwiNasService.serviceType == 0)
		return eQCWWAN_ERR_QMI_NOT_SUPPORTED;

	if (pKeyPdpContext == NULL)
		return eQCWWAN_ERR_INVALID_ARG;

	pack_swinas_SetPdpContextParams_t req;
	req.key_profile_data = *pKeyPdpContext;
	req.pExt_profile_data = pExtPdpContext;

	int ret = set_pdp_profile_settings(&s_SwiNasService, &req);

	if (eQCWWAN_ERR_NONE != ret)
		printf("set_pdp_profile_settings failed (%d)\n", ret);

	return ret;
}

