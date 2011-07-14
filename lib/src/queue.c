#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "list.h"

/* 
 * We cast a linkedlist pointer into a queue pointer. This allows us to use
 * all the list functions directly on a queue pointer, without having to store
 * any extra unnecessary data.
 */
struct queue { };

queue queue_create() {
	return (queue) list_create();
}

void queue_free(queue qu) {
	list_free((list) qu);
}

int queue_size(queue qu) {
	if (!qu)
		return ERROR_QUEUE_IS_NULL;
	return list_size((list) qu);
}

int queue_is_empty(queue qu) {
	if (!qu)
		return ERROR_QUEUE_IS_NULL;
	return list_is_empty((list) qu);
}

int queue_contains(queue qu, void *item) {
	if (!qu)
		return ERROR_QUEUE_IS_NULL;
	if (!item)
		return ERROR_QUEUE_ITEM_IS_NULL;
	return list_contains((list) qu, item);
}

void *queue_peek(queue qu) {
	return list_get_first((list) qu);
}

int queue_enqueue(queue qu, void *item) {
	if (!qu)
		return ERROR_QUEUE_IS_NULL;
	if (!item)
		return ERROR_QUEUE_ITEM_IS_NULL;
		
	int error = list_add_last((list) qu, item);
	if (error == ERROR_LIST_MALLOC_FAIL)
		return ERROR_QUEUE_MALLOC_FAIL;
	return SUCCESS_QUEUE;
}

void *queue_dequeue(queue qu) {
	return list_remove_first((list) qu);
}