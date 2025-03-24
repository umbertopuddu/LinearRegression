#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    long size;
    long double * data;
} Vector;

Vector init_vec(long double * data, long size);
Vector empty_vec(long size);
void free_vec(Vector * v);

long double dot(Vector * v1, Vector * v2);

#endif