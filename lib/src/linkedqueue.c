#include <stdio.h>
#include <stdlib.h>
#include "linkedqueue.h"

/* 
 * We cast a linkedlist pointer into a queue pointer. This allows us to use
 * all the list functions directly on a queue pointer, without having to store
 * any extra unnecessary data.
 */
typedef struct _linkedqueue *_linkedqueue;
struct _linkedqueue { };

queue _linkedqueue_create() {
	return (queue) linkedlist_methods.create();
}

void _linkedqueue_free(queue qu) {
	linkedlist_methods.free((list) qu);
}

int _linkedqueue_size(queue qu) {
	if (!qu)
		return ERROR_QUEUE_IS_NULL;
	return linkedlist_methods.size((list) qu);
}

int _linkedqueue_is_empty(queue qu) {
	if (!qu)
		return ERROR_QUEUE_IS_NULL;
	return linkedlist_methods.is_empty((list) qu);
}

int _linkedqueue_contains(queue qu, void *item) {
	if (!qu)
		return ERROR_QUEUE_IS_NULL;
	if (!item)
		return ERROR_QUEUE_ITEM_IS_NULL;
	return linkedlist_methods.contains((list) qu, item);
}

void *_linkedqueue_peek(queue qu) {
	return linkedlist_methods.get_first((list) qu);
}

int _linkedqueue_enqueue(queue qu, void *item) {
	if (!qu)
		return ERROR_QUEUE_IS_NULL;
	if (!item)
		return ERROR_QUEUE_ITEM_IS_NULL;
		
	int error = linkedlist_methods.add_last((list) qu, item);
	if (error == ERROR_LIST_MALLOC_FAIL)
		return ERROR_QUEUE_MALLOC_FAIL;
	return SUCCESS_QUEUE;
}

void *_linkedqueue_dequeue(queue qu) {
	return linkedlist_methods.remove_first((list) qu);
}

queue_methods linkedqueue_methods = {
	.create = &_linkedqueue_create,
	.free = &_linkedqueue_free,
	.size = &_linkedqueue_size,
	.is_empty = &_linkedqueue_is_empty,
	.contains = &_linkedqueue_contains,
	.peek = &_linkedqueue_peek,
	.enqueue = &_linkedqueue_enqueue,
	.dequeue = &_linkedqueue_dequeue,
};