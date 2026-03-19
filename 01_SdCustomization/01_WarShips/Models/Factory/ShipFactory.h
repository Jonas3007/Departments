#pragma once
#include "Coordinates.h"
#include "Ship.h"

class ShipFactory
{
	public:
		static Ship CreateShip(vector<Coordinates> coords, int shipSize);
};
