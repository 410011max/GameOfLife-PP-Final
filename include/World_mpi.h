#pragma once
#include <iostream>

using std::malloc;
using std::cout;
using std::endl;

class World_mpi
{
protected:
	short* grid;
	short* new_grid;
	unsigned int width;
	unsigned int height;

	int getNewLife(int x, int y);
	void setNewLife(int x, int y, int val);
	void swapGrids();

public:
	World_mpi(int, int);
	~World_mpi();

	int getNeighbors(int, int);

	int getLifeform(int x, int y);
	void setLife(int x, int y, int val);
	virtual void update(){ }

	void print();
};

