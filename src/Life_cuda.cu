#include "Life_cuda.h"

__global__ void simpleLifeKernel(int width, int height, const uint8_t* grid, uint8_t* new_grid, int iteration) {
    int worldSize = width * height;
 
    for (int i = 0; i < iteration; i++)
        for (int cellId = __mul24(blockIdx.x, blockDim.x) + threadIdx.x; cellId < worldSize; cellId += blockDim.x * gridDim.x) {
            int x = cellId % width;
            int yAbs = cellId - x;
            int xLeft = (x + width - 1) % width;
            int xRight = (x + 1) % width;
            int yAbsUp = (yAbs + worldSize - width) % worldSize;
            int yAbsDown = (yAbs + width) % worldSize;
        
            int aliveCells = grid[xLeft + yAbsUp] + grid[x + yAbsUp]
            + grid[xRight + yAbsUp] + grid[xLeft + yAbs] + grid[xRight + yAbs]
            + grid[xLeft + yAbsDown] + grid[x + yAbsDown] + grid[xRight + yAbsDown];
        
            new_grid[x + yAbs] = aliveCells == 3 || (aliveCells == 2 && grid[x + yAbs]) ? 1 : 0;
        }
}

__global__ void bitLifeKernel(int width, int height, uint8_t* grid, uint8_t* new_grid, int iteration) {
    int x = blockIdx.x * blockDim.x + threadIdx.x + 1;
    int y = blockIdx.y * blockDim.y + threadIdx.y + 1;

    for (int i = 0; i < iteration; i++)
    {
        if (x <= width && y <= height) {
            for (int i = 0; i < 8; ++i) {
                uint8_t data0 = grid[(x - 1) * width + (y - 1)];
                uint8_t data1 = grid[(x    ) * width + (y - 1)];
                uint8_t data2 = grid[(x + 1) * width + (y - 1)];

                data0 <<= 1;
                data1 <<= 1;
                data2 <<= 1;

                uint8_t aliveCells = (data0 & 0x14) + (data1 & 0x14) + (data2 & 0x14);
                aliveCells >>= 2;

                int index = x * width + y;

                new_grid[index] = 0;
                if (aliveCells == 3) {
                    new_grid[index] = 1;
                } else if (aliveCells == 2 && grid[index] == 1) {
                    new_grid[index] = 1;
                }

                x = (x + 1) % width;
                y = (y + 1) % height;
            }
        }    
    }
}


__global__ void kernelUpdate(int width, int height, uint8_t* grid, uint8_t* new_grid, int iteration) {
    int x = blockIdx.x * blockDim.x + threadIdx.x + 1;
    int y = blockIdx.y * blockDim.y + threadIdx.y + 1;

    for (int i = 0; i < iteration; i++)
    {
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
            if (m == 3) new_grid[index] = 1;          
            if (m == 2) new_grid[index] = grid[index];
        }
    }

}

void Life_cuda::update(int iteration)
{
	dim3 blockDim(5, 5);
    dim3 gridDim(width / blockDim.x, height / blockDim.y);

    uint8_t* d_grid;
	uint8_t* d_new_grid;

    // Allocate memory
    cudaMalloc((void**)&d_grid, worldSize * sizeof(uint8_t));
    cudaMalloc((void**)&d_new_grid, worldSize * sizeof(uint8_t));

    cudaMemcpy(d_grid, grid, worldSize * sizeof(uint8_t), cudaMemcpyHostToDevice);

    kernelUpdate<<<gridDim, blockDim>>>(width, height, d_grid, d_new_grid, iteration);
    // simpleLifeKernel<<<gridDim, blockDim>>>(width, height, d_grid, d_new_grid, iteration);
    // bitLifeKernel<<<gridDim, blockDim>>>(width, height, d_grid, d_new_grid, iteration);

    cudaMemcpy(new_grid, d_new_grid, worldSize * sizeof(uint8_t), cudaMemcpyDeviceToHost);

    // Free allocated memory
    cudaFree(d_grid);
    cudaFree(d_new_grid);

    swapGrids();
}