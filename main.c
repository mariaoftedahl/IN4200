#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
    The program now works for all files, just remember to change the value of d and epsilon
    Need to make W
    Make the top_n_webpages function
    Parallelize the code
    Fix the input arguments
*/

void read_graph_from_file(char *filename, int *N, int **row_ptr, int **col_idx, double **val);
void PageRank_iterations(int N, int *row_ptr, int *col_idx, double *val, double d, double epsilon, double *scores);
//void top_n_webpages(int N, double *scores, int n);

int main(int argc, char *argv[]) {

    int N = 0;                     // number of nodes in webgraph
    int n = 0;
    char *filename = argv[1];   // filename of file containing webgraph
    double d = 0.85;
    //double d = 1.0; //for simple webgraph
    //double epsilon = atof(argv[2]);
    double epsilon = 1e-06;
    double *scores = (double*)calloc(N, sizeof(double));

    int *row_ptr = NULL; int *col_idx = NULL; double *val = NULL;


    read_graph_from_file(filename, &N, &row_ptr, &col_idx, &val);
    PageRank_iterations(N, row_ptr, col_idx, val, d, epsilon, scores);
    //top_n_webpages(N, scores, n);

    free(row_ptr);
    free(col_idx);
    free(val);
    free(scores);

    return 0;
}