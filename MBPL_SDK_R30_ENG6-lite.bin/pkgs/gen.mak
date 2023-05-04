#-------------------------------------------------------------------------------
#
#  Name:
#    gen.mak
#
#  Description:
#    Generic Makefile to build the pkgs/{package}
#
#   The following make targets are available in this makefile:
#
#     all           - make .o and .a image files (default). Test programs are
#                     also built when present
#     clean         - delete object directory and image files
#
#   This file is include with the {package}.mak files using
#
#     include ../gen.mak
#
#   If GDB is to be used, then run the make at the top level with SYMBOLS=ON
#   and this will cause the compiler to create symbolic information in the
#   object files
#
# Copyright (c) 2011-2018 by Sierra Wireless, Incorporated. All Rights Reserved
#-------------------------------------------------------------------------------
#.SUFFIXES:
#-------------------------------------------------------------------------------
ifndef QMI_BUILD_BASE
export QMI_BUILD_BASE:=$(shell until [ -d pkgs ]; do cd ..; done; pwd)
endif
SLQSHOSTTYPE := $(shell uname -m)
PARTIALLLY_BUILD := 1
ifeq ($(SLQSHOSTTYPE),x86_64)
PARTIALLLY_BUILD := 0
endif
ifeq ($(SLQSHOSTTYPE),i686)
PARTIALLLY_BUILD := 0
endif
include $(QMI_BUILD_BASE)/pkgs/slqscompile.mak
#-------------------------------------------------------------------------------
# Variable definitions
#-------------------------------------------------------------------------------
BUILDDIR        := $(QMI_BUILD_BASE)/build
OBJSDIR         := $(BUILDDIR)/obj/$(CPU)/pkgs/$(PKG)

BUILDLIBDIR     := $(BUILDDIR)/lib
CORELIBDIR      := $(BUILDLIBDIR)/$(CPU)
SDKLIBDIR       := $(BUILDLIBDIR)/pkgs/sdk/$(CPU)
DCSLIBDIR       := $(BUILDLIBDIR)/$(CPU)
WDSLIBDIR       := $(BUILDLIBDIR)/$(CPU)
SLQSAPILIBDIR   := $(BUILDLIBDIR)/$(CPU)
DMSLIBDIR       := $(BUILDLIBDIR)/$(CPU)
NASLIBDIR       := $(BUILDLIBDIR)/$(CPU)
CBKLIBDIR       := $(BUILDLIBDIR)/$(CPU)
CATLIBDIR       := $(BUILDLIBDIR)/$(CPU)
RMSLIBDIR       := $(BUILDLIBDIR)/$(CPU)
FMSLIBDIR       := $(BUILDLIBDIR)/$(CPU)
SMSLIBDIR       := $(BUILDLIBDIR)/$(CPU)
OMADMLIBDIR     := $(BUILDLIBDIR)/$(CPU)
SARLIBDIR       := $(BUILDLIBDIR)/$(CPU)
SWILIBDIR       := $(BUILDLIBDIR)/$(CPU)
UIMLIBDIR       := $(BUILDLIBDIR)/$(CPU)
QOSLIBDIR       := $(BUILDLIBDIR)/$(CPU)
IMSLIBDIR       := $(BUILDLIBDIR)/$(CPU)
QMILIBDIR       := $(BUILDLIBDIR)/$(CPU)
QMILITELIBDIR      := $(BUILDLIBDIR)/$(CPU)
LOCLIBDIR       := $(BUILDLIBDIR)/$(CPU)
IMSALIBDIR      := $(BUILDLIBDIR)/$(CPU)
TMDLIBDIR       := $(BUILDLIBDIR)/$(CPU)
TSLIBDIR        := $(BUILDLIBDIR)/$(CPU)
LITEQMUXDIR      := $(BUILDLIBDIR)/$(CPU)
LITEMBIMDIR      := $(BUILDLIBDIR)/$(CPU)
LITEFWDIR          := $(BUILDLIBDIR)/$(CPU)
SWIDMSLIBDIR    := $(BUILDLIBDIR)/$(CPU)
SWINASLIBDIR    := $(BUILDLIBDIR)/$(CPU)
CTLLIBDIR       := $(BUILDLIBDIR)/$(CPU)
DSDLIBDIR       := $(BUILDLIBDIR)/$(CPU)
WDALIBDIR       := $(BUILDLIBDIR)/$(CPU)
COMMONLIBDIR   := $(BUILDLIBDIR)/$(CPU)

CORELIB         := $(CORELIBDIR)/libslqscore.a
SDKLIB          := $(SDKLIBDIR)/libslqssdk.a
SLQSAPILIB      := $(SLQSAPILIBDIR)/libslqsapi.a

LITEQMUXLIB          := $(LITEQMUXDIR)/liblite-qmux.a
LITEQMUXLIBSYMAPI   := $(LITEQMUXDIR)/liblite-qmux_sym_api_tmp
LITEQMUXLIBSYMDEF   := $(LITEQMUXDIR)/liblite-qmux_sym_def_tmp
LITEQMUXLIBSYMNS    := $(LITEQMUXDIR)/liblite-qmux_sym_ns_tmp
LITEQMUXLIBNAMESPACE := SWISDKLITEQMUX_

LITEMBIMLIB          := $(LITEMBIMDIR)/liblite-mbim.a
LITEMBIMLIBSYMAPI   := $(LITEMBIMDIR)/liblite-mbim_sym_api_tmp
LITEMBIMLIBSYMDEF   := $(LITEMBIMDIR)/liblite-mbim_sym_def_tmp
LITEMBIMLIBSYMNS    := $(LITEMBIMDIR)/liblite-mbim_sym_ns_tmp
LITEMBIMLIBNAMESPACE := SWISDKLITEMBIM_

LITEFWLIB          := $(LITEFWDIR)/liblite-fw.a
LITEFWLIBSYMAPI   := $(LITEFWDIR)/liblite-fw_sym_api_tmp
LITEFWLIBSYMDEF   := $(LITEFWDIR)/liblite-fw_sym_def_tmp
LITEFWLIBSYMNS    := $(LITEFWDIR)/liblite-fw_sym_ns_tmp
LITEFWLIBNAMESPACE := SWISDKLITEFW_

