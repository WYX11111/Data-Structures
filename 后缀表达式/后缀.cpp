#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

typedef char ElemType;
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

void Push_Sq(SqStack &S, ElemType &e)
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

int StackLength_Sq(SqStack S)
{
	return (S.top + 1);
}

int main()
{
	SqStack S;
	InitStack_Sq(S);

	char str[100];

	gets(str);
	
	char str1[100];
	char ch;
	char k[10];
	int i, j = 0, t, n = 0;
	char a, b;

	for(i = 0; str[i]; i++)
	{
		if(str[i] == '+' || str[i] == '-')
		{
			str1[n++] = str[i];
			if(str[i+1] == ' ')
				i++;
		}
		else
		{
			if(str[i] != ' ')
				k[j++] = str[i];

			else
			{
				k[j] = '\0';
				t = atoi(k);
				str1[n++] = t;
				j = 0;
			}
		}
	}
	
	str1[n] = '\0';

	for(i = 0; str1[i]; i++)
	{	
		ch = str1[i];

		if(ch != '+' && ch != '-')
			Push_Sq(S, ch);
		else if(ch == '+')
		{
			Pop_Sq(S,a);
			Pop_Sq(S,b);
			int x = (int)a + (int)b;
			a = char(x);
			Push_Sq(S, a);
		}
		
		else if(ch == '-')
		{
			Pop_Sq(S,a);
			Pop_Sq(S,b);
			int x = (int)a - (int)b;
			a = char(x);
			Push_Sq(S, a);
		}
	}
	Pop_Sq(S,a);

	printf("%d\n",a);

	return 0;
}