obj-m += chardev.o


all:
	make -C /lib/modules/`uname -r`/build M=`pwd` modules

char_dev_reload:
	sudo rm char_dev
	sudo mknod char_dev c 100 0
	sudo chmod a+w char_dev
clean:
	make -C /lib/modules/`uname -r`/build M=`pwd` clean

load:
	insmod chardev.ko
	dmesg -c | tail

unload:
	rmmod chardev
	dmesg -c | tail
test:
	make clean
	make
	sudo make unload || sudo make load
	make char_dev_reload

	$(info " --- TEST: DEFAULT IO END --- ")
	echo cock > char_dev
	cat char_dev

	$(info " --- TEST: FORWARD IO --- ")
	echo direction forward > char_dev
	cat char_dev

	$(info " --- TEST: BACK IO --- ")
	echo direction back > char_dev
	cat char_dev
run_ioctl:
	gcc ioctl.c -o ioctl.exe && ./ioctl.exe
