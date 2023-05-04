# makefile

include ../SampleApps.mak

_OBJ = displaysettings.o main.o user_input.o socket_server.o wda_handler.o tmd_handler.o ts_handler.o qos_handler.o swidms_handler.o ping.o netlink_util.o command_set.o lite-qmi-demo.o
OBJ  := $(patsubst %, $(ODIR)%, $(_OBJ))
LIBS  = -l m -L ../../lite-qmux/lib/$(CPU)/ -l lite-qmux -L ../../lite-mbim/lib/$(CPU)/ -l lite-mbim -L ../../lite-qmi/lib/$(CPU)/ \
	-L ../../lite-common/lib/$(CPU)  -l lite-qmi -lpthread -lcommon
CFLAGS += -I ../inc -I ../../lite-qmi/inc -I ../../lite-qmux/inc -I ./inc -I ../common/inc -I ../../pkgs/common 

STATICFLAG := 1
ifdef BUILDSTATICFLAG
STATICFLAG := $(BUILDSTATICFLAG)
endif

ifeq ($(STATICFLAG), 1)
LIBS  += -static-libgcc
CFLAGS += -static
endif

ifneq ($(GCC_SYS_ROOT),)
LIBS  += --sysroot=$(GCC_SYS_ROOT)
endif

$(ODIR)%.o:	$(SRCDIR)%.c
	@if [ -e $(ODIR) ] ;\
        then echo "$(ODIR) exists - good." ;\
        else mkdir -p $(ODIR);\
        fi;
	@echo Compiling $<

	$(CC) -g -c -o $@ $< $(CFLAGS)

$(ODIR)%.o:	$(CSRCDIR)%.c
	@if [ -e $(ODIR) ] ;\
        then echo "$(ODIR) exists - good." ;\
        else mkdir -p $(ODIR);\
        fi;
	@echo Compiling $<

	$(CC) -g -c -o $@ $< $(CFLAGS)

$(BINDIR)lite-qmi-connection-manager$(CPU): $(OBJ)
	@if [ -e $(BINDIR) ] ;\
        then echo "$(BINDIR) exists - good." ;\
        else mkdir -p $(BINDIR);\
        fi;
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

.PHONY clean:
	rm -rf $(DDIR)
	rm -rf $(BINDIR)lite-qmi-connection-manager$(CPU)
