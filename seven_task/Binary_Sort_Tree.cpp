#include<iostream>
#include<string>
using namespace std;
//Binary Sort Tree
typedef int InfoType;
typedef int ElemType;
typedef struct{
	ElemType key;
	InfoType otherinfo;
}RedType;

typedef struct BSTNode{
	RedType data;
	BSTNode *lchild,*rchild;
	BSTNode()
	{
		lchild=NULL;
		rchild=NULL;
	}
}BSTNode;
typedef BSTNode *BSTree;
void Error(string s)
{
	cout<<s<<endl;
	exit(1);
}
BSTree SearchBST(BSTree T,ElemType k)
{
	if(T==NULL) return NULL;
	else if(k==T->data.key) return T;
	else if(k<T->data.key) return SearchBST(T->lchild,k);
	else return SearchBST(T->rchild,k);
}
void Insert(BSTree &T,BSTNode *p)
{
	if(T==NULL) p=T;
	else if(p->data.key==T->data.key) Error("The key already exist!");
	else if(p->data.key<T->data.key) Insert(T->lchild,p);
	else Insert(T->rchild,p);
}
void InsertBST(BSTree &T,RedType r)
{
	
	if(!(SearchBST(T,r.key)))
	{
		BSTree s;
		s=new BSTNode;
		s->data=r;
		Insert(T,s);
	}
}

void CreateBST(BSTree &T,RedType r[],int n)
{
	int i;
	BSTree s;
	for(i=0;i<n;i++)
	{
		s=new BSTNode;
		s->data=r[i];
		InsertBST(T,s->data);
	}
}
void Delete(BSTree &T,BSTNode *p,BSTNode *f)
{
	if(!(p->lchild)&&!(p->rchild))
	{
		if(f->lchild==p) f->lchild=NULL;
		else f->rchild=NULL;
		delete p;
	}
	else if(!p->lchild)
	{
		if(f->lchild==p) f->lchild=p->rchild;
		else f->rchild=p->rchild;
		delete p;
	}
	else if(!p->rchild)
	{
		if(f->lchild==p) f->lchild=p->lchild;
		else f->rchild=p->lchild;
		delete p;
	}
	else
	{
		BSTNode *q,*fq;
		fq=p;
		q=p->rchild;
		while(q->lchild!=NULL)
		{
			fq=q;
			q=q->lchild;
		}
		p->data=q->data;
		if(fq==p)
		{
			fq->rchild=q->rchild;
		}
		else
		{
			fq->lchild=q->rchild;
		}
		delete q;
	}
}
void DeleteBST(BSTree &T,ElemType k)
{
	BSTree parent;
	BSTree p=T;
	while(p)
	{
		if(k==p->data.key) break;
		parent=p;
		if(k<p->data.key) p=p->lchild;
		else p=p->rchild;
	}
	if(!p) Error("Your key is not here!");
	else Delete(T,p,parent);
}
int main()
{
	return 0;
}