/**
 * @author  Pavel Ondračka <pavel.ondracka@gmail.com>
 * @version 1.0
 */

#include <stdlib.h>
#include <stdio.h>

struct stack{
   unsigned int stack_top;
   int stack_values[20];
};

int mem_register = 0;

/**
 * Puts a value from mem_register at end of the stack
 *
 * @param stack pointer
 */
void stack_push (struct stack* stack){
   if(!stack){
      fprintf(stderr, "Null argument!\n");
      return;
   }

   if(stack->stack_top > 19){
      fprintf(stderr, "Stack full!\n");
      return;
   }

   stack->stack_values[stack->stack_top] = mem_register;
   stack->stack_top++;
}

/**
 * Clears a last value from the stack
 *
 * @param stack pointer
 */
void stack_pop (struct stack* stack){
   if(!stack){
      fprintf(stderr, "Null argument!\n");
      return;
   }
   if(stack->stack_top < 1)
      return;
   stack->stack_values[stack->stack_top - 1] = 0;
   stack->stack_top--;
}

/**
 * Prints stack values and memory values
 *
 * @param stack pointer
 */
void print (const struct stack* stack){
   if(!stack){
      fprintf(stderr, "Null argument!\n");
      return;
   }

   printf("# Register %i | Stack ", mem_register);
   for(unsigned int i = 0; i < stack->stack_top; i++)
      printf("%i ", stack->stack_values[i]);
   printf("\n");
}
