#include <iostream>
#include <fstream>
#include "matrix.hh"
#include "matrix_mul.hh"

void fill_matrix_from_file(std::ifstream &infile, matrix* m, int n){
	int val;
	for (int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			infile>>val;
			m->mat[i][j] = val;
		}
	}
}

int main(int argc, char const *argv[])
{  
    int flag =  atoi(argv[1]);
    (void) flag;
    int n = atoi(argv[2]);
   	std::ifstream infile(argv[3]);

    matrix* a = malloc_matrix(n, n, n);
    fill_matrix_from_file(infile, a, n);
    matrix* b = malloc_matrix(n, n, n);
    fill_matrix_from_file(infile, b, n);
    int cross_over =64;
    matrix* c = strassen_pad(a, b, cross_over);
    for(int i=0; i<n; i++){
    	for(int j=0; j<n; j++){
    		printf("%d\n", c->mat[i][j]);
    	}
    }

    free_matrix(a);
    free_matrix(b);
    free_matrix(c);

}