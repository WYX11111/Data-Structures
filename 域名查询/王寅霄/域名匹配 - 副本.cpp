#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* ElemType;
typedef int BOOL;
 
#define TRUE 1
#define FALSE 0

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

//SqStack 为存储网址信息的栈，其存储的内容为"www" "baidu" "com"等
//Stack_T 为储存节点地址的栈，在删除节点时使用

//以下内容为SqStack操作
typedef struct {
   ElemType *elem;
   int top;
   int stacksize;
   int incrementsize;
} SqStack;

typedef struct CSNode{
	char *data;
	struct CSNode* firstchild;
	struct CSNode* nextsibling;	
}CSNode,*CSTree;

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
	strcpy(e, S.elem[S.top]);
	return TRUE; 
}

void Push_Sq(SqStack &S, ElemType e)
{
	S.top++;
	S.elem[S.top] = new char [10];
	strcpy(S.elem[S.top],e);
}

BOOL Pop_Sq(SqStack &S, ElemType &e)
{
	if(S.top == -1)
		return FALSE;
	strcpy(e, S.elem[S.top]);
	S.top--;
	return TRUE;
}

BOOL StackEmpty_Sq(SqStack S)
{
   if(S.top == -1)
     return TRUE;
   else
     return FALSE;
}

int StackLength_Sq(SqStack S)
{
	return (S.top + 1);
}

void TraverseStack(SqStack S)
{
	for(int k = S.top; k >= 0; k--)
	{
		printf("%s.",S.elem[k]);
	}
}

//以下内容为Stack_T操作
typedef CSNode* TElemType;
typedef struct {
   TElemType *elem;
   int top;
   int stacksize;
   int incrementsize;
} Stack_T;

void InitStack_T(Stack_T &S, int maxsize = STACK_INIT_SIZE, int incresize = STACKINCREMENT)
{
	S.elem = new TElemType[maxsize];
	S.top = -1;
	S.stacksize = maxsize;
	S.incrementsize = incresize;
}

BOOL GetTop_T(Stack_T S, TElemType &e)
{
	if(S.top == -1)
		return FALSE;
	e = S.elem[S.top];
	return TRUE; 
}

void Push_T(Stack_T &S, TElemType e)
{
	S.top++;
	S.elem[S.top] = e;
}

BOOL Pop_T(Stack_T &S, TElemType &e)
{
	if(S.top == -1)
		return FALSE;
	e = S.elem[S.top];
	S.top--;
	return TRUE;
}

BOOL StackEmpty_T(Stack_T S)
{
   if(S.top == -1)
     return TRUE;
   else
     return FALSE;
}

//以下内容为树形结构的操作
void InitTree_CS(CSTree &T)
{
	T = new CSNode;
	T->data = NULL;
	T->firstchild = NULL;
	T->nextsibling = NULL;
}

void OutPath(CSTree T, SqStack &S) 
{
	char *e;
	e = new char[10];
	while (T != NULL) 
	{
		Push_Sq(S, T->data );
		if(T->firstchild == NULL && strcmp(T->data, "www") == 0)
		{
			TraverseStack(S);
			printf("\b    IP:%s\n",T->nextsibling->data);
		}
		else OutPath( T->firstchild, S);
		Pop_Sq(S,e);
		T = T->nextsibling;
    }
}
CSNode *Add_loction(CSTree T, SqStack &S)
{
	char *a;
	a = new char[10];
	
	CSNode *t = T->firstchild;
	CSNode *s = T;
	CSNode *k;
	
	while(t)
	{
		GetTop_Sq(S, a);
		if(strcmp(t->data, a) != 0)
		
			t = t->nextsibling;
		
		else
		{
			Pop_Sq(S,a);
			s = t;
			t = t->firstchild;
		}
	}

	if(s->firstchild == NULL)
	{
		s->firstchild = new CSNode;
		k = s->firstchild;
	}

	else
	{
		s = s->firstchild;
		k = new CSNode;
		k->firstchild = NULL;
		k->nextsibling = NULL;
		while(s->nextsibling)
			s = s->nextsibling;
		s->nextsibling = k;
	}
	return k;
}

