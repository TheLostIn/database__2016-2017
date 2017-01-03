#include<iostream>
#include<fstream>
#include<time.h>
int maxn=30000;
#define RAND_MAX 32767
using namespace std;
int file_num=8;
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
	fstream f1[8];
	char file_name[28];
	char base_name[]="random_number";
	char *p;
	p=file_name;
	char num[]="0";
	char base_prefix[]=".txt";
	int j=0;
	while(j<file_num)
	{
		num[0]='0'+j;
		strcpy(file_name,base_name);
		strcat(file_name,num);
		strcat(file_name,base_prefix);
		cout<<file_name<<endl;
		f1[j].open(file_name,ios::out);
		int i=0;
		srand(clock());
		while(i<maxn)
		{
			if(j==0)
			{
				f1[j]<<i<<" ";
			}
			else if(j==1)
			{
				f1[j]<<RAND_MAX-i<<" ";
			}
			else
			{
				int p=rand()%RAND_MAX;
				f1[j]<<p<<" ";
			}
		
			i++;
		}
		f1[j].close();
		j++;
	}
}
int main()
{
//	create_order_number();
//	create_invert_number();
	create_random_number();
	return 0;
}