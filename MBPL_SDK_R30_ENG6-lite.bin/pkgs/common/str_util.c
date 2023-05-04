#include "str_util.h"

int strncpy_s(char* pDest, size_t dest_size, const char* pSrc, size_t n)
{
	if (pDest == NULL || dest_size == 0 || (pSrc == NULL && n > 0))
		return -1;

	if (n >= dest_size)
		n = dest_size - 1;
	
	if (n > 0)
		strncpy(pDest, pSrc, n);

	pDest[n] = 0;

	return n;
}

int strcpy_s(char* pDest, size_t dest_size, const char* pSrc)
{
	return strncpy_s(pDest, dest_size, pSrc, pSrc ? strlen(pSrc) : 0);
}

char* strcat_s(char* pDest, size_t dest_size, const char* pSrc)
{
	if (pDest && dest_size > 0 && pSrc &&
		strlen(pSrc) + strlen(pDest) < dest_size)
		strcat(pDest, pSrc);

	return pDest;
}
