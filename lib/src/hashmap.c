#include <stdio.h>
#include <stdlib.h>
#include "hashset.h"

int _DEFAULT_BUCKET_SIZE = 100;

typedef struct _hashmap *_hashmap;
struct _hashmap {
  int bucket_size;
  list *buckets; /* pointer to an array of pointers to lists */        
  int size;
  map_hash hash;
  map_equal equal;
  list bucket_changes; /* keeps track of insertions/deletions. if no item in bucket, remove and move to next */
};

/* 
 * Initialize a map and returns a pointer to the map. If there is not
 * enough memory, this returns NULL. If creating a treemap, only map_compare
 * will be set and the other two will be NULL. If creating a hashmap, 
 * map_compare will be NULL and the other two will be set.
 */
map _hashmap_create(map_compare cmp, map_hash hash, map_equal eq, int bucket_size) {
  if (!hash || !eq)
    return NULL;
  if (cmp)
    return NULL;
  _hashmap mp = malloc(sizeof(struct _hashmap));
  if (!mp)
    return NULL;    
  
  /* size will default to _default_bucket_size if size == -1 */
  mp->bucket_size = (bucket_size > 0) ? bucket_size : _DEFAULT_BUCKET_SIZE;
  
  /* allocate buckets and NULL out the lists */
  mp->buckets = malloc(sizeof(list) * mp->bucket_size);
  if (!mp->buckets) {
    free(mp);
    return NULL;
  }
  for (int i = 0; i < mp->bucket_size; i++)
    mp->buckets[i] = NULL;
  
  /* set the rest of the fields */
  mp->size = 0;
  mp->hash = hash;
  mp->equal = eq;
  mp->bucket_changes = linkedlist_methods.create(NULL);
  if (!mp->bucket_changes) {
    free(mp->buckets);
    free(mp);
    return NULL;
  }
  return (map) mp;
}

/* 
 * Frees the memory held by the map.
 */
void _hashmap_free(map mapp) {
  _hashmap mp = (_hashmap) mapp;
  if (!mp)
    return;
  linkedlist_methods.free(mp->bucket_changes);
  for (int i = 0; i < mp->bucket_size; i++) {
    if (mp->buckets[i])
      arraylist_methods.free(mp->buckets[i]);
  }
  free(mp->buckets);
  free(mp);
}

void _hashmap_free_items(map mapp, map_free_key free_key, map_free_value free_value) {
  _hashmap mp = (_hashmap) mapp;
  if (!mp)
    return;
    while (!linkedlist_methods.is_empty(mp->bucket_changes)) {
        void *item = linkedlist_methods.remove_first(mp->bucket_changes);
        free(item);
    }
  linkedlist_methods.free(mp->bucket_changes);
  for (int i = 0; i < mp->bucket_size; i++) {
    if (mp->buckets[i]) {
      while (!arraylist_methods.is_empty(mp->buckets[i])) {
        map_node node = (map_node) arraylist_methods.remove_last(mp->buckets[i]);
        free_key(node->key);
        free_value(node->value);
        free(node);
      }
      arraylist_methods.free(mp->buckets[i]);
    }
  }
  free(mp->buckets);
  free(mp);
}

/* 
 * Returns the number of keys in the map. If the map is NULL, this returns 
 * ERROR_MAP_IS_NULL.
 */
int _hashmap_size(map mapp) {
  _hashmap mp = (_hashmap) mapp;
  if (!mp)
    return ERROR_MAP_IS_NULL;
  return mp->size;
}

/* 
 * Returns 1 if the map has no keys, otherwise returns 0. If the map is NULL,
 * this returns ERROR_MAP_IS_NULL.
 */
int _hashmap_is_empty(map mapp) {
  _hashmap mp = (_hashmap) mapp;
  if (!mp)
    return ERROR_MAP_IS_NULL;
  return mp->size == 0;
}

int __hashmap_bucket(_hashmap mp, void *item) {
  return mp->hash(item) % mp->bucket_size;
}

/* 
 * Returns 1 if the key is in the map, otherwise returns 0. If the map is
 * NULL, this returns ERROR_MAP_IS_NULL. If the key is NULL, this returns
 * ERROR_MAP_ITEM_IS_NULL.
 */
