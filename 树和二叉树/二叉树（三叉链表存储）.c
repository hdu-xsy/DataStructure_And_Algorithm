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

typedef char TElemType_Tri;
typedef struct TBiTNode
{
	TElemType_Tri data;
	struct TBiTNode* patent;	
	//�ڶ������Ķ�������洢�ṹ��������һ��parent��ָ��˫�׽��
	struct TBiTNode *lchild;
	struct TBiTNode *rchild;
}TBiNode;
typedef TBiTNode* TBiTree;
typedef TBiTree QElemType_L;