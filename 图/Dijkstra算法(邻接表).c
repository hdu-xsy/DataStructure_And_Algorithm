#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define	OK			1
#define	ERROR		0
#define	OVERFLOW	-2
#define MAX_TREE_SIZE 100
typedef int Status;
#define MAX_VERTEX_NUM 20

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

typedef struct
{
	AdjList vertices;
	int vexnum, arcnum;
	int IncInfo;
}ALGraph;

Status CreateGraph(ALGraph *G)
{
	int i, j, k;
	char temp;
	VertexType v1, v2;
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
	char *temp2='\0';
	for (k = 1; k <= (*G).arcnum; k++)
	{
		scanf("%c%c", &v1, &v2);
		getchar(temp2);
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
			getchar(temp2);
		}
		if (r[i] == NULL)
			(*G).vertices[i].firstarc = p;
		else
			r[i]->nextarc = p;
		r[i] = p;
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
int GetInfo(ALGraph G, int i, int j)
{
	ArcNode *r;
	r = G.vertices[i].firstarc;
	while (r && r->adjvex != j)
		r = r->nextarc;
	if (r && r->adjvex == j)
		return r->Info.info;
	return INT_MAX;
}

void Dijkstra(ALGraph G,int v0,int path[],int dist[])
{
	int set[MAX_VERTEX_NUM + 1];
	int min, i, j, v, k;
	int tmp[MAX_VERTEX_NUM + 1];
	for (i = 1; i <= G.vexnum; i++)
	{
		dist[i] = GetInfo(G, v0, i);
		set[i] = 0;
		if (GetInfo(G, v0, i) < INT_MAX)
			path[i] = v0;
		else
			path[i] = -1;
	}
	set[v0] = 1;
	path[v0] = -1;
	for (i = 1; i <= G.vexnum; i++)
	{
		min = INT_MAX;
		for (j = 1; j <= G.vexnum; j++)
		{
			if (!set[j] && dist[j]<min)
			{
				v = j;
				min = dist[j];
			}
		}
		set[v] = 1;
		for (j = 1; j <= G.vexnum; j++)
		{
			if (!set[j] && min < INT_MAX && GetInfo(G, v, j) < INT_MAX && (min + GetInfo(G, v, j)) < dist[j])
			{
				dist[j] = min + GetInfo(G, v, j);
				path[j] = v;
			}
		}
	}
	for (i = 1; i <= G.vexnum; i++)
	{
		if (v0 != i)
		{
			printf("%c到%c的路径为：", G.vertices[v0].data, G.vertices[i].data);
			if (path[i] == -1)
				printf("X");
			else
			{
				tmp[0] = 0;
				if (v0 != i)
				{
					k = i;
					do
					{
						tmp[0]++;
						tmp[tmp[0]] = k;
						k = path[k];
					} while (path[k] != -1);
				}
				printf("%c", G.vertices[v0].data);
				if (tmp[0])
				{
					for (j = tmp[0]; j >= 1; j--)
						printf("%c", G.vertices[tmp[j]].data);
				}
			}
			printf(",权长为：");
			if (dist[i] == INT_MAX)
				printf("∞\n");
			else
				printf("%2d\n", dist[i]);
		}
	}
}

void main()
{
	Status CreateGraph(ALGraph *G);
	void OutputGraph(ALGraph G);
	void Dijkstra(ALGraph G, int v0, int path[], int dist[]);
	ALGraph G;
	int path[MAX_VERTEX_NUM + 1];
	int dist[MAX_VERTEX_NUM + 1];
	int v0 = 1;
	CreateGraph(&G);
	OutputGraph(G);
	printf("%c到其余各点的最短路径\n", G.vertices[v0].data);
	Dijkstra(G, v0, path, dist);
	printf("\n");
	system("pause");
}
