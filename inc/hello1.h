
#ifndef HELLO1_H
#define HELLO1_H

#include <linux/list.h>
#include <linux/slab.h>
#include <linux/ktime.h>

struct hello_list {
	struct list_head list;
	ktime_t time_before;
	ktime_t time_after;
};

int print_hello(uint count);

#endif