int _hashmap_contains(map mapp, void *key) {
  _hashmap mp = (_hashmap) mapp;
  if (!mp)
    return ERROR_MAP_IS_NULL;
  if (!key)
    return ERROR_MAP_ITEM_IS_NULL;
  int bucket = __hashmap_bucket(mp, key);
  list li = mp->buckets[bucket];
  if (!li)
    return 0;
  for (int i = 0; i < arraylist_methods.size(li); i++) {
    if (mp->equal(((map_node) arraylist_methods.get(li, i))->key , key))
      return 1;
  }
  return 0;
}

/*
 * Returns an array of pointers to the keys in the map. The number of keys 
 * will be the size of the array. If the map is NULL, this returns NULL. If 
 * the number of keys is 0, this returns NULL. If malloc fails, this also 
 * returns NULL.
 *
 * WARNING: Do not change the values of the keys.
 */
void **_hashmap_keys_to_array(map mapp) {
  _hashmap mp = (_hashmap) mapp;
  if (!mp)
    return NULL;
  int size = _hashmap_size((map) mp);
  if (!size)
    return NULL;
  void **keys = malloc(sizeof(void *) * size);
  if (!keys)
    return NULL;
  int current_bucket = 0;
  for (int i = 0; i < mp->bucket_size; i++) {
    if (mp->buckets[i]) {
      for (int j = 0; j < arraylist_methods.size(mp->buckets[i]); j++) {
        keys[current_bucket] = ((map_node) arraylist_methods.get(mp->buckets[i], j))->key;
        current_bucket++;
      }
    }
  }
  if (current_bucket != size) {
    free(keys);
    return NULL;
  }
  return keys;
}

/*
 * Returns a pointer to an array of structs containing (key,value) pairs.
 * The key and value fields will reference the actual values in the map.
 * The number of keys will be the size of the array. If the map is NULL,
 * this returns NULL. If the number of keys is 0, this returns NULL. If
 * malloc fails, this also returns NULL.
 */
map_node *_hashmap_to_array(map mapp) {
  _hashmap mp = (_hashmap) mapp;
  if (!mp)
    return NULL;
  int size = _hashmap_size((map) mp);
  if (!size)
    return NULL;
  map_node *nodes = malloc(sizeof(map_node) * size);
  if (!nodes)
    return NULL;
  int current_bucket = 0;
  for (int i = 0; i < mp->bucket_size; i++) {
    if (mp->buckets[i]) {
      for (int j = 0; j < arraylist_methods.size(mp->buckets[i]); j++) {
        nodes[current_bucket] = (map_node) arraylist_methods.get(mp->buckets[i], j);
        current_bucket++;
      }
    }
  }
  if (current_bucket != size) {
    free(nodes);
    return NULL;
  }
  return nodes; 
}

/* 
 * Adds the key, value pair to the map. If successful, this returns 
 * SUCCESS_MAP. If the map is NULL, this returns ERROR_MAP_IS_NULL. If either
 * the key or value is NULL, this returns ERROR_ITEM_IS_NULL. If the key
 * is already in the map, the old value will be clobbered.
 */
int _hashmap_add(map mapp, void *key, void *value) {
  _hashmap mp = (_hashmap) mapp;
  if (!mp)
    return ERROR_MAP_IS_NULL;
  if (!key)
    return ERROR_MAP_ITEM_IS_NULL;
  int bucket = __hashmap_bucket(mp, key);
  list li = mp->buckets[bucket];
  if (!li) {
    /* create a new list with this item, and set the bucket to this list */
    li = arraylist_methods.create(NULL);
    if (!li)
      return ERROR_MAP_MALLOC_FAIL;
    map_node node = malloc(sizeof(struct map_node));
    if (!node)
      return ERROR_MAP_MALLOC_FAIL;
    node->key = key;
    node->value = value;
    int error = arraylist_methods.add_first(li, node);
    if (error != SUCCESS_LIST)
      return ERROR_MAP_MALLOC_FAIL;
    mp->buckets[bucket] = li;
    mp->size++;
    /* add a reference to the list in bucket_changes */
    int *bucket_change = malloc(sizeof(int));
    if (!bucket_change)
        return ERROR_MAP_MALLOC_FAIL;
    *bucket_change = bucket;
    linkedlist_methods.add_first(mp->bucket_changes, bucket_change);
    return SUCCESS_MAP;
  }
  /* otherwise look for the item in the list. if it's in the list, update
   * the key's value */
  for (int i = 0; i < arraylist_methods.size(li); i++) {
    map_node node = (map_node) arraylist_methods.get(li, i);
    if (mp->equal(node->key, key)) {
      node->value = value;
      return SUCCESS_MAP;
    }
  }
  /* otherwise append the item to the list */
  map_node node = malloc(sizeof(struct map_node));
  if (!node)
    return ERROR_MAP_MALLOC_FAIL;
  node->key = key;
  node->value = value;
  int error = arraylist_methods.add_last(li, node);
  if (error != SUCCESS_LIST)
    return ERROR_MAP_MALLOC_FAIL;
  mp->size++;
	linkedlist_methods.add_first(mp->bucket_changes, li);
  return SUCCESS_MAP;
}

