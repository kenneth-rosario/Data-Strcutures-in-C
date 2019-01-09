//
// Created by root on 1/7/19.
//

#include <stddef.h>
#include "vector.h"
#ifndef CHAPTER6_ADAPTABLE_PRIORITY_QUEUE_H
#define CHAPTER6_ADAPTABLE_PRIORITY_QUEUE_H
    typedef struct APQ{
        VECTOR* heap;
        int (*cmp)(void *, void *);
    } APQ;

    typedef struct heap_entry{
        void *data;
        int index;
        APQ *owner;
    } heap_entry;

    #define get_entry_data(type, heap_entry) (type)(heap_entry->data)
    #define apq_peek(target) vector_get(0, target->heap)

    void make_apq(APQ *target, int (*cmp)(void *, void *));
    void destroy_apq(APQ *target);
    heap_entry *apq_insert(void *data, APQ *target, size_t data_size);
    void remove_min(APQ *target, void *to_store, size_t data_size);
    void apq_replace(heap_entry *target, void *with, size_t data_size);
    void apq_remove_entry(heap_entry *target);
#endif //CHAPTER6_ADAPTABLE_PRIORITY_QUEUE_H
