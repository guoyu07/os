.global _start
_start:
	mov $0x0a, %ah
#char
	mov $0x41, %al
#count
	mov $1, %cx
#page
	mov $1, %bh
	int $0x10

	hlt
