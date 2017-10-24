#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* ״̬�� */
#define	OK			1
#define	ERROR		0
#define	OVERFLOW	-2
#define TRUE		1
#define FALSE		0
typedef int Status;

#define MAXSTRLEN 255//˳�򴮵���󴮳�

//����˳��洢���Ͷ���
typedef unsigned char SString[MAXSTRLEN + 1]; //0�ŵ�Ԫ��Ŵ��ĳ���

Status StrAssign_Sq(SString T, const char *chars)//����һ����ֵ���ڳ���chars�Ĵ�T
{
	int i, len;
	len = strlen(chars);
	if (len>MAXSTRLEN)//chars����
		return ERROR;
	else
	{
		T[0] = len;
		for (i = 1; i<len; i++)
			T[i] = chars[i - 1];
		return OK;
	}
}

void StrCopy_Sq(SString T, SString S)//�ɴ�S���Ƶõ���T
{
	int i;
	for (i = 0; i<S[0]; i++)
		T[i] = S[i];
}

Status StrEmpty_Sq(SString S)//��SΪ�շ���TURE
{
	if (S[0] == 0)
		return TRUE;
	else
		return FALSE;
}

int StrCompare_Sq(SString S, SString T)//��S>T,����ֵ>0
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

int StrLength_Sq(SString S)//�󴮳�
{
	return S[0];
}

void ClearString_Sq(SString S)//���S
{
	S[0] = 0;
}

Status Concat_Sq(SString T, SString S1, SString S2)//��S1��S2������´�
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

Status SubString_Sq(SString Sub, SString S, int pos, int len)//����S�ĵ�Pos���ַ��𳤶�Ϊlen���Ӵ�
{
	int i;
	if (pos<1 || pos > S[0] || len<0 || pos + len - 1>S[0])
		return ERROR;
	for (i = 1; i < len; i++)
		Sub[i] = S[pos + i - 1];
	Sub[0] = len;
	return OK;
}

int Inded_Sq_1(SString S, SString T, int pos)//����T��S�е�pos���ַ����һ�γ���λ��
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

int Inded_Sq_2(SString S, SString T, int pos)//����T��S�е�pos���ַ����һ�γ���λ��
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
			i = i - (j - 1) + 1;//j-1����ͽ�͵�ǰ����j-1��λ��
			j = 1;
		}
	}
	if (j>T[0] && T[0])//T��Ϊ�մ�
		return i - T[0];//ƥ��ɹ�
	else
		return 0;
}

Status Replace_Sq(SString S, SString T, SString V)//��V�滻S���ֵ�˵����T��ȵĲ��ص����Ӵ�
{
	int i;
	i = Inded_Sq_2(S, T, 1); //Ѱ�ҵ�һ��ƥ���λ��
	while (S[0] - T[0] + V[0] <= MAXSTRLEN && i)//��ƥ����ַ����ҿ�����ȫ�滻
	{
		StrDelete_Sq(S, i, T[0]);//ɾ��T
		StrInsert_Sq(S, i, V);//����V
		i += V[0];//i�л�����һ��λ��
		i = Inded_Sq_2(S, T, i);//��λ����һ��ƥ����ַ���
	}
	if (i == 0)
		return OK;
	else
		return ERROR;
}

Status StrInsert_Sq(SString S, int pos, SString T)//��S�ĵ�pos���ַ�ǰ���봮T
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

Status StrDelete_Sq(SString S, int pos, int len)//�Ӵ�S��ɾ����pos���ַ��𳤶�Ϊlen���Ӵ�
{
	int i;
	if (pos<1 || pos + len - 1>S[0] || len<0)
		return ERROR;
	for (i = pos + len; i <= S[0]; i++)
		S[i - len] = S[i];
	S[0] -= len;
	return OK;
}

void DestroyString_Sq(SString S)//���ٴ�S
{

}

void StrPrint_Sq(SString S)//�����S
{
	int i;
	for (i = 1; i <= S[0]; i++)
		printf("%c", S[i]);
}
