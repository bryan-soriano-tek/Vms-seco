# makefile

include ../SampleApps.mak

_OBJ  = lite_fw_dld.o sysinfo.o
OBJ  := $(patsubst %, $(ODIR)%, $(_OBJ))

CFLAGS += -I ../../lite-fw/inc -I../../lite-qmi/inc -I ../../lite-qmux/inc -I ./inc -I ../../pkgs/common \
	-I ../../lite-mbim/inc -I ../common/inc -D_GNU_SOURCE

LIBS  = -L ../../lite-fw/lib/$(CPU)/ -L ../../lite-qmux/lib/$(CPU) -L ../../lite-mbim/lib/$(CPU)/ \
	-L ../../lite-qmi/lib/$(CPU) -L ../../lite-common/lib/$(CPU) \
	-llite-fw -llite-qmi -llite-qmux -llite-mbim -lcommon -lrt -lpthread

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

$(BINDIR)fwdwl-lite$(CPU): $(OBJ)
	@if [ -e $(BINDIR) ] ;\
        then echo "$(BINDIR) exists - good." ;\
        else mkdir -p $(BINDIR);\
        fi;
	$(CC) -g -o $@ $^ $(LDFLAGS) $(LIBS)

.PHONY clean:
	rm -rf $(DDIR)
	rm -rf $(BINDIR)fwdwl-lite$(CPU)
