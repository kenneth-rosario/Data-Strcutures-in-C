//
// Created by root on 1/7/19.
//

#include <stdlib.h>
#include <memory.h>
#include "adaptable-priority-queue.h"
#include "pq_essentials.h"

/*
 * Adaptable implementation of a priority queue using vector abstraction for dynamic array
*/

int compare(int i, int j,APQ *apq){
    heap_entry *h1 = vector_get(i, apq->heap);
    heap_entry *h2 = vector_get(j, apq->heap);
    return apq->cmp(h1->data, h2->data);
}

void make_apq(APQ *target, int (*cmp)(void *, void *)){
    target->heap = (VECTOR *)malloc(sizeof(VECTOR));
    vector_init(target->heap);
    target->cmp = cmp;
};

void destroy_apq(APQ *target){
    heap_entry *h1;
    while(target->heap->size != 0){
        h1 = vector_get(0, target->heap);
        apq_remove_entry(h1);
    }
    vector_destroy(target->heap);
    free(target->heap);
}

void apq_upheap(heap_entry *target, APQ *apq){
    if(target->owner != apq) exit(-1);
    while(target->index > 0){
        if(compare(target->index, parent(target->index), apq) > 0) return;
        heap_entry *h1 = vector_get(parent(target->index), apq->heap);
        h1->index = target->index;
        target->index = parent(target->index);
        vector_swap(h1->index, target->index, apq->heap);
    }
}

void apq_downheap(heap_entry *target, APQ *apq){
    if(target->owner != apq) exit(-1);
    while(has_left(target->index, apq)){
        int smallest = left(target->index);
        if(has_right(target->index, apq)){
            if(compare(smallest, right(target->index), apq) > 0)
                smallest = right(target->index);
        }
        if(compare(smallest, target->index, apq) > 0) return;
        heap_entry *h1 = vector_get(smallest, apq->heap);
        target->index = h1->index;
        h1->index = parent(target->index);
        vector_swap(target->index, h1->index, apq->heap);
    }
}

heap_entry *apq_insert(void *data, APQ *target, size_t data_size){
    heap_entry *hp = (heap_entry *)malloc(sizeof(heap_entry *));
    vector_append(&hp, target->heap, data_size);
    heap_entry *h1 = vector_get(target->heap->size - 1, target->heap);
    h1->owner = target;
    h1->index = target->heap->size - 1;
    h1->data = malloc(sizeof(data_size));
    memcpy(h1->data, data, data_size);
    apq_upheap(h1, target);
    free(hp);
    return h1;
};

void remove_min(APQ *target, void *to_store, size_t data_size){
    heap_entry *h1 = vector_get(0, target->heap);
    memcpy(to_store, h1->data, data_size);
    vector_swap(0, target->heap->size - 1, target->heap);
    heap_entry *h2 = vector_get(0, target->heap);
    h2->index = 0;
    h1->index = -1;
    vector_remove_last(target->heap);
    if(target->heap->size <= 0) return;
    h1 = vector_get(0, target->heap);
    apq_downheap(h1, target);
};

void apq_replace(heap_entry *target, void *with, size_t data_size){
    memcpy(target->data, with, data_size);
    if(parent(target->index) >= 0 && compare(target->index, parent(target->index), target->owner) < 0 ){
        apq_upheap(target, target->owner);
    }else{
        apq_downheap(target, target->owner);
    }
};

void apq_remove_entry(heap_entry *target){
    int temp = target->index;
    vector_swap(target->index, target->owner->heap->size -1, target->owner->heap);
    heap_entry *h1 = vector_get(temp, target->owner->heap);
    h1->index = temp;
    free(target->data);// cleaning the memory allocated in the memory heap when inserting
    target->data = NULL;
    target->index = -1;
    vector_remove_last(target->owner->heap);
    if(target->owner->heap->size <= 0) return;
    if(parent(h1->index) >= 0 && compare(h1->index, parent(h1->index), h1->owner) < 0 ){
        apq_upheap(h1, h1->owner);
    }else {
        apq_downheap(h1, h1->owner);
    }
}





