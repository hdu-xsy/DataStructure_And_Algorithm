#include <stdio.h>
#include <stdlib.h>
#include "./单链表链式存储.c"
#include "./单链表顺序存储结构.c"
#define	OK			1
#define	ERROR		0
#define	OVERFLOW	-2
#define TRUE		1
#define FALSE		0
#define NULL		((void*)0) 
typedef int Status;

void MergeList_L(LinkList La, LinkList *Lb, LinkList *Lc)
{
	LinkList pa, pb, pc;
	pa = La->next;
	pb = (*Lb)->next;
	pc = (*Lc) = La;
	while (pa && pb)
	{
		if (pa->data <= pb->data)
		{
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}
		else
		{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}
	pc->next = pa ? pa : pb;
	free(*Lb);
	*Lb = NULL;
}
