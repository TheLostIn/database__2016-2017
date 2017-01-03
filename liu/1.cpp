#include<iostream>
using namespace std;
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<fstream>

#define MAX 5
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAXSIZE 20
#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a)<(b))
#define LQ(a,b) ((a)<=(b))
#define MAX_NUM_OF_KEY 9
#define RADIX 10
#define MAX_SPACE 20000 

typedef int Status;
typedef int KeysType;
typedef int InfoType;

typedef struct
{
	KeysType keys[MAX_NUM_OF_KEY];//关键字
	InfoType otheritme;//其他数据项
	int next;
}SLCell;

typedef struct
{
	SLCell r[MAX_SPACE];//静态链表可利用空间
	int keynum;//当前关键字个数
	int recnum;//静态链表当前长度
}SLList;

typedef int ArrType[RADIX];//指针数组类型

int exchange=0;//交换次数
int compare=0;//比较次数

/*char Change(int n)
{
    if(n==0)
	{return '0';}
	else if(n==1)
	{return '1';}
	else if(n==2)
	{return '2';}
	else if(n==3)
	{return '3';}
	else if(n==4)
	{return '4';}
	else if(n==5)
	{return '5';}
	else if(n==6)
	{return '6';}
	else if(n==7)
	{return '7';}
	else if(n==8)
	{return '8';}
	else if(n==9)
	{return '9';}
}*/
void  Keys(int *keys,int n)//为关键字赋值关键字是从个位到高位一次放入数组Key[]的
{
 int i;
 for(i=0;n>0;i++)
 {
    keys[i]=n%10;
    n=n/10;
 }
}

Status Init(SLList &L,int j)
{
	/*int number,k,i,t;
	char A[MAX_NUM_OF_KEY],B[MAX_NUM_OF_KEY];
	L.recnum=MAX;
	L.keynum=5;*/
    fstream in;
	if(j==0)
	 {
	    in.open("1.txt",ios::in);
	 }
	 else if(j==1)
	 {
		in.open("2.txt",ios::in);
	 }
	 else if(j==2)
	 {
		in.open("3.txt",ios::in);
	 }
	 else if(j==3)
	 {
		in.open("4.txt",ios::in);
	 }
	 else if(j==4)
	 {
		in.open("5.txt",ios::in);
	 }
	 else if(j==5)
	 {
		in.open("6.txt",ios::in);
	 }
	 else if(j==6)
	 {
		in.open("7.txt",ios::in);
	 }
	 else if(j==7)
	 {
		in.open("8.txt",ios::in);
	 }
	 if(!in)
	 {
		cout<<"fail to open the file!\n";
		exit(0);
	 }
	 /*for(i=1;i<=L.recnum;i++)
	 {
		in>>number;
		k=0;
        while(number!=0)
		{
		   A[k]=Change(number%10);
		   number=(number-number%10)/10;
		   k++;
		}
		A[k]='\0';
		for(t=strlen(A);t<(MAX_NUM_OF_KEY-1);t++)
		{
		   strcpy(B,A);
		   strcat(B,"0");
		   strcpy(A,B);
		}
		for(j=0;j<(MAX_NUM_OF_KEY-1);j++)
		{L.r[i].keys[j]=A[j];}
		//重复使用
		for(j=0;j<L.keynum;j++)
		{A[j]='\0';}
	 }*/
	 int i,k;
 //char a[MAX_NUM_OF_KEY];

 L.recnum=MAX;
 L.keynum=5;
 for(i=1;i<=L.recnum;i++)//给关键字初始化为0
 {
  for(k=0;k<L.recnum;k++)
   L.r[i].keys[k]=0;
 }

 for(i=1;i<=L.recnum;i++)//输入数据项
 {  
  
  in>>L.r[i].otheritme;
  Keys(L.r[i].keys,L.r[i].otheritme) ;//为关键字赋值,关键字是从个位到高位一次放入数组Key[]的
  
 }
 /*cout<<endl<<"表L为:"<<endl;
 for(i=1;i<L.recnum;i++)//输出据项
  cout<<L.r[i].otheritme<<"->";
 cout<<L.r[i].otheritme<<endl;*/
 for(i=0;i<L.recnum;i++)//给next赋值
 L.r[i].next=i+1;
 L.r[L.recnum].next=0;
	 in.close();
	 return OK;
}

char ord(char c)
{return (c-'0');}

void Distribute(SLCell *r,int i,ArrType &f,ArrType &e)
{ 
   int j,p;
   for(j=0;j<RADIX;j++)
   f[j]=0; //各子表初始化为空表
   //	   cout<<"P"<<endl;
//	   system("pause");
   for(p=r[0].next;p;p=r[p].next)
   {
	 //    cout<<p<<endl;
	//   system("pause");
     //j=ord(r[p].keys[i]); //ord将记录中第i个关键字映射到[0..RADIX-1]
	 Keys(r[p].keys,r[p].keys[i]);
	 j=r[p].keys[i];
//	 cout<<j<<endl;
     compare++;
     if(f[j]==0)
	 {f[j]=p;}
     else
	 {
       r[e[j]].next=p;
       exchange++;
     }
     e[j]=p; //将p所指的结点插入第j个子表中
   }
}

Status succ(int i)//后继函数
{return (++i);}