#
# QMI Services libraries
#
DCSLIB          := $(DCSLIBDIR)/libdcs.a
WDSLIB          := $(WDSLIBDIR)/libwds.a
WDALIB          := $(WDALIBDIR)/libwda.a
DMSLIB          := $(DMSLIBDIR)/libdms.a
NASLIB          := $(NASLIBDIR)/libnas.a
CBKLIB          := $(CBKLIBDIR)/libcbk.a
CATLIB          := $(CATLIBDIR)/libcat.a
RMSLIB          := $(RMSLIBDIR)/librms.a
FMSLIB          := $(FMSLIBDIR)/libfms.a
SMSLIB          := $(SMSLIBDIR)/libsms.a
OMADMLIB        := $(OMADMLIBDIR)/libomadm.a
SARLIB          := $(SARLIBDIR)/libsar.a
UIMLIB          := $(UIMLIBDIR)/libuim.a
IMSLIB          := $(IMSLIBDIR)/libims.a
LOCLIB          := $(LOCLIBDIR)/libloc.a
IMSALIB         := $(IMSALIBDIR)/libimsa.a
TMDLIB          := $(TMDLIBDIR)/libtmd.a
TSLIB          := $(TSLIBDIR)/libts.a

SWILIB          := $(SWILIBDIR)/libswi.a
QOSLIB          := $(SWILIBDIR)/libqos.a
SWIDMSLIB       := $(SWIDMSLIBDIR)/libswidms.a
SWINASLIB       := $(SWINASLIBDIR)/libswinas.a
CTLLIB          := $(CTLLIBDIR)/libswictl.a
DSDLIB          := $(DSDLIBDIR)/libdsd.a
COMMONLIB        := $(COMMONLIBDIR)/libcommon.a

INCLUDE += -I $(QMI_BUILD_BASE)/pkgs/common \
	-I $(QMI_BUILD_BASE)/pkgs/lite-qmux \
	-I $(QMI_BUILD_BASE)/pkgs/qm \
	-I $(QMI_BUILD_BASE)/pkgs/lite-qmi

#
# Sum of all QMI Services
#
QMILIB          := $(QMILIBDIR)/libslqsqmi.a
LITEQMILIB         := $(QMILITELIBDIR)/liblite-qmi.a
LITEQMILIBSYMAPI   := $(QMILITELIBDIR)/liblite-qmi_sym_api_tmp
LITEQMILIBSYMDEF   := $(QMILITELIBDIR)/liblite-qmi_sym_def_tmp
LITEQMILIBSYMNS    := $(QMILITELIBDIR)/liblite-qmi_sym_ns_tmp
LITEQMILIBNAMESPACE := SWISDKLITE_

# -------------------------------------------------------
# Build required programs, $(CPU)/slqssdk and qatest$(CPU)
#--------------------------------------------------------
TESTSRC = $(PKG)test.c
have_testsrc := $(wildcard $(TESTSRC))
ifeq ($(strip $(have_testsrc)),sdktest.c)
TESTOBJ = $(OBJSDIR)/$(PKG)test.o
TESTEXE = $(CPU)/slqs$(PKG)
endif
#
# extract current directory name for special processing of some files
#
CURRENT_DIR = $(notdir $(PWD))
#
#-------------------------------------------------------------------------------
# Default Target
#-------------------------------------------------------------------------------
all:	$(OBJS)\
$(CORELIB) $(SDKLIB)  \
$(LITEFWLIB) \
$(DCSLIB) \
$(WDSLIB) \
$(WDALIB) \
$(DMSLIB) \
$(NASLIB) \
$(CBKLIB) \
$(CATLIB) \
$(RMSLIB) \
$(FMSLIB) \
$(SMSLIB) \
$(OMADMLIB) \
$(SARLIB) \
$(SWILIB) \
$(UIMLIB) \
$(IMSLIB) \
$(QOSLIB) \
$(LOCLIB) \
$(IMSALIB) \
$(TMDLIB) \
$(TSLIB) \
$(QMILIB) \
$(LITEQMILIB) \
$(LITEQMUXLIB) \
$(LITEMBIMLIB) \
$(SLQSAPILIB) \
$(SWIDMSLIB) \
$(SWINASLIB) \
$(CTLLIB) \
$(DSDLIB) \
$(COMMONLIB) \
$(TESTEXE) $(SDKTESTEXE) $(APITESTEXE)

$(OBJS): $(OBJSDIR)/%.o:%.c $(HDRS)
ifeq ($(VERBOSE),0)
	@echo "--- Building $(basename $<)"
else
	@echo "QMI Build base: $(QMI_BUILD_BASE)"
	@echo $(INCLUDE) $(LDFLAGS)
	@echo "============================"
	@echo "--- Building  $(PKG) for $(CPU)..."
	@echo "----------------------------"
endif
	@if [ ! -d $(OBJSDIR) ] ; then mkdir -p $(OBJSDIR) ; fi;
ifeq ($(DEF_ULONG_AS_EIGHT_BYTES_ON_64BIT),1)
	$(CC) $(CFLAGS) -DLITEQMI=1 -DULONG_AS_EIGHT_BYTES_ON_64BIT $(SLQSFLAG) $(INCLUDE) $< -o $@ 
else
	$(CC) $(CFLAGS) -DLITEQMI=1 $(SLQSFLAG) $(INCLUDE) $< -o $@ 
endif

#--
# When timestamp resolution is in seconds, it is possible that refreshly compiled object files
# has the same timestamp as target library.
# Ref: http://www.gnu.org/software/autoconf/manual/autoconf-2.64/html_node/Timestamps-and-Make.html
# Force archiving work around this issue
#--
.PHONY: $(CORELIB) $(SDKLIB) $(SLQSAPILIB) $(LITEQMILIB) $(LITEQMUXLIB) $(LITEQMILIB) $(LITEFWLIB)

$(CORELIB): $(COMMONOBJ) $(COREOBJ)
ifeq ($(VERBOSE),0)
	@echo "--- Archiving  $(CORELIB)..."
else
	@echo "--------------------------------------------"
	@echo "--- Archiving $(COREOBJ) to $(CORELIB)..."
	@echo "--------------------------------------------"
endif
	@if [ ! -d $(CORELIBDIR) ] ; then mkdir -p $(CORELIBDIR) ; fi;
	$(AR) $(AR_ARG) $(CORELIB) $(COMMONOBJ) > $(OUTPUT) || (echo "AR $(CORELIB) $$?"; exit 1)
	$(AR) $(AR_ARG) $(CORELIB) $(COREOBJ) > $(OUTPUT) || (echo "AR $(CORELIB) $$?"; exit 1)
	$(RANLIB) $(CORELIB) || (echo "RNLIB $(CORELIB) $$?"; exit 1)

$(SDKLIB): $(SDKOBJ)
ifeq ($(VERBOSE),0)
	@echo "--- Archiving $(SDKLIB)..."
else
	@echo "--------------------------------------------"
	@echo "--- Archiving $(SDKOBJ) to $(SDKLIB)..."
	@echo "--------------------------------------------"
