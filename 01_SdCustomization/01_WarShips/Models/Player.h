#pragma once
#include "Coordinates.h"
#include "Ship.h"
#include "ShipConfig.h"
#include <vector>
#include <string>

class Player
{
	public:
	//Attributes
		string Name;
		bool AllShipsDestroyed;
		bool AllShipsPlaced;
		vector<Ship> ShipInventory;
		vector<Coordinates> hits;
		vector<Coordinates> hitsReceived;
		vector<Coordinates> misses;
		// ShipsToPlace = {{ShipSize, Count}}
		vector<ShipConfig> ShipsToPlace = { {5, 0}, {4, 0}, {3, 0}, {2, 1} }; // Default ship configuration, can be modified as needed
		
		
	//Methods
		void setName(string name);
		bool checkIfShipSizeAvailable(int shipSize);
		void placeShip(vector<Coordinates> coords, int shipSize);
		void miss(Coordinates coords);
		bool checkForHit(Coordinates coords);
		void checkIfAllShipsPlaced();
		void checkAllShipsDestroyed();
		void updateShipStatus();
		void takeHit(Coordinates coords);
		void removeShipFromInventory(Coordinates coords);
		vector<Coordinates> getAllShipCoordinates();
		
};