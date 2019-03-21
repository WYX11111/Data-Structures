#include <stdio.h>
#include <stdlib.h>

void BubbleSort(int *a,int length)
{
	int i,j,last;
	int t;
	i = length;
	while(i > 0)
	{
		last = 0;
		for(j =0; j < i-1; j++)
		{
			if(a[j+1] > a[j])
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

int Search_Bin (int *a, int k, int length)
{
   int low, high, mid;
   low = 0;
   high = length-1;
   while (low <= high) 
   {
      mid = (low + high) / 2;
      if (k == a[mid])
          return  mid;
      else if ( k > a[mid])
        high = mid - 1;
      else low = mid + 1;
   }
   return 0;
}

void main()
{
	int i;
	int a[15]={119,120,100,95,89,88,56,87,45,32,12,10,8,5,1};
	BubbleSort(a,15);
	for(i = 0; i < 15; i++)
		printf("%d  ",a[i]);
	int k = Search_Bin(a,119,15);
	printf("\n%d\n",k+1);
}
