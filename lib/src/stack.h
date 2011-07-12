#ifndef STACK_H
#define STACK_H

typedef struct stack *stack;

stack stack_create();
void stack_free(stack);

typedef enum stack_error_numbers 
{
	SUCCESS_STACK = 1,
	ERROR_STACK_IS_NULL = -1,
	ERROR_STACK_IS_EMPTY = -2,
	ERROR_STACK_ITEM_IS_NULL = -3,
	ERROR_STACK_MALLOC_FAIL = -4
} stack_error_numbers;

int stack_size(stack);
int stack_is_empty(stack);
int stack_contains(stack, void *);
void *stack_peek(stack);
int stack_push(stack, void *);
void *stack_pop(stack);

#endif