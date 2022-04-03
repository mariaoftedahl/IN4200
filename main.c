#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

void read_graph_from_file(char *filename, int *N, int **row_ptr, int **col_idx, double **val);
void PageRank_iterations(int N, int *row_ptr, int *col_idx, double *val, double d, double epsilon, double *scores);
void top_n_webpages(int N, double *scores, int n);

int main(int argc, char *argv[]) {

    int N = 0;                                              // number of nodes in webgraph
    char *filename = argv[1];                               // filename of file containing webgraph as input argument
    double d = atof(argv[2]); 
    double epsilon = atof(argv[3]);                         // epsilon input argument
    int n = atoi(argv[4]);                                  // n top webpages input argument
    double *scores = (double*)calloc(N, sizeof(double));    // allocating array for the scores of the webpages

    int *row_ptr; int *col_idx; double *val;                // arrays needed for matrix in CRS format

    clock_t begin = clock();

    // calling functions

    read_graph_from_file(filename, &N, &row_ptr, &col_idx, &val);
    PageRank_iterations(N, row_ptr, col_idx, val, d, epsilon, scores);
    top_n_webpages(N, scores, n);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Execution time: %f\n ", time_spent);

    // freeing memory
    free(row_ptr);
    free(col_idx);
    free(val);
    free(scores);

    return 0;
}