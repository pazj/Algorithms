//2017053772_Paz Carolina Jimenez Saucedo


#include<stdio.h>
#include<limits.h>


void optimal(int i, int j, int n, int *bracket, int &numbers)
{
	if(i == j ) 
	{
		printf(" %d ", numbers++);
		return;
	}
	printf("(");

	optimal(i, *((bracket+i*n)+j),n,bracket,numbers);
	optimal(*((bracket+i*n)+j) + 1,j,n,bracket, numbers);
	
	printf(")");
}

void matrixChainOrder(int p[], int n)
{
	int m[n][n];
	int bracket[n][n];
	int i,j,k,L,q;

	for(i=1; i<n; i++)
		m[i][i] = 0; //number of multiplications
	
	//here L is chain length
	for(L=2; L<n; L++)
	{
		for(i=1; i<n-L+1; i++)
		{
			j = i+L-1;
			m[i][j] = INT_MAX; //assigning to maximum value
			
			for(k=i; k <= j-1; k++)
			{
				q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
				if (q < m[i][j])
				{
					m[i][j] = q;
					bracket[i][j] = k;
				}
			}
		}
	}

	int num = 1;
	printf("%d\n", m[1][n-1]);
	printf(" ");
	optimal(1, n-1, n, (int*)bracket, num);
	printf("\n");
}


int main()
{
	int n,i;

	//getting number of matrices
	scanf("%d", &n);
	n++;

	int arr[n];
	
	for(i=0;i<n;i++)
	{
		scanf("%d",&arr[i]);
	}
	int size = sizeof(arr)/sizeof(arr[0]);
	matrixChainOrder(arr,size);
	
	return 0;		
}
