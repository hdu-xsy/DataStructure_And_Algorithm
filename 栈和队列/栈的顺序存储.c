#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define	OK			1
#define TRUE        1
#define FALSE       0
#define	ERROR		0
#define	OVERFLOW	-2
typedef int Status;
#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a)<(b))
#define LQ(a,b) ((a)<=(b))
typedef  int SElemType_Sq;
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef struct
{
	SElemType_Sq *base;
	SElemType_Sq *top;
	int stacksize;
}SqStack;

Status InitStack_Sq(SqStack *S)
{
	//构造空栈
	(*S).base = (SElemType_Sq*)malloc(STACK_INIT_SIZE* sizeof(SElemType_Sq));
	if (!(*S).base)
		exit(OVERFLOW);
	(*S).top = (*S).base;
	(*S).stacksize = STACK_INIT_SIZE;
	return OK;
}

Status DestroyStack_Sq(SqStack *S)
{
	//销毁S
	free((*S).base);
	(*S).base = NULL;
	(*S).top = NULL;
	(*S).stacksize = 0;
	return 0;
}

Status ClearStack_Sq(SqStack *S)
{
	//置空S
	(*S).top = (*S).base;
	return OK;
}

Status StackEmpty_Sq(SqStack S)
{
	//判断S是否为空
	if (S.top == S.base)
		return TRUE;
	else
		return FALSE;
}

Status StackLength_Sq(SqStack S)
{
	//返回S元素个数
	return S.top - S.base;
}

Status GetTop_Sq(SqStack S, SElemType_Sq *e)
{
	//用e获取栈顶元素
	if (S.top == S.base)
		return ERROR;
	*e = *(S.top - 1);
	return OK;
}

Status Push_Sq(SqStack *S, SElemType_Sq *e)
{
	//元素e进栈
	if ((*S).top - (*S).base >= (*S).stacksize)
	{
		(*S).base = (SElemType_Sq*)realloc((*S).base, ((*S).stacksize + STACKINCREMENT) * sizeof(SElemType_Sq));
		if (!(*S).base)
			exit(OVERFLOW);
		(*S).top = (*S).base + (*S).stacksize;
		(*S).stacksize += STACKINCREMENT;
	}
	*(S->top) = e;
	(S->top)++;
	return OK;
}

Status Pop_Sq(SqStack *S, SElemType_Sq *e)
{
	//元素e出栈
	if ((*S).top == (*S).base)
		return ERROR;
	(*S).top--;
	*e = *((*S).top);
	return OK;
}

Status StackTraverse_Sq(SqStack S, void(Visit)(SElemType_Sq))
{
	//访问栈
	SElemType_Sq *p = S.base;
	while (p < S.top)
		Visit(*p++);
	return OK;
}
void main()
{

}
