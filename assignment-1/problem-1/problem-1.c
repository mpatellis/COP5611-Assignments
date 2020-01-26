// Michael Patellis
// COP5611 Spring 2020
// Program creates a simple linked list kernel module
// which can be loaded and unloaded
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>

#define NUMBER_BIRTHDAYS 5

typedef struct birthday
{
	int day;
	int month;
	int year;
	struct list_head list;
} birthday;

LIST_HEAD(birthdayList);

int birthdayInit(void)
{
	int i = 0;
	birthday* bd;
	birthday* readBirthday;
	
	printk(KERN_INFO "Loading module\n");
	
	for (i = 0; i < NUMBER_BIRTHDAYS; i++)
	{
		bd = kmalloc(sizeof(*bd), GFP_KERNEL);

		bd->day   = 7 + i;
		bd->month = 2 + i;
		bd->year  = 1979 + 5*i;

		INIT_LIST_HEAD(&bd->list);
		list_add_tail(&bd->list, &birthdayList);
	}

	list_for_each_entry(readBirthday, &birthdayList, list)
	{
		printk(KERN_INFO "Birthday: Month %d Day %d Year %d\n",
		readBirthday->month, readBirthday->day, readBirthday->year);
	}
	
	return 0;
}

void birthdayExit(void)
{
	birthday* toDelete;
	birthday* next;
	
	printk(KERN_INFO "Removing module\n");

	list_for_each_entry_safe(toDelete, next, &birthdayList, list)
	{
		printk(KERN_INFO "Deleting Birthday: Month %d Day %d Year %d\n",
		toDelete->month, toDelete->day, toDelete->year);

		list_del(&toDelete->list);
		kfree(toDelete);
	}

	printk(KERN_INFO "Module removed and memory freed\n");
}

module_init(birthdayInit);
module_exit(birthdayExit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("Michael Patellis");