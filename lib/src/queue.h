#ifndef _QUEUE_H
#define _QUEUE_H

/* 
 * Alias queue to be a pointer to a struct queue. We never instantiate a queue,
 * we only cast pointers into queues.
 */
typedef struct queue *queue;
struct queue { };

/*
 * This will return 1 if the two items are equal, 0 otherwise. If NULL is passed
 * in for create, the queue will use pointer equality.
 */
typedef int (*queue_equal)(void *, void *);

/*
 * This is a function that frees an item in the queue. A pointer to this kind of
 * function will be passed into free_items.
 */
typedef void (*queue_free_item)(void *);

/*
 * Enumeration of error and success return values for functions that return an
 * int. 
 */
typedef enum queue_error_numbers queue_error_numbers;
enum queue_error_numbers {
	SUCCESS_QUEUE = 1,
	ERROR_QUEUE_IS_NULL = -1,
	ERROR_QUEUE_IS_EMPTY = -2,
	ERROR_QUEUE_ITEM_IS_NULL = -3,
	ERROR_QUEUE_MALLOC_FAIL = -4
};

/*
 * This struct contains pointers to operations on queues.
 */
typedef struct queue_methods queue_methods;
struct queue_methods {
	/* 
	 * Initialize a queue and returns a pointer to the queue. If there is not
	 * enough memory, this returns NULL.
	 */
	queue (*create)(queue_equal);

	/* 
	 * Frees the memory held by the queue.
	 */
	void (*free)(queue);
	
	/*
	 * Frees the queue and the items inside the queue. If the the free_item
	 * function is NULL, this function will just use free.
	 */
	void (*free_items)(queue, queue_free_item);

	/* 
	 * Returns the length of the queue. If the queue is NULL, this returns 
	 * ERROR_QUEUE_IS_NULL.
	 */
	int (*size)(queue);

	/* 
	 * Returns 1 if the queue is empty, otherwise returns 0. If the queue is NULL,
	 * this returns ERROR_QUEUE_IS_NULL.
	 */
	int (*is_empty)(queue);

	/* 
	 * Returns 1 if the item is in the queue, otherwise returns 0. If the queue is
	 * NULL, this returns ERROR_QUEUE_IS_NULL. If the item is NULL, this returns
	 * ERROR_QUEUE_ITEM_IS_NULL.
	 */
	int (*contains)(queue, void *);

	/* 
	 * Returns a pointer to the top item in the queue. If the queue is NULL
	 * or is empty, this returns NULL.
	 */
	void *(*peek)(queue);

	/* 
	 * Adds the item to the queue. If successful, this returns SUCCESS_QUEUE. If 
	 * the queue is NULL, this returns ERROR_QUEUE_IS_NULL.
	 */
	int (*enqueue)(queue, void *);

	/* 
	 * Removes the first item in the queue and returns a pointer to it. If the 
	 * item is not found or if the queue is empty or NULL, this returns NULL.
	 */
	void *(*dequeue)(queue);
};

#endif