# SampleApps.mak
#
#include ../../pkgs/slqscompile.mak

IDIR    = -I inc/ \
          -I ../common/inc \
		  -I ../../pkgs/pack \
		  -I ../../pkgs \
		  -I ../../pkgs/qm \
		  -I ../../api/ \
		  -I../../api/qos/inc \
		  -I../../api/dcs/inc \
		  -I../../api/wds/inc \
		  -I../../api/dms/inc \
		  -I../../api/sms/inc \
		  -I../../api/nas/inc \
		  -I../../api/rms/inc \
		  -I../../api/cat/inc \
		  -I../../api/fms/inc \
		  -I../../api/omadm/inc \
		  -I../../api/sar/inc \
		  -I../../api/swi/inc \
		  -I../../api/ts/inc \
		  -I../../api/tmd/inc \
		  -I../../api/uim/inc \
		  -I../../api/ims/inc \
		  -I../../api/imsa/inc \
		  -I../../api/cbk/cat/inc \
		  -I../../api/cbk/dcs/inc \
		  -I../../api/cbk/dms/inc \
		  -I../../api/cbk/fms/inc \
		  -I../../api/cbk/nas/inc \
		  -I../../api/cbk/omadm/inc \
		  -I../../api/loc/inc \
		  -I../../api/cbk/uim/inc \
		  -I../../api/cbk/wds/inc \
		  -I../../api/cbk/wms/inc \
		  -I../../api/cbk/ts/inc \
		  -I../../api/cbk/tmd/inc \
		  -I../../api/cbk/inc \
          -I../../api/swidms/inc

CFLAGS  += $(IDIR) $(INCLUDE) -DSDK_EXE='"$(SDK_EXE)"'
VPATH   =
SRCDIR  = src/
CSRCDIR = ../common/src/
ODIR    = obj/$(CPU)/
DDIR    = obj/
LDIR    = ../../build/lib/$(CPU)/ -lrt -lpthread
BINDIR  = bin/

DEPS    = $(IDIR)SWIWWANCMAPI.h
LIBS    = -l slqsqmi -l slqsapi -l slqscore -l cbk -L $(LDIR) 

ifdef debug
CFLAGS += -D DEBUG
else
#CFLAGS += -Os
#LDFLAGS += -s
endif

