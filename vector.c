#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "vector.h"
#define inbound(i, size) i >= 0 && i < size
void vector_init(VECTOR *vec ){
	// Inits pointer to Vector
	// User is in charge of allocating the memory of the pointer either in the stack or in the heap
	vec->space = 20;
	vec->arr = calloc( vec->space , sizeof(void *) );
	vec->size = 0;

}

void vector_destroy(VECTOR *vec){
	while(vec->size != 0){
	    vector_remove_last(vec);
	}
	free(vec->arr);
}

static void vector_resize(int newSize, VECTOR *vec){
	void **arr = realloc(vec->arr, sizeof(void *) * newSize);
	if(arr){
		vec->arr = arr;
		vec->space = newSize; 
	}
}

void *vector_get(int i, VECTOR *vec){
	if (i >= 0 && i < vec->size){
		return vec->arr[i];	
	}else{
		printf("Out of bounds\n");
		exit(0);
	}
}

void vector_add(void *p, int i, VECTOR *vec, size_t data_size){
	if( i >= 0 && i <= vec->size){
	    if( vec->size == vec->space){
			printf("Increase Vector Space \n");
			vector_resize(vec->space*2, vec); 
		}
		for(int j = vec->size; j > i; --j ){
			vec->arr[j] = vec->arr[j-1];
		}
		void *temp = malloc(data_size);
		memcpy(temp, p, data_size);
		vec->arr[i] = temp;
		(vec->size)++;
	}else{
		printf("Index Out of Bounds \n");
		exit(0);
	}
}


void vector_set(void *p, int i, VECTOR *vec, size_t data_size){
	if( i >= 0 && i < vec->size){
		memcpy(vec->arr[i], p, data_size);
	}else{
		printf("Index Out of Bounds \n");
		exit(0);
	}
}

void vector_remove(int i, VECTOR *vec){
	if( i >= 0 && i < vec->size){
		free(vec->arr[i]);
	    for(int j = i; j < vec->size - 1; j++){
			vec->arr[j] = vec->arr[j+1];
			vec->arr[j+1] = NULL;
		}
	    vec->arr[vec->size - 1] = NULL;
		vec->size--;
		if( vec->size > 20 && vec->size == (vec->space)/4  ){
			vector_resize(vec->size + 20, vec);
        }
	}else{
		printf("Index Out of Bounds \n");
		exit(0);
	}
}

void vector_swap(int i, int j, VECTOR* vec){
	if(inbound(i, vec->size) && inbound(j, vec->size)){
		void *temp = vector_get(i, vec);
		vec->arr[i] = vec->arr[j];
		vec->arr[j] = temp;
	}
}

void vector_show_int(VECTOR *vec){
    for(int i = 0; i < vec->size; i++){
        printf("%d, ", *(int *)vector_get(i, vec));
    }
    printf("\n");
}