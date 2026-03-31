#pragma once
#include <vector>
#include "Coordinates.h"

using namespace std;

class Ship
{
	public:
	Ship(vector<Coordinates> coords, int size)
	{
		GridLocation = coords;
		Size = size;
		Destroyed = false;
	}
	Ship(vector<Coordinates> coords, int size, vector<Coordinates> hitsReceived)
	{
		GridLocation = coords;
		Size = size;
		HitsReceived = hitsReceived;
		CheckDestroyed();
	}
	//Attributes
		int Size;
		vector<Coordinates> GridLocation;
		vector<Coordinates> HitsReceived;
		bool Destroyed;
		
	//Methods
		void TakeHit(Coordinates coords);
		void CheckDestroyed();
		
		void setGridLocation(vector<Coordinates> coords);
		vector<Coordinates> getGridLocation();
};

