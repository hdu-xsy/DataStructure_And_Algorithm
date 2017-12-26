#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>
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

#define MAX_TREE_SIZE 100
typedef char TElemType_P;
typedef struct PTNode
{
	TElemType_P data;
	int parent;			//双亲位置域
}PTNode;
typedef struct
{
	PTNode nodes[MAX_TREE_SIZE];
	int n;				//结点数
}PTree;
