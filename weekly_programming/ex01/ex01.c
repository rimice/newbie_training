/**********************************************************************************************
*** Filename:
*** ex01.c
*** Copyright (c) 2013 Wistron
*** All rights reserved.
***
*** Description:
*** the code of weekly programming ex01 
***
*** Author/Creat Date:
*** Tenix Xu, 2013/5/24
***
*** Modification History:
***
*** Note:
***
************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>  

#define NUMBER 10000000


//整型数据排序
int compare( const void *a ,const void *b )
{
  return *(int*)a - *(int*)b ;
}


//打印数值
void printdata(int *p)
{
  int i;
  for(i=0;i<NUMBER;i++)
     {
       printf("data=%d\n",p[i]);
     }
}


int main()
{
  clock_t begain, end;
  begain = clock();
  srand(time(NULL));
  int *num;
  int i;
  double time;
  num= (int *)malloc(sizeof(int)*NUMBER);
  if (num!=NULL)
	for(i=0;i<NUMBER;i++)
	{
	   num[i]=rand()%55555;
	}
  else return 0;

  qsort(num,NUMBER,sizeof(int),compare); //qsort
  printdata(num);  //printdate
  free(num);       
  end = clock();
  time = (double)(end - begain)/CLOCKS_PER_SEC;
  printf("Time=%lf seconds\n",time);
  return 0; 
}