endif
	@if [ ! -d $(SDKLIBDIR) ] ; then mkdir -p $(SDKLIBDIR) ; fi;
	$(AR) $(AR_ARG) $(SDKLIB) $(SDKOBJ) > $(OUTPUT) || (echo "AR $(SDKLIB) $$?"; exit 1)
	$(RANLIB) $(SDKLIB) || (echo "RANLIB $(SDKLIB) $$?"; exit 1)

$(LITEQMUXLIB): $(COREOBJ) $(SDKOBJ) $(CBKOBJ) $(LITEQMUXOBJS)
ifeq ($(VERBOSE),0)
	@echo "--- Archiving $(LITEQMUXLIB)..."
else
	@echo "--------------------------------------------"
	@echo "--- Archiving $(LITEQMUXOBJS) to $(LITEQMUXLIB)..."
	@echo "--------------------------------------------"
endif
	@if [ ! -d $(LITEQMUXDIR) ] ; then mkdir -p $(LITEQMUXDIR) ; fi;
	@echo $(LITEQMUXOBJS)
	$(AR) $(AR_ARG) $(LITEQMUXLIB) $(COREOBJ) $(SDKOBJ) $(LITEQMUXOBJS) > $(OUTPUT) || (echo "AR $(LITEQMUXLIB) $$?"; exit 1)
	$(RANLIB) $(LITEQMUXLIB) || (echo "RANLIB $(LITEQMUXLIB) $$?"; exit 1)
ifeq ($(LITEQMI),1)
ifeq ($(PKG),lite-qmux)
	echo "--- Applying namespace prefix for $(LITEQMUXLIB)...";
	$(NM) -g --defined-only -fp $(OBJSDIR)/../lite-qmux/QmuxTransport.o $(OBJSDIR)/../lite-qmux/QmiService.o \
		$(OBJSDIR)/../lite-qmux/QmiTransaction.o $(OBJSDIR)/../lite-qmux/QmiSyncObject.o \
		$(OBJSDIR)/../lite-qmux/CtlService.o $(OBJSDIR)/../lite-qmux/QmuxLogging.o | \
		sed -ne 's/^\([^ ]*\).*[^:]$$/^\1'/p | \
		sort | uniq > $(LITEQMUXLIBSYMAPI)

	$(NM) -g --defined-only -fp $(LITEQMUXLIB) | \
		sed -ne 's/^\([^ ]*\).*[^:]$$/^^\1'/p | \
		sort | uniq > $(LITEQMUXLIBSYMDEF)

	$(NM) -g --undefined-only -fp $(LITEQMUXLIB) | \
		sed -ne 's/^\([^ ]*\).*[^:]$$/^\1'/p | \
		sort | uniq | \
		grep -v -f $(LITEQMUXLIBSYMDEF) >> $(LITEQMUXLIBSYMAPI)
# Create symbol redefinition file containing all global symbols from lite-qmi library
# that require namespace prefix. Exclude symbols from pattern match file
	$(NM) -g -fp $(LITEQMUXLIB) | \
		sed -ne 's/^\([^ ]*\).*[^:]$$/\1 $(LITEQMUXLIBNAMESPACE)\1'/p | \
		grep -v -f $(LITEQMUXLIBSYMAPI) | \
		sort | uniq > $(LITEQMUXLIBSYMNS)
# Apply namespace prefix to symbols in library
	$(OBJCOPY) --redefine-syms=$(LITEQMUXLIBSYMNS) $(LITEQMUXLIB)
endif
endif


$(LITEMBIMLIB): $(COREOBJ) $(SDKOBJ) $(CBKOBJ) $(LITEMBIMOBJS)
ifeq ($(VERBOSE),0)
	@echo "--- Archiving $(LITEMBIMLIB)..."
else
	@echo "--------------------------------------------"
	@echo "--- Archiving $(LITEMBIMOBJS) to $(LITEMBIMLIB)..."
	@echo "--------------------------------------------"
endif
	@if [ ! -d $(LITEMBIMDIR) ] ; then mkdir -p $(LITEMBIMDIR) ; fi;
	@echo $(LITEMBIMOBJS)
	$(AR) $(AR_ARG) $(LITEMBIMLIB) $(COREOBJ) $(SDKOBJ) $(LITEMBIMOBJS) > $(OUTPUT) || (echo "AR $(LITEMBIMLIB) $$?"; exit 1)
	$(RANLIB) $(LITEMBIMLIB) || (echo "RANLIB $(LITEMBIMLIB) $$?"; exit 1)
ifeq ($(LITEQMI),1)
ifeq ($(PKG),lite-mbim)
	echo "--- Applying namespace prefix for $(LITEMBIMLIB)...";
	$(NM) -g --defined-only -fp $(OBJSDIR)/../lite-mbim/MbimTransport.o $(OBJSDIR)/../lite-mbim/MbimTransaction.o \
		 $(OBJSDIR)/../lite-mbim/MbimIndicator.o $(OBJSDIR)/../lite-mbim/MbimSyncObject.o \
		 $(OBJSDIR)/../lite-mbim/BasicConnectDeviceService.o $(OBJSDIR)/../lite-mbim/MbimLogging.o |\
		sed -ne 's/^\([^ ]*\).*[^:]$$/^\1'/p | \
		sort | uniq > $(LITEMBIMLIBSYMAPI)

	$(NM) -g --defined-only -fp $(LITEMBIMLIB) | \
		sed -ne 's/^\([^ ]*\).*[^:]$$/^^\1'/p | \
		sort | uniq > $(LITEMBIMLIBSYMDEF)

	$(NM) -g --undefined-only -fp $(LITEMBIMLIB) | \
		sed -ne 's/^\([^ ]*\).*[^:]$$/^\1'/p | \
		sort | uniq | \
		grep -v -f $(LITEMBIMLIBSYMDEF) >> $(LITEMBIMLIBSYMAPI)
# Create symbol redefinition file containing all global symbols from lite-mbim library
# that require namespace prefix. Exclude symbols from pattern match file
	$(NM) -g -fp $(LITEMBIMLIB) | \
		sed -ne 's/^\([^ ]*\).*[^:]$$/\1 $(LITEMBIMLIBNAMESPACE)\1'/p | \
		grep -v -f $(LITEMBIMLIBSYMAPI) | \
		sort | uniq > $(LITEMBIMLIBSYMNS)
# Apply namespace prefix to symbols in library
	$(OBJCOPY) --redefine-syms=$(LITEMBIMLIBSYMNS) $(LITEMBIMLIB)
endif
endif


$(LITEFWLIB): $(COREOBJ) $(SDKOBJ) $(CBKOBJ) $(LITEFWOBJS)
ifeq ($(VERBOSE),0)
	@echo "--- Archiving $(LITEFWLIB)..."
