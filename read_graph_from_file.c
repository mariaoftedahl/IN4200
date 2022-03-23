#include <stdlib.h>
#include <stdio.h>
#include <math.h>



#include "methods.h"

/*
 * void function to read a webgraph from txt-file
 * char *filename: 
 * int *N:        
 * int **row_ptr:      
 * int **col_idx:
 * double **val:
*/

void read_graph_from_file(char *filename, int *N, int **row_ptr, int **col_idx, double **val){

    int links;
    FILE *fp;
    char buff[255];

    size_t start, stop;

    if (filename == NULL){
        printf("Provide filename.\n");
        exit(1);
    }

    fp = fopen(filename, "r");      // opening the txt-file

    // reading/skipping the first two lines of the txt-file
    fgets(buff, 255, (FILE*)fp);
    fgets(buff, 255, (FILE*)fp);

    // extracting the number of webpages (nodes)
    fscanf(fp, "%*s %*s %d %*s %d", N, &links);
    //printf("Number of nodes: %d\n", *N);
    //printf("Number of links: %d\n", links);


    // tried to skip the 4th line in the txt-file. didnt find out how to do this without assigning chars
    char text1[15], text2[15];
    fscanf(fp, "%*s %s %s", text1, text2);

    // allocating some temporary arrays
    int *row_count = (int*)calloc(*N, sizeof(int));
    int *col_count = (int*)calloc(*N, sizeof(int));
    int *temp_col = (int*)calloc(links, sizeof(int));
    int *temp_row = (int*)calloc(links, sizeof(int));
    int *temp = (int*)calloc(*N, sizeof(int));


    // extracting the values needed from the txt.file
    int outgoing_links, ingoing_links, self_links;
    self_links = 0;
    for (int i; i < *N; i++){
        temp[i] = 0;
    }
    for (int i = 0; i < links; i++){
        fscanf(fp, "%d %d", &outgoing_links, &ingoing_links);
        if (outgoing_links != ingoing_links){
            temp[outgoing_links]++;
            row_count[ingoing_links+1]++;               // needed for row_ptr
            col_count[outgoing_links]++;
            temp_col[i - self_links] = outgoing_links;                // needed for col_idx
            temp_row[i - self_links] = ingoing_links;                 // needed for val
            
        }
        else{
            self_links++;
        }

    }
    fclose(fp);  // closing the file


    // allocating row_ptr, col_idx and val

    *row_ptr = (int*)calloc(*N+1, sizeof(int*));
    *col_idx = (int*)calloc(links, sizeof(int*));
    *val = (double*)calloc(links, sizeof(double*));

    // filling row_ptr

    int count = 0;

    for (int i = 0; i < *N+1; i++){
        count += row_count[i];
        (*row_ptr)[i] = count;
    }

    links -= self_links;        // update number of links, subtracting if there are self-links
    
    sort_inplace(temp_row, temp_col, links);
    for (size_t i = 0; i < *N; i++) {
        start = (*row_ptr)[i], stop = (*row_ptr)[i+1];
        sort_inplace(&(temp_col[start]), &(temp_row[start]), stop - start);
    }

    
    *col_idx = temp_col;

    for (int i = 0; i < links; i++)
        (*val)[i] = 1.0 / (double) temp[(*col_idx)[i]];

    //printvec_d(*val, links);
    //printvec_i(*col_idx, links);
    //printvec_i(*row_ptr, *N+1);

  
    
}
