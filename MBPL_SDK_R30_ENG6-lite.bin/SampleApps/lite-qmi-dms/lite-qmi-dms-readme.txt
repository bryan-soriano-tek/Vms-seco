1. Description
==============

lite-qmi-dms (the application) is a sample application/utility that manages QMI Device Management Service on Sierra Wireless Modems based on Qualcomm chipsets.

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

  $cd SampleApps/lite-qmi-dms/
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

  -o  --operation  
        Automatically perform the specifed action without user interaction.
        If the operation has required parameters, they must also be provided.
        Operation-specific parameters will be ignored if the -o flag is not present, or if they are not associated with the specified operation.
        Supported operations: 
         GetModelId
         GetFSN
         GetDeviceCapabilities
         GetBandCapabilities
         GetDeviceManufacturer
         GetMSISDN
         GetFirmwareInformation
         GetMeidImei
         GetSwiHostDevInfo
         SetSwiHostDevInfo
          Parameters:
          -u  --manufacturer (string) (optional)
          -M  --model (string) (optional)
          -v  --version (string) (optional)
          -p  --plasmaId (string) (optional)
          -h  --hostId (string) (optional)
          -i  --instance (string) (optional)
         GetStoredImages
         DeleteStoredImage
          Parameters:
          -t  --type ('modem'|'pri') (mandatory)
            e.g. --type pri
          -I  --imageId (string) (mandatory)
          -b  --buildId (string) (mandatory)
         SetPower
          Parameters:
          -P  --powerState ('online'|'lowPower'|'factoryTestMode'|'offline'|'resetting'|'shuttingDown'|'persistentLowPower'|'modeOnlyLowPower'|'networkTest'|'campOnly') (mandatory)
            e.g. --powerState resetting
         GetPower
         GetAutoSimList
          Parameters:
          -c  --carrierName (string|'all') (mandatory)
            e.g. --carrierName all
         SetAutoSimList
          Parameters:
          -c  --carrierName (string) (mandatory)
          -k  --key (<ICCID>|<MCC:MNC>|'all') (mandatory)
            e.g. --key 302:690
          -t  --type ('modem'|'pri') (optional)
          -R  --rank (1-127|255) (optional)
          -s  --subpri (integer) (optional)
          Note: If --key is set to 'all', --rank and --subpri may be omitted, and will be ignored if present. In this case, all custom entries of the specifed carrier will be deleted. If --key is not 'all', --rank and --subpri are mandatory.
         GetCustomFeatures
         SetCustomFeatures
          Parameters:
          -f  --feature (<featureId>=<featureValue>) (mandatory)
            e.g. --feature customSetting=3





6. Examples
===========

Direct QMUX mode
  sudo ./lite-qmi-dmshostx86_64 -d /dev/mhi_0200_00.01.00_pipe_12
  sudo ./lite-qmi-dmshostx86_64 -d /dev/cdc-wdm0

MBIM mode
  sudo ./lite-qmi-dmshostx86_64 -d /dev/mhi_0200_00.01.00_pipe_12 -m
  sudo ./lite-qmi-dmshostx86_64 -d /dev/cdc-wdm0 -m

7. Notes, exceptions, etc.
==========================
Test Cases
  7.1 Get Model ID
    - String identifying the device model
         
  7.2 Get FSN
    - Factory Sequence Number

  7.3 Get Device Capabilities
   - Maximum Tx transmission rate
   - Maximum Rx transmission rate
   - Data Service Capability
   - SIM Capability
   - List of Radio Interfaces supported by the device

  7.4 Get Band Capabilities
   - Band Capability
   - TDS Band Capability
   - Supported LTE Bands
   - Supported NR5G Bands

  7.5  Get Device Manufacturer
    - Device Manufacturer

  7.6  Get MSISDN
    - String containing the voice number in use by the device
    - String containing the mobile ID number of the device.
    - International Mobile Subscriber ID

  7.7  Get Firmware Information
    - CWE Sierra Package String info

  7.8  Get MEID/IMEI
    - String containing the ESN of the device.
    - String containing the IMEI of the device.
    - String containing the MEID of the device.
    - IMEI software version number

  7.9  Get SWI Host Dev Info
    - Host Device Manufacturer Name
    - Host Device Model String
    - Host Device Software Version String
    - Host Device Plasma ID String
    - Device Host ID String
    - Instance of Host Device Info

  7.10  Set SWI Host Dev Info
    - Host Device Manufacturer Name
    - Host Device Model String
    - Host Device Software Version String
    - Host Device Plasma ID String
    - Device Host ID String
    - Instance of Host Device Info

  7.11 Set Event Report
    - Sets the device management state reporting conditions for the requesting control point

  7.12 Get Stored Images
  7.13 Delete Stored Image

  7.14  Set Power
    - Sets the operating mode of the device

  7.15  Get Power
    - Queries the current operating mode of the device

  7.16  Get Auto-SIM List
    - Queries the SIM and carrier match

  7.17  Set Auto-SIM List"
    - Set the SIM and carrier match

  7.18  Get Custom Features
    - Queries custom features

  7.19  Set Custom Features"
    - Set custom feature

 7.20 Get SDK Version
    - Get latest SDK build version
