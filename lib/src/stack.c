#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "list.h"

/* 
 * We cast a linkedlist pointer into a stack pointer. This allows us to use
 * all the list functions directly on a stack pointer, without having to store
 * any extra unnecessary data.
 */
struct stack { };

stack stack_create() {
	return (stack) list_create();
}

void stack_free(stack st) {
	list_free((list) st);
}

int stack_size(stack st) {
	if (!st)
		return ERROR_STACK_IS_NULL;
	return list_size((list) st);
}

int stack_is_empty(stack st) {
	if (!st)
		return ERROR_STACK_IS_NULL;
	return list_is_empty((list) st);
}

int stack_contains(stack st, void *item) {
	if (!st)
		return ERROR_STACK_IS_NULL;
	if (!item)
		return ERROR_STACK_ITEM_IS_NULL;
	return list_contains((list) st, item);
}

void *stack_peek(stack st) {
	return list_get_first((list) st);
}

int stack_push(stack st, void *item) {
	if (!st)
		return ERROR_STACK_IS_NULL;
	if (!item)
		return ERROR_STACK_ITEM_IS_NULL;
		
	int error = list_add_last((list) st, item);
	if (error == ERROR_LIST_MALLOC_FAIL)
		return ERROR_STACK_MALLOC_FAIL;
	return SUCCESS_STACK;
}

void *stack_pop(stack st) {
	return list_remove_first((list) st);
}