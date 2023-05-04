/*************
 *
 * Filename:    socket_server.h
 *
 * Purpose:     Contains function for handling socket requests
 *
 * Copyright: © 2022 Sierra Wireless Inc., all rights reserved
 *
 **************/
#ifndef __SOCKET_SERVER_H__
#define __SOCKET_SERVER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "user_input.h"

enum ARGUMENT_TYPE
{
	eDEPENDS,	// Mandatory or not is conditional
	eMANDATORY,	// Mandatory argument
	eOPTIONAL	// Optional argument
};

enum ARGUMENT_AVAIL
{
	eFound,			// Argument value is provided
	eFlagNotFound,	// Argument is not found
	eValueNotFound	// Argument is specified but value is missing
};

// Properties of argument
typedef struct
{
	const char* arg_short;		// Short form of argument
	const char* arg;			// Long form of argument
	const char* desc;			// Description of the argument
	const char* desc_short;		// Short description of the argument
	enum ARGUMENT_TYPE type;	// Type of argument
} ARGUMENT_SET;

// Properties of command
typedef struct
{
	const char* cmd;	// Command string
	const char* desc;	// Description of the command
	size_t arg_len;		// Number of arguments for the command
	ARGUMENT_SET* args;	// Pointer to argument array
	int opt;			// Command option ID
} COMMAND_SET;

// Map between value string and value number
typedef struct
{
	const char* str;
	uint8_t val;
} StrIntValMap;

//
// OpenSocket
//		Opens socket with specified name.
//
// param: socket_name [I] - Name of the socket
//
// returns: Socket file descriptor
//			- none 0 if socket is opened, 0 if failed
//
int OpenSocket(const char* socket_name);

//
// CloseSocket
//		Close opened socket.  Do nothing is socket is not opened
//
// param: none
//
// returns: void
//
void CloseSocket();

//
// LockSocket
//		Prevent other threads from writing to socket until it is unlocked
//
// param: none
//
// returns: void
//
void LockSocket();

//
// UnlockSocket
//		Allow other threads to write to socket after locking it
//
// param: none
//
// returns: void
//
void UnlockSocket();

//
// SockPrintf
//		Same as printf but to opened socket
//
// param: see printf
//
// returns: void
//
void SockPrintf(const char* const fmt, ...);

//
// SockLog
//		Logs to syslog and output to socket
//
// param: lvl [I] - level of output to syslog
//		  For the rest see printf
//
// returns: void
//
void SockLog(int lvl, const char* const fmt, ...);

//
// GetArgumentTypeString
//		Get argument requirement type string
//
// param: type [I] - enum ARGUMENT_TYPE value
//
// returns: Description string of type
//
const char* GetArgumentTypeString(enum ARGUMENT_TYPE type);

//
// PrintHelp
//		Print help information of command set
//
// param: procname		[I] - process name
//		  cmdset		[I] - Pointer to COMMAND_SET array
//		  size_cmdset	[I] - Size of COMMAND_SET array
//		  command		[I] - Command the information to be printed.  If NULL, print all commands
//
// returns: void
//
void PrintHelp(const char* procname, const COMMAND_SET* cmdset, size_t size_cmdset, const char* command);

//
// OutputPrompt
//		Output interactive prompt information of command set in stdout
//
// param: cmdset		[I] - Pointer to COMMAND_SET array
//		  size_cmdset	[I] - Size of COMMAND_SET array
//
// returns: void
//
void OutputPrompt(const COMMAND_SET* cmdset, size_t size_cmdset);

//
// OutputPrompt
//		Print command list usage information
//
// param: cmdset		[I] - Pointer to COMMAND_SET array
//		  size_cmdset	[I] - Size of COMMAND_SET array
//
// returns: void
//
void PrintCmdListUsage(const COMMAND_SET* cmdset, size_t size_cmdset);

//
// Command2Option
//		Return the option ID of the provided command string
//
// param: cmdset		[I] - Pointer to COMMAND_SET array
//		  size_cmdset	[I] - Size of COMMAND_SET array
//		  command		[I] - Command to be found
//		  nInvalidCmd	[I] - ID to be reutrned if command is not found
//
// returns: Option ID of the command, or nInvalidCmd if the command cannot be found in cmdset
//
int Command2Option(const COMMAND_SET* cmdset, size_t size_cmdset, const char* command, int nInvalidCmd);

