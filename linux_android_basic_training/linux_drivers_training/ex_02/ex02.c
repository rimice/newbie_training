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
#include "ex02_cmd.h"

#define DEV_SIZE 100

static struct class *ex_class;

struct chardev_ex 
{
	char buf[DEV_SIZE];
	unsigned int major;
	unsigned int minor;
	unsigned int cur_size;
	dev_t cdevno;
	struct cdev ex02;
};

struct chardev_ex chardev;

/*********************************************************
*** Description:
*** open the device
**********************************************************/
int ex02_open(struct inode *node,struct file *filp)
{ 
	struct chardev_ex *cdevp;
	cdevp = container_of(node->i_cdev,struct chardev_ex,ex02);
	filp->private_data=cdevp; 
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
struct chardev_ex *cdevp = filp->private_data;
	if(!cdevp->cur_size)
	{
		return 0;
	}


if(copy_to_user(buf,cdevp->buf,count))
	{
		ret = -EFAULT;
		printk("kernel read is fail\n");
	}
else
	{
		ret = count;
		cdevp->cur_size = count;
		printk("kernel read is ok  ");
		printk("cur_size:%d\n",cdevp->cur_size);
		printk("buf=%s\n",cdevp->buf);
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
	struct chardev_ex *cdevp = filp->private_data;
  
	if(copy_from_user(cdevp->buf,buf,count))
	{
		ret = -EFAULT;       
		printk("kernel write is wrong\n");
	}
	else    
	{
		ret = count;
		printk("kernel write is ok  ");
		cdevp->cur_size = count;
		printk("cur_size=%d\n",cdevp->cur_size);    
	}
  
	return ret;

}

/*********************************************************
*** Description:
*** ioctl
**********************************************************/
static ssize_t ex02_ioctl(struct file *filp,unsigned int cmd,unsigned long arg)
{
	struct chardev_ex *cdevp = filp->private_data;
	ssize_t ret = 0;
	switch(cmd)
		{
		case ex02_CLEAR:
			memset(cdevp->buf,0,DEV_SIZE);		
			filp->f_pos = 0;
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
	chardev.cur_size = 0;
	chardev.major = 0;
	chardev.minor = 0;

	if(chardev.major)
	{
		chardev.cdevno = MKDEV(chardev.major,chardev.minor);
		result = register_chrdev_region(chardev.cdevno,1,"ex02");
	}
	else
	{
		result = alloc_chrdev_region(&chardev.cdevno,chardev.minor,1,"alloc driver");
		chardev.major = MAJOR(chardev.cdevno);
		chardev.minor = MINOR(chardev.cdevno);    
	}
	if(result < 0)
	{
		printk("register is wrong\n");
		return result;
	}
   
	printk("major[%d] minor[%d]\n", chardev.major, chardev.minor);

	cdev_init( &chardev.ex02, &ex02_fops);

	if(!cdev_add(&chardev.ex02,chardev.cdevno,1)) //add
	{
		printk("cdev_add is ok\n"); 
	}
	else
	{
		printk("cdev_add is error\n"); 
		unregister_chrdev_region(chardev.cdevno,1);
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
	device_create(ex_class,NULL,chardev.cdevno,NULL,"ex02");
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
	cdev_del(&chardev.ex02);
	unregister_chrdev_region(chardev.cdevno,1);
	device_destroy(ex_class,chardev.cdevno);              
	class_destroy(ex_class);
	printk("device destory ok\n");
}


module_init(ex02_init);
module_exit(ex02_exit);

MODULE_AUTHOR("Tenix xu");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("exercise 02");
MODULE_ALIAS("A char device module");

