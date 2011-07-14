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

void list_free(list li) {
	if (!li)
		return;
	for (int i = 0; i < li->size; i++)
		free(li->data[i]);
	free(li->data);
	free(li);
}

/* resize the array by doubling it's current array_size. returns NULL if
 * the list is NULL or if malloc fails */
list _list_resize(list li) {
	if (!li)
		return NULL;
	int new_array_size = li->array_size * 2;
	void **new_data = malloc(sizeof(void *) * new_array_size);
	if (!new_data)
		return NULL;
	for (int i = 0; i < li->size; i++)
		new_data[i] = li->data[i];
	free(li->data);
	li->data = new_data;
	li->array_size = new_array_size;
	return li;
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