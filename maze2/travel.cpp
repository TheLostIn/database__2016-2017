/*
8�������������� (ѡ��)��ͼ��
[��������]
��ѧУ���Ͼ�����Ϊ������Ʋ�ʵ��ѧУ�;���֮�䣬�����뾰��֮���������
[����Ҫ��]
��1���������������15��������֮���·��������30����
��2������������������֮������·����
��3������ѧУ�����⾰��֮������·����
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
	cout<<"��������Ϊ��\n\n" ;
	for(i=0;i<web.vexnum;i++)
	{
		cout<<i+1<<":"<<toursite[i]<<endl<<endl;		
	}	
} 

void Dijk()
{
	int i,j,k,v,min;
	int final[16];		//��־�м�·����������·�� 
	int min_path[16+5];	//��¼��ÿ���������̾��� 
	int P[16+3][16+3]; //��¼ÿ��·������ͨ����Щ�� 
		
	for(i=0; i<web.vexnum; i++)//����0ΪԴ�㣬������� 
	{
		final[i] = 0;			//��ʼ��Դ�㵽ÿ�������·�����	
		min_path[i] = web.arcs[0][i];
	//	cout<<min_path[i]<<endl;
		for(j=0; j<web.arcnum; j++)
		{
			P[i][j] = -1;		//���ÿ�·�� 
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
		for(j=1; j<web.vexnum; j++)		//�ҵ�ÿһ�ֿɴ�·������̵�һ�� 
		{
			
//	cout<<"min_path min 2 "<<j<<" "<<min_path[j]<<"��"<<min<<endl; 
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
		cout<<"\n�������: "<<v<<" "<<min<<endl;
		
		for(j=0;P[v][j]!=v;j++)cout<<P[v][j]<<" "; 
	
		cout<<"\n�� "<<toursite[0]<<" �� "<<toursite[v]<<" "<<v<<" "<<"�����·��Ϊ��\n";
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
