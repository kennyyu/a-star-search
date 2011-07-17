#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* We define the initial array size constant. Whenever we need to add more items
 * to the list than the current size of the array, we double the size and copy
 * the items over. */
int _INIT_ARRAY_SIZE = 8;

/* we alias list to be a pointer to this struct */
struct list {
	int size;
	int array_size;
	void **data;
};

list list_create() {
	list li = malloc(sizeof(struct list));
	/* if malloc returned NULL, also return NULL */
	if (!li)
		return NULL;
	li->size = 0;
	li->array_size = _INIT_ARRAY_SIZE;
	li->data = malloc(sizeof(void *) * li->array_size);
	if (!li->data)
		return NULL;
	return li;
}

/* this does not free the items */
void list_free(list li) {
	if (!li)
		return;
	free(li->data);
	free(li);
}

/* resize the array by doubling it's current array_size. returns 
 * ERROR_LIST_MALLOC_FAIL if malloc fails, or returns ERROR_LIST_IS_NULL if
 * the list is NULL. On success, return SUCCESS_LIST */
int _list_resize(list li) {
	if (!li)
		return ERROR_LIST_IS_NULL;
	int new_array_size = li->array_size * 2;
	void **new_data = malloc(sizeof(void *) * new_array_size);
	if (!new_data)
		return ERROR_LIST_MALLOC_FAIL;
	for (int i = 0; i < li->size; i++)
		new_data[i] = li->data[i];
	free(li->data);
	li->data = new_data;
	li->array_size = new_array_size;
	return SUCCESS_LIST;
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
	
	for (int i = 0; i < li->size; i++) {
		if (li->data[i] == item)
			return 1;
	}
	return 0;
}
 
void *list_get_first(list li) {
	if (!li)
		return NULL;
	if (!li->size)
		return NULL;
	return li->data[0];
}

void *list_get_last(list li) {
	if (!li)
		return NULL;
	if (!li->size)
		return NULL;
	return li->data[li->size - 1];
}

void *list_get(list li, int index) {
	if (!li)
		return NULL;
	if (!li->size)
		return NULL;
	if (index < 0 || index >= li->size)
		return NULL;
	return li->data[index];
}

void **list_to_array(list li) {
	if (!li)
		return NULL;
	if (!li->size)
		return NULL;
	
	void **items = malloc(sizeof(void *) * li->size);
	if (!items)
		return NULL;
	for (int i = 0; i < li->size; i++)
		items[i] = li->data[i];
	return items;
}

int list_add_first(list li, void *item) {
	if (!li)
		return ERROR_LIST_IS_NULL;
	if (!item)
		return ERROR_LIST_ITEM_IS_NULL;
		
	/* resize array if the array is full */
	if (li->size == li->array_size) {
		int error = _list_resize(li);
		if (error != SUCCESS_LIST)
			return ERROR_LIST_MALLOC_FAIL;
	}
	/* shift all items one index over */
	for (int i = li->size - 1; i >= 0; i--) {
		li->data[i+1] = li->data[i];
	}
	li->data[0] = item;
	li->size++;
	return SUCCESS_LIST;
}

int list_add_last(list li, void *item) {
	if (!li)
		return ERROR_LIST_IS_NULL;
	if (!item)
		return ERROR_LIST_ITEM_IS_NULL;
		
	/* resize array if the array is full */
	if (li->size == li->array_size) {
		int error = _list_resize(li);
		if (error != SUCCESS_LIST)
			return ERROR_LIST_MALLOC_FAIL;
	}
	li->data[li->size] = item;
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
	
	li->data[index] = item;
	return SUCCESS_LIST;
}

int list_remove(list li, void *item) {
	if (!li)
		return ERROR_LIST_IS_NULL;
	if (!item)
		return ERROR_LIST_ITEM_IS_NULL;
	if (!li->size)
		return ERROR_LIST_IS_EMPTY;
	
	/* find position of the item in the list */
	int item_index = 0;
	for (int i = 0; i < li->size; i++) {
		if (item == li->data[i]) {
			item_index = i;
			break;
		}
	}
	
	/* shift over all items one index back */
	for (int i = item_index; i < li->size - 1; i++)
		li->data[i] = li->data[i+1];
	li->data[li->size - 1] = NULL;
	li->size--;
	return SUCCESS_LIST;
}

/* 
 * Removes the first item from the list and returns a pointer to it. If the 
 * item is not found or if the list is empty or NULL, this returns NULL.
 */
void *list_remove_first(list li) {
	if (!li)
		return NULL;
	if (!li->size)
		return NULL;
	
	/* shift over all items one index back */
	void *item = li->data[0];
	for (int i = 0; i < li->size - 1; i++)
		li->data[i] = li->data[i+1];
	li->data[li->size - 1] = NULL;
	li->size--;
	return item;
}

/* 
 * Removes the last item from the list and returns a pointer to it. If the 
 * item is not found or if the list is empty or NULL, this returns NULL.
 */
void *list_remove_last(list li) {
	if (!li)
		return NULL;
	if (!li->size)
		return NULL;
	
	void *item = li->data[li->size - 1];
	li->data[li->size - 1] = NULL;
	li->size--;
	return item;
}