#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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

#define MAX_TREE_SIZE 100
typedef char TElemType_Sq;
typedef TElemType_Sq SqBiTree[MAX_TREE_SIZE];

typedef struct
{
	int level;	//结点所在层
	int order;	//结点在本层序号
}Position;

void InitBiTree_Sq(SqBiTree T)
{
	//构造空二叉树T
	int i;
	for (i = 0; i < MAX_TREE_SIZE; i++)
		T[i] = '\0';//空树无结点
}

void ClearBiTree_Sq(SqBiTree T)
{
	//清空二叉树T
	int i;
	for (i = 0; i < MAX_TREE_SIZE; i++)
		T[i] = '\0';
}

void DestroyBiTree_Sq(SqBiTree T)
{
	//摧毁二叉树T
	//二叉树无法销毁
}

void BiTreeEmpty_Sq(SqBiTree T)
{
	//判断二叉树是否为空
	return T[0] == '\0' ? TRUE : FALSE;
}

void CreateBiTree_Le_Sq(SqBiTree T)
{
	//按层序序列构造二叉树
	char ch;
	int i = 0;
	while (scanf("%c", &ch) == 1 && ch != '\n')
	{
		if (ch == '^')
			T[i++] = '\0';
		else
			T[i++] = ch;
	}
	return OK;
}

void CreateBiTree_Pre_Sq(SqBiTree T)
{
	//按先序序列构造二叉树
	char ch;
	scanf("%c", &ch);
	if (ch == '^')
		T[i] = '\0';
	else
	{
		T[i] = ch;
		CreateBiTree_Pre_Sq(T, 2 * i + 1);
		CreateBiTree_Pre_Sq(T, 2 * i + 2);
	}
	return OK;
}

void BiTreeLength_Sq(SqBiTree T)
{
	//返回二叉树长度
	int len;
	for (len = MAX_TREE_SIZE; len - 1 >= 0; len--)
	{
		if (T[len - 1] != '\0')
			break;
	}
	return len;
}

void BiTreeDepth_Sq(SqBiTree T)
{
	//返回二叉树深度
	int level = 0;
	while ((int)pow(2, level) - 1 < BiTreeLength_Sq(T))
		level++;
	return level;
}

Status Root_Sq(SqBiTree T, TElemType_Sq *e)
{
	//返回二叉树的根
	if (BiTreeEmpty_Sq(T))
		return ERROR;
	*e = T[0];
	return OK;
}

TElemType_Sq Value_Sq(SqBiTree T, Position s)
{
	//返回结点值
	int i = (int)pow(2, s.level - 1) + s.order - 2;
	return T[i];
}

Status Assign_Sq(SqBiTree T, Position s, TElemType_Sq value)
{
	//赋值
	int i = (int)pow(2, s.level - 1) + s.order - 2;
	if (value == '\0' && (T[2 * i + 1] != '\0' || T[2 * i + 2] != '\0'))
		return ERROR;
	else if (value != '\0' && T[(i + 1) / 2 - 1] == '\0')
		return ERROR;
	else
		T[i] = value;
	return OK;
}

TElemType_Sq Parent_Sq(SqBiTree T, TElemType_Sq e)
{
	//返回某节点的双亲结点值
	int i;
	if (T[0] != '\0')
	{
		for (i = 0; i < MAX_TREE_SIZE; i++)
		{
			if (T[i] == e)
				return T[(i + 1) / 2 - 1];
		}
	}
	return '\0';
}

TElemType_Sq LeftChild_Sq(SqBiTree T, TElemType_Sq e)
{
	//返回某结点的左孩子结点值
	int i;
	if (T[0] == '\0')
		return '\0';
	for (i = 0; i < MAX_TREE_SIZE; i++)
	{
		if (T[i] == e)
			return T[2 * i + 1];
	}
	return '\0';
}

TElemType_Sq RightSibling_Sq(SqBiTree T, TElemType_Sq)
{
	//返回某结点的右兄弟结点值
	int i;
	if (T[0] == '\0')
		return '\0';
	for (i = 0; i < MAX_TREE_SIZE; i++)
	{
		if (i % 2 != 0 && T[i] == e)
				return T[i + 1];
	}
	return '\0';
}

TElemType_Sq LevelOrderTraverse_Sq(SqBiTree T, void(Visit)(TElemType_Sq))
{
	//层序遍历二叉树
	int i;
	int len = BiTreeLength_Sq(T);
	for (i = 0; i < len; i++)
	{
		if (T[i] != '\0')
			Visit(T[i]);
	}
}

void PreOrderTraverse_Sq(SqBiTree T, void(Visit)(TElemType_Sq), int i)
{
	//前序遍历二叉树
	if (T[i] != '\0')
	{
		Visit(T[i]);
		PreOrderTraverse_Sq(T, Visit, 2 * i + 1);
		PreOrderTraverse_Sq(T, Visit, 2 * i + 2);
	}
}

void InOrderTraverse_Sq(SqBiTree T, void(Visit)(TElemType_Sq), int i)
{
	//中序遍历二叉树
	if (T[i] != '\0')
	{
		InOrderTraverse_Sq(T, Visit, 2 * i + 1);
		Visit(T[i]);
		InOrderTraverse_Sq(T, Visit, 2 * i + 2);
	}
}

void PostOrderTraverse_Sq(SqBiTree T, void(Visit)(TElemType_Sq), int i)
{
	//后序遍历二叉树
	if (T[i] != '\0')
	{
		PostOrderTraverse_Sq(T, Visit, 2 * i + 1);
		PostOrderTraverse_Sq(T, Visit, 2 * i + 2);
		Visit(T[i]);
	}
}

void Print_Sq(SqBiTree T)
{
	//打印树
	int i, j, level;
	char tmp[MAX_TREE_SIZE][MAX_TREE_SIZE] = {};
	level = BiTreeDepth_Sq(T);
	for (i = 1; i <= level; i++)
		for (j = 1; j <= (int)pow(2, i - 1); j++)
			tmp[i - 1](int)pow(2, level - i) + (j - 1)*(int)pow(2, level - i + 1) - 1] = T[(int)pow(2, i - 1) - 1 + j - 1];
	for (i = 0; i < level; i++)
	{
		for (j = 0; j < 2 * (int)pow(2, level - 1) - 1; j++)
		{
			if (tmp[i][j] != '\0')
				printf("%c", tmp[i][j]);
			else
				printf(" ");
		}
		printf("\n");
	}
}