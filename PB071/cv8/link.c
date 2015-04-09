#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct t_item{
  int value;
  struct t_item *next;
}t_item;

void enqueue(t_item** list, int value);
int dequeue(t_item** list);

int main()
{
  int value;
  t_item *list = NULL;

  printf("Zadejte hodnoty (zaporna-konec):");
  do
  {
    scanf("%d",&value);
    if(value >= 0)
    enqueue(&list,value);
  }while(value>0);

  printf("Hodnoty v seznamu:\n");
  while((value=dequeue(&list))>0)
  {
    printf("%d ",value);
  }
  printf("\n");
  free(list);

  return 0;
}

void enqueue(t_item** list, int value)
{
  t_item *item = malloc(sizeof(t_item));
  item->value=value;
  item->next = NULL;
  if(!*list){
     *list = item;
  }
  else{
     t_item *last = *list;
     while( last->next != NULL )
     {
        last=last->next;
     }
     last->next=item;
}
}

int dequeue(t_item** list)
{
   if(*list == NULL)
      return -1;
   
   int value = (*list)->value;
   t_item *old = *list; 
   *list = (*list)->next;
   free(old);
   
   return value;
}
