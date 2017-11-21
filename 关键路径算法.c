#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define	OK			1
#define TRUE        1
#define	ERROR		0
#define	OVERFLOW	-2
#define MAX_TREE_SIZE 100
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

int path[MAX_VERTEX_NUM + 1][MAX_VERTEX_NUM + 1];
int step;
SqStack S;

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

void DFS(ALGraph G, int w)
{
	ArcNode *r;
	int e;
	int *p;
	int count;
	Push(&S, w);
	for (r = G.vertices[w].firstarc; r; r = r->nextarc)
	{
		step += r->Info.info;
		DFS(G, r->adjvex);
		step -= r->Info.info;
	}
	if (!r)
	{
		if (G.vertices[w].firstarc == NULL)
		{
			path[0][0]++;
			path[path[0][0]][0] = step;
			for (p = S.base, count = 1; p < S.top; p++, count++)
				path[path[0][0]][count] = *p;
		}
		Pop(&S, &e);
	}
}

int FindOrigin(ALGraph G)
{
	int k;
	ArcNode *r;
	int mark[21];
	for (k = 1; k <= G.vexnum; k++)
		mark[k] = 0;
	for (k = 1; k <= G.vexnum; k++)
	{
		r = G.vertices[k].firstarc;
		while (r)
		{
			mark[r->adjvex] = 1;
			r = r->nextarc;
		}
	}
	for (k = 1; k <= G.vexnum; k++)
	{
		if (!mark[k])
			return k;
	}
	return 0;
}

void CMP(ALGraph G)
{
	int i, j, start;
	int max = 0;
	for (i = 0; i <= G.vexnum; i++)
	{
		for (j = 0; j <= G.vexnum; j++)
			path[i][j] = 0;
	}
	step = 0;
	start = FindOrigin(G);
	InitStack_Sq(&S);
	DFS(G, start);
	for (i = 1; i <= path[0][0]; i++)
	{
		if (path[i][0] > max)
			max = path[i][0];
	}
	for (i = 1; i <= path[0][0]; i++)
	{
		if (path[i][0] == max)
		{
			for (j = 1; path[i][j] && j <= MAX_VERTEX_NUM; j++)
				printf("%c", G.vertices[path[i][j]].data);
			printf("\n");
		}
	}
}

void main()
{
	Status CreateGraph(ALGraph *G);
	void OutputGraph(ALGraph G);
	ALGraph G;
	CreateGraph(&G);
	OutputGraph(G);
	printf("关键路径为:");
	CMP(G);
	printf("\n");
	system("pause");
}
