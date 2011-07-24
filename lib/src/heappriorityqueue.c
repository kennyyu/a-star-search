#include <stdio.h>
#include <stdlib.h>
#include "heappriorityqueue.h"

struct heappqueue { };

pqueue _heappqueue_create(pqueue_compare cmp) {
	if (!cmp)
		return NULL;
	return (pqueue) arrayheap_methods.create((heap_compare) cmp);
}

void _heappqueue_free(pqueue pq) {
	if (!pq)
		return;
	arrayheap_methods.free((heap) pq);
}

int _heappqueue_size(pqueue pq) {
	if (!pq)
		return ERROR_PQUEUE_IS_NULL;
	return arrayheap_methods.size((heap) pq);
}

int _heappqueue_is_empty(pqueue pq) {
	if (!pq)
		return ERROR_PQUEUE_IS_NULL;
	return arrayheap_methods.is_empty((heap) pq);
}

int _heappqueue_contains(pqueue pq, void *item) {
	if (!pq)
		return ERROR_PQUEUE_IS_NULL;
	if (!item)
		return ERROR_PQUEUE_ITEM_IS_NULL;
	return arrayheap_methods.contains((heap) pq, item);
}

void *_heappqueue_peek(pqueue pq) {
	return arrayheap_methods.peek((heap) pq);
}

int _heappqueue_enqueue(pqueue pq, void *item) {
	if (!pq)
		return ERROR_PQUEUE_IS_NULL;
	if (!item)
		return ERROR_PQUEUE_ITEM_IS_NULL;
		
	int error = arrayheap_methods.add((heap) pq, item);
	if (error == ERROR_HEAP_MALLOC_FAIL)
		return ERROR_PQUEUE_MALLOC_FAIL;
	return SUCCESS_PQUEUE;
}

void *_heappqueue_dequeue(pqueue pq) {
	return arrayheap_methods.remove((heap) pq);
}

pqueue_methods heappqueue_methods = {
	.create = &_heappqueue_create,
	.free = &_heappqueue_free,
	.size = &_heappqueue_size,
	.is_empty = &_heappqueue_is_empty,
	.contains = &_heappqueue_contains,
	.peek = &_heappqueue_peek,
	.enqueue = &_heappqueue_enqueue,
	.dequeue = &_heappqueue_dequeue,
};