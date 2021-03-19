#include <iostream>
#include <matrix_mul.h>

int main(int argc, char const *argv[])
{  
    // auto t1 = std::chrono::high_resolution_clock::now();
    int flag =  atoi(argv[1]);
    int dim = atoi(argv[2]);
    int input_file = atoi(argv[3]);
    int mat1[4][4] = { { 1, 1, 1, 1 },
                       { 2, 2, 2, 2 },
                       { 3, 3, 3, 3 },
                       { 4, 4, 4, 4 } };
 
    int mat2[4][4] = { { 1, 1, 1, 1 },
                       { 2, 2, 2, 2 },
                       { 3, 3, 3, 3 },
                       { 4, 4, 4, 4 } };
    int new_matrix = conventional(mat1, mat2, 4, 4, 4, 4)
    std::cout << dim << std::endl;

}