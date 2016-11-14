#include<iostream>
#include<fstream>
#include<string>
using namespace std;
typedef struct stack * link;
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
//	cout<<"first_al: "<<p->alphabet<<endl;
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
				p=q_l;
				cout<<"ppp "<<chr<<endl;
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
//	cout<<"push: "<<l->alphabet<<endl;
	p->next=Head;
	p->cur_str=a;
	return p;
}
link pop(link Head)
{
	link p;
	p=Head;
//	cout<<"1"<<endl;
//	cout<<"cur_str: "<<(p->cur_str)<<endl;
	if(p==NULL)
	{
		cout<<"\nStack is Empty\n";
	}
	else{
//		cout<<"2"<<endl;
		p=p->next;
//		cout<<"3"<<endl;
	//	delete(Head);
	}
//	cout<<"pop: "<<p->p->alphabet<<endl;
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
		cout<<forest[i].alphabet<<" ";
		a+=forest[i].alphabet;
		if(forest[i].next!=NULL)
		{
			q_l=forest[i].next;
		
				while(q_l!=NULL)
				{
				//	cout<<"00000000000000"<<endl;
					if(q_l->sibling!=NULL)
					{
				//		cout<<"00000000000000"<<endl;
						letter *qp;
						qp=q_l->sibling;
					//	cout<<"before: "<<a<<endl;
						Head=push(Head,a,q_l->sibling);
			//			cout<<"push after : "<<Head->p->alphabet<<endl;
						while(qp)
						{
				//			cout<<endl<<"sib: "<<qp->alphabet<<endl;
							qp=qp->sibling;
						}
						

					}
					a+=q_l->alphabet;
					if(q_l->count>0)
					{
						cout<<a<<" -+"<<q_l->count<<"\t";
					}	
					if(q_l->next)
					{
						q_l=q_l->next;
					}else{
						break;
					}
				
				}	
			//	a+=q_l->alphabet;
			//	cout<<a<<"0\t";
			//	cout<<q_l->count;
				while(Head)   
				{
				//	cout<<"OPOPOPOPOP_d__"<<endl;
				//	cout<<"cur_str: "<<(Head->cur_str)<<endl;
				//	Head=Head->next;
					
				//	cout<<"llllll"<<endl;
					if(Head->p)
					{
				//		cout<<"ok"<<endl;
					}
					q_l=Head->p;
					a=Head->cur_str;
					Head=Head->next;
				//	cout<<"pppp"<<endl;
					while(q_l!=NULL)
					{
						if(q_l->sibling!=NULL)
						{
							Head=push(Head,a,q_l->sibling);
							cout<<"Head"<<Head->p->alphabet<<endl;
						}
						a+=q_l->alphabet;
						if(q_l->count>0)
						{
							cout<<a<<" "<<q_l->count<<"\t";
						}
				//	int mm;	
					//		cin>>mm;
					//---++++++++++++++++++++++++++++++++++=改到这里
						q_l=q_l->next;
						
					}	
				/*	a+=q_l->alphabet;
					cout<<a<<"\t";
					cout<<q_l->count;
					*/
				
				
				/*	if(Head)
					{
					//	cout<<"0p0p0p0p"<<endl;
						q_l=Head->p;
						//	a='.';
					
						a=Head->cur_str;
					}
						Head=Head->next;

					*/
				}
		}		
		cout<<" "<<endl;
		a='.';
	}
}
void display(letter *forest)
{
	int i=0;
	string a;
	letter *q_l;
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
//	display(forest);
	place=f1.tellg();
		chr=f1.get();
	while(!f1.eof())
	{
		
		while(!((chr>='A'&&chr<='Z')||(chr>='a'&&chr<='z'))&&!f1.eof())
		{
			place=f1.tellg();
			chr=f1.get();
		//	cout<<"o"<<endl;
		}            
		if(!f1.eof()&&((chr>='A'&&chr<='Z')||(chr>='a'&&chr<='z')))
		p=set_p(chr,p,forest);
		while(!f1.eof()&&((chr>='A'&&chr<='Z')||(chr>='a'&&chr<='z')))
		{
			chr=f1.get();
			if(f1.eof()) break;

		//	cout<<"insertint.. : "<<chr<<" "<<p->alphabet<<endl;
			if((chr>='A'&&chr<='Z')||(chr>='a'&&chr<='z'))
			{	
			q_l = new letter;
			q_l->addr_count=NULL;
			q_l->alphabet=chr;
			q_l->sibling=NULL;
			q_l->next=NULL;
			q_l->count=0;
		//	cout<<"pppp---"<<endl;
			if(p->next==NULL)
			{
				p->next=q_l;
				p=q_l;
			//	cout<<"ppp "<<chr<<endl;
			}else{
				origin=p;
				p=p->next;
				cur=p;
			//	cout<<"--------------"<<endl;
				//cout<<"q_l : "<<q_l->alphabet<<"p->al: "<<p->alphabet<<endl;
				if(p->alphabet>chr)
				{
					q_l->sibling=p;
					origin->next=q_l;
					p=q_l;
			//		return p;
				}else{
				//		cout<<"q_l : "<<q_l->alphabet<<"p->al: "<<p->alphabet<<endl;		
					while(p!=NULL)
					{
						if(p->alphabet<chr)
						{
						//	cout<<"test: "<<p->alphabet<<" ";
							cur=p;
							p=p->sibling;
						}else{
							break;
						}
					}

					if(p==NULL)
					{
				//		cout<<"q_l : "<<q_l->alphabet<<"p->al: "<<p->alphabet<<endl;
						cur->sibling=q_l;
						p=q_l;
					//	cout<<"q_l : "<<q_l->alphabet<<"p->al: "<<p->alphabet<<endl;
					}else if(p->alphabet>chr)
					{
					//	cout<<"xiao   q_l : "<<q_l->alphabet<<"p->al: "<<p->alphabet<<endl;
						q_l->sibling=p;
						cur->sibling=q_l;
						p=q_l;
		//				cout<<"sibling: "<<p->alphabet<<endl;
					}										
				}
			}
		//  p=insert(chr,p);
		}
		}
		//set_record(chr,p,place);
	//	cout<<"OPOP"<<endl;
		q = new addr;
		q->next=NULL;
		q->place=place;
		p->count++;
		if(p->addr_count)
			q->next=p->addr_count->next;
		p->addr_count=q;
	//	cout<<"p->cout : "<<p->count<<endl;
		//set_record(chr,p,place);

	place=f1.tellg();
		chr=f1.get();
	}
	f1.close();
//	display(forest);
	travel(forest);
	cout<<"end";


//------------------------------------------------




//----------------------------------------

}



int main()
{
	man_txt();
	string a;
	a="abc";
	cout<<a.length()<<endl;
	a="bkkkkk";
	a[2]='\0';
	cout<<a.length()<<endl;
	cout<<('A'=='A')<<endl;
	return 0;
}