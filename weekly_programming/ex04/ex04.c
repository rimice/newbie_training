/**********************************************************************************************
*** Filename:
***		ex04.c
***	Copyright (c) 2013 Wistron
***	All rights reserved.
***
***	Description:
***		To see the time about Sort
***
***	Author/Creat Date:
*** 		Tenix Xu, Jun 28,13
***
***	Note:
***
************************************************************************************************/


#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 100000

/*****************************************************************************************
***	Description:		
***		Unoptimized sort1	
*******************************************************************************************/
void sort1(int *x, int n)
{
	int i,j;
	int temp;
	for(i=1;i<n;i++)
	{
		for(j=i;j>0;j--)
		{
			if(x[j-1]>x[j])
			{
				temp=x[j-1];
				x[j-1]=x[j];
				x[j]=temp;
			}
		}
	}
}


/*****************************************************************************************
***	Description:		
***		 Optimized sort2 	
*******************************************************************************************/
void sort2(int *x, int n)
{
	int i,j;
	int temp;
	for(i=0;i<n;i++)
	{	
		temp=x[i];
		for(j=i;j>0 && x[j-1]>temp;j--)
		{	
			x[j]=x[j-1];	
		}
		x[j]=temp;		
	}

}

/*****************************************************************************************
***	Description:		
***		 Display sort 	
*******************************************************************************************/
void show(int *x,int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		printf("%d ",x[i]);
	}	
}




/*****************************************************************************************
***	Description:		
***		 The main function 
*******************************************************************************************/
int  main()
{
	int i,j;
	int x[N];
	char cmd1,cmd2;
	clock_t begin,end;
	double cost;
	srand((unsigned)time(NULL));
	while(1)
	{
		printf("Please choose sort\nr:random sort,i:increase sort,d:decrease sort,e:equivalent sort,q:quit\n");
		scanf("%c",&cmd1);getchar();
		if(cmd1=='r')
		{
			for(i=0;i<N;i++) 
			{
				x[i]=rand()%5555;
			}	
			show(x,N);
			printf("\n");
		}
		else if(cmd1=='i')
		{
			for(i=0;i<N;i++)
			{
				x[i]=i;
			}
			show(x,N);
			printf("\n");
		}
		else if(cmd1=='d')
		{
			for(i=0,j=N;i<N;i++,j--)
			{
				x[i]=j;
			}
			show(x,N);
			printf("\n");
		}
		else if(cmd1=='e')
		{
			for(i=0;i<N;i++)
			{
				x[i]=5555;
			}
			show(x,N);
			printf("\n");
		}
		else if(cmd1=='q')
		{
			return 0;
		}
		else
		{
			printf("input is error,please check\n")	;
			return 0;
		}

		printf("please input number, 1: choose unoptimized sort or 2: choose optimized sort\n");

		scanf("%c", &cmd2);getchar();
		if(cmd2 == '1')
		{
			begin=clock();
			sort1(x,N);
			end=clock();
			show(x,N);
			printf("\n");
			cost=(double)(end-begin)/CLOCKS_PER_SEC;
			printf("unoptimized sort cost %f seconds\n",cost );
		
		}
	
		else if(cmd2 == '2')
		{	
			begin=clock();
			sort2(x,N);
			end=clock();
			show(x,N);
			printf("\n");
			cost=(double)(end-begin)/CLOCKS_PER_SEC;
			printf("optimized sort cost %f seconds\n",cost );
		}
		else
		{
			printf("input is error,please check\n");
			return 0;
		}
	}
}	



