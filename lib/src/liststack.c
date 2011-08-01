#include <stdio.h>
#include <stdlib.h>
#include "liststack.h"

/* 
 * We cast a linkedlist pointer into a stack pointer. This allows us to use
 * all the list functions directly on a stack pointer, without having to store
 * any extra unnecessary data.
 */
typedef struct _liststack *_liststack;
struct _liststack { };

stack _liststack_create(stack_equal eq) {
	return (stack) linkedlist_methods.create(eq);
}

void _liststack_free(stack st) {
	linkedlist_methods.free((list) st);
}

int _liststack_size(stack st) {
	if (!st)
		return ERROR_STACK_IS_NULL;
	return linkedlist_methods.size((list) st);
}

int _liststack_is_empty(stack st) {
	if (!st)
		return ERROR_STACK_IS_NULL;
	return linkedlist_methods.is_empty((list) st);
}

int _liststack_contains(stack st, void *item) {
	if (!st)
		return ERROR_STACK_IS_NULL;
	if (!item)
		return ERROR_STACK_ITEM_IS_NULL;
	return linkedlist_methods.contains((list) st, item);
}

void *_liststack_peek(stack st) {
	return linkedlist_methods.get_first((list) st);
}

int _liststack_push(stack st, void *item) {
	if (!st)
		return ERROR_STACK_IS_NULL;
	if (!item)
		return ERROR_STACK_ITEM_IS_NULL;
		
	int error = linkedlist_methods.add_last((list) st, item);
	if (error == ERROR_LIST_MALLOC_FAIL)
		return ERROR_STACK_MALLOC_FAIL;
	return SUCCESS_STACK;
}

void *_liststack_pop(stack st) {
	return linkedlist_methods.remove_first((list) st);
}

stack_methods liststack_methods = {
	.create = &_liststack_create,
	.free = &_liststack_free,
	.size = &_liststack_size,
	.is_empty = &_liststack_is_empty,
	.contains = &_liststack_contains,
	.peek = &_liststack_peek,
	.push = &_liststack_push,
	.pop = &_liststack_pop,
};