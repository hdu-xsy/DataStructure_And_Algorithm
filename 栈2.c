#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef struct
{
  int *base;
  int *top;
  int stacksize;
}SqStack;

SqStack InitStack(SqStack &S)
{
  S.base = (int*)malloc(STACK_INIT_SIZE*sizeof(int));
  if(!S.base) exit("OVERFLOW");
  S.top = S.base;
  S.stacksize = STACK_INIT_SIZE;
  return S;
}

int GetTop(SqStack S,int e)
{
  if(S.top == S.base)
  return 0;
  e=*(s.top-1);
  printf("%d\n",e);
  return 1;
}

void Push(SqStack &S,int e)
{
  if(S.top-S.base>=S.stacksize)
  {
    S.base=(int*)realloc(S.base,S.stacksize+STACKINCREMENT*sizeof(int));
    if(!S.base) exit(-2);
    S.top = S.base+S.stacksize;
    S.stacksize += STACKINCREMENT;
  }
  *S.top++ = e;
}

int Pop(SqStack &S,int e)
{
  if(S.top == S.base)
  return 0;
  e= *--S.top;
  return 1;
}
