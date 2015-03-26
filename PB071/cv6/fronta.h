//Type for the queue item
typedef struct t_item {
   char *data;
   struct t_item *next;
 } t_item;

//Type for the queue
typedef struct t_queue {
    t_item *first, *last;
 } t_queue;
 
 /**
  * Adds string to the end of the queue
  * @param queue - the queue to put the string into it
  * @param string - the string to be enqueued
  * @returns the modified queue
  */
 t_queue enqueue(t_queue queue, char *string);

 /**
  * Removes the string in the front of the queue
  * @param queue - the queue of strings
  * @returns the first string in the queue, it has been removed.
  */ 
 char *dequeue(t_queue *queue);