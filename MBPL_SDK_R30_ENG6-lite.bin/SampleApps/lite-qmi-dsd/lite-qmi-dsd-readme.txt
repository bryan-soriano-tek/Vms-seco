1. Description
==============

lite-qmi-dsd (the application) is a sample application/utility that manages QMI Data System Determination Service on Sierra Wireless Modems based on Qualcomm chipsets.

2. Prerequisities
=================

The application should only be used with drivers included in MBPL release packages.  It does not work with GobiNet and GobiSerial drivers distributed with legacy SLQS packages.

2.1 PCIe driver
The mhictrl driver should be used for SDX55 based modems in PCIe mode. The modem should be recognized as /dev/mhixxx modems which can be listed via command "ls /dev/mhi*".

2.2 USB driver
The following drivers should be used for modems in USB mode: 
- Network Driver: Open Source cdc_mbim driver (for the MBIM interface) or the qmi_wwan driver (included in the MBPL release packages for the RmNet interface)
- Serial Driver: Open Source qcserial driver (included in MBPL release packages)

Please note that GobiNet and GobiSerial drivers (if installed) should be removed or blacklisted from host system before launching the application.  These drivers were distributed with older SLQS releases and are no longer supported.

To blacklist Gobixxx drivers, add the following entries to "/etc/modprobe.d/blacklist-modem.conf" file and restart the Linux platform:

blacklist GobiNet
blacklist GobiSerial

2.3 Build "pkgs"
See readme.txt under "pkgs" folder

2.4 Modem preparation
- Modem running latest firmware
- All antennas connected properly
- Valid SIM inserted
- Modem registered with the cellular network or callbox

3. Supported Modems
====================

  - Based on SDX55, Ex: EM9190/EM9191/EM7690, etc.

4. Build Instructions
=====================

  $cd SampleApps/lite-qmi-dsd/
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

The binaries should be built under the bin folder.


5. Command Options
==================

To check available user command options:
./bin/<appName> -h (or --help)
  Where appName is the CPU specific target binary.

App usage: 

  <appName> [-m] [-d <device>] [-V] [-h]

  -d  --device <QMI/MBIM device path>
        Specifies the QMI or the MBIM device path
        Example: 
        - "-p /dev/cdc-wdm0" for a USB modem (either MBIM or RmNet interface)
        - "-p /dev/mhi_0306_00.01.00_pipe_12" for PCIe MBIM interface
        - "-p /dev/mhi_0306_00.01.00_pipe_14" for PCIe QMI interface

  -m  --mbim
        Use MBIM interface (Over PCIe, or MBIM over USB)

  -q  --qmi
        Use direct QMUX interface (QMI over PCIe, or RmNet over USB)

  -r  --router
        Use QMUX Router

  -s  --socket
        Run socket mode

  -V  --version
        Show version information.

  -h  --help
        This option prints the usage instructions.

  -o  --operation  
        Automatically perform the specifed action without user interaction.
        If the operation has required parameters, they must also be provided.
        Operation-specific parameters will be ignored if the -o flag is not present, or if they are not associated with the specified operation.
        Supported operations: 
         GetDsdSystemStatus
         GetDsdUIInformation
         SystemStatusChange
          Parameters:
          -l  --limit_so_mask_change_ind 0|1 (Optional)
          -S  --report_data_system_status_changes 0|1 (Optional)
          -t  --report_pref_tech_change_only 0|1 (Optional)
          -b  --report_null_bearer_reason 0|1 (Optional)
         RegisterUIInformationChange
          Parameters:
          -u  --report_ui_changes 0|1 (Optional)
          -p  --suppress_so_change 0|1 (Optional)
          -B  --suppress_null_bearer_reason 0|1 (Optional)

6. Examples
===========

Direct QMUX mode
  sudo ./lite-qmi-dsdhostx86_64 -d /dev/mhi_0200_00.01.00_pipe_12
  sudo ./lite-qmi-dsdhostx86_64 -d /dev/cdc-wdm0

MBIM mode
  sudo ./lite-qmi-dsdhostx86_64 -d /dev/mhi_0200_00.01.00_pipe_12 -m
  sudo ./lite-qmi-dsdhostx86_64 -d /dev/cdc-wdm0 -m

Socket mode
  sudo ./lite-qmi-dsdhostx86_64 -s

7. Notes, exceptions, etc.
==========================
Test Cases
  7.1 Get DSD System Status	
    - Available Systems
    - APN Available System Info
    - Current and Recommended Global Preferred System Info
    - APN Current and Recommended Preferred System Info
    - Null Bearer reason
         
  7.2 Get DSD UI Information
    - Global UI Information
    - APN UI Information
    - Null Bearer reason

  7.3 System Status Change
   - Suppress SO changes
   - Register/Deregister for Data System Status Changes
   - Report only Preferred technology changes
   - Report NULL Bearer Reason

  7.4 Register UI Information Change
   - Register/Deregister for UI information changes
   - Suppress SO changes
   - Suppress NULL Bearer Reason

