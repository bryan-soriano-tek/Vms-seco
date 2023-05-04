/*************
 *
 * Filename:    user_input.h
 *
 * Purpose:     Contains function for handling user input functionalities
 *
 * Copyright: © 2022 Sierra Wireless Inc., all rights reserved
 *
 **************/
#ifndef __USER_INPUT_H__
#define __USER_INPUT_H__

#ifdef __cplusplus
extern "C" {
#endif

#pragma once
#include <stdint.h>
#include <stdbool.h>

#define SUCCESS                  0
#define ENTER_KEY                0x0A
#define ENTER_KEY_PRESSED        0
#define OPTION_LEN               16
#define MAX_MASK_SIZE			 20

#define MAX_FIELD_SIZE           128
#define MAX_INT16_VALUE_SIZE     0x7FFF
#define MAX_INT32_VALUE_SIZE	 0x7FFFFFFF
#define MAX_UINT32_VALUE_SIZE	 0xFFFFFFFF
#define MAX_UINT64_VALUE_SIZE	 0xFFFFFFFFFFFFFFFF

extern const char* const g_enterActionLeaveEmpty;
extern const char* const g_enterActionExit;
extern const char* const g_enterActionDefault;
extern const char* const g_enterActionZero;

void FlushStdinStream();
uint8_t GetStringFromUser(const char* pOptionList, const char* pFieldName, const char* pEnterAction, char* pBuffer, int bufLen);
int GetNumericValue(const char* pOptionList, const char* pFieldName, const char* pEnterAction, int enterVal, int min, int max);
uint64_t GetNumericValue64(const char* pOptionList, const char* pFieldName, const char* pEnterAction, unsigned int enterVal, unsigned int min, uint64_t max);
uint16_t GetInt8ArrayValue(const char* pOptionList, const char* pFieldName, const char* pEnterAction, char cDelimiter, uint8_t* pValues, size_t sizeValues);
uint8_t GetIPFromUser(char *pAddressString, char *pIPAddress, uint32_t *pAddress);
uint8_t GetIPv6FromUser(char *pIPAddress, uint8_t *pIpv6_address, uint8_t *pByteCount);
bool ExtractSubStringValue(const char* strSource, const char* strSignature, char cDelimiter, char* pDest, size_t sizeDest);
bool ExtractUInt8Value(const char* strSource, const char* strSignature, char cDelimiter, uint8_t* pDest);
bool ExtractUInt16Value(const char* strSource, const char* strSignature, char cDelimiter, uint16_t* pDest);
bool ExtractUInt32Value(const char* strSource, const char* strSignature, char cDelimiter, uint32_t* pDest);
bool ExtractUInt8ArrayValues(const char* strSource, const char* strSignature, char cDelimiter, char cValDelimiter, uint8_t* pDest, size_t* sizeDest);
bool ExtractUInt16ArrayValues(const char* strSource, const char* strSignature, char cDelimiter, char cValDelimiter, uint16_t* pDest, size_t* sizeDest);
bool ExtractUInt32ArrayValues(const char* strSource, const char* strSignature, char cDelimiter, char cValDelimiter, uint32_t* pDest, size_t* sizeDest);

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif // __USER_INPUT_H__