void AddTree_CS(CSTree &T, char *str, SqStack &S)
{
	int i, j, k;
	char *a;
	CSNode *s;
	InitStack_Sq(S);
	for(i = 0; (i > 0 && str[i-1] != '\0') || (i == 0 && str[i] != '\0'); i++)
	{
		a = new char[10];
		for(j = i, k = 0; str[j] != '.' && str[j]; j++,k++,i++)
			a[k] = str[j];
		a[k] = '\0';
		Push_Sq(S, a);
	}

	s = Add_loction(T, S);

	while(!StackEmpty_Sq(S))
	{
		s->data = new char[10];
		Pop_Sq(S,a);

		strcpy(s->data,a);
		
		s->firstchild = NULL;
		s->nextsibling = NULL;
		
		if(!StackEmpty_Sq(S))
		{
			s->firstchild = new CSNode;
			s = s->firstchild;
		}
	}

	s->nextsibling = new CSNode;
	s->nextsibling->data = new char[20];
	printf("输入网站IP:");
	scanf("%s",a);
	strcpy(s->nextsibling->data,a);
	s->nextsibling->firstchild = NULL;
	s->nextsibling->nextsibling = NULL;
}

int Find(CSTree T, char *str, SqStack &S)
{
	InitStack_Sq(S);
	int k,i,j;

	char *a;
	a = new char[10];
	for(i = 0; (i > 0 && str[i-1] != '\0') || (i == 0 && str[i] != '\0'); i++)
	{
		a = new char[10];
		for(j = i, k = 0; str[j] != '.' && str[j]; j++,k++,i++)
			a[k] = str[j];
		a[k] = '\0';
		Push_Sq(S, a);
	}

	CSNode *t = T->firstchild;
	CSNode *s = T;
	
	while(t)
	{
		GetTop_Sq(S, a);
		if(strcmp(t->data, a) != 0)
			t = t->nextsibling;
		else
		{
			if(StackLength_Sq(S) > 1)
			{
				Pop_Sq(S,a);
				s = t;
				t = t->firstchild;
			}
			else
			{
				printf("匹配成功\n\n");
				return 1;
			}
		}
	}
	printf("找不到该站点\n\n");
	return 0;
}

void Delete(CSTree &T, Stack_T &Q)
{
	CSNode *t;
	CSNode *s;
	Pop_T(Q, t);
	GetTop_T(Q ,s);
	if(t->firstchild == NULL && strcmp(t->data, "www") == 0)
	{
		free(t->nextsibling);
		free(t);
		s->firstchild = NULL;
	}
}

int DEL(CSTree &T, char *str, SqStack &S)
{
	Stack_T Q;
	InitStack_Sq(S);
	InitStack_T(Q);

	int k,i,j;

	char *a;
	a = new char[10];
	for(i = 0; (i > 0 && str[i-1] != '\0') || (i == 0 && str[i] != '\0'); i++)
	{
		a = new char[10];
		for(j = i, k = 0; str[j] != '.' && str[j]; j++,k++,i++)
			a[k] = str[j];
		a[k] = '\0';
		Push_Sq(S, a);
	}

	CSNode *t = T->firstchild;
	CSNode *s = T;
	
	while(t)
	{
		GetTop_Sq(S, a);
		if(strcmp(t->data, a) != 0)
			t = t->nextsibling;
		else
		{
			if(StackLength_Sq(S) > 1)
			{
				Pop_Sq(S,a);
				s = t;
				Push_T(Q, t);
				t = t->firstchild;
			}
			else
			{
				Push_T(Q, t);
				printf("已找到站点,删除中....\n");
				Delete(T, Q);
				printf("删除完成\n\n");
				return 1;
			}
		}
	}
	printf("找不到该站点\n\n");
	return 0;
}

int main()
{
	int i;
	CSTree T;
	SqStack S;

	InitTree_CS(T);

	char a[100];

	while(TRUE)
	{
		printf("选择功能:\n");
		printf("1.输入添加网址及IP\n");
		printf("2.匹配网址\n");
		printf("3.删除网址\n");
		printf("4.输出所有网址以及IP\n");

		scanf("%d",&i);
		getchar();
		if(i == 1)
		{
			printf("输入网址:");
			scanf("%s",a);
			AddTree_CS(T, a, S);
			S.top = -1;
		}
		if(i == 2)
		{
			printf("输入网址:");
			scanf("%s",a);
			Find(T, a, S);
			S.top = -1;
		}
		if(i == 3)
		{
			printf("输入网址:");
			scanf("%s",a);
			DEL(T, a, S);
			S.top = -1;
		}
		if(i == 4)
		{
			OutPath(T->firstchild, S);
			S.top = -1;
			printf("\n");
		}
	}
	return 0;
}