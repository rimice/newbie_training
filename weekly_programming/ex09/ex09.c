/**********************************************************************************************
*** Filename:
***		ex09.c
***	Copyright (c) 2013 Wistron
***	All rights reserved.
***
***	Description:
***		Using template to define a C++ class for the priority of ternary-tree
***
***	Author/Creat Date:
*** 		Tenix Xu, July 31,13
***
***	Note:
***
************************************************************************************************/
#include <iostream>  
#include<stdio.h>
#include<ctype.h>
using namespace std;  
/*
* template 
*/
template<class T>  
class priqueue 
{  
	public:  
		/*
		*init 
		*/
   		priqueue(int m)
   		{   
			maxsize = m;  
      		x = new T[maxsize+1];  
        	n = 0;  
		}  
		/*
		*add T
		*/
		void insert(T t)  
    		{   
				int i, r;  
        		x[++n] = t; 
        		for (i = n; i > 1 && x[r=(i+1)/3] > x[i]; i = r)      
				swap(x[r], x[i]);  
                 
    		}  
        /*
		*return smallest
		*/
   		 T extractmin()
    		{                
				int r, i;
				T t = x[1];
				x[1] = x[n--];
				T min_index;
				for(r=1;(i=3*r)+1 <= n; r = i)
				{
					min_index = x[i-1]<x[i] ? i-1 : i;
					min_index = x[i+1]<x[min_index] ? i+1 : min_index; 
					if(x[r] <= x[min_index])
					break;
					swap(x[r],x[min_index]);
					i++;
				}
				return t;  
    		}  
    	/*
		*print
		*/
   		 void print()  
    		{  
      			for (int i = 1; i < n+1; i++) 
          		cout << x[i] << " ";  
    		}  
	private:  
    		int n, maxsize;  
    		T   *x;  
			void swap(int &i, int &j)
			{   
				T t = i; 
				i = j; 
				j = t; 
			}  

};  
 
/*****************************************************************************************
***	Description:		
***		 the main function 
***	
***	Return Value:
***		    0
*******************************************************************************************/
int main(void)  
{   
	int n; 
    int number,num;
	int min;
	priqueue<int> p(0); 
	cout<<"please, insert how many number to insert"<<endl;
	cin>>num;
	cout<<num<<endl;
	for(n=0;n<num;n++)
	{	
		cout<<"please,insert a number"<<endl;
		cin>>number;
		p.insert(number);
		p.print();
		cout<<endl;
	}
		min=p.extractmin();
		cout<<"The smallest num is :"<<min<<endl;
	return 0;
}

  

