set terminal png size 800,600 
set output 'out.png'

# Key means label...
#set key inside bottom right
set xlabel 'Matrix size'
set ylabel 'Time (sec)'
set title 'Matrix multiplication speed on Wlofgang Cluster'
plot  "data.csv" using 2:2 title 'mmult' with linespoint, "data.csv" using 2:3 title 'mmultO3' with linespoint, "data.csv" using 2:4 title 'mmult_simd', "data.csv" using 2:5 title 'mmult_simdO3' with linespoint
