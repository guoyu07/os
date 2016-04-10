#include <types.h>
#include <x86.h>
#include <cga.h>

/* colors
 * 0:black, 1:blue, 2:green, 3:cyan, 4:red,
 * 5:magenta, 6:brown, 7:light grey, 8:dark grey,
 * 9:light blue, 10:light green, 11:light cyan, 12:light red,
 * 13:light magneta, 14: light brown, 15: white. 
 */
#define WOB     (0x0F00)        /* white on black */

#define BLANK   (0x0020 | WOB)

static u8 cursor_x = 0, cursor_y = 0;
static u16 *cga_ram = (u16 *)0xB8000;

static void move_cursor()
{
	u16 loc = cursor_y * 80 + cursor_x;
	/* set high cursor byte */
	outb(0x3D4, 14);
	outb(0x3D5, loc>>8);
	/* set low cursor byte */
	outb(0x3D4, 15);
	outb(0x3D5, loc);
}

/* FIXME this is slow */
static void scroll(void)
{
	if (cursor_y >= 25) {
		int i;
		for (i = 0; i < 25*80; i++) {
			cga_ram[i] = cga_ram[i+80];
		}
		for (i = 24*80; i < 25*80; i++) {
			cga_ram[i] = BLANK;
		}
		cursor_y = 24;
	}
}

void cga_putc(char c)
{
	u16 color = WOB;

	switch (c) {
		case '\n':
			cursor_x = 0;
			cursor_y++;
			break;
		case '\r':
			cursor_x = 0;
			break;
		case 0x08: /* backspace */
			if (cursor_x) {
				cursor_x--;
			}
			break;
		case 0x09: /* tab */
			cursor_x = (cursor_x + 8) & ~(8 - 1);
			break;
		default:
			/* printable character */
			if (c >= ' ') {
				cga_ram[cursor_y*80+cursor_x] = c | color;
				cursor_x++;
			}
			break;
	}

	scroll();
	move_cursor();
}

void cga_puts(const char *s)
{
	int i = 0;
	while (s[i]) {
		cga_putc(s[i]);
		i++;
	}
}

void cga_clear(void)
{
	int i;
	for (i = 0; i < 80*25; i++) {
		cga_ram[i] = BLANK;
	}
	cursor_x = cursor_y = 0;
	move_cursor();
}
