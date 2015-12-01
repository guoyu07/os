#start the first cpu, switch to 32-bit protected mode, jump into C

#include "asm.h"

#define SEG_KCODE 1
#define SEG_KDATA 2

#define CR0_PE 0x00000001

.code16
.global start
start:
	#disable interrupts
	cli

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

	#setup GDT
	lgdt gdtdesc
	
	mov %cr0, %eax
	or $CR0_PE, %eax
	mov %eax, %cr0

	ljmp $(SEG_KCODE<<3), $start32

	.code32
start32:
	xor %ax, %ax
	mov $(SEG_KDATA<<3), %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %ss
	xor %ax, %ax
	mov %ax, %fs
	mov %ax, %gs

	#setup stack
	mov $start, %esp
	call bootmain

	#never reach
	hlt

.p2align 2
gdt:
	SEG_NULLASM
	SEG_ASM(STA_X|STA_R, 0x0, 0xffffffff)
	SEG_ASM(STA_W, 0x0, 0xffffffff)
gdtdesc:
	.word (gdtdesc - gdt - 1)
	.long gdt
