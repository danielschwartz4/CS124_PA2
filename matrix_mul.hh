#ifndef MATRIX_HH
#define MATRIX_HH
#endif
struct matrix
{
	int ** mat;
	int rows; // number of rows
	int cols; // number of columns
	~matrix();
};

void conventional(matrix* a,
                  matrix* b,
                  matrix* output);