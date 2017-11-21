#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#pragma warning(disable:4996)

#define	OK			1
#define	ERROR		0
#define TRUE		1
#define FALSE		0
#define	OVERFLOW	-2
typedef int Status;
#define MAX_VERTEX_NUM 20
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

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

typedef struct
{
	int *base;
	int *top;
	int stacksize;
}SqStack;

Status InitStack_Sq(SqStack *S)
{
	(*S).base = (int *)malloc(STACK_INIT_SIZE * sizeof(int));
	if (!(*S).base)	exit(OVERFLOW);
	(*S).top = (*S).base;
	(*S).stacksize = STACK_INIT_SIZE;
	return OK;
}

Status Push(SqStack *S, int e)
{
	if ((*S).top - (*S).base >= (*S).stacksize)
	{
		(*S).base = (int *)realloc((*S).base, ((*S).stacksize + STACKINCREMENT) * sizeof(int));
		if (!(*S).base) exit(OVERFLOW);
		(*S).top = (*S).base + (*S).stacksize;
		(*S).stacksize += STACKINCREMENT;
	}
	*(S->top) = e;
	(S->top)++;
	return OK;
}

Status Pop(SqStack *S, int *e)
{
	if ((*S).top == (*S).base)	return ERROR;
	(*S).top--;
	*e = *((*S).top);
	return OK;
}

Status StackEmpty(SqStack S)
{
	if (S.top == S.base)
		return TRUE;
	else
		return ERROR;
}

void FindInDegree(ALGraph G, int indegree[MAX_VERTEX_NUM + 1])
{
	int i;
	ArcNode *p;
	for (i = 1; i <= G.vexnum; i++)
		indegree[i] = 0;
	for (i = 1; i <= G.vexnum; i++)
	{
		p = G.vertices[i].firstarc;
		while (p)
		{
			indegree[p->adjvex]++;
			p = p->nextarc;
		}
	}
}
Status TopologicalSort(ALGraph G, int Topo[])
{
	SqStack S;
	ArcNode *p;
	int i, k, count, indegree[MAX_VERTEX_NUM + 1];
	FindInDegree(G, indegree);
	InitStack_Sq(&S);
	for (i = 1; i <= G.vexnum; i++)
	{
		if (!indegree[i])
			Push(&S, i);
	}
	count = 0;
	while (!StackEmpty(S))
	{
		Pop(&S, &i);
		count++;
		Topo[count] = i;
		for (p = G.vertices[i].firstarc; p; p = p->nextarc)
		{
			k = p->adjvex;
			if (!(--indegree[k]))
				Push(&S, k);
		}
	}
	if (count < G.vexnum)
		return ERROR;
	else
		return OK;
}



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
	ALGraph G;
	CreateGraph(&G);
	OutputGraph(G);
	printf("拓扑排序\n");
	int k, Topo[MAX_VERTEX_NUM + 1];
	if (!TopologicalSort(G, Topo))
		printf("该有向图有回路\n");
	else
	{
		printf("该有向图的拓扑序列为:\n");
		for (k = 1; k <= G.vexnum; k++)
			printf("%c", G.vertices[Topo[k]].data);
	}
	system("pause");
	return 0;
}
