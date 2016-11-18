#include<iostream>
#include<fstream>
#include<string>
using namespace std;
typedef struct stack * link;
#define maxn 100
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
struct play_stack
{
	letter *p;
	char al;
};
play_stack p_s[maxn];
struct stack
{
	string cur_str;
	letter *p;
	link next;
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
	
			if(p->next==NULL)
			{
				p->next=q_l;
				p=q_l;
		
			}else{
				origin=p;
				p=p->next;
				cur=p;
		
			
				if(p->alphabet>chr)
				{
					q_l->sibling=p;
					origin->next=q_l;
					p=q_l;
		
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
						p=q_l;
	
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
		p->count++;
		if(p->addr_count)
			q->next=p->addr_count->next;
		p->addr_count=q;
}
link push(link Head,string a,letter *l)
{
	link p;
	p= new stack;
	if(p==NULL)
	{
		cout<<"\nMemory Error\n";
		return Head;
	}
	p->p=l;
	p->next=Head;
	p->cur_str=a;
	return p;
}
link pop(link Head)
{
	link p;
	p=Head;
	if(p==NULL)
	{
		cout<<"\nStack is Empty\n";
	}
	else{
		p=p->next;

	}
	return p;
}
void travel(letter *forest)
{
	int i=0;
	string a;
	link Head;
	letter *q_l;
	cout<<"oooo"<<endl;
	Head=NULL;
	for(i=0;i<52;i++)
	{
		cout<<forest[i].alphabet<<endl;
	//	a+=forest[i].alphabet;
		if(forest[i].next!=NULL)
		{
			q_l=&forest[i];
		
				while(q_l!=NULL)
				{
					if(q_l->sibling!=NULL)
					{
						letter *qp;
						qp=q_l->sibling;
						Head=push(Head,a,q_l->sibling);
						while(qp)
						{
							qp=qp->sibling;
						}
						

					}
					a+=q_l->alphabet;
					if(q_l->count>0)
					{
						addr *p_arr;
						p_arr=q_l->addr_count;
						cout<<a<<"\t place: \t";
						while(p_arr)
						{
						//	cout<<"true "<<p_arr->place;
							p_arr=p_arr->next;
						}
						cout<<"\tcount: \t"<<q_l->count<<endl;
					}	
					if(q_l->next)
					{
						q_l=q_l->next;
					}else{
						break;
					}
				
				}	
				while(Head)   
				{
					if(Head->p)
					{
					}
					q_l=Head->p;
					a=Head->cur_str;
					Head=Head->next;
					while(q_l!=NULL)
					{
						if(q_l->sibling!=NULL)
						{
							Head=push(Head,a,q_l->sibling);
//							cout<<"Head"<<Head->p->alphabet<<endl;
						}
						a+=q_l->alphabet;
						if(q_l->count>0)
						{
							cout<<a<<" ";
								addr *p_arr;
								p_arr=q_l->addr_count;
								while(p_arr)
								{
									cout<<" "<<p_arr->place<<" ";
									p_arr=p_arr->next;
								}
								cout<<q_l->count<<"\t";
						}
						q_l=q_l->next;
						
					}	
	
				}
		}		
		cout<<" "<<endl;
		a='.';
	}
}
void push_d_s(letter *p,int & top)
{
	top++;
		p_s[top].al=p->alphabet;
		p_s[top].p=p;
}
void read_ps(int top)
{
	cout<<"\t";
	for(int i=1;i<=top;i++)
	{
		cout<<p_s[i].p->alphabet;
	}
	addr *p;
	p=p_s[top].p->addr_count;
	if(p)
		cout<<"\tplace: ";
	while(p)
	{
		cout<<" "<<p->place<<" ";
		p=p->next;
	}
	cout<<" count: "<<p_s[top].p->count<<endl;
}
letter* pop_d_s(int &top)
{
	int tmp;
	tmp=top;
	top--;

	return p_s[tmp].p;

}
void display_stack(letter *forest)
{
	int top=0;
	int cur=0;
	letter *q_l;
	for(int i=0;i<52;i++)
	{
		top=0;
		cout<<forest[i].alphabet<<" "<<endl;		
		push_d_s(&forest[i],top);
		q_l=&forest[i];
		if(q_l->count>0)
		{
			read_ps(top);
		}
			
		if(forest[i].next)
		{
			q_l=forest[i].next;
			while(top!=0)
			{
		
				while(q_l!=NULL)
				{		
					push_d_s(q_l,top);			
					if(q_l->count>0)
					{
						read_ps(top);
					}
					q_l=q_l->next;
				}
				q_l=pop_d_s(top);
				while(q_l->sibling==NULL&&top!=0) 
				{
				
					q_l=pop_d_s(top);
				}
				if(q_l->sibling!=NULL)
				{
					q_l=q_l->sibling;
				}
				
			}

		}
		
	}

}
void display(letter *forest)
{
	int i=0;
	string a;
	letter *q_l;
//	cout<<"oooo"<<endl;
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
						cout<<a<<" "<<q_l->count<<"\t";
					}								
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
	place=f1.tellg();
		chr=f1.get();
	while(!f1.eof())
	{
		
		while(!((chr>='A'&&chr<='Z')||(chr>='a'&&chr<='z'))&&!f1.eof())
		{
			place=f1.tellg();
			chr=f1.get();
		}            
		if(!f1.eof()&&((chr>='A'&&chr<='Z')||(chr>='a'&&chr<='z')))
		p=set_p(chr,p,forest);
		while(!f1.eof()&&((chr>='A'&&chr<='Z')||(chr>='a'&&chr<='z')))
		{
			chr=f1.get();
			if(f1.eof()) break;
			if((chr>='A'&&chr<='Z')||(chr>='a'&&chr<='z'))
			{	
				p=insert(chr,p);
			}
		}

			q = new addr;
		q->next=NULL;
		q->place=place;
		p->count++;
		addr *m;
		m=p->addr_count;
		if(p->addr_count!=NULL)
			m=m->next;
	
		if(p->addr_count)
		{
			q->next=p->addr_count;
			p->addr_count=q;
//			cout<<"1: "<<1<<endl;
		}		
		else
		{
			p->addr_count=q;
//			cout<<"0: "<<0<<endl;
		}
		
//		cout<<place<<endl;
		place=f1.tellg();
		chr=f1.get();
	}
	f1.close();
	travel(forest);//stringÊä³ö
	display_stack(forest);//Õ»Êä³ö
	cout<<"end";

}



int main()
{
	man_txt();
	return 0;
}