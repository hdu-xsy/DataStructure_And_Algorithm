#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#define M 100

typedef struct
{
	int data[M];
	int *top;
}SqStack;

SqStack InitStack(SqStack &S)
{
	S.top = (int*)malloc(M*sizeof(int));
	return S;
}

void Push(SqStack &S,int e)
{
	*S.top ++= e;
}

void Pop(SqStack &S,int &e)
{
	e = * --S.top;
	printf("%d",e);
}
void main()
{
	SqStack InitStack(SqStack &S);
	void Push(SqStack &S,int e);
	void Pop(SqStack &S,int &e);
	int n,e;
		SqStack S;
		InitStack(S);
		scanf("%d",&e);
		Push(S,e);
		Pop(S,e);
}
