/**************************************************************
*** Filename:
*** ex02.c
*** Copyright (c) 2013 Wistron
*** All rights reserved.
***
*** Description:
*** Get how many "1" of a number at it's binary form.
***
*** Author/Creat Date:
*** Tenix Xu, May 31,13
***
*** Note:
*** 
******************************************************************/


/*****************************************************************
***Include Files
*****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h> 

/**************************************************************
*** Description:
*** Get how many "1" 
***
*** Parameters:
*** num:the number get in
*** Return Value:
*** Return the number of how many "1"
*******************************************************************/
int operation(int num)
{  
	int i=0;
	unsigned int count=0;
	for(i=0;i<32;i++)
	{
		if(num&0x80000000)
		count++;
		num<<=1;
	}
	return count;
}


/*****************************************************************************************
*** Description:
*** the main function, call the subfunction and print the result
******************************************************************************************/

int main()
{
	unsigned int num;
	scanf("%d",&num);  
	printf("result=%d\n",operation(num));
	return 0;
}
