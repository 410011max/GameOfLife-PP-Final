#include "World.h"


World::World(int w, int h)
{
	width = w;
	height = h;
	worldSize = width * height;
	grid = (uint8_t *)malloc(worldSize*sizeof(uint8_t));
	new_grid = (uint8_t *)malloc(worldSize*sizeof(uint8_t));

	for (int i = 0; i < worldSize; i++)
	{
		grid[i] = 0;
		new_grid[i] = 0;
	}
}

World::~World(){ 
	free(grid); free(new_grid); 
}

int World::getNewLife(int x, int y)
{ 
	return grid[x*width + y]; 
}

void World::setNewLife(int x, int y, int val)
{ 
	new_grid[x*width + y] = val; 
}

void World::swapGrids()
{
	std::swap(grid, new_grid);
}

int World::getNeighbors(int x, int y)
{
	int count = 0;
	if (x > 0 && (x < width - 1) && y > 0 && (y < height - 1)) {
		count += grid[(x - 1)*width + (y    )];
		count += grid[(x    )*width + (y - 1)];
		count += grid[(x - 1)*width + (y - 1)];
		count += grid[(x + 1)*width + (y    )];
		count += grid[(x    )*width + (y + 1)];
		count += grid[(x + 1)*width + (y + 1)];
		count += grid[(x + 1)*width + (y - 1)];
		count += grid[(x - 1)*width + (y + 1)];
	}
	
	return count;
}

int World::getLifeform(int x, int y)
{ 
	return grid[x*width + y]; 
}

void World::setLife(int x, int y, int val)
{ 
	grid[x*width + y] = val; 
}

void World::print()
{
	for (int i = 0; i < height; i++)
	{
		cout << endl;
		for (int j = 0; j < width; j++)
		{
			cout << getLifeform(j, i) << " ";
		}
	}
	cout << endl;

}
