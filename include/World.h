#pragma once
#include <iostream>

using std::malloc;
using std::cout;
using std::endl;

#ifndef _WORLD_H
#define _WORLD_H

class World
{
protected:
	short* grid;
	short* new_grid;
	int width;
	int height;
	int worldSize;

	int getNewLife(int x, int y);
	void setNewLife(int x, int y, int val);
	void swapGrids();

public:
	World(int, int);
	~World();

	int getNeighbors(int x, int y);

	int getLifeform(int x, int y);
	void setLife(int x, int y, int val);
	virtual void update(){ }

	void print();
};

#endif
