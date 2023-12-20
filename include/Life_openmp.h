#pragma once
#include "World_openmp.h"
class Life_openmp : public World_openmp
{
public:
	Life_openmp(int x, int y) : World_openmp(x, y){}

	virtual void update();
};
