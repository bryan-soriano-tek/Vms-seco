1. Description
==============

lite-qmi-connection-manager (the application) is a sample application/utility that manages data connections over Sierra Wireless Modems based on Qualcomm chipsets.  


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

  $cd SampleApps/lite-qmi-connection-manager/
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

To build with more debug information in out, use "debug=1" option.  For example,
  $make debug=1


5. Command Options
==================

None of the command line options are mandatory.  The program can detect the modem and interface automatically.

To check available user command options:
./bin/<appName> -h (or --help)
  Where appName is the CPU specific target binary.

App usage: 

  <appName> [[[-m|-q] [-d <QMI/MBIM device path>]]|[-r]] [-P enable|disable] [-R enable|disable] [-tm] [-ts] [-V] [-h]

  -d  --device <QMI/MBIM device path>
        Specifies the QMI or the MBIM device path
        Example: 
        - "-d /dev/cdc-wdm0" for a USB modem (either MBIM or RmNet interface)
        - "-d /dev/mhi_0306_00.01.00_pipe_12" for PCIe MBIM interface
        - "-d /dev/mhi_0306_00.01.00_pipe_14" for PCIe QMI interface

  -m  --mbim
        Use MBIM interface (MBIM over PCIe or USB)

  -q  --qmi
        Use direct QMUX interface (QMI over PCIe or USB)

  -r  --router
        Use QMUX Router

  -P  --ping enable|disable
        Set default value of pinging on connecton.  Default is enalbed
		
  -R  --routing enable|disable
        Set default value of routing table update on connecton.  Default is enalbed
		
  -s  --socket
        Run socket mode
		
  -S  --skipsync
        Skip syncing QMI control IDs
		
  -tm  --thermal_mitigation
        Enable thermal mitigation device monitoring.

  -ts  --thermal_sensor
        Enable thermal sensor monitoring.
        
  -V  --version
        Show version information.

  -h  --help
        This option prints the usage instructions.
  

6. Examples
===========

Automatic mode (default)
  sudo ./lite-qmi-connection-managerhostx86_64
  
Router mode (qmux-router is required to be running)
  ./lite-qmi-connection-managerhostx86_64 -r

Direct QMUX mode
  sudo ./lite-qmi-connection-managerhostx86_64 -q

MBIM mode
  sudo ./lite-qmi-connection-managerhostx86_64 -m

Socket mode
  sudo ./lite-qmi-connection-managerhostx86_64 -s


7. Notes, exceptions, etc.
==========================

7.1 Establish data session:
- Launch the app and verify the app communicates with the modem successfully:
- Use option 5 to list existing profiles.
- Use option 8 to modify profile settings or option 6 to create a new profile, if the desired profile is not available.
- Use option 1 to start data session; choose profile and desired PDP type.
  *** Do not use Attach profiles.
- Use option 3 to end data session.

7.2 Establish multiple PDN sessions:
- Launch the app and verify the app communicates with the modem successfully:
- Use option 5 to list existing profiles.
- Use option 8 to modify profile settings or option 6 to create a new profile, if the desired profile is not available. Two profiles with different APNs are required.
  *** Do not use Attach profiles.
- Use option 2 to start multiple PDN data session; choose profile and desired PDP
  type for the first session 
- Use option 2 again; choose profile with different APN and desired PDP type for the second session 
  *** Do not use Attach profiles.
- Use option 4 to end data sessions.

7.3 DNS may need to be configured
   "sudo nano /etc/resolv.conf"
   For IPv4, change "nameserver" to "8.8.8.8" and save the file.  For IPv6, add the following:
   "nameserver 2402:9d80:101:1:0:0:1:7"
   "nameserver 2402:9d80:101:1:0:0:1:4"

7.4 Data sessions established prior to launching the app cannot be disconnected (via other instances of the app, other apps or AT commands where applicable).

7.5 Socket mode usage
    When running in socket mode, this app runs as socket server.  User can communicate with it in another terminal via command line in the following format:
	echo “help” | nc -U /tmp/qmicm-server-socket
	This issues "help" command to this app, which displays the list of supported commands and argument list, if any.  netcat utility with "-U" (Unix domain socket) support is required.

7.6 Sequence of enabling WDS Event Report indications
    To enable WDS Event Report, data connection should be established beforehand.  Otherwise indication might be missed.
