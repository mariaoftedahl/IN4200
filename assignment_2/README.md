## Mandatory assignment 2 in IN4200

The goal of this assignment is the compilation of existing implementations of C functions as a stand-alone external library, and parallelization and MPI implementation of a numerical algorithm. The algorithm implemented is a simple denoising algorithm for grey-scale images. 

### Serial code

The [serial_code folder](https://github.com/mariaoftedahl/IN4200/tree/main/assignment_2/serial_code) contains the serial implementation of the algorithm, with a main program, a program containing the functions used, a header file, a Makefile, a noisy grey-scale image and an external library for reading and writing JPEG images (this is not included in the final delivery). The main program [serial_main.c](https://github.com/mariaoftedahl/IN4200/blob/main/assignment_2/serial_code/serial_main.c) takes four input arguments:

* input_jpeg_filename: greyscale image to be denoised in jpg-format
* output_jpeg_filename: chosen filename for denoised image in jpg-format
* kappa: scalar constant, 0.2 or below
* iters: number of iterations in the denoising algorithm

The main serial program calls a header file [functions.h](https://github.com/mariaoftedahl/IN4200/blob/main/assignment_2/serial_code/functions.h) which contains a data structure of an image related to denoising, declares the necessary functions and imports the necessary libraries. [functions.c](https://github.com/mariaoftedahl/IN4200/blob/main/assignment_2/serial_code/functions.c) contains all the functions used, including the denoising algorithm. 

When in the serial_code folder, the makefile will compile the code by entering

      $ make
      
in a LINUX terminal.

To execute the code, write

      $ ./serial_main mona_lisa_noisy.jpg mona_lisa_denoised.jpg 0.1 100
      
in the terminal.

In this compilation example, the input file used is mona_lisa_noisy.jpg, the output filename is mona_lisa_denoised.jpg with kappa = 0.1, and number of iterations iters = 100. To check the speedup due to the MPI implementation, the execution time of the denoising function will be printed, and the denoised image will be saved in the serial_code folder. The output will look like this:

      Execution time: 2.750000 seconds

To remove all the compiled object files from the source code, write 

      make clean
      
in the terminal.

### Parallel code

The same algorithm can be found in the [parallel_code folder](https://github.com/mariaoftedahl/IN4200/tree/main/assignment_2/parallel_code). The folder contains the same functions as the serial code folder, but with parallelization with MPI implemented. 

When in the parallel_code folder, the makefile will compile the code by entering

      $ make
      
in a LINUX terminal. MPI has to be installed for this to work.

To execute the code, write

      $ mpirun -np 2 ./parallel_main mona_lisa_noisy.jpg mona_lisa_denoised.jpg 0.1 100
      
in the terminal. The number 2 after the -np flag sets the number of processes to be used. To check the speedup due to the MPI implementation, the execution time of the denoising function will be printed together with the number of processes used, and the denoised image will be saved in the parallel_code folder. The output will look like this:

      Execution time with 2 processes: 1.680473 seconds
      
To remove all the compiled object files from the source code, write 

      make clean
      
in the terminal. 
      


