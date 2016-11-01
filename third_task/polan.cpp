#include<iostream>
using namespace std;

typedef int Status;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef char SElemType;
typedef struct{
	SElemType * base;
	SElemType * top;
	int stacksize;
}SqStack;
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

Status InitStack(SqStack &S);
Status DestroyStack(SqStack &S);
Status ClearStack(SqStack &S);
Status StackEmpty(SqStack S);
int StackLength(SqStack &S);
char GetTop(SqStack &S,SElemType &e);
Status Push(SqStack &S,SElemType e);
Status Pop(SqStack &S,SElemType &e);
Status StackTraverse(SqStack &S,Status (*visit)());
//从栈底到栈顶依次对栈中的每个元素调用visit()
//--------------------------------------------------
Status InitStack(SqStack &S)
{
	S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if(!S.base) exit(OVERFLOW);
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}
// Status DestroyStack(SqStack &S){

// }
// Status ClearStack(SqStack &S){

//}
Status StackEmpty(SqStack S){
	if(S.top==S.base){
		return TRUE;
	}
	return FALSE;
}
// int StackLength(SqStack &S){

// }
char GetTop(SqStack &S,SElemType &e){
	if(S.top == S.base) return '#';
		e = *(S.top-1);
		return e;
}
Status Push(SqStack &S,SElemType e){
	if(S.top - S.base >=S.stacksize){
		S.base = (SElemType *) realloc (S.base,(S.stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(!S.base) exit (OVERFLOW);
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top++ =e;
	return OK;
}
Status Pop(SqStack &S,SElemType &e){
	if(S.top==S.base) return  ERROR;
	e = *--S.top;
	return OK;
}
// Status StackTraverse(SqStack &S,Status (*visit)()){

// }
int In(char c,char *OP)
{
	int flag=0;
	while(*OP!=NULL&&!flag)
	{
		if(c==*OP)
		{
			flag=1;
		}
		OP++;
	}
	return flag;
}
int get_grade(char a)
{
	switch(a)
	{
	case '+':
		return 1;
	case '-':
		return 1;
	case '*':
		return 2;
	case '/':
		return 2;
	case '(':
		return 1;
	default:
		return 0;
	}
}
char Precede(char a,char b)
{	
	int grade_a=get_grade(a);
	int grade_b=get_grade(b);
	if(grade_a==grade_b)
	{
		return '=';
	}else if(grade_a>grade_b){
		return '>';
	}else{
		return '<';
	}
}
int count(char *q)
{
		SqStack ope,num;
		InitStack(ope);

}
int main()
{
	SqStack OPTR,OPND;

	char e;
	InitStack(OPTR);
	Push(OPTR,'#');
	InitStack(OPND);
	char OP[]="+-*/(";
	char ori[17]="2+3+5*7*(6+7)-9#";
	char res[17];
	char *p;
	char *q;
	q=res;
	p=ori;
	cout<<ori<<endl;
	while(*p!='#')
	{
		if((!In(*p,OP))&&*p!=')'){
			//Push(OPND,*p);
			*q=*p;
			q++;
			cout<<endl<<"now res:"<<res<<" ...."<<endl;
			cout<<"now p:"<<*p<<" ";
		}else if(In(*p,OP)){
			if(*p!='('&&Precede(GetTop(OPTR,e),*p)=='>')
			{
				while(GetTop(OPTR,e)!='#'){
						Pop(OPTR,e);
						(*q++)=e;
						cout<<endl<<res<<endl;
						cout<<e<<" ";
					//	cin>>e;				
					}

			}
			Push(OPTR,*p);
		}else if(*p==')'){
			while(GetTop(OPTR,e)!='('){
				Pop(OPTR,e);
				(*q++)=e;
				cout<<endl<<res<<endl;
				cout<<e<<" ";
			}
			Pop(OPTR,e);
		}else{
			cout<<"wrong"<<endl;
		}
		p++;
	}
	if(*p=='#')
	{
		Pop(OPTR,e);
		(*q++)=e;
		cout<<endl<<res<<endl;
		cout<<e<<" ";
	}
	*q='#';
	cout<<" .."<<res<<" ..　";
	q=res;
	cout<<endl;
	while(*q!='#')
	{
		cout<<*q++;
	}
	count(res);
	return 0;

}



