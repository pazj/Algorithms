//2017053772_Paz Carolina Jimenez Saucedo

#include <stdio.h>
#include <limits.h>

//function to get the maximum fo two integers

int max (int a, int b) {
	return ( a > b) ? a : b;
}

int numRodsUsed;
int cutRod(int price[],int rods[], int n)
{
	int val[n+1];
	int last_rod[n+1];
	val[0] = 0;
	int i, j;

	//build the table val[]
	for(i=1; i<=n; i++)
	{
		int max_val = INT_MIN;
		int best_rod_len = -1;
		for(j=0; j<i; j++)
		{
			if(max_val < price[j] + val[i-j-1])
			{
				max_val = price[j] + val[i-j-1];
				best_rod_len = j;
			}
		}
		val[i] = max_val;
		last_rod[i] = best_rod_len + 1;
	}
	for( i = n, j = 0; i > 0; i -= last_rod[i])
	{
		rods[j++] = last_rod[i];
	}
	numRodsUsed = j;
	return val[n];
}

int main()
{
	int arr[100];
	int max_price = sizeof(arr)/sizeof(arr[0]); //N prices
	int rods[max_price + 1]; //length of number of cuts

	if(scanf("%d", &max_price) != 1)
	{
		return 1;
	}
	if (max_price >= 100 && max_price < 1){
		printf("exceed");
	}
	for( int i = 0; i < max_price; i++){
		if(scanf("%d", &arr[i]) != 1){
			return 1;
		}
	}
	printf("%d \n",cutRod(arr,rods,max_price));
	printf("%d", rods[0]);
	
	for(int i = 1; i < numRodsUsed; i++){
		printf(" %d", rods[i]);
	}
	printf("\n");

	getchar();
	return 0;
}
