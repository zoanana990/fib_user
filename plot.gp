set xlabel 'numerical distribution'
set ylabel 'time(cycles)'
set title 'Fibonacci Number Iteration Method'
set term png enhanced font 'Verdana,10'
set output 'runtime.png'
set xrange [1:300]



plot [:][:]'fibnum_iter_300_time.txt' using 1:2 with points title 'num', \
'fibstr_iter_300_time.txt' using 1:2 with points title 'str'
