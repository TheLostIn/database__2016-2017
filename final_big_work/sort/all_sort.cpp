#include<iostream>
#include<fstream>
#include<stack>
using namespace std;

int count[9][9];
int file_num=8;
#define Space_Size 20000
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
typedef struct q_sort
{
	int low;
	int high;
	q_sort()
	{
		low=0;
		high=0;
	}
	q_sort(int l,int h)
	{
		low=l;
		high=h;
	}
}q_sort;
stack<q_sort>q_st;
typedef struct heap_sort
{
	int low;
	int high;
	heap_sort()
	{
		low=0;
		high=0;
	}
	heap_sort(int l,int h)
	{
		low=l;
		high=h;
	}
}heap_sort;
stack<heap_sort>h_st;

void read_numbers(int* b,int type)
{
	fstream f1;
	char file_name[28];
	char base_name[]="random_number";
	char *p;
	p=file_name;
	char num[]="0";
	char base_prefix[]=".txt";
	int j=0;
	num[0]='0'+type;
	strcpy(file_name,base_name);
	strcat(file_name,num);
	strcat(file_name,base_prefix);
//	cout<<file_name<<endl;
	f1.open(file_name,ios::in);
	int i=1;
	while(i<=maxn)
	{
		f1>>b[i++];
	}
	f1.close();
}
void read_radix_numbers(SLList *b,int type)
{
	fstream f1;
	char file_name[28];
	char base_name[]="random_number";
	char *p;
	p=file_name;
	char num[]="0";
	char base_prefix[]=".txt";
	int j=0;
	num[0]='0'+type;
	strcpy(file_name,base_name);
	strcat(file_name,num);
	strcat(file_name,base_prefix);
//	cout<<file_name<<endl;
	f1.open(file_name,ios::in);
	int i=1;
	int tmp;
	while(i<maxn)
	{	
			
		f1>>tmp;
		init_L(b,i++,tmp);
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

/*
¶ÑÅÅÐò¡¢Ö±½Ó²åÈëÅÅÐò¡¢ÕÛ°ë²åÈëÅÅÐò£¬ÆðÅÝÅÅÐò¡¢¿ìËÙÅÅÐò¡¢Ñ¡ÔñÅÅÐò£¬»ùÊýÅÅÐò
*/
void HeapAdjust(int *a,int low,int high,int col)
{
	a[0]=a[low];
	for(int j=2*low;j<=high;j*=2)
	{
		if((j<high)&&(a[j]<a[j+1]))
		{
			j++;
			count[0][col]++;
		}
		
		if(a[0]>=a[j])
		{
			count[0][col]++;
			break;
		}
		a[low]=a[j];
		low=j;
	}
	a[low]=a[0];
}
void HeapSort(int *a,int col)
{
	int high;
	count[0][col]++;
	for(int i=maxn/2;i>0;--i)
	{
		
		count[0][col]++;
		HeapAdjust(a,i,maxn,col);
	}
	
	count[0][col]++;
	
	count[0][col]++;
	for(high=maxn;high>1;high--)
	{
		
	count[0][col]++;
		a[0]=a[1];
		a[1]=a[high];
		a[high]=a[0];
		HeapAdjust(a,1,high-1,col);
	}
	
	count[0][col]++;
}
void Straight_sort(int *a,int col)
{
	for(int i=2;i<maxn;i++)
	{
		count[1][col]++;
		if(a[i]<a[i-1])
		{
			a[0]=a[i];	
			count[1][col]++;
			for(int j=i-1;a[0]<a[j];--j)
			{
				a[j+1]=a[j];
				count[1][col]++;
			}
			count[1][col]++;
			a[j+1]=a[0];
		}
	}
}
int search_place(int *a,int i,int col)
{
		int left,right,mid;
		left=1;
		right=i-1;
		mid=(i-1)/2;
		count[2][col]++;
		while(left<=right)
		{
			count[2][col]++;
		//	cout<<count[2][col]<<endl;
			if(a[i]<a[mid])
			{
				right=mid-1;
			}
			else if(a[i]>a[mid])
			{
				count[2][col]++;
				left=mid+1;
			}
			else
			{
				count[2][col]++;
				return mid;
			}
			mid=(left+right)/2;
	//		cout<<left<<" "<<right<<" "<<mid<<endl;
		//	system("pause");
		}
		return mid;

}
void Straight_half_sort(int *a,int col)
{
//	cout<<"p"<<endl;
	for(int i=2;i<maxn;i++)
	{
		count[2][col]++;

		if(a[i]<a[i-1])
		{
			int n;
		
			a[0]=a[i];
			n=search_place(a,i,col);
			for(int j=i-1;j>n;--j)
			{
				count[2][col]++;
				a[j+1]=a[j];
			}
	//		cout<<"po"<<endl;
			a[j+1]=a[0];
		}
	}
}
void bubble_sort(int *a,int col)
{
	int tag=0;
	count[3][col]++;
	for(int bound=1;tag==0;bound++)
	{
		count[3][col]++;
		count[3][col]++;
		tag=1;
		for(int i=maxn;i>bound;--i)
		{
			count[3][col]++;
			if(a[i]<a[i-1])
			{
				a[0]=a[i];
				a[i]=a[i-1];
				a[i-1]=a[0];
				tag=0;
			}
		}
		count[3][col]++;
	}	


}
int partition(int *a,int low,int high,int col)
{
	int pivotkey;
	a[0]=a[low];
	pivotkey=a[low];
	while(low<high)
	{
		while(low<high&&(a[high]>=pivotkey))
		{
			--high;
		}
		a[low]=a[high];
	//	low++;
		while(low<high&&(a[low]<=pivotkey))
		{
			++low;
		}
		a[high]=a[low];
	//	high++;
	//	cout<<low<<" "<<high<<" "<<endl;
	}
	a[low]=a[0];
	return low;

}
void qq_sort(int *a,int low,int high,int col)
{
	q_sort q;
	q_st.push(q_sort(low,high));
	int pivotpos;
	count[4][col]++;
	while(!q_st.empty()&&low<high)
	{

		pivotpos=partition(a,low,high,col);
		if(pivotpos+1<high)
		q_st.push(q_sort(pivotpos+1,high));
		if(pivotpos-1>low)
		q_st.push(q_sort(low,pivotpos-1));
		q=q_st.top();	
		q_st.pop();
		low=q.low;
		high=q.high;
		//	cout<<low<<" "<<high<<" "<<pivotpos<<endl;
		//	system("pause");
		count[4][col]++;
		}

}
void Q_sort(int *a,int low,int high,int col)
{
	count[4][col]++;
	cout<<high<<" "<<low<<"pp"<<endl;
	if(low<high){
	int pivotpos;
	pivotpos=partition(a,low,high,col);
	Q_sort(a,low,pivotpos-1,col);
	Q_sort(a,pivotpos+1,high,col);
	}

}
void quick_sort(int *a,int col)
{
//	Q_sort(a,1,maxn,col);
	qq_sort(a,1,maxn,col);
}

void select_sort(int *a,int col)
{
	count[5][col]++;
	for(int i=1;i<maxn;i++)
	{
		int k=i;
		count[5][col]++;
		for(int j=i+1;j<=maxn;j++)
		{	
			if(a[j]<a[k])
				k=j;
			count[5][col]++;
		}
		count[5][col]++;
		if(i!=k)
		{
			a[0]=a[i];
			a[i]=a[k];
			a[k]=a[0];
		}
		count[5][col]++;
	}
}

void radix_display_number(SLList *b)
{
	int i=0;
	while(i<maxn)
	{
		cout<<b->r[i++].next<<" ";
		if(i%10==0)
			cout<<endl;
	}
}
void Distribute(SLNode *r,int i,int *f,int *e,int col)
{
	int p;
	int j;
	count[6][col]++;
	for(j=0;j<RD;j++)
	{
		f[j]=0;		
		count[6][col]++;

	}
	count[6][col]++;
	for(p=r[0].next;p;p=r[p].next)
	{
		j=r[p].keys[i];
		if(!f[j]) f[j]=p;
		else r[e[j]].next=p;
		e[j]=p;
		count[6][col]++;
	}
	
}
void Collect(SLNode *r,int i,int *f,int *e,int col)
{
	int j;
	int t;
	for(j=0;!f[j];j++);
	r[0].next=f[j];
	t=e[j];
			count[6][col]++;
	while(j<(RD-1))
	{
					count[6][col]++;
		for(j++;(j<(RD-1))&&(!f[j]);j++)
		{
			count[6][col]++;
		}
				count[6][col]++;
			if(f[j])
			{
				r[t].next=f[j];
				t=e[j];
			}
			count[6][col]++;
	}
	r[t].next=0;


}
void RadixSort(SLList *L,int col)
{

	int i;
	int j=0;
	for(i=0;i<5;i++)
	{
				count[6][col]++;
		Distribute(L->r,i,f,e,col);
		Collect(L->r,i,f,e,col);
	}
	SLNode *r;
	r=L->r;
	i=r[0].next;
	cout<<"done"<<endl;
/*	while(i!=0)
	{
		j++;
		if(j%10==0) cout<<endl;
		cout<<r[i].key<<" ";
		i=r[i].next;
	}
	*/
}

/*
¶ÑÅÅÐò¡¢Ö±½Ó²åÈëÅÅÐò¡¢ÕÛ°ë²åÈëÅÅÐò£¬ÆðÅÝÅÅÐò¡¢¿ìËÙÅÅÐò¡¢Ñ¡ÔñÅÅÐò£¬»ùÊýÅÅÐò
*/
int main()
{
	int a[30005];
//	SLList *b;
//	b=new SLList;

	memset(count,0,sizeof(count));
	cout<<" heap  Straight  Straight_half  bubble  quick  select  RadixSort"<<endl;
	for(int i=0;i<file_num;i++)
	{
		SLList *b;
		b=new SLList;
		read_numbers(a,i);
		HeapSort(a,i);
		read_numbers(a,i);
		Straight_sort(a,i);
		read_numbers(a,i);
		Straight_half_sort(a,i);
		read_numbers(a,i);
		bubble_sort(a,i);	
		read_numbers(a,i);
		quick_sort(a,i);
		read_numbers(a,i);
		select_sort(a,i);
		read_radix_numbers(b,i);
		RadixSort(b,i);
		cout<<i+1<<" "<<count[0][i]<<" "<<count[1][i]<<" "<<count[2][i]<<" "<<count[3][i]<<" "<<count[4][i]<<" "<<count[5][i]<<" "<<count[6][i]<<endl;
	}
	return 0;
}