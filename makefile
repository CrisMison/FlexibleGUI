include build/rules

kernel:
	make -C classic/kernel all

tools:

menuconfig:	
	./build/kconfig/mconf kconfig
