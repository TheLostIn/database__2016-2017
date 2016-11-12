#include<iostream>
#include<stdio.h>
using namespace std;
#define N 8
struct stack{
	int row,col;
};
void pop(stack *p,int &top,int &row,int &col)
{
	if(top>=0&&top<=N)
	{
		row=p[top].row;
		col=p[top].col;
		p[top].col=-1;
		top--;
	}else{
		cout<<"wrong top pop"<<endl;
		exit(1);
	}
}
void push(stack *p,int &top,int row,int col)
{	
	if(top<=N&&top>=0)
	{	
		top++;
		p[top].row=row;
		p[top].col=col;
	
	}else{
		cout<<"wrong top"<<endl;
		exit(1);
	}
}
int back_search(stack *p,int top,int row,int col)
{
	int i;
	for(i=1;i<=top;i++)
	{
		if(p[i].col==col||(row-p[i].row)==(col-p[i].col)||(p[i].row-row)==(col-p[i].col))
		{
			return 0;
		}
	}
	return 1;
}
void display(stack *p)
{
	int i=0,j;
	cout<<endl;
	for(i=1;i<=N;i++)
	{
		for(j=0;j<N;j++)
		{
			if(j!=p[i].col)
			{
				cout<<0<<" ";
			}else{
				cout<<1<<" ";
			}
		}
		cout<<endl;
	}
}
void queen()
{
	stack s[N+1];
	int i=0,j=0,top=0;
	for(i=1;i<=N;i++)
	{
		s[i].row=0;
		s[i].col=-1;
	}
	i=0;
	j=0;
	push(s,top,i,j);
	i++;
	int count=0;
	while(!(i==0&&j==N))
	{
		if(j<N){
			if(back_search(s,top,i,j))
			{
			
				push(s,top,i,j);
				i++;
				j=0;
				if(i==N)
				{	count++;
					display(s);
				}
			}else{
				j++;
			}
		}else{
			if(j>=N){
				pop(s,top,i,j);
				j++;
			}
		}
	}
	cout<<count<<endl;
}
int main()
{
	queen();
	return 0;
}