else
	@echo "--------------------------------------------"
	@echo "--- Archiving $(LITEFWOBJS) to $(LITEFWLIB)..."
	@echo "--------------------------------------------"
endif
	@if [ ! -d $(LITEFWDIR) ] ; then mkdir -p $(LITEFWDIR) ; fi;
	@echo $(LITEFWOBJS)
	$(AR) $(AR_ARG) $(LITEFWLIB) $(COREOBJ) $(SDKOBJ) $(LITEFWOBJS) > $(OUTPUT) || (echo "AR $(LITEFWLIB) $$?"; exit 1)
	$(RANLIB) $(LITEFWLIB) || (echo "RANLIB $(LITEFWLIB) $$?"; exit 1)
ifeq ($(PKG),lite-fw)
	@echo "--- Applying namespace prefix for $(LITEFWLIB)...";
	$(NM) -g --defined-only -fp $(OBJSDIR)/../lite-fw/lite-fw.o $(OBJSDIR)/../lite-fw/utils.o | \
		sed -ne 's/^\([^ ]*\).*[^:]$$/^\1'/p | \
		sort | uniq > $(LITEFWLIBSYMAPI)

	$(NM) -g --defined-only -fp $(LITEFWLIB) | \
		sed -ne 's/^\([^ ]*\).*[^:]$$/^^\1'/p | \
		sort | uniq > $(LITEFWLIBSYMDEF)

	$(NM) -g --undefined-only -fp $(LITEFWLIB) | \
		sed -ne 's/^\([^ ]*\).*[^:]$$/^\1'/p | \
		sort | uniq | \
		grep -v -f $(LITEFWLIBSYMDEF) >> $(LITEFWLIBSYMAPI)
# Create symbol redefinition file containing all global symbols from lite-qmi library
# that require namespace prefix. Exclude symbols from pattern match file
	$(NM) -g -fp $(LITEFWLIB) | \
		sed -ne 's/^\([^ ]*\).*[^:]$$/\1 $(LITEFWLIBNAMESPACE)\1'/p | \
		grep -v -f $(LITEFWLIBSYMAPI) | \
		sort | uniq > $(LITEFWLIBSYMNS)
# Apply namespace prefix to symbols in library
	$(OBJCOPY) --redefine-syms=$(LITEFWLIBSYMNS) $(LITEFWLIB)
endif

$(DCSLIB): $(SDKOBJ) $(LIBSDKOBJS) $(DCSOBJ)
ifeq ($(VERBOSE),0)
	@echo "--- Archiving $(DCSLIB)..."
else
	@echo "--------------------------------------------"
	@echo "--- Archiving $(DCSOBJ) to $(DCSLIB)..."
	@echo "--------------------------------------------"
endif
	@if [ ! -d $(DCSLIBDIR) ] ; then mkdir -p $(DCSLIBDIR) ; fi;
	$(AR) $(AR_ARG) $(DCSLIB) $(DCSOBJ)  > $(OUTPUT) || (echo "AR $(DCSLIB) $$?"; exit 1)
	$(RANLIB) $(DCSLIB) || (echo "RANLIB $(DCSLIB) $$?"; exit 1)

$(WDSLIB): $(WDSOBJ)
ifeq ($(VERBOSE),0)
	@echo "--- Archiving $(WDSLIB)..."
else
	@echo "--------------------------------------------"
	@echo "--- Archiving $(WDSOBJ) to $(WDSLIB)..."
	@echo "--------------------------------------------"
endif
	@if [ ! -d $(WDSLIBDIR) ] ; then mkdir -p $(WDSLIBDIR) ; fi;
	$(AR) $(AR_ARG) $(WDSLIB)  $(WDSOBJ) > $(OUTPUT) || (echo "AR $(WDSLIB) $$?"; exit 1)
	$(RANLIB) $(WDSLIB) || (echo "RANLIB $(WDSLIB) $$?"; exit 1)

$(WDALIB): $(WDAOBJ)
ifeq ($(VERBOSE),0)
	@echo "--- Archiving $(WDALIB)..."
else
	@echo "--------------------------------------------"
	@echo "--- Archiving $(WDAOBJ) to $(WDALIB)..."
	@echo "--------------------------------------------"
endif
	@if [ ! -d $(WDALIBDIR) ] ; then mkdir -p $(WDALIBDIR) ; fi;
	$(AR) $(AR_ARG) $(WDALIB)  $(WDAOBJ) > $(OUTPUT) || (echo "AR $(WDALIB) $$?"; exit 1)
	$(RANLIB) $(WDALIB) || (echo "RANLIB $(WDALIB) $$?"; exit 1)

$(DMSLIB): $(DMSOBJ)
ifeq ($(VERBOSE),0)
	@echo "--- Archiving $(DMSLIB)..."
else
	@echo "--------------------------------------------"
	@echo "--- Archiving $(DMSOBJ) to $(DMSLIB)..."
	@echo "--------------------------------------------"
endif
	@if [ ! -d $(DMSLIBDIR) ] ; then mkdir -p $(DMSLIBDIR) ; fi;
	$(AR) $(AR_ARG) $(DMSLIB) $(DMSOBJ) > $(OUTPUT) || (echo "AR $(DMSLIBDIR) $$?"; exit 1)
	$(RANLIB) $(DMSLIB) || (echo "RANLIB $(DMSLIB) $$?"; exit 1)

$(NASLIB): $(NASOBJ)
ifeq ($(VERBOSE),0)
	@echo "--- Archiving $(NASLIB)..."
else
	@echo "--------------------------------------------"
	@echo "--- Archiving $(NASOBJ) to $(NASLIB)..."
	@echo "--------------------------------------------"
endif
	@if [ ! -d $(NASLIBDIR) ] ; then mkdir -p $(NASLIBDIR) ; fi;
	$(AR) $(AR_ARG) $(NASLIB) $(NASOBJ) > $(OUTPUT) || (echo "AR $(NASLIB) $$?"; exit 1)
	$(RANLIB) $(NASLIB) || (echo "RANLIB $(NASLIB) $$?"; exit 1)

$(CBKLIB): $(CBKOBJ)
ifeq ($(VERBOSE),0)
	@echo "--- Archiving $(CBKLIB)..."
else
	@echo "--------------------------------------------"
	@echo "--- Archiving $(CBKOBJ) to $(CBKLIB)..."
	@echo "--------------------------------------------"
