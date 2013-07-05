/*********************************************************************
*** Filename:
***          ex08.c
***	Copyright (c) 2013 Wistron
***	All rights reserved.
***
***	Description:
***		 A simple misc device.
***
***	Author/Creat Date:
*** 		Tenix Xu, July 5,13
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
#include<linux/gpio.h>
#include<asm/io.h>
#include <mach/mt_gpio.h>

#define BUF_SIZE 100
#define MISC_NAME "mis_drv"
volatile unsigned long phy,phy2,virt,virt2;

volatile unsigned long *gpiodat,*gpiodat2;
struct miscdev_ex{
 
	char buf[BUF_SIZE];
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
	int ret, value,value2;
    int value_r,value2_r;
    int direction;
    int mode;
	struct miscdev_ex *miscp = filp->private_data;

    gpiodat=(volatile unsigned long*)virt;
    gpiodat2=(volatile unsigned long*)virt2;

	if(!miscp->cur_size)
	{
		return 0;
	}
	if(*offset > BUF_SIZE)
	{
		return count? -ENXIO:0;
	}
	if(*offset+count > BUF_SIZE)
	{
		count = BUF_SIZE-*offset;
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
/*
*The value of mode and direction
*/
    mode = mt_get_gpio_mode(GPIO135);
    printk("GPIO135 mode= %d ",mode);
    
    direction = mt_get_gpio_dir(GPIO135);
    printk("GPIO135 direction is %d\n",direction);

/*Get and display the GPIO
 *GPIO135 is an enable pin of the front camera.
 *GPIO174 is a WIFI pin.
 *GPIO135 will be turn to zero when somebody open the front camera with GPIO174 no changing to
 *verify the value of GPIO.
*/
	value=mt_get_gpio_out(GPIO135);
	value2=mt_get_gpio_out(GPIO174);
	printk("value=%d ",value);
	printk("value2=%d\n",value2);	

    value_r =( *gpiodat) & (1<<7) ? 1:0;
    value2_r=( *gpiodat2) & (1<<14) ? 1:0;
    printk("value_r=%d ",value_r);
    printk("value2_r=%d\n",value2_r);

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
  
	if (*offset > BUF_SIZE)
	{
		return count? -ENXIO:0;
	}
	if(*offset + count > BUF_SIZE)
	{
		printk("offset+ count > BUF_SIZE, error\n");
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
	                	new_pos = BUF_SIZE + offset;
	                	break;

		default:
	        	printk("offset is wrong\n");
		return -EINVAL;
	}

     if(new_pos < 0 || new_pos > BUF_SIZE)
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
    phy=0x10005880; //the physical address of GPIO135
    phy2=0x100058a0;//the physical address of GPIO174
    virt=(unsigned long)ioremap(phy,0x04);
    virt2=(unsigned long)ioremap(phy2,0x4);

	miscp = kmalloc(sizeof(struct miscdev_ex),GFP_KERNEL);
	if(!miscp)
	{
		printk("kmalloc is error\n");
        return -ENOMEM;
	}
    memset(miscp,0,sizeof(struct miscdev_ex));
    
	ret = misc_register(&misc_dev);
	if( ret )
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
 
    iounmap((void *)virt);
    iounmap((void *)virt2);
	kfree(miscp);
	misc_deregister(&misc_dev);	
}




module_init(misc_init);
module_exit(misc_exit);

MODULE_AUTHOR("Tenix Xu");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("exercise 03");
MODULE_ALIAS("A char device module");

