obj-m +=sp-logger.o

KDIR = ..

all:
	$(MAKE) -C  $(KDIR) SUBDIRS=$(PWD)  modules

clean:
	rm  -rf *.o *.ko    *.mod.* *.symvers   *.order
