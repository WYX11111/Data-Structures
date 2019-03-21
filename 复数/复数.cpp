#include <stdio.h>

typedef struct{
	double real;
	double image;
}Complex;

Complex jia(Complex a, Complex c);
Complex jian(Complex a, Complex c);
Complex cheng(Complex a, Complex c);
Complex chu(Complex a, Complex c);

int main()
{
	double r1,i1;
	double r2,i2;
	Complex c1;
	Complex c2;
	Complex res;
	int t;

	printf("请输入两个复数进行运算\n");
	printf("输入第一个复数：\n");

	printf("输入实部：");
	scanf("%lf",&r1);

	printf("输入虚部：");
	scanf("%lf",&i1);

	printf("输入第二个复数：\n");

	printf("输入实部：");
	scanf("%lf",&r2);

	printf("输入虚部：");
	scanf("%lf",&i2);

	c1.real = r1;
	c1.image = i1;

	c2.real = r2;
	c2.image = i2;

	printf("选择运算 1(+) or 2(-) or 3(*) or 4(/)\n");

	scanf("%d",&t);

	if(t == 1)
	{
		res = jia(c1,c2);
		printf("结果是");
		printf("%.2lf",res.real);
		printf("+");
		printf("%.2lf",res.image);
		printf("i");

	}
	else if(t == 2)
	{
		res = jian(c1,c2);
   		printf("结果是");
		printf("%.2lf",res.real);
		printf("+");
		printf("%.2lf",res.image);
		printf("i");
	}
	else if(t == 3)
	{
		res = (c1,c2);
		printf("结果是");
		printf("%.2lf",res.real);
		printf("+");
		printf("%.2lf",res.image);
		printf("i");
	}
	else if(t == 4)
	{
		res = chu(c1,c2);
		printf("结果是");
		printf("%.2lf",res.real);
		printf("+");
		printf("%.2lf",res.image);
		printf("i");
	}
return 0;
}

Complex jia(Complex a, Complex c)
{
	Complex res;
    res.real = a.real + c.real;
	res.image = a.image + c.image;
    return res;
}

Complex jian(Complex a, Complex c)
{
	Complex res;
    res.real = a.real - c.real;
	res.image = a.image - c.image;
    return res;
}
Complex cheng(Complex a, Complex c)
{
	Complex res;
    res.real = a.real * c.image - a.image * c.real;
	res.image = a.image * c.real + a.real * c.image;
	return res;
}
Complex chu(Complex a, Complex c)
{
	Complex res;
	res.real = (a.real * c.image + a.image * c.real)/(c.image * c.image + c.real * c.real);
	res.image = (a.image * c.real - a.real * c.image)/(c.image * c.image + c.real * c.real);
	return res;
}