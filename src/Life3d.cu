#include "Life3d.h"

namespace life3
{
	__global__ void kernelUpdate(int width, int height, int depth, short* grid, short* new_grid)
    {
        int x = blockIdx.x * blockDim.x + threadIdx.x + 1;
        int y = blockIdx.y * blockDim.y + threadIdx.y + 1;
        int z = blockIdx.z * blockDim.z + threadIdx.z + 1;

        if (x <= width && y <= height && z <= depth)
        {
            // int m = getNeighbors(x, y, z);
            int m = 0;
		
			if (x > 0 && (x < width - 1) && y > 0 && (y < height - 1) && z > 0 && (z < depth - 1)) {
				m += grid[(y + 1) + x*width + z*width*height];
				m += grid[(y + 1) + x*width + (z+1)*width*height];
				m += grid[(y + 1) + x*width + (z-1)*width*height];

				m += grid[(y + 1) + (x + 1)*width + (z + 1)*width*height];
				m += grid[(y + 1) + (x + 1)*width + (z)*width*height];
				m += grid[(y + 1) + (x + 1)*width + (z - 1)*width*height];
				
				m += grid[(y + 1) + (x - 1)*width + z*width*height];
				m += grid[(y + 1) + (x - 1)*width + (z + 1)*width*height];
				m += grid[(y + 1) + (x - 1)*width + (z - 1)*width*height];
				//
				m += grid[(y - 1) + x*width + z*width*height];
				m += grid[(y - 1) + x*width + (z + 1)*width*height];
				m += grid[(y - 1) + x*width + (z - 1)*width*height];

				m += grid[(y - 1) + (x + 1)*width + (z + 1)*width*height];
				m += grid[(y - 1) + (x + 1)*width + (z)*width*height];
				m += grid[(y - 1) + (x + 1)*width + (z - 1)*width*height];

				m += grid[(y - 1) + (x - 1)*width + z*width*height];
				m += grid[(y - 1) + (x - 1)*width + (z + 1)*width*height];
				m += grid[(y - 1) + (x - 1)*width + (z - 1)*width*height];
				//
				m += grid[(y) + x*width + (z + 1)*width*height];
				m += grid[(y) + x*width + (z - 1)*width*height];

				m += grid[(y) + (x + 1)*width + (z + 1)*width*height];
				m += grid[(y) + (x + 1)*width + (z)*width*height];
				m += grid[(y) + (x + 1)*width + (z - 1)*width*height];

				m += grid[(y) + (x - 1)*width + z*width*height];
				m += grid[(y) + (x - 1)*width + (z + 1)*width*height];
				m += grid[(y) + (x - 1)*width + (z - 1)*width*height];
			}

			int index = z * width * height + y * width + x;
            new_grid[index] = 0;
            if (m < 3 || m > 5) 	new_grid[index] = 0;			// setNewLife(i, j, k, 0);
            if (m == 4 || m == 5) 	new_grid[index] = grid[index];	// setNewLife(i, j, k, getLifeform(i, j, k));
            if (m == 3) 			new_grid[index] = 1;			// setNewLife(i, j, k, 1);
        }
    }

    void Life3d::update()
    {
        dim3 blockDim(5, 5, 5);
        dim3 gridDim(width / blockDim.x, height / blockDim.y, depth / blockDim.z);

        short* d_grid;
        short* d_new_grid;

		// Allocate memory
        cudaMalloc((void**)&d_grid, worldSize * sizeof(short));
        cudaMalloc((void**)&d_new_grid, worldSize * sizeof(short));

        cudaMemcpy(d_grid, grid, worldSize * sizeof(short), cudaMemcpyHostToDevice);

        kernelUpdate<<<gridDim, blockDim>>>(width, height, depth, d_grid, d_new_grid);

        cudaMemcpy(new_grid, d_new_grid, worldSize * sizeof(short), cudaMemcpyDeviceToHost);

		// Free allocated memory
        cudaFree(d_grid);
        cudaFree(d_new_grid);

        swapGrids();
    }
}
