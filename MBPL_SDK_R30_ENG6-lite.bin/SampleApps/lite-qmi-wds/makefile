# makefile

include ../SampleApps.mak

_OBJ =  main.o wds-execute-command.o wds-display-result.o netlink_util.o user_input.o socket_server.o command_set.o lite-qmi-demo.o
OBJ  := $(patsubst %, $(ODIR)%, $(_OBJ))
LIBS  = -l m -L ../../lite-qmux/lib/$(CPU)/ -l lite-qmux -L ../../lite-mbim/lib/$(CPU)/ -l lite-mbim -L ../../lite-qmi/lib/$(CPU)/ \
	-L ../../lite-common/lib/$(CPU) -l lite-qmi -lpthread -lcommon
CFLAGS += -I ../../lite-qmi/inc -I ../../lite-qmux/inc -I ./inc -I ../../pkgs/common

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

$(BINDIR)lite-qmi-wds$(CPU): $(OBJ)
	@if [ -e $(BINDIR) ] ;\
        then echo "$(BINDIR) exists - good." ;\
        else mkdir -p $(BINDIR);\
        fi;
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS) 

.PHONY clean:
	rm -rf $(DDIR)
	rm -rf $(BINDIR)lite-qmi-wds$(CPU)

print-%: ; @echo $* is $($*) from $(origin $*) 