endif
	@if [ ! -d $(CBKLIBDIR) ] ; then mkdir -p $(CBKLIBDIR) ; fi;
	$(AR) $(AR_ARG) $(CBKLIB) $(CBKOBJ) > $(OUTPUT) || (echo "AR $(CBKLIB) $$?"; exit 1)
	$(RANLIB) $(CBKLIB) || (echo "RANLIB $(CBKLIB) $$?"; exit 1)

$(RMSLIB): $(RMSOBJ)
ifeq ($(VERBOSE),0)
	@echo "--- Archiving $(RMSLIB)..."
else
	@echo "--------------------------------------------"
	@echo "--- Archiving $(RMSOBJ) to $(RMSLIB)..."
	@echo "--------------------------------------------"
endif
	@if [ ! -d $(RMSLIBDIR) ] ; then mkdir -p $(RMSLIBDIR) ; fi;
	$(AR) $(AR_ARG) $(RMSLIB) $(RMSOBJ) > $(OUTPUT) || (echo "AR $(RMSLIB) $$?"; exit 1)
	$(RANLIB) $(RMSLIB) || (echo "RANLIB $(RMSLIB) $$?"; exit 1)

$(CATLIB): $(CATOBJ)
ifeq ($(VERBOSE),0)
	@echo "--- Archiving $(CATLIB)..."
else
	@echo "--------------------------------------------"
	@echo "--- Archiving $(CATOBJ) to $(CATLIB)..."
	@echo "--------------------------------------------"
endif
	@if [ ! -d $(CATLIBDIR) ] ; then mkdir -p $(CATLIBDIR) ; fi;
	$(AR) $(AR_ARG) $(CATLIB) $(CATOBJ) > $(OUTPUT) || (echo "AR $(CATLIB) $$?"; exit 1)
	$(RANLIB) $(CATLIB) || (echo "RANLIB $(CATLIB) $$?"; exit 1)

$(FMSLIB): $(FMSOBJ)
ifeq ($(VERBOSE),0)
	@echo "--- Archiving $(FMSLIB)..."
else
	@echo "--------------------------------------------"
	@echo "--- Archiving $(FMSOBJ) to $(FMSLIB)..."
	@echo "--------------------------------------------"
endif
	@if [ ! -d $(FMSLIBDIR) ] ; then mkdir -p $(FMSLIBDIR) ; fi;
	$(AR) $(AR_ARG) $(FMSLIB) $(FMSOBJ) > $(OUTPUT) || (echo "AR $(FMSLIB) $$?"; exit 1)
	$(RANLIB) $(FMSLIB) || (echo "RANLIB $(FMSLIB) $$?"; exit 1)

$(SMSLIB): $(SMSOBJ)
ifeq ($(VERBOSE),0)
	@echo "--- Archiving $(SMSLIB)..."
else
	@echo "--------------------------------------------"
	@echo "--- Archiving $(SMSOBJ) to $(SMSLIB)..."
	@echo "--------------------------------------------"
endif
	@if [ ! -d $(SMSLIBDIR) ] ; then mkdir -p $(SMSLIBDIR) ; fi;
	$(AR) $(AR_ARG) $(SMSLIB) $(SMSOBJ) > $(OUTPUT) || (echo "AR $(SMSLIB) $$?"; exit 1)
	$(RANLIB) $(SMSLIB) > $(OUTPUT)|| (echo "RANLIB $(SMSLIB) $$?"; exit 1)

$(OMADMLIB): $(OMADMOBJ)
ifeq ($(VERBOSE),0)
	@echo "--- Archiving $(OMADMLIB)..."
else
	@echo "--------------------------------------------"
	@echo "--- Archiving $(OMADMOBJ) to $(OMADMLIB)..."
	@echo "--------------------------------------------"
endif
	@if [ ! -d $(OMADMLIBDIR) ] ; then mkdir -p $(OMADMLIBDIR) ; fi;
	$(AR) $(AR_ARG) $(OMADMLIB) $(OMADMOBJ) > $(OUTPUT) || (echo "AR $(OMADMLIB) $$?"; exit 1)
	$(RANLIB) $(OMADMLIB) || (echo "RANLIB $(OMADMLIB) $$?"; exit 1)

$(SARLIB): $(SAROBJ)
ifeq ($(VERBOSE),0)
	@echo "--- Archiving $(SARLIB)..."
else
	@echo "--------------------------------------------"
	@echo "--- Archiving $(SAROBJ) to $(SARLIB)..."
	@echo "--------------------------------------------"
endif
	@if [ ! -d $(SARLIBDIR) ] ; then mkdir -p $(SARLIBDIR) ; fi;
	$(AR) $(AR_ARG) $(SARLIB) $(SAROBJ) > $(OUTPUT) || (echo "AR $(SARLIB) $$?"; exit 1)
	$(RANLIB) $(SARLIB) || (echo "RANLIB $(SARLIB) $$?"; exit 1)

$(SWILIB): $(SWIOBJ)
ifeq ($(VERBOSE),0)
	@echo "--- Archiving $(SWILIB)..."
else
	@echo "--------------------------------------------"
	@echo "--- Archiving $(SWIOBJ) to $(SWILIB)..."
	@echo "--------------------------------------------"
endif
	@if [ ! -d $(SWILIBDIR) ] ; then mkdir -p $(SWILIBDIR) ; fi;
	$(AR) $(AR_ARG) $(SWILIB) $(SWIOBJ) > $(OUTPUT) || (echo "AR $(SWILIB) $$?"; exit 1)
	$(RANLIB) $(SWILIB) || (echo "RANLIB $(SWILIB) $$?"; exit 1)

$(UIMLIB): $(UIMOBJ)
ifeq ($(VERBOSE),0)
	@echo "--- Archiving $(UIMLIB)..."
else
	@echo "--------------------------------------------"
	@echo "--- Archiving $(UIMOBJ) to $(UIMLIB)..."
	@echo "--------------------------------------------"
endif
	@if [ ! -d $(UIMLIBDIR) ] ; then mkdir -p $(UIMLIBDIR) ; fi;
	$(AR) $(AR_ARG) $(UIMLIB) $(UIMOBJ) > $(OUTPUT) || (echo "AR $(UIMLIB) $$?"; exit 1)
	$(RANLIB) $(UIMLIB) || (echo "RANLIB $(UIMLIB) $$?"; exit 1)

$(IMSLIB): $(IMSOBJ)
ifeq ($(VERBOSE),0)
	@echo "--- Archiving $(IMSLIB)..."
else
	@echo "--------------------------------------------"
	@echo "--- Archiving $(IMSOBJ) to $(IMSLIB)..."
	@echo "--------------------------------------------"
