#include <stdio.h>
#include <time.h>
#include <sys/times.h>
#include <stdlib.h>
#include <omp.h>
#include <mpi.h>

#include "mat.h"

#define min(x, y) ((x)<(y)?(x):(y))

int main(int argc, char* argv[])
{
    struct timespec start;
    struct timespec end;
    int nrows, ncols;
    double *a, *b, *c1,*c2,*c3,*c4,*c5, *c6;
    double *buffer, *result;
    int myid, numprocs;
    MPI_Status status;
    double starttime, endtime;
    int i, j, k, numsent, sender;
    double times1;
    double times2;
    double times3;
    double times4;
    double times5;
    double times6;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    
//        nrows = atoi(argv[1]);
//        ncols = nrows;


            FILE *fp = fopen("data.csv","w+");
            if(fp==NULL)
            {
                fprintf(stderr,"fopen() failed. \n");
                exit(EXIT_FAILURE);

            }
            //fprintf(fp,"size,mmult,mmultO3,mmult_simd,mmult_simdO3,mmult_mpi \n");
            fprintf(fp,"mmult_simdO3,mmult_omp,mmult_mpi \n");


     for(nrows = 100;nrows<=2000;nrows+=100)
     {

         ncols=nrows;
         a = (double*)malloc(sizeof(double) * nrows * ncols);
         b = (double*)malloc(sizeof(double) * nrows * ncols);
         c1 = (double*)malloc(sizeof(double) * nrows * ncols);
         c2 = (double*)malloc(sizeof(double) * nrows * ncols);
         c3 = (double*)malloc(sizeof(double) * nrows * ncols);
         c4 = (double*)malloc(sizeof(double) * nrows * ncols);
         c5 = (double*)malloc(sizeof(double) * nrows * ncols);
 	  c6 = (double*)malloc(sizeof(double) * nrows * ncols);

         buffer = (double*)malloc(sizeof(double) * ncols);
         result = (double*)malloc(sizeof(double) * ncols);
         if (myid == 0) {
             // Initialize matrices A and B

             a = gen_matrix(nrows, ncols);
             b = gen_matrix(ncols, ncols);
             // Here, you should fill a and b with your data
//             clock_gettime(CLOCK_REALTIME, &start);
//             mmult(c1,a,nrows,nrows,b,nrows,nrows);
//             clock_gettime(CLOCK_REALTIME, &end);
//             times1 = deltaTime(&start, &end);
//             printf("mmult: %d %f \n", nrows, times1);

//
             clock_gettime(CLOCK_REALTIME, &start);
             mmultO3(c2,a,nrows,nrows,b,nrows,nrows);
             clock_gettime(CLOCK_REALTIME, &end);
             times2 = deltaTime(&start, &end);
             printf("mmultO3: %d %f \n", nrows, times2);

             clock_gettime(CLOCK_REALTIME, &start);
             mmult_simd(c3,a,nrows,nrows,b,nrows,nrows);
             clock_gettime(CLOCK_REALTIME, &end);
             times3 = deltaTime(&start, &end);
             printf("mmult_simd: %d %f \n", nrows, times3);

             clock_gettime(CLOCK_REALTIME, &start);
             mmult_simdO3(c4,a,nrows,nrows,b,nrows,nrows);
             clock_gettime(CLOCK_REALTIME, &end);
             times4 = deltaTime(&start, &end);
             printf("mmult_simd03: %d %f \n",nrows, times4);

	     clock_gettime(CLOCK_REALTIME, &start);
             mmult_omp(c5,a,nrows,nrows,b,nrows,nrows);
             clock_gettime(CLOCK_REALTIME, &end);
             times5 = deltaTime(&start, &end);
             printf("mmult_omp: %d %f \n",nrows, times5);



             // Broadcast matrix B to all processes
             starttime = MPI_Wtime();
             MPI_Bcast(b, ncols*ncols, MPI_DOUBLE, 0, MPI_COMM_WORLD);



             // Send rows of A to worker processes
             numsent = 0;
             for (i = 1; i < min(numprocs, nrows); i++) {
                 for (j = 0; j < ncols; j++) {
                     buffer[j] = a[(i-1) * ncols + j];
                 }
                 MPI_Send(buffer, ncols, MPI_DOUBLE, i, i, MPI_COMM_WORLD);
                 numsent++;
             }

             for (i = 0; i < nrows; i++) {
                 MPI_Recv(result, ncols, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                 sender = status.MPI_SOURCE;
                 int row = status.MPI_TAG - 1;
                 for (j = 0; j < ncols; j++) {
                     c6[row*ncols + j] = result[j];
                 }

                 if (numsent < nrows) {
                     for (j = 0; j < ncols; j++) {
                         buffer[j] = a[numsent*ncols + j];
                     }
                     MPI_Send(buffer, ncols, MPI_DOUBLE, sender, numsent+1, MPI_COMM_WORLD);
                     numsent++;
                 } else {
                     MPI_Send(MPI_BOTTOM, 0, MPI_DOUBLE, sender, 0, MPI_COMM_WORLD);
                 }
             }
             endtime = MPI_Wtime();
             times6=endtime-starttime;
             printf("mmult_mpi: %d %f \n",nrows,times6);

             compare_matrices(c2,c3,nrows,nrows);
             compare_matrices(c2,c4,nrows,nrows);
             compare_matrices(c2,c5,nrows,nrows);
             compare_matrices(c2,c6,nrows,nrows);
             fprintf(fp,"%d,%lf,%lf,%lf,%lf, %lf\n",nrows,times2,times3,times4,times5, times6);
            //fprintf(fp,"%d,%lf,%lf, %lf\n",nrows,times4,times5, times6);


         } else {
             // Worker code
             MPI_Bcast(b, ncols*ncols, MPI_DOUBLE, 0, MPI_COMM_WORLD);
             while(1) {
                 MPI_Recv(buffer, ncols, MPI_DOUBLE, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                 if (status.MPI_TAG == 0) {
                     break;
                 }
                 int row = status.MPI_TAG - 1;

    		#pragma omp private(i, k) shared (result, buffer, b, ncols) for reduction(+:result)
                 for (i = 0; i < ncols; i++) {
                     result[i] = 0.0;
                     for (k = 0; k < ncols; k++) {
                         result[i] += buffer[k] * b[k*ncols + i];
                     }
                 }
                 MPI_Send(result, ncols, MPI_DOUBLE, 0, row+1, MPI_COMM_WORLD);
             }
         }
     }


        // If myid is 0, c now contains the result matrix

    

    MPI_Finalize();

    return 0;}
