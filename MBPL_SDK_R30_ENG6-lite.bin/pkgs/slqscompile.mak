# slqscompile.mak
#-------------------------------------------------------------------------------
# Global Settings
#-------------------------------------------------------------------------------
.EXPORT_ALL_VARIABLES:
ifndef QMI_BUILD_BASE
  QMI_BUILD_BASE:=$(shell until [ -d pkgs ]; do cd ..; done; pwd)
endif
ifndef LITEQMI
BUILD_LITEQMI:=1
else
ifeq ($(LITEQMI),0)
BUILD_LITEQMI:=0
else
BUILD_LITEQMI:=1
endif
endif
ifndef LITEQMUX
BUILD_LITEQMUX:=1
else
ifeq ($(LITEQMUX),0)
BUILD_LITEQMUX:=0
else
BUILD_LITEQMUX:=1
endif
endif
ifndef LITEMBIM
BUILD_LITEMBIM:=1
else
ifeq ($(LITEMBIM),0)
BUILD_LITEMBIM:=0
else
BUILD_LITEMBIM:=1
endif
endif
ifndef LITEFW
BUILD_LITEFW:=1
else
ifeq ($(LITEFW),0)
BUILD_LITEFW:=0
else
BUILD_LITEFW:=1
endif
endif
SLQSHOSTTYPE := $(shell uname -m)
CFLAGS       := -c -Wall -Werror -Wextra -fPIC -std=gnu99
INCLUDE      := -I.. $(QMI_INCLUDE) $(QMUX_INCLUDE)
LDFLAGS      := -lrt -lpthread
DEPSDIR      := ./dep
INSTALLDIR   :=
STATICFLAG := 1
# BUILD without static flags
ifdef BUILDSTATICFLAG
STATICFLAG := $(BUILDSTATICFLAG)
endif

ifeq ($(STATICFLAG), 1)
ifeq ($(BUILD_LITEQMI), 1)
	LDFLAGS += -static
else
	# without static flag, ppc report below
	#   libgcc_s.so.1 must be installed for pthread_cancel to work
	LDFLAGS += -static
endif
ifeq ($(BUILD_LITEFW), 1)
	LDFLAGS += -static
else
	# without static flag, ppc report below
	#   libgcc_s.so.1 must be installed for pthread_cancel to work
	LDFLAGS += -static
endif
ifeq ($(BUILD_LITEQMUX), 1)
	LDFLAGS += -static
else
	# without static flag, ppc report below
	#   libgcc_s.so.1 must be installed for pthread_cancel to work
	LDFLAGS += -static
endif
ifeq ($(BUILD_LITEMBIM), 1)
	LDFLAGS += -static
else
	# without static flag, ppc report below
	#   libgcc_s.so.1 must be installed for pthread_cancel to work
	LDFLAGS += -static
endif
endif
#
# DEBUG yes means the compiler prints backtrace function name on segfault.
ifeq ($(DEBUG),yes)
  LDFLAGS       += -rdynamic
endif

SLQSFLAG=-D SLQS
SYMBOLS := ON
AVMS_AUTO_START := 0
#CFLAGS += -D MULTI_MODEM_CONFIG
#CFLAGS += -D MULTI_MODEM_CONFIG_FILE=\"/etc/slqs-multi-config\"

#CFLAGS += -D DEBUG_IPC_MSG_FLAG
#CFLAGS += -D API_TIMEOUT
ifeq ($(AVMS_AUTO_START), 1)
	CFLAGS += -DAGENT_AUTO_START
endif
CFLAGS += -DDEBUG_LOG_TO_FILE
# disable muulti modem feature for platform not supporting shared memory api
# (shmget/shmat)
#CFLAGS += -DDISABLE_MULTI_MODEM

# Agent auto start enable, default disable
# CFLAGS += -DAGENT_AUTO_START

#memory map
#LDFLAGS += -Xlinker -Map=output.map

#-------------------------------------------------------------------------------
# DEBUG ON means the compiler should build for possible GDB debugging sessions
#
# Default is for no debugging which considerably reduces the size of the final
# image, especially when preparing a release for distribution
#
ifeq ($(SYMBOLS),ON)
  DBGFLAGS += -g
  CFLAGS += $(DBGFLAGS)
