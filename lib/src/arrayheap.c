#include <stdio.h>
#include <stdlib.h>
#include "arrayheap.h"

/*
 * A heap has an arraylist containing the items and a pointer to a compare
 * function.
 */
typedef struct _arrayheap *_arrayheap;

struct _arrayheap {
  list data;
  heap_compare compare;
};

/*
 * This implementation of the heap will keep the minimum item at the top.
 */
heap _arrayheap_create(heap_compare cmp) {
  if (!cmp)
    return NULL;
  _arrayheap hp = malloc(sizeof(struct _arrayheap));
  if (!hp)
    return NULL;
  hp->data = arraylist_methods.create(NULL);
  if (!hp->data)
    return NULL;
  hp->compare = cmp;
  return (heap) hp;
}

void _arrayheap_free(heap hep) {
  _arrayheap hp = (_arrayheap) hep;
  if (!hp)
    return;
  arraylist_methods.free(hp->data);
  free(hp);
}

void _arrayheap_free_items(heap hep, heap_free_item free_func) {
  _arrayheap hp = (_arrayheap) hep;
  if (!hp)
    return;
  arraylist_methods.free_items(hp->data, (list_free_item) free_func);
  free(hp);
}

int _arrayheap_size(heap hep) {
  _arrayheap hp = (_arrayheap) hep;
  if (!hp)
    return ERROR_HEAP_IS_NULL;
  return arraylist_methods.size(hp->data);
}

int _arrayheap_is_empty(heap hep) {
  _arrayheap hp = (_arrayheap) hep;
  if (!hp)
    return ERROR_HEAP_IS_NULL;
  return _arrayheap_size((heap) hp) == 0; 
}

int _arrayheap_contains(heap hep, void *item) {
  _arrayheap hp = (_arrayheap) hep;
  if (!hp)
    return ERROR_HEAP_IS_NULL;
  if (!item)
    return ERROR_HEAP_ITEM_IS_NULL;
  if (_arrayheap_is_empty((heap) hp))
    return 0;
  return arraylist_methods.contains(hp->data, item);
}

void **_arrayheap_to_array(heap hep) {
  _arrayheap hp = (_arrayheap) hep;
  if (!hp)
    return NULL;
  return arraylist_methods.to_array(hp->data);
}

void *_arrayheap_peek(heap hep) {
  _arrayheap hp = (_arrayheap) hep;
  if (!hp)
    return NULL;
  if (_arrayheap_is_empty((heap) hp))
    return NULL;
  return arraylist_methods.get_first(hp->data);
}

/* Internal. Do not use. 
 * Swaps the pointers at index1 and index2 in hp->data */
void __arrayheap_swap(_arrayheap hp, int index1, int index2) {
  void *temp = arraylist_methods.get(hp->data, index1);
  arraylist_methods.set(hp->data, index1, arraylist_methods.get(hp->data, index2));
  arraylist_methods.set(hp->data, index2, temp);
}

/* Internal. Do not use.
 * Returns the index of the minimum of the items pointed to by the indices */
int __arrayheap_min(_arrayheap hp, int index1, int index2) {
  return (hp->compare(arraylist_methods.get(hp->data, index1), 
                      arraylist_methods.get(hp->data, index2)) < 0)? index1 : index2;
}

int _arrayheap_add(heap hep, void *item) {
  _arrayheap hp = (_arrayheap) hep;
  if (!hp)
    return ERROR_HEAP_IS_NULL;
  if (!item)
    return ERROR_HEAP_ITEM_IS_NULL;
    
  /* add the item to the end of the list */
  if (arraylist_methods.add_last(hp->data, item) != SUCCESS_LIST)
    return ERROR_HEAP_MALLOC_FAIL;
  
  /* A node at position i has parents (i - 1) / 2 (integer division).
   * We swap the child with the parent if the child is less than the parent */
  int child = _arrayheap_size((heap) hp) - 1;
  int parent = (child - 1) / 2;
  while (child > 0 && __arrayheap_min(hp, child, parent) == child) {
    __arrayheap_swap(hp, child, parent);
    child = parent;
    parent = (child - 1) / 2;
  }
  return SUCCESS_HEAP;
}

/* 
 * Removes the min item from the heap and returns a pointer to it. If the 
 * item is not found or if the heap is empty or NULL, this returns NULL.
 */
void *_arrayheap_remove(heap hep) {
  _arrayheap hp = (_arrayheap) hep;
  if (!hp)
    return NULL;
  if (_arrayheap_is_empty((heap) hp))
    return NULL;
    
  /* get the first item */
  void *item = arraylist_methods.get_first(hp->data);
  __arrayheap_swap(hp, 0, _arrayheap_size((heap) hp) - 1);
  arraylist_methods.remove_last(hp->data);
  
  /* A node a position i has children at 2 * i + 1 and 2 * i + 2
   * If the parent is less than its child or children, we swap. If there
   * are multiple children, we swap with the lesser child. */
  int parent = 0;
  int least = 2 * parent + 1;
  while (least < _arrayheap_size((heap) hp)) {
    /* check if there is a right child */
    if (least + 1 < _arrayheap_size((heap) hp))
      least = __arrayheap_min(hp, least, least + 1);
    if (__arrayheap_min(hp, parent, least) == least) {
      __arrayheap_swap(hp, parent, least);
      parent = least;
      least = 2 * parent + 1;
    } else {
      break;
    }
  }
  return item;
}

heap _arrayheap_merge(heap hep1, heap hep2) {
  _arrayheap hp1 = (_arrayheap) hep1;
  _arrayheap hp2 = (_arrayheap) hep2;
  if (!hp1 && !hp2)
    return NULL;
    
  _arrayheap hp3 = (_arrayheap) _arrayheap_create(hp1->compare);
  if (!hp3)
    return NULL;
  
  void **items;
  int error;
  
  /* put all items in hp1 and hp2 into hp3 */
  if (hp1) {
    items = _arrayheap_to_array((heap) hp1);
    if (!items)
      return NULL;
    for (int i = 0; i < _arrayheap_size((heap) hp1); i++) {
      error = _arrayheap_add((heap) hp3, items[i]);
      if (error != SUCCESS_HEAP)
        return NULL;
    }
  }
  
  if (hp2) {
    items = _arrayheap_to_array((heap) hp2);
    for (int i = 0; i < _arrayheap_size((heap) hp2); i++) {
      error = _arrayheap_add((heap) hp3, items[i]);
      if (error != SUCCESS_HEAP)
        return NULL;
    }
  }

  return (heap) hp3;
}

heap_methods arrayheap_methods = {
  .create = &_arrayheap_create,
  .free = &_arrayheap_free,
  .free_items = &_arrayheap_free_items,
  .size = &_arrayheap_size,
  .is_empty = &_arrayheap_is_empty,
  .contains = &_arrayheap_contains,
  .to_array = &_arrayheap_to_array,
  .peek = &_arrayheap_peek,
  .add = &_arrayheap_add,
  .remove = &_arrayheap_remove,
  .merge = &_arrayheap_merge,
};