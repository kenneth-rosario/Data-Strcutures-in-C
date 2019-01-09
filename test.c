#include <stdio.h>
#include "vector.h"
#include "trivial-priority-queue.h"
#include "adaptable-priority-queue.h"
//
// Created by root on 1/7/19.
//
int numcmp(void *n1, void *n2){
    return *((int *)n1) - *((int *)n2);
}

void vector_test(){
    VECTOR vec;
    vector_init(&vec);
    int a[] = {57, 88, 10, 22, 55, 66, 88};
    int n = sizeof(a)/sizeof(a[0]);
    for(int i = 0; i < n; i++ ) {
        vector_append(a + i, (&vec), sizeof(int));
    }
    vector_show_int(&vec);
    vector_swap(0, 6, &vec);
    vector_swap(1, 5, &vec);
    int  b= 2;
    vector_add(&b, 2, &vec, sizeof(b));
    vector_add(&b, 0, &vec, sizeof(b));
    vector_remove(5, &vec);
    vector_show_int(&vec);
    vector_set(&b, 5, &vec, sizeof(b));
    b = 6;
    vector_show_int(&vec);
    printf("%d", numcmp(vector_get(0, &vec), vector_get(1, &vec)));
    vector_destroy(&vec);
}

void trivial_test_pq2(){
    PQ pq;
    int b;
    make_pq(numcmp, &pq);
    int a[] = {57, 88, 10, 22, 55, 66, 88};
    int n = sizeof(a)/sizeof(a[0]);
    for(int i = 0; i < n; i++){
        insert(a + i, &pq, sizeof(a[0]));
    }
    for(int i = 0; i < n; i++){
        dequeue(&pq, &b, sizeof(a[0]));
        a[i] = b;
    }
    vector_show_int(pq.heap);
    destroy_pq(&pq);
}

void trivial_test_pq(){
    PQ pq;
    int a[] = {1, 2, 3,6,7,8,9};
}

void print_int_apq(APQ *apq){
    heap_entry *k;
    for(int i = 0 ; i < apq.heap->size; ++i){
        k = vector_get(i, apq.heap);
        printf("%d, ", *(get_entry_data(int *, k)));
    }
    printf("\n");
}

void adaptable_test_pq(){
    APQ apq;
    heap_entry a;
    int b;
    make_apq(&apq, numcmp);
    b = 1;
    heap_entry *h1 = apq_insert(&b, &apq, sizeof(int));
    b = -2;
    heap_entry *h2 = apq_insert(&b, &apq, sizeof(int));
    b = 5;
    heap_entry *h3 = apq_insert(&b, &apq, sizeof(int));
    b = 0;
    heap_entry *h4 = apq_insert(&b, &apq, sizeof(int));
    b = 100;
    apq_replace(h2, &b, sizeof(int));
    apq_remove_entry(h1);
    int h5;
    remove_min(&apq, &h5, sizeof(int));
    heap_entry *k;
    for(int i = 0 ; i < apq.heap->size; ++i){
       k = vector_get(i, apq.heap);
       printf("%d, ", *(get_entry_data(int *, k)));
    }
    printf("\n");
    destroy_apq(&apq);
}


void adaptable_test_pq2(){
    APQ apq;
    int b;
    make_apq(&apq, numcmp);
    int a[] = {57, 88, 10, 22, 55, 66, 88};
    int n = sizeof(a)/sizeof(a[0]);
    for(int i = 0; i < n; i++){
        apq_insert(a + i, &apq, sizeof(a[0]));
    }
    print_int_apq(&apq);
    for(int i = 0; i < n; i++){
        remove_min(&apq, &b, sizeof(a[0]));
        a[i] = b;
    }
    destroy_apq(&apq);
}

int main(void){
   adaptable_test_pq2();
   exit(0);
}
