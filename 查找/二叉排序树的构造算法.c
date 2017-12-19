#include <stdio.h>
#include <stdlib.h>
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
typedef int KeyType;
typedef struct
{
	int key;
	float weight;
}ElemType_Search;
typedef struct
{
	ElemType_Search *elem;
	int length;
}SSTable;
typedef ElemType_Search BSTElemType;
typedef struct BSTNode
{
	BSTElemType data;
	struct BSTNode* lchild;
	struct BSTNode* rchild;
	union
	{
		int RTag;
	};
}BSTNode;
typedef BSTNode* BSTree;
BSTree SearchBST(BSTree BST, KeyType key,BSTree f,BSTree *p)
{
	if (!BST)
	{
		*p = f;
		return FALSE;
	}
	else if (EQ(key, BST->data.key))
	{
		*p = BST;
		return TRUE;
	}
	else if (LT(key, BST->data.key))
		return SearchBST(BST->lchild, key,BST,p);
	else
		return SearchBST(BST->rchild, key,BST,p);
}

Status InsertBST(BSTree *BST, BSTElemType e)
{
	BSTree p, s;
	if (!SearchBST(*BST, e.key, NULL, &p))
	{
		s = (BSTree)malloc(sizeof(BSTNode));
		s->data = e;
		s->lchild = s->rchild = NULL;
		if (!p)
			*BST = s;
		else if (LT(e.key, p->data.key))
			p->lchild = s;
		else
			p->rchild = s;
		return TRUE;
	}
	else
		return FALSE;
}
Status CreateBSTree(BSTree *BST, SSTable T)
{
	int i;
	*BST = NULL;
	if (T.length)
	{
		for (i = 1; i <= T.length; i++)
			InsertBST(BST, T.elem[i]);
	}
	return OK;
}
void InOrderTraverse_BST(BSTree BST, void(visit)(ElemType_Search))
{
	if (BST)
	{
		InOrderTraverse_BST(BST->lchild, visit);
		visit(BST->data);
		InOrderTraverse_BST(BST->rchild, visit);
	}
}
int Create(SSTable *T, int n)
{
	int i, a = 0;
	float b;
	T->elem = (ElemType_Search*)malloc((n + 1) * sizeof(ElemType_Search));
	if (!(T->elem))
		exit(OVERFLOW);
	(*T).length = n;
	for (i = 1; i <= n; i++)
	{
		scanf("%d", &a);
		(*T).elem[i].key = a;
	}
	return OK;
}
void PrintKey(ElemType_Search e)
{
	printf("%3d", e.key);
}
void Traverse(SSTable T, void(visit)(ElemType_Search))
{
	int i;
	for (i = 0; i < T.length; i++)
	{
		if (i && !(i % 10))
			printf("\n");
		visit(T.elem[i + 1]);
	}
	printf("\n");
}

void main()
{
	int Create(SSTable *T, int n);
	void Traverse(SSTable T, void(visit)(ElemType_Search));
	int Search_Bin(SSTable T, KeyType key);
	Status CreateBSTree(BSTree *BST, SSTable T);	
	void InOrderTraverse_BST(BSTree BST, void(visit)(ElemType_Search));
	SSTable T;	
	BSTree BST;
	int n, m = 0;
	printf("数组元素个数为:");
	scanf("%d", &n);
	printf("请依次输入数组元素:");
	Create(&T, n);
	Traverse(T, PrintKey);
	printf("\n");
	CreateBSTree(&BST, T);
	InOrderTraverse_BST(BST, PrintKey);
	printf("\n");
	system("pause");
	return 0;
}