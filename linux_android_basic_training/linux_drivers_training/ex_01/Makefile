obj-m := helloworld.o

KERNELDIR =$(shell uname -r)
	
build: 
	make -C /lib/modules/$(KERNELDIR)/build M=$(shell pwd) modules
clean:
	make -C /lib/modules/$(KERNELDIR)/build M=$(shell pwd) clean

 
