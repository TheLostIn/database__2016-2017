#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stack>
#define Max_Len 100 
using namespace std;
typedef struct point{
	int x;
	int y;
	point(){x=0;y=0;}
}point;
int maze[Max_Len][Max_Len];

int visit[Max_Len][Max_Len];
int wid=13,num;
point start,end;
int max_num=0;
void InitMaze()
{
	int i,j;
	for(i=0;i<=Max_Len;i++)
	{
		for(j=0;j<=Max_Len;j++)
		{
			if(i%2==0&&j%2==0)
			{
				maze[i][j]=0;
			}
			else
			{

				maze[i][j] = 1;			//1为障碍，0为通过 
			}
			//maze[i][j] = 1;			//1为障碍，0为通过 
			visit[i][j]=0;
		}
	}
}
int test(point p,int type=2)
{
	int x[4]={-2,0,2,0};
	int y[4]={0,2,0,-2};
	//cout<<"type: "<<type<<endl;
	if(type!=2)
	{
		x[0]=-1;
		x[2]=1;
		y[1]=1;
		y[3]=-1;
	}


	for(int i=0;i<4;i++)
	{
		int new_x=p.x+x[i];
		int new_y=p.y+y[i];
		if(new_x>0&&new_x<wid&&new_y>0&&new_y<wid)
		{
			cout<<new_x<<new_y<<endl;
			if(type==2)
			{
				if(visit[p.x+x[i]][p.y+y[i]]==0)
				{//	cout<<"good "<<new_x<<new_y<<endl;
					return i;
				}
			}
			else
			{
				if(maze[p.x+x[i]][p.y+y[i]]==0)
				{//	cout<<"good "<<new_x<<new_y<<endl;
					return i;
				}
			}
		
		}
	}
	return -1;
}
void CreatMaze()
{
	num=0;
	srand(clock());
	point road[Max_Len*Max_Len];
	int len,dir,i=1;
	int xx[4]={-1,0,1,0};
	int yy[4]={0,1,0,-1};
	int x[4]={-2,0,2,0};
	int y[4]={0,2,0,-2};
	int new_x;
	int new_y;
	point p;
	point path[Max_Len];
	cout<<"请输入迷宫的边长：\n";
	wid=13;
	//cin>>wid;
	len = wid;
	cout<<"在左边界上选择入口坐标：\n";
//	cin>>start.x>>start.y;
	start.x=2;
	start.y=2;
	p.x = start.x;
	p.y = start.y;
	path[0] = p;
	maze[p.x][p.y] = 0;
	visit[p.x][p.y] = 1;
	road[num++]=p;
	while(p.x != wid-1) 
	{
		int p_i=0;
		if(test(p)!=-1)
		{
			dir = rand()% 4;
			new_x=p.x+x[dir];
			new_y=p.y+y[dir];
			if(new_x>0&&new_x<=len&&new_y>0&&new_y<=len)
			{
				if(maze[new_x][new_y]==0&&visit[new_x][new_y]==0)
				{	
				//	cout<<dir<<" "<<new_x<<" "<<new_y<<endl;
				//	cout<<"paint : "<<p.x+xx[dir]<<" "<<p.y+yy[dir]<<endl;
				//	system("pause");
					maze[p.x+xx[dir]][p.y+yy[dir]] = 0;
						visit[p.x+xx[dir]][p.y+yy[dir]] = 1;
					p.x+=x[dir];
					p.y+=y[dir];
					path[i++] = p;
					visit[p.x][p.y]=1;
					road[num++]=p;
				}
			}
		}
		else
		{
		
			if(num!=1)
			{
			//	system("pause");
				p=road[--num];
				cout<<"p_i : "<<p_i<<" ppp"<<endl;
			}
			else
			{
				p=road[rand()%max_num];
			}
		}
	//	system("pause");
	//	cout<<"out: "<<dir<<" "<<new_x<<" "<<new_y<<endl;
	
	//	cout<<"out: "<<dir<<" "<<p.x<<" "<<p.y<<endl;
		if(max_num<num)
		{
			max_num=num;
		}
	}		
	int path_len = i;
	for(i=0;i<path_len;i++)
	{
		cout<<"("<<path[i].x<<","<<path[i].y<<")   ";		
	}	
	cout<<"ok"; 
	for(i=0;i<(wid*wid/5);i++)				//设置一定数量的干扰通路 
	{
		maze[1+rand()%wid][1+rand()%wid] = 0;
	}
}
void PrintMaze()
{
	cout<<"wid "<<wid<<endl;
	int i=0,j=0;
	for(i=1;i<=wid;i++)
	{
		cout<<"\n";
		for(j=1;j<=wid;j++)
		{


		/*	if(!maze[i][j])
			cout<<"0 ";
			else
				cout<<"  ";
				*/
			
			if(maze[i][j]>9)
				cout<<maze[i][j]<<" ";
			else
				cout<<maze[i][j]<<"  ";
		}
	}
} 

void Solve()
{
	stack<point> S;
	
	int x[4]={-1,0,1,0};
	int y[4]={0,1,0,-1};
	int index=0;
	point p;
	p.x = start.x ;
	p.y = start.y ;
	point cur;
	S.push(p);
	maze[p.x][p.y]=index++;
	int dir=0;
	while((p.x!=wid-1)&&!S.empty())
	{
		dir=test(p,1);
		cout<<"dir : "<<dir<<"   "<<p.x<<" "<<p.y<<endl;
		if(dir!=-1)
		{
			cur.x=p.x+x[dir];
			cur.y=p.y+y[dir];		
			maze[cur.x][cur.y]=index++;	
			S.push(p);
			p=cur;
		//	system("pause");
		}else
		{
			p=S.top();
			S.pop();
		}
		
	}


}
int main()
{
	wid=13;
	InitMaze();
	PrintMaze();
	cout<<"1 : "<<"edn"<<endl;
	CreatMaze(); 
	
	PrintMaze();
	Solve();
	PrintMaze();
	return 0;
} 
