#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define	OK			1
#define TRUE        1
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

int Create(SSTable *T,int n)
{
	int i, a=0;
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

int Search_Bin(SSTable T, KeyType key)
{
	int low, high, mid;
	low = 1;
	high = T.length;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (EQ(key, T.elem[mid].key))
			return mid;
		else if (LT(key, T.elem[mid].key))
			high = mid - 1;
		else
			low = mid + 1;
	}
	return 0;
}

void main()
{
	int Create(SSTable *T, int n);
	void Traverse(SSTable T, void(visit)(ElemType_Search));
	int Search_Bin(SSTable T, KeyType key);
	int n,m=0;
	printf("查找表中元素个数为:");
	scanf("%d", &n);
	SSTable T;
	Create(&T,n);
	Traverse(T, PrintKey);
	printf("\n");
	printf("要查找的元素");
	scanf("%d", &m);
	printf("%d\n",Search_Bin(T, m));
	system("pause");
	return 0;
}