#include <stdlib.h>
#include <string.h>
#include "str_util.h"
#include "dev_util.h"

// This function resolves usb device path on a given location.
// The usb device path is something like "/dev/cdc-wdm0".
bool locate_usb_adapter_path(usb_dev_loc_info* pusb_dev_loc, char* dev_path, int dev_path_size)
{
	char cmd[128] = "";

	if (pusb_dev_loc->hub_num == 0)
		snprintf(cmd, 128, "ls /sys/bus/usb/devices/%d-%d:%d.%d/usbmisc 2>&1",
			pusb_dev_loc->bus_num, pusb_dev_loc->port_num,
			pusb_dev_loc->dev_num, pusb_dev_loc->if_adapter);
	else if (pusb_dev_loc->subhub_num == 0)
		snprintf(cmd, 128, "ls /sys/bus/usb/devices/%d-%d.%d:%d.%d/usbmisc 2>&1",
			pusb_dev_loc->bus_num, pusb_dev_loc->hub_num, pusb_dev_loc->port_num,
			pusb_dev_loc->dev_num, pusb_dev_loc->if_adapter);
	else
	{
		snprintf(cmd, 128, "ls /sys/bus/usb/devices/%d-%d.%d.%d:%d.%d/usbmisc 2>&1",
			pusb_dev_loc->bus_num, pusb_dev_loc->hub_num, pusb_dev_loc->subhub_num,
			pusb_dev_loc->port_num, pusb_dev_loc->dev_num, pusb_dev_loc->if_adapter);
	}

	FILE* fp = popen(cmd, "r");
	if (!fp)
		return false;

	char resp[32] = "";
	bool ret = fgets(resp, 32, fp) && strstr(resp, "cdc");
	pclose(fp);

	if (!ret)
		return false;

	size_t len = strlen(resp);
	if (len > 0 && resp[len - 1] == '\n')
		resp[len - 1] = 0;

	if (strlen(dev_path) == 0)
	{
		// Path is not provided.  Return the first path found
		snprintf(dev_path, dev_path_size, "/dev/%s", resp);
		dev_path[dev_path_size - 1] = '\0';
		return true;
	}

	// Path is provided and match the driver name. Return true.
	return strstr(dev_path, resp) != NULL;
}

bool locate_usb_dev_bus_dev_num(usb_dev_loc_info** pusb_dev_loc, int* size)
{
	FILE * fp = popen("lsusb -d 1199:", "r");
	if (!fp)
		return false;

	char resp[SH_RESP_BUF_LEN] = "";
	int idx = 0;

	while (fgets(resp, SH_RESP_BUF_LEN, fp) && idx < *size)
	{
		int bus, dev;
		if (sscanf(resp, "Bus %d Device %d ID %*s %*s", &bus, &dev) == 2)
		{
			pusb_dev_loc[idx] = calloc(1, sizeof(usb_dev_loc_info));
			if (pusb_dev_loc[idx] == NULL)
				break;

			pusb_dev_loc[idx]->bus_num = bus;
			pusb_dev_loc[idx]->bus_dev = dev;

			idx++;
		}
	}

	pclose(fp);

	*size = idx;

	return idx > 0;
}

bool locate_usb_qdl(usb_dev_loc_info * pusb_dev_loc)
{
	if (pusb_dev_loc->bus_num == 0)
		return false;

	FILE * fp = popen("lsusb -t", "r");
	if (!fp)
		return false;

	char resp[SH_RESP_BUF_LEN] = "";
	bool found_bus = false;
	bool found_port = false;

	while (fgets(resp, SH_RESP_BUF_LEN, fp))
	{
		if (strstr(resp, "Class=root_hub"))
		{
			int bus_num = 0;
			if (sscanf(resp, "/:  Bus %d.Port %*s Dev %d, %*s %*s %*s", &bus_num, &pusb_dev_loc->dev_num) == 2 &&
				bus_num == pusb_dev_loc->bus_num)
			{
				pusb_dev_loc->hub_num = 0;
				found_bus = true;
			}

			continue;
		}

		if (!found_bus)
			continue;

		if (strstr(resp, "Class=Hub, Driver=hub") ||
			strstr(resp, "Class=, Driver=hub"))
		{
			if (strncmp(resp, "        |__ ", 12) == 0)
			{
				sscanf(resp, "%*s Port %d: %*s", &pusb_dev_loc->subhub_num);
			}
			else if (strncmp(resp, "    |__ ", 8) == 0)
			{
				sscanf(resp, "%*s Port %d: %*s", &pusb_dev_loc->hub_num);
			}
			continue;
		}

		found_port = strstr(resp, "Driver=qcserial") &&
			sscanf(resp, "%*s Port %d: Dev %*s If %d, %*s", &pusb_dev_loc->port_num, &pusb_dev_loc->if_qdl) == 2;

		if (found_port)
		{
			if (strncmp(resp, "            ", 12) != 0)
				pusb_dev_loc->subhub_num = 0;	// In case what we found here is not under a subhub node
			
			if (strncmp(resp, "        ", 8) != 0)
				pusb_dev_loc->hub_num = 0;	// In case what we found here is not under a hub node

			break;
		}
	}

	pclose(fp);

	return found_port;
}

