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
typedef char TElemType_C;
typedef struct CTNode
{
	int child;
	struct CTNode* next;
}CTNode;
typedef CTNode* ChildPtr;
typedef struct
{
	int parent;
	TElemType_C data;
	ChildPtr firstchild;	//孩子链表头指针
}CTBox;
typedef struct
{
	CTBox nodes[MAX_TREE_SIZE];
	int r; //根的位置
	int n; //根的结点数
}CTree;
