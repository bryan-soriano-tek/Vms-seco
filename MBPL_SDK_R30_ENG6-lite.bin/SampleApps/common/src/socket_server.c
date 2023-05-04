/**************
 *
 * Filename:    socket_server.c
 *
 * Purpose:     Provide support as socket server receiving commands and sending feedbacks
 *              from and to socket clients
 *
 * Copyright: © 2022 Sierra Wireless Inc., all rights reserved
 *
 **************/
#include <stdlib.h>
#include <poll.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdarg.h>
#include <errno.h>
#include <pthread.h>
#include "str_util.h"
#include "proc_util.h"
#include "socket_server.h"

// If defined, take user input string as if it were from socket
//#define FAKE_SOCKET

// Cache the name of the socket opened
#define MAX_SOCKET_NAME_SIZE 256
char g_socketName[MAX_SOCKET_NAME_SIZE] = "";

// File descriptor of the socket
int g_mainSocketFd = 0;
int g_clientSocketFd = 0;

// Cache command message received over the socket
#define MAX_SOCKET_MESSAGE_SIZE 512
char message[MAX_SOCKET_MESSAGE_SIZE];

// Maximum argv size
#define MAX_ARGV	32
char* argv[MAX_ARGV];
int argc = 0;

pthread_mutex_t socketWriteLock;

void LockSocket()
{
	pthread_mutex_lock(&socketWriteLock);
}

void UnlockSocket()
{
	pthread_mutex_unlock(&socketWriteLock);
}

const char* GetArgumentTypeString(enum ARGUMENT_TYPE type)
{
	switch (type)
	{
	case eDEPENDS:
		return "(Conditional)";
	case eMANDATORY:
		return "(Mandatory)";
	case eOPTIONAL:
		return "(Optional)";
	default:
		break;
	}

	return "";
}

void PrintHelp(const char* procname, const COMMAND_SET* cmdset, size_t size_cmdset, const char* command)
{
	SockPrintf("\r\n%s\r\n\r\n", procname);
	SockPrintf("Usage: command [arguments]\r\n\r\n");

	if (command)
		SockPrintf("Command: %s\r\n", command);
	else
		SockPrintf("Supported commands:\r\n\r\n");

	size_t i = 0;
	for (; i < size_cmdset; i++)
	{
		if ((command && strcmp(command, cmdset[i].cmd) != 0) || strlen(cmdset[i].cmd) == 0)
			continue;

		if (command == NULL)
			SockPrintf("%s\r\n", cmdset[i].cmd);
	
		SockPrintf("   %s\r\n", cmdset[i].desc);
		SockPrintf("   arguments: %s\r\n", cmdset[i].arg_len == 0 ? "none" :
			(cmdset[i].arg_len == 1 && cmdset[i].args[0].arg == NULL && cmdset[i].args[0].arg_short == NULL ? cmdset[i].args[0].desc : ""));

		for (size_t j = 0; j < cmdset[i].arg_len; j++)
		{
			if (cmdset[i].args[j].arg == NULL && cmdset[i].args[j].arg_short == NULL)
				break;

			SockPrintf("     -%s  --%s\r\n", cmdset[i].args[j].arg_short, cmdset[i].args[j].arg);
			SockPrintf("       %s %s\r\n", cmdset[i].args[j].desc, GetArgumentTypeString(cmdset[i].args[j].type));
		}

		SockPrintf("\r\n");

		if (command)
			break;
	}

	if (command && i >= size_cmdset)
		SockPrintf("   \"%s\" is not a supported command.\r\n\r\n", command);
}

void OutputPrompt(const COMMAND_SET* cmdset, size_t size_cmdset)
{
	printf("\nPlease select one of the following options or press 'q' to exit:\n");

	for (size_t i = 0; i < size_cmdset; i++)
		if (strlen(cmdset[i].desc) > 0)
			printf("\n    %d.\t%s", cmdset[i].opt, cmdset[i].desc);

	printf("\n    (q)uit to exit: \n");

	fflush(stdout);
}

