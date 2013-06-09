/**********************************************************************************************
*** Filename:
***		Linked_list.c
***	Copyright (c) 2013 Wistron
***	All rights reserved.
***
***	Description:
***		Creat a linked list, you can insert and delete nodes, print the list.
***	Author/Creat Date:
*** 		Tenix Xu, Jun 07, 13
***
***	Modification History:
***
***	Note:
***
************************************************************************************************/

#include <stdlib.h>
#include <stdio.h> 
#include <string.h>


/*the node */
struct node{
	int num;
	char name[40];
	char sex[10];
	unsigned age;
	struct node* next;
};

struct node *nodep,*head;

/*****************************************************************************************
***	Description:		
***		 Creat node 
***	
***	Return Value:
***		Return head pointer.
*******************************************************************************************/
struct node* creat(struct node* head)
{
	struct node* temp,*newp;
	newp = (struct node*)malloc(sizeof(struct node*));
	if(newp ==NULL)
	{
		printf("malloc is error\n");
		return NULL;
	}
	
	printf("Please input a number:\n");
	scanf("%d",&newp->num);
	printf("Please input a name:");
	scanf("%s",newp->name);
	printf("Please input sex:");
	scanf("%s",newp->sex);
	printf("Please input age:");
	scanf("%d",&newp->age);
	printf("\n");
	
	if( head==NULL )
	{
		head=newp;
		head->next=NULL;
	}
	else
	{
		printf("error,node is exit,please insert\n");
		return head;
	}
	printf("creat a node is ok\n");
	return head;
}

/*****************************************************************************************
***	Description:		
***		 Insert node 
***	
***	Return Value:
***		Return head pointer.
*******************************************************************************************/
struct node* insert(struct node* head)
{
	struct node *temp,*newp,*p;
	p=temp=head;
	newp = (struct node*)malloc(sizeof(struct node));
	if(newp==NULL)
	{
		printf("malloc is error\n");
	}
	if(head==NULL)
	{
		printf("please creat a node first\n");
		return;
	}
	printf("Input the number:");
	scanf("%d",&newp->num);
	printf("Input the name:");
	scanf("%s",newp->name);
	printf("Input the sex:");
	scanf("%s",newp->sex);
	printf("Input the age:");
	scanf("%d",&newp->age);
 


	while((p->num<newp->num)&&(p->next!=NULL))
	{
		temp=p;
		p=p->next;
	}

	if(p->num < newp->num)
	{		
		p->next=newp;
		newp->next=NULL;
	}
	else
	{	
		temp->next=newp;
		newp->next=p;

	}
	printf("insert a node is ok\n");
	return head;
  
}


/*****************************************************************************************
***	Description:		
***		 Delete node 
***	
***	Return Value:
***		Return head pointer.
*******************************************************************************************/
struct node* del(struct node* head,int num)
{
	struct node* p,*temp;
	p=head;	
	if( head==NULL )
	{
		printf("head is NUll\n");
		return;	
	}	
	while((p->num!=num)&&(p->next!=NULL))
	{
		temp=p;
		p=p->next;
	}
	if(p->num == num)
	{
		if( head == p )
		{
			head=head->next;
			printf("delete num is ok:%d\n",num);	
			return head;
		}
		else
		{
			temp->next=p->next;
			printf("delete num is ok:%d\n",num);
			return head;
		}
	}
	else
	printf("no this number\n");	
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
		printf("please creat a node first\n");
		return;
	}
	else
	{
		while(temp !=NULL)
		{
			printf("num:%d  name:%s  sex:%s  age:%d  \n",temp->num,temp->name,temp->sex,temp->age);
			temp=temp->next;
		}
	}
}


/*****************************************************************************************
***	Description:		
***		 the main function 
***	
***	Return Value:
***		    0
*******************************************************************************************/
int main()
{
	int num;
	char cmd;
	head=NULL;
	printf("c:creat a node\ni:insert a node\nd:delete a node\ns:show all information\ne:exit\n");		
		
	while(1)
	{
		scanf("%c",&cmd);
		if(cmd == 'c')
		{
			head=creat(head);
			show(head);		
		}
		else if(cmd == 'i')
		{
			insert(head);
		}
		else if(cmd == 'd')
		{
			printf("input the number you want to delete: ");
			scanf("%d",&num);
			head=del(head,num);		
		}
		else if(cmd == 's')
		{
			show(head);
		}
		else if(cmd == 'e')
		{
			break;
		}
	}
	return 0; 
}




