// This function serves the following purposes.
// 1. In a multi-up scenario, it finds the device in the matching location passed in pusb_dev_loc.
//    User specified "-P a-b.c" option, and find_match is true.
// 2. In a single-up scenario, it finds the device detailed location (hub number, port number etc)
//    User does not specify "-P" option. find_match is false.
// 3. After locating the device, determine the device mode (MBIM or QMI) by looking at which driver it uses
// 4. Locate USB device adapter interface number
bool locate_usb_adapter(usb_dev_loc_info* pusb_dev_loc, int* pmode, bool find_match)
{
	if (pusb_dev_loc->bus_num == 0)
		return false;

	usb_dev_loc_info cached_dev_loc;
	if (find_match)
	{
		// Cache the USB device location info, if we need to find a matching USB device.
		memcpy(&cached_dev_loc, pusb_dev_loc, sizeof(usb_dev_loc_info));
	}

	FILE * fp = popen("lsusb -t", "r");
	if (!fp)
		return false;

	char resp[SH_RESP_BUF_LEN] = "";
	bool found_bus = false;
	bool found_port = false;

	int bus_found = 0;
	int hub_found = 0;
	int subhub_found = 0;
	int port_found = 0;

	while (fgets(resp, SH_RESP_BUF_LEN, fp))
	{
		if (strstr(resp, "Class=root_hub"))
		{
			if (found_bus)
				break;

			int bus_num = 0;
			if (sscanf(resp, "/:  Bus %d.Port %*s Dev %d, %*s %*s %*s", &bus_num, &pusb_dev_loc->dev_num) == 2 &&
				bus_num == pusb_dev_loc->bus_num)
			{
				pusb_dev_loc->hub_num = 0;
				found_bus = true;
			}

			continue;
		}

		if (!found_bus)
			continue;

		if (strstr(resp, "Class=Hub, Driver=hub") ||
			strstr(resp, "Class=, Driver=hub"))
		{
			if (strncmp(resp, "        |__ ", 12) == 0)
			{
				sscanf(resp, "%*s Port %d: %*s", &pusb_dev_loc->subhub_num);
			}
			else if (strncmp(resp, "    |__ ", 8) == 0)
			{
				sscanf(resp, "%*s Port %d: %*s", &pusb_dev_loc->hub_num);
			}
			continue;
		}

		int port_num = 0, bus_dev = 0, if_adapter = 0;
		found_port = 
			(((*pmode == QMUX_INTERFACE_UNKNOWN || *pmode == QMUX_INTERFACE_DIRECT) &&
			  strstr(resp, "Driver=qmi_wwan")) ||
			((*pmode == QMUX_INTERFACE_UNKNOWN || *pmode == QMUX_INTERFACE_MBIM) &&
			  strstr(resp, "Class=Communications, Driver=cdc_mbim"))) &&
			sscanf(resp, "%*s Port %d: Dev %d, If %d, %*s", &port_num, &bus_dev, &if_adapter) == 3 &&
			bus_dev == pusb_dev_loc->bus_dev;

		if (found_port)
		{
			pusb_dev_loc->port_num = port_num;
			pusb_dev_loc->if_adapter = if_adapter;

			if (strncmp(resp, "            ", 12) != 0)
				pusb_dev_loc->subhub_num = 0;	// In case what we found here is not under a subhub node
			
			if (strncmp(resp, "        ", 8) != 0)
				pusb_dev_loc->hub_num = 0;	// In case what we found here is not under a hub node

			*pmode =
				strstr(resp, "Driver=qmi_wwan") ? QMUX_INTERFACE_DIRECT :
				strstr(resp, "Driver=cdc_mbim") ? QMUX_INTERFACE_MBIM : QMUX_INTERFACE_UNKNOWN;

			if (!find_match)
			{
				// If we do not need to find a matching device, we just find one. So, we are done here.
				//break;
				break;
			}
			else
			{
				// Check if the found one is the one we are searching for
				if (pusb_dev_loc->bus_num == cached_dev_loc.bus_num &&
					pusb_dev_loc->hub_num == cached_dev_loc.hub_num &&
					pusb_dev_loc->subhub_num == cached_dev_loc.subhub_num &&
					pusb_dev_loc->port_num == cached_dev_loc.port_num)
				{
					// We have found the matching device.  We are done here.
					break;
				}
				else
				{
					// We have not found the matching device, continue searching.
					found_port = false;
					bus_found = pusb_dev_loc->bus_num;
					hub_found = pusb_dev_loc->hub_num;
					subhub_found = pusb_dev_loc->subhub_num;
					port_found = pusb_dev_loc->port_num;
				}
			}
		}
	}

	pclose(fp);

	if (!found_port)
	{
		pusb_dev_loc->bus_num = bus_found;
		pusb_dev_loc->hub_num =	hub_found;
		pusb_dev_loc->subhub_num = subhub_found;
		pusb_dev_loc->port_num = port_found;
	}
	
	return found_port;
}

