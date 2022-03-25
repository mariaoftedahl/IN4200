#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//#include "methods.h"

/*
 * void function to rank the webpages
 * int N:         
 * int *row_ptr:      
 * int *col_idx:
 * double *val:
 * double d:
 * double epsilon:
 * double *scores:
*/


void PageRank_iterations(int N, int *row_ptr, int *col_idx, double *val, double d, double epsilon, double *scores){

    int i, j;
    int iter_count = 0;
    double diff;
    double iter_diff = 1.0; // making sure at least one iteration is done
    
    double *temp = (double*)calloc(N, sizeof(double));
    
    // Initial guess
    for (i = 0; i < N; i++)
    scores[i] = 1.0 / (double) N;

    
    int d_count = 0;
    int *D_temp = (int*)calloc(N, sizeof(int));

    // finding dangling nodes
    
    for (i = 0; i < N; i++){
        D_temp[i] = 1;
    }
        
    for (i = 0; i < row_ptr[N]; i++){
        D_temp[col_idx[i]] = 0;
    }

    int *D_final = malloc(N*sizeof(int));
    for (i = 0; i < N; i++)
    if (D_temp[i] == 1){
        D_final[d_count] = i;
        d_count++;
    }

    printf("Number of dangling webpages: %d\n", d_count);

    free(D_temp);

    //printvec_i(D_final, d_count);
    

    /*
        int W = 0;

        for (i = 0; i < d_count; i++){
            W += scores[D_final[i]];
        }

        double score_factor = (d*W) / ((double) N);
    */
   
    
    // Iterative procedure
    while(iter_diff > epsilon){
        
        for (i = 0; i < N; i++){
            temp[i] = 0.0;
            for (j = row_ptr[i]; j < row_ptr[i+1]; j++){
                temp[i] += ((1 - d)/((double) N)) + d*val[j]*scores[col_idx[j]];
                //temp[i] += ((1 - d)/((double) N)) + score_factor + d*val[j]*scores[col_idx[j]];
            }
    
        }
        
        for(i = 0; i < N; i++){
            diff = fabs(scores[i] - temp[i]);
            scores[i] = temp[i]; 
        }

        iter_diff = diff;
        //printvec_d(scores, N);

        iter_count++;
        
    }

    printf("Number of iterations until convergence: %d\n", iter_count);

    free(temp);
        
}