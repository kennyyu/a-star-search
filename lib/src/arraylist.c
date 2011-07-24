#include <stdio.h>
#include <stdlib.h>
#include "arraylist.h"

/* We define the initial array size constant. Whenever we need to add more items
 * to the list than the current size of the array, we double the size and copy
 * the items over. */
int _INIT_ARRAY_SIZE = 8;

/* we alias list to be a pointer to this struct */
typedef struct arraylist *arraylist;

struct arraylist {
	int size;
	int array_size;
	void **data;
};

list _arraylist_create() {
	arraylist li = malloc(sizeof(struct arraylist));
	/* if malloc returned NULL, also return NULL */
	if (!li)
		return NULL;
	li->size = 0;
	li->array_size = _INIT_ARRAY_SIZE;
	li->data = malloc(sizeof(void *) * li->array_size);
	if (!li->data)
		return NULL;
	return (list) li;
}

/* this does not free the items */
void _arraylist_free(list lis) {
	arraylist li = (arraylist) lis;
	if (!li)
		return;
	free(li->data);
	free(li);
}

/* resize the array by doubling it's current array_size. returns 
 * ERROR_LIST_MALLOC_FAIL if malloc fails, or returns ERROR_LIST_IS_NULL if
 * the list is NULL. On success, return SUCCESS_LIST */
int __arraylist_resize(arraylist li) {
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

int _arraylist_size(list lis) {
	arraylist li = (arraylist) lis;
	if (!li)
		return ERROR_LIST_IS_NULL;
 	return li->size;
}

int _arraylist_is_empty(list lis) {
	arraylist li = (arraylist) lis;
	if (!li)
		return ERROR_LIST_IS_NULL;
	return _arraylist_size((list) li) == 0;
}

int _arraylist_contains(list lis, void *item) {
	arraylist li = (arraylist) lis;
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
 
void *_arraylist_get_first(list lis) {
	arraylist li = (arraylist) lis;
	if (!li)
		return NULL;
	if (!li->size)
		return NULL;
	return li->data[0];
}

void *_arraylist_get_last(list lis) {
	arraylist li = (arraylist) lis;
	if (!li)
		return NULL;
	if (!li->size)
		return NULL;
	return li->data[li->size - 1];
}

void *_arraylist_get(list lis, int index) {
	arraylist li = (arraylist) lis;
	if (!li)
		return NULL;
	if (!li->size)
		return NULL;
	if (index < 0 || index >= li->size)
		return NULL;
	return li->data[index];
}

void **_arraylist_to_array(list lis) {
	arraylist li = (arraylist) lis;
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

int _arraylist_add_first(list lis, void *item) {
	arraylist li = (arraylist) lis;
	if (!li)
		return ERROR_LIST_IS_NULL;
	if (!item)
		return ERROR_LIST_ITEM_IS_NULL;
		
	/* resize array if the array is full */
	if (li->size == li->array_size) {
		int error = __arraylist_resize(li);
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

int _arraylist_add_last(list lis, void *item) {
	arraylist li = (arraylist) lis;
	if (!li)
		return ERROR_LIST_IS_NULL;
	if (!item)
		return ERROR_LIST_ITEM_IS_NULL;
		
	/* resize array if the array is full */
	if (li->size == li->array_size) {
		int error = __arraylist_resize(li);
		if (error != SUCCESS_LIST)
			return ERROR_LIST_MALLOC_FAIL;
	}
	li->data[li->size] = item;
	li->size++;
	return SUCCESS_LIST;
}

int _arraylist_set(list lis, int index, void *item) {
	arraylist li = (arraylist) lis;
	if (!li)
		return ERROR_LIST_IS_NULL;
	if (!item)
		return ERROR_LIST_ITEM_IS_NULL;
	if (index < 0 || index >= li->size)
		return ERROR_LIST_OUT_OF_BOUNDS;
	
	li->data[index] = item;
	return SUCCESS_LIST;
}

int _arraylist_remove(list lis, void *item) {
	arraylist li = (arraylist) lis;
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

void *_arraylist_remove_first(list lis) {
	arraylist li = (arraylist) lis;
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

void *_arraylist_remove_last(list lis) {
	arraylist li = (arraylist) lis;
	if (!li)
		return NULL;
	if (!li->size)
		return NULL;
	
	void *item = li->data[li->size - 1];
	li->data[li->size - 1] = NULL;
	li->size--;
	return item;
}

list_methods arraylist_methods = {
	.create = &_arraylist_create,
	.free = &_arraylist_free,
	.size = &_arraylist_size,
	.is_empty = &_arraylist_is_empty,
	.contains = &_arraylist_contains,
	.get_first = &_arraylist_get_first,
	.get_last = &_arraylist_get_last,
	.get = &_arraylist_get,
	.to_array = &_arraylist_to_array,
	.add_first = &_arraylist_add_first,
	.add_last = &_arraylist_add_last,
	.set = &_arraylist_set,
	.remove = &_arraylist_remove,
	.remove_first = &_arraylist_remove_first,
	.remove_last = &_arraylist_remove_last,
};