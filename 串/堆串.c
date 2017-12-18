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

typedef struct
{
	char *ch;
	int length
}HString;

void InitString_H(HString *S)
{
	//初始化S为空串
	(*S).ch = NULL;
	(*S).length = 0;
}

Status StrAssign_H(HString *T, char *chars)
{
	//生成一个其值等于常量chars的串T
	int i, j;
	InitString_H(T);
	i = strlen(chars);
	if (!i)
		return ERROR;
	else
	{
		(*T).ch = (char*)malloc(i * sizeof(char));
		if (!(*T).ch)
			exit(OVERFLOW);
		for (j = 0; j < i; j++)
			(*T).ch[j] = chars[j];
		(*T).length = i;
	}
	return OK;
}

Status strCopy_H(HString *T, HString S)
{
	//有串S复制得到串T
	int i;
	InitString_H(T);
	if (StrEmpty_H(S))
		return ERROR;
	(*T).ch = (char*)malloc(S.length * sizeof(char));
	if (!(*T).ch)
		exit(OVERFLOW);
	for (i = 0; i < S.length; i++)
		(*T).ch[i] = S.ch[i];
	(*T).length = S.length;
	return OK;
}

Status StrEmpty_H(HString S)
{
	//判断串是否为空
	if (S.length == 0 && S.ch == NULL)
		return TRUE;
	else
		return FALSE;
}

Status StrCompare_H(HString S, HString T)
{
	//若S>T，返回值>0
	int i;
	for (i = 0; i < S.length&&i < T.length; i++)
	{
		if (S.ch[i] != T.ch[i])
			return S.ch[i] - T.ch[i];
	}
	return S.length - T.length;
}

int StrLength_H(HString S)
{
	//串长
	if (StrEmpty_H(S))
		return 0;
	else
		return S.length;
}

Status ClearString_H(HString *S)
{
	//清空S
	if ((*S).ch)
	{
		free((*S).ch);
		(*S).ch = NULL;
	}
	(*S).length = 0;
	return OK;
}

Status Concat_H(HString *T, HString S1, HString S2)
{
	//用T返回由S1和S2联结而成的新串
	int i;
	InitString_H(T);
	(*T).length = S1.length + S2.length;
	(*T).ch = (char*)malloc((*T).length * sizeof(char));
	if (!(*T).ch)
		exit(OVERFLOW);
	for (i = 0; i < S1.length; i++)
		(*T).ch[i] = S1.ch[i];
	for (i = 0; i < S2.length; i++)
		(*T).ch[S1.length + i] = S2.ch[i];
	return OK;
}

Status SubString_H(HString *Sub, HString S, int pos, int len)
{
	//用Sub返回串S的第pos个字符起长度为len的子串
	int i;
	InitString_H(Sub);
	if (StrEmpty_H(S))
		return ERROR;
	if (pos<1 || pos>S.length || len < 0 || pos + len - 1>S.length)
		return ERROR;
	if (len)
	{
		(*Sub).ch = (char*)malloc(len * sizeof(char));
		if (!(*Sub).ch)
			exit(OVERFLOW);
		for (i = 0; i < len; i++)
			(*Sub).ch[i] = S.ch[i + pos - 1];
		(*Sub).length = len;
	}
	return OK;
}

int Index_H(HString S, HString T, int pos)
{
	//返回T在S中第pos个字符后第一次出现的位置,不存在则返回0
	int s, t, i;
	HString Sub;
	InitString_H(&Sub);
	if (pos > 0)
	{
		s = S.length;
		t = T.length;
		i = pos;
		while (i + t - 1 <= s)
		{
			SubString_H(&Sub, S, i, t);
			if (StrCompare_H(Sub, T))
				i++;
			else
				return i;
		}
	}
	return 0;
}

Status Replace_H(HString *S, HString T, HString V)
{
	//用V替换主串S中出现的说有与T相等的不重叠的子串
	int i;
	if (StrEmpty_H(T))
		return ERROR;
	i = Index_H(*S, T, 1);
	while (i != 0)
	{
		StrDelete_H(S, i, StrLength_H(T));
		StrInsert_H(S, i, V);
		i += StrLength_H(V);
		i = Index_H(*S, T, i);
	}
	return OK;

}

Status StrInsert_H(HString *S, int pos, HString T)
{
	//插入串T
	int i;
	if (pos<1 || pos>(*S).length + 1)
		return ERROR;
	if (StrEmpty_H(T))
		return ERROR;
	else
	{
		(*S).ch = (char*)realloc((*S).ch, ((*S).length + T.length) * sizeof(char));
		if (!(*S).ch)
			exit(OVERFLOW);
		for (i = (*S).length - 1; i >= pos - 1; i--)
			(*S).ch[i + T.length] = (*S).ch[i];
		for (i = 0; i < T.length; i++)
			(*S).ch[pos - 1 + i] = T.ch[i];
		(*S).length += T.length;
	}
	return OK;
}

Status StrDelete_H(HString *S,int pos,int len)
{
	//删除子串
	int i;
	if (StrEmpty_H(*S))
		return ERROR;
	if (pos<1 || pos + len - 1>(*S).length || len < 0)
		return ERROR;
	for (i = pos - 1; i + len <= (*S).length; i++)
		(*S).ch[i] = (*S).ch[i + len];
	(*S).length -= len;
	(*S).ch = (char*)realloc((*S).ch, (*S).length * sizeof(char));
	return OK;
}
void DestroyString_H(HString *S)
{
	//销毁串S
}

void StrPrint_H(HString S)
{
	//输出串S
	int i;
	if (StrEmpty(S))
		printf("空串");
	for (i = 0; i < S.length; i++)
		printf("%c", S.ch[i]);
}
void main()
{

}
