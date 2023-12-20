#include "Life.h"


__global__ void kernelUpdate(int width, int height, short* grid, short* new_grid) {
    int x = blockIdx.x * blockDim.x + threadIdx.x + 1;
    int y = blockIdx.y * blockDim.y + threadIdx.y + 1;

    if (x <= width && y <= height) {
        // int m = getNeighbors(x, y, 1);
        int m = 0;
        m += grid[(x - 1)*width + (y    )];
        m += grid[(x    )*width + (y - 1)];
        m += grid[(x - 1)*width + (y - 1)];
        m += grid[(x + 1)*width + (y    )];
        m += grid[(x    )*width + (y + 1)];
        m += grid[(x + 1)*width + (y + 1)];
        m += grid[(x + 1)*width + (y - 1)];
        m += grid[(x - 1)*width + (y + 1)];
        
        if (m == 3)
            new_grid[x*width + y] = 1;
            // setNewLife(x, y, 1);
        if (m == 2)
            new_grid[x*width + y] = grid[x*width + y];
            // setNewLife(x, y, getLifeform(x, y));
        if (m != 3 && m != 2)
            new_grid[x*width + y] = 0;
            // setNewLife(x, y, 0);
    }
}

void Life::update()
{
	dim3 blockDim(5, 5);
    dim3 gridDim(width / blockDim.x, height / blockDim.y);

    short* d_grid;
	short* d_new_grid;

    // Allocate memory
    cudaHostRegister(grid, worldSize*sizeof(short), cudaHostRegisterMapped);
    cudaHostGetDevicePointer(&d_grid, grid, 0);
    cudaHostRegister(new_grid, worldSize*sizeof(short), cudaHostRegisterMapped);
    cudaHostGetDevicePointer(&d_new_grid, new_grid, 0);

    kernelUpdate<<<gridDim, blockDim>>>(width, height, d_grid, d_new_grid);

    cudaDeviceSynchronize();
    // Free allocated memory
    cudaHostUnregister(grid);
    cudaHostUnregister(new_grid);

	swapGrids();
}