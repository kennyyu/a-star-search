#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "heap.h"

/*
 * A heap has an arraylist containing the items and a pointer to a compare
 * function.
 */
struct heap { 
	list data;
	heap_compare compare;
};

heap heap_create(heap_compare cmp) {
	if (!cmp)
		return NULL;
	heap hp = malloc(sizeof(heap));
	if (!hp)
		return NULL;
	hp->data = list_create();
	if (!hp->data)
		return NULL;
	hp->compare = cmp;
	return hp;
}

void heap_free(heap hp) {
	if (!hp)
		return;
	list_free(hp->data);
	free(hp);
}

/* 
 * Returns the number of elements in the heap. If the queue is NULL, this 
 * returns ERROR_HEAP_IS_NULL.
 */
int heap_size(heap hp) {
	if (!hp)
		return ERROR_HEAP_IS_NULL;
	return list_size(hp->data);
}

