#ifndef _FIFTEEN_PUZZLE_BOARD
#define _FIFTEEN_PUZZLE_BOARD

#include "../lib/src/list.h"

typedef struct node *node;
struct node {
	int dimension;
	int board[];
	int heuristic;
}

typedef enum board_directions board_directions;
enum board_directions {
	UP, 
	DOWN,
	LEFT,
	RIGHT
};

node node_create(dimension, int board[]);
node node_create_in_direction(node, board_directions);
void node_free(node);

int node_hash(node);
int node_equal(node, node);
list node_get_neighbors(node);

int node_distance_so_far(node);
int node_distance(node, node);
int node_heuristic(node);
int node_total_distance(node);

void print_node(node);

#endif