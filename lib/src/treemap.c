#include <stdio.h>
#include <stdlib.h>
#include "treemap.h"

typedef struct __binarytree_node *__binarytree_node;	
struct __binarytree_node {
	treemap_node data;
	__binarytree_node left;
	__binarytree_node right;
};

typedef struct _treemap *_treemap;
struct _treemap {
	int size;
	map_compare compare;
	__binarytree_node root;
};

map _treemap_create(map_compare cmp, map_hash hash, map_equal eq) {
	if (!cmp)
		return NULL;
	if (hash || eq)
		return NULL;
	_treemap mp = malloc(sizeof(struct _treemap));
	if (!mp)
		return NULL;
	mp->size = 0;
	mp->compare = cmp;
	mp->root = NULL;
	return (map) mp;
}

void __treemap_free_helper(__binarytree_node node) {
	if (!node)
		return;
	__treemap_free_helper(node->left);
	__treemap_free_helper(node->right);
	free(node);
}

void _treemap_free(map mapp) {
	_treemap mp = (_treemap) mapp;
	if (!mp)
		return;
	__treemap_free_helper(mp->root);
	free(mp);
}

int _treemap_size(map mapp) {
	_treemap mp = (_treemap) mapp;
	if (!mp)
		return ERROR_MAP_IS_NULL;
	return mp->size;
}

int _treemap_is_empty(map mapp) {
	_treemap mp = (_treemap) mapp;
	if (!mp)
		return ERROR_MAP_IS_NULL;
	return _treemap_size((map) mp) == 0;
}

int __treemap_contains_helper(map_compare cmp, __binarytree_node node, void *key) {
	if (!node)
		return 0;
	if ((*cmp)(node->data->key, key) == 0)
		return 1;
	return __treemap_contains_helper(cmp, node->left, key) || 
		__treemap_contains_helper(cmp, node->right, key);
}

int _treemap_contains(map mapp, void *key) {
	_treemap mp = (_treemap) mapp;
	if (!mp)
		return ERROR_MAP_IS_NULL;
	if (!key)
		return ERROR_MAP_ITEM_IS_NULL;
	return __treemap_contains_helper(mp->compare, mp->root, key);
}

/* in-order traversal (left, this, right) */
int __treemap_keys_to_array_helper(void **keys, __binarytree_node node, int position) {
	if (!keys)
		return 0;
	if (!node)
		return position;
	int new_position = __treemap_keys_to_array_helper(keys, node->left, position);
	keys[new_position] = node->data->key;
	return __treemap_keys_to_array_helper(keys, node->right, new_position + 1);
}

void **_treemap_keys_to_array(map mapp) {
	_treemap mp = (_treemap) mapp;
	if (!mp)
		return NULL;
	if (!mp->size)
		return NULL;
	void **keys = malloc(sizeof(void *) * mp->size);
	if (!keys)
		return NULL;
	int num_keys_added = __treemap_keys_to_array_helper(keys, mp->root, 0);
	
	/* make sure nothing went wrong while adding items to array */
	if (num_keys_added != mp->size) {
		free(keys);
		return NULL;
	}
	return keys;
}

/* in-order traversal (left, this, right) */
int __treemap_to_array_helper(treemap_node nodes, __binarytree_node node, int position) {
	if (!nodes)
		return 0;
	if (!node)
		return position;
	int new_position = __treemap_to_array_helper(nodes, node->left, position);
	nodes[new_position].key = node->data->key;
        nodes[new_position].value = node->data->value;
	return __treemap_to_array_helper(nodes, node->right, new_position + 1);
}

treemap_node _treemap_to_array(map mapp) {
	_treemap mp = (_treemap) mapp;
	if (!mp)
		return NULL;
	if (!mp->size)
		return NULL;
	treemap_node nodes = malloc(sizeof(struct treemap_node) * mp->size);
	if (!nodes)
		return NULL;
	int num_nodes_added = __treemap_to_array_helper(nodes, mp->root, 0);
	
	/* make sure nothing went wrong while adding items to array */
	if (num_nodes_added != mp->size) {
		free(nodes);
		return NULL;
	}
	return nodes;
}

