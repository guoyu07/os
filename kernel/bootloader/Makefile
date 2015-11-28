CFLAGS := -nostdinc -fno-pic -I./
BL := boot.bin

all: boot.S loader.c
	gcc $(CFLAGS) -c loader.c
	gcc $(CFLAGS) -c boot.S
	ld -e start -Ttext 0x7c00 -o bootsector.o boot.o loader.o
	objcopy -O binary -j .text bootsector.o $(BL)
	./sign.pl $(BL)

clean:
	rm -f *.o $(BL)
