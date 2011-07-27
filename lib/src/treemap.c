#include <stdio.h>
#include <stdlib.h>
#include "treemap.h"

typedef struct _treemap *_treemap;
struct _treemap {};

typedef struct __treemap_node *__treemap_node;
struct __treemap_node {
        void *key;
        void *value;
};

/* use macros to change cmp(a,b) to cmp(a->key, b->key) 
 * Or expose in the map_compare interface how to compare two nodes
 * move __treemap_node into map header file
 */
map_compare _map_compare_to_node_compare(map_compare cmp) {
        __treemap_node node1 = (__treemap_node) item1;
        __treemap_node node2 = (__treemap_node) item2;
        return cmp(node1->key, node2->key);
}

/* 
 * Initialize a map and returns a pointer to the map. If there is not
 * enough memory, this returns NULL. If creating a treemap, only map_compare
 * will be set and the other two will be NULL. If creating a hashmap, 
 * map_compare will be NULL and the other two will be set.
 */
map _treemap_create(map_compare cmp, map_hash hash, map_equal eq) {
        if (!cmp)
                return NULL;
        if (hash || eq)
                return NULL;
        map_compare map_cmp = _map_compare_to_node_compare(cmp);
        set mp = treeset_methods.create(map_cmp, hash, eq);
        if (!mp)
                return NULL;
        return (map) mp;
}

/* 
 * Frees the memory held by the map.
 */
void _treemap_free(map mp) {
        if (!mp)
                return;
        treeset_methods.free((set) mp);
}

/* 
 * Returns the number of keys in the map. If the map is NULL, this returns 
 * ERROR_MAP_IS_NULL.
 */
int _treemap_size(map mp) {
        if (!mp)
                return ERROR_MAP_IS_NULL;
        return treeset_methods.size((set) mp);
}

/* 
 * Returns 1 if the map has no keys, otherwise returns 0. If the map is NULL,
 * this returns ERROR_MAP_IS_NULL.
 */
int _treemap_is_empty(map mp) {
        if (!mp)
                return ERROR_MAP_IS_NULL;
        return treeset_methods.is_empty((set) mp);
}

/* 
 * Returns 1 if the key is in the map, otherwise returns 0. If the map is
 * NULL, this returns ERROR_MAP_IS_NULL. If the key is NULL, this returns
 * ERROR_MAP_ITEM_IS_NULL.
 */
int _treemap_contains_key(map mp, void *item) {
        if (!mp)
                return ERROR_MAP_IS_NULL;
        if (!item)
                return ERROR_MAP_ITEM_IS_NULL;
        return treeset_methods.contains((set) mp, item);
}

/* 
 * Removes the key from the map. If the key is not found, this returns
 * ERROR_MAP_ITEM_NOT_FOUND. If the key is NULL, this returns
 * ERROR_MAP_ITEM_IS_NULL. If the map is empty, this returns
 * ERROR_MAP_IS_EMPTY. If the map is NULL, this returns
 * ERROR_MAP_IS_NULL. On success, returns SUCCESS_MAP.
 */
int remove_key(map mp, void *item) {
        if (!mp)
                return ERROR_MAP_IS_NULL;
        if (!item)
                return ERROR_MAP_ITEM_IS_NULL;
        int error = treeset_methods.remove((set) mp, item);
        if (error == ERROR_SET_IS_EMPTY)
                return ERROR_MAP_IS_EMPTY;
        if (error == ERROR_SET_ITEM_NOT_FOUND)
                return ERROR_MAP_ITEM_NOT_FOUND;
        return SUCCESS_MAP;
}