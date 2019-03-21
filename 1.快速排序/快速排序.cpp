#include<stdio.h>
#include<stdlib.h>

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
   	
	printf("元素个数");
	scanf("%d",&length);

	a = new int[length];

	printf("输入元素\n");

	for(i = 1; i <= length; ++i)
		scanf("%d",&a[i]);

	QuickSort(a,1,length);

	for(i = 1; i <= length; ++i)
		printf("%d ",a[i]);
}