endif
###TEST INDICATION FLAG
#CFLAGS += -D TEST_NI_INDICATION

#-------------------------------------------------------------------------------
# if CPU is not specified, default to native host CPU: PC, PowerBook or
# Pandaboard, otherwise it has to be one of arm, ppc, mips, mipsel
#-------------------------------------------------------------------------------
ifndef CPU

#memory map
#LDFLAGS += -Xlinker -Map=output.map

  CPU:=host$(SLQSHOSTTYPE)
  UPPER_CPU:=$(CPU) # no need for uppercase here, 'host' to differentiate
#                         from conflicting cross-compile CPU defines
  CROSS_COMPILE :=
  SDK_EXE:=$(QMI_BUILD_BASE)/build/bin/$(CPU)/slqssdk
else
  UPPER_CPU:=$(shell echo $(CPU) | tr [a-z] [A-Z])
  SDK_EXE:=$(QMI_BUILD_BASE)/build/bin/$(CPU)/slqssdk

# 64bit host handling
ifeq ($(CPU),hostx86_64)
  CFLAGS += -m64
  LDFLAGS += -m64
endif

# 32bit host handling
ifeq ($(CPU),hosti686)
  CFLAGS += -m32 
  LDFLAGS += -m32
endif

# arm 32-bit compiler does not support eventfd.
ifeq ($(CPU),arm)
	#CFLAGS += -D_GNU_SOURCE -D_XOPEN_SOURCE=500 -D__USE_UNIX98
	CFLAGS += -D EVENT_FD_UNSUPPORTED -D_GNU_SOURCE -Wno-missing-field-initializers
endif


endif

CFLAGS += -D $(UPPER_CPU) -DSDK_EXE='"$(SDK_EXE)"'

#-------------------------------------------------------------------------------
# For arm, powerpc and MIPs, platform specific toolchains are used.
# These must be installed to the $(HOME) directory once and can be used for all
# SDK workspaces. If they do not exist,
#   make CPU=arm
#   make CPU=ppc
#   make CPU=mips
#   make CPU=mipsel
# will simply fail.
#-------------------------------------------------------------------------------
ifeq ($(CPU),arm)
  CROSS_COMPILE := $(HOME)/toolchain/arm/bin/arm-none-linux-gnueabi-
  INCLUDE       += -I$(HOME)/toolchain/arm/arm-none-linux-gnueabi/libc/usr/include
  LDFLAGS       += -L$(HOME)/toolchain/arm/lib/gcc/arm-none-linux-gnueabi/4.2.0/
  CFLAGS        += -march=armv5te
endif
# this is for backward compatibility
ifeq ($(CPU),arm9)
  CROSS_COMPILE := $(HOME)/toolchain/arm/bin/arm-none-linux-gnueabi-
  INCLUDE       += -I$(HOME)/toolchain/arm/arm-none-linux-gnueabi/libc/usr/include
  LDFLAGS       += -L$(HOME)/toolchain/arm/lib/gcc/arm-none-linux-gnueabi/4.2.0/
  CFLAGS        += -march=armv5te
endif
#
# If LTIB (Linux Target Image Build) is installed, use:
#  /opt/freescale/usr/local/gcc-4.3.74-eglibc-2.8.74-dp-2/powerpc-none-linux-gnuspe/
# otherwise if toolchain is available, use :
#  $(HOME)/toolchain/powerpc-none-linux-gnuspe
#
ifeq ($(CPU),ppc)
  CROSS_COMPILE := $(HOME)/toolchain/ppc/powerpc-none-linux-gnuspe/bin/powerpc-none-linux-gnuspe-
  INCLUDE       += -I$(HOME)/toolchain/ppc/powerpc-none-linux-gnuspe/powerpc-none-linux-gnuspe/libc/usr/include
  LDFLAGS       += -L$(HOME)/toolchain/ppc/powerpc-none-linux-gnuspe/powerpc-none-linux-gnuspe/libc/usr/lib
