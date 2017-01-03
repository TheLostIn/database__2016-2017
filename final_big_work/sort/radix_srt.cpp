#include<iostream>
#include<fstream>
using namespace std;
#define Space_Size 30000
#define RD 10
#define Key_Size 8
typedef int InfoType;
int maxn=Space_Size-5;
int f[10];
int e[10];
typedef struct SLNode
{
	int keys[Key_Size];
	InfoType otherInfo;
	int next;
	int key;
	SLNode()
	{
		key=0;
		//memset(keys,0,sizeof(keys));
		for(int i=0;i<Key_Size;i++)
		{
			keys[i]=0;
		}
		next=0;
	}
}LNode;
typedef struct
{
	SLNode r[Space_Size+1];
	int keynum;
	int length;
}SLList;
typedef int ArrType[RD];
void init_L(SLList *b,int i,int tmp)
{
	int j=0;
	b->r[i].key=tmp;
	b->r[i-1].next=i;
	while(tmp>0)
	{
		b->r[i].keys[j]=tmp%10;
		tmp/=10;
		j++;
	}
}
void read_numbers(SLList *b,int type)
{
	fstream f1;
	char a[20];
	char *p;
	p=a;
	switch(type)
	{
		case 0:
			p="order_number.txt";
			break;
		case 1:
			p="invert_number.txt";
			break;
		case 2:
			p="random_number5.txt";
			break;
		default:
			p="random_number.txt";
	}
	f1.open(p,ios::in);
	int i=1;
	int tmp;
	while(i<maxn)
	{	
			
		f1>>tmp;
		init_L(b,i++,tmp);
	
	}
	f1.close();
}

void display_number(SLList *b)
{
	int i=0;
	while(i<maxn)
	{
		cout<<b->r[i++].next<<" ";
		if(i%10==0)
			cout<<endl;
	}
}
void Distribute(SLNode *r,int i,int *f,int *e)
{
	int p;
	int j;
	for(j=0;j<RD;j++)
	{
		f[j]=0;
	}
	for(p=r[0].next;p;p=r[p].next)
	{
		j=r[p].keys[i];
		if(!f[j]) f[j]=p;
		else r[e[j]].next=p;
		e[j]=p;
	}
	
}
void Collect(SLNode *r,int i,int *f,int *e)
{
	int j;
	int t;
	for(j=0;!f[j];j++);
	r[0].next=f[j];
	t=e[j];

	while(j<(RD-1))
	{
	//	cout<<"find:"<<endl;
		for(j++;(j<(RD-1))&&(!f[j]);j++);

			if(f[j])
			{
				r[t].next=f[j];
				t=e[j];
			}
	}
	r[t].next=0;


}
void RadixSort(SLList *L)
{

	int i;
	int j=0;
	for(i=0;i<5;i++)
	{
		Distribute(L->r,i,f,e);
		Collect(L->r,i,f,e);

	}
	SLNode *r;
	r=L->r;
	i=r[0].next;
	cout<<"done"<<endl;
	while(i!=0)
	{
		j++;
		if(j%10==0) cout<<endl;
		cout<<r[i].key<<" ";
		i=r[i].next;
	}
}
int main()
{
	SLList *a;
	a=new SLList;
	read_numbers(a,2);
	 RadixSort(a);
	 cout<<endl;
	return 0;

}