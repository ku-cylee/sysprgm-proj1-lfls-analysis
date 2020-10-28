obj-m +=sp-logger.o

KDIR = ..

all:
	$(MAKE) -C  $(KDIR) SUBDIRS=$(PWD)  modules
	sudo rmmod sp_logger; sudo insmod sp-logger.ko

clean:
	rm  -rf *.o *.ko    *.mod.* *.symvers   *.order
