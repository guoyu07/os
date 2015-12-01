#ifndef _X86_H_
#define _X86_H_

static inline u8 inb(u16 port)
{
	u8 data;
	asm volatile("in %1, %0" : "=a"(data) : "d"(port));
	return data;
}

static inline void insl(int port, void *addr, int cnt)
{
	asm volatile("cld; rep insl" :
			"=D"(addr), "=c"(cnt) :
			"d"(port), "0"(addr), "1"(cnt) :
			"memory", "cc");
}

static inline void outb(u16 port, u8 data)
{
	asm volatile("out %0, %1" : : "a"(data), "d"(port));
}

static inline void stosb(void *addr, int data, int cnt)
{
	asm volatile("cld;rep stosb" :
			"=D" (addr), "=c"(cnt) :
			"0"(addr), "1"(cnt), "a"(data) :
			"memory", "cc");
}

#endif
