#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

/* Internal. Do not use. */
struct __linkedlist_node {
	void *data;
	struct __linkedlist_node *next;
	struct __linkedlist_node *prev;
}; 
typedef struct __linkedlist_node *__linkedlist_node;	

/* we alias list to be a pointer to this struct */
typedef struct linkedlist *linkedlist;

struct linkedlist {
	__linkedlist_node head;
	__linkedlist_node tail;
	int size;
};

list _linkedlist_create() {
	linkedlist li = malloc(sizeof(struct linkedlist));
	/* if malloc returned NULL, also return NULL */
	if (!li)
		return NULL;
	li->head = NULL;
	li->tail = NULL;
	li->size = 0;
	return (list) li;
}

void _linkedlist_free(list lis) {
	linkedlist li = (linkedlist) lis;
	if (!li)
		return;
	
	__linkedlist_node current = li->head;
	while (current) {
		if (!current->next) {
			/* current is the last node */
			free(current);
			break;
		} else {
			current = current->next;
			free(current->prev);
		}
	}
	free(li);
}

int _linkedlist_size(list lis) {
	linkedlist li = (linkedlist) lis;
	if (!li)
		return ERROR_LIST_IS_NULL;
 	return li->size;
}

int _linkedlist_is_empty(list lis) {
	linkedlist li = (linkedlist) lis;
	if (!li)
		return ERROR_LIST_IS_NULL;
	return _linkedlist_size((list) li) == 0;
}

int _linkedlist_contains(list lis, void *item) {
	linkedlist li = (linkedlist) lis;
	if (!li)
		return ERROR_LIST_IS_NULL;
	if (!item)
		return ERROR_LIST_ITEM_IS_NULL;
	
	__linkedlist_node current = li->head;
	while (current) {
		if (item == current->data) 
			return 1;
		else
			current = current->next;
	}
	return 0;
}

void *_linkedlist_get_first(list lis) {
	linkedlist li = (linkedlist) lis;
	if (!li)
		return NULL;
		
	/* list is empty */
	if (!li->head)
		return NULL;	
		
	return li->head->data;
}

void *_linkedlist_get_last(list lis) {
	linkedlist li = (linkedlist) lis;
	if (!li)
		return NULL;
	
	/* list is empty */
	if (!li->tail)
		return NULL;
		
	return li->tail->data;
}

void *_linkedlist_get(list lis, int index) {
	linkedlist li = (linkedlist) lis;
	if (!li)
		return NULL;
	if (!li->size)
		return NULL;
	if ((index < 0) || (index >= li->size))
		return NULL;
	
	__linkedlist_node current = li->head;
	for (int i = 0; i < index; i++) {
		current = current->next;
	}
	return current->data;
}

void **_linkedlist_to_array(list lis) {
	linkedlist li = (linkedlist) lis;
	if (!li || li->size == 0)
		return NULL;
		
	void **items = malloc(li->size * sizeof(void *));
	if (!items)
		return NULL;
	int counter = 0;
	__linkedlist_node current = li->head;
	while (current) {
		items[counter] = current;
		counter++;
		current = current->next;
	}
	return items;
}

int _linkedlist_add_first(list lis, void *item) {
	linkedlist li = (linkedlist) lis;
	if (!li)
		return ERROR_LIST_IS_NULL;
	if (!item)
		return ERROR_LIST_ITEM_IS_NULL;
	
	/* make a new node to contain the item */
	__linkedlist_node node = malloc(sizeof(struct __linkedlist_node));
	if (!node)
		return ERROR_LIST_MALLOC_FAIL;
	node->next = NULL;
	node->prev = NULL;
	node->data = item;

	/* if there are no elements in the list, set head and tail to node
	 * else reset node's next pointer, set head's prev to node, and set 
	 * head to node */
	if (!li->head) {
		li->head = node;
		li->tail = node;
	} else {
		node->next = li->head;
		li->head->prev = node;	
		li->head = node;
	}

	/* update size */
	li->size++;
	return SUCCESS_LIST;
}

