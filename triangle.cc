#include <iostream>
#include <vector>
#include "matrix.hh"
#include "matrix.cc"
#include "matrix_mul.hh"
#include "matrix_mul.cc"
#include <algorithm>


int calc_diagonal(matrix *m){
	int col_idx = 0;
  int rows = m->rows;
  int cols = m->cols;
  assert(rows == cols);
  int sum = 0;
  for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            if (j == col_idx)
            {
                sum = m->mat[i][j] + sum;
            }
        }
    }
  int num_triangles = sum / 6;
  std::cout << num_triangles;
  return num_triangles;
}

matrix* create_graph(float p, int v){
  matrix* m = malloc_matrix(v,v,v);
  for(int i = 0; i < v; i++)
    {
        for(int j = 0; j < v; j++)
        {
            m->mat[i][j] = 2;
        }
    }
  int rand_seed = (unsigned) time(0);
  srand(rand_seed);
  float r = rand() % 100 + 1;
  for(int i = 0; i < v; i++)
    {
        for(int j = 0; j < v; j++)
        {
            if (i == j)
            {
                m->mat[i][j] = 0;
            }
            else if (m->mat[i][j] == 2)
            {
                float r = rand() % 100 + 1;
                if (r / 100 < p)
                {
                    m->mat[i][j] = 1;
                    m->mat[j][i] = 1;
                }
                else
                {
                    m->mat[i][j] = 0;
                    m->mat[j][i] = 0;
                }
            }
            else
            {
                m->mat[i][j] = m->mat[i][j];
            }
            
        }
    }
  print_matrix((char*) "m", m);
  
  return m;
}

int main(){
  // matrix* c = malloc_matrix(4,4,4);
  // matrix* a_cubed = malloc_matrix(4,4,4);
  matrix* m = create_graph(.05, 1024);

  // conventional(m, m, c);
  // print_matrix((char*) "s", c);
  // conventional(c, m, a_cubed);
  // print_matrix((char*) "c", a_cubed);

  matrix* a_squared = strassen_pad(m, m, 1024);
  print_matrix((char*) "s", a_squared);
  matrix* a_cubed = strassen_pad(m, a_squared, 1024);
  print_matrix((char*) "c", a_cubed);

  int num_triangles = calc_diagonal(a_cubed);
  std::cout << num_triangles << "\n";

  free_matrix(a_squared);
  free_matrix(a_cubed);
  free_matrix(m);
}
