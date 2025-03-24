#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

Matrix init_matr(Vector * rows, long row_num)
{
    Matrix m;
    m.row_num = row_num;
    m.data = rows;
    return m;
}

Matrix empty_matr(long row_num, long col_num)
{
    Matrix m;
    m.data = malloc(sizeof(Vector) * row_num);
    m.row_num = row_num;
    m.col_num = col_num;

    for (int i = 0; i < row_num; i++)
    {
        m.data[i] = empty_vec(col_num);
    }
    return m;
}

void free_matr(Matrix * m)
{
    for (int i = 0; i < m->row_num; i++)
    {
        free_vec(&(m->data[i]));
    }
    free(m->data);
    return;
}

long double * get_m_pos(Matrix * m, long row, long col)
{
    return &(m->data[row].data[col]);
}

long double get_m_val(Matrix * m, long row, long col)
{
    return *get_m_pos(m, row, col);
}

Vector * get_row(Matrix * m, long row_num)
{
    if (row_num >= m->row_num)
    {
        fprintf(stderr, "Accessing matrix row out of bound: attempted %ld/%ld", row_num, m->row_num);
        exit(1);
    }
    return &(m->data[row_num]);
}

Vector * get_col(Matrix * m, long col_num)
{
    if (col_num >= m->col_num)
    {
        fprintf(stderr, "Accessing matrix column out of bound: attempted %ld/%ld", col_num, m->col_num);
        exit(1);
    }
    Vector col = empty_vec(m->row_num);
    for (int i = 0; i < m->row_num; i++)
    {
        col.data[i] = m->data[i].data[col_num];
    }
    Vector * column = malloc(sizeof(Vector));
    *column = col;
    return column;
}

Matrix mul_matr(Matrix * m1, Matrix * m2)
{
    if (m1 -> col_num != m2 -> row_num)
    {
        fprintf(stderr, "Cannot multiply matrices (not of size N x P and P x K)");
        exit(1);
    }
    Matrix result = empty_matr(m1 -> row_num, m2 -> col_num);
    
    for (int i = 0; i < m1 -> row_num; i++)
    {
        for (int j = 0; j < m2 -> col_num; j++)
        {
            Vector *col = get_col(m2, j);
            result.data[i].data[j] = dot(&m1 -> data[i], col);
            free_vec(col);
            free(col);
        }
    }
    return result;
}

Matrix inv_matr(Matrix *m)
{
    if (m->row_num != m->col_num)
    {
        fprintf(stderr, "Matrix inversion error: matrix is not square.\n");
        exit(1);
    }
    
    long n = m->row_num;
    
    Matrix aug = empty_matr(n, 2 * n);
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            aug.data[i].data[j] = m->data[i].data[j];
        }
        for (int j = n; j < 2 * n; j++)
        {
            aug.data[i].data[j] = (i == (j - n)) ? 1.0L : 0.0L;
        }
    }
    
    // Perform Gauss–Jordan elimination.
    for (int i = 0; i < n; i++)
    {
        long double pivot = aug.data[i].data[i];
        if (pivot == 0)
        {
            fprintf(stderr, "Matrix inversion error: singular matrix.\n");
            exit(1);
        }
        // Divide the pivot row by the pivot element.
        for (int j = 0; j < 2 * n; j++)
        {
            aug.data[i].data[j] /= pivot;
        }
        // Eliminate the current column from all other rows.
        for (int k = 0; k < n; k++)
        {
            if (k != i)
            {
                long double factor = aug.data[k].data[i];
                for (int j = 0; j < 2 * n; j++)
                {
                    aug.data[k].data[j] -= factor * aug.data[i].data[j];
                }
            }
        }
    }
    
    Matrix inv = empty_matr(n, n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            inv.data[i].data[j] = aug.data[i].data[j + n];
        }
    }
    
    free_matr(&aug);
    
    return inv;
}

Matrix t_matrix(Matrix *m)
{
    Matrix t = empty_matr(m->col_num, m->row_num);
    
    for (int i = 0; i < m->row_num; i++)
    {
        for (int j = 0; j < m->col_num; j++)
        {
            t.data[j].data[i] = m->data[i].data[j];
        }
    }
    
    return t;
}