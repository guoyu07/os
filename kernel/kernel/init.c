/* no return */
void init(void)
{
	char *i;
	char *vram = (char *)0xa0000;

	for (i = vram; i < (vram + 0xffff); i++) {
		*i = (long)i & 0x0f;
	}

	while (1) ;
}