int _treemap_add(map mapp, void *key, void *value) {
	_treemap mp = (_treemap) mapp;
	if (!mp)
		return ERROR_MAP_IS_NULL;
	if (!key)
		return ERROR_MAP_ITEM_IS_NULL;
        
        /* Check if the root is NULL */
	__binarytree_node current = mp->root;
        if (current == NULL) {
                current = malloc(sizeof(struct __binarytree_node));
		if (!current)
			return ERROR_MAP_MALLOC_FAIL;
		current->data = malloc(sizeof(struct treemap_node));
		if (!current->data) {
                        free(current);
			return ERROR_MAP_MALLOC_FAIL;
		}
                current->data->key = key;
                current->data->value = value;
                mp->root = current;
                return SUCCESS_MAP;
        }
        
        /* descend the tree with tailing pointers */
        __binarytree_node previous = NULL;
	map_compare cmp = mp->compare;
	int comparison;
	while (!current) {
		comparison = (*cmp)(key, current->data->key);
		if (comparison < 0) {
                        previous = current;
			current = current->left;
		}
		else if (comparison > 0) {
                        previous = current;
			current = current->right;
		}
		else {
                        /* key found, update value */
			current->data->value = value;
                        return SUCCESS_MAP;
                }  
	}
        
        /* update previous to point to the new node */
        current = malloc(sizeof(struct __binarytree_node));
        if (!current)
                return ERROR_MAP_MALLOC_FAIL;
        current->data = malloc(sizeof(struct treemap_node));
        if (!current->data) {
                free(current);
                return ERROR_MAP_MALLOC_FAIL;
        }
        current->data->key = key;
        current->data->value = value;
        if (comparison < 0)
                previous->left = current;
        else
                previous->right = current;
        return SUCCESS_MAP;
}

void *_treemap_get(map mapp, void *key) {
	_treemap mp = (_treemap) mapp;
	if (!mp)
		return NULL;
	if (!key)
		return NULL;
	__binarytree_node current = mp->root;
	map_compare cmp = mp->compare;
	int comparison;
	while (!current) {
		comparison = (*cmp)(key, current->data->key);
		if (comparison < 0)
			current = current->left;
		else if (comparison > 0)
			current = current->right;
		else
			return current->data->value;
	}
	return NULL;
}

__binarytree_node __treemap_remove_least(map_compare cmp, __binarytree_node node, treemap_node least) {
        if (!node) {
                return NULL;
                least->key = NULL;
        }
        __binarytree_node previousprevious = NULL;
        __binarytree_node previous = NULL;
        __binarytree_node current = node;
	while (!current) {
                previousprevious = previous;
                previous = current;
                current = current->left;
	}
        /* current is NULL, previous is least */
        least->key = previous->data->key;
        least->value = previous->data->value;
        if (previousprevious == NULL) {
                /* previous is the root of the tree */
                free(previous->data);
                free(previous);
                return node->right;
        } else {
                /* the root of the subtree did not change */
                previousprevious->left = previous->right;
                free(previous->data);
                free(previous);
        	return node;
        }
}

int _treemap_remove(map mapp, void *key) {
	_treemap mp = (_treemap) mapp;
	if (!mp)
		return ERROR_MAP_IS_NULL;
	if (!key)
		return ERROR_MAP_ITEM_IS_NULL;
        
        /* check if map is empty */
	__binarytree_node current = mp->root;
        if (current == NULL)
                return ERROR_MAP_IS_EMPTY;
        
        __binarytree_node previous = NULL;
	map_compare cmp = mp->compare;
	int comparison;
	while (!current) {
		comparison = (*cmp)(key, current->data->key);
		if (comparison < 0) {
                        previous = current;
			current = current->left;
		}
		else if (comparison > 0) {
                        previous = current;
			current = current->right;
		}
		else {
                        /* remove root of the tree */
                        if (current == mp->root) {
                                free(current->data);
                                free(current);
                                mp->root = NULL;
                                return SUCCESS_MAP;
                        }
                        /* remove least item from the right subtree of current
                         * and store the least node in the address of least.
                         * remove_least will return the new root after the removal */
                        treemap_node least = malloc(sizeof(struct treemap_node));
                        least->key = NULL;
                        __binarytree_node new_root = __treemap_remove_least(cmp, current->right, least);
                        if (!new_root && !least->key) {
                                /* there was nothing in the right subtree
                                 * replace current with left subtree */
                                if (previous->left == current)
                                        previous->left = current->left;
                                else
                                        previous->right = current->left;
                                free(current->data);
                                free(current);
                                return SUCCESS_MAP;
                        } else if (new_root && !least->key) {
                                return ERROR_MAP_ITEM_NOT_FOUND;
                        }                        
                        /* set least's right to the remaining right subtree
                         * set least's left to current's left subtree
                         * replace current with least by updating previous*/
                        __binarytree_node new_current = malloc(sizeof(struct treemap_node));
                        if (!new_current)
                                return ERROR_MAP_MALLOC_FAIL;
                        new_current->data = least;
                        new_current->left = current->left;
                        new_current->right = new_root;
                        if (previous->left == current)
                                previous->left = new_current;
                        else
                                previous->right = new_current;
                        free(current->data);
                        free(current);                 
                        return SUCCESS_MAP;
		}
	}
        
        /* item not found */
        return ERROR_MAP_ITEM_NOT_FOUND;
}

map_methods treemap_methods = {
	.create = &_treemap_create,
	.free = &_treemap_free,
	.size = &_treemap_size,
	.is_empty = &_treemap_is_empty,
	.contains = &_treemap_contains,
        .to_array = &_treemap_to_array,
	.keys_to_array = &_treemap_keys_to_array,
	.add = &_treemap_add,
	.get = &_treemap_get,
	.remove = &_treemap_remove,
};