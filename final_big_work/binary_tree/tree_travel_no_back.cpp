
#include<iostream>
#include<stack>
#include<queue>
using namespace std;
#define N 40
struct binary_tree{
	int data;
	binary_tree * left;
	binary_tree * right;
	binary_tree(int a = 0):data(a),left(NULL),right(NULL) {}
};
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
		cout<<tmp<<endl;
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
int main()
{
	binary_tree *root;
	root=read_num(root);
	cout<<"bfs: "<<endl;
	bfs(root);
	cout<<"pre_read: "<<endl;
	pre_read_while(root);	
	cout<<"mid_read: "<<endl;
	mid_read_while(root);
	cout<<"post_read: "<<endl;
	post_read_while(root);

	return 0;
}
