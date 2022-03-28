all: compile run

compile:
	gcc *.c -fopenmp

run:
	./a.out test.txt 0.000001 3

