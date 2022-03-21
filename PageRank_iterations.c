#include <stdlib.h>
#include <stdio.h>

//#include "methods.h"

/*
 * void function to read a webgraph from txt-file
 * int N:         
 * int *row_ptr:      
 * int *col_idx:
 * double *val:
 * double d:
 * double epsilon:
 * double *scores:
*/


void PageRank_iterations(int N, int *row_ptr, int *col_idx, double *val, double d, double epsilon, double *scores){

    int i, j, k;
    int N_iter = 5;     

    double *temp = (double*)calloc(N, sizeof(double));

    // Initial guess
    for (i = 0; i < N; i++)
    scores[i] = 1.0 / (double) N;

    printf("Initial guess:\n");
    printvec_d(scores,N);


    // Iterative procedure
    for (k = 0; k < N_iter; k++){
        printf("Iteration nr: %d\n", k+1);

        for (i = 0; i < N; i++){
            temp[i] = 0.0;
            for (j = row_ptr[i]; j < row_ptr[i+1]; j++){
                temp[i] += val[j]*scores[col_idx[j]];
            }
    
        }

        for(i = 0; i < N; i++){
            scores[i] = temp[i];
        }
        
        printvec_d(scores, N);
    }

    free(temp);

}