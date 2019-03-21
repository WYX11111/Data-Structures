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
	for(int k = 0; k <= S.top; k++)
	{
		printf("%s.",S.elem[k]);
	}

}
/*
typedef struct {
   CSTree *e;
   int top;
   int stacksize;
   int incrementsize;
} Stack_T;
void InitStack_T(Stack_T &S, int maxsize = STACK_INIT_SIZE, int incresize = STACKINCREMENT)
{
	S.elem = new CSTree[maxsize];
	S.top = -1;
	S.stacksize = maxsize;
	S.incrementsize = incresize;
}

BOOL GetTop_T(Stack_T S, CSTree &e)
{
	if(S.top == -1)
		return FALSE;
	e = S.elem[S.top];
	return TRUE;
}

void Push_T(Stack_T &S, CSTree e)
{
	S.top++;
	S.elem[S.top] = e;
}

BOOL Pop_T(Stack_T &S, CSTree &e)
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
*/
void InitTree_CS(CSTree &T)
{
	T = new CSNode;
	T->data = NULL;
	T->firstchild = NULL;
	T->nextsibling = NULL;
}

void create(CSNode *T, SqStack S)
{
	char *a;
	a = new char[10];
	CSNode *t = T->firstchild;
	if(t == NULL)
	{
		while(!StackEmpty_Sq(S))
		{
			t = new CSNode;
			t->data = new char[10];
			Pop_Sq(S, a);
			strcpy(t->data, a);
			t->firstchild = NULL;
			t->nextsibling = NULL;
			t = t->firstchild;
		}
	}
	else
	{
		while(t)
			t = t->nextsibling;
		while(!StackEmpty_Sq(S))
		{
			t = new CSNode;
			t->data = new char[10];
			Pop_Sq(S, a);
			strcpy(t->data, a);
			t->firstchild = NULL;
			t->nextsibling = NULL;
			t = t->firstchild;
		}
	}
}

CSNode *Find(CSNode *T, char *str)
{
	CSNode *t = T->firstchild;
	while(t)
	{
		if(strcmp(str, T->data) == 0)
			return t;
		else t = t->nextsibling;
	}
	return NULL;
}

void OutPath(CSTree T, SqStack &S) 
{
	char *e;
	e = new char[10];
	while (T != NULL) 
	{
		Push_Sq(S, T->data );
		if(T->firstchild == NULL && strcmp(T->data, "www") == 0)
			TraverseStack(S);
		else OutPath( T->firstchild, S);
		Pop_Sq(S,e);
		T = T->nextsibling;
    }
}

void AddTree_CS(CSTree &T, char *str)
{
	int i, j, k;
	char *a;
	SqStack S;
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

	GetTop_Sq(S, a);
	CSNode *t = Find(T, a);

	if(t != NULL)
	{
		while(t != NULL)
		{
			s = t;
			Pop_Sq(S, a);
			GetTop_Sq(S, a);
			t = Find(t, a);
		}
		create(s, S);
		printf("123123");
	}
	else 
	{
		create(T, S);
		printf("312312");
	}
	//OutPath(T->firstchild,S);
	//printf("%s",T->firstchild->data);
}

int main()
{
	CSTree T;
	InitTree_CS(T);

	char a[100];
	scanf("%s",a);
	AddTree_CS(T, a);
	scanf("%s",a);
	AddTree_CS(T, a);
	scanf("%s",a);
	AddTree_CS(T, a);
	return 0;
}