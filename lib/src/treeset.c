#include <stdio.h>
#include <stdlib.h>
#include "treeset.h"

typedef struct _treeset *_treeset;
struct _treeset { };

set _treeset_create(set_compare cmp, set_hash hash, set_equal eq) {
  if (!cmp)
    return NULL;
  if (hash || eq)
    return NULL;
  map se = treemap_methods.create(cmp, hash, eq);
  if (!se)
    return NULL;
  return (set) se;
}

void _treeset_free(set se) {
  if (!se)
    return;
  treemap_methods.free((map) se);
}

int _treeset_size(set se) {
  if (!se)
    return ERROR_SET_IS_NULL;
  return treemap_methods.size((map) se);
}

int _treeset_is_empty(set se) {
  if (!se)
    return ERROR_SET_IS_NULL;
  return treemap_methods.is_empty((map) se);
}

int _treeset_contains(set se, void *item) {
  if (!se)
    return ERROR_SET_IS_NULL;
  if (!item)
    return ERROR_SET_ITEM_IS_NULL;
  return treemap_methods.contains((map) se, item);
}

void **_treeset_to_array(set se) {
  if (!se)
    return NULL;
  return treemap_methods.keys_to_array((map) se);
}

int _treeset_add(set se, void *item) {
  if (!se)
    return ERROR_SET_IS_NULL;
  if (!item)
    return ERROR_SET_ITEM_IS_NULL;
  int error = treemap_methods.add((map) se, item, NULL);
  if (error == ERROR_MAP_MALLOC_FAIL)
    return ERROR_SET_MALLOC_FAIL;
  return SUCCESS_SET;
}

int _treeset_remove(set se, void *item) {
  if (!se)
    return ERROR_SET_IS_NULL;
  if (!item)
    return ERROR_SET_ITEM_IS_NULL;
  if (!treemap_methods.size((map) se))
    return ERROR_SET_IS_EMPTY;
  if (!treemap_methods.contains((map) se, item))
    return ERROR_SET_ITEM_NOT_FOUND;
  treemap_methods.remove((map) se, item);
  return SUCCESS_SET;
}

/* this will remove the minimum */
void *_treeset_remove_random(set se) {
  if (!se)
    return NULL;
  map_node node = treemap_methods.remove_random((map) se);
  if (!node)
    return NULL;
  return node->key;
}

set_methods treeset_methods = {
  .create = &_treeset_create,
  .free = &_treeset_free,
  .size = &_treeset_size,
  .is_empty = &_treeset_is_empty,
  .contains = &_treeset_contains,
  .to_array = &_treeset_to_array,
  .add = &_treeset_add,
  .remove = &_treeset_remove,
  .remove_random = &_treeset_remove_random,
};