#include <stdlib.h>
#include <stdio.h>
#include "fronta.h"

t_queue enqueue(t_queue queue, char *string){
   t_item *item = malloc(sizeof t_item);
   item->data = malloc((strlen(string)+1) * sizeof(char));
   strcpy(item->data, string);
   if(queue->first == NULL){
      queue->first = item;
   }
   if(queue->last)
      queue->last.next = item;
   queue->last=item;
   return queue;   
}

void listQueue(t_queue queue){
   while(queue.first != NULL){
      printf("%s\n", queue.first->data);
      queue.first = queue.first->next;
   }
}

char* readline(){
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

int main(){
   t_queue fronta = {NULL, NULL};

   char* input_string;
   readline();

   



   return 0;
}
