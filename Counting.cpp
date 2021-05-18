//2017053772_Paz Carolina Jimenez Saucedo

#include <stdio.h>

int count[100000];
int key[100000];
int Array[2] [100000];

int main(void){
	
	int n, m, k;  //n=number of inputs, m=range of input keys, k=number of query ranges

	if(scanf("%d%d%d", &n, &m, &k) != 3) //getting input values
	{
		return 1;
	}

	for(int i = 0; i < k; i++){
		if(scanf("%d %d" , &Array[0][i], &Array[1][i]) != 2)   //create and initialize the arrays
		{
			return 1;
		}
	}
	for(int i = 0; i < n ; i++){
		if(scanf("%d", &key[i]) != 1)
		{
			return 1;
		}
	}
	for(int i = 0; i < n; i++){
		count[key[i]]++;
	}
	for(int i = 0; i <= m; i++){
		count[i] = count[i] + count[i -1];
	}

	for(int i = 0; i < k; i++){
		printf("%d\n", count[Array[1][i]] - count[Array[0][i] - 1]);
	}
	return 0;
}
