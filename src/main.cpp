#include "World_serial.h"
#include "World_pthread.h"
#include "World_openmp.h"
#include "World_mpi.h"
#include "World_cuda.h"
#include "Life_serial.h"
#include "Life_pthread.h"
#include "Life_openmp.h"
#include "Life_mpi.h"
#include "Life_cuda.h"
#include "GLScene.h"

#include <iostream>
#include "time.h"

using std::malloc;
using std::cout;
using std::endl;

int main()
{
	// printf("Serial Time: %.2f ms\n", Serial_test());
	printf("Pthread Time: %.2f ms\n", Pthread_test());
	// printf("OpenMP Time: %.2f ms\n", OpenMP_test());
	// printf("MPI Time: %.2f ms\n", MPI_test());
	printf("CUDA Time: %.2f ms\n", CUDA_test());
}
