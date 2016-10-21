//数据结构》第2上机题 （线性表练习）
//1. 建立元素值为整型的顺序表，编程，用插入排序算法实现顺序表排序。
//2. 建立元素值为整型的单链表，编程，用插入排序算法实现单链表排序。	
//3．用顺序结构编程实现下列功能：假设以两个元素值为整型依值递增有序排列的线性表A和B 分别表示两个集合，现要求在A的空间上构成一个新线性表C，
//其元素为A和B元素的并集，且表C中的元素也是依值递增有序排列。
//4．用单链表结构编程实现下列功能：假设以两个元素值为整型依值递增有序排列的线性表A和B 分别表示两个集合，现要求在A的空间上构成一个新线性表C，
//其元素为A和B元素的并集，且表C中的元素也是依值递增有序排列。
//5．设有一个双向循环链表，每个结点中除有pre，data和next三个域外，还增设了一个访问频度域freq。在链表被起作用前，频度域freq的值均初始化为零，
//而当对链表进行一次LOCATE(L,x)的操作之后，被访问的结点（即元素值等于x的节点）中的频度域freq的值便增1，同时调整链表中结点之间的次序，
//使其按访问频度非递增的顺序排列，以便始终保持被频繁访问的结点总是靠近表头结点。试编程实现之（习题集P19  2.38）。
#include<iostream>
#include<stdio.h>
#define OVERFLOW -2
using namespace std;
struct both{
	int data;
	both * pre;
	both * next;
	int freq;
};
void create(both &l)
{
	int i;
    both *p,*q;
    p=&l;
    
    l.data=0;
	l.freq=0;
    l.next=NULL;
    for(i=1;i<21;i++)
    {
        q = new both; 
        q->data=rand();
        q->next=NULL;
		q->pre=NULL;
        p->next=q;
		q->pre=p;
        p=q;
        cout<<p->data<<" ";
    }
}
Locate(both &L,int x)
int main()
{
	both head;
	create(head);
	return 0;
}
