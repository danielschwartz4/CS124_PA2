#ifndef MATRIX_MUL_HH
#define MATRIX_MUL_HH

#include <stdlib.h> 
#include <stdio.h>
#include "matrix.hh"
#include <algorithm>

void conventional(matrix* a, matrix* b, matrix* output);

matrix* split(matrix* x, int row_start, int col_start, int row_break, int col_break);

void strassen(matrix* output, matrix* a, matrix* b, int n);

int compute_pad(int dim, int cross_over);

matrix* strassen_pad(matrix* a, matrix* b, int cross_over);

#endif