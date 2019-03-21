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
		p->pre = Q.rear;
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

int main()
{
	DLinkQueue Q;
	InitQueue(Q);
	int i, x, y;
	PosType a;
	while(1)
	{
		scanf("%d",&i);
		if(i == 1)
		{
			printf("+");
			scanf("%d %d",&x,&y);
			printf("%d %d\n",x,y);
			//EnQueue(Q, a);
			printf("11111111111");

		}
		if(i == 2)
		{
			printf("-");
			DeQueue(Q);
			GetHead(Q,a);
			printf("%d %d\n",a.xpos,a.ypos);
		}
		if(i == 3)
			printf("%d\n",QueueEmpty(Q));
		
	}
}