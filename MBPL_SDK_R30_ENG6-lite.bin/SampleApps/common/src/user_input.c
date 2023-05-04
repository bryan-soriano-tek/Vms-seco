#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <arpa/inet.h>
#include "str_util.h"
#include "user_input.h"

const char* const g_enterActionLeaveEmpty = "leave the field as blank";
const char* const g_enterActionExit = "exit";
const char* const g_enterActionDefault = "use default value";
const char* const g_enterActionZero = "set value 0";

/*
 * Name:     FlushStdinStream
 *
 * Purpose:  Flush the stdin stream
 *
 * Params:   None
 *
 * Return:   None
 *
 * Notes:    fflush does not work for input stream.
 */
void FlushStdinStream()
{
	int inputChar;

	/* keep on reading until a <New Line> or end of file is received */
	do
	{
		inputChar = getchar();

#ifdef DBG
		fprintf(stderr, "inputChar: 0x%x\n", inputChar);
#endif
	} while ((inputChar != ENTER_KEY) && (inputChar != EOF));
}

/*
 * Name:     GetStringFromUser
 *
 * Purpose:  Prompt the user to enter a string and store it in the received
 *           buffer.
 *
 * Params:   pFieldName - Name of the string to be retrieved.
 *           pBuffer    - Buffer to receive the string from user.
 *           bufLen     - Length of the buffer to receive the string from user.
 *
 * Return:   SUCCESS   - If the user enters a valid value
 *           ENTER_KEY - If the user presses the Enter key
 *
 * Notes:    None
 */
uint8_t GetStringFromUser(const char* pOptionList, const char* pFieldName, const char* pEnterAction, char* pBuffer, int bufLen)
{
	/* Print the menu */
	if (pOptionList)
		fprintf(stderr, "\n%s", pOptionList);

	fprintf(stderr, "\nPlease enter %s (up to %d Characters), or press <Enter> to %s: ",
		pFieldName, bufLen - 1, pEnterAction);

	/* Clear the buffer */
	memset(pBuffer, 0, bufLen);

	/* Receive the input from the user */
	while (fgets(pBuffer, bufLen, stdin) == NULL);

	/* If '/n' character is not read, there are more characters in input
		* stream. Clear the input stream.
		*/
	if (NULL == strchr(pBuffer, ENTER_KEY))
		FlushStdinStream();

	/* If only <ENTER> is pressed by the user, return to main menu */
	uint8_t rtn = ENTER_KEY == pBuffer[0] ? ENTER_KEY : ENTER_KEY_PRESSED;

	/* Remove the enter key read at the end of the buffer */
	size_t len = strlen(pBuffer);
	if (len > 0 && pBuffer[len - 1] == ENTER_KEY)
		pBuffer[len - 1] = '\0';

#ifdef DBG
	fprintf(stderr, "Entered Value : %s\n", pBuffer);
#endif

	return rtn;
}

int GetDigits(int n)
{
	int nDigits = 0;
	do
	{
		nDigits++;
		n /= 10;
	} while (n != 0);

	return nDigits;
}

int GetNumericValue(const char* pOptionList, const char* pFieldName, const char* pEnterAction, int enterVal, int min, int max)
{
	int nValue = 0;

	do
	{
		char pBuf[OPTION_LEN];
		int nBufLen = GetDigits(max) + 3;
		if (GetStringFromUser(pOptionList, pFieldName, pEnterAction, pBuf, nBufLen > OPTION_LEN ? OPTION_LEN : nBufLen) == ENTER_KEY)
			return enterVal;

		/* Convert the authentication value provided by user into integer */
		nValue = strtol(pBuf, NULL, 0);
	} while (nValue < min || nValue > max);

	return nValue;
}

uint64_t GetDigits64(uint64_t n)
{
	uint64_t nDigits = 0;
	do
	{
		nDigits++;
		n /= 10;
	} while (n != 0);

	return nDigits;
}

uint64_t GetNumericValue64(const char* pOptionList, const char* pFieldName, const char* pEnterAction, unsigned int enterVal, unsigned int min, uint64_t max)
{
	uint64_t nValue = 0;

	do
	{
		char pBuf[MAX_MASK_SIZE];
		uint64_t nBufLen = GetDigits64(max) + 1;
		if (GetStringFromUser(pOptionList, pFieldName, pEnterAction, pBuf, nBufLen > MAX_MASK_SIZE ? MAX_MASK_SIZE : nBufLen) == ENTER_KEY)
			return enterVal;

		/* Convert the authentication value provided by user into integer */
		nValue = (uint64_t)strtol(pBuf, NULL, 0);
	} while (nValue < min || nValue > max);

	return nValue;
}

