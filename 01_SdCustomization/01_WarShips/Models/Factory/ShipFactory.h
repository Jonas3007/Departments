#pragma once
#include "Coordinates.h"
#include "Ship.h"

class ShipFactory
{
	public:
		Ship CreateShip(vector<Coordinates> coords, int shipSize);
		Ship ExistingShip(vector<Coordinates> coords, int shipSize, vector<Coordinates> hitsReceived);
};
