#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

Vector init_vec(long double * data, long size)
{
    Vector vec;
    vec.data = data;
    vec.size = size;
    return vec;
}

Vector empty_vec(long size)
{
    Vector vec;
    vec.size = size;
    vec.data = malloc(sizeof(long double) * size);
    if (!vec.data) {
        perror("Failed to allocate vector data");
        exit(1);
    }
    for (long i = 0; i < size; i++)
    {
        vec.data[i] = 0.0L;
    }
    return vec;
}

void free_vec(Vector * v)
{
    if (v->data != NULL) {
        free(v->data);
        v->data = NULL;
    }
}

long double dot(Vector * v1, Vector * v2)
{
    if (v1->size != v2->size)
    {
        fprintf(stderr, "Cannot perform dot product on vectors of different sizes.\n");
        exit(1);
    }

    long double product = 0.0L;
    
    for (long i = 0; i < v1->size; i++)
    {
        product += v1->data[i] * v2->data[i];
    }
    
    return product;
}
