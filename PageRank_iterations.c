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
    //double iter_diff = 1.0; // making sure at least one iteration is done
    double diff = 1;
    
    double *temp = (double*)calloc(N, sizeof(double));
    
    // Initial guess
    for (i = 0; i < N; i++)
    scores[i] = 1.0 / (double) N;

    // finding dangling nodes

    int d_count = 0;
    int *D_temp = (int*)calloc(N, sizeof(int));
    
    for (i = 0; i < N; i++){
        D_temp[i] = 1;
    }
        
    for (i = 0; i < row_ptr[N]; i++){
        D_temp[col_idx[i]] = 0;
    }

    int *D = (int*)calloc(N, sizeof(int));

    for (i = 0; i < N; i++)
    if (D_temp[i] == 1){
        D[d_count] = i;
        d_count++;
    }

    printf("Number of dangling webpages: %d\n", d_count);
    //printvec_i(D, d_count);

    double tmp_diff = 0;

    double *new_scores = (double*)calloc(N, sizeof(double));
    double *tmp;

    double score_factor_1 = (1.0 - d) / ((double) N);
    

    while (epsilon <= diff){

        diff = 0;

        double W = 0;
        
        for (i = 0; i < d_count; i++){
            W += scores[D[i]];
        }
        
        
        
        double score_factor_2 = d*W / ((double) N);
        double score_factor = score_factor_1 + score_factor_2;
        

        for (i = 0; i < N; i++) {

            new_scores[i] = 0.0;
            
            for (j = row_ptr[i]; j < row_ptr[i+1]; j++){
                new_scores[i] += d*val[j]*scores[col_idx[j]];
            }
            new_scores[i] += score_factor;
            
            tmp_diff = fabs(new_scores[i] - scores[i]);

            if (tmp_diff > diff){
                diff = tmp_diff;
            }
        }

        
        
        
        // swap pointers to scores and new_scores
        tmp = new_scores;
        new_scores = scores; // new_scores is set back to 1/N
        scores = tmp; // scores will be the previous scores calculated
        //printvec_d(scores, N);
        
        iter_count++;
        
    }
    
   
    printf("Number of iterations until convergence: %d\n", iter_count);

    free(new_scores);
    free(D);
        
}