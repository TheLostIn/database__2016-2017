//数据结构》第2上机题 （线性表练习）
//1. 建立元素值为整型的顺序表，编程，用插入排序算法实现顺序表排序。
//2. 建立元素值为整型的单链表，编程，用插入排序算法实现单链表排序。	
//3．用顺序结构编程实现下列功能：假设以两个元素值为整型依值递增有序排列的线性表A和B 分别表示两个集合，现要求在A的空间上构成一个新线性表C，
//其元素为A和B元素的并集，且表C中的元素也是依值递增有序排列。
//4．用单链表结构编程实现下列功能：假设以两个元素值为整型依值递增有序排列的线性表A和B 分别表示两个集合，现要求在A的空间上构成一个新线性表C，
//其元素为A和B元素的并集，且表C中的元素也是依值递增有序排列。
//5．设有一个双向循环链表，每个结点中除有pre，data和next三个域外，还增设了一个访问频度域freq。在链表被起作用前，频度域freq的值均初始化为零，而当对链表进行一次LOCATE(L,x)的操作之后，被访问的结点（即元素值等于x的节点）中的频度域freq的值便增1，同时调整链表中结点之间的次序，使其按访问频度非递增的顺序排列，以便始终保持被频繁访问的结点总是靠近表头结点。试编程实现之（习题集P19  2.38）。
#include<iostream>
#include<stdio.h>
#define OVERFLOW -2
using namespace std;
struct list
{
	int *elem;
	int length;
	int listsize;
};
void create(list &l,int n)
{
	int i;

	l.elem=(int *)malloc(n*sizeof(int));
	if(!l.elem) exit(OVERFLOW);
	l.length=n;
	l.listsize=n;
	for(i=0;i<n;i++)	
	{
		l.elem[i]=rand();
	}
}
void sort(int *a,int n)
{
	int i,j,k,temp;
	for(i=0;i<n;i++)
	{
		for(j=0;a[i]>a[j]&&j<i;j++)
		{			
		}
		if(j<i)
		{
			temp=a[i];
			for(k=i;k>j;k--)
			{
				a[k]=a[k-1];
			}
			a[j]=temp;
		}
	}
	for(i=0;i<n;i++)
	{
	
		cout<<a[i]<<" ";
	}
	cout<<endl;
}
void print(list &l)
{
	int i;
	for(i=0;i<l.length-1;i++)
	{
		cout<<l.elem[i]<<" ";
		if(i%5==0) cout<<endl;
	}
	cout<<endl;
}
void m_sort(list &l1,list &l2)
{
	int i=0,j=0,k,temp;
	int *a,*b;
	a=l1.elem;
	b=l2.elem;

	while(i<l1.length&&j<l2.length)
	{
		if(a[i]>b[j])
		{
		
			for(k=l1.length;k>i;k--)
			{
				a[k]=a[k-1];
			}
			a[i]=b[j];
			j++;
			l1.length++;
		}else{
			i++;
		}
	}
	cout<<l1.listsize<<l1.length<<" "<<b[j]<<" "<<a[i]<<" "<<i<<" "<<j<<" "<<endl;
//	a[i]=;
	//a[i]=9;
	if(i==l1.length&&i<l1.listsize)
	{
	
		for(k=i;k<l1.listsize;k++)
		{
			a[k]=b[j];
			cout<<k<<" "<<j<<" ";
			l1.length++;
			j++;
		}
	}

	


}
void recreate(list &L1,int n)
{
	int *newbase;
	newbase=(int *)realloc(L1.elem,(L1.length+n)*sizeof(int));
	if(!newbase) exit(OVERFLOW);
	L1.listsize+=n;
}
int main()
{
	int n=8;
	list L1,L2;
	create(L1,n);
	create(L2,n);
	sort(L1.elem,L1.length);
	sort(L2.elem,L2.length);
	recreate(L2,L1.length);
	m_sort(L2,L1);
	print(L2);
	return 0;
}