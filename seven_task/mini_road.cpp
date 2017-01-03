/*
9 11
0 1 2 3 4 5 6 7 8
0 1 6
0 2 4
0 3 5
1 4 1
2 4 1
3 5 2
4 6 9
4 7 7
5 7 4
7 8 4
6 8 2

*/
//graph_w.txt


#include<iostream>
#include<stack>
#include<math.h>
#include<queue>
#include<string.h>
#include<string>
#include<algorithm>
#include<fstream>
using namespace std;
#define MAX 99999
#define Infinity MAX
#define Vertex_Max 20
int visit[100];
typedef int VRType;

	int mini[100];
	string road[100];
typedef int ElemType;
typedef enum{DG,UDG,UDN}GraphKind;
typedef struct EdgeNode_L
{
	int adjvex;
	EdgeNode_L * nextedge;
	int weight;
}EdgeNode_L;
typedef struct VexNode_L
{
	ElemType vex;
	int indegree;
	EdgeNode_L *firstedge;
	VexNode_L(){firstedge=NULL;indegree=0;}
}VexNode_L;
typedef struct 
{
	VexNode_L vexs[Vertex_Max];
	int vexnum,edgenum;
	int kind;
} ALGraph;

int LocateVex_L(ALGraph G,ElemType x)
{
	int k;
	for(k=0;(k<G.vexnum)&&(G.vexs[k].vex!=x);k++);
	if(k<G.vexnum) return k;
		else return -1;
}
void display_tree(ALGraph G)
{
	int n=G.vexnum;
	int i=0;
	cout<<"\tfirst_vex\t"<<"next_vex\t"<<"weight"<<endl;
	while(n--)
	{
		EdgeNode_L *p;
		p=G.vexs[i].firstedge;
		while(p)
		{
			cout<<"\t"<<G.vexs[i].vex<<"\t\t"<<G.vexs[p->adjvex].vex<<"\t\t"<<p->weight<<endl;
			p=p->nextedge;
		}
		i++;
	}
}
void CreateDG_ALG(ALGraph &G,int n,int e)
{
	fstream f1;
	f1.open("graph_w.txt",ios::in);
	int i,j;
	ElemType v1,v2;
	int weight;
	EdgeNode_L *p;
	int k;
	f1>>G.vexnum;
	f1>>G.edgenum;
	for(i=0;i<G.vexnum;i++)
	{
		f1>>G.vexs[i].vex;
	}
	for(k=0;k<G.edgenum;++k)
	{
		f1>>v1>>v2>>weight;
		i=LocateVex_L(G,v1);
		j=LocateVex_L(G,v2);
		while((i<0)||(i>(G.vexnum-1))||(j<0)||(j>(G.vexnum-1)))
		{
			cout<<"The edge doesn't exist,please input again"<<endl;
			system("pause");
			f1>>v1>>v2;
			i=LocateVex_L(G,v1);
			j=LocateVex_L(G,v2);
		}
		p = new EdgeNode_L;
		p->adjvex=j;
		p->weight=weight;
		p->nextedge=G.vexs[i].firstedge;
		G.vexs[i].firstedge=p;
		G.vexs[j].indegree++;
		
	}
	f1.close();
}

int get_mini(ALGraph G,int n)
{
	int i=0;
	int min=MAX;
	int re=-1;
	while(i<G.vexnum)
	{
		if((mini[i]!=-1)&&visit[i]==0)
			if(mini[i]<min)
			{
				min=mini[i];
				re=i;
			}
		i++;
	}
	return re;

}

int main()
{
	ALGraph G;
	int n;
	int e;
	int min;
	int cur;
	int v0=2;
	CreateDG_ALG(G,1,1);
	cout<<endl<<"This is how the tree like:"<<endl<<endl;
	display_tree(G);
	n=G.vexnum;
	int i=0;
	cur=v0;
	string a;
	memset(visit,0,sizeof(visit));
	memset(mini,-1,sizeof(mini));
	visit[v0]=1;
	mini[cur]=0;
	while(i<n)
	{
		road[i]=G.vexs[i].vex+'0';
		i++;
	}
	while(n)
	{
		EdgeNode_L *p;
		p=G.vexs[cur].firstedge;
		int t;
		while(p)
		{
			t=p->adjvex;		
			if(mini[t]==-1)
			{
				a='0'+t;
				mini[t]=mini[cur]+p->weight;
				road[t]=road[cur]+a;
			}
			else if(mini[t]>(mini[cur]+p->weight))
			{
				mini[t]=mini[cur]+p->weight;
				a='0'+road[cur];
				cout<<road[cur]+a<<endl;
				road[t]=road[cur]+a;
			}
			p=p->nextedge;
		}
		cur=get_mini(G,v0);
		if(cur==-1) break;
		visit[cur]=1;
		n--;
	
	}
	n=G.vexnum;
	i=0;
	cout<<endl<<"This is how the road like:"<<endl<<endl;
	cout<<"Start from "<<v0<<endl;
	cout<<"\tvex\tweight\troad"<<endl;
	while(i<n)
	{
		cout<<"\t"<<i<<"\t"<<mini[i]<<"\t"<<road[i++]<<endl;
	}
	return 0;
}
