#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

#include "../串/顺序串.c"
typedef enum { Atom, List }ElemTag;
typedef char AtomType;
typedef struct GLNode
{
	ElemTag tag;
	union
	{
		AtomType atom;
		struct GLNode *hp;
	}Union;
	struct GLNode *tp;
}GLNode;
typedef GLNode* GList;

void InitGList_GL_E(GList *L)
{
	//初始化广义表
}

void sever_GL_E(SString hstr, SString str)
{
	//将空串str分割成两部分,hsub为第一个','之前的子串，str为之后的子串

}

void CreateGList_GL_E(GList *L, SString S)
{
	//由S创建广义表
}

void ClearGList_GL_E(GList *L)
{
	//清空广义表
}

void CopyGList_GL_E(GList *T, GList L)
{
	//复制广义表
}

int GListLength_GL_E(GList L)
{
	//求广义表长度
}

int GListDepth_GL_E(GList L)
{
	//求广义表深度
}

Status GListEmpty_GL_E(GList L)
{
	//判断广义表是否为空
}

GList GetHead_GL_E(GList L)
{
	//获取表头
}

GList GetTail_GL_E(GList L)
{
	//获取表尾
}

void InsertFirst_GL_E(GList *L, GList e)
{
	//插入e
}

void DeleteFirst_GL_E(GList *L, GList *e)
{
	//删除表头并用e返回
}

void Traverse_GL_E(GList L, void(Visit)(AtomType))
{
	//遍历
}