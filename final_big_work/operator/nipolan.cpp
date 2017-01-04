#include<iostream>
#include<string>
#include<fstream>
using namespace std;
#include<stack>
#include<map>
#define EXPRESSION_FILE "exp.txt"
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
int nipolan(char *a,char *&post)
{
	stack<char>p;
	int i=0,j=0;
	int flag=0;
//	memset(post,' ',sizeof(post));
	i++;
	cout<<"origin expression: "<<a<<endl;
	while(a[i]!='#')
	{
		
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
				while(!p.empty()&&p.top()!='(')
				{
					post[j]=p.top();
					j++;
					p.pop();
				}
			
				if(p.empty())
				{
					return 0;
				}
				else
				{
					
					if(p.top()=='#')
					{
						cout<<"wrong expresion"<<endl;
						return 0;
					}
					if(p.top()=='(')
					{
						p.pop();
					}
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
	post[++j]='\0';
	cout<<"post: "<<post<<endl;
	return 1;
}

int count_expression(char post[],char *a)
{
	char *exp;
	memset(post,' ',sizeof(post));
	if(nipolan(a,post))
	{
		exp=post;
		stack<int>p;
		stack<char>op;
		while(*exp!='#')
		{
			if(*exp=='(')
			{
				return 0;
			}
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
				exp++;
			}
		}
		cout<<endl<<p.top()<<endl<<endl;
	}
	else
	{
		return 0;
	}
	return 1;
}
int main()
{
	fstream exp_file;
	int i=1;
	exp_file.open(EXPRESSION_FILE,ios::in);
	if(exp_file.fail())
	{
		cout<<"can't open file"<<endl;
		exit(1);
	}
	while(!exp_file.eof())
	{
		char post[30];
		char exp[30];
		exp_file>>exp;
		cout<<i++<<" :¡¡"<<endl;
		if(!(count_expression(post,exp)))
		{
			cout<<"wrong expression. :"<<exp<<endl<<endl;
		}
	}
	exp_file.close();
	return 0;
}