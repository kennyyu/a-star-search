#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* Internal. Do not use. */
struct _list_node {
	void *data;
	struct _list_node *next;
	struct _list_node *prev;
}; 
typedef struct _list_node *_list_node;	

/* we alias list to be a pointer to this struct */
struct list {
	_list_node head;
	_list_node tail;
	int size;
};

list list_create() {
	list li = malloc(sizeof(struct list));
	/* if malloc returned NULL, also return NULL */
	if (!li)
		return NULL;
	li->head = NULL;
	li->tail = NULL;
	li->size = 0;
	return li;
}

void list_free(list li) {
	if (!li)
		return;
	
	_list_node current = li->head;
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

int list_size(list li) {
	if (!li)
		return ERROR_LIST_IS_NULL;
 	return li->size;
}

int list_is_empty(list li) {
	if (!li)
		return ERROR_LIST_IS_NULL;
	return list_size(li) == 0;
}

int list_contains(list li, void *item) {
	if (!li)
		return ERROR_LIST_IS_NULL;
	if (!item)
		return ERROR_LIST_ITEM_IS_NULL;
	
	_list_node current = li->head;
	while (current) {
		if (item == current->data) 
			return 1;
		else
			current = current->next;
	}
	return 0;
}

void *list_get_first(list li) {
	if (!li)
		return NULL;
		
	/* list is empty */
	if (!li->head)
		return NULL;	
		
	return li->head->data;
}

void *list_get_last(list li) {
	if (!li)
		return NULL;
	
	/* list is empty */
	if (!li->tail)
		return NULL;
		
	return li->tail->data;
}

void *list_get(list li, int index) {
	if (!li)
		return NULL;
	if (!li->size)
		return NULL;
	if ((index < 0) || (index >= li->size))
		return NULL;
	
	_list_node current = li->head;
	for (int i = 0; i < index; i++) {
		current = current->next;
	}
	return current->data;
}

void **list_to_array(list li) {
	if (!li || li->size == 0)
		return NULL;
		
	void **items = malloc(li->size * sizeof(void *));
	if (!items)
		return NULL;
	int counter = 0;
	_list_node current = li->head;
	while (current) {
		items[counter] = current;
		counter++;
		current = current->next;
	}
	return items;
}

int list_add_first(list li, void *item) {
	if (!li)
		return ERROR_LIST_IS_NULL;
	if (!item)
		return ERROR_LIST_ITEM_IS_NULL;
	
	/* make a new node to contain the item */
	_list_node node = malloc(sizeof(struct _list_node));
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

int list_add_last(list li, void *item) {
	if (!li)
		return ERROR_LIST_IS_NULL;
	if (!item)
		return ERROR_LIST_ITEM_IS_NULL;
	
	/* make a new node to contain the item */
	_list_node node = malloc(sizeof(struct _list_node));
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

int list_set(list li, int index, void *item) {
	if (!li)
		return ERROR_LIST_IS_NULL;
	if (!item)
		return ERROR_LIST_ITEM_IS_NULL;
	if (index < 0 || index >= li->size)
		return ERROR_LIST_OUT_OF_BOUNDS;
	
	_list_node current = li->head;
	for (int i = 0; i < index; i++)
		current = current->next;
	current->data = item;
	return SUCCESS_LIST;
}

void *list_remove_first(list li) {
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

void *list_remove_last(list li) {
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

int list_remove(list li, void *item) {
	if (!li)
		return ERROR_LIST_IS_NULL;
	if (!item)
		return ERROR_LIST_ITEM_IS_NULL;
	if (li->size == 0)
		return ERROR_LIST_IS_EMPTY;
	
	_list_node current = li->head;
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



