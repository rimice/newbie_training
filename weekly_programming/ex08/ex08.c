/**********************************************************************************************
*** Filename:
***		ex08.c
***	Copyright (c) 2013 Wistron
***	All rights reserved.
***
***	Description:
***		Use linked list to generate the random increasing number
***	Author/Creat Date:
*** 		Tenix Xu, July 26, 13
***
***	Modification History:
***	    
***	Note:
***
************************************************************************************************/


#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 50000
#define M 1000


/*
*the node
*/
struct node 
{
	int number;
	struct node *next;
};
struct node *head;



/*****************************************************************************************
***	Description:		
***		 Creat node 
***	
***	Return Value:
***		Return head pointer.
*******************************************************************************************/
struct node* creat(struct node* head)
{
	struct node *newp;
	newp = (struct node*)malloc(sizeof(struct node*));
	if(newp ==NULL)
	{
		printf("malloc is error\n");
		return NULL;
	}
	
	if( head==NULL )
	{
		head=newp;
		head->next=NULL;
	}
	return head;
}



/*****************************************************************************************
***	Description:		
***		 Insert node 
***	
***	Return Value:
***		Return head pointer.
*******************************************************************************************/
struct node* insert(struct node * head;)
{	int i,j;
	struct node *temp,*p;

	srand(time(NULL));
	int *number=(int *)malloc(M*sizeof(long long int));	

	if(head==NULL)
	{
		printf(" head is error\n");
		return ;
	}
	

	int tem=0;
	head->number=rand()%N;
	head->next=NULL;
	number[0]=head->number;
	p=head;
	printf("head=%d\n",head->number);
	/*
	*Generate and check a random number
	*/
	for(j=1;j<M;j++)
	{
		tem=rand()%N;
		for(i=0;i<j;i++)
		{	
			if (tem == number[i])
			{	
				printf("number=%d is the exit,reselect\n",tem);
				tem=rand()%N;
			}	
			
		}
		number[j]=tem;
		printf("number[%d]=%d \n",j,number[j]);
		
		/*
		*Insert a number
		*/
		struct node *newp=(struct node* )malloc(sizeof(struct node));temp=NULL;
		if(newp==NULL)
		{
			printf("malloc is error\n");
		}
		
		newp->number=tem;
		newp->next=NULL;
		printf(" To insert a number:%d\n",number[i]);
		while((p->number < newp->number) && (p->next !=NULL ))
		{
			temp=p;
			p=p->next;
		}
		
		if(p->number < newp->number)
		{
			p->next=newp;
			newp->next=NULL;
			printf("insert on the tail, number= %d\n",newp->number);
		}
		else
		{
			if(p==head)
			{
				head=newp;
				newp->next=p;
				printf("insert on the start, number= %d\n",newp->number);
			}
			else
			{
				temp->next=newp;
				newp->next=p;
				printf("insert in the region, number=%d\n",newp->number);
			}
		}
		p=head;
	}
	return head;
}
/*****************************************************************************************
***	Description:		
***		 Display node 
***	
***	Return Value:
***		Void
*******************************************************************************************/
void show(struct node* head)
{
	struct node* temp;
	temp=head;
	if(temp==NULL)
	{
		printf("creat a node is error\n");
		return;
	}
	else
	{
		while(temp !=NULL)
		{
			printf("number:%d	 \n",temp->number);
			temp=temp->next;
		}
	}
}


/*****************************************************************************************
***	Description:		
***		 Printf node in a file 
***	
***	Return Value:
***		 Void
*******************************************************************************************/
void fprint(FILE *fd,struct node * head)
{
	struct node* temp;
	temp=head;
	if(temp==NULL)
	{
		printf("creat a node is error\n");
		return;
	}
	else
	{
		while(temp !=NULL)
		{
			fprintf(fd,"number:%d\n",temp->number);
			temp=temp->next;
		}
	}
			
}

/*****************************************************************************************
***	Description:		
***		 the main function 
***	
***	Return Value:
***		    Void
*******************************************************************************************/
void main()
{
	head =NULL;
	FILE *out=fopen("out.txt","w+");
	if( out == NULL)
	{
		printf("open out.txt is error\n");
	}

	head=creat(head);
	insert(head);
	show(head);
	fprint(out,head);
	fclose(out);
	printf("random increasing data write in out.txt\n");
}
