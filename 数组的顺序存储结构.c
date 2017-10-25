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

#define MAX_ARRAY_DIM 8   //数组的最大维度

typedef int AElemType_Sq;
typedef struct    //数组的顺序存储表示
{
  AElemType_Sq *base;   //数组元素基址
  int dim;              //数组维数
  int *bounds;          //数组维界基址（存放数组行列信息）
  int *constants        //数组映像函数常量基址（存放跨越某个维度时需要越过的元素个位）
}Array;

Status InitArray(Array *A,int dim,...)
{
  
}
