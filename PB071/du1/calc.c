/**
 * @author  Pavel Ondračka <pavel.ondracka@gmail.com>
 * @version 1.0
 */

#include <stdlib.h>
#include <stdio.h>

long npow(long a, long b){
   long ret = 1;
   for (long i = 0; i < b; i++)
      ret *= a;
   return ret;
}

long fact(long a){
   if(a < 0)
      return -1;
   long ret = 1;
   while(a > 0){
      ret *= a;
      a--;
   }
   return ret;
}

long sum(long num, long *data){
   long ret = 0;
   while(num != 0){
      ret += data[num-1];
      num--;
   }
   return ret;
}

float aver(long num, long *data){
   if(num == 0)
      return 0.0;
   long sum = 0;
   long n = num;
   while(num != 0){
      sum += data[num-1];
      num--;
   }
   return (float)sum / n;
}

long binom(long top, long bot){
   if(top < bot || bot < 0)
      return -1;
   return fact(top) / (fact(bot) * fact(top - bot));
}

long prime(long a){
   if(a == 2)
      return 1;
   if(a == 1 || a % 2 == 0)
      return 0;
   for(long i = 3; i <= a / 2; i += 2)
      if((a % i) == 0)
         return 0;
   return 1;
}

int main(){

   char op;
  printf("> ");

   while(scanf("%c", &op) != EOF){

      long n1, n2;
      float fn1, fn2;
      long *data;

      switch(op){

         case '+':
            scanf("%li %li", &n1, &n2);
            printf("# %li\n", n1 + n2);
            break;

         case '-':
            scanf("%li %li", &n1, &n2);
            printf("# %li\n", n1 - n2);
            break;

         case '/':
            scanf("%f %f", &fn1, &fn2);
            printf("# %.2f\n", fn1 / fn2);
            break;

         case 'd':
            scanf("%li %li", &n1, &n2);
            printf("# %li\n", n1 / n2);
            break;

         case 'm':
            scanf("%li %li", &n1, &n2);
            printf("# %li\n", n1 % n2);
            break;

         case '*':
            scanf("%li %li", &n1, &n2);
            printf("# %li\n", n1 * n2);
            break;

         case '^':
            scanf("%li %li", &n1, &n2);
            printf("# %li\n", npow(n1, n2));
            break;

         case '!':
            scanf("%li", &n1);
            printf("# %li\n", fact(n1));
            break;

         case 's':
            scanf("%li", &n1);
            if((data = (long*)malloc(n1 * sizeof(long))) == NULL){
               printf("failed to allocate memory\n");
               exit(1);
            }
            for(long i = 0; i < n1; i++)
               scanf("%li", &data[i]);
            printf("# %li\n", sum(n1, data));
            free(data);
            break;

         case 'a':
            scanf("%li", &n1);
            if((data = (long*)malloc(n1 * sizeof(long))) == NULL){
               printf("failed to allocate memory\n");
               exit(1);
            }
            for(long i = 0; i < n1; i++)
               scanf("%li", &data[i]);
            printf("# %.2f\n", aver(n1, data));
            free(data);
            break;

         case 'c':
            scanf("%li %li", &n1, &n2);
            printf("# %li\n", binom(n1, n2));
            break;

         case 'p':
            scanf("%li", &n1);
            printf("# %s\n", prime(n1) ? "y" : "n");
            break;
   
         case 'q':
            return 0;

         default:
            printf("Unknown operation %c\n", op);
            break;
      }

   char c;
   while((c = getchar())){
      if(c == '\n')
         break;
      else if(c == EOF)
         return 0;
   }
   printf("> ");
   }

   return 0;
}
