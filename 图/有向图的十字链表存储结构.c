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

#define MAX_VERTEX_NUM 40
typedef          InfoType;
typedef struct ArcBox
{
	int tailvex, headvex;	//尾顶点和头顶点位置
	struct ArcBox *hlink, *tLink;//弧头相同和弧尾相同的弧的链域
	InfoType info;
}ArcBox;
typedef char VertexType_OL;
typedef struct VexNode
{
	VertexType_OL data;
	ArcBox *firstin, *firstout;		//该定点第一条入弧和出弧
}VexNode;
typedef struct
{
	VexNode xlist[MAX_VERTEX_NUM + 1];
	int vexnum, arcnum;
	int IncInfo;
}OLGraph;

Status visited[MAX_VERTEX_NUM + 1];
void(*VisitFunc)(VertexType_OL e);

Status CreateDG_OL(OLGraph *G)
{
	int i, j, k;
	VertexType_OL v1, v2;
	char tmp;
	ArcBox *p;
	printf("依次输入顶点数 弧数 是否存在边信息");
	scanf("%d%d%d", &((*G).vexnum), &((*G).arcnum), &((*G).IncInfo));
	printf("依次输入各个顶点");
	for (i = 1; i <= (*G).vexnum; i++)
	{
		scanf("%c", &((*G).xlist[i].data));
		(*G).xlist[i].firstin = NULL;
		(*G).xlist[i].firstout = NULL;
	}
	scanf("%c", &tmp);
	for (k = 1; k <= (*G).arcnum; k++)
	{
		scanf("%c%c", &v1, &v2);
		i = LocateVex_OL(*G, v1);
		j = LocateVex_OL(*G, v2);
		if (!i || !j)
			return ERROR;
		p = (ArcBox *)malloc(sizeof(ArcBox));
		if (!p)
			exit(OVERFLOW);
		p->tailvex = i;
		p->headvex = j;
		p->hlink = (*G).xlist[j].firstin;
		(*G).xlist[j].firstin = p;
		p->tLink = (*G).xlist[i].firstout;
		(*G).xlist[i].firstout = p;
		if ((*G).IncInfo == 1)
			Input(&p->info);
	}
	return OK;
}

int LocateVex_OL(OLGraph G, VertexType_OL u)
{
	int i;
	for (i = 1; i <= G.vexnum; i++)
	{
		if (G.xlist[i].data == u)
			return i;
	}
	return 0;
}