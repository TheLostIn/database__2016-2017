#include<iostream>
using namespace std;

typedef int Status;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int ElemType;
typedef struct{
	ElemType * base;
	ElemType top;
	int stacksize;
}SqStack;
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

Status InitStack(SqStack &S);
Status DestroyStack(SqStack &S);
Status ClearStack(SqStack &S);
int StackLength(SqStack &S);
Status GetTop(SqStack &S,ElemType &e);
Status Push(SqStack &S,ElemType e);
Status Pop(SqStack &S,ElemType &e);
Status StackTraverse(SqStack &S,Status (*visit)());
void Increment(SqStack &S);
//从栈底到栈顶依次对栈中的每个元素调用visit()
//--------------------------------------------------
Status InitStack(SqStack &S)
{
	S.base = (ElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));
	if(!S.base) exit(OVERFLOW);
	S.top = -1;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}
Status DestroyStack(SqStack &S){
	delete []S.base;
	S.top=-1;
	S.stacksize=0;
	return OK;
}
Status ClearStack(SqStack &S){
	S.top=-1;
	return OK;
}
int StackLength(SqStack &S){
	return (S.top+1);
}
Status GetTop(SqStack &S,ElemType &e){
	if(S.top == -1) return ERROR;
		e = S.base[S.top];
		return OK;
}
Status Push(SqStack &S,ElemType e){
	if(S.top>=S.stacksize){
		S.base = (ElemType *) realloc (S.base,(S.stacksize+STACKINCREMENT)*sizeof(ElemType));
		if(!S.base) exit (OVERFLOW);
	//	S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	S.base[S.top++] =e;
	return OK;
}
Status Pop(SqStack &S,ElemType &e){
	if(S.top==-1) return  ERROR;
	e = S.base[S.top--];
	return OK;
}
// Status StackTraverse(SqStack &S,Status (*visit)()){

// }
void Increment(SqStack &S)
{
	int i;
	ElemType *newstack;
	newstack = new ElemType[S.stacksize+STACKINCREMENT];
	if(!newstack) ERROR("OVERFLOW");
	for(i=0;i<S.top;i++)
	{
		newstack[i]=S.base[i];
	}
	delete []S.base;
	S.base=newstack;
	S.stacksize+=STACKINCREMENT;
}
int main()
{
	return 0;

}



