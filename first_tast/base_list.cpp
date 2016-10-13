#include<iostream>
using namespace std;
#define LIST_INIT_SIZE 100
#define LIST_INCREMENT 10
#define ElemType int
typedef struct {
	ElemType *elem;
	int length;
	int listsize;
} SqList;

class List{
public:
	void InitList(SqList &);
	void DestroyList(SqList &);
	void ClearList(SqList &);
	int ListLength(SqList);
	void GetElem(SqList,int,int &);
	void LocateElem(SqList,int);
	void ListInsert(SqList &,int,int);
	void ListDelete(SqList &,int,ElemType &);
	void TraverseList(SqList);
	void Error(char *s);
	void Increment(SqList &);
};
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
void List::Error(char *s)
{
	cout<<s<<endl;
	exit(1);	
}
void List::InitList(SqList &L)
{
	L.elem = new ElemType[LIST_INIT_SIZE];
	if(!L.elem) Error("Overdlow");
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
}
void List::DestroyList(SqList &L)
{
	delete []L.elem;
	L.length = 0;
	L.listsize = 0;
}
void List::ClearList(SqList &L)
{
	L.length = 0;
}
int List::ListLength(SqList L)
{
	return L.length;
}
void List::GetElem(SqList L,int i,ElemType &e)
{
	if((i<1)||(i>L.length))
		Error("Position Error");
	e = L.elem[i-1];
}
int LocateElem(SqList L,ElemType e)
{
	int i = 1,*p;
	p = L.elem;
	while((i<=L.length)&&(*p++!=e)) i++;
	if(i<=L.length) return i;
	else return 0;
}
void List::ListInsert(SqList &L,int i,ElemType e)
{
	ElemType *q,*p;
	if((i<1)||(i>L.length+1))
	{
		Error(" Position Error");
	}
	if(L.length>=LIST_INIT_SIZE)
	{
		Increment(L);
	}
	q = &(L.elem[i-1]);
	for(p = &(L.elem[L.length-1]);p>=q;--p)
	{
		*(p+1) = *p;
	}
	*q = e;
	++L.length;
}
void List::Increment(SqList &L)
{
	ElemType *newlist;
	int i;
	newlist = new ElemType[L.listsize+LIST_INCREMENT];

	if(! newlist) Error(" Overflow");
	for(i = 0;i<L.length;i++)
	{
		newlist[i] = L.elem[i];
	}
	delete []L.elem;
	L.elem = newlist;//移交空间首地址
	L.listsize += LIST_INCREMENT;
}
void List::ListDelete(SqList &L,int i,ElemType &e)
{
	ElemType *p,*q;
	if((i<1)||(i>L.length))
	{
		Error("Position Error");
	}
	e = L.elem[i-1];
	p = &(L.elem[i-1]);
	q = L.elem + L.length -1;
	for(++p;p <= q;++p)
	{
		*(p-1) = *p;
	}
	--L.length;
}
void List::TraverseList(SqList L)
{
	int i;
	ElemType *p;
	if(L.length != 0)
	{
		i = 1;
		p = L.elem;
		while(i <= L.length)
		{
			cout<<*p++;
			i++;
		}
	}
}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
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