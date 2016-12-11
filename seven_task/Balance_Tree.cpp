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
	int bf;//balance factor
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
	cout<<"Search: "<<k<<endl;
	if(T==NULL) return NULL;
	else if(k==T->data.key) return T;
	else if(k<T->data.key) return SearchBST(T->lchild,k);
	else return SearchBST(T->rchild,k);
}
void Insert(BSTree &T,BSTNode *p)
{
	if(T==NULL) T=p;
	else if(p->data.key==T->data.key) Error("The key already exist!");
	else if(p->data.key<T->data.key) Insert(T->lchild,p);
	else Insert(T->rchild,p);
}
void InsertBST(BSTree &T,RedType r)
{
	
	if(!(SearchBST(T,r.key)))
	{
		cout<<"p"<<endl;
		BSTree s;
		s=new BSTNode;
		s->data=r;
		cout<<"InsertBST: "<<s->data.key<<endl;
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
		cout<<"Insert: "<<s->data.key<<endl;
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
void R_Rotate(BSTree &p)
{
	BSTree lc;
	lc=p->lchild;
	p->lchild=lc->rchild;
	lc->rchild=p;
	p=lc;
}
void L_Rotate(BSTree &p)
{
	BSTree rc;
	rc=p->rchild;
	p->rchild=rc->lchild;
	rc->lchild=p;
	p=rc;
}
#define LH +1
#define EH 0
#define RH -1
void LeftBalance(BSTree &T)
{
	BSTree lc,rd;
	lc=T->lchild;
	switch(lc->bf)
	{
	case LH:
		T->bf=lc->bf=EH;
		R_Rotate(T);
		break;
	case RH:
		rd=lc->rchild;
		switch(rd->bf)
		{
			case LH: T->bf=RH;lc->bf=EH;break;
			case EH: T->bf=lc->bf=EH;break;
			case RH: T->bf=EH;lc->bf=LH;break;
		}
		rd->bf=EH;
		L_Rotate(T->lchild);
		R_Rotate(T);
	}
}
void RightBalance(BSTree &T)
{
	BSTree rc,ld;
	rc=T->rchild;
	switch(rc->bf)
	{
	case RH:
		T->bf=rc->bf=EH;
		L_Rotate(T);
		break;
	case LH:
		ld=rc->lchild;
		switch(ld->bf)
		{
			case LH: T->bf=LH;rc->bf=EH;break;
			case EH: T->bf=rc->bf=EH;break;
			case RH: T->bf=EH;rc->bf=RH;break;
		}
		ld->bf=EH;
		R_Rotate(T->rchild);
		L_Rotate(T);
	}
}
int Insert_AVL(BSTree T,RedType r,int &taller)
{
	if(!T)
	{
		T=new BSTNode;
		T->bf=EH;
		T->data=r;
		taller=1;
	}
	else
	{
		if(r.key==T->data.key)
		{
			taller=0;
			return 0;
		}
		if(r.key<T->data.key)
		{
			if(!Insert_AVL(T->lchild,r,taller))
				return 0;
			if(taller)
			{
				switch(T->bf)
				{
					case LH:
						LeftBalance(T);
						taller=0;
						break;
					case EH:
						T->bf=LH;
						taller=1;
						break;
					case RH:
						T->bf=EH;
						taller=0;
						break;
				}
			}
		}
		else
		{
			if(!Insert_AVL(T->rchild,r,taller))
				return 0;
			if(taller)
			{
				switch(T->bf)
				{
					case RH:
						RightBalance(T);
						taller=0;
						break;
					case EH:
						T->bf=RH;
						taller=1;
						break;
					case LH:
						T->bf=EH;
						taller=0;
						break;
				}
			}
		}
	}
	return 1;
}
void mid_travel(BSTree &T)
{
	if(T->lchild!=NULL)
	{
		mid_travel(T->lchild);
	}
	
	if(T)	cout<<T->data.key<<" ";
	if(T->rchild!=NULL)
	{
		mid_travel(T->rchild);
	}

}
int main()
{
	int n=10;

	RedType a[10];
	for(int i=0;i<n;i++)
	{
		a[i].key=rand()%30;
		cout<<a[i].key<<endl;
	}
	BSTree T;
	T=NULL;
	CreateBST(T,a,10);
	cout<<endl;
	if(T==NULL) cout<<"P"<<endl;
	mid_travel(T);

	return 0;
}