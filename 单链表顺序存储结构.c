#define SEQUENCELIST_H

#include <stdio.h>
#include <stdlib.h>
#define STATUS_H

/* ״̬�� */
#define	TRUE		1			//��
#define	FALSE		0			//��
#define YES			1			//��
#define NO          0			//��
#define	OK			1			//ͨ��
#define	ERROR		0			//����
#define SUCCESS		1			//�ɹ�
#define UNSUCCESS	0			//ʧ��
#define	INFEASIBLE	-1			//������


#define	OVERFLOW	-2			//��ջ����
#define UNDERFLOW	-3			//��ջ����

#define NULL ((void*)0)

typedef int Status;

#define LIST_INIT_SIZE 100				//˳���洢�ռ�ĳ�ʼ������
#define LISTINCREMENT  10				//˳���洢�ռ�ķ�������


#define LELEMTYPE_SQ
typedef int LElemType_Sq;


typedef struct
{
	LElemType_Sq *elem;					//�洢�ռ��ַ��ָ���һ������ָ�룩
	int length;							//��ǰ˳�����
	int listsize;						//��ǰ����Ĵ洢����
}SqList;								//˳���0�ŵ�Ԫ����ʹ��

/* ˳������б� */
Status InitList_Sq(SqList *L)//��ʼ����˳���L
{
(*L).elem = (LElemType_Sq*)malloc(LIST_INIT_SIZE*sizeof(LElemType_Sq));
if(!(*L).elem)
  exit(OVERFLOW); 				//�����ڴ�ʧ��

(*L).length = 0;					//��ʼ��˳�����Ϊ0
(*L).listsize = LIST_INIT_SIZE;		//˳����ʼ�ڴ������

return OK;							//��ʼ���ɹ�
}

void ClearList_Sq(SqList *L)//���˳���L
{
	(*L).length = 0;
}

void DestroyList_Sq(SqList *L)//����˳���L
{
	free((*L).elem);

	(*L).elem = NULL;					//�ͷ��ڴ���ÿ�ָ��
	(*L).length = 0;
	(*L).listsize = 0;
}

Status ListEmpty_Sq(SqList L)//�ж�˳���L�Ƿ�Ϊ��
{
	return 	L.length==0 ? TRUE : FALSE;
}

int ListLength_Sq(SqList L)//����˳���L��Ԫ�ظ���
{
	return L.length;
}

Status GetElem_Sq(SqList L, int i, LElemType_Sq *e)//��e����˳���L�е�i��Ԫ��
{
	if(i<1 || i>L.length)
		return ERROR;					//iֵ���Ϸ�
	else
		*e = L.elem[i-1];

	return OK;
}


int LocateElem_Sq(SqList L, LElemType_Sq e, Status(Compare)(LElemType_Sq, LElemType_Sq))//����˳���L���׸���e����Compare��ϵ��Ԫ��λ��
{
	int i = 1;							//i�ĳ�ֵΪ��һ��Ԫ�ص�λ��

	while(i<=L.length && !Compare(e, L.elem[i-1]))
		++i;

	if(i<=L.length)
		return i;
	else
		return 0;
}

Status PriorElem_Sq(SqList L, LElemType_Sq cur_e, LElemType_Sq *pre_e)//��pre_e����cur_e��ǰ��
{
	int i = 1;

	if(L.elem[0]!=cur_e)				//��һ�������ǰ��
	{
		while(i<L.length && L.elem[i]!=cur_e)
			++i;

		if(i<L.length)
		{
			*pre_e = L.elem[i-1];
			return OK;
		}
	}

	return ERROR;
}

Status NextElem_Sq(SqList L, LElemType_Sq cur_e, LElemType_Sq *next_e)//��next_e����cur_e�ĺ��
{
	int i = 0;

	while(i<L.length && L.elem[i]!=cur_e)
		++i;

	if(i<L.length-1)					//���һ������޺��
	{
		*next_e = L.elem[i+1];
		return OK;
	}

	return ERROR;
}

Status ListInsert_Sq(SqList *L, int i, LElemType_Sq e)//��˳���L�ĵ�i��λ���ϲ���e
{
	LElemType_Sq *newbase;
	LElemType_Sq *p, *q;

	if(i<1 || i>(*L).length+1)
		return ERROR;					//iֵ���Ϸ�

	if((*L).length >= (*L).listsize)	//���洢�ռ��������迪���¿ռ�
	{
		newbase = (LElemType_Sq*)realloc((*L).elem, ((*L).listsize+LISTINCREMENT)*sizeof(LElemType_Sq));
		if(!newbase)
			exit(OVERFLOW);

		(*L).elem = newbase;
		(*L).listsize += LISTINCREMENT;
	}

	q = &(*L).elem[i-1];				//qΪ����λ��

	for(p=&(*L).elem[(*L).length-1]; p>=q; --p)
		*(p+1) = *p;					//����λ�ü�֮���Ԫ������

	*q = e;								//����e
	(*L).length++;						//����1

	return OK;
}

Status ListDelete_Sq(SqList *L, int i, LElemType_Sq *e)//ɾ��˳���L�ϵ�i��λ�õ�Ԫ�أ�����e����
{
	LElemType_Sq *p, *q;

	if(i<1 || i>(*L).length)
		return ERROR;					//iֵ���Ϸ�

	p = &(*L).elem[i-1];				//pΪ��ɾ��Ԫ�ص�λ��
	*e = *p;
	q = (*L).elem+(*L).length-1; 		//��βԪ��λ��

	for(++p; p<=q; ++p)
		*(p-1) = *p;					//��ɾԪ��֮���Ԫ������

	(*L).length--;						//����1

	return OK;
}


Status ListTraverse_Sq(SqList L, void (Visit)(LElemType_Sq))//��visit��������˳���L
{
	int i;

	for(i=0; i<L.length; i++)
		Visit(L.elem[i]);

	return OK;
}
