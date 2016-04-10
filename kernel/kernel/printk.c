#include <types.h>
#include <stdarg.h>
#include <printk.h>

char * itoa(u64 value, char * str, int base)
{
	char * rc;
	char * ptr;
	char * low;
	// Check for supported base.
	if (base < 2 || base > 36)
	{
		*str = '\0';
		return str;
	}
	rc = ptr = str;
	// Set '-' for negative decimals.
	if (value < 0 && base == 10)
	{
		*ptr++ = '-';
	}
	// Remember where the numbers start.
	low = ptr;
	// The actual conversion.
	do
	{
		// Modulo is negative for negative value. This trick makes abs() unnecessary.
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + value % base];
		value /= base;
	} while (value);
	// Terminating the string.
	*ptr-- = '\0';
	// Invert the numbers.
	while (low < ptr)
	{
		char tmp = *low;
		*low++ = *ptr;
		*ptr-- = tmp;
	}
	return rc;
}

static void printk2(const char *fmt, va_list argp)
{
	const char *p;
	u64 arg;
	char *s;
	char fmtbuf[32];

	for (p = fmt; *p != 0; p++) {
		if (*p != '%') {
			cga_putc(*p);
			continue;
		}
		switch (*++p) {
			case 'p':
				arg = va_arg(argp, long);
				fmtbuf[0] = '0';
				fmtbuf[1] = 'x';
				itoa(arg, fmtbuf+2, 16);
				cga_puts(fmtbuf);
				break;
			case 'x':
				arg = va_arg(argp, long);
				itoa(arg, fmtbuf, 16);
				cga_puts(fmtbuf);
				break;
			case 'd':
				arg = va_arg(argp, long);
				itoa(arg, fmtbuf, 10);
				cga_puts(fmtbuf);
				break;
			case 'c':
				arg = va_arg(argp, int);
				cga_putc((char)arg);
				break;
			case 's':
				s = va_arg(argp, char *);
				cga_puts(s);
				break;
			default:
				cga_putc(*p);
				break;
		}
	}
}

void printk(const char *fmt, ...)
{
	va_list argp;
	va_start(argp, fmt);
	printk2(fmt, argp);
	va_end(argp);
}
