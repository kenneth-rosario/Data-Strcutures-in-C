#include <memory.h>
#include "trivial-priority-queue.h"
#include "pq_essentials.h"
#define compare(i, j ,pq) pq->cmp(vector_get(i, pq->heap), vector_get(j, pq->heap))
/*
 * Elements in PQ must be pointers to the desired data
 * Trivial Implementation where only the retrieval and removal of the min is necessary
 * Using the vector abstraction as the dynamic array
 */

// Creates priority queue
void make_pq(int (*cmp)(void *, void *), PQ *ptr){
    VECTOR *vec = (VECTOR *)malloc(sizeof(VECTOR));
    vector_init(vec);
    ptr->heap = vec;
    ptr->cmp = cmp;
}

// No need to free pq because it was not created with malloc
void destroy_pq(PQ *pq){
    vector_destroy(pq->heap);
    free(pq->heap);
}

static int downheap(int i, PQ *pq){
    int smallest;
    while(has_left(i, pq)){
        smallest = left(i);
        if(has_right(i, pq)){
            if(compare(smallest, right(i), pq) > 0)
            smallest = right(i);
        }
        if(compare( smallest , i , pq) > 0 ){
            return i;
        }
        vector_swap(i, smallest, pq->heap);
        i = smallest;
    }
    return i;
}

static int upheap(int i, PQ *pq){
    while(i > 0){
        if(pq->cmp(vector_get(i, pq->heap), vector_get((i-1)/2, pq->heap)) > 0) return i;
        vector_swap(i, parent(i), pq->heap);
        i = parent(i);
    }
    return i;
}

// Vector or heap copies the value stored in p and adds it to the vector/heap
void insert(void *p, PQ *pq, size_t data_size){
    vector_append(p , (pq->heap), data_size);
    upheap(pq->heap->size - 1, pq);
}

// Copies the content of the min in to_store and removes
void dequeue(PQ *pq, void *to_store, size_t data_size){
    // Copys the contents of the currently min in order for the data to be independent of any reference
    memcpy(to_store, peek(pq), data_size);
    vector_swap(0, pq->heap->size-1, pq->heap);
    // removes the last which is the min and frees its data not affecting the to_store parameter
    vector_remove_last(pq->heap);
    downheap(0, pq);
}


