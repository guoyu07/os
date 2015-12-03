/* kernel loader */

#include <elf.h>
#include <x86.h>

#define SECTSIZE	(512)

void readseg(u8 *, u32, u32);

/* never return */
void bootmain(void)
{
	struct elfhdr *eh;
	struct proghdr *ph, *eph;
	u8 *pa;

	eh = (struct elfhdr *)0x10000;

	readseg((u8 *)eh, 4096, 0);

	/* FIXME! ELF64 sanity check */

	ph = (struct proghdr *)((u8 *)eh + eh->phoff);
	eph = ph + eh->phnum;

	for (; ph < eph; ph++) {
		pa = (u8 *)ph->paddr;
		readseg(pa, ph->filesz, ph->offset);
		if (ph->memsz > ph->filesz) {
			stosb(pa + ph->filesz, 0, ph->memsz - ph->filesz);
		}
	}

	((void(*)(void))(eh->entry))();
}

void readsect(void *dest, u32 offset)
{
	/* wait disk */
	while ((inb(0x1f7) & 0xc0) != 0x40)
		;

	outb(0x1f2, 1); /* count */
	outb(0x1f3, offset);
	outb(0x1f4, offset >> 8);
	outb(0x1f5, offset >> 16);
	outb(0x1f6, (offset >> 24) | 0xe0);
	outb(0x1f7, 0x20); /* read sectors */

	/* wait disk */
	while ((inb(0x1f7) & 0xc0) != 0x40)
		;

	insl(0x1f0, dest, SECTSIZE/4);
}

void readseg(u8 *pa, u32 sz, u32 offset)
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
