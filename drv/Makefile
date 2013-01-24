#
# Makefile for the pin drivers.
# 
# wrote by Zhiguang Li
# 13458499@qq.com
#
#


obj-m += pin_dev.o
pin_dev-objs := pindev.o gpio.o

all:
	make -C /home/Dspa/firetux_781Bittel/cache/custom/distfiles/linux SUBDIRS=`pwd` modules
	cp pin_dev.ko /home/tftproot/

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions modules.* Module.*

.PHONY: modules modules_install clean