uint16_t GetInt8ArrayValue(const char* pOptionList, const char* pFieldName, const char* pEnterAction, char cSeperator, uint8_t* pValues, size_t sizeValues)
{
	char pBuf[MAX_FIELD_SIZE];
	if (GetStringFromUser(pOptionList, pFieldName, pEnterAction, pBuf, MAX_FIELD_SIZE) == ENTER_KEY)
		return 0;

	uint16_t i = 0;
	const char* valueStr = pBuf;

	while (valueStr && i < sizeValues)
	{
		// Advance pointer to first digit number
		while ((*valueStr < '0' || *valueStr > '9') && *valueStr != 0)
			valueStr++;

		if (*valueStr == 0)
			break;

		pValues[i++] = atoi(valueStr);
		valueStr = strchr(valueStr, cSeperator);
	};

	return i;
}

/*
 * Name:     GetIPFromUser
 *
 * Purpose:  Prompt the user to enter the IP address and copy it in the passed
 *           buffer.
 *
 * Return:   SUCCESS   - In case valid IP Address is entered by the user
 *           ENTER_KEY - If enter key is pressed by the user
 *
 * Params:   pAddressString - Name of the address to be retrieved.
 *           pIPAddress     - Buffer to receive the address from user.
 *           pAddress       - Pointer to store received IP address after
 *                            conversion from dot notation to ULONG value.
 *
 * Notes:    None
 */
uint8_t GetIPFromUser(char *pAddressString, char *pIPAddress, uint32_t *pAddress)
{
	char szFieldName[MAX_FIELD_SIZE];
	sprintf(szFieldName, "%s Address in xxx.xxx.xxx.xxx format", pAddressString);

	do
	{
		if (GetStringFromUser(NULL, szFieldName, g_enterActionLeaveEmpty, pIPAddress, MAX_FIELD_SIZE) == ENTER_KEY)
		{
			*pAddress = 0;
			return ENTER_KEY;
		}

		uint8_t count = 0, IPAddressWrong = 0;

		/* Check if there is nothing followed by a Dot in the IP address or
		 * there are two adjacent dots.
		 */
		char *pCharacterOccurence = strchr(pIPAddress, '.');
		while (NULL != pCharacterOccurence)
		{
			if (('.' == pCharacterOccurence[1]) ||
				('\0' == pCharacterOccurence[1]))
			{
#ifdef DBG
				fprintf(stderr, "Two Adjacent dots or NULL after a dot:"\
					"Wrong IP Address\n");
#endif
				IPAddressWrong = 1;
				break;
			}

			count++;
			pCharacterOccurence = strchr((pCharacterOccurence + 1), '.');
		}

		/* If there are more than three dots in the IP address */
		if ((count != 3) || (IPAddressWrong == 1))
		{
#ifdef DBG
			fprintf(stderr, "Incorrect No. of dots in address : %d\n", count);
#endif
			IPAddressWrong = 0;
			count = 0;
			continue;
		}

		count = 0;

		/* Convert the IP address from DOT notation to ULONG */
	} while (inet_pton(AF_INET, pIPAddress, pAddress) == 0);

	/* Valid IP Address has been retrieved */
	return SUCCESS;
}

/*
 * Name:     GetIPv6FromUser
 *
 * Purpose:  Prompt the user to enter the IPV6 address and copy it in the passed
 *           buffer.
 *
 * Return:   SUCCESS   - In case valid IP Address is entered by the user
 *           ENTER_KEY - If enter key is pressed by the user
 *
 * Params:   pIPAddress     - Buffer to receive the address from user.
 *           pIpv6_address  - Pointer to store received IP address after
 *                            conversion from dot notation to uint8_t[16].
 * Notes:    None
 */
uint8_t GetIPv6FromUser(char *pIPAddress, uint8_t *pIpv6_address, uint8_t *pByteCount)
{
	char szFieldName[MAX_FIELD_SIZE] = { 0 };
	strcpy(szFieldName, "IPV6 Address in xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx format");

	if (GetStringFromUser(NULL, szFieldName, g_enterActionLeaveEmpty, pIPAddress, MAX_FIELD_SIZE) == ENTER_KEY)
	{
		*pIpv6_address = 0;
		*pIpv6_address = 0;

		return ENTER_KEY;
	}

	uint8_t index = 0;
	char *pSemicolon1 = pIPAddress;
	char szWord[5] = { 0 };
	*pByteCount = 0;
	uint8_t maxByte = 0xFF;
	int length = strlen(pIPAddress);

	char *pSemicolon2 = strchr(pIPAddress, ':');
	if (pSemicolon2 == NULL)
		pSemicolon2 = pIPAddress + length;

	uint16_t ipValue = 0;
	while ((pSemicolon2 - pSemicolon1) > 0)
	{
		if (StrNCpy(szWord, pSemicolon1, pSemicolon2 - pSemicolon1) < (pSemicolon2 - pSemicolon1))
		{
#ifdef DBG
			fprintf(stderr, "More than 4 characters between two semicolons:"\
				"Wrong IP Address\n");
#endif
			return maxByte;
		}
		sscanf(szWord, "%"SCNx16, &ipValue);
		*pIpv6_address++ = ipValue >> 8;
		*pIpv6_address++ = (uint8_t)(ipValue & 0x00FF);
		index++;

		*pByteCount += 2;
		/* If there are more than 15 dots in the IP address */
		if (index > 8)
		{
#ifdef DBG
			fprintf(stderr, "Incorrect No. of semicolon in address : %d\n", count);
#endif
			return maxByte;
		}

		if (pSemicolon2 == (pIPAddress + length))
			break;
		pSemicolon1 = pSemicolon2 + 1;
		pSemicolon2 = strchr(pSemicolon1, ':');
		if (pSemicolon2 == NULL)
			pSemicolon2 = pIPAddress + length;
	}

	/* Valid IPV6 Address has been retrieved */
	return SUCCESS;
}

