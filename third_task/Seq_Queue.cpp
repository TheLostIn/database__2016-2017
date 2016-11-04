#include<iostream>
using namespace std;
#define QUEUE_MAX_SIZE 100
typedef int ElemType;
typedef struct QNode{
	ElemType data;
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
void GetHead_Sq_L(LinkQueue Q,ElemType &e);
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
void GetHead_Sq_L(LinkQueue Q,ElemType &e)
{
	if(Q.front->next==NULL) ERROR("Queue Empty");
	e=Q.front->next->data;
}
void EnQueue_L(LinkQueue &Q,ElemType e)
{
	QNode *p;
	p=new QNode;
	p->data=e;
	p->next=NULL;
	Q.rear->next=p;
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
int main()
{
	return 0;
}