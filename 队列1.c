#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#define M 100

typedef struct
{
	int elem[M];
	int *rear;
	int front;
}SqQueue;

 SqQueue InitQueue(SqQueue &Q)
{
	Q.rear = (int*)malloc(M*sizeof(int));
	Q.front=0;
	return Q;
}

 void EnQueue(SqQueue &Q,int e)
 {

		Q.front++;
		for(int i=Q.front;i>0;i--)
		{
			*(Q.rear + i) = *(Q.rear+i-1);
		}
		*Q.rear = e;

 }
 void DeQueue(SqQueue &Q)
 {
	 Q.front--;
	 printf("%d\n",*(Q.rear+Q.front));

 }
void main()
{
	SqQueue InitQueue(SqQueue &Q);
	void EnQueue(SqQueue &Q,int e);
	void DeQueue(SqQueue &Q);
	int n,e;
	re:printf("1.��ʼ������2.����3.����\n");
	scanf("%d",&n);
	switch(n)
	{
	case 1:
		SqQueue Q;
		InitQueue(Q);
		goto re;
	case 2:
		printf("��Ԫ��e��������\n");
		scanf("%d",&e);
		EnQueue(Q,e);
		goto re;
	case 3:
		DeQueue(Q);
		goto re;
	}

	system("pause");
}
