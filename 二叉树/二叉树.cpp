#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;

typedef struct BiTNode
{
	ElemType data;
	struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

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

void main()
{
	BiTree T=NULL;
	CreateBiTree(T);
/*	printf("中序\n");
	InOrder_iter(T,1);
	printf("\n");
	printf("按层\n");

	int i = 0,j;
	for (i = 0; ; i++) 
	{
		j = print(T,i);
		printf("\n");
		if (j == 0)
			break;
	}  
*/
	int a = leaf_num(T);
	printf("\n%d\n",a);
}


/*
ABC##D##EH##GI###
         A
	B          E
C       D   H     G
               I     
*/
