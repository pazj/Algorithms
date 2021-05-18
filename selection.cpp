//2017053772_Paz Carolina Jimenez Saucedo

#include <stdio.h>

void swap(int *xp, int *yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void selectionSort(int arr[],int n, int m)
{
	int i, j, min_idx;
	//one by one move boundary of unsorted array
	for(i=0; i < m; i++){
		//find the minimum element in unsorted array
		min_idx = i;
		for(j = i+1; j < n; j++)
			if(arr[j] < arr[min_idx])
				min_idx = j;
		//swap the found minimum element with the first element
		swap(&arr[min_idx], &arr[i]);
	}
}
void printArray(int arr[], int n)
{
	int i;
	for(i=0; i < n; i++)
		printf("%d\n", arr[i]);
}

int main()
{
	int arr[30000],n,m,i; //n=size & m=until

	//number of elements
	if(scanf("%d %d",&n, &m) != 2)
	{
		return 1;
	}
	
	//hasta donde tiene que ordenar
	for(i=0; i<n ; i++)
		if(scanf("%d", &arr[i]) != 1)
		{
			return 1;
		}
	

	selectionSort(arr,n,m);
	printArray(arr,n);
	return 0;


}
			
