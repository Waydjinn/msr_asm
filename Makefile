obj-m += msr_rd.o

all:
	make -C /lib/modules/4.18.0-10-generic/build M=$(PWD) modules

clean:
	make -C /lib/modules/4.18.0-10-generic/build M=$(PWD) clean
