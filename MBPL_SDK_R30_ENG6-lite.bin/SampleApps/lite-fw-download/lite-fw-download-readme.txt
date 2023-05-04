1. Description
==============

lite-fw-download (the application) is a sample application/utility that uses lite-qmux library to perform firmware downloads for Sierra Wireless Modems based on Qualcomm chipsets.


2. Driver Prerequisites
=======================

The application should only be used with drivers included in MBPL R17 or newer release packages.  It does not work with GobiNet and GobiSerial drivers distributed with legacy SLQS packages.

2.1 PCIe driver
The mhictrl driver should be used for SDX55 based modems in PCIe mode. The device should be recognized as /dev/mhixxx devices which can be listed via command "ls /dev/mhi*".

2.2 USB driver
The following drivers should be used for modems in USB mode: 
- Network Driver: Open Source cdc_mbim driver (for the MBIM interface) or the qmi_wwan driver (included in the MBPL release packages for the RmNet interface)
- Serial Driver: Open Source qcserial driver (included in MBPL release packages)

Please note that GobiNet and GobiSerial drivers (if installed) should be removed or blacklisted from host system before launching the application.  These drivers were distributed with older SLQS releases and are no longer supported.
To blacklist Gobixxx drivers, add the following entries to "/etc/modprobe.d/blacklist-modem.conf" file and restart the Linux platform:

blacklist GobiNet
blacklist GobiSerial


3. Supported Devices
====================
  - Based on SDX62, Ex: EM9290
  - Based on SDX55, Ex: EM9190/EM9191/EM7690, etc.
  - Based on 9X50,  Ex: EM7565/EM7511/EM74X1, etc.
  - Based on 9X30,  Ex: EM7455/EM7430, etc.
  - Based on 9X15,  Ex: EM7355/EM7305, etc.
  - Based on 9X07,  Ex: WP76xx

Modem formfactor (EM/MC/WP/HL) is largely irrelevant for the purpose of this app and FW download feature. The overall functionality from a host perspective is equivalent.

  
4. Build Instructions
=====================

  $cd SampleApps/lite-fw-download/
For x86_64
  $make clean
  $make
For ARM64linaro
  $make clean CPU=arm64linaro
  $make CPU=arm64linaro
For ARM64
  $make clean CPU=arm64
  $make CPU=arm64
For Raspberry Pi ARM
  $make clean CPU=rpi
  $make CPU=rpi

The binaries should be created under the bin folder.


5. Command Options
==================

To list all supported commands:
sudo ./bin/<appName> -h 
Where appName is the CPU specific target binary.

