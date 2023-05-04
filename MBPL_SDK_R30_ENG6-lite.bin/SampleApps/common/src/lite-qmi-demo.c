#include <stdlib.h>
#include <stdbool.h>
#include "socket_server.h"
#include "lite-qmi-demo.h"

void DisplayResult(const char* func, int ret, swi_uint256_t* pParamPresenceMask, result_func result_proc, void* result_context)
{
	if (ret == eQCWWAN_ERR_NONE)
	{
		SockPrintf(ANSI_COLOR_GREEN);
		if (pParamPresenceMask)
			SockPrintf("%s ret: %d Mask: 0x%8.8x\n", func, ret, *(pParamPresenceMask->word));
		else
			SockPrintf("%s ret: %d\n", func, ret);

		if (result_proc)
			result_proc(result_context);
	}
	else
	{
		SockPrintf(ANSI_COLOR_RED);
		SockPrintf("%s errorCode: %d - %s\n", func, ret, helper_get_error_reason(ret));
	}
	SockPrintf(ANSI_COLOR_RESET);
}
