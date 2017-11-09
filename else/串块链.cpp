#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
#define CHUNKSIZE 3
class CString {
private:

	typedef struct Chunk {
		char ch[CHUNKSIZE];
		struct Chunk *next;
	}Chunk;

	struct LString
	{
		Chunk *head, *tail;
		int curlen;
	}*L;

public:
	CString();					//构造
	int AddChars(char *chars);  //添加字符串
	~CString();					//析构
	void StrPrint();			//输出
	CString(const CString &);	//拷贝构造
	CString concat(const CString &s);		//连接
	CString & operator = (const CString &rhs);	//复制赋值

private:
	void _Clear();
};

CString::CString()
{
	L = new LString;
	(*L).head = NULL;
	(*L).tail = NULL;
	(*L).curlen = 0;
}

int CString::AddChars(char *chars)
{
	int i, j, k, len, count;
	Chunk *r;
	len = strlen(chars);
	if (!len) return 0;
	i = len / CHUNKSIZE;
	j = len % CHUNKSIZE;
	if (j)	i++;
	for (k = 1; k <= i; k++)
	{
		r = (Chunk*)malloc(sizeof(Chunk));
		if (!r) exit(-3);
		r->next = NULL;
		if (k == 1)
			(*L).head = (*L).tail = r;
		else
		{
			(*L).tail->next = r;
			(*L).tail = r;
		}
		for (count = 0; count < CHUNKSIZE && count + (k - 1)*CHUNKSIZE < len; count++)
			(*L).tail->ch[count] = chars[count + (k - 1)*CHUNKSIZE];
	}
	while (count < CHUNKSIZE)
	{
		(*L).tail->ch[count] = '\0';
		count++;
	}
	(*L).curlen = len;
	return 1;
}

CString::~CString()
{
	while (L)
	{
		LString *l = L;
		L->head = l->head->next;
		L->tail = l->tail->next;
		delete l->head;
		delete l->tail;
	}
}

void CString::StrPrint()
{
	int i = 0;
	Chunk *p = (*L).head;
	if ((*L).head == NULL && (*L).tail == NULL && (*L).curlen == 0)
		printf("串为空串，无法输出");
	while (p)
	{
		if ((*p).ch[i])
			printf("%c", (*p).ch[i]);
		i = (i + 1) % CHUNKSIZE;
		if (!i)
			p = p->next;
	}
}

CString CString::concat(const CString &s)
{
	CString sp;
	int i, j, k, count;
	Chunk *r, *p, *q;
	r = sp.L->head;
	p = L->head;
	q = s.L->head;
	i = j = k = 0;
	while (p || q)
	{
		if (!r)
		{
			r = (Chunk*)malloc(sizeof(Chunk));
			if (!r) exit(-3);
			r->next = NULL;
			if (!sp.L->head)
				sp.L->head = sp.L->tail = r;
			else
			{
				sp.L->tail->next = r;
				sp.L->tail = r;
			}
		}
		if (p)
		{
			while (p && p->ch[j])
			{
				r->ch[i] = p->ch[j];
				i = (i + 1) % CHUNKSIZE;
				j = (j + 1) % CHUNKSIZE;
				if (!j || !(p->ch[j]))
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
				k = (k + 1) % CHUNKSIZE;
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
	sp.L->curlen = L->curlen + s.L->curlen;
	count = (sp.L->curlen - 1) % CHUNKSIZE + 1;
	while (count < CHUNKSIZE)
	{
		sp.L->tail->ch[count] = '\0';
		count++;
	}
	return sp;
}

void CString::_Clear()
{
	
}

CString::CString(const CString &rhs)
{
	L = new LString;
	Chunk *r, *p;
}

CString & CString::operator = (const CString &rhs)
{
	

	return *this;
}

void main()
{
	char c[201];
	cin >> c;
	CString s1;
	s1.AddChars(c);
	s1.StrPrint();
}