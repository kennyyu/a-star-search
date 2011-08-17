#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "a-star-search.h"
#include "options.h"
#include "../../lib/src/linkedlist.h"

int VERBOSE;
heuristic_metric HEURISTIC;

/* 
 * usage: solver [--help] [--verbose] [--heuristic <hamming | manhttan>] <dim> <pos 1> <pos 2> ... <pos dimension * dimension>
 */
void print_help(int help, char *progname) {
  if (help) {
    printf("usage: %s [--help] [--verbose] [--heuristic <hamming | manhttan>] <dim> <pos 1> <pos 2> ... <pos dim * dim>\n", progname);
    printf("\n");
    printf("arguments summary:\n");
    printf("\t--help\t\tDisplays this help text.\n");
    printf("\t--verbose\tDisplays verbose output when solving. This includes a GUI printout and the value of the distance metric.\n");
    printf("\t--heuristic <hamming | manhattan>\tHeuristic metric to use for the A* search. Manhattan is default.\n");
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

void solve(int verbose, heuristic_metric heuristic, int dimension, int positions[]) {
  VERBOSE = verbose;
	HEURISTIC = heuristic;
  if (VERBOSE) {
    printf("verbose: %d\n", verbose);
    printf("heuristic <HAMMING: %d | MANHATTAN: %d>: %d\n", HAMMING, MANHATTAN, HEURISTIC);
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

	if (VERBOSE) {
		printf("SOLUTION:\n");
  	while (!linkedlist_methods.is_empty(solution)) {
			printf("steps left: %d\n\n", linkedlist_methods.size(solution));
    	node current = (node) linkedlist_methods.remove_first(solution);
    	node_print(current);
  	}
  	printf("SOLVED\n");
	} else {
		if (linkedlist_methods.size(solution) == 1)
			return;
			
		node previous = NULL; 
		node current = linkedlist_methods.remove_first(solution);
		while (!linkedlist_methods.is_empty(solution)) {
			previous = current;
			current = linkedlist_methods.remove_first(solution);
			node_print_move(previous, current);
			printf(" ");
		}
		printf("\n");
	}
}

/* parse the command line arguments and call solve with the parameters */
int main(int argc, char *argv[]) {
  /* initialize optional arguments to default values */
  int help = 0;
  int verbose = 0;
	heuristic_metric heuristic = MANHATTAN;
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
    
    /* check if --heuristic <hamming | manhattan> option is passed */
    if (strncmp("--heuristic", argv[i], 6) == 0) {
      if (i + 1 >= argc) {
        printf("[ERROR] Must specify <hamming | manhattan> for '--heuristic'\n");
        print_help(help, argv[0]);
        return 1;
      }
			if (strncmp("hamming", argv[i+1], 8) == 0) {
				heuristic = HAMMING;
				i++;
				continue;
			} else if (strncmp("manhattan", argv[i+1], 10) == 0) {
				heuristic = MANHATTAN;
				i++;
				continue;
			} else {
        printf("[ERROR] Heuristic must be either 'hamming' or 'manhattan'\n");
        print_help(help, argv[0]);
        return 1;				
			}
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
  solve(verbose, heuristic, dimension, positions);
  return 0;
}
