#ifndef __LITE_QMI_DMS_H__
#define __LITE_QMI_DMS_H__

#include "common.h"
#include "msgid.h"
#include "qmerrno.h"

#define MAX_USER_INPUT_SIZE  512

typedef enum _status_code 
{
    SUCCESS =  0,    // The operation succeeded.
    FAILURE = -1,    // The operation failed.    
} status_code, *pstatus_code;

enum AppStateType
{
    AppUninitialized,
    AppRunning,
    AppShuttingDown,
    AppCommandExecuted,
    AppCommandWaitForDevice,

    AppGetMsisdn,
    AppGetImsi,
    AppGetIccid,
    AppGetBootAndPriVersion,
    AppGetPrlVersion,
    AppGetMeidImei,
    AppSetSwiHostDevInfo,
    AppSetEventReport,
    AppDeleteStoredImage,
	AppSetPower,
    AppGetAutoSimList,
    AppSetAutoSimList,
    AppSetAutoSimList2,
	AppSetCustomFeatures
};

#endif //__LITE_QMI_DMS_H__
