#include<iostream>
#include<cstdlib>
#include<cstdio>
#define MaxSize 1000
using namespace std;
 
typedef char TElemType;
 
typedef struct BiTNode
{
	TElemType data;
	int layer;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
struct Queue
{
	BiTree *data;
	int front,rear,size;
}q;
 
void push(BiTree T)
{
	q.data[q.rear++]=T;
	if(q.rear>=q.size)
	{
		cout<<"no space"<<endl;
		exit(-1);
	}
}
 
BiTree pop()
{
	if(q.front>=q.rear)
	{
		cout<<"error"<<endl;
		exit(-1);
	}	
	return q.data[q.front++];
}
 
bool empty()
{
	if(q.front>=q.rear)
		return 1;
	return 0;
}
 
int Max(int x,int y)
{
	return (x>y)?x:y;
}
 
void CreatBiTree(BiTree &T)
{
	char ch;
	cin>>ch;
	if(ch=='#')
	{
		T=NULL;
		return ;
	}
	T= new BiTNode;
	if(!T)
	{
		cout<<"no space"<<endl;
		exit(-1);
	}
	T->data=ch;
	T->lchild=NULL;
	T->rchild=NULL;
	CreatBiTree(T->lchild);
	CreatBiTree(T->rchild);
}
 
int CountDeepth(BiTree T)
{
	if(!T)
		return 0;
	return Max(CountDeepth(T->lchild),CountDeepth(T->rchild))+1;
}
 
void PrintTree(BiTree T,int deepth)
{
	int pre=0,flag=1;
	q.data=(BiTree*)malloc(MaxSize*sizeof(BiTree));
	q.front=q.rear=0;
	q.size=MaxSize;
	T->layer=0;
	push(T);
	while(1)
	{
		BiTree node=pop();
		if(node->layer>=deepth)
			break; 
		if(pre!=node->layer||flag)
		{
			cout<<endl;
			for(int i=1;i<(1<<(deepth-node->layer));i++)
				cout<<' ';
			cout<<node->data;
			pre=node->layer;
			flag=0;
		}
		else
		{
			for(int i=1;i<(1<<(deepth-node->layer+1));i++)
				cout<<' ';
			cout<<node->data;
		}
		if(node->lchild)
		{
			node->lchild->layer=node->layer+1;
			push(node->lchild);
		}
		else
		{
			BiTree node_null=(BiTree)malloc(sizeof(BiTNode));
			node_null->layer=node->layer+1;
			node_null->lchild=node_null->rchild=NULL;
			node_null->data=' ';
			push(node_null);
		}
		if(node->rchild)
		{
			node->rchild->layer=node->layer+1;
			push(node->rchild);
		}	
		else
		{
			BiTree node_null=(BiTree)malloc(sizeof(BiTNode));
			node_null->layer=node->layer+1;
			node_null->lchild=node_null->rchild=NULL;
			node_null->data=' ';
			push(node_null);
		}
	}	
}
 
void preorder(BiTree T)
{
	if(!T)
		return ;
	cout<<T->data;
	preorder(T->lchild);
	preorder(T->rchild);
}
 
void inorder(BiTree T)
{
	if(!T)
		return ;
	inorder(T->lchild);
	cout<<T->data;
	inorder(T->rchild);
}
 
void postorder(BiTree T)
{
	if(!T)
		return ;
	postorder(T->lchild);
	postorder(T->rchild);
	cout<<T->data;	
}
	
int main()
{	
	int deepth; 
	BiTree root=NULL;
	CreatBiTree(root);
	deepth=CountDeepth(root);
	PrintTree(root,deepth);
	cout<<endl<<"深度： "<<deepth<<endl;
	cout<<"前序： "; 
	preorder(root);
	cout<<endl<<"中序： ";
	inorder(root);
	cout<<endl<<"后序： ";
	postorder(root);
	cout<<endl;
	return 0;
}
