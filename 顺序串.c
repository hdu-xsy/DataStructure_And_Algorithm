#define SEQUENCELIST_H

#include <stdio.h>
#include <stdlib.h>
#define STATUS_H

/* 状态码 */
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

#difine MAXSTRLEN 255//顺序串的最大串长

//串的顺序存储类型定义
type unsigned char SString[MAXSTRLEN+1]; //0号单元存放串的长度

Status StrAssign_Sq(SString T,const char *chars)//生成一个其值等于常量chars的串T
{

}

void StrCopy_Sq(SString T,SString S)//由串S复制得到串T
{

}

Status StrEmpty_Sq(SString S)//若S为空返回TURE
{

}

int StrCompare_Sq(SString S,SString T)//若S>T,返回值>0
{

}

int StrLength_Sq(SString S)//求串长
{

}

void ClearString_Sq(SString S)//清空S
{

}

Status Concat_Sq(SString T,SString S1,SString S2)//求S1和S2联结的新串
{

}

Status SubString_Sq(SString Sub,SString S,int pos,int len)//返回S的第Pos个字符起长度为len的子串
{

}

int Inded_Sq_1(SString S,SString T,int pos)//返回T在S中第pos个字符后第一次出现位置
{

}

int Inded_Sq_2(SString S,SString T,int pos)//返回T在S中第pos个字符后第一次出现位置
{

}

Status Replace_Sq(SString S,SString T,SString V)//用V替换S出现的说有与T相等的不重叠的子串
{

}

Status StrInsert_Sq(SString S,int pos,SString T)//串S的第pos个字符前插入串T
{

}

Status StrDelete_Sq(SString S,int pos,int len)//从串S中删除第pos个字符起长度为len的子串
{

}

void DestroyString_Sq(SString S)//销毁串S
{

}

void StrPrint_Sq(SString S)//输出串S
{

}
