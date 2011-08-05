#include <stdio.h>
#include <stdlib.h>
#include "hashset.h"

typedef struct _hashset *_hashset;
struct _hashset { };

set _hashset_create(set_compare cmp, set_hash hash, set_equal eq) {
  if (!hash)
    return NULL;
  if (!eq)
    return NULL;
  if (cmp)
    return NULL;
  map se = hashmap_methods.create(NULL, hash, eq, -1);
  if (!se)
    return NULL;
  return (set) se;
}

void _hashset_free(set se) {
  if (!se)
    return;
  hashmap_methods.free((map) se);
}

void __hashset_dummy_free_value(void *value) {
  return;
}

void _hashset_free_items(set se, set_free_item free_func) {
  if (!se)
    return;
  free_func = (free_func) ? free_func : &free;
  hashmap_methods.free_items((map) se, (map_free_key) free_func, &__hashset_dummy_free_value);
}

int _hashset_size(set se) {
  if (!se)
    return ERROR_SET_IS_NULL;
  return hashmap_methods.size((map) se);
}

int _hashset_is_empty(set se) {
  if (!se)
    return ERROR_SET_IS_NULL;
  return hashmap_methods.is_empty((map) se);
}

int _hashset_contains(set se, void *item) {
  if (!se)
    return ERROR_SET_IS_NULL;
  if (!item)
    return ERROR_SET_ITEM_IS_NULL;
  return hashmap_methods.contains((map) se, item);
}

void **_hashset_to_array(set se) {
  if (!se)
    return NULL;
  return hashmap_methods.keys_to_array((map) se);
}

int _hashset_add(set se, void *item) {
  if (!se)
    return ERROR_SET_IS_NULL;
  if (!item)
    return ERROR_SET_ITEM_IS_NULL;
  int error = hashmap_methods.add((map) se, item, NULL);
  if (error == ERROR_MAP_MALLOC_FAIL)
    return ERROR_SET_MALLOC_FAIL;
  return SUCCESS_SET;
}

int _hashset_remove(set se, void *item) {
  if (!se)
    return ERROR_SET_IS_NULL;
  if (!item)
    return ERROR_SET_ITEM_IS_NULL;
  if (!hashmap_methods.size((map) se))
    return ERROR_SET_IS_EMPTY;
  if (!hashmap_methods.contains((map) se, item))
    return ERROR_SET_ITEM_NOT_FOUND;
  hashmap_methods.remove((map) se, item);
  return SUCCESS_SET;
}

void *_hashset_remove_random(set se) {
  if (!se)
    return NULL;
  map_node node = hashmap_methods.remove_random((map) se);
  if (!node)
    return NULL;
  return node->key;
}

set_methods hashset_methods = {
  .create = &_hashset_create,
  .free = &_hashset_free,
  .free_items = &_hashset_free_items,
  .size = &_hashset_size,
  .is_empty = &_hashset_is_empty,
  .contains = &_hashset_contains,
  .to_array = &_hashset_to_array,
  .add = &_hashset_add,
  .remove = &_hashset_remove,
  .remove_random = &_hashset_remove_random,
};