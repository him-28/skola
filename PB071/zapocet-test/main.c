#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
   char *name;
   int w;
}person;

int read_person(FILE *f, char** name, int *w){
   char str[100];
   if(fgets(str, 100, f) == NULL)
      return 0;
   char *dd = strchr(str, ':');
   int dotpos = (int)(dd - str);
   //printf("Position of delimiter is %i\n", dotpos);
   *name = malloc(sizeof(char) * (dotpos + 1));
   strncpy (*name, str, dotpos);
   sscanf(str+dotpos+1,"%i", w); 
   //printf("name: %s, weight: %i\n", name, *w);
   return 1;
}

int sum_weight(person *start, person *end){
   int sum = start->w;
   while(start != end){
      start++;
      sum += start->w;
   }
   return sum;
}

int main(int argc, char *argv[]){
   if (argc < 2){
      printf("Error: expected at one argument (input file)\n");
      return 1;
   }

   FILE *f;

   if((f = fopen(argv[1], "r") ) == NULL){
      printf("Error: Unable to open file %s", argv[1]);
      return 2;
   }

   person *p = NULL;

   char *name;
   int w;
   int num = 0;

   while(read_person(f, &name, &w)){
      p = realloc(p, sizeof(person) * (num + 1));
      p[num].w = w;
      p[num].name = name;
      num++;
   }

   int sum = sum_weight(p, p + num - 1); 

   printf("Name of first person: %s\nTotal weight: %i\n", p[0].name, sum);
 
   fclose(f);
   for(int i = 0; i < num; i++){
      free(p[i].name);
   }
   free(p);
    
   return 0;
}
