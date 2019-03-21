#include "╤сап.CPP"

typedef PosType ElemType;

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef struct {
   ElemType *elem;
   int top;
   int stacksize;
   int incrementsize;
} SqStack;

void InitStack_Sq(SqStack &S, int maxsize = STACK_INIT_SIZE, int incresize = STACKINCREMENT)
{
	S.elem = new ElemType[maxsize];
	S.top = -1;
	S.stacksize = maxsize;
	S.incrementsize = incresize;
}

bool GetTop_Sq(SqStack S, ElemType &e)
{
	if(S.top == -1)
		return false;
	e = S.elem[S.top];
	return true; 
}

void Push_Sq(SqStack &S, ElemType e)
{
	S.elem[++S.top] = e;
}

bool Pop_Sq(SqStack &S, ElemType &e)
{
	if(S.top == -1)
		return false;
	e = S.elem[S.top--];
	return true;
}
void DestroyStack_Sq(SqStack &S)
{
	delete S.elem;
	S.top = -1;
	S.stacksize = 0;
}

void ClearStack_Sq(SqStack &S)
{
	S.top = -1;
}

bool StackEmpty_Sq(SqStack S)
{
   if(S.top == -1)
     return true;
   else
     return false;
}

int StackLength_Sq(SqStack S)
{
	return (S.top + 1);
}

/*void StackTraverse_Sq(SqStack S)
{
	int p = S.top;
	while(p!=-1)
		cout << S.elem[p--];
}*/