all: fibnum.c
	gcc -o fibnum fibnum.c
	./fibnum > fib
plot: 
	gnuplot plot.gp