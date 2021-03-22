
#include <stdio.h>
#include <cstdio>
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
			int rand_seed = (unsigned) time(0);
			srand(rand_seed);
			m->mat[i][j] = rand()%3;
		}
	}
	return m;
}

int main(int argc, char const *argv[])
{	

	// FILE * pFile;
	// pFile = fopen("crossover.csv","w");
	int start_dim =  atoi(argv[1]);
	int end_dim = atoi(argv[2]);

	for(int i=start_dim; i<=end_dim; i++){
		// create matrices
		matrix* a = generate_rand_matrix(i);
		matrix* b = generate_rand_matrix(i);
		matrix* c = malloc_matrix(i,i,i);
		// time conventional
		start = clock();
		for (int trail=0; trail<5; trail++){
			conventional(a, b, c);
		}
		end = clock();
		double conv_spend = (double) (end-start)/5;

		// stranssen crossover explore
		int stranssen_cross_over=0;
		for(int cross_over=1; cross_over<=i; cross_over++){
			start = clock();
			for (int trail=0; trail<5; trail++){
				strassen_pad(a, b, cross_over);
			}
			end = clock();

			double strs_spend = (double) (end-start)/5;
			if (strs_spend<=conv_spend){
				stranssen_cross_over = cross_over;
				break;
			}
		}
		if(stranssen_cross_over==0){
			stranssen_cross_over=i;
		}

		printf("%d\t%d\n",i, stranssen_cross_over);		
		free_matrix(a);
		free_matrix(b);
		free_matrix(c);
	}
	// fclose (pFile);

	return 0;
}
