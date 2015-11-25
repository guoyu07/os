SRCS := $(wildcard *.c) $(wildcard *.S)
OBJS := $(patsubst %.c,%.o,$(patsubst %.S,%.o,$(SRCS)))
CFLAGS := -nostdin -nostdlib
ASFLAGS :=
LDFLAGS := -Tkernel.ld

all: $(OBJS) link

link:
	ld $(LDFLAGS) -o kernel $(OBJS)

