#include<iostream>
#include<fstream>
#include<string>
using namespace std;
struct addr
{
	int place;
	addr *next;
};

struct letter
{
	char alphabet;
	int count;
	addr *addr_count;
	letter *sibling;
	letter *next;
};
struct show
{
	int length;
	letter *p;
};
void init_letter(letter *p)
{
	p->addr_count=NULL;
	p->alphabet='A';
	p->count=0;
	p->sibling=0;
	p->next=NULL;
}
void init(letter *p)
{
	int i=0;
	for(i=0;i<26;i++)
	{
		p[i].alphabet='A'+i;
		p[i].sibling=NULL;
		p[i].addr_count=NULL;
		p[i].next=NULL;
		p[i].count=0;
		p[i+26].alphabet='a'+i;
		p[i+26].sibling=NULL;
		p[i+26].next=NULL;
		p[i+26].count=0;
		p[i+26].addr_count=NULL;
	}
}
letter* set_p(char chr,letter *p,letter *forest)
{
	if(chr>='A'&&chr<='Z')
	{
		p=&forest[((int)chr-'A')];
	}else if(chr>='a'&&chr<='z')
	{
		p=&forest[((int)chr-'a'+26)];
	}
	cout<<"first_al: "<<p->alphabet<<endl;
	return p;
}
letter* insert(char chr,letter *p)
{
	letter *cur,*origin,*q_l;
	q_l = new letter;
			q_l->addr_count=NULL;
			q_l->alphabet=chr;
			q_l->sibling=NULL;
			q_l->next=NULL;
			q_l->count=0;
			cout<<"pppp---"<<endl;
			if(p->next==NULL)
			{
				p->next=q_l;
			//	return p;
				p=q_l;
				cout<<"ppp "<<chr<<endl;
			//	display(forest);
			}else{
				origin=p;
				p=p->next;
				cur=p;
				if(p->alphabet>chr)
				{
					q_l->sibling=p;
					origin->next=q_l;
					p=q_l;
			//		return p;
				}else{
					while(p!=NULL)
					{
						if(p->alphabet<chr)
						{
							cur=p;
							p=p->sibling;
						}else{
							break;
						}
					}
					if(p==NULL)
					{
						cur->sibling=q_l;
						p=q_l;
					}else if(p->alphabet>chr)
					{
						q_l->sibling=p;
						cur->sibling=q_l;
					}										
				}
			}
	return p;

}
void set_record(char chr,letter *p,int place)
{
	addr *q;
	q = new addr;
	q->next=NULL;
	q->place=place;
	if(p->addr_count)
		q->next=p->addr_count->next;
	p->addr_count=q;
}
void display(letter *forest)
{
	int i=0;
	string a;
	letter *q_l;
//	q=NULL;
	cout<<"oooo"<<endl;
	for(i=0;i<52;i++)
	{
		cout<<forest[i].alphabet<<" ";
		a+=forest[i].alphabet;
		if(forest[i].next!=NULL)
		{
			q_l=forest[i].next;
			
				while(q_l->next!=NULL)
				{
					a+=q_l->alphabet;
					if(q_l->count>0)
					{
					//	a+=q_l->alphabet;
						cout<<a<<" "<<q_l->count<<"\t";
					}
					
				//	cout<<q_l->alphabet<<"\t";
				
					q_l=q_l->next;
				}	
				a+=q_l->alphabet;
				cout<<a<<"\t";
				cout<<q_l->count;
		}		
		cout<<" "<<endl;
		a='.';

	}
}
void man_txt()
{
	fstream f1;
	letter *p;
	addr *q;
		letter *q_l;
	letter forest[52];
	letter *origin,*cur;
	int place=0;
	char chr;
	init(forest);
	f1.open("1.txt",ios::in);
//	f2.open("en2.txt",ios::out);
	display(forest);
	while(!f1.eof())
	{
		place=f1.tellg();
		chr=f1.get();
		while(!((chr>='A'&&chr<='Z')||(chr>='a'&&chr<='z'))&&!f1.eof())
		{
			place=f1.tellg();
			chr=f1.get();
			cout<<"o"<<endl;
		}            
		if(!f1.eof()&&((chr>='A'&&chr<='Z')||(chr>='a'&&chr<='z')))
		p=set_p(chr,p,forest);
		while(!f1.eof()&&((chr>='A'&&chr<='Z')||(chr>='a'&&chr<='z')))
		{
			chr=f1.get();

			cout<<"insertint.. : "<<chr<<" "<<p->alphabet<<endl;
			if((chr>='A'&&chr<='Z')||(chr>='a'&&chr<='z'))
			{	
		//	p=insert(chr,p);
			
			q_l = new letter;
			q_l->addr_count=NULL;
			q_l->alphabet=chr;
			q_l->sibling=NULL;
			q_l->next=NULL;
			q_l->count=0;
			cout<<"pppp---"<<endl;
			if(p->next==NULL)
			{
				p->next=q_l;
			//	return p;
				p=q_l;
				cout<<"ppp "<<chr<<endl;
			//	display(forest);
			}else{
				origin=p;
				p=p->next;
				cur=p;
				if(p->alphabet>chr)
				{
					q_l->sibling=p;
					origin->next=q_l;
					p=q_l;
			//		return p;
				}else{
					while(p!=NULL)
					{
						if(p->alphabet<chr)
						{
							cur=p;
							p=p->sibling;
						}else{
							break;
						}
					}
					if(p==NULL)
					{
						cur->sibling=q_l;
						p=q_l;
					}else if(p->alphabet>chr)
					{
						q_l->sibling=p;
						cur->sibling=q_l;
					}										
				}
			}
		//  p=insert(chr,p);
		}
		}
		//set_record(chr,p,place);
		cout<<"OPOP"<<endl;
		q = new addr;
		q->next=NULL;
		q->place=place;
		p->count++;
		if(p->addr_count)
			q->next=p->addr_count->next;
		p->addr_count=q;
		cout<<"p->cout : "<<p->count<<endl;
		//set_record(chr,p,place);


	}
	//cout<<forest['a'-'a'+26].next->alphabet<<endl;
	f1.close();
//	f2.close();
	display(forest);
	cout<<"end";
}



int main()
{
	man_txt();

//	cout<<a;
//	cout<<a<<endl;
	cout<<('A'=='A')<<endl;
	return 0;
}