#include <stdio.h> 
#include <stdlib.h>
 
typedef int SElemType;
typedef int BOOL;
 
#define TRUE 1
#define FALSE 0

#define STACK_INIT_SIZE 10
#define STACKINCREMENT 10

typedef struct {
   SElemType *elem;
   int top;
   int stacksize;
   int incrementsize;
} SqStack;

void InitStack_Sq(SqStack &S, int maxsize = STACK_INIT_SIZE, int incresize = STACKINCREMENT)
{
	S.elem = new SElemType[maxsize];
	S.top = -1;
	S.stacksize = maxsize;
	S.incrementsize = incresize;
}

BOOL GetTop_Sq(SqStack S, SElemType &e)
{
	if(S.top == -1)
		return FALSE;
	e = S.elem[S.top];
	return TRUE; 
}

void Push_Sq(SqStack &S, SElemType e)
{
	S.elem[++S.top] = e;
}

BOOL Pop_Sq(SqStack &S, SElemType &e)
{
	if(S.top == -1)
		return FALSE;
	e = S.elem[S.top--];
	return TRUE;
}

void DestroyStack_Sq(SqStack &S)
{
	free(S.elem);
	S.top = -1;
	S.stacksize = 0;
}

void ClearStack_Sq(SqStack &S)
{
	S.top = -1;
}

BOOL StackEmpty_Sq(SqStack S)
{
   if(S.top == -1)
     return TRUE;
   else
     return FALSE;
}

BOOL StackFull_Sq(SqStack S)
{
   if(S.top == STACK_INIT_SIZE-1)
     return TRUE;
   else
     return FALSE;
}

int StackLength_Sq(SqStack S)
{
	return (S.top + 1);
}

void StackTraverse(SqStack S)
{
	int i = 0;
	printf("Garage status (%d cars): \n",StackLength_Sq(S));
	printf("___________________________________________________________\n");
	printf("|I   ");
	while(S.top >= i)
	{
		printf("%d   ",S.elem[i]);
		i++;
	}
	printf("\n___________________________________________________________\n");
}

BOOL ElemInStack(SqStack S, SElemType e)
{
	int i = 0;
	while(S.top >= i)
	{
		if(S.elem[i++] == e)
			return TRUE;
	}
	return FALSE;
}