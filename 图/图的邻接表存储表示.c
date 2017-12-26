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

#define INFINITY INT_MAX
#define MAX_VERTEX_NUM 40
typedef enum { DG, UDG }GraphKind;
typedef struct
{
	int info;
}InfoType;

typedef struct ArcNode
{
	int adjvex;					//顶点序号
	struct ArcNode *nextarc;	//指向下一条弧指针
	InfoType Info;
}ArcNode;
typedef char VertexType_AL;
typedef struct VNode
{
	VertexType_AL data;
	ArcNode *firstarc;
}VNode;
typedef VNode AdjList[MAX_VERTEX_NUM + 1];
typedef struct
{
	AdjList vertices;
	int vexnum, arcnum;
	int IncInfo;
	GraphKind kind;
}ALGraph;
Status visited[MAX_VERTEX_NUM + 1];
void(*VisitFunc)(VertexType_AL e);

Status CreateGraph(ALGraph *G)
{
	scanf("%d", &((*G).kind));
	switch ((*G).kind)
	{
	case DG:
		return CreateDG_AL(G);
	case UDG:
		return CreateUDG_AL(G);
	default:
		return ERROR;
	}
}

Status CreateDG_AL(ALGraph *G)
{
	//有向图
	int i, j, k;
	char temp;
	VertexType_AL v1, v2;
	ArcNode *p;
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
		i = LocateVex_AL(*G, v1);
		j = LocateVex_AL(*G, v2);
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
	}
	return OK;
}

Status CreateUDG_AL(ALGraph *G)
{
	//无向图
	int i, j, k;
	char temp;
	VertexType_AL v1, v2;
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
		i = LocateVex_AL(*G, v1);
		j = LocateVex_AL(*G, v2);
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

int LocateVex_AL(ALGraph G, VertexType_AL u)
{
	//寻找顶点的位置
	int i;
	for (i = 1; i <= G.vexnum; i++)
	{
		if (G.vertices[i].data == u)
			return i;
	}
	return 0;
}

int FirstAdjVex_AL(ALGraph G, VertexType_AL v)
{
	//第一个邻接顶点序号
	int k;
	ArcNode *p;
	k = LocateVex_AL(G, v);
	if (k && G.vertices[k].firstarc)
		return G.vertices[k].firstarc->adjvex;
	return 0;
}

int NextAdjVex_AL(ALGraph G, VertexType_AL v, VertexType_AL w)
{
	//下一个邻接顶点序号
	int k1, k2;
	ArcNode *p, *q;
	k1 = LocateVex_AL(G, v);
	k2 = LocateVex_AL(G, w);
	if (k1 && k2)
	{
		for (p = G.vertices[k1].firstarc; p; p->nextarc)
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

void DFSTraverse_AL(ALGraph G, void(Visit)(VertexType_AL))
{
	//深度优先遍历
	int v;
	VisitFunc = Visit;
	for (v = 1; v <= G.vexnum; v++)
		visited[v] = FALSE;
	for (v = 1; v <= G.vexnum; v++)
	{
		if (!visited[v])
			DFS_AL(G, v);
	}
}

void DFS_AL(ALGraph G, int v)
{
	//深度优先遍历函数
	int w;
	visited[v] = TRUE;
	VisitFunc(G.vertices[v].data);
	for (w = FirstAdjVex_AL(G, G.vertices[v].data); w; w = NextAdjVex_AL(G, G.vertices[v].data, G.vertices[w].data))
	{
		if (!visited[w])
			DFS_AL(G, w);
	}
}

void OutputALGraph(ALGraph G)
{
	//输出图
	int i, j;
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

