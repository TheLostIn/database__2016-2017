#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<iostream>
#include<fstream>
using namespace std;
typedef int ElemType;
typedef int Status;
#define ok 1
typedef struct LNode
{
	char words[24];                    //单词数组
	ElemType number;                  //单词出现次数
	struct LNode *next;
}Sqlist,*LinkList;

Status ShowTxt(LinkList &L)           //显示全文的函数
{
    ElemType i=0;
	LinkList p,s;
	L=(LinkList)malloc(sizeof(LNode));//产生头结点，并使L指向此头结点
	p=(LinkList)malloc(sizeof(LNode));
	//L->next=NULL;//头结点的指针域为空
	L->next=p;
	cout<<"111111";
	fstream datafile;
	datafile.open("English.txt",ios::in);
	p->number=1;                      //初始化
	cout<<"222222";
	if(!datafile)
	{
		cout<<"文件打开错误";
		exit(1);
	}
	char c;                            //获取文件中的字符
	c=datafile.get();
	cout<<"333333";
	while(!datafile.eof())               //判断是否到文件尾
	{
		p->words[i]=c;
		i++;
		cout<<"44444";
		if(c==' ')
		{
		p->words[i]='\0';
		cout<<"5555";
		s=(LinkList)malloc(sizeof(LNode));
		s->number=1;
		i=0;//字符个数重新从1开始计数
		p->next=s;
		s->next=NULL;
		p=s;
	    }
		if(datafile.eof())
			break;
		c=datafile.get();
	}
	datafile.close();
	return ok;
}
Status TraverseList(LinkList L)          //遍历输出函数
{
	LinkList p=L->next;
	while(p)
	{
		cout<<p->words;
		p=p->next;
	}
	cout<<endl;
	return ok;
}
Status GetNumber(LinkList L)          //统计单词出现的次数
{
	LinkList p,q,s,pre;
	string str;//定义一个字符串
	ElemType i=1;
	s=q=pre=L->next;
	str=q->words;
	p=q->next;
	while(q->next!=NULL)
	{
	while(p->next!=NULL)
	{
		if(str==p->words)
		{
			q->number++;
			s=p;
			pre->next=p->next;
			free(s);
		}                          
		pre=pre->next;
		p=pre->next;
	}
	//cout<<"nnnnnnn";
	q=q->next;
	pre=q;
	p=q->next;
	str=q->words;
    }
	return ok;
}
Status main()
{
	LinkList L;
	ShowTxt(L);
	cout<<"nnnnnndadadadadadadadadad";
	TraverseList(L);
	GetNumber(L);
	TraverseList(L);
	
	return ok;
}
