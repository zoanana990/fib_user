set xlabel 'numerical distribution'
set ylabel 'time(cycles)'
set title 'Fibonacci Number Iteration Method'
set term png enhanced font 'Verdana,10'
set output 'runtime.png'
set xrange [1:100]



plot [:][:]'./data/fibnum_iter_100_time.txt' using 1:2 with points title 'Number Iteration', \
'./data/fibstr_iter_100_time.txt' using 1:2 with points title 'String Iteration', \
'./data/fibstr_iter_100_kernel_time' using 1 with points title 'String Iteration in Kernel'
