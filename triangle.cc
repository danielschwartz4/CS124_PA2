#include <iostream>
#include <vector>
#include "matrix.hh"
#include "matrix_mul.hh"
#include <algorithm>
#include <ctime>


int calc_diagonal(matrix *m){
  int rows = m->rows;
  int cols = m->cols;
  assert(rows == cols);
  int sum = 0;
  for(int i = 0; i < rows; i++)
    {
      sum+=m->mat[i][i];
    }
  int num_triangles = sum / 6;
  printf("num_triangles: %d\n", num_triangles);
  // std::cout << num_triangles;
  return num_triangles;
}

float expected_num_triangles(int n, float p){
  return n*(n-1)*(n-2)/6*pow(p, 3);
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
                // printf("r: %f", r/100);
                if (r/100 <= p)
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
  // print_matrix((char*) "m", m);
  
  return m;
}

int main(int argc, char const *argv[]){
  
  int n = atoi(argv[1]);
  float p = atof(argv[2]);
  int cross_over = 64;

  int num_triangles = 0;

  for (int i =0; i<5; i++){
    matrix* m = create_graph(p, n);

    matrix* a_squared = strassen_pad(m, m, cross_over);
    // print_matrix((char*) "s", a_squared);
    matrix* a_cubed = strassen_pad(a_squared,m, cross_over);
    // print_matrix((char*) "c", a_cubed);

    num_triangles +=calc_diagonal(a_cubed);
    free_matrix(a_squared);
    free_matrix(a_cubed);
    free_matrix(m);
  }
 
  printf("%f\t%d\t%f\n", p, (num_triangles)/5, expected_num_triangles(n,p));

}
