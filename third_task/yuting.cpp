//设有一个双向循环链表，每个结点中除有pre，data和next三个域外，还增设了一个访问频度域freq。
//在链表被起作用前，频度域freq的值均初始化为零，而当对链表进行一次LOCATE(L,x)的操作之后，
//被访问的结点（即元素值等于x的节点）中的频度域freq的值便增1，同时调整链表中结点之间的次序，
//使其按访问频度非递增的顺序排列，以便始终保持被频繁访问的结点总是靠近表头结点

#include<iostream>
#include<malloc.h>
#include<stdlib.h>
using namespace std;
typedef int Elemtype;

typedef struct LNode
{
	Elemtype data;
	struct LNode *next;
	struct LNode *pre;
	int freq;
}LNode,*LinkList;

int Create_L(LinkList &L)
{
	cout<<"建立双向循环链表L："<<endl;
	L = (LinkList)malloc(sizeof(LNode));
	if( !L )
	{
		cout<<"ERROR"<<endl;
		exit(0);
	}
//	L->next = L;
//	L->pre = L;
	L->next=NULL;
	L->pre=NULL;
	L->freq=0;
	L->data=0;
	cout<<"请输入链表长度：";
	int i,n;
	cin>>n;
	LinkList p = L,q;
	for(i=0;i<n;i++)
	{
		q = (LinkList)malloc(sizeof(LNode));
		q->next = NULL;
		q->pre=NULL;
		q->data = i+1;
		q->freq = 0;
		cout<<q->data<<"  ";
	
		q->pre = p;
		p->next = q;
		p = q;
    }
//	q->next = L;
//	L->pre = q;
	cout<<endl<<"---------建立完成---------"<<endl;
	return 0;
}

int Print_L(LinkList L)
{
	cout<<endl<<"L：";
	LinkList q = L->next;
	int i = 1;
	while( q!=L )
	{
		cout<< i <<"、data:"<<q->data<<"  freq:"<<q->freq<<endl;
		q = q->next;
		i++;
	}
	return 0;
}

int Sort_L(LinkList L,LinkList p)
{
	
	LinkList newhead = p;
//	p->next = NULL;
	LinkList pre;      //pre指向插入位置的前驱 
	LinkList pre_t;    //pre_t指向当前元素的前驱 
	LinkList t;            //t为当前位置的元素 
	cout<<"pppp"<<endl;
	LinkList pp;
	pp=L;
	while(pp)
	{
		cout<<pp->data<<" "<<pp->freq<<endl;
		pp=pp->next;
	}
	pp=L->next;
	cin>>pp->next->data;
	cout<<endl<<newhead->data;
	while( newhead!=L&&newhead->freq<=p->freq )
	{
		newhead=newhead->pre;
		cout<<newhead->data;
	}
	cout<<"pppppp"<<endl;
	cin>>pp->data;
	if(p->next!=NULL&&newhead!=L)
	{
		p->next->pre=p->pre;
		p->pre->next=p->next;
		p->pre=newhead->pre;
		p->next=newhead;
		newhead->pre->next=p;
		newhead->next->pre=p;
	}else if(p->pre==L){
	
	}else if(p->pre!=L){
		p->pre->next=p->next;
		p->pre=newhead->pre;
		p->next=newhead;
		newhead->pre->next=p;
		newhead->next->pre=p;		
	}


	return 0;
}

int Locate_L(LinkList &L,int x)
{
	LinkList p = L->next;
	for( p;p != L;p = p->next )
	{
		if( p->data == x )  
		{
			p->freq++;
			cout<<p->freq;
			Sort_L(L,p);
		} 
	}
	return 0;
}

int main()
{
	LinkList L;
	Create_L(L);
	cout<<endl<<"————调用Locate函数中————"<<endl<<endl;
	Locate_L(L,1);
	Locate_L(L,1);
	Locate_L(L,1);
	Locate_L(L,2);
	Locate_L(L,1);
	Locate_L(L,3);
	Locate_L(L,3);
	Locate_L(L,6);
	Locate_L(L,6);
	Locate_L(L,6);
	cout<<"按频度freq排序后的链表："<<endl;
//	Sort_L(L);
	Print_L(L);
	return 0;
}
