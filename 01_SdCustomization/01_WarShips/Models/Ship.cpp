#include "Ship.h"
#include "Coordinates.h"
#include <vector>

void Ship::TakeHit(Coordinates coords)
{
	HitsReceived.push_back(coords);
	CheckDestroyed();
}

void Ship::CheckDestroyed()
{
	for(Coordinates gCoords : GridLocation)
	{
		for(Coordinates hCoords : HitsReceived)
		{
			if (gCoords.Letter == hCoords.Letter && gCoords.Number == hCoords.Number)
			{
				Destroyed = true;
			}
			else
			{
				Destroyed = false;
				return;
			}
		}
	}
}

void Ship::setGridLocation(vector<Coordinates> coords)
{
	GridLocation = coords;
}

vector<Coordinates> Ship::getGridLocation()
{
	return GridLocation;
}