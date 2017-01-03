#include<iostream>
#include<stack>
#include<fstream>
#include<queue>
using namespace std;
#define N 40
struct binary_tree{
	int data;
	binary_tree * left;
	binary_tree * right;
	binary_tree(int a = 0):data(a),left(NULL),right(NULL) {}
};
fstream f1;
void CreateBiTree(binary_tree* &BT)
{
	int ch;
	
	if(!f1.eof())
	{
		f1>>ch;
		cout<<ch<<endl;
		if(ch==0) BT=NULL;
		else{
			BT=new binary_tree;
			BT->data=ch;
			cout<<"left "<<ch<<endl;
			CreateBiTree(BT->left);
			cout<<"right "<<ch<<endl;
			CreateBiTree(BT->right);
		}
	}
}
void insert(binary_tree *cur,binary_tree * p)
{
	if(cur->data>p->data)
	{
		if(cur->left==NULL)
		{
			cur->left=p;
		}
		else
		{
			insert(cur->left,p);
		}
	}else
	{
		if(cur->right==NULL)
		{
			cur->right=p;
		}
		else
		{
			insert(cur->right,p);
		}
	}
}

void bfs(binary_tree *root)
{
	queue<binary_tree *> q;
	q.push(root);
	while(!q.empty())
	{
		binary_tree * p;
		p=q.front();
		q.pop();
		cout<<p->data<<" ";
		if(p->left!=NULL) q.push(p->left);
		if(p->right!=NULL) q.push(p->right);
	}
	cout<<endl;
}
binary_tree* read_num(binary_tree * root)
{

	int tmp;
	binary_tree *p,*q;
	root=NULL;
	p=root;
	int n=N;
	while(n--)
	{	
		tmp=rand()%10000;
		if(n==N-1)
			tmp=3000;
	//	cout<<tmp<<endl;
		q = new binary_tree;
		q->data=tmp;
		if(p!=NULL){
			insert(root,q);
		}
		else{
			root=q;
			p=root;
		}
	}
	
	return root;

}
void mid_read_while(binary_tree *root)
{
	binary_tree *p;
	p=root;
	stack<binary_tree*>q;

	while(!q.empty()||p)
	{
		while(p)
		{
			q.push(p);
			p=p->left;
		}
		p=q.top();
		q.pop();
		cout<<p->data<<" ";
		p=p->right;
	}
	cout<<endl;
}
void pre_read_while(binary_tree *root)
{
	binary_tree *p;
	p=root;
	stack<binary_tree*>q;
	while(!q.empty()||p)
	{
		while(p)
		{
			cout<<p->data<<" ";
			q.push(p);
			p=p->left;
		}
		p=q.top();
		q.pop();
		p=p->right;
	}
	cout<<endl;

}
void post_read_while(binary_tree *root)
{
	binary_tree *p,*last;
	p=root;
	stack<binary_tree*>q;
	last=NULL;
		while(p)
		{	
				q.push(p);
				p=p->left;
		}
		
	while(!q.empty())
	{
		p=q.top();
		q.pop();
		if(p->right==NULL||p->right==last)
		{
			cout<<p->data<<" ";
			last=p;			
		}		
		else
		{
			q.push(p);	
			p=p->right;			
			while(p)
			{
				q.push(p);
				p=p->left;
			}
		}
	}
	cout<<endl;
}
int check_is_sorted(binary_tree *root)
{
	binary_tree *p;
	int last;
	p=root;
	int flag=0;
	stack<binary_tree*>q;
	while(!q.empty()||p)
	{
		while(p)
		{
			q.push(p);
			p=p->left;
		}
		p=q.top();
		q.pop();
		if(!flag)
		{
			last=p->data;
			flag=1;
		}
	//	cout<<p->data<<" ";
		if(p->data>=last)
		{
			last=p->data;
		}
		else
		{
			return 0;
		}
		p=p->right;
	}
	cout<<endl;
	return 1;
}
int main()
{
	binary_tree *root;
	f1.open("bin.txt",ios::in);
	root=read_num(root);
//	CreateBiTree(root);//两种模式
/*	cout<<"bfs: "<<endl;
	bfs(root);
	cout<<"pre_read: "<<endl;
	pre_read_while(root);	
	cout<<"mid_read: "<<endl;
	mid_read_while(root);
	cout<<"post_read: "<<endl;
	post_read_while(root);
	*/
	if(!check_is_sorted(root))
		cout<<"this tree is not sorted"<<endl;
	else
		cout<<"this tree is sorted"<<endl;
	return 0;
}
