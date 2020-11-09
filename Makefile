KDIR ?= /usr/src/linux

.DEFAULT_GOAL := modules

%:
	$(MAKE) -C $(KDIR) M=$$PWD $@
