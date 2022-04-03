# Mandatory assignment 1 in IN4200

This program contains three serial functions, in which the goal is to rank webpages from a webgraph using the PageRank algorithm. [read_graph_from_file.c](https://github.com/mariaoftedahl/IN4200/blob/main/read_graph_from_file.c) reads a text file that contains a webgraph and builds the corresponding hyperlink matrix in CRS format. [PageRank_iterations.c](https://github.com/mariaoftedahl/IN4200/blob/main/PageRank_iterations.c) uses the PageRank algorithm to find the score of each webpage. [top_n_webpages.c](https://github.com/mariaoftedahl/IN4200/blob/main/top_n_webpages.c) prints out the top webpages and their corresponding indices. 

The program takes four input arguments: 

* filename: webpgraph in txt-format
* d: damping constant
* epsilon: stopping criterion of the iterative process
* n: number of top webpages to be printed out

To compile the code in a LINUX terminal, use the following command

      $ gcc main.c read_graph_from_file.c PageRank_iterations.c top_n_webpages.c -fopenmp
      
To run the code, use the following command

      $./a.out 100nodes_graph.txt 0.85 1e-6 3
     
The makefile will compile and run the code with these settings by entering

      $ make
      
in the LINUX terminal.

In this compilation example, the file used is 100nodes_graph.txt, with damping constant d = 0.85, stopping criterion epsilon = 1e-6 and the output will give n = 3 top webpages. The code is parallelized using OpenMP, and the flag -fopenmp then needs to be included. With [100nodes_graph.txt](https://github.com/mariaoftedahl/IN4200/blob/main/100nodes_graph.txt) the output will look like this:

      Number of nodes: 100
      Number of links: 250
      Self links: 1
      Updated number of links: 249
      Number of dangling webpages: 5
      Number of iterations until convergence: 22
      -----------------Results----------------
        Rank:    Webpage number:    Score:
          1           64            0.0493431
          2           67            0.0381858
          3           26            0.0353179
      Execution time: 0.203125

Unfortunately, the code does not work for [web-stanford.txt](https://github.com/mariaoftedahl/IN4200/blob/main/web-stanford.txt). There is a segmentation fault which I do not understand where is coming from, and since the code works fine for both [100nodes_graph.txt](https://github.com/mariaoftedahl/IN4200/blob/main/100nodes_graph.txt) and [simple_webgraph.txt](https://github.com/mariaoftedahl/IN4200/blob/main/simple_webgraph.txt), it was hard to find the source. This also made it hard to figure out if the parallelization was implemented correctly. With only 100 nodes and 250 links, the program runs too fast to see if there was a speedup in the execution time due to the parallelization.
