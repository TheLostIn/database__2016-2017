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
Status GetTop(SqStack &S,SElemType &e);
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

// }
// Status StackEmpty(SqStack S){

// }
// int StackLength(SqStack &S){

// }
Status GetTop(SqStack &S,SElemType &e){
	if(S.top == S.base) return ERROR;
		e = *(S.top-1);
		return OK;
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
int main()
{
	SqStack sq_origin,sq_operation,sq_data,sq_result;
	InitStack(sq_origin);
	InitStack(sq_operation);
	InitStack(sq_data);
	InitStack(sq_result);
	string ori="2+3+5*7*(6+7)-9";
	S.top=ori;







	return 0;

}



