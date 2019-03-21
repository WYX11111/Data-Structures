#include <stdio.h>
#include <stdlib.h>

#define maxsize 1000

typedef char ElemType;

typedef struct BiTNode
{
	ElemType data;
	struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

typedef struct seqqueue
{
    BiTree data[maxsize];          /*�����������͵�ָ������*/
    int front,rear;                 /*����ָ�롢��βָ��*/
}SeqQue,*SeQue;

/*��ʼ��ѭ������*/
void InitQue(SeQue Q)
{
    Q->front=Q->rear=0;
}
/*�ж��п�*/
int EmptyQue(SeQue Q)
{
    if(Q->front==Q->rear)
        return 1;
    else
        return 0;
}
/*�����*/
int EnQue(SeQue Q,BiTree T)
{
    if((Q->rear+1)%maxsize==Q->front)
    {
        printf("����������\n");      /*�����������ʧ�ܡ�*/
        return 0;
    }
    else
    {
        Q->rear=(Q->rear+1)%maxsize;
        Q->data[Q->rear]=T;
        return 1;                   /*����гɹ�*/
    }
}
/*������*/
int OutQue(SeQue Q)
{
    if(EmptyQue(Q))                 /*�ж϶����Ƿ�Ϊ��*/
    {
        printf("���пգ�\n");
        return 0;
    }
    else
    {
        Q->front=(Q->front+1)%maxsize;/*��Ϊ�գ������С�*/
        return 1;
    }
}
/*ȡ������Ԫ��*/
BiTree Gethead(SeQue Q)
{
    if(EmptyQue(Q))                  /*�ж϶����Ƿ�Ϊ��*/
        return NULL;
    else
        return Q->data[(Q->front+1)%maxsize];
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

void InOrder_iter(BiTree T,int level)
{
	if(T==NULL)
	return;

	InOrder_iter(T->lchild,level+1);

	printf("%c",T->data);

	InOrder_iter(T->rchild,level+1);
}

int print(BiTree T, int level) {  
    if (T == NULL || level < 0)  
        return 0;
    if (level == 0)
	{
		printf("%c  ",T->data);
		return 1;
	}
	return print(T->lchild, level - 1) + print(T->rchild, level - 1);
}

void Levelorder(BiTree T)
{
    BiTree p;
    SeqQue Q;
    InitQue(&Q);
    if(T!=NULL)
    {
        EnQue(&Q,T);
        while(!EmptyQue(&Q))
        {
            p=Gethead(&Q);
            OutQue(&Q);
            printf("%c ",p->data);
            if(p->lchild!=NULL)
                EnQue(&Q,p->lchild);
            if(p->rchild!=NULL)
                EnQue(&Q,p->rchild);
        }
    }
}

void main()
{
	BiTree T=NULL;
	CreateBiTree(T);
	printf("����\n");
	InOrder_iter(T,1);
	printf("\n");
	printf("����\n");
	Levelorder(T);
	/*int i = 0,j;
	for (i = 0; ; i++) 
	{
		j = print(T,i);
		printf("\n");
		if (j == 0)
			break;
	} */
}
