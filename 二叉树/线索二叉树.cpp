#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;

typedef struct BiThrNode {
      ElemType data;
      struct BiThrNode *lchild, *rchild;  // 左、右指针
      struct BiThrNode *pred, *succ;      // （左）前驱、（右）后继线索
} BiThrNode, *BiThrTree;

void CreateBiTree(BiThrTree &T)
{
    char ch;
    scanf("%c",&ch);

    if (ch == '#')
		T = NULL;
    else
    {
        T = new BiThrNode;
        T->data = ch;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);    
    }
}

void InThreading(BiThrTree p,BiThrTree &pre)
{
  // 对以根指针p所指二叉树进行中序遍历，在遍历过程中进行线索化
  // p为当前指针，pre是跟随指针，比p慢一拍遍历全二叉树
	if(p)
	{
		InThreading(p->lchild,pre);          // 左子树线索化
        pre->succ = p;  p->pred = pre;       // 建立线索，此时的pre为中序遍历左子树时的最后一个结点
        pre = p;                             // 保持pre指向形参p的前驱
        InThreading(p->rchild,pre);          //右子树线索化
	}
} // InThreading

void InOrderThreading(BiThrTree &H, BiThrTree T)
{
   // 建立根指针T所指二叉树的中序全线索链表，H指向该线索链表的头结点
	BiThrTree pre;
	H = new BiThrNode;                              // 创建线索链表的头结点
	H->lchild = T;  H->rchild = NULL;
	if (!T) 
	{
		H->pred = H;  
		H->succ = H;
	}// 空树头结点的线索指向头结点本身
  
	else 
	{
		pre = H;
		InThreading(T,pre);
		//对二叉树进行中序遍历，在遍历过程中进行线索化
		pre->succ = H;  H->pred = pre; // 此时的pre指向中序遍历的最后一个结点,图6.2中就是结点F,F(pre)的后继是H，H的前驱(pre)
	}
} // InOrderThreading

void InOrder(BiThrTree H)
{
   // H 为指向中序线索链表中头结点的指针，
   // 本算法中序遍历以H->lchild所指结点为根的二叉树
	BiThrTree p = H->succ;
	while( p!=H )
    { 
       printf("%c",p->data);
       p = p-> succ;
    }
}  // InOrder

void main()
{
	BiThrTree T,H;
	CreateBiTree(T);
	InOrderThreading(H,T);
	InOrder(H);
}