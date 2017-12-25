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
#include "../../git/data-structure/栈和队列/栈的顺序存储.c"
typedef char TElemType;
typedef struct BiTNode {
	TElemType data;			//结点元素
	struct BiTNode *lchild; //左孩子指针
	struct BiTNode *rchild;	//右孩子指针
}BiTNode;					//二叉树结点
typedef BiTNode* BiTree;	//指向二叉树结点的指针
typedef struct
{
	BiTree left;			//指向结点的左指针
	BiTree right;
	int n;					//当前结点的次序
}Node;
typedef BiTree SElemType_Sq;
void InitBiTree(BiTree *T)
{
	//初始化二叉树
	*T = NULL;
}

void ClearBiTree(BiTree *T)
{
	//清空二叉树
	if (*T)
	{
		if ((*T)->lchild)
			ClearBiTree(&((*T)->lchild));
		if ((*T)->rchild)
			ClearBiTree(&((*T)->rchild));
		free(*T);
		*T = NULL;
	}
}
Status BiTreeEmpty(BiTree T)
{
	//判断二叉树是否为空
	return T == NULL ? TRUE : ERROR;
}

void DestroyBiTree(BiTree *T)
{
	//销毁二叉树
	//二叉树无法被销毁
}

Status CreateBiTree(BiTree T)
{
	//先序序列构建二叉树
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
	return OK;
}

int BiTreeLength(BiTree T)
{
	//返回二叉树长度
	Node node[100];
	int i, len;
	i = len = 0;
	if (T)
	{
		node[i].left = T->lchild;
		node[i].right = T->rchild;
		node[i].n = 1;
		if (node[i].n > len)
			len = node[i].n;
		while (i >= 0)
		{
			while (node[i].left)
			{
				node[i + 1].left = node[i].left->lchild;
				node[i + 1].right = node[i].right->rchild;
				node[i + 1].n = 2 * node[i].n;
				node[i].left = NULL;
				i++;
				if (node[i].n > len)
					len = node[i].n;
			}
			if (node[i].right)
			{
				node[i + 1].left = node[i].right->lchild;
				node[i + 1].right = node[i].right->rchild;
				node[i + 1].n = 2 * node[i].n + 1;
				node[i].right = NULL;
				i++;
				if (node[i].n > len)
					len = node[i].n;
			}
			if (node[i].right)
			{
				node[i + 1].left = node[i].right->lchild;
				node[i + 1].right = node[i].right->rchild;
				node[i + 1].n = 2 * node[i].n + 1;
				node[i].right = NULL;
				i++;
				if (node[i].n > len)
					len = node[i].n;
			}
			if (node[i].left == NULL && node[i].right == NULL)
				i--;
		}
	}
	return len;
}

int BiTreeDepth(BiTree T)
{
	//返回二叉树深度
	int LD, RD;
	if (T == NULL)
	{
		return 0;
	}
	else
	{
		LD = BiTreeDepth(T->lchild);
		RD = BiTreeDepth(T->rchild);
		return (LD >= RD ? LD : RD) + 1;
	}
}

Status Root(BiTree T, TElemType *e)
{
	//用e返回二叉树的根节点值
	if (!T)
		return ERROR;
	else
	{
		*e = T->data;
		return OK;
	}
}

TElemType Value(BiTree p)
{
	//返回结点值
	return p->data;
}

void Assign(BiTree p, TElemType value)
{
	//为某节点赋值,p为结点指针
	p->data = value;
}

TElemType Parent(BiTree T, TElemType e)
{
	//返回某结点的双亲的结点值
	BiTNode node[100];
	int i = 0;
	if (T == NULL || (T != NULL && e == T->data))
		return '\0';
	node[i] = *T;
	while (i >= 0)
	{
		while (node[i].lchild)
		{
			if (node[i].lchild->data == e)
				return node[i].data;
			node[i + 1] = *(node[i].lchild);
			node[i].lchild = NULL;
			i++;
		}
		if (node[i].rchild)
		{
			if (node[i].rchild->data == e)
				return node[i].data;
			node[i + 1] = *(node[i].rchild);
			node[i].rchild = NULL;
			i++;
		}
		if (node[i].lchild == NULL && node[i].rchild == NULL)
			i--;
	}
	if (i < 0)
		return '\0';
}

TElemType RightChild(BiTree T, TElemType e)
{
	//返回某结点的右孩子结点值
	BiTNode node[100];
	int i = 0;
	if (!T)
		return '\0';
	node[i] = *T;
	while (i >= 0)
	{
		while (node[i].data != e && node[i].lchild)
		{
			node[i + 1] = *(node[i].lchild);
			node[i].lchild = NULL;
			i++;
		}
		if (node[i].data == e)
		{
			if (node[i].rchild)
				return node[i].rchild->data;
			else
				return '\0';
		}
		if (node[i].rchild)
		{
			node[i + 1] = *(node[i].rchild);
			node[i].rchild = NULL;
			i++;
		}
		if (node[i].lchild == NULL && node[i].rchild == NULL)
			i--;
	}
	if (i < 0)
		return '\0';
}

