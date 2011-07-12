#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue *queue;

queue queue_create();
void queue_free(queue);

typedef enum queue_error_numbers 
{
	SUCCESS_QUEUE = 1,
	ERROR_QUEUE_IS_NULL = -1,
	ERROR_QUEUE_IS_EMPTY = -2,
	ERROR_QUEUE_ITEM_IS_NULL = -3,
	ERROR_QUEUE_MALLOC_FAIL = -4
} queue_error_numbers;

int queue_size(queue);
int queue_is_empty(queue);
int queue_contains(queue, void *);
void *queue_peek(queue);
int queue_enqueue(queue, void *);
void *queue_dequeue(queue);

#endif