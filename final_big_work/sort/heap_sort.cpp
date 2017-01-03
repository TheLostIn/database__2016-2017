#include<iostream>
#include<fstream>
#include<stack>
using namespace std;
int maxn=30000;
int count[9];
int file_num=8;
typedef struct heap_sort
{
	int low;
	int high;
	heap_sort()
	{
		low=0;
		high=0;
	}
	heap_sort(int l,int h)
	{
		low=l;
		high=h;
	}
}heap_sort;
stack<heap_sort>h_st;
void read_numbers(int* b,int type)
{
	fstream f1;
	char file_name[28];
	char base_name[]="random_number";
	char *p;
	p=file_name;
	char num[]="0";
	char base_prefix[]=".txt";
	int j=0;
	num[0]='0'+type;
	strcpy(file_name,base_name);
	strcat(file_name,num);
	strcat(file_name,base_prefix);
	cout<<file_name<<endl;
	f1.open(file_name,ios::in);
	int i=1;
	while(i<=maxn)
	{
		f1>>b[i++];
	}
	f1.close();
}

void display_number(int a[])
{
	int i=1;
	while(i<=maxn)
	{
		cout<<a[i++]<<" ";
		if(i%10==0)
			cout<<endl;
	}
}
void HeapAdjust(int *a,int low,int high,int col)
{
	a[0]=a[low];
	for(int j=2*low;j<=high;j*=2)
	{
		if((j<high)&&(a[j]<a[j+1]))
		{
			j++;
			count[col]++;
		}
		
		if(a[0]>=a[j])
		{
			count[col]++;
			break;
		}
		a[low]=a[j];
		low=j;
	}
	a[low]=a[0];
}
void HeapSort(int *a,int col)
{
	int high;
	for(int i=maxn/2;i>0;--i)
	{
		HeapAdjust(a,i,maxn,col);
	}
	for(high=maxn;high>1;high--)
	{
		a[0]=a[1];
		a[1]=a[high];
		a[high]=a[0];
		HeapAdjust(a,1,high-1,col);
	}
}

int main()
{
	int a[30005];
	memset(count,0,sizeof(count));
	for(int i=0;i<file_num;i++)
	{
		read_numbers(a,i);
		HeapSort(a,i);
		cout<<endl<<"then: "<<endl;
		cout<<"count:  "<<count[i]<<endl;
	}
//	display_number(a);
	return 0;
}