#ifndef MAT_H
#define MAT_H

typedef struct mStruct {
	char *path;
	int nrows;
	int ncols;
} Matrix;


double *gen_matrix(int n, int m);
int compare_matrices(double* a, double* b, int nRows, int nCols);
double *read_matrix_from_file(Matrix *file);
void print_matrix(double *a, int nrows, int ncols);
double deltaTime(struct timespec *start, struct timespec *end);

int mmult(double *c, 
          double *a, int aRows, int aCols, 
          double *b, int bRows, int bCols);
int mmultO3(double *c,
          double *a, int aRows, int aCols,
          double *b, int bRows, int bCols);
int mmult_simd(double *c,
		double *a, int aRows, int aCals,
		double *b, int bRows, int bCols);

int mmult_simdO3(double *c,
               double *a, int aRows, int aCals,
               double *b, int bRows, int bCols);


int mmult_omp(double *c,
		      double *a, int aRows, int aCols,
		      double *b, int bRows, int bCols);

#endif
