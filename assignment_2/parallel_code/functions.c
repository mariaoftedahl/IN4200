#include "functions.h"


/*
    Swap two pointers
*/

void swap(void** a, void** b) {
    void* temp = *a;
    *a = *b;
    *b = temp;
}

/*
    Allocate 2D array image_data inside u, when m and n are given as input. 
*/
void allocate_image(image *u, int m, int n){
    u->m = m;
    u->n = n;
    
    u->image_data = malloc(m * sizeof *u->image_data);
    (u->image_data)[0] = malloc(m*n * sizeof (u->image_data)[0]);
    
    for (size_t i = 1; i < m; i++) {
        (u->image_data)[i] = &((u->image_data)[0][i*n]);
    }
}
   

/*
    Free storage used by the 2D array image_data inside u
*/
void deallocate_image(image *u){
    
    
    free(u->image_data[0]);
    free(u->image_data);
    
}

/*
    Convert jpg to image
*/

void convert_jpeg_to_image(const unsigned char* image_chars, image *u){

    // Fill up image_data with image_chars
    
    for (size_t i = 0; i < u->m; i++){
        for (size_t j = 0; j < u->n; j++){
            u->image_data[i][j] = image_chars[i*u->n + j];
        }
    }
    
}

/*
    Convert image to jpg
*/

void convert_image_to_jpeg(const image *u, unsigned char* image_chars){

    for (size_t i = 0; i < u->m; i++){
        for (size_t j = 0; j < u->n; j++){
            image_chars[i*u->n + j] = u->image_data[i][j];
        }
    }

}

/*
    Denoising algorithm with MPI communcation calls
*/

void iso_diffusion_denoising_parallel(image *u, image *u_bar, float kappa, int iters, int my_rank, int num_procs){
    
    // Boundary conditions
    // Each process initializes u_bar
    
    for(size_t i = 0; i < u->m; i++){
        u_bar->image_data[i][0] = u->image_data[i][0];
        u_bar->image_data[i][u->n-1] = u->image_data[i][u->n-1];
    }

    for(size_t j = 0; j < u->n; j++){
        u_bar->image_data[0][j] = u->image_data[0][j];
        u_bar->image_data[u->m-1][j] = u->image_data[u->m-1][j];
    }

    MPI_Status s;

    int odd = my_rank%2 != 0;

    float *topbuf = malloc(u->n*sizeof *topbuf); // buffer for top part of image-chunk
    float *botbuf = malloc(u->n*sizeof *botbuf); // buffer for bottom part of image-chunk

    for (size_t iter = 1; iter < iters; iter++){
        
        // communication in vertical direction

        if (odd) {

            // send and receive top
            topbuf = u->image_data[0];
            MPI_Recv(topbuf, u->n, MPI_FLOAT, my_rank-1, 0, MPI_COMM_WORLD, &s);
            MPI_Send(topbuf, u->n, MPI_FLOAT, my_rank-1, 0, MPI_COMM_WORLD);
            u->image_data[1] = topbuf;

            // send and receive bottom
            if (my_rank != num_procs-1){
                botbuf = u->image_data[u->m - 2];
                MPI_Send(botbuf, u->n, MPI_FLOAT, my_rank+1, 0, MPI_COMM_WORLD);
                MPI_Recv(botbuf, u->n, MPI_FLOAT, my_rank+1, 0, MPI_COMM_WORLD, &s);
                u->image_data[u->m - 1] = botbuf;
            }

        } else { // even 
            // send and receive bottom
            if (my_rank != num_procs-1){
                botbuf = u->image_data[u->m - 2];
                MPI_Send(botbuf, u->n, MPI_FLOAT, my_rank+1, 0, MPI_COMM_WORLD);
                MPI_Recv(botbuf, u->n, MPI_FLOAT, my_rank+1, 0, MPI_COMM_WORLD, &s);
                u->image_data[u->m - 1] = botbuf;
            }

            // send and receive top
            if (my_rank != 0){ // since my_rank-1 does not exist for my_rank=0
                topbuf = u->image_data[0];
                MPI_Recv(topbuf, u->n, MPI_FLOAT, my_rank-1, 0, MPI_COMM_WORLD, &s);
                MPI_Send(topbuf, u->n, MPI_FLOAT, my_rank-1, 0, MPI_COMM_WORLD);
                u->image_data[1] = topbuf;

            }

        }
        
        // denoising algorithm
        for (size_t i = 1; i < u->m-1; i++) { 
            for (size_t j = 1; j < u->n-1; j++) {
                u_bar->image_data[i][j] = u->image_data[i][j] + kappa * (u->image_data[i+1][j] + 
                                        u->image_data[i-1][j] - 4*u->image_data[i][j] +
                                        u->image_data[i][j+1] + u->image_data[i][j-1]); 
            }
        }
        swap((void*)&u, (void*)&u_bar);
    } // end iterations
    swap((void*)&u, (void*)&u_bar); // swapping back since it should not be done on last iteration

}

