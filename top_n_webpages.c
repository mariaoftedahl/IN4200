#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void top_n_webpages(int N, double *scores, int n){

    //n = 3;
    
    int *result = (int*)calloc(N, sizeof(int));

    for (int i = 0; i < N; i++){
        result[i] = i;
    }

    int max_index;
    double max_score;

    for (int i = 0; i < n; i++){
        max_index = i;
        max_score = scores[i];
        for (int j = i+1; j < N; j++){
            if (scores[j] > max_score){
                max_index = j;
                max_score = scores[j];
                swap_d(&scores[i], &scores[max_index]);
                swap_i(&result[i], &result[max_index]);
            }
        }
    }

    printf("---------------Results--------------\n");
    printf("  Rank:    Webpage number:    Score:\n");
    for (int i = 0; i < n; i++){
        printf("%5d      %7d            %g\n", i+1, result[i], scores[i]);
    }

    free(result);

}