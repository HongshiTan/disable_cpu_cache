EXTRA_CFLAGS = -m64
obj-m += disable_cache.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules