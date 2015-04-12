/**
 * @author  Pavel Ondračka <pavel.ondracka@gmail.com>
 * @version 1.0
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "queue.h"
#include "cpu.h"

int mem_register = 0;

/**
 * Add an insturction to the queue
 *
 * @param pointer to the queue
 * @param instruction type
 * @param instruction value
 */
void queue_add (struct queue* container, const enum instruction_type type, const int value){
   my_assert(container && "NULL argument!");

   struct instruction *item = malloc(sizeof(struct instruction));
   item->type = type;
   item->arg = value;
   item->next = NULL;

   queue_push(container, item);
}

/**
 * Print info about program usage 
 */
void print_help(){
   printf("Usage: cpu [options]\n");
   printf("Simulates simple CPU with queue and stack\n\n");
   printf("Allowed options\n");
   printf("-h\tprogram prints information abou usage and options, and exits\n");
   printf("-r <number>\tafter run commaind, program evaluates <number> of instruction\n");
   printf("-R\tafter run command, program evaluates all instructions in queue\n");
}

/**
 * Parse input arguments
 *
 * @param number of input arguments
 * @param string array with input arguments
 * @param argument of -r option  
 */
void parse_args(int argc, char *argv[], int* batch_size){
   my_assert(argc > 1 && "Number of arguments too low");

   if(strstr(argv[1], "-h") == argv[1]){
      my_assert(argc == 2 && "Number of arguments too low");
      print_help();
      exit(0);
   }
   else if(strstr(argv[1], "-r") == argv[1]){
      my_assert(argc == 3 && "Number of arguments too low");
      *batch_size = strtol(argv[2], NULL, 10);
      my_assert(*batch_size > 0 && "Incorrect argument value");
   }
   else if(strstr(argv[1], "-R") == argv[1]){
      my_assert(argc == 2 && "Number of arguments too low");
   }
   else
      exit(-1);
}

/**
 * Evalueate <batch_size> number of instructions in queue
 *
 * @param queue pointer
 * @param number of instruction to be evaluated, -1 if no limit
 */
void inst_run(struct queue *my_queue, int batch_size){
   struct instruction *next;

   while(batch_size-- != 0){
      if(queue_empty(my_queue))
         return;
      next = queue_pop(my_queue);

      switch(next->type){
         case INST_ADD:
            mem_register += next->arg;
            break;
         case INST_SUB:
            mem_register -= next->arg;
            break;
         case INST_INC:
            mem_register++;
            break;
         case INST_DEC:
            mem_register--;
            break;
         case INST_MUL:
            mem_register *= next->arg;
            break;
         case INST_DIV:
            mem_register /= next->arg;
            break;
      }

      free(next);
   }
}

/**
 * Reads one line from stdin
 */
char* read_line(){
   char c;
   char *line = NULL;
   int length = 0;
   while((c = getchar()) != '\n' && c != EOF){
      line=realloc(line, (length + 2) * sizeof(char));
      line[length++] = c;
      line[length] = 0;
   }
   return line;  
}

int main(int argc, char *argv[]){

   int batch_size = -1;
   parse_args(argc, argv, &batch_size);

   struct queue *my_queue;
   my_queue = malloc(sizeof(struct queue));
   queue_create(my_queue);

   struct stack my_stack = {0, {0}};

   printf("> ");
   char *input_line;

   while((input_line = read_line())){
      char cmd[100] = {0}; 
      int val;
      sscanf(input_line, "%s %i", cmd, &val);
      
      if(strstr(cmd, "quit") == cmd){
         queue_clear(my_queue);
         free(my_queue);
         free(input_line);
         return 0;
      }

      else if(strstr(cmd, "add") == cmd){
         queue_add(my_queue, INST_ADD, val);
      }

      else if(strstr(cmd, "sub") == cmd){
         queue_add(my_queue, INST_SUB, val);
      }

      else if(strstr(cmd, "inc") == cmd){
         queue_add(my_queue, INST_INC, val);
      }

      else if(strstr(cmd, "dec") == cmd){
         queue_add(my_queue, INST_DEC, val);
      }

      else if(strstr(cmd, "mul") == cmd){
         queue_add(my_queue, INST_MUL, val);
      }

      else if(strstr(cmd, "div") == cmd){
         queue_add(my_queue, INST_DIV, val);
      }

      else if(strstr(cmd, "reset") == cmd){
         queue_clear(my_queue);
      }
      else if(strstr(cmd, "push") == cmd){
         stack_push(&my_stack);
      }
      else if(strstr(cmd, "pop") == cmd){
         stack_pop(&my_stack);
      }
      else if(strstr(cmd, "size") == cmd){
         printf("> %i\n", queue_size(my_queue));
      }
      else if(strstr(cmd, "empty") == cmd){
         printf("> %i\n", queue_empty(my_queue));
      }
      else if(strstr(cmd, "print") == cmd){
         print(&my_stack);
      }
      else if(strstr(cmd, "run") == cmd){
         inst_run(my_queue, batch_size);
         print(&my_stack);
      }
      else
         my_assert(0 && "Unexpected input!");
   
   printf("> ");
   free(input_line);
   }

   queue_clear(my_queue);
   free(my_queue);

   return 0;

}
