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
	for (Coordinates gCoords : GridLocation)
	{
		bool hitAtThisCoord = false;
		for (Coordinates hCoords : HitsReceived)
		{
			if (gCoords.Letter == hCoords.Letter && gCoords.Number == hCoords.Number)
			{
				hitAtThisCoord = true;
				break;
			}
		}
		if (!hitAtThisCoord)
		{
			Destroyed = false;
			return; // If any coordinate of the ship has not been hit, the ship is not destroyed
		}
	}

	Destroyed = true; // If all coordinates of the ship have been hit, the ship is destroyed
}

void Ship::setGridLocation(vector<Coordinates> coords)
{
	GridLocation = coords;
}

vector<Coordinates> Ship::getGridLocation()
{
	return GridLocation;
}


