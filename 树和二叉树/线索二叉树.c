#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>
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
typedef char TElemType_Thr;
typedef enum { Link, Thread }PointerTag;	//Link=0����,Link=1����
typedef struct ThrBiNode
{
	TElemType_Thr data;
	struct ThrBiNode *lchild;
	struct ThrBiNode *rchild;
	//���ұ�־
	PointerTag LTag;
	PointerTag RTag;
	struct ThrBiNode *parent;
}ThrBiNode;
typedef ThrBiNode* ThrBiTree;
ThrBiTree pre;

Status CreateBiTree_Thr(ThrBiTree *T)
{
	//�������������δ��������
	TElemType_Thr ch;
	scanf("%c", &ch);
	if (ch == '#')
		*T = NULL;
	else
	{
		*T = (ThrBiTree)malloc(sizeof(ThrBiTree));
		if (!*T)
			exit(OVERFLOW);
		(*T)->data = ch;
		CreateBiTree_Thr(&(*T)->lchild);
		if ((*T)->lchild)
			(*T)->LTag = Link;
		else
			(*T)->LTag = Thread;
	}
	return OK;
}

void InThreading_Thr(ThrBiTree p)
{
	//����ȫ������
	if (p)
	{
		InTheading_Thr(p->lchild);
		if (!p->lchild)				//Ϊ��ǰ�������������ǰ������
		{
			p->LTag = Thread;
			p->lchild = pre;
		}
		if (!pre->rchild)			//Ϊ��һ����������������������
		{
			pre->RTag = Thread;
			pre->rchild = p;
		}
		pre = p;
		InThreading_Thr(p->rchild);
	}
}

Status InOrderThreading_Thr(ThrBiTree *Thrt, ThrBiTree T)
{
	//�������,ȫ������
	*Thrt = (ThrBiTree)malloc(sizeof(ThrBiNode));
	if (!*Thrt)
		exit(OVERFLOW);
	(*Thrt)->data = '\0';
	(*Thrt)->LTag = Link;
	(*Thrt)->RTag = Thread;
	(*Thrt)->rchild = *Thrt;
	if (!T)
		(*Thrt)->lchild = *Thrt;
	else
	{
		(*Thrt)->lchild = T;
		pre = *Thrt;
		InThreading_Thr(T);
		pre->rchild = *Thrt;		//���һ�����ָ��ͷ���
		pre->RTag = Thread;			//���һ�����������
		(*Thrt)->rchild = pre;		//ͷ���ָ�����һ�����
	}
	return OK;
}

Status InOrderTraverse_Thr(ThrBiTree Thrt, void(Visit)(TElemType_Thr))
{
	//��������ǵݹ�
	ThrBiTree p = Thrt->lchild;
	while (p != Thrt)
	{
		while (p->LTag == Link)
			p = p->lchild;
		Visit(p->data);
		while (p->RTag == Thread && p->rchild != Thrt)
		{
			p = p->rchild;
			Visit(p->data);
		}
		p = p->rchild;
	}
	return OK;
}