#include<iostream>
#include<string>
using namespace std;
#include<stack>
#include<map>
char a[100]="#12+90*(90+99)-29+12/2#";
char int_divide='_';
int count(int left,int right,char op)
{
	switch(op)
	{
		case '+':
			return left+right;
		case '-':
			return left-right;
		case '*':
			return left*right;
		case '/':
			return left/right;
		default:
			return -1;
	}
}
int priority(char a)
{
	switch(a)
	{
		case '(':
			return 1;
		case '+':
			return 2;
		case '-':
			return 2;
		case '*':
			return 3;
		case '/':
			return 3;
		default:
			return -1;
	}
}
void nipolan(char *post)
{
	stack<char>p;
	int i=0,j=0;
	int flag=0;
	memset(post,' ',sizeof(post));
	i++;
	while(a[i]!='#')
	{
		cout<<a[i]<<endl;
		if(a[i]=='(')
		{
			p.push(a[i]);
		}
		else if(a[i]>='0'&&a[i]<='9')
		{
			if(flag==0)
			{
				post[j++]=a[i];
				post[j]=int_divide;
				j++;
				flag=1;
			}
			else
			{
				post[j-1]=a[i];
				post[j]=int_divide;
				j++;
			}
		}
		else if(a[i]=='+'||a[i]=='-'||a[i]=='*'||a[i]=='/'||a[i]=='('||a[i]==')')
		{
			flag=0;
			if(a[i]==')')
			{
				while(p.top()!='(')
				{
					post[j]=p.top();
					j++;
					p.pop();
				}
				if(p.top()=='(')
				{
					p.pop();
				}
			}
			else if(p.empty()||priority(a[i])>priority(p.top()))
			{
				p.push(a[i]);
			}
			else if(a[i]=='(')
			{
				p.push(a[i]);
			}
			else
			{
				while(priority(a[i])<=priority(p.top()))
				{
					post[j++]=p.top();
					p.pop();
					if(p.empty())
					{
						break;
					}
				}
				p.push(a[i]);
			}
		}
		i++;
	}
	while(!p.empty())
	{
		post[j++]=p.top();
		p.pop();
	}
	post[j]='#';
	cout<<a<<endl;
	cout<<post<<endl;
}

int main()
{
	char post[100];
	char *exp;
	memset(post,' ',sizeof(post));
	nipolan(post);
	exp=&post[0];
	stack<int>p;
	stack<char>op;
//	cout<<post[2];
	while(*exp!='#')
	{
		cout<<*exp;
		if(*exp>='0'&&*exp<='9')
		{	
			int tmp=0;
			while(*(exp)!=int_divide)
			{	
				tmp=tmp*10+(*exp-'0');
				exp++;
			}
			p.push(tmp);
			exp++;
		}
		else if(*exp!='#')
		{
			int left,right;
			char chr;
			right=p.top();
			p.pop();
			left=p.top();
			p.pop();
			p.push(count(left,right,*exp));
//			cout<<endl<<"left: "<<left<<" right "<<right<<" "<<count(left,right,*exp)<<endl;
			exp++;
		}
	}
	cout<<endl<<p.top()<<endl;

	return 0;

}
