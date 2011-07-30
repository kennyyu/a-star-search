#include <stdio.h>
#include <stdlib.h>
#include "listqueue.h"

/* 
 * We cast a linkedlist pointer into a queue pointer. This allows us to use
 * all the list functions directly on a queue pointer, without having to store
 * any extra unnecessary data.
 */
typedef struct _listqueue *_listqueue;
struct _listqueue { };

queue _listqueue_create() {
	return (queue) linkedlist_methods.create();
}

void _listqueue_free(queue qu) {
	linkedlist_methods.free((list) qu);
}

int _listqueue_size(queue qu) {
	if (!qu)
		return ERROR_QUEUE_IS_NULL;
	return linkedlist_methods.size((list) qu);
}

int _listqueue_is_empty(queue qu) {
	if (!qu)
		return ERROR_QUEUE_IS_NULL;
	return linkedlist_methods.is_empty((list) qu);
}

int _listqueue_contains(queue qu, void *item) {
	if (!qu)
		return ERROR_QUEUE_IS_NULL;
	if (!item)
		return ERROR_QUEUE_ITEM_IS_NULL;
	return linkedlist_methods.contains((list) qu, item);
}

void *_listqueue_peek(queue qu) {
	return linkedlist_methods.get_first((list) qu);
}

int _listqueue_enqueue(queue qu, void *item) {
	if (!qu)
		return ERROR_QUEUE_IS_NULL;
	if (!item)
		return ERROR_QUEUE_ITEM_IS_NULL;
		
	int error = linkedlist_methods.add_last((list) qu, item);
	if (error == ERROR_LIST_MALLOC_FAIL)
		return ERROR_QUEUE_MALLOC_FAIL;
	return SUCCESS_QUEUE;
}

void *_listqueue_dequeue(queue qu) {
	return linkedlist_methods.remove_first((list) qu);
}

queue_methods listqueue_methods = {
	.create = &_listqueue_create,
	.free = &_listqueue_free,
	.size = &_listqueue_size,
	.is_empty = &_listqueue_is_empty,
	.contains = &_listqueue_contains,
	.peek = &_listqueue_peek,
	.enqueue = &_listqueue_enqueue,
	.dequeue = &_listqueue_dequeue,
};