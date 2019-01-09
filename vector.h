#ifndef VECTOR_H
#define  VECTOR_H
typedef struct VECTOR{

    int size;
    int space;
    void **arr;

} VECTOR;
#define vector_append(p, vec, data_size) vector_add(p, vec->size, vec, data_size)
#define vector_remove_last(vec) vector_remove(vec->size - 1, vec)
void vector_init(VECTOR *vec);
void vector_destroy(VECTOR *vec);
void *vector_get(int i, VECTOR *vec);
void vector_add(void *p, int i, VECTOR *vec, size_t);
void vector_set(void *p, int i, VECTOR *vec, size_t);
void vector_remove(int i, VECTOR *vec);
void vector_swap(int i, int j, VECTOR *vec);
void vector_show_int(VECTOR *);

#endif