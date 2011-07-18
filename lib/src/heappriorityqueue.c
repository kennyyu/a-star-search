#include <stdio.h>
#include <stdlib.h>
#include "priorityqueue.h"
#include "heap.h"

struct pqueue { };

pqueue pqueue_create(pqueue_compare cmp) {
	if (!cmp)
		return NULL;
	return (pqueue) heap_create((heap_compare) cmp);
}

void pqueue_free(pqueue pq) {
	if (!pq)
		return;
	heap_free((heap) pq);
}

int pqueue_size(pqueue pq) {
	if (!pq)
		return ERROR_PQUEUE_IS_NULL;
	return heap_size((heap) pq);
}

int pqueue_is_empty(pqueue pq) {
	if (!pq)
		return ERROR_PQUEUE_IS_NULL;
	return heap_is_empty((heap) pq);
}

int pqueue_contains(pqueue pq, void *item) {
	if (!pq)
		return ERROR_PQUEUE_IS_NULL;
	if (!item)
		return ERROR_PQUEUE_ITEM_IS_NULL;
	return heap_contains((heap) pq, item);
}

void *pqueue_peek(pqueue pq) {
	return heap_peek((heap) pq);
}

int pqueue_enpqueue(pqueue pq, void *item) {
	if (!pq)
		return ERROR_PQUEUE_IS_NULL;
	if (!item)
		return ERROR_PQUEUE_ITEM_IS_NULL;
		
	int error = heap_add((heap) pq, item);
	if (error == ERROR_HEAP_MALLOC_FAIL)
		return ERROR_PQUEUE_MALLOC_FAIL;
	return SUCCESS_PQUEUE;
}

void *pqueue_depqueue(pqueue pq) {
	return heap_remove((heap) pq);
}