#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "../../lib/src/linkedlist.h"

int node_compare(node n1, node n2) {
  return n1->total_distance - n2->total_distance;
}

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
	        if (n1->board[i] != n2->board[i]) {
		       return 0;
		}
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
		if (current->board[i] != goal->board[i])
			distance++;
	}
	return distance;
}

int node_distance(node n1, node n2) {
  return 1;
}

node node_create_from_board(int dimension, int board[]) {
	node current = malloc(sizeof(struct node));
	if (!current)
		return NULL;
	current->dimension = dimension;
	current->board = malloc(sizeof(int) * dimension * dimension);
	if (!current->board) {
		free(current);
		return NULL;
	}
	for (int i = 0; i < dimension * dimension; i++)
	  current->board[i] = board[i];
	current->distance_so_far = 0;
	current->heuristic = 0;
	current->total_distance = 0;
	return current;
}

node node_create_goal(int dimension, int board[]) {
	node goal = node_create_from_board(dimension, board);
	if (!goal)
		return NULL;
	goal->distance_so_far = INT_MAX;
	goal->heuristic = 0;
	goal->total_distance = goal->distance_so_far + goal->heuristic;
	return goal;
}

node node_create_start(int dimension, int board[]) {
	node start = node_create_from_board(dimension, board);
	if (!start)
		return NULL;
	start->distance_so_far = 0;
	start->heuristic = node_heuristic(start, GOAL);
	if (start->heuristic < 0) {
		free(start);
		return NULL;
	}
	start->total_distance = start->distance_so_far + start->heuristic;
	return start;
}

void node_free(node n) {
	if (!n)
		return;
	if (!n->board)
		return;
	free(n->board);
	free(n);
}

node node_create_in_direction(node n, board_directions direction) {
	if (!n)
		return NULL;
	if (!n->board)
		return NULL;
		
	/* find the location of the empty tile */
	int empty_position = 0;
	for (int i = 0; i < n->dimension * n->dimension; i++) {
		if (n->board[i] == 0)
			empty_position = i;
	}
	int row = empty_position / n->dimension;
	int col = empty_position % n->dimension;
	
	/* see if we can swap in the given direction */
	int swap_position = 0;
	if (direction == UP) {
		if (row == 0)
			return NULL;
		swap_position = (row - 1) * n->dimension + col;
	}
	if (direction == DOWN) {
		if (row == n->dimension - 1)
			return NULL;
		swap_position = (row + 1) * n->dimension + col;
	}
	if (direction == LEFT) {
		if (col == 0)
			return NULL;
		swap_position = row * n->dimension + (col - 1);
	}
	if (direction == RIGHT) {
		if (col == n->dimension - 1)
			return NULL;
		swap_position = row * n->dimension + (col + 1);
	}
	
	/* create a new node with the tiles swapped */
	int *board = malloc(sizeof(int) * n->dimension * n->dimension);
	if (!board)
		return NULL;
	node new_node = malloc(sizeof(struct node));
	if (!new_node) {
		free(board);
		return NULL;
	}
	new_node->dimension = n->dimension;
	new_node->board = board;
	for (int i = 0; i < n->dimension * n->dimension; i++)
		new_node->board[i] = n->board[i];
	new_node->board[empty_position] = n->board[swap_position];
	new_node->board[swap_position] = 0;
	// don't set the distances and heuristic here
	return new_node;
}

list node_get_neighbors(node current) {
	list li = linkedlist_methods.create(NULL);
	if (!li)
		return NULL;
	int directions[4] = {UP, DOWN, LEFT, RIGHT};
	node new_node = NULL;
	for (int i = 0; i < 4; i++) {
		new_node = node_create_in_direction(current, directions[i]);
		if (new_node)
			linkedlist_methods.add_first(li, new_node);
	}
	if (!linkedlist_methods.is_empty(li))
		return li;
	linkedlist_methods.free(li);
	return NULL;
}

void node_print(node n) {
	if (!n)
		return;
	if (!n->board)
		return;
	for (int i = 0; i < n->dimension; i++) {
		for (int j = 0; j < n->dimension; j++) {
		  if (n->board[i * n->dimension + j] == 0)
		    printf("");
		  else
		    printf("%d",n->board[i* n->dimension + j]);
		  if (j + 1 < n->dimension)
		    printf("\t");
		  else
		    printf("\n");
		}
	}
}
