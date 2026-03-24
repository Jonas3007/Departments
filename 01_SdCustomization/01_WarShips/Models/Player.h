#pragma once
#include "Coordinates.h"
#include "Ship.h"
#include "ShipConfig.h"
#include <vector>
#include <string>
#include "PlayerIntel.h"


class Player
{
	public:
	//Attributes
		string Name;
		bool AllShipsDestroyed;
		vector<Ship> ShipInventory;
		vector<Coordinates> Flag;
		vector<Coordinates> ShotsFired;
		vector<Coordinates> hitsReceived;
		// ShipsToPlace = {{ShipSize, Count}}
		vector<ShipConfig> ShipsToPlace = { {5, 1}, {4, 2}, {3, 3}, {2, 4} }; // Default ship configuration, can be modified as needed
		
	
	//Methods
		void placeShip(vector<Coordinates> coords, int shipSize);
		void placeFlag(Coordinates coords);
		void fireShot(Coordinates coords);
		bool checkForHit(Coordinates coords);
		void checkIfAllShipsPlaced(PlayerIntel *playerIntel);
		void checkAllShipsDestroyed();
		void updateShipStatus();
		
};