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
	while(n--)
	{
		EdgeNode_L *p;
		p=G.vexs[i].firstedge;
		cout<<G.vexs[i].vex<<": "<<endl;
		while(p)
		{
			cout<<G.vexs[p->adjvex].vex<<" "<<p->weight<<endl;
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
//	cout<<G.vexnum<<" "<<G.edgenum<<endl;
//	G.edgenum=e;
	for(i=0;i<G.vexnum;i++)
	{
		f1>>G.vexs[i].vex;
//		cout<<G.vexs[i].vex<<" ";
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
	n=G.vexnum;
	int i=0;
	cur=v0;
string a;
	memset(visit,0,sizeof(visit));
	memset(mini,-1,sizeof(mini));
	visit[v0]=1;
	while(n)
	{
		EdgeNode_L *p;
		p=G.vexs[cur].firstedge;
		int t;
		int re=-1;
		while(p)
		{
			t=p->adjvex;		
			if(mini[t]==-1)
				mini[t]=p->weight;
			else if(mini[t]>(mini[cur]+p->weight))
			{
				mini[t]=mini[cur]+p->weight;
				a='0'+mini[cur];
				road[t]=road[cur]+a;
			}
			p=p->nextedge;
		}
		cur=get_mini(G,v0);
		visit[cur]=1;
		n--;
	}
//	cout<<mini[12]<<endl;
	n=G.vexnum;
while(n--)
{
	cout<<road[n]<<endl;
}



	return 0;
}
