//���ݽṹ����2�ϻ��� �����Ա���ϰ��
//1. ����Ԫ��ֵΪ���͵�˳�����̣��ò��������㷨ʵ��˳�������
//2. ����Ԫ��ֵΪ���͵ĵ�������̣��ò��������㷨ʵ�ֵ���������	
//3����˳��ṹ���ʵ�����й��ܣ�����������Ԫ��ֵΪ������ֵ�����������е����Ա�A��B �ֱ��ʾ�������ϣ���Ҫ����A�Ŀռ��Ϲ���һ�������Ա�C��
//��Ԫ��ΪA��BԪ�صĲ������ұ�C�е�Ԫ��Ҳ����ֵ�����������С�
//4���õ�����ṹ���ʵ�����й��ܣ�����������Ԫ��ֵΪ������ֵ�����������е����Ա�A��B �ֱ��ʾ�������ϣ���Ҫ����A�Ŀռ��Ϲ���һ�������Ա�C��
//��Ԫ��ΪA��BԪ�صĲ������ұ�C�е�Ԫ��Ҳ����ֵ�����������С�
//5������һ��˫��ѭ������ÿ������г���pre��data��next�������⣬��������һ������Ƶ����freq��������������ǰ��Ƶ����freq��ֵ����ʼ��Ϊ�㣬�������������һ��LOCATE(L,x)�Ĳ���֮�󣬱����ʵĽ�㣨��Ԫ��ֵ����x�Ľڵ㣩�е�Ƶ����freq��ֵ����1��ͬʱ���������н��֮��Ĵ���ʹ�䰴����Ƶ�ȷǵ�����˳�����У��Ա�ʼ�ձ��ֱ�Ƶ�����ʵĽ�����ǿ�����ͷ��㡣�Ա��ʵ��֮��ϰ�⼯P19  2.38����
#include<iostream>
#include<stdio.h>
#define OVERFLOW -2
using namespace std;
struct list
{
	int *elem;
	int length;
	int listsize;
};
void create(list &l,int n)
{
	int i;

	l.elem=(int *)malloc(n*sizeof(int));
	if(!l.elem) exit(OVERFLOW);
	l.length=n;
	l.listsize=n;
	for(i=0;i<n;i++)	
	{
		l.elem[i]=rand();
	}
}
void sort(int *a,int n)
{
	int i,j,k,temp;
	for(i=0;i<n;i++)
	{
		for(j=0;a[i]>a[j]&&j<i;j++)
		{			
		}
		if(j<i)
		{
			temp=a[i];
			for(k=i;k>j;k--)
			{
				a[k]=a[k-1];
			}
			a[j]=temp;
		}
	}
	for(i=0;i<n;i++)
	{
	
		cout<<a[i]<<" ";
	}
	cout<<endl;
}
void print(list &l)
{
	int i;
	for(i=0;i<l.length-1;i++)
	{
		cout<<l.elem[i]<<" ";
		if(i%5==0) cout<<endl;
	}
	cout<<endl;
}
void m_sort(list &l1,list &l2)
{
	int i=0,j=0,k,temp;
	int *a,*b;
	a=l1.elem;
	b=l2.elem;

	while(i<l1.length&&j<l2.length)
	{
		if(a[i]>b[j])
		{
		
			for(k=l1.length;k>i;k--)
			{
				a[k]=a[k-1];
			}
			a[i]=b[j];
			j++;
			l1.length++;
		}else{
			i++;
		}
	}
	cout<<l1.listsize<<l1.length<<" "<<b[j]<<" "<<a[i]<<" "<<i<<" "<<j<<" "<<endl;
//	a[i]=;
	//a[i]=9;
	if(i==l1.length&&i<l1.listsize)
	{
	
		for(k=i;k<l1.listsize;k++)
		{
			a[k]=b[j];
			cout<<k<<" "<<j<<" ";
			l1.length++;
			j++;
		}
	}

	


}
void recreate(list &L1,int n)
{
	int *newbase;
	newbase=(int *)realloc(L1.elem,(L1.length+n)*sizeof(int));
	if(!newbase) exit(OVERFLOW);
	L1.listsize+=n;
}
int main()
{
	int n=8;
	list L1,L2;
	create(L1,n);
	create(L2,n);
	sort(L1.elem,L1.length);
	sort(L2.elem,L2.length);
	recreate(L2,L1.length);
	m_sort(L2,L1);
	print(L2);
	return 0;
}