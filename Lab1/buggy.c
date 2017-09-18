#include<stdio.h>

int main(void)
{
   int number = 10;
   int next_number = 12;
   float new_number;

   printf("%d\n", next_number); 
   printf("%d\n", number);
   printf("%d\n", number + next_number);

   printf("Enter a new number: ");
   scanf("%d", &new_number);
   

    	
 
   printf("Number Entered was %d\n", new_number);
  
}
