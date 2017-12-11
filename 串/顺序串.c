#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* 状态码 */
#define	OK			1
#define	ERROR		0
#define	OVERFLOW	-2
#define TRUE		1
#define FALSE		0
typedef int Status;

#define MAXSTRLEN 255//顺序串的最大串长

//串的顺序存储类型定义
typedef unsigned char SString[MAXSTRLEN + 1]; //0号单元存放串的长度

Status StrAssign_Sq(SString T, const char *chars)//生成一个其值等于常量chars的串T
{
	int i, len;
	len = strlen(chars);
	if (len>MAXSTRLEN)//chars过长
		return ERROR;
	else
	{
		T[0] = len;
		for (i = 1; i<len; i++)
			T[i] = chars[i - 1];
		return OK;
	}
}

void StrCopy_Sq(SString T, SString S)//由串S复制得到串T
{
	int i;
	for (i = 0; i<S[0]; i++)
		T[i] = S[i];
}

Status StrEmpty_Sq(SString S)//若S为空返回TURE
{
	if (S[0] == 0)
		return TRUE;
	else
		return FALSE;
}

int StrCompare_Sq(SString S, SString T)//若S>T,返回值>0
{
	int i = 1;
	while (i <= S[0] && i <= T[0])
	{
		if (S[i] == T[i])
			i++;
		else
			return S[i] - T[i];
	}
	return S[0] - T[0];
}

int StrLength_Sq(SString S)//求串长
{
	return S[0];
}

void ClearString_Sq(SString S)//清空S
{
	S[0] = 0;
}

Status Concat_Sq(SString T, SString S1, SString S2)//求S1和S2联结的新串
{
	int i;
	for (i = 1; i <= S1[0]; i++)
		T[i] = S1[i];
	if (S1[0] + S2[0] <= MAXSTRLEN)
	{
		for (i = 1; i <= S2[0]; i++)
			T[S1[0] + i] = S2[i];
		T[0] = S1[0] + S2[0];
		return OK;
	}
	else
	{
		for (i = 1; S1[0] + i <= MAXSTRLEN; i++)
			T[S1[0] + i] = S2[i];
		T[0] = MAXSTRLEN;
		return ERROR;
	}
}

Status SubString_Sq(SString Sub, SString S, int pos, int len)//返回S的第Pos个字符起长度为len的子串
{
	int i;
	if (pos<1 || pos > S[0] || len<0 || pos + len - 1>S[0])
		return ERROR;
	for (i = 1; i < len; i++)
		Sub[i] = S[pos + i - 1];
	Sub[0] = len;
	return OK;
}

int Inded_Sq_1(SString S, SString T, int pos)//返回T在S中第pos个字符后第一次出现位置
{
	int s, t;
	SString Sub;
	if (pos>0)
	{
		s = StrLength_Sq(S);
		t = StrLength_Sq(T);
		if (s && t)
		{
			while (pos + t - 1 <= s)
			{
				SubString_Sq(Sub, S, pos, t);
				if (!StrCompare_Sq(Sub, T))
					return pos;
				pos++;
			}
		}
	}
	return 0;
}

int Inded_Sq_2(SString S, SString T, int pos)//返回T在S中第pos个字符后第一次出现位置
{
	int i = pos;
	int j = 1;
	if (pos<1)
		return 0;
	while (i <= S[0] && j <= T[0])
	{
		if (S[i] == T[j])
		{
			i++;
			j++;
		}
		else
		{
			i = i - (j - 1) + 1;//j-1代表徒劳地前进了j-1个位置
			j = 1;
		}
	}
	if (j>T[0] && T[0])//T不为空串
		return i - T[0];//匹配成功
	else
		return 0;
}

Status Replace_Sq(SString S, SString T, SString V)//用V替换S出现的说有与T相等的不重叠的子串
{
	int i;
	i = Inded_Sq_2(S, T, 1); //寻找第一个匹配的位置
	while (S[0] - T[0] + V[0] <= MAXSTRLEN && i)//有匹配的字符串且可以完全替换
	{
		StrDelete_Sq(S, i, T[0]);//删除T
		StrInsert_Sq(S, i, V);//插入V
		i += V[0];//i切换到下一个位置
		i = Inded_Sq_2(S, T, i);//定位到下一个匹配的字符串
	}
	if (i == 0)
		return OK;
	else
		return ERROR;
}

Status StrInsert_Sq(SString S, int pos, SString T)//串S的第pos个字符前插入串T
{
	int i;
	if (pos<1 || pos>S[0] + 1 || S[0] + T[0]>MAXSTRLEN)
		return ERROR;
	for (i = S[0]; i >= pos; i--)
		S[i + T[0]] = S[i];
	for (i = pos; i <= pos + T[0] - 1; i++)
		S[i] = T[i - pos + 1];
	S[0] += T[0];
	return 1;
}

Status StrDelete_Sq(SString S, int pos, int len)//从串S中删除第pos个字符起长度为len的子串
{
	int i;
	if (pos<1 || pos + len - 1>S[0] || len<0)
		return ERROR;
	for (i = pos + len; i <= S[0]; i++)
		S[i - len] = S[i];
	S[0] -= len;
	return OK;
}

void DestroyString_Sq(SString S)//销毁串S
{

}

void StrPrint_Sq(SString S)//输出串S
{
	int i;
	for (i = 1; i <= S[0]; i++)
		printf("%c", S[i]);
}
