#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define RAND_MAX 2147483647

int length;

int Partition(int *a, int low ,int high)
{
	a[0] = a[low];
	int pivotkey=a[low];
	while(low < high)
	{
		while(low < high && a[high] >= pivotkey)
			--high;
		if(low < high)
			a[low++] = a[high];
		while(low < high && a[low] <= pivotkey)
			++low;
		if(low < high)
			a[high--] = a[low];
	}
	a[low] = a[0];
	return low;
}

void QuickSort(int *a, int s, int t)
{
	if(s < t)
	{
		int pivotloc = Partition(a, s ,t);
		QuickSort(a, s, pivotloc-1);
		QuickSort(a, pivotloc+1, t);

	}
}

void main()
{
	int *a, i,length;
   	clock_t start,stop;
	double s;

	a = (int *)malloc(sizeof(int) * 1000005);

	srand(time(NULL)); 
	
	length = 1000000;

	for(int k = 0; k < 1; k++)
	{
		for(i = 1; i <= length; ++i)
			a[i] = rand();
		start = clock();
		QuickSort(a,1,length);
	}
	stop = clock();

	s = (stop - start)/(double)CLK_TCK;

	printf("\n所用平均时间%lfs\n",s);
}