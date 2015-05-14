#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ALLOC_CHUNK 50

typedef struct{
   char* name;
   double aver_mark;
} student; 

void check_input(int argc){
   if(argc < 3){
      printf("Error: at least two arguments needed\n");
      printf("zapocet: <input file> <output file>\n");
      exit(-1);
   }

   if (argc > 3)
      printf("Warning: too many arguments, superfluous ones are ignored \n");
}

char* read_line(FILE *file){
   char c;
   unsigned int length = 0, bufsize = 0;
   char *line = NULL;

   while((c = fgetc(file)) != '\n' && c != EOF){
      if(length + 2 > bufsize){
         bufsize += ALLOC_CHUNK;
         line = realloc(line, bufsize * sizeof(unsigned char));
      }
      line[length] = c;
      length++;
      line[length] = 0;
   }
   if(length > 0)
      line = realloc(line, (length + 1) * sizeof(unsigned char));

   return line;
}

int read_students(student **s, FILE *file){
   int n = 0;
   char *line;

   while((line = read_line(file)) != NULL){
      //printf("%s\n", line);
      char *name;
      char *dd = strchr(line, ':');
      int dotpos = (int)(dd - line);
      unsigned int linesize = strlen(line);
      
      name = malloc(sizeof(char) * (dotpos + 1));
      strncpy(name, line, dotpos);
      *(name + dotpos) = 0;

      //printf("%s \n", name);

      unsigned int sum = 0;
      unsigned int n_mark = 0;
      double aver;

      for( int i = dotpos + 1; i < linesize; i++){
         char c = line[i];
         if(c >= '0' && c <= '9'){
            sum += c - '0';
            n_mark++;
         }
      }
      //printf("%i %i", sum, n_mark);
      aver = (double)sum / n_mark;
      //printf("%f", aver);

      *s = realloc(*s, sizeof(student) * (n + 1));
      ((*s)+n)->name = name;
      ((*s)+n)->aver_mark = aver;  

      n++;
      free(line);
   }

   return n;
}

int compare_students(const void * a, const void * b)
{
  if ( ((student*)a)->aver_mark < ((student*)b)->aver_mark ) return -1;
  else if ( ((student*)a)->aver_mark == ((student*)b)->aver_mark ) return 0;
  else return 1;
}

int main(int argc, char *argv[]){
   check_input(argc);

   FILE *infile, *outfile;

   if((infile = fopen(argv[1], "r")) == NULL){
      printf("Error: unable to open input file %s\n", argv[1]);
      return -2;
   } 

   if((outfile = fopen(argv[2], "w")) == NULL){
      printf("Error: unable to open output file %s\n", argv[2]);
      return -2;
   }

   student *s = NULL;
   unsigned int n;
   
   n = read_students(&s, infile);

   //sort_students(&s);
   qsort(s, n, sizeof(student), compare_students);

   for(int i = 0; i < n; i++){
      fprintf(outfile, "%s:%.2f\n", s[i].name, s[i].aver_mark);
      free(s[i].name);
   }

   free(s);
   fclose(infile);
   fclose(outfile);

   return 0;
}
