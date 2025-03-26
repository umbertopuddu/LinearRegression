#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include "vector.h"

typedef struct {
    long row_num;
    long col_num;
    long double **data;
} Matrix;

// Create an empty matrix with the given dimensions.
Matrix empty_matr(long row_num, long col_num);

// Free the memory associated with a matrix.
void free_matr(Matrix *m);

// Get a pointer to the element at (row, col).
long double * get_m_pos(Matrix *m, long row, long col);

// Get the value of the element at (row, col).
long double get_m_val(Matrix *m, long row, long col);

// Multiply two matrices (m1 * m2) and return the result.
Matrix mul_matr(Matrix *m1, Matrix *m2);

// Invert a square matrix using Gauss–Jordan elimination.
Matrix inv_matr(Matrix *m);

// Transpose a matrix.
Matrix t_matrix(Matrix *m);

// Get the specified row as a Vector.
Vector get_row(Matrix *m, long row);

// Get the specified column as a Vector.
Vector get_col(Matrix *m, long col);

// Macro to access matrix data with clean syntax.
// Usage: mat(M)[i][j] expands to ((M).data)[i][j]
#define mat(m) ((m).data)

#endif // MATRIX_H