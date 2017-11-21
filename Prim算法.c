#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define	OK			1
#define TRUE        1
#define	ERROR		0
#define	OVERFLOW	-2
#define MAX_VERTEX_NUM 20
typedef int Status;
typedef struct
{
	int info;
}InfoType;
typedef int VRType;
typedef struct ArcCell
{
	VRType adj;
	InfoType info;
}ArcCell;
typedef ArcCell AdjMatrix[MAX_VERTEX_NUM + 1][MAX_VERTEX_NUM + 1];
typedef struct
{
	char vexs[MAX_VERTEX_NUM + 1];
	AdjMatrix arcs;
	int vexnum, arcnum;
	int IncInfo;
}MGraph;

typedef struct
{
	char adjvex;
	VRType lowcost;
}Edge;
typedef struct
{
	int a, b;
	int w;
}EdgeSetType;

int LocateVex(MGraph G, char u)
{
	int i;
	for (i = 1; i <= G.vexnum; i++)
	{
		if (G.vexs[i] == u)
			return i;
	}
	return 0;
}
Status CreateUND(MGraph *G)
{
	int i, j, k;
	char v1, v2;
	VRType w;
	char tmp;
	printf("顶点数为:");
	scanf("%d", &((*G).vexnum));
	printf("边的数目为:");
	scanf("%d", &((*G).arcnum));
	printf("是否需要输入边的信息:(不含有则为0,含有为1)");
	scanf("%d", &((*G).IncInfo));
	printf("输入顶点集");
	scanf("%c", &tmp);
	for (i = 1; i <= (*G).vexnum; i++)
		scanf("%c", &((*G).vexs[i]));
	scanf("%c", &tmp);
	for (i = 1; i <= (*G).vexnum; i++)
	{
		for (j = 1; j <= (*G).vexnum; j++)
			(*G).arcs[i][j].adj = INT_MAX;
	}
	printf("输入弧的集合");
	for (k = 1; k <= G->arcnum; k++)
	{
		scanf("%c%c", &v1, &v2);
		getchar(tmp);
		i = LocateVex(*G, v1);
		j = LocateVex(*G, v2);
		if (!i || !j) return ERROR;
		printf("输入权值");
		scanf("%d", &((*G).arcs[i][j].adj));
		getchar(tmp);
		if((*G).IncInfo == 1)
			scanf("%d", &((*G).arcs[i][j].info));
		(*G).arcs[j][i] = (*G).arcs[i][j];
	}
	return OK;
}

void OutputMGraph(MGraph G)
{
	int i, j;
	if (!G.vexnum && !G.arcnum)
		printf("空表");
	else
	{
		printf(" ");
		for (i = 1; i <= G.vexnum; i++)
			printf("%4c", G.vexs[i]);
		printf("\n\n");
		for (i = 1; i <= G.vexnum; i++)
		{
			printf("%c", G.vexs[i]);
			for (j = 1; j <= G.vexnum; j++)
			{
				if (G.arcs[i][j].adj == INT_MAX)
					printf("%4s","max");
				else
					printf("%4d", G.arcs[i][j]);
			}
			printf("\n\n");
		}
	}
}

int Minimum(Edge closedge[], int n)
{
	int i, j;
	int min = INT_MAX;
	for (i = 1,j = 0; i <= n; i++)
	{
		if (closedge[i].lowcost)
		{
			if (closedge[i].lowcost <= min)
			{
				min = closedge[i].lowcost;
				j = i;
			}
		}
	}
	return j;
}

void MinSpanTree(MGraph G,char u)
{
	int i, j, k;
	Edge closedge[21];
	k = LocateVex(G, u);
	for (j = 1; j <= G.vexnum; j++)
	{
		if (j != k)
		{
			closedge[j].adjvex = u;
			closedge[j].lowcost = G.arcs[k][j].adj;
		}
	}
	closedge[k].lowcost = 0;
	printf("   %c\n", u);
	for (i = 1; i <= G.vexnum-1; i++)
	{
		k = Minimum(closedge, G.vexnum);
		printf("%2d,%c\n", closedge[k].lowcost, G.vexs[k]);
		closedge[k].lowcost = 0;
		for (j = 1; j <= G.vexnum; j++)
		{
			if (G.arcs[k][j].adj < closedge[j].lowcost)
			{
				closedge[j].adjvex = G.vexs[k];
				closedge[j].lowcost = G.arcs[k][j].adj;
			}
		}
	}
}

void main()
{
	Status CreateUND(MGraph *G);
	void OutputMGraph(MGraph G);
	MGraph G;
	CreateUND(&G);
	OutputMGraph(G);
	printf("prim算法:\n");
	printf("先后加入最小生成树的各结点及其对应的最小编的权值分别为：\n");
	MinSpanTree(G,'A');
	system("pause");
}
