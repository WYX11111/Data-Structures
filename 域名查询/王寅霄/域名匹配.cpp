#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* ElemType;
typedef int BOOL;
 
#define TRUE 1
#define FALSE 0

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

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

void TraverseStack(SqStack S)
{
	for(int k = S.top; k >= 0; k--)
	{
		printf("%s.",S.elem[k]);
	}
}

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

	CSNode *t = T->firstchild;

	if(t != NULL)
	{
		while(t->nextsibling)
			t = t->nextsibling;
	
		t->nextsibling = new CSNode;
		s = t->nextsibling;
	}
	else 
	{
		T->firstchild = new CSNode;
		s = T->firstchild;
	}

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

int match(CSTree T, SqStack S)
{
	CSNode *t = T->firstchild;
	char *a;
	a = new char[10];

	while(!StackEmpty_Sq(S))
	{
		Pop_Sq(S,a);
		if(strcmp(t->data, a) != 0)
			return 0;
		else
			t = t->firstchild;
	}
	return 1;
}

void Find(CSTree T, char *str, SqStack &S)
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
	Pop_Sq(S, a);
	
	CSNode *t = T->firstchild;

	while(t)
	{
		if(strcmp(t->data, a) == 0)
		{
			k = match(t, S);
			if(k == 1)
			{
				while(t->firstchild)
					t = t->firstchild;
				printf("匹配完成,IP:%s\n\n",t->nextsibling->data);
				break;
			}
			else
				t = t->nextsibling;
		}
		else
			t = t->nextsibling;
	}
	if(t == NULL)
		printf("找不到该站点\n\n");
}

void DEL(CSTree &T, char *str, SqStack &S)
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
	Pop_Sq(S, a);
	
	CSNode *t = T->firstchild;

	while(t)
	{
		if(strcmp(t->data, a) == 0)
		{
			k = match(t, S);
			if(k == 1)
				break;
			else
				t = t->nextsibling;
		}
		else
			t = t->nextsibling;
	}
	if(t == NULL)
		printf("找不到该站点\n\n");

	else
	{
		if(t == T->firstchild)
			T->firstchild = t->nextsibling;
		else
		{
			CSNode *s = T->firstchild;
			while(s->nextsibling != t)
				s = s->nextsibling;
			s->nextsibling = t->nextsibling;
		}
	printf("已删除该网址\n");
	}
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
		}
	}
	return 0;
}
