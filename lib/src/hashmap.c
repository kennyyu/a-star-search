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
        list least_bucket; /* keeps track of insertions/deletions. if no item in bucket, remove and move to next */
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
    if (!mp->buckets)
        return NULL;
    for (int i = 0; i < mp->bucket_size; i++)
        mp->buckets[i] = NULL;
    
    /* set the rest of the fields */
    mp->size = 0;
    mp->hash = hash;
    mp->equal = eq;
    mp->least_bucket = NULL;
    return (map) mp;
}

/* 
 * Frees the memory held by the map.
 */
void _hashmap_free(map mapp){
    _hashmap mp = (_hashmap) mp;
    if (!mp)
        return;
    arraylist_methods.free(mp->least_bucket);
    for (int i = 0; i < mp->bucket_size; i++)
        arraylist_methods.free(mp->buckets[i]);
    free(mp->buckets);
    free(mp);
}

/* 
 * Returns the number of keys in the map. If the map is NULL, this returns 
 * ERROR_MAP_IS_NULL.
 */
int _hashmap_size(map mapp) {
    _hashmap mp = (_hashmap) mp;
    if (!mp)
        return ERROR_MAP_IS_NULL;
    return mp->size;
}

/* 
 * Returns 1 if the map has no keys, otherwise returns 0. If the map is NULL,
 * this returns ERROR_MAP_IS_NULL.
 */
int _hashmap_is_empty(map mapp) {
    _hashmap mp = (_hashmap) mp;
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
        return SUCCESS_MAP;
    }
    /* otherwise look for the item in the list. if it's in the list, update
     * the key's value */
    for (int i = 0; i < arraylist_methods.size(li); i++) {
        map_node node = (map_node) arraylist_methods.get(li, i);
        if (mp->equal(node->key , key)) {
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
        if (mp->equal(node->key , key))
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
        if (mp->equal(node->key , key)) {
            int error = arraylist_methods.remove(li, node);
            if (error != SUCCESS_LIST)
                return NULL;
            void *value = node->value;
            free(node);
            mp->size--;
            return value;
        }
    }
    return NULL;
}