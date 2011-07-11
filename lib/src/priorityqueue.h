#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

typedef struct pqueue pqueue;

void pq_enqueue(pqueue *pq, void *item);
void *pq_dequeue(pqueue *pq);
int pq_size(pqueue *pq);
int pq_contains(pqueue *pq, void *item);
int pq_is_empty(pqueue *pq);

#endif