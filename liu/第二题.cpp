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
	char words[24];                    //��������
	ElemType number;                  //���ʳ��ִ���
	struct LNode *next;
}Sqlist,*LinkList;

Status ShowTxt(LinkList &L)           //��ʾȫ�ĵĺ���
{
    ElemType i=0;
	LinkList p,s;
	L=(LinkList)malloc(sizeof(LNode));//����ͷ��㣬��ʹLָ���ͷ���
	p=(LinkList)malloc(sizeof(LNode));
	//L->next=NULL;//ͷ����ָ����Ϊ��
	L->next=p;
	cout<<"111111";
	fstream datafile;
	datafile.open("English.txt",ios::in);
	p->number=1;                      //��ʼ��
	cout<<"222222";
	if(!datafile)
	{
		cout<<"�ļ��򿪴���";
		exit(1);
	}
	char c;                            //��ȡ�ļ��е��ַ�
	c=datafile.get();
	cout<<"333333";
	while(!datafile.eof())               //�ж��Ƿ��ļ�β
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
		i=0;//�ַ��������´�1��ʼ����
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
Status TraverseList(LinkList L)          //�����������
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
Status GetNumber(LinkList L)          //ͳ�Ƶ��ʳ��ֵĴ���
{
	LinkList p,q,s,pre;
	string str;//����һ���ַ���
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
