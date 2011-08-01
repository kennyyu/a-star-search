#ifndef _LIST_H
#define _LIST_H

/* 
 * Alias list to be a pointer to a struct list. We never instantiate a list, we
 * only cast pointers to a list.
 */
typedef struct list *list;
struct list { };

/*
 * Enumeration of error and success return values for functions that return an
 * int. 
 */
typedef enum list_error_numbers list_error_numbers;
enum list_error_numbers {
	SUCCESS_LIST = 1,
	ERROR_LIST_IS_NULL = -1,
	ERROR_LIST_IS_EMPTY = -2,
	ERROR_LIST_ITEM_NOT_FOUND = -3,
	ERROR_LIST_ITEM_IS_NULL = -4,
	ERROR_LIST_MALLOC_FAIL = -5,
	ERROR_LIST_OUT_OF_BOUNDS = -6
};

/* This returns 1 if the two items pointed to are equal, otherwise 0. If NULL
 * is passed in, pointer equality will be used. */
typedef int (*list_equal)(void *, void *);

/*
 * This struct will contain pointers to operations on lists.
 */
typedef struct list_methods list_methods;
struct list_methods {
	/* 
	 * Initialize a list and returns a pointer to the list. If there is not
	 * enough memory, this returns NULL.
	 */
	list (*create)(list_equal);

	/* 
	 * Frees the memory held by the list.
	 */
	void (*free)(list);

	/* 
	 * Returns the length of the list. If the list is NULL, this returns 
	 * ERROR_LIST_IS_NULL.
	 */
	int (*size)(list);

	/* 
	 * Returns 1 if the list is empty, otherwise returns 0. If the list is NULL,
	 * this returns ERROR_LIST_IS_NULL.
	 */
	int (*is_empty)(list);

	/* 
	 * Returns 1 if the item is in the list, otherwise returns 0. If the list is
	 * NULL, this returns ERROR_LIST_IS_NULL. If the item is NULL, this returns
	 * ERROR_LIST_ITEM_IS_NULL.
	 */
	int (*contains)(list, void *);

	/* 
	 * Returns a pointer to the first item in the list. If the list is NULL
	 * or is empty, this returns NULL.
	 */ 
	void *(*get_first)(list);

	/* 
	 * Returns a pointer to the last item in the list. If the list is NULL
	 * or is empty, this returns NULL.
	 */
	void *(*get_last)(list);

	/*
	 * Returns a pointer to the given index in the list. If the list is NULL, the
	 * list is empty, or if the index is out of bounds, return NULL.
	 */
	void *(*get)(list, int);

	/*
	 * Returns an array of pointers to the items in the list. They will be
	 * returned in the order in which they were added, respecting add_first and
	 * add_last. The length of the array will be the size of the array. If the
	 * list is NULL, this returns NULL. If the length is 0, this returns
	 * NULL. If malloc fails, this also returns NULL.
	 */
	void **(*to_array)(list);

	/* 
	 * Adds the item to the head of the list. If successful, this returns
	 * SUCCESS_LIST. If the list is NULL, this returns ERROR_LIST_IS_NULL.
	 */
	int (*add_first)(list, void *);

	/* 
	 * Adds the item to the tail of the list. If successful, this returns
	 * SUCCESS_LIST. If the list is NULL, this returns ERROR_LIST_IS_NULL.
	 */
	int (*add_last)(list, void *);

	/*
	 * Given an index position i, this sets the i-th element of the list to the
	 * item. If i < 0 or i >= size, then this returns ERROR_LIST_OUT_OF_BOUNDS. 
	 * If list is NULL, returns ERROR_LIST_IS_NULL. If the item is NULL, 
	 * returns ERROR_LIST_ITEM_IS_NULL. On success, returns SUCCESS_LIST.
	 */
	int (*set)(list, int, void *);

	/* 
	 * Removes the item from the list. If the item is not found, this returns
	 * ERROR_LIST_ITEM_NOT_FOUND. If the item is NULL, this returns
	 * ERROR_LIST_ITEM_IS_NULL. If the list is empty, this returns
	 * ERROR_LIST_IS_EMPTY. If the list is NULL, this returns
	 * ERROR_LIST_IS_NULL. On success, returns SUCCESS_LIST.
	 */
	int (*remove)(list, void *);

	/* 
	 * Removes the first item from the list and returns a pointer to it. If the 
	 * item is not found or if the list is empty or NULL, this returns NULL.
	 */
	void *(*remove_first)(list);

	/* 
	 * Removes the last item from the list and returns a pointer to it. If the 
	 * item is not found or if the list is empty or NULL, this returns NULL.
	 */
	void *(*remove_last)(list);	
};

#endif