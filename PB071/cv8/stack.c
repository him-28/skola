#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct t_item{
   char *value;
   struct t_item *next;
}t_item;

int push(t_item** stack,char *value);
char* pop(t_item** stack);
void list(t_item* stack);

int main()
{
  char *text;
  t_item *stack = NULL;
  text = calloc(250,sizeof(char));
  text = fgets(text,250,stdin);
  while(strlen(text)>1)
  {
    push(&stack,text);
    text = calloc(250,sizeof(char));
    fgets(text,250,stdin);
  }
  free(text);

  list(stack);
  char *c;
  while((c=pop(&stack))!=0)
  {
     puts(c);
     free(c);
  }

  return 0;
}

int push(t_item** stack,char *value)
{
  t_item* item = malloc(sizeof(t_item));
  if(item==NULL)return 0;
  item->value=value;
  item->next = *stack;
  *stack=item;
  return 1;
}
char* pop(t_item** stack)
{
   char* value = NULL;
   if(*stack != NULL)
   {
      value = (*stack)->value;
      t_item *old = *stack;
      *stack = (*stack)->next;
      free(old);
   }
   return value;
}

void list(t_item* stack)
{
   t_item *actual = stack;

   while(actual!=NULL)
   {
      puts(actual->value);
      actual = actual->next;
   }
}
