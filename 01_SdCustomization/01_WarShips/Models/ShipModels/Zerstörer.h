#pragma once 
#include "Ship.h"
#include "Coordinates.h"
#include <vector>

class Zerstörer : public Ship
{
	public:
	Zerstörer()
	{
		Size = 3;
	}
};	