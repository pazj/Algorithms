//2017053772_paz_carolina_jimenez_saucedo


#include<stdio.h>
#define MAX_BUF 100001



int main()
{
   int set_A[MAX_BUF]={0,};
   int set_B[MAX_BUF]={0,};
   int temp_A=0;
   int temp_B=0;

   //keys where n is number of keys in set_A
   //and m is the number of keys in set_B
   int N=0,M=0;
   int i=0,j=0;
   int cnt=0;
   
   
  if(scanf("%d %d", &N, &M) != 2){
	  return 2;
  }

   int origin_A[MAX_BUF]={0,};
   int origin_B[MAX_BUF]={0,};
  
   for(i=0 ; i<N ; i++)
   {
    if(scanf("%d",&origin_A[i]) != 1){
	    return 1;
    }
     temp_A = origin_A[i];
     set_A[temp_A] = 1;
   }
   for(i=0 ; i<M ; i++)
   {
     if(scanf("%d",&origin_B[i]) != 1){
	     return 1;
     }
      temp_B = origin_B[i];
      set_B[temp_B] = 1;
   }


   for(j =0;j < MAX_BUF;j++)
   {
      if(set_A[j] == 1 && set_B[j] == 1)
      {
        cnt++;
      }
   }

   printf("%d\n",cnt);

   return 0;
}
