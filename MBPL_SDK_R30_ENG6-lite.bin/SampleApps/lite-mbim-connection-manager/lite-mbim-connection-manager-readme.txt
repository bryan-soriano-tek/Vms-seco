1. Description
==============

lite-mbim-connection-manager (the application) is a sample application/utility that manages data connections over Sierra Wireless Modems based on Qualcomm chipsets over MBIM interface.  


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

  $cd SampleApps/lite-mbim-connection-manager/
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

  <appName> -s <path to settings config file> [-V] [-h]

  -s  --settingsPath <path to settings config file>
        path to settings configuration file (defaults to settings.conf)

  -V  --version
        Show version information.

  -h  --help
        This option prints the usage instructions.

Two sample settings configuration files are provided and are self-documenting.
- settings-simple.conf:
  This configures a single session.
- settings-vlan.conf:
  This configures 2 VLANs, each associated with a different PDN session.    


6. Examples
===========

$sudo ./lite-mbim-connection-managerhostx86_64 -s <path to settings file>


7. Notes, exceptions, etc.
==========================

7.1 There is minimal user interaction. 
The app will automatically 
- read the settings configuration file
- connect to the modem over the MBIM control path
- check subscriber status
- check and may prompt user for PIN if SIM is locked
- check and switch radio on if necessary
- check register state
- check packet service
- create VLANs if configured to do so
- for each configured session, establish a data connection
- for each configured session, update the OS network interfaces with IP addresses/mtus/routes
- if any ping destinations have been configured (to verify connectivity), they will be pinged
Press <enter> to disconnect sessions and exit program.

7.2 DNS may need to be configured
  "sudo nano /etc/resolv.conf"
  For IPv4, change "nameserver" to "8.8.8.8" and save the file.  For IPv6, add the following:
  "nameserver 2402:9d80:101:1:0:0:1:7"
  "nameserver 2402:9d80:101:1:0:0:1:4"
