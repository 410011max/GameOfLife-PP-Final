#pragma once
#include "World_mpi.h"
class Life_mpi : public World_mpi
{
public:
	Life_mpi(int x, int y) : World_mpi(x, y){}

	virtual void update();
};
