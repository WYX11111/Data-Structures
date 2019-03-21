#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;
typedef int BOOL;
 
#define TRUE 1
#define FALSE 0

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef struct 
{
   ElemType *elem;
   int top;
   int stacksize;
   int incrementsize;
} SqStack;

typedef struct 
{
    int weight;
	int lchild,rchild;
	int parent;
} HTNode;

typedef struct 
{
    HTNode *HTree; 
    int root;
	int h;
} HuffmanTree;

typedef char ** HuffmanCode;

// 栈的操作
void InitStack_Sq(SqStack &S, int maxsize = STACK_INIT_SIZE, int incresize = STACKINCREMENT)
{
	S.elem = new ElemType[maxsize];
	S.top = -1;
	S.stacksize = maxsize;
	S.incrementsize = incresize;
}

BOOL GetTop_Sq(SqStack S, ElemType &e)
{
	if(S.top == -1)
		return FALSE;
	e = S.elem[S.top];
	return TRUE; 
}

void Push_Sq(SqStack &S, ElemType e)
{
	S.elem[++S.top] = e;
}

BOOL Pop_Sq(SqStack &S, ElemType &e)
{
	if(S.top == -1)
		return FALSE;
	e = S.elem[S.top--];
	return TRUE;
}

int StackLength_Sq(SqStack S)
{
	return (S.top + 1);
}

BOOL StackEmpty_Sq(SqStack S)
{
   if(S.top == -1)
     return TRUE;
   else
     return FALSE;
}

//哈夫曼树的操作
void Select(HTNode *HT, int i, int &s1, int &s2)
{
	int j,k=0;

	while(HT[k].parent != -1)
		k++;
	s1 = k;
	
	for(j = 0; j < i; j++)
		if(HT[j].parent == -1 && HT[j].weight < HT[s1].weight)
			s1 = j;
	k = 0;
	
	while((HT[k].parent != -1 || k == s1))
		k++;
	
	s2 = k;

	for(j = 0; j < i; j++)
		if(HT[j].parent == -1 && HT[j].weight < HT[s2].weight && j != s1)
			s2 = j;
}

void StackCopytoArray(SqStack S,HuffmanCode HC, int i)
{
	int j = S.top;
	int k = 0;
	while(j >= k)
	{
		HC[i][k] = S.elem[k];
		k++;
	}
	HC[i][k] = '\0';
}

void Coding(HuffmanTree &HT, int i, SqStack &S, HuffmanCode HC)
{
	HT.h = 0;
	char e;
	if (HT.HTree) 
	{
		if ((HT.HTree[i].lchild==-1) && (HT.HTree[i].rchild==-1))
		{  //叶子结点 
			HC[i] = new char[StackLength_Sq(S)];
			if(HT.h < S.top + 1)
				HT.h = S.top + 2;
			StackCopytoArray(S,HC,i);
		}
		else
		{
		   Push_Sq( S,'0');
		   Coding(HT,HT.HTree[i].lchild,S,HC);
		   Pop_Sq( S, e );
		   Push_Sq( S,'1');
		   Coding(HT,HT.HTree[i].rchild,S,HC);
		   Pop_Sq( S, e );
		}
	}
}

void Create(HuffmanTree &HT,  int *w,  int n) 
{
	int i,m,s1,s2;

	if (n<=1)  
		return;

	m = 2 * n - 1;
	HT.HTree = new HTNode[m];
	
	for (i = 0; i < n; i++)
	{
		HT.HTree[i].weight = w[i];
		HT.HTree[i].lchild = -1;
		HT.HTree[i].rchild = -1;
		HT.HTree[i].parent = -1;
	}

	for ( ; i < m; i++) 
	{
		HT.HTree[i].weight = 0;
		HT.HTree[i].lchild = -1;
		HT.HTree[i].rchild = -1;
		HT.HTree[i].parent = -1;
	}

	for (i = n; i < m; i++)
	{
		Select(HT.HTree, i, s1, s2);
		HT.HTree [i].lchild = s1;
		HT.HTree[i].rchild = s2;
		HT.HTree[s1].parent = i;
		HT.HTree[s2].parent = i;
		HT.HTree[i].weight  = HT.HTree[s1].weight + HT.HTree[s2].weight;  
	}
/*	for(i=0;i<m;i++)
	{
		printf("\n%d:%d",i+1,HT.HTree[i]);
	}
*/
	HT.root = m-1;

	HuffmanCode	HC = new char *[n];

	SqStack S;
	InitStack_Sq(S);

	Coding(HT,HT.root,S,HC);

	for(int k = 0; k < n; k++)
	{
		printf("\nHT[%d]: %s",k,HC[k]);
	}

	//树的高度
	printf("\n树的高度:%d\n",HT.h);
}

void main()
{
	HuffmanTree HT;
	int i, n;
	int *w;
	w = new int[100];

	printf("构建哈夫曼树\n");
	printf("请输入哈弗曼树元素的个数：");
	scanf("%d",&n);
	for(i = 0; i < n; i++)
	{
		printf("请输入第%d个元素的权值:",i+1);
		scanf("%d",&w[i]);
	}
	Create(HT, w, n);
}