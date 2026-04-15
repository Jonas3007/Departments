#pragma once 
#include "Coordinates.h"
#include <vector>

struct ShipPlacementData
{
	int selectedShipSize;
	std::vector<Coordinates> placementCoordinates;
};