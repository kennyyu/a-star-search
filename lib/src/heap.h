#ifndef _HEAP_H
#define _HEAP_H

/* 
 * Alias heap to be a pointer to a struct heap.
 */
typedef struct heap *heap;
struct heap { };

/*
 * Alias heap_compare to be a function pointer type that takes two pointers to
 * items and compares them. Returns + if the first item > second item, 0 if
 * the first item = second item, - if the first item < second item.
 */
typedef int (*heap_compare) (void *, void *);

/*
 * Enumeration of error and success return values for functions that return an
 * int. 
 */
typedef enum heap_error_numbers 
{
	SUCCESS_HEAP = 1,
	ERROR_HEAP_IS_NULL = -1,
	ERROR_HEAP_IS_EMPTY = -2,
	ERROR_HEAP_ITEM_IS_NULL = -3,
	ERROR_HEAP_MALLOC_FAIL = -4
} heap_error_numbers;

typedef struct heap_methods heap_methods;

struct heap_methods {
	/* 
	 * Initialize a heap and returns a pointer to the heap. It takes a function 
	 * pointer to a compare function that takes two item pointers and returns +, 
	 * 0, -. If there is not enough memory, this returns NULL.
	 */
	heap (*create)(heap_compare);

	/* 
	 * Frees the memory held by the heap.
	 */
	void (*free)(heap);

	/* 
	 * Returns the number of elements in the heap. If the queue is NULL, this 
	 * returns ERROR_HEAP_IS_NULL.
	 */
	int (*size)(heap);

	/* 
	 * Returns 1 if the queue is empty, otherwise returns 0. If the heap is NULL,
	 * this returns ERROR_HEAP_IS_NULL.
	 */
	int (*is_empty)(heap);

	/* 
	 * Returns 1 if the item is in the heap, otherwise returns 0. If the heap is
	 * NULL, this returns ERROR_HEAP_IS_NULL. If the item is NULL, this returns
	 * ERROR_HEAP_ITEM_IS_NULL.
	 */
	int (*contains)(heap, void *);

	/*
	 * Returns an array of pointers to the items in the heap. They will be
	 * returned in an arbitrary order. The length of the array will be the size of
	 * the heap. If the heap is NULL, this returns NULL. If the length is 0, this 
	 * returns NULL. If malloc fails, this also returns NULL.
	 */
	void **(*to_array)(heap);

	/* 
	 * Returns a pointer to the min item in the heap. If the heap is NULL or is 
	 * empty, this returns NULL.
	 */
	void *(*peek)(heap);

	/* 
	 * Adds the item to the heap. If successful, this returns SUCCESS_HEAP. If 
	 * the queue is NULL, this returns ERROR_HEAP_IS_NULL. If there is not enough
	 * memory, this returns ERROR_HEAP_MALLOC_FAIL.
	 */
	int (*add)(heap, void *);

	/* 
	 * Removes the min item from the heap and returns a pointer to it. If the 
	 * item is not found or if the heap is empty or NULL, this returns NULL.
	 */
	void *(*remove)(heap);

	/*
	 * Merges two heaps and returns a pointer to the new heap. The old heaps are
	 * not changed. If both heaps are NULL, return NULL. If one of the heaps is 
	 * NULL, returns a copy of the other heap.
	 */
	heap (*merge)(heap, heap);

};

#endif