endif
	@if [ ! -d $(IMSLIBDIR) ] ; then mkdir -p $(IMSLIBDIR) ; fi;
	$(AR) $(AR_ARG) $(IMSLIB) $(IMSOBJ) > $(OUTPUT) || (echo "AR $(IMSLIB) $$?"; exit 1)
	$(RANLIB) $(IMSLIB) || (echo "RANLIB $(IMSLIB) $$?"; exit 1)

$(QOSLIB): $(QOSOBJ)
ifeq ($(VERBOSE),0)
	@echo "--- Archiving $(QOSLIB)..."
else
	@echo "--------------------------------------------"
	@echo "--- Archiving $(QOSOBJ) to $(QOSLIB)..."
	@echo "--------------------------------------------"
endif
	@if [ ! -d $(LIBDIR) ] ; then mkdir -p $(QOSLIBDIR) ; fi;
	$(AR) $(AR_ARG) $(QOSLIB) $(QOSOBJ) > $(OUTPUT) || (echo "AR $(QOSLIB) $$?"; exit 1)
	$(RANLIB) $(QOSLIB) || (echo "RANLIB $(QOSLIB) $$?"; exit 1)

$(LOCLIB): $(LOCOBJ)
ifeq ($(VERBOSE),0)
	@echo "--- Archiving $(LOCLIB)..."
else
	@echo "--------------------------------------------"
	@echo "--- Archiving $(LOCOBJ) to $(LOCLIB)..."
	@echo "--------------------------------------------"
endif
	@if [ ! -d $(LOCLIBDIR) ] ; then mkdir -p $(LOCLIBDIR) ; fi;
	$(AR) $(AR_ARG) $(LOCLIB) $(LOCOBJ) > $(OUTPUT) || (echo "AR $(LOCLIB) $$?"; exit 1)
	$(RANLIB) $(LOCLIB) || (echo "RANLIB $(LOCLIB) $$?"; exit 1)

$(IMSALIB): $(IMSAOBJ)
ifeq ($(VERBOSE),0)
	@echo "--- Archiving $(IMSALIB)..."
else
	@echo "--------------------------------------------"
	@echo "--- Archiving $(IMSAOBJ) to $(IMSALIB)..."
	@echo "--------------------------------------------"
endif
	@if [ ! -d $(IMSALIBDIR) ] ; then mkdir -p $(IMSALIBDIR) ; fi;
	$(AR) $(AR_ARG) $(IMSALIB) $(IMSAOBJ) > $(OUTPUT) || (echo "AR $(IMSALIB) $$?"; exit 1)
	$(RANLIB) $(IMSALIB) || (echo "RANLIB $(IMSALIB) $$?"; exit 1)

$(TMDLIB): $(TMDOBJ)
ifeq ($(VERBOSE),0)
	@echo "--- Archiving $(TMDLIB)..."
else
	@echo "--------------------------------------------"
	@echo "--- Archiving $(TMDOBJ) to $(TMDLIB)..."
	@echo "--------------------------------------------"
endif
	@if [ ! -d $(TMDLIBDIR) ] ; then mkdir -p $(TMDLIBDIR) ; fi;
	$(AR) $(AR_ARG) $(TMDLIB) $(TMDOBJ) > $(OUTPUT) || (echo "AR $(TMDLIB) $$?"; exit 1)
	$(RANLIB) $(TMDLIB) || (echo "RANLIB $(TMDLIB) $$?"; exit 1)

$(TSLIB): $(TSOBJ)
ifeq ($(VERBOSE),0)
	@echo "--- Archiving $(TSLIB)..."
else
	@echo "--------------------------------------------"
	@echo "--- Archiving $(TSOBJ) to $(TSLIB)..."
	@echo "--------------------------------------------"
endif
	@if [ ! -d $(TSLIBDIR) ] ; then mkdir -p $(TSLIBDIR) ; fi;
	$(AR) $(AR_ARG) $(TSLIB) $(TSOBJ) > $(OUTPUT) || (echo "AR $(TSLIB) $$?"; exit 1)
	$(RANLIB) $(TSLIB) || (echo "RANLIB $(TSLIB) $$?"; exit 1)

$(COMMONLIB): $(COMMONOBJ)
ifeq ($(VERBOSE),0)
	@echo "--- Archiving $(COMMONLIB)..."
	@echo "%%% $(COMMONOBJ)"
else
	@echo "--------------------------------------------"
	@echo "--- Archiving $(COMMONOBJ) to $(COMMONLIB)..."
	@echo "--------------------------------------------"
endif
	@if [ ! -d $(CBKLIBDIR) ] ; then mkdir -p $(CBKLIBDIR) ; fi;
	$(AR) $(AR_ARG) $(COMMONLIB) $(COMMONOBJ) > $(OUTPUT) || (echo "AR $(COMMONLIB) $$?"; exit 1)
	$(RANLIB) $(COMMONLIB) || (echo "RANLIB $(COMMONLIB) $$?"; exit 1)	

$(SWIDMSLIB): $(SWIDMSOBJ)
ifeq ($(VERBOSE),0)
	@echo "--- Archiving $(SWIDMSLIB)..."
else
	@echo "--------------------------------------------"
	@echo "--- Archiving $(SWIDMSOBJ) to $(SWIDMSLIB)..."
	@echo "--------------------------------------------"
endif
	@if [ ! -d $(SWIDMSLIBDIR) ] ; then mkdir -p $(SWIDMSLIBDIR) ; fi;
	$(AR) $(AR_ARG) $(SWIDMSLIB) $(SWIDMSOBJ) > $(OUTPUT) || (echo "AR $(SWIDMSLIB) $$?"; exit 1)
	$(RANLIB) $(SWIDMSLIB) || (echo "RANLIB $(SWIDMSLIB) $$?"; exit 1)

$(SWINASLIB): $(SWINASOBJ)
ifeq ($(VERBOSE),0)
	@echo "--- Archiving $(SWINASLIB)..."
else
	@echo "--------------------------------------------"
	@echo "--- Archiving $(SWINASOBJ) to $(SWINASLIB)..."
	@echo "--------------------------------------------"
endif
	@if [ ! -d $(SWINASLIBDIR) ] ; then mkdir -p $(SWINASLIBDIR) ; fi;
	$(AR) $(AR_ARG) $(SWINASLIB) $(SWINASOBJ) > $(OUTPUT) || (echo "AR $(SWINASLIB) $$?"; exit 1)
	$(RANLIB) $(SWINASLIB) || (echo "RANLIB $(SWINASLIB) $$?"; exit 1)
	
$(CTLLIB): $(CTLOBJ)
ifeq ($(VERBOSE),0)
	@echo "--- Archiving $(CTLLIB)..."
else
	@echo "--------------------------------------------"
	@echo "--- Archiving $(CTLOBJ) to $(CTLLIB)..."
	@echo "--------------------------------------------"
