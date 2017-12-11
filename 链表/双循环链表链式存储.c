#include <stdio.h>
#include <stdlib.h>

#define	OK			1
#define	ERROR		0
#define	OVERFLOW	-2
#define TRUE		1
#define FALSE		0
#define NULL		((void*)0) 
typedef int Status;

typedef int LElemType_DC;
typedef struct DuLNode
{
	LElemType_DC data;
	struct DuLNode *prior;
	struct DuLNode *next;
}DuLNode;
typedef DuLNode* DuLinkList;

Stutus ComGreater(LElemType_DC e, LElemType_DC data)
{
	return data > e ? TRUE : FALSE;
}
void PrintElem(LElemType_DC e)
{
	printf("%d", e);
}

Status InitList_DuL(DuLinkList *L) //初始化双链表L
{
	*L = (DuLinkList)malloc(sizeof(DuLNode));
	if (!(*L))
		exit(OVERFLOW);
	(*L)->next = (*L)->prior = *L;
	return OK;
}

Status ClearList_DuL(DuLinkList L) //置空L
{
	DuLinkList p,q;
	p = L->next;
	while (p != L)
	{
		q = p->next;
		free(p);
		p = q;
	}
	L->next = L->prior = L;
	return OK;
}

void DestroyList_DuL(DuLinkList *L) //销毁L
{
	ClearList_DuL(*L);
	free(*L);
	*L = NULL;
}

Status ListEmpty_Dul(DuLinkList L) //判断L是否为空
{
	if (L && L->next == L && L->prior == L)
		return TRUE;
	else
		return FALSE;
}

int ListLength_DuL(DuLinkList L) //返回L元素个数
{
	DuLinkList p;
	int count;
	if (L)
	{
		count = 0;
		p = L;
		while (p->next = L)
		{
			count++;
			p = p->next;
		}
	}
	return count;
}

Status GetElem_DuL(DuLinkList L, int i, LElemType_DC *e)	//用e接收L中第i个结点的元素值
{
	DuLinkList p;
	int count;
	if (L)
	{
		count = 1;
		p = L->next;
		while (p != L && count < i)
		{
			count++;
			p = p->next;
		}
		if (p != L)
		{
			*e = p->data;
			return OK;
		}
	}
	return ERROR;
}

int LocateElem_DuL(DuLinkList L, LElemType_DC e, Status(Compare)(LElemType_DC, LElemType_DC))	//返回L中第一个与e满足关系的元素序位
{
	DuLinkList p;
	int count;
	if (L)
	{
		count = 1;
		p = L->next;
		while (p != L && !Compare(e, p->data))
		{
			count++;
			p = p->next;
		}
		if (p != L)
			return count;
	}
	return 0;
}

Status PriorElem_DuL(DuLinkList L, LElemType_DC cur_e, LElemType_DC *pre_e) //用pre_e接收cur_e的前驱
{
	DuLinkList p;
	if (L)
	{
		p = L->next;
		while (p != L && p->data != cur_e)
			p = p->next;
		if (p != L &&p->prior != L)
		{
			*pre_e = p->prior->data;
			return OK;
		}
	}
	return ERROR;
}

Status NextElem_DuL(DuLinkList L, LElemType_DC cur_e, LElemType_DC *next_e)  //后继
{
	DuLinkList p;
	if (L)
	{
		p = L->next;
		while (p != L && p->data != cur_e)
			p = p->next;
		if (p != L &&p->prior != L)
		{
			*pre_e = p->next->data;
			return OK;
		}
	}
	return ERROR;
}

Status ListInsert_DuL(DuLinkList L, int i, LElemType_DC e) //插入
{
	DuLinkList p, s;
	if (i<1 || i>ListLength_DuL(L) + 1)
		return ERROR;
	p = GetElem_DuL(L, i);
	if (!p)
		p = L;
	s = (DuLinkList)malloc(sizeof(DuLNode));
	if (!s)
		exit(OVERFLOW);
	s->data = e;
	s->prior = p->prior;
	p->prior->next = s;
	s->next = p;
	p->prior = s;
	return OK;
}

Stuatus ListDelete_DuL(DuLinkList L, int i, LElemType_DC *e) //删除并接收
{
	DuLinkList p;
	if (!(p = GetElem_DuL(L, i)))
		return ERROR;
	*e = p->data;
	p->prior->next = p->next;
	p->next->prior = p->prior;
	free(p);
	p = NULL;
	return OK;
}

void ListTraverse_DuL(DuLinkList L, void(Visit)(LElemType_DC))	//遍历
{
	DuLinkList p;
	p = L->next;
	while (p != L)
	{
		Visit(p->data);
		p = p->next;
	}
}

