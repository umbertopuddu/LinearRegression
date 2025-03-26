#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

Matrix empty_matr(long row_num, long col_num)
{
    Matrix m;
    m.row_num = row_num;
    m.col_num = col_num;
    
    // Allocate memory for the array of row pointers.
    m.data = malloc(sizeof(long double*) * row_num);
    if (!m.data) {
        perror("Failed to allocate row pointers");
        exit(EXIT_FAILURE);
    }
    
    // Allocate one contiguous block for all matrix elements.
    long double *data_block = malloc(sizeof(long double) * row_num * col_num);
    if (!data_block) {
        perror("Failed to allocate data block");
        exit(EXIT_FAILURE);
    }
    
    // Point each row pointer to the appropriate position in the data block.
    for (long i = 0; i < row_num; i++) {
        m.data[i] = data_block + i * col_num;
    }
    
    return m;
}

void free_matr(Matrix *m)
{
    if (m->data != NULL) {
        free(m->data[0]); // Free the contiguous data block.
        free(m->data);    // Free the array of row pointers.
        m->data = NULL;
    }
}

long double * get_m_pos(Matrix *m, long row, long col)
{
    if (row < 0 || row >= m->row_num || col < 0 || col >= m->col_num) {
        fprintf(stderr, "Accessing matrix element out of bounds: attempted (%ld, %ld) in %ld x %ld matrix\n", 
                row, col, m->row_num, m->col_num);
        exit(EXIT_FAILURE);
    }
    return &mat(*m)[row][col];
}

long double get_m_val(Matrix *m, long row, long col)
{
    return *get_m_pos(m, row, col);
}

Matrix mul_matr(Matrix *m1, Matrix *m2)
{
    if (m1->col_num != m2->row_num) {
        fprintf(stderr, "Cannot multiply matrices: dimensions mismatch (%ld x %ld and %ld x %ld)\n", 
                m1->row_num, m1->col_num, m2->row_num, m2->col_num);
        exit(EXIT_FAILURE);
    }
    
    Matrix result = empty_matr(m1->row_num, m2->col_num);
    
    for (long i = 0; i < m1->row_num; i++) {
        for (long j = 0; j < m2->col_num; j++) {
            long double sum = 0.0L;
            for (long k = 0; k < m1->col_num; k++) {
                sum += mat(*m1)[i][k] * mat(*m2)[k][j];
            }
            mat(result)[i][j] = sum;
        }
    }
    
    return result;
}

Matrix inv_matr(Matrix *m)
{
    if (m->row_num != m->col_num) {
        fprintf(stderr, "Matrix inversion error: matrix is not square.\n");
        exit(EXIT_FAILURE);
    }
    
    long n = m->row_num;
    Matrix aug = empty_matr(n, 2 * n);
    
    // Set up the augmented matrix [m | I]
    for (long i = 0; i < n; i++) {
        for (long j = 0; j < n; j++) {
            mat(aug)[i][j] = mat(*m)[i][j];
        }
        for (long j = n; j < 2 * n; j++) {
            mat(aug)[i][j] = (i == (j - n)) ? 1.0L : 0.0L;
        }
    }
    
    // Perform Gauss–Jordan elimination.
    for (long i = 0; i < n; i++) {
        long double pivot = mat(aug)[i][i];
        if (pivot == 0) {
            fprintf(stderr, "Matrix inversion error: singular matrix.\n");
            exit(EXIT_FAILURE);
        }
        for (long j = 0; j < 2 * n; j++) {
            mat(aug)[i][j] /= pivot;
        }
        for (long k = 0; k < n; k++) {
            if (k != i) {
                long double factor = mat(aug)[k][i];
                for (long j = 0; j < 2 * n; j++) {
                    mat(aug)[k][j] -= factor * mat(aug)[i][j];
                }
            }
        }
    }
    
    Matrix inv = empty_matr(n, n);
    for (long i = 0; i < n; i++) {
        for (long j = 0; j < n; j++) {
            mat(inv)[i][j] = mat(aug)[i][j + n];
        }
    }
    
    free_matr(&aug);
    return inv;
}

Matrix t_matrix(Matrix *m)
{
    Matrix t = empty_matr(m->col_num, m->row_num);
    
    for (long i = 0; i < m->row_num; i++) {
        for (long j = 0; j < m->col_num; j++) {
            mat(t)[j][i] = mat(*m)[i][j];
        }
    }
    
    return t;
}

Vector get_row(Matrix *m, long row)
{
    if (row < 0 || row >= m->row_num) {
        fprintf(stderr, "Accessing matrix row out of bounds: attempted %ld in %ld rows\n", row, m->row_num);
        exit(EXIT_FAILURE);
    }
    Vector vec = empty_vec(m->col_num);
    for (long j = 0; j < m->col_num; j++) {
        vec.data[j] = mat(*m)[row][j];
    }
    return vec;
}

Vector get_col(Matrix *m, long col)
{
    if (col < 0 || col >= m->col_num) {
        fprintf(stderr, "Accessing matrix column out of bounds: attempted %ld in %ld columns\n", col, m->col_num);
        exit(EXIT_FAILURE);
    }
    Vector vec = empty_vec(m->row_num);
    for (long i = 0; i < m->row_num; i++) {
        vec.data[i] = mat(*m)[i][col];
    }
    return vec;
}
