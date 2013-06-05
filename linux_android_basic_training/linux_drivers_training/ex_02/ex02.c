/**********************************************************************************************
*** Filename:
*** ex02.c
*** Copyright (c) 2013 Wistron
*** All rights reserved.
***
*** Description:
*** A simple char device.
***
*** Author/Creat Date:
*** Tenix Xu, May 30,13
***
*** Note:
************************************************************************************************/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/errno.h>
#include <linux/device.h>
#include <linux/slab.h>
#include "ex02_cmd.h"

#define DEV_SIZE 100
unsigned int major,minor;

static struct class *ex_class;

struct chardev_ex 
{
	char buf[DEV_SIZE];
	unsigned int cur_size;	
	struct cdev ex02;
};

dev_t cdevno;
struct chardev_ex cdev;


/*********************************************************
*** Description:
*** open the device
**********************************************************/
int ex02_open(struct inode *node,struct file *filp)
{ 
	printk("open is ok\n");
	return 0;
}

/*********************************************************
*** Description:
*** close the device
**********************************************************/
int ex02_close(struct inode *node,struct file *filp)
{
	printk("close is ok\n");
	return 0;
}

/*********************************************************
*** Description:
*** read data
**********************************************************/
ssize_t ex02_read(struct file *filp,char __user *buf,size_t count,loff_t *offset)
{
	int ret;
	if(!cdev.cur_size)
	{
		return 0;
	}


if(copy_to_user(buf,cdev.buf,count))
	{
		ret = -EFAULT;
		printk("kernel read is fail\n");
	}
else
	{
		ret = count;
		cdev.cur_size = count;
		printk("kernel read is ok");
		printk("cur_size:%d\n",cdev.cur_size);
		printk("buf=%s\n",cdev.buf);
	}

	return ret;
}

/*********************************************************
*** Description:
*** write data
**********************************************************/
static ssize_t ex02_write(struct file *filp,const char __user *buf,size_t count, loff_t *offset)
{
	ssize_t ret;
	if(copy_from_user(cdev.buf,buf,count))
	{
		ret = -EFAULT;       
		printk("kernel write is wrong\n");
	}
	else    
	{
		ret = count;
		printk("kernel write is ok  ");
		cdev.cur_size = count;
		printk("cur_size=%d\n",cdev.cur_size);    
	}
  
	return ret;

}

/*********************************************************
*** Description:
*** ioctl
**********************************************************/
static ssize_t ex02_ioctl(struct file *filp,unsigned int cmd,unsigned long arg)
{
	ssize_t ret = 0;
	switch(cmd)
		{
		case ex02_CLEAR:
			memset(cdev.buf,0,DEV_SIZE);		
			ret = 0;
                        printk("buf is clear\n");
			break;
		default:	/*命令错误时的处理*/
			printk("cmd is error\n");
			ret = - EINVAL;
			break;
		}
	return ret;
}

/*
*The struct file_operations
*/
struct file_operations ex02_fops = {
	.owner = THIS_MODULE,
	.open = ex02_open,    
	.write = ex02_write,
	.unlocked_ioctl =ex02_ioctl,
	.read = ex02_read,  
	.release = ex02_close,
};


/*
*Loading function
*/
static int __init ex02_init(void)
{
	int result = 0;
	cdev.cur_size = 0;

	if(major)
	{
		cdevno = MKDEV(major,minor);
		result = register_chrdev_region(cdevno,1,"ex02");
	}
	else
	{
		result = alloc_chrdev_region(&cdevno,minor,1,"alloc driver");
		    
	}
	if(result < 0)
	{
		printk("register is wrong\n");
		return result;
	}

	cdev_init( &cdev.ex02, &ex02_fops);

	if(!cdev_add(&cdev.ex02,cdevno,1)) //add
	{
		printk("cdev_add is ok\n"); 
	}
	else
	{
		printk("cdev_add is error\n"); 
		unregister_chrdev_region(cdevno,1);
	}
/*
*Creat class and device.
*/
	ex_class = class_create(THIS_MODULE,"ex_class");
	if(IS_ERR(ex_class))
	{
		printk("creat ex_class failed!\n");
		return -1;
	}
	device_create(ex_class,NULL,cdevno,NULL,"ex02");
	printk("device create ok!\n");

	return 0;
}


/*
*Unistall function
*/
static void __exit ex02_exit(void)
{
/*delete the cdev,unregister char device,destory class and device
*/
	cdev_del(&cdev.ex02);
	unregister_chrdev_region(cdevno,1);
	device_destroy(ex_class,cdevno);              
	class_destroy(ex_class);
	printk("device destory ok\n");
}


module_init(ex02_init);
module_exit(ex02_exit);

MODULE_AUTHOR("Tenix xu");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("exercise 02");
MODULE_ALIAS("A char device module");