void PrintCmdListUsage(const COMMAND_SET* cmdset, size_t size_cmdset)
{
	for (size_t i = 0; i < size_cmdset; i++)
	{
		SockPrintf("         %s\n", cmdset[i].cmd);

		if (cmdset[i].arg_len > 0)
		{
			SockPrintf("          Parameters:\n");

			for (size_t j = 0; j < cmdset[i].arg_len; j++)
				SockPrintf("          -%s  --%s %s %s\n",
					cmdset[i].args[j].arg_short, cmdset[i].args[j].arg, cmdset[i].args[j].desc,
					GetArgumentTypeString(cmdset[i].args[j].type));
		}
	}
}

// Internal
const char* GetShortArgumentDesc(const ARGUMENT_SET* pArg)
{
	return pArg->desc_short ? pArg->desc_short : pArg->arg;
}

// Internal
enum ARGUMENT_AVAIL GetNameStringValuePtrPair(const char* pair, char* name, int sName, char** pvalue)
{
	if (pair == NULL || name == NULL || sName == 0 || pvalue == NULL)
		return eValueNotFound;

	char *pCharEnd = strstr(pair, "=");
	if (!pCharEnd)
		return eValueNotFound;

	strncpy_s(name, sName, pair, pCharEnd - pair);
	*pvalue = ++pCharEnd;

	return eFound;
}

enum ARGUMENT_AVAIL GetNameStringValuePair(const char* pair, char* name, int sName, char* value, int sValue)
{
	char* pvalue = NULL;
	if (value == NULL || sValue == 0 || 
		GetNameStringValuePtrPair(pair, name, sName, &pvalue) != eFound)
		return eValueNotFound;

	strcpy_s(value, sValue, pvalue);

	return eFound;
}

enum ARGUMENT_AVAIL GetNameByteValuePair(const char* pair, char* name, int sName, char* value)
{
	char* pvalue = NULL;
	if (value == NULL || GetNameStringValuePtrPair(pair, name, sName, &pvalue) != eFound)
		return eValueNotFound;

	*value = atoi(pvalue);

	return eFound;
}

enum ARGUMENT_AVAIL GetArgumentStrValue(const char* pCmd, const ARGUMENT_SET* pArg, const char** ppValue)
{
	if (argv[0] == NULL && pCmd)
	{
		SockLog(eLOG_INFO, "Error: missing arguments for %s command\n", pCmd);
		return eFlagNotFound;
	}

	enum ARGUMENT_AVAIL rtn = eFlagNotFound;

	for (int i = 0; i < argc; i++)
	{
		if (argv[i] &&
			((argv[i][0] == '-' && strcmp(&argv[i][1], pArg->arg_short) == 0) ||
			(argv[i][0] == '-' && argv[i][1] == '-' && strcmp(&argv[i][2], pArg->arg) == 0)))
		{
			*ppValue = argv[++i];
			rtn = *ppValue == NULL || **ppValue == 0 || **ppValue == '-' ? eValueNotFound : eFound;

			if (rtn != eFound)
				SockLog(eLOG_INFO, "Error: missing %s value after -%s or --%s flag\n",
					GetShortArgumentDesc(pArg), pArg->arg_short, pArg->arg);

			break;
		}
	}

	if (rtn != eFound && pArg->type == eMANDATORY)
		SockLog(eLOG_INFO, "Error: %s parameter is required\n", GetShortArgumentDesc(pArg));

	return rtn;
}

enum ARGUMENT_AVAIL CloneArgumentStrValue(const char* pCmd, const ARGUMENT_SET* pArg, char* pValue, int size)
{
	const char* valueStr = NULL;
	enum ARGUMENT_AVAIL rtn = GetArgumentStrValue(pCmd, pArg, &valueStr);
	if (rtn == eFound)
		strcpy_s(pValue, size, valueStr);

	return rtn;
}

