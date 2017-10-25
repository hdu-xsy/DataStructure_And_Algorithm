#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

/* 状态码 */
#define	TRUE		1			//真
#define	FALSE		0			//假
#define	OK			1			//通过
#define	ERROR		0			//错误

#define	OVERFLOW	-2			//堆栈上溢

typedef int Status;

#define MAXSIZE 400   //非零元素最大值为400

typedef int MElemType_TSq;
typedef struct
{
  int i,j;
  MElemType_TSq e;
}Triple;
typedef struct
{
  Triple data[MAXSIZE+1];
  int mu,nu,tu;
}TSMatrix;

Status CreateSMatrix_T(int n)//创建n个矩阵
{
  int count,k;
  TSMatrix *M;
  if(n<1)
    return ERROR;
  va_list ap;
  va_start(ap,n);
  for(count=1;count<=n;count++)
  {
    M=va_arg(ap,TSMatrix*);

  }
  va_end(ap);
  return OK;
}

void DestroySMatrix_T(TSMatrix *M)//摧毁矩阵
{
  (*M).mu=0;
  (*M).nu=0;
  (*M).tu=0;
}

void PrintSMatrix_T(TSMatrix M)//输出矩阵
{
  int r,c;
  int k=1;
  for(r=1;r<=M.mu;r++)
  {
    for(c=1;c<=M.mu;c++)
    {
      if(r=M.data[k].i && c==M.data[k].j)
      {
        printf("%3d",M.data[k].e);
        k++;
      }
      else
        printf("0");
    }
    printf("\n");
  }
}

void CopySMatrix_T(TSMatrix M,TSMatrix *T)//复制矩阵
{
  (*T)=M;
}

void AddSMatrix_T(TSMatrix M,TSMatrix N,TSMatrix *Q)//Q=M+N
{
  int m,n,k;
  if(M.mu!=N.mu || M.nu!=N.nu)
  {
    printf("两矩阵不能相加");
    return ERROR;
  }
  Q->mu=M.mu;
  Q->nu=M.nu;
  Q->tu=0;
  m=n=k=1;
  while(m<=M.tu && n<=N.tu)
  {
    if(M.data[m].i>N.data[n].i)
    {
      Q->data[k]=M.data[m];
      m++;
    }
    else if(M.data[m].i>N.data[n].i)
    {
      Q->data[k]=N.data[n];
      m++;
    }
    else
    {
      if(M.data[m].j<N.data[n].j)
      {
        Q->data[k]=M.data[m];
        m++;
      }

    }
  }
}
