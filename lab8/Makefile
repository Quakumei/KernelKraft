obj-m += chardev.o

all:
	make -C /lib/modules/`uname -r`/build M=`pwd` modules

clean:
	make -C /lib/modules/`uname -r`/build M=`pwd` clean

load:
	insmod chardev.ko
	dmesg -c | tail

unload:
	rmmod chardev
	dmesg -c | tail

run_ioctl:
	gcc ioctl.c -o ioctl.exe && ./ioctl.exe
