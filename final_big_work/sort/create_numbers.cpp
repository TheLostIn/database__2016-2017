#include<iostream>
#include<stdio.h>
#include<fstream>
#include<time.h>
#include<string.h>
#include<string>
int maxn=100;
#define RAND_MAX 32767
using namespace std;
void create_order_number()
{
	fstream f1;
	f1.open("order_number.txt",ios::out);
	int i=0;
	while(i<maxn)
	{
		f1>>i>>" ";
		i++;
		cout<<i<<endl;
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
		f1>>i>>" ";
		cout<<i<<endl;
		i--;
	}
	f1.close();
}
void create_random_number()
{
//	srand( (unsigned)time( NULL ) );
	fstream f1[6];
	char file_name[28];
	char base_name[]="random_number";
	char *p;
	p=file_name;
	char num[]="0";

//	f1.open("random_number.txt",ios::out);
	char base_prefix[]=".txt";
	int j=0;
	while(j<2)
	{
	//	file_name=base_name+".txt";
		num[0]='0'+j;
		strcpy(file_name,base_name);
		strcat(file_name,num);
		strcat(file_name,base_prefix);
		cout<<file_name<<endl;
		f1[j].open(file_name,ios::out);
		int i=0;
		srand(clock());
	/*	while(i<maxn)
		{
			int p=rand()%RAND_MAX;
			f1[j]>>p>>" ";
			i++;
		}
		
	*/	
		f1[j]>>"990">>" ";
		f1[j].close();
		j++;
	}

	
}
int main()
{
//	create_order_number();
	create_invert_number();
//	create_random_number();
	return 0;
}