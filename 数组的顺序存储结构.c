#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

/* ״̬�� */
#define	TRUE		1			//��
#define	FALSE		0			//��
#define	OK			1			//ͨ��
#define	ERROR		0			//����

#define	OVERFLOW	-2			//��ջ����

typedef int Status;

#define MAX_ARRAY_DIM 8   //��������ά��

typedef int AElemType_Sq;
typedef struct    //�����˳��洢��ʾ
{
  AElemType_Sq *base;   //����Ԫ�ػ�ַ
  int dim;              //����ά��
  int *bounds;          //����ά���ַ���������������Ϣ��
  int *constants        //����ӳ����������ַ����ſ�Խĳ��ά��ʱ��ҪԽ����Ԫ�ظ�λ��
}Array;

Status InitArray(Array *A,int dim,...)
{
  
}
