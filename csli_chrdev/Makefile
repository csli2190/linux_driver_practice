KERNELDIR = ../linux-6.0.8
PWD := $(shell pwd)
INSTALLDIR = /lib/modules/6.0.8/kernel

obj-m := csli_chrdev.o 

modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

install:
	cp csli_chrdev.ko $(INSTALLDIR)

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod *.mod.c .tmp_versions modules.order Module.symvers

.PHONY: modules install clean

