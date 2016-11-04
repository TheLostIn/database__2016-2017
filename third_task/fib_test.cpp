#include<iostream>
using namespace std;
#define QUEUE_MAX_SIZE 100
#define MAX_NUM 400000000
#define k 10
typedef int ElemType;
typedef struct QNode{
	ElemType data;
	int flag;
	struct QNode *next;
}QNode,*QueuePtr;
typedef struct{
	QueuePtr front;
	QueuePtr rear;
} LinkQueue;
void InitQueue_L(LinkQueue &Q);
void DestroyQueue_L(LinkQueue &Q);
void ClearQueue_L(LinkQueue &Q);
int QueueLength_L(LinkQueue Q);
void GetHead_Sq_L(LinkQueue &Q,ElemType &e);
void EnQueue_L(LinkQueue &Q,ElemType e);
void DeQueue_L(LinkQueue &Q,ElemType &e);
void ERROR(char *s)
{
	cout<<s<<endl;
	exit(1);	
}
void InitQueue_L(LinkQueue &Q)
{
	Q.front=Q.rear=new QNode;
	Q.front->next=NULL;
	Q.front->flag=9999;
	Q.front->data=0;
	Q.rear->next=Q.front;

}
void DestroyQueue_L(LinkQueue &Q)
{
	while(Q.front)
	{
		Q.rear=Q.front->next;
		delete Q.front;
		Q.front=Q.rear;
	}
}
void ClearQueue_L(LinkQueue &Q)
{
	QNode *p,*q;
	p=Q.front->next;
	while(p)
	{
		q=p;
		p=p->next;
		delete q;
	}
	Q.front->next=NULL;
	Q.rear=Q.front;
}
int QueueLength_L(LinkQueue Q)
{
	QNode *p;
	int length=0;
	p=Q.front;
	while(p->next)
	{
		length++;
		p=p->next;
	}
	return length;
}
void GetHead_Sq_L(LinkQueue &Q,ElemType &e)
{
	if(Q.front->next==NULL) ERROR("Queue Empty");
	e=Q.front->data;
	Q.front=Q.front->next;
	cout<<"flag:------"<<Q.front->flag<<endl;
}
void EnQueue_L(LinkQueue &Q,ElemType e,int i)
{
	QNode *p;
	p=new QNode;
	p->data=e;
	p->flag=i+1;
	p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
	cout<<endl<<"e: "<<e<<endl;
}
void DeQueue_L(LinkQueue &Q,ElemType &e)
{
	QNode *p;
	if(Q.front->next==NULL)
	{
		ERROR("Queue Empty");
	}
	p=Q.front->next;
	e=p->data;
	Q.front->next=p->next;
	if(Q.rear==p) Q.rear=Q.front;
	delete p;
}
void update_Queue(LinkQueue &Q,ElemType e)
{
	Q.rear=Q.rear->next;
	Q.rear->data=e;

//	cout<<endl<<"flag: "<<Q.front->data<<endl;
	
}
void print(LinkQueue &Q)
{
	QNode *p;
	p=Q.front;
	cout<<"flag: "<<p->flag<<" data: "<<p->data<<endl;
	p=p->next;
	while(p!=Q.front)
	{
		cout<<"flag: "<<p->flag<<" data: "<<p->data<<endl;
		p=p->next;
	}
}
int main()
{
	LinkQueue Q;
	int e,p;
	int i,t,temp;
	InitQueue_L(Q);
	for(i=0;i<k-2;i++)
	{
		EnQueue_L(Q,0,i);
		cout<<endl<<i;
	}
	EnQueue_L(Q,1,k-2);
	
//	update_Queue(Q,1);

	Q.rear->next=Q.front;
	GetHead_Sq_L(Q,e);
	update_Queue(Q,1);
	cout<<endl<<"start"<<endl;
	print(Q);
	cout<<endl<<"stop--"<<endl;


	cout<<"ppppppp"<<endl;
	cout<<Q.front->flag<<endl;
	cout<<Q.rear->flag<<endl;
	temp=1;
	while(temp<MAX_NUM)
	{
		GetHead_Sq_L(Q,e);
		//	cout<<"ppppppp"<<endl;
		cout<<endl<<"e:"<<e<<"temp:"<<temp<<endl;
		update_Queue(Q,temp*2-e);
		temp=temp*2-e;
		cout<<temp<<endl;

		print(Q);
	//	cin>>p;
	}

	return 0;
}