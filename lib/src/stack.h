#ifndef _STACK_H
#define _STACK_H

/* 
 * Alias stack to be a pointer to a struct stack. We never instantiate a stack,
 * we only cast pointers into stacks.
 */
typedef struct stack *stack;
struct stack { };

/*
 * This will return 1 if the two items are equal, 0 otherwise. If NULL is passed
 * into create, the stack will use pointer equality.
 */
typedef int (*stack_equal)(void *, void *);

/*
 * This is a function that frees an item in the stack. A pointer to this kind of
 * function will be passed into free_items.
 */
typedef void (*stack_free_item)(void *);

/*
 * Enumeration of error and success return values for functions that return an
 * int. 
 */
typedef enum stack_error_numbers stack_error_numbers;
enum stack_error_numbers {
  SUCCESS_STACK = 1,
  ERROR_STACK_IS_NULL = -1,
  ERROR_STACK_IS_EMPTY = -2,
  ERROR_STACK_ITEM_IS_NULL = -3,
  ERROR_STACK_MALLOC_FAIL = -4
};

/*
 * This struct contains pointers to operations on stacks.
 */
typedef struct stack_methods stack_methods;
struct stack_methods {
  /* 
   * Initialize a stack and returns a pointer to the stack. If there is not
   * enough memory, this returns NULL.
   */
  stack (*create)(stack_equal);

  /* 
   * Frees the memory held by the stack.
   */
  void (*free)(stack);

  /*
   * Frees the stack and the items inside the stack. If the the free_item
   * function is NULL, this function will just use free.
   */
  void (*free_items)(stack, stack_free_item);

  /* 
   * Returns the length of the stack. If the stackis NULL, this returns 
   * ERROR_STACK_IS_NULL.
   */
  int (*size)(stack);

  /* 
   * Returns 1 if the stack is empty, otherwise returns 0. If the stack is NULL,
   * this returns ERROR_STACK_IS_NULL.
   */
  int (*is_empty)(stack);

  /* 
   * Returns 1 if the item is in the stack, otherwise returns 0. If the stack is
   * NULL, this returns ERROR_STACK_IS_NULL. If the item is NULL, this returns
   * ERROR_STACK_ITEM_IS_NULL.
   */
  int (*contains)(stack, void *);

  /* 
   * Returns a pointer to the top item in the stack. If the stack is NULL
   * or is empty, this returns NULL.
   */
  void *(*peek)(stack);

  /* 
   * Adds the item to the stack. If successful, this returns SUCCESS_STACK. If 
   * the stack is NULL, this returns ERROR_STACK_IS_NULL.
   */
  int (*push)(stack, void *);

  /* 
   * Removes the top item from the stack and returns a pointer to it. If the 
   * item is not found or if the stack is empty or NULL, this returns NULL.
   */
  void *(*pop)(stack);
};

#endif