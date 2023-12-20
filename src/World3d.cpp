#include "World3d.h"

namespace world3
{
	World3d::World3d(int w, int h, int d)
	{
		width = w;
		height = h;
		depth = d;
		worldSize = width * height * depth;
		grid = (short *)malloc(worldSize*sizeof(short));
		new_grid = (short *)malloc(worldSize*sizeof(short));

		for (int i = 0; i < worldSize; i++)
		{
			grid[i] = 0;
			new_grid[i] = 0;
		}
	}

	World3d::~World3d(){
		free(grid); free(new_grid);
	}

	int World3d::getNewLife(int x, int y, int z)
	{
		return grid[y + x*width + z*width*height];
	}

	void World3d::setNewLife(int x, int y, int z, int val)
	{
		new_grid[y + x*width + z*width*height] = val;
	}

	void World3d::swapGrids()
	{
		std::swap(grid, new_grid);
	}

	int World3d::getNeighbors(int x, int y, int z)
	{
		int count = 0;
		
		if (x > 0 && (x < width - 1) && y > 0 && (y < height - 1) && z > 0 && (z < depth - 1)) {
			count += grid[(y+1) + x*width + z*width*height];
			count += grid[(y + 1) + x*width + (z+1)*width*height];
			count += grid[(y + 1) + x*width + (z-1)*width*height];

			count +=  grid[(y + 1) + (x + 1)*width + (z + 1)*width*height];
			count += grid[(y + 1) + (x + 1)*width + (z)*width*height];
			count += grid[(y + 1) + (x + 1)*width + (z - 1)*width*height];
			
			count += grid[(y + 1) + (x - 1)*width + z*width*height];
			count += grid[(y + 1) + (x - 1)*width + (z + 1)*width*height];
			count += grid[(y + 1) + (x - 1)*width + (z - 1)*width*height];
			//
			count += grid[(y - 1) + x*width + z*width*height];
			count += grid[(y - 1) + x*width + (z + 1)*width*height];
			count += grid[(y - 1) + x*width + (z - 1)*width*height];

			count += grid[(y - 1) + (x + 1)*width + (z + 1)*width*height];
			count += grid[(y - 1) + (x + 1)*width + (z)*width*height];
			count += grid[(y - 1) + (x + 1)*width + (z - 1)*width*height];

			count += grid[(y - 1) + (x - 1)*width + z*width*height];
			count += grid[(y - 1) + (x - 1)*width + (z + 1)*width*height];
			count += grid[(y - 1) + (x - 1)*width + (z - 1)*width*height];
			//
			count += grid[(y) + x*width + (z + 1)*width*height];
			count += grid[(y) + x*width + (z - 1)*width*height];

			count += grid[(y) + (x + 1)*width + (z + 1)*width*height];
			count += grid[(y) + (x + 1)*width + (z)*width*height];
			count += grid[(y) + (x + 1)*width + (z - 1)*width*height];

			count += grid[(y) + (x - 1)*width + z*width*height];
			count += grid[(y) + (x - 1)*width + (z + 1)*width*height];
			count += grid[(y) + (x - 1)*width + (z - 1)*width*height];
		}
		return count;
	}

	int World3d::getLifeform(int x, int y, int z)
	{
		return grid[y + x*width + z*width*height];
	}

	void World3d::setLife(int x, int y, int z, int val)
	{
		grid[y + x*width + z*width*height] = val;
	}

	void World3d::print()
	{
		for (int i = 0; i < height; i++)
		{
			cout << endl;
			for (int j = 0; j < width; j++)
			{
				for (int k = 0; k < depth; k++)
				{
					cout << getLifeform(j, i, k) << " ";
				}
			}
		}
		cout << endl;
		cout << endl;
	}
}
