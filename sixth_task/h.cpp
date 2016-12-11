#include<iostream>
using namespace std;
#include<fstream>
#include<stack>
#include<string.h>
#include<algorithm>
#include<cctype>
#include<string>
#include<time.h>
#include<map>
#include<queue>
#include<vector>
struct huff
{
	int data;
	int left;
	int right;
	int par;
	int chr;
	huff(int a=255){chr=a;}
};
int N;
huff *init_huff(huff *huff_man,map<char,int> cnt)
{
//	fstream f1;
	int i=1;
	huff_man = new huff[N];
//	f1.open("huff_num.txt",ios::in);
	for(map<char,int>::reverse_iterator rit=cnt.rbegin();rit!=cnt.rend();rit++)
	{
	//	cout<<(*rit).first<<","<<(*rit).second<<endl;
		huff_man[i].data=(*rit).second;
		huff_man[i].chr=(*rit).first;
		huff_man[i].par=0;
		huff_man[i].left=0;
		huff_man[i].right=0;
		cout<<i<<" "<<huff_man[i].data<<endl;
		i++;
	}
//	f1.close();
	return huff_man;
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
map<char,int> read_origin()
{
	//if txt in file then cancel the '//'
	map<char,int> cnt;
	char chr;
//	fstream f1;
	int i;
	int n=0;
	int rand_num=200;
	srand(time(NULL));
	cout<<"read"<<endl;
//	f1.open("huff_origin.txt",ios::in);
	while(rand_num--)
	{
		//chr=f1.get();
		chr=65+rand()%30;
		cout<<chr<<" ";
		if(!cnt.count(chr))
		{
			n++;
			cnt[chr]=0;
		}
		cnt[chr]++;
	}

	for(map<char,int>::reverse_iterator rit=cnt.rbegin();rit!=cnt.rend();rit++)
	{
		cout<<(*rit).first<<","<<(*rit).second<<endl;
	}
//	f1.close();
	cout<<endl<<n<<endl;
	N=n*2;
	cout<<N;
	return cnt;
}

void display(huff *huff_man)
{
	int i;
	for(i=1;i<N;i++)
	{
		cout<<i<<" "<<(char)huff_man[i].chr<<" "<<huff_man[i].data<<" "<<huff_man[i].par<<" "<<huff_man[i].left<<" "<<huff_man[i].right<<endl;
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
string * make_code(huff *huff_man)
{
	string a;
	int count =0 ;
	fstream f1;
	f1.open("huff_man.txt",ios::out);
	string *encode;
	encode= new string [N/2+1];
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
		cout<<endl<<(char)huff_man[i].chr<<" "<<a<<endl;
	//	cout<<a<<endl;
		f1<<a<<" ";
		encode[i]=a;
		a="";
	}
	f1.close();
	return encode;
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
void make_huff(huff * huff_man)
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
void turn_txt_to_huff()
{
	fstream f1,f2,f3;
	int chr;
	string code;
	int i=1;
	f1.open("huff_man.txt",ios::in);
	map<int,string> encode;
	while(!f1.eof())
	{
		if(f1.eof())
			break;
		f1>>chr;
		if(f1.eof()) break;
		f1>>code;
		encode[chr]=code;
	}
	f1.close();
	f2.open("encode.txt",ios::out);
	f3.open("huff_origin.txt",ios::in);  
	char ch;
	while(!f3.eof())
	{
		ch=f3.get();
		f2<<encode[(int)ch];
	}
	f2.close();
	f3.close();
}
void write_tree(map<char,string>en_code,huff * huff_man)
{
	fstream f1,f2;
	f1.open("huff_man.txt",ios::out);
	f2.open("huff_man_tree.dat",ios::out|ios::binary);
	cout<<"write:"<<endl;
	cout<<sizeof(huff_man)<<" "<<sizeof(huff)*N<<" "<<endl;
	for(int i=0;i<N;i++)
		f2.write((char *)&huff_man[i],sizeof(huff));
	display(huff_man);
	for(map<char,string>::reverse_iterator rit=en_code.rbegin();rit!=en_code.rend();rit++)
	{
		f1<<(int)(*rit).first<<" "<<(*rit).second<<endl;
		cout<<(int)(*rit).first<<" "<<(*rit).second<<endl;
	}
	f1.close();
	f2.close();
}
huff* read_tree()
{
	huff *tree;
	tree=new huff[N];
	int a;
	fstream f1;
	f1.open("huff_man_tree.dat",ios::binary|ios::in);
	f1.read((char *)tree,sizeof(huff)*N);
	f1.close();
	cout<<"tree:"<<endl;
	system("pause");
	display(tree);
	return tree;
}

void decode()
{
	fstream f1,f2;
	f1.open("encode.txt",ios::in);
	f2.open("decode.txt",ios::out);
	cout<<"decode"<<endl;
	int tmp;
	char chr;
	huff *huff_man;
	huff_man=read_tree();
//	map<int,char> encode;
//	encode=read_code();
	display(huff_man);
//	system("pause");
	while(!f1.eof())
	{
		tmp=N-1;
		cout<<tmp;
		while(((tmp==N-1)||tmp>N/2)&&!f1.eof())
		{
		//	cout<<"p"<<endl;
			f1>>chr;
			cout<<chr<<endl;
			if(chr=='0')
			{
				tmp=huff_man[tmp].left;
			//	cout<<"left:"<<tmp<<"par : "<<huff_man[tmp].par<<endl;
			}else if(chr=='1')
			{
				tmp=huff_man[tmp].right;
			//	cout<<"right:"<<tmp<<"par : "<<huff_man[tmp].par<<endl;
			}
		}
	//	cout<<"out"<<endl;
	//	cout<<tmp<<endl;
		if(!f1.eof())
		{
			if(huff_man[tmp].chr!=-1)
			{
				f2<<(char)huff_man[tmp].chr;	
				cout<<(char)huff_man[tmp].chr;
			}
		}
		
	}
	f1.close();
	f2.close();

cout<<(int)'?'<<endl;

}
void de_huff()
{
	huff * huff_man;
	huff_man=read_tree();
//	turn_txt_to_huff(encode);
	display(huff_man);
	decode();

}
int main()
{
	int i=1;
	map<char,int> cnt;
	map<char,string> en_code;
	string * encode;
	huff * huff_man;
	cnt = read_origin();
	huff_man = init_huff(huff_man,cnt);

	make_tree(huff_man);	
	display(huff_man);
	encode = make_code(huff_man);
	for(map<char,int>::reverse_iterator rit=cnt.rbegin();rit!=cnt.rend();rit++)
	{
		cout<<(*rit).first<<","<<(*rit).second<<endl;
		en_code[(*rit).first]=encode[i++];
	}
	//front is encode
	// next is decode 
/*	write_tree(en_code,huff_man);

	turn_txt_to_huff();
	
	de_huff();
*/
	return 0;
}
