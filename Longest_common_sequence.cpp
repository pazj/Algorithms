//2017053772_paz_carolina_jimenez_saucedo


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_BUF 500

int maximum(int A,int B)
{ 
   if(A>B) 
      return A; 
   else 
      return B; 
}

int BackTracking(int lenght_first, int lenght_second);

int comp_Val[MAX_BUF][MAX_BUF]={0,};
int arrow_Val[MAX_BUF][MAX_BUF]={0,};
char first_input[MAX_BUF],second_input[MAX_BUF];
char output[MAX_BUF];

int main(void)
{

   int i,j,cnt;
   int lenght_first,lenght_second;

   gets(first_input);
   gets(second_input);

   lenght_first = strlen(first_input);
   lenght_second = strlen(second_input);


   for (i = 0; i < MAX_BUF; i++) {
      comp_Val[0][i] = 0;
      comp_Val[i][0] = 0;
   }

   for (i = 1; i < lenght_second+1; i++)
   {
      for (j = 1; j < lenght_first+1; j++)
      {
         
         if (i>0 && j>0 && first_input[i-1] == first_input[j-1]) 
         {
            comp_Val[i][j] = comp_Val[i-1][j-1] + 1; 
		
	    //when the value of the diagonal is 3
            if (arrow_Val[i][j-1] == 3) 
            {
               arrow_Val[i][j] = 1; 
            }
            else
               arrow_Val[i][j] = 3;
         }

	 //when the top arrow is 2

         else if (i>0 && j>0 && second_input[i-1] != first_input[j-1]) 
         {
            if(comp_Val[i][j-1] <= comp_Val[i-1][j])
            {
               comp_Val[i][j] = comp_Val[i-1][j];
               arrow_Val[i][j] = 2; 
            }

            else
            {
               comp_Val[i][j] = comp_Val[i][j-1];
               arrow_Val[i][j] = 1;
            }
         }
      }
   }



   cnt = BackTracking(lenght_first,lenght_second);

   for (i = cnt; i >= 0; i--) {
      printf("%c",output[i]);
   }

   return 0;
}



int BackTracking(int lenght_first, int lenght_second)
{
   int k=0;
   int cnt=0;
   while(lenght_second != 0 && lenght_first != 0)
   {
      if(arrow_Val[lenght_second][lenght_first] == 1)
      {
         lenght_first--;
      }

      else if( arrow_Val[lenght_second][lenght_first] == 2)
      {
         lenght_second--;
      }

      else
      {
         output[k++] = first_input[lenght_first-1];
         lenght_first--;
         lenght_second--;
         cnt++;
      }

   }

   return cnt;
}
