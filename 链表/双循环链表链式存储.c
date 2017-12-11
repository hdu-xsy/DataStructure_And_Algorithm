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

Status InitList_DuL(DuLinkList *L) //��ʼ��˫����L
{
	*L = (DuLinkList)malloc(sizeof(DuLNode));
	if (!(*L))
		exit(OVERFLOW);
	(*L)->next = (*L)->prior = *L;
	return OK;
}

Status ClearList_DuL(DuLinkList L) //�ÿ�L
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

void DestroyList_DuL(DuLinkList *L) //����L
{
	ClearList_DuL(*L);
	free(*L);
	*L = NULL;
}

Status ListEmpty_Dul(DuLinkList L) //�ж�L�Ƿ�Ϊ��
{
	if (L && L->next == L && L->prior == L)
		return TRUE;
	else
		return FALSE;
}

int ListLength_DuL(DuLinkList L) //����LԪ�ظ���
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

Status GetElem_DuL(DuLinkList L, int i, LElemType_DC *e)	//��e����L�е�i������Ԫ��ֵ
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

int LocateElem_DuL(DuLinkList L, LElemType_DC e, Status(Compare)(LElemType_DC, LElemType_DC))	//����L�е�һ����e�����ϵ��Ԫ����λ
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

Status PriorElem_DuL(DuLinkList L, LElemType_DC cur_e, LElemType_DC *pre_e) //��pre_e����cur_e��ǰ��
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

Status NextElem_DuL(DuLinkList L, LElemType_DC cur_e, LElemType_DC *next_e)  //���
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

Status ListInsert_DuL(DuLinkList L, int i, LElemType_DC e) //����
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

Stuatus ListDelete_DuL(DuLinkList L, int i, LElemType_DC *e) //ɾ��������
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

void ListTraverse_DuL(DuLinkList L, void(Visit)(LElemType_DC))	//����
{
	DuLinkList p;
	p = L->next;
	while (p != L)
	{
		Visit(p->data);
		p = p->next;
	}
}

