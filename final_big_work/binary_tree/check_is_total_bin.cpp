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
#include<queue>
using namespace std;
struct binary_tree{
	int data;
	binary_tree * left;
	binary_tree * right;
	binary_tree() {left=NULL;right=NULL;}
};
fstream f1;
fstream f2;
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
		tmp=n;
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
int checking(binary_tree *root)
{
	queue<binary_tree*>q;
	binary_tree *p;
	q.push(root);
	int flag=1;
	while(!q.empty())
	{
		p=q.front();
		q.pop();
		if(!p) break;
		q.push(p->left);
		q.push(p->right);
	}
	while(!q.empty())
	{
		p=q.front();
		q.pop();
		if(p) 
		{
			flag=0;
			break;
		}
	}
	return flag;
}
void check_is_total_bin(binary_tree *root)
{
	if(checking(root))
	{
		cout<<"yeah it is a total binary tree"<<endl;
	}
	else
	{
		cout<<"sorry This is not a total binary tree"<<endl;
	}
}

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
	void pre_read(binary_tree * root)
{
	
	if(root!=NULL)
	{	
		pre_read(root->left);
		cout<<root->data<<" ";
		pre_read(root->right);
	}
}

int main()
{
	binary_tree *root;
//	root=read_num(root);

//	fstream f1;
	
	f1.open("bin2.txt",ios::in); //not bin
	//f1.open("bin.txt",ios::in);//is bin
	CreateBiTree(root);
	check_is_total_bin(root);
	f1.close();
	pre_read(root);
	//root=read_txt_num(root);
//	cout<<"The height of the binary tree: "<<count_leaves(root)<<endl;
	return 0;




}