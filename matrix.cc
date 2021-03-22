#include <iostream>
#include <vector>
#include "matrix.hh"


matrix* malloc_matrix(int num_rows, int num_cols, int pad){
  matrix* m = new matrix;
  // printf("malloc m: %p\n", m);
  m->rows = num_rows;
  m->cols = num_cols;
  m->pad = pad;
  m->mat = (int**) malloc(pad * sizeof(uintptr_t));
  // printf("malloc mat: %p\n", m->mat);
  for (int i =0; i<pad; i++){
    m->mat[i] = (int*) malloc(pad*sizeof(int));
    // printf("malloc i: %d %p\n", i, m->mat[i]);
    for(int j=0; j<pad; j++){
      m->mat[i][j] = 0;
    }
  }
  return m;
}

void free_matrix(matrix* m){
  // printf("test ");
  for (int i=0; i<m->pad; i++){
    // printf("free i: %d %p\n", i, m->mat[i]);
    free (m->mat[i]);
  }
  // printf("free m->mat %p\n", m->mat);
  free (m->mat);
  // printf("free m: %p\n", m);
  delete m;
}

void copy_matrix(matrix* dest, matrix* source, 
                  int row_start, int row_end,
                  int col_start, int col_end,
                  int dest_row_start, int dest_col_start){
    int dest_i=dest_row_start;
    int dest_j=dest_col_start;

    for (int i = row_start; i<row_end; i++){
      for (int j = col_start; j<col_end; j++){
        dest->mat[dest_i][dest_j] = source->mat[i][j];
        dest_j++;
      }
      dest_i++;
      dest_j=dest_col_start;
    }

}

void addition_assert(matrix* a, matrix* b, matrix* s){
  assert(a->rows==b->rows);
  assert(a->cols==b->cols);
  assert(a->rows==s->rows);
  assert(a->cols==s->cols);
}

//when ops is -1, it's matrix substraction. when opts is 1, it's matrix addition
void matrix_add(matrix* a, matrix* b, matrix* s, int ops){
  addition_assert(a, b, s);
  for (int i=0; i<a->pad; i++){
    for (int j=0; j<a->pad; j++){
      s->mat[i][j] = a->mat[i][j] + ops*b->mat[i][j];
    }
  }
}

void print_matrix(char* matrix_name, matrix* m){
	printf("%s\n", matrix_name);
	for(int i=0; i<m->pad; i++){
		for(int j=0; j<m->pad; j++){
			printf("%d\t", m->mat[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}