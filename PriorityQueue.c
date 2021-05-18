//2017053772_Paz Carolina Jimenez Saucedo


#include <stdio.h>
#include <stdlib.h>

#define MAX 100


void swap(int *p, int *q){
	int temp;
	temp = *p;
	*p = *q;
	*q = temp;
}

void max_heapify(int arr[],int i, int n)
{
	int largest;
	int left = 2*i;
	int right = 2*i+1;
	if(left <= n && arr[left] > arr[i])
		largest = left;
	else
		largest = right;
	if(right <= n && arr[right] > arr[largest])
		largest = right;
	if(largest != i)
	{
		swap (&arr[i],&arr[largest]);
		max_heapify(arr,largest, n);
	}
}

void build_maxheap(int arr[], int n)
{
	for(int i = n/2; i >= 1 ; i--)
	{
		max_heapify(arr,i, i-1);
	}
}

int maximum(int arr[])
{
	return arr[1]; //as the maximum element is the root element in the max heap
}

int extract_max(int arr[], int length)
{
	if(length == 0)
	{
		printf("queue is empty\n");
	}
	int max = arr[1];
	arr[1] = arr[length];
	length = length - 1;
	max_heapify(arr, 1, length);
	return max;
}
void increase_key(int arr[], int i, int key)
{
	if(key < arr[i])
	{
		printf("can't be inserted\n");
	}
	arr[i] = key;
	while( i > 1 && arr[i/2] < arr[i])
	{
		swap(&arr[i/2], &arr[i]);
		i = i/2;
	}
}

void insert(int arr[], int key, int n)
{
	arr[n+1] = -1;
	increase_key(arr,n+1,key);
}


void display(int arr[], int n)
{
	int i;
	if(n==0)
	{
		printf("Queue is empty");
		return;
	}
	for(i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

int main()
{
	int choice,arr[MAX],key,s;
	choice = 0; //que queres hacer con el queue?
	int n = 0; //numero de nodos en el queue

	while(1)
	{	
		scanf("%d",&choice);
		
	switch(choice)
	{
		case 1:
			scanf("%d", &key);
			insert(arr,key,n);
			build_maxheap(arr,n);
			n++;
			break;
		case 2:
			s = extract_max(arr,key);
			if (s != 0)
				printf("deleted value: %d", s);
			break;
//		case 3:
//			scanf(, &arr,&b);
//			display(arr,n);
//			break;
		case 0:
			display(arr, n);
			exit(0);
		default:
			printf("invalid");
			break;
     }
}
	return 0;
}
