#include <stdio.h>
#include <stdlib.h>
#include "treeset.h"

typedef struct __treeset_node *__treeset_node;	

struct __treeset_node {
	void *data;
	__treeset_node left;
	__treeset_node right;
};

typedef struct _treeset *_treeset;

struct _treeset {
	int size;
	set_compare compare;
	__treeset_node root;
};

set _treeset_create(set_compare cmp, set_hash hash, set_equal eq) {
	if (!cmp)
		return NULL;
	if (hash || eq)
		return NULL;
	_treeset se = malloc(sizeof(struct _treeset));
	if (!se)
		return NULL;
	se->size = 0;
	se->compare = cmp;
	se->root = NULL;
	return (set) se;
}

void __treeset_free_helper(__treeset_node node) {
	if (!node)
		return;
	__treeset_free_helper(node->left);
	__treeset_free_helper(node->right);
	free(node);
}

void _treeset_free(set sett) {
	_treeset se = (_treeset) sett;
	if (!se)
		return;
	__treeset_free_helper(se->root);
	free(se);
}

int _treeset_size(set sett) {
	_treeset se = (_treeset) sett;
	if (!se)
		return ERROR_SET_IS_NULL;
	return se->size;
}

int _treeset_is_empty(set sett) {
	_treeset se = (_treeset) sett;
	if (!se)
		return ERROR_SET_IS_NULL;
	return _treeset_size((set) se) == 0;
}

int __treeset_contains_helper(set_compare cmp, __treeset_node node, void *item) {
	if (!node)
		return 0;
	if (cmp(node->data, item) == 0)
		return 1;
	return __treeset_contains_helper(cmp, node->left, item) || 
		__treeset_contains_helper(cmp, node->right, item);
}

int _treeset_contains(set sett, void *item) {
	_treeset se = (_treeset) sett;
	if (!se)
		return ERROR_SET_IS_NULL;
	if (!item)
		return ERROR_SET_ITEM_IS_NULL;
	return __treeset_contains_helper(se->compare, se->root, item);
}

/* in-order traversal (left, this, right) */
int __treeset_to_array_helper(void **items, __treeset_node node, int position) {
	if (!items)
		return 0;
	if (!node)
		return position;
	int new_position = __treeset_to_array_helper(items, node->left, position);
	items[new_position] = node->data;
	return __treeset_to_array_helper(items, node->right, new_position + 1);
}

void **_treeset_to_array(set sett) {
	_treeset se = (_treeset) sett;
	if (!se)
		return NULL;
	if (!se->size)
		return NULL;
	void **items = malloc(sizeof(void *) * se->size);
	if (!items)
		return NULL;
	int num_items_added = __treeset_to_array_helper(items, se->root, 0);
	
	/* make sure nothing went wrong while adding items to array */
	if (num_items_added != se->size) {
		free(items);
		return NULL;
	}
	return items;
}

/* adds the item and returns the new root of the tree. Return NULL if malloc fails. */
__treeset_node __treeset_add_helper(set_compare cmp, __treeset_node node, void *item) {
	__treeset_node new_root;
	
	/* add the item if the current node is NULL */
	if (!node) {
		new_root = malloc(sizeof(struct __treeset_node));
		if (!new_root)
			return NULL;
		new_root->data = item;
		new_root->left = NULL;
		new_root->right = NULL;
		return new_root;
	}
	
	/* otherwise descend the binary search tree and add it to the appropriate position */
	int comparison = cmp(item, node->data);
	if (comparison < 0) {
		/* add item to left subtree */
		new_root = __treeset_add_helper(cmp, node->left, item);
		if (!new_root)
			return NULL;
		node->left = new_root;
	} else if (comparison > 0) {
		/* add item to right subtree */
		new_root = __treeset_add_helper(cmp, node->right, item);
		if (!new_root)
			return NULL;
		node->right = new_root;
	}
	
	/* do nothing if the item is already in the tree */
	return node;
}

int _treeset_add(set sett, void *item) {
	_treeset se = (_treeset) sett;
	if (!se)
		return ERROR_SET_IS_NULL;
	if (!item)
		return ERROR_SET_ITEM_IS_NULL;
	
	/* search for appropriate spot to add item, and update the new root */
	__treeset_node new_root = __treeset_add_helper(se->compare, se->root, item);
	if (!new_root)
		return ERROR_SET_MALLOC_FAIL;
	se->root = new_root;
	se->size++;
	return SUCCESS_SET;	
}

/* removes the least item and returns the least item. Returns NULL if node NULL */
/* if direction == 1, then node == prev->right. */
__treeset_node __treeset_remove_least(set_compare cmp, __treeset_node prev, __treeset_node node, int direction) {
	if (!node)
		return NULL;
	/* least item is the root of the original right subtree */
	if (!node->left) {
		__treeset_node least = node;
		if (direction == 1)
			prev->right = node->right;
		else
			prev->left = node->right;
		node->right = NULL;
		return least;
	}
	/* the least item is at least one level below the root of the right subtree */
	if (!node->left->left) {
		__treeset_node least = node->left;
		node->left = least->right;
		least->right = NULL;
		return least;
	}
	return __treeset_remove_least(cmp, node, node->left, 0);
}

/* removes the node from the tree and returns the root of the new tree */
__treeset_node __treeset_remove_helper(set_compare cmp, __treeset_node node, void *item) {
	if (!node)
		return NULL;
	
	int comparison = cmp(item, node->data);
	if (comparison < 0) {
		/* remove the item from the left subtree */
		node->left = __treeset_remove_helper(cmp, node->left, item);
		return node;
	} else if (comparison > 0) {
		/* remove the item from the right subtree */
		node->right = __treeset_remove_helper(cmp, node->right, item);
		return node;
	} else {
		/* remove least item from the right subtree */
		__treeset_node least = __treeset_remove_least(cmp, node, node->right, 1);
		if (!least) {
			/* if there are no items in the right subtree, return the left subtree */
			__treeset_node new_root = node->left;
			free(node);
			return new_root;
		}
		/* otherwise replace the current node with least, and return it */
		least->right = node->right;
		least->left = node->left;
		free(node);
		return least;
	}
}

int _treeset_remove(set sett, void *item) {
	_treeset se = (_treeset) sett;
	if (!se)
		return ERROR_SET_IS_NULL;
	if (!item)
		return ERROR_SET_ITEM_IS_NULL;
	if (!_treeset_size((set) se))
		return ERROR_SET_IS_EMPTY;
	if (!_treeset_contains((set) se, item))
		return ERROR_SET_ITEM_NOT_FOUND;
	
	se->root = __treeset_remove_helper(se->compare, se->root, item);
	se->size--;
	return SUCCESS_SET;
}

/* this will remove the minimum */
void *_treeset_remove_random(set sett) {
	_treeset se = (_treeset) sett;
	if (!se)
		return NULL;
	if (!_treeset_size((set) se))
		return NULL;
	if (!se->root)
		return NULL;
	if (!se->root->left) {
		/* the root is the minimum item */
		__treeset_node least = se->root;
		se->root = se->root->right;
		void *item = least->data;
		free(least);
		se->size--;
		return item;
	} else {
		/* find the least item in the left subtree */
		__treeset_node least = __treeset_remove_least(se->compare, se->root, se->root->left, 0);
		void *item = least->data;
		free(least);
		se->size--;
		return item;
	}
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