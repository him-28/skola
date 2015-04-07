/**
 * @author  Pavel Ondračka <pavel.ondracka@gmail.com>
 * @version 1.0
 */

#ifndef my_assert
#include <assert.h>
#define my_assert(x) assert(x)
#endif

enum instruction_type {INST_ADD, INST_SUB, INST_INC, INST_DEC, INST_MUL, INST_DIV};

struct queue {
   struct instruction* first;
   struct instruction* last;
};

struct instruction{
   struct instruction *next;
   enum instruction_type type;
   long value;
};

void queue_create (struct queue* container);

void queue_push (struct queue* container, struct instruction* item);

struct instruction* queue_pop (struct queue* container);

unsigned int queue_empty (const struct queue* container);

unsigned int queue_size (const struct queue* container);

unsigned int queue_clear (struct queue* container);
