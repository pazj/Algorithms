//2017053772_Paz_Carolina_Jimenez_Saucedp


#include <stdio.h>
#include <stdlib.h>

#define MAX_TREE_HT 100


//a huffman tree node

struct MinheapNode{
	//one of the input characters
	char data;

	//frequency of the character
	unsigned freq;

	//left and right child of this node
	struct MinheapNode *left, *right;
};

struct Minheap 
{
	//curretn size of minheap
	unsigned size;

	//capacity of minheap
	unsigned capacity;

	//attay of minheap pointers
	struct MinheapNode** array;
};


struct MinheapNode* newNode(char data, unsigned freq)
{
	struct MinheapNode* temp = (struct MinheapNode*)malloc(sizeof(struct MinheapNode));

	temp->left = temp->right = NULL;
	temp->data = data;
	temp->freq = freq;

	return temp;
}

//minheap capacity
struct Minheap* createMinheap(unsigned capacity)
{
	struct Minheap* minheap = (struct Minheap*)malloc(sizeof(struct Minheap));
	
	//current size iss 0
	minheap->size = 0;
	minheap->capacity = capacity;
	minheap->array = (struct MinheapNode**)malloc(minheap->capacity * sizeof(struct MinheapNode*));

	return minheap;
}

//a utility function to swap two minheap nodes
void swapMinHeapNode(struct MinheapNode** a, struct MinheapNode** b)
{
	struct MinheapNode* t = *a;
	*a = *b;
	*b = t;

}

//the standard minheapify function
void minHeapify(struct Minheap* minheap, int idx)
{
	int smallest = idx;
	int left = 2 * idx + 1;
	int right = 2 * idx + 2;
	
	if (left < minheap->size && minheap->array[left]->freq < minheap->array[smallest]->freq)
		smallest = right;

	if(right < minheap->size && minheap->array[right]->freq < minheap->array[smallest]->freq)
		smallest = right;

	if(smallest != idx){
		swapMinHeapNode(&minheap->array[smallest],&minheap->array[idx]);
		minHeapify(minheap, smallest);
	}
}

//function to check if size of heap is 1 or not
int isSizeOne(struct Minheap* minheap)
{
	return (minheap->size == 1);
}

struct MinheapNode* extractMin(struct Minheap* minheap)
{
	struct MinheapNode* temp = minheap->array[0];
	minheap->array[0] = minheap->array[minheap->size - 1];

	--minheap->size;
	minHeapify(minheap, 0 );

	return temp;
}

void insertMinheap(struct Minheap* minheap, struct MinheapNode* minHeapNode)
{
	++minheap->size;
	int i = minheap->size - 1;

	while ( i && minHeapNode->freq < minheap->array[(i - 1)]->freq){

		minheap->array[i] = minheap->array[(i - 1) / 2];
		i = (i - 1) / 2;
	}

	minheap->array[i] = minHeapNode;
}

//function to insert a new node to min heap
void buildMinheap(struct Minheap* minheap)
{
	int n = minheap->size - 1;
	int i;

	for(i = (n-1)/2; i >= 0; --i)
		minHeapify(minheap, i);
}

void printArr(int arr[], int n)
{
	int i;
	for(i = 0; i < n; i++){
		printf("%d",arr[i]);
	}

	printf("\n");
}

int isLeaf(struct MinheapNode* root)
{
	return !(root->left) && !(root->right);
}

struct Minheap* createAndBuildMinheap(char data[], int freq[], int size)
{
	struct Minheap* minheap = createMinheap(size);
	
	for(int i = 0; i < size; i++)
		minheap->array[i] = newNode(data[i],freq[i]);

	minheap->size = size;
	buildMinheap(minheap);

	return minheap;
}

struct MinheapNode* buildHuffmanTree(char data[],int freq[], int size)
{
	struct MinheapNode *left, *right,*top;

	struct Minheap* minheap = createAndBuildMinheap(data,freq, size);

	while(!isSizeOne(minheap)){
		left = extractMin(minheap);
		right = extractMin(minheap);

		top = newNode('$',left->freq + right->freq);

		top->left = left;
		top->right = right;

		insertMinheap(minheap, top);
	}

	return extractMin(minheap);
}

int check = 0;
int sum = 0;

void printCodes(struct MinheapNode* root, int arr[], int top)
{
	if(root->left){
		arr[top] = 0;
		printCodes(root->left,arr, top + 1);
	}
	if(root->right){
		arr[top] = 1;
		printCodes(root->right,arr, top + 1);
	}

	if(isLeaf(root)){
		printf("%c: ", root->data);
		printArr(arr,top);

//		check += top -1;
	}

}

void HuffmanCodes(char data[], int freq[], int size)
{
	//construct Huffman tree
	struct MinheapNode* root = buildHuffmanTree(data,freq, size);

	//print Huffman codes using the huffman tree built above
	int arr[MAX_TREE_HT], top = 0;

	printCodes(root, arr, top);

}


int main()
{
	 int n,s;
	
	 //scan total number of character
	scanf("%d", &n);

       	char data [n];
	int freq[n];
	for(int i = 0; i < n; i++)
	{
		scanf(" %s", &data[i]);
		scanf("%d", &freq[i]);
	}
	//total number of characters
	scanf("%d", &s);
	printf("%d\n", s*3);
	

	int size = sizeof(data) / sizeof(data[0]);	

	
	HuffmanCodes(data,freq,size);
	return 0;


}


		





