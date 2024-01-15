#include <iostream>
#include <chrono>
#include <vector>
#include <unistd.h>
#include <mpi.h>

using namespace std;

const int WIDTH = 496;
const int HEIGHT = 500;
#define MAX_CNT 999
int cnt = 0;
float total_time = 0.0;

// short * grid = (short *)malloc(WIDTH * HEIGHT * sizeof(short));
// short * new_grid = (short *)malloc(WIDTH * HEIGHT * sizeof(short));

short *grid, *new_grid, *local_grid, *local_new_grid;

void updateGrid(int local_height) {
    for (unsigned int i = 1; i < local_height - 1; i++) {
        for (unsigned int j = 1; j < WIDTH - 1; j++) {
            int m = 0;
            // Check the eight neighbors and wrap around at the edges
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (dx == 0 && dy == 0) continue; // Skip the cell itself
                    int x = (i + dx + HEIGHT) % HEIGHT;
                    int y = (j + dy + WIDTH) % WIDTH;
                    m += local_grid[x * WIDTH + y];
                }
            }

            // Apply the rules of the game
            int idx = i * WIDTH + j;
            if (m == 3) {
                local_new_grid[idx] = 1;
            } else if (m == 2) {
                local_new_grid[idx] = local_grid[idx];
            } else {
                local_new_grid[idx] = 0;
            }
        }
    }
    local_grid = local_new_grid; // Update the grid
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int local_height = HEIGHT / size;
    
    local_grid = new short[local_height * WIDTH];
    local_new_grid = new short[local_height * WIDTH];

    if (rank == 0) {
        grid = new short[WIDTH * HEIGHT];
        new_grid = new short[WIDTH * HEIGHT];
        for (unsigned int i = 0; i < WIDTH * HEIGHT; i++)
        {
            grid[i] = 0;
            new_grid[i] = 0;
        }
    }
    for (unsigned int i = 0; i < local_height * WIDTH; i++)
    {
        local_grid[i] = 0;
        local_new_grid[i] = 0;
    }


    for (int cnt = 0; cnt < MAX_CNT; ++cnt) {
        auto start = std::chrono::high_resolution_clock::now();
        MPI_Scatter(grid, local_height * WIDTH, MPI_SHORT,
                local_grid, local_height * WIDTH, MPI_SHORT, 0, MPI_COMM_WORLD);
        updateGrid(local_height);

        MPI_Gather(local_new_grid, local_height * WIDTH, MPI_SHORT,
                   new_grid, local_height * WIDTH, MPI_SHORT, 0, MPI_COMM_WORLD);
        if (rank == 0){
            // cout << cnt << endl;
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> elapsed = end - start;
            total_time += elapsed.count();
        }

        swap(local_grid, local_new_grid);
        if (rank == 0) {
            swap(grid, new_grid);
        }
    }


    if (rank == 0) {
        cout << total_time / MAX_CNT << " ms\n";
        delete[] grid;
        delete[] new_grid;
        
    }
    delete[] local_grid;
    // delete[] local_new_grid;
    MPI_Finalize();
    return 0;
}
