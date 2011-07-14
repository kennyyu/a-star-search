#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

/* Internal. Do not use. */
struct _list_node {
	void *data;
	struct _list_node *next;
	struct _list_node *prev;
}; 
typedef struct _list_node *_list_node;	

/* we alias linkedlist to be a pointer to this struct */
struct linkedlist {
	_list_node head;
	_list_node tail;
	int size;
};

linkedlist list_create() {
	linkedlist list = malloc(sizeof(struct linkedlist));
	/* if malloc returned NULL, also return NULL */
	if (!list)
		return NULL;
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return list;
}

void list_free(linkedlist list) {
	if (!list)
		return;
	
	_list_node current = list->head;
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
	free(list);
}

int list_size(linkedlist list) {
	if (!list)
		return ERROR_LIST_IS_NULL;
 	return list->size;
}

int list_is_empty(linkedlist list) {
	if (!list)
		return ERROR_LIST_IS_NULL;
	return list_size(list) == 0;
}

int list_contains(linkedlist list, void *item) {
	if (!list)
		return ERROR_LIST_IS_NULL;
	if (!item)
		return ERROR_LIST_ITEM_IS_NULL;
	
	_list_node current = list->head;
	while (current) {
		if (item == current->data) 
			return 1;
		else
			current = current->next;
	}
	return 0;
}

void *list_get_first(linkedlist list) {
	if (!list)
		return NULL;
		
	/* list is empty */
	if (!list->head)
		return NULL;	
		
	return list->head->data;
}

void *list_get_last(linkedlist list) {
	if (!list)
		return NULL;
	
	/* list is empty */
	if (!list->tail)
		return NULL;
		
	return list->tail->data;
}

void *list_get_next(linkedlist list, void *item) {
	if (!list)
		return NULL;
	
	_list_node current = list->head;
	while (current) {
		if (item == current->data) {
			if (!current->next) {
				/* current is the last item; there is no next */
				return NULL;
			} else {
				return current->next->data;
			}
		} else {
			current = current->next;
		}
	}
	
	/* item not found */
	return NULL;
}

void *list_get(linkedlist list, int index) {
	if (!list)
		return NULL;
	if (!list->size)
		return NULL;
	if ((index < 0) || (index >= list->size))
		return NULL;
	
	_list_node current = list->head;
	for (int i = 0; i < index; i++) {
		current = current->next;
	}
	return current->data;
}

void **list_to_array(linkedlist list) {
	if (!list || list->size == 0)
		return NULL;
		
	void **items = malloc(list->size * sizeof(void *));
	int counter = 0;
	_list_node current = list->head;
	while (current) {
		items[counter] = current;
		counter++;
		current = current->next;
	}
	return items;
}

int list_add_first(linkedlist list, void *item) {
	if (!list)
		return ERROR_LIST_IS_NULL;
	
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
	if (!list->head) {
		list->head = node;
		list->tail = node;
	} else {
		node->next = list->head;
		list->head->prev = node;	
		list->head = node;
	}

	/* update size */
	list->size++;
	return SUCCESS_LIST;
}

int list_add_last(linkedlist list, void *item) {
	if (!list)
		return ERROR_LIST_IS_NULL;
	
	/* make a new node to contain the item */
	_list_node node = malloc(sizeof(struct _list_node));
	if (!node)
		return ERROR_LIST_MALLOC_FAIL;
	node->next = NULL;
	node->prev = NULL;
	node->data = item;

	/* if there are no elements in the list, set head and tail to node
	 * else reset tail's next pointer, prev to tail, and set tail to node */	
	if (!list->tail) {
		list->head = node;
		list->tail = node;
	} else {
		node->prev = list->tail;
		list->tail->next = node;	
		list->tail = node;
	}

	/* update size */
	list->size++;
	return SUCCESS_LIST;
}

int list_set(linkedlist list, int index, void *item) {
	if (!list)
		return ERROR_LIST_IS_NULL;
	if (!item)
		return ERROR_LIST_ITEM_IS_NULL;
	if (index < 0 || index >= list->size)
		return ERROR_LIST_OUT_OF_BOUNDS;
	
	_list_node current = list->head;
	for (int i = 0; i < index; i++)
		current = current->next;
	current->data = item;
	return SUCCESS_LIST;
}

void *list_remove_first(linkedlist list) {
	if (!list)
		return NULL;
	if (!list->head)
		return NULL;	
	
	void *item = list->head->data;
	
	/* check if only one item in list */
	if (list->head == list->tail)
		list->tail = list->head->next;
	list->head = list->head->next;
	
	/* check if the new head is NULL */
	if (list->head)
		list->head->prev = NULL;
	list->size--;
	return item;
}

void *list_remove_last(linkedlist list) {
	if (!list)
		return NULL;
	if (!list->tail)
		return NULL;	
	
	void *item = list->tail->data;

	/* check if only one item in list */
	if (list->head == list->tail)
		list->head = list->tail->prev;
	list->tail = list->tail->prev;
	
	/* check if the new head is NULL */
	if (list->tail)
		list->tail->next = NULL;
	list->size--;
	return item;
}

int list_remove(linkedlist list, void *item) {
	if (!list)
		return ERROR_LIST_IS_NULL;
	if (!item)
		return ERROR_LIST_ITEM_IS_NULL;
	if (list->size == 0)
		return ERROR_LIST_IS_EMPTY;
	
	_list_node current = list->head;
	while (current) {
		if (current->data == item) {
			if (current->prev) {
				current->prev->next = current->next;
			} else {
				/* current is the first item in the list */
				if (list->tail == list->head) {
					/* current is the only item in the list */
					list->tail = current->next;
				}
				list->head = current->next;
			}
			if (current->next) {
				current->next->prev = current->prev;
			} else {
				/* current is the last item in the list */
				if (list->tail == list->head) {
					/* current is the only item in the list */
					list->head = current->prev;
				}
				list->tail = current->prev;
			}
			list->size--;
			return SUCCESS_LIST;
		}
		current = current->next;
	}
	
	return ERROR_LIST_ITEM_NOT_FOUND;
}



