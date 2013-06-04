obj-m := ex03.o

KERNELDIR =$(shell uname -r)
	
build: modules
modules:
	make -C /lib/modules/$(KERNELDIR)/build M=$(shell pwd) modules
clean:
	make -C /lib/modules/$(KERNELDIR)/build M=$(shell pwd) clean

 
