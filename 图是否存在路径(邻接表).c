#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#pragma warning(disable:4996)

#define	OK			1
#define	ERROR		0
#define TRUE		1
#define FALSE		0
#define	OVERFLOW	-2
#define MAX_TREE_SIZE 100
typedef int Status;
#define MAX_VERTEX_NUM 20
int tag;
typedef struct
{
	int info;
}InfoType;

typedef struct ArcNode
{
	int adjvex;
	struct ArcNode *nextarc;
	InfoType Info;
}ArcNode;

typedef char VertexType;
typedef struct VNode
{
	VertexType data;
	ArcNode *firstarc;
}VNode;

typedef VNode AdjList[MAX_VERTEX_NUM + 1];
Status visited[MAX_VERTEX_NUM + 1];

typedef struct
{
	AdjList vertices;
	int vexnum, arcnum;
	int IncInfo;
}ALGraph;
void visit(char c)
{
	printf("%c", c);
}
int FirstAdjVex(ALGraph G, VertexType v)
{
	int k;
	ArcNode *p;
	k = LocateVex(G, v);
	if (k && G.vertices[k].firstarc)
		return G.vertices[k].firstarc->adjvex;
	return 0;
}
int NextAdjVex(ALGraph G, VertexType v, VertexType w)
{
	int k1, k2;
	ArcNode *p, *q;
	k1 = LocateVex(G, v);
	k2 = LocateVex(G, w);
	if (k1 && k2)
	{
		for (p = G.vertices[k1].firstarc; p; p = p->nextarc)
		{
			if (p->adjvex == k2)
			{
				if (p->nextarc)
					return p->nextarc->adjvex;
				else
					return 0;
			}
		}
	}
	return 0;
}
void DFS(ALGraph G, int i, int j)
{
	int w;
	for (w = FirstAdjVex(G, G.vertices[i].data); w; w = NextAdjVex(G, G.vertices[i].data, G.vertices[w].data))
	{
		if (tag)
			return;
		if (!visited[w])
		{
			visited[w] = TRUE;
			if (w == j)
				tag = TRUE;
			else
				DFS(G, w, j);
		}
	}
}
Status Algo(ALGraph G, int i, int j)
{
	int v, w;
	ArcNode *p;
	if (i == j)
	{
		printf("参数错误\n");
		return ERROR;
	}
	for (v = 1; v <= G.vexnum; v++)
		visited[v] = FALSE;
	tag = FALSE;
	visited[i] = TRUE;
	DFS(G, i, j);
	if (tag)
	{
		printf("%c 到 %c 之间有通路\n", G.vertices[i].data, G.vertices[j].data);
		return TRUE;
	}
	else
	{
		printf("%c 到 %c 之间无通路\n", G.vertices[i].data, G.vertices[j].data);
		return ERROR;
	}
}

Status CreateGraph(ALGraph *G)
{
	int i, j, k;
	char temp;
	VertexType v1, v2;
	ArcNode *p, *q;
	ArcNode *r[MAX_VERTEX_NUM + 1];
	printf("顶点数为:");
	scanf("%d", &((*G).vexnum));
	printf("边的数目为:");
	scanf("%d", &((*G).arcnum));
	printf("是否需要输入边的信息:(不含有则为0,含有为1)");
	scanf("%d", &((*G).IncInfo));
	printf("输入顶点集");
	scanf("%c", &temp);
	for (i = 1; i <= (*G).vexnum; i++)
	{
		scanf("%c", &((*G).vertices[i].data));
		(*G).vertices[i].firstarc = NULL;
		r[i] = NULL;
	}
	scanf("%c", &temp);
	printf("输入弧的集合");
	for (k = 1; k <= (*G).arcnum; k++)
	{
		scanf("%c%c", &v1, &v2);
		i = LocateVex(*G, v1);
		j = LocateVex(*G, v2);
		if (!i || !j) return ERROR;
		p = (ArcNode *)malloc(sizeof(ArcNode));
		if (!p) exit(OVERFLOW);
		p->adjvex = j;
		p->nextarc = NULL;
		if ((*G).IncInfo == 1)
		{
			printf("输入其它信息");
			scanf("%d", &(p->Info.info));
		}
		if (r[i] == NULL)
			(*G).vertices[i].firstarc = p;
		else
			r[i]->nextarc = p;
		r[i] = p;
		q = (ArcNode *)malloc(sizeof(ArcNode));
		if (!q)
			exit(OVERFLOW);
		q->adjvex = i;
		q->nextarc = NULL;
		if ((*G).IncInfo == 1)
			q->Info = p->Info;
		if (r[j] == NULL)
			(*G).vertices[j].firstarc = q;
		else
			r[j]->nextarc = q;
		r[j] = q;
	}
	return OK;
}

int LocateVex(ALGraph G, VertexType u)
{
	int i;
	for (i = 1; i <= G.vexnum; i++)
	{
		if (G.vertices[i].data == u)
			return i;
	}
	return 0;
}

void OutputGraph(ALGraph G)
{
	int i;
	ArcNode *p;
	if (!G.vexnum && !G.arcnum)
		printf("此图为空图");
	else
	{
		for (i = 1; i <= G.vexnum; i++)
		{
			printf("%c -- ", G.vertices[i].data);
			p = G.vertices[i].firstarc;
			while (p)
			{
				printf(" %c", G.vertices[p->adjvex].data);
				p = p->nextarc;
			}
			printf("\n");
		}
	}
}
int main()
{
	int vi, vj;
	ALGraph G;
	CreateGraph(&G);
	OutputGraph(G);
	printf("输入两个顶点");
	scanf("%d%d", &vi, &vj);
	Algo(G, vi, vj);
	system("pause");
	return 0;
}
