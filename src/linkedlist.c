#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

/* Internal. Do not use. */
typedef struct _list_node {
	void *data;
	struct _list_node *next;
} _list_node;	

/* we alias linkedlist to be this struct */
struct linkedlist {
	_list_node *head;
	_list_node *tail;
	int size;
};

linkedlist *list_create() {
	linkedlist *list = malloc(sizeof(linkedlist));
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return list;
}

void list_free(linkedlist *list) {
	free(list);
}

int list_size(linkedlist *list) {
	return list->size;
}

int list_is_empty(linkedlist *list) {
	return list_size(list) == 0;
}

void list_add_first(linkedlist *list, void *item) {
	/* make a new node to contain the item */
	_list_node *node = malloc(sizeof(_list_node));
	node->next = NULL;
	node->data = item;

	/* if there are no elements in the list, set head and tail to node
	 * else reset node's next pointer, and set head to node */	
	if (list->head == NULL) {
		list->head = node;
		list->tail = node;
	} else {
		node->next = list->head;	
		list->head = node;
	}

	/* update size */
	list->size++;
}

void list_add_last(linkedlist *list, void *item) {
	/* make a new node to contain the item */
	_list_node *node = malloc(sizeof(_list_node));
	node->next = NULL;
	node->data = item;

	/* if there are no elements in the list, set head and tail to node
	 * else reset tail's next pointer, and set tail to node */	
	if (list->tail == NULL) {
		list->head = node;
		list->tail = node;
	} else {
		list->tail->next = node;	
		list->tail = node;
	}

	/* update size */
	list->size++;
}

int list_contains(linkedlist *list, void *item) {
	_list_node *current = list->head;
	while(!current) {
		if (item == current->data) 
			return 1;
		else
			current = current->next;
	}
	return 0;
}

void *list_remove(linkedlist *list, void *item);
void *list_remove_last(linkedlist *list);
void *list_remove_first(linkedlist *list);