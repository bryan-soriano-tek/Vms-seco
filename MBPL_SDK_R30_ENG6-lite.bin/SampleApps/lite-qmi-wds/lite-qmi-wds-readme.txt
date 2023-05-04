1. Description
==============

lite-qmi-wds (the application) is a sample application/utility that manages QMI Wireless Data Service on Sierra Wireless Modems based on Qualcomm chipsets.

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

  $cd SampleApps/lite-qmi-wds/
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
		
  -S  --skipsync
        Skip syncing QMI control IDs
		
  -V  --version
        Show version information.

  -h  --help
        This option prints the usage instructions.

  -o  --operation
        Automatically perform the specifed action without user interaction.
        If the operation has required parameters, they must also be provided.
        Operation-specific parameters will be ignored if the -o flag is not present, or if they are not associated with the specified operation.
        Supported operations:

        SetKeepAliveDataSession
        Parameters:
         -e  --keep-alive-data-session (0|1) (mandatory)
        ResetAndModifyProfileSettings
        Parameters:
         -i  --profile-id (1-24) (mandatory)
        GetApnOpReservedPcoList
         -a  --apn (string) (mandatory)
        GetApnMsisdnInfo
         -a  --apn (string) (mandatory)
        DeleteAllProfiles
         -p  --profile-persistence-mask (1|2) (optional)
         -c  --profile-client-type-mask (1|128) (optional)
        GetEhrpdFallbackApnList
        SetEhrpdFallbackApnList
        Parameters:
         -a  --apn (string) (mandatory)
        SetModemAssistedKaStart
        Parameters (at least one optional must be set):
         -a  --apn-name (string) (optional)
         -k  --keep_alive_type (0|1) (mandatory)
         -b  --timer-value (integer) (optional)
         -f  --dest-ipv4-address (string) (optional)
         -F  --source-ipv4-address (string) (optional)
         -g --dest-port (string) (optional)
         -G --source-port (string) (optional)
        SetModemAssistedKaStop
        Parameters:
         -K  --keep-alive-handle (integer) (mandatory)
        RegisterWdsEventRegister
        Parameters:
         -A  --ccri (0|1) (optional) 
         -B  --tsi (0|integer) (optional)
         -C  --tsim (mask) (optional)
         -D  --dsi (0|1) (optional)
         -E  --msi (0|1) (optional)
         -H  --dcsi (0|1) (optional)
         -I  --cpdsi (0|1) (optional)
         -J  --epmsi (0|1) (optional)
         -L  --ufci (0|1) (optional)
         -M  --apfri (0|1) (optional)
         -N  --dbtxi (0|1) (optional)
         -O  --dri (0|1) (optional)
        RegisterWdsIndicationRegister
        Parameters:
         -a  --apn (string) (optional) 
         -1  --ssi (0|1) (optional) 
         -2  --lap (0|1) (optional) 
         -3  --rpc (0|1) (optional) 
         -4  --aal (0|1) (optional) 
         -5  --aap (0|1) (optional) 
         -6  --rla (0|1) (optional) 
         -7  --apnm (string) (optional) 
         -8  --rbt (0|1) (optional) 
         -9  --rtp (0|1) (optional) 
        GetDefaultProfileId
        Parameters:
         -t  --profile-family (0|1) (mandatory)
        SetDefaultProfileId
        Parameters:
         -i  --profile-id (integer) (mandatory)
         -t  --profile-family (0|1) (mandatory)
        Set3GPPConfigItems
        Parameters (at least one optional must be set):
         -u  --profile-list (x,xx,x) (string) (optional)
         -w  --always-conect (0|1) (optional)
         -x  --3gpp-release (0|1|2|3|4|5|6|7) (optional)
         -y  --lte-profile (x,xx,x) (optiona)
        SetDownlinkThroughputReportPeriod
        Parameters:
         -z  --dl_throughput_report_period (integer) (mandatory)
        QueryDownlinkThroughputReportingStatus
        GetCurrentChannelrate

6. Examples
===========

Direct QMUX mode
  sudo ./lite-qmi-wdshostx86_64 -d /dev/mhi_0200_00.01.00_pipe_12
  sudo ./lite-qmi-wdshostx86_64 -d /dev/cdc-wdm0

MBIM mode
  sudo ./lite-qmi-wdshostx86_64 -d /dev/mhi_0200_00.01.00_pipe_12 -m
  sudo ./lite-qmi-wdshostx86_64 -d /dev/cdc-wdm0 -m

7. Notes, exceptions, etc.
==========================
Test Cases
  7.1 Set Keep Alive Data Session
  7.2 Reset And Modify Profile Settings
  7.3 Get APN Operator Reserved PCO List
  7.4 Get APN MSISDN Information
  7.5 Delete All Profiles
  7.6 Get EHRPD Fallback APN List
  7.7 Set EHRPD Fallback APN List
  7.8 Set Modem Assisted Keep Alive Start
  7.9 Set Modem Assisted Keep Alive Stop
  7.10 Register WDS Event Register
  7.11 Register WDS Indication Register
  7.12 Get Default Profile ID
  7.13 Set Default Profile ID
  7.14 Get 3GPP Config Items
  7.15 Set 3GPP Config Items
  7.16 Set Downlink Throughput Report Period
  7.17 Query Downlink Throughput Reporting Status
  7.18 Get Current Channel Rate
  7.19 GetDefaultNssai
  7.20 SetDefaultNssai
  7.21 GetProfileSnssai
  7.22 ConfigureProfileSnssai
  7.23 DeleteProfile
  7.24 ClearProfileSnssai


