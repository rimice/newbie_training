/*********************************************************************
*** Filename:
***          ex03.c
***	Copyright (c) 2013 Wistron
***	All rights reserved.
***
***	Description:
***		 A simple misc device.
***
***	Author/Creat Date:
*** 		Tenix Xu, Jun 4,13
***
***	Note:
***
***********************************************************************/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/miscdevice.h>
#include <linux/memory.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <asm/system.h>
#include <asm/uaccess.h>

#define DEV_SIZE 100
#define MISC_NAME "mis_drv"

struct miscdev_ex{
 
	char buf[DEV_SIZE];
	unsigned int cur_size;
};

struct miscdev_ex *miscp;


/*
* Open
*/
int misc_open(struct inode *node,struct file *filp)
{
	filp->private_data=miscp;
	printk("open is ok\n");
	return 0;
}

/*
* Close
*/
int misc_close(struct inode *node,struct file *filp)
{
	printk("close is ok\n");
	return 0;
}

/*****************************************************************************************
***	Description:		
***			read data from kernel	
***
***	Return Value:
***			If read sucessfully, return the bytes that have readed.
*******************************************************************************************/
ssize_t misc_read(struct file*filp, char __user *buf,size_t count,loff_t *offset)
{
	int ret;
	struct miscdev_ex *miscp = filp->private_data;
  
	if(!miscp->cur_size)
	{
		return 0;
	}
	if(*offset > DEV_SIZE)
	{
		return count? -ENXIO:0;
	}
	if(*offset+count > DEV_SIZE)
	{
		count = DEV_SIZE-*offset;
	}
  
	if(!copy_to_user(buf,miscp->buf+*offset,count))
	{
		ret = count;
		miscp->cur_size = count;
		*offset += count;
		printk("kernel read is ok\n");
		printk("buf=%s\n",miscp->buf);
	}
	else
	{
		printk("kernel read is error\n");
		ret = -EFAULT;
	}     
		return ret;
}


/*****************************************************************************************
***	Description:		
***			write data to kernel	
***
***	Return Value:
***			If write sucessfully, return the bytes that have written.
*******************************************************************************************/
ssize_t misc_write(struct file *filp, const char __user *buf, size_t count, loff_t *offset)
{
	int ret;
	struct miscdev_ex *miscp =  filp->private_data;
  
	if (*offset > DEV_SIZE)
	{
		return count? -ENXIO:0;
	}
		if(*offset + count > DEV_SIZE)
	{
		printk("offset+ count > DEV_SIZE, error\n");
		return -ENXIO;
	}

	if(!copy_from_user(miscp->buf+*offset,buf,count))
	{
		printk("kernel write is ok\n");
		*offset += count;
		miscp->cur_size = count;
		ret = count;
	}
	else
	ret = -EFAULT;
 	return ret;
}



/*****************************************************************************************
***	Description:	
***                 file location function	
*******************************************************************************************/
loff_t misc_llseek(struct file *filp,loff_t offset, int whence)
{
	loff_t new_pos;
	loff_t old_pos = filp->f_pos;

	switch(whence)
	{
		case SEEK_SET:
		new_pos = offset;
		break;

		case SEEK_CUR:
		new_pos = old_pos + offset;
		break;

		case SEEK_END:
		new_pos = DEV_SIZE + offset;
		break;

		default:
		printk("offset is wrong\n");
		return -EINVAL;
	}

       if(new_pos < 0 || new_pos > DEV_SIZE)
	{
		printk("F_pos is wrong\n");
		return -EINVAL;
	}

	filp->f_pos = new_pos;
	return  new_pos;
}

/*
* Driver methods
*/
struct file_operations misc_fops=
{
	.open = misc_open,
	.release = misc_close,
	.write = misc_write,
	.read = misc_read,
	.llseek = misc_llseek,  
};

/*
*Misc struct
*/
static struct miscdevice misc_dev=
{
	.minor= MISC_DYNAMIC_MINOR,
	.name= MISC_NAME,
	.fops= &misc_fops,
};


/*
*Loading function
*/
static int __init misc_init(void)
{
	int ret;
	miscp = kmalloc(sizeof(struct miscdev_ex),GFP_KERNEL);
	if(!miscp)
	{
		printk("kmalloc is error\n");
	}
   
	ret = misc_register(&misc_dev);
	if( !ret );
	{
		printk("register is error\n");
		return ret;
	}
       
	printk("register is ok\n");
	return 0;
} 

/*
*Unistall function
*/
static void __exit misc_exit(void)
{
	printk("exit\n");	
	kfree(miscp);
	misc_deregister(&misc_dev);	
}




module_init(misc_init);
module_exit(misc_exit);

MODULE_AUTHOR("Tenix Xu");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("exercise 03");
MODULE_ALIAS("A char device module");

