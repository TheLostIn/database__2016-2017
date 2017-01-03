
#include<iostream>
#include<fstream>
#include<stack>
using namespace std;
int maxn=30000;
typedef struct q_sort
{
	int low;
	int high;
	q_sort()
	{
		low=0;
		high=0;
	}
	q_sort(int l,int h)
	{
		low=l;
		high=h;
	}
}q_sort;
stack<q_sort>q_st;
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
			p="random_number3.txt";
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
		while(low<high&&(a[high]>=pivotkey))
		{
			--high;
		}
		a[low]=a[high];
	//	low++;
		while(low<high&&(a[low]<=pivotkey))
		{
			++low;
		}
		a[high]=a[low];
	//	high++;
	//	cout<<low<<" "<<high<<" "<<endl;
	}
	a[low]=a[0];
	
//	cout<<"partition: "<<low<<" "<<high<<endl;
	return low;

}
void Q_sort(int *a,int low,int high)
{
	if(low<high){
		
	int pivotpos;
	pivotpos=partition(a,low,high);
//	cout<<low<<" "<<high<<endl;
		if(pivotpos-1>=low)
	Q_sort(a,low,pivotpos-1);
		if(pivotpos+1<=high)
	Q_sort(a,pivotpos+1,high);
	}

}
void qq_sort(int *a,int low,int high)
{
	q_sort q;
	q_st.push(q_sort(low,high));
	int pivotpos;
		while(!q_st.empty()&&low<high)
		{	
			q=q_st.top();	
			q_st.pop();
			pivotpos=partition(a,low,high);
			if((pivotpos+1)<high)
			q_st.push(q_sort(pivotpos+1,high));
			if((pivotpos-1)>low)
			q_st.push(q_sort(low,pivotpos-1));
		
			low=q.low;
			high=q.high;
		}

}
void quick_sort(int *a)
{
//	Q_sort(a,1,maxn);
	qq_sort(a,1,maxn);
}
int main()
{
	int a[30005];
	read_numbers(a,2);	display_number(a);
	//	display_number(a);
	quick_sort(a);
	cout<<endl<<"then: "<<endl;
	display_number(a);
	return 0;

}