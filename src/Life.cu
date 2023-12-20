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
        
        int index = x*width + y;
        new_grid[index] = 0;
        if (m == 3)             new_grid[index] = 1;          
        if (m == 2)             new_grid[index] = grid[index];
    }
}

void Life::update()
{
	dim3 blockDim(5, 5);
    dim3 gridDim(width / blockDim.x, height / blockDim.y);

    short* d_grid;
	short* d_new_grid;

    // Allocate memory
    cudaMalloc((void**)&d_grid, worldSize * sizeof(short));
    cudaMalloc((void**)&d_new_grid, worldSize * sizeof(short));

    cudaMemcpy(d_grid, grid, worldSize * sizeof(short), cudaMemcpyHostToDevice);

    kernelUpdate<<<gridDim, blockDim>>>(width, height, d_grid, d_new_grid);

    cudaMemcpy(new_grid, d_new_grid, worldSize * sizeof(short), cudaMemcpyDeviceToHost);

    // Free allocated memory
    cudaFree(d_grid);
    cudaFree(d_new_grid);

    swapGrids();
}