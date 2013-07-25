/**********************************************************************************************
*** Filename:
***		ex07.c
***	Copyright (c) 2013 Wistron
***	All rights reserved.
***
***	Description:
***		Using the quick sort method to sort increasing data, decreasing data, random data.
***
***	Author/Creat Date:
*** 		Tenix Xu, July 24,13
***
***	Note:
***
************************************************************************************************/
#include<stdio.h>
#include<time.h>
#define N 100000

int x[N];


/*****************************************************************************************
***	Description:		
***		The function of quick sort 	
*******************************************************************************************/
void quick_sort(int s[], int l, int r)
{
    int i, j, x;
    if (l < r)
    {
        i = l;
        j = r;
        x = s[i];
        while (i < j)
        {
            while(i < j && s[j] > x)
				j--; //从右到到坐找第一个小于x的数
            if(i < j)
				s[i++] = s[j];
            
			while(i < j && s[i] < x)
				i++; // 从左到右找第一个大于x的数
            if(i < j) 
				s[j--] = s[i];
        }
        s[i] = x;
        quick_sort(s, l, i-1);// 递归调用 
        quick_sort(s, i+1, r);
    }
}


void fprint(int *x,FILE *fd)
{	
	int i;
	for(i=0;i<N;i++)
	{
		fprintf(fd,"x[%d]=%d\n",i,x[i]);
	}
}

int main()
{	
	int i,j;
	char cmd;
	clock_t begin,end;
	double time;		
	FILE *in=fopen("in.txt","w+");
	FILE *out=fopen("out.txt","w+");
	if(in==NULL ||out==NULL)
	{
		printf("Open is error\n");
	}
	else
		printf("Open is ok\n");
		
	printf("q:Quit\nr:Choose random data\ni:Choose increasing data\nd:Choose decreasing data\n");	
	while((cmd=getchar()) != 'q')
	{
		switch(cmd)
		{
			case 'r' :
					printf("Choose random data\n");
					/*
					*Random data
					*/
					for(i=0;i<N;i++)
					{
						x[i]=rand()%500000;
					}
					fprint(x,in);
					fclose(in);
					printf("Random date write in in.txt\n");
					break;
			case 'i' :
					printf("Choose increasing data\n");
					/*
					*Increasing data
					*/
					for(i=0;i<N;i++)
					{
						x[i]=i;
					}
					fprint(x,in);
					fclose(in);
					printf("Increasing data write in in.txt\n");
					break;
			case 'd' :
					printf("Choose decreasing data\n");
					/*
					*Decreasing data
					*/
					for(i=0,j=N;i<N;i++,j--)
					{
						x[i]=j;
					}
					fprint(x,in);
					fclose(in);
					printf("Decreasing data write in in.txt\n");
					break;
					
			default:
					printf("Input is error,please input again\nq:quit\nr:choose random data\ni:choose increasing data\nd:choose decreasing data\n");
					break;
		}
	
		if(cmd=='r'||cmd=='i'||cmd=='d')
		{
			printf("choose is ok\n");
			break;
		}

	}
	if(cmd == 'q')
	{
					
		return 0;
			
	}

	printf("Start quick sort, please wait\n");
	begin=clock();
	quick_sort(x,0,N-1);
	end=clock();
	printf("After quick sort\n");
	time=(double)(end - begin)/CLOCKS_PER_SEC;
	
	printf("time is %f\n",time);
	fprint(x,out);
	fclose(out);
	printf("Quick sort data write in out.txt\n");
	return 0;
}

/*
* The time of quick sort	
* Random data is 0.02s
* Increasing data is 11.84s
* Decreasing data is 12.62s	
*/
 



