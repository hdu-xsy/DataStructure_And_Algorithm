#define SEQUENCELIST_H

#include <stdio.h>
#include <stdlib.h>
#define STATUS_H

/* ״̬�� */
#define	TRUE		1
#define	FALSE		0
#define YES			1
#define NO          0
#define	OK			1
#define	ERROR		0
#define SUCCESS		1
#define UNSUCCESS	0
#define	INFEASIBLE	-1
#define	OVERFLOW	-2
#define UNDERFLOW	-3
#define NULL ((void*)0)

typedef int Status;

#difine MAXSTRLEN 255//˳�򴮵���󴮳�

//����˳��洢���Ͷ���
type unsigned char SString[MAXSTRLEN+1]; //0�ŵ�Ԫ��Ŵ��ĳ���

Status StrAssign_Sq(SString T,const char *chars)//����һ����ֵ���ڳ���chars�Ĵ�T
{

}

void StrCopy_Sq(SString T,SString S)//�ɴ�S���Ƶõ���T
{

}

Status StrEmpty_Sq(SString S)//��SΪ�շ���TURE
{

}

int StrCompare_Sq(SString S,SString T)//��S>T,����ֵ>0
{

}

int StrLength_Sq(SString S)//�󴮳�
{

}

void ClearString_Sq(SString S)//���S
{

}

Status Concat_Sq(SString T,SString S1,SString S2)//��S1��S2������´�
{

}

Status SubString_Sq(SString Sub,SString S,int pos,int len)//����S�ĵ�Pos���ַ��𳤶�Ϊlen���Ӵ�
{

}

int Inded_Sq_1(SString S,SString T,int pos)//����T��S�е�pos���ַ����һ�γ���λ��
{

}

int Inded_Sq_2(SString S,SString T,int pos)//����T��S�е�pos���ַ����һ�γ���λ��
{

}

Status Replace_Sq(SString S,SString T,SString V)//��V�滻S���ֵ�˵����T��ȵĲ��ص����Ӵ�
{

}

Status StrInsert_Sq(SString S,int pos,SString T)//��S�ĵ�pos���ַ�ǰ���봮T
{

}

Status StrDelete_Sq(SString S,int pos,int len)//�Ӵ�S��ɾ����pos���ַ��𳤶�Ϊlen���Ӵ�
{

}

void DestroyString_Sq(SString S)//���ٴ�S
{

}

void StrPrint_Sq(SString S)//�����S
{

}
