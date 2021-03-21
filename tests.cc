#include <cstdint>
#include <stdlib.h> 
#include <stdio.h>
#include "matrix.hh"
#include "matrix_mul.hh"

void create_matrix(matrix* m, int start=1){
	int x = start;
	for (int i =0; i<m->pad; i++){
		for(int j=0; j<m->pad; j++){
			m->mat[i][j] = x;
			x++;
		}
	}

}

void compare_matrix(matrix* a, matrix* b){
	assert(a->rows==b->rows);
	assert(a->cols==b->cols);
	for (int i = 0; i < a->rows; i++){
		for (int j = 0; i < a->cols; i++){
			assert(a->mat[i][j]==b->mat[i][j]);
		}
	}
}

// test matrix addition
void test_add(matrix* a, matrix* b, matrix* expect){
	matrix* tmp1 = malloc_matrix(a->rows, a->cols, a->pad);
	matrix_add(a, b, tmp1, 1);
	compare_matrix(tmp1, expect);
	free_matrix(tmp1);
}

// test matrix substraction
void test_sub(matrix* a, matrix*b){
	return;
}

//test copy_matrix
void test_copy_matrix(matrix* a, matrix expect){
	return;
}
void test_conventional(matrix* a, matrix* b, matrix* expect){
	matrix* tmp1 = malloc_matrix(a->rows, b->cols, a->pad);
	conventional(a, b, tmp1);
	compare_matrix(tmp1, expect);
	free_matrix(tmp1);
}

void test_strassen(matrix* a, matrix* b, matrix* expect){
	matrix* tmp1 = malloc_matrix(a->rows, b->cols, a->pad);
	strassen(tmp1, a, b,1);
	printf("here\n");
	compare_matrix(tmp1, expect);
	free_matrix(tmp1);
}

void test_strassen_pad(matrix* m, matrix* expect){
	return;
};

int main(int argc, char const *argv[]){
	matrix* a = malloc_matrix(2,2,2);
	create_matrix(a,1);

	matrix* b = malloc_matrix(2,2,2);
	create_matrix(b,1);

	matrix* c = malloc_matrix(2,2,2);
	for(int i=0; i<a->rows; i++){
		for (int j=0; j<a->rows; j++){
			c->mat[i][j] = a->mat[i][j]*2;
		}
	}

	compare_matrix(a, b);
	printf("pass compare_matrix\n");
	test_add(a, b, c);
	printf("pass test_add\n");

	c->mat[0][0] = 10;
	c->mat[0][1] = 13;
	c->mat[1][0] = 22;
	c->mat[1][1] = 29;
	create_matrix(b,2);
	test_conventional(a, b, c);
	printf("pass conventional\n");

	test_strassen(a,b,c);


	free_matrix(a);
	free_matrix(b);
	free_matrix(c);
	printf("finish test\n");
	return 0;
}