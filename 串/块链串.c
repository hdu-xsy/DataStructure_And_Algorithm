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
#define CHUNKSIZE 3
typedef struct
{
	char ch[CHUNKSIZE];
	struct Chunk *next;
}Chunk;
typedef struct
{
	Chunk *head, *tail;
	int curlen;
}LString;

void InitString_L(LString *T)
{
	//初始化块链串T
	(*T).head = NULL;
	(*T).tail = NULL;
	(*T).curlen = 0;
}

Status StrAssign_L(LString *T, char *chars)
{
	//生成一个其值等于常量chars的串T
	int len, i, j, k, count;
	Chunk *r;
	InitString_L(T);
	len = strlen(chars);
	if (!len)
		return ERROR;
	i = len / CHUNKSIZE;
	j = len % CHUNKSIZE;
	if (j)
		i++;
	for (k = 1; k <= i; k++)
	{
		r = (Chunk*)malloc(sizeof(Chunk));
		if (!r)
			exit(OVERFLOW);
		r->next = NULL;
		if (k == 1)
			(*T).head = (*T).tail = r;
		else
		{
			(*T).tail->next = r;
			(*T).tail = r;
		}
		for (count = 0; count < CHUNKSIZE && cout + (k - 1)*CHUNKSIZE < len; count++)
			(*T).tail->ch[count] = chars[count + (k - 1)*CHUNKSIZE];
	}
	while (count < CHUNKSIZE)
	{
		(*T).tail->ch[count] = '\0';
		count++;
	}
	(*T).curlen = len;
	return OK;
}

Status StrCopy_L(LString *T, LString S)
{
	//有串S复制得到串T
	int i;
	Chunk *r, *p;
	InitString_L(T);
	for (p = S.head; p; p = p->next)
	{
		r = (Chunk*)malloc(sizeof(Chunk));
		if (!r)
			exit(OVERFLOW);
		r->next = NULL;
		if (p == S.head)
			(*T).head = (*T).tail = r;
		else
		{
			(*T).tail->next = r;
			(*T).tail = r;
		}
		for (i = 0; i < CHUNKSIZE; i++)
			(*r).ch[i] = (*p).ch[i];
	}
	(*T).curlen = S.curlen;
	return OK;
}

Status StrEmpty_L(LString S)
{
	//若S为空串，返回TRUE
	if (S.head == NULL && S.tail == NULL && S.curlen == 0)
		return TRUE;
	else
		return ERROR;
}

int StrComnpare_L(LString S, LString T)
{
	//若S>T,返回值>0
	int i;
	int s = S.curlen;
	int t = T.curlen;
	Chunk *p = S.head;
	Chunk *q = T.head;
	while (p && q)
	{
		for (i = 0; i < CHUNKSIZE; i++)
		{
			if ((*p).ch[i] != (*q).ch[i])
				return (*p).ch[i] - (*q).ch[i];
		}
		p = p->next;
		q = q->next;
	}
	return s - t;
}

int StrLength_L(LString S)
{
	//求串长
	return S.curlen;
}

void ClearString_L(LString *S)
{
	//清空S
	Chunk *p, *q;
	p = (*S).head;
	while (p)
	{
		q = p->next;
		free(p);
		p = q;
	}
	(*S).head = NULL;
	(*S).tail = NULL;
	(*S).curlen = 0;
}

void Connat_L(LString *T, LString S1, LString S2)
{
	//用T返回由S1和S2联结而成的新串
	int i, j, k, count;
	Chunk *r, *p, *q;
	InitString_L(T);
	r = (*T).head;
	p = S1.head;
	q = S2.head;
	i = j = k = 0;
	while (p || q)
	{
		if (!r)
		{
			r = (Chunk*)malloc(sizeof(Chunk));
			if (!r)
				exit(OVERFLOW);
			r->next = NULL;
			if (!(*T).head)
				(*T).head = (*T).tail = r;
			else
			{
				(*T).tail->next = r;
				(*T).tail = r;
			}
		}
		if (p)
		{
			while (p && p->ch[j])
			{
				r->ch[i] = p->ch[j];
				i = (i + 1) % CHUNKSIZE;
				j = (j + 1) % CHUNKSIZE;
				if (!j || !(p->chp[j]))
					p = p->next;
				if (!i)
				{
					r = r->next;
					break;
				}
			}
		}
		else
		{
			while (q && q->ch[k])
			{
				r->ch[i] = q->ch[k];
				i = (i + 1) % CHUNKSIZE;
				j = (j + 1) % CHUNKSIZE;
				if (!k || !(q->ch[k]))
					q = q->next;
				if (!i)
				{
					r = r->next;
					break;
				}
			}
		}
	}
	(*T).curlen = S1.curlen + S2.curlen;
	count = ((*T).curlen - 1) % CHUNKSIZE+ 1;
	while (count < CHUNKSIZE)
	{
		(*T).tail->ch[count] = '\0';
		count++;
	}
}

Status SubString_L(LString *Sub, LString S, int pos, int len)
{
	//用Sub返回串S的第pos个字符起长度为len的子串

}

int Index_L(LString S, LString T, int pos)
{
	//返回T在S中第pos个字符后第一次出现的位置,不存在则返回0

}

Status Replace_L(LString *S, LString T, LString V)
{
	//用V替换主串S中出现的说有与T相等的不重叠的子串


}

Status StrInsert_L(LString *S, int pos, LString T)
{
	//插入串T

}

Status StrDelete_L(LString *S, int pos, int len)
{
	//删除子串
	
}
void DestroyString_L(LString *S)
{
	//销毁串S
}

void StrPrint_L(LString S)
{
	//输出串S

}
void main()
{

}