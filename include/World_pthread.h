#pragma once
#include <iostream>

using std::malloc;
using std::cout;
using std::endl;

#ifndef _WORLD_H
#define _WORLD_H

class World_pthread
{
protected:
	short* grid;
	short* new_grid;
	unsigned int width;
	unsigned int height;

	int getNewLife(int x, int y);
	//void setNewLife(int x, int y, int val);
	void swapGrids();

public:
	World_pthread(int, int);
	~World_pthread();

	int getNeighbors(int, int);
	int getWidth();
	int getHeight();

	int getLifeform(int x, int y);
	void setLife(int x, int y, int val);
	virtual void update(){ }

	void print();
	void setNewLife(int x, int y, int val);
};

#endif
