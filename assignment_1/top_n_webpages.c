#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

/*
    void function to find the n webpages with the highest score and their indices,
    and rank them in decreasing order
*/

void top_n_webpages(int N, double *scores, int n){
    
    int *result = (int*)calloc(N, sizeof(int)); 
    int max_index;
    double max_score;

    #pragma omp for
    for (int i = 0; i < N; i++){
        result[i] = i;
    }


    // sorting the webpages in decreasing order according to their score

    for (int i = 0; i < n; i++){

        max_index = i;
        max_score = scores[i];

        #pragma omp for
        for (int j = i + 1; j < N; j++){
            if (scores[j] > max_score){
                max_index = j;
                max_score = scores[j];

                double temp_1 = scores[i];
                scores[i] = scores[max_index];
                scores[max_index] = temp_1;

                int temp_2 = result[i];
                result[i] = result[max_index];
                result[max_index] = temp_2;
                
            }
        }
    }

    // output of the final result

    printf("-----------------Results----------------\n");
    printf("  Rank:    Webpage number:    Score:\n");
    for (int i = 0; i < n; i++){
        printf("%5d      %7d            %g\n", i+1, result[i], scores[i]);
    }

    free(result);

}