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

    for(int i = 0; i < a_rows; i++)
    {
        for(int j = 0; j < b_cols; j++)
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

*matrix split(matrix* x, 
              int row_start,
              int col_start,
              int row_break, 
              int col_break) 
{
    // Define output matrix
    *matrix new_mat[x_rows/2][x_cols/2]
    // New matrix index
    int row_pos = 0
    int row_pos = 0

    int x_rows = x->rows;
    int x_cols = x->cols;

    // Split matrices into quadrants
    for (int i=row_start; i<row_break; i++){ 
        for (int j=col_start; j<col_break; j++){ 
            *(new_mat->mat[row_pos][col_pos]) = x->mat[i][j]; 
            row_pos++; 
            col_pos++;
        }
    }
    return new_mat
}

*matrix strassen(matrix* a,
               matrix* b,
               matrix* output,
               int n)
{
    int a_rows = a->rows;
    int a_cols = a->cols;
    int b_rows = b->rows;
    int b_cols = b->cols;
    int output_rows = output->rows;
    int output_cols = output->cols;
    
    if (a->rows == n) {
        conventional(a, b, output);
        return output->mat[0][0];
    }
    // Strasse Magic
    a11 = split(a, 0, 0, a_rows/2, a_cols/2)
    a12 = split(a, 0, a_cols/2/2, a_rows/2, a_cols)
    a21 = split(a, a_rows/2, 0, a_rows, a_cols/2)
    a22 = split(a, a_rows/2, a_cols/2, a_rows, a_cols)

    p1 = strassen(a11, b12 - b22)   
    p2 = strassen(a11 + a12, b22)         
    p3 = strassen(a21 + a22, b11)         
    p4 = strassen(a22, b21 - b11)         
    p5 = strassen(a11 + a22, b11 + b22)         
    p6 = strassen(a12 - a22, b21 + b22)   
    p7 = strassen(a11 - b21, b11 + b12)   

    c11 = p5 + p4 - p2 + p6   
    c12 = p1 + p2            
    c21 = p3 + p4             
    c22 = p1 + p5 - p3 - p7

    // Combine 4 quadrants

}

