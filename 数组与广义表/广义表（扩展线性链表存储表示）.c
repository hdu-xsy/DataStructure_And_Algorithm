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

#include "../��/˳��.c"
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
	//��ʼ�������
}

void sever_GL_E(SString hstr, SString str)
{
	//���մ�str�ָ��������,hsubΪ��һ��','֮ǰ���Ӵ���strΪ֮����Ӵ�

}

void CreateGList_GL_E(GList *L, SString S)
{
	//��S���������
}

void ClearGList_GL_E(GList *L)
{
	//��չ����
}

void CopyGList_GL_E(GList *T, GList L)
{
	//���ƹ����
}

int GListLength_GL_E(GList L)
{
	//��������
}

int GListDepth_GL_E(GList L)
{
	//���������
}

Status GListEmpty_GL_E(GList L)
{
	//�жϹ�����Ƿ�Ϊ��
}

GList GetHead_GL_E(GList L)
{
	//��ȡ��ͷ
}

GList GetTail_GL_E(GList L)
{
	//��ȡ��β
}

void InsertFirst_GL_E(GList *L, GList e)
{
	//����e
}

void DeleteFirst_GL_E(GList *L, GList *e)
{
	//ɾ����ͷ����e����
}

void Traverse_GL_E(GList L, void(Visit)(AtomType))
{
	//����
}