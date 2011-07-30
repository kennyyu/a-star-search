#ifndef _MAP_H
#define _MAP_H

/* 
 * Alias map to be a pointer to a struct map. We never instantiate a map, we
 * only cast pointers into map.
 */
typedef struct map *map;
struct map { };

/*
 * The to_array function will return an array of structs containing (key,value)
 * pairs.
 */
typedef struct map_node *map_node;
struct map_node {
	void *key;
	void *value;
};

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
typedef enum map_error_numbers map_error_numbers;
enum map_error_numbers {
	SUCCESS_MAP = 1,
	ERROR_MAP_IS_NULL = -1,
	ERROR_MAP_IS_EMPTY = -2,
	ERROR_MAP_ITEM_NOT_FOUND = -3,
	ERROR_MAP_ITEM_IS_NULL = -4,
	ERROR_MAP_MALLOC_FAIL = -5
};

/*
 * This struct contains pointers to operations on maps.
 */
typedef struct map_methods map_methods;
struct map_methods {
	/* 
	 * Initialize a map and returns a pointer to the map. If there is not
	 * enough memory, this returns NULL. If creating a treemap, only map_compare
	 * will be set and the other two will be NULL. If creating a hashmap, 
	 * map_compare will be NULL and the other two will be set.
	 */
	map (*create)(map_compare, map_hash, map_equal);

	/* 
	 * Frees the memory held by the map.
	 */
	void (*free)(map);

	/* 
	 * Returns the number of keys in the map. If the map is NULL, this returns 
	 * ERROR_MAP_IS_NULL.
	 */
	int (*size)(map);

	/* 
	 * Returns 1 if the map has no keys, otherwise returns 0. If the map is NULL,
	 * this returns ERROR_MAP_IS_NULL.
	 */
	int (*is_empty)(map);

	/* 
	 * Returns 1 if the key is in the map, otherwise returns 0. If the map is
	 * NULL, this returns ERROR_MAP_IS_NULL. If the key is NULL, this returns
	 * ERROR_MAP_ITEM_IS_NULL.
	 */
	int (*contains)(map, void *);

	/*
	 * Returns an array of pointers to the keys in the map. The number of keys 
	 * will be the size of the array. If the map is NULL, this returns NULL. If 
	 * the number of keys is 0, this returns NULL. If malloc fails, this also 
	 * returns NULL.
	 *
	 * WARNING: Do not change the values of the keys.
	 */
	void **(*keys_to_array)(map);

	/*
	 * Returns a pointer to an array of structs containing (key,value) pairs.
	 * The key and value fields will reference the actual values in the map.
	 * The number of keys will be the size of the array. If the map is NULL,
	 * this returns NULL. If the number of keys is 0, this returns NULL. If
	 * malloc fails, this also returns NULL.
	 */
	map_node *(*to_array)(map);

	/* 
	 * Adds the key, value pair to the map. If successful, this returns 
	 * SUCCESS_MAP. If the map is NULL, this returns ERROR_MAP_IS_NULL. If either
	 * the key or value is NULL, this returns ERROR_ITEM_IS_NULL. If the key
	 * is already in the map, the old value will be clobbered.
	 */
	int (*add)(map, void *, void *);

	/*
	 * Gets the value associated with this key. If the map is NULL, this returns
	 * NULL. If the key is NULL, this also returns NULL.
	 */
	void *(*get)(map, void *);

	/* 
	 * Removes the key from the map and returns the associated value. If the
	 * the map is NULL, the map is empty, the key is NULL, or the key is not
	 * found, this returns NULL 
	 */
	void *(*remove)(map, void *);
	
	/*
	 * Removes a random element from the map and returns it as a map_node pointer.
	 * For treemaps, this will return elements in order by key. For hashmaps, 
	 * this will return in a random order. If the map is NULL, is empty, or malloc 
	 * fails, this returns NULL.
	 */
	map_node (*remove_random)(map);
};

#endif