#ifndef _SET_H
#define _SET_H

/* 
 * Alias set to be a pointer to a struct set.
 */
typedef struct set *set;
struct set { };

/*
 * Alias set_compare to be a function pointer type that takes two pointers 
 * to items and compares them. Returns + if the first item > second item, 0 if
 * the first item = second item, - if the first item < second item. This will
 * only be used for treeset.
 */
typedef int (*set_compare) (void *, void *);

/*
 * Alias set_hash to be a function pointer type that takes a pointer to an item 
 * and returns the item's hash value. This will only be used hashset.
 */
typedef int (*set_hash) (void *);

/*
 * Alias set_equal to be a function pointer type that takes two pointers to items
 * and compares them. Return 1 if they are equal, 0 otherwise. This will only be
 * used for hashset.
 */
typedef int (*set_equal) (void *, void *);

/*
 * Enumeration of error and success return values for functions that return an
 * int. 
 */
typedef enum set_error_numbers 
{
	SUCCESS_SET = 1,
	ERROR_SET_IS_NULL = -1,
	ERROR_SET_IS_EMPTY = -2,
	ERROR_SET_ITEM_NOT_FOUND = -3,
	ERROR_SET_ITEM_IS_NULL = -4,
	ERROR_SET_MALLOC_FAIL = -5
} set_error_numbers;

typedef struct set_methods set_methods;

struct set_methods {
	/* 
	 * Initialize a set and returns a pointer to the set. If there is not
	 * enough memory, this returns NULL. If creating a treeset, only set_compare
	 * will be set and the other two will be NULL. If creating a hashset, 
	 * set_compare will be NULL and the other two will be set.
	 */
	set (*create)(set_compare, set_hash, set_equal);

	/* 
	 * Frees the memory held by the set.
	 */
	void (*free)(set);

	/* 
	 * Returns the length of the set. If the set is NULL, this returns 
	 * ERROR_SET_IS_NULL.
	 */
	int (*size)(set);

	/* 
	 * Returns 1 if the set is empty, otherwise returns 0. If the set is NULL,
	 * this returns ERROR_SET_IS_NULL.
	 */
	int (*is_empty)(set);

	/* 
	 * Returns 1 if the item is in the set, otherwise returns 0. If the set is
	 * NULL, this returns ERROR_SET_IS_NULL. If the item is NULL, this returns
	 * ERROR_SET_ITEM_IS_NULL.
	 */
	int (*contains)(set, void *);

	/*
	 * Returns an array of pointers to the items in the set. They will be
	 * returned in the order in which they were added, respecting add_first and
	 * add_last. The length of the array will be the size of the array. If the
	 * set is NULL, this returns NULL. If the length is 0, this returns
	 * NULL. If malloc fails, this also returns NULL.
	 */
	void **(*to_array)(set);

	/* 
	 * Adds the item to the set. If successful, this returns SUCCESS_SET. If 
	 * the set is NULL, this returns ERROR_SET_IS_NULL. If the item is NULL,
	 * this returns ERROR_SET_ITEM_IS_NULL. If malloc fails, return
	 * ERROR_SET_MALLOC_FAIL.
	 */
	int (*add)(set, void *);

	/* 
	 * Removes the item from the set. If the item is not found, this returns
	 * ERROR_SET_ITEM_NOT_FOUND. If the item is NULL, this returns
	 * ERROR_SET_ITEM_IS_NULL. If the set is empty, this returns
	 * ERROR_SET_IS_EMPTY. If the set is NULL, this returns
	 * ERROR_SET_IS_NULL. On success, returns SUCCESS_SET.
	 */
	int (*remove)(set, void *);
	
	/* 
	 * For treeset, this removes the minimum item. For hashset, this removes
	 * a random element. A pointer to the item is returned. This is used for 
	 * destructive iteration. If the set is NULL or is empty, this returns NULL.
	 */
	void *(*remove_random)(set);	

};

#endif