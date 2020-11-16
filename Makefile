KDIR ?= /usr/src/linux

.DEFAULT_GOAL := modules
.PHONY: check

check:
	$(KDIR)/scripts/checkpatch.pl --no-tree -f asus-ec-sensors.c

%:
	$(MAKE) -C $(KDIR) M=$$PWD $@
