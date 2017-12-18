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
typedef int QElemType_L;

typedef struct
{
	QElemType_L data;
	struct QNode *next;
}QNode;
typedef QNode* QueuePtr;
typedef struct
{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

Status InitQueue_L(LinkQueue *Q)
{
	//初始化链队Q
	(*Q).front = (*Q).rear = (QueuePtr)malloc(sizeof(QNode));
	if (!(*Q).front)
		exit(OVERFLOW);
	(*Q).front->next = NULL;
	return OK;
}

void ClearQueue_L(LinkQueue *Q)
{
	//置空Q
	(*Q).rear = (*Q).front->next;
	while ((*Q).rear)
	{
		(*Q).front->next = (*Q).rear->next;
		free((*Q).rear);
		(*Q).rear = (*Q).front->next;
	}
	(*Q).rear = (*Q).front;
}

void DestroyQueue_L(LinkQueue *Q)
{
	//销毁Q
	while ((*Q).front)
	{
		(*Q).rear = (*Q).front->next;
		free((*Q).front);
		(*Q).front = (*Q).rear;
	}
}

Status QueueEmpty_L(LinkQueue Q)
{
	//判断Q是否为空
	if (Q.front == Q.rear)
		return TRUE;
	else
		return FALSE;
}

int QueueLength_L(LinkQueue Q)
{
	//返回Q元素个数
	int count = 0;
	QueuePtr p = Q.front;
	while (p != Q.rear)
	{
		count++;
		p = p->next;
	}
	return count;
}

Status GetHead_L(LinkQueue Q, QElemType_L *e)
{
	//用e获取队头元素
	QueuePtr p;
	if (Q.front == Q.rear)
		return ERROR;
	p = Q.front->next;
	*e = p->data;
	return OK;
}

Status EnQueue_L(LinkQueue *Q, QElemType_L e)
{
	//元素e入队
	QueuePtr p;
	p = (QueuePtr)malloc(sizeof(QNode));
	if (!p)
		exit(OVERFLOW);
	p->data = e;
	p->next = NULL;
	(*Q).rear->next = p;
	(*Q).rear = p;
	return OK;
}

Status DeQueue_L(LinkQueue *Q, QElemType_L *e)
{
	//元素e出队
	QueuePtr p;
	if ((*Q).front == (*Q).rear)
		return ERROR;
	p = (*Q).front->next;
	*e = p->data;
	(*Q).front->next = p->next;
	if ((*Q).rear == p)
		(*Q).rear = (*Q).front;
	free(p);
	return OK;
}

void QueueTraverse_L(LinkQueue Q, void(Visit)(QElemType_L))
{
	//访问队列
	QueuePtr p;
	p = Q.front->next;
	while (p)
	{
		Visit(p->data);
		p = p->next;
	}
}
void main()
{

}
