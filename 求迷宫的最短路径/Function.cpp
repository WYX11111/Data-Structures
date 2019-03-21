#include <stdio.h>

typedef struct
{
	int xpos;
	int ypos;
}PosType;

typedef struct DQNode
{
	PosType seat;
	struct DQNode *next;
	struct DQNode *pre;
}DQNode, *DqueuePtr;

typedef struct 
{
	DqueuePtr front;
	DqueuePtr rear;
}DLinkQueue;

void InitQueue(DLinkQueue &Q)
{
	Q.front = NULL;
	Q.rear = NULL;
}

void EnQueue(DLinkQueue &Q, PosType e)
{
	DqueuePtr p = new DQNode;
	
	p->seat.xpos = e.xpos;
	p->seat.ypos = e.ypos;
	p->next = NULL;
	
	if(!Q.rear)
	{
		p->pre = NULL;
		Q.rear = p;
		Q.front = p;
	}
	else
	{
		p->pre = Q.front;
		Q.rear->next = p;
		Q.rear = p;
	}
}

void GetHead(DLinkQueue Q, PosType &e)
{
	e.xpos = Q.front->seat.xpos;
	e.ypos = Q.front->seat.ypos;
}

void DeQueue(DLinkQueue &Q)
{
	Q.front = Q.front->next;
}

bool QueueEmpty(DLinkQueue Q)
{
	return(Q.front == NULL);
}


#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef struct {
   PosType *elem;
   int top;
   int stacksize;
   int incrementsize;
} SqStack;

void InitStack_Sq(SqStack &S, int maxsize = STACK_INIT_SIZE, int incresize = STACKINCREMENT)
{
	S.elem = new PosType[maxsize];
	S.top = -1;
	S.stacksize = maxsize;
	S.incrementsize = incresize;
}

bool GetTop_Sq(SqStack S, PosType &e)
{
	if(S.top == -1)
		return false;
	e.xpos = S.elem[S.top].xpos;
	e.ypos = S.elem[S.top].ypos;
	return true;
}

void Push_Sq(SqStack &S, PosType e)
{
	++S.top;
	S.elem[S.top] = e;
	S.elem[S.top].xpos = e.xpos;
	S.elem[S.top].ypos = e.ypos;
}

bool Pop_Sq(SqStack &S, PosType &e)
{
	if(S.top == -1)
		return false;
	e.xpos = S.elem[S.top].xpos;
	e.ypos = S.elem[S.top].ypos;
	S.top--;
	return true;
}

bool StackEmpty_Sq(SqStack S)
{
   if(S.top == -1)
     return true;
   else
     return false;
}
/*test
void main()
{
	DLinkQueue Q;
	InitQueue(Q);
	PosType a,b,c;
	a.xpos = 1;
	a.ypos = 1;
	b.xpos = 2;
	b.ypos = 2;

	EnQueue(Q, a);
	EnQueue(Q, b);
	GetHead(Q, c);
	printf("%d %d\n",c.xpos,c.ypos);
	DeQueue(Q);
	GetHead(Q, c);
	printf("%d %d\n",c.xpos,c.ypos);

	SqStack S;
	InitStack_Sq(S);

	Push_Sq(S, a);
	Pop_Sq(S, b);
	printf("%d %d",b.xpos,b.ypos);
}*/