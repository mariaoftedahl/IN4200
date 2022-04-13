#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>


/*
  void function to implement the PageRank algorithm to calculate the scores of the webpages
*/


void PageRank_iterations(int N, int *row_ptr, int *col_idx, double *val, double d, double epsilon, double *scores){

    int iter_count = 0;         
    double diff = 1;            // making sure at least one iteration is done

    // finding dangling webpages and their indices

    int d_count = 0;
    int *D_temp = (int*)calloc(N, sizeof(int));
    int *D = (int*)calloc(N, sizeof(int));
    
    #pragma omp parallel for
    for (int i = 0; i < N; i++){
        D_temp[i] = 1;
    }

    #pragma omp parallel for
    for (int i = 0; i < row_ptr[N]; i++){
        D_temp[col_idx[i]] = 0;
    }

    for (int i = 0; i < N; i++){
        if (D_temp[i] == 1){
            D[d_count] = i;
            d_count += 1;
        }
    }

    printf("Number of dangling webpages: %d\n", d_count);
    free(D_temp);

    double temp_diff = 0;

    double score_factor_1 = (1.0 - d) / ((double) N);
    double W;

    double *Ax = (double*)calloc(N, sizeof(double));

    // intial guess for the iterative procedure
    #pragma omp parallel for
    for (int i = 0; i < N; i++){
        Ax[i] = 1.0 / (double) N;
    }

    double temp_scores[N];

    #pragma omp parallel for
    for (int i = 0; i < N; i++){
        temp_scores[i] = Ax[i];
    }

    while (epsilon < diff){
        
        diff = 0;

        // matrix multiplication in CRS format
        #pragma omp parallel for
        for (int i = 0; i < N; i++){
            Ax[i] = 0.0;
            for (int j = row_ptr[i]; j < row_ptr[i+1]; j++){
                Ax[i] += val[j] * temp_scores[col_idx[j]];
            }
        }

        // calculating the scalar value W
        W = 0.0;

        #pragma omp parallel for reduction(+: W)
        for (int i = 0; i < d_count; i++){
            W += temp_scores[D[i]];
        } 

        double score_factor_2 = d*W / ((double) N);
        double score_factor = score_factor_1 + score_factor_2;

        // updating the score
        #pragma omp parallel for reduction(max: diff)
        for (int i = 0; i < N; i++){        
            scores[i] = score_factor + d * Ax[i];

            // implementing stopping criterion
            temp_diff = fabs(temp_scores[i] - scores[i]);

            if (temp_diff > diff){
                diff = temp_diff;
            }

            temp_scores[i] = scores[i];

        }   // end for loop

        iter_count++;
 
    } // end while loop
    
   
    printf("Number of iterations until convergence: %d\n", iter_count);


    // freeing memory of temporary arrays
    free(D);
    free(Ax);
    
        
}