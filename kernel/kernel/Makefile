SRCS := $(wildcard *.c) $(wildcard *.S)
OBJS := $(patsubst %.c,%.o,$(patsubst %.S,%.o,$(SRCS)))
CFLAGS := -O2 -nostdinc -nostdlib -fno-builtin -fno-stack-protector -fno-pic -static
ASFLAGS :=
LDFLAGS := -Tkernel.ld

all: $(OBJS)
	ld $(LDFLAGS) -N -o kernel $(OBJS)

clean:
	rm -f *.o kernel
