ENTRY(start)
SECTIONS
{
	.text 0x10000:
	{
/*		_text=.; */
		*(.text)
/*		_etext=ALIGN(4096); */
	}
	.data ALIGN(4096):
	{
/*		_data=.; */
		*(.data)
		*(.rodata)
/*		_edata=ALIGN(4096); */
	}
	.bss ALIGN(4096):
	{
/*		_bss=.; */
		*(.bss)
/*		_ebss=ALIGN(4096); */
	}
/*	_end=.; */
}
