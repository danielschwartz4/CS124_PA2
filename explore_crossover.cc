#include <iostream>
#include <vector>
#include "matrix.hh"
#include "matrix_mul.hh"
#include <algorithm>
#include <ctime>
#include <time.h>

clock_t start, end;

matrix* generate_rand_matrix(int dim){
	matrix* m = malloc_matrix(dim, dim, dim);
	for (int i = 0; i<dim; i++){
		for(int j=0; j<dim; j++){
			m->mat[i][j] = rand()%3;
		}
	}
	return m;
}

int main(int argc, char const *argv[])
{
	int n=150;
	matrix* a = generate_rand_matrix(n);
	matrix* b = generate_rand_matrix(n);
	matrix* c = malloc_matrix(n,n,n);
	start = clock();
	for (int trail=0; trail<5; trail++){
		conventional(a, b, c);
	}
	end = clock();
	double conv_spend = (double) (end-start)/5;

	for(int cross_over=1; cross_over<=n; cross_over++){
		start = clock();
		for (int trail=0; trail<5; trail++){
			strassen_pad(a, b, cross_over);
		}
		end = clock();

		double strs_spend = (double) (end-start)/5;

		printf("%d\t%f\t%f\n", cross_over, conv_spend, strs_spend);

	}
	free_matrix(a);
	free_matrix(b);
	free_matrix(c);
	return 0;
}
