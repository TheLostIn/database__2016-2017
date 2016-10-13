#include<iostream>
using namespace std;
#define ElemType int
typedef struct LNode 
{
	ElemType data;
	struct LNode *next;
} LNode;
typedef LNode *LinkList;
class L_List
{
public:
	void InitList(LinkList &L);
	LNode * LocateElem(LinkList L,ElemType e);
	void Error(char *s);
	void DestroyList(LinkList &L);
	void ClearList(LinkList &L);
	void GetElem(LinkList L,int i,ElemType &e);
	void ListInsert(LinkList &L,int i,ElemType e);
	void ListDelete(LinkList &L,int i,ElemType &e);
	void TraverseList(LinkList L);
};
void L_List::InitList(LinkList &L)
{
	L = new LNode;
	L -> next = NULL;
}
void L_List::Error(char *s)
{
	cout<<s<<endl;
	exit(1);	
}
void L_List::DestroyList(LinkList &L)
{
	LNode *p;
	while(L)
	{
		p = L;
		L = L->next;
		delete p;
	}
}
void L_List::ClearList(LinkList &L)
{
	LNode *p,*q;
	p=L->next;
	while(p)
	{
		q = p;
		p = p->next;
		delete q;
	}
	L->next = NULL;
}
int ListLength(LinkList L)
{
	LNode *p;
	p = L;
	int length = 0;
	while(p->next)
	{
		length++;
		p = p->next;
	}
	return length;
}
void L_List::GetElem(LinkList L,int i,ElemType &e)
{
	LNode *p;
	p = L->next;
	int j = 1;
	while(p&&(j<i))
	{
		p = p->next;
		++j;
	}
	if(!p||(j>i)) Error("Position Error");
	else e = p->data;
}
LNode * L_List::LocateElem(LinkList L,ElemType e)
{
	LNode *p;
	p = L->next;
	while(p&&(p->data!=e))
		p = p->next;
	return p;
}
void L_List::ListInsert(LinkList &L,int i,ElemType e)
{
	LNode *p,*s;
	p = L;
	int j = 0;
	while(p&&(j<i - 1))
	{
		p = p -> next;
		++j;
	}
	if(!p||(j > i-1)) 
	{
		Error("Position Error");
	}
	else 
	{
		s = new LNode;
		s -> data = e;
		s -> next = p->next;
		p -> next = s;
	}
}
void L_List::ListDelete(LinkList &L,int i,ElemType &e)
{
	int j;
	LNode *p,*q;
	p = L;
	j = 0;
	while((p -> next)&&(j < i-1))
	{
		p = p->next;
		++j;
	}
	if(!(p -> next)||(j > i-1))
	{
		Error("Position Error");

	}
	q = p -> next;
	e = q -> data;
	p -> next = q -> next;
	delete q;
}
void L_List::TraverseList(LinkList L)
{
	LNode *p;
	p = L-> next;
	while(p)
	{
		cout<<p->data;
		p = p->next;
	}
}
int main()
{
	return 0;
}