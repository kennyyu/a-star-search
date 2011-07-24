#ifndef _PRIORITYQUEUE_H
#define _PRIORITYQUEUE_H

/* 
 * Alias pqueue to be a pointer to a struct pqueue.
 */
typedef struct pqueue *pqueue;

/*
 * Alias pqueue_compare to be a function pointer type that takes two pointers 
 * to items and compares them. Returns + if the first item > second item, 0 if
 * the first item = second item, - if the first item < second item.
 */
typedef int (*pqueue_compare) (void *, void *);

/*
 * Enumeration of error and success return values for functions that return an
 * int. 
 */
typedef enum pqueue_error_numbers 
{
	SUCCESS_PQUEUE = 1,
	ERROR_PQUEUE_IS_NULL = -1,
	ERROR_PQUEUE_IS_EMPTY = -2,
	ERROR_PQUEUE_ITEM_IS_NULL = -3,
	ERROR_PQUEUE_MALLOC_FAIL = -4
} pqueue_error_numbers;

typedef struct pqueue_methods pqueue_methods;

struct pqueue_methods {
	/* 
	 * Initialize a pqueue and returns a pointer to the pqueue. If there is not
	 * enough memory, this returns NULL.
	 */
	pqueue (*create)(pqueue_compare);

	/* 
	 * Frees the memory held by the pqueue.
	 */
	void (*free)(pqueue);

	/* 
	 * Returns the length of the pqueue. If the pqueue is NULL, this returns 
	 * ERROR_PQUEUE_IS_NULL.
	 */
	int (*size)(pqueue);

	/* 
	 * Returns 1 if the pqueue is empty, otherwise returns 0. If pqueue is NULL,
	 * this returns ERROR_PQUEUE_IS_NULL.
	 */
	int (*is_empty)(pqueue);

	/* 
	 * Returns 1 if the item is in the pqueue, otherwise returns 0. If pqueue is
	 * NULL, this returns ERROR_PQUEUE_IS_NULL. If the item is NULL, this returns
	 * ERROR_PQUEUE_ITEM_IS_NULL.
	 */
	int (*contains)(pqueue, void *);

	/* 
	 * Returns a pointer to the min item in the pqueue. If the pqueue is NULL
	 * or is empty, this returns NULL.
	 */
	void *(*peek)(pqueue);

	/* 
	 * Adds the item to the pqueue. If successful, this returns SUCCESS_PQUEUE. If 
	 * the pqueue is NULL, this returns ERROR_PQUEUE_IS_NULL.
	 */
	int (*enqueue)(pqueue, void *);

	/* 
	 * Removes the min item in the pqueue and returns a pointer to it. If the 
	 * item is not found or if the pqueue is empty or NULL, this returns NULL.
	 */
	void *(*dequeue)(pqueue);

};

#endif