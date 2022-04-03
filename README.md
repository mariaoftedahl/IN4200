# Mandatory assignment 1 in IN4200

This program contains three serial functions, in which the goal is to rank webpages from a webgraph using the PageRank algorithm. [read_graph_from_file.c](https://github.com/mariaoftedahl/IN4200/blob/main/read_graph_from_file.c) reads a text file that contains a webgraph and builds the corresponding hyperlink matrix in CRS format. [PageRank_iterations.c](https://github.com/mariaoftedahl/IN4200/blob/main/PageRank_iterations.c) uses the PageRank algorithm to find the score of each webpage. [top_n_webpages.c](https://github.com/mariaoftedahl/IN4200/blob/main/top_n_webpages.c) prints out the top webpages and their corresponding indices. 

The program takes four input arguments: 

* n: number of top webpages


