#include<iostream>
#include<fstream>
using namespace std;
int maxn=30000 ;

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
void bubble_sort(int *a)
{
	int tag=0;
	for(int bound=1;tag==0;bound++)
	{
		tag=1;
	//	cout<<"bound:"<<bound<<endl;
	//	system("pause");
		for(int i=maxn;i>bound;--i)
		{
			if(a[i]<a[i-1])
			{
			//	cout<<a[i]<<" "<<a[i-1]<<endl;
			//	system("pause");
				a[0]=a[i];
				a[i]=a[i-1];
				a[i-1]=a[0];
				tag=0;
			}
		}
		
//	display_number(a);
	}
	

}

int main()
{
	int a[30005];
	read_numbers(a,1);
	bubble_sort(a);
	cout<<endl<<"then: "<<endl;
	display_number(a);
	return 0;

}