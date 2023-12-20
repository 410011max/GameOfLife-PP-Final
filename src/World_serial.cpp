#include "World_serial.h"


World_serial::World_serial(int w, int h)
{
	width = w;
	height = h;
	grid = (short *)malloc((width + 2)*(height + 2)*sizeof(short));
	new_grid = (short *)malloc((width + 2)*(height + 2)*sizeof(short));

	for (unsigned int i = 0; i < (width + 2)*(height + 2); i++)
	{
		grid[i] = 0;
		new_grid[i] = 0;
	}
}

World_serial::~World_serial(){ 
	free(grid); free(new_grid); 
}

int World_serial::getNewLife(int x, int y)
{ 
	return grid[x*(width + 2) + y]; 
}

void World_serial::setNewLife(int x, int y, int val)
{ 
	new_grid[x*(width + 2) + y] = val; 
}

void World_serial::swapGrids()
{
	std::swap(grid, new_grid);
}

int World_serial::getNeighbors(int x, int y, int val)
{
	int count = 0;

	count += grid[(x-1)*(width + 2) + (y)];
	count += grid[(x)*(width + 2) + (y-1)];
	count += grid[(x - 1)*(width + 2) + (y-1)];
	count += grid[(x + 1)*(width + 2) + (y)];

	count += grid[(x)*(width + 2) + (y+1)];
	count += grid[(x+1)*(width + 2) + (y+1)];
	count += grid[(x+1)*(width + 2) + (y-1)];
	count += grid[(x - 1)*(width + 2) + (y+1)];
	
	return count;
}

int World_serial::getLifeform(int x, int y)
{ 
	return grid[x*(width + 2) + y]; 
}

void World_serial::setLife(int x, int y, int val)
{ 
	grid[x*(width + 2) + y] = val; 
}

void World_serial::print()
{
	for (unsigned int i = 1; i <= height; i++)
	{
		cout << endl;
		for (unsigned int j = 1; j <= width; j++)
		{
			cout << getLifeform(j, i) << " ";
		}
	}
	cout << endl;

}
