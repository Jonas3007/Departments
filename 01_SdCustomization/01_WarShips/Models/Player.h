#pragma once

#include "Coordinates.h"
#include "Ship.h"
#include "ShipConfig.h"
#include <vector>
#include <string>

using namespace std;
class Player
{
	public:
	//Attributes
		bool AllShipsDestroyed;
		std::vector<Ship> ShipInventory;
		vector<Coordinates> Flag;
		vector<Coordinates> ShotsFired;
		vector<Coordinates> hitsReceived;
		// ShipConfig: ShipSize and Count
		vector<ShipConfig> ShipsToPlace = { {5, 1}, {4, 2}, {3, 3}, {2, 4} }; // Default ship configuration, can be modified as needed
		
	
	//Methods
		void placeShip(vector<Coordinates> coords, int shipSize);
		void placeFlag(Coordinates coords);
		void FireShot(Coordinates coords);
		bool CheckForHit(Coordinates coords);
		bool validateShipPlacement(vector<Coordinates> coords, int shipSize);
		
};