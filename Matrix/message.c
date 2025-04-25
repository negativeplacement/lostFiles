#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#define min(x, y) ((x)<(y)?(x):(y))

#include "mat.h"

int main(int argc, char* argv[])
{
    int nrows, ncols;
    double *aa;	/* the A matrix */
    double *bb;	/* the B matrix */
    double *cc1;	/* A x B computed using the omp-mpi code you write */
    double *cc2;	/* A x B computed using the conventional algorithm */
    int myid, numprocs;
    double starttime, endtime;
    double mmultStarttime, mmultEndtime;
    MPI_Status status;
    double *buffer, ans;
    int i, j, sender;
    int anstype, row;
    int numsent = 0;
    /* insert other global variables here */

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    if (argc > 1) {
        nrows = atoi(argv[1]);
        ncols = nrows;
        
        if (myid == 0) {
            // Controller Code goes here
            aa = gen_matrix(nrows, ncols);
            bb = gen_matrix(ncols, nrows);
            cc1 = (double*)malloc(sizeof(double) * nrows * nrows);
	    buffer = (double*)malloc(sizeof(double)* ncols); 
            starttime = MPI_Wtime();
            MPI_Bcast(bb, ncols * nrows, MPI_DOUBLE, 0, MPI_COMM_WORLD);
            /* Insert your controller code here to store the product into cc1*/
            int rows_per_process = (numprocs > 1) ? nrows / (numprocs - 1) : nrows;
            int remainder = nrows % (numprocs - 1);

            for (i = 1; i < numprocs; i++) {
                int local_rows = (i <= remainder) ? rows_per_process + 1 : rows_per_process;
                for (j = 0; j < ncols; j++) {
                    buffer[j] = aa[(i - 1) * rows_per_process * ncols + j];
                }
                MPI_Send(buffer, ncols, MPI_DOUBLE, i, local_rows, MPI_COMM_WORLD);
                numsent++;
            }

            for (i = 1; i < numprocs; i++) {
                int local_rows = (i <= remainder) ? rows_per_process + 1 : rows_per_process;
                MPI_Recv(&ans, 1, MPI_DOUBLE, i, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                anstype = status.MPI_TAG;
                cc1[anstype - 1] = ans;

                if (numsent < nrows) {
                    for (j = 0; j < ncols; j++) {
                        buffer[j] = aa[numsent * ncols + j];
                    }
                    MPI_Send(buffer, ncols, MPI_DOUBLE, i, numsent + 1, MPI_COMM_WORLD);
                    numsent++;
                }
            }
           
            endtime = MPI_Wtime();
            printf("MPI-OMP Elapsed time: %f seconds\n", (endtime - starttime));
            cc2  = malloc(sizeof(double) * nrows * nrows);
	    mmultStarttime = MPI_Wtime();
            mmult(cc2, aa, nrows, ncols, bb, ncols, nrows);
	    mmultEndtime = MPI_Wtime();
	    printf("MMult Elapsed time: %f seconds\n", (mmultEndtime - mmultStarttime));
            compare_matrices(cc2, cc1, nrows, nrows);
        } else {
            // Worder code goes here
	    MPI_Bcast(bb, ncols * nrows, MPI_DOUBLE, 0, MPI_COMM_WORLD);

            int local_rows = (myid <= nrows) ? 1 : 0;
            while (local_rows > 0) {
                MPI_Recv(buffer, ncols, MPI_DOUBLE, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                if (status.MPI_TAG == 0) {
                    break;
                }
                row = status.MPI_TAG;
                ans = 0.0;


                for (j = 0; j < ncols; j++) {
                    ans += buffer[j] * bb[j * ncols + row - 1];
                }
                MPI_Send(&ans, 1, MPI_DOUBLE, 0, row, MPI_COMM_WORLD);
                local_rows--;
            }
            free(aa);
            free(bb);
            free(cc1);
            free(buffer);
          }
    } else {
        fprintf(stderr, "Usage matrix_times_vector <size>\n");
    }
    MPI_Finalize();
    return 0;
}