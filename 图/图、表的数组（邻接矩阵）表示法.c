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
#include "../栈和队列/队列的链式存储.c"
typedef enum {
	DG, DN, UDG, UDN
}GraphKind;
typedef int VRType;
typedef     InfoType;
typedef struct ArcCell
{
	VRType adj;		//	权值,无权图中表示是否相邻
	InfoType info;
}ArcCell;
typedef ArcCell AdjMatrix[MAX_VERTEX_NUM + 1][MAX_VERTEX_NUM + 1];//邻接矩阵
typedef char VertexType_M;
typedef struct
{
	VertexType_M vexs[MAX_VERTEX_NUM + 1];	//顶点向量
	AdjMatrix arcs;							//邻接矩阵
	int vexnum, arcnum;						//图、表的当前顶点树和弧数
	int IncInfo;							//弧是否包含信息
	GraphKind kind;
}MGraph;
Status visited[MAX_VERTEX_NUM + 1];
void(*VisitFunc)(VertexType_M e);

Status CreateGraph_M(MGraph *G)
{
	//创建图表
	scanf("%d", &((*G).kind));
	switch ((*G).kind)
	{
	case DG:
		return CreateDG_M(G);
	case DN:
		return CreateDN_M(G);
	case UDG:
		return CreateUDG_M(G);
	case UDN:
		return CreateUDN_M(G);
	default:
		return ERROR;
	}
}

Status CreateDG_M(MGraph *G)
{
	//构造有向图
	int i, j, k;
	VertexType_M v1, v2;
	char tmp;
	printf("依次输入顶点数 弧数 是否存在边信息");
	scanf("%d%d%d", &((*G).vexnum), &((*G).arcnum), &((*G).IncInfo));
	printf("依次输入各个顶点");
	for (i = 1; i <= (*G).vexnum; i++)
		scanf("%c", &((*G).vexs[i]));
	scanf("%c", &tmp);
	for (i = 1; i <= G->vexnum; i++)
	{
		for (j = 1; i <= (*G).vexnum; j++)
			(*G).arcs[i][j].adj = 0;
	}
	for (k = 1; k <= (*G).arcnum; k++)
	{
		printf("依次输入各个边");
		scanf("%c%c", &v1, &v2);
		i = LocateVex_M(*G, v1);
		j = LocateVex_M(*G, v2);
		if (!i || !j)
			return ERROR;
		(*G).arcs[i][j].adj = 1;
		if ((*G).IncInfo == 1)
			Input(&((*G).arcs[i][j].info));
	}
	return OK;
}

Status CreateDN_M(MGraph *G)
{
	//构造有向网
	int i, j, k;
	VertexType_M v1, v2;
	char tmp;
	VRType w;
	printf("依次输入顶点数 弧数 是否存在边信息");
	scanf("%d%d%d", &((*G).vexnum), &((*G).arcnum), &((*G).IncInfo));
	printf("依次输入各个顶点");
	for (i = 1; i <= (*G).vexnum; i++)
		scanf("%c", &((*G).vexs[i]));
	scanf("%c", &tmp);
	for (i = 1; i <= G->vexnum; i++)
	{
		for (j = 1; i <= (*G).vexnum; j++)
			(*G).arcs[i][j].adj = INFINITY;
	}
	for (k = 1; k <= (*G).arcnum; k++)
	{
		printf("依次输入各个边和权值");
		scanf("%c%c%d", &v1, &v2, &w);
		i = LocateVex_M(*G, v1);
		j = LocateVex_M(*G, v2);
		if (!i || !j)
			return ERROR;
		(*G).arcs[i][j].adj = w;
		if ((*G).IncInfo == 1)
			Input(&((*G).arcs[i][j].info));
	}
	return OK;
}

Status CreateUDG_M(MGraph *G)
{
	//构造无向图
	int i, j, k;
	VertexType_M v1, v2;
	char tmp;
	printf("依次输入顶点数 弧数 是否存在边信息");
	scanf("%d%d%d", &((*G).vexnum), &((*G).arcnum), &((*G).IncInfo));
	printf("依次输入各个顶点");
	for (i = 1; i <= (*G).vexnum; i++)
		scanf("%c", &((*G).vexs[i]));
	scanf("%c", &tmp);
	for (i = 1; i <= G->vexnum; i++)
	{
		for (j = 1; i <= (*G).vexnum; j++)
			(*G).arcs[i][j].adj = 0;
	}
	for (k = 1; k <= (*G).arcnum; k++)
	{
		printf("依次输入各个边");
		scanf("%c%c", &v1, &v2);
		i = LocateVex_M(*G, v1);
		j = LocateVex_M(*G, v2);
		if (!i || !j)
			return ERROR;
		(*G).arcs[i][j].adj = 1;
		if ((*G).IncInfo == 1)
			Input(&((*G).arcs[i][j].info));
		(*G).arcs[j][i] = (*G).arcs[i][j];
	}
	return OK;
}