App usage:
  <appName> -f <FW path> -s <File name> -c <QMI/MBIM mode> -d <QDL Port> -p <QMI/MBIM device path> -P <USB device location path> -t <Download type> -w <FW image preference> -n <PRI image preference> -m <device family> -l <Log file path> -x <Image type> -b <block size> -h -F -i -a -r

  -f --fwpath <folder to firmware images>
        (Command is mandatory)
        This specifies the folder location of the firmware images to be downloaded.  
        Example: -f Images

  -s --singlefile <File name>
        (Command is optional)
        This specifies one single file from the firmware folder to be downloaded.
        This option must be used in conjunction with the "-f" option, and only the image filename has to be specified.
        When these options are used, the application searches the file under the firmware folder specified in "-f", and ignores any other firmware.
        Example: -s SWIX55C_01.07.08.00.cwe

  -m --modelfamily <device family>
        (Command is available but no longer needed)
        Can be used to specify the modem chipset family.
        The application automatically detects the modem chipset family if the option is not specified.
        - 1: 9x15 based modems family
        - 3: 9x30 based modems family
        - 4: 9x07, 9x50 or SDX55 modems family
        Example: -m 3
 
  -t --type <Download type>
        (Command is mandatory in non-default scenarios described in other sections below)
        Specifies the FW download type, with or without image switching
        - 1: Single FW image switching type implies the FW image (FW Application) is downloaded and placed by the modem in a predetermined slot/partition. 
        - 2: Non FW Image switching type implies FW image is downloaded in the active partition. Some devices may only have a single partition.
        - 3: Multi FW image switching implies the FW images are downloaded and placed by modem in FW slots.
             This value implies a force download (no explicit -F option required) and needs to be used together with -w/-n combination to indicate the desired image preferences.
        Example: -t 1

  -w --cwe <FW image pref>
        (Command is optional)
        Only required for FW image switching scenarios that require more than 2 FW files
        Specifies the file name of firmware image preference
        -w Command must be used in conjuction with -n Command
        Example: -w SWIX55C_01.07.08.00.cwe -n SWIX55C_01.07.08.00_GENERIC_016.003_000.nvu

  -n --nvu <PRI image pref>
        (Command is optional)
        Only required for FW image switching scenarios that require more than 2 FW files.
        Specifies the file name of carrier PRI image preference.
        - n Command must be used in conjunction with -w Command
        Example: -w SWIX55C_01.07.08.00.cwe -n SWIX55C_01.07.08.00_GENERIC_016.003_000.nvu
       
  -F --force
        (Command is optional)
        Only required for FW image switching scenarios, regardless of the number of FW files
        This Command requests a forced FW download for a FW image switch.

  -l --logfile  
        (Command is optional)
        Specifies the location and the filename of the logfile.  
        By default, the log file is saved as fwdwl.log file in the current folder.
        Example: -l log.txt

  -x --deleteimages <Image type>
       Deletes all device stored images which have the specified image type.
       -0: FW images
       -1: PRI images
       -255: All images
       Example: -x 255
       
  -R --retry <number of device connection retries>
        (Command is optional, should only be used for troubleshooting)
        Specifies number of device connection retries after a FW download is completed.
        The retry interval is 5 seconds.
        The default number of retries is 48. 
        Example: -R 3 (3 retries)

  -P --usbpath <USB device location path>
        (Command is available but not needed for single modem scenarios)  
        Specifies the USB device location in a bus#-port# format.
        When this option is used, both -d and -p options are ignored.
        This command applies only to SDX55/9x50/9x07 based modems USB mode.
        For 9x30 based modems this command only works when modems are connected to a USB2 port.
        Example: -P 2-9 or -P /sys/bus/usb/devices/2-9

  -p --devpath <QMI/MBIM device path>
        (Command is available but no longer needed for single modem scenarios)  
        Specifies the QMI or the MBIM device path.
	Example: 
	- "-p /dev/cdc-wdm0" for a USB modem (either MBIM or RmNet interface)
	- "-p /dev/mhi_0306_00.01.00_pipe_12" for PCIe MBIM interface
	- "-p /dev/mhi_0306_00.01.00_pipe_14" for PCIe QMI interface

  -d --qdl <QDL port>
        (Command is available but no longer needed for single modem scenarios)
        Specifies the QDL port while the modem is in download mode during a FW download.
        Example: "-d /dev/mhiqdl0" for PCIe device or "-d /dev/ttyUSB0" for USB device

  -c --devmode <QMI/MBIM>
        (Command is available but no longer needed)  
        It specifies the host interface mode (MBIM or QMI).
        The application automatically detects the host interface mode if the option is not specified.
        Example: -c QMI

  -b --blocksize
        (Command is optional)
        Should only be used on memory constrained platforms.
        Specifies File Read Block Size in bytes. 
        Example: -b 4096

  -h --help  
        This option prints the usage instructions.

  -v --version
        This option prints the application binary version.

  -i --fileinfo
        This option prints the detailed information of the image files available in the FW images folder.
	The application will exit without performing FW downloads.
        
  -a --autosim
        This option enables device AUTO-SIM based image switches.
        To disable device AUTO-SIM based image switches, initiate an actual external image switch request.

  -r --reset
        Resets device when device is in BOOT AND HOLD mode.
        This option only applies to devices that use Sahara protocol in BOOT AND HOLD mode, including 9x50, 9x07, SDX55 and SDX62/65 based devices.
        When this option is in use, the path to the QDLoader port should be specified via "-d" option.


