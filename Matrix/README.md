## SIMD  
Single Instruction Multiple Data, also known as SIMD, is one of the classifications of computing architecture that enables efficient execution of data-parallel tasks. This parallel processing technique applies one operation on multiple data elements simultaneously. In other words, it runs multiple data streams against an instruction stream, resulting in better performance. For example, it can operate an instruction on a vector of data that's a single unit, such as an array. In Pentium IV and later processors, that can boost the speed by a factor of two. Other SIMD instructions offer different features. Overall, it's very efficient in computing repetitive tasks, which makes it particularly applicable to media processing.
To compile a SIMD program, you can use gcc as usual with the compatible code. 

## OpenMP
OpenMP provides a portable API for developers of shared memory parallel applications. The API supports C/C++ and Fortran on a wide variety of architectures, such as Unix/Linux. It is designed for multi-processor/core machines. C/C++ openMp uses #prgama omp syntax with clauses to specify additional information with the directive. These directives enable the compiler to automatically parallelize the code for execution on multiple cores while also providing a level of control. OpenMP has three components. The first of which is a directive that specifies the parallel regions, work sharing, synchronization, data scope attributes, and orphaning. The second are the Environmental variables that control the number of threads, scheduling type, dynamic thread adjustment, and nested parallelism. Lastly, it has a runtime environment(APIs) that contains the number of threads, thread ID, dynamic thread adjustment, nested parallelism, timers, and locking. 
To compile an OpenMP program, you must include the -fopenmp compiler flag and omp library. 

## MPI  
MPI is a library and model for message-passing and distributed-memory computing. It defines a model of parallel computing where each parallel process has its local memory, and data must be explicitly shared by passing messages between processes. So, MPI provides a standardized way for processes running on multiple computers or nodes to communicate and exchange data in a parallel application. Using it allows programs to scale beyond the processors and shared memory of a single compute server to the distributed memory and processors of multiple compute servers combined. Generally, MPI is widely available on various programming languages and platforms, which makes it more versatile for large-scale data analytics and other compute-intensive tasks. 
All MPI programs need to have #include <mpi.h>. 
To compile an MPI program you must use the mpicc command and to run an MPI program use an mpirun or mpiexe command

## Comparision between SIMD, OMP, and MPI
Both SIMD, OMP, and MPI are parallel computing paradigms and models that allow
developers to perform parallelism in applications. SIMD, Single Instruction Multiple Data,
leverages the hardware component to process the same operation on multiple data elements
simultaneously. OMP utilizes shared memory systems to allow the developers to specify the code to run in parallel through directives. Those
directives give a level of control over how the compiler parallelizes the code. MPI allows
multiple independent processes to work simultaneously to communicate by sending and receiving messages. Those
processes are referred to together as a cluster or a network.  

As mentioned, SIMD, OMP, and MPI focus on different levels of parallel programming. SIMD
targets the data-level parallelism to process vectorized operations. OMP utilizes a shared
memory system to perform task-level parallelism. MPI is designed for a distributed system that
allows separated processes in the same network/cluster to communicate to perform large-scale
computing. Even though they all support parallel programming, they are ideals in different fields
depending on the environment and the task. Moreover, SIMD works with single-core while OMP
and MPI work with multi-core processors.

# Distributed parallel computing
## Explain the architecture of your solution and the variations of the algorithm you implemented.
Regarding distributed parallel computing, my solution architecture is to create a new .c file to run all the programs. For mmult, I directly use the solution provided by the lab, and mmult_simd is modified according to the requirements. It is a matrix multiplication algorithm that simulates the principles of SIMD. Then, these two files are compiled separately with or without the -O3 optimization, giving us the results for the first week.

Moving on to the second week, we modify the examples provided by the lab and lecture on vector and matrix multiplication to matrix-matrix multiplication. To modify this, we first need to understand the principles of vector-matrix multiplication. The example from the lecture works by creating multiple hosts and using a controller process to broadcast the vector to worker processes. Then, the controller process divides matrix a into nrows and sends each row to the worker processes for computation, while simultaneously receiving the results. After receiving the results, the controller process fills in the target c vector based on the returned tags.

Throughout this entire process, we only need to change the broadcasted vector to a matrix, and in the worker process, it is not just two vectors being multiplied (since each row of a sent over is just one row, so arow x b is vector multiplication, which doesn’t have space for optimization). Additionally, the worker process returns a column of answers, specifying which column it is in the tags. In the controller process, the algorithm for receiving results fills in c accordingly (which is the second algorithm that can be optimized). This is the main idea behind my MPI algorithm design.

Logically speaking, MPI should be very fast, significantly faster than -03simd, but it is not the case in the graph. I think one possibility is that my MPI algorithm design still has two places that can be optimized. One is in the controller process where the results are received. Since the worker process returns an array (a certain row of the result matrix), there may be room for optimization when filling the c matrix in the controller process. Moreover, in the worker process, an unoptimized matrix-vector multiplication is being performed, which I think is the most critical point. Perhaps there are other design methods, or adding OMP could make the worker process faster.

Of course, we can use MPI_scatter to distribute the matrix for fixed distribution computations, but I think it’s not very suitable when the number of server cores is unknown (even if we know the number of cores in the Chinook, Wolf123, and Cluster). However, we have ensured that our multiplication is precise. We have compared the results generated by each algorithm, and only after the comparison passed did we create the current graph.

