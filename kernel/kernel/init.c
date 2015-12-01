void start(void)
{
	*(unsigned short *)0xb8000 = 'Z' | 0x0700;
	while (1) ;
}
