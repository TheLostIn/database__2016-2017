#include<iostream>
#include<queue>
#include<stack>
#include<fstream>
using namespace std;
typedef struct country
{
	int weight;
	int next_country;
	country *next_sibling;
	country(){weight=0;next_country=0;next_sibling=NULL;}
}country;
struct Save_node{
	int from;
	int to;
	int weight;
	Save_node(){from=0;to=0;weight=0;}
	Save_node(int a,int b,int c){from=a;to=b;weight=c;}
};
typedef struct all_country
{
	country all_c[100];
	int country_num;
	int L_num;

}all_country;
int visit[100];
void read_table(all_country &C)
{
	fstream f1;
	f1.open("best_watering.txt",ios::in);
	f1>>C.country_num>>C.L_num;
	country *p;
	int from,to,weight;
	for(int i=0;i<C.L_num;i++)
	{
		f1>>from>>to>>weight;
		cout<<from<<" "<<to<<" "<<weight<<endl;
		p=new country;
		p->next_country=to;
		p->weight=weight;
		p->next_sibling=C.all_c[from].next_sibling;
		C.all_c[from].next_sibling=p;
	
		p=new country;
		p->next_country=from;
		p->weight=weight;
		p->next_sibling=C.all_c[to].next_sibling;
		C.all_c[to].next_sibling=p;
	}
	f1.close();
}
void get_mini(all_country C,int node,int &min_node,int &min_weight)
{
	country *p;
	min_node=-1;
	min_weight=-1;
	p=C.all_c[node].next_sibling;
	while(p)
	{
	//	cout<<endl<<visit[p->next_country]<<endl;
		if(visit[p->next_country]==0)
		{
			if(min_weight==-1||(p->weight<min_weight))
			{
				min_weight=p->weight;
				min_node=p->next_country;
			}
	//		cout<<endl<<"node: "<<node<<" min_node: "<<min_node<<" "<<min_weight<<endl;
		}
		p=p->next_sibling;
	}
}
void mini_road(all_country C)
{
	memset(visit,0,sizeof(visit));
	int v=1;
	int n=C.country_num;
	queue<Save_node> q;
	stack<int> p;
	int min_node;
	int min_weight;
	p.push(v);
	visit[v]=1;
	n--;
	while(n)
	{
		get_mini(C,v,min_node,min_weight);

	//	cout<<min_node<<" "<<min_weight<<endl;
	//	system("pause");
		if(min_node==-1)
		{
			v=p.top();
			p.pop();
		}
		else
		{
			q.push(Save_node(v,min_node,min_weight));
			visit[min_node]=1;
			p.push(min_node);
			v=min_node;
			n--;
		}
	}
	Save_node l;
	int sum=0;
	cout<<"The mini road: "<<endl;
	while(!q.empty())
	{
		l=q.front();
		q.pop();
		sum+=l.weight;
		cout<<l.from<<" "<<l.to<<" "<<l.weight<<endl;
	}
	cout<<"The mini cost :"<<sum<<endl;
}
void display_table(all_country C)
{
	int i=1;
	while(i<=C.country_num)
	{
		country *p;
		p=C.all_c[i].next_sibling;
		while(p)
		{
			cout<<i<<" "<<p->next_country<<" "<<p->weight<<endl;
			p=p->next_sibling;
		}
		i++;
	}

}
int main()
{

	all_country C;
	read_table(C);
	cout<<endl;
	display_table(C);
	cout<<endl;
	mini_road(C);
	return 0;
}