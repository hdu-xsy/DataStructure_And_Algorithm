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
#include "../../git/data-structure/ջ�Ͷ���/ջ��˳��洢.c"
typedef char TElemType;
typedef struct BiTNode {
	TElemType data;			//���Ԫ��
	struct BiTNode *lchild; //����ָ��
	struct BiTNode *rchild;	//�Һ���ָ��
}BiTNode;					//���������
typedef BiTNode* BiTree;	//ָ�����������ָ��
typedef struct
{
	BiTree left;			//ָ�������ָ��
	BiTree right;
	int n;					//��ǰ���Ĵ���
}Node;
typedef BiTree SElemType_Sq;
void InitBiTree(BiTree *T)
{
	//��ʼ��������
	*T = NULL;
}

void ClearBiTree(BiTree *T)
{
	//��ն�����
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
	//�ж϶������Ƿ�Ϊ��
	return T == NULL ? TRUE : ERROR;
}

void DestroyBiTree(BiTree *T)
{
	//���ٶ�����
	//�������޷�������
}

Status CreateBiTree(BiTree T)
{
	//�������й���������
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
	//���ض���������
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
	//���ض��������
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
	//��e���ض������ĸ��ڵ�ֵ
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
	//���ؽ��ֵ
	return p->data;
}

void Assign(BiTree p, TElemType value)
{
	//Ϊĳ�ڵ㸳ֵ,pΪ���ָ��
	p->data = value;
}

TElemType Parent(BiTree T, TElemType e)
{
	//����ĳ����˫�׵Ľ��ֵ
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
	//����ĳ�����Һ��ӽ��ֵ
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
	//����ĳ�������ֵܽ��ֵ
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
	//��ȡָ����e��ָ��
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
	//��T0����T��Ϊ���e������
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
	//ɾ��e������������������
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
	//�������������
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
	//������������� �ݹ�
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
	//������� �ǵݹ�
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

