#include<iostream>
#include<fstream>
using namespace std;
int maxn=9000;

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
int partition(int *a,int low,int high)
{
	int pivotkey;
	a[0]=a[low];
	pivotkey=a[low];
	while(low<high)
	{
		while(low<high&&a[high]>pivotkey)
		{
			high--;
		}
		a[low]=a[high];
		while(low<high&&a[low]<pivotkey)
		{
			low++;
		}
		a[high]=a[low];
//		cout<<endl<<a[low]<<endl;
	//	system("pause");
	}
	a[low]=a[0];
//	cout<<"low: "<<low<<endl;
//	system("pause");
	return low;

}
void q_sort(int *a,int low,int high)
{
	if(low<high){
		
	int pivotpos;
	pivotpos=partition(a,low,high);
//	if(low!=pivotpos)
	q_sort(a,low,pivotpos-1);
//	if(high!=pivotpos)
	q_sort(a,pivotpos+1,high);
	}

}
void quick_sort(int *a)
{
	q_sort(a,1,maxn);
}
int main()
{
	int a[30005];
	read_numbers(a,1);
		display_number(a);
	quick_sort(a);
	cout<<endl<<"then: "<<endl;
	display_number(a);
	return 0;

}