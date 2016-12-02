#include<iostream>
#include<fstream>
#include<string>
using namespace std;
#define N 52*2
struct huff
{
	int data;
	int left;
	int right;
	int par;
};
void init_huff(huff *huff_man)
{
	fstream f1;
	int i;
	f1.open("huff_num.txt",ios::in);
	for(i=1;i<=(N/2);i++)
	{
		f1>>huff_man[i].data;
		huff_man[i].par=0;
		huff_man[i].left=0;
		huff_man[i].right=0;
//		cout<<i<<" "<<huff_man[i].data<<endl;
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
void display(huff *huff_man)
{
	int i;
	for(i=1;i<N;i++)
	{
		cout<<i<<" "<<huff_man[i].data<<" "<<huff_man[i].par<<" "<<huff_man[i].left<<" "<<huff_man[i].right<<endl;
	}
}
huff* merge_tree(huff *huff_man,int t1 ,int t2,int place)
{
	huff_man[t1].par=place;
	huff_man[t2].par=place;
	huff_man[place].par=0;
	huff_man[place].data=huff_man[t1].data=place+huff_man[t2].data;
	huff_man[place].left=t1;
	huff_man[place].right=t2;
	return huff_man;
}
void make_code(huff *huff_man)
{
	string a;
	int count =0 ;
	fstream f1;
	f1.open("huff_man.txt",ios::out);
//	cout<<"llll"<<endl;
//	display(huff_man);
	for(int i=1;i<=N/2;i++)
	{
		int par;
		int p;
		char choose;

		p=i;
		par=huff_man[i].par;
	//	cout<<"oooo"<<endl;
	//	cout<<huff_man[par].data<<endl;

		while(par!=0)
		{
		//	cout<<"kkk"<<endl;
			if(huff_man[par].left==p)
				choose='0';
			else
				choose='1';
		
	//		cout<<choose<<endl;
			a+=choose;
			p=par;
			par=huff_man[par].par;
		}
		cout<<endl<<i<<" "<<a<<endl;
		f1<<a<<" ";
		a="";
	}


}
int main()
{
	int t1,t2,place;
	huff *huff_man;
	huff_man = new huff[N];
	init_huff(huff_man);
	for(place=N/2+1;place<N;place++)
	{
		t1=seek_min(huff_man,place);
		huff_man[t1].par=place;
		t2=seek_min(huff_man,place);
		huff_man[t2].par=place;
	//	cout<<t1<<" "<<t2<<endl;
		huff_man=merge_tree(huff_man,t1,t2,place);	
	}
	display(huff_man);
	make_code(huff_man);
	string a;
	a="ppp";
	cout<<a<<endl;
	a="";
	a+="o";
	cout<<a<<endl;
	return 0;	
}