int _linkedlist_add_last(list lis, void *item) {
	linkedlist li = (linkedlist) lis;
	if (!li)
		return ERROR_LIST_IS_NULL;
	if (!item)
		return ERROR_LIST_ITEM_IS_NULL;
	
	/* make a new node to contain the item */
	__linkedlist_node node = malloc(sizeof(struct __linkedlist_node));
	if (!node)
		return ERROR_LIST_MALLOC_FAIL;
	node->next = NULL;
	node->prev = NULL;
	node->data = item;

	/* if there are no elements in the list, set head and tail to node
	 * else reset tail's next pointer, prev to tail, and set tail to node */	
	if (!li->tail) {
		li->head = node;
		li->tail = node;
	} else {
		node->prev = li->tail;
		li->tail->next = node;	
		li->tail = node;
	}

	/* update size */
	li->size++;
	return SUCCESS_LIST;
}

int _linkedlist_set(list lis, int index, void *item) {
	linkedlist li = (linkedlist) lis;
	if (!li)
		return ERROR_LIST_IS_NULL;
	if (!item)
		return ERROR_LIST_ITEM_IS_NULL;
	if (index < 0 || index >= li->size)
		return ERROR_LIST_OUT_OF_BOUNDS;
	
	__linkedlist_node current = li->head;
	for (int i = 0; i < index; i++)
		current = current->next;
	current->data = item;
	return SUCCESS_LIST;
}

void *_linkedlist_remove_first(list lis) {
	linkedlist li = (linkedlist) lis;
	if (!li)
		return NULL;
	if (!li->head)
		return NULL;	
	
	void *item = li->head->data;
	
	/* check if only one item in list */
	if (li->head == li->tail)
		li->tail = li->head->next;
	li->head = li->head->next;
	
	/* check if the new head is NULL */
	if (li->head)
		li->head->prev = NULL;
	li->size--;
	return item;
}

void *_linkedlist_remove_last(list lis) {
	linkedlist li = (linkedlist) lis;
	if (!li)
		return NULL;
	if (!li->tail)
		return NULL;	
	
	void *item = li->tail->data;

	/* check if only one item in list */
	if (li->head == li->tail)
		li->head = li->tail->prev;
	li->tail = li->tail->prev;
	
	/* check if the new head is NULL */
	if (li->tail)
		li->tail->next = NULL;
	li->size--;
	return item;
}

int _linkedlist_remove(list lis, void *item) {
	linkedlist li = (linkedlist) lis;
	if (!li)
		return ERROR_LIST_IS_NULL;
	if (!item)
		return ERROR_LIST_ITEM_IS_NULL;
	if (li->size == 0)
		return ERROR_LIST_IS_EMPTY;
	
	__linkedlist_node current = li->head;
	while (current) {
		if (current->data == item) {
			if (current->prev) {
				current->prev->next = current->next;
			} else {
				/* current is the first item in the list */
				if (li->tail == li->head) {
					/* current is the only item in the list */
					li->tail = current->next;
				}
				li->head = current->next;
			}
			if (current->next) {
				current->next->prev = current->prev;
			} else {
				/* current is the last item in the list */
				if (li->tail == li->head) {
					/* current is the only item in the list */
					li->head = current->prev;
				}
				li->tail = current->prev;
			}
			li->size--;
			return SUCCESS_LIST;
		}
		current = current->next;
	}
	
	return ERROR_LIST_ITEM_NOT_FOUND;
}

/* initialize linkedlist manually */
list_methods linkedlist_methods = {
	.create = &_linkedlist_create,
	.free = &_linkedlist_free,
	.size = &_linkedlist_size,
	.is_empty = &_linkedlist_is_empty,
	.contains = &_linkedlist_contains,
	.get_first = &_linkedlist_get_first,
	.get_last = &_linkedlist_get_last,
	.get = &_linkedlist_get,
	.to_array = &_linkedlist_to_array,
	.add_first = &_linkedlist_add_first,
	.add_last = &_linkedlist_add_last,
	.set = &_linkedlist_set,
	.remove = &_linkedlist_remove,
	.remove_first = &_linkedlist_remove_first,
	.remove_last = &_linkedlist_remove_last,
};