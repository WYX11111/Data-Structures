#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1000

typedef int ElemType;

typedef struct{
	int i,j;
	ElemType e;
} Triple;

typedef struct{
	Triple data[MAXSIZE+1]; //data[0]不用
	int mu,nu,tu;           //行数，列数，值的个数
} TSMatrix;

void InitT(TSMatrix &T)
{
	int num;
	printf("输入三元组的行数、列数和非零元素个数");
	scanf("%d %d %d",&T.mu, &T.nu, &T.tu);
	for (num = 1; num <= T.tu; num++)
	{
		printf("输入第%d元素的行数：",num);
		scanf("%d",&T.data[num].i);
		printf("输入第%d元素的列数：",num);
		scanf("%d",&T.data[num].j);
		printf("输入第%d元素的值：  ",num);
		scanf("%d",&T.data[num].e);
	}
}

void print(TSMatrix T)
{
	int num;
	printf("  %d\t%d\t%d\n",T.mu,T.nu,T.tu);
	for (num = 1; num <= T.tu; num++)
		printf("  %d\t%d\t%d\n",T.data[num].i,T.data[num].j,T.data[num].e);
}

void add(TSMatrix Ta, TSMatrix Tb, TSMatrix &Tc)
{
	int num, num1;
	
	Tc.mu = Tb.mu; Tc.nu = Tb.nu; Tc.tu = Tb.tu;

	for (num = 1; num <= Ta.tu; num++)
	{
		Tc.data[num].i = Tb.data[num].i;
		Tc.data[num].j = Tb.data[num].j;
		Tc.data[num].e = Tb.data[num].e;
	}
	for (num = 1; num <= Ta.tu; num++)
	{
		for (num1 = 1; num1 <= Tb.tu; num1++)
			if (Tb.data[num1].i == Ta.data[num].i && Tb.data[num1].j == Ta.data[num].j)
			{
				Tc.data[num].e = Tb.data[num1].e + Ta.data[num].e;
				break;
			}
		if (num1 > Tb.tu)
		{
			Tc.tu++;
			Tc.data[Tc.tu].i = Ta.data[num].i;
			Tc.data[Tc.tu].j = Ta.data[num].j;
			Tc.data[Tc.tu].e = Ta.data[num].e;
		}
	}
}

void main()
{
	TSMatrix Ta,Tb,Tc;

	InitT(Ta);
	printf("矩阵A的三元组为:\n");
	print(Ta);

	InitT(Tb);
	printf("矩阵B的三元组为:\n");
	print(Tb);

	add(Ta,Tb,Tc);
	printf("矩阵A+B的三元组为:\n");
	print(Tc);
}