#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define RAND_MAX 2147483647

void Merge(int sourceArr[],int tempArr[], int startIndex, int midIndex, int endIndex)
{
    int i = startIndex, j=midIndex+1, k = startIndex;
    while(i!=midIndex+1 && j!=endIndex+1)
    {
        if(sourceArr[i] > sourceArr[j])
            tempArr[k++] = sourceArr[j++];
        else
            tempArr[k++] = sourceArr[i++];
    }
    while(i != midIndex+1)
        tempArr[k++] = sourceArr[i++];
    while(j != endIndex+1)
        tempArr[k++] = sourceArr[j++];
    for(i=startIndex; i<=endIndex; i++)
        sourceArr[i] = tempArr[i];
}

void MergeSort(int sourceArr[], int tempArr[], int startIndex, int endIndex)
{
    int midIndex;
    if(startIndex < endIndex)
    {
        midIndex = (startIndex + endIndex) / 2;
        MergeSort(sourceArr, tempArr, startIndex, midIndex);
        MergeSort(sourceArr, tempArr, midIndex+1, endIndex);
        Merge(sourceArr, tempArr, startIndex, midIndex, endIndex);
    }
}

void main()
{
	int *a, *b, i, length;
   	clock_t start,stop;
	double s;

	a = (int *)malloc(sizeof(int) * 1000005);
	b = (int *)malloc(sizeof(int) * 1000005);

	srand(time(NULL)); 

	start = clock();
	
	length = 1000000;

	for(int k = 0; k < 20; k++)
	{
		for(i = 1; i <= length; ++i)
			a[i] = rand();
		MergeSort(a, b, 1, length);
	}
	stop = clock();

	s = (stop - start)/(double)CLK_TCK/20.0;

	printf("\n所用平均时间%lfs\n",s);
}