6. Types of FW Download Operations
==================================
There are 2 distinct types of FW download scenarios. 

6.1 FW Image switching

This FW download type is used when a FW image is needed to be placed into a defined FW slot. In this scenario, the application requests the modem which FW Image and carrier configuration (Carrier PRI) to use (active slot). If the desired FW image and Carrier PRI are already downloaded, the modem simply reboots and switches to the requested configuration. The application only downloads the files that are needed by the modem. Command option "-F" can be used to force a FW download regardless if the modem has the intended FW and carrier PRI. After a successful FW download the modem places the newly downloaded FW image into a predetermined FW slot.

FW Image switching can be performed:
  - Implicitly: One FW image AND one matching carrier PRI located in the folder specified by the "-f" command.
  - Explicitly: By using command option "-t" and the number of FW images to be downloaded is different than 2. When more than 2 FW images are available for download (OEM PRI, multiple Carrier PRIs, and FW Images) then the "-w" AND "-n" commands must be used. 

There are 2 types of image switching as follows.
  - Single FW image switch indicated either implicitly or explicitly by "-t 1"
    This kind of image switch involves only one FW image along with one ore more carrier PRI images.  After the download, that FW image is placed into a FW slot chosen by modem.
  - Multi FW image switch indicated by "-t 3"
    This kind of image switch involves more than one FW images along with multiple carrier PRI images.  Since multiple FW images are downloaded, this option requires the user to explicitly specify the desired image preferences by "-w/-n" option.  After the download, all FW images are placed into FW slots sequentially, starting at slot 0.

Image switching notes:
  - FW Image switching feature relies on the QMI protocol.  The application reports an error if it is unable to establish the QMI communication with the modem.
  - For image switching involves more than one FW image along with multiple carrier PRI images, option "-t 3" should be used.  This ensures that modem places all downloaded FW images into FW slots.
  - Option "-t 1" can be used for image switches that involves ONE FW image and multiple PRI images, e.g., one FW and 3 carrier PRI images, or one FW and one carrier PRI and one OEMPRI images.
  - When downloading multiple carrier PRI images in one image switch session, please ensure there is only one carrier PRI image for one particular carrier.  Multiple carrier images for one same carrier is not supported by the modem.

6.2 Non FW image switching

Non FW image switching FW downloads don't place FW images into FW slots. In these scenarios, the application uses a different QMI object to switch the modem into download mode. If the modem is already in download mode, the application proceeds to download the FW images onto the modem without reporting any errors like image switching scenarios would. Unlike image switching scenarios, the application always downloads all images available in the FW location specified via option "-f" regardless if they are present in the modem or not. Additionally, the modem does NOT place the newly downloaded FW image into its slot (even for modems that support multiple FW slots).

Non FW image switching operations can be performed:
  - Implicitly: If the number of FW images is different than 2. 
  - Explictily: Using "-t 2" command.

Please note that a non FW image switching FW download does not update the modem image preference after a successful FW download. The newly downloaded FW images are not placed into FW slots (even the modem supports multiple slots).  Therefore, if the modem is in Low Power Mode due to a FW image mismatch (after a non image switching FW download), the user should consider using an image switching FW download (with "-t 1" command) to bring the modem out of Low Power Mode.


7. Examples
===========

The app usage has been significantly simplified. Except for the mandatory "-f" command, all other commands are optional. Some notable changes include:

