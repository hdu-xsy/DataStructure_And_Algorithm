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
typedef enum { unvisit, visit }VisitIf;
#define MAX_VERTEX_NUM 40
typedef          InfoType;
typedef struct EBox
{
	VisitIf mark;		//访问标记
	int ivex, jvex;		//两个顶点位置
	struct EBox *ilink, *jlink;	//两个顶点下一条边
	InfoType info;
}EBox;
typedef char VertexType_AML;
typedef struct VexNode
{
	VertexType_AML data;
	EBox *firstedge;
}VexBox;
typedef struct
{
	VexBox adjmulist[MAX_VERTEX_NUM + 1];	//表头向量
	int vexnum, edgenum;
	int IncInfo;
}AMLGraph;

Status visited[MAX_VERTEX_NUM + 1];
void(*VisitFunc)(VertexType_AML e);
