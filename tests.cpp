#include "matrix_mul.hh"
#include <cstdint>
#include <stdlib.h> 
#include <stdio.h>
#include <iostream>


matrix* create_matrix(int num_rows, int num_cols, int start=1){
  int x = start;
  matrix* m = new matrix;
  m->rows = num_rows;
  m->cols = num_cols;
  m->mat = (int**) malloc(num_rows*sizeof(uintptr_t));
  for (int i =0; i<num_rows; i++){
    m->mat[i] = (int*) malloc(num_cols*sizeof(int));
    for(int j=0; j<num_cols; j++){
      m->mat[i][j] = x;
      x++;
    }
  }
  return m;
}

void print_matrix(matrix* m, int num_rows, int num_cols){

  for (int i =0; i<num_rows; i++){
    std::cout << "\n";
    for(int j=0; j<num_cols; j++){
      std::cout << m->mat[i][j] << " ";
    }
  }
  std::cout << "\n";
}

int main(int argc, char const *argv[])
{

  matrix *a = create_matrix(4,4,1);
  matrix *b = create_matrix(4,4,1);
  matrix *z;
  conventional(a, b, z);
  int num_rows = z->rows;
  int num_cols = z->cols;
  print_matrix(z, num_rows, num_cols);
  delete z;
}
