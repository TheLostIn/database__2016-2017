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
	string product_name;
	product *next_same_product,*last_same_product;
	product *shop_next_product;
	shop_info *belong_shop;
	product(int a,int b,shop_info *c,string d)
	{
		price=a;
		sale_num=b;
		next_same_product=NULL;
		last_same_product=NULL;
		shop_next_product=NULL;
		belong_shop=c;
		product_name=d;
	}
	product()
	{
		price=0;
		sale_num=0;
		next_same_product=NULL;
		last_same_product=NULL;
		shop_next_product=NULL;
		belong_shop=NULL;
		product_name=' ';
	}
}product;
typedef struct shop
{
	shop_info shop_main;
	product *first_product;
	shop *next_shop;
	shop()
	{
		first_product=new product;
		next_shop=NULL;
	}
}shop;
typedef struct all_shop
{
	shop root;
	shop *head,*tail;
	int shop_num;
	int product_num;
	map<string,int>product_match;
	product all_pro[100];
	all_shop()
	{
		head=&root;
		tail=NULL;
		shop_num=0;
		product_num=0;
	}
}all_shop;
void insert_product(product all_pro[],product *pro,int id)
{
	product *p;
	if(all_pro[id].next_same_product==NULL)
	{
		all_pro[id].next_same_product=pro;
	}
	else
	{
		p=&all_pro[id];
		while(p->next_same_product&&(p->next_same_product->sale_num>pro->sale_num))
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
	//cout<<"ook"<<endl;
}
void display_product(all_shop All_s)
{
	product *p;
	for(int i=0;i<All_s.product_num;i++)
	{
	//int i=1;
		p=All_s.all_pro[i].next_same_product;
		while(p!=NULL)
		{
			cout<<p->belong_shop->name<<" "<<p->product_name<<" "<<p->price<<" "<<p->sale_num<<endl;
			p=p->next_same_product;
		}
	}
}
void display_shops(all_shop All_s)
{
	shop *p,*head;
	product *q;
	head=&All_s.root;
	p=head->next_shop;
	while(p)
	{
		cout<<p->shop_main.id<<" "<<p->shop_main.name<<" "<<p->shop_main.credity<<" "<<p->shop_main.product_num<<endl;
		q=p->first_product->shop_next_product;
		while(q)
		{
			cout<<q->product_name<<" "<<q->price<<" "<<q->sale_num<<endl;
			q=q->shop_next_product;
		}
		p=p->next_shop;
	}
	
}
void write_shop(shop head,char *save_file)
{
	fstream f1;
	f1.open(save_file,ios::out);
	shop *p;
	product *q;
	p=head.next_shop;
	while(p)
	{
		f1<<p->shop_main.id<<" "<<p->shop_main.name<<" "<<p->shop_main.credity<<" "<<p->shop_main.product_num<<" ";
		q=p->first_product->shop_next_product;
		while(q)
		{
			f1<<q->product_name<<" "<<q->price<<" "<<q->sale_num<<" ";
			q=q->shop_next_product;
		}
		f1<<"\n";
		p=p->next_shop;
	}
	f1.close();


}
void read_shop(all_shop &All_s)
{
	fstream f1;
	shop *s,*p;

	string pro_name;
	product *pro;
//	product all_pro[100];
	product *all_pro;
	all_pro=All_s.all_pro;
	memset(all_pro,NULL,sizeof(all_pro));
//	map<string,int>All_s.product_match;
	s=&All_s.root;
	//s=new shop;
	f1.open("shop.txt",ios::in);
	while(!f1.eof())
	{
		p = new shop;	
		int price;
		f1>>p->shop_main.id>>p->shop_main.name>>p->shop_main.credity>>p->shop_main.product_num;
	//	cout<<p->shop_main.id<<" "<<p->shop_main.name<<" "<<p->shop_main.credity<<" "<<p->shop_main.product_num<<endl;
		for(int i=0;i<p->shop_main.product_num;i++)
		{
			pro = new product;
			f1>>pro_name;
			if(!All_s.product_match.count(pro_name))
			{
				All_s.product_match[pro_name]=All_s.product_num++;
			}
			f1>>pro->price;
			f1>>pro->sale_num;
			pro->product_name=pro_name;
			//cout<<pro_name<<" "<<pro->price<<" "<<pro->sale_num<<endl;
			pro->belong_shop=&(p->shop_main);
			if(!p->first_product->shop_next_product)
			{
				p->first_product->shop_next_product=pro;
			}
			else
			{
				pro->shop_next_product=p->first_product->shop_next_product;
				p->first_product->shop_next_product=pro;
			}
			insert_product(all_pro,pro,All_s.product_match[pro_name]);
		}
		s->next_shop=p;
		s=p;
		All_s.shop_num++;
	}
	All_s.tail=p;
	f1.close();
}
shop *locate_shop(all_shop All_s,string s_name)
{
	shop *p;
	p=All_s.head->next_shop;
	while(p)
	{
		if(!p->shop_main.name.compare(s_name))
			return p;
		p=p->next_shop;
	}
	return NULL;
}
shop *locate_shop_p(all_shop All_s,string s_name)//locate_parent
{
	shop *p;
	p=All_s.head;
	while(p->next_shop)
	{
		if(!p->next_shop->shop_main.name.compare(s_name))
			return p;
		p=p->next_shop;
	}
	return NULL;
}
product* locate_product(shop *p,string pro_name)
{
	product *q;
	q=p->first_product;
	while(q)
	{
		if(q->product_name.compare(pro_name)==0)
			return q;
		q=q->shop_next_product;
	}
	return NULL;
}
product* locate_product_p(shop *p,string pro_name)
{
	product *q;
	q=p->first_product;
	while(q->shop_next_product)
	{
		if(q->shop_next_product->product_name.compare(pro_name)==0)
			return q;
		q=q->shop_next_product;
	}
	return NULL;
}
void adjust_product(product *pro)
{
	product *p;
	p=pro;
	if(p)
	cout<<p->product_name<<p->sale_num<<endl;
	
	if(p->last_same_product||p->next_same_product)
	{
	
		if(p->last_same_product->last_same_product&&(p->last_same_product->sale_num<pro->sale_num))
		{
			p=p->last_same_product;
			while(p->last_same_product&&(p->sale_num<pro->sale_num))
				p=p->last_same_product;
			cout<<"locate:"<<p->product_name<<p->sale_num<<endl;
		}
		else if(p->next_same_product&&(p->next_same_product->sale_num>pro->sale_num))
		{
			
			cout<<"locate:"<<p->product_name<<p->sale_num<<endl;
			p=p->next_same_product;

				while(p->next_same_product&&(p->sale_num>pro->sale_num))
				{
					p=p->next_same_product;
				}
				
				cout<<"locate:"<<p->product_name<<p->sale_num<<endl;
				if(p->next_same_product)
				{
					p=p->last_same_product;
				}	
				cout<<"locate:"<<p->product_name<<p->sale_num<<endl;
		}
		if(p!=pro)
		{
			if(pro->last_same_product)
				pro->last_same_product->next_same_product=pro->next_same_product;
			if(pro->next_same_product)
				pro->next_same_product->last_same_product=pro->last_same_product;
			pro->last_same_product=p;
			pro->next_same_product=p->next_same_product;
			if(p->next_same_product)
			p->next_same_product->last_same_product=pro;
			p->next_same_product=pro;
		}
	}
}
void add_product(all_shop &All_s)
{
	//locate the shop
	fstream f1;
	int n;
	f1.open("add_pro.txt",ios::in);
	while(!f1.eof())
	{
		string add_s;
		shop *p;
		int i=0;
		product *pro;
		f1>>add_s;
		f1>>n;
		p=locate_shop(All_s,add_s);
		if(p)
		{
			cout<<"found"<<endl;
			cout<<p->shop_main.product_num<<endl;
			string add_pro;
			while(!f1.eof()&&i<n)
			{
				f1>>add_pro;
			//	cout<<add_pro<<endl;
				pro=locate_product(p,add_pro);
				if(!pro)
				{
			//		cout<<"null"<<add_pro<<endl;
			//		cout<<add_pro<<endl;
					if(!All_s.product_match.count(add_pro))
					{
						All_s.product_match[add_pro]=All_s.product_num++;
					}
					pro=new product;
					pro->product_name=add_pro;
			
					f1>>pro->price>>pro->sale_num;
			//		cout<<"price: "<<pro->price<<"vsale: "<<pro->sale_num<<endl;
					pro->belong_shop=&p->shop_main;
					pro->shop_next_product=p->first_product->shop_next_product;
					p->first_product->shop_next_product=pro;
					p->shop_main.product_num++;
					insert_product(All_s.all_pro,pro,All_s.product_match[add_pro]);
				}
				else
				{
					f1>>pro->price>>pro->sale_num;
					pro->product_name=add_pro;
					adjust_product(pro);
				}
				i++;
			}
		}
	}
	
	f1.close();
}
void add_shop(all_shop &All_s)
{
	shop *p;
	fstream f1;
	shop *s;
	string pro_name;
	product *pro;
	product *all_pro;
	all_pro=All_s.all_pro;
	memset(all_pro,NULL,sizeof(all_pro));
	s=All_s.tail;
	f1.open("new_shop.txt",ios::in);
	while(!f1.eof())
	{
		p=new shop;
		f1>>p->shop_main.name>>p->shop_main.credity>>p->shop_main.product_num;
		p->shop_main.id=All_s.shop_num+1;
		cout<<p->shop_main.id<<" "<<p->shop_main.name<<" "<<p->shop_main.credity<<" "<<p->shop_main.product_num<<endl;	
		for(int i=0;i<p->shop_main.product_num;i++)
		{
			pro = new product;
			f1>>pro_name;
			if(!All_s.product_match.count(pro_name))
			{
				All_s.product_match[pro_name]=All_s.product_num++;
			}
			f1>>pro->price;
			f1>>pro->sale_num;
			pro->product_name=pro_name;
			cout<<pro_name<<" "<<pro->price<<" "<<pro->sale_num<<endl;
			pro->belong_shop=&(p->shop_main);
			if(!p->first_product->shop_next_product)
			{
				p->first_product->shop_next_product=pro;
			}
			else
			{
				pro->shop_next_product=p->first_product->shop_next_product;
				p->first_product->shop_next_product=pro;
			}
			insert_product(all_pro,pro,All_s.product_match[pro_name]);
		}
		s->next_shop=p;
		s=p;
		All_s.shop_num++;
	//	cout<<"ok"<<endl;
	}
	f1.close();
}
void buy_product(all_shop &All_s)
{
	fstream f1;
	shop *s_p;
	product *pro;
	f1.open("buy_product.txt",ios::in);
	string shop_name;
	string pro_name;
	int buy_num=0;
	while(!f1.eof())
	{
		f1>>shop_name;
		s_p=locate_shop(All_s,shop_name);
		if(s_p)
		{
			f1>>pro_name;
			pro=locate_product(s_p,pro_name);
			if(pro)
			{
				f1>>buy_num;
				pro->sale_num+=buy_num;
				adjust_product(pro);
			}
			else
			{
				cout<<"this doesn't have such product"<<endl;
			}
		}
		else
		{
			cout<<"no such shop: "<<shop_name<<endl;
			
		}
	}
}
void delete_product(all_shop &All_s,product *pro)
{
	if(!pro->last_same_product&&!pro->next_same_product)
	{
		All_s.all_pro[All_s.product_match[pro->product_name]].next_same_product=NULL;
	}
	else
	{
		if(pro->last_same_product)
			pro->last_same_product->next_same_product=pro->next_same_product;
		if(pro->next_same_product)
			pro->next_same_product->last_same_product=pro->last_same_product;
	}
	free(pro);
}
void delete_products(all_shop &All_s)
{
	fstream f1;
	string shop_name;
	string product_name;
	shop *s_p,*s_s_p;
	product *pro,*pro_p;
	f1.open("delete_products.txt",ios::in);
	while(!f1.eof())
	{
		f1>>shop_name;
		s_p=locate_shop(All_s,shop_name);
		if(s_p)
		{
			f1>>product_name;
			pro=locate_product(s_p,product_name);
		
			if(pro)
			{
				pro_p=locate_product_p(s_p,product_name);
				pro_p->shop_next_product=pro->shop_next_product;
				delete_product(All_s,pro);
			}
			else
			{
				cout<<endl<<"There is no "<<product_name<<"at shop "<<shop_name<<endl;
			}
		}
		else
		{
			cout<<"no such shop"<<endl;
		}

	}
	f1.close();

}
void delete_shop(all_shop &All_s,shop *s_p,shop *s_p_p)
{
	All_s.shop_num--;
	product *p,*q;
	int id;
	p=s_p->first_product;
	s_p->first_product=NULL;
	s_p_p->next_shop=s_p->next_shop;
	id=s_p_p->shop_main.id+1;
	s_p_p=s_p_p->next_shop;
	while(s_p_p)
	{
		s_p_p->shop_main.id=id++;
		s_p_p=s_p_p->next_shop;
	}
	while(p)
	{
		q=p->shop_next_product;
		delete_product(All_s,p);
		p=q;
	}
	free(s_p);
	

}
void delete_shops(all_shop &All_s)
{
	fstream f1;
	string shop_name;
	shop *s_p,*s_p_p;
	f1.open("delete_shop.txt",ios::in);
	while(!f1.eof())
	{
		f1>>shop_name;
		s_p=locate_shop(All_s,shop_name);
		if(s_p)
		{
			s_p_p=locate_shop_p(All_s,shop_name);
			delete_shop(All_s,s_p,s_p_p);
		}
		else
		{
			cout<<"no such shop!"<<endl;
		}

	}
	f1.close();

}
void search_product(all_shop All_s)
{
	fstream f1;
	string product_name;
	product *p;
	int flag=1;
	f1.open("search_product.txt",ios::in);
	while(!f1.eof())
	{
		f1>>product_name;
		flag=0;
		cout<<"searching "<<product_name<<endl;
		if(All_s.product_match.count(product_name))
		{
			p=All_s.all_pro[All_s.product_match[product_name]].next_same_product;
			while(p)
			{
				cout<<p->belong_shop->name<<" "<<p->product_name<<" "<<p->price<<" "<<p->sale_num<<endl;
				p=p->next_same_product;		
			}
			flag=1;
		}
		if(flag==0)
			cout<<"sorry can't find "<<product_name<<endl;
	}
}
int main()
{
	int flag=1;
	shop root;
	all_shop All_s;
	fstream f1;
	//read shop infomation

	product all_pro[100];
	cout<<"read shop info..."<<endl;
	system("pause");
	read_shop(All_s);

	while(flag)
	{
		cout<<"what do you want to do next: "<<endl;
		cout<<"1 : add shops"<<endl;
		cout<<"2 : add products"<<endl;
		cout<<"3 : display product information"<<endl;
		cout<<"4 : display shop information"<<endl;
		cout<<"5 : buy product"<<endl;
		cout<<"6 : delete shop"<<endl;
		cout<<"7 : delete shop"<<endl;
		cout<<"8 : search product"<<endl;
		cout<<"0 : end "<<endl;
		cin>>flag;
		switch(flag)
		{
			case 1:
				cout<<"add shop info..."<<endl;	
				cout<<"Please make sure that you have put the shop info you want to add at 'new_shop.txt'"<<endl;
				system("pause");
				add_shop(All_s);
				cout<<"put added info into file..."<<endl;	
				system("pause");
				write_shop(All_s.root,"added_shop.txt");
				cout<<"You can open added_shop.txt to check if shops was added"<<endl;
				system("pause");
				break;
			case 2:
				cout<<"add product"<<endl;
				cout<<"Please make sure that you have put the product info you want to add at 'new_pro.txt'"<<endl;
				add_product(All_s);
				cout<<"put added product info into file.."<<endl;	
				system("pause");
				write_shop(All_s.root,"added_product.txt");
				cout<<"You can open added_shop.txt to check if products was added"<<endl;
				system("pause");
				break;
			case 3:
				cout<<"product info"<<endl;	
				system("pause");
				display_product(All_s);
				break;
			case 4:
				cout<<"shop info"<<endl;	
				system("pause");
				display_shops(All_s);
				break;
			case 5:
				cout<<"buy product.."<<endl;
				cout<<"Please make sure that you have put the product info you want to buy at 'buy_product.txt'"<<endl;
				system("pause");
				buy_product(All_s);
				cout<<"update file"<<endl;
				write_shop(All_s.root,"bought_product.txt");
				cout<<"You can open bought_product.txt to check if products was bought"<<endl;
				system("pause");
				break;
			case 6:
				cout<<"delete shop.."<<endl;	
				cout<<"Please make sure that you have put the shop info you want to delete at 'delete_shops.txt'"<<endl;
				system("pause");
				delete_shops(All_s);
				cout<<"update file"<<endl;
				write_shop(All_s.root,"deleted_shop.txt");
				cout<<"You can open deleted_shop.txt to check if shops was deleted"<<endl;
				system("pause");
				break;
			case 7:
				cout<<endl<<"deletd product"<<endl;	
				cout<<"Please make sure that you have put the product info you want to delete at 'delete_products.txt'"<<endl;
				system("pause");
				delete_products(All_s);
				cout<<"update file"<<endl;
				write_shop(All_s.root,"deleted_product.txt");
				cout<<"You can open deleted_product.txt to check if products was deleted"<<endl;
				system("pause");
				break;
			case 8:
				cout<<"search product .."<<endl;
				cout<<"Please make sure that you have put the product info you want to search at 'search_product.txt'"<<endl;
				system("pause");
				search_product(All_s);
				write_shop(All_s.root,"shop2.txt");
				break;
			default:
				break;
		}
	}
	return 0;
}