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
typedef enum { Link, Thread }PointerTag;	//Link=0孩子,Link=1线索
typedef struct ThrBiNode
{
	TElemType_Thr data;
	struct ThrBiNode *lchild;
	struct ThrBiNode *rchild;
	//左右标志
	PointerTag LTag;
	PointerTag RTag;
	struct ThrBiNode *parent;
}ThrBiNode;
typedef ThrBiNode* ThrBiTree;
ThrBiTree pre;

Status CreateBiTree_Thr(ThrBiTree *T)
{
	//先序构造二叉树（未线索化）
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
	//中序全线索化
	if (p)
	{
		InTheading_Thr(p->lchild);
		if (!p->lchild)				//为当前结点左子树建立前驱线索
		{
			p->LTag = Thread;
			p->lchild = pre;
		}
		if (!pre->rchild)			//为上一个结点右子树建立后继线索
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
	//中序遍历,全线索化
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
		pre->rchild = *Thrt;		//最后一个结点指向头结点
		pre->RTag = Thread;			//最后一个结点线索化
		(*Thrt)->rchild = pre;		//头结点指向最后一个结点
	}
	return OK;
}

Status InOrderTraverse_Thr(ThrBiTree Thrt, void(Visit)(TElemType_Thr))
{
	//中序遍历非递归
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