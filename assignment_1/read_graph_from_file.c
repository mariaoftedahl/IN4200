#include <stdlib.h>
#include <stdio.h>

/*
    void function to read a webgraph from txt-file and build the corresponding hyperlink matrix in CRS format 
*/

void read_graph_from_file(char *filename, int *N, int **row_ptr, int **col_idx, double **val){

    int links;
    FILE *fp;
    char buff[255];

    int start, stop;

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
    int *col_count = (int*)calloc(*N, sizeof(int));
    int *temp_col = (int*)calloc(links, sizeof(int));
    int *temp_row = (int*)calloc(links, sizeof(int));
    int *temp = (int*)calloc(*N, sizeof(int));

    // allocating row_ptr, col_idx and val
    *row_ptr = (int*)calloc(*N+1, sizeof(int*));
    *col_idx = (int*)calloc(links, sizeof(int*));
    *val = (double*)calloc(links, sizeof(double*));

    int outgoing_links, ingoing_links, self_links;
    self_links = 0;

    for (int i; i < *N; i++){
        temp[i] = 0;
    }


    // extracting the values needed from the txt.file
    for (int i = 0; i < links; i++){
        fscanf(fp, "%d %d", &outgoing_links, &ingoing_links);
        
        if (outgoing_links != ingoing_links){
            temp[outgoing_links]++;
            row_count[ingoing_links+1]++;               
            col_count[outgoing_links]++;
            temp_col[i - self_links] = outgoing_links;               
            temp_row[i - self_links] = ingoing_links;                
            
        }
        else{
            self_links++;
        }
    
    }

    fclose(fp);  // closing the file

    printf("Self links: %d\n", self_links);

    links -= self_links;        // update number of links, subtracting if there are self-links

    printf("Updated number of links: %d\n", links);

    // filling row_ptr
    
    int count = 0;

    for (int i = 0; i < *N+1; i++){
        count += row_count[i];
        (*row_ptr)[i] = count;
    }
    
    // filling col_idx and val

    int *counter = (int*)calloc(*N, sizeof(int));

    for (int i = 0; i < *N; i++)
        counter[i] = 0;
    

    int idx;
    for (int i = 0; i < links; i++){   
        idx = (*row_ptr)[temp_row[i]] + counter[temp_row[i]];
        (*col_idx)[idx] = temp_col[i];

        counter[temp_row[i]] += 1;
        (*val)[idx] = 1.0/(col_count[temp_col[i]]);
    }

    // freeing memory of temporary arrays

    free(counter);
    free(row_count);
    free(col_count);
    free(temp);
    free(temp_col);
    free(temp_row);
  
}
