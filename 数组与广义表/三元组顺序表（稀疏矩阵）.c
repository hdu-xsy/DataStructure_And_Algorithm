#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)
#define	OK			1
#define TRUE        1
#define FALSE       0
#define	ERROR		0
#define	OVERFLOW	-2
#define UNDERFLOW   -3
typedef int Status;
#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a)<(b))
#define LQ(a,b) ((a)<=(b))

typedef int MElemType_Sq;
#define MAXSIZE 400
typedef struct
{
	int i, j;
	MElemType_Sq e;
}Triple;
typedef struct
{
	Triple data[MAXSIZE + 1];
	int mu, nu, tu;
}TSMatrix;

Status CreateSMatrix_T(int n , ...)
{
	//创建n个矩阵
	int count, k;
	TSMatrix *M;
	if (n < 1)
		return ERROR;
	va_list ap;
	__crt_va_start(ap, n);
	for (count = 1; count <= n; count++)
	{
		M = __crt_va_arg(ap, TSMatrix*);
		scanf("%d%d%d", &((*M).mu), &((*M).nu), &((*M).tu));
		for (k = 1; k <= (*M).tu; k++)
			scanf("%d%d%d", &((*M).data[k].i), &((*M).data[k].j), &((*M).data[k].e));
	}
	__crt_va_end(ap);
	return OK;
}

void DeatroySMatrix_T(TSMatrix *M)
{
	//摧毁
	(*M).mu = 0;
	(*M).nu = 0;
	(*M).tu = 0;
}

void PrintSMatrix_T(TSMatrix M)
{
	//输出矩阵
	int r, c;
	int k = 1;
	for (r = 1; r <= M.mu; r++)
	{
		for (c = 1; c <= M.mu; c++)
		{
			if (r == M.data[k].i && c == M.data[k].j)
			{
				printf("%3d", M.data[k].e);
				k++;
			}
			else
				printf("  0");
		}
		printf("\n");
	}
}

void copySMatrix_T(TSMatrix M, TSMatrix *T)
{
	//复制
	(*T) = M;
}

int AddSMatrix_T(TSMatrix M, TSMatrix N, TSMatrix *Q)
{
	//Q = M + N
	int m, n, k;
	if (M.mu != N.mu || M.nu != N.nu)
	{
		printf("两矩阵不能相加\n");
		return ERROR;
	}
	Q->mu = M.mu;
	Q->nu = M.nu;
	Q->tu = 0;
	m = n = k = 1;
	while (m <= M.tu && n <= N.tu)
	{
		if (M.data[m].i<N.data[n].i)
		{
			Q->data[k] = M.data[m];
			m++;
		}
		else if (M.data[m].i>N.data[n].i)
		{
			Q->data[k] = N.data[n];
			n++;
		}
		else
		{
			if (M.data[m].j<N.data[n].j)
			{
				Q->data[k] = M.data[m];
				m++;
			}
			else if (M.data[m].j>N.data[n].j)
			{
				Q->data[k] = N.data[n];
				n++;
			}
			else
			{
				if (M.data[m].e + N.data[n].e)
				{
					Q->data[k].i = M.data[m].i;
					Q->data[k].j = M.data[m].j;
					Q->data[k].e = M.data[m].e + N.data[n].e;
					m++;
					n++;
				}
				else
				{
					m++;
					n++;
					continue;
				}
			}
		}
		k++;
		Q->tu++;
	}
	while (m <= M.tu)
	{
		Q->data[k] = N.data[m];
		m++;
		k++;
		Q->tu++;
	}
	while (n <= N.tu)
	{
		Q->data[k] = N.data[n];
		n++;
		k++;
		Q->tu++;
	}
	return OK;
}

