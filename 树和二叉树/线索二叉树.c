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
typedef char TElemType_Thr;
typedef enum { Link, Thread }PointerTag;	//Link=0孩子,Link=1线索
typedef struct ThrBiNode
{
	TElemType_Thr data;
	struct ThrBiNode *lchild;
	struct ThrBiNode *rchild;
	//左右标志
	PointerTag LTag;
	PointerTag RTag;
	struct ThrBiNode *parent;
}ThrBiNode;
typedef ThrBiNode* ThrBiTree;
ThrBiTree pre;