enum ARGUMENT_AVAIL CloneArgumentStrValueWithLen8(const char* pCmd, const ARGUMENT_SET* pArg, char* pValue, int size, uint8_t* pLen)
{
	enum ARGUMENT_AVAIL rtn = CloneArgumentStrValue(pCmd, pArg, pValue, size);
	if (pLen)
		*pLen = rtn == eFound ? (uint8_t)strlen(pValue) : 0;

	return rtn;
}

enum ARGUMENT_AVAIL GetArgumentIntValue(const char* pCmd, const ARGUMENT_SET* pArg, unsigned int* pValue)
{
	ARGUMENT_SET arg = *pArg;
	arg.type = eDEPENDS;

	const char* valueStr = NULL;
	enum ARGUMENT_AVAIL rtn = GetArgumentStrValue(pCmd, &arg, &valueStr);

	if (rtn == eFound)
	{
		char* pEnd;
		*pValue = strtol(valueStr, &pEnd, 10);
		if (*pEnd != '\0')
		{
			SockLog(eLOG_INFO, "Error: %s number could not be converted to an integer\n", GetShortArgumentDesc(pArg));
			rtn = eValueNotFound;
		}
	}

	if (rtn != eFound && pArg->type == eMANDATORY)
		SockLog(eLOG_INFO, "Error: %s number must be specified after -%s or --%s flag\n",
			GetShortArgumentDesc(pArg), pArg->arg_short, pArg->arg);

	return rtn;
}

enum ARGUMENT_AVAIL GetArgumentIntValueWithSetFlag(const char* pCmd, const ARGUMENT_SET* pArg, unsigned int* pValue, bool* pSet)
{
	enum ARGUMENT_AVAIL rtn = GetArgumentIntValue(pCmd, pArg, pValue);
	*pSet = rtn == eFound;
	return rtn;
}

enum ARGUMENT_AVAIL GetArgumentByteValue(const char* pCmd, const ARGUMENT_SET* pArg, unsigned char* pValue)
{
	unsigned int val = 0;
	enum ARGUMENT_AVAIL rtn = GetArgumentIntValue(pCmd, pArg, &val);
	*pValue = (unsigned char)val;
	return rtn;
}

enum ARGUMENT_AVAIL GetArgumentBoolValue(const char* pCmd, const ARGUMENT_SET* pArg, bool* pValue)
{
	const char* valueStr = NULL;
	enum ARGUMENT_AVAIL rtn = GetArgumentStrValue(pCmd, pArg, &valueStr);
	if (rtn == eFound)
	{
		if (strcmp(valueStr, "1") == 0 || strcasecmp(valueStr, "y") == 0 || strcasecmp(valueStr, "yes") == 0 || strcasecmp(valueStr, "t") == 0 || strcasecmp(valueStr, "true") == 0)
			*pValue = true;
		else if (strcmp(valueStr, "0") == 0 || strcasecmp(valueStr, "n") == 0 || strcasecmp(valueStr, "no") == 0 || strcasecmp(valueStr, "f") == 0 || strcasecmp(valueStr, "false") == 0)
			*pValue = false;
		else
			rtn = eValueNotFound;
	}
	
	return rtn;
}

enum ARGUMENT_AVAIL GetArgumentByteBool01Value(const char* pCmd, const ARGUMENT_SET* pArg, unsigned char* pValue)
{
	bool val = false;
	enum ARGUMENT_AVAIL rtn = GetArgumentBoolValue(pCmd, pArg, &val);
	*pValue = val ? '\0' : '\1';
	return rtn;
}

enum ARGUMENT_AVAIL GetArgumentByteBool01ValueWithSetFlag(const char* pCmd, const ARGUMENT_SET* pArg, unsigned char* pValue, bool* pSet)
{
	enum ARGUMENT_AVAIL rtn = GetArgumentByteBool01Value(pCmd, pArg, pValue);
	*pSet = rtn == eFound;
	return rtn;
}

enum ARGUMENT_AVAIL GetMappedStrValue(const char* valueStr, StrIntValMap* pMap, size_t mapSize, uint8_t* pValue)
{
	for (size_t i = 0; i < mapSize; i++)
	{
		if (strcmp(valueStr, pMap[i].str) == 0)
		{
			*pValue = pMap[i].val;
			return eFound;
		}
	}

