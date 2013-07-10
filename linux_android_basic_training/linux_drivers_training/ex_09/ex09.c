/*********************************************************************
*** Filename:
***          ex09.c
***	Copyright (c) 2013 Wistron
***	All rights reserved.
***
***	Description:
***		 A simple proc device.
***
***	Author/Creat Date:
*** 		Tenix Xu, July 10 ,13
***
***	Note:
***
***********************************************************************/
#include<linux/proc_fs.h>
#include<linux/module.h>
#include<linux/init.h>
#include<asm/uaccess.h>

/******************************************************************
*** DEFINES
*******************************************************************/
#define ROOT_NAME "ex_dir"
#define PROC_NAME "ex_proc"
#define BUF_SIZE  200
#define NAME_SIZE 100

/******************************************************************
*** CONSTANTS AND VARIABLES
*******************************************************************/
static struct proc_dir_entry *ex_root;
static struct proc_dir_entry *ex_entry;

struct ex_proc
{
	char name[NAME_SIZE];
	char buf[BUF_SIZE];
};
struct ex_proc proc;


/*****************************************************************************************
***	Description:		
***			read data from kernel	
***
***	Return Value:
***			If read sucessfully, return the address 
*******************************************************************************************/
static int ex_read_proc(char *page,char **start,off_t off,int count ,int *eof,void *data)
{  
	int len;
	struct ex_proc *proc=(struct ex_proc *)data;
	char *p = page;

	p += sprintf(p,"%s, %s\n",proc->name,proc->buf);
	*start =  page + off;
	len = p - page;
	if(len > off)
		len -= off;
	else
		len = 0;
	return len < count ? len:count;
}


/*****************************************************************************************
***	Description:		
***			write data to kernel	
***
***	Return Value:
***			If write sucessfully, return the bytes that have written.
*******************************************************************************************/
static int ex_write_proc(struct file *file,const char __user *buffer,unsigned long count,void *data)
{   
    int count_t;
    struct ex_proc *proc=(struct ex_proc *)data;
    if(count > BUF_SIZE-1)
		count_t=BUF_SIZE-1;
    else
        count_t=count;
    if(copy_from_user(proc->buf,buffer,count_t))
    {
        printk("kernel write is error\n");
        return -EFAULT;
    }
    printk("kernel write is ok\n");
    proc->buf[count_t] ='\0';
    return count_t;
}





/*
*Loading function
*/
static int proc_test_init(void)
{
    ex_root=proc_mkdir(ROOT_NAME,NULL);
    if(ex_root==NULL)
    {
        printk("creat dir /proc/%s error\n",ROOT_NAME);
        remove_proc_entry(ROOT_NAME,NULL);
        return -ENOMEM;
    }
    printk("creat dir /proc/%s\n",ROOT_NAME);

    ex_entry=create_proc_entry(PROC_NAME,0666,ex_root);
    if(ex_entry==NULL)
    {
        printk("creat dir /proc/%s error\n",PROC_NAME);
        remove_proc_entry(PROC_NAME,NULL);
        return -ENOMEM;
    }
    printk("creat /proc/%s/%s\n",ROOT_NAME,PROC_NAME);

    strcpy(proc.name,"proc");
    strcpy(proc.buf,"buf");

    ex_entry->data=&proc;
    ex_entry->read_proc=ex_read_proc;
    ex_entry->write_proc=ex_write_proc;
    return 0;
}



/*
*Unistall function
*/
static void proc_test_exit(void)
{
    remove_proc_entry(PROC_NAME,ex_root);
    remove_proc_entry(ROOT_NAME,NULL);
    printk("All proc entry entry remove\n");
}


module_init(proc_test_init);
module_exit(proc_test_exit);

 
MODULE_AUTHOR("Tenix Xu");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("exercise 09");
MODULE_ALIAS("A proc device module");