endif
#
# Download from:
# http://www.denx.de/wiki/view/ELDK-5/WebHome#Section_1.6.
#
ifeq ($(CPU),ppc_4xx)
  CROSS_COMPILE := $(HOME)/toolchain/ELDK/usr/bin/ppc_4xx-
  INCLUDE       := -I.. $(QMI_INCLUDE) -I$(HOME)/toolchain/ELDK/usr/lib/gcc/powerpc-linux/4.2.2/include
  INCLUDE       += -I$(HOME)/toolchain/ELDK/ppc_4xx/usr/include
  LDFLAGS       := -L$(HOME)/toolchain/ELDK/usr/lib -static -lrt -lpthread
  CFLAGS        += -D OS_NO_SSCANF
endif

#
# Downloaded from:
# http://www.mentor.com/embedded-software/sourcery-tools/sourcery-codebench/lite-edition
# Note: the original file is an installer file.
#       This is an unzipped tarballed copy of the installed files.
# Note: uclibc is used here. Some applications may need libc and is overridden
#       in the make file for those.
#
ifeq ($(CPU),mips)
  CROSS_COMPILE := $(HOME)/toolchain/mips/bin/mips-linux-gnu-
  INCLUDE       += -I$(HOME)/toolchain/mips/mips-linux-gnu/libc/uclibc/usr/include
  LDFLAGS       += -L$(HOME)/toolchain/mips/mips-linux-gnu/libc/uclibc/usr/lib
  LDFLAGS       += -L$(HOME)/toolchain/mips/mips-linux-gnu/libc/uclibc/lib -muclibc
  #default mips toolchain from Sourcery does not support sscanf
  CFLAGS        += -D OS_NO_SSCANF
  #define mips toochain from Sourcery does not support backtrace
  CFLAGS        += -D NO_BACKTRACE
  CFLAGS        += -D EVENT_FD_UNSUPPORTED        
endif 

ifeq ($(CPU),mipsel)
  CROSS_COMPILE := $(HOME)/toolchain/mips/bin/mips-linux-gnu-
#  INCLUDE       += -I$(HOME)/toolchain/mips/mips-linux-gnu/libc/ulibc/usr/include
  INCLUDE       += -I$(HOME)/toolchain/mips/mips-linux-gnu/libc/el/usr/include
  LDFLAGS       += -EL -static
  CFLAGS        += -EL
  #default mips toolchain from Sourcery does not support sscanf
  CFLAGS        += -D OS_NO_SSCANF
  #define mips toochain from Sourcery does not support backtrace
  CFLAGS        += -D NO_BACKTRACE
endif

ifeq ($(CPU),mipseb)
  CROSS_COMPILE := $(HOME)/toolchain/mips/bin/mips-linux-gnu-
#  INCLUDE       += -I$(HOME)/toolchain/mips/mips-linux-gnu/libc/ulibc/usr/include
  INCLUDE       += -I$(HOME)/toolchain/mips/mips-linux-gnu/libc/usr/include
#  LDFLAGS       += -L$(HOME)/toolchain/mips/mips-linux-gnu/libc/uclibc/lib -muclibc -EB
  CFLAGS        += -EB
  #default mips toolchain from Sourcery does not support sscanf
  CFLAGS        += -D OS_NO_SSCANF
  #define mips toochain from Sourcery does not support backtrace
  CFLAGS        += -D NO_BACKTRACE
endif

ifeq ($(CPU),rspro)
  CROSS_COMPILE := $(HOME)/rspro/openwrt-sdk-19.07.3-ar71xx-generic_gcc-7.5.0_musl.Linux-x86_64/staging_dir/toolchain-mips_24kc_gcc-7.5.0_musl/bin/mips-openwrt-linux-
#  INCLUDE       += -I$(HOME)/toolchain/mips/mips-linux-gnu/libc/ulibc/usr/include
  INCLUDE       += -I$(HOME)/rspro/openwrt-sdk-19.07.3-ar71xx-generic_gcc-7.5.0_musl.Linux-x86_64/staging_dir/toolchain-mips_24kc_gcc-7.5.0_musl/include
  LDFLAGS       += -EB -static
#  CFLAGS        += -EL
  #default mips toolchain from Sourcery does not support sscanf
