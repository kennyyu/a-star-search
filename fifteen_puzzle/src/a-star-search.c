#include <stdio.h>
#include <stdlib.h>

#include "a-star-search.h"
#include "options.h"
#include "../../lib/src/hashmap.h"
#include "../../lib/src/hashset.h"
#include "../../lib/src/heappriorityqueue.h"
#include "../../lib/src/linkedlist.h"

node GOAL = NULL;
node START = NULL;

int __node_compare(void *n1, void *n2) {
  return node_compare((node) n1, (node) n2);
}

int __node_hash(void *n) {
  return node_hash((node) n);
}

int __node_equal(void *n1, void *n2) {
  return node_equal((node) n1, (node) n2);
}

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
  
  if (VERBOSE) {
    printf("START:\n");
    node_print(START);
    printf("\n");
    printf("GOAL:\n");
    node_print(GOAL);
  }
}

void reconstruct_path_helper(map came_from, node current, list path) {
  int error = linkedlist_methods.add_first(path, current);
  if (!error) {
    linkedlist_methods.free(path);
    return;
  }
  node parent = (node) hashmap_methods.get(came_from, current);
  if (parent)
    reconstruct_path_helper(came_from, parent, path);
}

list reconstruct_path(map came_from, node current) {
  list path = linkedlist_methods.create(NULL);
  if (!path)
    return NULL;
  reconstruct_path_helper(came_from, current, path);
  return path;
}

list a_star_search(node start, node goal) {
  /* the set of nodes already evaluated */
  set closed_set = hashset_methods.create(NULL, &__node_hash, &__node_equal);
  if (!closed_set)
    return NULL;
  
  /* priority queue of tentative nodes to be evaluated, compared by total_distance */
  pqueue open_pqueue = heappqueue_methods.create(&__node_compare);
  if (!open_pqueue) {
    hashset_methods.free(closed_set);
    return NULL;
  }

  /* set of unevaluated items. This will maintain the same items as the pqueue */
  set open_set = hashset_methods.create(NULL, &__node_hash, &__node_equal);
  if (!open_set) {
    hashset_methods.free(closed_set);
    heappqueue_methods.free(open_pqueue);
    return NULL;
  }

  /* the map of navigated nodes */
  map came_from = hashmap_methods.create(NULL, &__node_hash, &__node_equal, -1);
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

    if (VERBOSE) {
      printf("------------------------------------------\n");
      printf("minimum:\n");
      node_print(minimum);
      printf("\n");
    }

    /* we've reached our goal */    
    if (node_equal(minimum, goal) == 1) {
      GOAL->distance_so_far = minimum->distance_so_far;
      GOAL->total_distance = GOAL->distance_so_far;
      list solution = reconstruct_path(came_from, goal);
      return solution;
    }

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
        /* add to the open set and priority queue */
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
        /* if the tentative score is better, update scores and parent */
        hashmap_methods.add(came_from, neighbor, minimum);
        neighbor->distance_so_far = tentative_g_score;
        neighbor->heuristic = node_heuristic(neighbor, GOAL);
        neighbor->total_distance = neighbor->distance_so_far + neighbor->heuristic;

        if (VERBOSE) {
          printf("neighbor:\n");
          node_print(neighbor);
          printf("\n");
        }
      }
    }

  }
  return NULL;
}




