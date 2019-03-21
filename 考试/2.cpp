#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
 
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

typedef int BOOL;


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

BiTree search(BiTree &T, char ch)
{
	BiTree p = NULL;
    if(T == NULL)
        return NULL;
    if(T->data == ch)
        return T;
    if(p = search(T->lchild,ch))
        return p;
    return search(T->rchild,ch);
}

void BiTreeDepth(BiTree T , int h, int &depth) 
{ 
    if(T)
	{
        if (h>depth)
			depth = h;
        BiTreeDepth( T->lchild, h+1, depth );
        BiTreeDepth( T->rchild, h+1, depth );
    } 
}

void main()
{
	int d1, d2;
	BiTree T=NULL;
	CreateBiTree(T);
	getchar();
	char ch;
	printf("待查找的元素X");
	
    scanf("%c",&ch);

	T = search(T,ch);

	printf("%c",T->data);
	
	d1=0;
	d2=0;
	BiTreeDepth(T->lchild,1,d1);
	BiTreeDepth(T->rchild,1,d2);

	printf("深度差为:%d",d1-d2);

}
