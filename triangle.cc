#include <iostream>
#include <vector>
#include "matrix.hh"
#include "matrix_mul.hh"
#include <algorithm>
#include <ctime>
#include <time.h>


int calc_diagonal(matrix *m){
	int col_idx = 0;
  int rows = m->rows;
  int cols = m->cols;
  assert(rows == cols);
  int sum = 0;
  for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            if (j == col_idx)
            {
                sum = m->mat[i][j] + sum;
            }
        }
    }
  int num_triangles = sum / 6;
  return num_triangles;
}