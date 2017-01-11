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
fstream f1,f2;
void CreateBiTree(binary_tree* &BT)
{
	int ch;
	
	if(!f1.eof())
	{
		f1>>ch;
		cout<<ch<<" ";
		if(ch==0) BT=NULL;
		else{
			BT=new binary_tree;
			BT->data=ch;
		//	cout<<"left "<<ch<<endl;
			CreateBiTree(BT->left);
		//	cout<<"right "<<ch<<endl;
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

void pre_read(binary_tree * root)
{
	
	if(root!=NULL)
	{	
		cout<<root->data<<" ";
		pre_read(root->left);
		pre_read(root->right);
	}
}
void mid_read(binary_tree * root)
{
	
	if(root!=NULL)
	{	
		mid_read(root->left);
		cout<<root->data<<" ";
		mid_read(root->right);
	}
}
void post_read(binary_tree * root)
{
	
	if(root!=NULL)
	{			
		post_read(root->left);
		post_read(root->right);
		cout<<root->data<<" ";
	}
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
	//		f2<<p->data<<" ";
			p=p->left;
		}
	//	f2<<'0'<<" ";
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
			f2<<p->data<<" ";
			q.push(p);
			p=p->left;
		}
			f2<<'0'<<" ";
		p=q.top();
		q.pop();
		p=p->right;
	}
		f2<<'0'<<" ";
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

int test_file()
{
	binary_tree *root;
	f1.open("bin3.txt",ios::in);
//	f2.open("bin3.txt",ios::out);
	root=read_num(root);
	CreateBiTree(root);//两种模式
/*	cout<<"bfs: "<<endl;
	bfs(root);
	cout<<"pre_read: "<<endl;
	

	cout<<"post_read: "<<endl;
	post_read_while(root);
	*/	cout<<"mid_read: "<<endl;
	mid_read_while(root);
//	pre_read_while(root);	
	if(!check_is_sorted(root))
		cout<<"this tree is not sorted"<<endl;
	else
		cout<<"this tree is sorted"<<endl;
//	f2.close();
	f1.close();
	return 0;
}
void bin_h(binary_tree *root,int &max_height,int cur)
{
	if(cur>max_height)
		max_height=cur;
	if(root->left)
	{
		bin_h(root->left,max_height,cur+1);
	}	
	if(root->right)
	{
		bin_h(root->right,max_height,cur+1);
	}
}

int bin_height(binary_tree *root)
{
	int max_height=0;
	bin_h(root,max_height,1);
	return max_height;
}
void exchange(binary_tree *root)
{
	if(root)
	{
		binary_tree *p;
		p=root->left;
		root->left=root->right;
		root->right=p;
		exchange(root->left);
		exchange(root->right);
	}
}
void exchange_bin_tree(binary_tree *root)
{
	exchange(root);
}
void count_leave(binary_tree *root,int &count)
{
//	cout<<root->data<<endl;
	if(root->left)
	{	
		count_leave(root->left,count);
	}
	if(root->right)
	{
		count_leave(root->right,count);
	}
	if(!root->left&&!root->right)
	{
		count++;
//		cout<<endl<<root->data<<" ";
	}
}
int count_leaves(binary_tree *root)
{
	int count=0;
	count_leave(root,count);
	return count;
}
int main()
{
	binary_tree *root;
	
	f1.open("bin3.txt",ios::in);
	cout<<"Create Tree :"<<endl;
	CreateBiTree(root);
	cout<<endl<<"Recurrene: "<<endl;
	cout<<endl<<"pre_read:"<<endl;
	pre_read(root);
	cout<<endl<<"mid_read:"<<endl;
	mid_read(root);
	cout<<endl<<"pre_read:"<<endl;
	post_read(root);
	cout<<endl<<"non Recurrence: "<<endl;
	cout<<endl<<"pre_read_while:"<<endl;
	pre_read_while(root);
	cout<<endl<<"mid_read_while:"<<endl;
	mid_read_while(root);
	cout<<endl<<"post_read_while:"<<endl;
	post_read_while(root);
	cout<<endl<<"binary_tree_height: "<<endl;
	cout<<bin_height(root)<<endl;
	cout<<endl<<"exchange_left_and_right_tree: "<<endl;
	exchange_bin_tree(root);
	cout<<endl<<"mid_read:"<<endl;
	mid_read(root);
	cout<<endl<<endl<<"count_binary_tree_leaves:"<<endl;
	cout<<count_leaves(root)<<endl;
	cout<<"check_if_the_tree_is_sorted: "<<endl;
	if(!check_is_sorted(root))
		cout<<"this tree is not sorted"<<endl;
	else
		cout<<"this tree is sorted"<<endl;

	exchange_bin_tree(root);
		if(!check_is_sorted(root))
		cout<<"this tree is not sorted"<<endl;
	else
		cout<<"this tree is sorted"<<endl;
	return 0;
}

