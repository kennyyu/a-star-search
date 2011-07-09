#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdio.h>
#include <stdlib.h>


/* need to also add heap library, a star search library */
typedef int bool;

typedef struct pqueue_node {
	int val;
} pqueue_node;

typedef struct pqueue {
	struct pqueue *head;
} pqueue;

/* might be better to pass a pointer to a compare function */
int compare(void *node1, void *node2);
void enqueue(pqueue *pq, void *node);
void *dequeue(pqueue *pq);
int size(pqueue *pq);
bool contains(pqueue *pq);
bool is_empty(pqueue *pq);

#endif