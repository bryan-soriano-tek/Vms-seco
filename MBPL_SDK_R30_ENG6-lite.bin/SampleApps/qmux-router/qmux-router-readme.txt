1. Description
==============

qmux-router (the application) is a sample application/utility that acts as a daemon to multiplex QMI communication from multiple clients over Sierra Wireless Modems based on Qualcomm chipsets.  This allows multiple apps to work simutaniously.


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

  $cd SampleApps/qmux-router/
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

  <appName> [-m|-q] [-d <QMI/MBIM device path>] [-n] [-V] [-h]

  -d  --device <QMI/MBIM device path>
        Specifies the QMI or the MBIM device path
        Example: 
        - "-p /dev/cdc-wdm0" for a USB modem (either MBIM or RmNet interface)
        - "-p /dev/mhi_0306_00.01.00_pipe_12" for PCIe MBIM interface
        - "-p /dev/mhi_0306_00.01.00_pipe_14" for PCIe QMI interface

  -q  --qmi
        Use direct QMUX interface (QMI over PCIe, or RmNet over USB)

  -m  --mbim
        Use MBIM interface (Over PCIe, or MBIM over USB)

  -n  --normal
        Run as normal (non-daemon) process

  -V  --version
        Show version information.

  -h  --help
        This option prints the usage instructions.


6. Examples
===========

Automatic mode (default)
  $sudo ./qmux-routerhostx86_64

MBIM mode
  $sudo ./qmux-routerhostx86_64 -m

QMI mode
  $sudo ./qmux-routerhostx86_64 -q

Non-daemon mode
  $sudo ./qmux-routerhostx86_64 -n


7. Notes, exceptions, etc.
==========================

Stop the daemon process
To stop the process running as daemon, 
  1) note the process id printed out in the terminal when daemon is launched, e.g. 5000
  2) issue "sudo kill -s TERM 5000" command to terminate the process
