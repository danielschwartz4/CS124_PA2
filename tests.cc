#include <cstdint>
#include <stdlib.h> 
#include <stdio.h>
#include "matrix.hh"
#include "matrix_mul.hh"

void create_matrix(matrix* m, int start=1){
	int x = start;
	printf("m: %p\n", m);
	printf("m->mat: %p\n", m->mat);

	for (int i =0; i<m->pad; i++){
		printf("i: %p\n", m->mat[i]);
		for(int j=0; j<m->pad; j++){
			m->mat[i][j] = x;
			x++;
		}
	}

}

// test matrix addition
void test_add(matrix* a, matrix* b){
	return;
}

// test matrix substraction
void test_sub(matrix* a, matrix*b){
	return;
}

//test copy_matrix
void test_copy_matrix(matrix* a, matrix expect){
	return;
}
void test_conventional(matrix* m, matrix* expect){
	return;
}

void test_strassen(matrix* m, matrix* expect){
	return;
}

void test_strassen_pad(matrix* m, matrix* expect){
	return;
};

int main(int argc, char const *argv[]){
	matrix* a = malloc_matrix(2,2,1);
	create_matrix(a,1);

	matrix* b = malloc_matrix(2,2,2);
	create_matrix(b,2);


	free_matrix(a);
	free_matrix(b);
	return 0;
}