CFLAGS := -nostdin -nostdlib

all: boot.o
	objcopy -O binary -j .text boot.o bootsector
	./sign.pl bootsector

