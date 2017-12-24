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

typedef int CElemType;
typedef struct
{
	int i, j;
	CElemType e;
	struct OLNode *right;	//行表后继链域
	struct OLNode *down;	//列表后继链域
}OLNode;
typedef OLNode *OLink;
typedef struct
{
	OLink *rhead;
	OLink *chead;
	int mu, nu, tu;
}CrossList;


