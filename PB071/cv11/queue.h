#ifndef QUEUE_H
#define QUEUE_H


typedef struct qnode{
    int value;
    struct qnode* next;
}qnode;

typedef struct queue{
    qnode *first;
    qnode *last;
}queue;

/**
 * Vraci, jestli je fronta prazdna.
 * @param q fronta, ktera se testuje.
 * @return 0 - pokud fronta obsahuje nejake prvky, nenulovou hodnotu, pokud je 
 * prazdna (oba ukazatele first a last maji hodnotu NULL.)
 */
int isEmpty(queue* q);
/**
 * Inicializuje novou frontu (nastavi ukazatele first a last na hodnotu NULL.
 * @param queue - fronta, ktera se ma inicializovat.
 */ 
void initQueue(queue* queue);

/**
 * prida hodnotu na konec fronty.
 * @param value pridavana hodnota
 * @param queue fronta, do ktere se ma hodnota pridat.
 */
void enqueue(int value, queue* queue);

/**
 * Odebere z fronty 1. hodnotu.
 * @param queue fronta, ze ktere se ma hodnota odebrat.
 * @return odebranou hodnotu.
 */
int dequeue(queue* queue);
#endif // QUEUE_H
