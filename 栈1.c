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
	re:printf("1.��ʼ��ջ2.��ջ3.��ջ\n");
	scanf("%d\n",&n);
	switch(n)
	{
	case 1:
		SqStack S;
		InitStack(S);
		goto re;
	case 2:
		printf("����Ԫ��e\n");
		scanf("%d",&e);
		Push(S,e);
		goto re;
	case 3:
		Pop(S,e);
		goto re;
	}

	system("pause");
}