bool ExtractSubStringValue(const char* strSource, const char* strSignature, char cDelimiter, char* pDest, size_t sizeDest)
{
	if (strSource == NULL || strSignature == NULL || pDest == NULL || sizeDest == 0)
		return false;

	*pDest = 0;	// Preset to empty string

	char* pChar = strstr(strSource, strSignature);
	if (pChar)
	{
		pChar += strlen(strSignature);

		char* pCharEnd = strchr(pChar, cDelimiter != 0 ? cDelimiter : ',');
		if (pCharEnd == NULL && cDelimiter == 0)
			pCharEnd = strchr(pChar, ' ');

		if (pCharEnd)
			strncpy_s(pDest, sizeDest, pChar, pCharEnd - pChar);
		else
			strcpy_s(pDest, sizeDest, pChar);
	}

	return strlen(pDest) > 0;
}

bool ExtractUInt32Value(const char* strSource, const char* strSignature, char cDelimiter, uint32_t* pDest)
{
	char strValue[32];
	bool bFound = ExtractSubStringValue(strSource, strSignature, cDelimiter, strValue, sizeof(strValue));
	if (bFound)
		*pDest = strtol(strValue, NULL, 0);

	return bFound;
}

bool ExtractUInt8Value(const char* strSource, const char* strSignature, char cDelimiter, uint8_t* pDest)
{
	uint32_t val = 0;
	bool bFound = ExtractUInt32Value(strSource, strSignature, cDelimiter, &val);
	if (bFound)
		*pDest = (uint8_t)val;

	return bFound;
}

bool ExtractUInt16Value(const char* strSource, const char* strSignature, char cDelimiter, uint16_t* pDest)
{
	uint32_t val = 0;
	bool bFound = ExtractUInt32Value(strSource, strSignature, cDelimiter, &val);
	if (bFound)
		*pDest = (uint16_t)val;

	return bFound;
}

bool ExtractUInt8ArrayValues(const char* strSource, const char* strSignature, char cDelimiter, char cValDelimiter, uint8_t* pDest, size_t* sizeDest)
{
	char strValue[32];
	bool bFound = ExtractSubStringValue(strSource, strSignature, cDelimiter, strValue, sizeof(strValue));
	if (bFound)
	{
		char* pValue = strValue;
		size_t i = 0;
		for (; pValue && i < *sizeDest; i++)
		{
			pDest[i] = strtol(pValue, NULL, 0);
			pValue = strchr(pValue, cValDelimiter);
			if (pValue)
				pValue++;
		}

		*sizeDest = i;
	}

	return bFound;
}

bool ExtractUInt16ArrayValues(const char* strSource, const char* strSignature, char cDelimiter, char cValDelimiter, uint16_t* pDest, size_t* sizeDest)
{
	char strValue[32];
	bool bFound = ExtractSubStringValue(strSource, strSignature, cDelimiter, strValue, sizeof(strValue));
	if (bFound)
	{
		char* pValue = strValue;
		size_t i = 0;
		for (; pValue && i < *sizeDest; i++)
		{
			pDest[i] = strtol(pValue, NULL, 0);
			pValue = strchr(pValue, cValDelimiter);
			if (pValue)
				pValue++;
		}
	}

	return bFound;
}

bool ExtractUInt32ArrayValues(const char* strSource, const char* strSignature, char cDelimiter, char cValDelimiter, uint32_t* pDest, size_t* sizeDest)
{
	char strValue[32];
	bool bFound = ExtractSubStringValue(strSource, strSignature, cDelimiter, strValue, sizeof(strValue));
	if (bFound)
	{
		char* pValue = strValue;
		size_t i = 0;
		for (; pValue && i < *sizeDest; i++)
		{
			pDest[i] = strtol(pValue, NULL, 0);
			pValue = strchr(pValue, cValDelimiter);
			if (pValue)
				pValue++;
		}
	}

	return bFound;
}
