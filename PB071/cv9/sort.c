#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

int* generate(int size){
   int *ret = malloc(size * sizeof(int));
   for(int i = 0; i < size; i++)
      ret[i] = rand() % size;
   return ret;
}

int int_compare(const void* a, const void* b){
   int A = *((int *)a);
   int B = *((int *)b);

   return A - B;
}

void bubble (int* data, size_t size,
            int (*compar)(const void*,const void*)){
   if(!data)
      return;

   if(size<2)
      return;

   int done;

   do{
      done = 1;
      for (int i = 0; i< size - 1; i++){
         if(int_compare(&data[i], &data[i+1]) > 0){
            int temp = data[i+1];
            data[i+1] = data[i];
            data[i] = temp;
            done = 0;
         }
      }
   }
   while(done == 0);
}

int measure(int (*compar)(const void*,const void*)){
   return 0;
}

int main(){

   int *data = NULL;
   int *data1 = NULL;
   int i = 20;

   srand(time(NULL));

   while( (data = generate(i)) == NULL ){
      i -= 10000;
   }

   data1 = malloc(i * sizeof(int));
   memcpy(data1, data, i * sizeof(int));

   bubble(data1, i, int_compare);

   for(int j = 0; j < i; j++){
      printf("%i ", data[j]);
   } 
   printf("\n");

   for(int j = 0; j < i; j++){
       printf("%i ", data1[j]);
   }
   printf("\n");


   free(data);
   free(data1);
   
   return 0;
}
