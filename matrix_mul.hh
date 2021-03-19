#ifndef MATRIX_HH
#define MATRIX_HH
#endif
#include <stdlib.h> 
#include <stdio.h>

struct matrix
{
	int ** mat;
	int rows; // number of rows
	int cols; // number of columns
	~matrix();
};

matrix::~matrix(){
	printf("test ");
	for (int i=0; i<this->rows; i++){
		free (this->mat[i]);
	}
	free (this->mat);
}

void conventional(matrix* a,
                  matrix* b,
                  matrix* output);