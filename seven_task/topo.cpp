#include<iostream>
#include<stack>
#include<math.h>
#include<queue>
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

int LocateVex_L(ALGraph G,ElemType x)
{
	int k;
	for(k=0;(k<G.vexnum)&&(G.vexs[k].vex!=x);k++);
	if(k<G.vexnum) return k;
		else return -1;
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
	cout<<G.vexnum<<" "<<G.edgenum<<endl;
//	G.edgenum=e;
	for(i=0;i<G.vexnum;i++)
	{
		f1>>G.vexs[i].vex;
		cout<<G.vexs[i].vex<<" ";
	}
	cout<<endl;
	for(k=0;k<G.edgenum;++k)
	{
		f1>>v1>>v2>>weight;
		i=LocateVex_L(G,v1);
		j=LocateVex_L(G,v2);
		cout<<"i: "<<i<<"j: "<<j<<endl;
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
void display_G(ALGraph G)
{
	EdgeNode_L *p;
	for(int i=0;i<G.vexnum;i++)
	{
		p=G.vexs[i].firstedge;
		cout<<" --"<<G.vexs[i].vex<<" "<<endl;
		while(p)
		{
			cout<<G.vexs[p->adjvex].vex<<" "<<p->weight<<" ";
			p=p->nextedge;
		}
		cout<<"indegree: "<<G.vexs[i].indegree<<endl;
		cout<<endl;
	}
}
void topologicalSort()
{
	stack<int> s;
	ALGraph G;
	int i=0;
	int m;
	EdgeNode_L *p;
	CreateDG_ALG(G,2,2);
	display_G(G);
	for(i=0;i<G.vexnum;i++)
	{
		if(!G.vexs[i].indegree) 
			s.push(i);
	}
	cout<<"pppp"<<endl;
	while(!s.empty())
	{
		m=s.top();
		s.pop();
		cout<<G.vexs[m].vex<<" ";
		p=G.vexs[m].firstedge;
		for(;p;p=p->nextedge)
		{
			G.vexs[p->adjvex].indegree--;
			if(G.vexs[p->adjvex].indegree==0)
			{
				s.push(p->adjvex);
			}

		}
	}

}
int main()
{
	topologicalSort();
	return 0;
}