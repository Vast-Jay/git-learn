ifneq ($(KERNELRELEASE),)
obj-m := rtc_private.o

else
EXTRA_CFLAGS += -DDEBUG 
KDIR := /home/zhaixue/linux-5.4.70
ARCH_ARGS := ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-

all:
		make  $(ARCH_ARGS) -C $(KDIR) M=$(PWD) modules
clean:
		make  $(ARCH_ARGS) -C $(KDIR) M=$(PWD) modules clean
endif
