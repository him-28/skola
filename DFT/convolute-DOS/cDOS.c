#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){

   if(argc < 3)
      return -1;

   double limit = atof(argv[1]);

   double energy[10000];
   double DOS[10000];
   double dE[10000];
   double JDOS[10000] = {};
   unsigned n = 0;

   FILE *input;
   if((input = fopen(argv[2], "r")) == NULL)
      return -2;

   while(fscanf(input, "%lf %lf", energy + n, DOS + n) == 2){
      //printf("%lf %lf\n", energy[n], DOS[n]);
      n++;
   }

   for(unsigned i = 0; i < n; i++){
      dE[i] = energy[i] - energy[0];
      for(unsigned j = 1; j < n - i; j++){
         if(energy[i] < limit && energy[i + j] > limit){
            JDOS[j] += DOS[i]*DOS[i + j];
         }
      }
   }

   for(unsigned i = 0; i < n; i++){
      printf("%lf %lf\n", dE[i], JDOS[i] / 10000.0);
   }
}
