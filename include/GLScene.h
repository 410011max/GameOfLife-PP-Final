#include "Life_serial.h"
#include "Life_pthread.h"
#include "Life_openmp.h"
#include "Life_mpi.h"
#include "Life_cuda.h"
#include <ctime>

double Serial_test();
double Pthread_test();
double OpenMP_test();
double MPI_test();
double CUDA_test();
