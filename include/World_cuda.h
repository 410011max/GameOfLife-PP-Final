#pragma once
#include <iostream>

using std::malloc;
using std::cout;
using std::endl;

class World_cuda
{
protected:
	uint8_t* grid;
	uint8_t* new_grid;
	int width;
	int height;
	int worldSize;

	int getNewLife(int x, int y);
	void setNewLife(int x, int y, int val);
	void swapGrids();

public:
	World_cuda(int, int);
	~World_cuda();

	int getNeighbors(int x, int y);

	int getLifeform(int x, int y);
	void setLife(int x, int y, int val);
	virtual void update(){ }

	void print();
};
