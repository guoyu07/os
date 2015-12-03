ENTRY(init)
SECTIONS
{
	. = 0x100000;

	.text :
	{
		*(.text)
	}
	PROVIDE(etext = .);

	. = ALIGN(0x1000);
	PROVIDE(data = .);

	/* The whitespace around section is required, so that the section name is unambiguous. */
	.data :
	{
		*(.data)
		*(.rodata)
	}
	PROVIDE(edata = .);

	.bss ALIGN(4096):
	{
		*(.bss)
	}

	PROVIDE(end = .);

	/DISCARD/ :
	{
		*(.eh_frame .note.GNU-stack)
	}
}
