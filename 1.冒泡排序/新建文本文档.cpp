#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define RAND_MAX 2147483647

int length;

void BubbleSort(int *a)
{
	int i,j,last;
	int t;
	i = length;
	while(i > 0)
	{
		last = 0;
		for(j =0; j < i-1; j++)
		{
			if(a[j+1] < a[j])
			{
				t = a[j+1];
				a[j+1] = a[j];
				a[j] = t;
				last = j+1;
			}
		}
		i = last;
	}
}

void main()
{
	int a[30], i;
   	clock_t start,stop;
	double s;

	srand(time(NULL)); 

	start = clock();
	
	length = rand()%10 + 10;

	printf("%d个\n",length);

	for(i = 0; i < length; ++i)
		a[i] = rand();                     
	
	BubbleSort(a);
	
	for(i = 0; i < length; ++i)
		printf("%d   ",a[i]);

	stop = clock();

	s = (stop - start)/(double)CLK_TCK;

	printf("\n所用平均时间%lfs\n",s);
}