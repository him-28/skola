/**
 * @author  Pavel Ondračka <pavel.ondracka@gmail.com>
 * @version 1.0
 */

struct stack;
int mem_register;

void stack_push (struct stack* stack);
void stack_pop (struct stack* stack);
void print (const struct stack* stack);

