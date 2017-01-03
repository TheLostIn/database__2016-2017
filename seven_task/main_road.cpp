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
#define Infinity MAX
#define Vertex_Max 20
typedef int VRType;
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
int visit[100];
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
	while(n--)
	{
		EdgeNode_L *p;
		p=G.vexs[i].firstedge;
		cout<<G.vexs[i].vex<<": "<<endl;
		while(p)
		{
			cout<<G.vexs[p->adjvex].vex<<" weight: "<<p->weight<<endl;
			p=p->nextedge;
		}
		i++;
	}


}
void CreateDG_ALG(ALGraph &G,int n,int e)
{
	fstream f1;
	f1.open("main_road.txt",ios::in);
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
	//	cout<<"i: "<<i<<"j: "<<j<<endl;
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
	int mini=9999;
	EdgeNode_L *p;
	p=G.vexs[n].firstedge;
	int t;
	int re=-1;
	while(p)
	{
		t=p->adjvex;
		
		if(visit[t]==0)
		{
			if(p->weight<mini)
			{
				mini=p->weight;
				re=p->adjvex;
			}
		}
		p=p->nextedge;
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
	int final;
	CreateDG_ALG(G,1,1);
	display_tree(G);
	n=G.vexnum;
	 int i=0;
	 cout<<"indegree: "<<endl;
	while(n--)
	{
		cout<<i<<" "<<G.vexs[i].indegree<<endl;
		i++;
	}

	int state[100];
	memset(state,0,sizeof(state));
	string road[100];
	queue<int> q;
	n=G.vexnum;
	i=0;
	while(n--)
	{
		if(G.vexs[i].indegree==0)
		{
			q.push(i);
		}
		road[i]=i+'0';
		i++;
	}

	while(!q.empty())
	{	cur=q.front();
		q.pop();
		EdgeNode_L *p;
		p=G.vexs[cur].firstedge;
		int t;
		int re=-1;
		string a;
		while(p)
		{
			if((state[cur]+p->weight)>state[p->adjvex])
			{
				a='0'+p->adjvex;
				state[p->adjvex]=state[cur]+p->weight;
				final=p->adjvex;
				road[p->adjvex]=road[cur]+a;
			}
			G.vexs[p->adjvex].indegree--;
			if(G.vexs[p->adjvex].indegree==0)
			{
				q.push(p->adjvex);
			}
			p=p->nextedge;
		}
	}

	n=G.vexnum;
	i=0;
	cout<<"main road: "<<road[n-1]<<"¡¡weight: "<<state[final]<<endl;


	return 0;
}