#include<iostream>
#include<stack>
#include<queue>
using namespace std;
//Sequence 
#define BiTree_Size 100
typedef int ElemType;
typedef ElemType SqBiTree[BiTree_Size + 1];
//struct
typedef struct BTNode{
	ElemType data;
	BTNode *lchild,*rchild;
} BiTNode;
typedef BiTNode *BiTree;
class BinaryTree{
public:
	void InitBiTree(SqBiTree &T);
	void DestroyBiTree(SqBiTree &T);
	void CreateBiTree(SqBiTree &T);
	void ClearBiTree(SqBiTree &T);
	void BiTreeDepth(SqBiTree &T);
	BiTree Root(BiTNode &T);
	ElemType Value(BiTNode T);
	BiTree Parent(BiTree T);
	BiTree LeftChild(BiTree T,BiTree p);
	BiTree RightChild(BiTree T,BiTree p);
	void InsertChild(SqBiTree &T,SqBiTree p,SqBiTree LR,ElemType c);
	void DeleteChild(SqBiTree &T,SqBiTree LR);
	void PreOrderTraverse(SqBiTree T);
	void InOrderTraverse(BiTree T);
	void PostOrderTraverse(SqBiTree T);
};
BiTree LeftChild(BiTree T)
{
	if(T->lchild)
		return T->lchild;
	else return NULL;
}
BiTree RightChild(BiTree T)
{
	if(T->rchild)
		return T->rchild;
	else return NULL;

}

BiTree Parent(BiTree T,BiTree e)
{
	queue<BiTree> q;
	BiTree p;
	if (!T) {
    	return NULL;
    }else{
		q.push(T);
	}
	while(!q.empty())
	{
		p=q.front();
		
		if(p->lchild)
		{
			if(p->lchild==e)
				return p;
			q.push(p->lchild);
		}
		if(p->rchild)
		{
			if(p->rchild==e)
				return p;
			q.push(p->rchild);
		}
		q.pop();
	}
	return NULL;
}
ElemType Value(BiTree T)
{
	return T->data;
}
BiTree Root(BiTree T)
{
	if(T)
	{
		return T;
	}
}
void PreOrderTraverse(SqBiTree BT)
	{
		int n = BT[0];
	
		for(int i=1,int j;i<n;i++)
		{
			if(i==1) j=1;
			else if(2*j<=n) j=2*j;
			else if((j%2==0)&&(j<n)) j=j+1;
			else if(j>1){
				while((j/2)%2!=0) j=j/2;
				j=j/2+1;
			}
			cout<<BT[j];
		}

	}
	void InOrderTraverse(BiTree BT)
	{
		queue<BiTree> S;
		BiTree p,q;

		p=BT;
		while(p)
		{
			if(p){
				S.push(p);
				p=p->lchild;
			}
			else{
				q=S.front();
				S.pop();
				cout<<p->data;
				p=p->lchild;
			}
		}
	}
	void PostOrderTraverse(BiTNode* root)
	{
		if(root)
		{
			PostOrderTraverse(root->lchild);
			PostOrderTraverse(root->rchild);
			cout<<root->data;
		}
	}
	void CreateBiTree(BiTNode *BT)
	{
		int ch;
		cin>>ch;
		if(ch==0) BT=NULL;
		else{
			BT=new BiTNode;
			BT->data=ch;
			CreateBiTree(BT->lchild);
			CreateBiTree(BT->rchild);
		}
	}
int main()
{	
	return 0;
}