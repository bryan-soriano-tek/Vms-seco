#ifndef __LITE_QMI_WDS_H__
#define __LITE_QMI_WDS_H__

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
    AppGetKeepAliveOption,
    AppGetResetProfileInfo,
    AppGetApnOpResPcoList,
    AppGetApnMsisdnInfo,
    AppGetDeleteAllProfilesInfo,
    AppGetEhrpdFallbackApnList,
    AppSetEhrpdFallbackApnList,
    AppSetModemAssistedKaStart,
    AppSetModemAssistedKaStartOptions,
    AppSetModemAssistedKaStop,
    AppSetWdsEventReport,
    AppWdsIndicationRegister,
    AppWdsGetDefaultProfileId,
    AppWdsSetDefaultProfileId,
    AppWdsSet3GPPConfigItems,
    AppWdsSetSetDLThroughputRP,
    AppWdsSetDefaultNssai,
    AppWdsGetProfileSnssai,
    AppWdsSwiConfigureProfile,
    AppWdsDeleteProfile,
    AppWdsClearProfileSnssai,
};

#endif //__LITE_QMI_WDS_H__
