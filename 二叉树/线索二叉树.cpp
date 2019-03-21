#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;

typedef struct BiThrNode {
      ElemType data;
      struct BiThrNode *lchild, *rchild;  // ����ָ��
      struct BiThrNode *pred, *succ;      // ����ǰ�������ң��������
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
  // ���Ը�ָ��p��ָ��������������������ڱ��������н���������
  // pΪ��ǰָ�룬pre�Ǹ���ָ�룬��p��һ�ı���ȫ������
	if(p)
	{
		InThreading(p->lchild,pre);          // ������������
        pre->succ = p;  p->pred = pre;       // ������������ʱ��preΪ�������������ʱ�����һ�����
        pre = p;                             // ����preָ���β�p��ǰ��
        InThreading(p->rchild,pre);          //������������
	}
} // InThreading

void InOrderThreading(BiThrTree &H, BiThrTree T)
{
   // ������ָ��T��ָ������������ȫ��������Hָ������������ͷ���
	BiThrTree pre;
	H = new BiThrNode;                              // �������������ͷ���
	H->lchild = T;  H->rchild = NULL;
	if (!T) 
	{
		H->pred = H;  
		H->succ = H;
	}// ����ͷ��������ָ��ͷ��㱾��
  
	else 
	{
		pre = H;
		InThreading(T,pre);
		//�Զ�������������������ڱ��������н���������
		pre->succ = H;  H->pred = pre; // ��ʱ��preָ��������������һ�����,ͼ6.2�о��ǽ��F,F(pre)�ĺ����H��H��ǰ��(pre)
	}
} // InOrderThreading

void InOrder(BiThrTree H)
{
   // H Ϊָ����������������ͷ����ָ�룬
   // ���㷨���������H->lchild��ָ���Ϊ���Ķ�����
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