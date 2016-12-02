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
string encode[53];
void init_huff(huff *huff_man)
{
//	fstream f1;
	int i;
//	f1.open("huff_num.txt",ios::in);
	for(i=1;i<=(N/2);i++)
	{
		huff_man[i].data=0;
		huff_man[i].par=0;
		huff_man[i].left=0;
		huff_man[i].right=0;
//		cout<<i<<" "<<huff_man[i].data<<endl;
	}
//	f1.close();
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
	huff_man[place].data=huff_man[t1].data+huff_man[t2].data;
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
		while(par!=0)
		{
			if(huff_man[par].left==p)
				choose='0';
			else
				choose='1';
			a=choose+a;
			p=par;
			par=huff_man[par].par;
		}
		cout<<endl<<i<<" "<<a<<endl;
		f1<<a<<" ";
		a="";
	}
}
void get_rate(huff *huff_man)
{
	fstream f1;
	char chr;
	f1.open("huff_origin.txt");
	f1>>chr;
	while(!f1.eof())
	{
		if(chr>='A'&&chr<='Z')
			huff_man[chr-'A'+1].data++;
		else if(chr>='a'&&chr<='z')
			huff_man[chr-'a'+26+1].data++;
		cout<<chr;
		f1>>chr;
	}
	f1.close();
//	return huff_man;
}
int make_huff()
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
void make_tree(huff *huff_man)
{
	int t1,t2,place;
	for(place=N/2+1;place<N;place++)
	{
		t1=seek_min(huff_man,place);
		huff_man[t1].par=place;
		t2=seek_min(huff_man,place);
		huff_man[t2].par=place;
		huff_man=merge_tree(huff_man,t1,t2,place);	
	}
}
void turn_txt_to_huff(string *encode)
{
	fstream f1,f2,f3;
	char chr;
	int i=1;
	f1.open("huff_man.txt",ios::in);
	while(!f1.eof())
	{
		f1>>encode[i];
		cout<<encode[i]<<endl;
		i++;
	}
	f1.close();
	f2.open("encode.txt",ios::out);
	f3.open("huff_origin.txt",ios::in);
	while(!f3.eof())
	{
		f3>>chr;
		if(chr>='A'&&chr<='Z')
		{
			f2<<encode[chr-'A'+1]<<" ";
		}else if(chr>='a'&&chr<='z')
		{
			f2<<encode[chr-'a'+26+1]<<" ";
		}
	}
	f2.close();
	f3.close();
}
void write_tree(huff *huff_man)
{
	fstream f1;
	f1.open("huff_man_tree.dat",ios::binary|ios::out);
	f1.write((char *)huff_man,sizeof(huff)*N);
	f1.close();
}
huff* read_tree()
{
	huff *tree;
	tree=new huff[N];
	fstream f1;
	f1.open("huff_man_tree.dat",ios::binary|ios::in);
	f1.read((char *)tree,sizeof(huff)*N);
	f1.close();
	display(tree);
	return tree;
}
void decode(huff *huff_man)
{
	fstream f1,f2;
	f1.open("encode.txt",ios::in);
	f2.open("decode.txt",ios::out);
	
	int tmp;
	char chr;
	display(huff_man);
	while(!f1.eof())
	{
		tmp=N-1;
		cout<<tmp;
		while(((tmp==N-1)||tmp>N/2)&&!f1.eof())
		{
			cout<<"p"<<endl;
			f1>>chr;
			cout<<chr<<endl;
			if(chr=='0')
			{
				tmp=huff_man[tmp].left;
				cout<<"left:"<<tmp<<"par : "<<huff_man[tmp].par<<endl;
			}else if(chr=='1')
			{
				tmp=huff_man[tmp].right;
				cout<<"right:"<<tmp<<"par : "<<huff_man[tmp].par<<endl;
			}
		}
		cout<<"out"<<endl;
		cout<<tmp<<endl;
		if(!f1.eof())
		{
			if(tmp<=26)
			{
				f2<<(char)(tmp+'A'-1);
			}else{
				f2<<(char)(tmp+'a'-26);
			}
			while(!f1.eof()&&chr==' ')
			f1>>chr;
		}
		
	}
	f1.eof();
	f2.eof();

cout<<(int)'?'<<endl;

}
int main()
{
	
	huff *huff_man;
	
	huff_man = new huff[N];
/*	init_huff(huff_man);
	get_rate(huff_man);
	display(huff_man);
	
	make_tree(huff_man);
	display(huff_man);
	make_code(huff_man);
	write_tree(huff_man);
huff_man=read_tree();
	turn_txt_to_huff(encode);
	*/
	huff_man=read_tree();
//	decode(huff_man);

	
//

	
	return 0;
}