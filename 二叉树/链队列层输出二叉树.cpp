#include<stdio.h>
#include<stdlib.h>

typedef int Boolean;
typedef char ElemType;

typedef struct BiTNode
{
	ElemType data;
	struct BiTNode *lchild, *rchild;
} *BiTree;

typedef BiTree QElemType;

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

void CreateBiTree(BiTree &T)
{
    char ch;
    scanf("%c",&ch);

    if (ch == '#')
		T = NULL;
    else
    {
        T = (BiTree)malloc(sizeof(BiTNode));
        T->data = ch;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);    
    }
}

void Preorder(BiTree T) //��
{
    if(T)
	{
		printf("%c ",T->data);
		Preorder(T->lchild);
		Preorder(T->rchild);
	}
}

void InOrder(BiTree T) //��
{
	if(T)
	{
		InOrder(T->lchild);
		printf("%c ",T->data);
		InOrder(T->rchild);
	}
}

void Laterorder(BiTree T)  //��
{
    if(T)
	{
		Preorder(T->lchild);
		Preorder(T->rchild);
		printf("%c ",T->data);
	}
}

void print(BiTree T)
{
	BiTree e = T;
	LinkQueue Q;

	InitQueue(Q);
	EnQueue(Q,e);
	while(!QueueEmpty(Q))
	{
		DeQueue(Q, e);
		if(e->lchild != NULL)
			EnQueue(Q, e->lchild);
		if(e->rchild != NULL)
			EnQueue(Q, e->rchild);
		printf("%c ",e->data);
	}
}

void main()
{
	BiTree T=NULL;
	CreateBiTree(T);
	
	printf("����\n");
	Preorder(T);
	printf("\n");

	printf("����\n");
	InOrder(T);
	printf("\n");

	printf("����\n");
	Laterorder(T);
	printf("\n");
	
	printf("�㣺\n");
	print(T);
}