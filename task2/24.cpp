//���ݽṹ����2�ϻ��� �����Ա���ϰ��
//1. ����Ԫ��ֵΪ���͵�˳�����̣��ò��������㷨ʵ��˳�������
//2. ����Ԫ��ֵΪ���͵ĵ�������̣��ò��������㷨ʵ�ֵ���������	
//3����˳��ṹ���ʵ�����й��ܣ�����������Ԫ��ֵΪ������ֵ�����������е����Ա�A��B �ֱ��ʾ�������ϣ���Ҫ����A�Ŀռ��Ϲ���һ�������Ա�C��
//��Ԫ��ΪA��BԪ�صĲ������ұ�C�е�Ԫ��Ҳ����ֵ�����������С�
//4���õ�����ṹ���ʵ�����й��ܣ�����������Ԫ��ֵΪ������ֵ�����������е����Ա�A��B �ֱ��ʾ�������ϣ���Ҫ����A�Ŀռ��Ϲ���һ�������Ա�C��
//��Ԫ��ΪA��BԪ�صĲ������ұ�C�е�Ԫ��Ҳ����ֵ�����������С�
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
	p=l.next;
	int i=0;
	while(p!=NULL)
	{
		cout<<" "<<p->data<<" ";
		i++;
		if(i%5==0) cout<<endl;
		p=p->next;		
	}

}
void make_two_list(list &L1,list &L2)
{
	create(L1);
	create(L2);
	sort(L1);
	sort(L2);
	print(L1);
	cout<<endl;
	print(L2);
	cout<<endl;
}
void m_sort(list &L1,list &L2,list &L3)
{
	list *p,*q,*m,*r;
	p=&L1;
	q=L2.next;
	m=&L3;
	while(p->next!=NULL&&q!=NULL)
	{
		if((p->next->data)>q->data)
		{	
			m=q->next;
			q->next=p->next;
			p->next=q;
			q=m;
		}else{
			p=p->next;		
		}
	}		
	if(q!=NULL)
	{
		p->next=q;
	}
//	print(L3);
	
}
int main()
{
	list L1,L2,L3;
	L3.data=0;
	L3.next=NULL;

	make_two_list(L1,L2);
	m_sort(L2,L1,L3);
	cout<<endl;
	print(L1);
	return 0;

}

