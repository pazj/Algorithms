//2017053772_PazCarolinaJimenezSaucedo_A



#include <stdio.h>

//function to sort an array using insertion sort
//in descending order

void insertionSort(int arr[], int n)
{
	int i, key, j;
	for(i=1; i<n; i++)
	{
		key = arr[i];
		j = i-1;

//moving elements
	while( j >= 0 && arr[j] < key)
	{
		arr[j+1] = arr[j];
		j = j-1;
	}
	arr[j+1] = key;
	}
}
//function to print the array
void printArray(int arr[], int n)
{
	int i;
	for(i=0; i<n; i++)
		printf("%d \n", arr[i]);
}

int main()
{
	int arr[30000],n,i;


	if(scanf("%d", &n) != 1)
	{
		return 0;
	}
	for(i=0; i<n; i++)
		
	if(scanf("%d", &arr[i]) != 1)
	{
		return 0;
	}

	insertionSort(arr,n);
	printArray(arr,n);

	return 0;

}
