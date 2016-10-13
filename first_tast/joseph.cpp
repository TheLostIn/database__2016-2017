#include<iostream>
using namespace std;
struct joseph
{
	int data;
	int flag;
	joseph * next;
};
int main()
{
	void init(joseph &);
	void linger(joseph &);
	void display(joseph &);
	joseph head;	
	init(head);
	display(head);
	linger(head);
	display(head);
	return 0;
}
void init(joseph &head)
{
	joseph * jo;
	joseph * p;
	head.data=1;
	head.next=NULL;
	head.flag=0;
	p=&head;
	int i;
	for(i=2;i<21;i++)
	{
		jo = new joseph;
		jo->data=i;
		jo->flag=0;
		jo->next=NULL;
		p->next = jo;
		p=p->next;
	}
	p->next=&head;
}
void display(joseph &head)
{
	int i=1;
	joseph *p;
	p=&head;
	while(i<21)
	{
		cout<<"p->data "<<p->data<<" p->flag "<<p->flag<<"\n";
		p=p->next;
		i++;
	}
	cout<<'\n';
}
//假设循环数是4
void linger(joseph &head)
{
	int total,count,mod;
	joseph *p;
	p=&head;
	count=0;
	total=20;
	mod=4;
	
	while(total>1)
	{
		
		if(!p->flag)
		{
			count++;
			if(count%mod==0)
			{
				p->flag=1;
				total--;
			}
		}
		p=p->next;
	}
		while(p->flag)
	{
		p=p->next;
	}
		cout<<"survive: "<<p->data<<"\n";


}