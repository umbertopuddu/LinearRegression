#ifndef MATRIX
#define MATRIX

#include "vector.h"

typedef struct {
    long row_num;
    long col_num;
    Vector * data;
} Matrix;

Matrix init_matr(Vector * rows, long row_num);
Matrix empty_matr(long row_num, long col_num);
void free_matr(Matrix * m);
long double * get_m_pos(Matrix * m, long row, long col);
long double get_m_val(Matrix * m, long row, long col);
Vector * get_row(Matrix * m, long row_num);
Vector * get_col(Matrix * m, long col_num);
Matrix mul_matr(Matrix * m1, Matrix * m2);
Matrix inv_matr(Matrix *m);
Matrix t_matrix(Matrix *m);

#endif