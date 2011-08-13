#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "../lib/src/list.h"

struct node {
	int dimension;
	int board[];
	int distance_so_far;
	int heuristic;
	int total_distance;
}

enum board_directions {
	UP, 
	DOWN,
	LEFT,
	RIGHT
};

extern node GOAL;
extern node START;

int node_hash(node n) {
	if (!n)
		return -1;
	if (!n->board)
		return -2;
	
	int hash = 0;
	for (int i = 0; i < n->dimension * n->dimension; i++) {
		hash += i * n->board[i];
	}
	return hash;
}

/*
 * Returns:
 *			1 if they are equal
 *			0 if they are not
 * 			-1 if either is NULL
 * 			-2 if their dimensions do not match
 */
int node_equal(node n1, node n2) {
	if (!n1 || !n2)
		return -1;
	if (n1->dimension != n2->dimension)
		return -2;
	if (!n1->board || !n2->board)
		return -1;

	for (int i = 0; i < (n1->dimension) * (n1->dimension); i++) {
		if (n1->board[i] != n2->board[i])
			return 0;
	}
	return 1;
}

/* we use the hamming distance: number of blocks in wrong position */
int node_heuristic(node current, node goal) {
	if (!current || !goal)
		return -1;
	if (current->dimension != goal->dimension)
		return -2;
	if (!current->board || !goal->board)
		return -1;

	int distance = 0;
	for (int i = 0; i < (current->dimension) * (current->dimension); i++) {
		if (current->board[i] != current->dimension[i])
			distance++;
	}
	return distance;
}

node node_create_from_board(int dimension, int board[]) {
	node current = malloc(sizeof(struct node));
	if (!node)
		return NULL;
	current->dimension = dimension;
	current->board = malloc(sizeof(int) * dimension * dimension);
	if (!current->board) {
		free(current);
		return NULL;
	}
	current->distance_so_far = 0;
	current->heuristic = 0;
	current->total_distance = 0;
}

node node_create_goal(int dimension, int board[]) {
	node goal = node_create_from_board(dimension, board);
	if (!goal)
		return NULL;
	goal->distance_so_far = INT_MAX;
	goal->heuristic = 0;
	goal->total_distance = goal->distance_so_far + goal->heuristic;
}

node node_create_start(int dimension, int board[]) {
	node current = node_create_from_board(dimension, board);
	if (!current)
		return NULL;
	current->distance_so_far = 0;
	current->heuristic = node_heuristic(current, GOAL);
	if (current->heuristic < 0) {
		free(current);
		return NULL;
	}
	current->total_distance = current->distance_so_far + current->heuristic;
}

void node_free(node n) {
	if (!n)
		return;
	if (!n->board)
		return;
	free(n->board);
	free(n);
}

node node_create_in_direction(node, board_directions);

list node_get_neighbors(node);

void print_node(node);

#endif