#include <stdlib.h>
#include <stdio.h>

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
    printf("Number of nodes: %d\n", *N);
    printf("Number of links: %d\n", links);


    // tried to skip the 4th line in the txt-file. didnt find out how to do this without assigning chars
    char text1[15], text2[15];
    fscanf(fp, "%*s %s %s", text1, text2);

    // allocating some temporary arrays
    int *row_count = (int*)calloc(*N, sizeof(int));
    int *temp_col = (int*)calloc(links, sizeof(int));
    int *temp_row = (int*)calloc(links, sizeof(int));


    // extracting the values needed from the txt.file
    int outgoing_links, ingoing_links, self_links;
    self_links = 0;
    for (int i = 0; i < links; i++){
        fscanf(fp, "%d %d", &outgoing_links, &ingoing_links);
        if (outgoing_links != ingoing_links){
            row_count[ingoing_links+1]++;               // needed for row_ptr
            temp_col[i] = outgoing_links;                // needed for col_idx
            temp_row[i] = ingoing_links;                 // needed for val
            
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
        (*row_ptr)[i+1] = count;
        //printf("Row_ptr_indices: %d\n", (*row_ptr)[i+1]);
    }

    links -= self_links;        // update number of links, subtracting if there are self-links

    int *row_idx = (int*)calloc(links, sizeof(int));        // array with ingoing links needed for sorting

    // adding the values to col_idx and row_idx before sorting

    for (int i = 0; i < links; i++){
        (*col_idx)[i] = temp_col[i];
        row_idx[i] = temp_row[i];
    }

    /* 
       Found the shell sort on programiz.com
       Tried to implement it according to https://www.programiz.com/dsa/shell-sort
    */

    int temp1, temp2, j, interval;
    for (interval = links/2; interval > 0; interval /= 2){
        for (int i = interval; i < links; i ++){
            temp1 = row_idx[i];
            temp2 = (*col_idx)[i];
            for (j = i; j >= interval && row_idx[j-interval] > temp1; j -= interval){
                row_idx[j] = row_idx[j-interval];
                (*col_idx)[j] = (*col_idx)[j-interval];
            }
        
        row_idx[j] = temp1;
        (*col_idx)[j] = temp2;

        }
        
    }

    // printing col_idx to check if it is in the right order. now they are in the wrong order (but better than initially:))
    for (int i = 0; i < links; i++){
        printf("col_idx: %d\n", (*col_idx)[i]);
    }
    
}
