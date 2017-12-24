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

#define MAXSIZE 400
#define MAXRC 20

typedef int MElemType_RLSq;
typedef struct
{
	int i, j;
	MElemType_RLSq e;
}Triple;

typedef struct
{
	Triple data[MAXSIZE + 1];
	int rpos[MAXRC + 1];		//各行第一个非零元在三元组表的位置表
	int mu, nu, tu;
};