//
// Find USB device
//
// 1. lsusb -d 1199:
// 2.; extract bus_num and id in format "Bus <bus_num> Device sss ID <id> sss"
// 3. lsusb -t
// 4.; find line with "Class=root_hub", and bus_num in "/:  Bus <bus_num>.Port sss Dev <dev_id>, sss" is the same as that found in previous step
// 5.; if "Class=Hub, Driver=hub" is found, extract hub_num from "sss, Port <hum_num>: sss"
// 6.; find following line with "Class=Communications, Driver=cdc_mbim" or "Driver=qmi_wwan"
// 7.; extract port_num and if_adapter from format "sss Port <port_num>: Dev sss If <if_adapter>, sss"
// 8.; determine if the device found is under USB Hub
// 9.; device mode is QMI if "Driver=qmi_wwan", MBIM if "Driver=cdc_mbim"
// 10.; if under USB Hub, "ls /sys/bus/usb/devices/<bus_num>-<hub_num>.<subhub_num>.<port_num>:<dev_num>.<if_adapter>/usbmisc"
//      otherwiese "ls /sys/bus/usb/devices/<bus_num>-<port_num>:<dev_num>.<if_adapter>/usbmisc"
// 11.; the device name is found in the output of step 11 that starts with "cdc"

bool find_usb_adapter_path(char* dev_path, int dev_path_size, int* pmode, int* pif_adapter)
{
#define MAX_DEV 4

	usb_dev_loc_info* usb_dev_loc[MAX_DEV] = {NULL, NULL, NULL, NULL};

	bool found = false;

	int num_devs = MAX_DEV;
	locate_usb_dev_bus_dev_num(usb_dev_loc, &num_devs);

	for (int i = 0; i < num_devs; i++)
	{
		if (!found &&
			locate_usb_adapter(usb_dev_loc[i], pmode, false) &&
			// If device path is provided, do not get the path but need to get interface id
			locate_usb_adapter_path(usb_dev_loc[i], dev_path, dev_path_size))
		{
			if (pif_adapter)
				*pif_adapter = usb_dev_loc[i]->if_adapter;

			found = true;
		}

		free(usb_dev_loc[i]);
	}

	return found;
}

bool locate_pcie_dev(pcie_dev_loc_info* ppcie_dev_loc)
{
	FILE * fp = popen("lspci -v 2>&1", "r");
	if (!fp)
		return false;

	bool found = false;
	bool found_qc = false;

	char resp[SH_RESP_BUF_LEN] = "";
	while (!found && fgets(resp, SH_RESP_BUF_LEN, fp))
	{
		if (strstr(resp, "Qualcomm Device 03"))
		{
			if (sscanf(resp, "%d:%d.%*d Unassigned class %*s Qualcomm Device %d",
				&ppcie_dev_loc->bus_num, &ppcie_dev_loc->slot_num, &ppcie_dev_loc->model_num) == 3)
				found_qc = true;
		}
		else
			found = found_qc && strstr(resp, "Subsystem: Device 18d7");
	}

	pclose(fp);

	return found;
}

