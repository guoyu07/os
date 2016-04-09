KERNEL := kernel.elf
SRCS := $(wildcard *.c) $(wildcard *.S)
OBJS := $(patsubst %.c,%.o,$(patsubst %.S,%.o,$(SRCS)))
CFLAGS := -O2 -nostdinc -nostdlib -fno-builtin -fno-stack-protector -fno-pic -static -ggdb
CFLAGS := -I../include/
ASFLAGS :=
LDFLAGS := -Tkernel.ld

all: $(KERNEL)
	
$(KERNEL): $(OBJS)
	ld $(LDFLAGS) -N -o $@ $(OBJS)

update: all
	dd if=$(KERNEL) of=../boot.img seek=1 conv=notrunc

clean:
	rm -f *.o kernel.elf

.PHONY: all