//
// GetSocketCommand
//		Return the option ID of the provided command string
//
// param: cmdset		[I] - Pointer to COMMAND_SET array
//		  size_cmdset	[I] - Size of COMMAND_SET array
//		  command		[O] - If not NULL, returns the command string from socket
//		  nInvalidCmd	[I] - ID to be reutrned if command is not found
//
// returns: Option ID of the command, or nInvalidCmd if the command cannot be found in cmdset
//
int GetSocketCommand(const COMMAND_SET* cmdset, size_t size_cmdset, char** command, int nInvalidCmd);

//
// GetMappedStrValue
//		Return the mapped value number of the provided string
//
// param: valueStr	[I] - Pointer to string to search for
//		  pMap		[I] - Pointer to StrIntValMap array
//		  mapSize	[I] - Size of StrIntValMap array
//		  pValue	[O] - The mapped value of the string, if found
//
// returns: If argument value is found.  See ARGUMENT_AVAIL
//
enum ARGUMENT_AVAIL GetMappedStrValue(const char* valueStr, StrIntValMap* pMap, size_t mapSize, uint8_t* pValue);

//
// GetNameStringValuePair
//		Separate name and value in the pair string with format 'name=value'
//
// param: pair		[I] - Pointer to string to search for
//		  name		[O] - Buffer for name
//		  sName		[I] - Size of name buffer
//		  value		[O] - Buffer for value
//		  sValue	[I] - Size of value buffer
//
// returns: If argument value is found.  See ARGUMENT_AVAIL
//
enum ARGUMENT_AVAIL GetNameStringValuePair(const char* pair, char* name, int sName, char* value, int sValue);

//
// GetNameByteValuePair
//		Separate name and value in the pair string with format 'name=value'.  Return value as number
//
// param: pair		[I] - Pointer to string to search for
//		  name		[O] - Buffer for name
//		  sName		[I] - Size of name buffer
//		  value		[O] - Pointer to 8-bit value
//
// returns: If argument value is found.  See ARGUMENT_AVAIL
//
enum ARGUMENT_AVAIL GetNameByteValuePair(const char* pair, char* name, int sName, char* value);

//
// GetArgumentStrValue
//		Get the string value of the specified argument from the array
//
// param: pCmd		[I] - Command string.  Used for outputing error message if argument list is empty.  Could be NULL.
//		  pArg		[I] - Argument which value to search for
//		  ppValue	[O] - Pointer to the argument string value on output, if found
//
// returns: If argument value is found.  See ARGUMENT_AVAIL
//
enum ARGUMENT_AVAIL GetArgumentStrValue(const char* pCmd, const ARGUMENT_SET* pArg, const char** ppValue);

//
// CloneArgumentStrValue
//		Copy the string value of the specified argument to provided buffer
//
// param: pCmd		[I] - Command string.  Used for outputing error message if argument list is empty.  Could be NULL.
//		  pArg		[I] - Argument which value to search for
//		  pValue	[O] - Pointer to buffer to copy the argument string value to, if found
//		  size		[I] - Size of the pValue buffer
//
// returns: If argument value is found.  See ARGUMENT_AVAIL
//
enum ARGUMENT_AVAIL CloneArgumentStrValue(const char* pCmd, const ARGUMENT_SET* pArg, char* pValue, int size);

//
// CloneArgumentStrValueWithLen8
//		Copy the string value of the specified argument to provided buffer
//
// param: pCmd		[I] - Command string.  Used for outputing error message if argument list is empty.  Could be NULL.
//		  pArg		[I] - Argument which value to search for
//		  pValue	[O] - Pointer to buffer to copy the argument string value to, if found
//		  size		[I] - Size of the pValue buffer
//		  pLen		[O] - 8-bit length of the string, if found
//
// returns: If argument value is found.  See ARGUMENT_AVAIL
//
enum ARGUMENT_AVAIL CloneArgumentStrValueWithLen8(const char* pCmd, const ARGUMENT_SET* pArg, char* pValue, int size, uint8_t* pLen);

//
// GetArgumentIntValue
//		Get the unsigned int value of the specified argument from the array
//
// param: pCmd		[I] - Command string.  Used for outputing error message if argument list is empty.  Could be NULL.
//		  pArg		[I] - Argument which value to search for
//		  pValue	[O] - Pointer to the argument uint value on output, if found
//
// returns: If argument value is found.  See ARGUMENT_AVAIL
//
enum ARGUMENT_AVAIL GetArgumentIntValue(const char* pCmd, const ARGUMENT_SET* pArg, unsigned int* pValue);

