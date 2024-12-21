obj-m += rtl8852au.o

rtl8852au-objs := main.o usb/usb.o mac80211/mac80211.o

KERNEL_VERSION ?= `uname -r`
KERNEL_DIR ?= /lib/modules/$(KERNEL_VERSION)/build
PWD := $(shell pwd)
EXTRA_CFLAGS += -I$(src)/include

all:
	make -C $(KERNEL_DIR) M=$(PWD) modules

clean:
	make -C $(KERNEL_DIR) M=$(PWD) clean