TElemType LeftSibling(BiTree T, TElemType e)
{
	//返回某结点的左兄弟结点值
	BiTNode node[100];
	int i = 0;
	if (T == NULL || (T != NULL&&e == T->data))
		return '\0';
	node[i] = *T;
	while (i >= 0)
	{
		while (node[i].rchild)
		{
			if (node[i].rchild->data == e)
			{
				if (node[i].lchild)
					return node[i].lchild->data;
				else
					return '\0';
			}
			node[i + 1] = *(node[i].rchild);
			node[i].rchild = NULL;
			i++;
		}
		if (node[i].lchild)
		{
			if (node[i].lchild->data == e)
				return '\0';
			node[i + 1] = *(node[i].lchild);
			node[i].lchild = NULL;
			i++;
		}
		if (node[i].lchild == NULL && node[i].rchild == NULL)
			i--;
	}
	if (i < 0)
		return '\0';
}


BiTree LocatedBiTree(BiTree T, TElemType e)
{
	//获取指向结点e的指针
	BiTNode node[100];
	int i = 0;
	if (T == NULL)
		return NULL;
	if (T->data == e)
		return T;
	node[i] = *T;
	while (i >= 0)
	{
		while (node[i].lchild)
		{
			if (node[i].lchild->data == e)
				return node[i].lchild;
			node[i + 1] = *(node[i].lchild);
			node[i].lchild = NULL;
			i++;
		}
		if (node[i].rchild)
		{
			if (node[i].rchild->data == e)
				return node[i].rchild;
			node[i + 1] = *(node[i].rchild);
			node[i].rchild = NULL;
			i++;
		}
		if (node[i].lchild == NULL && node[i].rchild == NULL)
			i--;
	}
	if (i < 0)
		return NULL;
}

Status InsertBiTree(BiTree T, TElemType e, BiTree T0, int LR)
{
	//将T0插入T成为结点e的子树
	BiTree p = LocatedBiTree(T, e);
	if (p)
	{
		T0->rchild = LR ? p->rchild : p->lchild;
		LR ? (p->rchild = T0) : (p->lchild = T0);
		return OK;
	}
	return ERROR;
}

Status DeleteBiTree(BiTree T, TElemType e, int LR)
{
	//删除e结点的左子树或右子树
	BiTree p = LocatedBiTree(T, e);
	if (p)
	{
		LR ? ClearBiTree(&(p->rchild)) : ClearBiTree(&(p->lchild));
		return OK;
	}
	return ERROR;
}

void LevelOrderTraverse(BiTree T, void(Visit)(TElemType))
{
	//层序遍历二叉树
	int i, j;
	BiTree p[100];
	i = j = 0;
	if (T)
		p[j++] = T;
	while (i < j)
	{
		Visit(p[i]->data);
		if (p[i]->lchild)
			p[j++] = p[i]->lchild;
		if (p[i]->lchild)
			p[j++] = p[i]->rchild;
		i++;
	}
}

Status PreOrderTraverse(BiTree T, Status(Visit)(TElemType))
{
	//先序遍历二叉树 递归
	if (T)
	{
		if (Visit(T->data))
		{
			PreOrderTraverse(T->lchild, Visit);
			PreOrderTraverse(T->rchild, Visit);
		}
		return OK;
	}
	else
		return ERROR;
}

Status InOrderTraverse(BiTree T, Status(*Visit)(TElemType e))
{
	//中序遍历 非递归
	SqStack S;
	SElemType_Sq p;
	InitStack(&S);
	Push_Sq(&S, T);
	while (p || !StackEmpty(S))
	{
		if (p)
		{
			Push_Sq(&S, p);
			p = p->lchild;
		}
		else
		{
			Pop_Sq(&S, &p);
			if (!Visit(p->data))
				return ERROR;
			p = p->rchild;
		}
	}
	return OK;
}

Status Visit(TElemType e) {
	if (e == '\0') {
		return ERROR;
	}
	else {
		printf("%c", e);
	}
	return OK;
}



int main()
{
	Status CreateBiTree(BiTree T);
	Status Visit(TElemType e);
	BiTree T = NULL;
	Status(*visit)(TElemType e) = Visit;
	T = CreateBiTree(T);
	InOrderTraverse(T, visit);
	system("pause");
	return 0;
}

