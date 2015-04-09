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
   if(!item){
      fprintf(stderr, "NULL argument\n");
      return;
   }
   item->next = NULL;
   if(container->first == NULL){
      container->first = item;
      container->last = item;
      return;
   }
   container->last->next = item;
   container->last = item;
}

/**
 * Returns pointer to the first instruction in queue
 *
 * @param queue pointer
 */
struct instruction* queue_pop (struct queue* container){
   my_assert(container && "NULL argument!");

   if(!container->first){
      fprintf(stderr, "Instruction queue is empty\n");
      return NULL;
   }

   struct instruction *ret = container->first;

   if(container->first->next)
      container->first = container->first->next;
   else{
      container->first = NULL;
      container->last = NULL;
   }

   return ret;
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
 * Returns number of instructions in the queue
 *
 * @param queue pointer
 */
unsigned int queue_size (const struct queue* container){
   my_assert(container && "NULL argument!");

   if(!container->first)
      return 0;

   struct instruction* current = container->first;
   unsigned int n = 1;
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
   unsigned int n = 1;
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
