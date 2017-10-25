#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>

typedef struct LNode
{
	int data;
	struct LNode *next;
}LNode,*LinkList;

LinkList ListInitialize(LinkList &L)
{
	L = (LNode*)malloc(sizeof(LNode));
	L->next=NULL;
	return L;
}
int ListInsert(LinkList &L,int i,int e)
{
	LinkList p=L;
	int j=0;
	while(p&&j<i-1)
	{
		p=p->next;
		++j;
	}
	if(!p||j>i-1)
		return 0;
	LinkList s=(LinkList)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return 1;
}
void OutputList(LinkList L)
{
	LinkList L2=L->next;
	while(L2!=NULL)
	{
		printf("%d ",L2->data);
		L2=L2->next;
	}
	printf("\n");
}

int ListDelete_L(LinkList &L,int i,int e)
{
	LinkList p=L;int j = 0;
	while(p->next && j<i-1)
	{
		p=p>next;
		++j;
	}
	if(!(p->next||j>i-1))
	return 0;
	LinkList q=p->next;
	p->next=q->next;
	e=q->data;
	free(q);
	return 1;
}
