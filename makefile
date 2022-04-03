all: compile run

compile:
	gcc main.c read_graph_from_file.c PageRank_iterations.c top_n_webpages.c -fopenmp

run:
	./a.out 100nodes_graph.txt 0.85 1e-6 3

