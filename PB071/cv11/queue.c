#include <stdlib.h>

#include "queue.h"

int isEmpty(queue* q){
   return q->first ? 0 : 1;
}

void initQueue(queue* q){
   q->first = NULL;
   q->last = NULL;
}

void enqueue(int value, queue* q){
   qnode *node = malloc(sizeof(qnode));
   node->next = NULL;
   node->value = value;

   if(q->last){
      q->last->next = node;
      q->last = node;
   }
   else{
      q->first = node;
      q->last = node;
   }

}

int dequeue(queue* q){
   if(!q->first)
      return 0;
   int val = q->first->value;
   qnode *node = q->first;
   if(q->first != q->last){
      q->first = q->first->next;
   }
   else {
      q->first = NULL;
      q->last = NULL;
   }

   free(node);
   return val;   
}
