//����һ��˫��ѭ������ÿ������г���pre��data��next�������⣬��������һ������Ƶ����freq��
//������������ǰ��Ƶ����freq��ֵ����ʼ��Ϊ�㣬�������������һ��LOCATE(L,x)�Ĳ���֮��
//�����ʵĽ�㣨��Ԫ��ֵ����x�Ľڵ㣩�е�Ƶ����freq��ֵ����1��ͬʱ���������н��֮��Ĵ���
//ʹ�䰴����Ƶ�ȷǵ�����˳�����У��Ա�ʼ�ձ��ֱ�Ƶ�����ʵĽ�����ǿ�����ͷ���

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
	cout<<"����˫��ѭ������L��"<<endl;
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
	cout<<"�����������ȣ�";
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
	cout<<endl<<"---------�������---------"<<endl;
	return 0;
}

int Print_L(LinkList L)
{
	cout<<endl<<"L��";
	LinkList q = L->next;
	int i = 1;
	while( q!=L )
	{
		cout<< i <<"��data:"<<q->data<<"  freq:"<<q->freq<<endl;
		q = q->next;
		i++;
	}
	return 0;
}

int Sort_L(LinkList L,LinkList p)
{
	
	LinkList newhead = p;
//	p->next = NULL;
	LinkList pre;      //preָ�����λ�õ�ǰ�� 
	LinkList pre_t;    //pre_tָ��ǰԪ�ص�ǰ�� 
	LinkList t;            //tΪ��ǰλ�õ�Ԫ�� 
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
	cout<<endl<<"������������Locate�����С�������"<<endl<<endl;
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
	cout<<"��Ƶ��freq����������"<<endl;
//	Sort_L(L);
	Print_L(L);
	return 0;
}
