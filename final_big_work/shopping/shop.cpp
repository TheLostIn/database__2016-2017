#include<iostream>
#include<map>
#include<string>
#include<string.h>
#include<fstream>
using namespace std;
typedef struct shop_info
{
	int id;
	string name;
	int credity;
	int product_num;
	shop_info(int a,string b,int c,int d)
	{
		id=a;
		name=b;
		credity=c;
		product_num=d;
	}
	shop_info()
	{
		id=0;
		name=' ';
		credity=0;
		product_num=0;
	}
}shop_info;
typedef struct product
{
	int price;
	int sale_num;
	product *next_same_product,*last_same_product;
	product *shop_next_product;
	shop_info *belong_shop;
	product(int a,int b,shop_info *c)
	{
		price=a;
		sale_num=b;
		next_same_product=NULL;
		last_same_product=NULL;
		shop_next_product=NULL;
		belong_shop=c;
	}
	product()
	{
		price=0;
		sale_num=0;
		next_same_product=NULL;
		last_same_product=NULL;
		shop_next_product=NULL;
		belong_shop=NULL;
	}
}product;
typedef struct shop
{
	shop_info shop_main;
	product *first_product;
	shop *next_shop;
}shop;
void insert_product(product all_pro[],product *pro,int id)
{
	product *p,*q;
	if(all_pro[id].next_same_product==NULL)
	{
		all_pro[id].next_same_product=pro;
	}
	else
	{
		p=all_pro[id].next_same_product;
		while(p->sale_num>pro->sale_num&&p->next_same_product)
		{
			p=p->next_same_product;
		}
		pro->last_same_product=p;
		pro->next_same_product=p->next_same_product;
		if(p->next_same_product)
		{
			p->next_same_product->last_same_product=pro;
		}
		p->next_same_product=pro;
	}
}
void read_shop(shop *head)
{
	fstream f1;
	shop *s,*p;
	int product_num=0;
	string pro_name;
	product *pro;
	product all_pro[100];
	memset(all_pro,NULL,sizeof(all_pro));
	map<string,int>product_match;
	s=head;
	f1.open("shop.txt",ios::in);
	while(!f1.eof())
	{
		p = new shop;
		pro = new product;
		int price;
		f1>>p->shop_main.id>>p->shop_main.name>>p->shop_main.product_num;
		cout<<p->shop_main.id<<" "<<p->shop_main.name<<" "<<p->shop_main.product_num<<endl;
		for(int i=0;i<p->shop_main.product_num;i++)
		{
			f1>>pro_name;
			if(!product_match.count(pro_name))
			{
				product_match[pro_name]=product_num++;
			}
			f1>>pro->price;
			f1>>pro->sale_num;
			pro->belong_shop=&(p->shop_main);
			insert_product(all_pro,pro,product_match[pro_name]);
		}
		s->next_shop=p;
		s=p;
	}
	f1.close();

}
int main()
{
	shop *root;

//	read_shop(root);
	fstream f1;
	f1.open("shop.txt",ios::in);
	string a;
	while(!f1.eof())
	{
		f1<<a;
		cout<<a<<endl;
	}
	return 0;
}