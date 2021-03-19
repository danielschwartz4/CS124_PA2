#include <iostream>
#include <vector>


// I just initiated array size to a random number like 100 I need to figure out how to use pointers.
void conventional(int a[][100],
                  int b[][100],
                  int a_rows,
                  int a_cols,
                  int b_rows,
                  int b_cols,
                  int output[][100])
{
    int i, j, k;

    for(i = 0; i < a_rows; ++i)
    {
        for(j = 0; j < b_cols; ++j)
        {
            output[i][j] = 0;
        }
    }

    for (i = 0; i < a_rows; i++) {
        for (j = 0; j < b_cols; j++) {
            for (k = 0; k < a_cols; k++)
                output[i][j] += a[i][k] * b[k][j];
        }
    }
}