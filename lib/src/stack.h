#ifndef _STACK_H
#define _STACK_H

/* 
 * Alias stack to be a pointer to a struct stack.
 */
typedef struct stack *stack;

/*
 * Enumeration of error and success return values for functions that return an
 * int. 
 */
typedef enum stack_error_numbers 
{
	SUCCESS_STACK = 1,
	ERROR_STACK_IS_NULL = -1,
	ERROR_STACK_IS_EMPTY = -2,
	ERROR_STACK_ITEM_IS_NULL = -3,
	ERROR_STACK_MALLOC_FAIL = -4
} stack_error_numbers;

/* 
 * Initialize a stack and returns a pointer to the stack. If there is not
 * enough memory, this returns NULL.
 */
stack stack_create();

/* 
 * Frees the memory held by the stack.
 */
void stack_free(stack);

/* 
 * Returns the length of the stack. If the stackis NULL, this returns 
 * ERROR_STACK_IS_NULL.
 */
int stack_size(stack);

/* 
 * Returns 1 if the stack is empty, otherwise returns 0. If the stack is NULL,
 * this returns ERROR_STACK_IS_NULL.
 */
int stack_is_empty(stack);

/* 
 * Returns 1 if the item is in the stack, otherwise returns 0. If the stack is
 * NULL, this returns ERROR_STACK_IS_NULL. If the item is NULL, this returns
 * ERROR_STACK_ITEM_IS_NULL.
 */
int stack_contains(stack, void *);

/* 
 * Returns a pointer to the top item in the stack. If the stack is NULL
 * or is empty, this returns NULL.
 */
void *stack_peek(stack);

/* 
 * Adds the item to the stack. If successful, this returns SUCCESS_STACK. If 
 * the stack is NULL, this returns ERROR_STACK_IS_NULL.
 */
int stack_push(stack, void *);

/* 
 * Removes the top item from the stack and returns a pointer to it. If the 
 * item is not found or if the stack is empty or NULL, this returns NULL.
 */
void *stack_pop(stack);

#endif