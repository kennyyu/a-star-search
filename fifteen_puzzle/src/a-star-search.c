#include <stdio.h>
#include <stdlib.h>
#include "board.h"

node GOAL = NULL;
node START = NULL;

void setup_start_and_goal(int dimension, int positions[]) {
  START = malloc(sizeof(struct node));
  if (!START)
    return;
  START->board = malloc(sizeof(int) * dimension * dimension);
  if (!START->board) {
    free(START);
    return;
  }
  START->dimension = dimension;

  /* copy the input into the START board */
  for (int i = 0; i < dimension * dimension; i++)
    START->board[i] = positions[i];

  GOAL = malloc(sizeof(struct node));
  if (!GOAL)
    return;
  GOAL->board = malloc(sizeof(int) * dimension * dimension);
  if (!GOAL->board) {
    free(GOAL);
    return;
  }
  GOAL->dimension = dimension;

  /* create the goal board as 1, 2, ..., dimension * dimension - 1, 0 */
  for (int i = 0; i < dimension * dimension - 1; i++)
    GOAL->board[i] = i + 1;
  GOAL->board[dimension * dimension - 1] = 0;
}
