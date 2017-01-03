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
#include<map>
#include<iterator>
#include<math.h>
#include<queue>
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
	cout<<n<<endl;
	cout<<"display"<<endl;
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
//	cout<<e<<endl;
	for(i=0;i<G.vexnum;i++)
	{
		f1>>G.vexs[i].vex;
		cout<<G.vexs[i].vex<<" ";
	}
	for(k=0;k<G.edgenum;++k)
	{
		f1>>v1>>v2>>weight;
		i=LocateVex_L(G,v1);
		j=LocateVex_L(G,v2);
//		cout<<"i: "<<i<<"j: "<<j<<endl;
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
	
		p = new EdgeNode_L;
		p->adjvex=i;
		p->weight=weight;
		p->nextedge=G.vexs[j].firstedge;
		G.vexs[j].firstedge=p;
		G.vexs[i].indegree++;
	//	cout<<G.vexs[i].vex<<endl;
	}
	f1.close();
//	cout<<"end create"<<endl;
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
	int min;
	int i=3;
	int cur;
	int v0=2;
	map<int,int> road;


	memset(visit,0,sizeof(visit));
	CreateDG_ALG(G,1,1);
	display_tree(G);
	n = G.vexnum;
	stack<int> s;
	//start from v0
	v0=LocateVex_L(G,v0);
	visit[v0]=1;
	s.push(v0);
	n--;
	while(n)
	{
		cur=s.top();

		min=get_mini(G,cur);
		if(min!=-1)
		{
			road[cur]=min;
			cout<<G.vexs[min].vex<<" ";
			visit[min]=1;
			s.push(min);
			n--;
		}
	}
	cout<<endl<<"Ê÷£º"<<endl;
	 for (map<int,int>::iterator it=road.begin(); it!=road.end(); it++)  
    {  
       cout<<G.vexs[it->first].vex<<" -> "<<G.vexs[it->second].vex<<" "<<endl;  
    }  
	cout<<endl;
	return 0;
}