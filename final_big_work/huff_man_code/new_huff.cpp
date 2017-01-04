#include<iostream>
using namespace std;
#include<fstream>
#include<stack>
#include<string.h>
#include<algorithm>
#include<cctype>
#include<string>
#include<string.h>
#include<map>
#include<queue>
#include<vector>
#define FILE_TO_ENCODE "file_to_encode/"
#define FILE_TO_DECODE "file_to_decode/"
#define HUFF_TREE_DAT "huff_tree_dat/"
#define ENCODED_FILE "encoded_file/"
#define DECODED_FILE "decoded_file/"
#define SAVED_ENCODE "file_to_encode.txt"
#define SAVED_DECODE "file_to_decode.txt"
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
	fstream f1;
	int i=1;
	huff_man = new huff[N];
	f1.open("huff_num.txt",ios::in);
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
	f1.close();
	return huff_man;
}

char* get_file_name(char *pre,char *&suffix)
{
	char new_file[30];
	char *a;
	a=new_file;
	strcpy(a,pre);
	strcat(a,suffix);
	strcpy(suffix,a);
	cout<<suffix<<endl;
	return suffix;
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
map<char,int> read_origin(char *f_origin)
{
	map<char,int> cnt;
	char chr;
	fstream f1;
	int i;
	int n=0;
	f1.open(f_origin,ios::in);
	cout<<f_origin<<endl;
	system("pause");
	while(!f1.eof())
	{
		chr=f1.get();
		if(!cnt.count(chr))
		{
			n++;
			cnt[chr]=0;
		}
		cnt[chr]++;
		cout<<chr<<endl;
	}

	for(map<char,int>::reverse_iterator rit=cnt.rbegin();rit!=cnt.rend();rit++)
	{
		cout<<(*rit).first<<","<<(*rit).second<<endl;
	}
	f1.close();
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
		cout<<i<<" "<<huff_man[i].chr<<" "<<huff_man[i].data<<" "<<huff_man[i].par<<" "<<huff_man[i].left<<" "<<huff_man[i].right<<endl;
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
		cout<<a<<endl;
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
void turn_txt_to_huff(char *f_encode,char *f_origin)
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
	f2.open(f_encode,ios::out);
	f3.open(f_origin,ios::in);  
	char ch;
	while(!f3.eof())
	{
		ch=f3.get();
		f2<<encode[(int)ch];
	}
	f2.close();
	f3.close();
}
void write_tree(map<char,string>en_code,huff * huff_man,char * f_huff)
{
	fstream f1,f2;
	f1.open("huff_man.txt",ios::out);
	f2.open(f_huff,ios::out|ios::binary);
	cout<<"write:"<<endl;
	cout<<sizeof(huff_man)<<" "<<sizeof(huff)*N<<" "<<endl;
	f2.write((char*)&N,sizeof(int));
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
huff* read_tree(char * f_huff)
{
	huff *tree;
	int a;
	fstream f1;
	f1.open(f_huff,ios::binary|ios::in);
	if(f1.fail())
	{
		cout<<"can't open file: "<<f_huff<<endl;
		exit(1);
	}
	f1.read((char *)&N,sizeof(int));
	cout<<N<<endl;
	system("pause");
	tree=new huff[N];
	f1.read((char *)tree,sizeof(huff)*N);
	f1.close();
	cout<<"tree:"<<endl;
	system("pause");
	display(tree);
	return tree;
}

void decode(char *f_encode,char *f_decode,char *f_huff)
{
	fstream f1,f2;
	f1.open(f_encode,ios::in);
	f2.open(f_decode,ios::out);
	int tmp;
	char chr;
	huff *huff_man;
	huff_man=read_tree(f_huff);
	cout<<"huff_tree"<<endl;
	display(huff_man);
	while(!f1.eof())
	{
		tmp=N-1;
		cout<<tmp;
		while(((tmp==N-1)||tmp>N/2)&&!f1.eof())
		{
			f1>>chr;
			cout<<chr<<endl;
			if(chr=='0')
			{
				tmp=huff_man[tmp].left;
			}else if(chr=='1')
			{
				tmp=huff_man[tmp].right;
			}
		}
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
}

int encode_all_file()
{
	fstream f_to_encode;
	char f_o[30],f_en[30],f_hu[30];
	char *f_origin,*f_encode,*f_huff;
	f_origin=f_o;
	f_encode=f_en;
	f_huff=f_hu;
	f_to_encode.open(SAVED_ENCODE,ios::in);
	if(f_to_encode.fail())
	{
		cout<<"sorry cant't open file"<<endl;
		exit(1);
	}
	else
	{
		while(!f_to_encode.eof())
		{
			f_to_encode>>f_origin>>f_encode>>f_huff;
			cout<<f_origin<<" "<<f_encode<<" "<<f_huff<<endl;
			get_file_name(ENCODED_FILE,f_encode);
			get_file_name(HUFF_TREE_DAT,f_huff);
			get_file_name(FILE_TO_ENCODE,f_origin);
			cout<<f_origin<<" "<<f_encode<<" "<<f_huff<<endl;
			int i=1;
			map<char,int> cnt;
			map<char,string> en_code;
			string * encode;
			huff * huff_man;
			cnt = read_origin(f_origin);
			huff_man = init_huff(huff_man,cnt);
			make_tree(huff_man);	
			display(huff_man);
			encode = make_code(huff_man);
			for(map<char,int>::reverse_iterator rit=cnt.rbegin();rit!=cnt.rend();rit++)
			{
				cout<<(*rit).first<<","<<(*rit).second<<endl;
				en_code[(*rit).first]=encode[i++];
			}
			write_tree(en_code,huff_man,f_huff);
			turn_txt_to_huff(f_encode,f_origin);
		}
		f_to_encode.close();
	}
	return 0;
}
int decode_all_file()
{
	fstream f_to_decode;
	char f_decode[30],f_encode[30],f_huff[30];
	f_to_decode.open(SAVED_DECODE,ios::in);
	if(f_to_decode.fail())
	{
		cout<<"sorry cant't open file"<<endl;
		exit(1);
	}
	else
	{
		char f_d[30],f_en[30],f_hu[30];
		char *f_decode,*f_encode,*f_huff;
		f_decode=f_d;
		f_encode=f_en;
		f_huff=f_hu;
		while(!f_to_decode.eof())
		{
			f_to_decode>>f_encode>>f_decode>>f_huff;
			get_file_name(DECODED_FILE,f_decode);
			get_file_name(HUFF_TREE_DAT,f_huff);
			get_file_name(FILE_TO_DECODE,f_encode);
			cout<<f_encode<<" "<<f_decode<<" "<<f_huff<<endl;
			system("pause");
			decode(f_encode,f_decode,f_huff);
		}
		f_to_decode.close();
	}
	return 0;
}
int main()
{
	/*
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
	*/
	/*
	for(map<char,int>::reverse_iterator rit=cnt.rbegin();rit!=cnt.rend();rit++)
	{
		cout<<(*rit).first<<","<<(*rit).second<<endl;
		en_code[(*rit).first]=encode[i++];
	}
	*/
	/*
	write_tree(en_code,huff_man);

	turn_txt_to_huff();
	*/
	//de_huff();
	int flag=1;
	int choice=0;
	fstream f_to_encode;
	fstream f_to_decode;
	while(flag)
	{
		cout<<"加密请输入0 \n 解密请输入1"<<endl;
		cin>>choice;
		if(choice==0)
		{
			cout<<"请将待加密文件存放于file_to_encode文件夹下"<<endl<<endl;
			system("pause");
			cout<<"请将 待加密文件名 加密后文件名 生成哈弗曼树文件名 写在 file_to_encode.txt中"<<endl<<endl;
			cout<<"格式为 待加密文件名 加密后文件名 生成哈弗曼树文件名 "<<endl<<endl;
			cout<<"如： huff_origin.txt encoded_1.txt huff_1.dat"<<endl<<endl;
			cout<<"请再次确认"<<endl<<endl;
			system("pause");
			encode_all_file();

		}
		else if(choice==1)
		{
			cout<<"请将待解密文件存放于file_to_decode文件夹下"<<endl;
			system("pause");
			cout<<"请将 待解密文件名 解密后文件名 哈弗曼树文件名 写在 file_to_decode.txt中"<<endl<<endl;
			cout<<"格式为 待解密文件名 解密后文件名 哈弗曼树文件名 "<<endl<<endl;
			cout<<"如： encoded_1.txt huff_origin_1.txt  huff_1.dat"<<endl<<endl;
			cout<<"请再次确认"<<endl<<endl;
			system("pause");
			decode_all_file();
		}
		cout<<"flag: "<<endl;
		cin>>flag;
	}

	return 0;
}