//
// Find PCIe device
//
// 1. lspci - v
// 2.; find line with "Qualcomm Device 030"
// 3.; extract bus_num, slot_num and model_num in format "<bus_num>:<slot_num>.x sss Qualcomm Device <model_num>"
// 4.; find line with "Subsystem: Device 18d7" to confirm PCIe device found
// 5. ls / dev / mhi *
// 6.; find mbim device in the format of "mhi_<model_num:4>_<domain_num:2>.<bus_num:2>.<slot_num:2>_pipe_12
// 7.; find qmi device in the format of "mhi_<model_num:4>_<domain_num:2>.<bus_num:2>.<slot_num:2>_pipe_14

bool find_pcie_dev(char* dev_path, int dev_path_size, int* pmode, char * qdl_path, int qdl_path_size)
{
	pcie_dev_loc_info pcie_dev_loc;
	memset(&pcie_dev_loc, 0, sizeof(pcie_dev_loc_info));

	if (!locate_pcie_dev(&pcie_dev_loc))
		return false;

	FILE* fp = popen("ls /dev/mhi* 2>&1", "r");
	if (!fp)
		return false;

	char path_mbim[64] = "";
	snprintf(path_mbim, sizeof(path_mbim), "/dev/mhi_%04d_%02d.%02d.%02d_pipe_12", pcie_dev_loc.model_num, 
		pcie_dev_loc.domain_num, pcie_dev_loc.bus_num, pcie_dev_loc.slot_num);
	char path_qmi[64] = "";
	snprintf(path_qmi, sizeof(path_qmi), "/dev/mhi_%04d_%02d.%02d.%02d_pipe_14", pcie_dev_loc.model_num,
		pcie_dev_loc.domain_num, pcie_dev_loc.bus_num, pcie_dev_loc.slot_num);
	char path_qdl[] = "/dev/mhiqdl0";

	bool found = false;
	char resp[SH_RESP_BUF_LEN] = "";

	while (!found && fgets(resp, SH_RESP_BUF_LEN, fp))
	{
		if ((*pmode == QMUX_INTERFACE_UNKNOWN || *pmode == QMUX_INTERFACE_DIRECT) && strstr(resp, path_qmi))
		{
			strcpy_s(dev_path, dev_path_size, path_qmi);
			*pmode = QMUX_INTERFACE_DIRECT;
			if (qdl_path)
			{
				strcpy_s(qdl_path, qdl_path_size, path_qdl);
			}
			found = true;
		}
		else if ((*pmode == QMUX_INTERFACE_UNKNOWN || *pmode == QMUX_INTERFACE_MBIM) && strstr(resp, path_mbim))
		{
			strcpy_s(dev_path, dev_path_size, path_mbim);
			*pmode = QMUX_INTERFACE_MBIM;
			if (qdl_path)
			{
				strcpy_s(qdl_path, qdl_path_size, path_qdl);
			}
			found = true;
		}
		else if (strstr(resp, path_qdl))
		{
			if (qdl_path)
			{
				strcpy_s(qdl_path, qdl_path_size, path_qdl);
			}

			if (*pmode == QMUX_INTERFACE_UNKNOWN || *pmode == QMUX_INTERFACE_MBIM)
			{
				strcpy_s(dev_path, dev_path_size, path_mbim);
				*pmode = QMUX_INTERFACE_MBIM;
			}
			else if (*pmode == QMUX_INTERFACE_DIRECT)
			{
				strcpy_s(dev_path, dev_path_size, path_qmi);
				*pmode = QMUX_INTERFACE_DIRECT;
			}
			found = true;
		}
	}

	pclose(fp);

	return found;
}

const char* GetModeDesc(int mode)
{
	switch (mode)
	{
	case QMUX_INTERFACE_DIRECT:
		return "QMI";
	case QMUX_INTERFACE_MBIM:
		return "MBIM";
	case QMUX_INTERFACE_ROUTER:
		return "router";
	// case QMUX_INTERFACE_UNKNOWN:
	default:
		return "unknown";
	}
}

