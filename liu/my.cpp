#include<iostream>
#include<string>
#include<fstream>
using namespace std;
int l_s(int *list,int n,int x,int i)
{
	cout<<n<<" "<<x<<" "<<i<<endl;
	if(i<0||i>n)
		return -1;
	if(list[i]==x)
		return i;
	else
	return l_s(list,n,x,++i);

}
	int i=0;
int search(int *list,int n,int x)
{
	cout<<n<<" "<<x<<" "<<i<<endl;
	if(i<0||i>n)
		return -1;
	if(list[i]==x)
		return i;
	else
	{
		++i;
		return search(list,n,x);
	}
}

int main()
{
	int list[100];
	int n=5;
	int x=3;
	for(int i=0;i<n;i++)
	{
		list[i]=i+1;
	}
	cout<<search(list,n,x);

return 0;
}