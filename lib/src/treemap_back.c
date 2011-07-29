#include <stdio.h>
#include <stdlib.h>
#include "treemap.h"

typedef struct _treemap *_treemap;
struct _treemap { };

typedef struct __treemap_node *__treemap_node;
struct __treemap_node {
	void *key;
	void *value;
};

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
	set mp = treeset_methods.create(cmp, hash, eq);
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
 * Adds the key, value pair to the map. If successful, this returns 
 * SUCCESS_MAP. If the map is NULL, this returns ERROR_MAP_IS_NULL. If either
 * the key or value is NULL, this returns ERROR_ITEM_IS_NULL. If the key
 * is already in the map, the old value will be clobbered.
 */
int add(map mp, void *key, void *value) {
	if (!mp)
		return ERROR_MAP_IS_NULL;
	if (!key)
		return ERROR_MAP_ITEM_IS_NULL;
	__treemap_node node = (__treemap_node) treeset_methods.get((set) mp, key);
	if (node) {
		/* key is already in the set, just reset value to new value */
		node->value = value;
		return SUCCESS_MAP;
	} else {
		/* we need to add (key,value) to the treeset */
		node = malloc(sizeof(struct __treemap_node));
		if (!node) {
			free(node);
			return ERROR_MAP_MALLOC_FAIL;
		}
		node->key = key;
		node->value = value;
		int error = treeset_methods.add((set) mp, node);
		if (error == ERROR_SET_MALLOC_FAIL) {
			free(node);
			return ERROR_MAP_MALLOC_FAIL;
		}
		return SUCCESS_MAP;
	}
}

/*
 * Gets the value associated with this key. If the map is NULL, this returns
 * NULL. If the key is NULL, this also returns NULL.
 */
void *get(map mp, void *key) {
	if (!mp)
		return NULL;
	if (!key)
		return NULL;
	__treemap_node node = (__treemap_node) treeset_methods.get((set) mp, key);
	if (!node)
		return NULL;
	return node->key;
}

/* 
 * Removes the key from the map. If the key is not found, this returns
 * ERROR_MAP_ITEM_NOT_FOUND. If the key is NULL, this returns
 * ERROR_MAP_ITEM_IS_NULL. If the map is empty, this returns
 * ERROR_MAP_IS_EMPTY. If the map is NULL, this returns
 * ERROR_MAP_IS_NULL. On success, returns SUCCESS_MAP.
 */
int remove(map mp, void *item) {
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






/* adds the item and returns the new root of the tree. Return NULL if malloc fails. */
__binarytree_node __treemap_add_helper(map_compare cmp, __binarytree_node node, void *key, void *value) {
	__binarytree_node new_root;
	
	/* add the item if the current node is NULL */
	if (!node) {
		new_root = malloc(sizeof(struct __binarytree_node));
		if (!new_root)
			return NULL;
		new_root->data = malloc(sizeof(struct treemap_node));
		if (!new_root->data)
			return NULL;
		new_root->data->key = key;
		new_root->data->value = value;
		new_root->left = NULL;
		new_root->right = NULL;
		return new_root;
	}
	
	/* otherwise descend the binary search tree and add it to the appropriate position */
	int comparison = (*cmp)(key, node->data);
	if (comparison < 0) {
		/* add item to left subtree */
		new_root = __treemap_add_helper(cmp, node->left, key, value);
		if (!new_root)
			return NULL;
		node->left = new_root;
	} else if (comparison > 0) {
		/* add item to right subtree */
		new_root = __treemap_add_helper(cmp, node->right, key, value);
		if (!new_root)
			return NULL;
		node->right = new_root;
	}
	
	/* do nothing if the item is already in the tree */
	return node;
}

int _treemap_add(map mapp, void *key, void *value) {
	_treemap mp = (_treemap) mapp;
	if (!mp)
		return ERROR_MAP_IS_NULL;
	if (!key)
		return ERROR_MAP_ITEM_IS_NULL;
	if (_treemap_contains_key((map) mp, key))
		return SUCCESS_MAP;
	
	/* search for appropriate spot to add item, and update the new root */
	__binarytree_node new_root = __treemap_add_helper(mp->compare, mp->root, key, value);
	if (!new_root)
		return ERROR_MAP_MALLOC_FAIL;
	mp->root = new_root;
	mp->size++;
	return SUCCESS_MAP;	
}


/* removes the least item and returns the least item. Returns NULL if node NULL */
/* if direction == 1, then node == prev->right. */
__binarytree_node __treemap_remove_least(map_compare cmp, __binarytree_node prev, __binarytree_node node, int direction) {
	if (!node)
		return NULL;
	/* least item is the root of the original right subtree */
	if (!node->left) {
		__binarytree_node least = node;
		if (direction == 1)
			prev->right = node->right;
		else
			prev->left = node->right;
		node->right = NULL;
		return least;
	}
	/* the least item is at least one level below the root of the right subtree */
	if (!node->left->left) {
		__binarytree_node least = node->left;
		node->left = least->right;
		least->right = NULL;
		return least;
	}
	return __treemap_remove_least(cmp, node, node->left, 0);
}

/* removes the node from the tree and returns the root of the new tree */
__binarytree_node __treemap_remove_helper(map_compare cmp, __binarytree_node node, void *key) {
	if (!node)
		return NULL;
	
	int comparison = (*cmp)(key, node->data);
	if (comparison < 0) {
		/* remove the item from the left subtree */
		node->left = __treemap_remove_helper(cmp, node->left, key);
		return node;
	} else if (comparison > 0) {
		/* remove the item from the right subtree */
		node->right = __treemap_remove_helper(cmp, node->right, key);
		return node;
	} else {
		/* remove least item from the right subtree */
		__binarytree_node least = __treemap_remove_least(cmp, node, node->right, 1);
		if (!least) {
			/* if there are no items in the right subtree, return the left subtree */
			__binarytree_node new_root = node->left;
			free(node);
			return new_root;
		}
		/* otherwise replace the current node with least, and return it */
		least->right = node->right;
		least->left = node->left;
		free(node->data);
		free(node);
		return least;
	}
}

int _treemap_remove(map mapp, void *key) {
	_treemap mp = (_treemap) mapp;
	if (!mp)
		return ERROR_MAP_IS_NULL;
	if (!key)
		return ERROR_MAP_ITEM_IS_NULL;
	if (!_treemap_size((map) mp))
		return ERROR_MAP_IS_EMPTY;
	if (!_treemap_contains_key((map) mp, key))
		return ERROR_MAP_ITEM_NOT_FOUND;
	
	mp->root = __treemap_remove_helper(mp->compare, mp->root, key);
	mp->size--;
	return SUCCESS_MAP;
}
