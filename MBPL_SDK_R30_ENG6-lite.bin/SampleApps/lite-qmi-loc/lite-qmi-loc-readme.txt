1. Description
==============

lite-qmi-loc (the application) is a sample application/utility that manages QMI Location Service on Sierra Wireless Modems based on Qualcomm chipsets.

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

  $cd SampleApps/lite-qmi-loc/
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

          SetLocOperationMode
          Parameters:
           -O  --operation-mode (1|2|3|4|5|6) (mandatory)
          RegisterLocEvents
          Parameters:
           -M  --loc-event-mask (integer) (mandatory)
          SetLocInjectUTCTime
          Parameters:
           -t  --utc-time (integer) (mandatory)
           -u  --time-uncertainty (integer) (mandatory)
          GetNmeaTypes
          SetNmeaTypes
          Parameters:
           -n  --nmea-types (integer) (mandatory)
          RegisterMasterClient
          Parameters:
           -k  --master-client-key (integer) (mandatory)
          InjectSuplCerticficate
          Parameters:
           -H  --supl-cert-id (0|1|2|3|4|5|6|7|8|9) (mandatory)
           -S  --supl-cert-data (string) (mandatory)
          DeleteSuplCerticficate
          Parameters:
           -D  --supl-cert-id-del (integer) (optional)
          GetBestAvailablePosition
          Parameters:
           -T  --trans-id (integer) (mandatory)
          StartLocService
          Parameters:
           -A  --start-sid (0-255) (mandatory)
           -B  --start-fr (1|2) (optional)
           -C  --start-hal (1|2|3) (optional)
           -E  --start-irs (1|2) (optional)
           -F  --start-mi (integer) (optional)
           -G  --start-caa 1|2) (optional)
           -I  --start-mib (integer) (optional)
           -J  --start-mwt (integer) (optional)
           -K  --start-spr (0|1) (optional)
           -L  --start-rgo (0|1) (optional)
           -N  --start-gpm (1|2|3|4|5) (optional)
           -P  --start-tm (integer) (optional)
          StopLocService
          LocEventInjectTime
          SetGnssConstellReportConfig
          Parameters (At least one optional parameter must be set):
           -Q  --meas-report-config (0x01|0x02|0x04|0x08|0x10) (optional)
           -R  --sv-poly-report-config (0x01|0x02|0x04|0x08|0x10) (optional)
           -v  --report-full-ephemeris-db (0-255) (optional)
           -x  --report-full-sv-poly-db (0-255) (optional)
           -y  --report-full-iono-db (0-255) (optional)
          QueryGeofence
          Parameters:
           -f  --geofence-id (integer) (mandatory)
           -a  --transaction-id (integer) (mandatory)
          EditGeofence
          Parameters:
           -f  --geofence-id (integer) (mandatory)
           -a  --transaction-id (integer) (mandatory)
           -b  --geofence-state (1|2) (optional)
           -c  --breach-mask (1|2) (optional)
           -e  --responsiveness (1|2|3|4|5) (optional)
          AddCircularGeofence
          Parameters:
           -a  --transaction-id (integer) (mandatory)
           -j  --add-cga-latitude (double) (mandatory)
           -l  --add-cga-longtitude (double) (mandatory)
           -U  --add-cga-radius (integer) (mandatory)
           -1  --add-bm (0|1) (mandatory)
           -2  --add-ip (0|1) (mandatory)
           -3  --add-re (1|2|3|4|5) (optional)
           -4  --add-co (1|2|3) (optional)
           -5  --add-cre (integer) (optional)
           -6  --add-dt (integer) (optional)
           -7  --add-dmt (0|1) (optional)
          DeleteGeofence
          Parameters:
           -f  --geofence-id (integer) (mandatory)
           -a  --transaction-id (integer) (mandatory)
          GetNiGeofenceIdList
          Parameters:
           -f  --geofence-id (integer) (mandatory)
          GetGeofenceEngineConfig
          Parameters:
           -f  --geofence-id (integer) (mandatory)
          AddGeofenceContext
          Parameters:
           -f  --geofence-id (integer) (mandatory)
          DeleteGeofenceContext
          Parameters:
           -f  --geofence-id (integer) (mandatory)
           -a  --transaction-id (integer) (mandatory)
           -8  --context-id (integer) (optional)
          SetGeofenceEngineConfig
          Parameters:
           -a  --transaction-id (integer) (mandatory)
           -z  --config-gto (integer) (optional)
           -Z  --config-mgl (integer) (optional)
           -w  --config-mgs (1|2|4) (optional)
           -0  --config-ecp (0|1) (optional)
           -9  --config-got (integer) (optional)
           -p  --config-gmu (integer) (optional)
           -g  --config-mrv (integer) (optional)
           -i  --config-nsw (integer) (optional)
           -W  --config-gms (motionState, motionStateSpeed x,xx.xx ) (optional)                
          SetGeofenceEngineContext
          Parameters:
           -X  --utc-time-of-day (integer) (optional)
           -a  --transaction-id (integer) (mandatory)
           -Y  --temperature (integer) (optional) 
          DeleteAssistData

6. Examples
===========

Direct QMUX mode
  sudo ./lite-qmi-lochostx86_64 -d /dev/mhi_0200_00.01.00_pipe_12
  sudo ./lite-qmi-lochostx86_64 -d /dev/cdc-wdm0

MBIM mode
  sudo ./lite-qmi-lochostx86_64 -d /dev/mhi_0200_00.01.00_pipe_12 -m
  sudo ./lite-qmi-lochostx86_64 -d /dev/cdc-wdm0 -m

Socket mode
  sudo ./lite-qmi-lochostx86_64 -s

7. Notes, exceptions, etc.
==========================
Test Cases
  7.1 Set LOC Operation Mode
  7.2 Register LOC Events
  7.3 Start LOC Service
  7.4 Stop LOC Service
  7.5 Set loc inject UTC time
  7.6 Get LOC event inject time
  7.7 Get LOC NMEA Types
  7.8 Set LOC NMEA Types
  7.9 Register Master Client
  7.10 Inject Supl Certificate
  7.11 Delete Supl Certificate
  7.12 Get Best Available Position
  7.13 Set GNSS Constell Report Config
  7.14 Query Geofence"
  7.15 Edit Geofence"
  7.16. Add Circular Geofence"
  7.17. Delete Geofence"
  7.18. Get Network Initiated ID List"
  7.19. Get Geofence Engine Configuration"
  7.20. Add Geofence Context"
  7.21. Delete Geofence Context"
  7.22. Set Geofence Engine Configuration"
  7.23. Set Geofence Engine Context"
  7.24. Delete Assits Data
  7.25. Inject XTRA Data
  7.26. Query XTRA Info
  7.27. Get XTRA T-Session Control
  7.28. Set XTRA T-Session Control
  7.29. Inject XTRA PCID
  
