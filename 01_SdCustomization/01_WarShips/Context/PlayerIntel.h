#pragma once
#include "Coordinates.h"
#include "Ship.h"


struct PlayerIntel
{
	bool Alive;
	vector<Ship> ShipsInventory;
	vector<Coordinates> Flag;
	vector<Coordinates> ShotsFired;
	vector<Coordinates> hitsReceived;
};