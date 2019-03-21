#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define RAND_MAX 2147483647

int length;

void InsertSort(int *a, int length)
{
	int i,j;
	for (i = 2; i <= length; ++i)
		if(a[i] < a[i-1])
		{
			a[0] = a[i];
			for(j = i-1; a[0] < a[j]; --j)
				a[j+1] = a[j];
			a[j+1] = a[0];
		}
}

void main()
{
	int *a, i,length;
   	clock_t start,stop;
	double s;

	a = (int *)malloc(sizeof(int) * 1000005);

	srand(time(NULL)); 

	start = clock();
	
	length = 1000000;

	for(int k = 0; k < 1; k++)
	{
		for(i = 1; i <= length; ++i)
			a[i] = rand();
		InsertSort(a,length);
	}
	stop = clock();

	s = (stop - start)/(double)CLK_TCK/1.0;

	printf("\n所用平均时间%lfs\n",s);
}
