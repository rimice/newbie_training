/*********************************************************************
*** Filename:
***          ex10.c
***	Copyright (c) 2013 Wistron
***	All rights reserved.
***
***	Description:
***		 A simple sys device.
***
***	Author/Creat Date:
*** 		Tenix Xu, July 12,13
***
***	Note:
***
***********************************************************************/
#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>


/******************************************************************
*** DEFINES
*******************************************************************/
#define EX_SIZE 100



/******************************************************************
*** CONSTANTS AND VARIABLES
*******************************************************************/
struct bus_type ex10_bus = {
	.name = "ex10",
};

char ex_buf[EX_SIZE] = "sys_example";




/*****************************************************************************************
***	Description:		
***			read data from kernel	
***
*******************************************************************************************/
static ssize_t show_ex_bus(struct bus_type *bus, char *buf)
{
	return snprintf(buf, EX_SIZE, "%s\n", ex_buf);
}



/*****************************************************************************************
***	Description:		
***			write data to kernel	
***
*******************************************************************************************/
static ssize_t store_ex_bus(struct bus_type *bus, const char *buf, size_t count)
{
	return snprintf(ex_buf, EX_SIZE, "%s", buf);
}

/*
*Define attribute
*/
static BUS_ATTR(example, S_IRUGO|S_IWUGO, show_ex_bus, store_ex_bus);


/*
*Loading function
*/
static int __init ex_bus_init(void)
{
	int ret;
	/*总线注册*/
	ret = bus_register(&ex10_bus);
	if(ret){
		printk("bus register failed!\n");
		goto err1;	
	}

	ret = bus_create_file(&ex10_bus, &bus_attr_example);
	if(ret){
		printk("bus creat file failed!\n");
		goto err2;	
	}
	printk("bus creat is ok \n");
	return 0;

err2:
	bus_unregister(&ex10_bus);
err1:
	return ret;
}


/*
*Unistall function
*/
static void __exit ex_bus_exit(void)
{
	bus_remove_file(&ex10_bus, &bus_attr_example);
	bus_unregister(&ex10_bus);
	printk("bus is exit\n");
}

module_init(ex_bus_init);
module_exit(ex_bus_exit);

MODULE_AUTHOR("Tenix Xu");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("exercise 10");
MODULE_ALIAS("A proc device module");
