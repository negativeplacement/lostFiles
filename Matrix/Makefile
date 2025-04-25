PGMS=mmult_omp_timing matrix_times_vector hello test_mmult mxv_omp_mpi mmult_mpi_omp compareTime message

all:	${PGMS}


mmult_simd.o: mmult_simd.c
	gcc -c  mmult_simd.c
mmult_simdO3.o: mmult_simdO3.c
	gcc -c -O3 mmult_simdO3.c

mmult_mpi_omp:		mmult.o mmultO3.o mmult_simd.o mmult_simdO3.o mmult_mpi_omp.o mat.c 
	mpicc -o mmult_mpi_omp -fopenmp mmult.o mmult_simdO3.o mmultO3.o mmult_simd.o mmult_mpi_omp.o mat.c


message:  mmult.c mat.c
	mpicc -O3 -o message message.c mmult.c mat.c
mmult_mpi_omp.o:	mmult_mpi_omp.c
	mpicc -c -fopenmp -O3 mmult_mpi_omp.c

compareTime: compareTime.o mmult_simd.o mmult_simdO3.o mmultO3.o mmult.o mat.o
	mpicc -fopenmp -O3 -o compareTime compareTime.o mmult.o -O3 mmultO3.o -O3 mmult_simdO3.o mmult_simd.o mat.o -fopenmp mmult_omp.o
compareTime.o:  compareTime.c
	mpicc -c -fopenmp -O3 compareTime.c

mmult_omp_timing:	mmult.o mmult_omp.o mmult_omp_timing.o mat.c
	gcc -o mmult -fopenmp -O3 mmult.o mmult_omp.o mmult_omp_timing.o mat.c -o mmult_omp_timing


mat.o:	mat.c
	gcc -c mat.c 

mmultO3.o: mmultO3.c
	gcc -c -O3 mmultO3.c

mmult.o:	mmult.c
	gcc -c mmult.c

mmult_omp.o:	mmult_omp.c
	gcc -c -O3 -fopenmp mmult_omp.c

mmult_omp_timing.o:	mmult_omp_timing.c
	gcc -c -O3 mmult_omp_timing.c

matrix_times_vector:	matrix_times_vector.c mat.c
	mpicc -O3 -o matrix_times_vector matrix_times_vector.c mat.c

hello:	hello.c
	mpicc -O3 -o hello hello.c

mxv_omp_mpi:	mxv_omp_mpi.c mat.c
	mpicc -fopenmp -O3 -o mxv_omp_mpi mxv_omp_mpi.c mat.c

test_mmult:	test_mmult.c mmult.c mat.c
	gcc test_mmult.c mmult.c mat.c -lm -o test_mmult

run_test_mmult: test_mmult
	./test_mmult

clean:
	rm -f *.o
	rm -f ${PGMS}
