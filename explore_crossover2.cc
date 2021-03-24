#include <stdio.h>
#include <cstdio>
#include <vector>
#include "matrix.hh"
#include "matrix_mul.hh"
#include <algorithm>
#include <ctime>
#include <time.h>
#include <assert.h> 
#include <chrono>

clock_t conv_start, conv_end, str_start, str_end;

void generate_rand_matrix(matrix* m, int dim){
	for (int i = 0; i<dim; i++){
		for(int j=0; j<dim; j++){
			m->mat[i][j] = rand()%3;
		}
	}
}

int main(int argc, char const *argv[])
{	
	int dim =  atoi(argv[1]);
	int crossover_start = atoi(argv[2]);
	int increment = 10;
	assert(dim>=100);

	for(int crossover=crossover_start; crossover<=100; crossover+=increment){
		// create matrices
		matrix* a = malloc_matrix(dim, dim, dim);
		matrix* b = malloc_matrix(dim, dim, dim);

		// stranssen crossover explore
		double strs_spend = 0;

		for (int trail=0; trail<5; trail++){
				generate_rand_matrix(a, dim);
				generate_rand_matrix(b, dim);

				auto t_start = std::chrono::high_resolution_clock::now();
				matrix* c = strassen_pad(a, b, crossover);
				auto t_end = std::chrono::high_resolution_clock::now();
				strs_spend += std::chrono::duration<double, std::milli>(t_end-t_start).count();
				free_matrix(c);
			}

		
		printf("%lf\n", strs_spend/5);		
		free_matrix(a);
		free_matrix(b);
	
	}

	return 0;
}
