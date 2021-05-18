//2017053772_Paz Carolina Jimenez Saucedo

#include <stdio.h>
#include <stdlib.h>

//a heap has a current size and array elemnts


struct MaxHeap
{
	int size;
	int* array;
};

//a utility function to swap to integers
void swap(int*a, int* b )
{
	int t = *a;
	*a = *b;
	*b = t;
}

//the main function to heapify a Max heap. 
//the function assumes that everything under given root
//(elemenet at index idx) is already heapified
void maxHeapify(struct MaxHeap* maxHeap, int idx)
{
	int largest = idx; //initialize largest as root
	int left = (idx << 1) + 1; 
	int right = (idx + 1) << 1;

	//see if left child of root exists and is greater than root
	if(left < maxHeap->size && maxHeap->array[left] > maxHeap->array[largest])
		largest = left;

	//see if right child of root exists and is greater than the largest so far
	if(right < maxHeap->size && maxHeap->array[right] > maxHeap->array[largest])
		largest = right;

	//change root, if needed
	if (largest != idx)
	{
		swap(&maxHeap->array[largest], &maxHeap->array[idx]);
		maxHeapify(maxHeap, largest);
	}
}
//function to create a max heap
struct MaxHeap* createAndBuildHeap(int* array, int  size)
{
	int i;
	struct MaxHeap* maxHeap = (struct MaxHeap*) malloc(sizeof(struct MaxHeap));
	maxHeap->size = size;
	maxHeap->array = array;

	for(i = (maxHeap->size -2 ) / 2; i >= 0; --i)
		maxHeapify(maxHeap, i );
	return maxHeap;
}

//main function to sort an array of given size
void heapSort(int* array, int size)
{
	
	//buil a heap from the input data
	struct MaxHeap* maxHeap = createAndBuildHeap(array,size);

	while (maxHeap->size > 1)
	{
		swap(&maxHeap->array[0], &maxHeap->array[maxHeap->size -1]);
		--maxHeap->size;

		maxHeapify(maxHeap, 0);
	}

}

void printArray(int* arr, int size, int k)
{
	int i;
	for(i=size - 1; i >= size - k ; i--)
		printf("%d ", arr[i]);
	printf("\n");
	for(i = size - k -1; i >= 0 ; i--)
		printf("%d ", arr[i]);
	printf("\n");
}

int main()
{
	int number; //numero de elementos
	int k; //numero de elementos mas grandes por imprimir
	int arr[100000];

	//scanning number of elements
	if(scanf("%d %d",&number, &k) != 2)
	{
		return 1;
	}

	if( number > 100000 || k > 30)
	{
		printf("exceed");
	}

	for(int i = 0; i < number; i++){
		if(scanf("%d",&arr[i]) != 1 )
		{
			return 1;
		}
	}

	heapSort(arr,number);
	printArray(arr, number,k);

	return 0;
}


			
