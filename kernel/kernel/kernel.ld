ENTRY(init)
SECTIONS
{
	. = 0x100000;

	kernel_text = .;
	.text :
	{
		*(.text)
	}
	kernel_etext = .;

	. = ALIGN(0x1000);
	kernel_data = .;

	/* The whitespace around section is required, so that the section name is unambiguous. */
	.data :
	{
		*(.data)
		*(.rodata)
	}
	kernel_edata = .;

	.bss ALIGN(4096):
	{
		*(.bss)
	}

	kernel_end = .;

	/DISCARD/ :
	{
		*(.eh_frame .note.GNU-stack)
	}
}