/*
 * Gets the value associated with this key. If the map is NULL, this returns
 * NULL. If the key is NULL, this also returns NULL.
 */
void *_hashmap_get(map mapp, void *key) {
  _hashmap mp = (_hashmap) mapp;
  if (!mp)
    return NULL;
  if (!key)
    return NULL;
  int bucket = __hashmap_bucket(mp, key);
  list li = mp->buckets[bucket];
  if (!li)
    return NULL;
  for (int i = 0; i < arraylist_methods.size(li); i++) {
    map_node node = (map_node) arraylist_methods.get(li, i);
    if (mp->equal(node->key, key))
      return node->value;
  }
  return NULL;
}

/* 
 * Removes the key from the map and returns the associated value. If the
 * the map is NULL, the map is empty, the key is NULL, or the key is not
 * found, this returns NULL 
 */
void *_hashmap_remove(map mapp, void *key) {
  _hashmap mp = (_hashmap) mapp;
  if (!mp)
    return NULL;
  if (!key)
    return NULL;
  int bucket = __hashmap_bucket(mp, key);
  list li = mp->buckets[bucket];
  if (!li)
    return NULL;
  for (int i = 0; i < arraylist_methods.size(li); i++) {
    map_node node = (map_node) arraylist_methods.get(li, i);
    if (mp->equal(node->key, key)) {
      int error = arraylist_methods.remove(li, node);
      if (error != SUCCESS_LIST)
        return NULL;
      void *value = node->value;
      free(node);
      if (arraylist_methods.is_empty(li)) {
        arraylist_methods.free(li);
        mp->buckets[bucket] = NULL;
      }
      mp->size--;
      return value;
    }
  }
  return NULL;
}

/*
 * Removes a random element from the map and returns it as a map_node pointer.
 * For treemaps, this will return elements in order by key. For hashmaps, 
 * this will return in a random order. If the map is NULL, is empty, or malloc 
 * fails, this returns NULL.
 */
map_node _hashmap_remove_random(map mapp) {
    _hashmap mp = (_hashmap) mapp;
    if (!mp)
        return NULL;
    if (_hashmap_is_empty((map) mp))
        return NULL;
    while (linkedlist_methods.size(mp->bucket_changes)) {
        /* iterate through all the buckets pointed to by bucket_changes
         * remove a node from the first list. if the list is NULL or there
         * are no elements, remove the bucket from bucket_changes */
        int current = *(int *) linkedlist_methods.get_first(mp->bucket_changes);
        if (!mp->buckets[current]) {
            linkedlist_methods.remove_first(mp->bucket_changes);
            continue;
        }
        if (!arraylist_methods.is_empty(mp->buckets[current])) {
            map_node node = (map_node) arraylist_methods.get_first(mp->buckets[current]);
            if (!node)
                return NULL;
            void *key = node->key;
            void *value = node->value;
            node = malloc(sizeof(struct map_node));
            if (!node)
                return NULL;
            /* remove the key,value pair from the map. if there are no more
             * elements in the current list, remove it from bucket_changes */
            _hashmap_remove((map) mp, key); /* will set empty lists to NULL */
            if (arraylist_methods.is_empty(mp->buckets[current]))
                linkedlist_methods.remove_first(mp->bucket_changes);
            node->key = key;
            node->value = value;
            return node;
        } else {
            mp->buckets[current] = NULL;
            continue;
        }
    }
    return NULL;
}

map_methods hashmap_methods = {
  .create = &_hashmap_create,
  .free = &_hashmap_free,
  .free_items = &_hashmap_free_items,
  .size = &_hashmap_size,
  .is_empty = &_hashmap_is_empty,
  .contains = &_hashmap_contains,
  .keys_to_array = &_hashmap_keys_to_array,
  .to_array = &_hashmap_to_array,
  .add = &_hashmap_add,
  .get = &_hashmap_get,
  .remove = &_hashmap_remove,
  .remove_random = &_hashmap_remove_random,
};
