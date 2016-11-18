#include<iostream>
using namespace std;
#include<fstream>
#define TriList_Size 1000
typedef int Element;
typedef struct {
	int row,col;
	Element e;
}Triple;
typedef struct {
	Triple data[TriList_Size+1];
	int mu,nu,tu;
}TSMatrix;
void InitSMatrix(TSMatrix &M)
{
	M.tu=0;
	M.nu=0;
	M.mu=0;
}
void DestroySMatrix(TSMatrix &M);
void ReadSMatrix(TSMatrix &M)
{
	fstream f1;
	int i=0;
	f1.open("test.txt",ios::in);
	f1>>M.mu>>M.nu;
	while(!f1.eof())
	{
		f1>>M.data[i].row>>M.data[i].col>>M.data[i].e;
		M.tu++;
		i++;
	}
	for(i=0;i<M.tu;i++)
	{
		cout<<M.data[i].row<<" "<<M.data[i].col<<" "<<M.data[i].e<<endl;
	}
	cout<<" tu : "<<M.tu<<endl;
	f1.close();
}
void CopySMatrix(TSMatrix &M);
void AddSMatrix(TSMatrix &M);
void MulSMatrix(TSMatrix &M);
void TransposeSMatrix(TSMatrix M,TSMatrix &T)
{
	InitSMatrix(T);
	int i,j;
	int num[100],cpot[100];
	T.mu=M.mu;
	T.nu=M.nu;
	T.tu=M.tu;
	if(T.tu){
		for(i=0;i<=M.nu;i++)
		{
			num[i]=0;
			cpot[i]=0;
		//	cout<<num[i]<<endl;
		}
		for(i=0;i<M.tu;i++)
		{
			++num[M.data[i].col];
		}
		cpot[0]=0;
		for(i=1;i<=M.nu;i++)
		{
			cpot[i]=cpot[i-1]+num[i-1];
		}
	/*	for(i=0;i<M.nu;i++)
		{
			cout<<num[i]<<" "<<cpot[i]<<endl;
			
		}
	*/	for(i=0;i<M.tu;i++)
		{
			j=M.data[i].col;
			T.data[cpot[j]].row=M.data[i].col;
			T.data[cpot[j]].col=M.data[i].row;
			T.data[cpot[j]].e=M.data[i].e;
			cpot[j]++;
		}
		cout<<endl;
		for(i=0;i<T.tu;i++)
		{
			cout<<T.data[i].row<<" "<<T.data[i].col<<" "<<T.data[i].e<<endl;
		}

	}

}
int main()
{
	TSMatrix M,T;
	int *num,*cpot;
	InitSMatrix(M);
	ReadSMatrix(M);
	TransposeSMatrix(M,T);
	return 0;

}