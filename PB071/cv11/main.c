#include <stdlib.h>
#include <stdio.h>

#include "queue.h"

#define MU_ASSERT(message, test) do { if (!(test)) return message; } while (0)
#define MU_RUN_TEST(test) do { char *message = test(); tests_run++; \
                               if (message) return message; } while (0)
int tests_run = 0;

char *test_initQueue(void){
   queue my_queue;
   initQueue(&my_queue);

   MU_ASSERT("first is not NULL", my_queue.first == NULL);
   MU_ASSERT("last is not NULL", my_queue.last == NULL);

   return NULL;
}

char *test_isEmpty(void){
   queue my_queue;
   my_queue.first = NULL;
   my_queue.last = NULL;

   MU_ASSERT("queue should be empty", isEmpty(&my_queue) == 1);

   qnode node;
   my_queue.first = &node;
   my_queue.last = &node;

   MU_ASSERT("queue should be not empty", isEmpty(&my_queue) == 0);

   return NULL;
}


char *test_enqueue(void){
   queue my_queue;
   my_queue.first = NULL;
   my_queue.last = NULL;

   enqueue(1, &my_queue);

   MU_ASSERT("first item is not 1", my_queue.first->value == 1);
   MU_ASSERT("queue is not null", my_queue.first);
   MU_ASSERT("queue is not null", my_queue.last);

   enqueue(2, &my_queue);

   MU_ASSERT("second item is not 1", my_queue.first->next->value == 2);
   MU_ASSERT("second item is not 1", my_queue.last->value == 2);

   MU_ASSERT("first item is the same as second", my_queue.first != my_queue.last);

   free(my_queue.first);
   free(my_queue.last);

   return NULL;
}

char *test_dequeue(void){
   queue my_queue;
   my_queue.first = NULL;
   my_queue.last = NULL;

   enqueue(1, &my_queue);
   enqueue(2, &my_queue);

   MU_ASSERT("item is not 1", dequeue(&my_queue) == 1);

   MU_ASSERT("first item is not the same as second", my_queue.first == my_queue.last);

   MU_ASSERT("item is not 2", dequeue(&my_queue) == 2);

   MU_ASSERT("queue is not empty", isEmpty(&my_queue));

   return NULL;
}



char *tests(void){
   MU_RUN_TEST(test_initQueue);
   MU_RUN_TEST(test_isEmpty);
   MU_RUN_TEST(test_enqueue);
   MU_RUN_TEST(test_dequeue);

   return NULL;
}


int main(){
   char *result = tests(); 

   printf("number of tests run: %d\n", tests_run);
   if (result)
      printf("FAIL: %s\n", result);
   
   return 0 != result;
}