Status SubSMatrix_T(TSMatrix M, TSMatrix N, TSMatrix *Q)
{
	//Q = M - N
	int m, n, k;
	if (M.mu != N.mu || M.nu != N.nu)
	{
		printf("两矩阵不能相减\n");
		return ERROR;
	}
	Q->mu = M.mu;
	Q->nu = M.nu;
	Q->tu = 0;
	m = n = k = 1;
	while (m <= M.tu && n <= N.tu)
	{
		if (M.data[m].i<N.data[n].i)
		{
			Q->data[k] = M.data[m];
			m++;
		}
		else if (M.data[m].i>N.data[n].i)
		{
			Q->data[k].i = N.data[n].i;
			Q->data[k].j = N.data[n].j;
			Q->data[k].e = -N.data[n].e;
			n++;
		}
		else
		{
			if (M.data[m].j<N.data[n].j)
			{
				Q->data[k] = M.data[m];
				m++;
			}
			else if (M.data[m].j>N.data[n].j)
			{
				Q->data[k].i = N.data[n].i;
				Q->data[k].j = N.data[n].j;
				Q->data[k].e = -N.data[n].e;
				n++;
			}
			else
			{
				if (M.data[m].e - N.data[n].e)
				{
					Q->data[k].i = M.data[m].i;
					Q->data[k].j = M.data[m].j;
					Q->data[k].e = M.data[m].e - N.data[n].e;
					m++;
					n++;
				}
				else
				{
					m++;
					n++;
					continue;
				}
			}
		}
		k++;
		Q->tu++;
	}
	while (m <= M.tu)
	{
		Q->data[k] = M.data[m];
		m++;
		k++;
		Q->tu++;
	}
	while (n <= N.tu)
	{
		Q->data[k].i = N.data[n].i;
		Q->data[k].j = N.data[n].j;
		Q->data[k].e = -N.data[n].e;
		n++;
		k++;
		Q->tu++;
	}
	return OK;
}

Status MultSMatrix_T(TSMatrix M, TSMatrix N, TSMatrix *Q)
{
	//Q= M * N
	int m, n, i, j, k;
	MElemType_Sq c, c1, c2;
	if (M.nu != N.mu)
	{
		printf("两矩阵不能相乘\n");
		return ERROR;
	}
	Q->mu = M.mu;
	Q->nu = N.nu;
	Q->tu = 0;
	if (M.tu*N.tu)
	{
		for (i = 1; i <= M.mu; i++)
		{
			for (j = 1; j <= N.nu; j++)
			{
				c = 0;
				for (k = 1; k <= M.nu; k++)
				{
					c1 = 0;
					for (m = 1; m <= M.tu; m++)
					{
						if (M.data[m].i == i && M.data[m].j == k)
						{
							c1 = M.data[m].e;
							break;
						}
					}
					c2 = 0;
					for (n = 1; n <= N.tu; n++)
					{
						if (N.data[n].i == k && N.data[n].j == j)
						{
							c2 = N.data[n].e;
							break;
						}
					}
					if (c)
					{
						Q->tu++;
						Q->data[Q->tu].i = i;
						Q->data[Q->tu].j = j;
						Q->data[Q->tu].e = c;
					}
				}
			}
		}
		return OK;
	}
}

void TransponseSMatrix_T(TSMatrix M, TSMatrix *T)
{
	//转置
	int p, q, col;
	T->mu = M.nu;
	T->nu = M.mu;
	T->tu = M.tu;
	if (T->tu)
	{
		q = 1;
		for (col = 1; col <= M.mu; ++col)
		{
			for (p = 1; p <= M.tu; ++p)
			{
				if (M.data[p].j == col)
				{
					T->data[q].i = M.data[p].j;
					T->data[q].j = M.data[p].i;
					T->data[q].e = M.data[p].e;
					++q;
				}
			}
		}
	}
}

void FastTransponseSMatrix_T(TSMatrix M, TSMatrix *T)
{
	//快速转置
	int col, t, p, q;
	int num[M.nu];
	int copt[M.mu];
	T->mu = M.nu;
	T->nu = M.mu;
	T->tu = M.tu;
	if (T->tu)
	{
		for (col = 1; col <= M.nu; ++col)
			num[col] = 0;
		for (t = 1; t <= M.tu; ++t)
			num[M.data[t].j]++;
		copt[1] = 1;
		for (col = 2; col <= M.nu; ++col)
			copt[col] = copt[col - 1] + num[col - 1];
		for (p = 1; p <= M.tu; ++p)
		{
			col = M.data[p].j;
			q = copt[col];
			T->data[q].i = M.data[p].j;
			T->data[q].j = M.data[p].i;
			T->data[q].e = M.data[p].e;
			++copt[col];
		}
	}
}
void main()
{

}