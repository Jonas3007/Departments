#pragma once 
#include "Ship.h"
#include "Coordinates.h"
#include <vector>


class SchlachtSchiff : public Ship
{
	public:
	SchlachtSchiff()
	{
		Size = 5;
	}
};