all: fibnum.c
	gcc -o fibnum fibnum.c
	./fibnum > fib.txt
