//���ݽṹ����2�ϻ��� �����Ա���ϰ��
//1. ����Ԫ��ֵΪ���͵�˳�����̣��ò��������㷨ʵ��˳�������
//2. ����Ԫ��ֵΪ���͵ĵ�������̣��ò��������㷨ʵ�ֵ���������	
//3����˳��ṹ���ʵ�����й��ܣ�����������Ԫ��ֵΪ������ֵ�����������е����Ա�A��B �ֱ��ʾ�������ϣ���Ҫ����A�Ŀռ��Ϲ���һ�������Ա�C����Ԫ��ΪA��BԪ�صĲ������ұ�C�е�Ԫ��Ҳ����ֵ�����������С�
//4���õ�����ṹ���ʵ�����й��ܣ�����������Ԫ��ֵΪ������ֵ�����������е����Ա�A��B �ֱ��ʾ�������ϣ���Ҫ����A�Ŀռ��Ϲ���һ�������Ա�C����Ԫ��ΪA��BԪ�صĲ������ұ�C�е�Ԫ��Ҳ����ֵ�����������С�
//5������һ��˫��ѭ������ÿ������г���pre��data��next�������⣬��������һ������Ƶ����freq��������������ǰ��Ƶ����freq��ֵ����ʼ��Ϊ�㣬�������������һ��LOCATE(L,x)�Ĳ���֮�󣬱����ʵĽ�㣨��Ԫ��ֵ����x�Ľڵ㣩�е�Ƶ����freq��ֵ����1��ͬʱ���������н��֮��Ĵ���ʹ�䰴����Ƶ�ȷǵ�����˳�����У��Ա�ʼ�ձ��ֱ�Ƶ�����ʵĽ�����ǿ�����ͷ��㡣�Ա��ʵ��֮��ϰ�⼯P19  2.38����
#include<iostream>
using namespace std;
struct list
{
	int data;
	list *next;
};
void create(list &l)
{
	list *p,*q;
	p=&l;
	int i=0;
	l.data=0;
	l.next=NULL;
	for(i=1;i<21;i++)
	{
		q = new list; 
		q->data=rand();
		q->next=NULL;
		p->next=q;
		p=q;
		cout<<p->data<<" ";
	}
	
}
void sort(list &l)
{
	list *p,*q,*s,*r;
	if(l.next==NULL)
	{
		exit(1);
		
	}else{
		s=l.next;
		p=s->next;
		if(p->data<s->data)
		{
			s->next=p->next;
			p->next=s;
			l.next=p;
		}
		
		while(p->next!=NULL)
		{
			r=&l;
			q=r->next;
			while(q!=NULL&&p->data>q->data)
			{	
				r=q;
				q=q->next;			
			}
			if(!(p==q))
			{
				s->next=p->next;
				r->next=p;
				p->next=q;	
			}
			s=p;
			p=p->next;
			
		}
			r=&l;
			q=r->next;
			while(q!=NULL&&p->data>q->data)
			{	
				r=q;
				q=q->next;			
			}
			if(!(p==q))
			{
				s->next=p->next;
				r->next=p;
				p->next=q;	
			}

		cout<<endl;		
	}

}
void print(list &l)
{
	list *p;
	p=&l;
	while(p!=NULL)
	{
		cout<<p->data<<" ";
		p=p->next;		
	}

}
int main()
{
	list L;
	create(L);
	sort(L);
	print(L);
	return 0;

}

