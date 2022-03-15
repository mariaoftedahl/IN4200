#include <stdio.h>
#include <stdlib.h>

void read_graph_from_file(char *filename, int *N, int **row_ptr, int **col_idx, double **val);

int main(int argc, char *argv[]) {

    int N;                     // number of nodes in webgraph
    char *filename = argv[1];   // filename of file containing webgraph

    int *row_ptr; int *col_idx; double *val;

    read_graph_from_file(filename, &N, &row_ptr, &col_idx, &val);

}