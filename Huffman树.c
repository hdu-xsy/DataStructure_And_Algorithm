#include <stdio.h>
#include <stdlib.h>

#define	OK			1
#define	ERROR		0
#define	OVERFLOW	-2
#define MAX_TREE_SIZE 100
typedef int Status;

typedef struct
{
	unsigned int weight;
	unsigned int parent;
	unsigned int lchild;
	unsigned int rchild;
}HTNode;
typedef HTNode *HuffmanTree;

void InitTree_HT(HuffmanTree *HT)
{
	*HT = NULL;
}

void CreateHuffmanTree_HT(HuffmanTree *HT)
{
	int m, n;
	int w[MAX_TREE_SIZE];
	HuffmanTree p;
	int s1, s2;
	printf("哈夫曼树叶子节点个数:");
	scanf("%d", &n);
	printf("各叶子节点权值:");
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &w[i]);
	}
	m = 2 * n - 1;
	*HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));
	if (!(*HT)) exit(OVERFLOW);
	(*HT)[0].weight = n;
	for (int i = 1; i <= m; i++)
	{
		if (i <= n)
			(*HT)[i].weight = w[i];
		else
			(*HT)[i].weight = 0;
		(*HT)[i].parent = 0;
		(*HT)[i].lchild = 0;
		(*HT)[i].rchild = 0;
	}
	for (int i = n + 1; i <= m; i++)
	{
		Select_HT(*HT, i - 1, &s1, &s2);
		(*HT)[s1].parent = (*HT)[s2].parent = i;
		(*HT)[i].lchild = s1;
		(*HT)[i].rchild = s2;
		(*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;
	}
	return OK;
}

Status Select_HT(HuffmanTree HT, int end, int *order_1, int *order_2)
{
	HuffmanTree p;
	int i, count;
	int m, n, temp;
	if (end < 2) return ERROR;
	for (i = 1, count = 1; i <= end; i++)
	{
		if (HT[i].parent == 0)
		{
			if (count == 1) m = i;
			if (count == 2) n = i;
			count++;
		}
		if (count > 2)	break;
	}
	if (HT[m].weight > HT[n].weight)
	{
		temp = n;
		n = m;
		m = temp;
	}
	i = (m > n ? m : n) + 1;
	while (i <= end)
	{
		if (HT[i].parent == 0)
		{
			if (HT[i].weight < HT[m].weight)
			{
				n = m;
				m = i;
			}
			else
			{
				if (HT[i].weight >= HT[m].weight &&HT[i].weight < HT[n].weight)
					n = i;
			}
		}
		i++;
	}
	*order_1 = HT[m].weight <= HT[n].weight ? m : n;
	*order_2 = HT[m].weight > HT[n].weight ? m : n;
	return OK;
}

void ShowHuffmanTree_HT(HuffmanTree HT)
{
	printf("order  weight  parent  lchild  rchild\n");
	for (int i = 0; i < 2 * HT[0].weight; i++)
	{
		if (i == 0)
			printf("%4d %7d\n", i, HT[i].weight);
		else
			printf("%4d %7d %7d %7d %7d\n", i, HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);
	}
}

void WPL(HuffmanTree HT)
{
	int wpl=0;
	int n = HT[0].weight;
	int N;
	for (int i = 1; i <= n; i++)
	{
		if (HT[i].parent % 2 == 0)
		{
			N = (2 * n + 2 - HT[i].parent) / 2;
		}
		else
		{
			N = (2 * n + 1 - HT[i].parent) / 2;
		}
		wpl += HT[i].weight * N;
	}
	printf("WPL:%d\n", wpl);
}

void main()
{
	void CreateHuffmanTree_HT(HuffmanTree *HT);
	void InitTree_HT(HuffmanTree *HT);
	void ShowHuffmanTree_HT(HuffmanTree HT);
	void WPL(HuffmanTree HT);
	HuffmanTree HT;
	InitTree_HT(&HT);
	CreateHuffmanTree_HT(&HT);
	ShowHuffmanTree_HT(HT);
	WPL(HT);
	system("pause");
}
