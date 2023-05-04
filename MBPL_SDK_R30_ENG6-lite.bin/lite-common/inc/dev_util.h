#ifndef __DEV_UTIL_H__
#define __DEV_UTIL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdbool.h>

#define MAX_PATH_LEN		192

#define SH_RESP_BUF_LEN 	512

#ifndef QMUX_INTERFACE_UNKNOWN
#define QMUX_INTERFACE_UNKNOWN 0xFF
#endif

#ifndef QMUX_INTERFACE_DIRECT
#define QMUX_INTERFACE_DIRECT 0
#endif

#ifndef QMUX_INTERFACE_MBIM
#define QMUX_INTERFACE_MBIM 1
#endif

#ifndef QMUX_INTERFACE_ROUTER
#define QMUX_INTERFACE_ROUTER 2
#endif

/**
 * \ingroup common
 * 
 * USB device location information 
 * 
 * \param   bus_num
 *          - USB device bus number
 * 
 * \param   bus_dev
 *          - USB device bus device number
 * 
 * \param	hub_num
 * 			- USB device hub number
 * 
 * \param	subhub_num
 * 			- USB device subhub number
 * 
 * \param   port_num
 *          - USB device port number
 * 
 * \param   dev_num
 *          - USB device root_hub device number 
 * 
 * \param   if_adapter
 *          - USB device adapter interface number
 * 
 * \param   if_qdl
 *          - USB device QDL port interface number
 */
typedef struct _usb_dev_loc_info
{
	int bus_num;
	int bus_dev;
	int hub_num;
	int subhub_num;
	int port_num;
	int dev_num;
	int if_adapter;
	int if_qdl;
} usb_dev_loc_info;

/**
 * \ingroup common
 * 
 * PCIe device location information 
 * 
 * \param   domain_num
 *          - PCIe device domain number
 * 
 * \param   bus_num
 *          - PCIe device bus number
 * 
 * \param   slot_num
 *          - PCIe device slot number
 */
typedef struct _pcie_dev_loc_info
{
	int domain_num;
	int bus_num;
	int slot_num;
	int model_num;
} pcie_dev_loc_info;

/**
 * \ingroup	common
 * 
 * Function prototype for showing help menu.
 * 
 * \return none
 */
typedef void(*FNSHOWHELP)(const char*);

/**
 * \ingroup common
 * 
 *  This function retrieves device mode description.
 *
 *  \param[in]  mode
 *              - Device mode value.
 * 				- 0: QMI mode
 * 				- 1: MBIM mode
 * 				- 2: Router mode
 * 				- Others: mode unknown
 *
 *  \return Character string showing the device mode
 */
const char* GetModeDesc(int mode);

/**
 * \ingroup common
 * 
 *  This function initializes the device mode (QMI or MBIM) of the specified device path.
 *
 *  \param[in]  dev_path
 *              - Device path.
 *
 * 	\param[out]	ppcie
 * 				- Pointer to receive if device is PCIe.  If false, it is USB
 *
 *  \return Device mode value
 */
int InitDevMode(const char* dev_path, bool* ppcie);

/**
 * \ingroup common
 * 
 *  This function detects device path and mode.
 *
 *  \param[out] dev_path
 *              - Device path.
 * 
 * 	\param[in]	dev_path_size
 * 				- The size of the dev_path character string
 * 
 * 	\param[i/o]	pmode
 * 				- If pmode is specified as one of the following value, only to find the device path for that type.
 * 				- 0: QMI
 * 				- 1: MBIM
 * 
 * 	\param[out]	ppcie
 * 				- Pointer to receive if device is PCIe.  If false, it is USB
 * 
 * 	\param[out]	pif_adapter
 * 				- Pointer to adapter interface number.  If not NULL, adapter interface ID is returned.
 * 				- This is valid for USB only
 *
 *  \return true for successful, false otherwise.
 */
bool InitDevPaths(char* dev_path, int dev_path_size, int* pmode, bool* ppcie, int* pif_adapter);

/**
 * \ingroup common
 * 
 *  This function locates a PCIe device.
 *
 *  \param[out] dev_path
 *              - Device path.
 * 
 * 	\param[in]	dev_path_size
 * 				- The size of the dev_path character string
 * 
 * 	\param[i/o]	pmode
 * 				- If pmode is specified as one of the following value, only to find the device path for that type.
 * 				- 0: QMI
 * 				- 1: MBIM
 * 
 * 	\param[out]	qdl_path
 * 				- QDL port path
 * 
 *  \param[in]	qdl_path_size
 * 				- The size of the qdl_path character string
 *
 *  \return true for successful, false otherwise.
 */
