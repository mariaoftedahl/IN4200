all: compile run

compile:
	gcc main.c read_graph_from_file.c PageRank_iterations.c top_n_webpages.c

run:
	./a.out test.txt 0.000001 5

