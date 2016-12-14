#include<iostream>
#include<fstream>
#include<time.h>
int maxn=30000;
#define RAND_MAX 32767
using namespace std;
void create_order_number()
{
	fstream f1;
	f1.open("order_number.txt",ios::out);
	int i=0;
	char b=' ';
//	if()
	while(i<maxn)
	{
		f1<<i<<b;
		i++;
//		cout<<i<<endl;
	}
	f1.close();
}
void create_invert_number()
{
	fstream f1;
	f1.open("invert_number.txt",ios::out);
	int i=maxn;
	while(i>0)
	{
		f1<<i<<" ";
		i--;
	}
	f1.close();
}
void create_random_number()
{
	srand( (unsigned)time( NULL ) );
	fstream f1;
	f1.open("random_number.txt",ios::out);
	int i=0;
	while(i<maxn)
	{
		int p=rand()%RAND_MAX;
		f1<<p<<" ";
		i++;
	}
	f1.close();
}
int main()
{
	create_order_number();
	create_invert_number();
	create_random_number();
	return 0;
}