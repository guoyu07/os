#ifndef _ELF64_H_
#define _ELF64_H_

#include <types.h>

struct elfhdr {
	u8 ident[16];  /* Magic number and other info */
	u16 type;                 /* Object file type */
	u16 machine;              /* Architecture */
	u32 version;              /* Object file version */
	u64 entry;                /* Entry point virtual address */
	u64 phoff;                /* Program header table file offset */
	u64 shoff;                /* Section header table file offset */
	u32 flags;                /* Processor-specific flags */
	u16 ehsize;               /* ELF header size in bytes */
	u16 phentsize;            /* Program header table entry size */
	u16 phnum;                /* Program header table entry count */
	u16 shentsize;            /* Section header table entry size */
	u16 shnum;                /* Section header table entry count */
	u16 shstrndx;             /* Section header string table index */
};

struct proghdr {
	u32 type;
	u32 flags;
	u64 offset;
	u64 vaddr;
	u64 paddr;
	u64 filesz;
	u64 memsz;
	u64 align;
};

#endif
