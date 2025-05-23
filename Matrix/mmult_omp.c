#include "mat.h"

/**
 * An algorithm for matrix multiplication using OMP.
 *
 * @param c : the matrix in which to place the result of the matrix multiplication.
 * @param a : the first matrix.
 * @param aRows : the number of rows in a.
 * @param aCols : the number of columns in a.
 * @param b : the second matrix.
 * @param bRows : the number of rows in b.
 * @param bCols : the number of columns in b.
 * @return 0 if the matrix multiplication is successful.
 */


int mmult_omp(double *c,
              double *a, int aRows, int aCols,
              double *b, int bRows, int bCols)
{

    // Insert your code here
    int i, j, k;

    #pragma omp parallel for default(none) private(i, j, k) shared (a, b, c, aRows, aCols, bRows, bCols)
    for (i = 0; i < aRows; ++i)
    {
        for (j = 0; j < bCols; ++j)
        {
            c[i * bCols + j] = 0;
            for (k = 0; k < aCols; ++k)   // Use aCols for the inner loop
            {
                c[i * bCols + j] += a[i * aCols + k] * b[k * bCols + j];
            }
        }
    }


    return 0;
}

