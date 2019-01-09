//
// Created by root on 1/7/19.
//

#ifndef DATA_STRUCTURES_PQ_ESSENTIALS_H
#define DATA_STRUCTURES_PQ_ESSENTIALS_H
    #define left(i) 2*i + 1
    #define right(i) 2*i + 2
    #define parent(i) (i-1)/2
    #define has_left(i, pq) left(i) < pq->heap->size
    #define has_right(i, pq) right(i) < pq->heap->size
#endif //DATA_STRUCTURES_PQ_ESSENTIALS_H
