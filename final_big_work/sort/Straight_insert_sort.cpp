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
	while(i<maxn)
	{
		f1>>b[i++];
	}
	f1.close();
}

void display_number(int a[])
{
	int i=0;
	while(i<maxn)
	{
		cout<<a[i++]<<" ";
		if(i%10==0)
			cout<<endl;
	}
}
void Straight_sort(int *a)
{
	for(int i=2;i<maxn;i++)
	{
		if(a[i]<a[i-1])
		{
			a[0]=a[i];
			for(int j=i-1;a[0]<a[j];--j)
			{
				a[j+1]=a[j];
			}
			a[j+1]=a[0];
		}
	}
}
int main()
{
	int a[30005];
	read_numbers(a,2);
	display_number(a);
	Straight_sort(a);
	display_number(a);
	return 0;

}