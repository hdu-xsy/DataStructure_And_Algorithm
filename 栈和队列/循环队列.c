#include <stdio.h>
#include <stdlib.h>
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
typedef int QElemType_CSq;
#define MAXQSIZE 100

typedef struct
{
	QElemType_CSq *base;
	int front;
	int rear;
}CSqQueue;

Status InitQueue_CSq(CSqQueue *Q)
{
	//初始化循环队列Q
	(*Q).base = (QElemType_CSq*)malloc(MAXQSIZE * sizeof(QElemType_CSq));
	if (!(*Q).base)
		exit(OVERFLOW);
	(*Q).front = (*Q).rear = 0;
	return OK;
}

void ClearQueue_CSq(CSqQueue *Q)
{
	//置空Q
	(*Q).front = (*Q).rear = 0;
}

void DestroyQueue_CSq(CSqQueue *Q)
{
	//销毁Q
	if ((*Q).base)
		free((*Q).base);
	(*Q).base = NULL;
	(*Q).front = (*Q).rear = 0;
}

Status QueueEmpty_CSq(CSqQueue Q)
{
	//判断Q是否为空
	if (Q.front == Q.rear)
		return TRUE;
	else
		return FALSE;
}

int QueueLength_CSq(CSqQueue Q)
{
	//返回Q元素个数
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}

Status GetHead_CSq(CSqQueue Q, QElemType_CSq *e)
{
	//元素e入队
	if (Q.front == Q.rear)
		return ERROR;
	*e = Q.base[Q.front];
	return OK;

}

Status DeQueue_CSq(CSqQueue *Q, QElemType_CSq *e)
{
	//元素e出队
	if ((*Q).front == (*Q).rear)
		return ERROR;
	*e = (*Q).base[(*Q).front];
	(*Q).front = ((*Q).front + 1) % MAXQSIZE;
	return OK;
}

void QueueTraverse_CSq(CSqQueue Q, void(Visit)(QElemType_CSq))
{
	//访问队列
	int i = Q.front;
	while (i != Q.rear)
	{
		Visit(Q.base[i]);
		i = (i + 1) % MAXQSIZE;
	}
}
void main()
{

}