//
// GetArgumentIntValueWithSetFlag
//		Get the unsigned int value of the specified argument from the array
//
// param: pCmd		[I] - Command string.  Used for outputing error message if argument list is empty.  Could be NULL.
//		  pArg		[I] - Argument which value to search for
//		  pValue	[O] - Pointer to the argument uint value on output, if found
//        pSet		[O] - Pointer to boolean flag if the value is set on output
//
// returns: If argument value is found.  See ARGUMENT_AVAIL
//
enum ARGUMENT_AVAIL GetArgumentIntValueWithSetFlag(const char* pCmd, const ARGUMENT_SET* pArg, unsigned int* pValue, bool* pSet);

//
// GetArgumentByteValue
//		Get the unsigned char value of the specified argument from the array
//
// param: pCmd		[I] - Command string.  Used for outputing error message if argument list is empty.  Could be NULL.
//		  pArg		[I] - Argument which value to search for
//		  pValue	[O] - Pointer to the argument unsigned char value on output
//
// returns: If argument value is found.  See ARGUMENT_AVAIL
//
enum ARGUMENT_AVAIL GetArgumentByteValue(const char* pCmd, const ARGUMENT_SET* pArg, unsigned char* pValue);

//
// GetArgumentInt16Value
//		Get the unsigned 16-bit integer value of the specified argument from the array
//
// param: pCmd		[I] - Command string.  Used for outputing error message if argument list is empty.  Could be NULL.
//		  pArg		[I] - Argument which value to search for
//		  pValue	[O] - Pointer to the argument unsigned 16-bit integer value on output
//
// returns: If argument value is found.  See ARGUMENT_AVAIL
//
enum ARGUMENT_AVAIL GetArgumentInt16Value(const char* pCmd, const ARGUMENT_SET* pArg, uint16_t* pValue);

//
// GetArgumentBoolValue
//		Get the unsigned char value of the specified argument from the array
//
// param: pCmd		[I] - Command string.  Used for outputing error message if argument list is empty.  Could be NULL.
//		  pArg		[I] - Argument which value to search for
//		  pValue	[O] - Pointer to the argument bool value on output
//
// returns: If argument value is found.  See ARGUMENT_AVAIL
//
enum ARGUMENT_AVAIL GetArgumentBoolValue(const char* pCmd, const ARGUMENT_SET* pArg, bool* pValue);

//
// GetArgumentByteBool01Value
//		Get the unsigned char value of the specified argument from the array
//
// param: pCmd		[I] - Command string.  Used for outputing error message if argument list is empty.  Could be NULL.
//		  pArg		[I] - Argument which value to search for
//		  pValue	[O] - Pointer to the argument unsigned char value on output, 0 for false, 1 for true
//
// returns: If argument value is found.  See ARGUMENT_AVAIL
//
enum ARGUMENT_AVAIL GetArgumentByteBool01Value(const char* pCmd, const ARGUMENT_SET* pArg, unsigned char* pValue);

//
// GetArgumentIntValueWithSetFlag
//		Get the unsigned int value of the specified argument from the array
//
// param: pCmd		[I] - Command string.  Used for outputing error message if argument list is empty.  Could be NULL.
//		  pArg		[I] - Argument which value to search for
//		  pValue	[O] - Pointer to the argument unsigned char value on output, 0 for false, 1 for true
//        pSet		[O] - Pointer to boolean flag if the value is set on output
//
// returns: If argument value is found.  See ARGUMENT_AVAIL
//
enum ARGUMENT_AVAIL GetArgumentByteBool01ValueWithSetFlag(const char* pCmd, const ARGUMENT_SET* pArg, unsigned char* pValue, bool* pSet);

//
// GetArgumentMappedStrValue
//		Get the mapped unsigned byte value of the specified argument from the array
//
// param: pCmd		[I] - Command string.  Used for outputing error message if argument list is empty.  Could be NULL.
//		  pArg		[I] - Argument which value to search for
//		  pMap		[I] - Pointer to StrIntValMap array
//		  mapSize	[I] - Size of StrIntValMap array
//		  pValue	[O] - Pointer to the argument unsigned char value on output
//
// returns: If argument value is found.  See ARGUMENT_AVAIL
//
enum ARGUMENT_AVAIL GetArgumentMappedStrValue(const char* pCmd, const ARGUMENT_SET* pArg, StrIntValMap* pMap, size_t mapSize, uint8_t* pValue);

