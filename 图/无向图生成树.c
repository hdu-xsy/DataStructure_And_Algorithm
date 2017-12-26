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

#include "../树和二叉树/树的二叉链表(孩子-兄弟)存储表示.c"
#include "../图/图、表的数组（邻接矩阵）表示法.c"

void DFSForest(MGraph G, CSTree *T)
{
	//无向图生成树
	int v;
	CSTree p, q;
	InitTree_CS(T);
	for (v = 1; v <= G.vexnum; v++)
		visited[v] = FALSE;
	for (v = 1; v <= G.vexnum; v++)
	{
		if (!visited[v])
		{
			p = (CSTree)malloc(sizeof(CSNode));
			if (!p)
				exit(OVERFLOW);
			p->data = GetVex_M(G, v);
			p->firstchild = p->nextsibling = NULL;
			if (!(*T))
				*T = p;
			else
				q->nextsibling = p;
			q = p;
			DFSTree(G, v, &p);
		}
	}
}

void DFSTree(MGraph G, int v, CSTree *T)
{
	//结点v起始的树
	Status first;
	int w;
	CSTree p, q;
	visited[v] = TRUE;
	first = TRUE;
	for (w = FirstAdjVex_M(G, G.vexs[v]); w; w = NextAdjVex_M(G, G.vexs[v], G.vexs[w]))
	{
		if (!visited[w])
		{
			p = (CSTree)malloc(sizeof(CSNode));
			if (!p)
				exit(OVERFLOW);
			p->data = GetVex_M(G, w);
			p->firstchild = p->nextsibling = NULL;
			if (first)
			{
				(*T)->firstchild = p;
				first = FALSE;
			}
			else
				q->nextsibling = p;
			q = p;
			DFSTree(G, w, &q);
		}
	}
}
