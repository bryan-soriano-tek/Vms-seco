# makefile

include ../SampleApps.mak

_OBJ =  main.o ping.o netlink_util.o 
OBJ  := $(patsubst %, $(ODIR)%, $(_OBJ))
LIBS  = -l m -L ../../lite-mbim/lib/$(CPU)/ -l lite-mbim -lpthread -L ../../lite-common/lib/$(CPU) -lcommon
CFLAGS += -I ../../lite-mbim/inc -I ../../lite-qmi/inc -I ./inc -I ../../pkgs/common

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

$(BINDIR)lite-mbim-connection-manager$(CPU): $(OBJ)
	@if [ -e $(BINDIR) ] ;\
        then echo "$(BINDIR) exists - good." ;\
        else mkdir -p $(BINDIR);\
        fi;
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS) 

.PHONY clean:
	rm -rf $(DDIR)
	rm -rf $(BINDIR)lite-mbim-connection-manager$(CPU)

print-%: ; @echo $* is $($*) from $(origin $*) 
