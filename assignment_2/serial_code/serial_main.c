#include "functions.h"
#include <time.h>

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
    image u, u_bar;
    unsigned char *image_chars;


    // importing image
    import_JPEG_file(input_jpeg_filename, &image_chars, &m, &n, &c);

    // allocating image arrays
    allocate_image(&u, m, n);
    allocate_image(&u_bar, m, n);

    // converting image from jpeg (1D array) to 2D array
    convert_jpeg_to_image(image_chars, &u);

    clock_t begin = clock();
    // denoising algorithm
    iso_diffusion_denoising (&u, &u_bar, kappa, iters);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", time_spent);

    // converting image back to jpg format
    convert_image_to_jpeg(&u_bar, image_chars);
    // exporting denoised image to .jpg file
    export_JPEG_file(output_jpeg_filename, image_chars, m, n, c, 75);

    // freeing memory
    deallocate_image(&u);
    deallocate_image(&u_bar);

    return 0;
}