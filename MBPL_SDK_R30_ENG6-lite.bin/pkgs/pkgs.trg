#-------------------------------------------------------------------------------
#
#  Name:
#    pkgs.trg
#
#  Description:
#    Define packages here for inclusion into pkgs.mak
#
# Copyright (c) 2008 by Sierra Wireless, Incorporated.  All Rights Reserved.
#-------------------------------------------------------------------------------
#
# Variable definition - Packages, Ordered Alphabetically
AMDIR = am
DLDIR = dl
DSDIR = ds
ERDIR = er
HDDIR = hd
ICDIR = ic
IMDIR = im
MMDIR = mm
OSDIR = os
PIDIR = pi
QADIR = qa
QLDIR = ql
QMDIR = qm
SLDIR = sl
SMDIR = sm
SUDIR = su
USDIR = us
CIDIR = ci
IMDIR = im
LITEQMIDIR = lite-qmi
LITEQMUXDIR = lite-qmux
LITEMBIMDIR = lite-mbim
LITEFWDIR = lite-fw
COMMON = common

# Order is important in the following line
SUBDIRS = $(COMMON) $(ERDIR) $(AMDIR) $(OSDIR) $(MMDIR) $(SLDIR) $(QLDIR) $(PIDIR) $(DLDIR) $(HDDIR) $(ICDIR) $(USDIR) $(CIDIR) $(SMDIR) $(IMDIR) $(QMDIR) $(DSDIR) $(SUDIR) $(QADIR)

ifeq ($(LITEQMI), 1)
SUBDIRS = $(COMMON) $(ERDIR) $(AMDIR) $(OSDIR) $(MMDIR) $(SLDIR) $(QLDIR) $(PIDIR) $(DLDIR) $(HDDIR) $(ICDIR) $(USDIR) $(CIDIR) $(SMDIR) $(IMDIR) $(QMDIR) $(DSDIR) $(SUDIR) $(QADIR) $(LITEQMIDIR) $(LITEQMUXDIR) $(LITEMBIMDIR)
endif

ifeq ($(LITEFW), 1)
SUBDIRS = $(COMMON) $(ERDIR) $(AMDIR) $(OSDIR) $(MMDIR) $(SLDIR) $(QLDIR) $(PIDIR) $(DLDIR) $(HDDIR) $(ICDIR) $(USDIR) $(CIDIR) $(SMDIR) $(IMDIR) $(QMDIR) $(DSDIR) $(SUDIR) $(QADIR) $(LITEQMIDIR) $(LITEQMUXDIR) $(LITEMBIMDIR) $(LITEFWDIR)
endif
