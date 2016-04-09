CFLAGS := -nostdinc -fno-builtin -fno-pic -fno-stack-protector -ffreestanding -mno-red-zone -mno-mmx -mno-sse -mno-sse2
CFLAGS += -I./ -I../include -ggdb -static -Os
BL := boot.bin

all: $(BL)
	
$(BL): boot.S loader.c
	gcc $(CFLAGS) -c loader.c
	gcc $(CFLAGS) -c boot.S
	ld -e start -Ttext 0x7c00 -o bootsector.o boot.o loader.o
	objcopy -O binary -j .text bootsector.o $(BL)
	./sign.pl $(BL)

update: all
	dd if=$(BL) of=../boot.img conv=notrunc

clean:
	rm -f *.o $(BL)

.PHONY: all
