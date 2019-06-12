KERNEL_SOURCE=/lib/modules/`uname -r`/build

all:
	make -C ${KERNEL_SOURCE} M=`pwd` modules

obj-m += hello.o
