#ifndef MATRIX_HH
#define MATRIX_HH

#include <stdlib.h> 
#include <stdio.h>

typedef struct matrix
{
	int ** mat;
	int rows; // number of rows
	int cols; // number of columns
	int pad;
} matrix;

matrix* malloc_matrix(int num_rows, int num_cols, int pad);

void free_matrix(matrix* m);

void copy_matrix(matrix* dest, matrix* source, 
                  int row_start, int row_end,
                  int col_start, int col_end,
                  int dest_row_start, int dest_col_start);

void addition_assert(matrix* a, matrix* b, matrix* s);

void matrix_add(matrix* a, matrix* b, matrix* s, int ops);


#endif