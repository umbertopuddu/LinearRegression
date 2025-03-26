#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    long size;
    long double * data;
} Vector;

// Initialize a vector using pre-allocated data.
Vector init_vec(long double * data, long size);

// Allocate and return an empty vector (all elements set to zero) of the given size.
Vector empty_vec(long size);

// Free the memory allocated for a vector.
void free_vec(Vector * v);

// Compute the dot product of two vectors.
// Exits with an error if the vectors are not the same size.
long double dot(Vector * v1, Vector * v2);

// Macro to access vector data with clean syntax.
// Usage: vec(v)[i] expands to (v).data[i]
#define vec(v) ((v).data)

#endif