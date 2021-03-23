#include <stdio.h>
#include <cstdio>
#include <vector>
#include "matrix.hh"
#include "matrix_mul.hh"
#include <algorithm>
#include <ctime>
#include <time.h>

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
	// FILE * pFile;
	// pFile = fopen("crossover.csv","w");
	int start_dim =  atoi(argv[1]);
	int end_dim = atoi(argv[2]);

	for(int i=start_dim; i<=end_dim; i++){
		// create matrices
		matrix* a = malloc_matrix(i, i, i);
		matrix* b = malloc_matrix(i, i, i);
		matrix* c = malloc_matrix(i,i,i);
		// time conventional
		double conv_spend = 0;
		
		for (int trail=0; trail<5; trail++){
			generate_rand_matrix(a, i);
			generate_rand_matrix(b, i);
			conv_start = clock();
			conventional(a, b, c);
			conv_end = clock();
			conv_spend+=conv_end-conv_start;

		}
		conv_spend = conv_spend/5;

		// stranssen crossover explore
		int stranssen_cross_over=0;
		for(int cross_over=1; cross_over<=i; cross_over++){
			double strs_spend = 0;
			for (int trail=0; trail<5; trail++){
				generate_rand_matrix(a, i);
				generate_rand_matrix(b, i);

				str_start = clock();
				strassen_pad(a, b, cross_over);
				str_end = clock();
				strs_spend += str_end-str_start;
			}
			

			strs_spend =strs_spend/5;
			// printf("strs_spend: %lf\tconv_spend: %lf\n", strs_spend, conv_spend);
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
