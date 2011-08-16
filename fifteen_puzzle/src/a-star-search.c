#include <stdio.h>
#include <stdlib.h>
#include "board.h"

#include "../../lib/src/hashmap.h"
#include "../../lib/src/hashset.h"
#include "../../lib/src/heappriorityqueue.h"

node GOAL = NULL;
node START = NULL;

void setup_start_and_goal(int dimension, int positions[]) {
  int *board = malloc(sizeof(int) * dimension * dimension);
  for (int i = 0; i < dimension * dimension - 1; i++)
    board[i] = i + 1;
  board[dimension * dimension - 1] = 0;

  GOAL = node_create_goal(dimension, board);
  free(board);
  if (!GOAL)
    return;

  START = node_create_start(dimension, positions);
  if (!START)
    return;
  
  printf("START:\n");
  node_print(START);
  printf("\n");
  printf("GOAL:\n");
  node_print(GOAL);
}

list reconstruct_path(map came_from, node goal) {
  return NULL;
}

list a_star_search(node start, node goal) {
  /* the set of nodes already evaluated */
  set closed_set = hashset_methods.create(NULL, &node_hash, &node_equal);
  if (!closed_set)
    return NULL;
  
  /* priority queue of tentative nodes to be evaluated, compared by total_distance */
  pqueue open_pqueue = heappqueue_methods.create(&node_compare);
  if (!open_pqueue) {
    hashset_methods.free(closed_set);
    return NULL;
  }

  /* the map of navigated nodes */
  map came_from = hashmap_methods.create(NULL, &node_hash, &node_equal, -1);
  if (!came_from) {
    hashset_methods.free(closed_set);
    heappqueue_methods.free(open_pqueue);
    return NULL;
  }

  /* put in the start node */
  heappqueue_methods.enqueue(open_pqueue, start);

  while (!heappqueue_methods.is_empty(open_pqueue)) {
    node minimum = heappqueue_methods.dequeue(open_pqueue);

    /* we've reached our goal */    
    if (node_equal(minimum, goal))
      return reconstruct_path(came_from, goal);

    /* otherwise evaluate this node and check its neighbors */
    hashset_methods.add(closed_set, minimum);
    list neighbors = node_get_neighbors(minimum);
    if (!neighbors)
      continue;
    while (!linkedlist_methods.is_empty(neighbors)) {
      node neighbor = linkedlist_methods.remove_first(neighbors);
      
    }

  }
  return NULL;
}