bool find_pcie_dev(char* dev_path, int dev_path_size, int* pmode, char * qdl_path, int qdl_path_size);

/**
 * \ingroup common
 * 
 *  This function locates the bus numbers and devices number of USB devices.
 *
 *  \param[out] pusb_dev_loc
 *              - Pointer to array of usb_dev_loc_info structure pointers.
 * 				  The usb_dev_loc_info structures are allocated via calloc
 * 				  It is the responsibility of the caller of this function 
 * 				  to call free() on all the pointers allocated
 * 
 *  \param[in/out] size
 *              - Pointer to number of pointers in pusb_dev_loc.
 *                On input, it is the size of usb_dev_loc_info structure pointer in pusb_dev_loc
 *                On output, it is the nuber of usb_dev_loc_info structures allocated
 * 
 *  \return true for successful, false otherwise.
 */
bool locate_usb_dev_bus_dev_num(usb_dev_loc_info** pusb_dev_loc, int* size);

/**
 * \ingroup common
 * 
 *  This function locates a USB adapter, and places the device location info into a 
 *  \ref usb_dev_loc_info structure.
 *
 *  \param[i/o] pusb_dev_loc
 *              - Pointer to a \ref usb_dev_loc_info structure.
 * 				- If the caller wants to find a specific device,  this structure can be used to
 * 				  to hold the device location info (or part of the location info).
 * 
 * 	\param[i/o]	pmode
 * 				- If pmode is specified as one of the following value, only to find the USB device for that type.
 * 				- 0: QMI
 * 				- 1: MBIM
 * 
 *  \param[in]	find_match
 * 				- If pusb_dev_loc contains a valid USB location info, this flag is to indicate
 * 				  to find the adapter matches to that specific location.
 * 
 *  \return true for successful, false otherwise.
 */
bool locate_usb_adapter(usb_dev_loc_info* pusb_dev_loc, int* pmode, bool find_match);

/**
 * \ingroup common
 * 
 *  This function locates a USB QDL port, and places the device location info into a 
 *  \ref usb_dev_loc_info structure.
 *
 *  \param[in]  pusb_dev_loc
 *              - Pointer to a \ref usb_dev_loc_info structure.
 *
 *  \return true for successful, false otherwise.
 */
bool locate_usb_qdl(usb_dev_loc_info * pusb_dev_loc);
 
/**
 * \ingroup common
 * 
 *  This function locates a USB device adapter path.
 *
 *  \param[in]  pusb_dev_loc
 *              - Pointer to a \ref usb_dev_loc_info structure.
 * 
 *  \param[out] dev_path
 *              - Device path.
 * 
 * 	\param[in]	dev_path_size
 * 				- The size of the dev_path character string
 * 
 * \return true for successful, false otherwise.
 */
bool locate_usb_adapter_path(usb_dev_loc_info* pusb_dev_loc, char* dev_path, int dev_path_size);

/**
 * \ingroup common
 * 
 *  This function gets device information.
 *
 *  \param[i/o] dev_path
 *              - Path to Device.  If empty, will be filled.
 * 
 * 	\param[in]	dev_path_size
 * 				- Size of buffer dev_path points to.
 * 
 * 	\param[i/o]	pmode
 * 				- Interface mode, if unknown, will be filled.
 * 
 * 	\param[out]	ppcie
 * 				- Pointer to receive if device is PCIe.  If false, it is USB
 *
 * 	\param[out]	pif_adapter
 * 				- Adapter interface.  Valid for USB only.
 * 
 * 	\param[in]	valid
 * 				- Valid preconditions
 * 
 * 	\param[in]	pfnsh
 * 				- Pointer to ShowHelp function
 * 
 * 	\param[in]	pProcName
 * 				- Process name to be passed to pfhsh
 * 
 * 	\param[in]	showhelp
 * 				- Always show help flag
 * 
 * \return true for successful, false otherwise.
 */
bool GetDeviceInfo(
	char* dev_path,	
	size_t dev_path_size,	
	int* pmode,
	bool* ppcie,
	int* pif_adapter,	
	bool valid,		
	FNSHOWHELP pfnsh,		
	const char* pProcName,	
	bool showhelp);		

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif // __DEV_UTIL_H__

