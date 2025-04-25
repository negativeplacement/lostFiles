#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include "mat.h"

int mmultO3(double *c,
          double *a, int aRows, int aCols,
          double *b, int bRows, int bCols) {

    for(int i = 0; i < aRows; ++i) {
        for(int j = 0; j < bCols; ++j) {
            c[i * bCols + j] = 0;
            for(int k = 0; k < bCols; ++k) {
                c[i * bCols + j] += a[i * aCols + k] * b[k * bCols + j];
            }
        }
    }

    return 0;
}
