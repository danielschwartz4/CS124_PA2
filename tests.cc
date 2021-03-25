#include <cstdint>
#include <stdlib.h> 
#include <stdio.h>
#include <assert.h> 
#include "matrix.hh"
#include "matrix_mul.hh"
#include <iostream>

void create_matrix(matrix* m, int start=1){
	int x = start;
	for (int i =0; i<m->rows; i++){
		for(int j=0; j<m->cols; j++){
			m->mat[i][j] = x;
			x++;
		}
	}
}
matrix* create_random_matrix(int rows, int cols, float p){
	matrix* m = malloc_matrix(rows, cols, std::max(rows, cols));
	int rand_seed = (unsigned) time(0);
  srand(rand_seed);

	for(int i = 0; i < rows; i++)
			{
					for(int j = 0; j < cols; j++)
					{
							
							float r = rand() % 100 + 1;
							if (r / 100 < p)
							{
									m->mat[i][j] = 1;
							}
							else
							{
									m->mat[i][j] = 0;
							}
					}
			}
		return m;
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
void test_copy_matrix(matrix* a){
	matrix* tmp1 = malloc_matrix(a->rows, a->cols, a->pad);
	copy_matrix(tmp1, a, 0,a->rows, 0, a->cols, 0,0);
	compare_matrix(tmp1, a);
	free_matrix(tmp1);
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
	compare_matrix(tmp1, expect);
	free_matrix(tmp1);
}

void test_strassen_pad(matrix* a, matrix* b, int cross_over, matrix* expect){
	matrix* tmp1 = strassen_pad(a, b, cross_over);
	compare_matrix(expect, tmp1);
	free_matrix(tmp1);
};

int main(int argc, char const *argv[]){
	// Test addition and simple multiplication
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

	test_copy_matrix(a);
	printf("pass copy_matrix\n");

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
	printf("pass strassen\n");

// Test Odd multiplication
	matrix* x = malloc_matrix(5,5,5);
	create_matrix(x, 1);
	matrix* y = malloc_matrix(5,5,5);
	// make y an identity matrix
	for (int i=0;i< y->rows; i++){
		for(int j=0; j<y->cols; j++){
			if(i==j){
				y->mat[i][j]=1;
			}
			else{
				y->mat[i][j] = 0;
			}
		}
	}


	print_matrix((char*) "x",x);
	print_matrix((char*) "y", y);
	test_strassen_pad(x, y, 3, x);
	printf("pass strassen pad odd\n");

	free_matrix(a);
	free_matrix(b);
	free_matrix(c);
	free_matrix(x);
	free_matrix(y);
	

	// Test Odd and Even multiplication
	x = malloc_matrix(3,5,5);
	create_matrix(x, 1);
	y = malloc_matrix(5,3,5);
	create_matrix(y, 1);
	matrix *z = malloc_matrix(3,3,5);

	print_matrix((char*) "x",x);
	print_matrix((char*) "y", y);

	z->mat[0][0] = 135;
  	z->mat[0][1] = 150;
	z->mat[0][2] = 165;
  	z->mat[1][0] = 310;
  	z->mat[1][1] = 350;
	z->mat[1][2] = 390;
	z->mat[2][0] = 485;
	z->mat[2][1] = 550;
	z->mat[2][2] = 615;
	// std::cout << z;
	test_strassen_pad(x, y, 3, z);

	matrix* z1 = strassen_pad(x, y, 3);
	matrix* z2 = strassen_pad(x,y, 2);
	compare_matrix(z1, z2);


	printf("pass strassen pad\n");

	free_matrix(x);
	free_matrix(y);
	free_matrix(z);
	free_matrix(z1);
	free_matrix(z2);
	printf("finish test\n");

// Random matrix
	matrix* m1 = create_random_matrix(9,9,0.5);
	print_matrix((char*) "m1", m1);
	matrix* m2 = create_random_matrix(9,9,0.8);
	print_matrix((char*) "m2", m2);
	matrix* c1 = malloc_matrix(5,5,101);
	print_matrix((char*) "c1", c1);
	conventional(m1,m2,c1);
	test_strassen_pad(m1, m2, 1, c1);
	printf("pass compare_matrix\n");

	free_matrix(m1);
	free_matrix(m2);
	free_matrix(c1);
	return 0;
}