Status CreateUDN_M(MGraph *G)
{
	//构造无向网
	int i, j, k;
	VertexType_M v1, v2;
	char tmp;
	VRType w;
	printf("依次输入顶点数 弧数 是否存在边信息");
	scanf("%d%d%d", &((*G).vexnum), &((*G).arcnum), &((*G).IncInfo));
	printf("依次输入各个顶点");
	for (i = 1; i <= (*G).vexnum; i++)
		scanf("%c", &((*G).vexs[i]));
	scanf("%c", &tmp);
	for (i = 1; i <= G->vexnum; i++)
	{
		for (j = 1; i <= (*G).vexnum; j++)
			(*G).arcs[i][j].adj = INFINITY;
	}
	for (k = 1; k <= (*G).arcnum; k++)
	{
		printf("依次输入各个边和权值");
		scanf("%c%c%d", &v1, &v2, &w);
		i = LocateVex_M(*G, v1);
		j = LocateVex_M(*G, v2);
		if (!i || !j)
			return ERROR;
		(*G).arcs[i][j].adj = w;
		if ((*G).IncInfo == 1)
			Input(&((*G).arcs[i][j].info));
		(*G).arcs[j][i] = (*G).arcs[i][j];
	}
	return OK;
}

int LovateVex_M(MGraph G, VertexType_M u)
{
	//寻找顶点位置
	int i;
	for (i = 1; i <= G.vexnum; i++)
	{
		if (G.vexs[i] == u)
			return i;
	}
	return 0;
}

VertexType_M GetVex_M(MGraph G, int order)
{
	//返回值
	if (order >= 1 && order <= G.vexnum)
		return G.vexs[order];
	else
		return '\0';
}

int FirstAdjVex_M(MGraph G, VertexType_M v)
{
	//返回v的第一个邻接顶点序号
	int k, j, t;
	k = LovateVex_M(G, v);
	if (k)
	{
		if (G.kind % 2)
			t = INFINITY;
		else
			t = 0;
		for (j = 1; j <= G.vexnum; j++)
		{
			if (G.arcs[k][j].adj != t)
				return j;
		}
	}
	return 0;
}

int NextAdjVex_M(MGraph G, VertexType_M v, VertexType_M w)
{
	//返回v相对于w的下一个邻接顶点序号
	int k1, k2, j, t;
	k1 = LocateVex_M(G, v);
	k2 = LocateVex_M(G, w);
	if (k1&&k2)
	{
		if (G.kind % 2)
			t = INFINITY;
		else
			t = 0;
		for (j = k2 + 1; j <= G.vexnum; j++)
		{
			if (G.arcs[k1][j].adj != t)
				return j;
		}
	}
	return 0;
}

void DFSTraverse_M(MGraph G, void(Visit)(VertexType_M))
{
	//深度优先遍历
	int v;
	VisitFunc = Visit;
	for (v = 1; v <= G.vexnum; v++)
		visited[v] = FALSE;
	for (v = 1; v <= G.vexnum; v++)
	{
		if (!visited[v])
			DFS_M(G, v);
	}
}

void DFS_M(MGraph G, int v)
{
	//深度优先遍历函数
	int w;
	visited[v] = TRUE;
	VisitFunc(G.vexs[v]);
	for (w = FirstAdjVex_M(G, G.vexs[v]); w; w = NextAdjVex_M(G, G.vexs[v], G.vexs[w]))
	{
		if (!visited[w])
			DFS_M(G, w);
	}
}

void BFSTraverse_M(MGraph G, void(Visit)(VertexType_M))
{
	//广度优先遍历
	int v, w;
	LinkQueue Q;
	QElemType_L e;
	for (v = 1; v <= G.vexnum; v++)
		visited[v] = FALSE;
	InitQueue_L(&Q);
	for (v = 1; v <= G.vexnum; v++)
	{
		if (!visited[v])
		{
			visited[v] = TRUE;
			Visit(G.vexs[v]);
			EnQueue_L(&Q, v);
			while (!QueueEmpty_L(Q))
			{
				DeQueue_L(&Q, &e);
				for (w = FirstAdjVex_M(G, G.vexs[e]); w; w = NextAdjVex_M(G, G.vexs[e], G.vexs[w]))
				{
					if (!visited[w])
					{
						visited[w] = TRUE;
						Visit(G.vexs[w]);
						EnQueue_L(&Q, w);
					}
				}
			}
		}
	}
}