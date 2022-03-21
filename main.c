#include <stdio.h>
#include <stdlib.h>

void read_graph_from_file(char *filename, int *N, int **row_ptr, int **col_idx, double **val);
void PageRank_iterations(int N, int *row_ptr, int *col_idx, double *val, double d, double epsilon, double *scores);

int main(int argc, char *argv[]) {

    int N;                     // number of nodes in webgraph
    char *filename = argv[1];   // filename of file containing webgraph
    double d = 1.0;
    double epsilon;
    double *scores = (double*)calloc(N, sizeof(double));

    int *row_ptr; int *col_idx; double *val;


    read_graph_from_file(filename, &N, &row_ptr, &col_idx, &val);
    PageRank_iterations(N, row_ptr, col_idx, val, d, epsilon, scores);

    free(row_ptr);
    free(col_idx);
    free(val);

    return 0;
}