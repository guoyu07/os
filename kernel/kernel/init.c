#include <types.h>
#include <printk.h>

extern u64 kernel_text[], kernel_etext[], kernel_data[], kernel_edata[], kernel_end[];

static void show_kernel_info(void)
{
	printk("kernel version 0x%x\n", 0x1);
	printk("text %p etext %p data %p edata %p end %p\n", kernel_text, kernel_etext, kernel_data, kernel_edata, kernel_end);
	printk("kernel loaded at %p\n", kernel_text);
	printk("kernel text size %d\n", (kernel_etext - kernel_text));
	printk("kernel data size %d\n", (kernel_edata - kernel_data));
	printk("kernel total size %d\n", (kernel_end - kernel_text));
}

/* no return */
void init(void)
{
	cga_clear();
	cga_puts("Hello Wendy!\n");

	show_kernel_info();

	while (1) ;
}
