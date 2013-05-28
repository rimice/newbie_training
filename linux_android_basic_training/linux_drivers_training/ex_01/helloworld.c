/*****************************************************
** Filename: helloworld.c
** Copyright (c) 2013 Wistron
** All rights reserved.
**
** Description:
** This is a simple kernel module.
** Author/Created :
** Tenix Xu, May 24'13
** Modification History:
** Tenix Xu, May 28'13
**
****************************************************/

/**********************************************
*** Include Files
**********************************************/
#include <linux/init.h>
#include <linux/module.h>


/**********************************************
***Description:
*** helloword function
**********************************************/
static int helloworld(void)
{
  printk(KERN_ALERT "hello world\n");
  return 0;
}



/*******************************************
***Description:
*** exit function
*********************************************/
static void exit_hello(void)
{
  printk(KERN_ALERT "goodbye kernel");
}

module_init(helloworld);
module_exit(exit_hello);

/*
*Statement and description of the module
*/
MODULE_AUTHOR("Tenix xu");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("exercise 01");
MODULE_ALIAS("an example");