endif
	@if [ ! -d $(CTLLIBDIR) ] ; then mkdir -p $(CTLLIBDIR) ; fi;
	$(AR) $(AR_ARG) $(CTLLIB) $(CTLOBJ) > $(OUTPUT) || (echo "AR $(CTLLIB) $$?"; exit 1)
	$(RANLIB) $(CTLLIB) || (echo "RANLIB $(CTLLIB) $$?"; exit 1)

$(DSDLIB): $(DSDOBJ)
ifeq ($(VERBOSE),0)
	@echo "--- Archiving $(DSDLIB)..."
else
	@echo "--------------------------------------------"
	@echo "--- Archiving $(DSDOBJ) to $(DSDLIB)..."
	@echo "--------------------------------------------"
endif
	@if [ ! -d $(DSDLIBDIR) ] ; then mkdir -p $(DSDLIBDIR) ; fi;
	$(AR) $(AR_ARG) $(DSDLIB) $(DSDOBJ) > $(OUTPUT) || (echo "AR $(DSDLIB) $$?"; exit 1)
	$(RANLIB) $(DSDLIB) || (echo "RANLIB $(DSDLIB) $$?"; exit 1)

$(SLQSAPILIB): $(SLQSAPIOBJ) $(WDSOBJ) $(DMSOBJ) $(QOSOBJ) $(DSDOBJ)
ifeq ($(VERBOSE),0)
	@echo "--- Archiving $(SLQSAPILIB)..."
else
	@echo "--------------------------------------------"
	@echo "--- Archiving $(SLQSAPIOBJ) to $(SLQSAPILIB)..."
	@echo "--------------------------------------------"
endif
	@if [ ! -d $(SLQSAPILIBDIR) ] ; then mkdir -p $(SLQSAPILIBDIR) ; fi;
	$(AR) $(AR_ARG) $(SLQSAPILIB) $(SLQSAPIOBJ) $(FMSOBJ) $(WDSOBJ) $(DMSOBJ) $(QOSOBJ) $(DSDOBJ) > $(OUTPUT) || (echo "AR $(SLQSAPILIB) $$?"; exit 1)
	$(RANLIB) $(SLQSAPILIB)  || (echo "RANLIB $(LOCLIB) $$?"; exit 1)

$(QMILIB): $(COMMONOBJ) $(DCSOBJ) $(WDSOBJ) $(WDAOBJ) $(DMSOBJ) $(NASOBJ) $(CBKOBJ) $(CATOBJ) \
			$(RMSOBJ) $(FMSOBJ) $(SMSOBJ) $(OMADMOBJ) \
			$(SAROBJ) $(SWIOBJ) $(UIMOBJ) $(QOSOBJ) \
			$(IMSOBJ) $(LOCOBJ) $(IMSAOBJ) $(TMDOBJ) $(TSOBJ) \
            $(SWIDMSOBJ) $(SWINASOBJ) $(CTLOBJ) $(DSDOBJ) $(LIBSDKOBJ)

ifeq ($(VERBOSE),0)
	@echo "--- Archiving $(SLQSAPILIB)..."
else
	@echo "--------------------------------------------"
	@echo "--- Archiving to $(QMILIB)..."
	@echo "--------------------------------------------"
endif
	@if [ ! -d $(QMILIBDIR) ] ; then mkdir -p $(QMILIBDIR) ; fi;
	$(AR) $(AR_ARG) $(QMILIB) $(COMMONOBJ) $(DCSOBJ) $(WDSOBJ) $(DMSOBJ) $(NASOBJ) $(CBKOBJ) $(DSDOBJ) > $(OUTPUT) || (echo "AR $(QMILIB) $$?"; exit 1)
	$(AR) $(AR_ARG) $(QMILIB) $(CATOBJ) $(RMSOBJ) $(FMSOBJ) $(SMSOBJ) > $(OUTPUT) || (echo "AR $(QMILIB) $$?"; exit 1)
	$(AR) $(AR_ARG) $(QMILIB) $(OMADMOBJ) $(SAROBJ) $(SWIOBJ) > $(OUTPUT) || (echo "AR $(QMILIB) $$?"; exit 1)
	$(AR) $(AR_ARG) $(QMILIB) $(UIMOBJ) $(QOSOBJ) $(IMSOBJ) $(LOCOBJ) $(IMSAOBJ) $(TMDOBJ) $(TSOBJ) $(SWIDMSOBJ) $(SWINASOBJ) $(CTLOBJ) $(LIBSDKOBJ) $(WDAOBJ) > $(OUTPUT) || (echo "AR $(QMILIB) $$?"; exit 1)
	$(RANLIB) $(QMILIB) || (echo "RANLIB $(QMILIB) $$?"; exit 1)

$(LITEQMILIB): $(COMMONOBJ) $(DCSOBJ) $(WDSOBJ) $(WDAOBJ) $(DMSOBJ) $(NASOBJ) $(CBKOBJ) $(CATOBJ) $(DSDOBJ) \
			$(RMSOBJ) $(FMSOBJ) $(SMSOBJ) $(OMADMOBJ) \
			$(SAROBJ) $(SWIOBJ) $(UIMOBJ) $(QOSOBJ) \
			$(IMSOBJ) $(LOCOBJ) $(IMSAOBJ) \
			$(SLQSAPIOBJ) $(WDSOBJ) $(DMSOBJ) $(QOSOBJ) $(TMDOBJ) $(TSOBJ) \
			$(COREOBJ) $(SWIDMSOBJ) $(SWINASOBJ) $(CTLOBJ) $(DSDOBJ) \
			$(CKBOBJ) 
ifeq ($(VERBOSE),0)
	@echo "--- Archiving $(LITEQMILIB)..."
else
	@echo "--------------------------------------------"
	@echo "--- Archiving to $(LITEQMILIB)..."
	@echo "--------------------------------------------"
