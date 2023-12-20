#include "Benchmark.h"

const int size = 500;
const int itration = 1000; 
Life_serial* life_serial = new Life_serial(size, size);
Life_pthread* life_pthread = new Life_pthread(size, size);
Life_openmp* life_openmp = new Life_openmp(size, size);
Life_mpi* life_mpi = new Life_mpi(size, size);
Life_cuda* life_cuda = new Life_cuda(size, size);

double Serial_test()
{
    life_serial->~Life_serial();
    life_serial = new Life_serial(size, size);

    for (int i = 0; i < 0.6 * size * size; i++)
    {
        int x = rand() % size;
        int y = rand() % size;
        life_serial->setLife(x, y, 1);
    }

    double start = static_cast<double>(clock()) / CLOCKS_PER_SEC;
    for (int i = 0; i < itration; i++) life_serial->update();
    double end = static_cast<double>(clock()) / CLOCKS_PER_SEC;
    return (end - start) * 1000;
}

double Pthread_test()
{
    life_pthread->~Life_pthread();
    life_pthread = new Life_pthread(size, size);

    for (int i = 0; i < 0.6 * size * size; i++)
    {
        int x = rand() % size;
        int y = rand() % size;
        life_pthread->setLife(x, y, 1);
    }

    double start = static_cast<double>(clock()) / CLOCKS_PER_SEC;
    for (int i = 0; i < itration; i++) life_pthread->update();
    double end = static_cast<double>(clock()) / CLOCKS_PER_SEC;
    return (end - start) * 1000;
}

double OpenMP_test()
{
    life_openmp->~Life_openmp();
    life_openmp = new Life_openmp(size, size);

    for (int i = 0; i < 0.6 * size * size; i++)
    {
        int x = rand() % size;
        int y = rand() % size;
        life_openmp->setLife(x, y, 1);
    }

    double start = static_cast<double>(clock()) / CLOCKS_PER_SEC;
    for (int i = 0; i < itration; i++) life_openmp->update();
    double end = static_cast<double>(clock()) / CLOCKS_PER_SEC;
    return (end - start) * 1000;
}

double MPI_test()
{
    life_mpi->~Life_mpi();
    life_mpi = new Life_mpi(size, size);

    for (int i = 0; i < 0.6 * size * size; i++)
    {
        int x = rand() % size;
        int y = rand() % size;
        life_mpi->setLife(x, y, 1);
    }

    double start = static_cast<double>(clock()) / CLOCKS_PER_SEC;
    for (int i = 0; i < itration; i++) life_mpi->update();
    double end = static_cast<double>(clock()) / CLOCKS_PER_SEC;
    return (end - start) * 1000;
}

double CUDA_test()
{
    life_cuda->~Life_cuda();
    life_cuda = new Life_cuda(size, size);

    for (int i = 0; i < 0.6 * size * size; i++)
    {
        int x = rand() % size;
        int y = rand() % size;
        life_cuda->setLife(x, y, 1);
    }

    double start = static_cast<double>(clock()) / CLOCKS_PER_SEC;
    for (int i = 0; i < itration; i++)  life_cuda->update(1);
    double end = static_cast<double>(clock()) / CLOCKS_PER_SEC;
    return (end - start) * 1000;
}

double CUDA_1memcpy_test()
{
    life_cuda->~Life_cuda();
    life_cuda = new Life_cuda(size, size);

    for (int i = 0; i < 0.6 * size * size; i++)
    {
        int x = rand() % size;
        int y = rand() % size;
        life_cuda->setLife(x, y, 1);
    }

    double start = static_cast<double>(clock()) / CLOCKS_PER_SEC;
    life_cuda->update(itration);
    double end = static_cast<double>(clock()) / CLOCKS_PER_SEC;
    return (end - start) * 1000;
}
