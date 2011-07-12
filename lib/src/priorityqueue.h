#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

typedef struct pqueue *pqueue;

pqueue pqueue_create();
void pqueue_free(pqueue);

typedef enum pqueue_error_numbers 
{
	SUCCESS_PQUEUE = 1,
	ERROR_PQUEUE_IS_NULL = -1,
	ERROR_PQUEUE_IS_EMPTY = -2,
	ERROR_PQUEUE_ITEM_IS_NULL = -3,
	ERROR_PQUEUE_MALLOC_FAIL = -4
} pqueue_error_numbers;

int pqueue_size(pqueue);
int pqueue_is_empty(pqueue);
int pqueue_contains(pqueue, void *);
void *pqueue_peek(pqueue);
int pqueue_enpqueue(pqueue, void *);
void *pqueue_depqueue(pqueue);

#endif