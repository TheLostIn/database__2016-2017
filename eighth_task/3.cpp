//invert_number.txt 30000 numbers
 
#include<iostream>
#include<fstream>
using namespace std;
int maxn=30000 ;
 
void read_numbers(int* b,int type)
{
    fstream f1;
    char a[20];
    char *p;
    p=a;
    switch(type)
    {
        case 0:
            p="order_number.txt";
            break;
        case 1:
            p="invert_number.txt";
            break;
        case 2:
            p="random_number.txt";
            break;
        default:
            p="random_number.txt";
    }
    f1.open(p,ios::in);
    int i=1;
    while(i<=maxn)
    {
        f1>>b[i++];
    }
    f1.close();
}
 
void display_number(int a[])
{
    int i=1;
    while(i<=maxn)
    {
        cout<<a[i++]<<" ";
        if(i%10==0)
            cout<<endl;
    }
}
void Msort(int *a,int low,int mid,int high)
{
    int *t;
    int i,j,p;
    p=0;
    i=low;
    j=mid+1;
    t = new int[high-low+1];
    while(i<=mid&&j<=high)
    {
        if(a[i]<a[j])
        {
            t[p++]=a[i++];
        }
        else
        {
            t[p++]=a[j++];
        }
    }
    while(i<=mid)
    {
        t[p++]=a[i++];
    }
    while(j<=high)
    {
        t[p++]=a[j++];
    }
    for(p=0,i=low;i<=high;i++,p++)
    {
        a[i]=t[p];
    }
}
void Merge_sort(int *a,int low,int high)
{
    int mid;
    if(low<high)
    {
        mid=(low+high)/2;
        Merge_sort(a,low,mid);
        Merge_sort(a,mid+1,high);
        Msort(a,low,mid,high);
    }
}
 
void bubble_sort(int *a)
{
    int tag=0;
    int count=0;
    for(int bound=1;tag==0;bound++)
    {
        tag=1;
    //  cout<<"bound:"<<bound<<endl;
    //  system("pause");
        for(int i=maxn;i>bound;--i)
        {
            count++;
            if(a[i]<a[i-1])
            {
            //  cout<<a[i]<<" "<<a[i-1]<<endl;
            //  system("pause");
                a[0]=a[i];
                a[i]=a[i-1];
                a[i-1]=a[0];
                tag=0;
            }
        }
         
//  display_number(a);
    }
    cout<<"bubble: "<<count<<endl;
     
 
}
 
void select_sort(int *a)
{
    int count=0;
    for(int i=1;i<maxn;i++)
    {
        int k=i;
        for(int j=i+1;j<=maxn;j++)
        {
            count++;
            if(a[j]<a[k])
                k=j;
        }
        if(i!=k)
        {
            a[0]=a[i];
            a[i]=a[k];
            a[k]=a[0];
        }
    }
    cout<<"select: "<<count<<endl;
}
 
int main()
{
    int a[30005];
    read_numbers(a,1);
    Merge_sort(a,1,maxn);
    read_numbers(a,1);
    bubble_sort(a);
    read_numbers(a,1);
    select_sort(a);
    display_number(a);
    return 0;
 
}