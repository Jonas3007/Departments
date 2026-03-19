#pragma once 
#include <vector>
#include "Coordinates.h"
#include "Ship.h"

class U_Boot : public Ship
{
	public:
	U_Boot()
	{
		Size = 2;
	}
};