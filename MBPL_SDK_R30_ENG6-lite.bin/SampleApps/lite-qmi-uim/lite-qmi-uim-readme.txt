1. Description
==============

lite-qmi-uim (the application) is a sample application/utility that manages QMI User Identity Module Service on Sierra Wireless Modems based on Qualcomm chipsets.

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

  $cd SampleApps/lite-qmi-uim/
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

  -G  --skipget
        Skip getting client IDs.

  -R  --skiprelease
        Skip releasing client IDs.

  -C  --clientidspath
        Path of file where client IDs may be 
        saved or retrieved when 
        -G/-R options are used.
        File format consists of lines, 
        one for each QMI service: QMI service,client ID
        e.g. 2,27
             11,15

6. Examples
===========

Direct QMUX mode
  sudo ./lite-qmi-uimhostx86_64 -d /dev/mhi_0200_00.01.00_pipe_12
  sudo ./lite-qmi-uimhostx86_64 -d /dev/cdc-wdm0

MBIM mode
  sudo ./lite-qmi-uimhostx86_64 -d /dev/mhi_0200_00.01.00_pipe_12 -m
  sudo ./lite-qmi-uimhostx86_64 -d /dev/cdc-wdm0 -m

For scripting purposes it is useful to preserve QMI client IDs across application invocations.

1st invocation gets client IDs from modem and does not release them, 
instead it saves them to clientidsmap.txt.

  sudo ./lite-qmi-uimhostx86_64 -d /dev/cdc-wdm0 -R -C clientidsmap.txt

2nd invocation does not get client IDs from modem, it reads them from file, 
and does not release them.
  sudo ./lite-qmi-uimhostx86_64 -d /dev/cdc-wdm0 -G -R -C clientidsmap.txt

3rd invocation does not get client IDs from modem, it reads them from file, 
and finally it releases them.
  sudo ./lite-qmi-uimhostx86_64 -d /dev/cdc-wdm0 -G -C clientidsmap.txt
  

7. Notes, exceptions, etc.
==========================
Test Cases
  7.1  Get Slots Status
    - Physical Slot Status
    - Physical Slot Information
    - Slot EID Information
    - Extended Card State

  7.2  Get Card Status
    -  Extended Card Status
    - Card Status
    - Hot-Swap Status
    - Valid Card Status
    - Extended Card Status
    - Extended Hot-Swap Status
    - SIM Busy Status
    - Card Mode
    - Extended Info
    - Momentary Power Down

  7.3  Get ICCID
    - The ICCID of the card in the physical slot

  7.4  Event Register
    - Card status
    - SAP connection
    - Extended card status
    - Close of provisioning sessions
    - Physical slot status
    - SIM busy status
    - Reduced card status
    - Recovery complete
    - Supply voltage Vcc status
    - Card activation status
    - Remote SimLock Configuration
    - SimLock temporary unlock

  7.5  Switch Slot
    - Switche (activate) a physical slot for the given logical slot

  7.6  Verify PIN
    - Activates, deactivates, or switches the provisioning sessions

  7.7  Set PIN Protection
    - Enable or disable the protection of UIM contents by a specific PIN

  7.8  Unblock PIN
    - Unblocks a blocked PIN using the PUK code

  7.9  Power Down
    - Power down the card

  7.10  Power Up
    - Power up the card

  7.11  Reset
    - Resets the state of the issuing control point kept by the service
        
  7.12  Refresh Register
    - Register for file change notifications triggered by the card

  7.13  Refresh Get Last Event
    - Provide the ability to retrieve the last refresh event

  7.14  Get File Attributes
    - Retrieve the file attributes for any EF or DF in the card and provides access by the path

  7.15  Depersonalization
    - Deactivate or unblock the personalization on the phone

  7.16  Authenticate
    - Execute the authentication algorithm on the card

  7.17  Get Configuration
    - Get the modem configuration for the UIM module

  7.18  Change PIN
    - Change the value of the specified PIN

  7.19  Read Transparent
    - Read IMSI and ICCID from the card
