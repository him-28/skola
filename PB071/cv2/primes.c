#include<stdio.h>
#include<math.h>

/**
 Checks if the number is a prime number.
 @param number number to be tested
 @return 1 if the number is a prime 0 otherwise.
*/
int is_prime(unsigned number);

int main()
{
   unsigned number;
   printf("Zadejte kladnou hodnotu:");
   scanf("%u",&number);
   printf("%u ",number);
   
   if(is_prime(number))
   {
      printf("je");
   }
   else
   {
      printf("neni");
   }
   
   printf(" prvocislo\n");
}

int is_prime(unsigned number)
{
   if(number == 1 || number % 2 == 0)
      return 0; 
   if(number == 2)
      return 1;
   for(int i=3 ; i<=sqrt(number) ; i+=2)
   {
       if(number % i == 0)
           return 0;
   }
   return 1;
}
