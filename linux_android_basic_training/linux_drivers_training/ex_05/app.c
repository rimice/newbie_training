/*******************************************************************************
*** Filename:
*** app.c
*** Copyright (c) 2013 Wistron
*** All rights reserved.
***
*** Description:
*** test the misc device.
***
*** Author/Creat Date:
*** Tenix Xu, Jun 11,13
***
*** Note:
****************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdlib.h> 
#include "cmd.h"

char write_buf[30]="ioctl write";
int main(void)
{
	char buf[30];
	int fd;
	int ret;
	fd = open("/dev/mis_drv", O_RDWR);//打开       
	if(fd < 0)
	{
		printf("open is error\n");
		return -1;
	}
	printf("open is ok\n");

	ret=write(fd, "Tenix Xu", 10);//写入
	if(ret!= 10)
	{
		printf(" writing may error\n");
		exit(1);
	}   
       
	lseek(fd, 0, SEEK_SET);
	ret=read(fd, buf, 10);//读出
	if (ret <0 )
	{
	printf("Read is error\n");
	exit(1);
	}
	printf("buf is [%s]\n", buf);

	lseek(fd, 0, SEEK_SET);
     
	ret=ioctl(fd,IOCTL_WRITE,write_buf);//ioctl 写入
	if(ret<0)
	{
		printf("ioctl error\n");
	}
	ret= read(fd,buf,30); //读出
	if(ret<0)
	{
		printf("read is error\n");
	}
	printf("buf is [%s]\n",buf);

	lseek(fd, 0, SEEK_SET);
	ret=ioctl(fd,IOCTL_CLEAR,write_buf);//ioctl clear
	if(ret<0)
	{
		printf("ioctl error\n");
	}
	ret= read(fd,buf,30); //读出
	if(ret<0)
	{
		printf("read is error\n");
	}
	printf("buf is [%s]\n",buf);      
	close(fd); 
	printf("close is ok\n");
	return 0; 
}


