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
void ListInsert(LinkList &L,int i,int e)
{
	LinkList p=L;
	int j=0;
	while(p&&j<i-1)
	{
		p=p->next;
		++j;
	}
	if(!p||j>i-1)
		printf("ERROR");
	LinkList s=(LinkList)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;
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
void main()
{
	void ListInsert(LinkList &L,int i,int e);
	LinkList ListInitialize(LinkList &L);
	void OutputList(LinkList L);
	int n,i,e;
	re:printf("1.��ʼ��������2.����Ԫ��3.����\n");
	scanf("%d",&n);
	switch(n)
	{
	case 1:
		LinkList L;
		ListInitialize(L);
		goto re;
	case 2:
		printf("�ڵ�iλ�ò���Ԫ��e\n");
		scanf("%d",&i);
		scanf("%d",&e);
		ListInsert(L,i,e);
		goto re;
	case 3:
		OutputList(L);
		goto re;
	}
	system("pause");
}