void Collect(SLCell *r,int i,ArrType f,ArrType e)
{
    
   int j,t;
   for(j=0;!f[j];j=succ(j)); //找第一个非空子表，succ为求后继函数 
   r[0].next=f[j];         //r[0].next指向第一个非空子表中第一个结点
   exchange++;
   t=e[j];  
   while(j<RADIX-1)
   {
	//   cout<<"P"<<endl;
//	   system("pause");
	  //for(j=succ(j);j<RADIX-1&&!f[j];j=succ(j));//找下一个非空子表 
	   for(j=j+1;j<RADIX-1&&!f[j];j++);
	  compare++;
	  if(f[j])//链接两个非空子表
	  { 
		r[t].next=f[j];
		t=e[j];
		exchange++;
	  }
   }
   r[t].next=0; //t指向最后一个非空子表中的最后一个结点
   
}

void RadixSort(SLList &L)
{ 
   int i;
   ArrType f,e;
   //for(i=0;i<L.recnum;++i)
   //L.r[i].next=i+1;
   //L.r[L.recnum].next=0;//将L改造为静态链表
   for(i=0;i<L.keynum;++i)//按最低位优先依次对各关键字进行分配和收集
   { 
     Distribute(L.r,i,f,e);//第i趟分配
     Collect(L.r,i,f,e);//第i趟收集
   }
}

void Print(SLList L,int j)
{
    fstream out;
	int p;
	/*int sum=0;
	int x=10000;
	int number;*/
	if(j==0)
	{
	    out.open("1_order.txt",ios::out);
	}
	else if(j==1)
	{
	    out.open("2_order.txt",ios::out);
	}
	else if(j==2)
	{
		out.open("3_order.txt",ios::out);
	}
	else if(j==3)
	{
		out.open("4_order.txt",ios::out);
	}
	else if(j==4)
	{
		out.open("5_order.txt",ios::out);
	}
	else if(j==5)
	{
		out.open("6_order.txt",ios::out);
	}
	else if(j==6)
	{
		out.open("7_order.txt",ios::out);
	}
	else if(j==7)
	{
		out.open("8_order.txt",ios::out);
	}
	if(!out)
	{
		cout<<"fail to open the file!\n";
		exit(0);
	}
    /*while(i)
    {
		 for(k=L.keynum-1;k>=0;k--)
		 {
		    number=ord(L.r[i].keys[k]);
		    sum=number*x+sum;
		    x=x/10;
		 }
		 x=10000;
		 out<<sum<<'\n';
		 i=L.r[i].next;
		 sum=0; 
   }*/
	 for(p=L.r[0].next;L.r[p].next;p=L.r[p].next)
	 {
        out<<L.r[p].otheritme<<'\n';
	 }
     out<<L.r[p].otheritme;
   out.close();
}

int main()
{
    int sum_compare=0,sum_exchange=0;
	int i,j;
	float start,end;
	int sum_time=0;
	SLList L;
	srand(time(NULL)); 
	int a[MAX];
    fstream out;
    for(j=0;j<6;j++)
	{ 
		if(j==0)
		{
			out.open("1.txt",ios::out);
		}
		else if(j==1)
		{
			out.open("2.txt",ios::out);
		}
		else if(j==2)
		{
			out.open("3.txt",ios::out);
		}
		else if(j==3)
		{
			out.open("4.txt",ios::out);
		}
		else if(j==4)
		{
			out.open("5.txt",ios::out);
		}
		else if(j==5)
		{
			out.open("6.txt",ios::out);
		}
		if(!out)
		{
			cout<<"fail to open the file!\n";
			exit(0);
		}
        for(i=0;i<MAX;i++)
        {
	     	a[i]=rand()%1000;
	        out<<a[i]<<'\n';
        } 
        out.close();
	}

	out.open("7.txt",ios::out);
    if(!out)
    {
    	cout<<"open fail";
    	exit(0);
    }
    for(i=1;i<MAX;i++)
    {
    	out<<i<<'\n';
    }
    out.close();

    out.open("8.txt",ios::out);
    for(i=MAX;i>=1;i--)
    {
    	out<<i<<'\n';
    }
    out.close();

	cout<<"Radix Sorting:\n";
	cout<<"No:     time:   exchange time:    compare time:\n";
	for(j=0;j<8;j++)
	{
		Init(L,j);
		start=(float)clock();
		RadixSort(L);
		end=(float)clock();
		cout<<(j+1)<<":    "<<(end-start)<<"ms     "<<exchange<<"     "<<compare<<"      \n";
		sum_time+=end-start;
		sum_exchange+=exchange;
		sum_compare+=compare;
		exchange=0;
		compare=0;
		//Print(L,j);

		fstream out;
		int p;
		if(j==0)
		{
			out.open("1_order.txt",ios::out);
		}
		else if(j==1)
		{
			out.open("2_order.txt",ios::out);
		}
		else if(j==2)
		{
			out.open("3_order.txt",ios::out);
		}
		else if(j==3)
		{
			out.open("4_order.txt",ios::out);
		}
		else if(j==4)
		{
			out.open("5_order.txt",ios::out);
		}
		else if(j==5)
		{
			out.open("6_order.txt",ios::out);
		}
		else if(j==6)
		{
			out.open("7_order.txt",ios::out);
		}
		else if(j==7)
		{
			out.open("8_order.txt",ios::out);
		}
		if(!out)
		{
			cout<<"fail to open the file!\n";
			exit(0);
		}
		 for(p=L.r[0].next;L.r[p].next;p=L.r[p].next)
		 {
			out<<L.r[p].otheritme<<'\n';
		 }
		 out<<L.r[p].otheritme;
	     out.close();

	}
    cout<<"average time:"<<sum_time/8<<"ms"<<'\n';
	cout<<"average exchange time:"<<sum_exchange/8<<"ms"<<'\n';
	cout<<"average compare time:"<<sum_compare/8<<"ms"<<'\n';
    return 0;
}
