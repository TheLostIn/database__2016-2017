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
        q->data=i;
        q->next=NULL;
		q->pre=NULL;
		q->freq=0;
        p->next=q;
		q->pre=p;
        p=q;
 //       cout<<p->data<<" ";
    }
}
void sort(both *p,both &L)
{
	both *s,*q,*r;
	s=p->pre;
	while(((p->freq)>(s->freq))&&s!=&L)
	{
		s=s->pre;
	}
	if(p->next!=NULL)
	{
		p->pre->next=p->next;
		p->next->pre=p->pre;
		p->pre=s;
		p->next=s->next;
		s->next->pre=p;
		s->next=p;
	}else{
	
		p->pre->next=p->next;
	//	p->next->pre=p->pre;
		p->pre=s;
		p->next=s->next;
		s->next->pre=p;
		s->next=p;
//		cout<<s->data;
//		cout<<"final"<<endl;
	}
	
}
void Locate(both &L,int x)
{
	int flag=0;
	both *p,*q;
	p=L.next;
	while(p!=NULL)
	{
		if(p->data==x)
		{
//			cout<<x;
			p->freq++;
			sort(p,L);
			flag=1;
		}
		p=p->next;
	}
}

void print(both &L)
{
	both *p;
	p=L.next;
	while(p!=NULL)
	{
		cout<<p->data<<" "<<p->freq<<endl;
		p=p->next;
	}
}
int main()
{
	both head;
	int i,t;
	create(head);
	cout<<"init:"<<endl;
	print(head);
	int n=rand()%200;

//	cout<<n<<endl;

	for(i=0;i<n;i++)
	{
		t=rand()%21;
		Locate(head,t);
	}
//cout<<"-------------------"<<endl;

	cout<<"then:"<<endl;
	print(head);
	return 0;
}