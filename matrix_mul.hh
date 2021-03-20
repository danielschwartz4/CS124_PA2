#ifndef MATRIX_HH
#define MATRIX_HH

#include <stdlib.h> 
#include <stdio.h>

typedef struct matrix
{
	int ** mat;
	int rows; // number of rows
	int cols; // number of columns
} matrix;

// matrix::~matrix(){
// 	printf("test ");
// 	for (int i=0; i<this->rows; i++){
// 		free (this->mat[i]);
// 	}
// 	free (this->mat);
// }

struct matrix;

void free_matrix(matrix* m);

void conventional(matrix* a,
                  matrix* b,
                  matrix* output);

#endif