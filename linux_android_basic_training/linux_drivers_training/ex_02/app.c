/*******************************************************************************
*** Filename:
*** app.c
*** Copyright (c) 2013 Wistron
*** All rights reserved.
***
*** Description:
*** test the char driver device.
***
*** Author/Creat Date:
*** Tenix Xu, May 30,13
***
*** Note:
****************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdlib.h> 
#include "ex02_cmd.h"

int main(void)
{
	char buf[20];
	int fd;
        int ret;
	fd = open("/dev/ex02", O_RDWR);//打开       
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
   
	ret=read(fd, buf, 10);//读出
	if (ret <0 )
	   {
	     printf("Read is error\n");
	     exit(1);
	   }
        printf("buf is [%s]\n", buf);

        ioctl(fd,ex02_CLEAR);  //再清空 
        ret=read(fd, buf, 10);
	if (ret <0 )
	   {
	     printf("Read is error\n");
	     exit(1);
	   } 
        printf("buf is [%s]\n", buf);//读出清空后的buf
     
	close(fd); 
        printf("close is ok\n");
	return 0;
}


