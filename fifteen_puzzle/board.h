#ifndef _FIFTEEN_PUZZLE_BOARD
#define _FIFTEEN_PUZZLE_BOARD

#include "../lib/src/list.h"

typedef struct node *node;
extern node GOAL;
extern node START;

typedef enum board_directions board_directions;

node node_create_in_direction(node, board_directions);
void node_free(node);

int node_hash(node);
int node_equal(node, node);
list node_get_neighbors(node);

int node_distance_so_far(node);
int node_distance(node, node);
int node_heuristic(node, node);
int node_total_distance(node);

void print_node(node);

#endif