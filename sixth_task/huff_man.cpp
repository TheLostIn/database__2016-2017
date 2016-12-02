#include<iostream>
using namespace std;
#include<fstream>
#include<stack>
#include<string.h>
#include<algorithm>
#include<cctype>
#include<string>
#include<map>
#include<queue>
#include<vector>
struct huff
{
	int data;
	int left;
	int right;
	int par;
};
#define N 50
void init_huff(huff *huff_man)
{
	fstream f1;
	int i;
	f1.open("huff_num.txt",ios::in);
	for(i=1;i<=(N/2);i++)
	{
		huff_man[i].data=0;
		huff_man[i].par=0;
		huff_man[i].left=0;
		huff_man[i].right=0;
		cout<<i<<" "<<huff_man[i].data<<endl;
	}
	f1.close();
}
int seek_min(huff *huff_man,int place)
{
	int i;
	int j;
	int min=0;
	int sub=0;
	for(i=1;i<N;i++)
	{
		if(huff_man[i].par==0)
		{
			min=i;
			break;
		}
	}
	for(i;i<=(N/2);i++)
	{
	//	cout<<"search"<<endl;
		if((huff_man[i].par==0)&&(huff_man[i].data<huff_man[min].data))
		{
			min=i;
	//		cout<<i<<endl;
		}
			
	}
//	huff_man[min].par=place;
//	cout<<min<<endl;
	return min;
}
int main()
{
	map<char,int> cnt;
	char p='p';
/*	if(!cnt.count(p)) cnt[p]=0;
	cnt[p]++;
	cout<<cnt.count(p);
	*/
	return 0;
}
