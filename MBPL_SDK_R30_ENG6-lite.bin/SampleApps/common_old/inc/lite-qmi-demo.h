#ifndef __LITE_QMI_DEMO_H__
#define __LITE_QMI_DEMO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include "msgid.h"
#include "qmerrno.h"

#define MAX_SERVICE_NAME_SIZE   64
#define MAX_TEST_ID_INPUT_SIZE  16

#define MAX_DEBUG_BUF_SIZE  1024

//typedef enum _status_code 
//{
//    SUCCESS =  0,    // The operation succeeded.
//    FAILURE = -1,    // The operation failed.    
//} status_code, *pstatus_code;
#define INVALID_ID -1

//return if dump function input argument is NULL
#define CHECK_DUMP_ARG_PTR_IS_NULL if (NULL == ptr) { return ;};

//return if pointer is NULL
#define RETURN_IF_PTR_IS_NULL(x) if (NULL == x) { return ;};

#define IFPRINTF(s,p)   if( NULL != p ){ printf(s,*p); }

// This could be moved to a SDKLITE header
#define QMI_HDR_LEN      6

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef void (*result_func)(void*);

void DisplayResult(const char* func, int ret, swi_uint256_t* pParamPresenceMask, result_func result_proc, void* result_context);

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif //__LITE_QMI_DEMO_H__

