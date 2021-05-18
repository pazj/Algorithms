//2017053772_PazCarolinaJimenezSaucedo_A

#include <stdlib.h>
#include <stdio.h>

//merges to subarrays of arr[]
//first subarray is arr[l....m]
//secodn subarray is arr[m+1...r]

void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m-l+1;
	int n2 = r-m;
	
	/*create temp arrays */
	int L[n1], R[n2];
	
	/*copy data to temp arrays */
	for(i=0; i < n1; i++)
		L[i] = arr[l + i];
	for(j=0; j<n2; j++)
		R[j] = arr[m +1+j];

	/*merge the temp arrays back into arr[l...r] */
	i=0;
	j=0;
	k=l;
	while (i<n1 && j<n2)
	{
		if(L[i] >= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}
	while ( j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
    
   
}

void mergeSort(int arr[], int l, int r)
{
	if (l < r)
	{
		int m = l+(r-l)/2;

		//sort first and second half
		mergeSort(arr, l, m);
		mergeSort(arr, m+1, r);

		merge(arr, l, m, r);
	}
}

//fucntion to print the array
void printArray(int A[], int size)
{
	int i;
	for(i=0; i<size; i++)
		printf("%d \n",A[i]);
	printf("\n");
}

int main()
{
	int array[100000], n, i;

	if(scanf("%d",&n) != 1)
	{
		return 0;
	}

	for(i=0; i<n; i++)

		if(scanf("%d",&array[i]) !=1)
		{
			return 0;
		}

	
	mergeSort(array, 0, n - 1);
	printArray(array,n);

	return 0;
}
