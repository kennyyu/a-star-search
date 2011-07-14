#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/* 
 * Alias linkedlist to be a pointer to a struct linkedlist.
 */
typedef struct linkedlist *linkedlist;

/*
 * Enumeration of error and success return values for functions that return an
 * int. 
 */
typedef enum list_error_numbers 
{
	SUCCESS_LIST = 1,
	ERROR_LIST_IS_NULL = -1,
	ERROR_LIST_IS_EMPTY = -2,
	ERROR_LIST_ITEM_NOT_FOUND = -3,
	ERROR_LIST_ITEM_IS_NULL = -4,
	ERROR_LIST_MALLOC_FAIL = -5,
	ERROR_LIST_OUT_OF_BOUNDS = -6
} list_error_numbers;

/* 
 * Initialize a linkedlist and returns a pointer to the list. If there is not
 * enough memory, this returns NULL.
 */
linkedlist list_create();

/* 
 * Frees the memory held by the linkedlist.
 */
void list_free(linkedlist);

/* 
 * Returns the length of the list. If the linkedlist is NULL, this returns 
 * ERROR_LIST_IS_NULL.
 */
int list_size(linkedlist);

/* 
 * Returns 1 if the list is empty, otherwise returns 0. If the list is NULL,
 * this returns ERROR_LIST_IS_NULL.
 */
int list_is_empty(linkedlist);

/* 
 * Returns 1 if the item is in the list, otherwise returns 0. If the list is
 * NULL, this returns ERROR_LIST_IS_NULL. If the item is NULL, this returns
 * ERROR_LIST_ITEM_IS_NULL.
 */
int list_contains(linkedlist, void *);

/* 
 * Returns a pointer to the first item in the list. If the linkedlist is NULL
 * or is empty, this returns NULL.
 */ 
void *list_get_first(linkedlist);

/* 
 * Returns a pointer to the last item in the list. If the linkedlist is NULL
 * or is empty, this returns NULL.
 */
void *list_get_last(linkedlist);

/*
 * Returns a pointer to the next item in the list, after the given item. If
 * the given item is the last item in the list, the item is NULL or not in 
 * the list, or if the linkedlist is NULL, this returns NULL. Use this for 
 * iterating through the list. 
 *
 * WARNING: Do not mutate the list while iterating.
 *
 * Example:
 *		for (item = list_get_first(list); 
 *				 !list_is_empty(list); 
 *				 list_get_next(list, item)) {
 *						// process list
 *		}
 */
void *list_get_next(linkedlist, void *);

/*
 * Returns a pointer to the given index in the list. If the list is NULL, the
 * list is empty, or if the index is out of bounds, return NULL.
 */
void *list_get(linkedlist, int);

/*
 * Returns an array of pointers to the items in the list. They will be
 * returned in the order in which they were added, respecting add_first and
 * add_last. The length of the array will be the size of the array. If the
 * linkedlist is NULL, this returns NULL. If the length is 0, this returns
 * NULL.
 */
void **list_to_array(linkedlist);

/* 
 * Adds the item to the head of the list. If successful, this returns
 * SUCCESS_LIST. If the linkedlist is NULL, this returns ERROR_LIST_IS_NULL.
 */
int list_add_first(linkedlist, void *);

/* 
 * Adds the item to the tail of the list. If successful, this returns
 * SUCCESS_LIST. If the linkedlist is NULL, this returns ERROR_LIST_IS_NULL.
 */
int list_add_last(linkedlist, void *);

/*
 * Given an index position i, this sets the i-th element of the list to the
 * item. If i < 0 or i >= size, then this returns ERROR_LIST_OUT_OF_BOUNDS. 
 * If linkedlist is NULL, returns ERROR_LIST_IS_NULL. If the item is NULL, 
 * returns ERROR_LIST_ITEM_IS_NULL. On success, returns SUCCESS_LIST.
 */
int list_set(linkedlist, int, void *);

/* 
 * Removes the item from the list. If the item is not found, this returns
 * ERROR_LIST_ITEM_NOT_FOUND. If the item is NULL, this returns
 * ERROR_LIST_ITEM_IS_NULL. If the linkedlist is empty, this returns
 * ERROR_LIST_IS_EMPTY. If the linkedlist is NULL, this returns
 * ERROR_LIST_IS_NULL.
 */
int list_remove(linkedlist, void *);

/* 
 * Removes the first item from the list and returns a pointer to it. If the 
 * item is not found or if the linkedlist is empty or NULL, this returns NULL.
 */
void *list_remove_first(linkedlist);

/* 
 * Removes the last item from the list and returns a pointer to it. If the 
 * item is not found or if the linkedlist is empty or NULL, this returns NULL.
 */
void *list_remove_last(linkedlist);

#endif