//
// GetArgumentMappedStrUint32Value
//		Get the mapped unsigned 32-bit int value of the specified argument from the array
//
// param: pCmd		[I] - Command string.  Used for outputing error message if argument list is empty.  Could be NULL.
//		  pArg		[I] - Argument which value to search for
//		  pMap		[I] - Pointer to StrIntValMap array
//		  mapSize	[I] - Size of StrIntValMap array
//		  pValue	[O] - Pointer to the argument unsigned 32-bit int value on output
//
// returns: If argument value is found.  See ARGUMENT_AVAIL
//
enum ARGUMENT_AVAIL GetArgumentMappedStrUint32Value(const char* pCmd, const ARGUMENT_SET* pArg, StrIntValMap* pMap, size_t mapSize, uint32_t* pValue);

//
// GetArgumentIpValue
//		Get the 32-bit ipv4 address value of the specified argument from the array
//
// param: pCmd		[I] - Command string.  Used for outputing error message if argument list is empty.  Could be NULL.
//		  pArg		[I] - Argument which value to search for
//		  pValue	[O] - Pointer to the argument ipv4 address value on output
//
// returns: If argument value is found.  See ARGUMENT_AVAIL
//
enum ARGUMENT_AVAIL GetArgumentIpValue(const char* pCmd, const ARGUMENT_SET* pArg, uint32_t* pValue);

//
// GetArgumentIpv6Value
//		Get the 128-bit ipv6 address value of the specified argument from the array
//
// param: pCmd		   [I] - Command string.  Used for outputing error message if argument list is empty.  Could be NULL.
//		  pArg		   [I] - Argument which value to search for
//		  pValue	   [O] - Buffer to store ipv6 address value on output. Must be at least 16 bytes.
//
// returns: If argument value is found.  See ARGUMENT_AVAIL
//
enum ARGUMENT_AVAIL GetArgumentIpv6Value(const char* pCmd, const ARGUMENT_SET* pArg, uint8_t* pValue, size_t size);

// GetArgumentInt64Value
//		Get the unsigned int value of the specified argument from the array
//
// param: pCmd		[I] - Command string.  Used for outputing error message if argument list is empty.  Could be NULL.
//		  pArg		[I] - Argument which value to search for
//		  pValue	[O] - Pointer to the argument uint value on output, if found
//
// returns: If argument value is found.  See ARGUMENT_AVAIL
//
enum ARGUMENT_AVAIL GetArgumentInt64Value(const char* pCmd, const ARGUMENT_SET* pArg, uint64_t* pValue);

//
// GetArgumentInt16Value
//		Get the unsigned int16 value of the specified argument from the array
//
// param: pCmd		[I] - Command string.  Used for outputing error message if argument list is empty.  Could be NULL.
//		  pArg		[I] - Argument which value to search for
//		  pValue	[O] - Pointer to the argument uint value on output, if found
//
// returns: If argument value is found.  See ARGUMENT_AVAIL
//
enum ARGUMENT_AVAIL GetArgumentInt16Value(const char* pCmd, const ARGUMENT_SET* pArg, uint16_t* pValue);

//
// GetArgumentInt8ArrayValue
//		Get the unsigned int16 value of the specified argument from the array
//
// param: pCmd		[I] - Command string.  Used for outputing error message if argument list is empty.  Could be NULL.
//		  pArg		[I] - Argument which value to search for
//		  cSeperator[I] - Seperator charactor for values in input string
//		  pLen		[O] - Pointer to size of the filled array
//		  pValues	[O] - Pointer to value array
//		  pArg		[I] - Size of value array
//
// returns: If argument value is found.  See ARGUMENT_AVAIL
//
enum ARGUMENT_AVAIL GetArgumentInt8ArrayValue(const char* pCmd, const ARGUMENT_SET* pArg, char cSeperator, uint16_t* pLen, uint8_t* pValues, size_t sizeValues);

#define CLONE_ARG_STR_VALUE(c, a, v) CloneArgumentStrValue((c), (a), (v), sizeof((v)))
#define CLONE_ARG_STR_VALUE_WITH_LEN8(c, a, v, l) CloneArgumentStrValueWithLen8((c), (a), (v), sizeof((v)), (l))
#define GET_ARG_MAPPED_STR_VALUE(c, a, m, v) GetArgumentMappedStrValue((c), (a), (m), sizeof((m))/sizeof(StrIntValMap), (v))
#define GET_ARG_MAPPED_UINT32_VALUE(c, a, m, v) GetArgumentMappedStrUint32Value((c), (a), (m), sizeof((m))/sizeof(StrIntValMap), (v))
#define GET_ARG_INT8_ARRAY_VALUE(c, a, s, l, v) GetArgumentInt8ArrayValue((c), (a), (s), (l), (v), sizeof((v)))

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif // __SOCKET_SERVER_H__
