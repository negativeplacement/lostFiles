/**
 * Incomplete program to multiply a matrix times a matrix using both
 * MPI to distribute the computation among nodes and OMP
 * to distribute the computation among threads.
 */

#include "omp.h"
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#define min(x, y) ((x)<(y)?(x):(y))

#include "mat.h"

int main(int argc, char* argv[])
{
    struct timespec start;
    struct timespec end;
    int nrows, ncols;
    double *a, *b, *c;
    double *buffer, *result;
    int myid, numprocs;
    MPI_Status status;
    double starttime, endtime;
    int i, j, k, numsent, sender;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    if (argc > 2)
    {
        Matrix m1 = {.path = argv[1]};
        Matrix m2 = {.path = argv[2]};

        a = read_matrix_from_file(&m1);
        b = read_matrix_from_file(&m2);

        if (m1.ncols != m2.nrows)
        {
            fprintf(stderr, "Dimensions doesn't match, a = %d x %d, b = %d x %d\n", m1.nrows, m1.ncols, m2.nrows, m2.ncols);
            exit(EXIT_FAILURE);
        }

        c = (double *) malloc (sizeof(double) * m1.nrows * m2.ncols);

        buffer = (double*)malloc(sizeof(double) * m1.ncols);
        result = (double*)malloc(sizeof(double) * m2.ncols);

        nrows = m1.nrows;
        ncols = m2.ncols;

        if (myid == 0)
        {
            // Broadcast matrix B to all processes
            starttime = MPI_Wtime();
            MPI_Bcast(b, m2.nrows*ncols, MPI_DOUBLE, 0, MPI_COMM_WORLD);

            // Send rows of A to worker processes
            numsent = 0;
            for (i = 1; i < min(numprocs, nrows); i++)
            {
                for (j = 0; j < m1.ncols; j++)
                {
                    buffer[j] = a[(i-1) * m1.ncols + j];
                }
                MPI_Send(buffer, m1.ncols, MPI_DOUBLE, i, i, MPI_COMM_WORLD);
                numsent++;
            }

            for (i = 0; i < nrows; i++)
            {
                MPI_Recv(result, ncols, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                sender = status.MPI_SOURCE;
                int row = status.MPI_TAG - 1;
                for (j = 0; j < ncols; j++)
                {
                    c[row*ncols + j] = result[j];
                }
                if (numsent < nrows)
                {
                    for (j = 0; j < m1.ncols; j++)
                    {
                        buffer[j] = a[numsent*m1.ncols + j];
                    }
                    MPI_Send(buffer, m1.ncols, MPI_DOUBLE, sender, numsent+1, MPI_COMM_WORLD);
                    numsent++;
                }
                else
                {
                    MPI_Send(MPI_BOTTOM, 0, MPI_DOUBLE, sender, 0, MPI_COMM_WORLD);
                }
            }
            endtime = MPI_Wtime();

            FILE *res = fopen("result.txt", "w+");
            if(res == NULL)
            {
                fprintf(stderr, "Unable to open file at path '%s'\n", "result.txt");
                exit(EXIT_FAILURE);
            }
            fprintf(res, "%d %d\n", nrows, ncols);
            for (int i = 0; i < nrows; i++)
            {
                for (int j = 0; j < m2.ncols; j++)
                {
                    fprintf(res, "%5lf ", c[m2.ncols * i + j]);
                }
                fputs("\n", res);
            }

            double *c1 = (double*) malloc(sizeof(double) * nrows * ncols);
            mmult(c1, a, m1.nrows, m1.ncols, b, m2.nrows, m2.ncols);
            compare_matrices(c, c1, nrows, ncols);

            fclose(res);

            free(a);
            free(b);
            free(c);
            free(buffer);
            free(result);

            for (i = 1; i < numprocs; i++)
            {
                MPI_Send(MPI_BOTTOM, 0, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
            }
        }
        else
        {
            // Worker code
            MPI_Bcast(b, m2.nrows*ncols, MPI_DOUBLE, 0, MPI_COMM_WORLD);
            while(1)
            {
                MPI_Recv(buffer, m1.ncols, MPI_DOUBLE, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                if (status.MPI_TAG == 0)
                {
                    break;
                }
                int row = status.MPI_TAG - 1;
    		#pragma omp private(i, k) shared (result, buffer, b, ncols) for reduction(+:result)
                for (i = 0; i < ncols; i++)
                {
                    result[i] = 0.0;
                    for (k = 0; k < ncols; k++)
                    {
                        result[i] += buffer[k] * b[k*ncols + i];
                    }
                }
                MPI_Send(result, ncols, MPI_DOUBLE, 0, row+1, MPI_COMM_WORLD);
            }
        }
        // If myid is 0, c now contains the result matrix
    }
    else
    {
        fprintf(stderr, "Usage: matrix_multiply <size>\n");
    }

    MPI_Finalize();

    return 0;
}

