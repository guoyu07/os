#include "types.h"
#include "cga.h"

/* no return */
void init(void)
{
	cga_clear();
	cga_puts("Hello Wendy!");

	while (1) ;
}
