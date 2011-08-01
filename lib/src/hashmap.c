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
    linkedlist_methods.free(mp->least_bucket);
    for (int i = 0; i < mp->bucket_size; i++)
        linkedlist_methods.free(mp->buckets[i]);
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