	return eValueNotFound;
}

enum ARGUMENT_AVAIL GetArgumentMappedStrValue(const char* pCmd, const ARGUMENT_SET* pArg, StrIntValMap* pMap, size_t mapSize, uint8_t* pValue)
{
	const char* valueStr = NULL;
	enum ARGUMENT_AVAIL rtn = GetArgumentStrValue(pCmd, pArg, &valueStr);

	if (rtn != eFound)
		return rtn;

	rtn = GetMappedStrValue(valueStr, pMap, mapSize, pValue);
	if (rtn == eValueNotFound)
	{
		SockLog(eLOG_ERROR, "Error: invalid %s. Supported options are ", GetShortArgumentDesc(pArg));

		// Assuming mapSize > 1
		for (size_t i = 0; i < mapSize; i++)
			SockLog(eLOG_ERROR, i == 0 ? "%s" : (i < mapSize - 1 ? ", %s" : ", and %s\n"), pMap[i].str);
	}

	return rtn;
}

enum ARGUMENT_AVAIL GetArgumentMappedStrUint32Value(const char* pCmd, const ARGUMENT_SET* pArg, StrIntValMap* pMap, size_t mapSize, uint32_t* pValue)
{
	uint8_t val;
	enum ARGUMENT_AVAIL rtn = GetArgumentMappedStrValue(pCmd, pArg, pMap, mapSize, &val);
	*pValue = val;
	return rtn;
}

enum ARGUMENT_AVAIL GetArgumentInt64Value(const char* pCmd, const ARGUMENT_SET* pArg, uint64_t* pValue)
{
	ARGUMENT_SET arg = *pArg;
	arg.type = eDEPENDS;

	const char* valueStr = NULL;
	enum ARGUMENT_AVAIL rtn = GetArgumentStrValue(pCmd, &arg, &valueStr);

	if (rtn == eFound)
	{
		char* pEnd;
		*pValue = strtoll(valueStr, &pEnd, 10);
		if (*pEnd != '\0')
		{
			SockLog(eLOG_INFO, "Error: %s number could not be converted to an uint64_t value\n", GetShortArgumentDesc(pArg));
			rtn = eValueNotFound;
		}
	}

	if (rtn != eFound && pArg->type == eMANDATORY)
		SockLog(eLOG_INFO, "Error: %s number must be specified after -%s or --%s flag\n",
			GetShortArgumentDesc(pArg), pArg->arg_short, pArg->arg);

	return rtn;
}

enum ARGUMENT_AVAIL GetArgumentInt16Value(const char* pCmd, const ARGUMENT_SET* pArg, uint16_t* pValue)
{
	unsigned int val = 0;
	enum ARGUMENT_AVAIL rtn = GetArgumentIntValue(pCmd, pArg, &val);
	*pValue = (uint16_t)val;
	return rtn;
}

enum ARGUMENT_AVAIL GetArgumentInt8ArrayValue(const char* pCmd, const ARGUMENT_SET* pArg, char cSeperator, uint16_t* pLen, uint8_t* pValues, size_t sizeValues)
{
	if (pLen == NULL || pValues == NULL)
		return eValueNotFound;

	const char* valueStr = NULL;
	enum ARGUMENT_AVAIL rtn = GetArgumentStrValue(pCmd, pArg, &valueStr);

	if (rtn != eFound)
		return rtn;

	uint16_t i = 0;

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

	*pLen = i;

	return i > 0 ? rtn : eValueNotFound;
}

enum ARGUMENT_AVAIL GetArgumentIpValueInternal(bool bIPv6, const char* pCmd, const ARGUMENT_SET* pArg, uint8_t* pValue, size_t size)
{
	if (pValue == NULL)
	{
		SockLog(eLOG_INFO, "Error: IPv%d buffer not provided\n", bIPv6 ? 6 : 4);
		return eFlagNotFound;
	}

