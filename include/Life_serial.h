#pragma once
#include "World_serial.h"
class Life_serial : public World_serial
{
public:
	Life_serial(int x, int y) : World_serial(x, y){}

	virtual void update();
};
