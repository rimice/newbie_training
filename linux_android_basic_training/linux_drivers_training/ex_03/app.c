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
*** Tenix Xu, Jun 4,13
***
*** Note:
****************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdlib.h> 

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
    
	close(fd); 
        printf("close is ok\n");
	return 0;
}


