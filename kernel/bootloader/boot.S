#start the first cpu, switch to 64-bit protected mode, jump into C

#define SEG_KCODE 1
#define SEG_KDATA 2

.code16
.global start
start:
#disable interrupts
	cli
	cld

	xor %ax, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %ss

#enable A20
seta20.1:
	inb $0x64, %al               # Wait for not busy
	testb $0x2, %al
	jnz seta20.1

	movb $0xd1, %al               # 0xd1 -> port 0x64
	outb %al, $0x64

seta20.2:
	inb $0x64, %al               # Wait for not busy
	testb $0x2, %al
	jnz seta20.2

	movb $0xdf, %al               # 0xdf -> port 0x60
	outb %al, $0x60

#enable PAE paging
	mov %cr4, %eax
	or $(1<<5), %eax
	mov %eax, %cr4

#setup PML4
#setup 4 tables at 0x1000(a PML4T, a PDPT, a PDT, and a PT), identity map the first two megabytes
	mov $0x1000, %edi
	mov %edi, %cr3
	xor %eax, %eax
	mov $4096, %ecx
	rep stosl
	mov %cr3, %edi
	movl $0x2003, (%edi)
	add $0x1000, %edi
	movl $0x3003, (%edi)
	add $0x1000, %edi
	movl $0x4003, (%edi)
	add $0x1000, %edi
#fill PT
	mov $0x3, %ebx
	mov $512, %ecx
setpte:
	mov %ebx, (%edi)
	add $8, %edi
	add $0x1000, %ebx
	loop setpte

#set LM
	mov $0xc0000080, %ecx
	rdmsr
	or $(1<<8), %eax
	wrmsr

#enable PG & PE
	mov %cr0, %eax
	or $(1<<31 | 1), %eax
	mov %eax, %cr0

#setup GDT
	lgdt gdtdesc
	
	ljmp $(SEG_KCODE<<3), $start64

	.code64
start64:
	mov $(SEG_KDATA<<3), %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %ss
	xor %eax, %eax
	mov %ax, %fs
	mov %ax, %gs

#setup stack
	mov $start, %rsp

#jump into C, no return
	call bootmain

.p2align 2
gdt:
#null
	.byte 0,0,0,0,0,0,0,0
#code
	.word 0,0
	.byte 0
	.byte 0x9a
	.byte 0x20
	.byte 0
#data
	.word 0,0
	.byte 0
	.byte 0x92
	.byte 0
	.byte 0
gdtdesc:
	.word (gdtdesc - gdt - 1)
	.long gdt
