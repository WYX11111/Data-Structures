#include <stdio.h> 
#include <stdlib.h>
 
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

int Stack_Judge(ElemType* arr,ElemType* cur,int len)
{
    int i = 0;
    int j = 0;

    char e;

	if(arr == NULL || cur == NULL)
    {
        return -1;
    }

	SqStack S;
    InitStack_Sq(S);

    while(1)
    {
        if(i < len)
        {
            Push_Sq(S,arr[i++]);
        }

        //比较栈顶元素和测试字符串
		GetTop_Sq(S,e);
        if(e == cur[j])
        {
            Pop_Sq(S, e);//相等，出栈
            j++;

        }
		if(!StackEmpty_Sq(S))//判断当前栈是否为空
        {
			GetTop_Sq(S, e);
			if(e == cur[j])//不为空继续比较栈顶和测试字符串
            {
                Pop_Sq(S, e);
                j++;
            }
        }

        if(i == len)//字符串已全部入栈
        {
            if(!StackEmpty_Sq(S))
            {
				GetTop_Sq(S, e);
                if(e != cur[j])
                {
                    break;
                }
            }
        }

        if(j == len)//测试字符串已遍历完
        {
            break;
        }
    }//while

    if(StackEmpty_Sq(S))//查看当前栈是否为空
    {
        return 1;//YES
    }
    else
    {
        return 0;//NO
    }
}

int main()
{
    char arr[100];
    char cur[100];
	int len;
    printf("输入字符串：");
	scanf("%s",arr);

    for(len = 0; arr[len]; len++);

    printf("输入测试字符串：");
	scanf("%s",cur);

	if(Stack_Judge(arr,cur,len)==1)
		printf("Yes");
	else
		printf("NO");
    return 0;
}
