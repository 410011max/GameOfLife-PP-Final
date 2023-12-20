#pragma once
#include "World_cuda.h"
class Life_cuda : public World_cuda
{
public:
	Life_cuda(int x, int y) : World_cuda(x, y){}

	virtual void update(int iteration);
};