int InitDevMode(const char* dev_path, bool* ppcie)
{
	if (dev_path == NULL)
		return QMUX_INTERFACE_UNKNOWN;;

	const char* dev_name = strrchr(dev_path, '/');

	if (dev_name == NULL)
		return QMUX_INTERFACE_UNKNOWN;
	
	int mode = QMUX_INTERFACE_UNKNOWN;

	dev_name++;

	*ppcie = strstr(dev_name, "mhi");
	if (*ppcie)
	{
		// PCIe
		if (strstr(dev_name, "_12"))
			mode = QMUX_INTERFACE_MBIM;
		else if (strstr(dev_name, "_14"))
			mode = QMUX_INTERFACE_DIRECT;
	}
	else
	{
		// USB
		char cmd_part1[] = "udevadm info -x -a -p $(find /sys/bus/usb/devices/usb*/ -name ";
		char cmd[MAX_PATH_LEN] = "";
		snprintf(cmd, MAX_PATH_LEN, "%s%s) | grep DRIVERS", cmd_part1, dev_name);

		FILE * fp = popen(cmd, "r");
		if (fp)
		{
			char resp[128] = "";

			while (mode == QMUX_INTERFACE_UNKNOWN && fgets(resp, 128, fp))
			{
				if (strstr(resp, "cdc_mbim"))
					mode = QMUX_INTERFACE_MBIM;
				else if (strstr(resp, "qmi_wwan"))
					mode = QMUX_INTERFACE_DIRECT;
			}

			pclose(fp);
		}
	}

	return mode;
}

#ifndef ANDROID_LOGGING

bool InitDevPaths(char* dev_path, int dev_path_size, int* pmode, bool* ppcie, int* pif_adapter)
{
	// Return true if only one device is found
	if (dev_path == NULL || dev_path_size == 0 || pmode == NULL || ppcie == NULL)
		return false;

	bool bPathProvided = strlen(dev_path) > 0;	// If device path is provided, we already know if it's PCIe

	int pcie_mode = *pmode;
	int usb_mode = *pmode;
	bool pcie = bPathProvided ? *ppcie : find_pcie_dev(dev_path, dev_path_size, &pcie_mode, NULL, 0);
	bool usb = bPathProvided && *ppcie ? false : find_usb_adapter_path(dev_path, dev_path_size, &usb_mode, pif_adapter);

	if (pcie && usb && !bPathProvided)
	{
		printf("\nBoth PCIe and USB devices are found. Unable to determine the device to use.\n\n");
		return false;
	}

	if (!pcie && !usb && !bPathProvided)
	{
		printf("\nNeither PCIe nor USB device can be identified.\n\n");
		return false;
	}

	if (*pmode != QMUX_INTERFACE_ROUTER)
		*pmode = pcie ? pcie_mode : usb_mode;

	*ppcie = pcie;

	return true;
}

bool GetDeviceInfo(char* dev_path, size_t dev_path_size, int* pmode, bool* ppcie, int* pif_adapter,
	bool valid, FNSHOWHELP pfnsh, const char* pProcName, bool showhelp)
{
	if (dev_path == NULL || pmode == NULL || ppcie == NULL || strlen(dev_path) >= dev_path_size)
		return false;

	valid = valid &&
		(dev_path[0] == 0 /* empty path */ ||
		(*pmode != QMUX_INTERFACE_ROUTER && strstr(dev_path, "/dev/") == dev_path && strstr(dev_path, " ") == NULL));

	if (valid)
	{
		if (strlen(dev_path) > 0)
		{
			// If device path is provided, need to determine if it is PCIe and get the device mode
			int mode = InitDevMode(dev_path, ppcie);
			if (*pmode == QMUX_INTERFACE_UNKNOWN)
				*pmode = mode;
		}

		valid = InitDevPaths(dev_path, dev_path_size, pmode, ppcie, pif_adapter);

		if (valid && *pmode == QMUX_INTERFACE_UNKNOWN)
		{
			printf("\nUnable to identify mode of device %s\n\n", dev_path);
			valid = false;
		}
	}

	if ((!valid || showhelp) && pfnsh)
	{
		pfnsh(pProcName);

		if (!valid)
			return false;
	}

	if (*ppcie && pif_adapter)
		*pif_adapter = 4;	// For PCIe interface adapter needs to be 4

	return true;
}

#else	// #ifndef ANDROID_LOGGING