	if ((bIPv6 && size < 16) || (!bIPv6 && size < sizeof(uint32_t)))
	{
		SockLog(eLOG_INFO, "Error: IPv%d buffer too small\n", bIPv6 ? 6 : 4);
		return eFlagNotFound;
	}

	ARGUMENT_SET arg = *pArg;
	arg.type = eDEPENDS;

	const char* valueStr = NULL;
	enum ARGUMENT_AVAIL rtn = GetArgumentStrValue(pCmd, &arg, &valueStr);

	if (rtn == eFound)
	{
		/* Convert the IP address from string to binary */
		if (inet_pton(bIPv6 ? AF_INET6 : AF_INET, valueStr, pValue) != 1)
		{
			SockLog(eLOG_INFO, "Failed to convert -%s parameter to binary format\n", pArg->arg);
			rtn = eValueNotFound;
		}
	}

	if (rtn != eFound && pArg->type == eMANDATORY)
		SockLog(eLOG_INFO, "Error: %s must be specified\n", pArg->desc_short ? pArg->desc_short : pArg->arg);

	return rtn;
}

enum ARGUMENT_AVAIL GetArgumentIpValue(const char* pCmd, const ARGUMENT_SET* pArg, uint32_t* pValue)
{
	return GetArgumentIpValueInternal(false, pCmd, pArg, (uint8_t*)pValue, sizeof(uint32_t));
}

enum ARGUMENT_AVAIL GetArgumentIpv6Value(const char* pCmd, const ARGUMENT_SET* pArg, uint8_t* pValue, size_t size)
{
	return GetArgumentIpValueInternal(true, pCmd, pArg, pValue, size);
}

int Command2Option(const COMMAND_SET* cmdset, size_t size_cmdset, const char* command, int nInvalidCmd)
{
	for (size_t i = 0; i < size_cmdset; i++)
	{
		if (strcmp(command, cmdset[i].cmd) == 0)
			return cmdset[i].opt;
	}

	return nInvalidCmd;
}

// Internal function
int GetCmdFromSet(const COMMAND_SET* cmdset, size_t size_cmdset, char** command, int nInvalidCmd)
{
	if (command)
		*command = NULL;

	char* cmd = strtok(message, " ");
	if (cmd == NULL)
		return nInvalidCmd;
		
	size_t cmdlen = strlen(cmd);
	if (cmdlen > 0 && cmd[cmdlen - 1] == '\n')
	{
		cmd[cmdlen - 1] = '\0';
	}

	for (argc = 0; argc < MAX_ARGV; argc++)
	{
		argv[argc] = strtok(NULL, " ");
		if (argv[argc] == NULL)
			break;
	}

	if (argc > 0 && strlen(argv[argc - 1]) != 0 && argv[argc - 1][strlen(argv[argc - 1]) - 1] == '\n')
		argv[argc - 1][strlen(argv[argc - 1]) - 1] = '\0';

	if (command)
		*command = cmd;

	return Command2Option(cmdset, size_cmdset, cmd, nInvalidCmd);
}

int OpenSocket(const char* socket_name)
{
	if (socket_name == NULL || strlen(socket_name) == 0)
	{
		SockLog(eLOG_ERROR, "OpenSocket: Missing socket name\n");
		return g_mainSocketFd;
	}

	if (g_mainSocketFd != 0)
	{
		SockLog(strcmp(socket_name, g_socketName) == 0 ? eLOG_INFO : eLOG_ERROR, "Socket %s is already open\n", g_socketName);
		return g_mainSocketFd;
	}

	if (pthread_mutex_init(&socketWriteLock, NULL) != 0)
	{
		SockLog(eLOG_ERROR, "OpenSocket: Failed to initialize socket write mutex\n");
		return g_mainSocketFd;
	}

	g_socketName[0] = 0;

#ifdef FAKE_SOCKET
	SockLog(eLOG_INFO, "Fake socket: %s\n", socket_name);
	g_mainSocketFd = -1;
#else
	//establish a socket to recieve further commands
	struct sockaddr_un serverInfo;
	g_mainSocketFd = socket(PF_LOCAL, SOCK_STREAM, 0);

	if (g_mainSocketFd)
	{
		serverInfo.sun_family = AF_LOCAL;
		StrCpy(serverInfo.sun_path, socket_name);
		bind(g_mainSocketFd, (struct sockaddr*)&serverInfo, SUN_LEN(&serverInfo));

		if (listen(g_mainSocketFd, 5) != 0)
		{
			SockLog(eLOG_ERROR, "Failed to listen: %s\n", strerror(errno));
			close(g_mainSocketFd);
			g_mainSocketFd = 0;
		}
	}
#endif

	if (g_mainSocketFd)
	{
		StrCpy(g_socketName, socket_name);
		SockLog(eLOG_INFO, "Socket opened. Issue socket command from another terminal in the format as:\n  echo <command> | sudo nc -U %s\n", g_socketName);
	}
	else
		unlink(socket_name);

	return g_mainSocketFd;
}

