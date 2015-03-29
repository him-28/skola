#ifndef my_assert
#include <assert.h>
#define my_assert(x) assert(x)
#endif

struct queue;
struct instruction;

void queue_create (struct queue* container);

void queue_push (struct queue* container, struct instruction* item);

struct instruction* queue_pop (struct queue* container);

unsigned int queue_empty (const struct queue* container);

unsigned int queue_size (const struct queue* container);

unsigned int queue_clear (struct queue* container);
