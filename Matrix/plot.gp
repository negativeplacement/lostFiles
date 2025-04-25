set datafile separator ","
set title "Algo Comparison"
set xlabel "Size"
set ylabel "Time (sec)"
set terminal pngcairo
set output 'output_graph.png'

plot "data.csv" using 1:2 with lines title "mmultO3" lt rgb "blue", \
     "data.csv" using 1:3 with lines title "mmult_simd" lt rgb "green", \
     "data.csv" using 1:4 with lines title "mmult_simdO3" lt rgb "yellow",\
     "data.csv" using 1:5 with lines title "mmult_omp" lt rgb "purple",	 \
     "data.csv" using 1:6 with lines title "mmult_mpi" lt rgb "black"	
