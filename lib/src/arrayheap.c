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

/*
 * This implementation of the heap will keep the minimum item at the top.
 */
heap heap_create(heap_compare cmp) {
	if (!cmp)
		return NULL;
	heap hp = malloc(sizeof(struct heap));
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

int heap_size(heap hp) {
	if (!hp)
		return ERROR_HEAP_IS_NULL;
	return list_size(hp->data);
}

int heap_is_empty(heap hp) {
	if (!hp)
		return ERROR_HEAP_IS_NULL;
	return heap_size(hp) == 0;	
}

int heap_contains(heap hp, void *item) {
	if (!hp)
		return ERROR_HEAP_IS_NULL;
	if (!item)
		return ERROR_HEAP_ITEM_IS_NULL;
	if (heap_is_empty(hp))
		return 0;
	return list_contains(hp->data, item);
}

void **heap_to_array(heap hp) {
	if (!hp)
		return NULL;
	return list_to_array(hp->data);
}

void *heap_peek(heap hp) {
	if (!hp)
		return NULL;
	if (heap_is_empty(hp))
		return NULL;
	return list_get_first(hp->data);
}

/* Internal. Do not use. 
 * Swaps the pointers at index1 and index2 in hp->data */
void _heap_swap(heap hp, int index1, int index2) {
	void *temp = list_get(hp->data, index1);
	list_set(hp->data, index1, list_get(hp->data, index2));
	list_set(hp->data, index2, temp);
}

/* Internal. Do not use.
 * Returns the index of the minimum of the items pointed to by the indices */
int _heap_min(heap hp, int index1, int index2) {
	return (hp->compare(list_get(hp->data, index1), 
											list_get(hp->data, index2)) < 0)? index1 : index2;
}

int heap_add(heap hp, void *item) {
	if (!hp)
		return ERROR_HEAP_IS_NULL;
	if (!item)
		return ERROR_HEAP_ITEM_IS_NULL;
		
	/* add the item to the end of the list */
	if (list_add_last(hp->data, item) != SUCCESS_LIST)
		return ERROR_HEAP_MALLOC_FAIL;
	
	/* A node at position i has parents (i - 1) / 2 (integer division).
	 * We swap the child with the parent if the child is less than the parent */
	int child = heap_size(hp) - 1;
	int parent = (child - 1) / 2;
	while (child > 0 && _heap_min(hp, child, parent) == child) {
		_heap_swap(hp, child, parent);
		child = parent;
		parent = (child - 1) / 2;
	}
	return SUCCESS_HEAP;
}

/* 
 * Removes the min item from the heap and returns a pointer to it. If the 
 * item is not found or if the heap is empty or NULL, this returns NULL.
 */
void *heap_remove(heap hp) {
	if (!hp)
		return NULL;
	if (heap_is_empty(hp))
		return NULL;
		
	/* get the first item */
	void *item = list_get_first(hp->data);
	_heap_swap(hp, 0, heap_size(hp) - 1);
	list_remove_last(hp->data);
	
	/* A node a position i has children at 2 * i + 1 and 2 * i + 2
	 * If the parent is less than its child or children, we swap. If there
	 * are multiple children, we swap with the lesser child. */
	int parent = 0;
	int least = 2 * parent + 1;
	while (least < heap_size(hp)) {
		/* check if there is a right child */
		if (least + 1 < heap_size(hp))
			least = _heap_min(hp, least, least + 1);
		if (_heap_min(hp, parent, least) == least) {
			_heap_swap(hp, parent, least);
			parent = least;
			least = 2 * parent + 1;
		} else {
			break;
		}
	}
	return item;
}

heap heap_merge(heap hp1, heap hp2) {
	if (!hp1 && !hp2)
		return NULL;
		
	heap hp3 = heap_create(hp1->compare);
	if (!hp3)
		return NULL;
	
	void **items;
	int error;
	
	/* put all items in hp1 and hp2 into hp3 */
	if (hp1) {
		items = heap_to_array(hp1);
		if (!items)
			return NULL;
		for (int i = 0; i < heap_size(hp1); i++) {
			error = heap_add(hp3, items[i]);
			if (error != SUCCESS_HEAP)
				return NULL;
		}
	}
	
	if (hp2) {
		items = heap_to_array(hp2);
		for (int i = 0; i < heap_size(hp2); i++) {
			error = heap_add(hp3, items[i]);
			if (error != SUCCESS_HEAP)
				return NULL;
		}
	}

	return hp3;
}