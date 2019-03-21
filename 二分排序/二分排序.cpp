#include <stdio.h>
#include <stdlib.h>

void binaryInsertSort(int *array, int n)
{
	int i, j, temp, left, right, middle;
	for(i = 0; i < n; i++)
	{
		temp = array[i];
		left = 0;
		right = i-1;
		middle = 0;

		while(left <= right)
		{
			middle = (left + right)/2;
			if(temp<array[middle])
				right = middle-1;
			else
				left = middle + 1;
		}
		for(j = i-1; j >= left; j--)
			array[j+1] = array[j];
		if(left != i )
			array[left] = temp;
	}
	for (i = 0; i < n; i++)
		printf("%d  ",array[i]);
}

void main()
{
	int n, i;
	scanf("%d",&n);
	int *array = new int[n];
	for(i = 0; i < n; i++)
	{
		scanf("%d",&array[i]);
	}
	binaryInsertSort(array, n);
}