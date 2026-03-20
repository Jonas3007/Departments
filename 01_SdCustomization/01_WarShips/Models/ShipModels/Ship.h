#pragma once
#include <vector>
#include "Coordinates.h"

using namespace std;

class Ship
{
	public:
	Ship(vector<Coordinates> coords)
	{
		GridLocation = coords;
		Destroyed = false;
	}
	//Attributes
		int Size;
		vector<Coordinates> GridLocation;
		vector<Coordinates> HitsReceived;
		bool Destroyed;
		
	//Methods
		virtual void TakeHit(Coordinates coords);
		virtual void CheckDestroyed();
		
		virtual void setGridLocation(vector<Coordinates> coords, int shipSize);
		virtual vector<Coordinates> getGridLocation();
};

