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
typedef enum{Head,Tail}Mark;
typedef enum {Atom,List}ElemTag;
typedef char AtomType;
typedef struct GLNode
{
	union { int mark; };
	ElemTag tag;
	union
	{
		AtomType atom;
		struct
		{
			struct GLNode *hp;
			struct GLNode *tp;
		}ptr;
	}Union;
}GLNode;
typedef GLNode* GList;

void InitGList_GL_H_T(GList *L)
{
	//初始化广义表
	*L = NULL;
}

void sever_GL_H_T(SString hstr, SString str)
{
	//将空串str分割成两部分,hsub为第一个','之前的子串，str为之后的子串
	int i, k, n;
	SString ch;
	n = strLength_Sq(str);
	i = k = 0;
	do
	{
		++i;
		SubString_Sq(ch, str, i, 1);
		if (ch[1] == '(')
			++k;
		if (ch[1] == ')')
			--k;
	} while (i < n && (ch[1] != ',' || k != 0));
	if (i < n)
	{
		SubString_Sq(hstr, str, 1, i - 1);
		SubString_Sq(str, str, i + 1, n - 1);
	}
	else
	{
		StrCopy_Sq(hstr, str);
		ClearString_Sq(str);
	}
}

void CreateGList_GL_H_T(GList *L, SString S)
{
	//由S创建广义表
	SString emp, hsub, sub;
	GList p, q;
	StrAssign_Sq(emp, "()");
	if (!StrCompare_Sq(S, emp))
		*L = NULL;
	else
	{
		*L = (GList)malloc(sizeof(GLNode));
		if (!*L)
			exit(OVERFLOW);
		if (StrLength_Sq(S) == 1)
		{
			(*L)->tag = Atom;
			(*L)->Union.atom = S[1];
			(*L)->mark = 0;
		}
		else
		{
			(*L)->tag = List;
			(*L)->mark = 0;
			p = *L;
			SubString_Sq(sub, S, 2, StrLength_Sq(S) - 2);
			do
			{
				sever_GL_H_T(hsub, sub);
				CreateGList_GL_H_T(&(p->Union.ptr.hp), hsub);
				q = p;
				if (!StrEmpty_Sq(sub))
				{
					p = (GList)malloc(sizeof(GLNode));
					if (!p)
						exit(OVERFLOW);
					p->tag = List;
					p->mark = 0;
					q->Union.ptr.tp = p;
				}
			} while (!StrEmpty_Sq(sub));
			q->Union.ptr.tp = NULL;
		}
	}
}

void ClearGList_GL_H_T(GList *L)
{
	//清空广义表
	GList p, q;
	if (*L)
	{
		if ((*L)->tag == Atom)
		{
			free(*L);
			*L = NULL;
		}
		else
		{
			p = (*L)->Union.ptr.hp;
			q = (*L)->Union.ptr.tp;
			free(*L);
			*L = NULL;
			ClearGList_GL_H_T(&p);
			ClearGList_GL_H_T(*q);
		}
	}
}

void CopyGList_GL_H_T(GList *T, GList L)
{
	//复制广义表
	if (!L)
		*T = NULL;
	else
	{
		*T = (GList)malloc(sizeof(GLNode));
		if (!*T)
			exit(OVERFLOW);
		(*T)->tag = L->tag;
		if (L->tag == Atom)
			(*T)->Union.atom = L->Union.atom;
		else
		{
			CopyGList_GL_H_T(&((*T)->Union.ptr.hp), L->Union.ptr.hp);
			CopyGList_GL_H_T(&((*T)->Union.ptr.tp), L->Union.ptr.tp);
		}
	}
}

int GListLength_GL_H_T(GList L)
{
	//求广义表长度
	int count;
	for (count = 0; L; count++, L = L->Union.ptr.tp);
	return count;
}

int GListDepth_GL_H_T(GList L)
{
	//求广义表深度
	int max, deep;
	GList p;
	if (!L)
		return 1;
	if (L->tag = Atom)
		return 0;
	for (max = 0, p = L; p; p = p->Union.ptr.hp)
	{
		deep = GListDepth_GL_H_T(p->Union.ptr.hp);
		if (depp > max)
			max = deep;
	}
	return max + 1;
}

Status GListEmpty_GL_H_T(GList L)
{
	//判断广义表是否为空
	if (!L)
		return TRUE;
	else
		return FALSE;
}

GList GetHead_GL_H_T(GList L)
{
	//获取表头
	GList p;
	if (!L)
	{
		printf("广义表为空\n");
		exit(ERROR);
	}
	CopyGList_GL_H_T(&p, L->Union.ptr.hp);
	return p;
}

GList GetTail_GL_H_T(GList L)
{
	//获取表尾
	GList p;
	if (!L)
	{
		printf("广义表为空\n");
		exit(ERROR);
	}
	CopyGList_GL_H_T(&p, L->Union.ptr.tp);
	return p;
}

void InsertFirst_GL_H_T(GList *L, GList e)
{
	//插入e
	GList g;
	g = (GList)malloc(sizeof(GLNode));
	if (!g)
		exit(OVERFLOW);
	g->tag = 1;
	g->Union.ptr.hp = e;
	g->Union.ptr.tp = *L;
	*L = g;
}

void DeleteFirst_GL_H_T(GList *L, GList *e)
{
	//删除表头并用e返回
	GList p;
	if (!(*L))
	{
		printf("广义表为空");
		exit(OVERFLOW);
	}
	p = *L;
	*L = (*L)->Union.ptr.tp;
	CopyGList_GL_H_T(e, p->Union.ptr.hp);
	free(p);
	p = NULL;
}

void Traverse_GL_H_T(GList L, void(Visit)(AtomType))
{
	//遍历
	if (L)
	{
		if (L->tag == Atom)
			Visit(L->Union.atom);
		else
		{
			Traverse_GL_H_T(L->Union.ptr.hp, Visit);
			Traverse_GL_H_T(L->Union.ptr.tp, Visit);
		}
	}
}