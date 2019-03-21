#include <iostream>

using namespace std;

void matrixmul(int **a, int **b, int m, int n, int m1, int n1)
{
	int i,j,k;
	int **matrix;
	matrix = new int * [m];
	for (i = 0; i < m; i++)
		matrix[i] = new int [n1]; 
	for(i = 0; i < m; i++)
	{
		for(j = 0; j < n1; j++)
			matrix[i][j] = 0;
     }
	if(n != m1)
	{
		cout << "input error!";
		exit(0);
	}
	printf("The result:\n");
	for(i = 0; i < m; i++)
	{
		for(j = 0; j < n1; j++)
		{
			for(k = 0; k < n1; k++)
				matrix[i][j] = matrix[i][j] + a[i][k] * b[k][j];
		}
	}
	for(i = 0; i < m; i++)
	{
		for(j = 0; j < n1; j++)
			cout << matrix[i][j] << "  ";
		cout << endl;
	} 
}


int main()
{
	int n1,m1,n,m;
	int **dm1,**dm;
	int i,j;
	cout << "input the first matrix size m(行),n(列):";
	cin >> m >> n;
	dm = new int * [m];
	for (i = 0; i < m; i++)
		if((dm[i] = new int [n]) == NULL)
			exit(0);
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
			cin >> dm[i][j];
	}

	cout << "input the second matrix size m(行),n(列):";
	cin >> m1 >> n1;
	dm1 = new int * [m1];
	for (i = 0; i < m; i++)
		if((dm1[i] = new int [n1]) == NULL)
			exit(0);
	for (i = 0; i < m1; i++)
	{
		for (j = 0; j < n1; j++)
			cin >> dm1[i][j];
	}

	matrixmul(dm,dm1,m,n,m1,n1);

	return 0;
}