- Command "-c" is now obsolete.  The application searches for the interface (MBIM or QMI).
- For single device scenarios (most typical), the application automatically determines the correct device path.  This applies to both USB and PCIe interfaces. Although this is a recommended approach, the "-p" and "-d" commands are still available and can be used to overwrite the automatic detection method.  
- For USB interfaces, option "-P" is used to specify the location of the USB device. Once specified, the application ignores option "-p" and "-d" (if specified) and search for the device at that particular location.  This "-P" option is typically useful for multiple USB devices scenarios.  This allows the user to specify the USB device location, and stop worrying about the actual device path which could change during a FW download procedure.
- The application now always generates a FW download log called fwdwl.log in the same directory as the application, even when option "-l" is not used.  fwdwl.log is created with overwrite attribute.  That means fwdwl.log only includes logs from the latest FW download session.  If option "-l" is used, the application will save the FW download logs to the file user specified with option "-l".  Unlike the default fwdwl.log, the user specified log file is created with append attribute.
- Option "-m" is to specify device chipset family.  The application will default to "-m 4" if this option is not in use.  This should meet the requirement for most cases as "-m 4" fits for SDX55/9X07/9X50 based devices.  For FW download scenaros for 9X30 or 9X15 devices, an explicit "-m 3" or "-m 1" option respectively is required.
- Option "-w" and "-n" are only needed for image switching FW download scenarios that there are more than 2 images to be downloaded.  For image switching scenarios that there are exact 2 images (one FW image and one matching carrier PRI), there is no need to use "-w" and "-n" option as the application is capable of determining the images preference from those 2 images.

The following are some command examples:

- $sudo ./fwdwl-litehostx86_64 -f Images
The application searches for a connected modem and performs a FW download with the FW images located in  the Images file folder.  This command is equivalent to command "sudo ./fwdwl-litehostx86_64 -f Image -m 4 -l fwdwl.log", and the simpliest command to use if the application default behavior meets the user requirement.
This command does not work if any of the following circumstances occur:
  - There are more than one Sierra Wireless modems connected to the host platforms. The user must use command "-p" or "-P" to specify the target device path.
  - The modem connected to the host platform is not based on 9X07/9X50/SDX55 chipsets (e.g., 9X30).  The user must use option "-m 3" to specify a 9X30 device family.
  
- $sudo ./fwdwl-litehostx86_64 -d /dev/mhiqdl0 -p /dev/mhi_0200_00.01.00_pipe_12 -m 4 -f Images -l log.txt
The application performs a FW download on an SDX55 PCIe modem and the log is saved in log.txt.

- $sudo ./fwdwl-litehostx86_64 -F -d /dev/ttyUSB0 -p /dev/cdc-wdm1 -w fw.cwe -n carrier.pri -t 1 -f Images -l log.txt
The application performs an image switching type FW download on a family 4 type USB modem (SDX55/9X07/9X50) "/dev/cdc-wdm1" and the log is saved in log.txt.  The target image preference is specified to fw.cwe and carrier.pri.

- $sudo ./fwdwl-litehostx86_64 -P 2-9 -f Images
The application performs an image switching type FW download on the USB modem on location 2-9.  It is assumed that the modem is SDX55/9X07/9X50 based and the 2 FW images are: one FW image and one matching carrier PRI image.

- $sudo ./fwdwl-litehostx86_64 -d /dev/ttyUSB0 -p /dev/cdc-wdm1 -m 3 -f Images -l log.txt
The application performs a FW download on a modem family 3 type USB device (9X30) "/dev/cdc-wdm1".

- $sudo ./fwdwl-litehostx86_64 -d /dev/ttyUSB0 -p /dev/cdc-wdm1 -m 4 -t 1 -f Images -l log.txt
The application performs a FW image switching FW download on a family 4 type device (WP76xx) "/dev/cdc-wdm1".

- $sudo ./fwdwl-litehostx86_64 -P 2-9 -f Images -F -l log.txt
The application performs a FW download on a USB modem located at "2-9" (bus 2, device 9).  Option "-P" is for USB only and typically useful when multiple USB modems are connected to host.

- $sudo ./fwdwl-litehostx86_64 -a
The application enables device AUTO-SIM based image switch feature.  There is no actual FW download occurred.  Device will reset and come back in APP mode with AUTO-SIM feature enabled.

- $sudo ./fwdwl-litehostx86_64 -f 9x50 -P 2-9 -F -a
The application performs an image switch with the images located in 9x50 folder, and then enables device AUTO-SIM based image switch feature after the successful image switch.

