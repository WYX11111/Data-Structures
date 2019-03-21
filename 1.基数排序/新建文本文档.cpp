#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define RAND_MAX 2147483647

struct num
{
    int t[10];
};

typedef struct student_information stu;

void RadixSort (num *a, int n);
void RadixPass (num *a, num *b, int n, int i);

void RadixSort (num *a, int n)
{
	num *b;
	int i = 2,j;
	b = (num *)malloc(sizeof(num) * n);
	
	while(i >= 0)
	{
		RadixPass(a, b, n, i);
		i--;
		if(i >= 0)
		{
			RadixPass(b, a, n, i);
			i--;
		}
		else
			for(j = 0; j < n; j++)
				a[j] = b[j];
	}
}

void RadixPass (num *a, num *b, int n, int i)
{
	int count[10];
	int j,k;
	for(j = 0; j < 10; j++)
		count[j] = 0;
	for(k = 0; k < n; k++)
		count[a[k].t[i]] ++;
	for(j = 1; j < 10; j++)
		count[j] = count[j - 1] + count[j];
	for(k = n - 1; k >= 0; k--)
	{
		j = a[k].t[i];
		b[count[j] - 1] = a[k];
		count[j]--;
	}
}

void main()
{
	num *a;
	int i, j, t, bit, r;
	clock_t start,stop;
	double s;
	srand(time(NULL)); 
	a = (num *)malloc(sizeof(num) * 1000005);    //就跟构造一个长度为num的int型数组一个道理  a = (int *)malloc(sizeof(int) * num)
	
	for(i = 0; i < 1000000; i++)
	{
		t = rand();

		for(j = 0; j < 10; j++)
			a[i].t[j] = 0;
		
		bit = 9;
		while(t != 0)
		{
			r = t % 10;
			a[i].t[bit--] = r;
			t = t / 10;
		}
	}

	start = clock();

	RadixSort(a,1000000);

	stop = clock();

	s = (stop - start)/(double)CLK_TCK;

	printf("\n所用平均时间%lfs\n",s);
}