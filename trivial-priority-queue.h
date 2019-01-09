#include "vector.h"
#include <stdlib.h>
#define peek(pq) vector_get(0, pq->heap)
#ifndef TPQ_H
#define TPQ_H
typedef struct PQ {
    VECTOR *heap;
    int (*cmp)(void *, void *);
} PQ;

void make_pq(int (*cmp)(void *, void *), PQ *pq);
void insert(void *p, PQ *pq, size_t data_size);
void dequeue(PQ *, void *, size_t data_size);
void destroy_pq(PQ *pq);

#endif