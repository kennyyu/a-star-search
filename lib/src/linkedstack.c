#include <stdio.h>
#include <stdlib.h>
#include "linkedstack.h"

/* 
 * We cast a linkedlist pointer into a stack pointer. This allows us to use
 * all the list functions directly on a stack pointer, without having to store
 * any extra unnecessary data.
 */
struct linkedstack { };

stack _linkedstack_create() {
	return (stack) linkedlist_methods.create();
}

void _linkedstack_free(stack st) {
	linkedlist_methods.free((list) st);
}

int _linkedstack_size(stack st) {
	if (!st)
		return ERROR_STACK_IS_NULL;
	return linkedlist_methods.size((list) st);
}

int _linkedstack_is_empty(stack st) {
	if (!st)
		return ERROR_STACK_IS_NULL;
	return linkedlist_methods.is_empty((list) st);
}

int _linkedstack_contains(stack st, void *item) {
	if (!st)
		return ERROR_STACK_IS_NULL;
	if (!item)
		return ERROR_STACK_ITEM_IS_NULL;
	return linkedlist_methods.contains((list) st, item);
}

void *_linkedstack_peek(stack st) {
	return linkedlist_methods.get_first((list) st);
}

int _linkedstack_push(stack st, void *item) {
	if (!st)
		return ERROR_STACK_IS_NULL;
	if (!item)
		return ERROR_STACK_ITEM_IS_NULL;
		
	int error = linkedlist_methods.add_last((list) st, item);
	if (error == ERROR_LIST_MALLOC_FAIL)
		return ERROR_STACK_MALLOC_FAIL;
	return SUCCESS_STACK;
}

void *_linkedstack_pop(stack st) {
	return linkedlist_methods.remove_first((list) st);
}

stack_methods linkedstack_methods = {
	.create = &_linkedstack_create,
	.free = &_linkedstack_free,
	.size = &_linkedstack_size,
	.is_empty = &_linkedstack_is_empty,
	.contains = &_linkedstack_contains,
	.peek = &_linkedstack_peek,
	.push = &_linkedstack_push,
	.pop = &_linkedstack_pop,
};