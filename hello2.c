
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include "hello1.h"

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("y_zabara_io14");
MODULE_DESCRIPTION("Hello2 Module");

static uint howmany = 1;

module_param(howmany, uint, S_IRUGO);
MODULE_PARM_DESC(howmany, "Number of printed 'Hello, world!'");

static int __init hello2_init(void)
{
	int a;
	pr_info("Hello2 Module loaded.\n");

	a = print_hello(howmany);
	return a;
}

static void __exit hello2_exit(void)
{
	pr_info("Hello2 Module unloaded.\n");
}

module_init(hello2_init);
module_exit(hello2_exit);

