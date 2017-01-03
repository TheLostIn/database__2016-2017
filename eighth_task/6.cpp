/*
30000 29999 29998 29997 29996 29995 29994 29993 29992 29991 29990 29989 29988 29987 29986 29985 29984 29983 29982 29981 29980 29979 29978 29977 29976 29975 29974 29973 29972 29971 29970 29969 29968 29967 29966 29965 29964 29963 29962 29961 29960 29959 29958 29957 29956 29955 29954 29953 29952 29951 29950 29949 29948 29947 29946 29945 29944 29943 29942 29941 29940 29939 29938 29937 29936 29935 29934 29933 29932 29931 29930 29929 29928 29927 29926 29925 29924 29923 29922 29921 29920 29919 29918 29917 29916 29915 29914 29913 29912 29911 29910 29909 29908 29907 29906 29905 29904 29903 29902 29901 29900 29899 29898 29897 29896 29895 29894 29893 29892 29891 29890 29889 29888 29887 29886 29885 29884 29883 29882 29881 29880 29879 29878 29877 29876 29875 29874 29873 29872 29871 29870 29869 29868 29867 29866 29865 29864 29863 29862 29861 29860 29859 29858 29857
*/
//invert_number.txt
/*
9043 2265 19587 3331 12417 16569 25318 31507 4321 25898 21799 29912 25659 4703 7164 26685 6301 5825 17017 4375 9051 22501 1844 9653 19285 955 6311 12728 26744 25097 28885 4901 15496 23064 5169 19897 18716 174 14267 10365 18154 16955 4716 18842 8772 32087 24020 17517 8419 8556 18946 19934 5348 9648 26788 2798 16656 27735 21359 11664 21088 26118 4545 21434 4800 2442 389 23739 14612 29642 18264 10447 31353 17402 2537 30449 16589 2066 31910 21744 10865 19839 32149 21957 14157 10776 19071 548 18197 20819 4436 14161 19659 2489 24523 26677 23430 5783 13897 29873 
*/
//random_number.txt
/*
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48
*/
//order_number.txt
#include<iostream>
#include<fstream>
using namespace std;
#define Space_Size 30000
#define RD 10
#define Key_Size 8
typedef int InfoType;
int maxn=Space_Size-5;
int f[10];
int e[10];
typedef struct SLNode
{
    int keys[Key_Size];
    InfoType otherInfo;
    int next;
    int key;
    SLNode()
    {
        key=0;
        //memset(keys,0,sizeof(keys));
        for(int i=0;i<Key_Size;i++)
        {
            keys[i]=0;
        }
        next=0;
    }
}LNode;
typedef struct
{
    SLNode r[Space_Size+1];
    int keynum;
    int length;
}SLList;
typedef int ArrType[RD];
void init_L(SLList *b,int i,int tmp)
{
    int j=0;
    b->r[i].key=tmp;
    b->r[i-1].next=i;
    while(tmp>0)
    {
        b->r[i].keys[j]=tmp%10;
        tmp/=10;
        j++;
    }
}
void read_numbers(SLList *b,int type)
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
    int tmp;
    while(i<maxn)
    {   
             
        f1>>tmp;
        init_L(b,i++,tmp);
     
    }
    f1.close();
}
 
void display_number(SLList *b)
{
    int i=0;
    while(i<maxn)
    {
        cout<<b->r[i++].next<<" ";
        if(i%10==0)
            cout<<endl;
    }
}
void Distribute(SLNode *r,int i,int *f,int *e)
{
    int p;
    int j;
    for(j=0;j<RD;j++)
    {
        f[j]=0;
    }
    for(p=r[0].next;p;p=r[p].next)
    {
        j=r[p].keys[i];
        if(!f[j]) f[j]=p;
        else r[e[j]].next=p;
        e[j]=p;
    }
     
}
void Collect(SLNode *r,int i,int *f,int *e)
{
    int j;
    int t;
    for(j=0;!f[j];j++);
    r[0].next=f[j];
    t=e[j];
    //cout<<"0 :"<<endl;
     
//cout<<endl<<j<<" f "<<f[j]<<" "<<e[j]<<" "<<" "<<r[f[j]].next<<" "<<r[e[j]].next<<endl;
/*      for(j=0;j<RD;j++)
    {
        cout<<endl<<f[j]<<" "<<e[j]<<endl;
        i=j;
    while(i!=0)
    {
        cout<<r[i].key<<" ";
        i=r[i].next;
    }
    }
    */
    while(j<(RD-1))
    {
    //  cout<<"find:"<<endl;
        for(j++;(j<(RD-1))&&(!f[j]);j++);
         
//  cout<<"j: "<<j<<" f[j]:"<<f[j]<<" e[j]"<<e[j]<<" "<<r[e[j]].next<<endl;
    //      cout<<j<<endl;
        //  system("pause");
    //      cout<<f[j]<<" ";
             
    //      cout<<endl<<"j: "<<j<<" f[j]:"<<f[j]<<" "<<e[j]<<" "<<r[t].next<<endl;
            if(f[j])
            {
                r[t].next=f[j];
                t=e[j];
            }
    //      cout<<"j: "<<j<<" f[j]:"<<f[j]<<" "<<e[j]<<" "<<r[t].next<<endl;
             
//cout<<endl<<j<<" f "<<f[j]<<" "<<e[j]<<" "<<" "<<r[f[j]].next<<" "<<r[e[j]].next<<endl;
    }
    r[t].next=0;
 
 
}
void RadixSort(SLList *L)
{
 
    int i;
    int j=0;
    for(i=0;i<5;i++)
    {
        Distribute(L->r,i,f,e);
         
//  display_number(a);
        Collect(L->r,i,f,e);
 
    }
    SLNode *r;
    r=L->r;
    i=r[0].next;
    while(i!=0)
    {
        j++;
        if(j%10==0) cout<<endl;
        cout<<r[i].key<<" ";
        i=r[i].next;
    }
}
int main()
{
    SLList *a;
    a=new SLList;
    read_numbers(a,1);
//  display_number(a);
//  Straight_sort(a);
//  display_number(a);
     RadixSort(a);
     cout<<endl;
    //display_number(a);
    return 0;
 
}