- $sudo ./fwdwl-litehostx86_64 -f sdx55_03.09.01.00 -s SWIX55C_03.09.01.00-001_GENERIC_030.032_000.nvu
The application downloads image file SWIX55C_03.09.01.00-001_GENERIC_030.032_000.nvu from sdx55_03.09.01.00 to device as a non image switch scenario.

- $sudo ./fwdwl-litehostx86_64 -f /home/a/WORK/Firmware/RC7611/R6.4/ATT/ -s RC76xx_Release6.4_ATT_7611.spk -t 1
The application downloads image file RC76xx_Release6.4_ATT_7611.spk from /home/a/WORK/Firmware/RC7611/R6.4/ATT/ folder as an image switch scenario.

- $sudo ./fwdwl-litehostx86_64 -r -d /dev/ttyUSB0
The application resets the device on /dev/ttyUSB0 port.

- $sudo ./fwdwl-litehostx86_64 -x 255
The application deletes all (both FW and PRI) images from device.

- $sudo ./fwdwl-litehostx86_64 -f Images -t 3 -w SWIX55C_03.09.15.00-001.cwe -n SWIX55C_03.09.15.00-001_GENERIC_030.049_000.nvu
The application downloads all the images from Images folder, and sets the image preferences to SWIX55C_03.09.15.00-001.cwe and SWIX55C_03.09.15.00-001_GENERIC_030.049_000.nvu.

8. Firmware Download Scenarios
==============================

Assuming all FW images to be downloaded are placed in Images folder.

Case 1: Downloading one non spk image

e.g., cwe or nvu file, this FW image can only be downloaded through non image switch FW download. No need to specify "-t" command as the application treats this as a non FW image switching case by default.

$sudo ./fwdwl-litehostx86_64 -f Images

Case 2: Downloading one .spk FW image for FW image switching

For FW image switching scenarios for WP type devices, this is typically done through one .spk FW image. Command "-t 1" must be used to indicate a FW image switching FW download.  The retrieves the image preference setting from the .spk file.

$sudo ./fwdwl-litehostx86_64 -t 1 -f Images -l log.txt

Case 3: Downloading two images

When downloading two images, it is better to specify an image switching or non image switching FW download via option "-t".  However, if the two images are one FW image and its matching carrier PRI, it is ok to omit the "-t" option and the application assumes it is an image switching scenario and retrieve images preferences from the two images.  If the two images are not one FW image and its matching carrier PRI, you need to use option "-t 2" to indicate a non image switch FW download as command shown below.

$sudo ./fwdwl-litehostx86_64 -d /dev/mhiqdl0 -p /dev/mhi_0306_00.01.00_pipe_12 -l pcie_mbim.log -f Images -t 2

Case 4: Downloading three or more images 

If you are downloading three or more images without "-t" option, the application will assume this is a non image switch firmware download.  All image files will be downloaded however, the FW image (if there is one within the images downloaded) will not be placed into a firmware slot.  If you want the downloaded FW image being placed into a firmware slot, you need to specify the firmware download is an image switching type with command argument "-t 1".  In addition, you also need to specify the FW and PRI image preferences via "-w" and "-n" option.

$sudo ./fwdwl-litehostx86_64 -d /dev/mhiqdl0 -p /dev/mhi_0306_00.01.00_pipe_12 -l pcie_mbim.log -f Images -t 2
$sudo ./fwdwl-litehostx86_64 -d /dev/mhiqdl0 -p /dev/mhi_0306_00.01.00_pipe_12 -l pcie_mbim.log -f Images -t 1 -w spkg.cwe -n carrier.nvu

Case 5: Image switching involves more than one FW image and multiple PRI images

