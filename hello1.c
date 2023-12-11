
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include "hello1.h"

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("y_zabara_io14");
MODULE_DESCRIPTION("Hello1 Module");

// Голова списку
static LIST_HEAD(my_list_head);

int print_hello(uint count)
{
	uint i;
	struct hello_list *md;
	
	if (count == 0 || (count > 5 && count <= 10))
		pr_warn("Warning: count is 0 or between 5 and 10.\n");

	if (count > 10) {
		pr_err("Error: count is greater than 10. Module cannot be loaded.\n");
		return -EINVAL;
	}

	for (i = 0; i < count; ++i) {
		md = kmalloc(sizeof(struct hello_list), GFP_KERNEL);

		md->time_before = ktime_get();
		pr_info("Hello, world!\n");
		md->time_after = ktime_get();
		list_add_tail(&md->list, &my_list_head);
	}
	return 0;
}

EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void)
{
	pr_info("Hello1 Module loaded.\n");
	return 0;
}

static void __exit hello1_exit(void)
{
	struct hello_list *md, *tmp;

	list_for_each_entry_safe(md, tmp, &my_list_head, list) {
		pr_info("md times: %lld ns\n",
		ktime_to_ns(ktime_sub(md->time_after, md->time_before)));
		list_del(&md->list);
		kfree(md);
	}
	BUG_ON(!list_empty(&my_list_head));
	pr_info("Hello1 Module unloaded.\n");
}

module_init(hello1_init);
module_exit(hello1_exit);
