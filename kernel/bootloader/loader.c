/* kernel loader */

#include <elf.h>
#include <x86.h>

#define SECTSIZE	(512)

void readseg(u8 *, u64, u64);

/* never return */
void bootmain(void)
{
	struct elfhdr *eh;
	struct proghdr *ph, *eph;
	void (*entry)(void);
	u8 *pa;

	eh = (struct elfhdr *)0x10000;

	readseg((u8 *)eh, 512, 0);

	/* FIXME! ELF64 sanity check */

	while (1);
	ph = (struct proghdr *)((u8 *)eh + eh->phoff);
	eph = ph + eh->phnum;

	for (; ph < eph; ph++) {
		pa = (u8 *)ph->paddr;
		readseg(pa, ph->filesz, ph->offset);
		if (ph->memsz > ph->filesz) {
			stosb(pa + ph->filesz, 0, ph->memsz - ph->filesz);
		}
	}

	entry = (void(*)(void))(eh->entry);
	entry();
}

void waitdisk()
{
	//wait for disk ready
	while ((inb(0x1f7) & 0xc0) != 0x40)
		;
}

void readsect(void *dest, u32 offset)
{
	waitdisk();

	outb(0x1f2, 1); /* count */
	outb(0x1f3, offset);
	outb(0x1f4, offset >> 8);
	outb(0x1f5, offset >> 16);
	outb(0x1f6, (offset >> 24) | 0xe0);
	outb(0x1f7, 0x20); /* read sectors */

	waitdisk();

	insl(0x1f0, dest, SECTSIZE/4);
}

void readseg(u8 *pa, u64 sz, u64 offset)
{
	u8 *epa;

	epa = pa + sz;

	/* round down to sector boundary */
	pa -= offset % SECTSIZE;
	/* bytes to sectors; kernel starts at sector 1 */
	offset = (offset / SECTSIZE) + 1;
	
	for (; pa < epa; pa += SECTSIZE, offset++) {
		readsect(pa, offset);
	}
}
