//完成第一、二、三次上机题
//1．输入稀疏矩阵，建立稀疏矩阵三元组顺序结构，实现转置（1、2）；
//2. 统计一篇英文文章中各单词出现的频度。
//   输入： 一篇txt格式英文内容
//   输出： 单词：频度      例如： the: 10;  long: 5 
//3. 利用栈操作实现八皇后问题求解 (选做题) 。

#include<iostream>
#include<string>
using namespace std;
#include<fstream>

struct word_place{
	int place;
	word_place * w_next;
};
struct word{
	int count;
	string words;
	word *next,*pre;
	word_place *w_p_cur_next,*w_p_head;
};
void man_txt()
{
	fstream f1,f2;
	char chr;
	f1.open("eng.txt",ios::in);
	f2.open("en2.txt",ios::out);
	while(!f1.eof())
	{
		chr=f1.get() ;
		if(chr!=','&&chr!='.'&&chr!='\"'&&chr!='?'&&chr!='!')
		{
			f2<<chr;
			cout<<chr;
		}
	}
	f1.close();
	f2.close();
	cout<<"end";
}
void display(word * p)
{
	word *q;
	word_place *w_p;
	fstream f1;
	f1.open("rand.txt",ios::out);
	int i=0;
	while(i<52)
	{
		q=&p[i];
		while(q)
		{
			cout<<"\t"<<q->words<<" \t"<<q->count<<" "<<endl;
			f1<<"\t"<<q->words<<" \t"<<q->count<<" "<<endl;
			w_p=q->w_p_head;
			while(w_p)
			{
				f1<<"\t\t"<<w_p->place<<endl;
				w_p=w_p->w_next;
			}
			q=q->next;
		}
		cout<<endl;
		i++;
	}

}
int comp()
{

	fstream f1;
	string a,b,c;
	a="what";
	c="b";
	b="whas";
	f1.open("ee2.txt",ios::in);

	int i=0;
	word w[52];
	word *cur[52];
	word_place *w_p;
	word *p,*q;
	int place;
	string tmp,tmp_first;
	for(i=0;i<26;i++)
	{
		w[i].words=(char)(i+'A');
		w[i].next=NULL;
		w[i].pre=NULL;
		w[i].w_p_cur_next=NULL;
		w[i].w_p_head=NULL;
		w[i].count=0;
		w[i+26].words=(char)(i+'a');
		w[i+26].next=NULL;
		w[i+26].pre=NULL;
		w[i+26].w_p_cur_next=NULL;
		w[i+26].w_p_head=NULL;
		w[i+26].count=0;
		cout<<w[i].words<<" "<<w[i+26].words<<endl;
	}

	cout<<(char)('A'+5)<<endl;
	cout<<(a.substr(0,1).compare("a"))<<endl;
	while(!f1.eof())
	{	
		place=f1.tellg();
		f1>>tmp;
		tmp_first=tmp.substr(0,1);
		cout<<tmp<<endl;
		if((tmp_first.compare("A")>=0)&&(tmp_first.compare("Z")<=0))
		{
			i=tmp_first[0]-'A';
		}else if((tmp_first.compare("a")>=0)&&(tmp_first.compare("z")<=0)){
			i=tmp_first[0]-'a'+26;
		}else{
			i=-1;
		}
		if(i!=-1)
		{
			p = new word;
			p->words=tmp;
			p->next=NULL;
			cout<<"p->words: "<<p->words<<endl;
			if(w[i].next==NULL)
			{
				p->pre=&w[i];
				w[i].next=p;
				cur[i]=p;
				p->count=1;
				cout<<"new: "<<p->words<<endl;
				//w_p
				w_p = new word_place;
				w_p->place=place;
				w_p->w_next=NULL;
				cur[i]->w_p_head=w_p;
				cur[i]->w_p_cur_next=w_p;
			//	cout<<"ppp"<<endl;
			}else{
				cout<<cur[i]->words<<" "<<tmp<<" "<<cur[i]->words.compare(tmp)<<" "<<(cur[i]->words.compare(tmp)<0&&cur[i]->next);
				if(cur[i]->words.compare(tmp)>0)
				{
					cout<<"++++++++++++++++++"<<endl;
					cout<<cur[i]->words<<" "<<endl;
					cout<<tmp<<endl;
					cout<<"++++++++"<<endl;

					while(cur[i]->words.compare(tmp)>0&&cur[i]!=&w[i])
					{
						cur[i]=cur[i]->pre;
						cout<<"---------"<<endl;
					}
					cout<<"++++++++++++++++++"<<endl;
					cout<<cur[i]->words<<" "<<endl;
					cout<<tmp<<endl;
					cout<<"++++++++"<<endl;
				}else if(cur[i]->words.compare(tmp)<0){
					cout<<"................."<<endl;
					cout<<cur[i]->words<<" "<<endl;
					cout<<tmp<<endl;
					cout<<"..........."<<endl;
					while(cur[i]->words.compare(tmp)<0&&cur[i]->next)
					{
						cur[i]=cur[i]->next;
					}
					
						if(cur[i]->words.compare(tmp)>0)
						{
							cur[i]=cur[i]->pre;
						}
					
					cout<<"..........."<<endl;
					cout<<cur[i]->words<<" "<<endl;
					cout<<tmp<<endl;
					cout<<".........."<<endl;
				}
				if(cur[i]->words.compare(tmp)==0)
				{
					cout<<endl<<endl<<"="<<cur[i]->words<<"===="<<p->words<<endl;
					cout<<"pop"<<cur[i]->w_p_cur_next->place<<endl;
					
					w_p = new word_place;
					w_p->place=place;
					w_p->w_next=NULL;

					if(cur[i]->w_p_cur_next)
					{
						cout<<"pop"<<cur[i]->w_p_cur_next->place<<endl;
					}
					cur[i]->w_p_cur_next->w_next=w_p;
					cur[i]->w_p_cur_next=w_p;
					cur[i]->count++;
				}else{
					p->pre=cur[i];
					p->next=cur[i]->next;
					if(cur[i]->next)
					{
						cur[i]->next->pre=p;
					}
					cur[i]->next=p;//插入word节点
					//插入w_p节点
					w_p = new word_place;
					w_p->place=place;
					w_p->w_next=NULL;
					p->w_p_head=w_p;
					p->w_p_cur_next=w_p;
					p->count=1;
					cur[i]=p;
					cout<<cur[i]->words<<" place: "<<cur[i]->w_p_cur_next->place<<endl;
					
				}
			}
		}
		cout<<"old"<<endl;
		
	}
	display(w);
	f1.close();
	return 0;
}
int main()
{
	comp();	
	return 0;
}

				
