export ROOTDIR = $(shell pwd)
export LIBSDIR = $(shell pwd)/build/lib
include build/make.rules

kernel:
	make -C classic/kernel all

tools:

menuconfig:
	./build/kconfig/mconf kconfig

clean:
	make -C classic/kernel clean