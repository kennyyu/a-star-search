#ifndef _TREEMAP_H
#define _TREEMAP_H

#include "map.h"

/* 
 * C does not provide support for allocating functions at runtime (lambdas).
 * Thus, to transform a set compare function into a map compare function,
 * we use a macro to override the behavior of cmp in treeset to compare
 * the two parameters' key fields.
 */
#define cmp(node1, node2) cmp(node1->key, node2->key)

#include "treeset.h"

extern map_methods treemap_methods;

#endif