void CloseSocket()
{
	if (g_clientSocketFd)
	{
		close(g_clientSocketFd);
		g_clientSocketFd = 0;
	}

	if (g_mainSocketFd)
	{
#ifndef FAKE_SOCKET
		close(g_mainSocketFd);
#endif
		g_mainSocketFd = 0;
	}

	unlink(g_socketName);
	g_socketName[0] = 0;

	pthread_mutex_destroy(&socketWriteLock);
}

void SockPrintf(const char* const fmt, ...)
{
	va_list arg;
	va_start(arg, fmt);
	if (g_clientSocketFd == 0)
		vprintf(fmt, arg);
	else
		vdprintf(g_clientSocketFd, fmt, arg);
	va_end(arg);
}

void SockLog(int lvl, const char* const fmt, ...)
{
	char buff[255];
	va_list arg;

	va_start(arg, fmt);
	vsnprintf(buff, 254, fmt, arg);
	va_end(arg);

	wl(lvl, buff);

	if (g_mainSocketFd == 0 || g_mainSocketFd == -1)
		return;

	va_start(arg, fmt);
	vdprintf(g_mainSocketFd, fmt, arg);
	va_end(arg);
}

int GetSocketCommand(const COMMAND_SET* cmdset, size_t size_cmdset, char** command, int nInvalidCmd)
{
	if (g_mainSocketFd == 0)
		return nInvalidCmd;

#ifdef FAKE_SOCKET
	GetStringFromUser(NULL, "Enter command string", g_enterActionLeaveEmpty, message, sizeof(message));
#else
	struct sockaddr_un clientInfo;
	socklen_t clientInfoLength;

	if (g_clientSocketFd != 0)
		close(g_clientSocketFd);

	g_clientSocketFd = accept(g_mainSocketFd, (struct sockaddr*)&clientInfo, &clientInfoLength);

	const int POLL_TIMEOUT_MS = 500;

	char* buffer = message;
	size_t size = sizeof(message);
	memset(buffer, 0, size);
	size--;	// Leave room for NULL terminator

	struct pollfd socketPollInfo;
	socketPollInfo.fd = g_clientSocketFd;
	socketPollInfo.events = POLLIN;

	while (poll(&socketPollInfo, 1, POLL_TIMEOUT_MS) > 0)
	{
		if (size <= 0)
		{
			SockLog(eLOG_INFO, "Error: recieved message is too long\n");
			return nInvalidCmd;
		}

		int bytesRead = 0;

		do
		{
			bytesRead = read(g_clientSocketFd, buffer, size);
		} while (bytesRead == -1 && (errno == EAGAIN || errno == EINTR));

		if (bytesRead == 0)
			break;

		if (bytesRead < 0)
		{
			SockLog(eLOG_INFO, "Error: reading from socket error %d - %s\n", errno, strerror(errno));
			return nInvalidCmd;
		}

		buffer += bytesRead;
		size -= bytesRead;
	}
#endif

	printf("Process socket message: \"%s\"\n", message);

	return GetCmdFromSet(cmdset, size_cmdset, command, nInvalidCmd);
}