Assuming we have the following images in Images folder.  We want to download all of these images in one FW download session and place all the FW images into modem FW slots.  Also, the modem image preferences needs to be set to SWIX55C_03.09.15.00-001.cwe/SWIX55C_03.09.15.00-001_GENERIC_030.049_000.nvu combination.
- SWIX55C_03.04.03.00-001.cwe/SWIX55C_03.04.03.00-001_TELSTRA_030.014_000.nvu
- SWIX55C_03.09.06.00-001.cwe/SWIX55C_03.09.06.00-001_ATT_030.038_000.nvu
- SWIX55C_03.09.15.00-001.cwe/SWIX55C_03.09.15.00-001_GENERIC_030.049_000.nvu

$sudo ./fwdwl-litehostx86_64 -f Images -t 3 -w SWIX55C_03.09.15.00-001.cwe -n SWIX55C_03.09.15.00-001_GENERIC_030.049_000.nvu
$sudo ./fwdwl-litehostx86_64 -f Images -t 3 -P 2-9.4 -w SWIX55C_03.09.15.00-001.cwe -n SWIX55C_03.09.15.00-001_GENERIC_030.049_000.nvu
$sudo ./fwdwl-litehostx86_64 -f Images -t 3 -p /dev/cdc-wdm0 -w SWIX55C_03.09.15.00-001.cwe -n SWIX55C_03.09.15.00-001_GENERIC_030.049_000.nvu

9. Notes
========

9.1 When a device is stuck in FW download (BOOT&HOLD) mode, you can try resetting the device via option "-r -d <path to QDLoader>" to bring the device back to APP mode.  If device is still in BOOT&HOLD mode, the following steps must be used to bring the modem back into APP mode.
a) Download a FW CWE image to bring the modem back to APP mode. However, the device might be in low power mode due to an image mismatch.
b) Perform an image switch FW download with both a FW CWE image and a matching carrier PRI image. This step should also bring the modem back to ONLINE mode.

9.2 Option "-P" allows user to specify USB device location (bus#-port#) and let the FW download tool search for device (adapter and QDL interfaces).  When "-P" command is used, the app ignores the "-d" and "-p" commands if they are specified.  This command should not be used on 9X30 based modems that are connected through USB3 because the device location info may change when the modem switches to download mode. However, this feature can still be used on 9X30 modems that are connected through USB2 interface.

The application supports FW downloads to USB devices that are connected to host through USB hubs.  The following hub hierarchy scenarios are supported.
a) "-P bus#-port#" - Device is connected to host root_hub directly.
b) "-P bus#-hub#.port#" - Device is connected to a sub_hub which is connected to the host root_hub.
c) "-P bus#-hub#.hub#.port#" - Device is connected to a sub_hub on another sub_hub which is connected to the host root_hub.

9.3 Option "-a" enables device AUTO-SIM based image switch feature.  Device needs to be reset to allow the feature to take effect.  Once enabled, device performs image switches automatically based on the SIM inserted.  To disable the device AUTO-SIM feature, launch an image switch request via this application.

This option can be used alone or together with an image switch option.  The application behaves slightly different in terms of confirming the AUTO-SIM feature status or not after enabling it.
a) $sudo ./fwdwl-litehostx86_64 -a
The application enables device AUTO-SIM based image switch, and confirms if the AUTO-SIM feature is enabled or not after the device reset.
b) $sudo ./fwdwl-litehostx86_64 -f <FW location> -a
The application performs an image switch with the images in <FW location> first and then enables AUTO-SIM feature after the successful image switch.  Once the QMI request of enabling AUTO-SIM feature is sent to device, the application terminates.  In other words, the application does not wait for device reset and confirm the status of request.

9.4 litefw_download API
The core FW download process is handled by litefw_download API defined in the lite-fw library.  When calling litefw_download API, the application passes user specified command options to the API via a _userOptions structure.  Please note that the log_file_path parameter of _userOptions structure is not used in litefw_download API.  The application logging feature is implemented in the application level (outside of the litefw_download API).

However, the lite-fw library provides an interface litefw_set_log_func() which allows registering an external logging routine for lite-fw logging purpose.  If registered, the lite-fw library directs logging messages to the registered external logging routine.  If not, the logging messages are directed to syslog.  For details, please refer to start_logging function in the application source code.
