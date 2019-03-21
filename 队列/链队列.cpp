#include<stdio.h>
#include<stdlib.h>

typedef int Boolean;
typedef char QElemType;
#define TRUE 1;
#define FALSE 0;

typedef struct LNode
{
	QElemType data;
	struct LNode *next;
}LNode, *LinkList;     //�����е�ÿһ���ڵ�

typedef LinkList QueuePtr;

typedef struct
{
	QueuePtr front;
	QueuePtr rear;
} LinkQueue;   //������

void InitQueue(LinkQueue &Q)
{
	//����һ��ֻ��ͷ�ڵ�Ŀն���
	Q.front = Q.rear = new LNode;
	Q.front->next = NULL;
}

void EnQueue(LinkQueue &Q, QElemType e)
{
	LNode *p = new LNode;
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
}

Boolean DeQueue(LinkQueue &Q, QElemType &e)
{
	if(Q.front == Q.rear)
		return FALSE;

	LNode *p = Q.front->next;

	e = p->data;
	Q.front->next = p->next;
	if(Q.rear == p)
	Q.rear = Q.front;
	delete p;
	return TRUE;
}

Boolean QueueEmpty(LinkQueue Q)
{
	if(Q.front == Q.rear)
		return TRUE;
	return FALSE;
}