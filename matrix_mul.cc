#include <stdlib.h> 
#include <stdio.h>
#include <assert.h> 
#include "matrix_mul.hh"
#include <algorithm>


void conventional(matrix* a,
                  matrix* b,
                  matrix* output)
{
    int a_rows = a->rows;
    int b_cols = b->cols;

    for(int i = 0; i < a_rows; i++)
    {
        for(int j = 0; j < b_cols; j++)
        {
            output->mat[i][j] = 0;
        }
    }

    for (int i = 0; i < a->pad; i++) {
        for (int j = 0; j < b->pad; j++) {
            for (int k = 0; k < a->pad; k++)
                output->mat[i][j] += a->mat[i][k] * b->mat[k][j];
        }
    }
}


matrix* split(matrix* x, 
              int row_start,
              int col_start,
              int row_break, 
              int col_break) 
{
    // Define output matrix
    int x_rows = x->rows;
    int x_cols = x->cols;

    matrix* new_mat = malloc_matrix(x_rows/2, x_cols/2, x->pad/2);

    // New matrix index
    int row_pos = 0;
    int col_pos = 0;

    
    // Split matrices into quadrants

    copy_matrix(new_mat, x, row_start, row_break, 
                col_start, col_break, row_pos, col_pos);
    return new_mat;
}

void strassen(matrix* output,matrix* a,
               matrix* b, 
               int cross_over)
{
    int a_pad = a->pad;
    int b_pad = b->pad;
    int output_rows = output->rows;
    int output_cols = output->cols;
    int output_pad = output->pad;
    
    if (a->pad <=cross_over|| b->pad<=cross_over)
    {
        conventional(a, b, output);
        return ;
    }
    // Strasse Magic
    matrix* a11 = split(a, 0, 0, a_pad/2, a_pad/2);
    matrix* a12 = split(a, 0, a_pad/2, a_pad/2, a_pad);
    matrix* a21 = split(a, a_pad/2, 0, a_pad, a_pad/2);
    matrix* a22 = split(a, a_pad/2, a_pad/2, a_pad, a_pad);

    matrix* b11 = split(b, 0, 0, b_pad/2, b_pad/2);
    matrix* b12 = split(b, 0, b_pad/2, b_pad/2, b_pad);
    matrix* b21 = split(b, b_pad/2, 0, b_pad, b_pad/2);
    matrix* b22 = split(b, b_pad/2, b_pad/2, b_pad, b_pad);


    // Make subtraction and and addition function

    matrix* p[8];

    for(int i =1; i<8; i++){
      p[i] = malloc_matrix(output_rows/2, output_cols/2, output_pad/2);
    }

    matrix* tmp1 = malloc_matrix(output_rows/2, output_cols/2, output_pad/2);
    matrix* tmp2 = malloc_matrix(output_rows/2, output_cols/2, output_pad/2);
    matrix* tmp3 = malloc_matrix(output_rows/2, output_cols/2, output_pad/2);

    matrix_add(b12, b22, tmp1,-1);
    strassen(p[1], a11, tmp1,cross_over);

    matrix_add(a11, a12, tmp1, 1);
    strassen(p[2], tmp1, b22,cross_over);

    matrix_add(a21, a22, tmp1,1);
    strassen(p[3], tmp1, b11, cross_over);

    matrix_add(b21, b11, tmp1, -1);
    strassen(p[4], a22, tmp1, cross_over);

    matrix_add(a11, a22, tmp1, 1);
    matrix_add(b11,b22, tmp2, 1);
    strassen(p[5], tmp1, tmp2,cross_over);

    matrix_add(a12, a22, tmp1, -1);
    matrix_add(b21, b22, tmp2, 1);
    strassen(p[6], tmp1, tmp2,cross_over);

    matrix_add(a11, a21, tmp1, -1);
    matrix_add(b11, b12, tmp2, 1);
    strassen(p[7], tmp1, tmp2,cross_over);

    // c11
    matrix_add(p[5], p[4], tmp1, 1);
    matrix_add(tmp1, p[2], tmp2, -1);
    matrix_add(tmp2, p[6], tmp3, 1);
    copy_matrix(output, tmp3, 0, output_pad/2, 0, output_pad/2, 0,0);

    //c12
    matrix_add(p[1], p[2], tmp1, 1);
    copy_matrix(output, tmp1, 0, output_pad/2, 
                0, output_pad/2, 0, output_pad/2);
    //c21
    matrix_add(p[3], p[4], tmp1, 1);
    copy_matrix(output, tmp1, 0, output_pad/2, 
                0, output_pad/2, output_pad/2,0);
    //c22
    matrix_add(p[1], p[5], tmp1, 1);
    matrix_add(tmp1, p[3], tmp2, -1);
    matrix_add(tmp2, p[7], tmp3, -1);
    copy_matrix(output, tmp3, 0, output_pad/2, 
                0, output_pad/2, output_pad/2, output_pad/2);

    free_matrix(a11);
    free_matrix(a12);
    free_matrix(a21);
    free_matrix(a22);
    
    free_matrix(b11);
    free_matrix(b12);
    free_matrix(b21);
    free_matrix(b22);

    for (int i=1; i<8; i++){
      free_matrix(p[i]);
    }

    free_matrix(tmp1);
    free_matrix(tmp2);
    free_matrix(tmp3);

}

int compute_pad(int dim, int cross_over){
  int pad = dim;
  while(pad>cross_over){
    pad = (pad+1)/2;
  }
  while(pad<dim){
    pad = pad*2;
  }
  return pad;
}

matrix* strassen_pad(matrix* a, matrix* b, int cross_over){
  int dim = std::max(std::max(a->rows, a->cols), std::max(b->rows, b->cols));
  int pad = compute_pad(dim, cross_over);
  matrix* new_a = malloc_matrix(a->rows, a->cols, pad);
  copy_matrix(new_a, a, 0, a->rows, 0, a->cols, 0,0);

  matrix* new_b = malloc_matrix(b->rows, b->cols, pad);
  copy_matrix(new_b, b, 0, b->rows, 0, b->cols, 0,0);

  matrix* output = malloc_matrix(a->rows, b->cols, pad);

  strassen(output, new_a, new_b, cross_over);

  free_matrix(new_a);
  free_matrix(new_b);
  return output;
}
