#pragma once
#include "Coordinates.h"
#include "Ship.h"
#include <string>


struct PlayerIntel
{
	string PlayerName;
	bool Alive;
	bool AllShipsPlaced;
	vector<Ship> ShipsInventory;
	vector<Coordinates> Flag;
	vector<Coordinates> ShotsFired;
	vector<Coordinates> hitsReceived;
};