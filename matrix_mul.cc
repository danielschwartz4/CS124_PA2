#include <iostream>
#include <vector>
#include "matrix_mul.hh"


// struct matrix
// {
//   int ** mat;
//   int rows; // number of rows
//   int cols; // number of columns
// };

void free_matrix(matrix* m);


void conventional(matrix* a,
                  matrix* b,
                  matrix* output);


void free_matrix(matrix* m){
  printf("test ");
  for (int i=0; i<m->rows; i++){
    printf("free %d %p\n", i, m->mat[i]);
    free (m->mat[i]);
  }
  printf("free mat %p\n", m->mat);
  free (m->mat);
}

// I just initiated array size to a random number like 100 I need to figure out how to use pointers.
void conventional(matrix* a,
                  matrix* b,
                  matrix* output)
{
    int a_rows = a->rows;
    int a_cols = a->cols;
    int b_rows = b->rows;
    int b_cols = b->cols;
    int output_rows = output->rows;
    int output_cols = output->cols;

    assert(a_cols==b_rows);
    assert(output_rows==a_rows);
    assert(output_cols==b_cols);

    for(int i = 0; i < a_rows; ++i)
    {
        for(int j = 0; j < b_cols; ++j)
        {
            output->mat[i][j] = 0;
        }
    }

    for (int i = 0; i < a_rows; i++) {
        for (int j = 0; j < b_cols; j++) {
            for (int k = 0; k < a_cols; k++)
                output->mat[i][j] += a->mat[i][k] * b->mat[k][j];
        }
    }
}

