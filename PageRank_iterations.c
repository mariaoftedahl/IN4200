#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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


void PageRank_iterations(int N, int *row_ptr, int *col_idx, double *val, double d, double epsilon, double *scores, int *D, int *D_count){

    int i, j, iter_count;
    double max_diff, diff;
    double iter_diff = 1.0; // making sure at least one iteration is done
    
    double *temp = (double*)calloc(N, sizeof(double));
    
    // Initial guess
    for (i = 0; i < N; i++)
    scores[i] = 1.0 / (double) N;

    // Iterative procedure
    while(iter_diff > epsilon){
        //printf("Iteration nr: %d\n", k+1);

        for (i = 0; i < N; i++){
            temp[i] = 0.0;
            for (j = row_ptr[i]; j < row_ptr[i+1]; j++){
                temp[i] += ((1 - d)/((double) N)) + d*val[j]*scores[col_idx[j]];
            }
    
        }

        for(i = 0; i < N; i++){
            diff = fabs(scores[i] - temp[i]);
            scores[i] = temp[i]; 
        }

        iter_diff = diff;
        printvec_d(scores, N);

        iter_count++;
    }

    printf("Number of iterations until convergence: %d\n", iter_count);

    free(temp);
    
    
}