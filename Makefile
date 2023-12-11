# Makefile

ifneq ($(KERNELRELEASE),)
# kbuild part of makefile
obj-m := hello1.o hello2.o

else
# normal makefile
KDIR ?= /lib/modules/`uname -r`/build
DIR := inc
ccflags-y += -I$(DIR)
default:
	$(MAKE) -C $(KDIR) M=$$PWD
clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean
endif

