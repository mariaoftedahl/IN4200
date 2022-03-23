#include <stdio.h>
#include <stdlib.h>
#include <math.h>



void read_graph_from_file(char *filename, int *N, int **row_ptr, int **col_idx, double **val);
void PageRank_iterations(int N, int *row_ptr, int *col_idx, double *val, double d, double epsilon, double *scores);
//void top_n_webpages(int N, double *scores, int n);

int main(int argc, char *argv[]) {

    int N;                     // number of nodes in webgraph
    int n;
    char *filename = argv[1];   // filename of file containing webgraph
    double d = 1.0;
    double epsilon = 0.000001;
    double *scores = (double*)calloc(N, sizeof(double));

    int *row_ptr; int *col_idx; double *val;


    read_graph_from_file(filename, &N, &row_ptr, &col_idx, &val);
    PageRank_iterations(N, row_ptr, col_idx, val, d, epsilon, scores);
    //top_n_webpages(N, scores, n);

    free(row_ptr);
    free(col_idx);
    free(val);

    return 0;
}