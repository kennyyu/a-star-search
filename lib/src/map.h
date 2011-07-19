#ifndef _MAP_H
#define _MAP_H

/* 
 * Alias map to be a pointer to a struct map.
 */
typedef struct map *map;

/*
 * Alias map_compare to be a function pointer type that takes two pointers 
 * to items and compares them. Returns + if the first item > second item, 0 if
 * the first item = second item, - if the first item < second item. This will
 * only be used for treemap.
 */
typedef int (*map_compare) (void *, void *);

/*
 * Alias map_hash to be a function pointer type that takes a pointer to an item 
 * and returns the item's hash value. This will only be used hashmap.
 */
typedef int (*map_hash) (void *);

/*
 * Alias map_equal to be a function pointer type that takes two pointers to items
 * and compares them. Return 1 if they are equal, 0 otherwise. This will only be
 * used for hashmap.
 */
typedef int (*map_equal) (void *, void *);

/*
 * Enumeration of error and success return values for functions that return an
 * int. 
 */
typedef enum map_error_numbers 
{
	SUCCESS_MAP = 1,
	ERROR_MAP_IS_NULL = -1,
	ERROR_MAP_IS_EMPTY = -2,
	ERROR_MAP_ITEM_NOT_FOUND = -3,
	ERROR_MAP_ITEM_IS_NULL = -4,
	ERROR_MAP_MALLOC_FAIL = -5
} map_error_numbers;

/* 
 * Initialize a map and returns a pointer to the map. If there is not
 * enough memory, this returns NULL. If creating a treemap, only map_compare
 * will be set and the other two will be NULL. If creating a hashmap, 
 * map_compare will be NULL and the other two will be set.
 */
map map_create(map_compare, map_hash, map_equal);

/* 
 * Frees the memory held by the map.
 */
void map_free(map);

/* 
 * Returns the number of keys in the map. If the map is NULL, this returns 
 * ERROR_MAP_IS_NULL.
 */
int map_size(map);

/* 
 * Returns 1 if the map has no keys, otherwise returns 0. If the map is NULL,
 * this returns ERROR_MAP_IS_NULL.
 */
int map_is_empty(map);

/* 
 * Returns 1 if the key is in the map, otherwise returns 0. If the map is
 * NULL, this returns ERROR_MAP_IS_NULL. If the key is NULL, this returns
 * ERROR_MAP_ITEM_IS_NULL.
 */
int map_contains_key(map, void *);

/* 
 * Returns 1 if the value is in the map, otherwise returns 0. If the map is
 * NULL, this returns ERROR_MAP_IS_NULL. If the value is NULL, this returns
 * ERROR_MAP_ITEM_IS_NULL.
 */
int map_contains_value(map, void *);

/*
 * Returns an array of pointers to the keys in the map. The number of keys 
 * will be the size of the array. If the map is NULL, this returns NULL. If 
 * the number of keys is 0, this returns NULL. If malloc fails, this also 
 * returns NULL.
 */
void **map_keys_to_array(map);

/*
 * Returns an array of pointers to the value in the map. The number of
 * distinct values will be the size of the array. If the map is NULL, this 
 * returns NULL. If the number of distinct values is 0, this returns NULL. 
 * If malloc fails, this also returns NULL.
 */
void **map_values_to_array(map);

/* 
 * Adds the key, value pair to the map. If successful, this returns 
 * SUCCESS_MAP. If the map is NULL, this returns ERROR_MAP_IS_NULL. If either
 * the key or value is NULL, this returns ERROR_ITEM_IS_NULL. If the key
 * is already in the map, the old value will be clobbered.
 */
int map_set(map, void *, void *);

/*
 * Gets the value associated with this key. If the map is NULL, this returns
 * NULL. If the key is NULL, this also returns NULL.
 */
void *map_get(map, void *);

/* 
 * Removes the key from the map. If the key is not found, this returns
 * ERROR_MAP_ITEM_NOT_FOUND. If the key is NULL, this returns
 * ERROR_MAP_ITEM_IS_NULL. If the map is empty, this returns
 * ERROR_MAP_IS_EMPTY. If the map is NULL, this returns
 * ERROR_MAP_IS_NULL. On success, returns SUCCESS_MAP.
 */
int map_remove_key(map, void *);

#endif