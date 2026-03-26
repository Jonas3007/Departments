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
		bool AllShipsPlaced;
		vector<Ship> ShipInventory;
		vector<Coordinates> Flag;
		vector<Coordinates> hits;
		vector<Coordinates> hitsReceived;
		// ShipsToPlace = {{ShipSize, Count}}
		vector<ShipConfig> ShipsToPlace = { {5, 1}, {4, 1}, {3, 1}, {2, 1} }; // Default ship configuration, can be modified as needed
		
	
	//Methods
		void setName(string name);
		bool checkIfShipSizeAvailable(int shipSize);
		void placeShip(vector<Coordinates> coords, int shipSize);
		void placeFlag(Coordinates coords);
		bool checkForHit(Coordinates coords);
		bool checkIfAllShipsPlaced();
		void checkAllShipsDestroyed();
		void updateShipStatus();
		
};