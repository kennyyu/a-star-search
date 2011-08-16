#ifndef _A_STAR_SEARCH
#define _A_STAR_SEARCH

#include "board.h"
#include "../../lib/src/list.h"
#include "../../lib/src/map.h"

void setup_start_and_goal(int, int[]);
list reconstruct_path(map, node);
list a_star_search(node, node);

#endif
