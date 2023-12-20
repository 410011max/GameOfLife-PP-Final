#pragma once
#include "World_pthread.h"
class Life_pthread : public World_pthread
{
public:
	Life_pthread(int x, int y) : World_pthread(x, y){}

	virtual void update();
};
