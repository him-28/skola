#include <stdlib.h>
#include <stdio.h>

#include "queue.h"

struct instruction{
   struct instruction *next;
   enum instruction_type type;
   long value;
};

struct queue {
   struct instruction* first;
   struct instruction* last;
};

void queue_create (struct queue* container){
   my_assert(container && "NULL argument!");
   container->first = NULL;
   container->last = NULL;
}

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

struct instruction* queue_pop (struct queue* container){
   my_assert(container && "NULL argument!");
   if(!container->first)
      fprintf(stderr, "Instruction queue is empty\n");
   return container->first;
}

unsigned int queue_empty (const struct queue* container){
   my_assert(container && "NULL argument!");
   return !container->first ? 1 : 0;
}

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