bool locate_android_usb_dev_bus_num(int* pbus_num)
{
	FILE * fp = popen("lsusb", "r");
	if (!fp)
		return false;

	char resp[SH_RESP_BUF_LEN] = "";
	bool found = false;

	while (!found && fgets(resp, SH_RESP_BUF_LEN, fp))
	{
		int vid_num = 0;
		if (sscanf(resp, "Bus %d Device %*s ID %d:%*s", pbus_num, &vid_num) == 2 && vid_num == 1199)
			found = true;
	}

	pclose(fp);

	return found;
}

bool locate_android_usb_dev_interface(int bus_num, int* plev, int* pport, int* pcfg, int* pif_adapter, int* pmode)
{
	FILE * fp = fopen("/sys/kernel/debug/usb/devices", "r");
	if (!fp)
		return false;

	char resp[SH_RESP_BUF_LEN] = "";
	bool found = false;
	bool foundT = false;
	bool foundC = false;

	while (!found && fgets(resp, SH_RESP_BUF_LEN, fp))
	{
		int bus = 0;
		int lev = 0;
		int port = 0;
		int cfg = 0;

		if (sscanf(resp, "T:  Bus=%d Lev=%d %*s Port=%d %*s", &bus, &lev, &port) == 3)
		{
			foundT = bus == bus_num;
			if (foundT)
			{
				*plev = lev;
				*pport = port;
			}
			else
				foundC = false;
		}
		else if (sscanf(resp, "C:* #Ifs= %*s Cfg#= %d %*s", &cfg) == 1 && foundT)
		{
			foundC = true;
			*pcfg = cfg;
		}
		else if (strstr(resp, " Cls=02(comm.) ") && strstr(resp, " Driver=cdc_mbim"))
		{
			if (pmode)
				*pmode = QMUX_INTERFACE_MBIM;
			found = sscanf(resp, "I:* If#= %d %*s", pif_adapter) == 1 && foundT && foundC;
		}
		else if (strstr(resp, " Driver=qmi_wwan"))
		{
			if (pmode)
				*pmode = QMUX_INTERFACE_DIRECT;
			found = sscanf(resp, "I:* If#= %d %*s", pif_adapter) == 1 && foundT && foundC;
		}
	}

	pclose(fp);

	return found;
}

//
// Find Android SWI USB device
//
// 1. lsusb
// 2.; extract Bus and ID in format "Bus <bus_num> Device sss: ID <id>"
// 3.; Use the bus_num of id starts with "1199:"
// 4.; Open "/sys/kernel/debug/usb/devices"
// 5.; Find line with "T: Bus=<idx> Lev=<lev> sss Port=<port> sss", where idx == id (in value, not text)
// 6.; Before the next "T:" line, find "C:* #Ifs= sss Cfg#= "<cfg> sss"
// 7.; If the device is in MBIM mode
//     Before the next "T: " or "C:* " line, find "I:* If#= <if_adapter> sss Cls=02(comm.) sss Driver=cdc_mbim"
//     If the device is in RmNet mode
//     Before the next "T: " or "C:* " line, find "I:* If#= <if_adapter> sss Cls=ff(vend.) sss Driver=qmi_wwan"
// 8. if <port> == 0 "ls /sys/bus/usb/devices/<bus_num>-<lev>:<cfg>.<if_adapter>/usbmisc"
//    otherwise "ls /sys/bus/usb/devices/<bus_num>-<port>.<lev>:<cfg>.<if_adapter>/usbmisc"

bool InitDevPaths(char* dev_path, int dev_path_size, int* pmode, bool* ppcie __unused, int* pif_adapter __unused)
{
	if (pmode)
		*pmode = QMUX_INTERFACE_UNKNOWN;

	usb_dev_loc_info usb_dev_loc;
	memset(&usb_dev_loc, 0, sizeof(usb_dev_loc_info));

	return locate_android_usb_dev_bus_num(&usb_dev_loc.bus_num) &&
		locate_android_usb_dev_interface(usb_dev_loc.bus_num, &usb_dev_loc.port_num, &usb_dev_loc.hub_num, &usb_dev_loc.dev_num, &usb_dev_loc.if_adapter, pmode) &&
		locate_usb_adapter_path(&usb_dev_loc, dev_path, dev_path_size);
}

#endif	// #ifndef ANDROID_LOGGING
