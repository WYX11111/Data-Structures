#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
 
#define TRUE 1
#define FALSE 0

#define STACK_INIT_SIZE 100

typedef struct {
   double *elem;
   int top;
   int stacksize;
} NUMStack;

typedef struct {
   char *elem;
   int top;
   int stacksize;
} CHARStack;

void InitStack_NUM(NUMStack &S, int maxsize = STACK_INIT_SIZE)
{
	S.elem = new double[maxsize];
	S.top = -1;
	S.stacksize = maxsize;
}

void InitStack_CHAR(CHARStack &S, int maxsize = STACK_INIT_SIZE)
{
	S.elem = new char[maxsize];
	S.top = -1;
	S.stacksize = maxsize;
}

bool GetTop_NUM(NUMStack S, double &e)
{
	if(S.top == -1)
		return FALSE;
	e = S.elem[S.top];
	return TRUE; 
}

bool GetTop_CHAR(CHARStack S, char &e)
{
	if(S.top == -1)
		return FALSE;
	e = S.elem[S.top];
	return TRUE; 
}

void Push_NUM(NUMStack &S, double e)
{
	S.top++;
	S.elem[S.top] = e;
}

void Push_CHAR(CHARStack &S, char e)
{
	S.top++;
	S.elem[S.top] = e;
}

bool Pop_NUM(NUMStack &S, double &e)
{
	if(S.top == -1)
		return FALSE;
	e = S.elem[S.top--];
	return TRUE;
}

bool Pop_CHAR(CHARStack &S, char &e)
{
	if(S.top == -1)
		return FALSE;
	e = S.elem[S.top];
	S.top--;
	return TRUE;
}

bool StackEmpty_NUM(NUMStack S)
{
   if(S.top == -1)
     return TRUE;
   else
     return FALSE;
}

bool StackEmpty_CHAR(CHARStack S)
{
   if(S.top == -1)
     return TRUE;
   else
     return FALSE;
}

int StackLength_NUM(NUMStack S)
{
	return (S.top + 1);
}

int StackLength_CHAR(CHARStack S)
{
	return (S.top + 1);
}

int opmember(char c)
{
	if(c == '+' || c == '-' || c == '*' || c == '/')
		return 1;

	if(c == '(' )
		return 2;
	
	if(c == ')' )
		return 3; 
	
	else
		return 0;
}

int getpre(char c) //设置各个操作符的优先级
{
	if(c == '#' )
		return -1; 
	
	if(c == '(' ) 
		return 0;
	
	if(c == '+' || c == '-') 
		return 1;
	
	if(c == '*'|| c == '/')
		return 2;

	if(c == ')' ) 
		return 3;
}

bool compare(char a,char b)
{
	if(getpre(a) >= getpre(b))
		return 1;
	else
		return 0;
}

bool isnum(char c)
{
	if(c >= '0' && c <= '9')return 1;
	else 
		return 0;
}

bool islogic(char *s) //判断一个表达式是否合法
{
	int len = strlen(s);
	int l=0,r=0;//用于记录括号个数
	
	if(opmember(s[0] == 1 || opmember(s[0]) == 3) )//开头是运算或是右括号，不合法
		return 0;

	if(opmember(s[len-1]) == 1 || opmember(s[len-1] == 2)) //结尾是运算或是左边括号，不合法
		return 0;
	
	for(int i=0; i<len-1; i++)
	{
		if(s[i]=='(') 
			l++;

		if(s[i]==')') 
			r++;

		if(opmember(s[i]) == 3 && isnum (s[i+1]) == 1 )
			return 0; //右括号后直接接数字，不合法

		if(opmember(s[i]) == 1 && opmember(s[i+1]) == 1 )
			return 0; //两个运算符相连，不合法
		
		if(opmember(s[i]) == 1 && opmember(s[i+1]) == 3 )
			return 0; //运算符接右括号，不合法
		
		if(opmember(s[i]) == 2 && opmember(s[i+1]) == 3 )
			return 0; //左括号接右括号，不合法

		if(isnum(s[i]) == 1 && opmember(s[i+1]) == 2) 
			return 0; //数字后接左括号，不合法
		
		if(s[i]=='/' && s[i+1]=='0') 
			return 0; //除0，不合法
	}

	if(s[len-1] == ')' ) 
		r++;

	if(l != r)
		return 0; //左右括号数不相等，不合法
	
	return 1;
}

double operate(double a,char op,double b)
{
	if(op == '+')
		return a+b;
	
	if(op=='-')
		return a-b;
	if(op=='*')
		return a*b;
	if(op=='/')
		return a/b;
}

void transform(CHARStack &op, char *suffix, char *s)
{
	InitStack_CHAR(op);

	Push_CHAR(op,'#');
	
	int i=0,k=0;

	char ch=s[0],c;
	
	while(!StackEmpty_CHAR(op))
	{
		if(isnum(ch))
			suffix[k++]=ch;
		
		else
		{
			suffix[k++]=' ';
			switch(ch)
			{
			case'(':Push_CHAR(op,ch);break;
			
			case')':
				{
					Pop_CHAR(op,c);
					
					while( c != '(' )
					{
						suffix[k++]=c;
						Pop_CHAR(op,c);
					}
					break;
				}
			default:
				{
					while(GetTop_CHAR(op,c) && (compare(c,ch)) )
					{
						suffix[k++] = c;
						Pop_CHAR(op,c);
					}
					if(ch!='#')
						Push_CHAR(op,ch);
					break;
				}//default
			}//switch
		}//else
		if(ch!='#'){
			i++;
			ch=s[i];
		}
	}//while
	suffix[k]='\0';
}//transform

void calculate(NUMStack &num,char *suffix)
{
	double num1,num2,num3,cur,ans;
	int flag;
	InitStack_NUM(num);
	int len = strlen(suffix),i = 0;

	while(i<len)
	{
		if(suffix[i] == ' ')
		{
			i++;
			continue;
		}

		else if(suffix[i]=='#')
			break;
		
		else
		{
			cur=0;
			flag=0;
			
			while(isnum(suffix[i]))
			{
				cur*=10;
				cur+=suffix[i++]-'0';
				flag=1;
			}

			if(flag)
			{
				Push_NUM(num,cur);	
			}	
			if(suffix[i]==' ')
			{
				i++;
				continue;
			}

			if(opmember(suffix[i])==1)
			{
				Pop_NUM(num,num1);

				Pop_NUM(num,num2);

				num3=operate(num2,suffix[i++],num1);

				Push_NUM(num,num3);
			}
		}
	}

	Pop_NUM(num,ans);
	printf("%.2lf\n",ans);
}
int main()
{
	NUMStack num;
	CHARStack op;

	char suffix[101],s[101];

	while(scanf("%s",s)!='\0')
	{
		memset(suffix,0,sizeof(suffix));
		int len=strlen(s);
		if(!islogic(s))
			printf("输入算式有误!\n");
		else
		{
			s[len]='#';
			transform(op,suffix,s);
			calculate(num,suffix);
		}
	}
	return 0;
}