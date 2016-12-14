/*
新建txt文件 命名为 "bin_tree.txt",内容格式 : 

 23 45 56 23 67
89 23 4 5 68
23 45 5 23 45
12 23 45 111 4566 
  */
#include<iostream>
#include<fstream>
#include<stack>
using namespace std;
//二叉树的中序先序后序遍历
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
	//else if(cur->data<p->data)
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

//读文件：：：
binary_tree* read_txt_num(binary_tree * root)
{
	fstream f1;
	int tmp;
	binary_tree *p,*q;
	f1.open("bin_tree.txt",ios::in);
	root=NULL;
	p=root;
	while(!f1.eof())
	{
		f1>>tmp;
		q = new binary_tree;
		q->data=tmp;
		if(p!=NULL){
			insert(p,q);
		}
		else{
			root=q;
			p=root;
			cout<<"root"<<endl<<p->data<<endl;
			if(p!=NULL){cout<<"ppp";}
		}
	}

	//pre_read(p);
	return root;

}
binary_tree* read_num(binary_tree * root)
{

	int tmp;
	binary_tree *p,*q;
	root=NULL;
	p=root;
	int n=90;
	while(n--)
	{	
		tmp=rand()%10000;
		if(n==89)
			tmp=3000;
		cout<<tmp<<"\t";
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
void count_leave(binary_tree *root,int &count)
{
	cout<<root->data<<endl;
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
		cout<<endl<<root->data<<" ";
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
	root=read_num(root);
	//root=read_txt_num(root);
	cout<<"The height of the binary tree: "<<count_leaves(root)<<endl;
	return 0;




}