endif
	@if [ ! -d $(QMILITELIBDIR) ] ; then mkdir -p $(QMILITELIBDIR) ; fi;
	$(AR) $(AR_ARG) $(LITEQMILIB) $(COMMONOBJ) $(DCSOBJ) $(WDSOBJ) $(DMSOBJ) $(NASOBJ) $(CBKOBJ) $(DSDOBJ) > $(OUTPUT) || (echo "AR $(LITEQMILIB) $$?"; exit 1)
	$(AR) $(AR_ARG) $(LITEQMILIB) $(CATOBJ) $(RMSOBJ) $(FMSOBJ) $(SMSOBJ) > $(OUTPUT) || (echo "AR $(LITEQMILIB) $$?"; exit 1)
	$(AR) $(AR_ARG) $(LITEQMILIB) $(OMADMOBJ) $(SAROBJ) $(SWIOBJ) > $(OUTPUT) || (echo "AR $(LITEQMILIB) $$?"; exit 1)
	$(AR) $(AR_ARG) $(LITEQMILIB) $(UIMOBJ) $(QOSOBJ) $(IMSOBJ) $(LOCOBJ) $(IMSAOBJ) $(TMDOBJ) $(TSOBJ) $(SWIDMSOBJ) $(SWINASOBJ) $(CTLOBJ) > $(OUTPUT) $(WDAOBJ)|| (echo "AR $(LITEQMILIB) $$?"; exit 1)
	$(AR) $(AR_ARG) $(LITEQMILIB) $(SLQSAPIOBJ) $(WDSOBJ) $(DMSOBJ) $(QOSOBJ) $(DSDOBJ) > $(OUTPUT) || (echo "AR $(LITEQMILIB) $$?"; exit 1)
	$(AR) $(AR_ARG) $(LITEQMILIB) $(COREOBJ) > $(OUTPUT) || (echo "AR $(LITEQMILIB) $$?"; exit 1)
	$(AR) $(AR_ARG) $(LITEQMILIB) $(CKBOBJ) > $(OUTPUT) || (echo "AR $(LITEQMILIB) $$?"; exit 1)
	$(RANLIB) $(LITEQMILIB) || (echo "RANLIB $(LITEQMILIB) $$?"; exit 1)
ifeq ($(PKG),lite-qmi)
# Apply namespace prefix to symbols only used internally within library to prevent
# link conflicts with customer app
	@echo "--- Applying namespace prefix for $(LITEQMILIB)..."
# Create pattern match file containing symbols for external SDK Lite APIs
# (defined global symbols from lite-qmi package objects) and symbols that are
# undefined within in library. Note that in lite-qmi package $(SLQSAPIOBJ) = $(OBJS)
ifeq ($(PARTIALLLY_BUILD),0)
#######################################################################
	$(NM) -g --defined-only -fp $(SLQSAPIOBJ) | \
		sed -ne 's/^\([^ ]*\).*[^:]$$/^\1'/p | \
		sort | uniq > $(LITEQMILIBSYMAPI)

	$(NM) -g --defined-only -fp $(LITEQMILIB) | \
		sed -ne 's/^\([^ ]*\).*[^:]$$/^^\1'/p | \
		sort | uniq > $(LITEQMILIBSYMDEF)

	$(NM) -g --undefined-only -fp $(LITEQMILIB) | \
		sed -ne 's/^\([^ ]*\).*[^:]$$/^\1'/p | \
		sort | uniq | \
		grep -v -f $(LITEQMILIBSYMDEF) >> $(LITEQMILIBSYMAPI)
#######################################################################
else
#######################################################################
	$(NM) -g --defined-only -fp $(SLQSAPIOBJ) | \
		sed -ne 's/^\([^ ]*\).*[^:]$$/^\1'/p | \
		sort | uniq > $(LITEQMILIBSYMAPI)
	$(eval NUMBEROFDEF = $(shell $(NM_EXEC) -g --undefined-only -fp $(LITEQMILIB) | \
		sed -ne 's/^\([^ ]*\).*[^:]$$/^^\1'/p | \
		sort | uniq | wc -l))
	$(NM) -g --defined-only -fp $(LITEQMILIB) | \
		sed -ne 's/^\([^ ]*\).*[^:]$$/^^\1'/p | \
		sort | uniq > $(LITEQMILIBSYMDEF)
	{ \
	set -e ;\
	for i in $$(seq 10 10 $(NUMBEROFDEF)) ;do \
	echo "$${i} / $(NUMBEROFDEF)"; \
	$(NM_EXEC) -g --undefined-only -fp $(LITEQMILIB) | \
		sed -ne 's/^\([^ ]*\).*[^:]$$/^\1'/p | \
		sort | uniq | head -n "$${i}" | tail -n 10 | \
		grep -v -f "$(LITEQMILIBSYMDEF)" | \
		xargs -s 50000 -r0 printf "%s\n" >> $(LITEQMILIBSYMAPI) ;\
	done ;\
	}
#######################################################################
endif
# Create symbol redefinition file containing all global symbols from lite-qmi library
# that require namespace prefix. Exclude symbols from pattern match file
ifeq ($(PARTIALLLY_BUILD),0)
#######################################################################
	$(NM) -g -fp $(LITEQMILIB) | \
		sed -ne 's/^\([^ ]*\).*[^:]$$/\1 $(LITEQMILIBNAMESPACE)\1'/p | \
		grep -v -f $(LITEQMILIBSYMAPI) | \
		sort | uniq > $(LITEQMILIBSYMNS)
else
#######################################################################
	$(eval NUMBEROFSYM = $(shell $(NM_EXEC) -g -fp $(LITEQMILIB) | \
		sed -ne 's/^\([^ ]*\).*[^:]$$/\1 $(LITEQMILIBNAMESPACE)\1'/p | \
		sort | uniq | wc -l))
	{ \
	for i in $$(seq 10 10 $(NUMBEROFSYM)) ;do \
	$(NM_EXEC) -g -fp $(LITEQMILIB) | \
		sed -ne 's/^\([^ ]*\).*[^:]$$/\1 $(LITEQMILIBNAMESPACE)\1'/p | \
		head -n "$${i}" | tail -n 10 | \
		grep -v -f $(LITEQMILIBSYMAPI) | \
		xargs -s 50000 -r0 printf "%s\n" | \
		sort | uniq >> $(LITEQMILIBSYMNS); \
	done ;\
	}
########################################################################
endif
#Remove swi_uint common function as they need to be external
	sed '/swi_uint/d' $(LITEQMILIBSYMNS) > $(LITEQMILIBSYMNS)_tmp
	mv $(LITEQMILIBSYMNS)_tmp $(LITEQMILIBSYMNS)
# Apply namespace prefix to symbols in library
#	$(OBJCOPY) --redefine-syms=$(LITEQMILIBSYMNS) $(LITEQMILIB)
endif

#-------------------------------------------------------------------------------
# Test Targets
#-------------------------------------------------------------------------------
#
#
$(TESTEXE):  $(TESTSRC) $(OBJS) $(SDKLIB) $(CORELIB) $(SLQSAPILIB) $(HDRS)
#
#--------------------------------------------------------------------------------
# Clean files
#--------------------------------------------------------------------------------
.PHONY: clean
clean:
	@echo "Cleaning $(PKG) files..."
	rm -fr $(OBJSDIR)/*.o

.PHONY: debug
debug:
	@echo "CFLAGS="$(CFLAGS)
