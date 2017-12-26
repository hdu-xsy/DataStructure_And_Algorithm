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

typedef char TElemType_CS;
typedef struct CSNode
{
	TElemType_CS data;
	struct CSNode* firstchild;	//ָ����
	struct CSNode* nextsibling;	//ָ���ֵ�
}CSNode;
typedef CSNode* CSTree;
typedef CSTree SElemType_Sq;

void InitTree_CS(CSTree *T)
{
	//�������T
	*T = NULL;
}

Status TreeEmpty_CS(CSTree T)
{
	//�ж����Ƿ�Ϊ��
	return T == NULL ? TRUE : ERROR;
}

Status CreateTree_CS(CSTree *T)
{
	//�������й�����
	char ch;
	scanf("%c", &ch);
	if (ch == '#')
		*T = NULL;
	else
	{
		*T = (CSTree)malloc(sizeof(CSNode));
		if (!(*T))
			exit(OVERFLOW);
		(*T)->data = ch;
		CreateTree_CS(&(*T)->firstchild);
		CreateTree_CS(&(*T)->nextsibling);
	}
	return OK;
}

void LevelOrderTraverse_CS(CSTree T, void(Visit)(TElemType_CS))
{
	//�������
	int i, j;
	CSTree Q[100];
	i = j = 0;
	if (T)
		Q[j++] = T;
	while (i < j)
	{
		while (Q[i])
		{
			Visit(Q[i]->data);
			if (Q[i]->firstchild)
				Q[j++] = Q[i]->firstchild;
			Q[i] = Q[i]->nextsibling;
		}
		i++;
	}
}

void PreOrderTraverse_CS(CSTree T, void(Visit)(TElemType_CS))
{
	//�������
	if (T)
	{
		Visit(T->data);
		PreOrderTraverse_CS(T->firstchild, Visit);
		PreOrderTraverse_CS(T->nextsibling, Visit);
	}
}
