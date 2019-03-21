#include <stdio.h>
#include <stdlib.h>
 
#define TRUE 1
#define FALSE 0

#define QUEUE_INIT_SIZE 100
#define QUEUEINCREMENT 10

typedef char ElemType;

typedef struct BiTNode
{
	ElemType data;
	struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

typedef BiTree QElemType;

typedef int BOOL;

typedef struct {
   QElemType *elem;
   int front;
   int rear;
   int queuesize;
   int incrementsize;
} SqQueue;

void InitQueue_Sq(SqQueue &Q, int maxsize = QUEUE_INIT_SIZE, int incresize = QUEUEINCREMENT)
{
	Q.elem = new QElemType[maxsize];
	Q.front = 0;
	Q.rear = 0;
	Q.queuesize = maxsize;
	Q.incrementsize = incresize;
}

BOOL GetTop_Sq(SqQueue Q, QElemType &e)
{
	if(Q.rear == Q.front)
		return FALSE;
	e = Q.elem[Q.front];
	return TRUE; 
}

void EnQueue_Sq(SqQueue &Q, QElemType e)
{
	if((Q.rear+1) % Q.queuesize == Q.front)
		return;
	Q.elem[Q.rear] = e;
	Q.rear = (Q.rear+1) % Q.queuesize;
}

BOOL DeQueue_Sq(SqQueue &Q, QElemType &e)
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

void InOrder_iter(BiTree T)
{
	if(T==NULL)
	return;

	InOrder_iter(T->lchild);

	printf("%c",T->data);

	InOrder_iter(T->rchild);
}
void print(BiTree T)
{
	BiTree e = T;
	SqQueue Q;
	InitQueue_Sq(Q);
	EnQueue_Sq(Q,e);
	while(!QueueEmpty_Sq(Q))
	{
		DeQueue_Sq(Q, e);
		if(e->lchild != NULL)
			EnQueue_Sq(Q, e->lchild);
		if(e->rchild != NULL)
			EnQueue_Sq(Q, e->rchild);
		printf("%c",e->data);
	}
}

void BiTreeDepth(BiTree T , int h, int &depth)    //计算深度
{ 
    if(T)
	{
        if (h>depth)
			depth = h;   
        BiTreeDepth( T->lchild, h+1, depth );
        BiTreeDepth( T->rchild, h+1, depth );
    } 
}


int leaf_num(BiTree T)   //计算叶子节点
{
	if (T == NULL)
		return 0;

	if (T->lchild == NULL && T->rchild == NULL)
		return 1;
    return (leaf_num(T->lchild) + leaf_num(T->rchild));
}

int in_num(BiTree T)     //计算内部节点
{
	if(T == NULL)
		return 0;
	else if(T->lchild == NULL && T->rchild == NULL)
		return 0;

    else
		return (1 + in_num(T->lchild) + in_num(T->rchild));;
}




BiTree GetTreeNode(ElemType item, BiTree lptr , BiTree rptr )
{ //生成一个元素值为item，左指针为lptr，右指针为rptr的结点
	BiTree T = new BiTNode;
    T->data = item; 
    T->lchild = lptr; 
    T->rchild = rptr;
    return T;
}

BiTree CopyTree(BiTree T)
{  
	BiTree newlptr,newrptr,newnode;
    if (!T) 
		return NULL; //复制一棵空树
    
	if(T->lchild ) 
        newlptr = CopyTree(T->lchild); //复制（遍历）左子树
    else
		newlptr = NULL;
    
	if (T->rchild ) 
       newrptr = CopyTree(T->rchild); //复制（遍历）右子树
    else  
		newrptr = NULL;
    
	newnode = GetTreeNode(T->data, newlptr, newrptr); //生成根结点
    return newnode;
}


void main()
{
	int d;          //深度
	BiTree T=NULL;
	CreateBiTree(T);
	
	printf("中序\n");
	InOrder_iter(T);
	printf("\n");
	
	printf("按层\n");
	print(T);
	
	d=0;
	BiTreeDepth(T,1,d);
	printf("深度为:%d",d);
}
