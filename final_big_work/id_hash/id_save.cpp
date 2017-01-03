/*
53 012 m 320602198609292020
54 102 w 3206231987081527508
55 110 m 320611198611252614
56 111 w 320602198606300021
57 112 w 320602198509120547
60 113 m 320683198511032018
61 114 w 320683198812046026
*/
//id_example.txt


/*
123123123
123123123
123123123
320602198704121529
320611198407212631
320623198502280013
320681198609114414
320682198505083605
32060219861072029
320621198806242048
320611198611252614
320602198606300021
320602198509120547
320683198511032018
320683198812046026
*/
//exam.txt
#include<iostream>
#include<fstream>
using namespace std;
#include<string>
typedef struct id_node{
	int num;
	string id_num;
	string name;
	id_node *next_id;
	string sex;
	id_node()
	{
		sex="nu";
		id_num=' ';
		name=' ';
		next_id=NULL;
	}
}id_node;
typedef struct id_info
{
	id_node id[100];
	int id_num;
	id_info(){id_num=0;}
}id_all_info;
int Hash(string a)
{
	//320602198605140521
	//012345678901234567
	//    02  8605140521
	//028+506+140+125
	int b[19];
	for(int i=0;i<a.length();i++)
	{
		b[i]=a[i]-'0';
	//	cout<<b[i]<<endl;
	}
	return ((b[4]+b[11]+b[12]+b[18])*100+(b[5]+b[10]+b[13]+b[17])*10+(b[8]+b[9]+b[15]+b[16]))%100;
}
void read_id_info(id_all_info &ID)
{
	fstream f1;
	f1.open("id_example.txt",ios::in);
	id_node *id,*p;
	int j;
	while(!f1.eof())
	{
		id = new id_node;
		f1>>id->num>>id->name>>id->sex>>id->id_num;
		j=Hash(id->id_num);
//		cout<<j<<endl;
	//	system("pause");
		ID.id_num++;
		if(ID.id[j].next_id==NULL)
		{
			ID.id[j].next_id=id;
		}
		else
		{
			p=ID.id[j].next_id;
			while(p->next_id!=NULL)
			{
				p=p->next_id;
			}
			p->next_id=id;
		}
	}
	f1.close();
}
void display_id_info(id_all_info ID)
{
	int n,i=0;
	n=ID.id_num;
	id_node *p;
	while(i<100)
	{
		p=ID.id[i].next_id;
		while(p)
		{
		//	system("pause");
			cout<<i<<" "<<p->num<<" "<<p->name<<" "<<p->id_num<<endl;
			p=p->next_id;
		}
		i++;
	//	cout<<i<<endl;

	}
}
id_node* search_is_id_exist(id_all_info ID,string a)
{
	int j;
	j=Hash(a);
	id_node *p;
	p=ID.id[j].next_id;
	int flag=0;
	while(p&&(p->id_num.compare(a)))
	{
		p=p->next_id;
	}
	if(p)
	{
		return p;
	}
	return NULL;
}
void test_search(id_all_info ID)
{
	fstream f1;
	f1.open("exam.txt",ios::in);
	string b;
	id_node *p;
	int flag=0;
	while(!f1.eof())
	{
//		system("pause");
		p=NULL;
		f1>>b;
		if(b.length()<=20&&b.length()>=16)
		{
			p=search_is_id_exist(ID,b);
		}
		else
		{
			cout<<"searching: "<<b<<endl;
			cout<<"This id number is illegal"<<endl<<endl;
		}
		if(p)
		{
			cout<<"searching: "<<b<<endl;
			cout<<p->num<<" "<<p->name<<" "<<p->sex<<" "<<p->id_num<<endl<<endl;
		}
	}
	f1.close();
}
int main()
{
	id_all_info ID;
	read_id_info(ID);
	display_id_info(ID);
	test_search(ID);
	return 0;
}