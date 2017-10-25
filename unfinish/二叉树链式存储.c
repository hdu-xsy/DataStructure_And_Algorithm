#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define OK        1
#define ERROR       0
#define OVERFLOW    -1
#define STACK_INIT_SIZE     100
#define STACKINCREMENT      10

typedef int Status;
typedef char ElemType;

typedef struct BiTNode {
	char data;
	struct BiTNode *lchild;
	struct BiTNode *rchild;
}BiTNode, *BiTree;

typedef BiTree SElemType;

typedef struct {
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;

BiTree CreateBiTree(BiTree T) {
	char ch;
	scanf("%c", &ch);
	if (ch == '#') T = NULL;
	else {
		if (!(T = (BiTNode *)malloc(sizeof(BiTNode))))
			exit(OVERFLOW);
		T->data = ch;
		T->lchild = CreateBiTree(T->lchild);
		T->rchild = CreateBiTree(T->rchild);
	}
	return T;
}


Status InOrderTraverse(BiTree T, Status(*Visit)(ElemType e)) {
	SqStack S;
	SElemType p;
	InitStack(&S);      p = T;
	while (p || !StackEmpty(S)) {
		if (p) {
			Push(&S, p); p = p->lchild;
		}
		else {
			Pop(&S, &p); if (!Visit(p->data))  return ERROR;
			p = p->rchild;
		}
	}
	DestroyStack(&S);
	return OK;

}

Status Visit(ElemType e) {
	if (e == '\0') {
		return ERROR;
	}
	else {
		printf("%c", e);
	}
	return OK;
}

Status InitStack(SqStack *S) {
	S->base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!S->base)
	{
		printf("·ÖÅäÄÚ´æÊ§°Ü.\n");
		exit(0);
	}
	S->top = S->base;
	S->stacksize = STACK_INIT_SIZE;
	return OK;
}

Status DestroyStack(SqStack *S) {
	if (!S)
	{
		exit(0);
	}
	free(S->base);
	return OK;
}


Status StackEmpty(SqStack S) {
	if (S.top == S.base)
		return 1;
	else
		return 0;
}


Status GetTop(SqStack S, SElemType *e) {
	if (S.top == S.base) {
		return 0;
	}
	else {
		*e = *(S.top - 1);
		return OK;
	}
}

Status Push(SqStack *S, SElemType e) {
	if (S->top - S->base >= S->stacksize)
	{
		S->base = (SElemType *)realloc(S->base, (S->stacksize + STACKINCREMENT) * sizeof(SElemType));
		if (!S->base)
		{
			printf("ÖØÐÂÉêÇë¿Õ¼äÊ§°Ü.\n");
			exit(0);
		}
		S->top = S->base + S->stacksize;
		S->stacksize += STACKINCREMENT;
	}
	*S->top++ = e;
	return OK;
}

Status Pop(SqStack *S, SElemType *e) {
	if (S->top == S->base)
	{
		return ERROR;
	}
	*e = *(--S->top);
	return OK;
}

int main()
{
	BiTree CreateBiTree(BiTree T);
	Status Visit(ElemType e);
	BiTree T = NULL;
	Status(*visit)(ElemType e) = Visit;
	T = CreateBiTree(T);
	InOrderTraverse(T, visit);
	system("pause");
	return 0;
}
