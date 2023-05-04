1. Description
==============

lite-qmi-nas (the application) is a sample application/utility that manages QMI Network Access Service on Sierra Wireless Modems based on Qualcomm chipsets.

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
  - Based on 9X50,  Ex: EM7565/EM7511/EM74X1, etc.
  - Based on 9X30,  Ex: EM7455/EM7430, etc.
  - Based on 9X15,  Ex: EM7355/EM7305, etc.
  - Based on 9X07,  Ex: WP76xx

4. Build Instructions
=====================

  $cd SampleApps/lite-qmi-nas/
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

  -V  --version
        Show version information.

  -h  --help
        This option prints the usage instructions.


6. Examples
===========

Direct QMUX mode
  sudo ./lite-qmi-nashostx86_64 -d /dev/mhi_0200_00.01.00_pipe_12
  sudo ./lite-qmi-nashostx86_64 -d /dev/cdc-wdm0

MBIM mode
  sudo ./lite-qmi-nashostx86_64 -d /dev/mhi_0200_00.01.00_pipe_12 -m
  sudo ./lite-qmi-nashostx86_64 -d /dev/cdc-wdm0 -m

7. Notes, exceptions, etc.
==========================
Test Cases
  7.1 Set System Selection Preference
  7.2 Set Band Preference
  7.3 Indication Register
  7.4 Get Signal Info
  7.5 Get System Info
  7.6 Set 5G Signal Strength Thresholds  
  7.7 Get Plmn Name
  7.8 Get Cell Location Info
  7.9 Get Network Time
  7.10 Get TxRx Info Ext
  7.11 Get eDRX Params
  7.12 Get eDRX Params Ext
  7.13 Set eDRX Params
  7.14 Get RF Info
  7.15 Get System Selection Preference
  7.16 Block Nr5g Plmn
  7.17 Unblock Nr5g Plmn
  7.18 Reset Nr5g Plmn Blocking
  7.19 Set ENDC Configuration
  7.20 Get Antenna Signal Info
  7.21 Get Nr5g Cell Info
  7.22 Set NR5G Band Priority
  7.23 Get Sys Info Ext
  7.24 Get RFDEV status (SWINAS)
  7.25 Set mmWave config (SWINAS)
  7.26 Get System Selection Preference Ext
  7.27 Get CQI
  7.28 Get Lte Carrier Cell Information
  7.29 Get LTE CPHY Carrier aggregation Information
  7.30 Get Modem Status Information  
  7.31 Get Home Network Information  
  7.32 Get Serving System Information
  7.33 Get the ENDC Configuration
