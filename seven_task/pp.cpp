/*
6 9
0 1 2 3 4 5
1 4
0 1
0 2
0 5
2 5
2 3
3 5
3 4
4 5
*/
//graph.txt
#include<iostream>
#include<stack>
#include<queue>
#include<algorithm>
#include<fstream>
using namespace std;
#define Infinity MAX
#define Vertex_Max 20
typedef int VRType;
typedef int ElemType;
typedef enum{DG,UDG,UDN}GraphKind;
typedef struct {
    ElemType vexs[Vertex_Max];
    VRType edges[Vertex_Max][Vertex_Max];
    int vexnum,edgenum;
    GraphKind kind;
}MGraph;
typedef struct EdgeNode_L
{
    int adjvex;
    EdgeNode_L * nextedge;
    int weight;
}EdgeNode_L;
typedef struct VexNode_L
{
    ElemType vex;
    EdgeNode_L *firstedge;
    VexNode_L(){firstedge=NULL;}
}VexNode_L;
typedef struct
{
    VexNode_L vexs[Vertex_Max];
    int vexnum,edgenum;
    int kind;
}ALGraph;
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
    f1.open("graph.txt",ios::in);
    int i,j;
    ElemType v1,v2;
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
        f1>>v1>>v2;
        i=LocateVex_L(G,v1);
        j=LocateVex_L(G,v2);
    //    cout<<"i: "<<i<<"j: "<<j<<endl;
        while((i<0)||(i>(G.vexnum-1))||(j<0)||(j>(G.vexnum-1)))
        {
            cout<<"The edge doesn't exist,please input again"<<endl;
            f1>>v1>>v2;
            i=LocateVex_L(G,v1);
            j=LocateVex_L(G,v2);
        }
        p = new EdgeNode_L;
        p->adjvex=j;
        p->nextedge=G.vexs[i].firstedge;
        G.vexs[i].firstedge=p;
    }
    f1.close();
}
int LocateVex(MGraph G,ElemType x)
{
    int k;
    for(k=0;(k<G.vexnum)&&(G.vexs[k]!=x);k++);
    if(k<G.vexnum) return k;
        else return -1;
}
void CreateUDG_MG(MGraph &G,int n,int e)
{
    fstream f1;
    f1.open("graph.txt",ios::in);
    int i,j;
    ElemType v1,v2;
    int k;
    f1>>G.vexnum;
    f1>>G.edgenum;
    cout<<G.vexnum<<" "<<G.edgenum<<endl;
//	G.edgenum=e;
    for(i=0;i<G.vexnum;i++)
    {
        f1>>G.vexs[i];
        cout<<G.vexs[i]<<" ";
    }
    cout<<endl;
    for(i=0;i<G.vexnum;i++)
        for(j=0;j<G.vexnum;j++) 
            G.edges[i][j]=0;
    for(i=0;i<G.vexnum;i++)
    {
    //	f1>>G.vexs[i];
        cout<<G.vexs[i]<<" ";
    }
    cout<<endl;
    for(k=0;k<G.edgenum;++k)
    {
        f1>>v1>>v2;
        i=LocateVex(G,v1);
        j=LocateVex(G,v2);
  //      cout<<"i: "<<i<<"j: "<<j<<endl;
        while((i<0)||(i>(G.vexnum-1))||(j<0)||(j>(G.vexnum-1)))
        {
            cout<<"The edge doesn't exist,please input again"<<endl;
            f1>>v1>>v2;
            i=LocateVex(G,v1);
            j=LocateVex(G,v2);
        }
        G.edges[i][j]=G.edges[j][i]=1;
    }
    f1.close();
}
void display_G(MGraph G)
{
    for(int i=0;i<G.vexnum;i++)
    {
        for(int j=0;j<G.vexnum;j++)
            cout<<G.edges[i][j]<<" ";
        cout<<endl;
    }
}	
int visited[Vertex_Max];
void BFSTraverse(MGraph G)
{
    int v;
    for(v=0;v<G.vexnum;v++) visited[v]=0;
    queue<int> q;
    for(v=0;v<G.vexnum;v++)
    {
        if(!visited[v])
        {
            cout<<G.vexs[v]<<" ";
            visited[v]=1;
            q.push(v);
            while(!q.empty())
            {
                int u;
                u=q.front();
                //cout<<"get front:"<<u<<endl;
                for(int w=0;w<G.vexnum;w++)
                {
                
                    if(G.edges[u][w]!=0&&(!visited[w]))
                    {
                        visited[w]=1;
                        cout<<G.vexs[w]<<" ";
                        q.push(w);
                    }
                }
                q.pop();
            }
        }
    }
}
void DFS_ALG(ALGraph G,int v)
{
    EdgeNode_L *p;
    cout<<G.vexs[v].vex<<" ";
    visited[v]=1;
    int j;
    for(p=G.vexs[v].firstedge;p;p=p->nextedge)
    {
        j=p->adjvex;
        if(!visited[j]) DFS_ALG(G,j);
    }
    
}
void DFSTraverse_L(ALGraph G)
{
    int visited[Vertex_Max];
    int v;
    for(v=0;v<G.vexnum;v++)
    {
        visited[v]=0;
    }
    for(v=0;v<G.vexnum;v++)
    {
        if(!visited[v])
            DFS_ALG(G,v);
    }
}
void DFSTraverse(MGraph G)
{
    int visited[Vertex_Max];
    int v,w;
    for(v=0;v<G.vexnum;v++) visited[v]=0;
    stack<int> q;
    for(v=0;v<G.vexnum;v++)
    {
        if(!visited[v])
        {
            cout<<G.vexs[v]<<" ";
            visited[v]=1;
            q.push(v);
            int u;
            u=v;
            while(!q.empty())
            {
                //cout<<"get front:"<<u<<endl;
                for(w=0;w<G.vexnum;w++)
                {				
                    if(G.edges[u][w]!=0&&(!visited[w]))
                    {
                        visited[w]=1;
                        cout<<G.vexs[w]<<" ";
                        q.push(w);
                        u=w;
                        break;
                    }
                }
                if(w==G.vexnum)
                {
                    u=q.top();
                    q.pop();
                }
            }
        }
    }
}
int main()
{
    MGraph G;
    ALGraph A_G;
    CreateUDG_MG(G,10,10);
    display_G(G);
    cout<<endl;
	cout<<"BFS : "<<endl;
    BFSTraverse(G);
    cout<<endl;
	cout<<"DFS :¡¡"<<endl;
    DFSTraverse(G);
    cout<<endl<<endl;
    CreateDG_ALG(A_G,1,1);
	cout<<"DFS :"<<endl;
    DFSTraverse_L(A_G);
    return 0;
}