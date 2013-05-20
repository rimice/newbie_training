#include <linux/init.h>
#include <linux/module.h>

static int helloworld(void)
{
  printk(KERN_ALERT "hello world\n");
  return 0;
}

static void exit_hello(void)
{
  printk(KERN_ALERT "goodbye kernel");
}

module_init(helloworld);
module_exit(exit_hello);


MODULE_AUTHOR("Tenix xu");
MODULE_LICENSE("Dual BSD/GPL");
//MODULE_DESCRIPTION("exercise 01");
//MODULE_ALIAS("an example");
