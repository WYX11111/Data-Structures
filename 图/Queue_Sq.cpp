#include <stdio.h> 
#include <stdlib.h>
 
typedef int ElemType;
typedef int BOOL;
 
#define TRUE 1
#define FALSE 0

#define QUEUE_INIT_SIZE 100
#define QUEUEINCREMENT 10

typedef struct {
   ElemType *elem;
   int front;
   int rear;
   int queuesize;
   int incrementsize;
} SqQueue;

void InitQueue_Sq(SqQueue &Q, int maxsize = QUEUE_INIT_SIZE, int incresize = QUEUEINCREMENT)
{
	Q.elem = new ElemType[maxsize];
	Q.front = 0;
	Q.rear = 0;
	Q.queuesize = maxsize;
	Q.incrementsize = incresize;
}

BOOL GetTop_Sq(SqQueue Q, ElemType &e)
{
	if(Q.rear == Q.front)
		return FALSE;
	e = Q.elem[Q.front];
	return TRUE; 
}

void EnQueue_Sq(SqQueue &Q, ElemType e)
{
	if((Q.rear+1) % Q.queuesize == Q.front)
		return;
	Q.elem[Q.rear] = e;
	Q.rear = (Q.rear+1) % Q.queuesize;
}

BOOL DeQueue_Sq(SqQueue &Q, ElemType &e)
{
	if(Q.rear == Q.front)
		return FALSE;
	e = Q.elem[Q.front];
	Q.front = (Q.front + 1) % Q.queuesize;
	return TRUE;
}

BOOL QueueEmpty_Sq(SqQueue Q)
{
   if(Q.rear == Q.front)
     return TRUE;
   else
     return FALSE;
}

int QueueLength_Sq(SqQueue Q)
{
	return (Q.rear - Q.front + Q.queuesize) % Q.queuesize;
}
