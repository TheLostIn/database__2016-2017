#include<stdio.h>
struct stu
{
	char name[20];
	int age;
};
int write()
{
	FILE *f1;
	int i=0;
	struct stu a[10];
	if((f1=fopen("stu.dat","w"))==NULL)
	{
		printf("NULL \n");
		exit(1);
	}


	while(i<10)
	{
		scanf("%s",a[i].name);
		printf("%s\n",a[i].name);
		a[i].age=i;
		i++;
	}
	fwrite(a,sizeof(struct stu),10,f1);
	fclose(f1);
	return 0;

}
int main()
{
	FILE *f1;
	int i=0;
	struct stu a[10];
	struct b;
	if((f1=fopen("stu.dat","r"))==NULL)
	{
		printf("NULL \n");
		exit(1);
	}
	
//	fread(&a[0],sizeof(struct stu),1,f1);
	while(!feof(f1))
	{
		
	
		fread(&a[i],sizeof(struct stu),1,f1);
		printf("%s %d\n",a[i].name,a[i].age);
		i++;
	}
	/*

	while(i<1)
	{
		printf("%s %d\n",a[i].name,a[i].age);
		i++;
	}
	*/
	fclose(f1);
	return 0;

}
