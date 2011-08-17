#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "a-star-search.h"
#include "options.h"
#include "../../lib/src/linkedlist.h"

int VERBOSE;

/* 
 * usage: solver [--help] [--verbose] [--max <int>] <dim> <pos 1> <pos 2> ... <pos dimension * dimension>
 */
void print_help(int help, char *progname) {
  if (help) {
    printf("usage: %s [--help] [--verbose] [--max <int>] <dim> <pos 1> <pos 2> ... <pos dim * dim>\n", progname);
    printf("\n");
    printf("arguments summary:\n");
    printf("\t--help\t\tDisplays this help text.\n");
    printf("\t--verbose\tDisplays verbose output when solving. This includes a GUI printout and the value of the distance metric.\n");
    printf("\t--max <int>\tMaximum number of moves to step through when solving.\n");
    printf("\t<dim>\t\tDimension of the square board. If the dimension is n, then we have an n x n board.\n");
    printf("\t<pos k>\t\tNumber at position k, where starting from 1, we count left to right, up to down. Put a 0 to mark the empty spot.\n");
  } else {
    printf("Try %s --help for usage\n", progname);
  }
}

int is_positive(char *s) {
  for (int i = 0; s[i]; i++) {
    if (!isdigit(s[i]))
      return 0;
  }
  return 1;
}

void solve(int verbose, int max, int dimension, int positions[]) {
  VERBOSE = verbose;
  if (VERBOSE) {
    printf("verbose: %d\n", verbose);
    printf("max: %d\n", max);
    printf("dimension: %d\n", dimension);
    printf("positions: [");
    for (int i = 0; i < dimension * dimension; i++) {
      printf("%d", positions[i]);
      if (i + 1 < dimension * dimension)
        printf(", ");
    }
    printf("]\n\n");
  }
  setup_start_and_goal(dimension, positions);
  list solution = a_star_search(START, GOAL);

  if (!solution) {
    printf("NO SOLUTION\n");
    return;
  }
  printf("SOLUTION:\n");

  while (!linkedlist_methods.is_empty(solution)) {
    printf("steps left: %d\n\n", linkedlist_methods.size(solution));
    node current = (node) linkedlist_methods.remove_first(solution);
    node_print(current);
  }
  printf("SOLVED\n");
}

/* parse the command line arguments and call solve with the parameters */
int main(int argc, char *argv[]) {
  /* initialize optional arguments to default values */
  int help = 0;
  int verbose = 0;
  int max = 100;
  int dimension = 0;
  
  /* skip argv[0] == program name */
  int i;
  for (i = 1; i < argc; i++) {
    /* check if --help option is passed */
    if (strncmp("--help", argv[i], 7) == 0) {
      help = 1;
      print_help(help, argv[0]);
      return 0;
    }
    
    /* check if --verbose option is passed */
    if (strncmp("--verbose", argv[i], 10) == 0) {
      /* do not allow duplicate --verbose arguments */
      if (verbose) {
        printf("[ERROR] Duplicate '--verbose' arguments\n");
        print_help(help, argv[0]);
        return 1;
      }
      verbose = 1;
      continue;
    }
    
    /* check if --max <int> option is passed */
    if (strncmp("--max", argv[i], 6) == 0) {
      if (i + 1 >= argc) {
        printf("[ERROR] Must specify <int> for '--max <int>'\n");
        print_help(help, argv[0]);
        return 1;
      }
      if (!is_positive(argv[i+1]) || atoi(argv[i+1]) <= 0) {
        printf("[ERROR] Max must be a positive integer for '--max <int>'\n");
        print_help(help, argv[0]);
        return 1;
      }
      max = atoi(argv[i+1]);
      i++;
      continue;
    }
    
    /* make sure dimension is passed in */
    if (is_positive(argv[i]) && atoi(argv[i]) > 0) {
      dimension = atoi(argv[i]);
      i++;
      break;
    }
  }

  /* ERROR if no dimension passed */
  if (!dimension) {
    printf("[ERROR] Must specify dimension.\n");
    print_help(help, argv[0]);
    return 1;
  }
  
  /* verify if dimension * dimension positions are passed in */
  if ( (argc - i) != (dimension * dimension) ) {
    printf("[ERROR] Must specify dimension * dimension positions\n");
    print_help(help, argv[0]);
    return 1;
  }
  
  /* place the positions into an array, makes sure all numbers are in proper range */
  int positions[dimension * dimension];
  for (; i < argc; i++) {
    if (!is_positive(argv[i])) {
      printf("[ERROR] Position cannot contain non-numeric characters\n");
      print_help(help, argv[0]);
      return 1;
    }
    int temp = atoi(argv[i]);
    if (temp < 0 || temp >= dimension * dimension) {
      printf("[ERROR] Position must be between 0 <= number <= dimension * dimension - 1\n");
      print_help(help, argv[0]);
      return 1;
    }
    positions[(dimension * dimension) - (argc - i)] = temp;
  }
  
  /* make sure no duplicates */
  int sum = 0;
  for (i = 0; i < dimension * dimension; i++) {
    sum += positions[i];
  }
  if (sum != ((dimension * dimension - 1) * (dimension * dimension) / 2)) {
    printf("[ERROR] Positions cannot contain duplicates\n");
    print_help(help, argv[0]);
    return 1;
  }
  
  /* call the solver using the parameters */
  solve(verbose, max, dimension, positions);
  return 0;
}
