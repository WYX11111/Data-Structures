#include<stdio.h>
#include<stdlib.h>

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

	printf("元素个数");
	scanf("%d",&length);

	a = new int[length];

	printf("输入元素\n");

	for(i = 1; i <= length; ++i)
		scanf("%d",&a[i]);
	InsertSort(a,length);
	
	for(i = 1; i <= length; ++i)
		printf("%d ",a[i]);
}
