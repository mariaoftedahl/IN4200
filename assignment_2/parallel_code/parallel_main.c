#include "functions.h"

/* declarations of functions import_JPEG_file and export_JPEG_file */

void import_JPEG_file (const char* filename, unsigned char** image_chars,
                       int* image_height, int* image_width,
                       int* num_components);
void export_JPEG_file (const char* filename, const unsigned char* image_chars,
                       int image_height, int image_width,
                       int num_components, int quality);


int main(int argc, char *argv[]){

    int m, n, c;
    char *input_jpeg_filename = argv[1];
    char *output_jpeg_filename = argv[2];
    float kappa = atof(argv[3]);
    int iters = atoi(argv[4]);
    int my_m, my_n;
    int my_rank, num_procs;     // decided at runtime
    image u, u_bar;
    unsigned char *image_chars, *my_image_chars;

    MPI_Init(&argc, &argv);
    
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
   
    if (my_rank==0){
        import_JPEG_file(input_jpeg_filename, &image_chars, &m, &n, &c);
    }

    // Broadcast m and n to all processes

    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    /* 2D decomposition of the m x n pixels evenly among the MPI processes */

    MPI_Comm comm_cart;

    int dim[2], period[2], reorder, my_coord[2];
    dim[0] = 1; // x-direction
    dim[1] = num_procs; // y-direction
    period[0] = 0; // x direction
    period[1] = 0; // y direction
    reorder = 1;

    MPI_Cart_create(MPI_COMM_WORLD, 2, dim, period, reorder, &comm_cart);
    MPI_Comm_rank(comm_cart, &my_rank);
    MPI_Cart_coords(comm_cart, my_rank, 2, my_coord);

    int my_m_temp = m / num_procs;
    int rest = m % num_procs;

    if(rest != 0) my_m_temp++;

    int my_start = my_coord[1]*(my_m_temp);
    int my_stop = (my_coord[1]+1)*(my_m_temp);

    if(my_coord[1] == num_procs - 1) my_stop = m;

    my_m = my_stop - my_start;
    my_n = n;
    
    /* each process asks process 0 for a partitioned region */
    /* of image_chars and copy the values into u */
    
    // defining chunk size for image_chars to be divided in
    int chunk_size = my_m*my_n;

    // allocating my_image_chars
    my_image_chars = malloc(chunk_size*sizeof(my_image_chars));
    
    // gather chunk sizes in send_counts
    int *send_counts = malloc(num_procs*sizeof(*send_counts));
    MPI_Gather(&chunk_size, 1, MPI_INT, send_counts, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    // making displs array with indices of image_chars according to send_counts
    int *displs = malloc(num_procs*sizeof(*displs));

    for (size_t i = 0; i < num_procs; i++){
        displs[i] = i*send_counts[i];
    }

    // ask process 0 for chunk of image_chars using scatterv
    MPI_Scatterv(image_chars, send_counts, displs, MPI_UNSIGNED_CHAR, my_image_chars, chunk_size, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);

    allocate_image(&u, my_m, my_n);
    allocate_image(&u_bar, my_m, my_n);
    convert_jpeg_to_image(my_image_chars, &u);

    iso_diffusion_denoising_parallel(&u, &u_bar, kappa, iters, my_rank, num_procs);
    convert_image_to_jpeg(&u_bar, my_image_chars);
  
    // gathering chunks of my_image_chars (after denoising) in image_chars again
  
    MPI_Gatherv(my_image_chars, chunk_size, MPI_UNSIGNED_CHAR, image_chars, send_counts, displs, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);

    if (my_rank == 0) {
        export_JPEG_file(output_jpeg_filename, image_chars, m, n, c, 75);
        free(image_chars);
    }
    
    free(displs);
    free(send_counts);
    deallocate_image(&u);
    deallocate_image(&u_bar);

    MPI_Finalize();
    
    return 0;
}