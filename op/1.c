#include<stdio.h>
#include<stdlib.h>
typedef struct WORKER{
	int id;
	char name[10];
	float salary;
}EMP;
EMP *fun(EMP a[81])
{
	EMP temp;
	int i,j;
	for(i=0;i<81;i++)
	{
		for(j=0;j<81;j++)
		{
			if(a[j].salary>a[j+1].salary)
			temp=a[j];
			a[j]=a[j+1];
			a[j+1]=temp;
		} 
	}
}


int main()
{
	EMP a[81],b[81];
	FILE *fp;
	fp=fopen("workerlink.dat","rb");
	if(fp=NULL)
	{printf("cannot open");}
	else
	{
		int i=0;
		while(!feof(fp))
		{
			fread(b,1,sizeof(EMP),fp);
			if(b.salary<=5000)
			{
				a+i=EMP;
				i++;	
			}
		}
	}
	a[81]=fun(a);
	int j=0;
	for(j=0;j<81;j++)
	printf("%d,%s,%f\n",a[j].id,a[j].name,a[j].salary);
	return 0;
}
