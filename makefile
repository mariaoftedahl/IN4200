all: compile run

compile:
	gcc main.c read_graph_from_file.c PageRank_iterations.c

run:
	./a.out simple_webgraph.txt

