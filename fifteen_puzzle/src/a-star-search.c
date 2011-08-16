#include <stdio.h>
#include <stdlib.h>
#include "board.h"

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
