#include<iostream>
#include<fstream>
using namespace std;
int maxn=30000;
void read_numbers(int* b,int type)
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
			p="random_number.txt";
			break;
		default:
			p="random_number.txt";
	}
	f1.open(p,ios::in);
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
void HeapAdjust(int *a,int low,int high)
{
	a[0]=a[low];
	for(int j=2*low;j<=high;j*=2)
	{
		if((j<high)&&(a[j]<a[j+1]))
			j++;
		if(a[0]>=a[j])
			break;
		a[low]=a[j];
		low=j;
	}
	a[low]=a[0];
}
void HeapSort(int *a)
{
	int high;
	for(int i=maxn/2;i>0;--i)
	{
		HeapAdjust(a,i,maxn);
	}
	for(high=maxn;high>1;high--)
	{
		a[0]=a[1];
		a[1]=a[high];
		a[high]=a[0];
		HeapAdjust(a,1,high-1);
	}
}

int main()
{
	int a[30005];
	read_numbers(a,1);
	display_number(a);
	HeapSort(a);
	cout<<endl<<"then: "<<endl;
	display_number(a);
	return 0;
}