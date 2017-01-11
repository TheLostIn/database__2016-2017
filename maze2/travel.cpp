/*
8、景点游历问题 (选做)（图）
[问题描述]
以学校和南京景点为例，设计并实现学校和景点之间，景点与景点之间的游历。
[基本要求]
（1）景点个数不少于15个，景点之间的路径不少于30条。
（2）给出任意两个景点之间的最短路径。
（3）给出学校到任意景点之间的最短路径。
*/ 
#include<iostream>
//#include<climits> 
#define M_VEX_NUM 30 
#define filename "info.txt"
#define IN_MAX 9999999
using namespace std;
#include<string>

#include<fstream>
#define mmm 15

string toursite[M_VEX_NUM];

typedef struct Graph
{
	int vexnum;
	int arcnum;
	int arcs[M_VEX_NUM][M_VEX_NUM];	
	Graph()
	{
		vexnum=0;
		arcnum=0;
	}
}Graph;
Graph web; 

void Init(Graph& G)
{
	int i,j;
	for(i=0;i<M_VEX_NUM;i++)
	{
		for(j=0;j<M_VEX_NUM;j++)
		{
			G.arcs[i][j] = IN_MAX;	
		} 
		toursite[i] = " ";
	}
}

void ReadFile()
{
	int i,a,b,weight;
	fstream f1;
	f1.open(filename,ios::in);
	cout<<web.vexnum<<web.arcnum<<endl;

	f1>>web.vexnum>>web.arcnum;
	
	cout<<web.vexnum<<web.arcnum<<endl;
	for(i=0;i<web.arcnum;i++)
	{
		f1>>a>>b>>weight;
		web.arcs[a-1][b-1] = weight; 
		web.arcs[b-1][a-1] = weight;
		cout<<a<<" "<<b<<" "<<weight<<endl; 
	}	
	for(i=0;i<web.vexnum;i++)
	{
		f1>>a>>toursite[i];
		cout<<a<<" "<<toursite[i]<<endl;
	}
	
} 

void print_info()
{
	int i;
	cout<<"景点依次为：\n\n" ;
	for(i=0;i<web.vexnum;i++)
	{
		cout<<i+1<<":"<<toursite[i]<<endl<<endl;		
	}	
} 

void Dijk()
{
	int i,j,k,v,min;
	int final[16];		//标志中间路径还是永久路径 
	int min_path[16+5];	//记录到每个顶点的最短距离 
	int P[16+3][16+3]; //记录每条路径具体通过哪些点 
		
	for(i=0; i<web.vexnum; i++)//顶点0为源点，无需计算 
	{
		final[i] = 0;			//初始化源点到每个顶点的路径标记	
		min_path[i] = web.arcs[0][i];
	//	cout<<min_path[i]<<endl;
		for(j=0; j<web.arcnum; j++)
		{
			P[i][j] = -1;		//设置空路径 
		}
		if(min_path[i]<IN_MAX)
		{
			P[i][0] = 0; P[i][1] = i;
		} 
	}
	
	
	min_path[0] = 0; final[0] = 1;P[0][0] = 0;	 
	for(int w=0;w<web.vexnum;w++)
	{
		for(j=0;j<web.vexnum;j++){
		//if (P[w][j]>=0)	
		cout<<P[w][j]<<"  ";
		//	else cout<<"#  ";		
		}
		cout<<"\n";
	}
	for(j=0;j<web.vexnum;j++)
		cout<<j<<" min_path "<<" "<<min_path[j]<<endl;
	for(i=0; i<web.vexnum; i++)
	{
		min = IN_MAX; 
		for(j=1; j<web.vexnum; j++)		//找到每一轮可达路径中最短的一条 
		{
			
//	cout<<"min_path min 2 "<<j<<" "<<min_path[j]<<"　"<<min<<endl; 
			if(!final[j])
			{
				if(min_path[j] < min)
				{
					min = min_path[j];			
					v = j;
				}				
			}	
		}
		final[v] = 1;
		cout<<"\n本轮最短: "<<v<<" "<<min<<endl;
		
		for(j=0;P[v][j]!=v;j++)cout<<P[v][j]<<" "; 
	
		cout<<"\n从 "<<toursite[0]<<" 到 "<<toursite[v]<<" "<<v<<" "<<"的最短路径为：\n";
		for(j=0;P[v][j]!=v;j++)
		{
			if(P[v][j]!=-1)
			cout<<"-p: "<<toursite[P[v][j]]<<"--";			
		}
		cout<<toursite[v]<<"\n";	

		for(j=1; j<web.vexnum; ++j)
		{
		//	cout<<"v: "<<v<<" j: "<<j<<" "<<web.arcs[v][j]<<" "<<min_path[j]<<" final[j]: "<<final[j]<<" "<<min
		//		<<endl;
			if((!final[j] )&& ((min + web.arcs[v][j] )< min_path[j]))
			{
					cout<<"v: "<<v<<" j: "<<j<<" "<<web.arcs[v][j]<<" "<<min_path[j]<<" final[j]: "<<final[j]<<" "<<min
				<<endl;
				cout<<"in"<<endl;
				min_path[j] = min + web.arcs[v][j];
				for(k=0; P[v][k]!=v;k++)
				{
					P[j][k] = P[v][k];	
					cout<<"p  00000 : v: "<<v<<" k: "<<k<<" j: "<<j<<" "<<P[v][0]<<endl;
				//	system("pause");
				}
				k++;
				P[j][k] = k;
				k++;
				P[j][k] = j;
			}
		}
			for(j=0;j<web.vexnum;j++)
		cout<<j<<" min_path "<<" "<<min_path[j]<<endl;
	}
}

int main()
{
	Init(web);
	ReadFile();
	print_info(); 
	Dijk();
	
	print_info(); 
	return 0; 
}
