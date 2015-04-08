/**
 * @author  Pavel Ondračka <pavel.ondracka@gmail.com>
 * @version 1.0
 */

#include <stdlib.h>
#include <stdio.h>

#include "queue.h"

/**
 * Initializes queue
 *
 * @param queue pointer
 */
void queue_create (struct queue* container){
   my_assert(container && "NULL argument!");
   container->first = NULL;
   container->last = NULL;
}

/**
 * Adds instruction to the queue end
 *
 * @param queue pointer
 * @param pointer to the instruction
 */
void queue_push (struct queue* container, struct instruction* item){
   my_assert(container && "NULL argument!");
   if(!item)
      fprintf(stderr, "NULL argument\n");
   if(container->first == NULL){
      container->first = item;
      container->last = item;
      return;
   }
   container->last->next = item;
   container->last = item;
   return;
}

/**
 * Returns pointer to the first instruction in queue 
 *
 * @param queue pointer
 */
struct instruction* queue_pop (struct queue* container){
   my_assert(container && "NULL argument!");
   if(!container->first)
      fprintf(stderr, "Instruction queue is empty\n");
   return container->first;
}

/**
 * Checks if queue is empty
 *
 * @param queue pointer
 */
unsigned int queue_empty (const struct queue* container){
   my_assert(container && "NULL argument!");
   return !container->first ? 1 : 0;
}

/**
 * Returns number of instructions in the queuevalgrind
 *
 * @param queue pointer
 */
unsigned int queue_size (const struct queue* container){
   my_assert(container && "NULL argument!");

   if(!container->first)
      return 0;

   struct instruction* current = container->first;
   int n = 0;
   while(current->next){
      n++;
      current = current->next;
   }
   return n;
}

/**
 * Clears queue and dealocates all instructions
 *
 * @param queue pointer
 */
unsigned int queue_clear (struct queue* container){
   my_assert(container && "NULL argument!");

   if(!container->first)
      return 0;

   struct instruction* current = container->first;
   int n = 0;
   while(current->next){
      struct instruction* last = current;
      current = current->next;
      free(last);
      n++;
   }
   free(current);

   container->first = NULL;
   container->last = NULL;

   return n;
}
