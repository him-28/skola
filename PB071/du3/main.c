#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "queue.h"
#include "cpu.h"

void print_help(){
};

int main(int argc, char *argv[]){
   my_assert(argc > 1 && "Number of arguments too low");

   long batch_size = 0;

   if(strstr(argv[1], "-h") != NULL){
      my_assert(argc == 2 && "Number of arguments too low");
      print_help();
   }
   else if(strstr(argv[1], "-r") != NULL){
      my_assert(argc == 3 && "Number of arguments too low");
      char **end_char = NULL;
      batch_size = strtol(argv[2], end_char, 10);
      assert(batch_size > 1 && **end_char == 0 && "Incorrect argument value");
   }
   else if(strstr(argv[1], "-R") != NULL){
      my_assert(argc == 2 && "Number of arguments too low");
   }
   else
      my_assert(0 && "Unknown input switch");

   printf("> ");

   return 0;

}
