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
		void TakeHit(Coordinates coords);
		void CheckDestroyed();
		
		void setGridLocation(vector<Coordinates> coords, int shipSize);
		vector<Coordinates> getGridLocation();
};

class SchlachtSchiff : public Ship
{
	public:
	SchlachtSchiff()
	{
		Size = 5;
	}
};