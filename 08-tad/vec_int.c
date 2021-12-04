#include <stdlib.h>

#include "vec_int.h"


typedef struct _vec_int {
    int *data;
    int size;
    int capacity;
} vec_int;


vec_int *vec_int_create() {
    vec_int *vec = malloc(sizeof(vec_int));
    vec->capacity = 2;
    vec->size = 0;
    vec->data = malloc(vec->capacity*sizeof(int));
    return vec;
}

void vec_int_destroy(vec_int **_v) {
    free((*_v)->data);
    free(*_v);
    *_v = NULL;
}

int vec_int_size(vec_int *v) {
    return v->size;
}

int vec_int_at(vec_int *v, int p, int *vi) {
    if(p >= (v->size)){
        return 0;
    }
    *vi = v->data[p];
    return 1;
}

int vec_int_insert(vec_int *v, int p, int x) {
    if(p > v->size || p<0){
        return 0;
    }
    int size = vec_int_size(v);
    if (size == v->capacity){
        v->capacity *= 2;
        v->data = realloc(v->data, v->capacity*sizeof(int));
    }
    for(int j=size;j>p; j--){
        v->data[j] = v->data[j-1];
    }
    v->data[p] = x;
    v->size += 1;
    return 1;
}

int vec_int_remove(vec_int *v, int p) {
    if(p >= v->size || p<0){
        return 0;
    }
    int size = vec_int_size(v);
    if (size < (v->capacity)*0.25){
        v->capacity /= 2;
        v->data = realloc(v->data, v->capacity*sizeof(int));
    }
    for(int j=p+1;j<size; j++){
        v->data[j-1] = v->data[j];
    }
    v->size-=1;
    return 1;
}