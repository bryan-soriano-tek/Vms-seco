1. Description
==============

This readme file provides basic instructions on how to build all the SDK libraries.  These are required by applications that require QMI communication support with supported Sierra Wireless modems.  Build instructions for sample applications are available in their folders.


2. Build Instructions
=====================

The top level SDK packages is "pkgs".
Navigate to this directory and type:

- Intel x86/x64 based platforms:

"make complete"

- ARM based platforms:

"make CPU=arm64linaro complete"
"make CPU=arm64 complete"
"make CPU=rpi complete"

- For other CPUs and platforms: please use the correct toolchain. gen.mak - edit the compiler, library and include paths accordingly.


The binaries should be created under the build/lib/<CPU variant> folder.
