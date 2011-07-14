#ifndef _QUEUE_H
#define _QUEUE_H

/* 
 * Alias queue to be a pointer to a struct queue.
 */
typedef struct queue *queue;

/*
 * Enumeration of error and success return values for functions that return an
 * int. 
 */
typedef enum queue_error_numbers 
{
	SUCCESS_QUEUE = 1,
	ERROR_QUEUE_IS_NULL = -1,
	ERROR_QUEUE_IS_EMPTY = -2,
	ERROR_QUEUE_ITEM_IS_NULL = -3,
	ERROR_QUEUE_MALLOC_FAIL = -4
} queue_error_numbers;

/* 
 * Initialize a queue and returns a pointer to the queue. If there is not
 * enough memory, this returns NULL.
 */
queue queue_create();

/* 
 * Frees the memory held by the queue.
 */
void queue_free(queue);

/* 
 * Returns the length of the queue. If the queue is NULL, this returns 
 * ERROR_QUEUE_IS_NULL.
 */
int queue_size(queue);

/* 
 * Returns 1 if the queue is empty, otherwise returns 0. If the queue is NULL,
 * this returns ERROR_QUEUE_IS_NULL.
 */
int queue_is_empty(queue);

/* 
 * Returns 1 if the item is in the queue, otherwise returns 0. If the queue is
 * NULL, this returns ERROR_QUEUE_IS_NULL. If the item is NULL, this returns
 * ERROR_QUEUE_ITEM_IS_NULL.
 */
int queue_contains(queue, void *);

/* 
 * Returns a pointer to the top item in the queue. If the queue is NULL
 * or is empty, this returns NULL.
 */
void *queue_peek(queue);

/* 
 * Adds the item to the queue. If successful, this returns SUCCESS_QUEUE. If 
 * the queue is NULL, this returns ERROR_QUEUE_IS_NULL.
 */
int queue_enqueue(queue, void *);

/* 
 * Removes the first item in the queue and returns a pointer to it. If the 
 * item is not found or if the queue is empty or NULL, this returns NULL.
 */
void *queue_dequeue(queue);

#endif