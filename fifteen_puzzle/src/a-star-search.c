#include <stdio.h>
#include <stdlib.h>

#include "a-star-search.h"
#include "../../lib/src/hashmap.h"
#include "../../lib/src/hashset.h"
#include "../../lib/src/heappriorityqueue.h"
#include "../../lib/src/linkedlist.h"

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

void reconstruct_path_helper(map came_from, node current, list path) {
  printf("inside reconstruct path helper\n");
  int error = linkedlist_methods.add_first(path, current);
  printf("error while adding current to path: %d\n", error);
  printf("added current to path\n");
  printf("size after adding: %d\n", linkedlist_methods.size(path));
  node parent = (node) hashmap_methods.get(came_from, current);
  if (parent) {
    printf("adding parents\n");
    reconstruct_path_helper(came_from, parent, path);
  }
}

list reconstruct_path(map came_from, node current) {
  printf("inside reconstruct path\n");
  list path = linkedlist_methods.create(NULL);
  if (!path)
    return NULL;
  reconstruct_path_helper(came_from, current, path);
  printf("leaving reconstruct path\n");
  printf("size before leaving: %d\n", linkedlist_methods.size(path));
  return path;
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

  /* set of unevaluated items. This will maintain the same items as the pqueue */
  set open_set = hashset_methods.create(NULL, &node_hash, &node_equal);
  if (!open_set) {
    hashset_methods.free(closed_set);
    heappqueue_methods.free(open_pqueue);
    return NULL;
  }

  /* the map of navigated nodes */
  map came_from = hashmap_methods.create(NULL, &node_hash, &node_equal, -1);
  if (!came_from) {
    hashset_methods.free(closed_set);
    heappqueue_methods.free(open_pqueue);
    hashset_methods.free(open_set);
    return NULL;
  }

  /* put in the start node */
  heappqueue_methods.enqueue(open_pqueue, start);
  hashset_methods.add(open_set, start);

  while (!heappqueue_methods.is_empty(open_pqueue)) {
    node minimum = (node) heappqueue_methods.dequeue(open_pqueue);
    hashset_methods.remove(open_set, minimum);

    printf("------------------------------------------\n");
    printf("minimum:\n");
    node_print(minimum);
    printf("distance so far: %d\n", minimum->distance_so_far);
    printf("heuristic: %d\n", minimum->heuristic);
    printf("total_distance: %d\n", minimum->total_distance);
    printf("\n");

    /* we've reached our goal */    
    printf("calling node_equal\n");
    if (node_equal(minimum, goal) == 1) {
      list solution = reconstruct_path(came_from, goal);
      printf("before returning to solver\n");
      printf("size: %d\n", linkedlist_methods.size(solution));
      return solution;
    }

    printf("past node_equal\n");

    /* otherwise evaluate this node and check its neighbors */
    hashset_methods.add(closed_set, minimum);
    list neighbors = node_get_neighbors(minimum);
    if (!neighbors)
      continue;

    while (!linkedlist_methods.is_empty(neighbors)) {
      node neighbor = (node) linkedlist_methods.remove_first(neighbors);

      if (hashset_methods.contains(closed_set, neighbor))
	continue;
      int tentative_g_score = minimum->distance_so_far 
	+ node_distance(minimum, neighbor);
      int tentative_is_better;
      
      if (!hashset_methods.contains(open_set, neighbor)) {
	neighbor->distance_so_far = tentative_g_score;
	neighbor->heuristic = node_heuristic(neighbor, GOAL);
	neighbor->total_distance = neighbor->distance_so_far + neighbor->heuristic;

	heappqueue_methods.enqueue(open_pqueue, neighbor);
	hashset_methods.add(open_set, neighbor);
	tentative_is_better = 1;
      } else if (tentative_g_score < neighbor->distance_so_far) {
	tentative_is_better = 1;
      } else {
	tentative_is_better = 0;
      }

      if (tentative_is_better) {
	/* parent of neighbor is minimum */
	hashmap_methods.add(came_from, neighbor, minimum);
	neighbor->distance_so_far = tentative_g_score;
	neighbor->heuristic = node_heuristic(neighbor, GOAL);
	neighbor->total_distance = neighbor->distance_so_far + neighbor->heuristic;

	printf("neighbor:\n");
	node_print(neighbor);
	printf("distance so far: %d\n", neighbor->distance_so_far);
	printf("heuristic: %d\n", neighbor->heuristic);
	printf("total_distance: %d\n", neighbor->total_distance);
	printf("\n");
      }
    }

  }
  return NULL;
}