#  CFLAGS        += -D OS_NO_SSCANF
  #define mips toochain from Sourcery does not support backtrace
  CFLAGS        += -D NO_BACKTRACE
#  CFLAGS        += -D_GNU_SOURCE
endif

#raspberry pi (https://github.com/raspberrypi/tools.git)
ifeq ($(CPU),rpi)
ARCH := $(shell getconf LONG_BIT)
CROSS_COMPILE_32 := $(HOME)/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin/arm-linux-gnueabihf-
CROSS_COMPILE_64 := $(HOME)/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-
#CROSS_COMPILE := $(CROSS_COMPILE_$(ARCH))
CROSS_COMPILE := $(CROSS_COMPILE_32)
endif

ifeq ($(CPU),arm64)
CROSS_COMPILE := /$(HOME)/toolchain/arm64bit/be/aarch64ebv8-marvell-linux-gnu-5.2.1_x86_64_20151117/bin/aarch64_be-marvell-linux-gnu-
endif

# linaro gcc-linaro-7.4.1-2019.02-x86_64_aarch64-linux-gnu.tar.xz
# from (http://releases.linaro.org/components/toolchain/binaries/7.4-2019.02/aarch64-linux-gnu/) 
ifeq ($(CPU),arm64linaro)
CROSS_COMPILE := /$(HOME)/toolchain/gcc-linaro-7.4.1-2019.02-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-
endif

# arm64le build for Digi
ifeq ($(CPU),arm64le)
STAGING_DIR := $(HOME)/toolchain/OpenWrt-Toolchain-ipq-ipq60xx_64_gcc-5.2.0_musl-1.1.16.Linux-x86_64/toolchain-aarch64_cortex-a53_gcc-5.2.0_musl-1.1.16/bin/
CROSS_COMPILE := $(HOME)/toolchain/OpenWrt-Toolchain-ipq-ipq60xx_64_gcc-5.2.0_musl-1.1.16.Linux-x86_64/toolchain-aarch64_cortex-a53_gcc-5.2.0_musl-1.1.16/bin/aarch64-openwrt-linux-musl-
endif

#GCC SYSTEM ROOT PATH
GCC_SYS_ROOT :=
ifdef SYS_ROOT
GCC_SYS_ROOT := $(SYS_ROOT)
CFLAGS += --sysroot=$(GCC_SYS_ROOT)
LDFLAGS += --sysroot=$(GCC_SYS_ROOT)
endif
ifdef SYS_INC
INCLUDE += -I$(SYS_INC)
endif
ifdef SYS_LIB
LDFLAGS += -L$(SYS_LIB) --sysroot=$(GCC_SYS_ROOT)
endif
# $(CROSS_COMPILE) is empty if not defined
ifndef VERBOSE
VERBOSE := 0
OUTPUT := /dev/null
else
OUTPUT := /dev/stdout
endif
NM_EXEC := $(CROSS_COMPILE)nm
ifeq ($(VERBOSE),0)
	CC := @$(CROSS_COMPILE)gcc
AR := @$(CROSS_COMPILE)ar
RANLIB := @$(CROSS_COMPILE)ranlib
NM := @$(CROSS_COMPILE)nm
OBJCOPY := @$(CROSS_COMPILE)objcopy
else
	CC := $(CROSS_COMPILE)gcc
AR := $(CROSS_COMPILE)ar
RANLIB := $(CROSS_COMPILE)ranlib
NM := $(CROSS_COMPILE)nm
OBJCOPY := $(CROSS_COMPILE)objcopy
endif
AR_VERSION := $(shell $(CROSS_COMPILE)ar --version | grep "ar " | sed 's/^.* //g' | sed -e 's/\.\([0-9][0-9]\)/\1/g' -e 's/\.\([0-9]\)/0\1/g')
AR_ARG := rv
BC := $(shell bc --help 2> /dev/null)
ifndef BC
AR_VERSION := $(shell echo $(AR_VERSION))
else
AR_VERSION := $(shell echo $(AR_VERSION) | bc)
endif
AR_VERSION := "134 ABC"
ifeq ($(shell test $(AR_VERSION) -gt 224 2>/dev/null; echo $$?),0)
AR_ARG := rv
endif
#

